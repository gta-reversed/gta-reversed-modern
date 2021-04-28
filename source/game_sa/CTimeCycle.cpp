/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

float& CTimeCycle::m_BrightnessAddedToAmbientBlue{ *(float*)0xB79E30 };
float& CTimeCycle::m_BrightnessAddedToAmbientGreen{ *(float*)0xB79E34 };
float& CTimeCycle::m_BrightnessAddedToAmbientRed{ *(float*)0xB79E38 };

int& CTimeCycle::m_ExtraColourInter{ *(int*)0xB79E3C };
int& CTimeCycle::m_ExtraColourWeatherType{ *(int*)0xB79E40 };
int& CTimeCycle::m_ExtraColour{ *(int*)0xB79E44 };

int& CTimeCycle::m_FogReduction{ *(int*)0xB79E48 };

float* CTimeCycle::m_fShadowDisplacementY{ (float*)0xB79E50 };   //m_fShadowDisplacementY[16]
float* CTimeCycle::m_fShadowDisplacementX{ (float*)0xB79E90 };   //m_fShadowDisplacementX[16]
float* CTimeCycle::m_fShadowSideY{ (float*)0xB79ED0 };           //m_fShadowSideY[16]
float* CTimeCycle::m_fShadowSideX{ (float*)0xB79F10 };           //m_fShadowSideX[16]
float* CTimeCycle::m_fShadowFrontY{ (float*)0xB79F50 };          //m_fShadowFrontY[16]
float* CTimeCycle::m_fShadowFrontX{ (float*)0xB79F90 };          //m_fShadowFrontX[16]

int& CTimeCycle::m_CurrentStoredValue{ *(int*)0xB79FD0 };

unsigned char* CTimeCycle::m_nDirectionalMult{ (unsigned char*)0xB79FD8 };		 //m_nDirectionalMult[184]

unsigned char* CTimeCycle::m_nWaterFogAlpha{ (unsigned char*)0xB7A090 };			 //m_nWaterFogAlpha[184]

unsigned char* CTimeCycle::m_nHighLightMinIntensity{ (unsigned char*)0xB7A148 };   //m_nHighLightMinIntensity[184]

unsigned char* CTimeCycle::m_fCloudAlpha{ (unsigned char*)0xB7A200 };              //m_fCloudAlpha[184]

unsigned char* CTimeCycle::m_fPostFx2Alpha{ (unsigned char*)0xB7A2B8 };            //m_fPostFx2Alpha[184]
unsigned char* CTimeCycle::m_fPostFx2Blue{ (unsigned char*)0xB7A370 };             //m_fPostFx2Blue[184]
unsigned char* CTimeCycle::m_fPostFx2Green{ (unsigned char*)0xB7A428 };            //m_fPostFx2Green[184]
unsigned char* CTimeCycle::m_fPostFx2Red{ (unsigned char*)0xB7A4E0 };              //m_fPostFx2Red[184]
unsigned char* CTimeCycle::m_fPostFx1Alpha{ (unsigned char*)0xB7A598 };            //m_fPostFx1Alpha[184]
unsigned char* CTimeCycle::m_fPostFx1Blue{ (unsigned char*)0xB7A650 };             //m_fPostFx1Blue[184]
unsigned char* CTimeCycle::m_fPostFx1Green{ (unsigned char*)0xB7A708 };            //m_fPostFx1Green[184]
unsigned char* CTimeCycle::m_fPostFx1Red{ (unsigned char*)0xB7A7C0 };              //m_fPostFx1Red[184]

unsigned char* CTimeCycle::m_fWaterAlpha{ (unsigned char*)0xB7A878 };              //m_fWaterAlpha[184]
unsigned char* CTimeCycle::m_fWaterBlue{ (unsigned char*)0xB7A930 };               //m_fWaterBlue[184]
unsigned char* CTimeCycle::m_fWaterGreen{ (unsigned char*)0xB7A9E8 };              //m_fWaterGreen[184]
unsigned char* CTimeCycle::m_fWaterRed{ (unsigned char*)0xB7AAA0 };                //m_fWaterRed[184]

unsigned char* CTimeCycle::m_nFluffyCloudsBottomBlue{ (unsigned char*)0xB7AB58 };  //m_nFluffyCloudsBottomBlue[184]
unsigned char* CTimeCycle::m_nFluffyCloudsBottomGreen{ (unsigned char*)0xB7AC10 }; //m_nFluffyCloudsBottomGreen[184]
unsigned char* CTimeCycle::m_nFluffyCloudsBottomRed{ (unsigned char*)0xB7ACC8 };   //m_nFluffyCloudsBottomRed[184]

unsigned char* CTimeCycle::m_nLowCloudsBlue{ (unsigned char*)0xB7AD80 };           //m_nLowCloudsBlue[184]
unsigned char* CTimeCycle::m_nLowCloudsGreen{ (unsigned char*)0xB7AE38 };          //m_nLowCloudsGreen[184]
unsigned char* CTimeCycle::m_nLowCloudsRed{ (unsigned char*)0xB7AEF0 };            //m_nLowCloudsRed[184]

