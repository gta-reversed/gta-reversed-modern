#include "StdInc.h"

#include "TextDebugModule.h"
#include <imgui.h>

namespace TextDebugModule {

void ProcessImGui() {
    const auto flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
    if (ImGui::BeginTable("TextDebugModule", 3, flags)) {
        ImGui::TableSetupColumn("Table");
        ImGui::TableSetupColumn("Key");
        ImGui::TableSetupColumn("String");
        ImGui::TableHeadersRow();

        const auto WriteRow = [](const auto& entry, const auto& tabl) {
            ImGui::TableNextRow();
            ImGui::PushID(&entry);

            ImGui::TableNextColumn();
            ImGui::Text("%s", tabl);

            ImGui::TableNextColumn();
            ImGui::Text("%08X", entry.hash);

            ImGui::TableNextColumn();
            ImGui::Text("%s", entry.string);

            ImGui::PopID();
        };

        for (const auto& entry : TheText.GetMissionKeys()) {
            WriteRow(entry, TheText.GetMissionName());
        }

        for (const auto& entry : TheText.GetKeys()) {
            WriteRow(entry, "MAIN");
        }

        ImGui::EndTable();
    }
}

} // namespace TextDebugModule
