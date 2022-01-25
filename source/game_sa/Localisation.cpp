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
    Install("CLocalisation", "Initialise", 0x56D180, &CLocalisation::Initialise);
    Install("CLocalisation", "SetNormalGame", 0x56D1A0, &CLocalisation::SetNormalGame);
    Install("CLocalisation", "SetFrenchGame", 0x56D1C0, &CLocalisation::SetFrenchGame);
    Install("CLocalisation", "SetGermanGame", 0x56D1E0, &CLocalisation::SetGermanGame);
    Install("CLocalisation", "GermanGame", 0x56D200, &CLocalisation::GermanGame);
    Install("CLocalisation", "FrenchGame", 0x56D210, &CLocalisation::FrenchGame);
    Install("CLocalisation", "Metric", 0x56D220, &CLocalisation::Metric);
    Install("CLocalisation", "Blood", 0x56D230, &CLocalisation::Blood);
    Install("CLocalisation", "Porn", 0x56D240, &CLocalisation::Porn);
    Install("CLocalisation", "ScreamsFromKills", 0x56D240, &CLocalisation::ScreamsFromKills);
    Install("CLocalisation", "Prostitutes", 0x56D240, &CLocalisation::Prostitutes);
    Install("CLocalisation", "KickingWhenDown", 0x56D270, &CLocalisation::KickingWhenDown);
    Install("CLocalisation", "ShootLimbs", 0x56D280, &CLocalisation::ShootLimbs);
    Install("CLocalisation", "KnockDownPeds", 0x56D290, &CLocalisation::KnockDownPeds);
    Install("CLocalisation", "KillFrenzy", 0x56D290, &CLocalisation::KillFrenzy);
    Install("CLocalisation", "StealFromDeadPed", 0x56D2B0, &CLocalisation::StealFromDeadPed);
    Install("CLocalisation", "KillPeds", 0x56D2C0, &CLocalisation::KillPeds);
    Install("CLocalisation", "PedsOnFire", 0x56D2C0, &CLocalisation::PedsOnFire);
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
    return FrontEndMenuManager.m_nLanguage != eLanguage::AMERICAN;
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
