/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "TimeCycle.h"

float& CTimeCycle::m_BrightnessAddedToAmbientBlue{ *(float*)0xB79E30 };
float& CTimeCycle::m_BrightnessAddedToAmbientGreen{ *(float*)0xB79E34 };
float& CTimeCycle::m_BrightnessAddedToAmbientRed{ *(float*)0xB79E38 };

int32& CTimeCycle::m_ExtraColourInter{ *(int32*)0xB79E3C };
int32& CTimeCycle::m_ExtraColourWeatherType{ *(int32*)0xB79E40 };
int32& CTimeCycle::m_ExtraColour{ *(int32*)0xB79E44 };

int32& CTimeCycle::m_FogReduction{ *(int32*)0xB79E48 };

float* CTimeCycle::m_fShadowDisplacementY{ (float*)0xB79E50 };   //m_fShadowDisplacementY[16]
float* CTimeCycle::m_fShadowDisplacementX{ (float*)0xB79E90 };   //m_fShadowDisplacementX[16]
float* CTimeCycle::m_fShadowSideY{ (float*)0xB79ED0 };           //m_fShadowSideY[16]
float* CTimeCycle::m_fShadowSideX{ (float*)0xB79F10 };           //m_fShadowSideX[16]
float* CTimeCycle::m_fShadowFrontY{ (float*)0xB79F50 };          //m_fShadowFrontY[16]
float* CTimeCycle::m_fShadowFrontX{ (float*)0xB79F90 };          //m_fShadowFrontX[16]

int32& CTimeCycle::m_CurrentStoredValue{ *(int32*)0xB79FD0 };

uint8* CTimeCycle::m_nDirectionalMult{ (uint8*)0xB79FD8 };		 //m_nDirectionalMult[184]

uint8* CTimeCycle::m_nWaterFogAlpha{ (uint8*)0xB7A090 };			 //m_nWaterFogAlpha[184]

uint8* CTimeCycle::m_nHighLightMinIntensity{ (uint8*)0xB7A148 };   //m_nHighLightMinIntensity[184]

uint8* CTimeCycle::m_fCloudAlpha{ (uint8*)0xB7A200 };              //m_fCloudAlpha[184]

uint8* CTimeCycle::m_fPostFx2Alpha{ (uint8*)0xB7A2B8 };            //m_fPostFx2Alpha[184]
uint8* CTimeCycle::m_fPostFx2Blue{ (uint8*)0xB7A370 };             //m_fPostFx2Blue[184]
uint8* CTimeCycle::m_fPostFx2Green{ (uint8*)0xB7A428 };            //m_fPostFx2Green[184]
uint8* CTimeCycle::m_fPostFx2Red{ (uint8*)0xB7A4E0 };              //m_fPostFx2Red[184]
uint8* CTimeCycle::m_fPostFx1Alpha{ (uint8*)0xB7A598 };            //m_fPostFx1Alpha[184]
uint8* CTimeCycle::m_fPostFx1Blue{ (uint8*)0xB7A650 };             //m_fPostFx1Blue[184]
uint8* CTimeCycle::m_fPostFx1Green{ (uint8*)0xB7A708 };            //m_fPostFx1Green[184]
uint8* CTimeCycle::m_fPostFx1Red{ (uint8*)0xB7A7C0 };              //m_fPostFx1Red[184]

uint8* CTimeCycle::m_fWaterAlpha{ (uint8*)0xB7A878 };              //m_fWaterAlpha[184]
uint8* CTimeCycle::m_fWaterBlue{ (uint8*)0xB7A930 };               //m_fWaterBlue[184]
uint8* CTimeCycle::m_fWaterGreen{ (uint8*)0xB7A9E8 };              //m_fWaterGreen[184]
uint8* CTimeCycle::m_fWaterRed{ (uint8*)0xB7AAA0 };                //m_fWaterRed[184]

uint8* CTimeCycle::m_nFluffyCloudsBottomBlue{ (uint8*)0xB7AB58 };  //m_nFluffyCloudsBottomBlue[184]
uint8* CTimeCycle::m_nFluffyCloudsBottomGreen{ (uint8*)0xB7AC10 }; //m_nFluffyCloudsBottomGreen[184]
uint8* CTimeCycle::m_nFluffyCloudsBottomRed{ (uint8*)0xB7ACC8 };   //m_nFluffyCloudsBottomRed[184]

uint8* CTimeCycle::m_nLowCloudsBlue{ (uint8*)0xB7AD80 };           //m_nLowCloudsBlue[184]
uint8* CTimeCycle::m_nLowCloudsGreen{ (uint8*)0xB7AE38 };          //m_nLowCloudsGreen[184]
uint8* CTimeCycle::m_nLowCloudsRed{ (uint8*)0xB7AEF0 };            //m_nLowCloudsRed[184]

