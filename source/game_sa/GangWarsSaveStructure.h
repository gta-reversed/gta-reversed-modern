/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "Vector.h"

class CGangWarsSaveStructure {
public:
    bool bGangWarsActive;
private:
    char _pad1[3];
public:
    uint32 State;
    uint32 TimeStarted;
    uint32 GangWarZoneInfoIndex;
    uint32 GangWarNavigationZoneIndex;
    CVector CoorsOfPlayerAtStartOfWar;
    uint32 Gang1;
    uint32 Gang2;
    uint32 WarFerocity;
    uint32 LastTimeInArea;
    uint32 State2;
    float TimeTillNextAttack;
    CVector PointOfAttack;
    uint32 FightTimer;
    uint32 RadarBlip;
    bool bPlayerIsCloseby;
private:
    char _pad4D[3];
public:
    float TerritoryUnderControlPercentage;
    float Difficulty;

     void Construct();
     void Extract();
};

VALIDATE_SIZE(CGangWarsSaveStructure, 0x58);
