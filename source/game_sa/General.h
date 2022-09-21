/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <cstdlib> // RAND_MAX

class CGeneral {
public:
    static void InjectHooks();

    /*!
    * @brief Normalize the `angle` to be between [-180, 180] deg
    */
    static float LimitAngle(float angle);

    /*!
    * @brief Normalize the angle to be between [-pi, pi]
    */
    static float LimitRadianAngle(float angle);
    static float GetRadianAngleBetweenPoints(float x1, float y1, float x2, float y2);
    static float GetATanOfXY(float x, float y);
    static float GetATanOf(CVector2D point) { return GetATanOfXY(point.x, point.y); }
    static uint32 GetNodeHeadingFromVector(float x, float y);
    static bool SolveQuadratic(float a, float b, float c, float& x1, float& x2);
    static float GetAngleBetweenPoints(float x1, float y1, float x2, float y2);
    static uint16 GetRandomNumber();
    static int32 GetRandomNumberInRange(const int32 min, const int32 max);
    static float GetRandomNumberInRange(const float min, const float max);

    // NOTSA - Helpers
    static float GetRadianAngleBetweenPoints(CVector2D a, CVector2D b);
    static bool  RandomBool(uint8 chanceOfTrue);
    static bool  DoCoinFlip();

    /*!
    * @return An item from the range choosen randomly. Same as Python's `random.choice`
    */
    template<rng::random_access_range R>
    static auto& RandomChoice(const R& range) {
        return range[(size_t)CGeneral::GetRandomNumberInRange(0, rng::size(range))];
    }

    /*
    * @notsa
    * @brief Return a random node heading, or direction as commonly referred to. See `GetNodeHeadingFromVector`
    */
    static auto RandomNodeHeading() {
        return (uint8)CGeneral::GetRandomNumberInRange(0, 8);
    }
};

constexpr float RAND_MAX_INT_RECIPROCAL = 1.0f / static_cast<float>(RAND_MAX + 1); // 1.0 / 32768.0 == 1.0 / (RAND_MAX + 1) = 0.0000305175781
constexpr float RAND_MAX_FLOAT_RECIPROCAL = 1.0f / static_cast<float>(RAND_MAX);   // 1.0 / 32767.0 == 1.0 / RAND_MAX       = 0.0000305185094
