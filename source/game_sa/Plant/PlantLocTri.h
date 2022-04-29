#pragma once

#include "Vector.h"

class CPlantLocTri {
public:
    CVector       posn;
    CVector       posn1;
    CVector       posn2;
    CVector       posn3;
    float         m_fDistance;
    CVector       m_RandVec;
    uint16        m_Density1;
    uint16        m_Density2;
    uint16        m_Density3;
    uint8         m_SurfaceId;
    uint8         m_nLight;
    uint8         m_nFlags;
    CPlantLocTri* m_PrevPlant;
    CPlantLocTri* m_NextPlant;

public:
    void Add(const CVector& p1, const CVector& p2, const CVector& p3, uint8 material, uint8 light, bool bIsProcPlant, bool bIsProcObj);
    void Release();
};
VALIDATE_SIZE(CPlantLocTri, 0x54);
