#include "StdInc.h"

#include "ShadowCamera.h"

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

/*!
* @addr 0x705660
* @brief Render an inverted color version of the camera's raster onto itself
*/
void CShadowCamera::InvertRaster() {
    const auto& raster = GetRwRenderRaster();
    const auto  width = (float)RwRasterGetWidth(raster), height = (float)RwRasterGetHeight(raster);

    // Helper to construct vertices used here
    const auto MkVert = [rhw = 1.f / RwCameraGetNearClipPlane(m_pRwCamera)](float x, float y) {
        return RwIm2DVertex{
            .x = x,
            .y = y,
            .z = RwIm2DGetNearScreenZ(),

            .rhw = rhw,

            .emissiveColor = 0xFFFFFFFF
        };
    };

    RwIm2DVertex vertices[]{
        MkVert(0.f,   0.f),    // Top left
        MkVert(0.f,   height), // Bottom left
        MkVert(width, 0.f),    // Top right
        MkVert(width, height), // Bottom right
    };

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, RWRSTATE(rwBLENDINVDESTCOLOR));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDZERO));

    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, std::size(vertices));

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND, RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDINVSRCALPHA));
}

// 0x705770
RwRaster* CShadowCamera::GetRwRenderRaster() const {
    return RwCameraGetRaster(m_pRwCamera);
}

// 0x705780
RwTexture* CShadowCamera::GetRwRenderTexture() const {
    return m_pRwRenderTexture;
}

/*!
* @addr 0x705790
* @brief Draw a 1px wide outline on the edges of the camera's rastrer
* @return The raster the outline was rendered to
*/
RwRaster* CShadowCamera::DrawOutlineBorder(const RwRGBA& color) {
    // Helper to construct vertices used here
    const auto MkVert = [
        rhw   = 1.f / RwCameraGetNearClipPlane(m_pRwCamera),
        color = CRGBA(color).ToIntARGB() // Same shit, different packaging
    ](float x, float y) {
        return RwIm2DVertex{
            .x = x,
            .y = y,
            .z = RwIm2DGetNearScreenZ(),

            .rhw = rhw,

            .emissiveColor = color
        };
    };

    // NOTE: Code seemingly assumes the aspect ratio of the image is 1:1
    const auto w = RwRasterGetWidth(GetRwRenderRaster()) - 1.f;
    RwIm2DVertex vertices[]{
        MkVert(0.f, 0.f),
        MkVert(w,   0.f),
        MkVert(w,   w),
        MkVert(0.f, w),
    };

    if (RwCameraBeginUpdate(m_pRwCamera)) {
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(0));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(0));
        RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(0));

        RwImVertexIndex indices[]{0, 1, 2, 3, 0};
        RwIm2DRenderIndexedPrimitive(rwPRIMTYPEPOLYLINE, vertices, std::size(vertices), indices, std::size(indices));

        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(1u));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(1u));

        RwCameraEndUpdate(m_pRwCamera);
    }

    return GetRwRenderRaster();
}

/*!
* @addr 0x705B60
* @brief Create camera and render texture
* @param rasterSizePower Size of the raster, final size in pixels will be `pow(2, rasterSizePower)`
* @return The camera created
*/
RwCamera* CShadowCamera::Create(int32 rasterSizePower) {
    const auto rasterSizeInPx = 1 << rasterSizePower; // Size of raster in pixels. Same as `pow(2, rasterSize)`

    if (m_pRwCamera = RwCameraCreate()) {
        if (const auto frame = RwFrameCreate()) {
            rwObjectHasFrameSetFrame(m_pRwCamera, frame);
            if (RwCameraGetFrame(m_pRwCamera)) {
                if (const auto raster = RwRasterCreate(rasterSizeInPx, rasterSizeInPx, 0, rwRASTERTYPECAMERATEXTURE)) {
                    RwCameraSetRaster(m_pRwCamera, raster);
                    if (m_pRwRenderTexture = RwTextureCreate(raster)) {
                        RwTextureSetAddressing(m_pRwRenderTexture, rwFILTERMIPNEAREST | rwFILTERMIPNEAREST);
                        RwTextureSetFilterMode(m_pRwRenderTexture, rwFILTERLINEAR);

                        RwCameraSetProjection(m_pRwCamera, rwPARALLEL);

                        // Success
                        return m_pRwCamera;
                    }
                }
            }
        }
    }

    // Fail
    Destroy();
    return nullptr;
}

/*!
* @addr 0x705620
* @brief Render the atomic using the default render callback
*
* @param          atomic The atomic to render
* @param [unused] data
*
* @return The `atomic`
*
* Used in 3-4 places, but (mostly) inlined in the final exe
*/
RpAtomic* atomicQuickRender(RpAtomic* atomic, void* data) {
    UNUSED(data);

    // Save original callback
    const auto origcb = RpAtomicGetRenderCallBack(atomic);

    // Set default callback
    RpAtomicSetRenderCallBack(atomic, &AtomicDefaultRenderCallBack);

    // NOTSA: Omitting useless `if` - It's condition always evals to `false` - Perhaps BUG?

    // Render using default
    AtomicDefaultRenderCallBack(atomic);

    // Set original (if not null) or use default
    RpAtomicSetRenderCallBack(atomic, origcb ? origcb : &AtomicDefaultRenderCallBack);

    return atomic;
}

