#pragma once
#include "CompressedVector.h"

class CompressedBox
{
public:
    CompressedVector m_vecMin;
    CompressedVector m_vecMax;
};
VALIDATE_SIZE(CompressedBox, 0xC);