unsigned char* CTimeCycle::m_fLightsOnGroundBrightness{ (unsigned char*)0xB7AFA8 }; //m_fLightsOnGroundBrightness[184]
signed short* CTimeCycle::m_fFogStart{ (signed short*)0xB7B060 };                 //m_fFogStart[184]
signed short* CTimeCycle::m_fFarClip{ (signed short*)0xB7B1D0 };                  //m_fFarClip[184]
unsigned char* CTimeCycle::m_nPoleShadowStrength{ (unsigned char*)0xB7B340 };      //m_nPoleShadowStrength[184]
unsigned char* CTimeCycle::m_nLightShadowStrength{ (unsigned char*)0xB7B3F8 };     //m_nLightShadowStrength[184]
unsigned char* CTimeCycle::m_nShadowStrength{ (unsigned char*)0xB7B4B0 };          //m_nShadowStrength[184]
char* CTimeCycle::m_fSpriteBrightness{ (char*)0xB7B568 };                   //m_fSpriteBrightness[184]
char* CTimeCycle::m_fSpriteSize{ (char*)0xB7B620 };                        //m_fSpriteSize[184]

char* CTimeCycle::m_fSunSize{ (char*)0xB7B6D8 };                           //m_fSunSize[184]
unsigned char* CTimeCycle::m_nSunCoronaBlue{ (unsigned char*)0xB7B790 };          //m_nSunCoronaBlue[184]
unsigned char* CTimeCycle::m_nSunCoronaGreen{ (unsigned char*)0xB7B848 };         //m_nSunCoronaGreen[184]
unsigned char* CTimeCycle::m_nSunCoronaRed{ (unsigned char*)0xB7B900 };           //m_nSunCoronaRed[184]
unsigned char* CTimeCycle::m_nSunCoreBlue{ (unsigned char*)0xB7B9B8 };           //m_nSunCoreBlue[184]
unsigned char* CTimeCycle::m_nSunCoreGreen{ (unsigned char*)0xB7BA70 };          //m_nSunCoreGreen[184]
unsigned char* CTimeCycle::m_nSunCoreRed{ (unsigned char*)0xB7BB28 };            //m_nSunCoreRed[184]

unsigned char* CTimeCycle::m_nSkyBottomBlue{ (unsigned char*)0xB7BBE0 };         //m_nSkyBottomBlue[184]
unsigned char* CTimeCycle::m_nSkyBottomGreen{ (unsigned char*)0xB7BC98 };        //m_nSkyBottomGreen[184]
unsigned char* CTimeCycle::m_nSkyBottomRed{ (unsigned char*)0xB7BD50 };         //m_nSkyBottomRed[184]
unsigned char* CTimeCycle::m_nSkyTopBlue{ (unsigned char*)0xB7BE08 };            //m_nSkyTopBlue[45]
unsigned char* CTimeCycle::m_nSkyTopGreen{ (unsigned char*)0xB7BEC0 };           //m_nSkyTopGreen[45]
unsigned char* CTimeCycle::m_nSkyTopRed{ (unsigned char*)0xB7BF78 };             //m_nSkyTopRed[45]

unsigned char* CTimeCycle::m_nAmbientBlue_Obj{ (unsigned char*)0xB7C030 };      //m_nAmbientBlue_Obj[184]
unsigned char* CTimeCycle::m_nAmbientGreen_Obj{ (unsigned char*)0xB7C0E8 };     //m_nAmbientGreen_Obj[184]
unsigned char* CTimeCycle::m_nAmbientRed_Obj{ (unsigned char*)0xB7C1A0 };       //m_nAmbientRed_Obj[184]
unsigned char* CTimeCycle::m_nAmbientBlue{ (unsigned char*)0xB7C258 };          //m_nAmbientBlue[184]
unsigned char* CTimeCycle::m_nAmbientGreen{ (unsigned char*)0xB7C310 };         //m_nAmbientGreen[184]
unsigned char* CTimeCycle::m_nAmbientRed{ (unsigned char*)0xB7C3C8 };           //m_nAmbientRed[184]

unsigned int& CTimeCycle::m_NumBoxes{ *(unsigned int*)0xB7C480 };

unsigned int& CTimeCycle::m_bExtraColourOn{ *(unsigned int*)0xB7C484 };
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

}

// Converted from cdecl void CTimeCycle::AddOne(CBox &box,short farclip,int extracolor,float strength,float falloff,float lodDistMult)	0x55FF40	
void CTimeCycle::AddOne(CBox& box, short farClip, int extraColor, float strength, float falloff, float lodDistMult) {
    plugin::Call<0x55FF40, CBox&, short, int, float, float, float>(box, farClip, extraColor, strength, falloff, lodDistMult);
}

