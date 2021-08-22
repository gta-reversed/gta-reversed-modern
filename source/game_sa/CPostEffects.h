#pragma once

#include "PluginBase.h"
#include "rwcore.h"

class CPostEffects
{
public:
    static void CPostEffects::InjectHooks();

    static float& CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE;
    static float& CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP;
    static float& CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT;
    static int& CPostEffects::m_colourLeftUOffset;
    static int& CPostEffects::m_colourRightUOffset;
    static int& CPostEffects::m_colourTopVOffset;
    static int& CPostEffects::m_colourBottomVOffset;
    static bool& CPostEffects::m_bRadiosity;
    static bool& CPostEffects::m_bInCutscene;
    static bool& CPostEffects::m_bNightVision;
    static bool& CPostEffects::m_bInfraredVision;
    static bool& CPostEffects::m_bGrainEnable;
    static bool& CPostEffects::m_bHeatHazeFX;
    static bool& CPostEffects::m_bDarknessFilter;
    static bool& CPostEffects::m_bCCTV;
    static bool& CPostEffects::m_bSkipPostProcess;
    static bool& CPostEffects::m_bSavePhotoFromScript;
    static RwRGBAReal& CPostEffects::m_fInfraredVisionHeatObjectCol;

    static RwRaster& CPostEffects::pRasterFrontBuffer;
    static RwRaster& CPostEffects::randomRaster;

    static void DrawQuad(float x1, float y1, float x2, float y2, char red, unsigned int green, unsigned int blue, char alpha, RwRaster *raster);
    static bool IsVisionFXActive ();
    static bool NightVisionSetLights();
    static void ImmediateModeRenderStatesReStore();
    static bool InfraredVisionSetLightsForDefaultObjects();
    static bool FilterFX_StoreAndSetDayNightBalance();
    static bool FilterFX_RestoreDayNightBalance();
    static void Close();
    static void ScriptResetForEffects();
};
