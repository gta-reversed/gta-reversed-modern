/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#define FUNC_CTheZones__InitZonesPopulationSettings 0x5720D0
#define FUNC_CTheZones__ResetZonesRevealed 0x572110
#define FUNC_CTheZones__GetCurrentZoneLockedOrUnlocked 0x572130
#define FUNC_CTheZones__AssignZoneInfoForThisZone 0x572180
#define FUNC_CTheZones__ZoneIsEntirelyContainedWithinOtherZone 0x572220
#define FUNC_CTheZones__PointLiesWithinZone 0x572270
#define FUNC_CTheZones__GetLevelFromPosition 0x572300
#define FUNC_CTheZones__FindSmallestZoneForPosition 0x572360
#define FUNC_CTheZones__GetZoneInfo 0x572400
#define FUNC_CTheZones__FillZonesWithGangColours 0x572440
#define FUNC_CTheZones__GetInfoZone 0x572590
#define FUNC_CTheZones__GetMapZone 0x5725A0
#define FUNC_CTheZones__Calc2DDistanceBetween2Zones 0x5725b0
#define FUNC_CTheZones__Init 0x572670
#define FUNC_CTheZones__SetCurrentZoneAsUnlocked 0x572800
#define FUNC_CTheZones__CreateZone 0x5728A0
#define FUNC_CTheZones__FindZone 0x572B80
#define FUNC_CTheZones__FindZoneByLabel 0x572C40
#define FUNC_CTheZones__SetZoneRadarColours 0x572cc0
#define FUNC_CTheZones__Update 0x572D10
#define FUNC_CTheZones__Save 0x5D2E60 
#define FUNC_CTheZones__Load 0x5D2F40

// Variables
eLevelName& CTheZones::m_CurrLevel = *(eLevelName*)0xBA6718;

char* CTheZones::ZonesVisited = (char*)0xBA3730;
int& CTheZones::ZonesRevealed = *(int*)0xBA372C;

short& CTheZones::TotalNumberOfMapZones = *(short*)0xBA1900;
CZone* CTheZones::NavigationZoneArray = (CZone*)0xBA3798; 

short& CTheZones::TotalNumberOfNavigationZones = *(short*)0xBA3794;
CZone* CTheZones::MapZoneArray = (CZone*)0xBA1908;

short& CTheZones::TotalNumberOfZoneInfos = *(short*)0xBA1DE8;
CZoneInfo* CTheZones::ZoneInfoArray = (CZoneInfo*)0xBA1DF0;


void CTheZones::InjectHooks()
{
    ReversibleHooks::Install("CTheZones", "ResetZonesRevealed", FUNC_CTheZones__ResetZonesRevealed, &CTheZones::ResetZonesRevealed);
    ReversibleHooks::Install("CTheZones", "GetCurrentZoneLockedOrUnlocked", FUNC_CTheZones__GetCurrentZoneLockedOrUnlocked, &CTheZones::GetCurrentZoneLockedOrUnlocked);
    ReversibleHooks::Install("CTheZones", "PointLiesWithinZone", FUNC_CTheZones__PointLiesWithinZone, &CTheZones::PointLiesWithinZone);
    ReversibleHooks::Install("CTheZones", "GetNavigationZone", FUNC_CTheZones__GetInfoZone, &CTheZones::GetNavigationZone);
    ReversibleHooks::Install("CTheZones", "GetMapZone", FUNC_CTheZones__GetMapZone, &CTheZones::GetMapZone);
    ReversibleHooks::Install("CTheZones", "Save", FUNC_CTheZones__Save, &CTheZones::Save);
    ReversibleHooks::Install("CTheZones", "Load", FUNC_CTheZones__Load, &CTheZones::Load);
    ReversibleHooks::Install("CTheZones", "PostZoneCreation", 0x572B70, &CTheZones::PostZoneCreation);
}

