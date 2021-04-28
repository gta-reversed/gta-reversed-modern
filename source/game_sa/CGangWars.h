/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CZoneInfo.h"
#include "CZone.h"
#include "CRadar.h"
#include "CVector.h"

enum eGangAttackState {
    NO_ATTACK = 0,
    WAR_NOTIFIED = 1,
    PLAYER_CAME_TO_WAR = 2
};

enum eGangWarState {
    NOT_IN_WAR = 0,
    PREFIRST_WAVE = 1,
    FIRST_WAVE = 2,
    PRESECOND_WAVE = 3,
    SECOND_WAVE = 4,
    PRETHIRD_WAVE = 5,
    THIRD_WAVE = 6
};

class CGangWars {
public:
    static int& ZoneInfoForTraining;
    static int (&GangRatingStrength)[3]; // static int GangRatingStrength[3]
    static int (&GangRatings)[3];        // static int GangRatings[3]
    static int& FightTimer;
    static float& TimeTillNextAttack;
    static eGangAttackState& State2;
    static int& Gang2;
    static unsigned int& LastTimeInArea;
    static int& WarFerocity;
    static float& Provocation;
    static unsigned int& TimeStarted;
    static eGangWarState& State;
    static int (&aSpecificZones)[6]; // static int aSpecificZones[6]
    static float& Difficulty;
    static int& Gang1;
    static CZone*& pZoneToFightOver;
    static CZoneInfo*& pZoneInfoToFightOver;
    static bool& bGangWarsActive;
    static bool& bTrainingMission;
    static bool& bPlayerIsCloseby;
    static bool& bCanTriggerGangWarWhenOnAMission;
    static int& NumSpecificZones;
    static CRadar*& RadarBlip;
    static float& TerritoryUnderControlPercentage;
    static bool& bIsPlayerOnAMission;
    static CVector& CoorsOfPlayerAtStartOfWar;
    static CVector& PointOfAttack;

public:
    static void InjectHooks();

    static void AddKillToProvocation(ePedType pedType);
    static bool AttackWaveOvercome();
    static unsigned int CalculateTimeTillNextAttack();
    static bool CanPlayerStartAGangWarHere(CZoneInfo* zoneInfo);
    static void CheerVictory();
    static void ClearSpecificZonesToTriggerGangWar();
    static void ClearTheStreets();
    static bool CreateAttackWave(int warFerocity, int waveID);
    static bool CreateDefendingGroup(int unused);
    static void DoStuffWhenPlayerVictorious();
    static bool DoesPlayerControlThisZone(CZoneInfo* zoneInfo);
    static bool DontCreateCivilians();
    static void EndGangWar(bool bEnd);
    static bool GangWarFightingGoingOn();
    static bool GangWarGoingOn();
    static void InitAtStartOfGame();
    static void Load();
    static void MakeEnemyGainInfluenceInZone(int gangId, int gangDensityIncreaser);
    static bool MakePlayerGainInfluenceInZone(float removeMult);
    static bool PedStreamedInForThisGang(int gangId);
    static bool PickStreamedInPedForThisGang(int gangId, int* outPedId);
    static bool PickZoneToAttack();
    static void ReleaseCarsInAttackWave();
    static int ReleasePedsInAttackWave(bool isEndOfWar, bool restoreGangPedsAcquaintance);
    static void Save();
    static void SetGangWarsActive(bool bActive);
    static void SetSpecificZoneToTriggerGangWar(int zoneId);
    static void StartDefensiveGangWar();
    static void StartOffensiveGangWar();
    static void StrengthenPlayerInfluenceInZone(int groveDensityIncreaser);
    static void SwitchGangWarsActive();
    static void TellGangMembersTo(bool bIsGangWarEnding);
    static void TellStreamingWhichGangsAreNeeded(int* GangsBitFlags);
    static void Update();
    static void UpdateTerritoryUnderControlPercentage();
};

//#include "meta/meta.CGangWars.h"
