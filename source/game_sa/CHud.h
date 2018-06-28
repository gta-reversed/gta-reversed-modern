/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CSprite2d.h"

enum DRAW_FADE_STATE {

};

enum eHudSprites {
    HUDSPRITE_FIST,
    HUDSPRITE_SITEM16,
    HUDSPRITE_SITEROCKET,
    HUDSPRITE_RADARDISC,
    HUDSPRITE_RADARRINGPLANE,
    HUDSPRITE_SKIPICON
};

class CPed;

class  CHud {
public:
    static char(*m_BigMessage)[128]; // static char m_BigMessage[7][128]
    static bool &bScriptDontDisplayAreaName;
    static bool &bScriptDontDisplayVehicleName;
    static bool &bScriptForceDisplayWithCounters;
    static bool &bScriptDontDisplayRadar;
    static int &m_LastBreathTime;
    static bool &bDrawClock;
    static int &m_WeaponState;
    static int &m_WeaponFadeTimer;
    static int &m_WeaponTimer;
    static int &m_LastWeapon;
    static int &m_WantedState;
    static int &m_WantedFadeTimer;
    static int &m_WantedTimer;
    static int &m_LastWanted;
    static int &m_DisplayScoreState;
    static int &m_DisplayScoreFadeTimer;
    static int &m_DisplayScoreTimer;
    static int &m_LastDisplayScore;
    static int &m_EnergyLostState;
    static int &m_EnergyLostFadeTimer;
    static int &m_EnergyLostTimer;
    static int &m_LastTimeEnergyLost;
    static char *&m_pVehicleNameToPrint;
    static int &m_VehicleState;
    static int &m_VehicleFadeTimer;
    static int &m_VehicleNameTimer;
    static char *&m_pLastVehicleName;
    static char *&m_pVehicleName;
    static bool &m_bDraw3dMarkers;
    static bool &m_Wants_To_Draw_Hud;
    static float &m_fHelpMessageTime; // in seconds
    static float &m_fHelpMessageBoxWidth; // default 200.0
    static bool &m_bHelpMessagePermanent;
    static float &m_fHelpMessageStatUpdateValue;
    static unsigned short &m_nHelpMessageMaxStatValue;
    static unsigned short &m_nHelpMessageStatId;
    static bool &m_bHelpMessageQuick;
    static int &m_nHelpMessageState;
    static int &m_nHelpMessageFadeTimer;
    static int &m_nHelpMessageTimer;
    static char *m_pHelpMessageToPrint; // static char m_pHelpMessageToPrint[400]
    static char *m_pLastHelpMessage; // static char m_pLastHelpMessage[400]
    static char *m_pHelpMessage; // static char m_pHelpMessage[400]
    static int &m_ZoneState;
    static int &m_ZoneFadeTimer;
    static int &m_ZoneNameTimer;
    static char *m_Message; // static char m_Message[400]
    static char *&m_ZoneToPrint;
    static char *&m_pLastZoneName;
    static char *&m_pZoneName;
    static short &m_ItemToFlash; // -1 - no item
    static bool &bDrawingVitalStats;
    static CSprite2d *Sprites; // static CSprite2d Sprites[6]

    static void Draw(); // called each frame from Render2dStuff()
    static void DrawAfterFade();
    static void DrawAreaName();
    static void DrawBustedWastedMessage();
    static void DrawCrossHairs();
    static float DrawFadeState(DRAW_FADE_STATE fadeState, int arg1);
    static void DrawHelpText();
    static void DrawMissionTimers();
    static void DrawMissionTitle();
    static void DrawOddJobMessage(unsigned char priority);
    static void DrawRadar();
    static void DrawScriptText(unsigned char priority);
    static void DrawSubtitles();
    static void DrawSuccessFailedMessage();
    static void DrawVehicleName();
    static void DrawVitalStats();
    static void GetRidOfAllHudMessages(unsigned char arg0);
    static float GetYPosBasedOnHealth(unsigned char playerId, float pos, char offset);
    static bool HelpMessageDisplayed();
    static void Initialise();
    static void ReInitialise();
    static void ResetWastedText();
    static void SetBigMessage(char* text, unsigned short style);
    static void SetHelpMessage(char const* text, bool quickMessage, bool permanent, bool addToBrief);
    static void SetHelpMessageStatUpdate(unsigned char state, unsigned short statId, float diff, float max); // for 'state', see enum eStatUpdateState (CStats.h)
    static void SetHelpMessageWithNumber(char const* text, int number, bool quickMessage, bool permanent);
    static void SetMessage(char* text);
    static void SetVehicleName(char* name);
    static void SetZoneName(char* name, unsigned char displayState);
    static void Shutdown();
    static void DrawAmmo(CPed* ped, int x, int y, float alpha);
    static void DrawPlayerInfo();
    static void DrawTripSkip();
    static void DrawWanted();
    static void DrawWeaponIcon(CPed* ped, int x, int y, float alpha);
    static void RenderArmorBar(int playerId, int x, int y);
    static void RenderBreathBar(int playerId, int x, int y);
    static void RenderHealthBar(int playerId, int x, int y);
};

extern short &TimerMainCounterHideState;
extern bool &TimerMainCounterWasDisplayed;
extern short *TimerCounterHideState;  // short TimerCounterHideState[4]
extern short *TimerCounterWasDisplayed;  // short TimerCounterWasDisplayed[4]
extern int &OddJob2OffTimer;
extern float &OddJob2XOffset;
extern int &OddJob2Timer;
extern float *BigMessageAlpha;  // float BigMessageAlpha[7]
extern float *BigMessageInUse;  // float BigMessageInUse[7]
extern float *BigMessageX;  // float BigMessageX[7]
extern char *LastBigMessage;  // char LastBigMessage[256]
extern unsigned short &OddJob2On;
extern float &PagerXOffset; // default 150.0