// Functions
void CTheZones::InitZonesPopulationSettings()
{
    ((void(__cdecl*)()) FUNC_CTheZones__InitZonesPopulationSettings)();
}

void CTheZones::ResetZonesRevealed()
{
    memset(ZonesVisited, 0, 100); // TODO: sizeof(CTheZones::ExploredTerritoriesArray)
    ZonesRevealed = 0;
}

bool CTheZones::GetCurrentZoneLockedOrUnlocked(float posx, float posy)
{
    return CTheZones::ZonesVisited[10 *	(unsigned __int8)((posx + 3000.0) * 0.0016666667) -
                                        (unsigned __int8)((posy + 3000.0) * 0.0016666667) + 9] != 0;
}

void CTheZones::AssignZoneInfoForThisZone(short index)
{
    ((void(__cdecl*)(short)) FUNC_CTheZones__AssignZoneInfoForThisZone) (index);
}

bool CTheZones::ZoneIsEntirelyContainedWithinOtherZone(CZone* pZone1, CZone* pZone2)
{
    return ((bool(__cdecl*)(CZone*, CZone*)) FUNC_CTheZones__ZoneIsEntirelyContainedWithinOtherZone) (pZone1, pZone2);
}

// Returns true if point lies within zone
bool CTheZones::PointLiesWithinZone(CVector const* pPoint, CZone* pZone)
{
    return
        pZone->m_fX1 <= pPoint->x &&
        pZone->m_fX2 >= pPoint->x && 
        pZone->m_fY1 <= pPoint->y && 
        pZone->m_fY2 >= pPoint->y && 
        pZone->m_fZ1 <= pPoint->z && 
        pZone->m_fZ2 >= pPoint->z;
}

// Returns eLevelName from position
eLevelName CTheZones::GetLevelFromPosition(CVector const& point)
{
    return ((eLevelName(__cdecl*)(CVector const&))0x572300)(point);
}

// Returns pointer to zone by a point
CZone* CTheZones::FindSmallestZoneForPosition(const CVector& point, bool FindOnlyZonesType0)
{
    return ((CZone * (__cdecl*)(const CVector&, bool)) FUNC_CTheZones__FindSmallestZoneForPosition)(point, FindOnlyZonesType0);
}

// 572400
CZoneExtraInfo* CTheZones::GetZoneInfo(const CVector& point, CZone** outzone)
{
    return ((CZoneExtraInfo * (__cdecl*)(const CVector&, CZone**)) FUNC_CTheZones__GetZoneInfo) (point, outzone);
}

void CTheZones::FillZonesWithGangColours(bool DisableRadarGangColors)
{
    ((void(__cdecl*)(bool)) FUNC_CTheZones__FillZonesWithGangColours) (DisableRadarGangColors);
}

// Returns pointer to zone by index
// 572590
CZone* CTheZones::GetNavigationZone(unsigned short index)
{
    return &CTheZones::NavigationZoneArray[index];
}

// Returns pointer to zone by index
CZone* CTheZones::GetMapZone(unsigned short index)
{
    return &CTheZones::MapZoneArray[index];
}

long double CTheZones::Calc2DDistanceBetween2Zones(CZone* Zone1, CZone* Zone2)
{
    return ((long double(__cdecl*)(CZone*, CZone*)) FUNC_CTheZones__Calc2DDistanceBetween2Zones) (Zone1, Zone2);
}

// Initializes CTheZones
void CTheZones::Init()
{
    ((void(__cdecl*)()) FUNC_CTheZones__Init)();
}

// Unlock the current zone
void CTheZones::SetCurrentZoneAsUnlocked()
{
    ((void(__cdecl*)()) FUNC_CTheZones__SetCurrentZoneAsUnlocked)();
}

// Creates a zone
void CTheZones::CreateZone(const char* name, eZoneType type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, eLevelName island, const char* GXT_key)
{
    ((void(__cdecl*)(const char*, eZoneType, float, float, float, float, float, float, eLevelName island, const char*)) FUNC_CTheZones__CreateZone)
        (name, type, posX1, posY1, posZ1, posX2, posY2, posZ2, island, GXT_key);
}

