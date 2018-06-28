/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CCamera.h"

class  CGeneral {
public:
    static float LimitAngle(float angle);
    static float LimitRadianAngle(float angle);
    static float GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2);
    static float GetATanOfXY(float x, float y);
    static unsigned char GetNodeHeadingFromVector(float x, float y);
    static bool SolveQuadratic(float a, float b, float c, float& x1, float& x2);
    static float GetAngleBetweenPoints(float x1, float y1, float x2, float y2);
    static unsigned int GetRandomNumberInRange(int min, int max); // returns random int in range [min;max)
    static float GetRandomNumberInRange(float min, float max); // returns random float in range [min;max)
    static void CamShakeNoPos(CCamera *camera, float strength);
};