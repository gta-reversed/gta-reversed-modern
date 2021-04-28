/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CColourSet.h"
#include "CBox.h"

class CTimeCycleBox;

class CTimeCycle {
public:
    static float& m_BrightnessAddedToAmbientBlue;
    static float& m_BrightnessAddedToAmbientGreen;
    static float& m_BrightnessAddedToAmbientRed;

    static int& m_ExtraColourInter;
    static int& m_ExtraColourWeatherType;
    static int& m_ExtraColour;

    static int& m_FogReduction;

    static float* m_fShadowDisplacementY;               // m_fShadowDisplacementY[16]
    static float* m_fShadowDisplacementX;               // m_fShadowDisplacementX[16]
    static float* m_fShadowSideY;                       // m_fShadowSideY[16]
    static float* m_fShadowSideX;                       // m_fShadowSideX[16]
    static float* m_fShadowFrontY;                      // m_fShadowFrontY[16]
    static float* m_fShadowFrontX;                      // m_fShadowFrontX[16]

    static int& m_CurrentStoredValue;

    static unsigned char* m_nDirectionalMult;           // m_nDirectionalMult[184]
    static unsigned char* m_nWaterFogAlpha;             // m_nWaterFogAlpha[184]
    static unsigned char* m_nHighLightMinIntensity;     // m_nHighLightMinIntensity[184]
    static unsigned char* m_fCloudAlpha;                // m_fCloudAlpha[184]

    static unsigned char* m_fPostFx2Alpha;              // m_fPostFx2Alpha[184]
    static unsigned char* m_fPostFx2Blue;               // m_fPostFx2Blue[184]
    static unsigned char* m_fPostFx2Green;              // m_fPostFx2Green[184]
    static unsigned char* m_fPostFx2Red;                // m_fPostFx2Red[184]
    static unsigned char* m_fPostFx1Alpha;              // m_fPostFx1Alpha[184]
    static unsigned char* m_fPostFx1Blue;               // m_fPostFx1Blue[184]
    static unsigned char* m_fPostFx1Green;              // m_fPostFx1Green[184]
    static unsigned char* m_fPostFx1Red;                // m_fPostFx1Red[184]

    static unsigned char* m_fWaterAlpha;                // m_fWaterAlpha[184]
    static unsigned char* m_fWaterBlue;                 // m_fWaterBlue[184]
    static unsigned char* m_fWaterGreen;                // m_fWaterGreen[184]
    static unsigned char* m_fWaterRed;                  // m_fWaterRed[184]

    static unsigned char* m_nFluffyCloudsBottomBlue;    // m_nFluffyCloudsBottomBlue[184]
    static unsigned char* m_nFluffyCloudsBottomGreen;   // m_nFluffyCloudsBottomGreen[184]
    static unsigned char* m_nFluffyCloudsBottomRed;     // m_nFluffyCloudsBottomRed[184]

    static unsigned char* m_nLowCloudsBlue;             // m_nLowCloudsBlue[184]
    static unsigned char* m_nLowCloudsGreen;            // m_nLowCloudsGreen[184]
    static unsigned char* m_nLowCloudsRed;              // m_nLowCloudsRed[184]

    static unsigned char* m_fLightsOnGroundBrightness;  // m_fLightsOnGroundBrightness[184]
    static signed short* m_fFogStart;                   // m_fFogStart[184]
    static signed short* m_fFarClip;                    // m_fFarClip[184]
    static unsigned char* m_nPoleShadowStrength;        // m_nPoleShadowStrength[184]
    static unsigned char* m_nLightShadowStrength;       // m_nLightShadowStrength[184]
    static unsigned char* m_nShadowStrength;            // m_nShadowStrength[184]
    static char* m_fSpriteBrightness;                   // m_fSpriteBrightness[184]
    static char* m_fSpriteSize;                         // m_fSpriteSize[184]
    static char* m_fSunSize;                            // m_fSunSize[184]

    static unsigned char* m_nSunCoronaBlue;             // m_nSunCoronaBlue[184]
    static unsigned char* m_nSunCoronaGreen;            // m_nSunCoronaGreen[184]
    static unsigned char* m_nSunCoronaRed;              // m_nSunCoronaRed[184]
    static unsigned char* m_nSunCoreBlue;               // m_nSunCoreBlue[184]
    static unsigned char* m_nSunCoreGreen;              // m_nSunCoreGreen[184]
    static unsigned char* m_nSunCoreRed;                // m_nSunCoreRed[184]

    static unsigned char* m_nSkyBottomBlue;             // m_nSkyBottomBlue[184]
    static unsigned char* m_nSkyBottomGreen;            // m_nSkyBottomGreen[184]
    static unsigned char* m_nSkyBottomRed;              // m_nSkyBottomRed[184]
    static unsigned char* m_nSkyTopBlue;                // m_nSkyTopBlue[45]
    static unsigned char* m_nSkyTopGreen;               // m_nSkyTopGreen[45]
    static unsigned char* m_nSkyTopRed;                 // m_nSkyTopRed[45]

    static unsigned char* m_nAmbientBlue_Obj;           // m_nAmbientBlue_Obj[184]
    static unsigned char* m_nAmbientGreen_Obj;          // m_nAmbientGreen_Obj[184]
    static unsigned char* m_nAmbientRed_Obj;            // m_nAmbientRed_Obj[184]
    static unsigned char* m_nAmbientBlue;               // m_nAmbientBlue[184]
    static unsigned char* m_nAmbientGreen;              // m_nAmbientGreen[184]
    static unsigned char* m_nAmbientRed;                // m_nAmbientRed[184]

    static unsigned int& m_NumBoxes;
    static unsigned int& m_bExtraColourOn;
    static CColourSet& m_CurrentColours;

    static float& m_fCurrentRGB1Red;
    static float& m_fCurrentRGB1Green;
    static float& m_fCurrentRGB1Blue;
    static float& m_fCurrentRGB2Red;
    static float& m_fCurrentRGB2Green;
    static float& m_fCurrentRGB2Blue;

    static CTimeCycleBox* m_aBoxes; // m_aBoxes[20]
    static CVector* m_VectorToSun;  // m_VectorToSun[16]
    static RwRGBA& m_BelowHorizonGrey;
    static RwV3d& m_vecDirnLightToSun;

public:
    static void InjectHooks();

    static void AddOne(CBox& box, short farClip, int extraColor, float strength, float falloff, float lodDistMult);
    static void CalcColoursForPoint(CVector point, CColourSet* pCurrentColourSet);
    static float FindFarClipForCoors(CVector cameraPos);
    static void FindTimeCycleBox(CVector pos, CTimeCycleBox** outbox, float* interpolation, bool bCheckLod, bool bCheckFar, CTimeCycleBox* exclude);
    static float GetAmbientBlue();
    static float GetAmbientBlue_BeforeBrightness();
    static float GetAmbientBlue_Obj();
    static float GetAmbientGreen();
    static float GetAmbientGreen_BeforeBrightness();
    static float GetAmbientGreen_Obj();
    static float GetAmbientRed();
    static float GetAmbientRed_BeforeBrightness();
    static float GetAmbientRed_Obj();
    static void InitForRestart();
    static void Initialise();
    static void SetConstantParametersForPostFX();
    static void Shutdown();
    static void StartExtraColour(int colour, bool bNoExtraColorInterior);
    static void StopExtraColour(bool bNoExtraColorInterior);
    static void Update();
};
