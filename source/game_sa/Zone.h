/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "rw/rwplcore.h" // for RwRGBA struct

enum eZoneType : uint8 {
    ZONE_TYPE_NAVI = 0, // controls text s
    ZONE_TYPE_MAP = 3
};

enum eLevelName : uint8 {
    LEVEL_NAME_COUNTRY_SIDE,
    LEVEL_NAME_LOS_SANTOS,
    LEVEL_NAME_SAN_FIERRO,
    LEVEL_NAME_LAS_VENTURAS
};

struct CZoneExtraInfo {
    char   m_nGangDensity[10];
    char   m_nDealerDensity;
    RwRGBA ZoneColor;
    char   m_nFlags;
    char   m_nPopulationRace;
};

class CZone {
public:
    uint32     m_nLabel[2];
    char       m_szTextKey[8];
    int16      m_fX1;
    int16      m_fY1;
    int16      m_fZ1;
    int16      m_fX2;
    int16      m_fY2;
    int16      m_fZ2;
    int16      m_nZoneExtraIndexInfo;
    eZoneType  m_nType;
    eLevelName m_nLevel;

    const char* GetTranslatedName() const;
};

VALIDATE_SIZE(CZone, 0x20);
