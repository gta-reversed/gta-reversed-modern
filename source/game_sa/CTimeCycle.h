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

    static int32& m_ExtraColourInter;
    static int32& m_ExtraColourWeatherType;
    static int32& m_ExtraColour;

    static int32& m_FogReduction;

    static float* m_fShadowDisplacementY;               // m_fShadowDisplacementY[16]
    static float* m_fShadowDisplacementX;               // m_fShadowDisplacementX[16]
    static float* m_fShadowSideY;                       // m_fShadowSideY[16]
    static float* m_fShadowSideX;                       // m_fShadowSideX[16]
    static float* m_fShadowFrontY;                      // m_fShadowFrontY[16]
    static float* m_fShadowFrontX;                      // m_fShadowFrontX[16]

    static int32& m_CurrentStoredValue;

    static uint8* m_nDirectionalMult;           // m_nDirectionalMult[184]
    static uint8* m_nWaterFogAlpha;             // m_nWaterFogAlpha[184]
    static uint8* m_nHighLightMinIntensity;     // m_nHighLightMinIntensity[184]
    static uint8* m_fCloudAlpha;                // m_fCloudAlpha[184]

    static uint8* m_fPostFx2Alpha;              // m_fPostFx2Alpha[184]
    static uint8* m_fPostFx2Blue;               // m_fPostFx2Blue[184]
    static uint8* m_fPostFx2Green;              // m_fPostFx2Green[184]
    static uint8* m_fPostFx2Red;                // m_fPostFx2Red[184]
    static uint8* m_fPostFx1Alpha;              // m_fPostFx1Alpha[184]
    static uint8* m_fPostFx1Blue;               // m_fPostFx1Blue[184]
    static uint8* m_fPostFx1Green;              // m_fPostFx1Green[184]
    static uint8* m_fPostFx1Red;                // m_fPostFx1Red[184]

    static uint8* m_fWaterAlpha;                // m_fWaterAlpha[184]
    static uint8* m_fWaterBlue;                 // m_fWaterBlue[184]
    static uint8* m_fWaterGreen;                // m_fWaterGreen[184]
    static uint8* m_fWaterRed;                  // m_fWaterRed[184]

    static uint8* m_nFluffyCloudsBottomBlue;    // m_nFluffyCloudsBottomBlue[184]
    static uint8* m_nFluffyCloudsBottomGreen;   // m_nFluffyCloudsBottomGreen[184]
    static uint8* m_nFluffyCloudsBottomRed;     // m_nFluffyCloudsBottomRed[184]

    static uint8* m_nLowCloudsBlue;             // m_nLowCloudsBlue[184]
    static uint8* m_nLowCloudsGreen;            // m_nLowCloudsGreen[184]
    static uint8* m_nLowCloudsRed;              // m_nLowCloudsRed[184]

    static uint8* m_fLightsOnGroundBrightness;  // m_fLightsOnGroundBrightness[184]
    static int16* m_fFogStart;                  // m_fFogStart[184]
    static int16* m_fFarClip;                   // m_fFarClip[184]
    static uint8* m_nPoleShadowStrength;        // m_nPoleShadowStrength[184]
    static uint8* m_nLightShadowStrength;       // m_nLightShadowStrength[184]
    static uint8* m_nShadowStrength;            // m_nShadowStrength[184]
    static char* m_fSpriteBrightness;           // m_fSpriteBrightness[184]
    static char* m_fSpriteSize;                 // m_fSpriteSize[184]
    static char* m_fSunSize;                    // m_fSunSize[184]

    static uint8* m_nSunCoronaBlue;             // m_nSunCoronaBlue[184]
    static uint8* m_nSunCoronaGreen;            // m_nSunCoronaGreen[184]
    static uint8* m_nSunCoronaRed;              // m_nSunCoronaRed[184]
    static uint8* m_nSunCoreBlue;               // m_nSunCoreBlue[184]
    static uint8* m_nSunCoreGreen;              // m_nSunCoreGreen[184]
    static uint8* m_nSunCoreRed;                // m_nSunCoreRed[184]

    static uint8* m_nSkyBottomBlue;             // m_nSkyBottomBlue[184]
    static uint8* m_nSkyBottomGreen;            // m_nSkyBottomGreen[184]
    static uint8* m_nSkyBottomRed;              // m_nSkyBottomRed[184]
    static uint8* m_nSkyTopBlue;                // m_nSkyTopBlue[45]
    static uint8* m_nSkyTopGreen;               // m_nSkyTopGreen[45]
    static uint8* m_nSkyTopRed;                 // m_nSkyTopRed[45]

    static uint8* m_nAmbientBlue_Obj;           // m_nAmbientBlue_Obj[184]
    static uint8* m_nAmbientGreen_Obj;          // m_nAmbientGreen_Obj[184]
    static uint8* m_nAmbientRed_Obj;            // m_nAmbientRed_Obj[184]
    static uint8* m_nAmbientBlue;               // m_nAmbientBlue[184]
    static uint8* m_nAmbientGreen;              // m_nAmbientGreen[184]
    static uint8* m_nAmbientRed;                // m_nAmbientRed[184]

    static uint32& m_NumBoxes;
    static uint32& m_bExtraColourOn;
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

    static void AddOne(CBox& box, int16 farClip, int32 extraColor, float strength, float falloff, float lodDistMult);
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
    static void StartExtraColour(int32 colour, bool bNoExtraColorInterior);
    static void StopExtraColour(bool bNoExtraColorInterior);
    static void Update();

    // helpers
    static CRGBA GetCurrentSkyBottomColor() {
        return m_CurrentColours.GetSkyBottom();
    }
};
