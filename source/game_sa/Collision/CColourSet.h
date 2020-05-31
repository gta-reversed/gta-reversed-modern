/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class CColourSet {
public:
    float          m_fAmbientRed;
    float          m_fAmbientGreen;
    float          m_fAmbientBlue;
    float          m_fAmbientRed_Obj;
    float          m_fAmbientGreen_Obj;
    float          m_fAmbientBlue_Obj;
    float          m_fDirectionalRed;
    float          m_fDirectionalGreen;
    float          m_fDirectionalBlue;
    unsigned short m_nSkyTopRed;
    unsigned short m_nSkyTopGreen;
    unsigned short m_nSkyTopBlue;
    unsigned short m_nSkyBottomRed;
    unsigned short m_nSkyBottomGreen;
    unsigned short m_nSkyBottomBlue;
    unsigned short m_nSunCoreRed;
    unsigned short m_nSunCoreGreen;
    unsigned short m_nSunCoreBlue;
    unsigned short m_nSunCoronaRed;
    unsigned short m_nSunCoronaGreen;
    unsigned short m_nSunCoronaBlue;
    float          m_fSunSize;
    float          m_fSpriteSize;
    float          m_fSpriteBrightness;
    unsigned short m_nShadowStrength;
    unsigned short m_nLightShadowStrength;
    unsigned short m_nPoleShadowStrength;
    float          m_fFarClip;
    float          m_fFogStart;
    float          m_fLightsOnGroundBrightness;
    unsigned short m_nLowCloudsRed;
    unsigned short m_nLowCloudsGreen;
    unsigned short m_nLowCloudsBlue;
    unsigned short m_nFluffyCloudsBottomRed;
    unsigned short m_nFluffyCloudsBottomGreen;
    unsigned short m_nFluffyCloudsBottomBlue;
    float          m_fWaterRed;
    float          m_fWaterGreen;
    float          m_fWaterBlue;
    float          m_fWaterAlpha;
    float          m_fPostFx1Red;
    float          m_fPostFx1Green;
    float          m_fPostFx1Blue;
    float          m_fPostFx1Alpha;
    float          m_fPostFx2Red;
    float          m_fPostFx2Green;
    float          m_fPostFx2Blue;
    float          m_fPostFx2Alpha;
    float          m_fCloudAlpha;
    unsigned int   m_nHighLightMinIntensity;
    unsigned short m_nWaterFogAlpha;
    float          m_fIllumination;
    float          m_fLodDistMult;

    //funcs
    CColourSet(int weatherId, int timeId);
    void Interpolate(CColourSet* a, CColourSet* b, float factor_a, float factor_b, bool bIgnoreSky);
};

VALIDATE_SIZE(CColourSet, 0xAC);
