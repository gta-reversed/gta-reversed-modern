/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned int& CWanted::MaximumWantedLevel = *(unsigned int*)0x8CDEE4;
unsigned int& CWanted::nMaximumWantedLevel = *(unsigned int*)0x8CDEE8;
bool& CWanted::bUseNewsHeliInAdditionToPolice = *(bool*)0xB7CB8C;

void CWanted::InjectHooks()
{
    HookInstall(0x561F40, &CWanted::AreSwatRequired);
    HookInstall(0x561F60, &CWanted::AreFbiRequired);
    HookInstall(0x561F80, &CWanted::AreArmyRequired);
    HookInstall(0x561C70, &CWanted::InitialiseStaticVariables);
    HookInstall(0x561E70, &CWanted::SetMaximumWantedLevel);
}

// Converted from cdecl void CWanted::InitialiseStaticVariables(void) 0x561C70
// Initialize Static Variables
void CWanted::InitialiseStaticVariables() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x561C70>();
#else
    MaximumWantedLevel = 6;
    nMaximumWantedLevel = 9200;
    bUseNewsHeliInAdditionToPolice = 0;
#endif // USE_DEFAULT_FUNCTIONS

}

// Converted from thiscall void CWanted::UpdateWantedLevel(void) 0x561C90
void CWanted::UpdateWantedLevel() {
    plugin::CallMethod<0x561C90, CWanted*>(this);
}

// Converted from cdecl void CWanted::SetMaximumWantedLevel(int level) 0x561E70
// Set Maximum Wanted Level
void CWanted::SetMaximumWantedLevel(int level) 
{
#ifdef USE_DEFAULT_FUNCTIONS

    plugin::Call<0x561E70, int>(level);
#else
    switch (level)
    {
    case 0:
        MaximumWantedLevel = 0;
        nMaximumWantedLevel = 0;
        break;
    case 1:
        MaximumWantedLevel = 1;
        nMaximumWantedLevel = 115;
        break;
    case 2:
        MaximumWantedLevel = 2;
        nMaximumWantedLevel = 365;
        break;
    case 3:
        MaximumWantedLevel = 3;
        nMaximumWantedLevel = 875;
        break;
    case 4:
        MaximumWantedLevel = 4;
        nMaximumWantedLevel = 1800;
        break;
    case 5:
        MaximumWantedLevel = 5;
        nMaximumWantedLevel = 3500;
        break;
    case 6:
        MaximumWantedLevel = 6;
        nMaximumWantedLevel = 6900;
        break;
    default:
        return;
    }

#endif
}

// Converted from thiscall bool CWanted::AreMiamiViceRequired(void) 0x561F30
bool CWanted::AreMiamiViceRequired() {
    return plugin::CallMethodAndReturn<bool, 0x561F30, CWanted*>(this);
}

// Converted from thiscall bool CWanted::AreSwatRequired(void) 0x561F40
// Checks if SWAT is needed after four wanted level stars
bool CWanted::AreSwatRequired() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x561F40, CWanted*>(this);
#else
    return m_nWantedLevel == 4 || m_bSwatRequired;
#endif // USE_DEFAULT_FUNCTIONS
}

// Converted from thiscall bool CWanted::AreFbiRequired(void) 0x561F60
// Checks if FBI is needed after five wanted level stars
bool CWanted::AreFbiRequired() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x561F60, CWanted*>(this);
#else
    return m_nWantedLevel == 5 || m_bFbiRequired;
#endif // USE_DEFAULT_FUNCTIONS
}

// Converted from thiscall bool CWanted::AreArmyRequired(void) 0x561F80
// Checks if Army is needed after six wanted level stars
bool CWanted::AreArmyRequired() 
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x561F80, CWanted*>(this);
#else
    return m_nWantedLevel == 6 || m_bArmyRequired;
#endif // USE_DEFAULT_FUNCTIONS
}

