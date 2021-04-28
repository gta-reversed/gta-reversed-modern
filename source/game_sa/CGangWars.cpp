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

void CGangWars::InjectHooks() {
//    ReversibleHooks::Install("CGangWars", "AddKillToProvocation", 0x443950, &CGangWars::AddKillToProvocation);
//    ReversibleHooks::Install("CGangWars", "AttackWaveOvercome", 0x0, &CGangWars::AttackWaveOvercome);
//    ReversibleHooks::Install("CGangWars", "CalculateTimeTillNextAttack", 0x0, &CGangWars::CalculateTimeTillNextAttack);
//    ReversibleHooks::Install("CGangWars", "CanPlayerStartAGangWarHere", 0x443F80, &CGangWars::CanPlayerStartAGangWarHere);
//    ReversibleHooks::Install("CGangWars", "CheerVictory", 0x0, &CGangWars::CheerVictory);
//    ReversibleHooks::Install("CGangWars", "ClearSpecificZonesToTriggerGangWar", 0x443FF0, &CGangWars::ClearSpecificZonesToTriggerGangWar);
//    ReversibleHooks::Install("CGangWars", "ClearTheStreets", 0x4444B0, &CGangWars::ClearTheStreets);
//    ReversibleHooks::Install("CGangWars", "CreateAttackWave", 0x444810, &CGangWars::CreateAttackWave);
//    ReversibleHooks::Install("CGangWars", "CreateDefendingGroup", 0x4453D0, &CGangWars::CreateDefendingGroup);
//    ReversibleHooks::Install("CGangWars", "DoStuffWhenPlayerVictorious", 0x0, &CGangWars::DoStuffWhenPlayerVictorious);
//    ReversibleHooks::Install("CGangWars", "DoesPlayerControlThisZone", 0x0, &CGangWars::DoesPlayerControlThisZone);
//    ReversibleHooks::Install("CGangWars", "DontCreateCivilians", 0x0, &CGangWars::DontCreateCivilians);
//    ReversibleHooks::Install("CGangWars", "EndGangWar", 0x4464C0, &CGangWars::EndGangWar);
//    ReversibleHooks::Install("CGangWars", "GangWarFightingGoingOn", 0x443AC0, &CGangWars::GangWarFightingGoingOn);
//    ReversibleHooks::Install("CGangWars", "GangWarGoingOn", 0x0, &CGangWars::GangWarGoingOn);
//    ReversibleHooks::Install("CGangWars", "InitAtStartOfGame", 0x443920, &CGangWars::InitAtStartOfGame);
//    ReversibleHooks::Install("CGangWars", "Load", 0x0, &CGangWars::Load);
//    ReversibleHooks::Install("CGangWars", "MakeEnemyGainInfluenceInZone", 0x0, &CGangWars::MakeEnemyGainInfluenceInZone);
//    ReversibleHooks::Install("CGangWars", "MakePlayerGainInfluenceInZone", 0x0, &CGangWars::MakePlayerGainInfluenceInZone);
//    ReversibleHooks::Install("CGangWars", "PedStreamedInForThisGang", 0x0, &CGangWars::PedStreamedInForThisGang);
//    ReversibleHooks::Install("CGangWars", "PickStreamedInPedForThisGang", 0x0, &CGangWars::PickStreamedInPedForThisGang);
//    ReversibleHooks::Install("CGangWars", "PickZoneToAttack", 0x443B00, &CGangWars::PickZoneToAttack);
//    ReversibleHooks::Install("CGangWars", "ReleaseCarsInAttackWave", 0x0, &CGangWars::ReleaseCarsInAttackWave);
//    ReversibleHooks::Install("CGangWars", "ReleasePedsInAttackWave", 0x0, &CGangWars::ReleasePedsInAttackWave);
//    ReversibleHooks::Install("CGangWars", "Save", 0x5D5530, &CGangWars::Save);
//    ReversibleHooks::Install("CGangWars", "SetGangWarsActive", 0x0, &CGangWars::SetGangWarsActive);
//    ReversibleHooks::Install("CGangWars", "SetSpecificZoneToTriggerGangWar", 0x444010, &CGangWars::SetSpecificZoneToTriggerGangWar);
//    ReversibleHooks::Install("CGangWars", "StartDefensiveGangWar", 0x444300, &CGangWars::StartDefensiveGangWar);
//    ReversibleHooks::Install("CGangWars", "StartOffensiveGangWar", 0x446050, &CGangWars::StartOffensiveGangWar);
//    ReversibleHooks::Install("CGangWars", "StrengthenPlayerInfluenceInZone", 0x0, &CGangWars::StrengthenPlayerInfluenceInZone);
//    ReversibleHooks::Install("CGangWars", "SwitchGangWarsActive", 0x0, &CGangWars::SwitchGangWarsActive);
//    ReversibleHooks::Install("CGangWars", "TellGangMembersTo", 0x0, &CGangWars::TellGangMembersTo);
//    ReversibleHooks::Install("CGangWars", "TellStreamingWhichGangsAreNeeded", 0x443D50, &CGangWars::TellStreamingWhichGangsAreNeeded);
//    ReversibleHooks::Install("CGangWars", "Update", 0x446610, &CGangWars::Update);
//    ReversibleHooks::Install("CGangWars", "UpdateTerritoryUnderControlPercentage", 0x443DE0, &CGangWars::UpdateTerritoryUnderControlPercentage);
}

