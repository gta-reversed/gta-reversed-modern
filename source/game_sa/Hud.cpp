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
int32& CHud::m_LastBreathTime = *(int32*)0xBAA3FC;
bool& CHud::bDrawClock = *(bool*)0xBAA400;
int32& CHud::m_WeaponState = *(int32*)0xBAA404;
int32& CHud::m_WeaponFadeTimer = *(int32*)0xBAA408;
int32& CHud::m_WeaponTimer = *(int32*)0xBAA40C;
int32& CHud::m_LastWeapon = *(int32*)0xBAA410;
int32& CHud::m_WantedState = *(int32*)0xBAA414;
int32& CHud::m_WantedFadeTimer = *(int32*)0xBAA418;
int32& CHud::m_WantedTimer = *(int32*)0xBAA41C;
int32& CHud::m_LastWanted = *(int32*)0xBAA420;
int32& CHud::m_DisplayScoreState = *(int32*)0xBAA424;
int32& CHud::m_DisplayScoreFadeTimer = *(int32*)0xBAA428;
int32& CHud::m_DisplayScoreTimer = *(int32*)0xBAA42C;
int32& CHud::m_LastDisplayScore = *(int32*)0xBAA430;
int32& CHud::m_EnergyLostState = *(int32*)0xBAA434;
int32& CHud::m_EnergyLostFadeTimer = *(int32*)0xBAA438;
int32& CHud::m_EnergyLostTimer = *(int32*)0xBAA43C;
int32& CHud::m_LastTimeEnergyLost = *(int32*)0xBAA440;
char*& CHud::m_pVehicleNameToPrint = *(char**)0xBAA444;
int32& CHud::m_VehicleState = *(int32*)0xBAA448;
int32& CHud::m_VehicleFadeTimer = *(int32*)0xBAA44C;
int32& CHud::m_VehicleNameTimer = *(int32*)0xBAA450;
char*& CHud::m_pLastVehicleName = *(char**)0xBAA454;
char*& CHud::m_pVehicleName = *(char**)0xBAA458;
bool& CHud::m_bDraw3dMarkers = *(bool*)0xBAA45C;
bool& CHud::m_Wants_To_Draw_Hud = *(bool*)0xBAA45D;
float& CHud::m_fHelpMessageTime = *(float*)0xBAA460;
float& CHud::m_fHelpMessageBoxWidth = *(float*)0x8D0934;
bool& CHud::m_bHelpMessagePermanent = *(bool*)0xBAA464;
float& CHud::m_fHelpMessageStatUpdateValue = *(float*)0xBAA468;
uint16& CHud::m_nHelpMessageMaxStatValue = *(uint16*)0xBAA46C;
uint16& CHud::m_nHelpMessageStatId = *(uint16*)0xBAA470;
bool& CHud::m_bHelpMessageQuick = *(bool*)0xBAA472;
int32& CHud::m_nHelpMessageState = *(int32*)0xBAA474;
int32& CHud::m_nHelpMessageFadeTimer = *(int32*)0xBAA478;
int32& CHud::m_nHelpMessageTimer = *(int32*)0xBAA47C;
char* CHud::m_pHelpMessageToPrint = (char*)0xBAA480;
char* CHud::m_pLastHelpMessage = (char*)0xBAA610;
char* CHud::m_pHelpMessage = (char*)0xBAA7A0;
int32& CHud::m_ZoneState = *(int32*)0xBAA930;
int32& CHud::m_ZoneFadeTimer = *(int32*)0xBAA934;
int32& CHud::m_ZoneNameTimer = *(int32*)0xBAA938;
char* CHud::m_Message = (char*)0xBAB040;
char*& CHud::m_ZoneToPrint = *(char**)0xBAB1D0;
char*& CHud::m_pLastZoneName = *(char**)0xBAB1D4;
char*& CHud::m_pZoneName = *(char**)0xBAB1D8;
int16& CHud::m_ItemToFlash = *(int16*)0xBAB1DC;
bool& CHud::bDrawingVitalStats = *(bool*)0xBAB1DE;
CSprite2d* CHud::Sprites = (CSprite2d*)0xBAB1FC;
int16& TimerMainCounterHideState = *(int16*)0xBAA388;
bool& TimerMainCounterWasDisplayed = *(bool*)0xBAA38A;
int16* TimerCounterHideState = (int16*)0xBAA38C;
int16* TimerCounterWasDisplayed = (int16*)0xBAA394;
int32& OddJob2OffTimer = *(int32*)0xBAA398;
float& OddJob2XOffset = *(float*)0xBAA39C;
int32& OddJob2Timer = *(int32*)0xBAA3A0;
float* BigMessageAlpha = (float*)0xBAA3A4;
float* BigMessageInUse = (float*)0xBAA3C0;
float* BigMessageX = (float*)0xBAA3DC;
char* LastBigMessage = (char*)0xBAABC0;
uint16& OddJob2On = *(uint16*)0xBAB1E0;
float& PagerXOffset = *(float*)0x8D0938;

// 0x58FAE0
void CHud::Draw() {
    plugin::Call<0x58FAE0>();
}

// 0x58D490
void CHud::DrawAfterFade() {
    plugin::Call<0x58D490>();
}

