/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "rw/rwplcore.h" // for RwRGBA struct
#include "eLevelName.h"

enum eZoneType : uint8 {
    ZONE_TYPE_NAVI = 0, // controls text s
    ZONE_TYPE_MAP = 3
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

    // NOTSA
    CRect GetRect() const {
        return {(float)m_fX1, (float)m_fY1, (float)m_fX2, (float)m_fY2};
    }
};

VALIDATE_SIZE(CZone, 0x20);
