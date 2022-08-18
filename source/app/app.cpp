#include "StdInc.h"

#include "app.h"
#include "platform.h"
#include "RealTimeShadowManager.h"
#include "Credits.h"
#include "Clouds.h"
#include "CustomBuildingRenderer.h"
#include "Plugins/BreakablePlugin/BreakablePlugin.h"

static bool& gammaChanged = *(bool*)(0xC920C8);
static const D3DGAMMARAMP& savedGamma = *reinterpret_cast<const D3DGAMMARAMP*>(0xC8D4C8);

void AppInjectHooks() {

    // RH_ScopedGlobalInstall(DefinedState, 0x734650);
    // RH_ScopedGlobalInstall(DefinedState2d, 0x734750);

    // fail RH_ScopedGlobalInstall(PluginAttach, 0x53D870);
    // fail RH_ScopedGlobalInstall(AppEventHandler, 0x53EC10);

    {
    RH_ScopedNamespaceName("Game");
    RH_ScopedCategory("app");

    RH_ScopedGlobalInstall(RenderEffects, 0x53E170);
    RH_ScopedGlobalInstall(FrontendIdle, 0x53E770);
    RH_ScopedGlobalInstall(DoRWStuffStartOfFrame, 0x53D690);
    RH_ScopedGlobalInstall(DoRWStuffStartOfFrame_Horizon, 0x53D7A0);
    RH_ScopedGlobalInstall(DoRWStuffEndOfFrame, 0x53D840);
    RH_ScopedGlobalInstall(Idle, 0x53E920);
    RH_ScopedGlobalInstall(RenderScene, 0x53DF40);
    RH_ScopedGlobalInstall(RenderMenus, 0x53E530);
    RH_ScopedGlobalInstall(GameInit, 0x5BF3B0);
    RH_ScopedGlobalInstall(TheGame, 0x53DF10);
    RH_ScopedGlobalInstall(InitialiseGame, 0x53E580);
    RH_ScopedGlobalInstall(IsForegroundApp, 0x746060);
    }

    {
    RH_ScopedNamespaceName("Input");
    RH_ScopedCategory("app");

    RH_ScopedGlobalInstall(HandleKeyDown, 0x743DF0);
    RH_ScopedGlobalInstall(HandleKeyUp, 0x7443C0);
    RH_ScopedGlobalInstall(KeyboardHandler, 0x744880);
    RH_ScopedGlobalInstall(HandlePadButtonDown, 0x7448B0);
    RH_ScopedGlobalInstall(HandlePadButtonUp, 0x744930);
    RH_ScopedGlobalInstall(PadHandler, 0x7449F0);
    RH_ScopedGlobalInstall(AttachInputDevices, 0x744A20);
    }

    {
    RH_ScopedNamespaceName("Lights");
    RH_ScopedCategory("app");

    RH_ScopedGlobalInstall(ActivateDirectional, 0x735C80);
    RH_ScopedGlobalInstall(DeActivateDirectional, 0x735C70);
    RH_ScopedGlobalInstall(LightsCreate, 0x5BA520);
    RH_ScopedGlobalInstall(LightsDestroy, 0x735730);
    RH_ScopedGlobalInstall(LightsEnable, 0x735720);
    RH_ScopedGlobalInstall(SetLightsWithTimeOfDayColour, 0x7354E0);
    RH_ScopedGlobalInstall(WorldReplaceNormalLightsWithScorched, 0x7357E0);
    RH_ScopedGlobalInstall(WorldReplaceScorchedLightsWithNormal, 0x735820);
    // RH_ScopedGlobalInstall(AddAnExtraDirectionalLight, 0x735840);
    RH_ScopedGlobalInstall(RemoveExtraDirectionalLights, 0x7359E0);
    RH_ScopedGlobalInstall(SetAmbientAndDirectionalColours, 0x735A20);
    RH_ScopedGlobalInstall(ReSetAmbientAndDirectionalColours, 0x735C40);
    RH_ScopedGlobalInstall(SetFlashyColours, 0x735AB0);
    RH_ScopedGlobalInstall(SetFlashyColours_Mild, 0x735B40);
    RH_ScopedGlobalInstall(SetBrightMarkerColours, 0x735BD0);
    RH_ScopedGlobalInstall(SetDirectionalColours, 0x735D70);
    RH_ScopedGlobalInstall(SetAmbientColoursToIndicateRoadGroup, 0x735C90);
    RH_ScopedGlobalInstall(SetFullAmbient, 0x735D10);
    RH_ScopedGlobalOverloadedInstall(SetAmbientColours, "void", 0x735D30, void(*)());
    RH_ScopedGlobalOverloadedInstall(SetAmbientColours, "color", 0x735D50, void(*)(RwRGBAReal* color));
    RH_ScopedGlobalInstall(SetLightColoursForPedsCarsAndObjects, 0x735D90);
    RH_ScopedGlobalInstall(SetLightsForInfraredVisionHeatObjects, 0x735E40);
    RH_ScopedGlobalInstall(StoreAndSetLightsForInfraredVisionHeatObjects, 0x735E70);
    RH_ScopedGlobalInstall(RestoreLightsForInfraredVisionHeatObjects, 0x735EF0);
    RH_ScopedGlobalInstall(SetLightsForInfraredVisionDefaultObjects, 0x735F20);
    RH_ScopedGlobalInstall(SetLightsForNightVision, 0x735F70);
    RH_ScopedGlobalInstall(GetDayNightBalance, 0x6FAB30);
    }
}

