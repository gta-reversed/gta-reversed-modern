#include "StdInc.h"

#include "RealTimeShadowManager.h"
#include "Shadows.h"

CRealTimeShadowManager& g_realTimeShadowMan = *(CRealTimeShadowManager*)0xC40350;

void CRealTimeShadowManager::InjectHooks() {
    RH_ScopedClass(CRealTimeShadowManager);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Init, 0x7067C0);
    RH_ScopedInstall(ReturnRealTimeShadow, 0x705B30);
    RH_ScopedInstall(GetRealTimeShadow, 0x706970, { .reversed = false });
    RH_ScopedInstall(Update, 0x706AB0, { .reversed = false });
    RH_ScopedInstall(DoShadowThisFrame, 0x706BA0);
    RH_ScopedInstall(Exit, 0x706A60);
}

// 0x7067C0
void CRealTimeShadowManager::Init() {
    if (m_bInitialised) {
        return;
    }

    for (auto& shdw : m_apShadows) {
        shdw = new CRealTimeShadow();
        shdw->Create(true, 4, true);
    }

    m_BlurCamera.Create(6);

    m_GradientCamera.Create(6);
    m_GradientCamera.MakeGradientRaster();

    m_bInitialised = true;
}

// 0x706A60
void CRealTimeShadowManager::Exit() {
    if (!m_bInitialised) {
        return;
    }

    for (auto& shdw : m_apShadows) {
        if (const auto owner = shdw->m_pOwner) {
            delete shdw; // `shdw->m_pOwner` nulled out by this
            delete owner; // Why?
        }
    }

    // Nice hack
    m_BlurCamera.~CShadowCamera();
    m_GradientCamera.~CShadowCamera();

    m_bInitialised = false;
}

void CRealTimeShadowManager::ReturnRealTimeShadow(CRealTimeShadow* shdw) {
    if (m_bInitialised) {
        shdw->m_pOwner->m_pShadowData = nullptr;
        shdw->m_pOwner = nullptr;
    }
}

void CRealTimeShadowManager::ReInit() {
    plugin::CallMethod<0x706870, CRealTimeShadowManager*>(this);
}

void CRealTimeShadowManager::Update() {
    if (m_bInitialised && m_bNeedsReinit) {
        ReInit();
        m_bNeedsReinit = false;
    }

    for (auto& shdw : m_apShadows) {
        if (!shdw->m_pOwner) {
            continue;
        }

        // 0x305eed - 0x305f0f: Update intensity
        constexpr auto INTENSITY_STEP = 3;
        if (shdw->m_bKeepAlive) {
            shdw->m_nIntensity = std::min(100, shdw->m_nIntensity + INTENSITY_STEP);
        } else { // Fade out
            if (shdw->m_nIntensity >= INTENSITY_STEP) {
                shdw->m_nIntensity -= INTENSITY_STEP;
            } else {
                shdw->m_nIntensity = 0; // Avoid underflow
            }
        }

        if (shdw->m_nIntensity) {
            shdw->Update();
            CShadows::StoreRealTimeShadow(
                shdw->m_pOwner,
                CTimeCycle::m_fShadowDisplacementX[CTimeCycle::m_CurrentStoredValue],
                CTimeCycle::m_fShadowDisplacementY[CTimeCycle::m_CurrentStoredValue],
                CTimeCycle::m_fShadowFrontX[CTimeCycle::m_CurrentStoredValue],
                CTimeCycle::m_fShadowFrontY[CTimeCycle::m_CurrentStoredValue],
                CTimeCycle::m_fShadowSideX[CTimeCycle::m_CurrentStoredValue],
                CTimeCycle::m_fShadowSideY[CTimeCycle::m_CurrentStoredValue]
            );
        } else if (m_bInitialised) {
            shdw->m_pOwner->m_pShadowData = nullptr;
            shdw->m_pOwner = nullptr;
        }
    }

    // TODO: ??? - Perhaps debug code left accidentally in?
    for (auto& shdw : m_apShadows) {
        shdw->m_bKeepAlive = false;
    }
}

CRealTimeShadow& CRealTimeShadowManager::GetRealTimeShadow(CPhysical* physical) {
    return plugin::CallMethodAndReturn<CRealTimeShadow&, 0x706970, CRealTimeShadowManager*, CPhysical*>(this, physical);
    /*
    * Unfinished
    if (m_bInitialised) {
        return;
    }

    bool isFirstPlayer{};

    if (!physical->IsPed() || physical->AsPed()->IsPlayer()) {
        if (FindPlayerPed()->IsInVehicle()) { // Maybe wrong?
            if (FindPlayerPed()->m_pVehicle->GetMoveSpeed().SquaredMagnitude() < sq(0.3f)) {
                return;
            }
        }
    }
    */
}

void CRealTimeShadowManager::DoShadowThisFrame(CPhysical* physical) {
    switch (g_fx.GetFxQuality()) {
    case 3: // Always render
        break;
    case 2: { // Only draw for main player
        if (physical->IsPed()) {
            if (physical->AsPed()->m_nPedType == PED_TYPE_PLAYER1) {
                break;
            }
        }
        return;
    }
    default: // For any other quality: skip
        return;
    }

    if (const auto shdw = physical->m_pShadowData) {
        shdw->m_bKeepAlive = true;
    } else {
        (void)GetRealTimeShadow(physical); // ???
    }
}
