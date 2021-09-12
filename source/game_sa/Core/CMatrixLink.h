/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CMatrix.h"

class CPlaceable;

class CMatrixLink : public CMatrix {
public:
    CMatrixLink() : CMatrix() {}
    CMatrixLink(float fScale) : CMatrix() { SetScale(fScale); }

public:
    CPlaceable*  m_pOwner;
    CMatrixLink* m_pPrev;
    CMatrixLink* m_pNext;

public:
    static void InjectHooks();

    inline void Insert(CMatrixLink* pWhere);
    inline void Remove();
};

VALIDATE_SIZE(CMatrixLink, 0x54);
