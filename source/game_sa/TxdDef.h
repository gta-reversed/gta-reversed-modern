/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class TxdDef {
public:
    RwTexDictionary* m_pRwDictionary;
    int16_t m_wRefsCount;
    int16_t m_wParentIndex;
    uint32_t m_hash;
};

VALIDATE_SIZE(TxdDef, 0xC);