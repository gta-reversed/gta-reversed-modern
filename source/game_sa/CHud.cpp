/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

char(*CHud::m_BigMessage)[128] = (char(*)[128])0xBAACC0;
bool& CHud::bScriptDontDisplayAreaName = *(bool*)0xBAA3F8;
bool& CHud::bScriptDontDisplayVehicleName = *(bool*)0xBAA3F9;
bool& CHud::bScriptForceDisplayWithCounters = *(bool*)0xBAA3FA;
bool& CHud::bScriptDontDisplayRadar = *(bool*)0xBAA3FB;
int& CHud::m_LastBreathTime = *(int*)0xBAA3FC;
bool& CHud::bDrawClock = *(bool*)0xBAA400;
int& CHud::m_WeaponState = *(int*)0xBAA404;
int& CHud::m_WeaponFadeTimer = *(int*)0xBAA408;
int& CHud::m_WeaponTimer = *(int*)0xBAA40C;
int& CHud::m_LastWeapon = *(int*)0xBAA410;
int& CHud::m_WantedState = *(int*)0xBAA414;
int& CHud::m_WantedFadeTimer = *(int*)0xBAA418;
int& CHud::m_WantedTimer = *(int*)0xBAA41C;
int& CHud::m_LastWanted = *(int*)0xBAA420;
int& CHud::m_DisplayScoreState = *(int*)0xBAA424;
int& CHud::m_DisplayScoreFadeTimer = *(int*)0xBAA428;
int& CHud::m_DisplayScoreTimer = *(int*)0xBAA42C;
int& CHud::m_LastDisplayScore = *(int*)0xBAA430;
int& CHud::m_EnergyLostState = *(int*)0xBAA434;
int& CHud::m_EnergyLostFadeTimer = *(int*)0xBAA438;
int& CHud::m_EnergyLostTimer = *(int*)0xBAA43C;
int& CHud::m_LastTimeEnergyLost = *(int*)0xBAA440;
char*& CHud::m_pVehicleNameToPrint = *(char**)0xBAA444;
int& CHud::m_VehicleState = *(int*)0xBAA448;
int& CHud::m_VehicleFadeTimer = *(int*)0xBAA44C;
int& CHud::m_VehicleNameTimer = *(int*)0xBAA450;
char*& CHud::m_pLastVehicleName = *(char**)0xBAA454;
char*& CHud::m_pVehicleName = *(char**)0xBAA458;
bool& CHud::m_bDraw3dMarkers = *(bool*)0xBAA45C;
bool& CHud::m_Wants_To_Draw_Hud = *(bool*)0xBAA45D;
float& CHud::m_fHelpMessageTime = *(float*)0xBAA460;
float& CHud::m_fHelpMessageBoxWidth = *(float*)0x8D0934;
bool& CHud::m_bHelpMessagePermanent = *(bool*)0xBAA464;
float& CHud::m_fHelpMessageStatUpdateValue = *(float*)0xBAA468;
unsigned short& CHud::m_nHelpMessageMaxStatValue = *(unsigned short*)0xBAA46C;
unsigned short& CHud::m_nHelpMessageStatId = *(unsigned short*)0xBAA470;
bool& CHud::m_bHelpMessageQuick = *(bool*)0xBAA472;
int& CHud::m_nHelpMessageState = *(int*)0xBAA474;
int& CHud::m_nHelpMessageFadeTimer = *(int*)0xBAA478;
int& CHud::m_nHelpMessageTimer = *(int*)0xBAA47C;
char* CHud::m_pHelpMessageToPrint = (char*)0xBAA480;
char* CHud::m_pLastHelpMessage = (char*)0xBAA610;
char* CHud::m_pHelpMessage = (char*)0xBAA7A0;
int& CHud::m_ZoneState = *(int*)0xBAA930;
int& CHud::m_ZoneFadeTimer = *(int*)0xBAA934;
int& CHud::m_ZoneNameTimer = *(int*)0xBAA938;
char* CHud::m_Message = (char*)0xBAB040;
char*& CHud::m_ZoneToPrint = *(char**)0xBAB1D0;
char*& CHud::m_pLastZoneName = *(char**)0xBAB1D4;
char*& CHud::m_pZoneName = *(char**)0xBAB1D8;
short& CHud::m_ItemToFlash = *(short*)0xBAB1DC;
bool& CHud::bDrawingVitalStats = *(bool*)0xBAB1DE;
CSprite2d* CHud::Sprites = (CSprite2d*)0xBAB1FC;
short& TimerMainCounterHideState = *(short*)0xBAA388;
bool& TimerMainCounterWasDisplayed = *(bool*)0xBAA38A;
short* TimerCounterHideState = (short*)0xBAA38C;
short* TimerCounterWasDisplayed = (short*)0xBAA394;
int& OddJob2OffTimer = *(int*)0xBAA398;
float& OddJob2XOffset = *(float*)0xBAA39C;
int& OddJob2Timer = *(int*)0xBAA3A0;
float* BigMessageAlpha = (float*)0xBAA3A4;
float* BigMessageInUse = (float*)0xBAA3C0;
float* BigMessageX = (float*)0xBAA3DC;
char* LastBigMessage = (char*)0xBAABC0;
unsigned short& OddJob2On = *(unsigned short*)0xBAB1E0;
float& PagerXOffset = *(float*)0x8D0938;

