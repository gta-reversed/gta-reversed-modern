/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "common.h"
#include "GxtChar.h"
#include "CDebugMenu.h"
#include "CarCtrl.h"
#include "UserDisplay.h"
#include "PostEffects.h"
#include "SpecialFX.h"
#include "Hud.h"

int32& g_nNumIm3dDrawCalls = *(int32*)0xB73708;
int32 gDefaultTaskTime = 9999999; // or 0x98967F a.k.a (one milllion - 1)

char(&PC_Scratch)[16384] = *(char(*)[16384])0xC8E0C8;

RpLight* (&pExtraDirectionals)[6] = *reinterpret_cast<RpLight* (*)[6]>(0xC886F0);
int32& numExtraDirectionalLights = *reinterpret_cast<int32*>(0xC88708);

RwV3d& sun2Dir = *reinterpret_cast<RwV3d*>(0xB7CB14);

RwRGBAReal& FullLight = *reinterpret_cast<RwRGBAReal*>(0x8D60C0); //  <1.0, 1.0, 1.0, 1.0>

char (&IndicateR)[8] = *reinterpret_cast<char (*)[8]>(0x8D60D0);
char (&IndicateG)[8] = *reinterpret_cast<char (*)[8]>(0x8D60D8);
char (&IndicateB)[8] = *reinterpret_cast<char (*)[8]>(0x8D60E0);

RpLight*& pAmbient = *reinterpret_cast<RpLight**>(0xC886E8);
RwRGBAReal& AmbientLightColour = *reinterpret_cast<RwRGBAReal*>(0xC886A4);
RwRGBAReal& AmbientLightColourForFrame = *reinterpret_cast<RwRGBAReal*>(0xC886D4);
RwRGBAReal& AmbientLightColourForFrame_PedsCarsAndObjects = *reinterpret_cast<RwRGBAReal*>(0xC886C4);
RpLight*& pDirect = *reinterpret_cast<RpLight**>(0xC886EC);
RwRGBAReal& DirectionalLightColour = *reinterpret_cast<RwRGBAReal*>(0xC88694);
RwRGBAReal& DirectionalLightColourForFrame = *reinterpret_cast<RwRGBAReal*>(0xC886B4);

RwRGBAReal (&DirectAmbientLight)[2] = *reinterpret_cast<RwRGBAReal (*)[2]>(0xC8865C); // Direct, Ambient Light

float& gfLaRiotsLightMult = *(float*)0x8CD060; // 1.0f

void InjectCommonHooks() {
    RH_ScopedNamespaceName("Common");
    RH_ScopedCategory("Common");

    RH_ScopedGlobalInstall(MakeUpperCase, 0x7186E0);
    RH_ScopedGlobalInstall(DefinedState, 0x734650);
    RH_ScopedGlobalInstall(DefinedState2d, 0x734750);

    RH_ScopedGlobalInstall(LightsCreate, 0x5BA520);
    RH_ScopedGlobalInstall(LightsDestroy, 0x735730);
    RH_ScopedGlobalInstall(WorldReplaceNormalLightsWithScorched, 0x7357E0);
//    RH_ScopedGlobalInstall(AddAnExtraDirectionalLight, 0x735840);
    RH_ScopedGlobalInstall(RemoveExtraDirectionalLights, 0x7359E0);
    RH_ScopedGlobalInstall(SetBrightMarkerColours, 0x735BD0);
    RH_ScopedGlobalInstall(ReSetAmbientAndDirectionalColours, 0x735C40);
    RH_ScopedGlobalInstall(DeActivateDirectional, 0x735C70);
    RH_ScopedGlobalInstall(ActivateDirectional, 0x735C80);
    RH_ScopedGlobalOverloadedInstall(SetAmbientColours, "void", 0x735D30, void(*)());
    RH_ScopedGlobalOverloadedInstall(SetAmbientColours, "color", 0x735D50, void(*)(RwRGBAReal* color));
    RH_ScopedGlobalInstall(SetDirectionalColours, 0x735D70);
    RH_ScopedGlobalInstall(SetLightColoursForPedsCarsAndObjects, 0x735D90);
    RH_ScopedGlobalInstall(SetLightsForInfraredVisionHeatObjects, 0x735E40);
    RH_ScopedGlobalInstall(StoreAndSetLightsForInfraredVisionHeatObjects, 0x735E70);
    RH_ScopedGlobalInstall(RestoreLightsForInfraredVisionHeatObjects, 0x735EF0);
    RH_ScopedGlobalInstall(SetLightsForInfraredVisionDefaultObjects, 0x735F20);
    RH_ScopedGlobalInstall(SetLightsForNightVision, 0x735F70);
    RH_ScopedGlobalInstall(GetDayNightBalance, 0x6FAB30);

    RH_ScopedGlobalInstall(AsciiToGxtChar, 0x718600);
    RH_ScopedGlobalInstall(WriteRaster, 0x005A4150);
    // RH_ScopedOverloadedInstall(CalcScreenCoors, "VVff", 0x71DA00, bool(*)(const CVector&, CVector*, float*, float*));
    // RH_ScopedOverloadedInstall(CalcScreenCoors, "VV", 0x71DAB0, bool(*)(const CVector&, CVector*));
    RH_ScopedGlobalInstall(LittleTest, 0x541330);
}

