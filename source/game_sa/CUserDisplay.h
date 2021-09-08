/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPlaceName.h"
#include "COnscreenTimer.h"
#include "CCurrentVehicle.h"

class CUserDisplay {
public:
    static CPlaceName&      PlaceName;
    static COnscreenTimer&  OnscnTimer;
    static CCurrentVehicle& CurrentVehicle;

public:
    static void InjectHooks();

    static void Init();
    static void Process();
};