uint8* CTimeCycle::m_fLightsOnGroundBrightness{ (uint8*)0xB7AFA8 }; //m_fLightsOnGroundBrightness[184]
int16* CTimeCycle::m_fFogStart{ (int16*)0xB7B060 };                 //m_fFogStart[184]
int16* CTimeCycle::m_fFarClip{ (int16*)0xB7B1D0 };                  //m_fFarClip[184]
uint8* CTimeCycle::m_nPoleShadowStrength{ (uint8*)0xB7B340 };      //m_nPoleShadowStrength[184]
uint8* CTimeCycle::m_nLightShadowStrength{ (uint8*)0xB7B3F8 };     //m_nLightShadowStrength[184]
uint8* CTimeCycle::m_nShadowStrength{ (uint8*)0xB7B4B0 };          //m_nShadowStrength[184]
char* CTimeCycle::m_fSpriteBrightness{ (char*)0xB7B568 };                   //m_fSpriteBrightness[184]
char* CTimeCycle::m_fSpriteSize{ (char*)0xB7B620 };                        //m_fSpriteSize[184]

char* CTimeCycle::m_fSunSize{ (char*)0xB7B6D8 };                           //m_fSunSize[184]
uint8* CTimeCycle::m_nSunCoronaBlue{ (uint8*)0xB7B790 };          //m_nSunCoronaBlue[184]
uint8* CTimeCycle::m_nSunCoronaGreen{ (uint8*)0xB7B848 };         //m_nSunCoronaGreen[184]
uint8* CTimeCycle::m_nSunCoronaRed{ (uint8*)0xB7B900 };           //m_nSunCoronaRed[184]
uint8* CTimeCycle::m_nSunCoreBlue{ (uint8*)0xB7B9B8 };           //m_nSunCoreBlue[184]
uint8* CTimeCycle::m_nSunCoreGreen{ (uint8*)0xB7BA70 };          //m_nSunCoreGreen[184]
uint8* CTimeCycle::m_nSunCoreRed{ (uint8*)0xB7BB28 };            //m_nSunCoreRed[184]

uint8* CTimeCycle::m_nSkyBottomBlue{ (uint8*)0xB7BBE0 };         //m_nSkyBottomBlue[184]
uint8* CTimeCycle::m_nSkyBottomGreen{ (uint8*)0xB7BC98 };        //m_nSkyBottomGreen[184]
uint8* CTimeCycle::m_nSkyBottomRed{ (uint8*)0xB7BD50 };         //m_nSkyBottomRed[184]
uint8* CTimeCycle::m_nSkyTopBlue{ (uint8*)0xB7BE08 };            //m_nSkyTopBlue[45]
uint8* CTimeCycle::m_nSkyTopGreen{ (uint8*)0xB7BEC0 };           //m_nSkyTopGreen[45]
uint8* CTimeCycle::m_nSkyTopRed{ (uint8*)0xB7BF78 };             //m_nSkyTopRed[45]

uint8* CTimeCycle::m_nAmbientBlue_Obj{ (uint8*)0xB7C030 };      //m_nAmbientBlue_Obj[184]
uint8* CTimeCycle::m_nAmbientGreen_Obj{ (uint8*)0xB7C0E8 };     //m_nAmbientGreen_Obj[184]
uint8* CTimeCycle::m_nAmbientRed_Obj{ (uint8*)0xB7C1A0 };       //m_nAmbientRed_Obj[184]
uint8* CTimeCycle::m_nAmbientBlue{ (uint8*)0xB7C258 };          //m_nAmbientBlue[184]
uint8* CTimeCycle::m_nAmbientGreen{ (uint8*)0xB7C310 };         //m_nAmbientGreen[184]
uint8* CTimeCycle::m_nAmbientRed{ (uint8*)0xB7C3C8 };           //m_nAmbientRed[184]

uint32& CTimeCycle::m_NumBoxes{ *(uint32*)0xB7C480 };

uint32& CTimeCycle::m_bExtraColourOn{ *(uint32*)0xB7C484 };
CColourSet& CTimeCycle::m_CurrentColours = *(CColourSet*)0xB7C4A0;

float& CTimeCycle::m_fCurrentRGB1Red = *(float*)0xB7C518;
float& CTimeCycle::m_fCurrentRGB1Green = *(float*)0xB7C51C;
float& CTimeCycle::m_fCurrentRGB1Blue = *(float*)0xB7C520;
float& CTimeCycle::m_fCurrentRGB2Red = *(float*)0xB7C528;
float& CTimeCycle::m_fCurrentRGB2Green = *(float*)0xB7C52C;
float& CTimeCycle::m_fCurrentRGB2Blue = *(float*)0xB7C530;

