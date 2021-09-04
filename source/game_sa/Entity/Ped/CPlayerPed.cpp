/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

char* abTempNeverLeavesGroup = (char*)0xC0BC08;
int& gPlayIdlesAnimBlockIndex = *(int*)0xC0BC10;
bool& CPlayerPed::bHasDisplayedPlayerQuitEnterCarHelpText = *(bool*)0xC0BC15;

void CPlayerPed::InjectHooks() {
    ReversibleHooks::Install("CPlayerPed", "ResetSprintEnergy", 0x60A530, &CPlayerPed::ResetSprintEnergy);
    ReversibleHooks::Install("CPlayerPed", "ResetPlayerBreath", 0x60A8A0, &CPlayerPed::ResetPlayerBreath);
    ReversibleHooks::Install("CPlayerPed", "RemovePlayerPed", 0x6094A0, &CPlayerPed::RemovePlayerPed);
    ReversibleHooks::Install("CPlayerPed", "Busted", 0x609EF0, &CPlayerPed::Busted);
    ReversibleHooks::Install("CPlayerPed", "GetWantedLevel", 0x41BE60, &CPlayerPed::GetWantedLevel);
    ReversibleHooks::Install("CPlayerPed", "SetWantedLevel", 0x609F10, &CPlayerPed::SetWantedLevel);
    ReversibleHooks::Install("CPlayerPed", "SetWantedLevelNoDrop", 0x609F30, &CPlayerPed::SetWantedLevelNoDrop);
    ReversibleHooks::Install("CPlayerPed", "CheatWantedLevel", 0x609F50, &CPlayerPed::CheatWantedLevel);
    ReversibleHooks::Install("CPlayerPed", "DoStuffToGoOnFire", 0x60A020, &CPlayerPed::DoStuffToGoOnFire);
    ReversibleHooks::Install("CPlayerPed", "Load", 0x5D46E0, &CPlayerPed::Load);
    ReversibleHooks::Install("CPlayerPed", "Save", 0x5D57E0, &CPlayerPed::Save);
    ReversibleHooks::Install("CPlayerPed", "DeactivatePlayerPed", 0x609520, &CPlayerPed::DeactivatePlayerPed);
    ReversibleHooks::Install("CPlayerPed", "ReactivatePlayerPed", 0x609540, &CPlayerPed::ReactivatePlayerPed);
}

struct WorkBufferSaveData {
    uint32          saveSize = sizeof(WorkBufferSaveData); // Never read, but written
    uint32          chaosLevel{};
    uint32          wantedLevel{};
    CPedClothesDesc clothesDesc{};
    uint32          chosenWeapon{};
};
VALIDATE_SIZE(WorkBufferSaveData, 132u + 4u);

// 0x5D46E0
bool CPlayerPed::Load() {
    CPed::Load();

    WorkBufferSaveData savedData{};
    CGenericGameStorage::LoadDataFromWorkBuffer(&savedData, sizeof(WorkBufferSaveData));

    CWanted* wanted = m_pPlayerData->m_pWanted;
    wanted->m_nChaosLevel = savedData.chaosLevel;
    wanted->m_nWantedLevel= savedData.wantedLevel;

    m_pPlayerData->m_nChosenWeapon = savedData.chosenWeapon;
    *m_pPlayerData->m_pPedClothesDesc = savedData.clothesDesc;

    return true;
}

// 0x5D57E0
bool CPlayerPed::Save() {
    WorkBufferSaveData saveData{};

    CWanted* wanted = m_pPlayerData->m_pWanted;
    saveData.chaosLevel = wanted->m_nChaosLevel;
    saveData.wantedLevel = wanted->m_nWantedLevel;

    saveData.chosenWeapon = m_pPlayerData->m_nChosenWeapon;
    saveData.clothesDesc = *m_pPlayerData->m_pPedClothesDesc;

    CGenericGameStorage::SaveDataToWorkBuffer(&saveData, sizeof(WorkBufferSaveData));

    return true;
}

// 0x60D5B0
CPlayerPed::CPlayerPed(int playerId, bool bGroupCreated) : CPed(plugin::dummy) {
    plugin::CallMethod<0x60D5B0, CPlayerPed *, int, bool>(this, playerId, bGroupCreated);
}

