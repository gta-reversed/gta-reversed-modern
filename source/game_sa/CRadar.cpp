/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

unsigned int MAX_RADAR_SPRITES = 64;
unsigned int MAX_RADAR_TRACES = 175;
unsigned int MAX_AIRSTRIP_INFOS = 4;
unsigned int MAX_RADAR_WIDTH_TILES = 12;
unsigned int MAX_RADAR_HEIHGT_TILES = 12;

float& CRadar::m_fRadarOrientation = *(float*)0xBA8310;
float& CRadar::m_radarRange = *(float*)0xBA8314;
unsigned short* CRadar::MapLegendList = (unsigned short*)0xBA8318;
unsigned short& CRadar::MapLegendCounter = *(unsigned short*)0xBA86B8;
CRGBA* CRadar::ArrowBlipColour = (CRGBA*)0xBA86D4;
tRadarTrace* CRadar::ms_RadarTrace = (tRadarTrace*)0xBA86F0;
CVector2D& CRadar::vec2DRadarOrigin = *(CVector2D*)0xBAA248;
CSprite2d* CRadar::RadarBlipSprites = (CSprite2d*)0xBAA250;
CRect& CRadar::m_radarRect = *(CRect*)0x8D0920;
unsigned char& CRadar::airstrip_location = *(unsigned char*)0xBA8300;
int& CRadar::airstrip_blip = *(int*)0xBA8304;
airstrip_info* airstrip_table = (airstrip_info*)0x8D06E0;
int* gRadarTextures = (int*)0xBA8478;

// Converted from cdecl void CRadar::LoadTextures(void) 0x5827D0
void CRadar::LoadTextures()
{
    ((void(__cdecl*)())0x5827D0)();
}

// Converted from cdecl int CRadar::GetNewUniqueBlipIndex(int blipArrId) 0x582820
int CRadar::GetNewUniqueBlipIndex(int blipArrId)
{
    return ((int(__cdecl*)(int))0x582820)(blipArrId);
}

// Converted from cdecl int CRadar::GetActualBlipArrayIndex(int blipIndex) 0x582870
int CRadar::GetActualBlipArrayIndex(int blipIndex)
{
    return ((int(__cdecl*)(int))0x582870)(blipIndex);
}

// Converted from cdecl void CRadar::DrawLegend(int x,int y,int blipType) 0x5828A0
void CRadar::DrawLegend(int x, int y, int blipType)
{
    ((void(__cdecl*)(int, int, int))0x5828A0)(x, y, blipType);
}

// Converted from cdecl float CRadar::LimitRadarPoint(CVector2D &point) 0x5832F0
float CRadar::LimitRadarPoint(CVector2D& point)
{
    return ((float(__cdecl*)(CVector2D&))0x5832F0)(point);
}

// Converted from cdecl void CRadar::LimitToMap(float *pX,float *pY) 0x583350
void CRadar::LimitToMap(float* pX, float* pY)
{
    ((void(__cdecl*)(float*, float*))0x583350)(pX, pY);
}

// Converted from cdecl uchar CRadar::CalculateBlipAlpha(float distance) 0x583420
unsigned char CRadar::CalculateBlipAlpha(float distance)
{
    return ((unsigned char(__cdecl*)(float))0x583420)(distance);
}

// Converted from cdecl void CRadar::TransformRadarPointToScreenSpace(CVector2D &out,CVector2D const&in) 0x583480
void CRadar::TransformRadarPointToScreenSpace(CVector2D& out, CVector2D const& in)
{
    ((void(__cdecl*)(CVector2D&, CVector2D const&))0x583480)(out, in);
}

// Converted from cdecl void CRadar::TransformRealWorldPointToRadarSpace(CVector2D &out,CVector2D const&in) 0x583530
void CRadar::TransformRealWorldPointToRadarSpace(CVector2D& out, CVector2D const& in)
{
    ((void(__cdecl*)(CVector2D&, CVector2D const&))0x583530)(out, in);
}

// Converted from cdecl void CRadar::TransformRadarPointToRealWorldSpace(CVector2D &out,CVector2D const&in) 0x5835A0
void CRadar::TransformRadarPointToRealWorldSpace(CVector2D& out, CVector2D const& in)
{
    ((void(__cdecl*)(CVector2D&, CVector2D const&))0x5835A0)(out, in);
}

