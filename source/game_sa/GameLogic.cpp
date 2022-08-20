#include "StdInc.h"

//CGameLogic::SavedWeaponSlots
int32& CGameLogic::nPrintFocusHelpCounter = *reinterpret_cast<int32*>(0x96A8B8);
int32& CGameLogic::nPrintFocusHelpTimer = *reinterpret_cast<int32*>(0x96A8B4);
float& CGameLogic::f2PlayerStartHeading = *reinterpret_cast<float*>(0x96A840);
CVector& CGameLogic::vec2PlayerStartLocation = *reinterpret_cast<CVector*>(0x96A9AC);
bool& CGameLogic::bPlayersCanBeInSeparateCars = *reinterpret_cast<bool*>(0x96A8B3);
bool& CGameLogic::bPlayersCannotTargetEachOther = *reinterpret_cast<bool*>(0x96A8B2);

//CGameLogic::AfterDeathStartPointOrientations[16] = 0x96A850;
//CVector& CGameLogic::AfterDeathStartPoints[16] = *reinterpret_cast<CVector*>(0x96A8D4);
int32& CGameLogic::NumAfterDeathStartPoints = *reinterpret_cast<int32*>(0x96A890);

bool& CGameLogic::SkipToBeFinishedByScript = *reinterpret_cast<bool*>(0x96A894);
CVehicle*& CGameLogic::SkipVehicle = *reinterpret_cast<CVehicle**>(0x96A898);
uint32& CGameLogic::SkipTimer = *reinterpret_cast<uint32*>(0x96A89C);
eSkipState& CGameLogic::SkipState = *reinterpret_cast<eSkipState*>(0x96A8A0);
//CGameLogic::SkipDestinationOrientation
//CGameLogic::SkipDestination

bool& CGameLogic::bScriptCoopGameGoingOn = *reinterpret_cast<bool*>(0x96A8A8);
int32& CGameLogic::TimeOfLastEvent = *reinterpret_cast<int32*>(0x96A8AC);
eGameState& CGameLogic::GameState = *reinterpret_cast<eGameState*>(0x96A8B0);
int32& CGameLogic::ActivePlayers = *reinterpret_cast<int32*>(0x96A8B1);

bool& CGameLogic::bPenaltyForDeathApplies = *reinterpret_cast<bool*>(0x8A5E48);
bool& CGameLogic::bPenaltyForArrestApplies = *reinterpret_cast<bool*>(0x8A5E49);
bool& CGameLogic::bLimitPlayerDistance = *reinterpret_cast<bool*>(0x8A5E4A);
float& CGameLogic::MaxPlayerDistance = *reinterpret_cast<float*>(0x8A5E4C); // default 20.0
int32& CGameLogic::n2PlayerPedInFocus = *reinterpret_cast<int32*>(0x8A5E50); // default 2

void CGameLogic::InjectHooks() {
    RH_ScopedClass(CGameLogic);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(CalcDistanceToForbiddenTrainCrossing, 0x4418E0);
    // RH_ScopedInstall(ClearSkip, 0x441560);
    // RH_ScopedInstall(DoWeaponStuffAtStartOf2PlayerGame, 0x4428B0);
    // RH_ScopedInstall(StorePedsWeapons, 0x0);
    // RH_ScopedInstall(FindCityClosestToPoint, 0x441B70);
    RH_ScopedInstall(ForceDeathRestart, 0x441240);
    RH_ScopedInstall(InitAtStartOfGame, 0x441210);
    RH_ScopedInstall(IsCoopGameGoingOn, 0x441390);
    // RH_ScopedInstall(IsPlayerAllowedToGoInThisDirection, 0x441E10);
    // RH_ScopedInstall(IsPlayerUse2PlayerControls, 0x442020);
    // RH_ScopedInstall(IsPointWithinLineArea, 0x4416E0);
    RH_ScopedInstall(IsSkipWaitingForScriptToFadeIn, 0x4416C0);
    // RH_ScopedInstall(LaRiotsActiveHere, 0x441C10);
    // RH_ScopedInstall(Save, 0x5D33C0);
    // RH_ScopedInstall(Load, 0x5D3440);
    // RH_ScopedInstall(PassTime, 0x4414C0);
    // RH_ScopedInstall(Remove2ndPlayerIfPresent, 0x4413C0);
    // RH_ScopedInstall(ResetStuffUponResurrection, 0x442980);
    // RH_ScopedInstall(RestorePedsWeapons, 0x441D30);
    // RH_ScopedInstall(RestorePlayerStuffDuringResurrection, 0x442060);
    // RH_ScopedInstall(SetPlayerWantedLevelForForbiddenTerritories, 0x441770);
    // RH_ScopedInstall(SetUpSkip, 0x4423C0);
    // RH_ScopedInstall(SkipCanBeActivated, 0x4415C0);
    RH_ScopedInstall(SortOutStreamingAndMemory, 0x441440);
    // RH_ScopedInstall(StopPlayerMovingFromDirection, 0x441290);
    // RH_ScopedInstall(Update, 0x442AD0);
    // RH_ScopedInstall(UpdateSkip, 0x442480);
}

