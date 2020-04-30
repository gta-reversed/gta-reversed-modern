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
bool& CLoadingScreen::m_bPaused = *(bool*)0xBAB319;
bool& CLoadingScreen::m_bWantToPause = *(bool*)0xBAB31A;
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

// Converted from cdecl void CLoadingScreen::Shutdown(void) 0x58FF10 
void CLoadingScreen::Shutdown() {
    plugin::Call<0x58FF10>();
}

// Converted from cdecl void CLoadingScreen::RenderSplash(void) 0x58FF60 
void CLoadingScreen::RenderSplash() {
    plugin::Call<0x58FF60>();
}

// Converted from cdecl void CLoadingScreen::LoadSplashes(uchar bStarting,uchar bNvidia) 0x5900B0 
void CLoadingScreen::LoadSplashes(unsigned char bStarting, unsigned char bNvidia) {
    plugin::Call<0x5900B0, unsigned char, unsigned char>(bStarting, bNvidia);
}

// Converted from cdecl void CLoadingScreen::DisplayMessage(char const *message) 0x590220 
void CLoadingScreen::DisplayMessage(char const* message) {
    plugin::Call<0x590220, char const*>(message);
}

// Converted from cdecl void CLoadingScreen::SetLoadingBarMsg(char const *msg1,char const *msg2) 0x590240 
void CLoadingScreen::SetLoadingBarMsg(char const* msg1, char const* msg2) {
    plugin::Call<0x590240, char const*, char const*>(msg1, msg2);
}

// Converted from cdecl double CLoadingScreen::GetClockTime(bool bIgnorePauseTime) 0x590280 
double CLoadingScreen::GetClockTime(bool bIgnorePauseTime) {
    return plugin::CallAndReturn<double, 0x590280, bool>(bIgnorePauseTime);
}

// Converted from cdecl void CLoadingScreen::Init(bool unusedflag,bool bLoaded) 0x5902B0 
void CLoadingScreen::Init(bool unusedflag, bool bLoaded) {
    plugin::Call<0x5902B0, bool, bool>(unusedflag, bLoaded);
}

// Converted from cdecl void CLoadingScreen::Continue(void) 0x590320 
void CLoadingScreen::Continue() {
    plugin::Call<0x590320>();
}

// Converted from cdecl void CLoadingScreen::RenderLoadingBar(void) 0x590370 
void CLoadingScreen::RenderLoadingBar() {
    plugin::Call<0x590370>();
}

// Converted from cdecl void CLoadingScreen::DisplayNextSplash(void) 0x5904D0 
void CLoadingScreen::DisplayNextSplash() {
    plugin::Call<0x5904D0>();
}

// Converted from cdecl void CLoadingScreen::StartFading(void) 0x590530 
void CLoadingScreen::StartFading() {
    plugin::Call<0x590530>();
}

// Converted from cdecl void CLoadingScreen::DisplayPCScreen(void) 0x590570 
void CLoadingScreen::DisplayPCScreen() {
    plugin::Call<0x590570>();
}

// Converted from cdecl void CLoadingScreen::Update(void) 0x5905E0 
void CLoadingScreen::Update() {
    plugin::Call<0x5905E0>();
}

// Converted from cdecl void CLoadingScreen::DoPCTitleFadeOut(void) 0x590860 
void CLoadingScreen::DoPCTitleFadeOut() {
    plugin::Call<0x590860>();
}

// Converted from cdecl void CLoadingScreen::DoPCTitleFadeIn(void) 0x590990 
void CLoadingScreen::DoPCTitleFadeIn() {
    plugin::Call<0x590990>();
}

// Converted from cdecl void CLoadingScreen::DoPCScreenChange(uint bFinish) 0x590AC0 
void CLoadingScreen::DoPCScreenChange(unsigned int bFinish) {
    plugin::Call<0x590AC0, unsigned int>(bFinish);
}

// Converted from cdecl void CLoadingScreen::NewChunkLoaded(void) 0x590D00 
void CLoadingScreen::NewChunkLoaded() {
    plugin::Call<0x590D00>();
}




