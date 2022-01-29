#include "StdInc.h"
#include "FXDebugModule.h"
#include <PostEffects.h>

#include <imgui.h>

namespace FXDebugModule {
void Initialise() {
    // NOP
}

void ProcessImgui() {
    const struct { const char* name; bool& value; } settings[]{
        {"In Cutscene",             CPostEffects::m_bInCutscene},
        {"Skip Post Process",       CPostEffects::m_bDisableAllPostEffect},
        {"Save Photo From Script",  CPostEffects::m_bSavePhotoFromScript},
        {"Radiosity",               CPostEffects::m_bRadiosity},
        {"Night Vision",            CPostEffects::m_bNightVision},
        {"Infrared Vision",         CPostEffects::m_bInfraredVision},
        {"Grain",                   CPostEffects::m_bGrainEnable},
        {"Heat Haze FX",            CPostEffects::m_bHeatHazeFX},
        {"Darkness Filter",         CPostEffects::m_bDarknessFilter},
        {"CCTV",                    CPostEffects::m_bCCTV},
        {"SpeedFX Test Mode",       CPostEffects::m_bSpeedFXTestMode},
        {"Fog",                     CPostEffects::m_bFog},
        {"Water Depth Darkness",    CPostEffects::m_bWaterDepthDarkness},
        {"Color Correction",        CPostEffects::m_bColorEnable},
    };
    for (const auto& [name, value] : settings) {
        ImGui::Checkbox(name, &value);
    }
}

void ProcessRender() {
    // NOP
}
};
