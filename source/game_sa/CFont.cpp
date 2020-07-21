#include "StdInc.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CFont.h"

CSprite2d* CFont::Sprite = (CSprite2d*)0xC71AD0;
CSprite2d* CFont::ButtonSprite = (CSprite2d*)0xC71AD8;
unsigned char& CFont::m_nExtraFontSymbolId = *(unsigned char*)0xC71A54;
bool& CFont::m_bNewLine = *(bool*)0xC71A55;
CRGBA* CFont::m_Color = (CRGBA*)0xC71A60;
CVector2D* CFont::m_Scale = (CVector2D*)0xC71A64;
float& CFont::m_fSlant = *(float*)0xC71A6C;
CVector2D* CFont::m_fSlantRefPoint = (CVector2D*)0xC71A70;
bool& CFont::m_bFontJustify = *(bool*)0xC71A78;
bool& CFont::m_bFontCentreAlign = *(bool*)0xC71A79;
bool& CFont::m_bFontRightAlign = *(bool*)0xC71A7A;
bool& CFont::m_bFontBackground = *(bool*)0xC71A7B;
bool& CFont::m_bEnlargeBackgroundBox = *(bool*)0xC71A7C;
bool& CFont::m_bFontPropOn = *(bool*)0xC71A7D;
bool& CFont::m_bFontIsBlip = *(bool*)0xC71A7E;
unsigned int CFont::m_dwFontAlpha = *(unsigned int*)0xC71A80;
CRGBA* CFont::m_FontBackgroundColor = (CRGBA*)0xC71A84;
float& CFont::m_fWrapx = *(float*)0xC71A88;
float& CFont::m_fFontCentreSize = *(float*)0xC71A8C;
float& CFont::m_fRightJustifyWrap = *(float*)0xC71A90;
unsigned char& CFont::m_FontTextureId = *(unsigned char*)0xC71A94;
unsigned char& CFont::m_FontStyle = *(unsigned char*)0xC71A95;
unsigned char& CFont::m_nFontShadow = *(unsigned char*)0xC71A96;
CRGBA* CFont::m_FontDropColor = (CRGBA*)0xC71A97;
unsigned char& CFont::m_nFontOutlineSize = *(unsigned char*)0xC71A9B;
unsigned char& CFont::m_nFontOutline = *(unsigned char*)0xC71A9C;

tFontData* gFontData = (tFontData*)0xC718B0;

void CFont::Initialise()
{
    ((void(__cdecl*)())0x5BA690)();
}

void CFont::Shutdown()
{
    ((void(__cdecl*)())0x7189B0)();
}

void CFont::PrintChar(float x, float y, char character)
{
    ((void(__cdecl*)(float, float, char))0x718A10)(x, y, character);
}

char* CFont::ParseToken(char* text, CRGBA& color, bool isBlip, char* tag)
{
    return ((char* (__cdecl*)(char*, CRGBA&, bool, char*))0x718F00)(text, color, isBlip, tag);
}

void CFont::SetScale(float w, float h)
{
    ((void(__cdecl*)(float, float))0x719380)(w, h);
}

void CFont::SetScaleForCurrentlanguage(float w, float h)
{
    ((void(__cdecl*)(float, float))0x7193A0)(w, h);
}

void CFont::SetSlantRefPoint(float x, float y)
{
    ((void(__cdecl*)(float, float))0x719400)(x, y);
}

void CFont::SetSlant(float value)
{
    ((void(__cdecl*)(float))0x719420)(value);
}

void CFont::SetColor(CRGBA color)
{
    ((void(__cdecl*)(CRGBA))0x719430)(color);
}

void CFont::SetFontStyle(short style)
{
    ((void(__cdecl*)(short))0x719490)(style);
}

void CFont::SetWrapx(float value)
{
    ((void(__cdecl*)(float))0x7194D0)(value);
}

void CFont::SetCentreSize(float value)
{
    ((void(__cdecl*)(float))0x7194E0)(value);
}

void CFont::SetRightJustifyWrap(float value)
{
    ((void(__cdecl*)(float))0x7194F0)(value);
}

void CFont::SetAlphaFade(float alpha)
{
    ((void(__cdecl*)(float))0x719500)(alpha);
}

void CFont::SetDropColor(CRGBA color)
{
    ((void(__cdecl*)(CRGBA))0x719510)(color);
}

void CFont::SetDropShadowPosition(short value)
{
    ((void(__cdecl*)(short))0x719570)(value);
}

void CFont::SetEdge(short value)
{
    ((void(__cdecl*)(short))0x719590)(value);
}


#ifdef SetProp
#define SET_PROP_USED
#undef SetProp
#endif
void CFont::SetProportional(bool on)
{
    ((void(__cdecl*)(bool))0x7195B0)(on);
}
#ifdef SET_PROP_USED
#undef SET_PROP_USED
#define SetProp SetPropA
#endif

void CFont::SetBackground(bool enable, bool includeWrap)
{
    ((void(__cdecl*)(bool, bool))0x7195C0)(enable, includeWrap);
}

void CFont::SetBackgroundColor(CRGBA color)
{
    ((void(__cdecl*)(CRGBA))0x7195E0)(color);
}

void CFont::SetJustify(bool on)
{
    ((void(__cdecl*)(bool))0x719600)(on);
}

void CFont::SetOrientation(eFontAlignment alignment)
{
    ((void(__cdecl*)(eFontAlignment))0x719610)(alignment);
}

void CFont::InitPerFrame()
{
    ((void(__cdecl*)())0x719800)();
}

void CFont::RenderFontBuffer()
{
    ((void(__cdecl*)())0x719840)();
}

float CFont::GetStringWidth(char* string, bool unk1, bool unk2)
{
    return ((float(__cdecl*)(char*, bool, bool))0x71A0E0)(string, unk1, unk2);
}

void CFont::DrawFonts()
{
    ((void(__cdecl*)())0x71A210)();
}

short CFont::ProcessCurrentString(bool print, float x, float y, char* text)
{
    return ((short(__cdecl*)(bool, float, float, char*))0x71A220)(print, x, y, text);
}

short CFont::GetNumberLines(float x, float y, char* text)
{
    return ((short(__cdecl*)(float, float, char*))0x71A5E0)(x, y, text);
}

short CFont::ProcessStringToDisplay(float x, float y, char* text)
{
    return ((short(__cdecl*)(float, float, char*))0x71A600)(x, y, text);
}

void CFont::GetTextRect(CRect* rect, float x, float y, char* text)
{
    ((void(__cdecl*)(CRect*, float, float, char*))0x71A620)(rect, x, y, text);
}

void CFont::PrintString(float x, float y, char* text)
{
    ((void(__cdecl*)(float, float, char*))0x71A700)(x, y, text);
}

void CFont::PrintStringFromBottom(float x, float y, char* text)
{
    ((void(__cdecl*)(float, float, char*))0x71A820)(x, y, text);
}
