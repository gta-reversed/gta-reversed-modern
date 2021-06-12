/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CBox.h"

class CBoundingBox : public CBox {
public:
    CBoundingBox();
    CBoundingBox(CVector vecMin, CVector vecMax);

    bool IsPointWithin(const CVector& point);
};

VALIDATE_SIZE(CBoundingBox, 0x18);

extern int32_t& numBBFailed;
