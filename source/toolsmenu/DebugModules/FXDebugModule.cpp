#include "StdInc.h"

#include "FXDebugModule.h"

#include "PostEffects.h"

#include <imgui.h>

namespace FXDebugModule {
void Initialise() {
    // NOP
}

void ProcessImgui() {
    const struct { const char* name; bool& value; } settings[]{
        { "In Cutscene",             CPostEffects::m_bInCutscene           },
        { "Skip Post Process",       CPostEffects::m_bDisableAllPostEffect },
        { "Save Photo From Script",  CPostEffects::m_bSavePhotoFromScript  },
        { "Radiosity",               CPostEffects::m_bRadiosity            },
        { "Night Vision",            CPostEffects::m_bNightVision          },
        { "Infrared Vision",         CPostEffects::m_bInfraredVision       },
        { "Grain",                   CPostEffects::m_bGrainEnable          },
        { "Heat Haze FX",            CPostEffects::m_bHeatHazeFX           },
        { "Darkness Filter",         CPostEffects::m_bDarknessFilter       },
        { "CCTV",                    CPostEffects::m_bCCTV                 },
        { "SpeedFX Test Mode",       CPostEffects::m_bSpeedFXTestMode      },
        { "Fog",                     CPostEffects::m_bFog                  },
        { "Water Depth Darkness",    CPostEffects::m_bWaterDepthDarkness   },
        { "Color Correction",        CPostEffects::m_bColorEnable          },
    };
    for (const auto& [name, value] : settings) {
        ImGui::Checkbox(name, &value);
    }

    const auto u8_zero = 0, u8_max = 255;

    if (ImGui::CollapsingHeader("Infrared Vision")) {
        ImGui::DragScalar("Grain Strength",    ImGuiDataType_S32, &CPostEffects::m_InfraredVisionGrainStrength, 0.5f, &u8_zero, &u8_max);
        ImGui::DragFloat("Filter Radius",      &CPostEffects::m_fInfraredVisionFilterRadius, 0.001f);
        // ImGui::DragFloat("Switch On FX Coun",  &CPostEffects::m_fInfraredVisionSwitchOnFXCoun);
        ImGui::DragScalarN("Color",            ImGuiDataType_U8, &CPostEffects::m_InfraredVisionCol, 4);
        ImGui::DragScalarN("Main Color",       ImGuiDataType_U8, &CPostEffects::m_InfraredVisionMainCol, 4);
        ImGui::DragFloat4("Heat Object Color", *reinterpret_cast<float(*)[4]>(&CPostEffects::m_fInfraredVisionHeatObjectCol), 0.01f, 0.0, 1.0f);
    }

    if (ImGui::CollapsingHeader("Heat Haze FX")) {
        const auto min = HEAT_HAZE_0;
        const auto max = (MAX_HEAT_HAZE_TYPES - 1);

        ImGui::DragScalar("Type",          ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXType, 0.05f, &min, &max);
        ImGui::DragScalar("Intensity",     ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXIntensity, 0.5f, &u8_zero, &u8_max);
        ImGui::DragScalar("Random Shift",  ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXRandomShift);
        ImGui::DragScalar("Speed Min",     ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXSpeedMin);
        ImGui::DragScalar("Speed Max",     ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXSpeedMax);
        ImGui::DragScalar("Scan Size X",   ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXScanSizeX);
        ImGui::DragScalar("Scan Size Y",   ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXScanSizeY);
        ImGui::DragScalar("Render Size X", ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXRenderSizeX);
        ImGui::DragScalar("Render Size Y", ImGuiDataType_U32, &CPostEffects::m_HeatHazeFXRenderSizeY);
    };
}

void ProcessRender() {
    // NOP
}
};
