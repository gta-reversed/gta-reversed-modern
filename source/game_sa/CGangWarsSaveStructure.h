/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class  CGangWarsSaveStructure {
public:
    bool bGangWarsActive;
private:
    char _pad1[3];
public:
    unsigned int State;
    unsigned int TimeStarted;
    unsigned int GangWarZoneInfoIndex;
    unsigned int GangWarNavigationZoneIndex;
    CVector CoorsOfPlayerAtStartOfWar;
    unsigned int Gang1;
    unsigned int Gang2;
    unsigned int WarFerocity;
    unsigned int LastTimeInArea;
    unsigned int State2;
    float TimeTillNextAttack;
    CVector PointOfAttack;
    unsigned int FightTimer;
    unsigned int RadarBlip;
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

//#include "meta/meta.CGangWarsSaveStructure.h"
