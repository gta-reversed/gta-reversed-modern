/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class RegisteredMotionBlurStreak;

class CMotionBlurStreaks {
public:
    static constexpr uint32 MAX_NUM_MOTIONBLUR_STREAKS = 4; // default 4
    static CRegisteredMotionBlurStreak(&aStreaks)[MAX_NUM_MOTIONBLUR_STREAKS]; // static CRegisteredMotionBlurStreak aStreaks[4]

    static constexpr uint32 NUM_STREAK_VERTICES = 4;
    static RxObjSpace3DVertex(&aStreakVertices)[NUM_STREAK_VERTICES];
    static constexpr uint32 NUM_STREAK_INDICES = 12;
    static RxVertexIndex(&aIndices)[NUM_STREAK_INDICES];

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void Render();
    static void RegisterStreak(uint32 id, uint8 red, uint8 green, uint8 blue, uint8 alpha, CVector leftPoint, CVector rightPoint);
};
