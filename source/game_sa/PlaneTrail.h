/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

#define PLANE_TRAIL_BUFSZ 16

class CPlaneTrail {
public:
    // Shifting buffers, with 2000ms intervals
    // first element being the most recent
    CVector m_positions[PLANE_TRAIL_BUFSZ];
    uint32  m_timepoints[PLANE_TRAIL_BUFSZ];

public:
    static void InjectHooks();

    void Init();
    void Render(float intensity);
    void RegisterPoint(CVector point);
};

VALIDATE_SIZE(CPlaneTrail, 0x100);
