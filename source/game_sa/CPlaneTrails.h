/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPlaneTrail.h"

#define NUM_PLANE_TRAILS 3

class CPlaneTrails {
public:
    static CPlaneTrail (&aArray)[NUM_PLANE_TRAILS];

public:
    static void InjectHooks();

public:
    static void Init();
    static void Render();
    static void RegisterPoint(CVector point, uint32 trailIndex);
    static void Update();
};
