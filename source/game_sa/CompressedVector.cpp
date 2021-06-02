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
        static_cast<int16_t>(vec.x * 128.0f),
        static_cast<int16_t>(vec.y * 128.0f),
        static_cast<int16_t>(vec.z * 128.0f)
    };
}

float UncompressUnitFloat(int16_t val) {
    return static_cast<float>(val) / 4096.0f;
}

CVector UncompressUnitVector(const CompressedVector& compressedVec) {
    return {
        static_cast<float>(compressedVec.x) / 4096.0f,
        static_cast<float>(compressedVec.y) / 4096.0f,
        static_cast<float>(compressedVec.z) / 4096.0f
    };
}

CompressedVector CompressUnitVector(CVector const& vec) {
    return {
        static_cast<int16_t>(vec.x * 4096.0f),
        static_cast<int16_t>(vec.y * 4096.0f),
        static_cast<int16_t>(vec.z * 4096.0f)
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
        static_cast<int16_t>(vec.x * 8.0f),
        static_cast<int16_t>(vec.y * 8.0f),
        static_cast<int16_t>(vec.z * 8.0f)
    };
}