// Converted from thiscall int CWanted::NumOfHelisRequired(void) 0x561FA0
int CWanted::NumOfHelisRequired() {
    return plugin::CallMethodAndReturn<int, 0x561FA0, CWanted*>(this);
}

// Converted from cdecl void CWanted::ResetPolicePursuit(void) 0x561FD0
void CWanted::ResetPolicePursuit() {
    plugin::Call<0x561FD0>();
}

// Converted from thiscall void CWanted::ClearQdCrimes(void) 0x561FE0
void CWanted::ClearQdCrimes() {
    plugin::CallMethod<0x561FE0, CWanted*>(this);
}

// Converted from thiscall bool CWanted::AddCrimeToQ(eCrimeType crimeType,int crimeId,CVector const&posn,bool bAlreadyReported,bool bPoliceDontReallyCare) 0x562000
bool CWanted::AddCrimeToQ(eCrimeType crimeType, int crimeId, CVector const& posn, bool bAlreadyReported, bool bPoliceDontReallyCare) {
    return plugin::CallMethodAndReturn<bool, 0x562000, CWanted*, eCrimeType, int, CVector const&, bool, bool>(this, crimeType, crimeId, posn, bAlreadyReported, bPoliceDontReallyCare);
}

// Converted from thiscall void CWanted::ReportCrimeNow(eCrimeType crimeType,CVector const&posn,bool bPoliceDontReallyCare) 0x562120
void CWanted::ReportCrimeNow(eCrimeType crimeType, CVector const& posn, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562120, CWanted*, eCrimeType, CVector const&, bool>(this, crimeType, posn, bPoliceDontReallyCare);
}

// Converted from cdecl void CWanted::RemovePursuitCop(CCopPed *cop,CCopPed **copsArray,uchar &copsCounter) 0x562300
void CWanted::RemovePursuitCop(CCopPed* cop, CCopPed** copsArray, unsigned char& copsCounter) {
    plugin::Call<0x562300, CCopPed*, CCopPed**, unsigned char&>(cop, copsArray, copsCounter);
}

// Converted from thiscall bool CWanted::IsInPursuit(CCopPed *cop) 0x562330
bool CWanted::IsInPursuit(CCopPed* cop) {
    return plugin::CallMethodAndReturn<bool, 0x562330, CWanted*, CCopPed*>(this, cop);
}

// Converted from cdecl void CWanted::UpdateEachFrame(void) 0x562360
void CWanted::UpdateEachFrame() {
    plugin::Call<0x562360>();
}

// Converted from thiscall void CWanted::Initialise(void) 0x562390
void CWanted::Initialise() {
    plugin::CallMethod<0x562390, CWanted*>(this);
}

// Converted from thiscall void CWanted::Reset(void) 0x562400
void CWanted::Reset() {
    plugin::CallMethod<0x562400, CWanted*>(this);
}

// Converted from thiscall void CWanted::RegisterCrime(eCrimeType crimeType,CVector const&posn,uint crimeId,bool bPoliceDontReallyCare) 0x562410
void CWanted::RegisterCrime(eCrimeType crimeType, CVector const& posn, CPed* ped, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562410, CWanted*, eCrimeType, CVector const&, CPed*, bool>(this, crimeType, posn, ped, bPoliceDontReallyCare);
}

// Converted from thiscall void CWanted::RegisterCrime_Immediately(eCrimeType crimeType,CVector const&posn,uint crimeId,bool bPoliceDontReallyCare) 0x562430
void CWanted::RegisterCrime_Immediately(eCrimeType crimeType, CVector const& posn, CPed* ped, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562430, CWanted*, eCrimeType, CVector const&, CPed*, bool>(this, crimeType, posn, ped, bPoliceDontReallyCare);
}

// Converted from thiscall void CWanted::SetWantedLevel(int level) 0x562470
void CWanted::SetWantedLevel(int level) {
    plugin::CallMethod<0x562470, CWanted*, int>(this, level);
}