// Converted from cdecl void CHud::Draw(void) 0x58FAE0
void CHud::Draw() {
    plugin::Call<0x58FAE0>();
}

// Converted from cdecl void CHud::DrawAfterFade(void) 0x58D490
void CHud::DrawAfterFade() {
    plugin::Call<0x58D490>();
}

// Converted from cdecl void CHud::DrawAreaName(void) 0x58AA50
void CHud::DrawAreaName() {
    plugin::Call<0x58AA50>();
}

// Converted from cdecl void CHud::DrawBustedWastedMessage(void) 0x58CA50
void CHud::DrawBustedWastedMessage() {
    plugin::Call<0x58CA50>();
}

// Converted from cdecl void CHud::DrawCrossHairs(void) 0x58E020
void CHud::DrawCrossHairs() {
    plugin::Call<0x58E020>();
}

// Converted from cdecl float CHud::DrawFadeState(DRAW_FADE_STATE fadeState,int) 0x58D580
float CHud::DrawFadeState(DRAW_FADE_STATE fadeState, int arg1) {
    return plugin::CallAndReturn<float, 0x58D580, DRAW_FADE_STATE, int>(fadeState, arg1);
}

// Converted from cdecl void CHud::DrawHelpText(void) 0x58B6E0
void CHud::DrawHelpText() {
    plugin::Call<0x58B6E0>();
}

// Converted from cdecl void CHud::DrawMissionTimers(void) 0x58B180
void CHud::DrawMissionTimers() {
    plugin::Call<0x58B180>();
}

// Converted from cdecl void CHud::DrawMissionTitle(void) 0x58D240
void CHud::DrawMissionTitle() {
    plugin::Call<0x58D240>();
}

// Converted from cdecl void CHud::DrawOddJobMessage(uint8_t priority) 0x58CC80
void CHud::DrawOddJobMessage(unsigned char priority) {
    plugin::Call<0x58CC80, unsigned char>(priority);
}

// Converted from cdecl void CHud::DrawRadar(void) 0x58A330
void CHud::DrawRadar() {
    plugin::Call<0x58A330>();
}

// Converted from cdecl void CHud::DrawScriptText(uint8_t priority) 0x58C080
void CHud::DrawScriptText(unsigned char priority) {
    plugin::Call<0x58C080, unsigned char>(priority);
}

// Converted from cdecl void CHud::DrawSubtitles(void) 0x58C250
void CHud::DrawSubtitles() {
    plugin::Call<0x58C250>();
}

// Converted from cdecl void CHud::DrawSuccessFailedMessage(void) 0x58C6A0
void CHud::DrawSuccessFailedMessage() {
    plugin::Call<0x58C6A0>();
}

// Converted from cdecl void CHud::DrawVehicleName(void) 0x58AEA0
void CHud::DrawVehicleName() {
    plugin::Call<0x58AEA0>();
}

// Converted from cdecl void CHud::DrawVitalStats(void) 0x589650
void CHud::DrawVitalStats() {
    plugin::Call<0x589650>();
}

// Converted from cdecl void CHud::GetRidOfAllHudMessages(uint8_t) 0x588A50
void CHud::GetRidOfAllHudMessages(unsigned char arg0) {
    plugin::Call<0x588A50, unsigned char>(arg0);
}

// Converted from cdecl float CHud::GetYPosBasedOnHealth(uint8_t playerId,float pos,signed char offset) 0x588B60
float CHud::GetYPosBasedOnHealth(unsigned char playerId, float pos, char offset) {
    return plugin::CallAndReturn<float, 0x588B60, unsigned char, float, signed>(playerId, pos, offset);
}

