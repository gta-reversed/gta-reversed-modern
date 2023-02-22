/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"
#include "platform.h"
#include "LoadingScreen.h"

void CLoadingScreen::InjectHooks() {
    RH_ScopedClass(CLoadingScreen);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x5902B0);
    RH_ScopedInstall(Shutdown, 0x58FF10);
    RH_ScopedInstall(RenderSplash, 0x58FF60);
    RH_ScopedInstall(LoadSplashes, 0x5900B0);
    RH_ScopedInstall(DisplayMessage, 0x590220);
    RH_ScopedInstall(SetLoadingBarMsg, 0x590240);
    RH_ScopedInstall(GetClockTime, 0x590280);
    RH_ScopedInstall(Pause, 0x590310);
    RH_ScopedInstall(Continue, 0x590320);
    RH_ScopedInstall(RenderLoadingBar, 0x590370);
    RH_ScopedInstall(DisplayNextSplash, 0x5904D0);
    RH_ScopedInstall(StartFading, 0x590530);
    RH_ScopedInstall(DisplayPCScreen, 0x590570);
    RH_ScopedInstall(Update, 0x5905E0, { .reversed = false });
    RH_ScopedInstall(DoPCTitleFadeOut, 0x590860);
    RH_ScopedInstall(DoPCTitleFadeIn, 0x590990);
    RH_ScopedInstall(DoPCScreenChange, 0x590AC0);
    RH_ScopedInstall(NewChunkLoaded, 0x590D00);
    RH_ScopedInstall(IsActive, 0x744DB5);

    RH_ScopedGlobalInstall(LoadingScreen, 0x53DED0);
}

// 0x5902B0
void CLoadingScreen::Init(bool unusedFlag, bool loaded) {
    if (IsActive())
        return;

    if (!loaded) {
        LoadSplashes(false, false);
    }

    m_currDisplayedSplash = -1;
    m_bActive = true;
    m_timeSinceLastScreen = GetClockTime();
}

// 0x58FF10
void CLoadingScreen::Shutdown() {
    m_bActive = false;
    for (auto& splash : m_aSplashes) {
        if (splash.m_pTexture) {
            splash.Delete();
        }
    }

    auto slot = CTxdStore::FindTxdSlot("loadscs");
    if (slot != -1) {
        CTxdStore::RemoveTxd(slot);
        CTxdStore::RemoveTxdSlot(slot);
    }
}

// 0x58FF60
void CLoadingScreen::RenderSplash() {
    CSprite2d::InitPerFrame();
    CRect rect(-5.0f, -5.0f, SCREEN_WIDTH + 5.0f, SCREEN_HEIGHT + 5.0f);
    CRGBA color(255, 255, 255, 255);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, RWRSTATE(rwTEXTUREADDRESSCLAMP));

    if (m_bFading) {
        GetCurrentDisplayedSplash().Draw(rect, color);

        if (m_bFadeInNextSplashFromBlack || m_bFadeOutCurrSplashToBlack) {
            color.Set(0, 0, 0);
            color.a = (m_bFadeInNextSplashFromBlack) ? 255 - m_FadeAlpha : m_FadeAlpha;

            CSprite2d::DrawRect(rect, color);
        } else {
            color.a = 255 - m_FadeAlpha;

            m_aSplashes[m_currDisplayedSplash - 1].Draw(rect, color);
        }
    } else if (!m_bReadyToDelete) {
        GetCurrentDisplayedSplash().Draw(rect, color);
    }
}

// 0x5900B0
void CLoadingScreen::LoadSplashes(bool starting, bool nvidia) {
    CFileMgr::SetDir("MODELS\\TXD\\");
    auto slot = CTxdStore::AddTxdSlot("loadscs");
    CTxdStore::LoadTxd(slot, "loadscs.txd");
    CTxdStore::AddRef(slot);
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(slot);

    // srand affects the global state, can not be omitted.
    LARGE_INTEGER pc;
    QueryPerformanceCounter(&pc);
    srand(pc.u.LowPart);

    // NOTSA
    uint8 screenIdx[15];
    std::iota(std::begin(screenIdx), std::end(screenIdx), 0u); // todo: rng::iota

    // exclude 0, title_pcXX.
    std::shuffle(std::begin(screenIdx) + 1, std::end(screenIdx), std::mt19937{std::random_device{}()});

    char name[20];
    for (auto id = 0u; id < MAX_SPLASHES; id++) {
        if (starting) {
            sprintf(name, nvidia ? "nvidia" : "eax");
        } else if (id) {
            sprintf(name, "loadsc%d", screenIdx[id]);
        } else {
#ifdef USE_EU_STUFF
            sprintf(name, "title_pc_EU");
#else
            sprintf(name, "title_pc_US");
#endif
        }
        m_aSplashes[id].SetTexture(name);
    }
    CTxdStore::PopCurrentTxd();
    CFileMgr::SetDir("");
}

// 0x590220
void CLoadingScreen::DisplayMessage(const char* message) {
    strcpy_s(m_PopUpMessage, message);
}

