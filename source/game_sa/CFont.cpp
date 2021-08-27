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
unsigned char& CFont::m_nExtraFontSymbolId = *(unsigned char*)0xC71A54; // aka. PS2Symbol
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
unsigned char& CFont::m_nFontOutlineOrShadow = *(unsigned char*)0xC71A9C;

tFontData* gFontData = (tFontData*)0xC718B0;

void CFont::InjectHooks() {
    ReversibleHooks::Install("CFont", "Initialise", 0x5BA690, &CFont::Initialise);
    ReversibleHooks::Install("CFont", "SetEdge", 0x719590, &CFont::SetEdge);
    ReversibleHooks::Install("CFont", "DrawFonts", 0x71A210, &CFont::DrawFonts);

    // wip
    ReversibleHooks::Install("CFont", "SetScale", 0x719380, &CFont::SetScale);
    ReversibleHooks::Install("CFont", "SetScaleForCurrentlanguage", 0x7193A0, &CFont::SetScaleForCurrentlanguage);
    ReversibleHooks::Install("CFont", "SetSlantRefPoint", 0x719400, &CFont::SetSlantRefPoint);
    ReversibleHooks::Install("CFont", "SetSlant", 0x719420, &CFont::SetSlant);
    ReversibleHooks::Install("CFont", "SetColor", 0x719430, &CFont::SetColor);
    ReversibleHooks::Install("CFont", "SetFontStyle", 0x719490, &CFont::SetFontStyle);
    ReversibleHooks::Install("CFont", "SetWrapx", 0x7194D0, &CFont::SetWrapx);
    ReversibleHooks::Install("CFont", "SetCentreSize", 0x7194E0, &CFont::SetCentreSize);
}

// 0x7187C0
void ReadFontsDat() {
    plugin::Call<0x7187C0>();
}

