/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

CTimer::TimerFunction_t& CTimer::ms_fnTimerFunction = *(TimerFunction_t*)0xB7CB28;

bool& CTimer::m_sbEnableTimeDebug = *(bool*)0xB7CB40;
bool& CTimer::bSkipProcessThisFrame = *(bool*)0xB7CB89;
bool& CTimer::bSlowMotionActive = *(bool*)0xB7CB88;
float& CTimer::game_FPS = *(float*)0xB7CB50;

bool& CTimer::m_CodePause = *(bool*)0xB7CB48;
bool& CTimer::m_UserPause = *(bool*)0xB7CB49;

unsigned int& CTimer::m_FrameCounter = *(unsigned int*)0xB7CB4C;
unsigned int& CTimer::m_snTimerDivider = *(unsigned int*)0xB7CB2C;

float& CTimer::ms_fTimeStepNonClipped = *(float*)0xB7CB58;
float& CTimer::ms_fTimeStep = *(float*)0xB7CB5C;
float& CTimer::ms_fTimeScale = *(float*)0xB7CB64;

unsigned int& CTimer::m_snTimeInMillisecondsPauseMode = *(unsigned int*)0xB7CB7C;
unsigned int& CTimer::m_snTimeInMillisecondsNonClipped = *(unsigned int*)0xB7CB80;
unsigned int& CTimer::m_snTimeInMilliseconds = *(unsigned int*)0xB7CB84;
unsigned int& CTimer::ms_nPreviousTimeInMillisecondsNonClipped = *(unsigned int*)0xB7CB68;
std::uint64_t& CTimer::m_snRenderStartTime = *(std::uint64_t*)0xB7CB38;

unsigned int& CTimer::m_snPPPPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB78;
unsigned int& CTimer::m_snPPPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB74;
unsigned int& CTimer::m_snPPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB70;
unsigned int& CTimer::m_snPreviousTimeInMilliseconds = *(unsigned int*)0xB7CB6C;

float& CTimer::ms_fOldTimeStep = *(float*)0xB7CB54;
float& CTimer::ms_fSlowMotionScale = *(float*)0xB7CB60;

void CTimer::InjectHooks()
{
    HookInstall(0x561B10, &Update);
}

void CTimer::Initialise()
{
    ((void(__cdecl *)()) 0x5617E0)();
}

void CTimer::Shutdown()
{
    ((void(__cdecl *)()) 0x5618C0)();
}

// Also called GetRealTimeScale in some idbs
void CTimer::UpdateVariables(float timeStep)
{
    ((void(__cdecl *)(float)) 0x5618D0)(timeStep);
}

void CTimer::Suspend()
{
    ((void(__cdecl *)()) 0x5619D0)();
}

void CTimer::Resume()
{
    ((void(__cdecl *)()) 0x561A00)();
}

int CTimer::GetCyclesPerMillisecond()
{
    return ((int(__cdecl *)()) 0x561A40)();
}

int CTimer::GetCyclesPerFrame()
{
    return ((int(__cdecl *)()) 0x561A50)();
}

unsigned int CTimer::GetCurrentTimeInCycles()
{
    return ((unsigned int(__cdecl *)()) 0x561A80)();
}

void CTimer::Stop()
{
    ((void(__cdecl *)()) 0x561AA0)();
}

bool CTimer::GetIsSlowMotionActive()
{
    return ((bool(__cdecl *)()) 0x561AD0)();
}

void CTimer::StartUserPause()
{
    ((void(__cdecl *)()) 0x561AF0)();
}

void CTimer::EndUserPause()
{
    ((void(__cdecl *)()) 0x561B00)();
}

void CTimer::Update()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__cdecl *)()) 0x561B10)();
#else
    if (!ms_fnTimerFunction)
        return;

    m_sbEnableTimeDebug = true;
    game_FPS = float(1000.0 / (m_snTimeInMillisecondsNonClipped - ms_nPreviousTimeInMillisecondsNonClipped));

    // Update history
    m_snPPPPreviousTimeInMilliseconds = m_snPPPreviousTimeInMilliseconds;
    m_snPPPreviousTimeInMilliseconds = m_snPPreviousTimeInMilliseconds;
    m_snPPreviousTimeInMilliseconds = m_snPreviousTimeInMilliseconds;
    m_snPreviousTimeInMilliseconds = m_snTimeInMilliseconds;

    ms_nPreviousTimeInMillisecondsNonClipped = m_snTimeInMillisecondsNonClipped;

    const auto nRenderTimeBefore = m_snRenderStartTime;
    m_snRenderStartTime = ms_fnTimerFunction();

    auto fTimeDelta = float(m_snRenderStartTime - nRenderTimeBefore);

    const bool bPaused = m_CodePause || m_UserPause;
    if (!bPaused)
        fTimeDelta *= ms_fTimeScale;

    m_snTimeInMillisecondsPauseMode += unsigned int(fTimeDelta / m_snTimerDivider);

    UpdateVariables(bPaused ? 0.0f : fTimeDelta);
    m_FrameCounter++;
#endif
}

void CTimer::UpdateTimeStep(float fTimeStep)
{
    if (fTimeStep > 0.00001f)
        CTimer::ms_fTimeStep = fTimeStep;
    else
        CTimer::ms_fTimeStep = 0.00001f;
}
