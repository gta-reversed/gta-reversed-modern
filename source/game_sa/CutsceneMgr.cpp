/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CutsceneMgr.h"
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
    plugin::Call<0x5AFD60>();
}

// 0x5B04D0
void CCutsceneMgr::FinishCutscene() {
    plugin::Call<0x5B04D0>();
}

// 0x5B0550
long long CCutsceneMgr::GetCutsceneTimeInMilleseconds() {
    return plugin::CallAndReturn<long long, 0x5B0550>();
}

// 0x5B0570
bool CCutsceneMgr::HasCutsceneFinished() {
    return plugin::CallAndReturn<bool, 0x5B0570>();
}

// 0x5AFAD0
void CCutsceneMgr::HideRequestedObjects() {
    plugin::Call<0x5AFAD0>();
}

// 0x4D5A20
void CCutsceneMgr::Initialise() {
    plugin::Call<0x4D5A20>();
}

// 0x4D5D10
bool CCutsceneMgr::IsCutsceneSkipButtonBeingPressed() {
    return plugin::CallAndReturn<bool, 0x4D5D10>();
}

// 0x4D5AB0
void CCutsceneMgr::LoadAnimationUncompressed(const char* animName) {
    plugin::Call<0x4D5AB0, const char*>(animName);
}

// 0x4D5E80
void CCutsceneMgr::LoadCutsceneData(const char* cutsceneName) {
    plugin::Call<0x4D5E80, const char*>(cutsceneName);
}

// 0x5B11C0
void CCutsceneMgr::LoadCutsceneData_loading() {
    plugin::Call<0x5B11C0>();
}

// 0x5B13F0
void CCutsceneMgr::LoadCutsceneData_overlay(const char* cutsceneName) {
    plugin::Call<0x5B13F0, const char*>(cutsceneName);
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
    RH_ScopedGlobalInstall(FinishCutscene, 0x5B04D0, {.reversed = false});
    RH_ScopedGlobalInstall(HasCutsceneFinished, 0x5B0570, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData_preload, 0x5B05A0, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData_loading, 0x5B11C0, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData_overlay, 0x5B13F0, {.reversed = false});
    RH_ScopedGlobalInstall(StartCutscene, 0x5B1460, {.reversed = false});
    RH_ScopedGlobalInstall(SetupCutsceneToStart, 0x5B14D0, {.reversed = false});
    RH_ScopedGlobalInstall(GetCutsceneTimeInMilleseconds, 0x5B0550, {.reversed = false});
    RH_ScopedGlobalInstall(CreateCutsceneObject, 0x5B02A0);
    RH_ScopedGlobalInstall(DeleteCutsceneData_overlay, 0x5AFD60, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData_postload, 0x5AFBC0, {.reversed = false});
    //RH_ScopedGlobalInstall(sub_489400, 0x489400, {.reversed = false});
    RH_ScopedGlobalInstall(Initialise, 0x4D5A20, {.reversed = false});
    RH_ScopedGlobalInstall(LoadAnimationUncompressed, 0x4D5AB0, {.reversed = false});
    RH_ScopedGlobalInstall(RemoveEverythingBecauseCutsceneDoesntFitInMemory, 0x4D5AF0, {.reversed = false});
    RH_ScopedGlobalInstall(LoadEverythingBecauseCutsceneDeletedAllOfIt, 0x4D5C10, {.reversed = false});
    RH_ScopedGlobalInstall(Update, 0x4D5D00, {.reversed = false});
    RH_ScopedGlobalInstall(IsCutsceneSkipButtonBeingPressed, 0x4D5D10, {.reversed = false});
    RH_ScopedGlobalInstall(AppendToNextCutscene, 0x4D5DB0);
    RH_ScopedGlobalInstall(BuildCutscenePlayer, 0x4D5E20);
    RH_ScopedGlobalInstall(RemoveCutscenePlayer, 0x4D5E50, {.reversed = false});
    RH_ScopedGlobalInstall(Shutdown, 0x4D5E60, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData, 0x4D5E80, {.reversed = false});
    RH_ScopedGlobalInstall(DeleteCutsceneData, 0x4D5ED0);
    //RH_ScopedGlobalInstall(sub_5099F0, 0x5099F0, {.reversed = false});
    RH_ScopedGlobalInstall(HideRequestedObjects, 0x5AFAD0, { .reversed = false });
    RH_ScopedGlobalInstall(UpdateCutsceneObjectBoundingBox, 0x5B01E0);
    RH_ScopedGlobalInstall(CalculateBoundingSphereRadiusCB, 0x5B0130);
    RH_ScopedGlobalInstall(SkipCutscene, 0x5B1700, {.reversed = false});
    RH_ScopedGlobalInstall(Update_overlay, 0x5B1720, {.reversed = false});
}
