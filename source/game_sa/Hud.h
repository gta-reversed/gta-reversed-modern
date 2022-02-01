/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CSprite2d;

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

class CHud {
public:
    static char(*m_BigMessage)[128]; // static char m_BigMessage[7][128]
    static bool &bScriptDontDisplayAreaName;
    static bool &bScriptDontDisplayVehicleName;
    static bool &bScriptForceDisplayWithCounters;
    static bool &bScriptDontDisplayRadar;
    static int32 &m_LastBreathTime;
    static bool &bDrawClock;
    static int32 &m_WeaponState;
    static int32 &m_WeaponFadeTimer;
    static int32 &m_WeaponTimer;
    static int32 &m_LastWeapon;
    static int32 &m_WantedState;
    static int32 &m_WantedFadeTimer;
    static int32 &m_WantedTimer;
    static int32 &m_LastWanted;
    static int32 &m_DisplayScoreState;
    static int32 &m_DisplayScoreFadeTimer;
    static int32 &m_DisplayScoreTimer;
    static int32 &m_LastDisplayScore;
    static int32 &m_EnergyLostState;
    static int32 &m_EnergyLostFadeTimer;
    static int32 &m_EnergyLostTimer;
    static int32 &m_LastTimeEnergyLost;
    static char *&m_pVehicleNameToPrint;
    static int32 &m_VehicleState;
    static int32 &m_VehicleFadeTimer;
    static int32 &m_VehicleNameTimer;
    static char *&m_pLastVehicleName;
    static char *&m_pVehicleName;
    static bool &m_bDraw3dMarkers;
    static bool &m_Wants_To_Draw_Hud;
    static float &m_fHelpMessageTime; // in seconds
    static float &m_fHelpMessageBoxWidth; // default 200.0
    static bool &m_bHelpMessagePermanent;
    static float &m_fHelpMessageStatUpdateValue;
    static uint16 &m_nHelpMessageMaxStatValue;
    static uint16 &m_nHelpMessageStatId;
    static bool &m_bHelpMessageQuick;
    static int32 &m_nHelpMessageState;
    static int32 &m_nHelpMessageFadeTimer;
    static int32 &m_nHelpMessageTimer;
    static char *m_pHelpMessageToPrint; // static char m_pHelpMessageToPrint[400]
    static char *m_pLastHelpMessage; // static char m_pLastHelpMessage[400]
    static char *m_pHelpMessage; // static char m_pHelpMessage[400]
    static int32 &m_ZoneState;
    static int32 &m_ZoneFadeTimer;
    static int32 &m_ZoneNameTimer;
    static char *m_Message; // static char m_Message[400]
    static char *&m_ZoneToPrint;
    static char *&m_pLastZoneName;
    static char *&m_pZoneName;
    static int16 &m_ItemToFlash; // -1 - no item
    static bool &bDrawingVitalStats;
    static CSprite2d *Sprites; // static CSprite2d Sprites[6]

    static void Draw(); // called each frame from Render2dStuff()
    static void DrawAfterFade();
    static void DrawAreaName();
    static void DrawBustedWastedMessage();
    static void DrawCrossHairs();
    static float DrawFadeState(DRAW_FADE_STATE fadeState, int32 arg1);
    static void DrawHelpText();
    static void DrawMissionTimers();
    static void DrawMissionTitle();
    static void DrawOddJobMessage(uint8 priority);
    static void DrawRadar();
    static void DrawScriptText(uint8 priority);
    static void DrawSubtitles();
    static void DrawSuccessFailedMessage();
    static void DrawVehicleName();
    static void DrawVitalStats();
    static void GetRidOfAllHudMessages(uint8 arg0);
    static float GetYPosBasedOnHealth(uint8 playerId, float pos, char offset);
    static bool HelpMessageDisplayed();
    static void Initialise();
    static void ReInitialise();
    static void ResetWastedText();
    static void SetBigMessage(char* text, uint16 style);
    static void SetHelpMessage(char const* text, bool quickMessage, bool permanent, bool addToBrief);
    static void SetHelpMessageStatUpdate(uint8 state, uint16 statId, float diff, float max); // for 'state', see enum eStatUpdateState (CStats.h)
    static void SetHelpMessageWithNumber(char const* text, int32 number, bool quickMessage, bool permanent);
    static void SetMessage(char* text);
    static void SetVehicleName(char* name);
    static void SetZoneName(char* name, uint8 displayState);
    static void Shutdown();
    static void DrawAmmo(CPed* ped, int32 x, int32 y, float alpha);
    static void DrawPlayerInfo();
    static void DrawTripSkip();
    static void DrawWanted();
    static void DrawWeaponIcon(CPed* ped, int32 x, int32 y, float alpha);
    static void RenderArmorBar(int32 playerId, int32 x, int32 y);
    static void RenderBreathBar(int32 playerId, int32 x, int32 y);
    static void RenderHealthBar(int32 playerId, int32 x, int32 y);
};

extern int16 &TimerMainCounterHideState;
extern bool &TimerMainCounterWasDisplayed;
extern int16 *TimerCounterHideState;  // int16 TimerCounterHideState[4]
extern int16 *TimerCounterWasDisplayed;  // int16 TimerCounterWasDisplayed[4]
extern int32 &OddJob2OffTimer;
extern float &OddJob2XOffset;
extern int32 &OddJob2Timer;
extern float *BigMessageAlpha;  // float BigMessageAlpha[7]
extern float *BigMessageInUse;  // float BigMessageInUse[7]
extern float *BigMessageX;  // float BigMessageX[7]
extern char *LastBigMessage;  // char LastBigMessage[256]
extern uint16 &OddJob2On;
extern float &PagerXOffset; // default 150.0
