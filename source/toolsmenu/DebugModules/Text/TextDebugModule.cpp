#include "StdInc.h"

#include "TextDebugModule.h"

#include <imgui.h>

namespace TextDebugModule {

void ProcessImgui() {
    static ImGuiTableFlags flags = ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody;
    if (ImGui::BeginTable("PoolsDebugModule", 2, flags)) {
        ImGui::TableSetupColumn("Key");
        ImGui::TableSetupColumn("Str");
        ImGui::TableHeadersRow();


        for (auto i = 0; i < TheText.m_MainKeyArray.m_size; i++) {
            const CKeyEntry* str = &TheText.m_MainKeyArray.m_data[i];

            ImGui::TableNextRow();
            ImGui::PushID(i);

            ImGui::TableNextColumn();
            ImGui::Text("%d", str->hash);

            ImGui::TableNextColumn();
            ImGui::Text("%s", str->string);

            ImGui::PopID();
        }

        ImGui::EndTable();
    }
}

void ProcessRender() {

}

} // namespace TextDebugModule