/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPlaceName;
#include "OnscreenTimer.h"
class CCurrentVehicle;

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
