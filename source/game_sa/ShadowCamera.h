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

    CShadowCamera();
    ~CShadowCamera();

    void       CreateTexture();
    RwCamera*  SetFrustum(float viewWindow);
    RwCamera*  SetLight(RpLight* light);
    RwCamera*  SetCenter(RwV3d* center);
    void       InvertRaster();
    RwRaster*  GetRwRenderRaster();
    RwTexture* GetRwRenderTexture();
    RwRaster*  DrawOutlineBorder(const RwRGBA& color);
    RwCamera*  Create(int32 rasterSize);
    RwCamera*  Update(RpClump* object);
    RwCamera*  Update(RpAtomic* object);
    void       MakeGradientRaster();
    RwImage*   CreateRwImage();
    RwRaster*  DrawBlurInRect(RwRect* rect);
    void       RasterResample(RwRaster* raster);
    void       RasterBlur(RwRaster* raster, int32 numPasses);
};

VALIDATE_SIZE(CShadowCamera, 8);