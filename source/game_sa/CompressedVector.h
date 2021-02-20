/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class  CompressedVector {
public:
    signed short x;
    signed short y;
    signed short z;
};

// 0x411590
void UncompressVector(CVector* outVec, const CompressedVector* compressedVec);
CVector UncompressVector(const CompressedVector* compressedVec);

// 0x4115F0
float UncompressUnitFloat(signed short val);
void UncompressUnitVector(CVector* outVec, const CompressedVector* compressedVec);
CVector UncompressUnitVector(const CompressedVector* compressedVec);

CompressedVector CompressUnitVector(CVector const& vec);

VALIDATE_SIZE(CompressedVector, 6);
