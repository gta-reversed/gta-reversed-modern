#pragma once

class CPostEffects
{
public:
    static float& CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE;
    static float& CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP;
    static float& CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT;
    static int& CPostEffects::m_colourLeftUOffset;
    static int& CPostEffects::m_colourRightUOffset;
    static int& CPostEffects::m_colourTopVOffset;
    static int& CPostEffects::m_colourBottomVOffset;
    static bool& CPostEffects::m_bRadiosity;
};