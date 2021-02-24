/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class CompressedVector {
public:
    int16_t x;
    int16_t y;
    int16_t z;
};

VALIDATE_SIZE(CompressedVector, 6);

CVector UncompressVector(const CompressedVector& compressedVec);
CompressedVector CompressVector(const CVector& vec);
float UncompressUnitFloat(int16_t val);
CVector UncompressUnitVector(const CompressedVector& compressedVec);
CompressedVector CompressUnitVector(CVector const& vec);
