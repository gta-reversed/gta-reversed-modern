#include "StdInc.h"

/*
	Plugin-SDK (Grand Theft Auto San Andreas) source file
	Authors: GTA Community. See more here
	https://github.com/DK22Pac/plugin-sdk
	Do not delete this comment block. Respect others' work!
*/

#define VAR_CTheZones__m_CurrLevel 0xBA6718
#define VAR_CTheZones__ExploredTerritoriesArray 0xBA3730
#define VAR_CTheZones__TotalNumberExploredTerritories 0xBA372C
#define VAR_CTheZones__TotalNumberOfInfoZones 0x572A5A
#define VAR_CTheZones__ZoneInfoArray 0xBA3798
#define VAR_CTheZones__TotalNumberOfMapZones 0xBA3794
#define VAR_CTheZones__MapZoneArray 0xBA1908

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

void CTheZones::InjectHooks()
{
	HookInstall(FUNC_CTheZones__ResetZonesRevealed, &CTheZones::ResetZonesRevealed, 7);
	HookInstall(FUNC_CTheZones__GetCurrentZoneLockedOrUnlocked, &CTheZones::GetCurrentZoneLockedOrUnlocked, 7);
}

// Variables
eLevelName& CTheZones::m_CurrLevel = *(eLevelName*)VAR_CTheZones__m_CurrLevel;

char* CTheZones::ExploredTerritoriesArray = (char*)VAR_CTheZones__ExploredTerritoriesArray;
int& CTheZones::TotalNumberExploredTerritories = *(int*)VAR_CTheZones__TotalNumberExploredTerritories;

short& CTheZones::TotalNumberOfMapZones = *(short*)VAR_CTheZones__TotalNumberOfInfoZones;
CZone* CTheZones::ZoneInfoArray = (CZone*)VAR_CTheZones__ZoneInfoArray;

short& CTheZones::TotalNumberOfInfoZones = *(short*)VAR_CTheZones__TotalNumberOfMapZones;
CZone* CTheZones::MapZoneArray = (CZone*)VAR_CTheZones__MapZoneArray;

// Functions
void CTheZones::InitZonesPopulationSettings()
{
	((void(__cdecl*)()) FUNC_CTheZones__InitZonesPopulationSettings) ();
}

void CTheZones::ResetZonesRevealed()
{
#ifdef USE_DEFAULT_FUNCTIONS
	((void(__cdecl*)()) FUNC_CTheZones__ResetZonesRevealed) ();
#else
	memset(CTheZones::ExploredTerritoriesArray, 0, sizeof(CTheZones::ExploredTerritoriesArray));
	CTheZones::TotalNumberExploredTerritories = 0;
#endif
}

bool CTheZones::GetCurrentZoneLockedOrUnlocked(float posx, float posy)
{
#ifdef USE_DEFAULT_FUNCTIONS
	return ((bool(__cdecl*)(float, float)) FUNC_CTheZones__GetCurrentZoneLockedOrUnlocked) (posx, posy);
#else
	return CTheZones::ExploredTerritoriesArray[(unsigned int)(10 * ((posx + 3000.0) * 0.0016666667) - ((posy + 3000.0) * 0.0016666667) + 9)] != 0;
#endif
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
	return ((bool(__cdecl*)(CVector const*, CZone*)) FUNC_CTheZones__PointLiesWithinZone)(pPoint, pZone);
}

// Returns eLevelName from position
eLevelName CTheZones::GetLevelFromPosition(CVector const* pPoint)
{
	return ((eLevelName(__cdecl*)(CVector const*)) FUNC_CTheZones__GetLevelFromPosition)(pPoint);
}

// Returns pointer to zone by a point
CZone* CTheZones::FindSmallestZoneForPosition(const CVector& point, bool FindOnlyZonesType0)
{
	return ((CZone * (__cdecl*)(const CVector&, bool)) FUNC_CTheZones__FindSmallestZoneForPosition)(point, FindOnlyZonesType0);
}

CZoneExtraInfo* CTheZones::GetZoneInfo(CVector* point, CZone** outzone)
{
	return ((CZoneExtraInfo * (__cdecl*)(CVector*, CZone**)) FUNC_CTheZones__GetZoneInfo) (point, outzone);
}

void CTheZones::FillZonesWithGangColours(bool DisableRadarGangColors)
{
	((void(__cdecl*)(bool)) FUNC_CTheZones__FillZonesWithGangColours) (DisableRadarGangColors);
}

// Returns pointer to zone by index
CZone* CTheZones::GetInfoZone(short index)
{
	return ((CZone * (__cdecl*)(short)) FUNC_CTheZones__GetInfoZone)(index);
}

// Returns pointer to zone by index
CZone* CTheZones::GetMapZone(short index)
{
	return ((CZone * (__cdecl*)(short)) FUNC_CTheZones__GetMapZone)(index);
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
	((void(__cdecl*)()) FUNC_CTheZones__Save) ();
}

// Load CTheZones info
void CTheZones::Load()
{
	((void(__cdecl*)()) FUNC_CTheZones__Load) ();
}