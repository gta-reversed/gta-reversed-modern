/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

char *abTempNeverLeavesGroup = (char *)0xC0BC08;
int &gPlayIdlesAnimBlockIndex = *(int *)0xC0BC10;
bool &CPlayerPed::bHasDisplayedPlayerQuitEnterCarHelpText = *(bool *)0xC0BC15;

void CPlayerPed::InjectHooks()
{
    HookInstall(0x60A530, &CPlayerPed::ResetSprintEnergy); 
    HookInstall(0x60A8A0, &CPlayerPed::ResetPlayerBreath);
    HookInstall(0x6094A0, &CPlayerPed::RemovePlayerPed);
}

// Converted from thiscall void CPlayerPed::CPlayerPed(int playerId,bool bGroupCreated) 0x60D5B0
CPlayerPed::CPlayerPed(int playerId, bool bGroupCreated) : CPed(plugin::dummy) {
    plugin::CallMethod<0x60D5B0, CPlayerPed *, int, bool>(this, playerId, bGroupCreated);
}

// Converted from cdecl void CPlayerPed::RemovePlayerPed(int playerId) 0x6094A0
void CPlayerPed::RemovePlayerPed(int playerId) {
#ifdef USE_DEFAULT_FUNCTIONS
  plugin::Call<0x6094A0, int>(playerId);
#else
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
        if (playerPed)
            playerPed->DeletingDestructor(1);
        pPlayerInfo->m_pPed = nullptr;
    }
#endif
}

// Converted from cdecl void CPlayerPed::DeactivatePlayerPed(int playerId) 0x609520
void CPlayerPed::DeactivatePlayerPed(int playerId) {
    plugin::Call<0x609520, int>(playerId);
}

// Converted from cdecl void CPlayerPed::ReactivatePlayerPed(int playerId) 0x609540
void CPlayerPed::ReactivatePlayerPed(int playerId) {
    plugin::Call<0x609540, int>(playerId);
}

// Converted from thiscall CPad* CPlayerPed::GetPadFromPlayer(void) 0x609560
CPad* CPlayerPed::GetPadFromPlayer() {
    return plugin::CallMethodAndReturn<CPad*, 0x609560, CPlayerPed *>(this);
}

// Converted from thiscall bool CPlayerPed::CanPlayerStartMission(void) 0x609590
bool CPlayerPed::CanPlayerStartMission() {
    return plugin::CallMethodAndReturn<bool, 0x609590, CPlayerPed *>(this);
}