CTimeCycleBox* CTimeCycle::m_aBoxes{ (CTimeCycleBox*)0xB7C550 };  //m_aBoxes[20]

CVector* CTimeCycle::m_VectorToSun{ (CVector*)0xB7CA50 };   //m_VectorToSun[16]
RwRGBA& CTimeCycle::m_BelowHorizonGrey{ *(RwRGBA*)0xB7CB10 };
RwV3d& CTimeCycle::m_vecDirnLightToSun{ *(RwV3d*)0xB7CB14 };

void CTimeCycle::InjectHooks() {
    RH_ScopedClass(CTimeCycle);
    RH_ScopedCategoryGlobal();

    // RH_ScopedInstall(AddOne, 0x55FF40);
}

// 0x55FF40
void CTimeCycle::AddOne(CBox& box, int16 farClip, int32 extraColor, float strength, float falloff, float lodDistMult) {
    plugin::Call<0x55FF40, CBox&, int16, int32, float, float, float>(box, farClip, extraColor, strength, falloff, lodDistMult);
}

// 0x5603D0
void CTimeCycle::CalcColoursForPoint(CVector point, CColourSet* pCurrentColourSet) {
    plugin::Call<0x5603D0, CVector, CColourSet*>(point, pCurrentColourSet);
}

// 0x5616E0
float CTimeCycle::FindFarClipForCoors(CVector cameraPos) {
    return plugin::CallAndReturn<float, 0x5616E0, CVector>(cameraPos);
}

// 0x55FFD0
void CTimeCycle::FindTimeCycleBox(CVector pos, CTimeCycleBox** outbox, float* interpolation, bool bCheckLod, bool bCheckFar, CTimeCycleBox* exclude) {
    plugin::Call<0x55FFD0, CVector, CTimeCycleBox**, float*, bool, bool, CTimeCycleBox*>(pos, outbox, interpolation, bCheckLod, bCheckFar, exclude);
}

// 0x560350
float CTimeCycle::GetAmbientBlue() {
    return plugin::CallAndReturn<float, 0x560350>();
}

// 0x5603B0
float CTimeCycle::GetAmbientBlue_BeforeBrightness() {
    return plugin::CallAndReturn<float, 0x5603B0>();
}

// 0x560380
float CTimeCycle::GetAmbientBlue_Obj() {
    return plugin::CallAndReturn<float, 0x560380>();
}

// 0x560340
float CTimeCycle::GetAmbientGreen() {
    return plugin::CallAndReturn<float, 0x560340>();
}

// 0x5603A0
float CTimeCycle::GetAmbientGreen_BeforeBrightness() {
    return plugin::CallAndReturn<float, 0x5603A0>();
}

// 0x560370
float CTimeCycle::GetAmbientGreen_Obj() {
    return plugin::CallAndReturn<float, 0x560370>();
}

// 0x560330
float CTimeCycle::GetAmbientRed() {
    return plugin::CallAndReturn<float, 0x560330>();
}

// 0x560390
float CTimeCycle::GetAmbientRed_BeforeBrightness() {
    return plugin::CallAndReturn<float, 0x560390>();
}

// 0x560360
float CTimeCycle::GetAmbientRed_Obj() {
    return plugin::CallAndReturn<float, 0x560360>();
}

// 0x5601F0
void CTimeCycle::InitForRestart() {
    plugin::Call<0x5601F0>();
}

// Converted from cdecl void CTimeCycle::Initialise()	0x5BBAC0
void CTimeCycle::Initialise() {
    plugin::Call<0x5BBAC0>();
}

// 0x560210
void CTimeCycle::SetConstantParametersForPostFX() {
    plugin::Call<0x560210>();
}

// empty function
void CTimeCycle::Shutdown() {
    plugin::Call<0x5601E0>();
}

// 0x55FEC0
void CTimeCycle::StartExtraColour(int32 colour, bool bNoExtraColorInterior) {
    plugin::Call<0x55FEC0, int32, bool>(colour, bNoExtraColorInterior);
}

// 0x55FF20
void CTimeCycle::StopExtraColour(bool bNoExtraColorInterior) {
    plugin::Call<0x55FF20, bool>(bNoExtraColorInterior);
}

// 0x561760
void CTimeCycle::Update() {
    plugin::Call<0x561760>();
}

CRGBA CTimeCycle::GetCurrentSkyBottomColor() {
    return m_CurrentColours.GetSkyBottom();
}
