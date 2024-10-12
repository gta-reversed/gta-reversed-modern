#include "StdInc.h"

#include "IdleCam.h"
#include "InterestingEvents.h"

CIdleCam& gIdleCam = *(CIdleCam*)0xB6FDA0;
uint32& gbCineyCamProcessedOnFrame = *(uint32*)0xB6EC40;

void CIdleCam::InjectHooks() {
    RH_ScopedClass(CIdleCam);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GetLookAtPositionOnTarget, 0x50EAE0, { .reversed = false });
    RH_ScopedInstall(Init, 0x50E6D0);
    RH_ScopedInstall(Reset, 0x50A160);
    RH_ScopedInstall(ProcessIdleCamTicker, 0x50A200);
    RH_ScopedInstall(SetTarget, 0x50A280, { .reversed = false });
    RH_ScopedInstall(FinaliseIdleCamera, 0x50E760, { .reversed = false });
    RH_ScopedInstall(SetTargetPlayer, 0x50EB50, { .reversed = false });
    RH_ScopedInstall(IsTargetValid, 0x517770, { .reversed = false });
    RH_ScopedInstall(ProcessTargetSelection, 0x517870, { .reversed = false });
    RH_ScopedInstall(ProcessSlerp, 0x5179E0, { .reversed = false });
    RH_ScopedInstall(ProcessFOVZoom, 0x517BF0, { .reversed = false });
    RH_ScopedInstall(Run, 0x51D3E0);
    RH_ScopedInstall(Process, 0x522C80, { .reversed = false });
    RH_ScopedInstall(IdleCamGeneralProcess, 0x50E690);
}

// 0x517760
CIdleCam::CIdleCam() {
    Init();
}

// 0x50E6D0
void CIdleCam::Init() {
    m_DistStartFOVZoom                         = 15.0f;
    m_ZoomNearest                              = 15.0f;
    m_SlerpDuration                            = 2000.0f;
    m_TimeControlsIdleForIdleToKickIn          = 90000.0f;
    m_TimeToConsiderNonVisibleEntityAsOccluded = 3000.0f;
    m_DistTooClose                             = 4.0f;
    m_DistTooFar                               = 80.0f;
    m_DegreeShakeIdleCam                       = 1.0f;
    m_ShakeBuildUpTime                         = 3000.0f;
    m_ZoomFarthest                             = 70.0f;
    m_DurationFOVZoom                          = 1000.0f;
    m_TargetLOSFramestoReject                  = 14;
    m_TimeBeforeNewZoomIn                      = 12000.0f;
    m_TimeMinimumToLookAtSomething             = 5000.0f;
    m_IncreaseMinimumTimeFactorForZoomedIn     = 2.0f;
    m_LastTimePadTouched                       = 0;
    m_IdleTickerFrames                         = 0;
    Reset(false);
}

// 0x50A160
void CIdleCam::Reset(bool resetControls) {
    m_PositionToSlerpFrom.Reset();
    m_LastIdlePos.Reset();
    m_TimeSlerpStarted               = -1.0f;
    m_TimeIdleCamStarted             = -1.0f;
    m_TimeLastTargetSelected         = -1.0f;
    m_ZoomFrom                       = -1.0f;
    m_ZoomTo                         = -1.0f;
    m_TimeZoomStarted                = -1.0f;
    m_TimeTargetEntityWasLastVisible = -1.0f;
    m_TimeLastZoomIn                 = -1.0f;
    m_Target                         = 0;
    m_ZoomState                      = 3;
    m_nForceAZoomOut                 = 0;
    m_CurFOV                         = 70.0f;
    m_TargetLOSCounter               = 0;
    m_bHasZoomedIn                   = 0;
    m_SlerpTime                      = 1.0f;

    if (resetControls) {
        CPad::GetPad()->LastTimeTouched = CTimer::GetTimeInMS();
    }
}

// 0x50A200
void CIdleCam::ProcessIdleCamTicker() {
    if (m_LastTimePadTouched == CPad::GetPad(0)->LastTimeTouched) {
        m_IdleTickerFrames += static_cast<uint32>(CTimer::ms_fTimeStep * 20.0f);
    } else {
        m_LastTimePadTouched = CPad::GetPad(0)->LastTimeTouched;
        m_IdleTickerFrames   = 0;
    }
}

// inlined
bool CIdleCam::IsItTimeForIdleCam() {
    // return (float)field_94 <= field_28;
    return false; // Android
}

// wrong name?
// 0x50E690
void CIdleCam::IdleCamGeneralProcess() {
    if (gIdleCam.m_IdleTickerFrames <= gIdleCam.m_TimeControlsIdleForIdleToKickIn) {
        g_InterestingEvents.m_b1 = false;
    }

    if (TheCamera.GetActiveCam().m_nMode != MODE_FOLLOWPED) {
        g_InterestingEvents.m_b1    = false;
        gIdleCam.m_IdleTickerFrames = 0;
    }
}

// 0x50EAE0
void CIdleCam::GetLookAtPositionOnTarget(CEntity* target, CVector* posn) {
    plugin::CallMethod<0x50EAE0, CIdleCam*, CEntity*, CVector*>(this, target, posn);
}

// 0x517BF0
void CIdleCam::ProcessFOVZoom(float a1) {
    plugin::CallMethod<0x517BF0, CIdleCam*, float>(this, a1);
}

// 0x517770
bool CIdleCam::IsTargetValid(CEntity* target) {
    return plugin::CallMethodAndReturn<bool, 0x517770, CIdleCam*, CEntity*>(this, target);
}

// 0x50A280
void CIdleCam::SetTarget(CEntity* target) {
    plugin::CallMethod<0x50A280, CIdleCam*, CEntity*>(this, target);
}

// 0x50EB50
void CIdleCam::SetTargetPlayer() {
    plugin::CallMethod<0x50EB50, CIdleCam*>(this);
}

// 0x517870
void CIdleCam::ProcessTargetSelection() {
    plugin::CallMethod<0x517870, CIdleCam*>(this);
}

// inlined, see ProcessSlerp
void CIdleCam::VectorToAnglesRotXRotZ(CVector* posn, float* outA1, float* outA2) {
    assert(false);
}

// 0x5179E0
float CIdleCam::ProcessSlerp(float& outX, float& outZ) {
    return plugin::CallMethodAndReturn<float, 0x5179E0, CIdleCam*, float&, float&>(this, outX, outZ);
}

// 0x50E760
void CIdleCam::FinaliseIdleCamera(float a1, float a2, float a3) {
    plugin::CallMethod<0x50E760, CIdleCam*, float, float, float>(this, a1, a2, a3);
}

// 0x51D3E0
void CIdleCam::Run() {
    const auto beginTime = CTimer::GetTimeInMS();
    ProcessTargetSelection();

    const auto shakeDegree = [&] {
        if (const auto d = beginTime - m_TimeIdleCamStarted; d < m_ShakeBuildUpTime) {
            return d / m_ShakeBuildUpTime;
        }
        return 1.0f;
    }();

    float angleX{}, angleZ{};
    m_SlerpTime = ProcessSlerp(angleX, angleZ);
    ProcessFOVZoom(m_SlerpTime);
    FinaliseIdleCamera(angleX, angleZ, shakeDegree);
}

// 0x522C80
void CIdleCam::Process() {
    plugin::CallMethod<0x522C80, CIdleCam*>(this);
}