/*!
* @notsa
* @brief Internal function to render to reduce copy-paste code
*
* @param geo             The geometry to be rendered
* @param geoFlagsToClear Flags to clear from geometry for rendering this time (all flags will be restored afterwards)
* @param Render          The function that should render everything necessary
*/
template<typename RenderFnT>
void CShadowCamera::Update_Internal(RpAtomic* atomic, uint32 geoFlagsToClear, RenderFnT&& Render) {
    // Clear camera raster to be transparent
    RwRGBA color(0xFF, 0xFF, 0xFF, 0);
    RwCameraClear(m_pRwCamera, &color, rwCAMERACLEARZ | rwCAMERACLEARIMAGE);

    // Now update camera
    if (RwCameraBeginUpdate(m_pRwCamera)) {
        const auto geo = RpAtomicGetGeometry(atomic);

        // Save original flags
        const auto ogflags = RpGeometryGetFlags(geo);

        // Clear some for this render pass (optimization)
        RpGeometrySetFlags(geo, ogflags & ~geoFlagsToClear);

        // Render
        Render();

        // Restore flags
        RpGeometrySetFlags(geo, ogflags);

        // Render the camera's current raster, but inverted
        // This is basically the shadow (I think)
        InvertRaster();

        // Finish update
        RwCameraEndUpdate(m_pRwCamera);
    }
}

/*!
* @addr  0x705BF0
* @brief Render a clump and all its atomics
*/
RwCamera* CShadowCamera::Update(RpClump* clump) {
    Update_Internal(
        GetFirstAtomic(clump), // Not quite sure... They render all atomics, but only modify the first atomics geometry's flags? Why not render all atomics separately?
        rpGEOMETRYTEXTURED | rpGEOMETRYPRELIT | rpGEOMETRYLIGHT | rpGEOMETRYMODULATEMATERIALCOLOR | rpGEOMETRYTEXTURED2,
        [&] { RpClumpForAllAtomics(clump, &atomicQuickRender, nullptr); }
    );

    return m_pRwCamera;
}

/*!
* @addr 0x705C80
* @brief Render an atomic
*/
RwCamera* CShadowCamera::Update(RpAtomic* atomic) {
    Update_Internal(
        atomic,
        rpGEOMETRYTEXTURED | rpGEOMETRYPRELIT | rpGEOMETRYNORMALS | rpGEOMETRYLIGHT | rpGEOMETRYMODULATEMATERIALCOLOR | rpGEOMETRYTEXTURED2,
        [&] { atomicQuickRender(atomic, nullptr); }
    );

    return m_pRwCamera;
}

// 0x705D20
RwCamera* CShadowCamera::MakeGradientRaster() {
    // Monocolor intensity of the gardient
    constexpr float MIN_COLOR_INTENSITY{ 64.f }, MAX_COLOR_INTENSITY{ 128.f };

    if (!m_pRwCamera) {
        return nullptr;
    }

    const auto& raster = GetRwRenderRaster();
    const auto  width  = RwRasterGetWidth(raster), height = RwRasterGetHeight(raster);

    // Raster too small, do nothing (Assumes aspect ratio is 1:1)
    if (height < 1) {
        return nullptr;
    }

    if (!RwCameraBeginUpdate(m_pRwCamera)) {
        return nullptr;
    }

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDZERO));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDINVDESTCOLOR));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,         RWRSTATE(rwSHADEMODEFLAT));

    // Draw lines along the X axis while moving along the Y axis from top to bottom.
    // Each line is less and less intense in color
    {
        const auto cistep = (MIN_COLOR_INTENSITY - MAX_COLOR_INTENSITY) / (float)height; // Color intensity step each iteration
        float      cicurr = MAX_COLOR_INTENSITY; // Current color intensity

        const auto nscrz  = RwIm2DGetNearScreenZ();

        for (auto y{0}; y < height; y++, cicurr += cistep) {
            const auto MkVert = [
                &,
                rhw = 1.f / RwCameraGetNearClipPlane(m_pRwCamera),
                cc  = (uint8)cicurr
            ] (float x) {
                return RwIm2DVertex{
                    .x = x,
                    .y = (float)y,
                    .z = nscrz,

                    .rhw = rhw,

                    .emissiveColor = RWRGBALONG(cc, cc, cc, cc)
                };
            };

            RwIm2DVertex vertices[2]{
                MkVert(0.f),
                MkVert((float)(width - 1)),
            };
        
            RwIm2DRenderLine(vertices, std::size(vertices), 0, 1);
        }
    }

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,   RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,    RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,   RWRSTATE(rwSHADEMODEGOURAUD));

    RwCameraEndUpdate(m_pRwCamera);

    return m_pRwCamera;
}

