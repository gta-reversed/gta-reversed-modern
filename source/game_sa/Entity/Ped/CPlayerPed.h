/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPed.h"
#include "eWeaponType.h"
#include "CPad.h"
#include "eSprintType.h"

class CEventDamage;
class CPlayerInfo;

class CPlayerPed : public CPed {
public:
	CPed *m_pPlayerTargettedPed;
	int field_7A0;

    // did we display "JCK_HLP" message
    static bool &bHasDisplayedPlayerQuitEnterCarHelpText;

    CPlayerPed(int playerId, bool bGroupCreated);

    // Thanks to Silent
    inline CWanted *GetWanted() {
        return m_pPlayerData ? m_pPlayerData->m_pWanted : nullptr;
    }

    CPad* GetPadFromPlayer();
    bool CanPlayerStartMission();
    bool IsHidden();
    void ReApplyMoveAnims();
    bool DoesPlayerWantNewWeapon(eWeaponType weaponType, bool arg1);
    // dummy function
    void ProcessPlayerWeapon(CPad* pad);
    void PickWeaponAllowedFor2Player();
    void UpdateCameraWeaponModes(CPad* pad);
    void ProcessAnimGroups();
    void ClearWeaponTarget();
    float GetWeaponRadiusOnScreen();
    float FindTargetPriority(CEntity* entity);
    void Clear3rdPersonMouseTarget();
    // GetWanted()->m_nWantedLevel = 0;
    void Busted();
    void SetWantedLevel(int level);
    void SetWantedLevelNoDrop(int level);
    void CheatWantedLevel(int level);
    bool CanIKReachThisTarget(CVector posn, CWeapon* weapon, bool arg2);
    CPlayerInfo* GetPlayerInfoForThisPlayerPed();
    void DoStuffToGoOnFire();
    void AnnoyPlayerPed(bool arg0);
    void ClearAdrenaline();
    void DisbandPlayerGroup();
    void MakeGroupRespondToPlayerTakingDamage(CEventDamage const& damageEvent);
    void TellGroupToStartFollowingPlayer(bool arg0, bool arg1, bool arg2);
    void MakePlayerGroupDisappear();
    void MakePlayerGroupReappear();
    void ResetSprintEnergy();
    bool HandleSprintEnergy(bool arg0, float arg1);
    float ControlButtonSprint(eSprintType sprintType);
    float GetButtonSprintResults(eSprintType sprintType);
    void ResetPlayerBreath();
    void HandlePlayerBreath(bool arg0, float arg1);
    void SetRealMoveAnim();
    void MakeChangesForNewWeapon(eWeaponType weaponType);
    void Compute3rdPersonMouseTarget(bool meleeWeapon);
    void DrawTriangleForMouseRecruitPed();
    bool DoesTargetHaveToBeBroken(CEntity* entity, CWeapon* weapon);
    void KeepAreaAroundPlayerClear();
    void SetPlayerMoveBlendRatio(CVector* arg0);
    CPed* FindPedToAttack();
    void ForceGroupToAlwaysFollow(bool enable);
    void ForceGroupToNeverFollow(bool enable);
    void MakeThisPedJoinOurGroup(CPed* ped);
    bool PlayerWantsToAttack();
    void SetInitialState(bool bGroupCreated);
    void MakeChangesForNewWeapon(int weaponSlot);
    void EvaluateTarget(CEntity* target, CEntity** outTarget, float* outTargetPriority, float maxDistance, float arg4, bool arg5);
    void EvaluateNeighbouringTarget(CEntity* target, CEntity** outTarget, float* outTargetPriority, float maxDistance, float arg4, bool arg5);
    void ProcessGroupBehaviour(CPad* pad);
    // return PlayerWantsToAttack();
    bool PlayerHasJustAttackedSomeone();
    void ProcessWeaponSwitch(CPad* pad);
    bool FindWeaponLockOnTarget();
    bool FindNextWeaponLockOnTarget(CEntity* arg0, bool arg1);
    int GetWantedLevel();

    static void RemovePlayerPed(int playerId);
    static void DeactivatePlayerPed(int playerId);
    static void ReactivatePlayerPed(int playerId);
    static bool PedCanBeTargettedVehicleWise(CPed* ped);
    static void SetupPlayerPed(int playerId);
};

VALIDATE_SIZE(CPlayerPed, 0x7A4);

extern char *abTempNeverLeavesGroup; // char abTempNeverLeavesGroup[7];
extern int &gPlayIdlesAnimBlockIndex;

bool LOSBlockedBetweenPeds(CEntity* entity1, CEntity* entity2);