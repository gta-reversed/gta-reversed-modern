/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

class CTimer {
public:
    typedef std::uint64_t(__cdecl* TimerFunction_t)();
    static TimerFunction_t& ms_fnTimerFunction;

    // class variables
    static bool& m_sbEnableTimeDebug;
    static bool& bSkipProcessThisFrame;
    static bool& bSlowMotionActive;
    static float& game_FPS;

    static bool& m_CodePause;
    static bool& m_UserPause;
    static unsigned int& m_FrameCounter;
    static float& ms_fTimeStepNonClipped;
    static float& ms_fTimeStep;
    static unsigned int& m_snTimerDivider;

    static float& ms_fOldTimeStep;
    static float& ms_fSlowMotionScale;

    // game speed
    static float& ms_fTimeScale;
    static unsigned int& m_snTimeInMillisecondsPauseMode;
    static unsigned int& m_snTimeInMillisecondsNonClipped;
    static unsigned int& m_snPreviousTimeInMillisecondsNonClipped;
    static unsigned int& m_snTimeInMilliseconds;
    static std::uint64_t& m_snRenderStartTime;
    static std::uint64_t& m_snRenderPauseTime;
    static unsigned int& m_snRenderTimerPauseCount;

    // Freshly from R*:
    static unsigned int& m_snPPPPreviousTimeInMilliseconds;
    static unsigned int& m_snPPPreviousTimeInMilliseconds;
    static unsigned int& m_snPPreviousTimeInMilliseconds;
    static unsigned int& m_snPreviousTimeInMilliseconds;

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
    static unsigned int GetCyclesPerMillisecond();
    static unsigned int GetCyclesPerFrame();
    static std::uint64_t GetCurrentTimeInCycles();
    static bool GetIsSlowMotionActive();
    static bool GetIsPaused() { return m_UserPause || m_CodePause; }
    static void UpdateVariables(float timeStep);
    static void UpdateTimeStep(float fTimeStep);

    static inline uint32_t GetTimeStepInMilliseconds() { return static_cast<uint32_t>(ms_fTimeStep * 20.0F); }
    static void Update();
};
