/*
    Plugin-SDK file
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
    float left   = 1000000.0F;  // x1
    float bottom = -1000000.0F; // y2
    float right  = -1000000.0F; // x2
    float top    = 1000000.0F;  // y1

public:
    static void InjectHooks();

    constexpr CRect() = default;
    constexpr CRect(float fLeft, float fTop, float fRight, float fBottom) :
        left{ fLeft },
        top{ fTop },
        right{ fRight },
        bottom{ fBottom }
    {
        assert(!IsFlipped());
    }

    // From center and size
    constexpr CRect(const CVector2D& center, float size) :
        left{ center.x - size, },
        top{ center.y - size, },
        right{ center.x + size, },
        bottom{ center.y + size, }
    {
        assert(!IsFlipped());
    }

    constexpr bool IsFlipped() const { return left > right || top > bottom; }
    void Restrict(const CRect& restriction);
    void Resize(float resizeX, float resizeY);
    bool IsPointInside(const CVector2D& point) const;
    bool IsPointInside(const CVector2D& point, float tolerance) const;
    void SetFromCenter(float x, float y, float size);
    void GetCenter(float* x, float* y) const;
    void StretchToPoint(float x, float y);

    inline CVector2D GetCenter() const { return CVector2D((right + left) * 0.5F, (top + bottom) * 0.5F); }
};

VALIDATE_SIZE(CRect, 0x10);
