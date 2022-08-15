#include "StdInc.h"

#include "app.h"
#include "platform.h"
#include "RealTimeShadowManager.h"
#include "Credits.h"
#include "Clouds.h"

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
        CameraSize(Scene.m_pRwCamera, nullptr, SCREEN_VIEW_WINDOW, CDraw::GetAspectRatio());
        CVisibilityPlugins::SetRenderWareCamera(Scene.m_pRwCamera);
        RwCameraClear(Scene.m_pRwCamera, &gColourTop, rwCAMERACLEARZ);
        if (!RsCameraBeginUpdate(Scene.m_pRwCamera)) {
            return;
        }
        goto LABEL_16;
    }

    CVector2D mousePos{ SCREEN_WIDTH / 2.0f, SCREEN_HEIGHT / 2.0f };
    RsMouseSetPos(&mousePos);
    CRenderer::ConstructRenderList();
    CRenderer::PreRender();
    CWorld::ProcessPedsAfterPreRender();
    g_realTimeShadowMan.Update();
    CMirrors::BeforeMainRender();

    bool v3;
    if (CWeather::LightningFlash) {
        cc.m_nSkyBottomRed   = 255;
        cc.m_nSkyBottomGreen = 255;
        cc.m_nSkyBottomBlue  = 255;
        v3 = DoRWStuffStartOfFrame_Horizon(255, 255, 255, 255, 255, 255, 255);
    } else {
        v3 = DoRWStuffStartOfFrame_Horizon(cc.m_nSkyTopRed, cc.m_nSkyTopGreen, cc.m_nSkyTopBlue, cc.m_nSkyBottomRed, cc.m_nSkyBottomGreen, cc.m_nSkyBottomBlue, 255);
    }

    if (v3) {
        DefinedState();
        RwCameraSetFarClipPlane(Scene.m_pRwCamera, cc.m_fFarClip);
        Scene.m_pRwCamera->fogPlane = cc.m_fFogStart;
        CMirrors::RenderMirrorBuffer();
        RenderScene();
        CVisibilityPlugins::RenderWeaponPedsForPC();
        CVisibilityPlugins::ms_weaponPedsForPC.Clear();
        RenderEffects();
        if (!TheCamera.m_nBlurType || TheCamera.m_nBlurType == 2) {
            if (TheCamera.m_fScreenReductionPercentage > 0.0f) {
                TheCamera.SetMotionBlurAlpha(150);
            }
        }
        TheCamera.RenderMotionBlur();
        Render2dStuff();

    LABEL_16:
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
}
