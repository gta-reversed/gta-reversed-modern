/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "RenderWare.h"

class CVector {
public:
    float x, y, z;

    CVector();
    CVector(float X, float Y, float Z);

    // Returns length of vector
    float Magnitude();

    // Returns length of 2d vector
    float Magnitude2D();

    // Normalises a vector
    void Normalise();

    // Normalises a vector and returns length
    float NormaliseAndMag();

    // Performs cross calculation
    void Cross(const CVector& left, const CVector &right);

    float Dot();
 
    // Adds left + right and stores result
    void Sum(const CVector& left, const CVector &right);

    // Subtracts left - right and stores result
    void Difference(const CVector& left, const CVector &right);

    void operator=(const CVector& right);
    void operator+=(const CVector& right);
    void operator-=(const CVector& right);
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

    inline float SquaredMagnitude()
    {
        return x*x + y*y + z*z;
    }
};

inline CVector operator-(const CVector& vecOne, const CVector& vecTwo) {
    return CVector(vecOne.x - vecTwo.x, vecOne.y - vecTwo.y, vecOne.z - vecTwo.z);
}

inline CVector operator+(const CVector& vecOne, const CVector& vecTwo) {
    return CVector(vecOne.x + vecTwo.x, vecOne.y + vecTwo.y, vecOne.z + vecTwo.z);
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

inline float DistanceBetweenPoints(const CVector &pointOne, const CVector &pointTwo) {
    CVector diff = pointTwo - pointOne;
    return diff.Magnitude();
}

CVector* CrossProduct(CVector* out, CVector* a, CVector* b);
float DotProduct(CVector* v1, CVector* v2);
VALIDATE_SIZE(CVector, 0xC);
