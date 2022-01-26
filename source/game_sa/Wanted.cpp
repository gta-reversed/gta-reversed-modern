/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

uint32& CWanted::MaximumWantedLevel = *(uint32*)0x8CDEE4;
// 0x8CDEE8
uint32 CWanted::MaximumChaosLevel = 9200; // original name nMaximumWantedLevel
bool& CWanted::bUseNewsHeliInAdditionToPolice = *(bool*)0xB7CB8C;

void CWanted::InjectHooks()
{
    RH_ScopedInstall(UpdateWantedLevel, 0x561C90);
    RH_ScopedInstall(AreSwatRequired, 0x561F40);
    RH_ScopedInstall(AreFbiRequired, 0x561F60);
    RH_ScopedInstall(AreArmyRequired, 0x561F80);
    RH_ScopedInstall(InitialiseStaticVariables, 0x561C70);
    RH_ScopedInstall(SetMaximumWantedLevel, 0x561E70);
    RH_ScopedInstall(Initialise, 0x562390);
    RH_ScopedInstall(ClearQdCrimes, 0x561FE0);
    RH_ScopedInstall(IsInPursuit, 0x562330);
    RH_ScopedInstall(SetWantedLevel, 0x562470);
    RH_ScopedInstall(CheatWantedLevel, 0x562540);
    RH_ScopedInstall(SetWantedLevelNoDrop, 0x562570);
    RH_ScopedInstall(ClearWantedLevelAndGoOnParole, 0x5625A0);
    RH_ScopedOverloadedInstall(CanCopJoinPursuit, "func", 0x562F60, bool (*)(CCopPed*, uint8, CCopPed**, uint8&));
    // RH_ScopedOverloadedInstall(CanCopJoinPursuit, "method", 0x562FB0, bool (CWanted::*)(CCopPed*));
}

// 0x562390
void CWanted::Initialise() {
    m_nFlags &= 0xC0;
    m_nChaosLevel = 0;
    m_nChaosLevelBeforeParole = 0;
    m_nLastTimeWantedDecreased = 0;
    m_nLastTimeWantedLevelChanged = 0;
    m_nTimeOfParole = 0;
    m_nCopsInPursuit = 0;
    m_nMaxCopsInPursuit = 0;
    m_nMaxCopCarsInPursuit = 0;
    m_nChanceOnRoadBlock = 0;
    m_fMultiplier = 1.0f;
    m_nTimeCounting = 0;
    m_bLeavePlayerAlone = false;
    m_nWantedLevel = 0;
    m_nWantedLevelBeforeParole = 0;
    m_nCopsBeatingSuspect = 0;

    for (auto& cop : m_pCopsInPursuit) {
        cop  = nullptr;
    }

    ClearQdCrimes();
}

// 0x562400
void CWanted::Reset() {
    Initialise();
}

// Initialize Static Variables
// 0x561C70
void CWanted::InitialiseStaticVariables() 
{
    MaximumWantedLevel = 6;
    MaximumChaosLevel = 9200;
    bUseNewsHeliInAdditionToPolice = false;
}

// 0x561C90
void CWanted::UpdateWantedLevel() {
    //plugin::CallMethod<0x561C90, CWanted*>(this);
    m_nChaosLevel = std::min(m_nChaosLevel, MaximumChaosLevel);

    uint32 wantedLevel = m_nWantedLevel;

    if (m_nChaosLevel > 4800) {
        CStats::IncrementStat(eStats::STAT_TOTAL_NUMBER_OF_WANTED_STARS_ATTAINED, (float)(6 - wantedLevel));
        m_nWantedLevel = 6;
        m_nMaxCopCarsInPursuit = 3;
        m_nMaxCopsInPursuit = 10;
        m_nChanceOnRoadBlock = 30;
    }
    else if (m_nChaosLevel > 2400) {
        CStats::IncrementStat(eStats::STAT_TOTAL_NUMBER_OF_WANTED_STARS_ATTAINED, (float)(5 - wantedLevel));
        m_nWantedLevel = 5;
        m_nMaxCopCarsInPursuit = 2;
        m_nMaxCopsInPursuit = 6;
        m_nChanceOnRoadBlock = 24;
    }
    else if (m_nChaosLevel > 1200) {
        CStats::IncrementStat(eStats::STAT_TOTAL_NUMBER_OF_WANTED_STARS_ATTAINED, (float)(4 - wantedLevel));
        m_nWantedLevel = 4;
        m_nMaxCopCarsInPursuit = 2;
        m_nMaxCopsInPursuit = 6;
        m_nChanceOnRoadBlock = 18;
    }
    else if (m_nChaosLevel > 550) {
        CStats::IncrementStat(eStats::STAT_TOTAL_NUMBER_OF_WANTED_STARS_ATTAINED, (float)(3 - wantedLevel));
        m_nWantedLevel = 3;
        m_nMaxCopCarsInPursuit = 2;
        m_nMaxCopsInPursuit = 4;
        m_nChanceOnRoadBlock = 12;
    }
    else if (m_nChaosLevel > 180) {
        CStats::IncrementStat(eStats::STAT_TOTAL_NUMBER_OF_WANTED_STARS_ATTAINED, (float)(2 - wantedLevel));
        m_nWantedLevel = 2;
        m_nMaxCopCarsInPursuit = 2;
        m_nMaxCopsInPursuit = 3;
        m_nChanceOnRoadBlock = 0;
    }
    else if (m_nChaosLevel > 50) {
        CStats::IncrementStat(eStats::STAT_TOTAL_NUMBER_OF_WANTED_STARS_ATTAINED, (float)(1 - wantedLevel));
        m_nWantedLevel = 1;
        m_nMaxCopCarsInPursuit = 1;
        m_nMaxCopsInPursuit = 1;
        m_nChanceOnRoadBlock = 0;
    }
    else {
        if (m_nWantedLevel == 1)
            CStats::IncrementStat(STAT_TOTAL_NUMBER_OF_WANTED_STARS_EVADED, 1.0);

        m_nWantedLevel = 0;
        m_nMaxCopCarsInPursuit = 0;
        m_nMaxCopsInPursuit = 0;
        m_nChanceOnRoadBlock = 0;
    }

    if (wantedLevel != m_nWantedLevel)
        m_nLastTimeWantedLevelChanged = CTimer::GetTimeInMS();

    if (m_bEverybodyBackOff || m_bPoliceBackOff || m_bPoliceBackOffGarage) {
        m_nMaxCopCarsInPursuit = 0;
        m_nMaxCopsInPursuit = 0;
        m_nChanceOnRoadBlock = 0;
    }
}

