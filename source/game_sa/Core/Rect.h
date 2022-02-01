/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector2D.h"

/* CRect class describes a rectangle.

        A(left;top)_____________________→
        |                               |
        |                               |
        |                               |
        |_________________B(right;bottom)
        ↓
*/

class CRect {
public:
    float left;   // x1
    float bottom; // y1
    float right;  // x2
    float top;    // y2

public:
    static void InjectHooks();

    CRect();
    CRect(float fLeft, float fTop, float fRight, float fBottom);

    bool IsFlipped() const;
    void Restrict(CRect const& restriction);
    void Resize(float resizeX, float resizeY);
    bool IsPointInside(CVector2D const& point) const;
    bool IsPointInside(CVector2D const& point, float tolerance) const;
    void SetFromCenter(float x, float y, float size);
    void GetCenter(float* x, float* y) const;
    void StretchToPoint(float x, float y);

    inline CVector2D GetCenter() const { return CVector2D((right + left) * 0.5F, (top + bottom) * 0.5F); }
};

VALIDATE_SIZE(CRect, 0x10);
