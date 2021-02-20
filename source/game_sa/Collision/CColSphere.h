/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CSphere.h"

class CColSphere : public CSphere {
public:
    unsigned char m_nMaterial;
    union {
        unsigned char m_nFlags;
        struct {
            unsigned char m_bFlag0x01 : 1;
            unsigned char m_bIsSingleColDataAlloc : 1;
            unsigned char m_bIsActive : 1;
            unsigned char m_bFlag0x08 : 1;
            unsigned char m_bFlag0x10 : 1;
            unsigned char m_bFlag0x20 : 1;
            unsigned char m_bFlag0x40 : 1;
            unsigned char m_bFlag0x80 : 1;
        };
    };
    unsigned char m_nLighting;
    unsigned char m_nLight;

    static void InjectHooks();

    void Set(float radius, CVector const& center);
    void Set(float radius, CVector const& center, std::uint8_t material, std::uint8_t flags, std::uint8_t lighting);
    bool IntersectRay(CVector const& rayOrigin, CVector const& direction, CVector& intersectPoint1, CVector& intersectPoint2);
    bool IntersectEdge(CVector const& startPoint, CVector const& endPoint, CVector& intersectPoint1, CVector& intersectPoint2);
    bool IntersectSphere(CColSphere const& right);
    bool IntersectPoint(CVector const& point);
};

VALIDATE_SIZE(CColSphere, 0x14);
