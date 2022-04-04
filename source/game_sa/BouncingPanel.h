#pragma once

#include "Vector.h"

class CVehicle;
struct RwFrame;

class  CBouncingPanel {
    static float& BOUNCE_SPRING_DAMP_MULT; // 0.95
    static float& BOUNCE_SPRING_RETURN_MULT; // 0.1
    static float& BOUNCE_VEL_CHANGE_LIMIT; // 0.1
    static float& BOUNCE_HANGING_DAMP_MULT; // 0.98
    static float& BOUNCE_HANGING_RETURN_MULT; // 0.02

public:
    uint16 m_nFrameId{(uint16)-1};
    uint16 m_nAxis{};
    float    m_fAngleLimit{};
    CVector  m_vecRotation{};
    CVector  m_vecPos{};

public:
    CBouncingPanel() = default;

    static void InjectHooks();

    void ResetPanel();
    void SetPanel(int16 frameId, int16 axis, float angleLimit);
    float GetAngleChange(float velocity) const;
    void ProcessPanel(CVehicle* vehicle, RwFrame* frame, CVector arg2, CVector arg3, float arg4, float arg5);
};
VALIDATE_SIZE(CBouncingPanel, 0x20);
