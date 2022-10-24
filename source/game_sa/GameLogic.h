#pragma once

#include "Vector.h"

class CEntity;
class CPed;
class CVehicle;

enum eSkipState {
    SKIP_STATE_0,
    SKIP_STATE_1,
    SKIP_STATE_2,
    SKIP_STATE_3,
    SKIP_STATE_4,
    SKIP_STATE_5,
};

class CPed;

class CGameLogic {
public:
    static float& f2PlayerStartHeading;
    static CVector& vec2PlayerStartLocation;
    static bool& bPlayersCanBeInSeparateCars;

    inline static std::array<CVector, 16>& AfterDeathStartPoints = *reinterpret_cast<std::array<CVector, 16>*>(0x96A8D4);

    static int32& TimeOfLastEvent;
    static eGameState& GameState;
    static bool& bPlayersCannotTargetEachOther;
    static int32& ActivePlayers; // unused
    static float& m_96A890;
    static int32& nPrintFocusHelpTimer;
    static int32& nPrintFocusHelpCounter;
    static bool& bScriptCoopGameGoingOn;

    static bool& SkipToBeFinishedByScript;
    static CVehicle*& SkipVehicle;
    static uint32& SkipTimer;
    static eSkipState& SkipState;
    static int32& SkipDestinationOrientation;
    static int32& SkipDestination;

    static int32& NumAfterDeathStartPoints;

    static bool& bPenaltyForDeathApplies;
    static bool& bPenaltyForArrestApplies;
    static bool& bLimitPlayerDistance;
    static float& MaxPlayerDistance;
    static int32& n2PlayerPedInFocus;

public:
    static void InjectHooks();

    static float CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool someBool, CVector* pOutDistance);
    static void ClearSkip(bool a1);
    static void DoWeaponStuffAtStartOf2PlayerGame(bool a1);
    static void StorePedsWeapons(CPed* ped);
    static void FindCityClosestToPoint(float x, float y);
    static void ForceDeathRestart();
    static void InitAtStartOfGame();
    static bool IsCoopGameGoingOn();
    static bool IsPlayerAllowedToGoInThisDirection(CPed* ped, float moveDirectionX, float moveDirectionY, float moveDirectionZ, float distanceLimit);
    static bool IsPlayerUse2PlayerControls(CPed* ped);
    static bool IsPointWithinLineArea(int32 a1, float x, float y);
    static bool IsSkipWaitingForScriptToFadeIn();
    static bool LaRiotsActiveHere();
    static void Save();
    static void Load();
    static void PassTime(uint32 minutes);
    static void Remove2ndPlayerIfPresent();
    static void ResetStuffUponResurrection();
    static void RestorePedsWeapons(CPed* ped);
    static void RestorePlayerStuffDuringResurrection(CPlayerPed* player, CVector posn, float playerStartHeading);
    static void SetPlayerWantedLevelForForbiddenTerritories(uint16 townNumber);
    static void SetUpSkip(CVector coors, float angle, bool afterMission, CEntity* vehicle, bool finishedByScript);
    static bool SkipCanBeActivated();
    static void SortOutStreamingAndMemory(const CVector& translation, float angle);
    static void StopPlayerMovingFromDirection(int32 playerId, CVector direction);
    static void Update();
    static void UpdateSkip();
};
