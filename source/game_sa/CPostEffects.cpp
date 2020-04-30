#include "StdInc.h"

float& CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE = *(float*)0x8D5168;
float& CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP = * (float*)0x8D516C;
float& CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT = *(float*)0x8D5170;
int& CPostEffects::m_colourLeftUOffset = *(int*)0x8D5150;
int& CPostEffects::m_colourRightUOffset = *(int*)0x8D5154;
int& CPostEffects::m_colourTopVOffset = *(int*)0x8D5158;
int& CPostEffects::m_colourBottomVOffset = *(int*)0x8D515C;
bool& CPostEffects::m_bRadiosity = *(bool*)0xC402CC;