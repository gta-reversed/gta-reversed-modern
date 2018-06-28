/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"

class CTrainNode {
public:
    short x;
    short y;
    short z;
    unsigned short m_nDistanceFromStart;
    bool m_nSurfaceLighting;
    bool m_bSurfLightingFound;

    CTrainNode();
    void SetX(float X);
    void SetY(float Y);
    void SetZ(float Z);
    float GetX();
    float GetY();
    float GetZ();
    CVector GetPosn();
    void SetDistanceFromStart(float dist);
    float GetDistanceFromStart();
    unsigned char GetLightingFromCollision();
};

VALIDATE_SIZE(CTrainNode, 0xA);