void MessageLoop() {
    tagMSG msg;
    while (PeekMessageA(&msg, 0, 0, 0, PM_REMOVE | PM_NOYIELD)) {
        if (msg.message == WM_QUIT) {
            RsGlobal.quit = true;
        } else {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }
}

// 0x54ECE0
void TransformPoint(RwV3d& point, const CSimpleTransform& placement, const RwV3d& vecPos) {
    plugin::Call<0x54ECE0, RwV3d&, const CSimpleTransform&, const RwV3d&>(point, placement, vecPos);
}

// 0x54EEA0
void TransformVectors(RwV3d* vecsOut, int32 numVectors, const CMatrix& matrix, const RwV3d* vecsin) {
    plugin::Call<0x54EEA0, RwV3d*, int32, const CMatrix&, const RwV3d*>(vecsOut, numVectors, matrix, vecsin);
}

// 0x54EE30
void TransformVectors(RwV3d* vecsOut, int32 numVectors, const CSimpleTransform& transform, const RwV3d* vecsin) {
    plugin::Call<0x54EE30, RwV3d*, int32, const CSimpleTransform&, const RwV3d*>(vecsOut, numVectors, transform, vecsin);
}

// 0x4D62A0
AnimBlendFrameData* RpAnimBlendClumpFindFrame(RpClump* clump, char* name) {
    return ((AnimBlendFrameData * (__cdecl*)(RpClump*, char*))0x4D62A0)(clump, name);
}

char ToUpper(char ch) {
    return (ch >= 'a' && ch <= 'z') ? ch - ('a' - 'A') : ch;
}

// 0x7186E0
char* MakeUpperCase(char* dest, const char * src) {
    for (; *src; src++, dest++)
        *dest = ToUpper(*src);
    *dest = 0;
    return dest;
}

// NOTSA
bool EndsWith(const char* str, const char* with, bool caseSensitive) {
    const auto strsz = strlen(str), withsz = strlen(with);
    assert(strsz >= withsz);
    return (caseSensitive ? strncmp : _strnicmp)(str + strsz - withsz, with, withsz) == 0;
}

// 0x734650
void DefinedState() {
    CRGBA rgbaFog(
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomRed,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
        (uint8)CTimeCycle::m_CurrentColours.m_nSkyBottomBlue
    );

    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          RWRSTATE((RWRGBALONG(0, 0, 0, 255))));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEFOGCOLOR,             RWRSTATE(rgbaFog.ToIntARGB()));
    RwRenderStateSet(rwRENDERSTATEFOGTYPE,              RWRSTATE(rwFOGTYPELINEAR));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLNONE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(2)); // TODO: ?
}

// 0x734750
void DefinedState2d() {
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTUREPERSPECTIVE,   RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,        RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEBORDERCOLOR,          RWRSTATE((RWRGBALONG(0, 0, 0, 255))));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLNONE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(2)); // TODO: ?
}

// todo: move
// 0x53D690
void DoRWStuffStartOfFrame(int16 nR1, int16 nG1, int16 nB1, int16 nR2, int16 nG2, int16 nB2, int16 nA) {
    plugin::Call<0x53D690, int16, int16, int16, int16, int16, int16, int16>(nR1, nG1, nB1, nR2, nG2, nB2, nA);
}

