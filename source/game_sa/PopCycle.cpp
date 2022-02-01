/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

float& CPopCycle::m_NumOther_Cars = *(float*)0xC0BC30;
float& CPopCycle::m_NumCops_Cars = *(float*)0xC0BC34;
float& CPopCycle::m_NumGangs_Cars = *(float*)0xC0BC38;
float& CPopCycle::m_NumDealers_Cars = *(float*)0xC0BC3C;
float& CPopCycle::m_NumOther_Peds = *(float*)0xC0BC40;
float& CPopCycle::m_NumCops_Peds = *(float*)0xC0BC44;
float& CPopCycle::m_NumGangs_Peds = *(float*)0xC0BC48;
float& CPopCycle::m_fPercOther = *(float*)0xC0BC4C;
float& CPopCycle::m_fPercCops = *(float*)0xC0BC50;
float& CPopCycle::m_fPercGangs = *(float*)0xC0BC54;
float& CPopCycle::m_fPercDealers = *(float*)0xC0BC58;
bool& CPopCycle::m_bCurrentZoneIsGangArea = *(bool*)0xC0BC5C;
float& CPopCycle::m_fCurrentZoneDodgyness = *(float*)0xC0BC60;
CZone*& CPopCycle::m_pCurrZone = *(CZone**)0xC0BC64;
CZoneInfo*& CPopCycle::m_pCurrZoneInfo = *(CZoneInfo**)0xC0BC68;
int32& CPopCycle::m_nCurrentZoneType = *(int32*)0xC0BC6C;
int32& CPopCycle::m_nCurrentTimeOfWeek = *(int32*)0xC0BC70;
int32& CPopCycle::m_nCurrentTimeIndex = *(int32*)0xC0BC74;
char* CPopCycle::m_nPercTypeGroup = (char*)0xC0BC78;
uint8* CPopCycle::m_nPercOther = (uint8*)0xC0DE38;
uint8* CPopCycle::m_nPercCops = (uint8*)0xC0E018;
uint8* CPopCycle::m_nPercGang = (uint8*)0xC0E1F8;
uint8* CPopCycle::m_nPercDealers = (uint8*)0xC0E3D8;
uint8* CPopCycle::m_nMaxNumCars = (uint8*)0xC0E5B8;
uint8* CPopCycle::m_nMaxNumPeds = (uint8*)0xC0E798;
float& CPopCycle::m_NumDealers_Peds = *(float*)0xC0E978;


// Converted from cdecl bool CPopCycle::FindNewPedType(ePedType *arg1,int32 * modelindex,bool arg3,bool arg4)	0x60FBD0
bool CPopCycle::FindNewPedType(ePedType* arg1, int32* modelindex, bool arg3, bool arg4) {
    return plugin::CallAndReturn<bool, 0x60FBD0, ePedType*, int32*, bool, bool>(arg1, modelindex, arg3, arg4);
}

// Converted from cdecl float CPopCycle::GetCurrentPercOther_Peds()	0x610310
float CPopCycle::GetCurrentPercOther_Peds() {
    return plugin::CallAndReturn<float, 0x610310>();
}

// Converted from cdecl void CPopCycle::Initialise()	0x5BC090
void CPopCycle::Initialise() {
    plugin::Call<0x5BC090>();
}

// Converted from cdecl bool CPopCycle::IsPedAppropriateForCurrentZone(int32 modelindex)	0x610150
bool CPopCycle::IsPedAppropriateForCurrentZone(int32 modelindex) {
    return plugin::CallAndReturn<bool, 0x610150, int32>(modelindex);
}

// Converted from cdecl bool CPopCycle::IsPedInGroup(int32 modelIndex,int32 PopCycle_Group)	0x610210
bool CPopCycle::IsPedInGroup(int32 modelIndex, int32 PopCycle_Group) {
    return plugin::CallAndReturn<bool, 0x610210, int32, int32>(modelIndex, PopCycle_Group);
}

// Converted from cdecl bool CPopCycle::PedIsAcceptableInCurrentZone(int32 modelIndex)	0x610720
bool CPopCycle::PedIsAcceptableInCurrentZone(int32 modelIndex) {
    return plugin::CallAndReturn<bool, 0x610720, int32>(modelIndex);
}

// Converted from cdecl int32 CPopCycle::PickARandomGroupOfOtherPeds()	0x610420
int32 CPopCycle::PickARandomGroupOfOtherPeds() {
    return plugin::CallAndReturn<int32, 0x610420>();
}

int32 CPopCycle::PickPedMIToStreamInForCurrentZone()
{
    return plugin::CallAndReturn<int32, 0x60FFD0>();
}

// Converted from cdecl void CPopCycle::PlayerKilledADealer()	0x610490
void CPopCycle::PlayerKilledADealer() {
    plugin::Call<0x610490>();
}

// Converted from cdecl void CPopCycle::Update()	0x610BF0
void CPopCycle::Update() {
    plugin::Call<0x610BF0>();
}

// Converted from cdecl void CPopCycle::UpdateAreaDodgyness()	0x610560
void CPopCycle::UpdateAreaDodgyness() {
    plugin::Call<0x610560>();
}

// Converted from cdecl void CPopCycle::UpdateDealerStrengths()	0x6104B0
void CPopCycle::UpdateDealerStrengths() {
    plugin::Call<0x6104B0>();
}

// Converted from cdecl void CPopCycle::UpdatePercentages()	0x610770
void CPopCycle::UpdatePercentages() {
    plugin::Call<0x610770>();
}
