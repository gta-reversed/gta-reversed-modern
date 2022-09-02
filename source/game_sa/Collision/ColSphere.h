/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Sphere.h"
#include "ColPoint.h"
#include "ColSurface.h"

class CColSphere : public CSphere {
public:
    CColSurface m_Surface;

public:
    static void InjectHooks();

    CColSphere() = default;

    CColSphere(const CSphere& sp) : CSphere(sp) {}

    constexpr CColSphere(CSphere sp, eSurfaceType material, uint8 pieceType, tColLighting lighting = tColLighting(0xFF)) : CSphere(sp) {
        m_Surface.m_nMaterial = material;
        m_Surface.m_nPiece = pieceType;
        m_Surface.m_nLighting = lighting;
    }

    CColSphere(float radius, const CVector& center) : CSphere(radius, center){};

    CColSphere(const CVector& center, float radius) : CSphere(radius, center){};

    void Set(float radius, const CVector& center, eSurfaceType material, uint8 flags, tColLighting lighting = tColLighting(0xFF));
    bool IntersectRay(const CVector& rayOrigin, const CVector& direction, CVector& intersectPoint1, CVector& intersectPoint2);
    bool IntersectEdge(const CVector& startPoint, const CVector& endPoint, CVector& intersectPoint1, CVector& intersectPoint2);
    bool IntersectSphere(const CColSphere& right);
    bool IntersectPoint(const CVector& point);
};
VALIDATE_SIZE(CColSphere, 0x14);
