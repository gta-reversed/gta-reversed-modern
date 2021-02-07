#pragma once
#include "PluginBase.h"
#include "CVector.h"

struct CByteCompressedVector
{
    int8_t x;
    int8_t y;
    int8_t z;

    CByteCompressedVector(){}
    CByteCompressedVector(CVector const& vec)
    {
        x = static_cast<int8_t>(vec.x * 127.0F);
        y = static_cast<int8_t>(vec.y * 127.0F);
        z = static_cast<int8_t>(vec.z * 127.0F);
    }
    inline CVector Decompress() const { return CVector(x, y, z) / 127.0F; }
};

class CCompressedMatrixNotAligned
{
public:
    CVector m_vecPos;
    CByteCompressedVector m_vecRight;
    CByteCompressedVector m_vecForward;

public:
    static void InjectHooks();

    void DecompressIntoFullMatrix(CMatrix& matrix);
    void CompressFromFullMatrix(CMatrix& matrix);
};
