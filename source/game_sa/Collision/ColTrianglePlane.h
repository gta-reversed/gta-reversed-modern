/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CompressedVector.h"
#include "Vector.h"
#include "ColTriangle.h"

enum eTrianglePlaneOrientation : uint8 {
    POS_X = 0,
    NEG_X = 1,
    POS_Y = 2,
    NEG_Y = 3,
    POS_Z = 4,
    NEG_Z = 5,
};

class CColTrianglePlane {
public:
    CompressedVector m_normal;
    uint16           m_nDistance;
    uint8            m_nOrientation;

public:
    static void InjectHooks();

    void GetNormal(CVector& out);
    CVector GetNormal() const noexcept;
    void Set(const CompressedVector* vertices, CColTriangle& triangle);
};
VALIDATE_SIZE(CColTrianglePlane, 0xA);
