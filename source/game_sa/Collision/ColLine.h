/*
        Plugin-SDK file
        Authors: GTA Community. See more here
        https://github.com/DK22Pac/plugin-sdk
        Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CColLine {
public:
    CVector m_vecStart;
    float   m_fStartSize;
    CVector m_vecEnd;
    float   m_fEndSize;

public:
    static void InjectHooks();

    CColLine() = default;
    CColLine(const CVector& start, const CVector& end);

    void Set(const CVector& start, const CVector& end);

    /*!
    * @notsa
    * @brief Distance to a point from this line (Uses `CCollision::DistToLine`)
    */
    float DistTo(CVector pos) const;
};

VALIDATE_SIZE(CColLine, 0x20);
