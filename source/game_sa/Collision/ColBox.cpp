#include "StdInc.h"

#include "ColBox.h"

CColBox& CColBox::operator=(const CColBox& right) {
    m_vecMin = right.m_vecMin;
    m_vecMax = right.m_vecMax;
    m_nMaterial = right.m_nMaterial;
    m_nLighting = right.m_nLighting;
    return *this;
}
