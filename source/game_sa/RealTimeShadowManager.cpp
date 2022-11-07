#include "StdInc.h"

#include "RealTimeShadowManager.h"

CRealTimeShadowManager& g_realTimeShadowMan = *(CRealTimeShadowManager*)0xC40350;

void CRealTimeShadowManager::InjectHooks() {
    RH_ScopedClass(CRealTimeShadowManager);
    RH_ScopedCategoryGlobal(); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Init, 0x7067C0);
    RH_ScopedInstall(ReturnRealTimeShadow, 0x705B30, { .reversed = false });
    RH_ScopedInstall(GetRealTimeShadow, 0x706970, { .reversed = false });
    RH_ScopedInstall(Update, 0x706AB0, { .reversed = false });
    RH_ScopedInstall(DoShadowThisFrame, 0x706BA0, { .reversed = false });
}

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

void CRealTimeShadowManager::Exit() {
    plugin::CallMethod<0x706A60, CRealTimeShadowManager*>(this);
}

void CRealTimeShadowManager::ReInit() {
    plugin::CallMethod<0x706870, CRealTimeShadowManager*>(this);
}

void CRealTimeShadowManager::Update() {
    plugin::CallMethod<0x706AB0, CRealTimeShadowManager*>(this);
}

CRealTimeShadow& CRealTimeShadowManager::GetRealTimeShadow(CPhysical* physical) {
    return plugin::CallMethodAndReturn<CRealTimeShadow&, 0x706970, CRealTimeShadowManager*, CPhysical*>(this, physical);
}

void CRealTimeShadowManager::DoShadowThisFrame(CPhysical* physical) {
    plugin::CallMethod<0x706BA0, CRealTimeShadowManager*, CPhysical*>(this, physical);
}

void CRealTimeShadowManager::ReturnRealTimeShadow(CRealTimeShadow* pShadow) {
    plugin::CallMethod<0x705B30, CRealTimeShadowManager*, CRealTimeShadow*>(this, pShadow);
}
