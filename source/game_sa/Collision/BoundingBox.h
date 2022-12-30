/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Box.h"

class CBoundingBox : public CBox {
public:
    CBoundingBox(const CBox& box) :
        CBox(box)
    {
    }

    CBoundingBox();
    CBoundingBox(CVector vecMin, CVector vecMax);
    explicit CBoundingBox(const CBox& box) : CBox(box) { }

    [[nodiscard]] bool IsPointWithin(const CVector& point) const;
    inline void SetMinMax(CVector min, CVector max);
};

VALIDATE_SIZE(CBoundingBox, 0x18);

extern int32& numBBFailed;