// 0x58AA50
void CHud::DrawAreaName() {
    plugin::Call<0x58AA50>();
}

// 0x58CA50
void CHud::DrawBustedWastedMessage() {
    plugin::Call<0x58CA50>();
}

// 0x58E020
void CHud::DrawCrossHairs() {
    plugin::Call<0x58E020>();
}

// 0x58D580
float CHud::DrawFadeState(DRAW_FADE_STATE fadeState, int32 arg1) {
    return plugin::CallAndReturn<float, 0x58D580, DRAW_FADE_STATE, int32>(fadeState, arg1);
}

// 0x58B6E0
void CHud::DrawHelpText() {
    plugin::Call<0x58B6E0>();
}

// 0x58B180
void CHud::DrawMissionTimers() {
    plugin::Call<0x58B180>();
}

// 0x58D240
void CHud::DrawMissionTitle() {
    plugin::Call<0x58D240>();
}

// 0x58CC80
void CHud::DrawOddJobMessage(uint8 priority) {
    plugin::Call<0x58CC80, uint8>(priority);
}

// 0x58A330
void CHud::DrawRadar() {
    plugin::Call<0x58A330>();
}

// 0x58C080
void CHud::DrawScriptText(uint8 priority) {
    plugin::Call<0x58C080, uint8>(priority);
}

// 0x58C250
void CHud::DrawSubtitles() {
    plugin::Call<0x58C250>();
}

// 0x58C6A0
void CHud::DrawSuccessFailedMessage() {
    plugin::Call<0x58C6A0>();
}

// 0x58AEA0
void CHud::DrawVehicleName() {
    plugin::Call<0x58AEA0>();
}

// 0x589650
void CHud::DrawVitalStats() {
    plugin::Call<0x589650>();
}

// 0x588A50
void CHud::GetRidOfAllHudMessages(uint8 arg0) {
    plugin::Call<0x588A50, uint8>(arg0);
}

// 0x588B60
float CHud::GetYPosBasedOnHealth(uint8 playerId, float pos, char offset) {
    return plugin::CallAndReturn<float, 0x588B60, uint8, float, signed>(playerId, pos, offset);
}

bool CHud::HelpMessageDisplayed() {
    return plugin::CallAndReturn<bool, 0x588B50>();
}

// 0x5BA850
void CHud::Initialise() {
    plugin::Call<0x5BA850>();
}

// 0x588880
void CHud::ReInitialise() {
    plugin::Call<0x588880>();
}

// 0x589070
void CHud::ResetWastedText() {
    plugin::Call<0x589070>();
}

// 0x588FC0
void CHud::SetBigMessage(char* text, uint16 style) {
    plugin::Call<0x588FC0, char*, uint16>(text, style);
}

// 0x588BE0
void CHud::SetHelpMessage(char const* text, bool quickMessage, bool permanent, bool addToBrief) {
    plugin::Call<0x588BE0, char const*, bool, bool, bool>(text, quickMessage, permanent, addToBrief);
}

// 0x588D40
void CHud::SetHelpMessageStatUpdate(uint8 state, uint16 statId, float diff, float max) {
    plugin::Call<0x588D40, uint8, uint16, float, float>(state, statId, diff, max);
}

void CHud::SetHelpMessageWithNumber(char const* text, int32 number, bool quickMessage, bool permanent) {
    plugin::Call<0x588E30, char const*, int32, bool, bool>(text, number, quickMessage, permanent);
}

// 0x588F60
void CHud::SetMessage(char* text) {
    plugin::Call<0x588F60, char*>(text);
}

// 0x588F50
void CHud::SetVehicleName(char* name) {
    plugin::Call<0x588F50, char*>(name);
}

// 0x588BB0
void CHud::SetZoneName(char* name, uint8 displayState) {
    plugin::Call<0x588BB0, char*, uint8>(name, displayState);
}

// 0x588850
void CHud::Shutdown() {
    plugin::Call<0x588850>();
}

// 0x5893B0
void CHud::DrawAmmo(CPed* ped, int32 x, int32 y, float alpha) {
    plugin::Call<0x5893B0, CPed*, int32, int32, float>(ped, x, y, alpha);
}

// 0x58EAF0
void CHud::DrawPlayerInfo() {
    plugin::Call<0x58EAF0>();
}

// 0x58A160
void CHud::DrawTripSkip() {
    plugin::Call<0x58A160>();
}

// 0x58D9A0
void CHud::DrawWanted() {
    plugin::Call<0x58D9A0>();
}

// 0x58D7D0
void CHud::DrawWeaponIcon(CPed* ped, int32 x, int32 y, float alpha) {
    plugin::Call<0x58D7D0, CPed*, int32, int32, float>(ped, x, y, alpha);
}

// 0x5890A0
void CHud::RenderArmorBar(int32 playerId, int32 x, int32 y) {
    plugin::Call<0x5890A0, int32, int32, int32>(playerId, x, y);
}

// 0x589190
void CHud::RenderBreathBar(int32 playerId, int32 x, int32 y) {
    plugin::Call<0x589190, int32, int32, int32>(playerId, x, y);
}

// 0x589270
void CHud::RenderHealthBar(int32 playerId, int32 x, int32 y) {
    plugin::Call<0x589270, int32, int32, int32>(playerId, x, y);
}