// 0x6094A0
void CPlayerPed::RemovePlayerPed(int playerId) {
    CPed* playerPed = CWorld::Players[playerId].m_pPed;
    CPlayerInfo* pPlayerInfo = &CWorld::Players[playerId];
    if (playerPed)
    {
        CVehicle* playerVehicle = playerPed->m_pVehicle;
        if (playerVehicle && playerVehicle->m_pDriver == playerPed)
        {
            playerVehicle->m_nStatus = STATUS_PHYSICS;
            playerVehicle->m_fGasPedal = 0.0f;
            playerVehicle->m_fBreakPedal = 0.1f;
        }
        CWorld::Remove(static_cast<CEntity*>(playerPed));
        delete playerPed;
        pPlayerInfo->m_pPed = nullptr;
    }
}

// 0x609520
void CPlayerPed::DeactivatePlayerPed(int playerId) {
    assert(playerId >= 0); // NOTSA
    CWorld::Remove(FindPlayerPed(playerId));
}

// 0x609540
void CPlayerPed::ReactivatePlayerPed(int playerId) {
    assert(playerId >= 0); // NOTSA
    CWorld::Add(FindPlayerPed(playerId));
}

// 0x609560
CPad* CPlayerPed::GetPadFromPlayer() {
    return plugin::CallMethodAndReturn<CPad*, 0x609560, CPlayerPed *>(this);
}

// 0x609590
bool CPlayerPed::CanPlayerStartMission() {
    return plugin::CallMethodAndReturn<bool, 0x609590, CPlayerPed *>(this);
}

// 0x609620
bool CPlayerPed::IsHidden() {
    return plugin::CallMethodAndReturn<bool, 0x609620, CPlayerPed *>(this);
}

// 0x609650
void CPlayerPed::ReApplyMoveAnims() {
    plugin::CallMethod<0x609650, CPlayerPed *>(this);
}

// 0x609710
bool CPlayerPed::DoesPlayerWantNewWeapon(eWeaponType weaponType, bool arg1) {
    return plugin::CallMethodAndReturn<bool, 0x609710, CPlayerPed *, eWeaponType, bool>(this, weaponType, arg1);
}

// 0x6097F0
void CPlayerPed::ProcessPlayerWeapon(CPad* pad) {
    plugin::CallMethod<0x6097F0, CPlayerPed *, CPad*>(this, pad);
}

// 0x609800
void CPlayerPed::PickWeaponAllowedFor2Player() {
    plugin::CallMethod<0x609800, CPlayerPed *>(this);
}

// 0x609830
void CPlayerPed::UpdateCameraWeaponModes(CPad* pad) {
    plugin::CallMethod<0x609830, CPlayerPed *, CPad*>(this, pad);
}

// 0x6098F0
void CPlayerPed::ProcessAnimGroups() {
    plugin::CallMethod<0x6098F0, CPlayerPed *>(this);
}

// 0x609C80
void CPlayerPed::ClearWeaponTarget() {
    plugin::CallMethod<0x609C80, CPlayerPed *>(this);
}

// 0x609CD0
float CPlayerPed::GetWeaponRadiusOnScreen() {
    return plugin::CallMethodAndReturn<float, 0x609CD0, CPlayerPed *>(this);
}

// 0x609D90
bool CPlayerPed::PedCanBeTargettedVehicleWise(CPed* ped) {
    return plugin::CallAndReturn<bool, 0x609D90, CPed*>(ped);
}

// 0x609DE0
float CPlayerPed::FindTargetPriority(CEntity* entity) {
    return plugin::CallMethodAndReturn<float, 0x609DE0, CPlayerPed *, CEntity*>(this, entity);
}

// 0x609ED0
void CPlayerPed::Clear3rdPersonMouseTarget() {
    plugin::CallMethod<0x609ED0, CPlayerPed *>(this);
}

// 0x609EF0
void CPlayerPed::Busted() {
    CWanted* pWanted = GetWanted();
    if (pWanted) {
        pWanted->m_nChaosLevel = 0;
    }
}

// 0x41BE60
unsigned int CPlayerPed::GetWantedLevel() {
    CWanted* pWanted = GetWanted();
    if (pWanted) {
        return pWanted->m_nWantedLevel;
    }

    return 0;
}

// 0x609F10
void CPlayerPed::SetWantedLevel(int level) {
    CWanted* pWanted = GetWanted();
    pWanted->SetWantedLevel(level);
}

// 0x609F30
void CPlayerPed::SetWantedLevelNoDrop(int level) {
    CWanted* pWanted = GetWanted();
    pWanted->SetWantedLevelNoDrop(level);
}

