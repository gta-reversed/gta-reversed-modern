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
    constexpr FixedVector(CVector v3d) : x(v3d.x), y(v3d.y), z(v3d.z) {}

    constexpr operator CVector() const { return CVector{ x, y, z }; }
};
