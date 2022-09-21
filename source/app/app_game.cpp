#include "StdInc.h"

#include "app.h"

#include "platform.h"

#include "CDebugMenu.h"

#include "Credits.h"
#include "BreakManager_c.h"
#include "MovingThings.h"
#include "PlantMgr.h"
#include "Clouds.h"
#include "Skidmarks.h"
#include "Ropes.h"
#include "Glass.h"
#include "WaterCannons.h"
#include "PostEffects.h"
#include "UserDisplay.h"
#include "Securom.h"
#include "LoadingScreen.h"
#include "ControllerConfigManager.h"
#include "Birds.h"
#include "VehicleRecording.h"
#include "Shadows.h"
#include "Garages.h"

// 0x53E170
void RenderEffects() {
    CBirds::Render();
    CSkidmarks::Render();
    CRopes::Render();
    CGlass::Render();
    CMovingThings::Render();
    CVisibilityPlugins::RenderReallyDrawLastObjects();
    CCoronas::Render();
    g_fx.Render(TheCamera.m_pRwCamera, false);
    CWaterCannons::Render();
    CWaterLevel::RenderWaterFog();
    CClouds::MovingFogRender();
    CClouds::VolumetricCloudsRender();
    if (CHeli::NumberOfSearchLights || CTheScripts::NumberOfScriptSearchLights) {
        CHeli::Pre_SearchLightCone();
        CHeli::RenderAllHeliSearchLights();
        CTheScripts::RenderAllSearchLights();
        CHeli::Post_SearchLightCone();
    }
    CWeaponEffects::Render();
    if (CReplay::Mode != MODE_PLAYBACK && !CPad::GetPad()->DisablePlayerControls) {
        FindPlayerPed()->DrawTriangleForMouseRecruitPed();
    }
    CSpecialFX::Render();
    CVehicleRecording::Render();
    CPointLights::RenderFogEffect();
    CRenderer::RenderFirstPersonVehicle();
    CPostEffects::Render();
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

// 0x53E770
void FrontendIdle() {
    CDraw::CalculateAspectRatio();
    CTimer::Update();
    CSprite2d::SetRecipNearClip();
    CSprite2d::InitPerFrame();
    CFont::InitPerFrame();
    CPad::UpdatePads();

    if (FrontEndMenuManager.m_bActivateMenuNextFrame) {
        FrontEndMenuManager.m_bMenuActive = true;
    }
    FrontEndMenuManager.Process();

    if (RsGlobal.quit != 0)
        return;

    AudioEngine.Service();
    CameraSize(Scene.m_pRwCamera, nullptr, SCREEN_VIEW_WINDOW, CDraw::GetAspectRatio());
    CVisibilityPlugins::SetRenderWareCamera(Scene.m_pRwCamera);

    RwCameraClear(Scene.m_pRwCamera, &gColourTop, rwCAMERACLEARZ);
    if (!RsCameraBeginUpdate(Scene.m_pRwCamera))
        return;

    DefinedState();
    RenderMenus();
    SecuromStateDisplay();
    DoFade();
    CHud::DrawAfterFade();
    CMessages::Display(false);
    CFont::DrawFonts();
    CCredits::Render();
    CFont::DrawFonts();
    CDebug::DebugDisplayTextBuffer();
    FlushObrsPrintfs();

    RwCameraEndUpdate(Scene.m_pRwCamera);
    RsCameraShowRaster(Scene.m_pRwCamera);
}

// 0x53DF40
void RenderScene() {
    bool underWater = CWeather::UnderWaterness <= 0.0f;

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));

    if (CMirrors::TypeOfMirror == MIRROR_TYPE_NONE) {
        CMovingThings::Render_BeforeClouds();
        CClouds::Render();
    }

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE, RWRSTATE(rwSHADEMODEGOURAUD));

    CCarFXRenderer::PreRenderUpdate();
    CRenderer::RenderRoads();
    CCoronas::RenderReflections();
    CRenderer::RenderEverythingBarRoads();
    g_breakMan.Render(false);

    CRenderer::RenderFadingInUnderwaterEntities();

    // If under water render this immediately, otherwise 
    // only after rendering the stuff below.
    if (underWater) {
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
        CWaterLevel::RenderWater();
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
    }

    CRenderer::RenderFadingInEntities();
    if (!CMirrors::bRenderingReflection) {
        float nearClipPlaneOld = RwCameraGetNearClipPlane(Scene.m_pRwCamera);
        float farPlane = RwCameraGetFarClipPlane(Scene.m_pRwCamera);

        float v3;
        float z = CCamera::GetActiveCamera().m_vecFront.z;
        if (z <= 0.0f)
            v3 = -z;
        else
            v3 = 0.0f;

        constexpr float flt_8CD4F0 = 2.0f;
        constexpr float flt_8CD4EC = 5.9604645e-8f; // Same as 1 / (float)(1 << 24) => 1 / 16777216.f ; Not sure if that means anything..

        float unknown = ((flt_8CD4F0 * flt_8CD4EC * 0.25f - flt_8CD4F0 * flt_8CD4EC) * v3 + flt_8CD4F0 * flt_8CD4EC) * (farPlane - nearClipPlaneOld);

        RwCameraEndUpdate(Scene.m_pRwCamera);

        RwCameraSetNearClipPlane(Scene.m_pRwCamera, unknown + nearClipPlaneOld);
        RwCameraBeginUpdate(Scene.m_pRwCamera);
        CShadows::UpdateStaticShadows();
        CShadows::RenderStaticShadows();
        CShadows::RenderStoredShadows();
        RwCameraEndUpdate(Scene.m_pRwCamera);
        RwCameraSetNearClipPlane(Scene.m_pRwCamera, nearClipPlaneOld);

        RwCameraBeginUpdate(Scene.m_pRwCamera);
    }

    g_breakMan.Render(true);
    CPlantMgr::Render();

    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));

    if (CMirrors::TypeOfMirror == MIRROR_TYPE_NONE) {
        CClouds::RenderBottomFromHeight();
        CWeather::RenderRainStreaks();
        CCoronas::RenderSunReflection();
    }

    if (!underWater) {
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
        CWaterLevel::RenderWater();
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
    }

    gRenderStencil();
}

// 0x53E530
void RenderMenus() {
    if (FrontEndMenuManager.m_bMenuActive) {
        FrontEndMenuManager.DrawFrontEnd();
    }
}

// 0x5BF3B0
void GameInit() {
    VERIFY(Initialise3D(nullptr));
    srand(RsTimer());
}

// unused, leftover
// 0x53DF10
void TheGame() {
    printf("Into TheGame!!!");
    CTimer::Initialise();
    CGame::Initialise("DATA\\GTA.DAT");
    LoadingScreen("Starting Game");
}

// 0x53E580
void InitialiseGame() {
    int32 version_number = 78;
    CGame::Initialise(GAME_LEVEL_FILE);
    AudioEngine.Restart();
    if (FrontEndMenuManager.m_bLoadingData) {
        FrontEndMenuManager.m_bStartGameLoading = true;
    }
}

// 0x746060
bool IsForegroundApp() {
    return ForegroundApp;
}
