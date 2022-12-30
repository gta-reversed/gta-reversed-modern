/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "FxPlane.h"

class FxSphere_c {
public:
    RwV3d  m_vecCenter;
    float  m_fRadius;
    uint32 m_nNumPlanesPassed;

public:
    static void* operator new(uint32 size, int32 notAligned);
    static void  operator delete(void* data);

    FxSphere_c();

    bool  IsCollision(FxSphere_c* sphere);
    float GetDistToPlane(FxPlane_c* plane);
};

VALIDATE_SIZE(FxSphere_c, 0x14);