/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CBuilding.h"

class CAnimatedBuilding : public CBuilding {
protected:
    CAnimatedBuilding(plugin::dummy_func_t) : CBuilding(plugin::dummy) {}
public:
    CAnimatedBuilding();
};

VALIDATE_SIZE(CAnimatedBuilding, 0x38);