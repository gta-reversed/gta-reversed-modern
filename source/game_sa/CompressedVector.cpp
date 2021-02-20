#include "StdInc.h"

// 0x411590
void UncompressVector(CVector* outVec, const CompressedVector* compressedVec)
{
    outVec->x = static_cast<float>(compressedVec->x) / 128.0F;
    outVec->y = static_cast<float>(compressedVec->y) / 128.0F;
    outVec->z = static_cast<float>(compressedVec->z) / 128.0F;
}

CVector UncompressVector(const CompressedVector* compressedVec)
{
    CVector outVec;
    UncompressVector(&outVec, compressedVec);
    return outVec;
}

float UncompressUnitFloat(signed short val)
{
    return static_cast<float>(val) / 4096.0F;
}

void UncompressUnitVector(CVector* outVec, const CompressedVector* compressedVec)
{
    outVec->x = static_cast<float>(compressedVec->x) / 4096.0F;
    outVec->y = static_cast<float>(compressedVec->y) / 4096.0F;
    outVec->z = static_cast<float>(compressedVec->z) / 4096.0F;
}

CVector UncompressUnitVector(const CompressedVector* compressedVec)
{
    CVector outVec;
    UncompressUnitVector(&outVec, compressedVec);
    return outVec;
}

CompressedVector CompressUnitVector(CVector const& vec)
{
    CompressedVector outVec;
    outVec.x = static_cast<int16_t>(vec.x * 4096.0F);
    outVec.y = static_cast<int16_t>(vec.y * 4096.0F);
    outVec.z = static_cast<int16_t>(vec.z * 4096.0F);
    return outVec;
}