// 0x4418E0
float CGameLogic::CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool someBool, CVector* pOutDistance) {
    return plugin::CallAndReturn<float, 0x4418E0, CVector, CVector, bool, CVector*>(vecPoint, vecMoveSpeed, someBool, pOutDistance);
}

// 0x441560
void CGameLogic::ClearSkip(bool a1) {
    plugin::Call<0x441560, bool>(a1);
}

// 0x4428B0
void CGameLogic::DoWeaponStuffAtStartOf2PlayerGame(bool a1) {
    plugin::Call<0x4428B0, bool>(a1);
}

// used in CGameLogic::DoWeaponStuffAtStartOf2PlayerGame
// 0x
void CGameLogic::StorePedsWeapons(CPed* ped) {
    plugin::Call<0x0, CPed*>(ped);
}

// 0x441B70
void CGameLogic::FindCityClosestToPoint(float x, float y) {
    plugin::Call<0x441B70, float, float>(x, y);
}

// 0x441240
void CGameLogic::ForceDeathRestart() {
    CWorld::Players[CWorld::PlayerInFocus].m_nPlayerState = PLAYERSTATE_HAS_DIED;
    GameState = GAME_STATE_LOGO;
    TimeOfLastEvent = CTimer::GetTimeInMS() - 3001;
    TheCamera.SetFadeColour(0, 0, 0);
    TheCamera.Fade(4.0f, eFadeFlag::FADE_IN);
}

// 0x441210
void CGameLogic::InitAtStartOfGame() {
    ActivePlayers            = true;
    SkipState                = SKIP_STATE_0;
    NumAfterDeathStartPoints = 0;
    GameState                = GAME_STATE_INITIAL;
    TimeOfLastEvent          = 0;
    nPrintFocusHelpTimer     = 0;
    nPrintFocusHelpCounter   = 0;
    bScriptCoopGameGoingOn   = false;
}

// 2 players are playing
// 0x441390
bool CGameLogic::IsCoopGameGoingOn() {
    return CWorld::Players[0].m_pPed && CWorld::Players[1].m_pPed;
}

// 0x441E10
bool CGameLogic::IsPlayerAllowedToGoInThisDirection(CPed* ped, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit) {
    return plugin::CallAndReturn<bool, 0x441E10, CPed*, float, float, float, float>(ped, moveDirectionX, moveDirectionY, moveDirectionZ, distanceLimit);
}

// 0x442020
bool CGameLogic::IsPlayerUse2PlayerControls(CPed* ped) {
    return plugin::CallAndReturn<bool, 0x442020, CPed*>(ped);
}

// 0x4416E0
bool CGameLogic::IsPointWithinLineArea(int32 a1, float x, float y) {
    return plugin::CallAndReturn<bool, 0x4416E0, int32, float, float>(a1, x, y);
}

// 0x4416C0
bool CGameLogic::IsSkipWaitingForScriptToFadeIn() {
    if (CGameLogic::SkipState != SKIP_STATE_5) {
        return false;
    }
    CGameLogic::SkipState = SKIP_STATE_0;
    return true;
}

// 0x441C10
bool CGameLogic::LaRiotsActiveHere() {
    return plugin::CallAndReturn<bool, 0x441C10>();
}

// 0x5D33C0
void CGameLogic::Save() {
    plugin::Call<0x5D33C0>();

//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::NumAfterDeathStartPoints, sizeof(int32));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::bPenaltyForDeathApplies,  sizeof(bool));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::bPenaltyForArrestApplies, sizeof(bool));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::GameState,                sizeof(eGameState));
//    CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::TimeOfLastEvent,          sizeof(uint32));
//    for (int32 i = 0; i < NumAfterDeathStartPoints; ++i) {
//        CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::AfterDeathStartPoints[i],            sizeof(CVector));
//        CGenericGameStorage::SaveDataToWorkBuffer(&CGameLogic::AfterDeathStartPointOrientations[i], sizeof(float));
//    }
}

