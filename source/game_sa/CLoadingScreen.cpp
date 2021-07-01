/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"


int& CLoadingScreen::m_currDisplayedSplash = *(int*)0x8D093C;
int& CLoadingScreen::m_numChunksLoaded = *(int*)0x8D0940;
int& CLoadingScreen::m_chunkBarAppeared = *(int*)0x8D0944;
char* CLoadingScreen::m_PopUpMessage = (char*)0xBAB268;
char* CLoadingScreen::m_LoadingGxtMsg2 = (char*)0xBAB278;
char* CLoadingScreen::m_LoadingGxtMsg1 = (char*)0xBAB2C8;
bool& CLoadingScreen::m_bActive = *(bool*)0xBAB318;
bool& CLoadingScreen::m_bWantToPause = *(bool*)0xBAB319;
bool& CLoadingScreen::m_bPaused = *(bool*)0xBAB31A;
bool& CLoadingScreen::m_bFading = *(bool*)0xBAB31C;
bool& CLoadingScreen::m_bLegalScreen = *(bool*)0xBAB31D;
bool& CLoadingScreen::m_bFadeInNextSplashFromBlack = *(bool*)0xBAB31E;
bool& CLoadingScreen::m_bFadeOutCurrSplashToBlack = *(bool*)0xBAB31F;
char& CLoadingScreen::m_FadeAlpha = *(char*)0xBAB320;
float& CLoadingScreen::m_StartFadeTime = *(float*)0xBAB324;
float& CLoadingScreen::m_ClockTimeOnPause = *(float*)0xBAB328;
float& CLoadingScreen::m_PauseTime = *(float*)0xBAB32C;
bool& CLoadingScreen::m_bReadyToDelete = *(bool*)0xBAB33D;
float& CLoadingScreen::m_timeSinceLastScreen = *(float*)0xBAB340;
CSprite2d* CLoadingScreen::m_aSplashes = (CSprite2d*)0xBAB35C;  // CSprite2d CLoadingScreen::m_aSplashes[7]

void CLoadingScreen::InjectHooks() {
    ReversibleHooks::Install("CLoadingScreen", "LoadingScreen", 0x53DED0, LoadingScreen);
}

// 0x5902B0
void CLoadingScreen::Init(bool unusedFlag, bool bLoaded) {
    plugin::Call<0x5902B0, bool, bool>(unusedFlag, bLoaded);
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
    plugin::Call<0x5900B0, unsigned char, unsigned char>(bStarting, bNvidia);
}

// 0x590220
void CLoadingScreen::DisplayMessage(char const* message) {
    plugin::Call<0x590220, char const*>(message);
}

// 0x590240
void CLoadingScreen::SetLoadingBarMsg(char const* msg1, char const* msg2) {
    plugin::Call<0x590240, char const*, char const*>(msg1, msg2);
}

// 0x590280
double CLoadingScreen::GetClockTime(bool bIgnorePauseTime) {
    return plugin::CallAndReturn<double, 0x590280, bool>(bIgnorePauseTime);
}

// 0x590320
void CLoadingScreen::Continue() {
    plugin::Call<0x590320>();
}

// 0x590370
void CLoadingScreen::RenderLoadingBar() {
    plugin::Call<0x590370>();
}

// 0x5904D0
void CLoadingScreen::DisplayNextSplash() {
    plugin::Call<0x5904D0>();
}

// 0x590530
void CLoadingScreen::StartFading() {
    plugin::Call<0x590530>();
}

// 0x590570
void CLoadingScreen::DisplayPCScreen() {
    plugin::Call<0x590570>();
}

// 0x5905E0
void CLoadingScreen::Update() {
    plugin::Call<0x5905E0>();
}

// 0x590860
void CLoadingScreen::DoPCTitleFadeOut() {
    plugin::Call<0x590860>();
}

// 0x590990
void CLoadingScreen::DoPCTitleFadeIn() {
    plugin::Call<0x590990>();
}

// 0x590AC0
void CLoadingScreen::DoPCScreenChange(unsigned int bFinish) {
    plugin::Call<0x590AC0, unsigned int>(bFinish);
}

// 0x590D00
void CLoadingScreen::NewChunkLoaded() {
    plugin::Call<0x590D00>();
}

// 0x53DED0
void LoadingScreen(const char* msg1, const char* msg2) {
    if (msg1) {
        CLoadingScreen::SetLoadingBarMsg(msg1, msg2);
    }
    CLoadingScreen::NewChunkLoaded();
}
