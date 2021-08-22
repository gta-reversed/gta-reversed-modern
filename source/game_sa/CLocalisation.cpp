/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

bool& CLocalisation::nastyGame = *(bool*)0xB9B7EC;
bool& CLocalisation::germanGame = *(bool*)0xB9B7ED;
bool& CLocalisation::frenchGame = *(bool*)0xB9B7EE;

void CLocalisation::InjectHooks() {
    ReversibleHooks::Install("CLocalisation", "Initialise", 0x56D180, &CLocalisation::Initialise);
    ReversibleHooks::Install("CLocalisation", "SetNormalGame", 0x56D1A0, &CLocalisation::SetNormalGame);
    ReversibleHooks::Install("CLocalisation", "SetFrenchGame", 0x56D1C0, &CLocalisation::SetFrenchGame);
    ReversibleHooks::Install("CLocalisation", "SetGermanGame", 0x56D1E0, &CLocalisation::SetGermanGame);
    ReversibleHooks::Install("CLocalisation", "GermanGame", 0x56D200, &CLocalisation::GermanGame);
    ReversibleHooks::Install("CLocalisation", "FrenchGame", 0x56D210, &CLocalisation::FrenchGame);
    ReversibleHooks::Install("CLocalisation", "Metric", 0x56D220, &CLocalisation::Metric);
    ReversibleHooks::Install("CLocalisation", "Blood", 0x56D230, &CLocalisation::Blood);
    ReversibleHooks::Install("CLocalisation", "Porn", 0x56D240, &CLocalisation::Porn);
    ReversibleHooks::Install("CLocalisation", "ScreamsFromKills", 0x56D240, &CLocalisation::ScreamsFromKills);
    ReversibleHooks::Install("CLocalisation", "Prostitutes", 0x56D240, &CLocalisation::Prostitutes);
    ReversibleHooks::Install("CLocalisation", "KickingWhenDown", 0x56D270, &CLocalisation::KickingWhenDown);
    ReversibleHooks::Install("CLocalisation", "ShootLimbs", 0x56D280, &CLocalisation::ShootLimbs);
    ReversibleHooks::Install("CLocalisation", "KnockDownPeds", 0x56D290, &CLocalisation::KnockDownPeds);
    ReversibleHooks::Install("CLocalisation", "KillFrenzy", 0x56D290, &CLocalisation::KillFrenzy);
    ReversibleHooks::Install("CLocalisation", "StealFromDeadPed", 0x56D2B0, &CLocalisation::StealFromDeadPed);
    ReversibleHooks::Install("CLocalisation", "KillPeds", 0x56D2C0, &CLocalisation::KillPeds);
    ReversibleHooks::Install("CLocalisation", "PedsOnFire", 0x56D2C0, &CLocalisation::PedsOnFire);
}

// 0x56D180
void CLocalisation::Initialise() {
    nastyGame = true;
    germanGame = false;
    frenchGame = false;
}

// 0x56D1A0
void CLocalisation::SetNormalGame() {
    nastyGame = true;
    frenchGame = false;
    germanGame = false;
}

// 0x56D1C0
void CLocalisation::SetFrenchGame() {
    frenchGame = true;
    germanGame = false;
    nastyGame = true;
}

// 0x56D1E0
void CLocalisation::SetGermanGame() {
    germanGame = true;
    frenchGame = false;
    nastyGame = false;
}

// 0x56D200
bool CLocalisation::GermanGame() {
    return germanGame;
}

// 0x56D210
bool CLocalisation::FrenchGame() {
    return frenchGame;
}

// 0x56D220
bool CLocalisation::Metric() {
    return FrontEndMenuManager.m_nLanguage != false;
}

// 0x56D230
bool CLocalisation::Blood() {
    return true;
}

// 0x56D240
bool CLocalisation::Porn() {
    return true;
}

// 0x56D250
bool CLocalisation::ScreamsFromKills() {
    return !germanGame;
}

// 0x56D260
bool CLocalisation::Prostitutes() {
    return true;
}

// 0x56D270
bool CLocalisation::KickingWhenDown() {
    return true;
}

// 0x56D280
bool CLocalisation::ShootLimbs() {
    return nastyGame;
}

// 0x56D290
bool CLocalisation::KnockDownPeds() {
    return nastyGame;
}

// 0x56D2A0
bool CLocalisation::KillFrenzy() {
    return nastyGame;
}

// 0x56D2B0
bool CLocalisation::StealFromDeadPed() {
    return nastyGame;
}

// 0x56D2C0
bool CLocalisation::KillPeds() {
    return nastyGame;
}

// 0x56D2D0
bool CLocalisation::PedsOnFire() {
    return nastyGame;
}