// Converted from cdecl void CRadar::TransformRealWorldToTexCoordSpace(CVector2D &out,CVector2D const&in,int,int) 0x583600
void CRadar::TransformRealWorldToTexCoordSpace(CVector2D& out, CVector2D const& in, int arg2, int arg3)
{
    ((void(__cdecl*)(CVector2D&, CVector2D const&, int, int))0x583600)(out, in, arg2, arg3);
}

// Converted from cdecl void CRadar::CalculateCachedSinCos(void) 0x583670
void CRadar::CalculateCachedSinCos()
{
    ((void(__cdecl*)())0x583670)();
}

// Converted from cdecl int CRadar::SetCoordBlip(eBlipType type,CVector posn,uint,eBlipDisplay blipDisplay, char* scriptName) 0x583820
int CRadar::SetCoordBlip(eBlipType type, CVector posn, _IGNORED_ unsigned int arg2, eBlipDisplay blipDisplay, _IGNORED_ char* scriptName)
{
    return ((int(__cdecl*)(eBlipType, CVector, unsigned int, eBlipDisplay, char*))0x583820)(type, posn, arg2, blipDisplay, scriptName);
}

// Converted from cdecl int CRadar::SetShortRangeCoordBlip(eBlipType type,CVector posn,uint,eBlipDisplay blipDisplay, char* scriptName) 0x583920
int CRadar::SetShortRangeCoordBlip(eBlipType type, CVector posn, unsigned int arg2, eBlipDisplay blipDisplay, char* scriptName)
{
    return ((int(__cdecl*)(eBlipType, CVector, unsigned int, eBlipDisplay, char*))0x583920)(type, posn, arg2, blipDisplay, scriptName);
}

// Converted from cdecl int CRadar::SetEntityBlip(eBlipType type,int entityHandle,uint,eBlipDisplay blipDisplay) 0x5839A0
int CRadar::SetEntityBlip(eBlipType type, int entityHandle, unsigned int arg2, eBlipDisplay blipDisplay)
{
    return ((int(__cdecl*)(eBlipType, int, unsigned int, eBlipDisplay))0x5839A0)(type, entityHandle, arg2, blipDisplay);
}

// Converted from cdecl void CRadar::ChangeBlipColour(int blipIndex,uint color) 0x583AB0
void CRadar::ChangeBlipColour(int blipIndex, unsigned int color)
{
    ((void(__cdecl*)(int, unsigned int))0x583AB0)(blipIndex, color);
}

// Converted from cdecl bool CRadar::HasThisBlipBeenRevealed(int blipArrId) 0x583AF0
bool CRadar::HasThisBlipBeenRevealed(int blipArrId)
{
    return ((bool(__cdecl*)(int))0x583AF0)(blipArrId);
}

// Converted from cdecl bool CRadar::DisplayThisBlip(int spriteId,signed char priority) 0x583B40
bool CRadar::DisplayThisBlip(int spriteId, char priority)
{
    return ((bool(__cdecl*)(int, signed))0x583B40)(spriteId, priority);
}

// Converted from cdecl void CRadar::ChangeBlipBrightness(int blipIndex,int brightness) 0x583C70
void CRadar::ChangeBlipBrightness(int blipIndex, int brightness)
{
    ((void(__cdecl*)(int, int))0x583C70)(blipIndex, brightness);
}

// Converted from cdecl void CRadar::ChangeBlipScale(int blipIndex,int size) 0x583CC0
void CRadar::ChangeBlipScale(int blipIndex, int size)
{
    ((void(__cdecl*)(int, int))0x583CC0)(blipIndex, size);
}

// Converted from cdecl void CRadar::ChangeBlipDisplay(int blipIndex,eBlipDisplay blipDisplay) 0x583D20
void CRadar::ChangeBlipDisplay(int blipIndex, eBlipDisplay blipDisplay)
{
    ((void(__cdecl*)(int, eBlipDisplay))0x583D20)(blipIndex, blipDisplay);
}

