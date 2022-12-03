#pragma once

#include "Vector.h"

struct CByteCompressedVector {
    int8 x;
    int8 y;
    int8 z;

    CByteCompressedVector() = default;
    CByteCompressedVector(const CVector& vec) {
        x = static_cast<int8>(vec.x * 127.0F);
        y = static_cast<int8>(vec.y * 127.0F);
        z = static_cast<int8>(vec.z * 127.0F);
    }
    inline CVector Decompress() const {
        return CVector(x, y, z) / 127.0F;
    }
};

class CCompressedMatrixNotAligned {
public:
    CVector               m_vecPos;
    CByteCompressedVector m_vecRight;
    CByteCompressedVector m_vecForward;

private:
    uint16                align;

public:
    static void InjectHooks();

    void DecompressIntoFullMatrix(CMatrix& matrix) const;
    void CompressFromFullMatrix(CMatrix& matrix);
};
VALIDATE_SIZE(CCompressedMatrixNotAligned, 20);