// 0x590240
void CLoadingScreen::SetLoadingBarMsg(const char* msg1, const char* msg2) {
    if (msg1)
        AsciiToGxtChar(msg1, m_LoadingGxtMsg1);
    else
        m_LoadingGxtMsg1[0] = '\0';

    if (msg2)
        AsciiToGxtChar(msg2, m_LoadingGxtMsg2);
    else
        m_LoadingGxtMsg2[0] = '\0';
}

// 0x590280
float CLoadingScreen::GetClockTime(bool ignorePauseTime) {
    float time = (float)GetMillisecondTime() / 1000.0f;
    return ignorePauseTime ? time : time - m_PauseTime;
}

// 0x590310
void CLoadingScreen::Pause() {
    // NOP
}

// 0x590320
void CLoadingScreen::Continue() {
    if (!IsActive())
        return;

    m_bWantToPause = false;
    if (m_bPaused) {
        m_bPaused = false;
        m_PauseTime = GetClockTime() - m_ClockTimeOnPause + m_PauseTime;
    }
}

// 0x590370
void CLoadingScreen::RenderLoadingBar() {
    if (m_bLegalScreen || gfLoadingPercentage <= 0.0f || gfLoadingPercentage >= 100.0f)
        return;

    CSprite2d::DrawBarChart(
        SCREEN_STRETCH_X(50.0f),
        SCREEN_STRETCH_FROM_BOTTOM(40.0f),
        (uint16)SCREEN_STRETCH_X(180.0f),
        (uint8)SCREEN_STRETCH_Y(10.0f),
        gfLoadingPercentage,
        0,
        false,
        true,
        HudColour.GetRGBA(HUD_COLOUR_LIGHT_GRAY, 255),
        CRGBA{ 0, 0, 0, 0 }
    );

    if (m_TimeBarAppeared == 0.0f) {
        m_TimeBarAppeared = GetClockTime();
    }
}

// 0x5904D0, inlined
void CLoadingScreen::DisplayNextSplash() {
    if (m_currDisplayedSplash == 6 || m_bFading)
        return;

    m_FadeAlpha = 255;
    if (RwCameraBeginUpdate(Scene.m_pRwCamera)) {
        DefinedState2d();
        RenderSplash();
        RenderLoadingBar();
        RwCameraEndUpdate(Scene.m_pRwCamera);
        RsCameraShowRaster(Scene.m_pRwCamera);
    }
    m_currDisplayedSplash++;
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

// 0x590860
void CLoadingScreen::DoPCTitleFadeOut() {
    m_bFadeInNextSplashFromBlack = true;
    m_currDisplayedSplash = 0;
    m_bFading = true;

    for (auto i = 0; i < 50; i++) {
        m_FadeAlpha = static_cast<uint8>((float)i * 5.0f);
        DisplayPCScreen();
    }

    m_FadeAlpha = 255;
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

    for (auto i = 50u; i > 0u; i--) {
        m_FadeAlpha = static_cast<uint8>((float)i * 5.0f);
        DisplayPCScreen();
    }

    m_bFadeInNextSplashFromBlack = true;
}

// 0x590AC0
void CLoadingScreen::DoPCScreenChange(uint32 finish) {
    m_bFading = true;

    if (finish) {
        m_bFadeOutCurrSplashToBlack = true;
    } else {
        m_currDisplayedSplash++;
    }

    for (auto i = 20; i > 0; i--) {
        m_FadeAlpha = 0;
        DisplayPCScreen();
    }

    for (auto i = 0u; i < 50u; i++) {
        float alpha = (float)i * 5.0f;
        m_FadeAlpha = (uint8)alpha;

        if (finish || m_bFadeInNextSplashFromBlack) {
            float amplitude = m_bFadeOutCurrSplashToBlack ? (255.0f - alpha) / 255.0f : 1.0f;
            AudioEngine.ServiceLoadingTune(amplitude);
        }
        DisplayPCScreen();
    }
    m_FadeAlpha = 255;
    DisplayPCScreen();
    m_bFadeInNextSplashFromBlack = false;
    m_bFading = false;

    if (finish) {
        Shutdown();
    }
}

// 0x590D00
void CLoadingScreen::NewChunkLoaded() {
    if (!IsActive())
        return;

    ++m_numChunksLoaded;
    if (m_chunkBarAppeared != -1) {
        gfLoadingPercentage = (float)(m_numChunksLoaded - m_chunkBarAppeared) / (140.0f - (float)m_chunkBarAppeared) * 100.0f;
    }

    auto now = GetClockTime();
    auto delta = now - m_timeSinceLastScreen;

    if (m_numChunksLoaded == 140) {
        return DoPCScreenChange((uint32)true);
    }

    if ((m_currDisplayedSplash && delta < 5.0f) || delta < 5.5f) {
        return DisplayPCScreen();
    }

    DoPCScreenChange((uint32)false);
    m_timeSinceLastScreen = now;

    if (m_chunkBarAppeared == -1) {
        m_chunkBarAppeared = m_numChunksLoaded;
    }
}

// 0x5905E0, unused
void CLoadingScreen::Update() {
    plugin::Call<0x5905E0>();
}

// 0x53DED0
void LoadingScreen(const char* msg1, const char* msg2, const char* msg3) {
    if (msg1) {
        CLoadingScreen::SetLoadingBarMsg(msg1, msg2);
    }
    CLoadingScreen::NewChunkLoaded();
}
