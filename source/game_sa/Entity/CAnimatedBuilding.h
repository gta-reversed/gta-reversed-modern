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
public:
    CAnimatedBuilding() : CBuilding() {}

public:
    static void InjectHooks();

    void ProcessControl() override;
    void ProcessCollision() override;
    void PreRender() override;

private:
    void ProcessControl_Reversed();
    void ProcessCollision_Reversed();
    void PreRender_Reversed();
};

VALIDATE_SIZE(CAnimatedBuilding, 0x38);
