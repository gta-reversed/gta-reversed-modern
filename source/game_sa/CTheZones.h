/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CVector.h"
#include "CZone.h"


class  CTheZones
{
public:
	// Variables

	static eLevelName& m_CurrLevel;	
	
	// Explored teritories

	// Count: 100
	static char* ZonesVisited;
	// Number of explored territories
	static int& ZonesRevealed;

	// Info zones
	static short& TotalNumberOfNavigationZones;
	// Count: 380
	static CZone* NavigationZoneArray;

	// Map zones
	static short& TotalNumberOfMapZones;
	// Count: 39
	static CZone* MapZoneArray;

	static short& TotalNumberOfZoneInfos;

	static CZoneInfo* ZoneInfoArray;

	// Functions
	
	static void InjectHooks();

	static void InitZonesPopulationSettings();
	
	static void ResetZonesRevealed();
		
	static void AssignZoneInfoForThisZone(short index);
	
	static bool ZoneIsEntirelyContainedWithinOtherZone(CZone* pZone1, CZone* pZone2);
	
	static bool GetCurrentZoneLockedOrUnlocked(float posx, float posy);
	
	// Returns true if point lies within zone
	static bool PointLiesWithinZone(CVector const* pPoint, CZone * pZone);
	
	// Returns eLevelName from position
	static eLevelName GetLevelFromPosition(CVector const& point);
	
	// Returns pointer to zone by a point
	static CZone* FindSmallestZoneForPosition(const CVector& point, bool FindOnlyZonesType0);
	
	static CZoneExtraInfo* GetZoneInfo(const CVector& point, CZone **outzone);
	
	static void FillZonesWithGangColours(bool DisableRadarGangColors);
	
	// Returns pointer to zone by index
	static CZone* GetNavigationZone(unsigned short index);
	
	// Returns pointer to zone by index
	static CZone* GetMapZone(unsigned short index);
	
	static long double Calc2DDistanceBetween2Zones(CZone *Zone1, CZone *Zone2);
	
	// Initializes CTheZones
	static void Init();
	
	// Unlock the current zone
	static void SetCurrentZoneAsUnlocked();
	
	// Creates a zone
	static void CreateZone(const char *name, eZoneType type, float posX1, float posY1, float posZ1, float posX2, float posY2, float posZ2, eLevelName island, const char *GXT_key);

	// Returns 1 if point within the specified zonename otherwise return 0
	static bool FindZone(CVector* point, int zonename_part1 ,int zonename_part2,eZoneType type);
	
	// Returns pointer to zone by index
	static short FindZoneByLabel(const char* name, eZoneType type);
	
	static void SetZoneRadarColours(short index, char flag, unsigned char red, unsigned char green, unsigned char blue);
	
	// Updates CTheZones info
	static void Update();
	
	// Save CTheZones info
	static void Save();

	// Load CTheZones info
	static void Load();

};
