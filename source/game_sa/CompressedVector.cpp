#include "StdInc.h"

CVector UncompressVector(const CompressedVector& compressedVec)
{
    CVector result;
    result.x = static_cast<float>(compressedVec.x) / 128.0F;
    result.y = static_cast<float>(compressedVec.y) / 128.0F;
    result.z = static_cast<float>(compressedVec.z) / 128.0F;
    return result;
}

CompressedVector CompressVector(const CVector& vec)
{
    CompressedVector result;
    result.x = static_cast<int16_t>(vec.x * 128.0f);
    result.y = static_cast<int16_t>(vec.y * 128.0f);
    result.z = static_cast<int16_t>(vec.z * 128.0f);
    return result;
}

float UncompressUnitFloat(int16_t val)
{
    return static_cast<float>(val) / 4096.0F;
}

CVector UncompressUnitVector(const CompressedVector& compressedVec)
{
    CVector result;
    result.x = static_cast<float>(compressedVec.x) / 4096.0F;
    result.y = static_cast<float>(compressedVec.y) / 4096.0F;
    result.z = static_cast<float>(compressedVec.z) / 4096.0F;
    return result;
}

CompressedVector CompressUnitVector(CVector const& vec)
{
    CompressedVector result;
    result.x = static_cast<int16_t>(vec.x * 4096.0F);
    result.y = static_cast<int16_t>(vec.y * 4096.0F);
    result.z = static_cast<int16_t>(vec.z * 4096.0F);
    return  result;
}

CVector UncompressLargeVector(const CompressedVector& compressedVec)
{
    CVector result;
    result.x = static_cast<float>(compressedVec.x) / 8.0F;
    result.y = static_cast<float>(compressedVec.y) / 8.0F;
    result.z = static_cast<float>(compressedVec.z) / 8.0F;
    return result;
}

CompressedVector CompressLargeVector(const CVector& vec)
{
    CompressedVector result;
    result.x = static_cast<int16_t>(vec.x * 8.0F);
    result.y = static_cast<int16_t>(vec.y * 8.0F);
    result.z = static_cast<int16_t>(vec.z * 8.0F);
    return  result;
}