// Returns 1 if point lies within the specified zonename otherwise return 0
bool CTheZones::FindZone(CVector* point, int zonename_part1, int zonename_part2, eZoneType type)
{
    return ((bool(__cdecl*)(CVector*, int, int, eZoneType)) FUNC_CTheZones__FindZone)(point, zonename_part1, zonename_part2, type);
}

// Returns pointer to zone by index
short CTheZones::FindZoneByLabel(const char* name, eZoneType type)
{
    return ((short(__cdecl*)(const char*, eZoneType)) FUNC_CTheZones__FindZoneByLabel)(name, type);
}

void CTheZones::SetZoneRadarColours(short index, char flag, unsigned char red, unsigned char green, unsigned char blue)
{
    ((void(__cdecl*)(short, char, unsigned char, unsigned char, unsigned char)) FUNC_CTheZones__SetZoneRadarColours) (index, flag, red, green, blue);
}

// Updates CTheZones info
void CTheZones::Update()
{
    ((void(__cdecl*)()) FUNC_CTheZones__Update)();
}

// Save CTheZones info
void CTheZones::Save()
{
    CGenericGameStorage::SaveDataToWorkBuffer(&m_CurrLevel, 4);
    CGenericGameStorage::SaveDataToWorkBuffer(&TotalNumberOfNavigationZones, 2);
    CGenericGameStorage::SaveDataToWorkBuffer(&TotalNumberOfZoneInfos, 2);
    CGenericGameStorage::SaveDataToWorkBuffer(&TotalNumberOfMapZones, 2);

    for (int i = 0; i < TotalNumberOfNavigationZones; i++)
    {
        CGenericGameStorage::SaveDataToWorkBuffer(&NavigationZoneArray[i], 0x20);
    }

    for (int i = 0; i < TotalNumberOfZoneInfos; i++)
    {
        CGenericGameStorage::SaveDataToWorkBuffer(&ZoneInfoArray[i], 0x11);
    }

    for (int i = 0; i < TotalNumberOfMapZones; i++)
    {
        CGenericGameStorage::SaveDataToWorkBuffer(&MapZoneArray[i], 0x20);
    }

    CGenericGameStorage::SaveDataToWorkBuffer(ZonesVisited, 100);
    CGenericGameStorage::SaveDataToWorkBuffer(&ZonesRevealed, 4);
}

// Load CTheZones info
void CTheZones::Load()
{
    Init();
    CGenericGameStorage::LoadDataFromWorkBuffer(&m_CurrLevel, 4);
    CGenericGameStorage::LoadDataFromWorkBuffer(&TotalNumberOfNavigationZones, 2);
    CGenericGameStorage::LoadDataFromWorkBuffer(&TotalNumberOfZoneInfos, 2);
    CGenericGameStorage::LoadDataFromWorkBuffer(&TotalNumberOfMapZones, 2);

    for (int i = 0; i < TotalNumberOfNavigationZones; i++)
    {
        CGenericGameStorage::LoadDataFromWorkBuffer(&NavigationZoneArray[i], 0x20u);
    }

    for (int i = 0; i < TotalNumberOfZoneInfos; i++)
    {
        CGenericGameStorage::LoadDataFromWorkBuffer(&ZoneInfoArray[i], 0x11u);
    }

    for (int i = 0; i < TotalNumberOfMapZones; i++)
    {
        CGenericGameStorage::LoadDataFromWorkBuffer(&MapZoneArray[i], 0x20u);
    }
    CGenericGameStorage::LoadDataFromWorkBuffer(ZonesVisited, 100);
    CGenericGameStorage::LoadDataFromWorkBuffer(&ZonesRevealed, 4u);
}

// dummy function
// 0x572B70
void CTheZones::PostZoneCreation() {
    // NOP
}
