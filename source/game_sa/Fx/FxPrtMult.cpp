#include "StdInc.h"

#include "FxPrtMult.h"

// 0x4AB270
FxPrtMult_c::FxPrtMult_c() {
    SetColor(1.0f, 1.0f, 1.0f, 1.0f);
    m_fSize       = 1.0f;
    field_14      = 1.0f;
    m_fLife       = 1.0f;
}

// 0x4AB290
FxPrtMult_c::FxPrtMult_c(float red, float green, float blue, float alpha, float size, float arg5, float lastFactor) {
    SetUp(red, green, blue, alpha, size, arg5, lastFactor);
}

// 0x4AB2D0
void FxPrtMult_c::SetUp(float red, float green, float blue, float alpha, float size, float arg5, float lastFactor) {
    SetColor(red, green, blue, alpha);
    m_fSize       = size;
    field_14      = arg5;
    m_fLife       = lastFactor;
}