// 0x53D690
bool DoRWStuffStartOfFrame(int16 TopRed, int16 TopGreen, int16 TopBlue, int16 BottomRed, int16 BottomGreen, int16 BottomBlue, int16 Alpha) {
    RwRGBA TopColor{ (uint8)TopRed, (uint8)TopGreen, (uint8)TopBlue, (uint8)Alpha };
    RwRGBA BottomColor{ (uint8)BottomRed, (uint8)BottomGreen, (uint8)BottomBlue, (uint8)Alpha };

    CDraw::CalculateAspectRatio();
    CameraSize(Scene.m_pRwCamera, nullptr, SCREEN_VIEW_WINDOW, SCREEN_ASPECT_RATIO);
    CVisibilityPlugins::SetRenderWareCamera(Scene.m_pRwCamera);
    RwCameraClear(Scene.m_pRwCamera, &TopColor, rwCAMERACLEARZ | rwCAMERACLEARSTENCIL);

    if (!RsCameraBeginUpdate(Scene.m_pRwCamera))
        return false;

    CSprite2d::InitPerFrame();

    if (Alpha != 0)
        CSprite2d::DrawRect(CRect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT), BottomColor, BottomColor, TopColor, TopColor);

    return true;
}

// 0x53D7A0
bool DoRWStuffStartOfFrame_Horizon(int16 TopRed, int16 TopGreen, int16 TopBlue, int16 BottomRed, int16 BottomGreen, int16 BottomBlue, int16 Alpha) {
    CDraw::CalculateAspectRatio();
    CameraSize(Scene.m_pRwCamera, nullptr, SCREEN_VIEW_WINDOW, SCREEN_ASPECT_RATIO);
    CVisibilityPlugins::SetRenderWareCamera(Scene.m_pRwCamera);
    RwCameraClear(Scene.m_pRwCamera, &gColourTop, rwCAMERACLEARZ | rwCAMERACLEARSTENCIL);

    if (!RsCameraBeginUpdate(Scene.m_pRwCamera))
        return false;

    DefinedState();
    TheCamera.m_mViewMatrix.Update();
    CClouds::RenderSkyPolys();

    return true;
}

// 0x53D840
void DoRWStuffEndOfFrame() {
    plugin::Call<0x53D840>();
}

