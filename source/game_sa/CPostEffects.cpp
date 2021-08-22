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
bool& CPostEffects::m_bGrainEnable = *(bool*)0xC402B4;
bool& CPostEffects::m_bHeatHazeFX = *(bool*)0xC402BA;
bool& CPostEffects::m_bDarknessFilter = *(bool*)0xC402C4;
bool& CPostEffects::m_bCCTV = *(bool*)0xC402C5;
bool& CPostEffects::m_bSkipPostProcess = *(bool*)0xC402CF;
bool& CPostEffects::m_bSavePhotoFromScript = *(bool*)0xC402D0;
RwRGBAReal& CPostEffects::m_fInfraredVisionHeatObjectCol = *(RwRGBAReal*)0x8D50BC;

RwRaster& CPostEffects::pRasterFrontBuffer = *(RwRaster*)(0xC402D8);
RwRaster& CPostEffects::randomRaster = *(RwRaster*)(0xC402B0);

void CPostEffects::InjectHooks() {
//    ReversibleHooks::Install("CPostEffects", "DrawQuad", 0x700EC0, &CPostEffects::DrawQuad);
//    ReversibleHooks::Install("CPostEffects", "IsVisionFXActive", 0x7034F0, &CPostEffects::IsVisionFXActive);
//    ReversibleHooks::Install("CPostEffects", "NightVisionSetLights", 0x7012E0, &CPostEffects::NightVisionSetLights);
//    ReversibleHooks::Install("CPostEffects", "ImmediateModeRenderStatesReStore", 0x700E00, &CPostEffects::ImmediateModeRenderStatesReStore);
//    ReversibleHooks::Install("CPostEffects", "InfraredVisionSetLightsForDefaultObjects", 0x701430, &CPostEffects::InfraredVisionSetLightsForDefaultObjects);
//    ReversibleHooks::Install("CPostEffects", "FilterFX_StoreAndSetDayNightBalance", 0x7034B0, &CPostEffects::FilterFX_StoreAndSetDayNightBalance);
//    ReversibleHooks::Install("CPostEffects", "FilterFX_RestoreDayNightBalance", 0x7034D0, &CPostEffects::FilterFX_RestoreDayNightBalance);
//    ReversibleHooks::Install("CPostEffects", "Close", 0x7010C0, &CPostEffects::Close);
//    ReversibleHooks::Install("CPostEffects", "ScriptResetForEffects", 0x7010F0, &CPostEffects::ScriptResetForEffects);
}

void CPostEffects::DrawQuad(float x1, float y1, float x2, float y2, char red, unsigned int green, unsigned int blue, char alpha, RwRaster *raster) {
    plugin::Call<0x700EC0>();
}

bool CPostEffects::IsVisionFXActive()
{
    return plugin::CallAndReturn<bool, 0x7034F0>();
}

bool CPostEffects::NightVisionSetLights()
{
    return plugin::CallAndReturn<bool, 0x7012E0>();
}

void CPostEffects::ImmediateModeRenderStatesReStore() {
    plugin::Call<0x700E00>();
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

void CPostEffects::Close()
{
    plugin::Call<0x7010C0>();
}

void CPostEffects::ScriptResetForEffects() {
    plugin::Call<0x7010F0>();
}
