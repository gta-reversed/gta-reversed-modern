/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include <win.h> // TODO: Remove (Included because of isForeground)

#include "Fx.h"
#include "CutsceneMgr.h"
#include "Rubbish.h"
#include <TempColModels.h>

uint32 MAX_NUM_CUTSCENE_OBJECTS = 50;
uint32 MAX_NUM_CUTSCENE_PARTICLE_EFFECTS = 8;
uint32 MAX_NUM_CUTSCENE_ITEMS_TO_HIDE = 50;
uint32 MAX_NUM_CUTSCENE_ATTACHMENTS = 50;

// 0x5B0380
int32 CCutsceneMgr::AddCutsceneHead(CObject* object, int32 arg1) {
    return 0;
}

// 0x4D5DB0
void CCutsceneMgr::AppendToNextCutscene(const char* objectName, const char* animName) {
    const auto CopyAndLower = [](auto&& dst, const char* src) {
        strcpy_s(dst, src);
        _strlwr_s(dst);
    };

    auto& num = ms_numAppendObjectNames;
    CopyAndLower(ms_cAppendObjectName[num], objectName);
    CopyAndLower(ms_cAppendAnimName[num], animName);
    num++;
}

// 0x5B0450
void CCutsceneMgr::AttachObjectToBone(CCutsceneObject* attachment, CCutsceneObject* object, int32 boneId) {
    attachment->m_pAttachmentObject = object;
    attachment->m_nAttachBone       = RpHAnimIDGetIndex(GetAnimHierarchyFromSkinClump(object->m_pRwClump), boneId);
}

// 0x5B0480
void CCutsceneMgr::AttachObjectToFrame(CCutsceneObject* attachment, CEntity* object, const char* frameName) {
    attachment->m_pAttachmentObject = nullptr;
    attachment->m_pAttachToFrame    = RpAnimBlendClumpFindFrame(object->m_pRwClump, frameName)->m_pFrame;
}

// 0x5B04B0
void CCutsceneMgr::AttachObjectToParent(CCutsceneObject* attachment, CEntity* object) {
    attachment->m_pAttachmentObject = nullptr;
    attachment->m_pAttachToFrame    = RpClumpGetFrame(object->m_pRwClump);
}

// 0x4D5E20
void CCutsceneMgr::BuildCutscenePlayer() {
    const auto plyr = FindPlayerPed();
    CClothes::RebuildPlayerIfNeeded(plyr);
    CStreaming::RequestModel(MODEL_CSPLAY, STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED);
    CStreaming::LoadAllRequestedModels(true);
    CClothes::RebuildCutscenePlayer(plyr, true);
}

// 0x5B0130
RpAtomic* CalculateBoundingSphereRadiusCB(RpAtomic* atomic, void* data) {
    auto& maxRadius = *(float*)data;

    const auto sp = RpAtomicGetBoundingSphere(atomic);

    // Take bound sphere's center, and transform it all back to the world
    auto center = sp->center;
    for (RwFrame* frame = RpAtomicGetFrame(atomic); RwFrameGetParent(frame); frame = RwFrameGetParent(frame)) {
        RwV3dTransformPoint(&center, &center, RwFrameGetMatrix(frame));
    }

    // Not sure? I guess `center` is now just the offset from the object space center?
    // Fuck knows...
    maxRadius = std::max(RwV3dLength(&center) + sp->radius, maxRadius);

    return atomic;
}

// 0x5B01E0
void CCutsceneMgr::UpdateCutsceneObjectBoundingBox(RpClump* clump, eModelID modelId) {
    assert(IsModelIDForCutScene(modelId));
    assert(RwObjectGetType(clump) == rpCLUMP);

    // Figure out bounding sphere radius
    float radius = 0.f;
    RpClumpForAllAtomics(clump, CalculateBoundingSphereRadiusCB, &radius);

    // Now update the col model with it
    auto& cm = CTempColModels::ms_colModelCutObj[modelId - MODEL_CUTOBJ01];
    cm.GetBoundingSphere().m_fRadius = radius;
    cm.GetBoundingBox() = CBoundingBox{ // Bounding box of the sphere basically
        {-radius, -radius, -radius},
        { radius,  radius,  radius}
    };
}

