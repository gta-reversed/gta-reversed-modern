#include "StdInc.h"

#include "ShadowCamera.h"

void CShadowCamera::InjectHooks() {
    RH_ScopedClass(CShadowCamera);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(CShadowCamera, 0x7053F0, { .reversed = false }); // TODO: Constructor
    // RH_ScopedInstall(~CShadowCamera, 0x705B50);
    RH_ScopedInstall(Destroy, 0x705400, { .reversed = false });
    RH_ScopedInstall(SetFrustum, 0x7054C0);
    RH_ScopedInstall(SetLight, 0x705520);
    RH_ScopedInstall(SetCenter, 0x705590);
    RH_ScopedInstall(InvertRaster, 0x705660, { .reversed = false });
    RH_ScopedInstall(GetRwRenderRaster, 0x705770);
    RH_ScopedInstall(GetRwRenderTexture, 0x705780);
    RH_ScopedInstall(DrawOutlineBorder, 0x705790, { .reversed = false });
    RH_ScopedInstall(Create, 0x705B60, { .reversed = false });
    RH_ScopedOverloadedInstall(Update, "Clump", 0x705BF0, RwCamera*(CShadowCamera::*)(RpClump*), { .reversed = false });
    RH_ScopedOverloadedInstall(Update, "Atomic", 0x705C80, RwCamera * (CShadowCamera::*)(RpAtomic*), { .reversed = false });
    RH_ScopedInstall(MakeGradientRaster, 0x705D20, { .reversed = false });
    RH_ScopedInstall(RasterResample, 0x706070, { .reversed = false });
    RH_ScopedInstall(RasterBlur, 0x706170, { .reversed = false });
}

// 0x7053F0
CShadowCamera::CShadowCamera() {
    m_pRwCamera = nullptr;
    m_pRwRenderTexture = nullptr;
}

// 0x705B50
CShadowCamera::~CShadowCamera() {
    Destroy();
}

// 0x705400
void CShadowCamera::Destroy() {
    return plugin::CallMethod<0x705400, CShadowCamera*>(this);

    /*
    if (!m_pRwCamera)
        return;

    if (auto frame = RwCameraGetFrame(m_pRwCamera)) {
        rwObjectHasFrameSetFrame(&frame, nullptr); // bad
        RwFrameDestroy(frame);
    }

    if (auto* frameBuffer = GetRwRenderRaster()) {
        frameBuffer = nullptr; // TODO: BUG
        RwRasterDestroy(frameBuffer);
    }

    if (m_pRwRenderTexture) {
        RwTextureSetRaster(m_pRwRenderTexture, nullptr);
        RwTextureDestroy(m_pRwRenderTexture);
        m_pRwRenderTexture = nullptr;
    }

    RwCameraDestroy(m_pRwCamera);
    m_pRwCamera = nullptr;
    */
}

// 0x7054C0
void CShadowCamera::SetFrustum(float radius) {
    RwCameraSetFarClipPlane(m_pRwCamera, radius + radius);
    RwCameraSetNearClipPlane(m_pRwCamera, radius / 1000.0f);

    const CVector2D window(radius, radius);
    RwCameraSetViewWindow(m_pRwCamera, &window);
}

// 0x705520
void CShadowCamera::SetLight(RpLight* light) {
    auto* lightFrame  = RpLightGetFrame(light);
    auto* lightMatrix = RwFrameGetMatrix(lightFrame);
    auto* cameraFrame = RwCameraGetFrame(m_pRwCamera);
    cameraFrame->modelling.right = lightMatrix->right;
    cameraFrame->modelling.up = lightMatrix->up;
    cameraFrame->modelling.at = lightMatrix->at;
    RwMatrixUpdate(&cameraFrame->modelling);
    RwFrameUpdateObjects(cameraFrame);
}

// signature changed
// 0x705590
void CShadowCamera::SetCenter(const CVector& center) {
    auto frame = RwCameraGetFrame(m_pRwCamera);
    auto mat = RwFrameGetMatrix(frame);
    *RwMatrixGetPos(mat) = m_pRwCamera->farPlane / -2.0f * mat->at + center;
    RwMatrixUpdate(&frame->modelling);
    RwFrameUpdateObjects(frame);
    RwFrameOrthoNormalize(frame);
}

// 0x705660
void CShadowCamera::InvertRaster() {
    plugin::CallMethod<0x705660, CShadowCamera*>(this);
}

// 0x705770
RwRaster* CShadowCamera::GetRwRenderRaster() const {
    return RwCameraGetRaster(m_pRwCamera);
}

// 0x705780
RwTexture* CShadowCamera::GetRwRenderTexture() const {
    return m_pRwRenderTexture;
}

// 0x705790
RwRaster* CShadowCamera::DrawOutlineBorder(const RwRGBA& color) {
    return plugin::CallMethodAndReturn<RwRaster*, 0x705790, CShadowCamera*, const RwRGBA&>(this, color);
}

// 0x705B60
RwCamera* CShadowCamera::Create(int32 rasterSize) {
    return plugin::CallMethodAndReturn<RwCamera*, 0x705B60, CShadowCamera*, int32>(this, rasterSize);
}

// 0x705BF0
RwCamera* CShadowCamera::Update(RpClump* clump) {
    return plugin::CallMethodAndReturn<RwCamera*, 0x705BF0, CShadowCamera*, RpClump*>(this, clump);
}

// 0x705C80
RwCamera* CShadowCamera::Update(RpAtomic* atomic) {
    return plugin::CallMethodAndReturn<RwCamera*, 0x705C80, CShadowCamera*, RpAtomic*>(this, atomic);
}

// 0x705D20
void CShadowCamera::MakeGradientRaster() {
    plugin::CallMethod<0x705D20, CShadowCamera*>(this);
}

// 0x706070
RwRaster* CShadowCamera::RasterResample(RwRaster* raster) {
    return plugin::CallMethodAndReturn<RwRaster*, 0x706070, CShadowCamera*, RwRaster*>(this, raster);
}

// 0x706170
RwRaster* CShadowCamera::RasterBlur(RwRaster* raster, int32 numPasses) {
    return plugin::CallMethodAndReturn<RwRaster*, 0x706170, CShadowCamera*, RwRaster*, int32>(this, raster, numPasses);
}
