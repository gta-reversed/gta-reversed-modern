#pragma once

#include "Vector.h"

class CEntity;
class CPed;
class CVehicle;

enum eSkipState {
    SKIP_NONE,
    SKIP_AVAILABLE,
    SKIP_IN_PROGRESS,
    SKIP_FADING_OUT,
    SKIP_AFTER_MISSION,
    SKIP_WAITING_SCRIPT
};

class CPed;

class CGameLogic {
public:
    static float& f2PlayerStartHeading;
    static CVector& vec2PlayerStartLocation;
    static bool& bPlayersCanBeInSeparateCars;

    inline static CVector& SkipPosition = *reinterpret_cast<CVector*>(0x96A8D4);
    inline static float& SkipHeading = *reinterpret_cast<float*>(0x96A8A4);

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

    static float CalcDistanceToForbiddenTrainCrossing(CVector vecPoint, CVector vecMoveSpeed, bool ignoreMoveSpeed, CVector& outDistance);
    static void ClearSkip(bool afterMission);
    static void DoWeaponStuffAtStartOf2PlayerGame(bool shareWeapons);
    static void StorePedsWeapons(CPed* ped);
    static uint32 FindCityClosestToPoint(CVector2D point);
    static void ForceDeathRestart();
    static void InitAtStartOfGame();
    static bool IsCoopGameGoingOn();
    static bool IsPlayerAllowedToGoInThisDirection(CPed* ped, CVector moveDirection, float distanceLimit);
    static bool IsPlayerUse2PlayerControls(CPed* ped);
    static bool IsPointWithinLineArea(const CVector* points, uint32 numPoints, float x, float y);
    static bool IsSkipWaitingForScriptToFadeIn();
    static bool LaRiotsActiveHere();
    static void Save();
    static void Load();
    static void PassTime(uint32 minutes);
    static void Remove2ndPlayerIfPresent();
    static void ResetStuffUponResurrection();
    static void RestorePedsWeapons(CPed* ped);
    static void RestorePlayerStuffDuringResurrection(CPlayerPed* player, CVector posn, float playerStartHeading);
    static void SetPlayerWantedLevelForForbiddenTerritories(bool immediately);
    static void SetUpSkip(CVector coors, float angle, bool afterMission, CEntity* vehicle, bool finishedByScript);
    static bool SkipCanBeActivated();
    static void SortOutStreamingAndMemory(const CVector& translation, float angle);
    static void StopPlayerMovingFromDirection(int32 playerId, CVector direction);
    static void Update();
    static void UpdateSkip();

    // @notsa
    static bool IsAPlayerInFocusOn2PlayerGame() {
        return n2PlayerPedInFocus < 2;
    }

    // @notsa
    static bool CanPlayerTripSkip() {
        return SkipState == SKIP_AVAILABLE || SkipState == SKIP_AFTER_MISSION;
    }
};