// 0x5B02A0
CCutsceneObject* CCutsceneMgr::CreateCutsceneObject(eModelID modelId) {
    CStreaming::ImGonnaUseStreamingMemory();

    // Create col model for it (If cutscene object)
    if (IsModelIDForCutScene(modelId)) {
        const auto mi = CModelInfo::GetModelInfo(modelId);
        mi->SetColModel(&CTempColModels::ms_colModelCutObj[modelId - MODEL_CUTOBJ01]);
        UpdateCutsceneObjectBoundingBox(mi->m_pRwClump, modelId);
    }

    // Actually create the object now
    const auto obj = ms_pCutsceneObjects[ms_numCutsceneObjs++] = new CCutsceneObject{};
    obj->SetModelIndex(modelId);

    CStreaming::IHaveUsedStreamingMemory();

    return obj;
}

// 0x4D5ED0
void CCutsceneMgr::DeleteCutsceneData() {
    DeleteCutsceneData_overlay();
    CStreaming::SetMissionDoesntRequireModel(MODEL_CSPLAY);
    if (restoreEverythingAfterCutscene) {
        LoadEverythingBecauseCutsceneDeletedAllOfIt();
    }
}

// 0x5AFD60
void CCutsceneMgr::DeleteCutsceneData_overlay() {
    if (!ms_cutsceneLoadStatus) {
        return;
    }

    // We suspend the timer here (is resumed at the end)
    CTimer::Suspend();

    // Restore multipliers
    CPopulation::PedDensityMultiplier = m_fPrevPedDensity;
    CCarCtrl::CarDensityMultiplier = m_fPrevCarDensity;

    // Restore extra colors
    if (m_PrevExtraColourOn) {
        CTimeCycle::StartExtraColour(m_PrevExtraColour, false);
    } else {
        CTimeCycle::StopExtraColour(false);
    }

    // Make hidden entities visible again
    for (auto& e : ms_pHiddenEntities | rng::views::take(ms_iNumHiddenEntities)) {
        if (e) {
            CEntity::CleanUpOldReference(e);
            e->m_bIsVisible = true;
        }
    }
    ms_iNumHiddenEntities = 0;

    // Destroy particle effects
    for (auto& fx : ms_pParticleEffects | rng::views::take(ms_iNumParticleEffects)) {
        if (fx.m_pFxSystem) {
            g_fxMan.DestroyFxSystem(fx.m_pFxSystem);
            fx.m_pFxSystem = nullptr;
        }
    }
    ms_iNumParticleEffects = 0;

    CMessages::ClearMessages(false);
    CRubbish::SetVisibility(false);
    
    // Delete cutscene objects
    for (auto& obj : ms_pCutsceneObjects | rng::views::take(ms_numCutsceneObjs)) {
        assert(obj);

        CWorld::Remove(obj);
        obj->DeleteRwObject();
        delete obj;
    }
    ms_numCutsceneObjs = 0;

    // Unload anims
    if (ms_animLoaded) {
        CAnimManager::RemoveLastAnimFile();
    }
    ms_animLoaded = false;
    ms_cutsceneAssociations.DestroyAssociations();
    ms_aUncompressedCutsceneAnims[0][0] = 0;
    ms_numUncompressedCutsceneAnims = 0;

    if (dataFileLoaded) {
        TheCamera.RestoreWithJumpCut();
        TheCamera.SetWideScreenOff();
        TheCamera.DeleteCutSceneCamDataMemory();
    }

    CIplStore::ClearIplsNeededAtPosn();

    ms_cutsceneLoadStatus = false;
    ms_running = false;

    const auto plyr = FindPlayerPed();
    const auto pad = CPad::GetPad(0);
    plyr->m_bIsVisible = true;
    pad->bPlayerSkipsToDestination = false;
    pad->Clear(false, false); // moved up here
    plyr->GetPlayerInfoForThisPlayerPed()->MakePlayerSafe(0, 10000.0);

    if (_stricmp(ms_cutsceneName, "finale") != 0) {
        AudioEngine.StopCutsceneTrack(true);
        CAudioEngine::EnableEffectsLoading();
        CAEPedSpeechAudioEntity::EnableAllPedSpeech();
    }

    CStreaming::ms_disableStreaming = false;
    CWorld::bProcessCutsceneOnly = false;

    if (dataFileLoaded) {
        CGame::DrasticTidyUpMemory(TheCamera.CCamera::GetScreenFadeStatus() == NAME_FADE_IN ? true : false);
    }

    // there's some code to restore the player's stored weapons, but it
    // doesn't seem to do anything, cause the guarding `if`'s
    // condition is always false

    // Tell the streamer that we don't need any (possibly) loaded special chars
    for (const auto modelId : ms_iModelIndex | rng::views::take(ms_numLoadObjectNames)) {
        if (CTheScripts::ScriptResourceManager.HasResourceBeenRequested(modelId, RESOURCE_TYPE_MODEL_OR_SPECIAL_CHAR)) {
            CStreaming::SetMissionDoesntRequireModel(modelId);
        }
    }

    CStreaming::SetMissionDoesntRequireModel(MODEL_CSPLAY);
    CStreaming::StreamZoneModels(FindPlayerCoors());

    CTimer::Resume();

    CStreaming::ForceLayerToRead(true);
}

