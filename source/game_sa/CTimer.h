/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

class CTimer {
public:
    typedef uint64(__cdecl* TimerFunction_t)();
    static TimerFunction_t& ms_fnTimerFunction;

    // class variables
    static bool& m_sbEnableTimeDebug;
    static bool& bSkipProcessThisFrame;
    static bool& bSlowMotionActive;
    static float& game_FPS;

    static bool& m_CodePause;
    static bool& m_UserPause;
    static uint32& m_FrameCounter;
    static float& ms_fTimeStepNonClipped;
    static float& ms_fTimeStep;
    static uint32& m_snTimerDivider;

    static float& ms_fOldTimeStep;
    static float& ms_fSlowMotionScale;

    // game speed
    static float& ms_fTimeScale;
    static uint32& m_snTimeInMillisecondsPauseMode;
    static uint32& m_snTimeInMillisecondsNonClipped;
    static uint32& m_snPreviousTimeInMillisecondsNonClipped;
    static uint32& m_snTimeInMilliseconds;
    static uint64& m_snRenderStartTime;
    static uint64& m_snRenderPauseTime;
    static uint32& m_snRenderTimerPauseCount;

    // Freshly from R*:
    static uint32& m_snPPPPreviousTimeInMilliseconds;
    static uint32& m_snPPPreviousTimeInMilliseconds;
    static uint32& m_snPPreviousTimeInMilliseconds;
    static uint32& m_snPreviousTimeInMilliseconds;

public:
    static void InjectHooks();

    // class functions
    static void Initialise();
    static void Shutdown();
    static void Suspend();
    static void Resume();
    static void Stop();
    static void StartUserPause();
    static void EndUserPause();
    static uint32 GetCyclesPerMillisecond();
    static uint32 GetCyclesPerFrame();
    static uint64 GetCurrentTimeInCycles();
    static bool GetIsSlowMotionActive();
    static bool GetIsPaused() { return m_UserPause || m_CodePause; }
    static void UpdateVariables(float timeStep);
    static void UpdateTimeStep(float fTimeStep);
    static void Update();

    // Inlined funcs
    // They could have used functions with a longer name, ex:
    // GetTimeInMillisecond, we have shorter GetTimeInMS
    static uint32 GetFrameCounter() { return m_FrameCounter; }
    static uint32 GetTimeInMS() { return m_snTimeInMilliseconds; }
    static uint32 GetTimeStepInMS() { return static_cast<uint32>(ms_fTimeStep * 20.0F); }
};