// todo: move
// 0x53D840
void DoRWStuffEndOfFrame() {
    plugin::Call<0x53D840>();
}

// todo: move
// 0x53EC10
RsEventStatus AppEventHandler(RsEvent nEvent, void* param) {
    return plugin::CallAndReturn<RsEventStatus, 0x53EC10, RsEvent, void*>(nEvent, param);
}

// 0x7354E0
void SetLightsWithTimeOfDayColour(RpWorld* world) {
    assert(world);
    if (pAmbient) {
        AmbientLightColourForFrame.red   = CTimeCycle::GetAmbientRed() * CCoronas::LightsMult;
        AmbientLightColourForFrame.green = CTimeCycle::GetAmbientGreen() * CCoronas::LightsMult;
        AmbientLightColourForFrame.blue  = CTimeCycle::GetAmbientBlue() * CCoronas::LightsMult;

        AmbientLightColourForFrame_PedsCarsAndObjects.red   = CTimeCycle::GetAmbientRed_Obj()   * CCoronas::LightsMult;
        AmbientLightColourForFrame_PedsCarsAndObjects.green = CTimeCycle::GetAmbientGreen_Obj() * CCoronas::LightsMult;
        AmbientLightColourForFrame_PedsCarsAndObjects.blue  = CTimeCycle::GetAmbientBlue_Obj()  * CCoronas::LightsMult;

        if (CWeather::LightningFlash) {
            AmbientLightColourForFrame.blue  = 1.0f;
            AmbientLightColourForFrame.green = 1.0f;
            AmbientLightColourForFrame.red   = 1.0f;
            AmbientLightColourForFrame_PedsCarsAndObjects.blue  = 1.0f;
            AmbientLightColourForFrame_PedsCarsAndObjects.green = 1.0f;
            AmbientLightColourForFrame_PedsCarsAndObjects.red   = 1.0f;
        }
        RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    }

    if (pDirect) {
        const float color = CTimeCycle::m_CurrentColours.m_fIllumination * 0.99609375f * CCoronas::LightsMult;
        DirectionalLightColourForFrame.red   = color;
        DirectionalLightColourForFrame.green = color;
        DirectionalLightColourForFrame.blue  = color;
        RpLightSetColor(pDirect, &DirectionalLightColourForFrame);

        CVector vecDir   = CTimeCycle::m_vecDirnLightToSun;
        CVector vecUp    = CrossProduct(CVector(0, 0, 1), vecDir);
        vecUp.Normalise();
        CVector vecRight = CrossProduct(vecUp, vecDir);

        RwMatrix mxTransform;
        mxTransform.right = vecRight;
        mxTransform.up    = vecUp;
        mxTransform.at    = -vecDir;
        RwFrameTransform(RpLightGetFrame(pDirect), &mxTransform, rwCOMBINEREPLACE);
    }
}

// 0x735720 unused
void LightsEnable(int32 arg0) {
    // NOP
}

// 0x5BA520
void LightsCreate(RpWorld* world) {
    if (!world) {
        return;
    }

    RwRGBAReal color;

    pAmbient = RpLightCreate(rpLIGHTAMBIENT);
    RpLightSetFlags(pAmbient, rpLIGHTLIGHTATOMICS);
    color.red   = 0.25f;
    color.green = 0.25f;
    color.blue  = 0.20f;
    RpLightSetColor(pAmbient, &color);

    pDirect = RpLightCreate(rpLIGHTDIRECTIONAL);
    RpLightSetFlags(pDirect, rpLIGHTLIGHTATOMICS);
    color.red   = 1.00f;
    color.green = 0.85f;
    color.blue  = 0.45f;
    RpLightSetColor(pDirect, &color);
    RpLightSetRadius(pDirect, 2.0f);

    RwFrame* frame = RwFrameCreate();
    rwObjectHasFrameSetFrame(pDirect, frame);
    RwV3d _vecLight = { 1.0f, 1.0f, 0.0f };
    RwFrameRotate(frame, &_vecLight, 160.0f, rwCOMBINEPRECONCAT);

    RpWorldAddLight(world, pAmbient);
    RpWorldAddLight(world, pDirect);

    for (auto& light : pExtraDirectionals) {
        light = RpLightCreate(rpLIGHTDIRECTIONAL);
        RpLightSetFlags(light, NULL);

        color.red   = 1.0f;
        color.green = 0.5f;
        color.blue  = 0.0f;
        RpLightSetColor(light, &color);
        RpLightSetRadius(light, 2.0f);
        rwObjectHasFrameSetFrame(light, RwFrameCreate());

        RpWorldAddLight(world, light);
    }
}

