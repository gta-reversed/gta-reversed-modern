/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h" // !!!

#include "RenderWare.h"
#include <numeric>

// Hacky solution so we need to not modify `RwV3d`
constexpr RwV3d ConstructRwV3d(float x, float y, float z) {
    RwV3d v{};
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

class CVector : public RwV3d {
public:

    constexpr CVector() :
        RwV3d(ConstructRwV3d(0.0f, 0.0f, 0.0f))
    {
    }

    constexpr CVector(float X, float Y, float Z) :
        RwV3d(ConstructRwV3d(X, Y, Z))
    {
    }

    constexpr CVector(RwV3d rwVec) :
        RwV3d(rwVec)
    {
    }

public:
    static void InjectHooks();

    static CVector Random(float min, float max);

    // Returns length of vector
    float Magnitude() const;

    // Returns length of 2d vector
    float Magnitude2D();

    // Normalises a vector
    void Normalise();

    // Normalises a vector and returns length (in-place)
    float NormaliseAndMag();

    // Performs cross calculation
    void Cross(const CVector& left, const CVector &right);
 
    // Adds left + right and stores result
    void Sum(const CVector& left, const CVector &right);

    // Subtracts left - right and stores result
    void Difference(const CVector& left, const CVector &right);

    void operator=(const RwV3d& right)
    {
        x = right.x; y = right.y; z = right.z;
    }

    void operator=(const CVector& right);
    void operator+=(const CVector& right);
    void operator-=(const CVector& right);
    void operator*=(const CVector& right);
    void operator *= (float multiplier);
    void operator /= (float divisor);

    // matrix * vector multiplication
    void FromMultiply(class CMatrix  const& matrix, CVector const& vector);
    void FromMultiply3x3(class CMatrix  const& matrix, CVector const& vector);

    inline void Set(float X, float Y, float Z) {
        x = X; y = Y; z = Z;
    }

    inline RwV3d ToRwV3d() {
        return{ x, y, z };
    }

    inline void FromRwV3d(RwV3d &rwvec) {
        x = rwvec.x; y = rwvec.y; z = rwvec.z;
    }

    inline float SquaredMagnitude() const
    {
        return x*x + y*y + z*z;
    }

    inline float SquaredMagnitude2D() 
    {
        return x * x + y * y;
    }

    inline bool IsZero() const
    {
        return x == 0.0F && y == 0.0F && z == 0.0F;
    }

    // Calculate the average position
    static CVector Average(const CVector* begin, const CVector* end);

    static CVector AverageN(const CVector* begin, size_t n) {
        return Average(begin, begin + n);
    }
};

inline CVector operator-(const CVector& vecOne, const CVector& vecTwo) {
    return CVector(vecOne.x - vecTwo.x, vecOne.y - vecTwo.y, vecOne.z - vecTwo.z);
}

inline CVector operator+(const CVector& vecOne, const CVector& vecTwo) {
    return CVector(vecOne.x + vecTwo.x, vecOne.y + vecTwo.y, vecOne.z + vecTwo.z);
}

inline CVector operator*(const CVector& vecOne, const CVector& vecTwo) {
    return CVector(vecOne.x * vecTwo.x, vecOne.y * vecTwo.y, vecOne.z * vecTwo.z);

}
inline bool operator!=(const CVector& vecOne, const CVector& vecTwo) {
    return vecOne.x != vecTwo.x || vecOne.y != vecTwo.y || vecOne.z != vecTwo.z;
}

inline bool operator!=(const CVector& vec, float notEqualTo) {
    return vec.x != notEqualTo || vec.y != notEqualTo || vec.z != notEqualTo;
}

inline bool operator==(const CVector& vec, float equalTo) {
    return vec.x == equalTo && vec.y == equalTo && vec.z == equalTo;
}

inline bool operator==(const CVector& vecLeft, const CVector& vecRight)
{
    return vecLeft.x == vecRight.x && vecLeft.y == vecRight.y && vecLeft.z == vecRight.z;
}

inline CVector operator*(const CVector& vec, float multiplier) {
    return CVector(vec.x * multiplier, vec.y * multiplier, vec.z * multiplier);
}

inline CVector operator/(const CVector& vec, float dividend) {
    return CVector(vec.x / dividend, vec.y / dividend, vec.z / dividend);
}

inline CVector operator*(float multiplier, const CVector& vec) {
    return CVector(vec.x * multiplier, vec.y * multiplier, vec.z * multiplier);
}

inline CVector operator-(const CVector& vec) {
    return CVector(-vec.x, -vec.y, -vec.z);
}

inline float DistanceBetweenPoints(const CVector &pointOne, const CVector &pointTwo) {
    return (pointTwo - pointOne).Magnitude();
}
inline float DistanceBetweenPointsSquared(const CVector& pointOne, const CVector& pointTwo) {
    return (pointTwo - pointOne).SquaredMagnitude();
}

inline CVector Lerp(const CVector& vecOne, const CVector& vecTwo, float fProgress) {
    return vecOne * (1.0F - fProgress) + vecTwo * fProgress;
}

inline CVector Pow(const CVector& vec, float fPow) {
    return CVector(pow(vec.x, fPow), pow(vec.y, fPow), pow(vec.z, fPow));
}

CVector* CrossProduct(CVector* out, CVector* a, CVector* b);
float DotProduct(CVector* v1, CVector* v2);
CVector CrossProduct(const CVector& a, const CVector& b);
float DotProduct(const CVector& v1, const CVector& v2);
float DotProduct2D(const CVector& v1, const CVector& v2);
static CVector Normalized(CVector v) { v.Normalise(); return v; }

VALIDATE_SIZE(CVector, 0xC);