// Converted from cdecl void CRadar::SetBlipSprite(int blipIndex,int spriteId) 0x583D70
void CRadar::SetBlipSprite(int blipIndex, int spriteId)
{
    ((void(__cdecl*)(int, int))0x583D70)(blipIndex, spriteId);
}

// Converted from cdecl void CRadar::SetBlipAlwaysDisplayInZoom(int blipIndex,uchar display) 0x583DB0
void CRadar::SetBlipAlwaysDisplayInZoom(int blipIndex, unsigned char display)
{
    ((void(__cdecl*)(int, unsigned char))0x583DB0)(blipIndex, display);
}

// Converted from cdecl void CRadar::SetBlipFade(int blipIndex,uchar fade) 0x583E00
void CRadar::SetBlipFade(int blipIndex, unsigned char fade)
{
    ((void(__cdecl*)(int, unsigned char))0x583E00)(blipIndex, fade);
}

// Converted from cdecl void CRadar::SetCoordBlipAppearance(int blipIndex,uchar appearance) 0x583E50
void CRadar::SetCoordBlipAppearance(int blipIndex, unsigned char appearance)
{
    ((void(__cdecl*)(int, unsigned char))0x583E50)(blipIndex, appearance);
}

// Converted from cdecl void CRadar::SetBlipFriendly(int blipIndex,uchar friendly) 0x583EB0
void CRadar::SetBlipFriendly(int blipIndex, unsigned char friendly)
{
    ((void(__cdecl*)(int, unsigned char))0x583EB0)(blipIndex, friendly);
}

// Converted from cdecl void CRadar::SetBlipEntryExit(int blipIndex,CEntryExit *enex) 0x583F00
void CRadar::SetBlipEntryExit(int blipIndex, CEntryExit* enex)
{
    ((void(__cdecl*)(int, CEntryExit*))0x583F00)(blipIndex, enex);
}

// Converted from cdecl void CRadar::ShowRadarTrace(float x,float y,uint size,uchar red,uchar green,uchar blue,uchar alpha) 0x583F40
void CRadar::ShowRadarTrace(float x, float y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha)
{
    ((void(__cdecl*)(float, float, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char))0x583F40)(x, y, size, red, green, blue, alpha);
}

// Converted from cdecl void CRadar::ShowRadarTraceWithHeight(float x,float y,uint size,uchar red,uchar green,uchar blue,uchar alpha,uchar type) 0x584070
void CRadar::ShowRadarTraceWithHeight(float x, float y, unsigned int size, unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha, unsigned char type)
{
    ((void(__cdecl*)(float, float, unsigned int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char))0x584070)(x, y, size, red, green, blue, alpha, type);
}

// Converted from cdecl void CRadar::ShowRadarMarker(CVector posn,uint color,float radius) 0x584480
void CRadar::ShowRadarMarker(CVector posn, unsigned int color, float radius)
{
    ((void(__cdecl*)(CVector, unsigned int, float))0x584480)(posn, color, radius);
}

// Converted from cdecl uint CRadar::GetRadarTraceColour(uint color,uchar bright, uchar friendly) 0x584770
unsigned int CRadar::GetRadarTraceColour(unsigned int color, unsigned char bright, unsigned char friendly)
{
    return ((unsigned int(__cdecl*)(unsigned int, unsigned char, unsigned char))0x584770)(color, bright, friendly);
}

// Converted from cdecl void CRadar::DrawRotatingRadarSprite(CSprite2d *sprite,float x,float y,float angle,uint width, uint height, CRGBA const&color) 0x584850
void CRadar::DrawRotatingRadarSprite(CSprite2d* sprite, float x, float y, float angle, unsigned int width, unsigned int height, CRGBA color)
{
    ((void(__cdecl*)(CSprite2d*, float, float, float, unsigned int, unsigned int, CRGBA))0x584850)(sprite, x, y, angle, width, height, color);
}

// Converted from cdecl void CRadar::DrawYouAreHereSprite(float x,float y) 0x584960
void CRadar::DrawYouAreHereSprite(float x, float y)
{
    ((void(__cdecl*)(float, float))0x584960)(x, y);
}