bool Im2DRenderQuad(RwReal x1, RwReal y1, RwReal x2, RwReal y2, RwReal z, RwReal recipCamZ, RwReal uvOffset) {
    const auto MkVert = [=] (float x, float y, float u, float v) {
        return RwIm2DVertex{
            .x = x,
            .y = y,
            .z = z,

            .rhw = recipCamZ,

            .emissiveColor = 0xFFFFFFFF,

            .u = u,
            .v = v
        };
    };

    RwIm2DVertex vertices[]{
        MkVert(x1, y1, uvOffset,       uvOffset      ),
        MkVert(x1, y2, uvOffset,       uvOffset + 1.0),
        MkVert(x2, y1, uvOffset + 1.0, uvOffset      ),
        MkVert(x2, y2, uvOffset + 1.0, uvOffset + 1.0),
    };

    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertices, std::size(vertices));

    return true;
}

// 0x706070
RwRaster* CShadowCamera::RasterResample(RwRaster* sourceRaster) {
    if (!m_pRwCamera) {
        return nullptr;
    }

    if (!RwCameraBeginUpdate(m_pRwCamera)) {
        return nullptr;
    }

    RwRenderStateSet(rwRENDERSTATESRCBLEND,      RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,     RWRSTATE(rwBLENDZERO));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,   RWRSTATE(0));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(sourceRaster));

    const auto size = RwRasterGetWidth(sourceRaster);
    Im2DRenderQuad(
        0.f,          0.f,
        (RwReal)size, (RwReal)size,
        RwIm2DGetNearScreenZ(),
        1.f / RwCameraGetNearClipPlane(m_pRwCamera),
        0.5f / size
    );

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,    RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,   RWRSTATE(rwBLENDINVSRCALPHA));

    RwCameraEndUpdate(m_pRwCamera);

    return GetRwRenderRaster();
}

// 0x706170
RwRaster* CShadowCamera::RasterBlur(RwRaster* blurRaster, int32 numPasses) {
    if (!m_pRwCamera) {
        return nullptr;
    }

    const auto camRaster = RwCameraGetRaster(m_pRwCamera);

    if (!numPasses) { // NOTSA
        return camRaster;
    }

    const auto DoRenderQuad2D = [
        size = RwRasterGetWidth(blurRaster),
        rhw = 1.f / RwCameraGetNearClipPlane(m_pRwCamera)
    ] (float uv) {
        Im2DRenderQuad(
            0.f, 0.f,
            (RwReal)size, (RwReal)size,
            RwIm2DGetNearScreenZ(),
            rhw,
            uv / size
        );
    };

    for (auto i{ 0 }; i < numPasses; i++) {
        if (RwCameraBeginUpdate(m_pRwCamera)) {
            if (i == 0) { // First pass
                RwRenderStateSet(rwRENDERSTATESRCBLEND, RWRSTATE(rwBLENDONE));
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDZERO));
                RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(FALSE));
                RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, RWRSTATE(rwFILTERLINEAR));
            }
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(blurRaster));

            DoRenderQuad2D(0.5f + 0.5f);

            RwCameraEndUpdate(m_pRwCamera);
        }

        // Swap raster
        RwCameraSetRaster(m_pRwCamera, blurRaster);

        if (RwCameraBeginUpdate(m_pRwCamera)) {
            RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(camRaster));

            DoRenderQuad2D(0.5f - 0.5f);

            if (i == numPasses - 1) { // LastPass (pun intended)
                RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(TRUE));
                RwRenderStateSet(rwRENDERSTATESRCBLEND, RWRSTATE(rwBLENDSRCALPHA));
                RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDINVSRCALPHA));
            }

            RwCameraEndUpdate(m_pRwCamera);
        }

        // Swap raster back to original
        RwCameraSetRaster(m_pRwCamera, camRaster);
    }

    return camRaster;
}

void CShadowCamera::InjectHooks() {
    RH_ScopedClass(CShadowCamera);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(CShadowCamera, 0x7053F0, { .reversed = false }); // TODO: Constructor
    // RH_ScopedInstall(~CShadowCamera, 0x705B50);
    RH_ScopedInstall(Destroy, 0x705400, { .reversed = false });
    RH_ScopedInstall(SetFrustum, 0x7054C0);
    RH_ScopedInstall(SetLight, 0x705520);
    RH_ScopedInstall(SetCenter, 0x705590);
    RH_ScopedInstall(InvertRaster, 0x705660);
    RH_ScopedInstall(GetRwRenderRaster, 0x705770);
    RH_ScopedInstall(GetRwRenderTexture, 0x705780);
    RH_ScopedInstall(DrawOutlineBorder, 0x705790);
    RH_ScopedInstall(Create, 0x705B60);
    RH_ScopedOverloadedInstall(Update, "Clump", 0x705BF0, RwCamera * (CShadowCamera::*)(RpClump*));
    RH_ScopedOverloadedInstall(Update, "Atomic", 0x705C80, RwCamera * (CShadowCamera::*)(RpAtomic*));
    RH_ScopedInstall(MakeGradientRaster, 0x705D20);
    RH_ScopedInstall(RasterResample, 0x706070);
    RH_ScopedInstall(RasterBlur, 0x706170);

    RH_ScopedGlobalInstall(atomicQuickRender, 0x705620);
    RH_ScopedGlobalInstall(Im2DRenderQuad, 0x705A20);
}
