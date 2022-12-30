#pragma once

#include "RenderWare.h"

class FxPrtMult_c {
public:
    RwRGBAReal m_Color;
    float      m_fSize;
    float      field_14;
    float      m_fLife;

public:
    FxPrtMult_c();
    FxPrtMult_c(float red, float green, float blue, float alpha, float size, float arg5, float lastFactor);

    void SetUp(float red, float green, float blue, float alpha, float size, float arg5, float lastFactor);

    inline void SetColor(float red, float green, float blue, float alpha = 1.0f) {
        m_Color.red   = red;
        m_Color.green = green;
        m_Color.blue  = blue;
        m_Color.alpha = alpha;
    }
};

VALIDATE_SIZE(FxPrtMult_c, 0x1C);
