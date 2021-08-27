#include "StdInc.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CFont.h"

CFontChar (&setup)[9] = *(CFontChar(*)[9])0xC716B0;

CFontChar* m_pEmptyChar = (CFontChar*)0xC716A8;
CFontChar& CFont::RenderState = *(CFontChar*)0xC71AA0;
CSprite2d (&CFont::Sprite)[MAX_FONT_SPRITES] = *(CSprite2d(*)[2])0xC71AD0;
CSprite2d (&CFont::ButtonSprite)[MAX_FONT_BUTTON_SPRITES] = *(CSprite2d(*)[15])0xC71AD8;
unsigned char& CFont::m_nExtraFontSymbolId = *(unsigned char*)0xC71A54; // aka. PS2Symbol
bool& CFont::m_bNewLine = *(bool*)0xC71A55;
CRGBA* CFont::m_Color = (CRGBA*)0xC71A60;
CVector2D& CFont::m_Scale = *(CVector2D*)0xC71A64;
float& CFont::m_fSlant = *(float*)0xC71A6C;
CVector2D& CFont::m_fSlantRefPoint = *(CVector2D*)0xC71A70;
bool& CFont::m_bFontJustify = *(bool*)0xC71A78;
bool& CFont::m_bFontCentreAlign = *(bool*)0xC71A79;
bool& CFont::m_bFontRightAlign = *(bool*)0xC71A7A;
bool& CFont::m_bFontBackground = *(bool*)0xC71A7B;
bool& CFont::m_bEnlargeBackgroundBox = *(bool*)0xC71A7C;
bool& CFont::m_bFontPropOn = *(bool*)0xC71A7D;
bool& CFont::m_bFontIsBlip = *(bool*)0xC71A7E;
unsigned int CFont::m_dwFontAlpha = *(unsigned int*)0xC71A80;
CRGBA& CFont::m_FontBackgroundColor = *(CRGBA*)0xC71A84;
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
    ReversibleHooks::Install("CFont", "Shutdown", 0x7189B0, &CFont::Shutdown);

    // styling functions
    ReversibleHooks::Install("CFont", "SetScale", 0x719380, &CFont::SetScale);
    ReversibleHooks::Install("CFont", "SetScaleForCurrentlanguage", 0x7193A0, &CFont::SetScaleForCurrentlanguage);
    ReversibleHooks::Install("CFont", "SetSlantRefPoint", 0x719400, &CFont::SetSlantRefPoint);
    ReversibleHooks::Install("CFont", "SetSlant", 0x719420, &CFont::SetSlant);
    ReversibleHooks::Install("CFont", "SetColor", 0x719430, &CFont::SetColor);
    ReversibleHooks::Install("CFont", "SetFontStyle", 0x719490, &CFont::SetFontStyle);
    ReversibleHooks::Install("CFont", "SetWrapx", 0x7194D0, &CFont::SetWrapx);
    ReversibleHooks::Install("CFont", "SetCentreSize", 0x7194E0, &CFont::SetCentreSize);
    ReversibleHooks::Install("CFont", "SetRightJustifyWrap", 0x7194F0, &CFont::SetRightJustifyWrap);
    ReversibleHooks::Install("CFont", "SetAlphaFade", 0x719500, &CFont::SetAlphaFade);
    ReversibleHooks::Install("CFont", "SetDropColor", 0x719510, &CFont::SetDropColor);
    ReversibleHooks::Install("CFont", "SetDropShadowPosition", 0x719570, &CFont::SetDropShadowPosition);
    ReversibleHooks::Install("CFont", "SetEdge", 0x719590, &CFont::SetEdge);
    ReversibleHooks::Install("CFont", "SetProportional", 0x7195B0, &CFont::SetProportional);
    ReversibleHooks::Install("CFont", "SetBackground", 0x7195C0, &CFont::SetBackground);
    ReversibleHooks::Install("CFont", "SetBackgroundColor", 0x7195E0, &CFont::SetBackgroundColor);
    ReversibleHooks::Install("CFont", "SetJustify", 0x719600, &CFont::SetJustify);
    ReversibleHooks::Install("CFont", "SetOrientation", 0x719610, &CFont::SetOrientation);

    ReversibleHooks::Install("CFont", "DrawFonts", 0x71A210, &CFont::DrawFonts);

    // wip
    ReversibleHooks::Install("CFont", "GetTextRect", 0x71A620, &CFont::GetTextRect);
    ReversibleHooks::Install("CFont", "PrintString", 0x71A700, &CFont::PrintString);
    ReversibleHooks::Install("CFont", "PrintStringFromBottom", 0x71A820, &CFont::PrintStringFromBottom);
    ReversibleHooks::Install("CFont", "InitPerFrame", 0x719800, &CFont::InitPerFrame);
    
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

