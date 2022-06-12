#pragma once

#include "Vector.h"

class CRange3D {
public:
    CVector m_Min, m_Max;

public:
    CRange3D(CVector min, CVector max);

    void DebugShowRange(int32);
    CVector GetRandomPointInRange();
    bool IsInRange(CVector point);
};