// 0x609F50
void CPlayerPed::CheatWantedLevel(int level) {
    CWanted* pWanted = GetWanted();
    pWanted->CheatWantedLevel(level);
}

// 0x609F80
bool CPlayerPed::CanIKReachThisTarget(CVector posn, CWeapon* weapon, bool arg2) {
    return plugin::CallMethodAndReturn<bool, 0x609F80, CPlayerPed *, CVector, CWeapon*, bool>(this, posn, weapon, arg2);
}

// 0x609FF0
CPlayerInfo* CPlayerPed::GetPlayerInfoForThisPlayerPed() {
    return plugin::CallMethodAndReturn<CPlayerInfo*, 0x609FF0, CPlayerPed *>(this);
}

// 0x60A020
void CPlayerPed::DoStuffToGoOnFire() {
    if (m_nPedState == PEDSTATE_SNIPER_MODE)
        TheCamera.ClearPlayerWeaponMode();
}

// 0x60A040
void CPlayerPed::AnnoyPlayerPed(bool arg0) {
    plugin::CallMethod<0x60A040, CPlayerPed *, bool>(this, arg0);
}

// 0x60A070
void CPlayerPed::ClearAdrenaline() {
    plugin::CallMethod<0x60A070, CPlayerPed *>(this);
}

// 0x60A0A0
void CPlayerPed::DisbandPlayerGroup() {
    plugin::CallMethod<0x60A0A0, CPlayerPed *>(this);
}

// 0x60A110
void CPlayerPed::MakeGroupRespondToPlayerTakingDamage(CEventDamage const& damageEvent) {
    plugin::CallMethod<0x60A110, CPlayerPed *, CEventDamage const&>(this, damageEvent);
}

// 0x60A1D0
void CPlayerPed::TellGroupToStartFollowingPlayer(bool arg0, bool arg1, bool arg2) {
    plugin::CallMethod<0x60A1D0, CPlayerPed *, bool, bool, bool>(this, arg0, arg1, arg2);
}

// 0x60A440
void CPlayerPed::MakePlayerGroupDisappear() {
    plugin::CallMethod<0x60A440, CPlayerPed *>(this);
}

// 0x60A4B0
void CPlayerPed::MakePlayerGroupReappear() {
    plugin::CallMethod<0x60A4B0, CPlayerPed *>(this);
}

// 0x60A530
void CPlayerPed::ResetSprintEnergy()
{
    m_pPlayerData->m_fTimeCanRun = CStats::GetFatAndMuscleModifier(STAT_MOD_TIME_CAN_RUN);
}

// 0x60A550
bool CPlayerPed::HandleSprintEnergy(bool arg0, float arg1) {
    return plugin::CallMethodAndReturn<bool, 0x60A550, CPlayerPed *, bool, float>(this, arg0, arg1);
}

// 0x60A610
float CPlayerPed::ControlButtonSprint(eSprintType sprintType) {
    return plugin::CallMethodAndReturn<float, 0x60A610, CPlayerPed *, eSprintType>(this, sprintType);
}

// 0x60A820
float CPlayerPed::GetButtonSprintResults(eSprintType sprintType) {
    return plugin::CallMethodAndReturn<float, 0x60A820, CPlayerPed *, eSprintType>(this, sprintType);
}

void CPlayerPed::ResetPlayerBreath() {
    m_pPlayerData->m_fBreath = CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG);
    m_pPlayerData->m_bRequireHandleBreath = false;
}

// 0x60A8D0
void CPlayerPed::HandlePlayerBreath(bool bDecreaseAir, float fMultiplier) {
    plugin::CallMethod<0x60A8D0, CPlayerPed *, bool, float>(this, bDecreaseAir, fMultiplier);
}

// 0x60A9C0
void CPlayerPed::SetRealMoveAnim() {
    plugin::CallMethod<0x60A9C0, CPlayerPed *>(this);
}

// 0x60B460
void CPlayerPed::MakeChangesForNewWeapon(eWeaponType weaponType) {
    plugin::CallMethod<0x60B460, CPlayerPed *, eWeaponType>(this, weaponType);
}

// 0x60B550
bool LOSBlockedBetweenPeds(CEntity* entity1, CEntity* entity2) {
    return plugin::CallAndReturn<bool, 0x60B550, CEntity*, CEntity*>(entity1, entity2);
}

