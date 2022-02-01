/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class CZoneInfo {
public:
    uint8  GangDensity[10];
    uint8  DrugDealerCounter;
    RwRGBA ZoneColor;
    union {
        struct {
            uint8 zonePopulationType : 5;
        };
        uint8 Flags1;
    };
    uint8 Flags2;
};

VALIDATE_SIZE(CZoneInfo, 0x11);
