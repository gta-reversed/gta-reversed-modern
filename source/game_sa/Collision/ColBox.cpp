#include "StdInc.h"

#include "ColBox.h"

CColBox& CColBox::operator=(const CColBox& right) {
    m_vecMin = right.m_vecMin;
    m_vecMax = right.m_vecMax;
    m_Surface.m_nMaterial = right.m_Surface.m_nMaterial;
    m_Surface.m_nLighting = right.m_Surface.m_nLighting;
    return *this;
}

// 0x40EE70
void CColBox::Set(const CVector& sup, const CVector& inf, eSurfaceType material, uint8 pieceType, tColLighting lighting) {
    m_vecMin = sup;
    m_vecMax = inf;
    m_Surface.m_nMaterial = material;
    m_Surface.m_nPiece = pieceType;
    m_Surface.m_nLighting = lighting;
}
