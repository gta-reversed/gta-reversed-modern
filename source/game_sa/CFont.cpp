#include "StdInc.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CFont.h"

CFontChar (&setup)[9] = *(CFontChar(*)[9])0xC716B0;
CFontChar* pEmptyChar = (CFontChar*)0xC716A8;

CFontChar& CFont::RenderState = *(CFontChar*)0xC71AA0;
CSprite2d (&CFont::Sprite)[MAX_FONT_SPRITES] = *(CSprite2d(*)[2])0xC71AD0;
CSprite2d (&CFont::ButtonSprite)[MAX_FONT_BUTTON_SPRITES] = *(CSprite2d(*)[15])0xC71AD8;
eExtraFontSymbol& CFont::PS2Symbol = *(eExtraFontSymbol*)0xC71A54;
bool& CFont::m_bNewLine = *(bool*)0xC71A55;
CRGBA& CFont::m_Color = *(CRGBA*)0xC71A60;
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
uint32 CFont::m_dwFontAlpha = *(uint32*)0xC71A80;
CRGBA& CFont::m_FontBackgroundColor = *(CRGBA*)0xC71A84;
float& CFont::m_fWrapx = *(float*)0xC71A88;
float& CFont::m_fFontCentreSize = *(float*)0xC71A8C;
float& CFont::m_fRightJustifyWrap = *(float*)0xC71A90;
uint8& CFont::m_FontTextureId = *(uint8*)0xC71A94;
uint8& CFont::m_FontStyle = *(uint8*)0xC71A95;
uint8& CFont::m_nFontShadow = *(uint8*)0xC71A96;
CRGBA& CFont::m_FontDropColor = *(CRGBA*)0xC71A97;
uint8& CFont::m_nFontOutlineSize = *(uint8*)0xC71A9B;
uint8& CFont::m_nFontOutline = *(uint8*)0xC71A9C;
uint8& CFont::m_nFontOutlineOrShadow = *(uint8*)0xC71A9C;

tFontData* gFontData = (tFontData*)0xC718B0;

void CFont::InjectHooks() {
    ReversibleHooks::Install("CFont", "Initialise", 0x5BA690, &CFont::Initialise);
    ReversibleHooks::Install("CFont", "Shutdown", 0x7189B0, &CFont::Shutdown);
    //ReversibleHooks::Install("CFont", "PrintChar", 0x718A10, &CFont::PrintChar);
    ReversibleHooks::Install("CFont", "ParseToken", 0x718F00, &CFont::ParseToken);

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

    ReversibleHooks::Install("CFont", "InitPerFrame", 0x719800, &CFont::InitPerFrame);
    //ReversibleHooks::Install("CFont", "RenderFontBuffer", 0x719840, &CFont::RenderFontBuffer);
    ReversibleHooks::Install("CFont", "GetStringWidth", 0x71A0E0, &CFont::GetStringWidth);
    ReversibleHooks::Install("CFont", "DrawFonts", 0x71A210, &CFont::DrawFonts);
    //ReversibleHooks::Install("CFont", "ProcessCurrentString", 0x71A220, &CFont::ProcessCurrentString);
    ReversibleHooks::Install("CFont", "GetNumberLines", 0x71A5E0, &CFont::GetNumberLines);
    ReversibleHooks::Install("CFont", "ProcessStringToDisplay", 0x71A600, &CFont::ProcessStringToDisplay);
    ReversibleHooks::Install("CFont", "GetTextRect", 0x71A620, &CFont::GetTextRect);
    ReversibleHooks::Install("CFont", "PrintString", 0x71A700, &CFont::PrintString);
    ReversibleHooks::Install("CFont", "PrintStringFromBottom", 0x71A820, &CFont::PrintStringFromBottom);
    ReversibleHooks::Install("CFont", "GetLetterSize", 0x719750, &CFont::GetLetterSize);

    ReversibleHooks::Install("", "ReadFontsDat", 0x7187C0, &ReadFontsDat);
    //ReversibleHooks::Install("", "GetScriptLetterSize", 0x719670, &GetScriptLetterSize);
    //ReversibleHooks::Install("", "GetIDforPropVal", 0x7192C0, &GetIDforPropVal);
    ReversibleHooks::Install("", "GetLetterIdPropValue", 0x718770, &GetLetterIdPropValue);
}

