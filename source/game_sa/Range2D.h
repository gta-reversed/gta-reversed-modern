#pragma once

#include "Vector2D.h"

class CRange2D {
public:
    CVector2D m_Min, m_Max;

public:
    CRange2D(CVector2D min, CVector2D max);

    void DebugShowRange(int32);
    CVector2D GetRandomPointInRange();
    bool IsInRange(const CVector2D& point);
};