// 0x60B650
void CPlayerPed::Compute3rdPersonMouseTarget(bool meleeWeapon) {
    plugin::CallMethod<0x60B650, CPlayerPed *, bool>(this, meleeWeapon);
}

// 0x60BA80
void CPlayerPed::DrawTriangleForMouseRecruitPed() {
    plugin::CallMethod<0x60BA80, CPlayerPed *>(this);
}

// 0x60C0C0
bool CPlayerPed::DoesTargetHaveToBeBroken(CEntity* entity, CWeapon* weapon) {
    return plugin::CallMethodAndReturn<bool, 0x60C0C0, CPlayerPed *, CEntity*, CWeapon*>(this, entity, weapon);
}

// 0x60C1E0
void CPlayerPed::KeepAreaAroundPlayerClear() {
    plugin::CallMethod<0x60C1E0, CPlayerPed *>(this);
}

// 0x60C520
void CPlayerPed::SetPlayerMoveBlendRatio(CVector* arg0) {
    plugin::CallMethod<0x60C520, CPlayerPed *, CVector*>(this, arg0);
}

// 0x60C5F0
CPed* CPlayerPed::FindPedToAttack() {
    return plugin::CallMethodAndReturn<CPed*, 0x60C5F0, CPlayerPed *>(this);
}

// 0x60C7C0
void CPlayerPed::ForceGroupToAlwaysFollow(bool enable) {
    plugin::CallMethod<0x60C7C0, CPlayerPed *, bool>(this, enable);
}

// 0x60C800
void CPlayerPed::ForceGroupToNeverFollow(bool enable) {
    plugin::CallMethod<0x60C800, CPlayerPed *, bool>(this, enable);
}

// 0x60C840
void CPlayerPed::MakeThisPedJoinOurGroup(CPed* ped) {
    plugin::CallMethod<0x60C840, CPlayerPed *, CPed*>(this, ped);
}

// 0x60CC50
bool CPlayerPed::PlayerWantsToAttack() {
    return plugin::CallMethodAndReturn<bool, 0x60CC50, CPlayerPed *>(this);
}

// 0x60CD20
void CPlayerPed::SetInitialState(bool bGroupCreated) {
    plugin::CallMethod<0x60CD20, CPlayerPed *, bool>(this, bGroupCreated);
}

// 0x60D000
void CPlayerPed::MakeChangesForNewWeapon(int weaponSlot) {
    plugin::CallMethod<0x60D000, CPlayerPed *, int>(this, weaponSlot);
}

// 0x60D020
void CPlayerPed::EvaluateTarget(CEntity* target, CEntity** outTarget, float* outTargetPriority, float maxDistance, float arg4, bool arg5) {
    plugin::CallMethod<0x60D020, CPlayerPed *, CEntity*, CEntity**, float*, float, float, bool>(this, target, outTarget, outTargetPriority, maxDistance, arg4, arg5);
}

// 0x60D1C0
void CPlayerPed::EvaluateNeighbouringTarget(CEntity* target, CEntity** outTarget, float* outTargetPriority, float maxDistance, float arg4, bool arg5) {
    plugin::CallMethod<0x60D1C0, CPlayerPed *, CEntity*, CEntity**, float*, float, float, bool>(this, target, outTarget, outTargetPriority, maxDistance, arg4, arg5);
}

// 0x60D350
void CPlayerPed::ProcessGroupBehaviour(CPad* pad) {
    plugin::CallMethod<0x60D350, CPlayerPed *, CPad*>(this, pad);
}

// 0x60D5A0
bool CPlayerPed::PlayerHasJustAttackedSomeone() {
    return plugin::CallMethodAndReturn<bool, 0x60D5A0, CPlayerPed *>(this);
}

// 0x60D790
void CPlayerPed::SetupPlayerPed(int playerId) {
    plugin::Call<0x60D790, int>(playerId);
}

// 0x60D850
void CPlayerPed::ProcessWeaponSwitch(CPad* pad) {
    plugin::CallMethod<0x60D850, CPlayerPed *, CPad*>(this, pad);
}

// 0x60DC50
bool CPlayerPed::FindWeaponLockOnTarget() {
    return plugin::CallMethodAndReturn<bool, 0x60DC50, CPlayerPed *>(this);
}

// 0x60E530
bool CPlayerPed::FindNextWeaponLockOnTarget(CEntity* arg0, bool arg1) {
    return plugin::CallMethodAndReturn<bool, 0x60E530, CPlayerPed *, CEntity*, bool>(this, arg0, arg1);
}