// 0x7187C0
void ReadFontsDat() {
    CFileMgr::SetDir(gta_empty_string);
    auto file = CFileMgr::OpenFile("DATA\\FONTS.DAT", "rb");

    char* attrib[26];

    uint32 totalFonts = 0;
    uint32 fontId = 0;

    for (auto line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file)) {
        if (*line == '\0' || *line == '#')
            continue;

        if (sscanf(line, "%s", &attrib) == EOF)
            continue;

        if (!memcmp(attrib, "[TOTAL_FONTS]", 14)) {
            auto nextLine = CFileLoader::LoadLine(file);

            sscanf(nextLine, "%d", &totalFonts);
        }
        else if (!memcmp(attrib, "[FONT_ID]", 10)) {
            auto nextLine = CFileLoader::LoadLine(file);

            sscanf(nextLine, "%d", &fontId);
        }
        else if (!memcmp(attrib, "[REPLACEMENT_SPACE_CHAR]", 25)) {
            auto nextLine = CFileLoader::LoadLine(file);
            uint32 spaceValue;

            sscanf(nextLine, "%d", &spaceValue); // maybe use inttypes?
            gFontData[fontId].m_spaceValue = spaceValue;
        }
        else if (!memcmp(attrib, "[PROP]", 7)) {
            for (int i = 0; i < 26; i++) {
                auto nextLine = CFileLoader::LoadLine(file);
                uint32 propValues[8];

                sscanf(nextLine, "%d  %d  %d  %d  %d  %d  %d  %d",
                    &propValues[0], &propValues[1], &propValues[2], &propValues[3],
                    &propValues[4], &propValues[5], &propValues[6], &propValues[7]);

                for (int j = 0; j < 8; j++)
                    gFontData[fontId].m_propValues[i * 8 + j] = propValues[j];
            }
        }
        else if (!memcmp(attrib, "[UNPROP]", 9)) {
            auto nextLine = CFileLoader::LoadLine(file);
            uint32 unpropValue;

            sscanf(nextLine, "%d", &unpropValue);
            gFontData[fontId].m_unpropValue = unpropValue;
        }
    }

    CFileMgr::CloseFile(file);
}

