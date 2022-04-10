#pragma once

#include <RenderWare.h>
#include "Vector.h"

enum class ERenderColorType : int32 {
    DEFAULT = 0,
    RANGE   = 1,
    BRIGHT  = 2,
};

struct RenderInfo_t {
    RwRGBA           m_Color;
    uint8            m_nColorRangeRed;
    uint8            m_nColorRangeGreen;
    uint8            m_nColorRangeBlue;
    uint8            m_nColorBrightBias;
    ERenderColorType m_nColorType;

    float    m_fSizeX;
    float    m_fSizeY;
    float    m_fSizeXBias;
    float    m_fSizeYBias;

    float    m_fSpriteTop;
    float    m_fSpriteBottom;
    float    m_fSpriteLeft;
    float    m_fSpriteRight;

    int32    m_nTrailScreenMode;
    float    m_fTrailTime;

    bool     m_bAnimTextureUsed;
    int8     m_nAnimTexId;

    bool     m_bHeatHaze;
    bool     m_bSelfLit;

    RwMatrix m_FlatMatrix;
    bool     m_bFlatUsed;

    bool     m_bDirUsed;
    bool     m_bIgnoreDirThisFrame;

    int8     m_nSmokeCount; // ?
    CVector  m_Direction;
    float    m_ColR;
    float    m_ColG;
    float    m_ColB;
    float    m_ColA;
    float    field_98;
    float    m_PrtSize;  // ?
    float    m_Lifetime; // ?

    void SetColor(float red, float green, float blue, float alpha) {
        m_Color.red   = (uint8)red;
        m_Color.green = (uint8)green;
        m_Color.blue  = (uint8)blue;
        m_Color.alpha = (uint8)alpha;
    }

    void SetRangeColor(float red, float green, float blue) {
        m_nColorRangeRed   = (uint8)red;
        m_nColorRangeGreen = (uint8)green;
        m_nColorRangeBlue  = (uint8)blue;
    }

    void Process() {
        m_Color.red           = 255;
        m_Color.green         = 255;
        m_Color.blue          = 255;
        m_Color.alpha         = 255;
        m_fSizeX              = 0.1f;
        m_fSizeY              = 0.1f;
        m_nColorType          = ERenderColorType::DEFAULT;
        m_fSizeXBias          = 0.0f;
        m_fSizeYBias          = 0.0f;
        m_fSpriteTop          = 0.5f;
        m_fSpriteBottom       = -0.5f;
        m_fSpriteLeft         = 0.5f;
        m_fSpriteRight        = -0.5f;
        m_bHeatHaze           = false;
        m_bSelfLit            = false;
        m_bFlatUsed           = false;
        m_bAnimTextureUsed    = false;
        m_nTrailScreenMode    = 0;
        m_bDirUsed            = false;
        m_bIgnoreDirThisFrame = false;
        m_nSmokeCount         = -1;
    }
};
VALIDATE_SIZE(RenderInfo_t, 0xA4);
