/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CBox {
public:
    CVector m_vecMin{}, m_vecMax{};

public:
    static void InjectHooks();

    void Set(const CVector& vecMin, const CVector& vecMax);
    // updates box corners, like (if left>right then swap(left, right))
    void Recalc();

public:
    CBox() = default;

    CBox(CVector min, CVector max) :
        m_vecMin(min),
        m_vecMax(max)
    {

    }

    inline CVector GetSize() const { return m_vecMax - m_vecMin; }
    inline float GetWidth() const { return m_vecMax.x - m_vecMin.x; }
    inline float GetLength() const { return m_vecMax.y - m_vecMin.y; }
    inline float GetHeight() const { return m_vecMax.z - m_vecMin.z; }
    inline CVector GetCenter() const { return (m_vecMin + m_vecMax) / 2.f; }
};

VALIDATE_SIZE(CBox, 0x18);
