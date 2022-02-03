/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"
#include "Vector.h"

class CQuaternion {
public:
    CVector imag;
    float   real;

public:
    static void InjectHooks();

    CQuaternion();

    // Quat to matrix
    void Get(RwMatrix* out);

    // Quat to euler angles
    void Get(float *x, float *y, float *z);

    // Quat to axis & angle
    void Get(RwV3d *axis, float *angle);

    // Stores result of quat multiplication
    void Multiply(const CQuaternion& a, const CQuaternion& b);

    // Spherical linear interpolation
    void Slerp(const CQuaternion& from, const CQuaternion& to, float halftheta, float sintheta_inv, float t);

    // Quat from matrix
    void Set(RwMatrix  const& m);

    // Quat from euler angles
    void Set(float x, float y, float z);

    // Quat from axis & angle
    void Set(RwV3d *axis, float angle);

    // Spherical linear interpolation
    void Slerp(const CQuaternion& from, const CQuaternion& to, float t);

    // Conjugate of a quat
    void Conjugate();

    // Squared length of a quat
    float GetLengthSquared();

    // Add right to the quat
    void operator+=(const CQuaternion& right);

    // Substract right from the quat
    void operator-=(const CQuaternion& right);

    // Assigns value from other quat
    void operator=(const CQuaternion& right);

    // Multiplies quat by a floating point value
    void operator*=(float multiplier);

    // Multiplies quat by a floating point value
    void Scale(float multiplier);

    // Copies value from other quat
    void Copy(const CQuaternion& from);

    // Gets a dot product for quats
    void Dot(const CQuaternion& a);

    // Normalises a quat
    void Normalise();
};

VALIDATE_SIZE(CQuaternion, 0x10);
