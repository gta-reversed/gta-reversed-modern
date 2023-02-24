#include "StdInc.h"

#include "AmbienceTrackManagerDebugModule.h"

#include <imgui.h>
#include "AEAmbienceTrackManager.h"

void AmbienceTrackManagerDebugModule::RenderWindow() {
    const notsa::ui::ScopedWindow window{ "Ambience Track Manager", {400.f, 600.f}, m_IsOpen, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize };
    if (!m_IsOpen) {
        return;
    }

    if (ImGui::BeginTable("AmbienceTrackManagerDebugModule", 2, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Borders)) {
        const auto KVRow = [](const char* label, const char* vfmt, auto v) {
            ImGui::TableNextColumn();
            ImGui::Text(label);

            ImGui::TableNextColumn();
            ImGui::Text(vfmt, v);
        };

        KVRow("Stop",                           "%s", AEAmbienceTrackManager.m_bStop ? "true" : "false");
        KVRow("Stop Prev",                      "%s", AEAmbienceTrackManager.m_bStopPrev ? "true" : "false");
        KVRow("b3",                             "%s", AEAmbienceTrackManager.m_b3 ? "true" : "false");
        KVRow("Is Ambience Radio Active",       "%d", AEAmbienceTrackManager.m_IsAmbienceRadioActive);
        KVRow("Channel Id",                     "%d", AEAmbienceTrackManager.m_nChannel);
        KVRow("Special Mission Ambience Track", "%d", AEAmbienceTrackManager.m_nSpecialMissionAmbienceTrack);
        KVRow("Track Play Time",                "%d", AEAmbienceTrackManager.m_nTrackPlayTime);
        KVRow("Time In Ms",                     "%d", AEAmbienceTrackManager.m_nTimeInMs);
        KVRow("dword24",                        "%d", AEAmbienceTrackManager.dword24);
        KVRow("byte28",                         "%d", AEAmbienceTrackManager.byte28);

        ImGui::EndTable();
    }

    ImGui::SliderFloat("Volume %f",    &AEAmbienceTrackManager.m_nVolume, -100.f, 100.f, NULL, ImGuiSliderFlags_Logarithmic);
    ImGui::SliderFloat("Frequency %f", &AEAmbienceTrackManager.m_fFreqFactor, 0.0f, 100.0f, NULL, ImGuiSliderFlags_Logarithmic);
    ImGui::InputInt("Track Id %d",     &AEAmbienceTrackManager.m_nTrackId);
}

void AmbienceTrackManagerDebugModule::RenderMenuEntry() {
    notsa::ui::DoNestedMenuIL({ "Extra", "Audio" }, [&] {
        ImGui::MenuItem("Ambience Track Manager", nullptr, &m_IsOpen);
    });
}
