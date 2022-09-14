/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CPlaneTrail {
    constexpr static inline auto PLANE_TRAIL_BUF_SIZE = 16u;
public:

    /// Shifting buffers, with 2000ms intervals first element being the most recent

    CVector m_Positions[PLANE_TRAIL_BUF_SIZE];

    /*!
    * Filled with 0 by default. If `0` it means that this point shouldn't be used
    * either because it has expired(30'000 ms) or because it was never inited
    */
    uint32  m_Timepoints[PLANE_TRAIL_BUF_SIZE];

public:
    static void InjectHooks();

    void Init();
    void Render(float intensity);
    void RegisterPoint(CVector point);
    void Update(CVector pos, const CRGBA& color, uint32 coronaIdx, uint32 timeModifierMs, uint8 afterHour, uint8 beforeHour);

    /// @notsa
    bool IsPointInUse(size_t pt);
};
VALIDATE_SIZE(CPlaneTrail, 0x100);
