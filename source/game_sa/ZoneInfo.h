/*
    Plugin-SDK file
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
    CRGBA  ZoneColor;
    union {
        struct {
            uint8 zonePopulationType : 5;
            uint8 radarMode : 2;
            uint8 noCops : 1;
            uint8 zonePopulationRace : 4; // bitfield for races, see `ePedRace`. Default value (RACE_DEFAULT) isn't counted. See `IsPedAppropriateForCurrentZone` for usage example.
        };
        struct {
            uint8 Flags1, Flags2;
        };
    };
};

VALIDATE_SIZE(CZoneInfo, 0x11);