// 0x5BA690
void CFont::Initialise() {
    int fontsTxd = CTxdStore::AddTxdSlot("fonts");
    CTxdStore::LoadTxd(fontsTxd, "MODELS\\FONTS.TXD");
    CTxdStore::AddRef(fontsTxd);
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(fontsTxd);
    CFont::Sprite->SetTexture((char *) "font2", (char *) "font2m");
    CFont::Sprite[1].SetTexture((char *) "font1", (char *) "font1m");

    ReadFontsDat();

    CFont::SetScale(1.0f, 1.0f);
    CFont::SetSlantRefPoint((float) RsGlobal.maximumWidth, 0.0f);
    CFont::SetSlant(0.0);

    CFont::SetColor(CRGBA(255, 255, 255, 0));
    CFont::SetOrientation(ALIGN_LEFT);
    CFont::SetJustify(false);

    CFont::SetWrapx((float) RsGlobal.maximumWidth);

    CFont::SetCentreSize((float) RsGlobal.maximumWidth);
    CFont::SetBackground(false, false);

    CFont::SetBackgroundColor(CRGBA(128, 128, 128, 128));
    CFont::SetProportional(true);
    CFont::SetFontStyle(FONT_GOTHIC);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetAlphaFade(255.0f);
    CFont::SetDropShadowPosition(0);
    CTxdStore::PopCurrentTxd();

    int ps2btnsTxd = CTxdStore::AddTxdSlot("ps2btns");
    CTxdStore::LoadTxd(ps2btnsTxd, "MODELS\\PCBTNS.TXD");
    CTxdStore::AddRef(ps2btnsTxd);
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(ps2btnsTxd);
    CFont::ButtonSprite[1].SetTexture((char *) "up", (char *) "upA");
    CFont::ButtonSprite[2].SetTexture((char *) "down", (char *) "downA");
    CFont::ButtonSprite[3].SetTexture((char *) "left", (char *) "leftA");
    CFont::ButtonSprite[4].SetTexture((char *) "right", (char *) "rightA");
    CTxdStore::PopCurrentTxd();
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

// 0x719380
void CFont::SetScale(float w, float h)
{
    m_Scale->Set(w, h);
}

// 0x7193A0
void CFont::SetScaleForCurrentlanguage(float w, float h)
{
    switch (FrontEndMenuManager.m_nLanguage) {
    case 1:
    case 2:
    case 3:
    case 4:
        m_Scale->Set(h, w * 0.8f);
        break;
    }

    m_Scale->Set(w, h);
}

// 0x719400
void CFont::SetSlantRefPoint(float x, float y)
{
    m_fSlantRefPoint->Set(x, y);
}

// 0x719420
void CFont::SetSlant(float value)
{
    m_fSlant = value;
}

// 0x719430
void CFont::SetColor(CRGBA color)
{
    *m_Color = color;

    if (m_dwFontAlpha < 255) {
        m_Color->a = (color.a * m_dwFontAlpha) / 255;
    }
}

// 0x719490
void CFont::SetFontStyle(eFontStyle style)
{
    switch (style) {
    case FONT_PRICEDOWN:
        m_FontTextureId = 1;
        m_FontStyle = 1;
        break;
    case FONT_MENU:
        m_FontTextureId = 0;
        m_FontStyle = 2;
        break;
    default:
        m_FontTextureId = style;
        m_FontStyle = 0;
    }
}

// 0x7194D0
void CFont::SetWrapx(float value)
{
    m_fWrapx = value;
}

// 0x7194E0
void CFont::SetCentreSize(float value)
{
    m_fFontCentreSize = value;
}

// 0x7194F0
void CFont::SetRightJustifyWrap(float value)
{
    //((void(__cdecl*)(float))0x7194F0)(value);
    m_fRightJustifyWrap = value;
}

// 0x719500
void CFont::SetAlphaFade(float alpha)
{
    //((void(__cdecl*)(float))0x719500)(alpha);
    m_dwFontAlpha = alpha;
}

// 0x719510
void CFont::SetDropColor(CRGBA color)
{
    //((void(__cdecl*)(CRGBA))0x719510)(color);
    *m_FontDropColor = color;

    if (m_dwFontAlpha < 255)
        m_FontDropColor->a = m_Color->a * m_dwFontAlpha;
}

// 0x719570
void CFont::SetDropShadowPosition(short value)
{
    //((void(__cdecl*)(short))0x719570)(value);
    m_nFontOutlineSize = 0;
    m_nFontOutlineOrShadow = 0;
    m_nFontShadow = (uint8_t)value;
}

// 0x719590
void CFont::SetEdge(short value) {
    m_nFontShadow = 0;
    m_nFontOutlineSize = (uint8_t)value;
    m_nFontOutlineOrShadow = (uint8_t)value;
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

// 0x7195C0
void CFont::SetBackground(bool enable, bool includeWrap)
{
    //((void(__cdecl*)(bool, bool))0x7195C0)(enable, includeWrap);
    m_bFontBackground = enable;
    m_bEnlargeBackgroundBox = includeWrap;
}

// 0x7195E0
void CFont::SetBackgroundColor(CRGBA color)
{
    //((void(__cdecl*)(CRGBA))0x7195E0)(color);
    *m_FontBackgroundColor = color;
}

// 0x719600
void CFont::SetJustify(bool on)
{
    m_bFontJustify = on;
}

// 0x719610
void CFont::SetOrientation(eFontAlignment alignment)
{
    m_bFontCentreAlign = alignment == ALIGN_CENTER;
    m_bFontRightAlign = alignment == ALIGN_RIGHT;
}

// 0x719800
// not done.
void CFont::InitPerFrame()
{
    m_nFontOutline = 0;
    m_nFontOutlineOrShadow = 0;
    m_nFontShadow = 0;
    m_bNewLine = false;
    m_nExtraFontSymbolId = 0;
    //RenderState.m_wFontTexture = -1;
    //m_pEmptyChar = &setup
    CSprite::InitSpriteBuffer();
}

void CFont::RenderFontBuffer()
{
    ((void(__cdecl*)())0x719840)();
}

float CFont::GetStringWidth(char* string, bool unk1, bool unk2)
{
    return ((float(__cdecl*)(char*, bool, bool))0x71A0E0)(string, unk1, unk2);
}

// same as RenderFontBuffer()
// 0x71A210
void CFont::DrawFonts() {
    CFont::RenderFontBuffer();
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

void CFont::PrintString(float x, float y, const char* text)
{
    ((void(__cdecl*)(float, float, const char*))0x71A700)(x, y, text);
}

void CFont::PrintStringFromBottom(float x, float y, char* text)
{
    ((void(__cdecl*)(float, float, char*))0x71A820)(x, y, text);
}
