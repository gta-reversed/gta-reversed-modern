#pragma once

#include "ShadowCamera.h"

class CRealTimeShadow;

class CRealTimeShadowManager {
public:
    static constexpr int32 NUM_REALTIME_SHADOWS = 16;

public:
    char             m_bInitialised;
    char             m_bNeedsReinit;
    CRealTimeShadow* m_apShadows[NUM_REALTIME_SHADOWS];
    CShadowCamera    m_BlurCamera;
    CShadowCamera    m_GradientCamera[4];

public:
    static void InjectHooks();

    void Init();
    void Exit();
    void ReInit();
    void Update();

    CRealTimeShadow& GetRealTimeShadow(CPhysical* pPhysical);
    void             DoShadowThisFrame(CPhysical* pPhysical);
    void             ReturnRealTimeShadow(CRealTimeShadow* pShadow);
};

extern CRealTimeShadowManager& g_realTimeShadowMan;
