/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CSphere {
public:
    CVector m_vecCenter;
    float   m_fRadius;

    CSphere() {};
    CSphere(CVector center, float radius) : m_vecCenter(center), m_fRadius(radius) {};
    CSphere(float radius, CVector center) : m_vecCenter(center), m_fRadius(radius) {};

    void Set(float radius, const CVector& center);
};

VALIDATE_SIZE(CSphere, 0x10);