// 0x53EC10
RsEventStatus AppEventHandler(RsEvent event, void* param) {
    return plugin::CallAndReturn<RsEventStatus, 0x53EC10, RsEvent, void*>(event, param);

    switch (event) {
    case rsCAMERASIZE:
        CameraSize(Scene.m_pRwCamera, static_cast<RwRect*>(param), SCREEN_VIEW_WINDOW, DEFAULT_ASPECT_RATIO);
        return rsEVENTPROCESSED;
    case rsINPUTDEVICEATTACH:
        AttachInputDevices();
        return rsEVENTPROCESSED;
    case rsPLUGINATTACH:
        PluginAttach();
        return rsEVENTPROCESSED;
    case rsRWINITIALIZE:
        Initialise3D(param);
        return rsEVENTPROCESSED;
    case rsRWTERMINATE:
        Terminate3D();
        return rsEVENTPROCESSED;
    case rsINITIALIZE:
        CGame::InitialiseOnceBeforeRW();
        RsInitialize();
        return rsEVENTPROCESSED;
    case rsTERMINATE:
        CGame::FinalShutdown();
        return rsEVENTPROCESSED;
    case rsIDLE:
        Idle(param);
        return rsEVENTPROCESSED;
    case rsRENDER:
        FrontendIdle();
        return rsEVENTPROCESSED;
    default:
        return rsEVENTNOTPROCESSED;
    }
}

// 0x53D870
bool PluginAttach() {
    // return plugin::CallAndReturn<bool, 0x53D870>();

    if (!RpWorldPluginAttach()) {
        DEV_LOG("Couldn't attach RpWorldPluginAttach plugin");
        return false;
    }

    if (!RpSkinPluginAttach()) {
        DEV_LOG("Couldn't attach RpSkinPluginAttach plugin");
        return false;
    }

    if (!RtAnimInitialize()) {
        DEV_LOG("Couldn't attach RtAnimInitialize plugin");
        return false;
    }

    if (!RpHAnimPluginAttach()) {
        DEV_LOG("Couldn't attach RpHAnimPluginAttach plugin");
        return false;
    }

    if (!NodeNamePluginAttach()) {
        DEV_LOG("Couldn't attach NodeNamePluginAttach plugin");
        return false;
    }

    if (!CVisibilityPlugins::PluginAttach()) {
        DEV_LOG("Couldn't attach Visibility plugins");
        return false;
    }

    if (!RpAnimBlendPluginAttach()) {
        DEV_LOG("Couldn't attach RpAnimBlend plugin");
        return false;
    }

    if (!CTxdStore::PluginAttach()) {
        DEV_LOG("Couldn't attach CTxdStore plugin");
        return false;
    }

    if (!RpMatFXPluginAttach()) {
        DEV_LOG("Couldn't attach RpMatFX plugin");
        return false;
    }

    if (!RpUVAnimPluginAttach()) {
        DEV_LOG("Couldn't attach RpUVAnim plugin");
        return false;
    }

    if (!CCustomBuildingRenderer::PluginAttach()) {
        DEV_LOG("Couldn't attach CCustomBuildingRenderer plugin");
        return false;
    }

    if (!CCarFXRenderer::RegisterPlugins()) {
        DEV_LOG("Couldn't attach CCarFXRenderer plugin");
        return false;
    }

    if (!(RpAnisotPluginAttach(), BreakablePluginAttach())) {
        DEV_LOG("Couldn't attach RpAnisot plugin");
        return false;
    }

    if (!CCollisionPlugin::PluginAttach()) {
        DEV_LOG("Couldn't attach CCollisionPlugin plugin");
        return false;
    }

    if (!C2dEffect::PluginAttach()) {
        DEV_LOG("Couldn't attach C2dEffect plugin");
        return false;
    }

    if (!PipelinePluginAttach()) {
        DEV_LOG("Couldn't attach Pipeline plugin");
        return false;
    }
    return true;
}

// 0x5BF390
bool Initialise3D(void* param) {
    // todo: CMemoryMgr::PushMemId(MEMID_RENDER);
    RwBool bInitialised = RsRwInitialize(param);
    // CMemoryMgr::PopMemId();
    if (bInitialised) {
        return CGame::InitialiseRenderWare();
    }
    return false;
}

