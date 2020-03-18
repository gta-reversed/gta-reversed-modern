/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

short& MI_FIRE_HYDRANT = *(short*)0x8CD594;
short& MI_PARKINGMETER = *(short*)0x8CD548;
short& MI_PARKINGMETER2 = *(short*)0x8CD54C;
short& MI_POOL_CUE_BALL = *(short*)0x8CD778;

CBaseModelInfo **CModelInfo::ms_modelInfoPtrs = (CBaseModelInfo**)0xA9B0C8;

// Converted from stdcall void CModelInfo::ReInit2dEffects(void) 0x4C63B0
void CModelInfo::ReInit2dEffects()
{
    ((void(__cdecl *)())0x4C63B0)();
}

// Converted from stdcall void CModelInfo::ShutDown(void) 0x4C63E0
void CModelInfo::ShutDown()
{
    ((void(__cdecl *)())0x4C63E0)();
}

// Converted from stdcall CAtomicModelInfo* CModelInfo::AddAtomicModel(int index) 0x4C6620
CAtomicModelInfo* CModelInfo::AddAtomicModel(int index)
{
    return ((CAtomicModelInfo* (__cdecl *)(int))0x4C6620)(index);
}

// Converted from stdcall CDamageAtomicModelInfo* CModelInfo::AddDamageAtomicModel(int index) 0x4C6650
CDamageAtomicModelInfo* CModelInfo::AddDamageAtomicModel(int index)
{
    return ((CDamageAtomicModelInfo* (__cdecl *)(int))0x4C6650)(index);
}

// Converted from stdcall CLodAtomicModelInfo* CModelInfo::AddLodAtomicModel(int index) 0x4C6680
CLodAtomicModelInfo* CModelInfo::AddLodAtomicModel(int index)
{
    return ((CLodAtomicModelInfo* (__cdecl *)(int))0x4C6680)(index);
}

// Converted from stdcall CTimeModelInfo* CModelInfo::AddTimeModel(int index) 0x4C66B0
CTimeModelInfo* CModelInfo::AddTimeModel(int index)
{
    return ((CTimeModelInfo* (__cdecl *)(int))0x4C66B0)(index);
}

// Converted from stdcall CLodTimeModelInfo* CModelInfo::AddLodTimeModel(int index) 0x4C66E0
CLodTimeModelInfo* CModelInfo::AddLodTimeModel(int index)
{
    return ((CLodTimeModelInfo* (__cdecl *)(int))0x4C66E0)(index);
}

// Converted from stdcall CWeaponModelInfo* CModelInfo::AddWeaponModel(int index) 0x4C6710
CWeaponModelInfo* CModelInfo::AddWeaponModel(int index)
{
    return ((CWeaponModelInfo* (__cdecl *)(int))0x4C6710)(index);
}

// Converted from stdcall CClumpModelInfo* CModelInfo::AddClumpModel(int) index 0x4C6740
CClumpModelInfo* CModelInfo::AddClumpModel(int index)
{
    return ((CClumpModelInfo* (__cdecl *)(int))0x4C6740)(index);
}

// Converted from stdcall CVehicleModelInfo* CModelInfo::AddVehicleModel(int index) 0x4C6770
CVehicleModelInfo* CModelInfo::AddVehicleModel(int index)
{
    return ((CVehicleModelInfo* (__cdecl *)(int))0x4C6770)(index);
}

// Converted from stdcall CPedModelInfo* CModelInfo::AddPedModel(int index) 0x4C67A0
CPedModelInfo* CModelInfo::AddPedModel(int index)
{
    return ((CPedModelInfo* (__cdecl *)(int))0x4C67A0)(index);
}

// Converted from stdcall void CModelInfo::Initialise(void) 0x4C6810
void CModelInfo::Initialise()
{
    ((void(__cdecl *)())0x4C6810)();
}