bool CHud::HelpMessageDisplayed() {
    return plugin::CallAndReturn<bool, 0x588B50>();
}

// Converted from cdecl void CHud::Initialise(void) 0x5BA850
void CHud::Initialise() {
    plugin::Call<0x5BA850>();
}

// Converted from cdecl void CHud::ReInitialise(void) 0x588880
void CHud::ReInitialise() {
    plugin::Call<0x588880>();
}

// Converted from cdecl void CHud::ResetWastedText(void) 0x589070
void CHud::ResetWastedText() {
    plugin::Call<0x589070>();
}

// Converted from cdecl void CHud::SetBigMessage(char *text,uint16_t style) 0x588FC0
void CHud::SetBigMessage(char* text, unsigned short style) {
    plugin::Call<0x588FC0, char*, unsigned short>(text, style);
}

// Converted from cdecl void CHud::SetHelpMessage(char const*text,bool quickMessage,bool permanent,bool addToBrief) 0x588BE0
void CHud::SetHelpMessage(char const* text, bool quickMessage, bool permanent, bool addToBrief) {
    plugin::Call<0x588BE0, char const*, bool, bool, bool>(text, quickMessage, permanent, addToBrief);
}

// Converted from cdecl void CHud::SetHelpMessageStatUpdate(uint8_t state,uint16_t statId,float diff,float max) 0x588D40
void CHud::SetHelpMessageStatUpdate(unsigned char state, unsigned short statId, float diff, float max) {
    plugin::Call<0x588D40, unsigned char, unsigned short, float, float>(state, statId, diff, max);
}

void CHud::SetHelpMessageWithNumber(char const* text, int number, bool quickMessage, bool permanent) {
    plugin::Call<0x588E30, char const*, int, bool, bool>(text, number, quickMessage, permanent);
}

// Converted from cdecl void CHud::SetMessage(char *text) 0x588F60
void CHud::SetMessage(char* text) {
    plugin::Call<0x588F60, char*>(text);
}

// Converted from cdecl void CHud::SetVehicleName(char *name) 0x588F50
void CHud::SetVehicleName(char* name) {
    plugin::Call<0x588F50, char*>(name);
}

// Converted from cdecl void CHud::SetZoneName(char *name,uint8_t displayState) 0x588BB0
void CHud::SetZoneName(char* name, unsigned char displayState) {
    plugin::Call<0x588BB0, char*, unsigned char>(name, displayState);
}

// Converted from cdecl void CHud::Shutdown(void) 0x588850
void CHud::Shutdown() {
    plugin::Call<0x588850>();
}

// Converted from cdecl void CHud::DrawAmmo(CPed *ped, int x, int y, float alpha) 0x5893B0
void CHud::DrawAmmo(CPed* ped, int x, int y, float alpha) {
    plugin::Call<0x5893B0, CPed*, int, int, float>(ped, x, y, alpha);
}

// Converted from cdecl void CHud::DrawPlayerInfo(void) 0x58EAF0
void CHud::DrawPlayerInfo() {
    plugin::Call<0x58EAF0>();
}

// Converted from cdecl void CHud::DrawTripSkip(void) 0x58A160
void CHud::DrawTripSkip() {
    plugin::Call<0x58A160>();
}

// Converted from cdecl void CHud::DrawWanted(void) 0x58D9A0
void CHud::DrawWanted() {
    plugin::Call<0x58D9A0>();
}

// Converted from cdecl void CHud::DrawWeaponIcon(CPed *ped, int x, int y, float alpha) 0x58D7D0
void CHud::DrawWeaponIcon(CPed* ped, int x, int y, float alpha) {
    plugin::Call<0x58D7D0, CPed*, int, int, float>(ped, x, y, alpha);
}

// Converted from cdecl void CHud::RenderArmorBar(int playerId, int x, int y) 0x5890A0
void CHud::RenderArmorBar(int playerId, int x, int y) {
    plugin::Call<0x5890A0, int, int, int>(playerId, x, y);
}

// Converted from cdecl void CHud::RenderBreathBar(int playerId, int x, int y) 0x589190
void CHud::RenderBreathBar(int playerId, int x, int y) {
    plugin::Call<0x589190, int, int, int>(playerId, x, y);
}

// Converted from cdecl void CHud::RenderHealthBar(int playerId, int x, int y) 0x589270
void CHud::RenderHealthBar(int playerId, int x, int y) {
    plugin::Call<0x589270, int, int, int>(playerId, x, y);
}