// Converted from thiscall bool CPlayerPed::IsHidden(void) 0x609620
bool CPlayerPed::IsHidden() {
    return plugin::CallMethodAndReturn<bool, 0x609620, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::ReApplyMoveAnims(void) 0x609650
void CPlayerPed::ReApplyMoveAnims() {
    plugin::CallMethod<0x609650, CPlayerPed *>(this);
}

// Converted from thiscall bool CPlayerPed::DoesPlayerWantNewWeapon(eWeaponType weaponType, bool) 0x609710
bool CPlayerPed::DoesPlayerWantNewWeapon(eWeaponType weaponType, bool arg1) {
    return plugin::CallMethodAndReturn<bool, 0x609710, CPlayerPed *, eWeaponType, bool>(this, weaponType, arg1);
}

// Converted from thiscall void CPlayerPed::ProcessPlayerWeapon(CPad *pad) 0x6097F0
void CPlayerPed::ProcessPlayerWeapon(CPad* pad) {
    plugin::CallMethod<0x6097F0, CPlayerPed *, CPad*>(this, pad);
}

// Converted from thiscall void CPlayerPed::PickWeaponAllowedFor2Player(void) 0x609800
void CPlayerPed::PickWeaponAllowedFor2Player() {
    plugin::CallMethod<0x609800, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::UpdateCameraWeaponModes(CPad *pad) 0x609830
void CPlayerPed::UpdateCameraWeaponModes(CPad* pad) {
    plugin::CallMethod<0x609830, CPlayerPed *, CPad*>(this, pad);
}

// Converted from thiscall void CPlayerPed::ProcessAnimGroups(void) 0x6098F0
void CPlayerPed::ProcessAnimGroups() {
    plugin::CallMethod<0x6098F0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::ClearWeaponTarget(void) 0x609C80
void CPlayerPed::ClearWeaponTarget() {
    plugin::CallMethod<0x609C80, CPlayerPed *>(this);
}

// Converted from thiscall float CPlayerPed::GetWeaponRadiusOnScreen(void) 0x609CD0
float CPlayerPed::GetWeaponRadiusOnScreen() {
    return plugin::CallMethodAndReturn<float, 0x609CD0, CPlayerPed *>(this);
}

// Converted from cdecl bool CPlayerPed::PedCanBeTargettedVehicleWise(CPed *ped) 0x609D90
bool CPlayerPed::PedCanBeTargettedVehicleWise(CPed* ped) {
    return plugin::CallAndReturn<bool, 0x609D90, CPed*>(ped);
}

// Converted from thiscall float CPlayerPed::FindTargetPriority(CEntity *entity) 0x609DE0
float CPlayerPed::FindTargetPriority(CEntity* entity) {
    return plugin::CallMethodAndReturn<float, 0x609DE0, CPlayerPed *, CEntity*>(this, entity);
}

// Converted from thiscall void CPlayerPed::Clear3rdPersonMouseTarget(void) 0x609ED0
void CPlayerPed::Clear3rdPersonMouseTarget() {
    plugin::CallMethod<0x609ED0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::Busted(void) 0x609EF0
void CPlayerPed::Busted() {
    plugin::CallMethod<0x609EF0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::SetWantedLevel(int level) 0x609F10
void CPlayerPed::SetWantedLevel(int level) {
    plugin::CallMethod<0x609F10, CPlayerPed *, int>(this, level);
}

// Converted from thiscall void CPlayerPed::SetWantedLevelNoDrop(int level) 0x609F30
void CPlayerPed::SetWantedLevelNoDrop(int level) {
    plugin::CallMethod<0x609F30, CPlayerPed *, int>(this, level);
}

// Converted from thiscall void CPlayerPed::CheatWantedLevel(int level) 0x609F50
void CPlayerPed::CheatWantedLevel(int level) {
    plugin::CallMethod<0x609F50, CPlayerPed *, int>(this, level);
}

// Converted from thiscall bool CPlayerPed::CanIKReachThisTarget(CVector posn, CWeapon *weapon, bool) 0x609F80
bool CPlayerPed::CanIKReachThisTarget(CVector posn, CWeapon* weapon, bool arg2) {
    return plugin::CallMethodAndReturn<bool, 0x609F80, CPlayerPed *, CVector, CWeapon*, bool>(this, posn, weapon, arg2);
}

// Converted from thiscall CPlayerInfo* CPlayerPed::GetPlayerInfoForThisPlayerPed(void) 0x609FF0
CPlayerInfo* CPlayerPed::GetPlayerInfoForThisPlayerPed() {
    return plugin::CallMethodAndReturn<CPlayerInfo*, 0x609FF0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::DoStuffToGoOnFire(void) 0x60A020
void CPlayerPed::DoStuffToGoOnFire() {
    plugin::CallMethod<0x60A020, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::AnnoyPlayerPed(bool) 0x60A040
void CPlayerPed::AnnoyPlayerPed(bool arg0) {
    plugin::CallMethod<0x60A040, CPlayerPed *, bool>(this, arg0);
}

// Converted from thiscall void CPlayerPed::ClearAdrenaline(void) 0x60A070
void CPlayerPed::ClearAdrenaline() {
    plugin::CallMethod<0x60A070, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::DisbandPlayerGroup(void) 0x60A0A0
void CPlayerPed::DisbandPlayerGroup() {
    plugin::CallMethod<0x60A0A0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::MakeGroupRespondToPlayerTakingDamage(CEventDamage const& damageEvent) 0x60A110
void CPlayerPed::MakeGroupRespondToPlayerTakingDamage(CEventDamage const& damageEvent) {
    plugin::CallMethod<0x60A110, CPlayerPed *, CEventDamage const&>(this, damageEvent);
}

// Converted from thiscall void CPlayerPed::TellGroupToStartFollowingPlayer(bool, bool, bool) 0x60A1D0
void CPlayerPed::TellGroupToStartFollowingPlayer(bool arg0, bool arg1, bool arg2) {
    plugin::CallMethod<0x60A1D0, CPlayerPed *, bool, bool, bool>(this, arg0, arg1, arg2);
}

// Converted from thiscall void CPlayerPed::MakePlayerGroupDisappear(void) 0x60A440
void CPlayerPed::MakePlayerGroupDisappear() {
    plugin::CallMethod<0x60A440, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::MakePlayerGroupReappear(void) 0x60A4B0
void CPlayerPed::MakePlayerGroupReappear() {
    plugin::CallMethod<0x60A4B0, CPlayerPed *>(this);
}

void CPlayerPed::ResetSprintEnergy() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x60A530, CPlayerPed *>(this);
#else
    m_pPlayerData->m_fTimeCanRun = CStats::GetFatAndMuscleModifier(STAT_MOD_TIME_CAN_RUN);
#endif
}

// Converted from thiscall bool CPlayerPed::HandleSprintEnergy(bool, float) 0x60A550
bool CPlayerPed::HandleSprintEnergy(bool arg0, float arg1) {
    return plugin::CallMethodAndReturn<bool, 0x60A550, CPlayerPed *, bool, float>(this, arg0, arg1);
}

// Converted from thiscall float CPlayerPed::ControlButtonSprint(eSprintType sprintType) 0x60A610
float CPlayerPed::ControlButtonSprint(eSprintType sprintType) {
    return plugin::CallMethodAndReturn<float, 0x60A610, CPlayerPed *, eSprintType>(this, sprintType);
}

// Converted from thiscall float CPlayerPed::GetButtonSprintResults(eSprintType sprintType) 0x60A820
float CPlayerPed::GetButtonSprintResults(eSprintType sprintType) {
    return plugin::CallMethodAndReturn<float, 0x60A820, CPlayerPed *, eSprintType>(this, sprintType);
}

void CPlayerPed::ResetPlayerBreath() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x60A8A0, CPlayerPed *>(this);
#else
    m_pPlayerData->m_fBreath = CStats::GetFatAndMuscleModifier(STAT_MOD_AIR_IN_LUNG);
    m_pPlayerData->m_bRequireHandleBreath = false;
#endif
}

// Converted from thiscall void CPlayerPed::HandlePlayerBreath(bool, float) 0x60A8D0
void CPlayerPed::HandlePlayerBreath(bool bDecreaseAir, float fMultiplier) {
    plugin::CallMethod<0x60A8D0, CPlayerPed *, bool, float>(this, bDecreaseAir, fMultiplier);
}

// Converted from thiscall void CPlayerPed::SetRealMoveAnim(void) 0x60A9C0
void CPlayerPed::SetRealMoveAnim() {
    plugin::CallMethod<0x60A9C0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::MakeChangesForNewWeapon(eWeaponType weaponType) 0x60B460
void CPlayerPed::MakeChangesForNewWeapon(eWeaponType weaponType) {
    plugin::CallMethod<0x60B460, CPlayerPed *, eWeaponType>(this, weaponType);
}

// Converted from cdecl bool LOSBlockedBetweenPeds(CEntity *entity1, CEntity *entity2) 0x60B550
bool LOSBlockedBetweenPeds(CEntity* entity1, CEntity* entity2) {
    return plugin::CallAndReturn<bool, 0x60B550, CEntity*, CEntity*>(entity1, entity2);
}

// Converted from thiscall void CPlayerPed::Compute3rdPersonMouseTarget(bool meleeWeapon) 0x60B650
void CPlayerPed::Compute3rdPersonMouseTarget(bool meleeWeapon) {
    plugin::CallMethod<0x60B650, CPlayerPed *, bool>(this, meleeWeapon);
}

// Converted from thiscall void CPlayerPed::DrawTriangleForMouseRecruitPed(void) 0x60BA80
void CPlayerPed::DrawTriangleForMouseRecruitPed() {
    plugin::CallMethod<0x60BA80, CPlayerPed *>(this);
}

// Converted from thiscall bool CPlayerPed::DoesTargetHaveToBeBroken(CEntity *entity,CWeapon *weapon) 0x60C0C0
bool CPlayerPed::DoesTargetHaveToBeBroken(CEntity* entity, CWeapon* weapon) {
    return plugin::CallMethodAndReturn<bool, 0x60C0C0, CPlayerPed *, CEntity*, CWeapon*>(this, entity, weapon);
}

// Converted from thiscall void CPlayerPed::KeepAreaAroundPlayerClear(void) 0x60C1E0
void CPlayerPed::KeepAreaAroundPlayerClear() {
    plugin::CallMethod<0x60C1E0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::SetPlayerMoveBlendRatio(CVector *) 0x60C520
void CPlayerPed::SetPlayerMoveBlendRatio(CVector* arg0) {
    plugin::CallMethod<0x60C520, CPlayerPed *, CVector*>(this, arg0);
}

// Converted from thiscall CPed* CPlayerPed::FindPedToAttack(void) 0x60C5F0
CPed* CPlayerPed::FindPedToAttack() {
    return plugin::CallMethodAndReturn<CPed*, 0x60C5F0, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::ForceGroupToAlwaysFollow(bool enable) 0x60C7C0
void CPlayerPed::ForceGroupToAlwaysFollow(bool enable) {
    plugin::CallMethod<0x60C7C0, CPlayerPed *, bool>(this, enable);
}

// Converted from thiscall void CPlayerPed::ForceGroupToNeverFollow(bool enable) 0x60C800
void CPlayerPed::ForceGroupToNeverFollow(bool enable) {
    plugin::CallMethod<0x60C800, CPlayerPed *, bool>(this, enable);
}

// Converted from thiscall void CPlayerPed::MakeThisPedJoinOurGroup(CPed *ped) 0x60C840
void CPlayerPed::MakeThisPedJoinOurGroup(CPed* ped) {
    plugin::CallMethod<0x60C840, CPlayerPed *, CPed*>(this, ped);
}

// Converted from thiscall bool CPlayerPed::PlayerWantsToAttack(void) 0x60CC50
bool CPlayerPed::PlayerWantsToAttack() {
    return plugin::CallMethodAndReturn<bool, 0x60CC50, CPlayerPed *>(this);
}

// Converted from thiscall void CPlayerPed::SetInitialState(bool bGroupCreated) 0x60CD20
void CPlayerPed::SetInitialState(bool bGroupCreated) {
    plugin::CallMethod<0x60CD20, CPlayerPed *, bool>(this, bGroupCreated);
}

// Converted from thiscall void CPlayerPed::MakeChangesForNewWeapon(int weaponSlot) 0x60D000
void CPlayerPed::MakeChangesForNewWeapon(int weaponSlot) {
    plugin::CallMethod<0x60D000, CPlayerPed *, int>(this, weaponSlot);
}

// Converted from thiscall void CPlayerPed::EvaluateTarget(CEntity *target,CEntity **outTarget,float *outTargetPriority,float maxDistance,float,bool) 0x60D020
void CPlayerPed::EvaluateTarget(CEntity* target, CEntity** outTarget, float* outTargetPriority, float maxDistance, float arg4, bool arg5) {
    plugin::CallMethod<0x60D020, CPlayerPed *, CEntity*, CEntity**, float*, float, float, bool>(this, target, outTarget, outTargetPriority, maxDistance, arg4, arg5);
}

// Converted from thiscall void CPlayerPed::EvaluateNeighbouringTarget(CEntity *target,CEntity **outTarget,float *outTargetPriority,float maxDistance,float,bool) 0x60D1C0
void CPlayerPed::EvaluateNeighbouringTarget(CEntity* target, CEntity** outTarget, float* outTargetPriority, float maxDistance, float arg4, bool arg5) {
    plugin::CallMethod<0x60D1C0, CPlayerPed *, CEntity*, CEntity**, float*, float, float, bool>(this, target, outTarget, outTargetPriority, maxDistance, arg4, arg5);
}

// Converted from thiscall void CPlayerPed::ProcessGroupBehaviour(CPad *pad) 0x60D350
void CPlayerPed::ProcessGroupBehaviour(CPad* pad) {
    plugin::CallMethod<0x60D350, CPlayerPed *, CPad*>(this, pad);
}

// Converted from thiscall bool CPlayerPed::PlayerHasJustAttackedSomeone(void) 0x60D5A0
bool CPlayerPed::PlayerHasJustAttackedSomeone() {
    return plugin::CallMethodAndReturn<bool, 0x60D5A0, CPlayerPed *>(this);
}

// Converted from cdecl void CPlayerPed::SetupPlayerPed(int playerId) 0x60D790
void CPlayerPed::SetupPlayerPed(int playerId) {
    plugin::Call<0x60D790, int>(playerId);
}

// Converted from thiscall void CPlayerPed::ProcessWeaponSwitch(CPad *pad) 0x60D850
void CPlayerPed::ProcessWeaponSwitch(CPad* pad) {
    plugin::CallMethod<0x60D850, CPlayerPed *, CPad*>(this, pad);
}

// Converted from thiscall bool CPlayerPed::FindWeaponLockOnTarget(void) 0x60DC50
bool CPlayerPed::FindWeaponLockOnTarget() {
    return plugin::CallMethodAndReturn<bool, 0x60DC50, CPlayerPed *>(this);
}

// Converted from thiscall bool CPlayerPed::FindNextWeaponLockOnTarget(CEntity *,bool) 0x60E530
bool CPlayerPed::FindNextWeaponLockOnTarget(CEntity* arg0, bool arg1) {
    return plugin::CallMethodAndReturn<bool, 0x60E530, CPlayerPed *, CEntity*, bool>(this, arg0, arg1);
}

// Converted from thiscall int CPlayerPed::GetWantedLevel(void) 0x41BE60
int CPlayerPed::GetWantedLevel() {
    return plugin::CallMethodAndReturn<int, 0x41BE60, CPlayerPed *>(this);
}
