#pragma once

#include "FixedFloat.hpp"
#include "Rect.h"

template<typename T, float CompressValue>
struct FixedRect {
    constexpr FixedRect() = default;

    constexpr FixedRect(CRect rt) :
        left(rt.left),
        top(rt.top),
        right(rt.right),
        bottom(rt.bottom)
    {}

    // NOTE: Notice that args are not retarded like the CRect ctor!
    constexpr FixedRect(T X1_left, T Y1_top, T X2_right, T Y2_bottom) :
        left(X1_left),
        top(Y1_top),
        right(X2_right),
        bottom(Y2_bottom)
    {}

    constexpr operator CRect() const { return CRect{ left, bottom, right, top }; }

    constexpr CVector2D GetXY1() const { return { left, top }; }
    constexpr CVector2D GetXY2() const { return { right, bottom }; }

public: // Public, because in some cases it might be useful to only access 1
    FixedFloat<T, CompressValue> left{}, top{}, right{}, bottom{}; // x1,y1,x2,y2
};