// 0x5BA690
void CFont::Initialise() {
    int fontsTxd = CTxdStore::AddTxdSlot("fonts");
    CTxdStore::LoadTxd(fontsTxd, "MODELS\\FONTS.TXD");
    CTxdStore::AddRef(fontsTxd);
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(fontsTxd);
    Sprite[0].SetTexture("font2", "font2m");
    Sprite[1].SetTexture("font1", "font1m");

    ReadFontsDat();

    SetScale(1.0f, 1.0f);
    SetSlantRefPoint(SCREEN_WIDTH, 0.0f);
    SetSlant(0.0);

    SetColor(CRGBA(255, 255, 255, 0));
    SetOrientation(eFontAlignment::ALIGN_LEFT);
    SetJustify(false);

    SetWrapx(SCREEN_WIDTH);

    SetCentreSize(SCREEN_WIDTH);
    SetBackground(false, false);

    SetBackgroundColor(CRGBA(128, 128, 128, 128));
    SetProportional(true);
    SetFontStyle(eFontStyle::FONT_GOTHIC);
    SetRightJustifyWrap(0.0f);
    SetAlphaFade(255.0f);
    SetDropShadowPosition(0);
    CTxdStore::PopCurrentTxd();

    int ps2btnsTxd = CTxdStore::AddTxdSlot("ps2btns");
    CTxdStore::LoadTxd(ps2btnsTxd, "MODELS\\PCBTNS.TXD");
    CTxdStore::AddRef(ps2btnsTxd);
    CTxdStore::PushCurrentTxd();
    CTxdStore::SetCurrentTxd(ps2btnsTxd);

    ButtonSprite[1].SetTexture("up", "upA");
    ButtonSprite[2].SetTexture("down", "downA");
    ButtonSprite[3].SetTexture("left", "leftA");
    ButtonSprite[4].SetTexture("right", "rightA");

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

// 0x718A10
void CFont::PrintChar(float x, float y, char character)
{
    plugin::Call<0x718A10, float, float, char>(x, y, character);

    // todo: check the fucking uv values

    /*
    // out of screen
    if (x < 0.0f || x > SCREEN_WIDTH || y < 0.0f || y > SCREEN_HEIGHT)
        return;

    if (PS2Symbol) {
        // extra symbol to be drawn (e.g. PS2 buttons)

        CRect rt = {
            x,
            2.0f * RenderState.m_fHeight + y,
            17.0f * RenderState.m_fHeight + x,
            19.0f * RenderState.m_fHeight + y
        };
            

        ButtonSprite[PS2Symbol].Draw(rt, { 255, 255, 255, RenderState.m_color.a });

        return;
    }

    if (!character || character == '?') {
        float propValue = GetLetterIdPropValue(character) / 32.0f;
        bool zeroed = false;

        if (RenderState.m_nFontStyle == 1 && character == 208) {
            character = 0;
            zeroed = true;
        }

        //auto v1 = (character >> 4);
        //auto u1 = (character & 0xf) / 16.0f;

        auto propval = propValue / 32.0f;

        if (RenderState.m_dwFontTexture && RenderState.m_dwFontTexture != 1) {
            if (!zeroed) {
                CRect rt = {
                    y,
                    x,
                    32.0f * propValue * RenderState.m_fWidth + x,
                    16.0f * RenderState.m_fHeight + y,
                };

                float u1 = (character & 0xF) / 16.0f;
                float v1 = (character >> 4) / 16.0f;
                float u2 = propval / 16.0f + u1;
                float v2 = v1;
                float u3 = u1;
                float v3 = v1 + 0.0625;
                float u4 = u2 - 0.0001f;
                float v4 = v3 - 0.0001f;

                CSprite2d::AddToBuffer(rt, RenderState.m_color, u1, v1, u2, v2, u3, v3, u4, v4);
            }

            return;
        }

        if (!zeroed) {
            CRect rt;

            rt.left = x;

            if (RenderState.m_fSlant == 0.0f) {
                rt.top = y;
                rt.right = 32.0f * RenderState.m_fWidth + x;

                if (character < 0xC0) {
                    rt.bottom = 20.0f * RenderState.m_fHeight + y;

                    float u1 = (character & 0xF) / 16.0f;
                    float v1 = (character >> 4) / 12.8f + 0.0021f;
                    float u2 = u1 + 0.0615f;
                    float v2 = v1;
                    float u3 = u1;
                    float v3 = v2 - 0.0021f;
                    float u4 = u2;
                    float v4 = v2 - 0.0021f;

                    CSprite2d::AddToBuffer(rt, RenderState.m_color, u1, v1, u2, v2, u3, v3, u4, v4);
                }
                else {
                    rt.bottom = 16.0f * RenderState.m_fHeight + y;

                    float u1 = (character & 0xF) / 16.0f;
                    float v1 = (character >> 4) / 12.8f + 0.0021f;
                    float u2 = u1 + 0.0615f;
                    float v2 = v1;
                    float u3 = u1;
                    float v3 = v2 - 0.016f;
                    float u4 = u2;
                    float v4 = v2 - 0.015f;

                    CSprite2d::AddToBuffer(rt, RenderState.m_color, u1, v1, u2, v2, u3, v3, u4, v4);
                }
            }
            else {
                rt.top = y + 0.015f;
                rt.right = 32.0f * RenderState.m_fWidth + x;
                rt.bottom = 20.0f * RenderState.m_fHeight + y + 0.015f;

                float u1 = (character & 0xF) / 16.0f;
                float v1 = (character >> 4) / 12.8f + 0.00055f;
                float u2 = u1 + 0.0615f;
                float v2 = (character >> 4) / 12.8f + 0.078125f;
                float u3 = u1;
                float v3 = v2 - 0.016f;
                float u4 = u2;
                float v4 = v2 - 0.015f;

                CSprite2d::AddToBuffer(rt, RenderState.m_color, u1, v1, u2, v2, u3, v3, u4, v4);
            }
        }
    }
    */
}

// 0x718F00
char* CFont::ParseToken(char* text, CRGBA& color, bool isBlip, char* tag)
{
    // info about tokens: https://gtamods.com/wiki/GXT#Tokens

    char* next = ++text;

    auto ApplyStyle = [&](eHudColours hudColor) {
        if (!isBlip)
            color = HudColour.GetRGBA(hudColor, color.a);

        if (tag)
            *tag = *next;
    };

    switch (*next) {
    case '<':
        PS2Symbol = EXSYMBOL_DPAD_LEFT;
        break;
    case '>':
        PS2Symbol = EXSYMBOL_DPAD_RIGHT;
        break;
    case 'A':
    case 'a':
        PS2Symbol = EXSYMBOL_L3;
        break;
    case 'B':
    case 'b':
        ApplyStyle(HUD_COLOUR_DARK_BLUE);
        break;
    case 'C':
    case 'c':
        PS2Symbol = EXSYMBOL_R3;
        break;
    case 'D':
    case 'd':
        PS2Symbol = EXSYMBOL_DPAD_DOWN;
        break;
    case 'G':
    case 'g':
        ApplyStyle(HUD_COLOUR_GREEN);
        break;
    case 'H':
    case 'h':
        if (!isBlip) {
            color = {
                    (uint8)std::min((float)color.r * 1.5f, 255.0f),
                    (uint8)std::min((float)color.g * 1.5f, 255.0f),
                    (uint8)std::min((float)color.b * 1.5f, 255.0f),
                    color.a
            };
        }

        if (tag)
            *tag = *next;
        break;
    case 'J':
    case 'j':
        PS2Symbol = EXSYMBOL_R1;
        break;
    case 'K':
    case 'k':
        PS2Symbol = EXSYMBOL_KEY;
        break;
    case 'M':
    case 'm':
        PS2Symbol = EXSYMBOL_L2;
        break;
    case 'N':
    case 'n':
        m_bNewLine = true;
        break;
    case 'O':
    case 'o':
        PS2Symbol = EXSYMBOL_CIRCLE;
        break;
    case 'P':
    case 'p':
        ApplyStyle(HUD_COLOUR_PURPLE);
        break;
    case 'Q':
    case 'q':
        PS2Symbol = EXSYMBOL_SQUARE;
        break;
    case 'R':
    case 'r':
        ApplyStyle(HUD_COLOUR_RED);
        break;
    case 'S':
    case 's':
        ApplyStyle(HUD_COLOUR_LIGHT_GRAY);
        break;
    case 'T':
    case 't':
        PS2Symbol = EXSYMBOL_TRIANGLE;
        break;
    case 'U':
    case 'u':
        PS2Symbol = EXSYMBOL_DPAD_UP;
        break;
    case 'V':
    case 'v':
        PS2Symbol = EXSYMBOL_R2;
        break;
    case 'W':
    case 'w':
        ApplyStyle(HUD_COLOUR_LIGHT_GRAY);
        break;
    case 'X':
    case 'x':
        PS2Symbol = EXSYMBOL_CROSS;
        break;
    case 'Y':
    case 'y':
        ApplyStyle(HUD_COLOUR_CREAM);
        break;
    case 'l':
        ApplyStyle(HUD_COLOUR_BLACK);
        break;
    default:
        break;
    }

    if (*next != '~') {
        // skip text to the next '~' character.
        for(; *next && *next != '~'; next++);
    }

    if (*next)
        return next + 1;

    return next + 2;
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
        m_Scale.Set(w * 0.8f, h);
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
    m_Color = color;

    if (m_dwFontAlpha < 255) {
        m_Color.a = (color.a * m_dwFontAlpha) / 255;
    }
}

// 0x719490
void CFont::SetFontStyle(eFontStyle style)
{
    switch (style) {
    case eFontStyle::FONT_PRICEDOWN:
        m_FontTextureId = 1;
        m_FontStyle = 1;
        break;
    case eFontStyle::FONT_MENU:
        m_FontTextureId = 0;
        m_FontStyle = 2;
        break;
    default:
        m_FontTextureId = static_cast<uint8>(style);
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
    m_FontDropColor = color;

    if (m_dwFontAlpha < 255)
        m_FontDropColor.a = m_Color.a * m_dwFontAlpha;
}

// 0x719570
void CFont::SetDropShadowPosition(int16 value)
{
    m_nFontOutlineSize = 0;
    m_nFontOutlineOrShadow = 0;
    m_nFontShadow = (uint8)value;
}

// 0x719590
void CFont::SetEdge(int8 value) {
    m_nFontShadow = 0;
    m_nFontOutlineSize = value;
    m_nFontOutlineOrShadow = value;
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
    m_bFontCentreAlign = alignment == eFontAlignment::ALIGN_CENTER;
    m_bFontRightAlign = alignment == eFontAlignment::ALIGN_RIGHT;
}

// 0x719800
void CFont::InitPerFrame()
{
    m_nFontOutline = 0;
    m_nFontOutlineOrShadow = 0;
    m_nFontShadow = 0;
    m_bNewLine = false;
    PS2Symbol = EXSYMBOL_NONE;
    RenderState.m_dwFontTexture = 0;
    pEmptyChar = &setup[0];

    CSprite::InitSpriteBuffer();
}

// 0x719840
void CFont::RenderFontBuffer()
{
    plugin::Call<0x719840>();
}

// 0x71A0E0
float CFont::GetStringWidth(char* string, bool full, bool scriptText)
{
    size_t len = CMessages::GetStringLength(string);

    char data[400] = {0};

    strncpy(data, string, len);

    CMessages::InsertPlayerControlKeysInString(data);

    float width = 0.0f;
    bool bLastWasTag = false, bLastWasLetter = false;

    char* pStr = data;

    while (true) {
        if (*pStr == ' ' && !full)
            break;
        if (*pStr == '\0')
            break;

        if (*pStr == '~') {
            if (!full && (bLastWasTag || bLastWasLetter))
                return width;

            char* next = pStr + 1;

            if (*next != '~') {
                for (; *next && *next != '~'; next++);
            }

            pStr = next + 1;

            if (bLastWasLetter || *pStr == '~')
                bLastWasTag = true;
        }
        else {
            if (!full && *pStr == ' ' && bLastWasTag)
                return width;

            char upper = *pStr - 0x20;

            pStr++;
            if (scriptText) {
                width += GetScriptLetterSize(upper);
            }
            else {
                width += GetLetterSize(upper);
            }
        }
    }

    return width;
}

// same as RenderFontBuffer() (0x71A210)
void CFont::DrawFonts() {
    RenderFontBuffer();
}

// 0x71A220
int16 CFont::ProcessCurrentString(bool print, float x, float y, const char* text)
{
    return plugin::CallAndReturn<int16, 0x71A220, bool, float, float, const char*>(print, x, y, text);
}

// 0x71A5E0
int16 CFont::GetNumberLines(float x, float y, const char* text)
{
    return ProcessCurrentString(false, x, y, text);
}

// 0x71A600
int16 CFont::ProcessStringToDisplay(float x, float y, const char* text)
{
    return ProcessCurrentString(true, x, y, text);
}

// 0x71A620
void CFont::GetTextRect(CRect* rect, float x, float y, const char* text)
{
    const int16 nLines = GetNumberLines(x, y, text);

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
    rect->top = (float)nLines * 18.0f * m_Scale.y + y + 4.0f;
}

// 0x71A700
void CFont::PrintString(float x, float y, const char* text)
{
    if (*text == '\0' || *text == '*')
        return;

    if (m_bFontBackground) {
        CRect rt;

        RenderState.m_color = m_Color;
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
    float drawY = y - (18.0f * m_Scale.y) * (float)CFont::GetNumberLines(x, y, text);

    if (m_fSlant != 0.0f)
        drawY -= (m_fSlantRefPoint.x - x) * m_fSlant + m_fSlantRefPoint.y;

    PrintString(x, drawY, text);
}

// 0x719750
float CFont::GetLetterSize(uint8 letterId)
{
    uint8 propValueIdx = letterId;

    if (letterId == 0x3F) {
        letterId = 0;
        propValueIdx = 0;
    }

    if (m_FontStyle)
        propValueIdx = GetIDforPropVal(letterId, m_FontStyle);
    else if (propValueIdx == 0x91)
        propValueIdx = '?';
    else if (propValueIdx > 0x9B)
        propValueIdx = 0;

    if (m_bFontPropOn)
        return ((float)gFontData[m_FontTextureId].m_propValues[propValueIdx]
            + (float)m_nFontOutlineSize) * m_Scale.x;

    return ((float)gFontData[m_FontTextureId].m_unpropValue + (float)m_nFontOutlineSize)
        * m_Scale.x;
}

// 0x719670, original name unknown
float GetScriptLetterSize(uint8 letterId)
{
    return plugin::CallAndReturn<float, 0x719670, uint8>(letterId);
}

// 0x7192C0
uint8 GetIDforPropVal(uint8 letterId, uint8 fontStyle)
{
    if (fontStyle == 1) {
        switch (letterId) {
        case 1:
            return 208;
        case 4:
            return 93;
        case 7:
            return 206;
        case 14:
            return 207;
        }
    }

    switch (letterId) {
    case 6:
        return 10;
    case 8:
        return 94;
    case 9:
        return 95;
    case 26:
        return 154;
    case 31:
        return 91;
    case 62:
        return 32;
    case 143:
        return 205;
    }

    if (letterId >= 16 && letterId <= 25)
        return letterId - 128;
    if (letterId >= 21 && letterId <= 58)
        return letterId + 122;
    if (letterId >= 64 && letterId <= 90)
        return letterId + 90;

    return letterId;
}

// 0x718770
float GetLetterIdPropValue(uint8 letterId)
{
    uint8 id = letterId;

    if (letterId == '?')
        id = 0;

    if (CFont::RenderState.m_bPropOn)
        return gFontData[CFont::RenderState.m_dwFontTexture].m_propValues[id];
    else
        return gFontData[CFont::RenderState.m_dwFontTexture].m_unpropValue;
}