// 0x5B04D0
void CCutsceneMgr::FinishCutscene() {
    if (dataFileLoaded) {
        ms_cutsceneTimer = TheCamera.CCamera::GetCutSceneFinishTime() / 1000.f;
        TheCamera.CCamera::FinishCutscene();
    }
    FindPlayerPed()->m_bIsVisible = true;
    FindPlayerInfo().MakePlayerSafe(false, 10000.f);
}

// 0x5B0550
uint64 CCutsceneMgr::GetCutsceneTimeInMilleseconds() {
    return (uint64)ms_cutsceneTimer * 1000;
}

// 0x5B0570
bool CCutsceneMgr::HasCutsceneFinished() {
    return !dataFileLoaded || TheCamera.GetPositionAlongSpline() == 1.0;;
}

// 0x5AFAD0
void CCutsceneMgr::HideRequestedObjects() {
    if (ms_iNumHiddenEntities == 0) {
        return;
    }

    for (const auto& cr : ms_crToHideItems | rng::views::take(ms_iNumHiddenEntities)) {
        int32 modelId;
        if (!CModelInfo::GetModelInfo(cr.m_szObjectName, &modelId)) {
            DEV_LOG("Invalid model name({})", cr.m_szObjectName);
            continue;
        }

        int16 nObjInRng;
        CEntity* objInRng[32];
        CWorld::FindObjectsOfTypeInRange(modelId, cr.m_vecPosn, 1.5f, true, &nObjInRng, (int16)std::size(objInRng), objInRng, true, false, false, true, true);
        for (auto e : objInRng | rng::views::take((size_t)nObjInRng)) {
            if (!e->m_bIsVisible) {
                continue;
            }
            e->m_bIsVisible = false;
            CEntity::SetEntityReference(ms_pHiddenEntities[ms_iNumHiddenEntities++], e);
        }
    }
}

// 0x4D5A20
void CCutsceneMgr::Initialise() {
    ms_cutsceneLoadStatus = 0;
    ms_running            = false;
    ms_animLoaded         = false;
    ms_cutsceneProcessing = false;
    ms_useLodMultiplier   = false;
    ms_wasCutsceneSkipped = false;
    ms_hasFileInfo        = false;
    ms_pCutsceneDir       = new CDirectory{};
}

