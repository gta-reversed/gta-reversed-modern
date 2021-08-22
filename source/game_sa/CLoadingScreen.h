/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CSprite2d.h"



class  CLoadingScreen {
public:
	
	static int &m_currDisplayedSplash;  // 0x8D093C
	static int &m_numChunksLoaded;      // 0x8D0940
	static int &m_chunkBarAppeared;     // 0x8D0944
	static char *m_PopUpMessage;        // m_PopUpMessage[16] 
	static char *m_LoadingGxtMsg2;      // m_LoadingGxtMsg2[80] 
	static char *m_LoadingGxtMsg1;      // m_LoadingGxtMsg1[80] 
	static bool &m_bActive;             // 0xBAB318
	static bool & m_bWantToPause;       // 0xBAB319
	static bool & m_bPaused;            // 0xBAB31A
	static bool &m_bFading;             // 0xBAB31C
	static bool &m_bLegalScreen;        // 0xBAB31D
	static bool &m_bFadeInNextSplashFromBlack; // 0xBAB31E
	static bool &m_bFadeOutCurrSplashToBlack;  // 0xBAB31F
	static char &m_FadeAlpha;                  // 0xBAB320
	static float &m_StartFadeTime;             // 0xBAB324
	static float &m_ClockTimeOnPause;          // 0xBAB328
	static float &m_PauseTime;                 // 0xBAB32C
	static bool &m_bReadyToDelete;             // 0xBAB33D
	static float &m_timeSinceLastScreen;       // 0xBAB340
	static CSprite2d *m_aSplashes;             // CSprite2d CLoadingScreen::m_aSplashes[7]  0xBAB35C
	
	
	// funcs
	
	static void Shutdown();
    static void RenderSplash();
    static void LoadSplashes(unsigned char bStarting, unsigned char bNvidia);
    static void DisplayMessage(char const* message);
    static void SetLoadingBarMsg(char const* msg1, char const* msg2);
    static double GetClockTime(bool bIgnorePauseTime);
    static void Init(bool unusedflag, bool bLoaded);
    static void Continue();
    static void RenderLoadingBar();
    static void DisplayNextSplash();
    static void StartFading();
    static void DisplayPCScreen();
    static void Update();
    static void DoPCTitleFadeOut();
    static void DoPCTitleFadeIn();
    static void DoPCScreenChange(unsigned int bFinish);
    static void NewChunkLoaded();
	
};

void LoadingScreen(char* msg1, char* msg2);