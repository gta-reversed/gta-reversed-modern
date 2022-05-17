/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CarCtrl.h"
#include "Tasks/TaskTypes/TaskComplexWander.h"

class CZone;
class CZoneInfo;
class CRadar;

enum eGangAttackState {
    NO_ATTACK          = 0,
    WAR_NOTIFIED       = 1,
    PLAYER_CAME_TO_WAR = 2
};

enum eGangWarState {
    NOT_IN_WAR     = 0,
    PREFIRST_WAVE  = 1,
    FIRST_WAVE     = 2,
    PRESECOND_WAVE = 3,
    SECOND_WAVE    = 4,
    PRETHIRD_WAVE  = 5,
    THIRD_WAVE     = 6
};

class CGangWars {
public:
    static int32& ZoneInfoForTraining;
    static int32 (&GangRatingStrength)[3]; // static int32 GangRatingStrength[3]
    static int32 (&GangRatings)[3];        // static int32 GangRatings[3]
    static int32& FightTimer;
    static float& TimeTillNextAttack;
    static eGangAttackState& State2;
    static int32& Gang2;
    static uint32& LastTimeInArea;
    static int32& WarFerocity;
    static float& Provocation;
    static uint32& TimeStarted;
    static eGangWarState& State;
    static int32 (&aSpecificZones)[6]; // static int32 aSpecificZones[6]
    static float& Difficulty;
    static int32& Gang1;
    static CZone*& pZoneToFightOver;
    static CZoneInfo*& pZoneInfoToFightOver;
    static bool& bGangWarsActive;
    static bool& bTrainingMission;
    static bool& bPlayerIsCloseby;
    static bool& bCanTriggerGangWarWhenOnAMission;
    static int32& NumSpecificZones;
    static CRadar*& RadarBlip; // TODO/BUG: No way this is correct
    static float& TerritoryUnderControlPercentage;
    static bool& bIsPlayerOnAMission;
    static CVector& CoorsOfPlayerAtStartOfWar;
    static CVector& PointOfAttack;

public:
    static void InjectHooks();

    static void InitAtStartOfGame();

    static void Load();
    static void Save();

    static void AddKillToProvocation(ePedType pedType);
    static bool AttackWaveOvercome();
    static float CalculateTimeTillNextAttack();
    static bool CanPlayerStartAGangWarHere(CZoneInfo* zoneInfo);
    static void CheerVictory();
    static void ClearSpecificZonesToTriggerGangWar();
    static void ClearTheStreets();
    static bool CreateAttackWave(int32 warFerocity, int32 waveID);
    static bool CreateDefendingGroup(int32 unused);
    static void DoStuffWhenPlayerVictorious();
    static bool DoesPlayerControlThisZone(CZoneInfo* zoneInfo);
    static bool DontCreateCivilians();
    static void EndGangWar(bool bEnd);

    static bool GangWarFightingGoingOn();
    static bool GangWarGoingOn();

    static void MakeEnemyGainInfluenceInZone(int32 gangId, int32 gangDensityIncreaser);
    static bool MakePlayerGainInfluenceInZone(float removeMult);

    static bool PedStreamedInForThisGang(int32 gangId);
    static bool PickStreamedInPedForThisGang(int32 gangId, int32* outPedId);
    static bool PickZoneToAttack();

    static void ReleaseCarsInAttackWave();
    static uint32 ReleasePedsInAttackWave(bool isEndOfWar, bool restoreGangPedsAcquaintance);

    static void SetGangWarsActive(bool active);
    static void SetSpecificZoneToTriggerGangWar(int32 zoneId);

    static void StartDefensiveGangWar();
    static void StartOffensiveGangWar();

    static void StrengthenPlayerInfluenceInZone(int32 groveDensityIncreaser);
    static void SwitchGangWarsActive();

    static void TellGangMembersTo(bool isGangWarEnding);
    static void TellStreamingWhichGangsAreNeeded(uint32* GangsBitFlags);

    static void Update();
    static void UpdateTerritoryUnderControlPercentage();
};
