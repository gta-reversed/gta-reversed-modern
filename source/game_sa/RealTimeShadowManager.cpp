#include "StdInc.h"

#include "RealTimeShadowManager.h"

CRealTimeShadowManager& g_realTimeShadowMan = *(CRealTimeShadowManager*)0xC40350;

void CRealTimeShadowManager::InjectHooks() {
    RH_ScopedClass(CRealTimeShadowManager);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Init, 0x7067C0);
    RH_ScopedInstall(ReturnRealTimeShadow, 0x705B30);
    RH_ScopedInstall(GetRealTimeShadow, 0x706970, { .reversed = false });
    RH_ScopedInstall(Update, 0x706AB0, { .reversed = false });
    RH_ScopedInstall(DoShadowThisFrame, 0x706BA0);
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

    m_GradientCamera[0].Create(6);
    m_GradientCamera[0].MakeGradientRaster();

    m_bInitialised = true;
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
    plugin::CallMethod<0x706AB0, CRealTimeShadowManager*>(this);
}

CRealTimeShadow& CRealTimeShadowManager::GetRealTimeShadow(CPhysical* physical) {
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
        shdw->m_bCreated = true;
    } else {
        (void)GetRealTimeShadow(physical); // ???
    }
}
