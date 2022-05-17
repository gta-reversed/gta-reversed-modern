/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

#include "LoadingScreen.h"

// temp
void RsCameraShowRaster(RwCamera* camera) {
    plugin::Call<0x619440, RwCamera*>(camera);
}

void CLoadingScreen::InjectHooks() {
    RH_ScopedClass(CLoadingScreen);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x5902B0);
    // RH_ScopedInstall(Shutdown, 0x58FF10);
    // RH_ScopedInstall(RenderSplash, 0x58FF60);
    // RH_ScopedInstall(LoadSplashes, 0x5900B0);
    RH_ScopedInstall(DisplayMessage, 0x590220);
    RH_ScopedInstall(SetLoadingBarMsg, 0x590240);
    RH_ScopedInstall(GetClockTime, 0x590280);
    RH_ScopedInstall(Pause, 0x590310);
    RH_ScopedInstall(Continue, 0x590320);
    // RH_ScopedInstall(RenderLoadingBar, 0x590370);
    RH_ScopedInstall(DisplayNextSplash, 0x5904D0);
    RH_ScopedInstall(StartFading, 0x590530);
    RH_ScopedInstall(DisplayPCScreen, 0x590570);
    // RH_ScopedInstall(Update, 0x5905E0);
    RH_ScopedInstall(DoPCTitleFadeOut, 0x590860);
    RH_ScopedInstall(DoPCTitleFadeIn, 0x590990);
    // RH_ScopedInstall(DoPCScreenChange, 0x590AC0);
    // RH_ScopedInstall(NewChunkLoaded, 0x590D00);

    RH_ScopedGlobalInstall(LoadingScreen, 0x53DED0);
}

// 0x5902B0
void CLoadingScreen::Init(bool unusedFlag, bool bLoaded) {
    if (m_bActive)
        return;

    if (!bLoaded) {
        LoadSplashes(false, false);
    }

    m_currDisplayedSplash = -1;
    m_bActive = true;
    m_timeSinceLastScreen = GetClockTime();
}

// 0x58FF10
void CLoadingScreen::Shutdown() {
    plugin::Call<0x58FF10>();
}

// 0x58FF60
void CLoadingScreen::RenderSplash() {
    plugin::Call<0x58FF60>();
}

// 0x5900B0
void CLoadingScreen::LoadSplashes(bool bStarting, bool bNvidia) {
    plugin::Call<0x5900B0, uint8, uint8>(bStarting, bNvidia);
}

// 0x590220
void CLoadingScreen::DisplayMessage(const char* message) {
    strcpy(m_PopUpMessage, message);
}

// 0x590240
void CLoadingScreen::SetLoadingBarMsg(const char* msg1, const char* msg2) {
    if (msg1)
        AsciiToGxtChar(msg1, m_LoadingGxtMsg1);
    else
        m_LoadingGxtMsg1[0] = 0;

    if (msg2)
        AsciiToGxtChar(msg2, m_LoadingGxtMsg2);
    else
        m_LoadingGxtMsg2[0] = 0;
}

// 0x590280
float CLoadingScreen::GetClockTime(bool bIgnorePauseTime) {
    float time = (float)GetMillisecondTime() / 1000.0f;
    return bIgnorePauseTime ? time : time - m_PauseTime;
}

// 0x590310
void CLoadingScreen::Pause() {
    // NOP
}

// 0x590320
void CLoadingScreen::Continue() {
    if (m_bActive) {
        m_bWantToPause = false;
        if (m_bPaused) {
            m_bPaused = false;
            m_PauseTime = GetClockTime() - m_ClockTimeOnPause + m_PauseTime;
        }
    }
}

// 0x590370
void CLoadingScreen::RenderLoadingBar() {
    plugin::Call<0x590370>();
}

// 0x5904D0
void CLoadingScreen::DisplayNextSplash() {
    if (m_currDisplayedSplash != 6 && !m_bFading) {
        m_FadeAlpha = -1;
        if (RwCameraBeginUpdate(Scene.m_pRwCamera)) {
            DefinedState2d();
            RenderSplash();
            RenderLoadingBar();
            RwCameraEndUpdate(Scene.m_pRwCamera);
            RsCameraShowRaster(Scene.m_pRwCamera);
        }
        m_currDisplayedSplash++;
    }
}

// 0x590530
void CLoadingScreen::StartFading() {
    m_bFading = true;
    m_FadeAlpha = 0;
    m_StartFadeTime = GetClockTime(false);
}

// 0x590570
void CLoadingScreen::DisplayPCScreen() {
    if (RwCameraBeginUpdate(Scene.m_pRwCamera)) {
        DefinedState2d();
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
        RenderSplash();
        if (m_currDisplayedSplash > 0 && (!m_bFading || m_currDisplayedSplash != 1)) {
            RenderLoadingBar();
        }
        RwCameraEndUpdate(Scene.m_pRwCamera);
        RsCameraShowRaster(Scene.m_pRwCamera);
    }
}

// 0x5905E0
void CLoadingScreen::Update() {
    plugin::Call<0x5905E0>();
}

// 0x590860
void CLoadingScreen::DoPCTitleFadeOut() {
    m_bFadeInNextSplashFromBlack = true;
    m_currDisplayedSplash = 0;
    m_bFading = true;

    for (auto i = 0; i < 50; i++) {
        m_FadeAlpha = (uint32)((float)i * 5.0f);
        DisplayPCScreen();
    }

    m_FadeAlpha = -1;
    DisplayPCScreen();
    m_bFading = false;
}

// 0x590990
void CLoadingScreen::DoPCTitleFadeIn() {
    m_bFadeInNextSplashFromBlack = true;
    m_currDisplayedSplash = 0;
    m_bFading = true;

    for (auto i = 200; i > 0; i--) {
        m_FadeAlpha = 255;
        DisplayPCScreen();
    }

    for (auto i = 50; i > 0; i--) {
        m_FadeAlpha = (uint32)((float)i * 5.0f);
        DisplayPCScreen();
    }

    m_bFadeInNextSplashFromBlack = true;
}

// 0x590AC0
void CLoadingScreen::DoPCScreenChange(uint32 bFinish) {
    plugin::Call<0x590AC0, uint32>(bFinish);
}

// 0x590D00
void CLoadingScreen::NewChunkLoaded() {
    plugin::Call<0x590D00>();
}

// 0x53DED0
void LoadingScreen(const char* msg1, const char* msg2, const char* msg3) {
    if (msg1) {
        CLoadingScreen::SetLoadingBarMsg(msg1, msg2);
    }
    CLoadingScreen::NewChunkLoaded();
}