// 0x443950
void CGangWars::AddKillToProvocation(ePedType pedType) {
    plugin::Call<0x443950, ePedType>(pedType);
}

// 0x0
bool CGangWars::AttackWaveOvercome() {
    return plugin::CallAndReturn<bool, 0x0>();
}

unsigned int CGangWars::CalculateTimeTillNextAttack() {
    return plugin::CallAndReturn<unsigned int, 0x0>();
}

// 0x443F80
bool CGangWars::CanPlayerStartAGangWarHere(CZoneInfo* zoneInfo) {
    return plugin::CallAndReturn<bool, 0x443F80, CZoneInfo*>(zoneInfo);
}

// 0x0
void CGangWars::CheerVictory() {
    plugin::Call<0x0>();
}

// 0x443FF0
void CGangWars::ClearSpecificZonesToTriggerGangWar() {
    plugin::Call<0x443FF0>();
}

// 0x4444B0
void CGangWars::ClearTheStreets() {
    plugin::Call<0x4444B0>();
}

// 0x444810
bool CGangWars::CreateAttackWave(int warFerocity, int waveID) {
    return plugin::CallAndReturn<bool, 0x444810, int, int>(warFerocity, waveID);
}

// 0x4453D0
bool CGangWars::CreateDefendingGroup(int unused) {
    return plugin::CallAndReturn<bool, 0x4453D0, int>(unused);
}

// 0x
void CGangWars::DoStuffWhenPlayerVictorious() {
    plugin::Call<0x0>();
}

// unused
// 0x
bool CGangWars::DoesPlayerControlThisZone(CZoneInfo* zoneInfo) {
    return plugin::CallAndReturn<bool, 0x0, CZoneInfo*>(zoneInfo);;
}

// 0x
bool CGangWars::DontCreateCivilians() {
    return plugin::CallAndReturn<bool, 0x0>();
}

// 0x4464C0
void CGangWars::EndGangWar(bool bEnd) {
    plugin::Call<0x4464C0>();
}

// 0x443AC0
bool CGangWars::GangWarFightingGoingOn() {
    return plugin::CallAndReturn<bool, 0x443AC0>();
}

// 0x
bool CGangWars::GangWarGoingOn() {
    return plugin::CallAndReturn<bool, 0x0>();
}

// 0x443920
void CGangWars::InitAtStartOfGame() {
    plugin::CallDynGlobal(0x443920);
}

// 0x
void CGangWars::Load() {
    plugin::Call<0x0>();
}

// 0x
void CGangWars::MakeEnemyGainInfluenceInZone(int gangId, int gangDensityIncreaser) {
    plugin::Call<0x0, int, int>(gangId, gangDensityIncreaser);
}

// 0x
bool CGangWars::MakePlayerGainInfluenceInZone(float removeMult) {
    return plugin::CallAndReturn<bool, 0x0, float>(removeMult);
}

// 0x
bool CGangWars::PedStreamedInForThisGang(int gangId) {
    return plugin::CallAndReturn<bool, 0x0, int>(gangId);
}

// 0x
bool CGangWars::PickStreamedInPedForThisGang(int gangId, int* outPedId) {
    return plugin::CallAndReturn<bool, 0x0, int, int*>(gangId, outPedId);
}

// 0x443B00
bool CGangWars::PickZoneToAttack() {
    return plugin::CallAndReturn<bool, 0x443B00>();
}

// 0x
void CGangWars::ReleaseCarsInAttackWave() {
    plugin::Call<0x0>();
}

// 0x
// return num of released peds
int CGangWars::ReleasePedsInAttackWave(bool isEndOfWar, bool restoreGangPedsAcquaintance) {
    return plugin::CallAndReturn<int, 0x0, bool, bool>(isEndOfWar, restoreGangPedsAcquaintance);
}

// 0x5D5530
void CGangWars::Save() {
    plugin::Call<0x5D5530>();
}

// 0x
void CGangWars::SetGangWarsActive(bool bActive) {
    plugin::Call<0x0, bool>(bActive);
}

// 0x444010
void CGangWars::SetSpecificZoneToTriggerGangWar(int zoneId) {
    plugin::Call<0x444010, int>(zoneId);
}

// 0x444300
void CGangWars::StartDefensiveGangWar() {
    plugin::Call<0x444300>();
}

// 0x446050
void CGangWars::StartOffensiveGangWar() {
    plugin::Call<0x446050>();
}

// 0x
void CGangWars::StrengthenPlayerInfluenceInZone(int groveDensityIncreaser) {
    plugin::Call<0x0, int>(groveDensityIncreaser);
}

// 0x
// unused
void CGangWars::SwitchGangWarsActive() {
    plugin::Call<0x0>();
}

// 0x
void CGangWars::TellGangMembersTo(bool bIsGangWarEnding) {
    plugin::Call<0x0, bool>(bIsGangWarEnding);
}

// 0x443D50
void CGangWars::TellStreamingWhichGangsAreNeeded(int* GangsBitFlags) {
    plugin::CallDynGlobal<int*>(0x443D50, GangsBitFlags);
}

// 0x446610
void CGangWars::Update() {
    plugin::Call<0x446610>();
}

// 0x443DE0
void CGangWars::UpdateTerritoryUnderControlPercentage() {
    plugin::Call<0x443DE0>();
}
