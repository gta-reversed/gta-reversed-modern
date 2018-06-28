/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "rw/rwplcore.h"     // for RwRGBA stuct

enum eZoneType {
	ZONE_TYPE_NAVI = 0,		// controls text s
	ZONE_TYPE_MAP = 3
};

enum eLevelName {
	LEVEL_NAME_COUNTRY_SIDE,
	LEVEL_NAME_LOS_SANTOS,
	LEVEL_NAME_SAN_FIERRO,
	LEVEL_NAME_LAS_VENTURAS
};

struct CZoneExtraInfo {
	char m_nGangDensity[10];
	char m_nDealerDensity;
	RwRGBA ZoneColor;
	char m_nFlags;
	char m_nPopulationRace;
};

class CZone {
public:
    unsigned int  m_nLabel[2];
	char          m_szTextKey[8];
	short         m_fX1;
	short         m_fY1;
	short         m_fZ1;
	short         m_fX2;
	short         m_fY2;
	short         m_fZ2;
	short         m_nZoneExtraIndexInfo;
	unsigned char m_nType; // see eZoneType
    unsigned char m_nLevel; // see eLevelName

	// Returns pointer to GXT name string.
	const char* GetTranslatedName();
};

VALIDATE_SIZE(CZone, 0x20);