// 0x7189B0
void CFont::Shutdown()
{
    Sprite[0].Delete();
    Sprite[1].Delete();

    auto fontSlot = CTxdStore::FindTxdSlot("fonts");
    CTxdStore::RemoveTxdSlot(fontSlot);

    for (CSprite2d& bs : ButtonSprite) {
        bs.Delete();
    }

    auto buttonSlot = CTxdStore::FindTxdSlot("ps2btns");
    CTxdStore::RemoveTxdSlot(buttonSlot);
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
    m_Scale.Set(w, h);
}

// 0x7193A0
void CFont::SetScaleForCurrentlanguage(float w, float h)
{
    switch (FrontEndMenuManager.m_nLanguage) {
    case 1:
    case 2:
    case 3:
    case 4:
        m_Scale.Set(h, w * 0.8f);
        break;
    default:
        m_Scale.Set(w, h);
    }
}

// 0x719400
void CFont::SetSlantRefPoint(float x, float y)
{
    m_fSlantRefPoint.Set(x, y);
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
    m_fRightJustifyWrap = value;
}

// 0x719500
void CFont::SetAlphaFade(float alpha)
{
    m_dwFontAlpha = alpha;
}

// 0x719510
void CFont::SetDropColor(CRGBA color)
{
    *m_FontDropColor = color;

    if (m_dwFontAlpha < 255)
        m_FontDropColor->a = m_Color->a * m_dwFontAlpha;
}

// 0x719570
void CFont::SetDropShadowPosition(short value)
{
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

// 0x7195B0
void CFont::SetProportional(bool on)
{
    m_bFontPropOn = on;
}

// 0x7195C0
void CFont::SetBackground(bool enable, bool includeWrap)
{
    m_bFontBackground = enable;
    m_bEnlargeBackgroundBox = includeWrap;
}

// 0x7195E0
void CFont::SetBackgroundColor(CRGBA color)
{
    m_FontBackgroundColor = color;
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
void CFont::InitPerFrame()
{
    m_nFontOutline = 0;
    m_nFontOutlineOrShadow = 0;
    m_nFontShadow = 0;
    m_bNewLine = false;
    m_nExtraFontSymbolId = 0;
    RenderState.m_wFontTexture = 0; // todo: make sense of this
    m_pEmptyChar = &setup[0];

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

// same as RenderFontBuffer() (0x71A210)
void CFont::DrawFonts() {
    RenderFontBuffer();
}

short CFont::ProcessCurrentString(bool print, float x, float y, const char* text)
{
    return ((short(__cdecl*)(bool, float, float, const char*))0x71A220)(print, x, y, text);
}

short CFont::GetNumberLines(float x, float y, const char* text)
{
    return ((short(__cdecl*)(float, float, const char*))0x71A5E0)(x, y, text);
}

short CFont::ProcessStringToDisplay(float x, float y, const char* text)
{
    return ((short(__cdecl*)(float, float, const char*))0x71A600)(x, y, text);
}

// 0x71A620
void CFont::GetTextRect(CRect* rect, float x, float y, const char* text)
{
    auto nLines = GetNumberLines(x, y, text);

    if (m_bFontCentreAlign) {
        rect->left = m_fFontCentreSize / 2.0f - x + 4.0f;
        rect->right = m_fFontCentreSize / 2.0f + x + 4.0f;
    }
    else if (m_bFontRightAlign) {
        rect->left = m_fRightJustifyWrap - 4.0f;
        rect->right = x;
    }
    else {
        rect->left = x - 4.0f;
        rect->right = m_fWrapx + 4.0f;
    }

    rect->bottom = y - 4.0f;
    rect->top = nLines * 18.0f * m_Scale.y + y + 4.0f;
}

// 0x71A700
void CFont::PrintString(float x, float y, const char* text)
{
    if (*text == '\0' || *text == '*')
        return;

    if (m_bFontBackground) {
        CRect rt;

        RenderState.m_color = *m_Color;
        GetTextRect(&rt, x, y, text);

        if (m_bEnlargeBackgroundBox) {
            rt.left -= 1.0f;
            rt.right += 1.0f;
            rt.top += 1.0f;
            rt.bottom -= 1.0f;

            FrontEndMenuManager.DrawWindow(rt, '\0', 0, m_FontBackgroundColor, false, true);
        } else {
            CSprite2d::DrawRect(rt, m_FontBackgroundColor);
        }
    }

    ProcessStringToDisplay(x, y, text);
}

// 0x71A820
void CFont::PrintStringFromBottom(float x, float y, const char* text)
{
    float drawY = y - (18.0f * m_Scale.y) * CFont::GetNumberLines(x, y, text);

    if (m_fSlant != 0.0f)
        drawY -= (m_fSlantRefPoint.x - x) * m_fSlant + m_fSlantRefPoint.y;

    PrintString(x, drawY, text);
}