// Converted from thiscall void CWanted::CheatWantedLevel(int level) 0x562540
void CWanted::CheatWantedLevel(int level) {
    plugin::CallMethod<0x562540, CWanted*, int>(this, level);
}

// Converted from thiscall void CWanted::SetWantedLevelNoDrop(int level) 0x562570
void CWanted::SetWantedLevelNoDrop(int level) {
    plugin::CallMethod<0x562570, CWanted*, int>(this, level);
}

// Converted from thiscall void CWanted::ClearWantedLevelAndGoOnParole(void) 0x5625A0
void CWanted::ClearWantedLevelAndGoOnParole() {
    plugin::CallMethod<0x5625A0, CWanted*>(this);
}

// Converted from cdecl int CWanted::WorkOutPolicePresence(CVector posn,float radius) 0x5625F0
int CWanted::WorkOutPolicePresence(CVector posn, float radius) {
    return plugin::CallAndReturn<int, 0x5625F0, CVector, float>(posn, radius);
}

// Converted from thiscall void CWanted::UpdateCrimesQ(void) 0x562760
void CWanted::UpdateCrimesQ() {
    plugin::CallMethod<0x562760, CWanted*>(this);
}

// Converted from thiscall bool CWanted::IsClosestCop(CPed *ped,int numCopsToCheck) 0x5627D0
bool CWanted::IsClosestCop(CPed* ped, int numCopsToCheck) {
    return plugin::CallMethodAndReturn<bool, 0x5627D0, CWanted*, CPed*, int>(this, ped, numCopsToCheck);
}

// Converted from cdecl CCopPed* CWanted::ComputePursuitCopToDisplace(CCopPed *cop,CCopPed **copsArray) 0x562B00
CCopPed* CWanted::ComputePursuitCopToDisplace(CCopPed* cop, CCopPed** copsArray) {
    return plugin::CallAndReturn<CCopPed*, 0x562B00, CCopPed*, CCopPed**>(cop, copsArray);
}

// Converted from thiscall void CWanted::RemovePursuitCop(CCopPed *cop) 0x562C10
void CWanted::RemovePursuitCop(CCopPed* cop) {
    plugin::CallMethod<0x562C10, CWanted*, CCopPed*>(this, cop);
}

// Converted from thiscall void CWanted::RemoveExcessPursuitCops(void) 0x562C40
void CWanted::RemoveExcessPursuitCops() {
    plugin::CallMethod<0x562C40, CWanted*>(this);
}

// Converted from thiscall void CWanted::Update(void) 0x562C90
void CWanted::Update() {
    plugin::CallMethod<0x562C90, CWanted*>(this);
}

// Converted from cdecl bool CWanted::CanCopJoinPursuit(CCopPed *cop,uchar maxCopsCount,CCopPed **copsArray,uchar &copsCounter) 0x562F60
bool CWanted::CanCopJoinPursuit(CCopPed* cop, unsigned char maxCopsCount, CCopPed** copsArray, unsigned char& copsCounter) {
    return plugin::CallAndReturn<bool, 0x562F60, CCopPed*, unsigned char, CCopPed**, unsigned char&>(cop, maxCopsCount, copsArray, copsCounter);
}

// Converted from thiscall bool CWanted::CanCopJoinPursuit(CCopPed *cop) 0x562FB0
bool CWanted::CanCopJoinPursuit(CCopPed* cop) {
    return plugin::CallMethodAndReturn<bool, 0x562FB0, CWanted*, CCopPed*>(this, cop);
}

// Converted from thiscall bool CWanted::SetPursuitCop(CCopPed *cop) 0x563060
bool CWanted::SetPursuitCop(CCopPed* cop) {
    return plugin::CallMethodAndReturn<bool, 0x563060, CWanted*, CCopPed*>(this, cop);
}
