/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CutsceneMgr.h"

uint32 MAX_NUM_CUTSCENE_OBJECTS = 50;
uint32 MAX_NUM_CUTSCENE_PARTICLE_EFFECTS = 8;
uint32 MAX_NUM_CUTSCENE_ITEMS_TO_HIDE = 50;
uint32 MAX_NUM_CUTSCENE_ATTACHMENTS = 50;

bool &CCutsceneMgr::ms_useCutsceneShadows = *(bool *)0x8AC158;
uint32 &CCutsceneMgr::numPlayerWeaponsToRestore = *(uint32 *)0xB5EB58;
uint32 *CCutsceneMgr::playerWeaponsToRestore_Ammo = (uint32 *)0xB5EB5C;
uint32 *CCutsceneMgr::playerWeaponsToRestore_Type = (uint32 *)0xB5EB90;
char(*CCutsceneMgr::ms_cAppendAnimName)[32] = (char(*)[32])0xB5EBC8;
char(*CCutsceneMgr::ms_cAppendObjectName)[32] = (char(*)[32])0xB5F208;
CDirectory *CCutsceneMgr::ms_pCutsceneDir = (CDirectory *)0xB5F848;
uint32 &CCutsceneMgr::ms_cutsceneLoadStatus = *(uint32 *)0xB5F84C;
bool &CCutsceneMgr::ms_animLoaded = *(bool *)0xB5F850;
bool &CCutsceneMgr::ms_running = *(bool *)0xB5F851;
bool &CCutsceneMgr::ms_cutsceneProcessing = *(bool *)0xB5F852;
bool &CCutsceneMgr::ms_useLodMultiplier = *(bool *)0xB5F853;
bool &CCutsceneMgr::ms_wasCutsceneSkipped = *(bool *)0xB5F854;
bool &CCutsceneMgr::ms_hasFileInfo = *(bool *)0xB5F855;
uint32 &CCutsceneMgr::ms_numAppendObjectNames = *(uint32 *)0xB5F858;
bool &CCutsceneMgr::restoreEverythingAfterCutscene = *(bool *)0xB5F85C;
float &CCutsceneMgr::m_fPrevCarDensity = *(float *)0xBC1D68;
float &CCutsceneMgr::m_fPrevPedDensity = *(float *)0xBC1D6C;
tCutsceneParticleEffect *CCutsceneMgr::ms_pParticleEffects = (tCutsceneParticleEffect *)0xBC1D70;
tCutsceneRemoval *CCutsceneMgr::ms_crToHideItems = (tCutsceneRemoval *)0xBC20D0;
CEntity **CCutsceneMgr::ms_pHiddenEntities = (CEntity **)0xBC2968;
uint32 &CCutsceneMgr::ms_numAttachObjectToBones = *(uint32 *)0xBC2A30;
bool *CCutsceneMgr::ms_bRepeatObject = (bool *)0xBC2A34;
tCutsceneAttachment *CCutsceneMgr::ms_iAttachObjectToBone = (tCutsceneAttachment *)0xBC2A68;
char(*CCutsceneMgr::ms_aUncompressedCutsceneAnims)[32] = (char(*)[32])0xBC2CC0;
int32 *CCutsceneMgr::ms_iTextDuration = (int32 *)0xBC2DC0;
int32 *CCutsceneMgr::ms_iTextStartTime = (int32 *)0xBC2EC0;
char(*CCutsceneMgr::ms_cTextOutput)[8] = (char(*)[8])0xBC2FC0;
int32 *CCutsceneMgr::ms_iModelIndex = (int32 *)0xBC31C0;
char(*CCutsceneMgr::ms_cLoadAnimName)[32] = (char(*)[32])0xBC3288;
char(*CCutsceneMgr::ms_cLoadObjectName)[32] = (char(*)[32])0xBC38C8;
float &CCutsceneMgr::ms_cutsceneTimer = *(float *)0xBC3F08;
char *CCutsceneMgr::ms_cutsceneName = (char *)0xBC3F0C;
uint32 &CCutsceneMgr::ms_cutscenePlayStatus = *(uint32 *)0xBC3FE0;
uint32 &CCutsceneMgr::ms_numCutsceneObjs = *(uint32 *)0xBC3FE4;
uint32 &CCutsceneMgr::ms_numLoadObjectNames = *(uint32 *)0xBC3FE8;
uint32 &CCutsceneMgr::ms_numTextOutput = *(uint32 *)0xBC3FEC;
uint32 &CCutsceneMgr::ms_currTextOutput = *(uint32 *)0xBC3FF0;
uint32 &CCutsceneMgr::ms_numUncompressedCutsceneAnims = *(uint32 *)0xBC3FF4;
uint32 &CCutsceneMgr::ms_iNumHiddenEntities = *(uint32 *)0xBC3FF8;
uint32 &CCutsceneMgr::ms_iNumParticleEffects = *(uint32 *)0xBC3FFC;
uint32 &CCutsceneMgr::m_PrevExtraColour = *(uint32 *)0xBC4000;
bool &CCutsceneMgr::m_PrevExtraColourOn = *(bool *)0xBC4004;
bool &CCutsceneMgr::dataFileLoaded = *(bool *)0xBC4006;
CAnimBlendAssocGroup &CCutsceneMgr::ms_cutsceneAssociations = *(CAnimBlendAssocGroup *)0xBC4020;
CVector &CCutsceneMgr::ms_cutsceneOffset = *(CVector *)0xBC4034;

// 0x5B0380
int32 CCutsceneMgr::AddCutsceneHead(CObject* object, int32 arg1) {
    return 0;
}

// 0x4D5DB0
void CCutsceneMgr::AppendToNextCutscene(const char* objectName, const char* animName) {
    const auto CopyAndLower = [](auto&& dst, const char* src) {
        strcpy_s(dst, src);
        strlwr(dst);
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
    plugin::Call<0x4D5E20>();
}

// 0x5B02A0
CCutsceneObject* CCutsceneMgr::CreateCutsceneObject(int32 modelId) {
    return plugin::CallAndReturn<CCutsceneObject*, 0x5B02A0, int32>(modelId);
}

// 0x4D5ED0
void CCutsceneMgr::DeleteCutsceneData() {
    plugin::Call<0x4D5ED0>();
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

// 0x5B01E0
void UpdateCutsceneObjectBoundingBox(RpClump* clump, int32 modelId) {
    plugin::Call<0x5B01E0, RpClump*, int32>(clump, modelId);
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
    RH_ScopedGlobalInstall(CreateCutsceneObject, 0x5B02A0, {.reversed = false});
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
    RH_ScopedGlobalInstall(BuildCutscenePlayer, 0x4D5E20, {.reversed = false});
    RH_ScopedGlobalInstall(RemoveCutscenePlayer, 0x4D5E50, {.reversed = false});
    RH_ScopedGlobalInstall(Shutdown, 0x4D5E60, {.reversed = false});
    RH_ScopedGlobalInstall(LoadCutsceneData, 0x4D5E80, {.reversed = false});
    RH_ScopedGlobalInstall(DeleteCutsceneData, 0x4D5ED0, {.reversed = false});
    //RH_ScopedGlobalInstall(sub_5099F0, 0x5099F0, {.reversed = false});
    RH_ScopedGlobalInstall(HideRequestedObjects, 0x5AFAD0, {.reversed = false});
    RH_ScopedGlobalInstall(SkipCutscene, 0x5B1700, {.reversed = false});
    RH_ScopedGlobalInstall(Update_overlay, 0x5B1720, {.reversed = false});
}
