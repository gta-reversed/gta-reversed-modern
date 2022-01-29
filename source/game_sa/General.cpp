/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include <random>
#include <cassert>

static std::random_device randomDevice;
static std::mt19937 randomEngine(randomDevice());

void CGeneral::InjectHooks() {
    RH_ScopedClass(CGeneral);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(LimitAngle, 0x53CB00);
    RH_ScopedInstall(LimitRadianAngle, 0x53CB50);
    RH_ScopedInstall(GetRadianAngleBetweenPoints, 0x53CBE0);
    RH_ScopedInstall(GetATanOfXY, 0x53CC70);
    RH_ScopedInstall(GetNodeHeadingFromVector, 0x53CDC0);
    RH_ScopedInstall(SolveQuadratic, 0x53CE30);
    RH_ScopedInstall(GetAngleBetweenPoints, 0x53CEA0);
    RH_ScopedOverloadedInstall(GetRandomNumberInRange, "int", 0x407180, int32 (*)(const int32, const int32));
    RH_ScopedOverloadedInstall(GetRandomNumberInRange, "float", 0x41BD90, float (*)(const float, const float));
}

// 0x53CB00
float CGeneral::LimitAngle(float angle) {
    while (angle >= 180.0f) {
        angle -= 360.0f;
    }

    while (angle < -180.0f) {
        angle += 360.0f;
    }

    return angle;
}

// 0x53CB50
float CGeneral::LimitRadianAngle(float angle) {
    float result = clamp(angle, -25.0f, 25.0f);

    while (result >= PI) {
        result -= 2 * PI;
    }

    while (result < -PI) {
        result += 2 * PI;
    }

    return result;
}

// 0x53CBE0
float CGeneral::GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2) {
    float x = x2 - x1;
    float y = y2 - y1;

    if (y == 0.0f)
        y = 0.0001f;

    if (x > 0.0f) {
        if (y > 0.0f)
            return PI - atan2(x / y, 1.0f);
        else
            return -atan2(x / y, 1.0f);
    } else {
        if (y > 0.0f)
            return -(PI + atan2(x / y, 1.0f));
        else
            return -atan2(x / y, 1.0f);
    }
}

// 0x53CC70
float CGeneral::GetATanOfXY(float x, float y) {
    if (x == 0.0f && y == 0.0f)
        return 0.0f;

    // Wikipedia explains this function in great detail: https://en.wikipedia.org/wiki/Atan2

    float xabs = abs(x);
    float yabs = abs(y);

    if (xabs < yabs) {
        if (y > 0.0f) {
            if (x > 0.0f)
                return 0.5f * PI - atan2(x / y, 1.0f);
            else
                return 0.5f * PI + atan2(-x / y, 1.0f);
        } else {
            if (x > 0.0f)
                return 1.5f * PI + atan2(x / -y, 1.0f);
            else
                return 1.5f * PI - atan2(-x / -y, 1.0f);
        }
    } else {
        if (y > 0.0f) {
            if (x > 0.0f)
                return atan2(y / x, 1.0f);
            else
                return PI - atan2(y / -x, 1.0f);
        } else {
            if (x > 0.0f)
                return 2.0f * PI - atan2(-y / x, 1.0f);
            else
                return PI + atan2(-y / -x, 1.0f);
        }
    }
}

// 0x53CDC0
uint32 CGeneral::GetNodeHeadingFromVector(float x, float y) {
    float angle = GetRadianAngleBetweenPoints(x, y, 0.0f, 0.0f);
    if (angle < 0.0f)
        angle += TWO_PI;

    angle = TWO_PI - angle + RWDEG2RAD(22.5f);

    if (angle >= TWO_PI)
        angle -= TWO_PI;

    return (uint32)floor(angle / RWDEG2RAD(45.0f));
}

// 0x53CE30
bool CGeneral::SolveQuadratic(float a, float b, float c, float& x1, float& x2) {
    float discriminant = b * b - 4.f * a * c;
    if (discriminant < 0.0f)
        return false;

    float discriminantSqrt = sqrt(discriminant);
    x2 = (-b + discriminantSqrt) / (2.0f * a);
    x1 = (-b - discriminantSqrt) / (2.0f * a);
    return true;
}

// 0x53CEA0
float CGeneral::GetAngleBetweenPoints(float x1, float y1, float x2, float y2) {
    return RWRAD2DEG(GetRadianAngleBetweenPoints(x1, y1, x2, y2));
}

/**
 * Returns a pseudo-random number between min and max, exclusive [min, max).
 * @param  min Minimum value
 * @param  max Maximum value. Must be greater than min.
 * @return Integer between min and max, exclusive.
 * @addr   0x407180
 */
int32 CGeneral::GetRandomNumberInRange(const int32 min, const int32 max) {
#ifdef BETTER_RNG
    // TODO: Use better RNG
#else
    return min + static_cast<int32>(rand() * RAND_MAX_INT_RECIPROCAL * (max - min));
#endif
}

/**
 * Returns a pseudo-random number between min and max, inclusive [min, max].
 * @param  min Minimum value
 * @param  max Maximum value. Must be greater than min.
 * @return Float between min and max, exclusive.
 * @addr   0x41BD90
 */
float CGeneral::GetRandomNumberInRange(const float min, const float max) {
#ifdef BETTER_RNG
    std::uniform_real_distribution<float> uniform_dist(min, max);
    return uniform_dist(randomEngine);
#else
    return min + (max - min) * rand() * RAND_MAX_FLOAT_RECIPROCAL;
#endif
}
