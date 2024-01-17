/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <Base.h>
#include <RenderWare.h>
#include <extensions/utility.hpp>

class CZoneInfo {
public:
    uint8  GangDensity[10]{};
    uint8  DrugDealerCounter{}; /// Counter updated in `UpdateDealerStrengths`. Only used durning gang wars. Max value is the size of the array in the beforementioned function (15 currently)
    CRGBA  ZoneColor{};
    struct {
        uint8 zonePopulationType : 5{ 5 };
        uint8 radarMode : 2{};
        uint8 noCops : 1{};
        uint8 zonePopulationRace : 4{0b1111}; // Bitfield for race allowed in the zone. See `ePedRace`. Default value (RACE_DEFAULT) isn't counted. See `IsPedAppropriateForCurrentZone` for usage example.
    };

    auto GetSumOfGangDensity() const {
        return notsa::accumulate(
            GangDensity,  
            (size_t)(0u) // Making sure no overflow occurs (because uint8 is used instead of casting to a wider type)
        );
    }
};
VALIDATE_SIZE(CZoneInfo, 0x11);
