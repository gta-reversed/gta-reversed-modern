/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <span>

#include "RenderWare.h"

class CVector;

class CVector2D : public RwV2d {
public:
    constexpr CVector2D() = default;
    constexpr CVector2D(float XY) : RwV2d{XY, XY} {}
    constexpr CVector2D(float X, float Y) : RwV2d{ X, Y } {}
    constexpr CVector2D(const RwV2d& vec2d)     { x = vec2d.x; y = vec2d.y; }
    constexpr CVector2D(const CVector2D& vec2d) { x = vec2d.x; y = vec2d.y; }

    CVector2D(const CVector& vec3d);

    static void InjectHooks();

    /// Normalize this vector in-place
    void  Normalise();

    /// Get a normalized copy of this vector
    auto Normalized() const {
        CVector2D cpy = *this;
        cpy.Normalise();
        return cpy;
    }

    [[nodiscard]] constexpr inline float SquaredMagnitude() const {
        return x * x + y * y;
    }

    // Returns length of vector
    [[nodiscard]] inline float Magnitude() const {
        return std::sqrt(x * x + y * y);
    }

    [[nodiscard]] inline bool IsZero() const {
        return x == 0.0F && y == 0.0F;
    }

    CVector2D& operator=(const CVector2D& right) {
        x = right.x;
        y = right.y;
        return *this;
    }

    inline void Sum(CVector2D& a, CVector2D& b) {
        x = a.x + b.x;
        y = a.y + b.y;
    }

    inline void Difference(CVector2D& a, CVector2D& b) {
        x = a.x - b.x;
        y = a.y - b.y;
    }

    inline void operator+=(const CVector2D& right) {
        x += right.x;
        y += right.y;
    }

    inline void operator-=(const CVector2D& right) {
        x -= right.x;
        y -= right.y;
    }

    inline void operator*=(float multiplier) {
        x *= multiplier;
        y *= multiplier;
    }

    inline void operator/=(float divisor) {
        x /= divisor;
        y /= divisor;
    }

    inline void Set(float X, float Y) {
        x = X;
        y = Y;
    }
     
    [[nodiscard]] float Heading() const {
        return std::atan2(-x, y);
    }


    auto GetComponents() const {
        return std::span{ reinterpret_cast<const float*>(this), 2 };
    }

    constexpr friend CVector2D operator*(const CVector2D& vec, float multiplier) {
        return { vec.x * multiplier, vec.y * multiplier };
    }

    /// Calculate the dot product with another vector
    float Dot(const CVector2D& lhs) const {
        return x * lhs.x + y * lhs.y;
    }

    //! Get a copy of `*this` vector projected onto `projectOnTo` (which is assumed to be unit length)
    CVector2D ProjectOnToNormal(const CVector2D& projectOnTo) const {
        return projectOnTo * Dot(projectOnTo);
    }

    //! Wrapper around `CGeneral::GetNodeHeadingFromVector`
    uint32 NodeHeading() const;

    //! Get a vector with the same magnitude as `*this` but rotated by `radians` (Interval: [0, 2PI])
    CVector2D RotatedBy(float radians) const;

    //! Get vector perpendicular to `*this` on the right side (Same direction `*this` rotated by -90)
    //! Also see `GetPerpLeft` and `RotatedBy`
    //! (This sometimes is also called a 2D cross product https://stackoverflow.com/questions/243945 )
    CVector2D GetPerpRight() const;

    //! Get vector perpendicular to `*this` on the left side (Same direction `*this` rotated by 90)
    //! Also see `GetPerpRight` and `RotatedBy`
    CVector2D GetPerpLeft() const;
};

constexpr inline CVector2D operator-(const CVector2D& vecOne, const CVector2D& vecTwo) {
    return { vecOne.x - vecTwo.x, vecOne.y - vecTwo.y };
}

constexpr inline CVector2D operator-(const CVector2D& vecOne) {
    return { -vecOne.x, -vecOne.y };
}

constexpr inline CVector2D operator+(const CVector2D& vecOne, const CVector2D& vecTwo) {
    return { vecOne.x + vecTwo.x, vecOne.y + vecTwo.y };
}

constexpr inline CVector2D operator*(const CVector2D& vecOne, const CVector2D& vecTwo) {
    return { vecOne.x * vecTwo.x, vecOne.y * vecTwo.y };
}

constexpr inline CVector2D operator/(const CVector2D& vecOne, const CVector2D& vecTwo) {
    return { vecOne.x / vecTwo.x, vecOne.y / vecTwo.y };
}

constexpr inline CVector2D operator/(const CVector2D& vec, float dividend) {
    return { vec.x / dividend, vec.y / dividend };
}

constexpr inline CVector2D operator*(float multiplier, const CVector2D& vec) {
    return { vec.x * multiplier, vec.y * multiplier };
}

constexpr inline bool operator!=(const CVector2D& vecOne, const CVector2D& vecTwo) {
    return vecOne.x != vecTwo.x || vecOne.y != vecTwo.y;
}

constexpr inline bool operator!=(const CVector2D& vec, float notEqualTo) {
    return vec.x != notEqualTo || vec.y != notEqualTo;
}

constexpr inline bool operator==(const CVector2D& vec, float equalTo) {
    return vec.x == equalTo && vec.y == equalTo;
}

constexpr inline bool operator==(const CVector2D& vecLeft, const CVector2D& vecRight) {
    return vecLeft.x == vecRight.x && vecLeft.y == vecRight.y;
}

inline float DistanceBetweenPoints2D(const CVector2D& pointOne, const CVector2D& pointTwo) {
    return (pointTwo - pointOne).Magnitude();
}

constexpr inline float DistanceBetweenPointsSquared2D(const CVector2D& pointOne, const CVector2D& pointTwo) {
    return (pointTwo - pointOne).SquaredMagnitude();
}

constexpr inline float DotProduct2D(const CVector2D& v1, const CVector2D& v2) {
    return v1.y * v2.y + v1.x * v2.x;
}

constexpr static bool IsPointWithinBounds2D(CVector2D min, CVector2D max, CVector2D point) {
    return (point.x >= min.x && point.x <= max.x) &&
           (point.y >= min.y && point.y <= max.y);
}

constexpr static bool IsPointInRectangle2D(CVector2D rectTopLeft, CVector2D rectSize, CVector2D point) {
    return IsPointWithinBounds2D(rectTopLeft + rectSize, rectTopLeft, point);
}

static CVector2D Normalized2D(CVector2D v) { v.Normalise(); return v; }

static auto abs(const CVector2D& v2d) {
    return CVector2D{ std::abs(v2d.x), std::abs(v2d.y) };
}