// Converted from stdcall CBaseModelInfo* CModelInfo::GetModelInfo(char* name,int *index) 0x4C5940
CBaseModelInfo* CModelInfo::GetModelInfo(char* name, int* index)
{
    return ((CBaseModelInfo* (__cdecl *)(char*, int*))0x4C5940)(name, index);
}

// Converted from stdcall CBaseModelInfo* CModelInfo::GetModelInfoFromHashKey(uint,int *index) 0x4C59B0
CBaseModelInfo* CModelInfo::GetModelInfoFromHashKey(unsigned int arg0, int* index)
{
    return ((CBaseModelInfo* (__cdecl *)(unsigned int, int*))0x4C59B0)(arg0, index);
}

// Converted from stdcall CBaseModelInfo* CModelInfo::GetModelInfouint16_t(char *name,ushort *int16index) 0x4C59F0
CBaseModelInfo* CModelInfo::GetModelInfouint16_t(char* name, unsigned short* int16index)
{
    return ((CBaseModelInfo* (__cdecl *)(char*, unsigned short*))0x4C59F0)(name, int16index);
}

// Converted from stdcall CBaseModelInfo* CModelInfo::GetModelInfo(char* name,int minIndex,int maxInedx) 0x4C5A20
CBaseModelInfo* CModelInfo::GetModelInfo(char* name, int minIndex, int maxInedx)
{
    return ((CBaseModelInfo* (__cdecl *)(char*, int, int))0x4C5A20)(name, minIndex, maxInedx);
}

// Converted from stdcall void* CModelInfo::Get2dEffectStore(void) 0x4C5A60
void* CModelInfo::Get2dEffectStore()
{
    return ((void* (__cdecl *)())0x4C5A60)();
}

// Converted from stdcall bool CModelInfo::IsBoatModel(int index) 0x4C5A70
bool CModelInfo::IsBoatModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5A70)(index);
}

// Converted from stdcall bool CModelInfo::IsCarModel(int index) 0x4C5AA0
bool CModelInfo::IsCarModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5AA0)(index);
}

// Converted from stdcall bool CModelInfo::IsTrainModel(int index) 0x4C5AD0
bool CModelInfo::IsTrainModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5AD0)(index);
}

// Converted from stdcall bool CModelInfo::IsHeliModel(int index) 0x4C5B00
bool CModelInfo::IsHeliModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5B00)(index);
}

// Converted from stdcall bool CModelInfo::IsPlaneModel(int index) 0x4C5B30
bool CModelInfo::IsPlaneModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5B30)(index);
}

// Converted from stdcall bool CModelInfo::IsBikeModel(int index) 0x4C5B60
bool CModelInfo::IsBikeModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5B60)(index);
}

// Converted from stdcall bool CModelInfo::IsFakePlaneModel(int index) 0x4C5B90
bool CModelInfo::IsFakePlaneModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5B90)(index);
}

// Converted from stdcall bool CModelInfo::IsMonsterTruckModel(int index) 0x4C5BC0
bool CModelInfo::IsMonsterTruckModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5BC0)(index);
}

// Converted from stdcall bool CModelInfo::IsQuadBikeModel(int index) 0x4C5BF0
bool CModelInfo::IsQuadBikeModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5BF0)(index);
}

// Converted from stdcall bool CModelInfo::IsBmxModel(int index) 0x4C5C20
bool CModelInfo::IsBmxModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5C20)(index);
}

// Converted from stdcall bool CModelInfo::IsTrailerModel(int index) 0x4C5C50
bool CModelInfo::IsTrailerModel(int index)
{
    return ((bool(__cdecl *)(int))0x4C5C50)(index);
}

// Converted from stdcall int CModelInfo::IsVehicleModelType(int index) 0x4C5C80
int CModelInfo::IsVehicleModelType(int index)
{
    return ((int(__cdecl *)(int))0x4C5C80)(index);
}

CBaseModelInfo *CModelInfo::GetModelInfo(int index) {
    return CModelInfo::ms_modelInfoPtrs[index];
}