// Converted from cdecl void CRadar::SetupRadarRect(int x,int y) 0x584A80
void CRadar::SetupRadarRect(int x, int y)
{
    ((void(__cdecl*)(int, int))0x584A80)(x, y);
}

// Converted from cdecl bool ClipRadarTileCoords(int &x,int &y) 0x584B00
bool ClipRadarTileCoords(int& x, int& y)
{
    return ((bool(__cdecl*)(int&, int&))0x584B00)(x, y);
}

// Converted from cdecl void CRadar::RequestMapSection(int x,int y) 0x584B50
void CRadar::RequestMapSection(int x, int y)
{
    ((void(__cdecl*)(int, int))0x584B50)(x, y);
}

// Converted from cdecl void CRadar::RemoveMapSection(int x,int y) 0x584BB0
void CRadar::RemoveMapSection(int x, int y)
{
    ((void(__cdecl*)(int, int))0x584BB0)(x, y);
}

// Converted from cdecl void CRadar::RemoveRadarSections(void) 0x584BF0
void CRadar::RemoveRadarSections()
{
    ((void(__cdecl*)())0x584BF0)();
}

// Converted from cdecl void CRadar::StreamRadarSections(int x,int y) 0x584C50
void CRadar::StreamRadarSections(int x, int y)
{
    ((void(__cdecl*)(int, int))0x584C50)(x, y);
}

// Converted from cdecl bool IsPointInsideRadar(CVector2D const&point) 0x584D40
bool IsPointInsideRadar(CVector2D const& point)
{
    return ((bool(__cdecl*)(CVector2D const&))0x584D40)(point);
}

// Converted from cdecl void GetTextureCorners(int x,int y,CVector2D *corners) 0x584D90
void GetTextureCorners(int x, int y, CVector2D* corners)
{
    ((void(__cdecl*)(int, int, CVector2D*))0x584D90)(x, y, corners);
}

// Converted from cdecl int LineRadarBoxCollision(CVector2D &result,CVector2D const&lineStart,CVector2D const&lineEnd) 0x584E00
int LineRadarBoxCollision(CVector2D& result, CVector2D const& lineStart, CVector2D const& lineEnd)
{
    return ((int(__cdecl*)(CVector2D&, CVector2D const&, CVector2D const&))0x584E00)(result, lineStart, lineEnd);
}

// Converted from cdecl int CRadar::ClipRadarPoly(CVector2D *out,CVector2D const*in) 0x585040
int CRadar::ClipRadarPoly(CVector2D* out, CVector2D const* in)
{
    return ((int(__cdecl*)(CVector2D*, CVector2D const*))0x585040)(out, in);
}

// Converted from cdecl void CRadar::DrawAreaOnRadar(CRect const&rect,CRGBA const&color,bool inMenu) 0x5853D0
void CRadar::DrawAreaOnRadar(CRect const& rect, CRGBA const& color, bool inMenu)
{
    ((void(__cdecl*)(CRect const&, CRGBA const&, bool))0x5853D0)(rect, color, inMenu);
}

// Converted from cdecl void CRadar::DrawRadarMask(void) 0x585700
void CRadar::DrawRadarMask()
{
    ((void(__cdecl*)())0x585700)();
}

// Converted from cdecl void CRadar::StreamRadarSections(CVector const&worldPosn) 0x5858D0
void CRadar::StreamRadarSections(CVector const& worldPosn)
{
    ((void(__cdecl*)(CVector const&))0x5858D0)(worldPosn);
}

// Converted from cdecl void CRadar::Shutdown(void) 0x585940
void CRadar::Shutdown()
{
    ((void(__cdecl*)())0x585940)();
}

// Converted from cdecl void CRadar::InitFrontEndMap(void) 0x585960
void CRadar::InitFrontEndMap()
{
    ((void(__cdecl*)())0x585960)();
}

// Converted from cdecl void CRadar::AddBlipToLegendList(uchar,int blipArrId) 0x5859F0
void CRadar::AddBlipToLegendList(unsigned char arg0, int blipArrId)
{
    ((void(__cdecl*)(unsigned char, int))0x5859F0)(arg0, blipArrId);
}

// Converted from cdecl void CRadar::SetMapCentreToPlayerCoords(void) 0x585B20
void CRadar::SetMapCentreToPlayerCoords()
{
    ((void(__cdecl*)())0x585B20)();
}

