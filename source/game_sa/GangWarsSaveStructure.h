/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CGangWarsSaveStructure {
public:
    bool             bGangWarsActive;
    eGangWarState    State;
    uint32           TimeStarted;
    uint32           GangWarZoneInfoIndex;
    uint32           GangWarNavigationZoneIndex;
    CVector          CoorsOfPlayerAtStartOfWar;
    uint32           Gang1;
    uint32           Gang2;
    uint32           WarFerocity;
    uint32           LastTimeInArea;
    eGangAttackState State2;
    float            TimeTillNextAttack;
    CVector          PointOfAttack;
    uint32           FightTimer;
    int32            RadarBlip;
    bool             bPlayerIsCloseby;
    float            TerritoryUnderControlPercentage;
    float            Difficulty;

public:
     void Construct();
     void Extract() const;
};
VALIDATE_SIZE(CGangWarsSaveStructure, 0x58);
