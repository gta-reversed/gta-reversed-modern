/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <cstdlib> // RAND_MAX


class CGeneral {
public:
    static void InjectHooks();

    static float LimitAngle(float angle);
    static float LimitRadianAngle(float angle);
    static float GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2);
    static float GetATanOfXY(float x, float y);
    static unsigned int GetNodeHeadingFromVector(float x, float y);
    static bool SolveQuadratic(float a, float b, float c, float& x1, float& x2);
    static float GetAngleBetweenPoints(float x1, float y1, float x2, float y2);
    static int GetRandomNumberInRange(const int min, const int max);
    static float GetRandomNumberInRange(const float min, const float max);
};

extern constexpr float RAND_MAX_INT_RECIPROCAL = 1.0f / static_cast<float>(RAND_MAX + 1); // 1.0 / 32768.0 == 1.0 / (RAND_MAX + 1) = 0.0000305175781
extern constexpr float RAND_MAX_FLOAT_RECIPROCAL = 1.0f / static_cast<float>(RAND_MAX);   // 1.0 / 32767.0 == 1.0 / RAND_MAX       = 0.0000305185094
