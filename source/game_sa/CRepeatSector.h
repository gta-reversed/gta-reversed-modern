/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CPtrListDoubleLink.h"

enum eRepeatSectorList {
    REPEATSECTOR_VEHICLES = 0,
    REPEATSECTOR_PEDS = 1,
    REPEATSECTOR_OBJECTS = 2
};

class  CRepeatSector {
public:
    CPtrListDoubleLink m_lists[3];
};

VALIDATE_SIZE(CRepeatSector, 0xC);