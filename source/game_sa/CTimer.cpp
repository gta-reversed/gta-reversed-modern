/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "oswrapper.h"

CTimer::TimerFunction_t& CTimer::ms_fnTimerFunction = *(TimerFunction_t*)0xB7CB28; // Izzotop: Added in commit 50ce121c. That should be just timerDef.

bool& CTimer::m_sbEnableTimeDebug = *(bool*)0xB7CB40;
bool& CTimer::bSkipProcessThisFrame = *(bool*)0xB7CB89;
bool& CTimer::bSlowMotionActive = *(bool*)0xB7CB88;
float& CTimer::game_FPS = *(float*)0xB7CB50;

bool& CTimer::m_CodePause = *(bool*)0xB7CB48;
bool& CTimer::m_UserPause = *(bool*)0xB7CB49;

unsigned int& CTimer::m_FrameCounter = *(unsigned int*)0xB7CB4C;
unsigned int& CTimer::m_snTimerDivider = *(unsigned int*)0xB7CB2C;

float& CTimer::ms_fTimeStep = *(float*)0xB7CB5C;
float& CTimer::ms_fTimeStepNonClipped = *(float*)0xB7CB58;
float& CTimer::ms_fOldTimeStep = *(float*)0xB7CB54;

float& CTimer::ms_fTimeScale = *(float*)0xB7CB64;
float& CTimer::ms_fSlowMotionScale = *(float*)0xB7CB60;

unsigned int& CTimer::m_snTimeInMillisecondsPauseMode = *(unsigned int*)0xB7CB7C;
unsigned int& CTimer::m_snTimeInMillisecondsNonClipped = *(unsigned int*)0xB7CB80;
unsigned int& CTimer::m_snTimeInMilliseconds = *(unsigned int*)0xB7CB84;
unsigned int& CTimer::m_snPreviousTimeInMillisecondsNonClipped = *(unsigned int*)0xB7CB68;

std::uint64_t& CTimer::m_snRenderStartTime = *(std::uint64_t*)0xB7CB38;
std::uint64_t& CTimer::m_snRenderPauseTime = *(std::uint64_t*)0xB7CB30;
unsigned int& CTimer::m_snRenderTimerPauseCount = *(unsigned int*)0xB7CB44;

unsigned int& CTimer::m_snPPPPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB6C;
unsigned int& CTimer::m_snPPPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB70;
unsigned int& CTimer::m_snPPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB74;
unsigned int& CTimer::m_snPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB78;


void CTimer::InjectHooks()
{
    ReversibleHooks::Install("CTimer", "Initialise", 0x5617E0, &CTimer::Initialise);
    ReversibleHooks::Install("CTimer", "Shutdown", 0x5618C0, &CTimer::Shutdown);
    ReversibleHooks::Install("CTimer", "Suspend", 0x5619D0, &CTimer::Suspend);
    ReversibleHooks::Install("CTimer", "Resume", 0x561A00, &CTimer::Resume);
    ReversibleHooks::Install("CTimer", "Stop", 0x561AA0, &CTimer::Stop);
    ReversibleHooks::Install("CTimer", "StartUserPause", 0x561AF0, &CTimer::StartUserPause);
    ReversibleHooks::Install("CTimer", "EndUserPause", 0x561B00, &CTimer::EndUserPause);
    ReversibleHooks::Install("CTimer", "GetCyclesPerMillisecond", 0x561A40, &CTimer::GetCyclesPerMillisecond);
    ReversibleHooks::Install("CTimer", "GetCyclesPerFrame", 0x561A50, &CTimer::GetCyclesPerFrame);
    ReversibleHooks::Install("CTimer", "GetCurrentTimeInCycles", 0x561A80, &CTimer::GetCurrentTimeInCycles);
    ReversibleHooks::Install("CTimer", "GetIsSlowMotionActive", 0x561AD0, &CTimer::GetIsSlowMotionActive);
    ReversibleHooks::Install("CTimer", "UpdateVariables", 0x5618D0, &CTimer::UpdateVariables);
    ReversibleHooks::Install("CTimer", "Update", 0x561B10, &CTimer::Update);
}

// 64-bit RsTimer wrapper
// 0x5617C0
std::uint64_t GetMillisecondTime() {
    return plugin::CallAndReturn<std::uint64_t, 0x5617C0>();
    // return RsTimer();
}

// 0x5617E0
void CTimer::Initialise()
{
    m_UserPause = false;
    m_CodePause = false;
    bSlowMotionActive = false;
    bSkipProcessThisFrame = false;

    m_snTimeInMilliseconds = 0;
    m_snTimeInMillisecondsPauseMode = 1;
    m_snTimeInMillisecondsNonClipped = 1;
    m_snPreviousTimeInMilliseconds = 0;
    m_snPPreviousTimeInMilliseconds = 0;
    m_snPPPreviousTimeInMilliseconds = 0;
    m_snPPPPreviousTimeInMilliseconds = 0;
    m_snPreviousTimeInMillisecondsNonClipped = 0;

    m_snRenderTimerPauseCount = 0;

    m_FrameCounter = 0;
    m_sbEnableTimeDebug = false;
    game_FPS = 0.0f;

    ms_fTimeScale = 1.0;
    ms_fSlowMotionScale = -1.0;
    ms_fTimeStep = 1.0f;
    ms_fOldTimeStep = 1.0f;
    // unused dword_B7CB60 = 0xBF800000;

    TimerFunction_t timerFunc;
    auto frequency = GetOSWPerformanceFrequency();
    if (frequency) {
        timerFunc = GetOSWPerformanceTime;
        m_snTimerDivider = frequency / 1000;
    } else {
        timerFunc = GetMillisecondTime;
        m_snTimerDivider = 1;
    }
    ms_fnTimerFunction = timerFunc;
    m_snRenderStartTime = timerFunc();
}

