#include "StdInc.h"

#include "GangWarsSaveStructure.h"

// 0x5D2620
void CGangWarsSaveStructure::Construct() {
    assert(0);
    bGangWarsActive = CGangWars::bGangWarsActive;
    State = CGangWars::State;
    TimeStarted = CGangWars::TimeStarted;
    GangWarZoneInfoIndex = -1;

    if (CGangWars::pZoneInfoToFightOver) {
        GangWarZoneInfoIndex = std::find(CTheZones::ZoneInfoArray,
            CTheZones::ZoneInfoArray + CTheZones::TotalNumberOfZoneInfos, *CGangWars::pZoneInfoToFightOver)
            - CTheZones::ZoneInfoArray;

        GangWarNavigationZoneIndex = std::find(CTheZones::NavigationZoneArray,
            CTheZones::NavigationZoneArray + CTheZones::TotalNumberOfNavigationZones, *CGangWars::pZoneToFightOver)
            - CTheZones::NavigationZoneArray;
    }

    CoorsOfPlayerAtStartOfWar = CGangWars::CoorsOfPlayerAtStartOfWar;
    Gang1 = CGangWars::Gang1;
    Gang2 = CGangWars::Gang2;
    WarFerocity = CGangWars::WarFerocity;
    LastTimeInArea = CGangWars::LastTimeInArea;
    State2 = CGangWars::State2;
    TimeTillNextAttack = CGangWars::TimeTillNextAttack;
    PointOfAttack = CGangWars::PointOfAttack;
    FightTimer = CGangWars::FightTimer;
    RadarBlip = CGangWars::RadarBlip;
    bPlayerIsCloseby = CGangWars::bPlayerIsCloseby;
    TerritoryUnderControlPercentage = CGangWars::TerritoryUnderControlPercentage;
}

// 0x5D2740
void CGangWarsSaveStructure::Extract() {
    assert(0);
}