// 0x53D910
void Terminate3D() {
    CGame::ShutdownRenderWare();

    if (gammaChanged) {
        if (auto* device = static_cast<IDirect3DDevice9*>(RwD3D9GetCurrentD3DDevice())) {
            device->SetGammaRamp(0, D3DSGR_CALIBRATE, &savedGamma);
        }
        gammaChanged = false;
    }

    RsRwTerminate();
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

// 0x53E920
void Idle(void* param) {
    /* FPS lock. Limits to 26 frames per second.
    CTimer::GetCurrentTimeInCycles();
    CTimer::GetCyclesPerMillisecond();
    do
        CurrentTimeInCycles = CTimer::GetCurrentTimeInCycles();
    while ( CurrentTimeInCycles / CTimer::GetCyclesPerMillisecond() - g_LastTickTime < 14 );
    v2 = CTimer::GetCurrentTimeInCycles();
    g_LastTickTime = v2 / CTimer::GetCyclesPerMillisecond();
    */

    CTimer::Update();
    CSprite2d::InitPerFrame();
    CFont::InitPerFrame();
    CPointLights::NumLights = 0;
    CGame::Process();
    AudioEngine.Service();
    SetLightsWithTimeOfDayColour(Scene.m_pRpWorld);
    if (!param) {
        return;
    }

    auto& cc = CTimeCycle::m_CurrentColours;
    if (FrontEndMenuManager.m_bMenuActive || TheCamera.GetScreenFadeStatus() == eNameState::NAME_FADE_IN) {
        CDraw::CalculateAspectRatio();
        CameraSize(Scene.m_pRwCamera, nullptr, SCREEN_VIEW_WINDOW, SCREEN_ASPECT_RATIO);
        CVisibilityPlugins::SetRenderWareCamera(Scene.m_pRwCamera);
        RwCameraClear(Scene.m_pRwCamera, &gColourTop, rwCAMERACLEARZ);
        if (!RsCameraBeginUpdate(Scene.m_pRwCamera)) {
            return;
        }
    }

    if (!FrontEndMenuManager.m_bMenuActive && TheCamera.GetScreenFadeStatus() != eNameState::NAME_FADE_IN) {
        CVector2D mousePos{SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f};
        RsMouseSetPos(&mousePos);
        CRenderer::ConstructRenderList();
        CRenderer::PreRender();
        CWorld::ProcessPedsAfterPreRender();
        g_realTimeShadowMan.Update();
        CMirrors::BeforeMainRender();

        bool started;
        if (CWeather::LightningFlash) {
            cc.m_nSkyBottomRed = 255;
            cc.m_nSkyBottomGreen = 255;
            cc.m_nSkyBottomBlue = 255;
            started = DoRWStuffStartOfFrame_Horizon(255, 255, 255, 255, 255, 255, 255);
        } else {
            started = DoRWStuffStartOfFrame_Horizon(cc.m_nSkyTopRed, cc.m_nSkyTopGreen, cc.m_nSkyTopBlue, cc.m_nSkyBottomRed, cc.m_nSkyBottomGreen, cc.m_nSkyBottomBlue, 255);
        }
        if (!started)
            return;

        DefinedState();
        RwCameraSetFarClipPlane(Scene.m_pRwCamera, cc.m_fFarClip);
        Scene.m_pRwCamera->fogPlane = cc.m_fFogStart;
        CMirrors::RenderMirrorBuffer();
        RenderScene();
        CVisibilityPlugins::RenderWeaponPedsForPC();
        CVisibilityPlugins::ms_weaponPedsForPC.Clear();
        RenderEffects();
        if (TheCamera.m_nBlurType == MOTION_BLUR_NONE  || TheCamera.m_nBlurType == MOTION_BLUR_LIGHT_SCENE) {
            if (TheCamera.m_fScreenReductionPercentage > 0.0f) {
                TheCamera.SetMotionBlurAlpha(150);
            }
        }
        TheCamera.RenderMotionBlur();
        Render2dStuff();
    }

    if (FrontEndMenuManager.m_bMenuActive) {
        FrontEndMenuManager.DrawFrontEnd();
    }

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));
    DoFade();
    CHud::DrawAfterFade();
    CMessages::Display(false);
    CFont::DrawFonts();
    CCredits::Render();
    CDebug::DebugDisplayTextBuffer();
    FlushObrsPrintfs();
    RwCameraEndUpdate(Scene.m_pRwCamera);
    RsCameraShowRaster(Scene.m_pRwCamera);
}
