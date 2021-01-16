/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CRegisteredMotionBlurStreak.h"


class CMotionBlurStreaks {
public:
    static constexpr unsigned int MAX_NUM_MOTIONBLUR_STREAKS = 4; // default 4
    static CRegisteredMotionBlurStreak(&aStreaks)[MAX_NUM_MOTIONBLUR_STREAKS]; // static CRegisteredMotionBlurStreak aStreaks[4]

    static constexpr unsigned int NUM_STREAK_VERTICES = 4;
    static RxObjSpace3DVertex(&aStreakVertices)[NUM_STREAK_VERTICES];
    static constexpr unsigned int NUM_STREAK_INDICES = 12;
    static RxVertexIndex(&aIndices)[NUM_STREAK_INDICES];

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void Render();
    static void RegisterStreak(unsigned int id, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, CVector leftPoint, CVector rightPoint);
};
