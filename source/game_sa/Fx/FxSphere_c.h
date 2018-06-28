/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "FxPlane_c.h"

class FxSphere_c {
public:
    RwV3d m_vecCenter;
    float m_fRadius;
    unsigned int m_nNumPlanesPassed;

    FxSphere_c();
    static void* operator new(unsigned int size, int notAligned);
    static void operator delete(void* data);
    bool IsCollision(FxSphere_c* sphere);
    float GetDistToPlane(FxPlane_c* plane);
};

VALIDATE_SIZE(FxSphere_c, 0x14);