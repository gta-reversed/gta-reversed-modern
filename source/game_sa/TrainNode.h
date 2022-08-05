/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"

class CTrainNode {
public:
    int16  x;
    int16  y;
    int16  z;
    uint16 m_nDistanceFromStart;
    tColLighting m_nSurfaceLighting;
    bool m_bSurfLightingFound;

public:
    CTrainNode();

    void SetX(float X);
    void SetY(float Y);
    void SetZ(float Z);
    [[nodiscard]] float GetX() const;
    [[nodiscard]] float GetY() const;
    [[nodiscard]] float GetZ() const;
    CVector GetPosn() const;
    void SetDistanceFromStart(float dist);
    [[nodiscard]] float GetDistanceFromStart() const;
    tColLighting GetLightingFromCollision();
};
VALIDATE_SIZE(CTrainNode, 0xA);