// Converted from cdecl void CRadar::Draw3dMarkers(void) 0x585BF0
void CRadar::Draw3dMarkers()
{
    ((void(__cdecl*)())0x585BF0)();
}

// Converted from cdecl void CRadar::SetRadarMarkerState(int,uchar) 0x585FE0
void CRadar::SetRadarMarkerState(int arg0, unsigned char arg1)
{
    ((void(__cdecl*)(int, unsigned char))0x585FE0)(arg0, arg1);
}

// Converted from cdecl void CRadar::DrawRadarSprite(ushort spriteId,float x,float y,uchar alpha) 0x585FF0
void CRadar::DrawRadarSprite(unsigned short spriteId, float x, float y, unsigned char alpha)
{
    ((void(__cdecl*)(unsigned short, float, float, unsigned char))0x585FF0)(spriteId, x, y, alpha);
}

// Converted from cdecl void CRadar::DrawRadarSection(int x,int y) 0x586110
void CRadar::DrawRadarSection(int x, int y)
{
    ((void(__cdecl*)(int, int))0x586110)(x, y);
}

// Converted from cdecl void CRadar::DrawRadarSectionMap(int x,int y,CRect rect) 0x586520
void CRadar::DrawRadarSectionMap(int x, int y, CRect rect)
{
    ((void(__cdecl*)(int, int, CRect))0x586520)(x, y, rect);
}

// Converted from cdecl void CRadar::DrawRadarGangOverlay(bool inMenu) 0x586650
void CRadar::DrawRadarGangOverlay(bool inMenu)
{
    ((void(__cdecl*)(bool))0x586650)(inMenu);
}

// Converted from cdecl void CRadar::DrawRadarMap(void) 0x586880
void CRadar::DrawRadarMap()
{
    ((void(__cdecl*)())0x586880)();
}

// Converted from cdecl void CRadar::DrawMap(void) 0x586B00
void CRadar::DrawMap()
{
    ((void(__cdecl*)())0x586B00)();
}

// Converted from cdecl void CRadar::DrawCoordBlip(int blipArrId,uchar isSprite) 0x586D60
void CRadar::DrawCoordBlip(int blipArrId, unsigned char isSprite)
{
    ((void(__cdecl*)(int, unsigned char))0x586D60)(blipArrId, isSprite);
}

// Converted from cdecl void CRadar::DrawEntityBlip(int blipArrId,uchar) 0x587000
void CRadar::DrawEntityBlip(int blipArrId, unsigned char arg1)
{
    ((void(__cdecl*)(int, unsigned char))0x587000)(blipArrId, arg1);
}

// Converted from cdecl void CRadar::ClearActualBlip(int blipArrId) 0x587C10
void CRadar::ClearActualBlip(int blipArrId)
{
    ((void(__cdecl*)(int))0x587C10)(blipArrId);
}

// Converted from cdecl void CRadar::ClearBlipForEntity(eBlipType blipType,int entityHandle) 0x587C60
void CRadar::ClearBlipForEntity(eBlipType blipType, int entityHandle)
{
    ((void(__cdecl*)(eBlipType, int))0x587C60)(blipType, entityHandle);
}

// Converted from cdecl void CRadar::ClearBlip(int blipIndex) 0x587CE0
void CRadar::ClearBlip(int blipIndex)
{
    ((void(__cdecl*)(int))0x587CE0)(blipIndex);
}

// Converted from cdecl void CRadar::SetupAirstripBlips(void) 0x587D20
void CRadar::SetupAirstripBlips()
{
    ((void(__cdecl*)())0x587D20)();
}

// Converted from cdecl void CRadar::Initialise(void) 0x587FB0
void CRadar::Initialise()
{
    ((void(__cdecl*)())0x587FB0)();
}

// Converted from cdecl void CRadar::DrawBlips(void) 0x588050
void CRadar::DrawBlips()
{
    ((void(__cdecl*)())0x588050)();
}

void CRadar::Load()
{
    ((void(__cdecl*)())0x5D53C0)();
}

void CRadar::Save()
{
    ((void(__cdecl*)())0x5D5860)();
}
