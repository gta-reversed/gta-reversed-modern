#pragma once
#include "FixedFloat.hpp"
#include "Vector.h"

template<typename T, float CompressValue>
struct FixedVector {
    constexpr FixedVector() = default;
    constexpr FixedVector(float X, float Y, float Z) : x(X), y(Y), z(Z) {}
    constexpr FixedVector(CVector v3d) : x(v3d.x), y(v3d.y), z(v3d.z) {}
    explicit constexpr FixedVector(T X, T Y, T Z) : x(X), y(Y), z(Z) {}

    constexpr operator CVector() const { return CVector{ x, y, z }; }

public: // Public, because in some cases it might be useful to only access 1
    FixedFloat<T, CompressValue> x{}, y{}, z{};
};
