#include "StdInc.h"
#include "RealTimeShadow.h"

void CRealTimeShadow::InjectHooks() {
    RH_ScopedClass(CRealTimeShadow);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Constructor, 0x706410);
    RH_ScopedInstall(Destructor, 0x706440);

    RH_ScopedInstall(SetLightProperties, 0x705900);
    RH_ScopedInstall(GetShadowRwTexture, 0x7059F0, {.reversed = false});
    RH_ScopedInstall(DrawBorderAroundTexture, 0x705A00, {.reversed = false});
    RH_ScopedInstall(Create, 0x706460, {.reversed = false});
    RH_ScopedInstall(Update, 0x706600, { .reversed = false });
    RH_ScopedInstall(Destroy, 0x705990);
}

CRealTimeShadow::~CRealTimeShadow() {
    Destroy();
}

// 0x705900
RwFrame* CRealTimeShadow::SetLightProperties(float angle, float, bool doSetCamLight) {
    if (const auto frame = RpLightGetFrame(m_pLight)) {
        const RwV3d xaxis{ 0.f, 1.f, 0.f };
        RwFrameRotate(frame, &xaxis, angle, rwCOMBINEREPLACE);

        const RwV3d yaxis{ 1.f, 0.f, 0.f };
        RwFrameRotate(frame, &yaxis, angle, rwCOMBINEPOSTCONCAT);

        if (doSetCamLight) {
            m_camera.SetLight(m_pLight);
        }

        return frame;
    }
    return nullptr;
}

// 0x7059F0
RwTexture* CRealTimeShadow::GetShadowRwTexture() {
    return plugin::CallMethodAndReturn<RwTexture*, 0x7059F0, CRealTimeShadow*>(this);
}

// 0x705990
void CRealTimeShadow::Destroy() {
    m_pOwner = nullptr;
    m_nRwObjectType = (uint32)-1;
    if (m_pLight) {
        // This is so convoluted... Do we actually have to do it like this? Wouldnt a simple `RwFrameDestroy(RpLightGetFrame(m_pLight))` work?
        const auto frame = RpLightGetFrame(m_pLight);
        rwObjectHasFrameSetFrame(m_pLight, nullptr);
        RwFrameDestroy(frame);

        RpLightDestroy(m_pLight);

        m_pLight = nullptr;
    }
}

// 0x705A00
void CRealTimeShadow::DrawBorderAroundTexture(RwRGBA const& color) {
    return plugin::CallMethodAndReturn<void, 0x705A00, CRealTimeShadow*, RwRGBA const&>(this, color);
}

// 0x706460
bool CRealTimeShadow::Create(bool isBlurred, int32 blurPasses, bool drawMoreBlur) {
    return plugin::CallMethodAndReturn<bool, 0x706460, CRealTimeShadow*, bool, int32, bool>(this, isBlurred, blurPasses, drawMoreBlur);
}

// 0x706600
RwTexture* CRealTimeShadow::Update() {
    return plugin::CallMethodAndReturn<RwTexture*, 0x706600, CRealTimeShadow*>(this);
}
