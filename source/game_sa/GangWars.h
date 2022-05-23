/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CarCtrl.h"
#include "Radar.h"
#include "PedType.h"

class CZone;
class CZoneInfo;

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
    static inline int32& ZoneInfoForTraining = *reinterpret_cast<int32*>(0x8A5F40); // -1
    static inline std::array<int32, 3>& GangRatingStrength = *reinterpret_cast<std::array<int32, 3>*>(0x96AB2C);
    static inline std::array<int32, 3>& GangRatings = *reinterpret_cast<std::array<int32, 3>*>(0x96AB38);
    static inline int32& FightTimer = *reinterpret_cast<int32*>(0x96AB44);
    static inline float& TimeTillNextAttack = *reinterpret_cast<float*>(0x96AB48);
    static inline int32& Gang2 = *reinterpret_cast<int32*>(0x96AB50);
    static inline uint32& LastTimeInArea = *reinterpret_cast<uint32*>(0x96AB54);
    static inline int32& WarFerocity = *reinterpret_cast<int32*>(0x96AB58);
    static inline float& Provocation = *reinterpret_cast<float*>(0x96AB5C);
    static inline uint32& TimeStarted = *reinterpret_cast<uint32*>(0x96AB60);
    static inline eGangWarState& State = *reinterpret_cast<eGangWarState*>(0x96AB64);
    static inline eGangAttackState& State2 = *reinterpret_cast<eGangAttackState*>(0x96AB4C);
    static inline std::array<int32, 6> aSpecificZones = *reinterpret_cast<std::array<int32, 6>*>(0x96AB68);
    static inline float& Difficulty = *reinterpret_cast<float*>(0x96AB80);
    static inline int32& Gang1 = *reinterpret_cast<int32*>(0x96AB84);
    static inline CZone*& pZoneToFightOver = *reinterpret_cast<CZone**>(0x96AB88);
    static inline CZoneInfo*& pZoneInfoToFightOver = *reinterpret_cast<CZoneInfo**>(0x96AB8C);
    static inline bool& bGangWarsActive = *reinterpret_cast<bool*>(0x96AB90);
    static inline bool& bTrainingMission = *reinterpret_cast<bool*>(0x96AB91);
    static inline bool& bPlayerIsCloseby = *reinterpret_cast<bool*>(0x96AB92);
    static inline bool& bCanTriggerGangWarWhenOnAMission = *reinterpret_cast<bool*>(0x96AB93);
    static inline int32& NumSpecificZones = *reinterpret_cast<int32*>(0x96AB94);
    static inline int32& RadarBlip = *reinterpret_cast<int32*>(0x96AB98);
    static inline float& TerritoryUnderControlPercentage = *reinterpret_cast<float*>(0x96AB9C);
    static inline bool& bIsPlayerOnAMission = *reinterpret_cast<bool*>(0x96ABA0);
    static inline CVector& CoorsOfPlayerAtStartOfWar = *reinterpret_cast<CVector*>(0x96ABBC);
    static inline CVector& PointOfAttack = *reinterpret_cast<CVector*>(0x96ABC8);

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

    // NOTSA
private:
    static uint32 GetGangColor(int32 gang) {
        assert(gang >= GANG_BALLAS && gang <= GANG_VAGOS);
        auto col1 = ((uint8_t*)(0x8D1344))[gang];
        auto col2 = ((uint8_t*)(0x8D1350))[gang];
        auto col3 = ((uint8_t*)(0x8D135C))[gang];

        return ((col3 | (((col1 << 8) | col2) << 8)) << 8) | 0xFF;
    }
};