// Set Maximum Wanted Level
// 0x561E70
void CWanted::SetMaximumWantedLevel(int32 level)
{
    switch (level)
    {
    case 0:
        MaximumWantedLevel = 0;
        MaximumChaosLevel = 0;
        break;
    case 1:
        MaximumWantedLevel = 1;
        MaximumChaosLevel = 115;
        break;
    case 2:
        MaximumWantedLevel = 2;
        MaximumChaosLevel = 365;
        break;
    case 3:
        MaximumWantedLevel = 3;
        MaximumChaosLevel = 875;
        break;
    case 4:
        MaximumWantedLevel = 4;
        MaximumChaosLevel = 1800;
        break;
    case 5:
        MaximumWantedLevel = 5;
        MaximumChaosLevel = 3500;
        break;
    case 6:
        MaximumWantedLevel = 6;
        MaximumChaosLevel = 6900;
        break;
    default:
        return;
    }
}

// 0x561F30
bool CWanted::AreMiamiViceRequired() {
    return plugin::CallMethodAndReturn<bool, 0x561F30, CWanted*>(this);
}

// Checks if SWAT is needed after four wanted level stars
// 0x561F40
bool CWanted::AreSwatRequired() const
{
    return m_nWantedLevel == 4 || m_bSwatRequired;
}

// Checks if FBI is needed after five wanted level stars
// 0x561F60
bool CWanted::AreFbiRequired() const
{
    return m_nWantedLevel == 5 || m_bFbiRequired;
}

// Checks if Army is needed after six wanted level stars
// 0x561F80
bool CWanted::AreArmyRequired() const
{
    return m_nWantedLevel == 6 || m_bArmyRequired;
}

// 0x561FA0
int32 CWanted::NumOfHelisRequired() {
    return plugin::CallMethodAndReturn<int32, 0x561FA0, CWanted*>(this);
}

// 0x561FD0
void CWanted::ResetPolicePursuit() {
    plugin::Call<0x561FD0>();
}

// 0x562760
void CWanted::UpdateCrimesQ() {
    plugin::CallMethod<0x562760, CWanted*>(this);
}

// 0x561FE0
void CWanted::ClearQdCrimes() {
    for (auto& crime : m_CrimesBeingQd) {
        crime.m_nCrimeType = eCrimeType::CRIME_NONE;
    }
}

// 0x562000
bool CWanted::AddCrimeToQ(eCrimeType crimeType, int32 crimeId, const CVector& posn, bool bAlreadyReported, bool bPoliceDontReallyCare) {
    return plugin::CallMethodAndReturn<bool, 0x562000, CWanted*, eCrimeType, int32, const CVector&, bool, bool>(this, crimeType, crimeId, posn, bAlreadyReported, bPoliceDontReallyCare);
}

// 0x562120
void CWanted::ReportCrimeNow(eCrimeType crimeType, const CVector& posn, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562120, CWanted*, eCrimeType, const CVector&, bool>(this, crimeType, posn, bPoliceDontReallyCare);
}

// 0x562300
void CWanted::RemovePursuitCop(CCopPed* cop, CCopPed** copsArray, uint8& copsCounter) {
    plugin::Call<0x562300, CCopPed*, CCopPed**, uint8&>(cop, copsArray, copsCounter);
}

