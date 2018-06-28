/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CZoneInfo.h"
#include "CZone.h"
#include "CRadar.h"
#include "CVector.h"

enum  eGangAttackState {
    NO_ATTACK = 0,
    WAR_NOTIFIED = 0X1,
    PLAYER_CAME_TO_WAR = 0X2
};

enum  eGangWarState {
    NOT_IN_WAR = 0,
    PREFIRST_WAVE = 0X1,
    FIRST_WAVE = 0X2,
    PRESECOND_WAVE = 0X3,
    SECOND_WAVE = 0X4,
    PRETHIRD_WAVE = 0X5,
    THIRD_WAVE = 0X6
};

class  CGangWars {
public:
     static int &ZoneInfoForTraining;
     static int(&GangRatingStrength)[3]; // static int GangRatingStrength[3]
     static int(&GangRatings)[3]; // static int GangRatings[3]
     static int &FightTimer;
     static float &TimeTillNextAttack;
     static eGangAttackState &State2;
     static int &Gang2;
     static unsigned int &LastTimeInArea;
     static int &WarFerocity;
     static float &Provocation;
     static unsigned int &TimeStarted;
     static eGangWarState &State;
     static int(&aSpecificZones)[6]; // static int aSpecificZones[6]
     static float &Difficulty;
     static int &Gang1;
     static CZone *&pZoneToFightOver;
     static CZoneInfo *&pZoneInfoToFightOver;
     static bool &bGangWarsActive;
     static bool &bTrainingMission;
     static bool &bPlayerIsCloseby;
     static bool &bCanTriggerGangWarWhenOnAMission;
     static int &NumSpecificZones;
     static CRadar *&RadarBlip;
     static float &TerritoryUnderControlPercentage;
     static bool &bIsPlayerOnAMission;
     static CVector &CoorsOfPlayerAtStartOfWar;
     static CVector &PointOfAttack;

     static void AddKillToProvocation(int Pedtype);
     static bool AttackWaveOvercome();
     static unsigned int CalculateTimeTillNextAttack();
     static bool CanPlayerStartAGangWarHere(CZoneInfo *zoneInfo);
     static void CheerVictory();
     static void ClearSpecificZonesToTriggerGangWar();
     static void ClearTheStreets();
     static bool CreateAttackWave(int warFerocity, int waveID);
     static bool CreateDefendingGroup(int unsued);
     static void DoStuffWhenPlayerVictorious();
    //! unused
     static bool DoesPlayerControlThisZone(CZoneInfo *zoneinfo);
     static bool DontCreateCivilians();
     static void EndGangWar(bool bEnd);
     static bool GangWarFightingGoingOn();
     static bool GangWarGoingOn();
     static void InitAtStartOfGame();
     static void Load();
     static void MakeEnemyGainInfluenceInZone(int GangID, int GangDensityIncreaser);
     static bool MakePlayerGainInfluenceInZone(float remove_mult);
     static bool PedStreamedInForThisGang(int gangID);
     static bool PickStreamedInPedForThisGang(int gangID, int *outPedID);
     static bool PickZoneToAttack();
     static void ReleaseCarsInAttackWave();
    //! return num of released peds
     static int ReleasePedsInAttackWave(bool IsEndOfWar, bool RestoreGangPedsAcquaintance);
     static void Save();
     static void SetGangWarsActive(bool bActive);
     static void SetSpecificZoneToTriggerGangWar(int zoneId);
     static void StartDefensiveGangWar();
     static void StartOffensiveGangWar();
     static void StrengthenPlayerInfluenceInZone(int GroveDensityIncreaser);
    //! unused
     static void SwitchGangWarsActive();
     static void TellGangMembersTo(int bIsGangWarEnding);
     static void TellStreamingWhichGangsAreNeeded(int *GangsBitFlags);
     static void Update();
     static void UpdateTerritoryUnderControlPercentage();
};

//#include "meta/meta.CGangWars.h"
