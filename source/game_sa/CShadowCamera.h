/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"

class  CShadowCamera
{
public:
	RwCamera *m_pRwCamera;
	RwTexture *m_pRwRenderTexture;

	CShadowCamera();
	~CShadowCamera();

	void CreateTexture();
	RwCamera *SetFrustum(float viewWindow);
	RwCamera *SetLight(RpLight *light);
	RwCamera *SetCenter(RwV3d *center);
	void InvertRaster();
	RwRaster *GetRwRenderRaster();
	RwTexture *GetRwRenderTexture();
	RwRaster *DrawOutlineBorder(RwRGBA  const& color);
	RwCamera *Create(int rasterSize);
	RwCamera *Update(RpClump *object);
	RwCamera *Update(RpAtomic *object);
	void MakeGradientRaster();
	RwImage *CreateRwImage();
	RwRaster *DrawBlurInRect(RwRect *rect);
	void RasterResample(RwRaster *raster);
	void RasterBlur(RwRaster *raster, int numPasses);
};


VALIDATE_SIZE(CShadowCamera, 8);