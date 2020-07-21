/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CRGBA.h"
#include "CRect.h"
#include "CSprite2d.h"

#define MAX_FONT_SPRITES 2
#define MAX_FONT_BUTTON_SPRITES 15

struct tFontData {
    char m_propValues[208];
    char m_spaceValue;
    char m_unpropValue;
};

enum eFontAlignment : unsigned char {
    ALIGN_CENTER,
    ALIGN_LEFT,
    ALIGN_RIGHT
};

enum eFontStyle : unsigned char {
    FONT_GOTHIC,
    FONT_SUBTITLES,
    FONT_MENU,
    FONT_PRICEDOWN
};
class  CFont {
public:
    // static variables

    // font textures array. Num of elements: MAX_FONT_SPRITES (2)
    static CSprite2d *Sprite;
    // button textures array. Num of elements: MAX_FONT_BUTTON_SPRITES (15)
    static CSprite2d *ButtonSprite;
    static unsigned char& m_nExtraFontSymbolId;
    static bool& m_bNewLine;
    static CRGBA *m_Color;
    static CVector2D *m_Scale;
    static float& m_fSlant;
    static CVector2D *m_fSlantRefPoint;
    static bool& m_bFontJustify;
    static bool& m_bFontCentreAlign;
    static bool& m_bFontRightAlign;
    static bool& m_bFontBackground;
    static bool& m_bEnlargeBackgroundBox;
    static bool& m_bFontPropOn;
    static bool& m_bFontIsBlip;
    static unsigned int m_dwFontAlpha;
    static CRGBA *m_FontBackgroundColor;
    static float& m_fWrapx;
    static float& m_fFontCentreSize;
    static float& m_fRightJustifyWrap;
    static unsigned char& m_FontTextureId;
    static unsigned char& m_FontStyle;
    static unsigned char& m_nFontShadow;
    static CRGBA *m_FontDropColor;
    static unsigned char& m_nFontOutlineSize;
    static unsigned char& m_nFontOutline;

    // static functions

    // CFont initialisation
    static void Initialise();
    // CFont closing
    static void Shutdown();
    // this adds a single character into rendering buffer
    static void PrintChar(float x, float y, char character);
    // get next ' ' character in a string
    static char *GetNextSpace(char *string);
    // tags processing
    static char *ParseToken(char *text, CRGBA & color, bool isBlip, char *tag);
    // text scaling
    static void SetScale(float w, float h);
    // text scaling depends on current language
    static void SetScaleForCurrentlanguage(float w, float h);
    // set text rotation point
    static void SetSlantRefPoint(float x, float y);
    // set text rotation angle
    static void SetSlant(float value);
    // set text color
    static void SetColor(CRGBA color);
    // set text style
    static void SetFontStyle(short style);
    // set line width at right
    static void SetWrapx(float value);
    // set line width at center
    static void SetCentreSize(float value);
    static void SetRightJustifyWrap(float value);
    // like a 'global' font alpha, multiplied with each text alpha (from SetColor)
    static void SetAlphaFade(float alpha);
    // drop color is used for text shadow and text outline
    static void SetDropColor(CRGBA color);
    // set shadow size
    static void SetDropShadowPosition(short value);
    // set outline size
    static void SetEdge(short value);
    // toggles character proportions in text
#ifdef SetProp
#undef SetProp
#endif
    static void SetProportional(bool on);
    // setups text background
    static void SetBackground(bool enable, bool includeWrap);
    // sets background color
    static void SetBackgroundColor(CRGBA color);
    static void SetJustify(bool on);
    static void SetOrientation(eFontAlignment alignment);
    // need to call this each frame
    static void InitPerFrame();
    // draw text we have in buffer
    static void RenderFontBuffer();
    static float GetStringWidth(char *string, bool unk1, bool unk2);
    // same as RenderFontBuffer()
    static void DrawFonts();
    static short ProcessCurrentString(bool print, float x, float y, char *text);
    static short GetNumberLines(float x, float y, char *text);
    static short ProcessStringToDisplay(float x, float y, char *text);
    static void GetTextRect(CRect *rect, float x, float y, char *text);
    static void PrintString(float x, float y, char *text);
    static void PrintStringFromBottom(float x, float y, char *text);
};
