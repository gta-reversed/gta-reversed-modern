/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include <Base.h>
#include "RenderWare.h"

class CShadowCamera { // AKA CShadowImage
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

    /*!
    * @addr 0x705D20
    * @brief Make a monocolor intensity gardient
    * @return The camera the gardient was rendered on if successful, `nullptr` otherwise.
    */
    RwCamera*  MakeGradientRaster();

    RwImage*   CreateRwImage();
    RwRaster*  DrawBlurInRect(RwRect* rect);
    RwRaster*  RasterResample(RwRaster* raster);

    /*!
    * @addr 0x706170
    * @brief Render a blurry version of the camera's raster onto `blurRaster`
    * @return The camera's raster
    */
    RwRaster*  RasterBlur(RwRaster* blurRaster, int32 numPasses);

private:
    // NOTSA
    template<typename RenderFnT>
    void Update_Internal(RpAtomic* atomic, uint32 geoFlagsToClear, RenderFnT&& Render);
};
VALIDATE_SIZE(CShadowCamera, 0x8);