// 0x4D5D10
bool CCutsceneMgr::IsCutsceneSkipButtonBeingPressed() {
    const auto pad = CPad::GetPad(0);
    return pad->IsCrossPressed()
        || pad->IsMouseLButtonPressed()
        || pad->IsEnterJustPressed()
        || pad->IsStandardKeyJustDown(' ')
        || !isForeground; // ????
}

// 0x4D5AB0
void CCutsceneMgr::LoadAnimationUncompressed(const char* animName) {
    DEV_LOG("Loading uncompressed anim ({})", animName);

    strcpy_s(ms_aUncompressedCutsceneAnims[ms_numUncompressedCutsceneAnims++], animName);
    ms_aUncompressedCutsceneAnims[ms_numUncompressedCutsceneAnims][0] = 0; // Null terminate next
}

// 0x4D5E80
void CCutsceneMgr::LoadCutsceneData(const char* cutsceneName) {
    DEV_LOG("Loading cutscene ({})", cutsceneName);

    const auto plyr = FindPlayerPed(-1);

    CClothes::RebuildPlayerIfNeeded(plyr);

    CStreaming::RequestModel(MODEL_CSPLAY, STREAMING_PRIORITY_REQUEST | STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED);
    CStreaming::LoadAllRequestedModels(true);

    CClothes::RebuildCutscenePlayer(plyr, MODEL_CSPLAY);

    if (!ms_pCutsceneDir->HasLoaded()) {
        ms_pCutsceneDir->ReadDirFile("ANIM\\CUTS.IMG");
    }

    LoadCutsceneData_overlay(cutsceneName);
}

// 0x5B11C0
void CCutsceneMgr::LoadCutsceneData_loading() {
    // Make sure all neceesary models are streamed in
    for (const auto model : ms_iModelIndex | rng::views::take(ms_numLoadObjectNames)) {
        if (!CStreaming::IsModelLoaded(model)) {
            return;
        }
    }

    // All models are streamed in now
    LoadCutsceneData_postload();

    // Load custcene anims and create objects
    CCutsceneObject* obj = nullptr;
    for (auto i = 0; i < ms_numLoadObjectNames; i++) {
        if (!ms_bRepeatObject[i]) {
            obj = CreateCutsceneObject(ms_iModelIndex[i]);
        }
        if (const auto& animName = ms_cLoadAnimName[i]; animName[0]) {
            SetCutsceneAnim(animName, obj);
        }
    }

    // Create FXs that are attached to objects
    for (auto& csfx : ms_pParticleEffects | rng::views::take(ms_iNumParticleEffects)) {
        // Create the effect's transform matrix
        RwMatrix fxTransform;
        g_fx.CreateMatFromVec(&fxTransform, &csfx.m_vecPosn, &csfx.m_vecDirection);

        // Find object's matrix
        const auto objMat = [&]() -> RwMatrix* {
            const auto objIdx = csfx.m_nObjectId;

            // If not a cutscene object we don't have an object matrix - i'm not quite sure how this works, but okay.
            if (objIdx < 0 || objIdx >= ms_numCutsceneObjs + 1) { // TODO: Bug? Pretty sure the +1 is erronous...
                return nullptr;
            }

            // If it's a skinned object, we use bone indencies
            const auto csobj = ms_pCutsceneObjects[objIdx];
            if (const auto atomic = GetFirstAtomic(csobj->m_pRwClump); atomic && RpSkinGeometryGetSkin(RpAtomicGetGeometry(atomic))) {
                const auto nodeIdx = notsa::ston<uint32>({ csfx.m_szObjectPart }); // Obj Part is just an node index in this case
                const auto hier = GetAnimHierarchyFromSkinClump(csobj->m_pRwClump);
                return &RpHAnimHierarchyGetMatrixArray(hier)[RpHAnimIDGetIndex(hier, nodeIdx)];
            }

            // If not skinned, it's the name of a frame
            if (const auto frame = CClumpModelInfo::GetFrameFromName(csobj->m_pRwClump, csfx.m_szObjectPart)) {
                return RwFrameGetMatrix(frame);
            } else {
                DEV_LOG("Part({}) of object not found", csfx.m_szObjectPart);
            }

            // Otherwise we're fucked
            return nullptr;
        }();

        // Finally, create the fx
        csfx.m_pFxSystem = g_fxMan.CreateFxSystem(csfx.m_szEffectName, &fxTransform, objMat, true);
    }

    // Finally, process attachments
    for (const auto& v : ms_iAttachObjectToBone | rng::views::take(ms_numAttachObjectToBones)) {
        AttachObjectToBone(ms_pCutsceneObjects[v.m_nCutscenePedObjectId], ms_pCutsceneObjects[v.m_nCutscenePedObjectId], v.m_nBoneId);
    }
}