// 0x735730
void LightsDestroy(RpWorld* world) {
    if (!world) {
        return;
    }

    if (pAmbient) {
        RpWorldRemoveLight(world, pAmbient);
        RpLightDestroy(pAmbient);
        pAmbient = nullptr;
    }

    if (pDirect) {
        RpWorldRemoveLight(world, pDirect);
        RwFrameDestroy(RpLightGetFrame(pDirect));
        RpLightDestroy(pDirect);
        pDirect = nullptr;
    }

    for (auto& light : pExtraDirectionals) {
        RpWorldRemoveLight(world, light);
        RwFrameDestroy(RpLightGetFrame(light));
        RpLightDestroy(light);
        light = nullptr;
    }
}

// lighting = [ 0.0f; 1.0f ]
// 0x7357E0
void WorldReplaceNormalLightsWithScorched(RpWorld* world, float lighting) {
    RwRGBAReal color{lighting, lighting, lighting};
    RpLightSetColor(pAmbient, &color);
    DeActivateDirectional();
}

// unused
// 0x735820
void WorldReplaceScorchedLightsWithNormal(RpWorld* world) {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    ActivateDirectional();
}

// 0x735840
void AddAnExtraDirectionalLight(RpWorld* world, float x, float y, float z, float red, float green, float blue) {
    ((void(__cdecl *)(RpWorld*, float, float, float, float, float, float))0x735840)(world, x, y, z, red, green, blue);
}

// 0x7359E0
void RemoveExtraDirectionalLights(RpWorld* world) {
    for (auto& light : pExtraDirectionals) {
        RpLightSetFlags(light, 0x0);
    }
    numExtraDirectionalLights = 0;
}

