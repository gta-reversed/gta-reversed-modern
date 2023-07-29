#pragma once

#include "CompressedVector.h"

class CompressedBox {
public:
    CompressedVector m_vecMin;
    CompressedVector m_vecMax;

    void DrawWireFrame(CRGBA color, const CMatrix& transform) const;
};
VALIDATE_SIZE(CompressedBox, 0xC);
