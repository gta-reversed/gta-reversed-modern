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

// Converted from cdecl void CWanted::InitialiseStaticVariables(void) 0x561C70
void CWanted::InitialiseStaticVariables() {
    plugin::Call<0x561C70>();
}

// Converted from thiscall void CWanted::UpdateWantedLevel(void) 0x561C90
void CWanted::UpdateWantedLevel() {
    plugin::CallMethod<0x561C90, CWanted*>(this);
}

// Converted from cdecl void CWanted::SetMaximumWantedLevel(int level) 0x561E70
void CWanted::SetMaximumWantedLevel(int level) {
    plugin::Call<0x561E70, int>(level);
}

// Converted from thiscall bool CWanted::AreMiamiViceRequired(void) 0x561F30
bool CWanted::AreMiamiViceRequired() {
    return plugin::CallMethodAndReturn<bool, 0x561F30, CWanted*>(this);
}

// Converted from thiscall bool CWanted::AreSwatRequired(void) 0x561F40
bool CWanted::AreSwatRequired() {
    return plugin::CallMethodAndReturn<bool, 0x561F40, CWanted*>(this);
}

// Converted from thiscall bool CWanted::AreFbiRequired(void) 0x561F60
bool CWanted::AreFbiRequired() {
    return plugin::CallMethodAndReturn<bool, 0x561F60, CWanted*>(this);
}

// Converted from thiscall bool CWanted::AreArmyRequired(void) 0x561F80
bool CWanted::AreArmyRequired() {
    return plugin::CallMethodAndReturn<bool, 0x561F80, CWanted*>(this);
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
void CWanted::RegisterCrime(eCrimeType crimeType, CVector const& posn, unsigned int crimeId, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562410, CWanted*, eCrimeType, CVector const&, unsigned int, bool>(this, crimeType, posn, crimeId, bPoliceDontReallyCare);
}

// Converted from thiscall void CWanted::RegisterCrime_Immediately(eCrimeType crimeType,CVector const&posn,uint crimeId,bool bPoliceDontReallyCare) 0x562430
void CWanted::RegisterCrime_Immediately(eCrimeType crimeType, CVector const& posn, unsigned int crimeId, bool bPoliceDontReallyCare) {
    plugin::CallMethod<0x562430, CWanted*, eCrimeType, CVector const&, unsigned int, bool>(this, crimeType, posn, crimeId, bPoliceDontReallyCare);
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