// fMult = [ 0.0f; 1.0f ]
// used in SetFlashyColours and SetFlashyColours_Mild which unused
// 0x735A20
void SetAmbientAndDirectionalColours(float fMult) {
    AmbientLightColour.red       = fMult * AmbientLightColourForFrame.red;
    AmbientLightColour.green     = fMult * AmbientLightColourForFrame.green;
    AmbientLightColour.blue      = fMult * AmbientLightColourForFrame.blue;

    DirectionalLightColour.red   = fMult * DirectionalLightColourForFrame.red;
    DirectionalLightColour.green = fMult * DirectionalLightColourForFrame.green;
    DirectionalLightColour.blue  = fMult * DirectionalLightColourForFrame.blue;

    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// fMult = [ 0.0f; 1.0f ]
// 0x735AB0 unused
void SetFlashyColours(float fMult) {
    if (CTimer::GetTimeInMS() & 0x100) {
        AmbientLightColour.red   = 1.0f;
        AmbientLightColour.green = 1.0f;
        AmbientLightColour.blue  = 1.0f;
        DirectionalLightColour = DirectionalLightColourForFrame;

        RpLightSetColor(pAmbient, &AmbientLightColour);
        RpLightSetColor(pDirect, &DirectionalLightColour);
        return;
    }
    SetAmbientAndDirectionalColours(fMult * 0.75f);
}

// fMult = [ 0.0f; 1.0f ]
// 0x735B40 unused
void SetFlashyColours_Mild(float fMult) {
    if ((CTimer::GetTimeInMS() & 0x100) != 0) {
        AmbientLightColour.red   = 0.65f;
        AmbientLightColour.green = 0.65f;
        AmbientLightColour.blue  = 0.65f;
        DirectionalLightColour = DirectionalLightColourForFrame;

        RpLightSetColor(pAmbient, &AmbientLightColour);
        RpLightSetColor(pDirect, &DirectionalLightColour);
        return;
    }
    SetAmbientAndDirectionalColours(fMult * 0.9f);
}

// 0x735BD0
void SetBrightMarkerColours(float lighting) {
    AmbientLightColour.red   = 0.6f;
    AmbientLightColour.green = 0.6f;
    AmbientLightColour.blue  = 0.6f;

    DirectionalLightColour.red   = 1.0f;
    DirectionalLightColour.green = 1.0f;
    DirectionalLightColour.blue  = 1.0f;

    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// 0x735C40
void ReSetAmbientAndDirectionalColours() {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
    RpLightSetColor(pDirect, &DirectionalLightColourForFrame);
}

// 0x735C80
void ActivateDirectional() {
    RpLightSetFlags(pDirect, rpLIGHTLIGHTATOMICS);
}

// 0x735C70
void DeActivateDirectional() {
    RpLightSetFlags(pDirect, 0x0);
}

/*!
 * @addr 0x735C90
 * @param idx Color index 0..8
 */
void SetAmbientColoursToIndicateRoadGroup(int32 idx) {
    // used to convert 0-255 to 0.0f-1.0f

    AmbientLightColour.red   = (float)IndicateR[idx % 7] * 255.0f;
    AmbientLightColour.green = (float)IndicateG[idx % 7] * 255.0f;
    AmbientLightColour.blue  = (float)IndicateB[idx % 7] * 255.0f;
    RpLightSetColor(pAmbient, &AmbientLightColour);
}

// unused
// 0x735D10
void SetFullAmbient() {
    RpLightSetColor(pAmbient, &FullLight);
}

// 0x735D30
void SetAmbientColours() {
    RpLightSetColor(pAmbient, &AmbientLightColourForFrame);
}

// 0x735D50
void SetAmbientColours(RwRGBAReal* color) {
    assert(color);
    RpLightSetColor(pAmbient, color);
}

// 0x735D70
void SetDirectionalColours(RwRGBAReal* color) {
    assert(color);
    RpLightSetColor(pDirect, color);
}

// fMult = [ 0.0f; 1.0f ]
// 0x735D90
void SetLightColoursForPedsCarsAndObjects(float fMult) {
    DirectionalLightColour.red   = fMult * DirectionalLightColourForFrame.red;
    DirectionalLightColour.green = fMult * DirectionalLightColourForFrame.green;
    DirectionalLightColour.blue  = fMult * DirectionalLightColourForFrame.blue;

    AmbientLightColour.red       = fMult * AmbientLightColourForFrame_PedsCarsAndObjects.red;
    AmbientLightColour.green     = fMult * AmbientLightColourForFrame_PedsCarsAndObjects.green;
    AmbientLightColour.blue      = fMult * AmbientLightColourForFrame_PedsCarsAndObjects.blue;

    AmbientLightColour.red      += CTimeCycle::m_BrightnessAddedToAmbientRed;
    AmbientLightColour.green    += CTimeCycle::m_BrightnessAddedToAmbientRed;
    AmbientLightColour.blue     += CTimeCycle::m_BrightnessAddedToAmbientRed;

    RpLightSetColor(pAmbient, &AmbientLightColour);
    RpLightSetColor(pDirect, &DirectionalLightColour);
}

// 0x735E40
void SetLightsForInfraredVisionHeatObjects() {
    RpLightSetColor(pAmbient, &CPostEffects::m_fInfraredVisionHeatObjectCol);
    RpLightSetColor(pDirect, &CPostEffects::m_fInfraredVisionHeatObjectCol);
}

// 0x735E70
void StoreAndSetLightsForInfraredVisionHeatObjects() {
    DirectAmbientLight[1] = AmbientLightColour;
    DirectAmbientLight[0] = DirectionalLightColour;
    SetLightsForInfraredVisionHeatObjects();
}

// 0x735EF0
void RestoreLightsForInfraredVisionHeatObjects() {
    RpLightSetColor(pAmbient, &DirectAmbientLight[1]);
    RpLightSetColor(pDirect, &DirectAmbientLight[0]);
}

// 0x735F20
void SetLightsForInfraredVisionDefaultObjects() {
    RwRGBAReal color{0.0f, 0.0f, 1.0f, 1.0f};
    RpLightSetColor(pAmbient, &color);
    RpLightSetColor(pDirect, &color);
}

// 0x735F70
void SetLightsForNightVision() {
    RwRGBAReal color{0.0f, 1.0f, 0.0f, 1.0f};
    RpLightSetColor(pAmbient, &color);
    RpLightSetColor(pDirect, &color);
}

// 0x6FAB30
float GetDayNightBalance() {
    const auto minutes = CClock::GetMinutesToday();

    if (minutes < 360.0f)
        return 1.0f;

    if (minutes < 420.0f)
        return (420.0f - minutes) * (1.0f / 60.0f);

    if (minutes < 1200.0f)
        return 0.0f;

    if (minutes >= 1260.0f)
        return 1.0f;

    return 1.0f - (1260.0f - minutes) * (1.0f / 60.0f);
}

// 0x70F9B0
bool GraphicsLowQuality() {
    if (g_fx.GetFxQuality() < FX_QUALITY_MEDIUM)
        return false;
    if (RwRasterGetDepth(RwCameraGetRaster(Scene.m_pRwCamera)) < 32)
        return false;
    return true;
}

// 0x5A4150
void WriteRaster(RwRaster* raster, const char* path) {
    assert(raster);
    assert(path && path[0]);

    RwImage* img = RwImageCreate(RwRasterGetWidth(raster), RwRasterGetHeight(raster), RwRasterGetDepth(raster));
    RwImageAllocatePixels(img);
    RwImageSetFromRaster(img, raster);
    RtPNGImageWrite(img, path);
    RwImageDestroy(img);
}

// 0x71DA00
bool CalcScreenCoors(const CVector& vecPoint, CVector* vecOutPos, float* screenX, float* screenY)
{
    return plugin::CallAndReturn<bool, 0x71DA00, const CVector&, CVector*, float*, float*>(vecPoint, vecOutPos, screenX, screenY);

    // TODO: Figure out how to get screen size..
    //CVector screen =  TheCamera.m_mViewMatrix * vecPoint;
    //if (screen.z <= 1.0f)
    //    return false;

    //const float depth = 1.0f / screen.z;

    //CVector2D screenSize{}; // TODO..

    //*vecOutPos = screen * depth * CVector(screenSize.x, screenSize.y, 1.0f);

    //*screenX = screenSize.x * depth / CDraw::ms_fFOV * 70.0f;
    //*screenY = screenSize.y * depth / CDraw::ms_fFOV * 70.0f;

    //return true;
}

// 0x71DAB0
bool CalcScreenCoors(const CVector& vecPoint, CVector* vecOutPos)
{
    return plugin::CallAndReturn<bool, 0x71DAB0, const CVector&, CVector*>(vecPoint, vecOutPos);
}

// 0x541330
void LittleTest() {
    ++g_nNumIm3dDrawCalls;
}

// used only in COccluder::ProcessLineSegment
// 0x71DB80
bool DoesInfiniteLineTouchScreen(float fX, float fY, float fXDir, float fYDir) {
    return plugin::CallAndReturn<bool, 0x71DB80, float, float, float, float>(fX, fY, fXDir, fYDir);
}

// Used only in COcclusion, COccluder, CActiveOccluder
// 0x71E050
bool IsPointInsideLine(float fLineX, float fLineY, float fXDir, float fYDir, float fPointX, float fPointY, float fTolerance) {
    return (fPointX - fLineX) * fYDir - (fPointY - fLineY) * fXDir >= fTolerance;
}

// 0x53E160
void RenderDebugShit() {
    PUSH_RENDERGROUP("RenderDebugShit");
    CTheScripts::RenderTheScriptDebugLines();
#ifndef FINAL
    // if(gbShowCollisionLines) CRenderer::RenderCollisionLines();
    // ThePaths.DisplayPathData();
    // CDebug::DrawLines();
    DefinedState();
#endif
    POP_RENDERGROUP();
}

// 0x53E230
void Render2dStuff() {
    RenderDebugShit(); // NOTSA, temp

    const auto DrawOuterZoomBox = []() {
        CPed* player = FindPlayerPed();
        eWeaponType weaponType = WEAPON_UNARMED;
        if (player)
            weaponType = player->GetActiveWeapon().m_nType;
        eCamMode camMode = CCamera::GetActiveCamera().m_nMode;
        bool firstPersonWeapon = false;
        if (camMode == MODE_SNIPER
            || camMode == MODE_SNIPER_RUNABOUT
            || camMode == MODE_ROCKETLAUNCHER
            || camMode == MODE_ROCKETLAUNCHER_RUNABOUT
            || camMode == MODE_CAMERA
            || camMode == MODE_HELICANNON_1STPERSON)
        {
            firstPersonWeapon = true;
        }

        if ((weaponType == WEAPON_SNIPERRIFLE || weaponType == WEAPON_ROCKET) && firstPersonWeapon) {
            CRGBA black(0, 0, 0, 255);
            if (weaponType == WEAPON_ROCKET)
            {
                CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(180.0f)), black);
                CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(170.0f), SCREEN_WIDTH, SCREEN_HEIGHT), black);
            }
            else
            {
                CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT / 2 - SCREEN_SCALE_Y(210.0f)), black);
                CSprite2d::DrawRect(CRect(0.0f, SCREEN_HEIGHT / 2 + SCREEN_SCALE_Y(210.0f), SCREEN_WIDTH, SCREEN_HEIGHT), black);
            }
            CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH / 2 - SCREEN_SCALE_X(210.0f), SCREEN_HEIGHT), black);
            CSprite2d::DrawRect(CRect(SCREEN_WIDTH / 2 + SCREEN_SCALE_X(210.0f), 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), black);
        }
    };

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(rwRENDERSTATENARENDERSTATE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,          RWRSTATE(rwCULLMODECULLNONE));

    CReplay::Display();
    CPickups::RenderPickUpText();
    if (TheCamera.m_bWideScreenOn && !FrontEndMenuManager.m_bWidescreenOn) TheCamera.DrawBordersForWideScreen();
    DrawOuterZoomBox();
    AudioEngine.DisplayRadioStationName();
    CHud::Draw();
    CSpecialFX::Render2DFXs();
    CUserDisplay::OnscnTimer.ProcessForDisplay();
    CMessages::Display(true);
    CDarkel::DrawMessages();
    CGarages::PrintMessages();
    CFont::DrawFonts();

    // NOTSA: ImGui menu draw loop
    CDebugMenu::ImGuiDrawLoop();
}