// 0x562330
bool CWanted::IsInPursuit(CCopPed* cop) {
    for (auto& elem : m_pCopsInPursuit) {
        if (elem == cop) {
            return true;
        }
    }

    return false;
}

// 0x562360
void CWanted::UpdateEachFrame() {
    plugin::Call<0x562360>();
}

// 0x562410
void CWanted::RegisterCrime(eCrimeType crimeType, const CVector& posn, CPed* ped, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562410, CWanted*, eCrimeType, CVector const&, CPed*, bool>(this, crimeType, posn, ped, bPoliceDontReallyCare);
}

// 0x562430
void CWanted::RegisterCrime_Immediately(eCrimeType crimeType, const CVector& posn, CPed* ped, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562430, CWanted*, eCrimeType, CVector const&, CPed*, bool>(this, crimeType, posn, ped, bPoliceDontReallyCare);
}

// 0x562470
void CWanted::SetWantedLevel(uint32 level) {
    if (CCheat::m_aCheatsActive[CHEAT_I_DO_AS_I_PLEASE])
        return;

    uint32 newLevel = std::min(level, MaximumWantedLevel);

    ClearQdCrimes();

    switch (newLevel) {
    case 0:
        m_nChaosLevel = 0;
        break;
    case 1:
        m_nChaosLevel = 70;
        break;
    case 2:
        m_nChaosLevel = 200;
        break;
    case 3:
        m_nChaosLevel = 570;
        break;
    case 4:
        m_nChaosLevel = 1220;
        break;
    case 5:
        m_nChaosLevel = 2420;
        break;
    case 6:
        m_nChaosLevel = 4620;
        break;
    }
    UpdateWantedLevel();
}

// 0x562540
void CWanted::CheatWantedLevel(uint32 level) {
    if (level > MaximumWantedLevel) {
        SetMaximumWantedLevel(level);
    }

    SetWantedLevel(level);
    UpdateWantedLevel();
}

// 0x562570
void CWanted::SetWantedLevelNoDrop(uint32 level) {
    if (m_nWantedLevel < m_nWantedLevelBeforeParole)
        SetWantedLevel(m_nWantedLevelBeforeParole);

    if (level > m_nWantedLevel)
        SetWantedLevel(level);
}

// 0x5625A0
void CWanted::ClearWantedLevelAndGoOnParole() {
    CStats::IncrementStat(STAT_TOTAL_NUMBER_OF_WANTED_STARS_EVADED, m_nWantedLevel);
    auto playerWanted = FindPlayerWanted(-1);
    m_nChaosLevelBeforeParole = playerWanted->m_nChaosLevel;
    m_nWantedLevelBeforeParole = playerWanted->m_nWantedLevel;
    m_nTimeOfParole = CTimer::GetTimeInMS();
    m_nChaosLevel = 0;
    m_nWantedLevel = 0;
}

// 0x5625F0
int32 CWanted::WorkOutPolicePresence(CVector posn, float radius) {
    return plugin::CallAndReturn<int32, 0x5625F0, CVector, float>(posn, radius);
}

// 0x5627D0
bool CWanted::IsClosestCop(CPed* ped, int32 numCopsToCheck) {
    return plugin::CallMethodAndReturn<bool, 0x5627D0, CWanted*, CPed*, int32>(this, ped, numCopsToCheck);
}

// 0x562B00
CCopPed* CWanted::ComputePursuitCopToDisplace(CCopPed* cop, CCopPed** copsArray) {
    return plugin::CallAndReturn<CCopPed*, 0x562B00, CCopPed*, CCopPed**>(cop, copsArray);
}

// 0x562C10
void CWanted::RemovePursuitCop(CCopPed* cop) {
    plugin::CallMethod<0x562C10, CWanted*, CCopPed*>(this, cop);
}

// 0x562C40
void CWanted::RemoveExcessPursuitCops() {
    plugin::CallMethod<0x562C40, CWanted*>(this);
}

// 0x562C90
void CWanted::Update() {
    plugin::CallMethod<0x562C90, CWanted*>(this);
}

// 0x562F60
bool CWanted::CanCopJoinPursuit(CCopPed* target, uint8 maxCopsCount, CCopPed** copsArray, uint8& copsCounter) {
    if (!maxCopsCount)
        return false;

    while (true) {
        if (copsCounter < maxCopsCount)
            return true;

        CCopPed* cop = ComputePursuitCopToDisplace(target, copsArray);
        if (!cop)
            break;

        RemovePursuitCop(cop, copsArray, copsCounter);
    }
    return false;
}

// 0x562FB0
bool CWanted::CanCopJoinPursuit(CCopPed* cop) {
    return plugin::CallMethodAndReturn<bool, 0x562FB0, CWanted*, CCopPed*>(this, cop);
}

// 0x563060
bool CWanted::SetPursuitCop(CCopPed* cop) {
    return plugin::CallMethodAndReturn<bool, 0x563060, CWanted*, CCopPed*>(this, cop);
}