// 0x5B13F0
void CCutsceneMgr::LoadCutsceneData_overlay(const char* cutsceneName) {
    CTimer::Suspend();

    ms_cutsceneProcessing = true;
    ms_wasCutsceneSkipped = false;

    if (!m_bDontClearZone) {
        CStreaming::RemoveCurrentZonesModels();
    }

    ms_pCutsceneDir->Clear();
    ms_pCutsceneDir->ReadDirFile("ANIM\\CUTS.IMG");

    CStreaming::RemoveUnusedModelsInLoadedList();
    CGame::DrasticTidyUpMemory(true);
    strcpy_s(ms_cutsceneName, cutsceneName);
    CCutsceneMgr::LoadCutsceneData_preload();

    CTimer::Resume();
}

// 0x5AFBC0
void CCutsceneMgr::LoadCutsceneData_postload() {
    plugin::Call<0x5AFBC0>();
}

// 0x5B05A0
void CCutsceneMgr::LoadCutsceneData_preload() {
    plugin::Call<0x5B05A0>();
}

// 0x4D5C10
void CCutsceneMgr::LoadEverythingBecauseCutsceneDeletedAllOfIt() {
    plugin::Call<0x4D5C10>();
}

// 0x4D5E50
void CCutsceneMgr::RemoveCutscenePlayer() {
    plugin::Call<0x4D5E50>();
}

// 0x4D5AF0
void CCutsceneMgr::RemoveEverythingBecauseCutsceneDoesntFitInMemory() {
    plugin::Call<0x4D5AF0>();
}

// 0x5B0390
void CCutsceneMgr::SetCutsceneAnim(const char* animName, CObject* object) {
    plugin::Call<0x5B0390, const char*, CObject*>(animName, object);
}

// 0x5B0420
void CCutsceneMgr::SetCutsceneAnimToLoop(const char* animName) {
    plugin::Call<0x5B0420, const char*>(animName);
}

// 0x5B0440
void CCutsceneMgr::SetHeadAnim(const char* animName, CObject* headObject) {
    // NOP
}

// 0x5B14D0
void CCutsceneMgr::SetupCutsceneToStart() {
    plugin::Call<0x5B14D0>();
}

// 0x4D5E60
void CCutsceneMgr::Shutdown() {
    plugin::Call<0x4D5E60>();
}

// 0x5B1700
void CCutsceneMgr::SkipCutscene() {
    plugin::Call<0x5B1700>();
}

// 0x5B1460
void CCutsceneMgr::StartCutscene() {
    plugin::Call<0x5B1460>();
}

// 0x4D5D00
void CCutsceneMgr::Update() {
    plugin::Call<0x4D5D00>();
}

// 0x5B1720
void CCutsceneMgr::Update_overlay() {
    plugin::Call<0x5B1720>();
}

// 0x5AFA50
int16 FindCutsceneAudioTrackId(const char* cutsceneName) {
    return plugin::CallAndReturn<int16, 0x5AFA50, const char*>(cutsceneName);
}