// 0x5D3440
void CGameLogic::Load() {
    plugin::Call<0x5D3440>();

//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::NumAfterDeathStartPoints, sizeof(int32));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::bPenaltyForDeathApplies,  sizeof(bool));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::bPenaltyForArrestApplies, sizeof(bool));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::GameState,                sizeof(eGameState));
//    CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::TimeOfLastEvent,          sizeof(uint32));
//    for (int32 i = 0; i < NumAfterDeathStartPoints; ++i) {
//        CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::AfterDeathStartPoints[i],            sizeof(CVector));
//        CGenericGameStorage::LoadDataFromWorkBuffer(&CGameLogic::AfterDeathStartPointOrientations[i], sizeof(float));
//    }
}

// 0x4414C0
void CGameLogic::PassTime(uint32 time) {
    plugin::Call<0x4414C0, uint32>(time);
}

// 0x4413C0
void CGameLogic::Remove2ndPlayerIfPresent() {
    plugin::Call<0x4413C0>();
}

// 0x442980
void CGameLogic::ResetStuffUponResurrection() {
    plugin::Call<0x442980>();
}

// 0x441D30
void CGameLogic::RestorePedsWeapons(CPed* ped) {
    return plugin::Call<0x441D30, CPed*>(ped);

    static CWeapon (&s_SavedWeapons)[13] = *(CWeapon(*)[13])0x96A9B8;

    ped->ClearWeapons();
    for (auto& weapon : s_SavedWeapons) {
        auto modelId1 = CWeaponInfo::GetWeaponInfo(weapon.m_nType, eWeaponSkill::STD)->m_nModelId1;
        auto modelId2 = CWeaponInfo::GetWeaponInfo(weapon.m_nType, eWeaponSkill::STD)->m_nModelId2;
        if (   (modelId1 == MODEL_INVALID || CStreaming::GetInfo(modelId1).IsLoaded())
            && (modelId2 == MODEL_INVALID || CStreaming::GetInfo(modelId2).IsLoaded()) // FIX_BUGS: They checked modelId1 twice
        ) {
            ped->GiveWeapon(weapon.m_nType, weapon.m_nTotalAmmo, true);
        }
    }
}

// 0x442060
void CGameLogic::RestorePlayerStuffDuringResurrection(CPlayerPed* player, float x, float y, float z, float playerStartHeading) {
    plugin::Call<0x442060, CPlayerPed*, float, float, float, float>(player, x, y, z, playerStartHeading);
}

// townNumber ∈ [0, 1]
// 0x441770
void CGameLogic::SetPlayerWantedLevelForForbiddenTerritories(uint16 townNumber) {
    plugin::Call<0x441770, uint16>(townNumber);
}

// 0x4423C0
void CGameLogic::SetUpSkip(int32 fX, int32 fY, int32 fZ, float fAngle, bool bAfterMission, CEntity* vehicle, bool bFinishedByScript) {
    plugin::Call<0x4423C0, int32, int32, int32, float, bool, CEntity*, bool>(fX, fY, fZ, fAngle, bAfterMission, vehicle, bFinishedByScript);
}

// 0x4415C0
bool CGameLogic::SkipCanBeActivated() {
    return plugin::CallAndReturn<bool, 0x4415C0>();
}

// 0x441440
void CGameLogic::SortOutStreamingAndMemory(const CVector& translation, float angle) {
    CTimer::Stop();
    float farClip = CTimeCycle::FindFarClipForCoors(translation);
    RwCameraSetFarClipPlane(TheCamera.m_pRwCamera, farClip);
    CStreaming::FlushRequestList();
    CStreaming::DeleteRwObjectsAfterDeath(translation);
    CStreaming::RemoveUnusedModelsInLoadedList();
    CGame::DrasticTidyUpMemory(true);
    CStreaming::LoadSceneCollision(translation);
    CRenderer::RequestObjectsInDirection(translation, angle, STREAMING_LOADING_SCENE);
    CStreaming::LoadScene(translation);
    CTimer::Update();
}

// 0x441290
void CGameLogic::StopPlayerMovingFromDirection(int32 playerId, CVector direction) {
    plugin::Call<0x441290, int32, CVector>(playerId, direction);
}

// 0x442AD0
void CGameLogic::Update() {
    plugin::Call<0x442AD0>();
}

// 0x442480
void CGameLogic::UpdateSkip() {
    plugin::Call<0x442480>();
}