// NOTSA
std::wstring UTF8ToUnicode(const std::string &str)
{
    std::wstring out;

    int32 size = MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0);
    if (size)
    {
        std::vector<wchar_t> temp;
        temp.resize(size, 0);

        if (MultiByteToWideChar(CP_UTF8, MB_ERR_INVALID_CHARS, str.data(), str.length(), temp.data(), size))
        {
            out.resize(size);
            std::copy(temp.begin(), temp.end(), out.begin());
        }
    }

    return out;
}

// NOTSA
std::string UnicodeToUTF8(const std::wstring &str)
{
    std::string out;

    int32 size = WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str.data(), str.length(), nullptr, 0, nullptr, nullptr);
    if (size)
    {
        std::vector<char> temp;
        temp.resize(size, 0);

        if (WideCharToMultiByte(CP_UTF8, WC_ERR_INVALID_CHARS, str.data(), str.length(), temp.data(), size, nullptr, nullptr))
        {
            out.resize(size);
            std::copy(temp.begin(), temp.end(), out.begin());
        }
    }

    return out;
}

int32 WindowsCharset = static_cast<int32>(GetACP());

uint16& uiTempBufferIndicesStored = *(uint16*)0xC4B954;
uint16& uiTempBufferVerticesStored = *(uint16*)0xC4B950;
RxVertexIndex(&aTempBufferIndices)[TOTAL_TEMP_BUFFER_INDICES] = *(RxVertexIndex(*)[TOTAL_TEMP_BUFFER_INDICES])0xC4B958;
RxObjSpace3DVertex(&aTempBufferVertices)[TOTAL_TEMP_BUFFER_VERTICES] = *(RxObjSpace3DVertex(*)[TOTAL_TEMP_BUFFER_VERTICES])0xC4D958; // size 1024 - after this there are 2 more arrays like this, both sized 512
RwD3D9Vertex(&aRadiosityVertexBuffer)[TOTAL_RADIOSITY_VERTEX_BUFFER] = *reinterpret_cast<RwD3D9Vertex(*)[TOTAL_RADIOSITY_VERTEX_BUFFER]>(0xC5F958);
