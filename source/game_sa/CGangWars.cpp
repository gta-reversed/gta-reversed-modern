/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

int& CGangWars::ZoneInfoForTraining = *reinterpret_cast<int*>(0x8A5F40);
int(&CGangWars::GangRatingStrength)[3] = *reinterpret_cast<int(*)[3]>(0x96AB2C);
int(&CGangWars::GangRatings)[3] = *reinterpret_cast<int(*)[3]>(0x96AB38);
int& CGangWars::FightTimer = *reinterpret_cast<int*>(0x96AB44);
float& CGangWars::TimeTillNextAttack = *reinterpret_cast<float*>(0x96AB48);
eGangAttackState& CGangWars::State2 = *reinterpret_cast<eGangAttackState*>(0x96AB4C);
int& CGangWars::Gang2 = *reinterpret_cast<int*>(0x96AB50);
unsigned int& CGangWars::LastTimeInArea = *reinterpret_cast<unsigned int*>(0x96AB54);
int& CGangWars::WarFerocity = *reinterpret_cast<int*>(0x96AB58);
float& CGangWars::Provocation = *reinterpret_cast<float*>(0x96AB5C);
unsigned int& CGangWars::TimeStarted = *reinterpret_cast<unsigned int*>(0x96AB60);
eGangWarState& CGangWars::State = *reinterpret_cast<eGangWarState*>(0x96AB64);
int(&CGangWars::aSpecificZones)[6] = *reinterpret_cast<int(*)[6]>(0x96AB68);
float& CGangWars::Difficulty = *reinterpret_cast<float*>(0x96AB80);
int& CGangWars::Gang1 = *reinterpret_cast<int*>(0x96AB84);
CZone*& CGangWars::pZoneToFightOver = *reinterpret_cast<CZone**>(0x96AB88);
CZoneInfo*& CGangWars::pZoneInfoToFightOver = *reinterpret_cast<CZoneInfo**>(0x96AB8C);
bool& CGangWars::bGangWarsActive = *reinterpret_cast<bool*>(0x96AB90);
bool& CGangWars::bTrainingMission = *reinterpret_cast<bool*>(0x96AB91);
bool& CGangWars::bPlayerIsCloseby = *reinterpret_cast<bool*>(0x96AB92);
bool& CGangWars::bCanTriggerGangWarWhenOnAMission = *reinterpret_cast<bool*>(0x96AB93);
int& CGangWars::NumSpecificZones = *reinterpret_cast<int*>(0x96AB94);
CRadar*& CGangWars::RadarBlip = *reinterpret_cast<CRadar**>(0x96AB98);
float& CGangWars::TerritoryUnderControlPercentage = *reinterpret_cast<float*>(0x96AB9C);
bool& CGangWars::bIsPlayerOnAMission = *reinterpret_cast<bool*>(0x96ABA0);
CVector& CGangWars::CoorsOfPlayerAtStartOfWar = *reinterpret_cast<CVector*>(0x96ABBC);
CVector& CGangWars::PointOfAttack = *reinterpret_cast<CVector*>(0x96ABC8);

void CGangWars::TellStreamingWhichGangsAreNeeded(int* GangsBitFlags) {
    plugin::CallDynGlobal<int*>(0x443D50, GangsBitFlags);
}

void CGangWars::InitAtStartOfGame() {
    plugin::CallDynGlobal(0x443920);
}
