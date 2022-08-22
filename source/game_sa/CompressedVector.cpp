#include "StdInc.h"

CVector UncompressVector(const CompressedVector& compressedVec) {
    return {
        static_cast<float>(compressedVec.x) / 128.0f,
        static_cast<float>(compressedVec.y) / 128.0f,
        static_cast<float>(compressedVec.z) / 128.0f
    };
}

CompressedVector CompressVector(const CVector& vec) {
    return {
        static_cast<int16>(vec.x * 128.0f),
        static_cast<int16>(vec.y * 128.0f),
        static_cast<int16>(vec.z * 128.0f)
    };
}

float UncompressUnitFloat(int16 val) {
    return static_cast<float>(val) / 4096.0f;
}

CVector UncompressUnitVector(const CompressedVector& compressedVec) {
    return {
        static_cast<float>(compressedVec.x) / 4096.0f,
        static_cast<float>(compressedVec.y) / 4096.0f,
        static_cast<float>(compressedVec.z) / 4096.0f
    };
}

CompressedVector CompressUnitVector(const CVector& vec) {
    return {
        static_cast<int16>(vec.x * 4096.0f),
        static_cast<int16>(vec.y * 4096.0f),
        static_cast<int16>(vec.z * 4096.0f)
    };
}

CVector UncompressLargeVector(const CompressedVector& compressedVec) {
    return {
        static_cast<float>(compressedVec.x) / 8.0f,
        static_cast<float>(compressedVec.y) / 8.0f,
        static_cast<float>(compressedVec.z) / 8.0f
    };
}

CompressedVector CompressLargeVector(const CVector& vec) {
    return {
        static_cast<int16>(vec.x * 8.0f),
        static_cast<int16>(vec.y * 8.0f),
        static_cast<int16>(vec.z * 8.0f)
    };
}

static constexpr float FX_RECIPROCAL = std::numeric_limits<int16>::max();

CVector UncompressFxVector(const CompressedVector& compressedVec) {
    return {
        static_cast<float>(compressedVec.x) / FX_RECIPROCAL,
        static_cast<float>(compressedVec.y) / FX_RECIPROCAL,
        static_cast<float>(compressedVec.z) / FX_RECIPROCAL
    };
}

CVector CompressFxVector(const CompressedVector& compressedVec) {
    return {
        static_cast<float>(compressedVec.x) * FX_RECIPROCAL,
        static_cast<float>(compressedVec.y) * FX_RECIPROCAL,
        static_cast<float>(compressedVec.z) * FX_RECIPROCAL
    };
}