// Converted from cdecl void CTimeCycle::CalcColoursForPoint(CVector point,CColourSet * pCurrentColourSet)	0x5603D0	
void CTimeCycle::CalcColoursForPoint(CVector point, CColourSet* pCurrentColourSet) {
    plugin::Call<0x5603D0, CVector, CColourSet*>(point, pCurrentColourSet);
}

// Converted from cdecl void CTimeCycle::FindFarClipForCoors(CVector cam_pos)	0x5616E0
float CTimeCycle::FindFarClipForCoors(CVector cameraPos) {
    return plugin::CallAndReturn<float, 0x5616E0, CVector>(cameraPos);
}

// Converted from cdecl void CTimeCycle::FindTimeCycleBox(CVector pos,CTimeCycleBox **outbox,float *interpolation,bool bCheckLod,bool bCheckFar,CTimeCycleBox *exclude)	0x55FFD0
void CTimeCycle::FindTimeCycleBox(CVector pos, CTimeCycleBox** outbox, float* interpolation, bool bCheckLod, bool bCheckFar, CTimeCycleBox* exclude) {
    plugin::Call<0x55FFD0, CVector, CTimeCycleBox**, float*, bool, bool, CTimeCycleBox*>(pos, outbox, interpolation, bCheckLod, bCheckFar, exclude);
}

// Converted from cdecl float CTimeCycle::GetAmbientBlue(void)	0x560350	
float CTimeCycle::GetAmbientBlue() {
    return plugin::CallAndReturn<float, 0x560350>();
}

// Converted from cdecl float CTimeCycle::GetAmbientBlue_BeforeBrightness(void)	0x5603B0	
float CTimeCycle::GetAmbientBlue_BeforeBrightness() {
    return plugin::CallAndReturn<float, 0x5603B0>();
}

// Converted from cdecl float CTimeCycle::GetAmbientBlue_Obj(void)	0x560380	
float CTimeCycle::GetAmbientBlue_Obj() {
    return plugin::CallAndReturn<float, 0x560380>();
}

// Converted from cdecl float CTimeCycle::GetAmbientGreen(void)	0x560340	
float CTimeCycle::GetAmbientGreen() {
    return plugin::CallAndReturn<float, 0x560340>();
}

// Converted from cdecl float CTimeCycle::GetAmbientGreen_BeforeBrightness(void)	0x5603A0	
float CTimeCycle::GetAmbientGreen_BeforeBrightness() {
    return plugin::CallAndReturn<float, 0x5603A0>();
}

// Converted from cdecl float CTimeCycle::GetAmbientGreen_Obj(void)	0x560370	
float CTimeCycle::GetAmbientGreen_Obj() {
    return plugin::CallAndReturn<float, 0x560370>();
}

// Converted from cdecl float CTimeCycle::GetAmbientRed(void)	0x560330	
float CTimeCycle::GetAmbientRed() {
    return plugin::CallAndReturn<float, 0x560330>();
}

// Converted from cdecl float CTimeCycle::GetAmbientRed_BeforeBrightness(void)	0x560390
float CTimeCycle::GetAmbientRed_BeforeBrightness() {
    return plugin::CallAndReturn<float, 0x560390>();
}

// Converted from cdecl float CTimeCycle::GetAmbientRed_Obj(void)	0x560360	
float CTimeCycle::GetAmbientRed_Obj() {
    return plugin::CallAndReturn<float, 0x560360>();
}

// Converted from cdecl void CTimeCycle::InitForRestart(void)0x5601F0
void CTimeCycle::InitForRestart() {
    plugin::Call<0x5601F0>();
}

// Converted from cdecl void CTimeCycle::Initialise(void)	0x5BBAC0
void CTimeCycle::Initialise() {
    plugin::Call<0x5BBAC0>();
}

// Converted from cdecl void CTimeCycle::SetConstantParametersForPostFX(void)0x560210
void CTimeCycle::SetConstantParametersForPostFX() {
    plugin::Call<0x560210>();
}

// empty function
void CTimeCycle::Shutdown() {
    plugin::Call<0x5601E0>();
}

// Converted from cdecl void CTimeCycle::StartExtraColour(int colour,bool bNoExtraColorInterior)	0x55FEC0
void CTimeCycle::StartExtraColour(int colour, bool bNoExtraColorInterior) {
    plugin::Call<0x55FEC0, int, bool>(colour, bNoExtraColorInterior);
}

// Converted from cdecl void CTimeCycle::StopExtraColour(bool bNoExtraColorInterior)	0x55FF20
void CTimeCycle::StopExtraColour(bool bNoExtraColorInterior) {
    plugin::Call<0x55FF20, bool>(bNoExtraColorInterior);
}

// Converted from cdecl void CTimeCycle::Update(void)	0x561760
void CTimeCycle::Update() {
    plugin::Call<0x561760>();
}
