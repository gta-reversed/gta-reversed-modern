#pragma once
#include "FixedFloat.hpp"
#include "Vector.h"

template<typename T, float CompressValue>
class FixedVector {
    FixedFloat<T, CompressValue> x{}, y{}, z{};

public:
    constexpr FixedVector() = default;
    constexpr FixedVector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    constexpr FixedVector(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

    constexpr auto operator=(const CVector& rhs) {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    constexpr operator CVector() { return CVector{ x, y, z }; }
};