// 0x5618C0
void CTimer::Shutdown() {
    m_sbEnableTimeDebug = false;
}

// 0x5619D0
void CTimer::Suspend()
{
    if (m_sbEnableTimeDebug)
    {
        if (++m_snRenderTimerPauseCount <= 1)
            m_snRenderPauseTime = ms_fnTimerFunction();
    }
}

// 0x561A00
void CTimer::Resume()
{
    if (m_sbEnableTimeDebug)
    {
        if (!--m_snRenderTimerPauseCount) {
            m_snRenderStartTime = ms_fnTimerFunction() - m_snRenderPauseTime + m_snRenderStartTime;
        }
    }
}

// 0x561AA0
void CTimer::Stop()
{
    m_snPPPPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
    m_snPPPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
    m_snPPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
    m_snPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
    m_sbEnableTimeDebug = false;
    m_snPreviousTimeInMillisecondsNonClipped = m_snTimeInMillisecondsNonClipped;
}

// 0x561AF0
void CTimer::StartUserPause()
{
    m_UserPause = true;
}

// 0x561B00
void CTimer::EndUserPause()
{
    m_UserPause = false;
}

// 0x561A40
unsigned int CTimer::GetCyclesPerMillisecond()
{
    return m_snTimerDivider;
}

// cycles per ms * 20
// 0x561A50
unsigned int CTimer::GetCyclesPerFrame()
{
    return (unsigned int)((float)m_snTimerDivider * 20.0f);
}

// 0x561A80
std::uint64_t CTimer::GetCurrentTimeInCycles()
{
    return GetOSWPerformanceTime() - m_snRenderStartTime;
}

// 0x561AD0
bool CTimer::GetIsSlowMotionActive()
{
    return ms_fTimeScale < 1.0f;
}

// 0x5618D0
void CTimer::UpdateVariables(float timeStep)
{
    /* Izzotop: from IDA directly to here (tested)
    float step = timeStep / float(m_snTimerDivider);
    m_snTimeInMillisecondsNonClipped += (unsigned int)(step);
    ms_fTimeStepNonClipped = step * 0.05f; // step / 20.0f;

    if (step > 300.f) {
        step = 300.f;
    }
    m_snTimeInMilliseconds += (unsigned int)(step);

    if (ms_fTimeStepNonClipped < 0.01f &&
        !GetIsPaused() &&
        !CSpecialFX::bSnapShotActive
    ) {
        ms_fTimeStepNonClipped = 0.01f;
    }

    ms_fOldTimeStep = ms_fTimeStep;

    if (ms_fTimeStepNonClipped > 3.0f) {
        ms_fTimeStep = 3.0f;
    } else if (ms_fTimeStepNonClipped > 0.00001f) {
        ms_fTimeStep = ms_fTimeStepNonClipped;
    } else {
        ms_fTimeStep = 0.00001f;
    }
    */

    // Pirulax: Shorter code, same functionality.
    const float realStep = (float)timeStep / (float)m_snTimerDivider;
    m_snTimeInMillisecondsNonClipped += (unsigned int)realStep;
    ms_fTimeStepNonClipped = 0.05f * realStep; // step / 20.0f;

    const auto timeToAdd = (unsigned int)std::min<float>(realStep, 300.0f); // Clamp to max 300
    m_snTimeInMilliseconds += timeToAdd;
    if (ms_fTimeStepNonClipped < 0.01f && !m_UserPause && !m_CodePause && !CSpecialFX::bSnapShotActive) {
        ms_fTimeStepNonClipped = 0.01f;
    }

    ms_fOldTimeStep = ms_fTimeStep;
    ms_fTimeStep = clamp<float>(ms_fTimeStepNonClipped, 0.00001f, 3.0f);
}

void CTimer::UpdateTimeStep(float fTimeStep)
{
    ms_fTimeStep = std::max(fTimeStep, 0.00001f);
}

// 0x561B10
void CTimer::Update()
{
    if (!ms_fnTimerFunction)
        return;

    m_sbEnableTimeDebug = true;
    game_FPS = float(1000.0f / float(m_snTimeInMillisecondsNonClipped - m_snPreviousTimeInMillisecondsNonClipped));

    // Update history
    m_snPPPPreviousTimeInMilliseconds = m_snPPPreviousTimeInMilliseconds;
    m_snPPPreviousTimeInMilliseconds = m_snPPreviousTimeInMilliseconds;
    m_snPPreviousTimeInMilliseconds = m_snPreviousTimeInMilliseconds;
    m_snPreviousTimeInMilliseconds = m_snTimeInMilliseconds;
    m_snPreviousTimeInMillisecondsNonClipped = m_snTimeInMillisecondsNonClipped;

    const uint64_t nRenderTimeBefore = m_snRenderStartTime;
    m_snRenderStartTime = ms_fnTimerFunction();
    auto fTimeDelta = float(m_snRenderStartTime - nRenderTimeBefore);
    if (!GetIsPaused())
        fTimeDelta *= ms_fTimeScale;

    m_snTimeInMillisecondsPauseMode += (unsigned int)(fTimeDelta / float(m_snTimerDivider));
    if (GetIsPaused())
        fTimeDelta = 0.0f;

    UpdateVariables(fTimeDelta);
    m_FrameCounter++;
}
