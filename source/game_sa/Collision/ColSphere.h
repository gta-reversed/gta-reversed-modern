/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Sphere.h"

class CColSphere : public CSphere {
public:
    union {
        uint8 m_nMaterial;
        uint8 m_nColSlot;
    };
    union {
        uint8 m_nFlags;
        struct {
            uint8 m_bNotEmpty : 1;
            uint8 m_bIsSingleColDataAlloc : 1;
            uint8 m_bIsActive : 1;
            uint8 m_bFlag0x08 : 1;
            uint8 m_bFlag0x10 : 1;
            uint8 m_bFlag0x20 : 1;
            uint8 m_bFlag0x40 : 1;
            uint8 m_bFlag0x80 : 1;
        };
    };
    uint8 m_nLighting;
    uint8 m_nLight;

public:
    static void InjectHooks();

    CColSphere() = default;

    explicit CColSphere(const CSphere& sp) :
        CSphere(sp)
    {
    }

    CColSphere(CSphere sp, uint8 material, uint8 flags, uint8 lighting) :
        CSphere(sp),
        m_nMaterial(material),
        m_nFlags(flags),
        m_nLighting(lighting)
    {
    }

    CColSphere(float radius, const CVector& center) : 
        CSphere(radius, center)
    {
    };

    void Set(float radius, const CVector& center, uint8 material, uint8 flags, uint8 lighting);
    bool IntersectRay(const CVector& rayOrigin, const CVector& direction, CVector& intersectPoint1, CVector& intersectPoint2);
    bool IntersectEdge(const CVector& startPoint, const CVector& endPoint, CVector& intersectPoint1, CVector& intersectPoint2);
    bool IntersectSphere(const CColSphere& right);
    bool IntersectPoint(const CVector& point);
};

VALIDATE_SIZE(CColSphere, 0x14);
