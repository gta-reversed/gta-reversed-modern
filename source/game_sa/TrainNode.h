/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
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
    bool   m_nSurfaceLighting;
    bool   m_bSurfLightingFound;

    CTrainNode();

    void    SetX(float X);
    void    SetY(float Y);
    void    SetZ(float Z);
    float   GetX();
    float   GetY();
    float   GetZ();
    CVector GetPosn();
    void    SetDistanceFromStart(float dist);
    float   GetDistanceFromStart();
    uint8   GetLightingFromCollision();
};

VALIDATE_SIZE(CTrainNode, 0xA);