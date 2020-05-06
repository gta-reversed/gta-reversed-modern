/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "RenderWare.h"

class CZoneInfo
{
public:
    std::uint8_t GangDensity[10];
    std::uint8_t DrugDealerCounter;
	RwRGBA ZoneColor;
    union {
        struct {
            std::uint8_t zonePopulationType : 5;
        };
        std::uint8_t Flags1;
    };
	std::uint8_t Flags2;
};

VALIDATE_SIZE(CZoneInfo, 0x11);
