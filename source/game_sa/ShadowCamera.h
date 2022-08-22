/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RenderWare.h"

class CShadowCamera {
public:
    RwCamera*  m_pRwCamera;
    RwTexture* m_pRwRenderTexture;

public:
    static void InjectHooks();

    CShadowCamera();
    ~CShadowCamera();

    void       Destroy();
    void       CreateTexture();
    void       SetFrustum(float viewWindow);
    void       SetLight(RpLight* light);
    void       SetCenter(const CVector& center);
    void       InvertRaster();
    RwRaster*  GetRwRenderRaster() const;
    RwTexture* GetRwRenderTexture() const;
    RwRaster*  DrawOutlineBorder(const RwRGBA& color);
    RwCamera*  Create(int32 rasterSize);
    RwCamera*  Update(RpClump* clump);
    RwCamera*  Update(RpAtomic* atomic);
    void       MakeGradientRaster();
    RwImage*   CreateRwImage();
    RwRaster*  DrawBlurInRect(RwRect* rect);
    RwRaster*  RasterResample(RwRaster* raster);
    RwRaster*  RasterBlur(RwRaster* raster, int32 numPasses);
};
VALIDATE_SIZE(CShadowCamera, 0x8);
