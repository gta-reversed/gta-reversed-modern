#pragma once

#include "Vector.h"

class CEntity;

class CIdleCam {
public:
    CEntity* m_Target;
    CVector  m_PositionToSlerpFrom;
    float    m_TimeSlerpStarted;
    float    m_SlerpDuration;
    CVector  m_LastIdlePos;
    float    m_SlerpTime;
    float    m_TimeControlsIdleForIdleToKickIn;
    float    m_TimeIdleCamStarted;
    int32    m_LastFrameProcessed;
    float    m_TimeLastTargetSelected;
    float    m_TimeMinimumToLookAtSomething;
    float    m_TimeTargetEntityWasLastVisible;
    float    m_TimeToConsiderNonVisibleEntityAsOccluded;
    float    m_DistTooClose;
    float    m_DistStartFOVZoom;
    float    m_DistTooFar;
    int32    m_TargetLOSFramestoReject;
    int32    m_TargetLOSCounter;
    int32    m_ZoomState;
    float    m_ZoomFrom;
    float    m_ZoomTo;
    float    m_TimeZoomStarted;
    float    m_ZoomNearest;
    float    m_ZoomFarthest;
    float    m_CurFOV;
    float    m_DurationFOVZoom;
    bool     m_nForceAZoomOut;
    bool     m_bHasZoomedIn;
    uint16   _pad;
    float    m_TimeBeforeNewZoomIn;
    float    m_TimeLastZoomIn;
    float    m_IncreaseMinimumTimeFactorForZoomedIn;
    float    m_DegreeShakeIdleCam;
    float    m_ShakeBuildUpTime;
    int32    m_LastTimePadTouched;
    int32    m_IdleTickerFrames;
    CCam*    m_Cam;

public:
    static void InjectHooks();

    CIdleCam();

    void Init();
    void Reset(bool a1);
    void ProcessIdleCamTicker();
    bool IsItTimeForIdleCam();
    void IdleCamGeneralProcess();
    void GetLookAtPositionOnTarget(CEntity* target, CVector* posn);
    void ProcessFOVZoom(float a1);
    bool IsTargetValid(CEntity* target);
    void SetTarget(CEntity* target);
    void SetTargetPlayer();
    void ProcessTargetSelection();
    void VectorToAnglesRotXRotZ(CVector* posn, float* outA1, float* outA2);
    void ProcessSlerp(float* outA1, float* outA2);
    void FinaliseIdleCamera(float a1, float a2, float a3);
    void Run();
    void Process();
};

VALIDATE_SIZE(CIdleCam, 0x9C);

extern CIdleCam& gIdleCam;
extern uint32& gbCineyCamProcessedOnFrame;
