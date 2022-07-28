/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Stats.h"

#define M_PI 3.14159265358979323846 // pi
class CSprite2d;

enum DRAW_FADE_STATE {
    WANTED_STATE        = 0,
    ENERGY_LOST_STATE   = 1,
    DISPLAY_SCORE_STATE = 2,
    WEAPON_STATE        = 3,
};

enum eNameState {
    NAME_DONT_SHOW = 0,
    NAME_SHOW      = 1,
    NAME_FADE_IN   = 2,
    NAME_FADE_OUT  = 3,
    NAME_SWITCH    = 4,
};

enum eHudSprite {
    SPRITE_FIST,
    SPRITE_SITE_M16,
    SPRITE_SITE_ROCKET,
    SPRITE_RADAR_DISC,
    SPRITE_RADAR_RING_PLANE,
    SPRITE_SKIP_ICON
};

enum eBigMessageStyle : uint16 {
    BIG_MESSAGE_STYLE_0,
    BIG_MESSAGE_STYLE_1,
    BIG_MESSAGE_STYLE_2,
    BIG_MESSAGE_STYLE_3,
    BIG_MESSAGE_STYLE_4,
    BIG_MESSAGE_STYLE_5,
    BIG_MESSAGE_STYLE_6
};

class CPed;

class CHud {
public:
    static bool&     bScriptDontDisplayAreaName;
    static bool&     bScriptDontDisplayVehicleName;
    static bool&     bScriptForceDisplayWithCounters;
    static bool&     bScriptDontDisplayRadar;

    static inline int32& m_LastBreathTime = *(int32*)0xBAA3FC;
    static bool&     bDrawClock;

    static inline uint32& m_WeaponState = *(uint32*)0xBAA404;
    static inline uint32& m_WeaponFadeTimer = *(uint32*)0xBAA408;
    static inline uint32& m_WeaponTimer = *(uint32*)0xBAA40C;
    static inline uint32& m_LastWeapon = *(uint32*)0xBAA410;

    static inline uint32& m_WantedState = *(uint32*)0xBAA414;
    static inline uint32& m_WantedFadeTimer = *(uint32*)0xBAA418;
    static inline uint32& m_WantedTimer = *(uint32*)0xBAA41C;
    static inline uint32& m_LastWanted = *(uint32*)0xBAA420;

    static inline uint32& m_DisplayScoreState = *(uint32*)0xBAA424;
    static inline uint32& m_DisplayScoreFadeTimer = *(uint32*)0xBAA428;
    static inline uint32& m_DisplayScoreTimer = *(uint32*)0xBAA42C;
    static inline uint32& m_LastDisplayScore = *(uint32*)0xBAA430;

    static inline uint32& m_EnergyLostState = *(uint32*)0xBAA434;
    static inline uint32& m_EnergyLostFadeTimer = *(uint32*)0xBAA438;
    static inline uint32& m_EnergyLostTimer = *(uint32*)0xBAA43C;
    static inline uint32& m_LastTimeEnergyLost = *(uint32*)0xBAA440;

    static char*&    m_pVehicleNameToPrint;
    static eNameState& m_VehicleState;
    static int32&   m_VehicleFadeTimer;
    static int32&   m_VehicleNameTimer;
    static char*&    m_pLastVehicleName;
    static char*&    m_pVehicleName;

    static bool&     m_bDraw3dMarkers;
    static bool&     m_Wants_To_Draw_Hud;

    static float&    m_fHelpMessageTime;     // in seconds
    static float&    m_fHelpMessageBoxWidth; // default 200.0
    static bool&     m_bHelpMessagePermanent;
    static float&    m_fHelpMessageStatUpdateValue;
    static uint16&   m_nHelpMessageMaxStatValue;
    static uint16&   m_nHelpMessageStatId;
    static bool&     m_bHelpMessageQuick;
    static int32&    m_nHelpMessageState;
    static int32&    m_nHelpMessageFadeTimer;
    static int32&    m_nHelpMessageTimer;
    static char      (&m_pHelpMessageToPrint)[400];
    static char      (&m_pLastHelpMessage)[400];
    static char      (&m_pHelpMessage)[400];

    static eNameState& m_ZoneState; // see eNameState
    static int32&      m_ZoneFadeTimer;
    static int32&      m_ZoneNameTimer;

    static inline char (&m_Message)[400] = *(char (*)[400])0xBAB040;
    static inline char (&m_BigMessage)[7][128] = *(char (*)[7][128])0xBAACC0;

    static char*&    m_ZoneToPrint;
    static char*&    m_pLastZoneName;
    static char*&    m_pZoneName;

    static int16&    m_ItemToFlash; // -1 - no item
    static bool&     bDrawingVitalStats;

    static CSprite2d (&Sprites)[6];

public:
    static void InjectHooks();

    static void Initialise();
    static void ReInitialise();
    static void Shutdown();

    static void  GetRidOfAllHudMessages(bool arg0);
    static float GetYPosBasedOnHealth(uint8 playerId, float pos, int8 offset);
    static bool HelpMessageDisplayed();

    static void ResetWastedText();

    static void SetBigMessage(const char* message, eBigMessageStyle style);
    static void SetHelpMessage(char const* text, bool quickMessage, bool permanent, bool addToBrief);
    static void SetHelpMessageStatUpdate(eStatUpdateState state, uint16 statId, float diff, float max);
    static void SetHelpMessageWithNumber(char const* text, int32 number, bool quickMessage, bool permanent);
    static void SetMessage(char* text);
    static void SetVehicleName(char* name);
    static void SetZoneName(char* name, uint8 displayState);

    static void Draw();
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
    static void DrawAmmo(CPed* ped, int32 x, int32 y, float alpha);
    static void DrawPlayerInfo();
    static inline void DrawClock();
    static inline void DrawMoney(const CPlayerInfo& playerInfo, uint8 alpha);
    static inline void DrawWeapon(CPlayerPed* ped0, CPlayerPed* ped1);

    static void DrawTripSkip();
    static void DrawWanted();
    static void DrawWeaponIcon(CPed* ped, int32 x, int32 y, float alpha);
    static void RenderArmorBar(int32 playerId, int32 x, int32 y);
    static void RenderBreathBar(int32 playerId, int32 x, int32 y);
    static void RenderHealthBar(int32 playerId, int32 x, int32 y);
};