void CCutsceneMgr::InjectHooks() {
    RH_ScopedClass(CCutsceneMgr);
    RH_ScopedCategory(); // TODO: Change this to the appropriate category!

    //RH_ScopedGlobalInstall(SetPos_wrongname_inlined, 0x47E070, {.reversed = false});
    RH_ScopedGlobalInstall(SetCutsceneAnim, 0x5B0390, {.reversed = false});
    RH_ScopedGlobalInstall(SetCutsceneAnimToLoop, 0x5B0420, {.reversed = false});
    RH_ScopedGlobalInstall(SetHeadAnim, 0x5B0440, {.reversed = false});
    RH_ScopedGlobalInstall(AttachObjectToBone, 0x5B0450);
    RH_ScopedGlobalInstall(AttachObjectToFrame, 0x5B0480);
    RH_ScopedGlobalInstall(AttachObjectToParent, 0x5B04B0);
    RH_ScopedGlobalInstall(AddCutsceneHead, 0x5B0380, {.reversed = false});
    RH_ScopedGlobalInstall(FinishCutscene, 0x5B04D0);
    RH_ScopedGlobalInstall(HasCutsceneFinished, 0x5B0570);
    RH_ScopedGlobalInstall(LoadCutsceneData_preload, 0x5B05A0, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData_loading, 0x5B11C0);
    RH_ScopedGlobalInstall(LoadCutsceneData_overlay, 0x5B13F0);
    RH_ScopedGlobalInstall(StartCutscene, 0x5B1460, {.reversed = false});
    RH_ScopedGlobalInstall(SetupCutsceneToStart, 0x5B14D0, {.reversed = false});
    RH_ScopedGlobalInstall(GetCutsceneTimeInMilleseconds, 0x5B0550);
    RH_ScopedGlobalInstall(CreateCutsceneObject, 0x5B02A0);
    RH_ScopedGlobalInstall(DeleteCutsceneData_overlay, 0x5AFD60);
    RH_ScopedGlobalInstall(LoadCutsceneData_postload, 0x5AFBC0, {.reversed = false});
    //RH_ScopedGlobalInstall(sub_489400, 0x489400, {.reversed = false});
    RH_ScopedGlobalInstall(Initialise, 0x4D5A20);
    RH_ScopedGlobalInstall(LoadAnimationUncompressed, 0x4D5AB0);
    RH_ScopedGlobalInstall(RemoveEverythingBecauseCutsceneDoesntFitInMemory, 0x4D5AF0, {.reversed = false});
    RH_ScopedGlobalInstall(LoadEverythingBecauseCutsceneDeletedAllOfIt, 0x4D5C10, {.reversed = false});
    RH_ScopedGlobalInstall(Update, 0x4D5D00, {.reversed = false});
    RH_ScopedGlobalInstall(IsCutsceneSkipButtonBeingPressed, 0x4D5D10);
    RH_ScopedGlobalInstall(AppendToNextCutscene, 0x4D5DB0);
    RH_ScopedGlobalInstall(BuildCutscenePlayer, 0x4D5E20);
    RH_ScopedGlobalInstall(RemoveCutscenePlayer, 0x4D5E50, {.reversed = false});
    RH_ScopedGlobalInstall(Shutdown, 0x4D5E60, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData, 0x4D5E80);
    RH_ScopedGlobalInstall(DeleteCutsceneData, 0x4D5ED0);
    //RH_ScopedGlobalInstall(sub_5099F0, 0x5099F0, {.reversed = false});
    RH_ScopedGlobalInstall(HideRequestedObjects, 0x5AFAD0);
    RH_ScopedGlobalInstall(UpdateCutsceneObjectBoundingBox, 0x5B01E0);
    RH_ScopedGlobalInstall(CalculateBoundingSphereRadiusCB, 0x5B0130);
    RH_ScopedGlobalInstall(SkipCutscene, 0x5B1700, {.reversed = false});
    RH_ScopedGlobalInstall(Update_overlay, 0x5B1720, {.reversed = false});
}
