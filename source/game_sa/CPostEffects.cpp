#include "StdInc.h"

float& CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE = *(float*)0x8D5168;
float& CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP = * (float*)0x8D516C;
float& CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT = *(float*)0x8D5170;
int& CPostEffects::m_colourLeftUOffset = *(int*)0x8D5150;
int& CPostEffects::m_colourRightUOffset = *(int*)0x8D5154;
int& CPostEffects::m_colourTopVOffset = *(int*)0x8D5158;
int& CPostEffects::m_colourBottomVOffset = *(int*)0x8D515C;
bool& CPostEffects::m_bRadiosity = *(bool*)0xC402CC;
bool& CPostEffects::m_bInCutscene = *(bool*)0xC402B7;
bool& CPostEffects::m_bNightVision = *(bool*)0xC402B8;
bool& CPostEffects::m_bInfraredVision = *(bool*)0xC402B9;


bool CPostEffects::IsVisionFXActive()
{
    return plugin::CallAndReturn<bool, 0x7034F0>();
}

bool CPostEffects::NightVisionSetLights()
{
    return plugin::CallAndReturn<bool, 0x7012E0>();
}

bool CPostEffects::InfraredVisionSetLightsForDefaultObjects()
{
    return plugin::CallAndReturn<bool, 0x701430>();
}

bool CPostEffects::FilterFX_StoreAndSetDayNightBalance()
{
    return plugin::CallAndReturn<bool, 0x7034B0>();
}

bool CPostEffects::FilterFX_RestoreDayNightBalance()
{
    return plugin::CallAndReturn<bool, 0x7034D0>();
}
