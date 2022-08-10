/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

constexpr auto PLANE_TRAIL_BUF_SIZE = 16;

class CPlaneTrail {
public:
    // Shifting buffers, with 2000ms intervals
    // first element being the most recent
    CVector m_Positions[PLANE_TRAIL_BUF_SIZE];
    uint32  m_Timepoints[PLANE_TRAIL_BUF_SIZE];

public:
    static void InjectHooks();

    void Init();
    void Render(float intensity);
    void RegisterPoint(CVector point);
    void Update(CVector pos, const CRGBA& color, uint32 coronaIdx, uint32 timeModifierMs, uint8 afterHour, uint8 beforeHour);
};
VALIDATE_SIZE(CPlaneTrail, 0x100);
