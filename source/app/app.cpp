#include "StdInc.h"

#include "app.h"
#include "platform.h"
#include "Shadows.h"
#include "PlantMgr.h"
#include "MovingThings.h"
#include "BreakManager_c.h"
#include "RealTimeShadowManager.h"
#include "Credits.h"
#include "Clouds.h"
#include "CarFXRenderer.h"

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

void RenderEffects() {
    plugin::Call<0x53E170>();
}


// 0x53DF40
void RenderScene() {
    bool underWater = CWeather::UnderWaterness <= 0.0f;

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));

    if (CMirrors::TypeOfMirror == MIRROR_TYPE_0) {
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

    if (CMirrors::TypeOfMirror == MIRROR_TYPE_0) {
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
