#include "StdInc.h"

#ifdef EXTRA_DEBUG_FEATURES

#include "Occlusion.h"
#include "ActiveOccluder.h"
#include "Occluder.h"
#include "Lines.h"

#include "imgui.h"

bool COcclusionDebugModule::DrawActiveOcclusions = false;
int COcclusionDebugModule::NumEntitiesSkipped = 0;

void COcclusionDebugModule::ProcessImGui() {
    ImGui::InputScalar("NumInteriorOcculdersOnMap", ImGuiDataType_::ImGuiDataType_S32, &COcclusion::NumInteriorOcculdersOnMap, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("NumOccludersOnMap", ImGuiDataType_::ImGuiDataType_S32, &COcclusion::NumOccludersOnMap, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("NumActiveOccluders", ImGuiDataType_::ImGuiDataType_S32, &COcclusion::NumActiveOccluders, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);

    ImGui::NewLine();
    ImGui::InputScalar("FarAwayList", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::FarAwayList, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("NearbyList", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::NearbyList, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("ListWalkThroughFA", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::ListWalkThroughFA, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);
    ImGui::InputScalar("PreviousListWalkThroughFA", ImGuiDataType_::ImGuiDataType_S16, &COcclusion::PreviousListWalkThroughFA, nullptr, nullptr, nullptr, ImGuiInputTextFlags_ReadOnly);

    ImGui::NewLine();
    ImGui::Text("Num skipped: %d", COcclusionDebugModule::NumEntitiesSkipped);
    COcclusionDebugModule::NumEntitiesSkipped = 0;

    ImGui::NewLine();
    ImGui::Checkbox("Draw Active Occlusions", &COcclusionDebugModule::DrawActiveOcclusions);
}

void COcclusionDebugModule::ProcessRender() {
    if (COcclusionDebugModule::DrawActiveOcclusions && COcclusion::NumActiveOccluders > 0) {
        CSprite::FlushSpriteBuffer();
        const CRGBA white = { 255, 255, 255, 255 };
        for (auto& occl : std::span{ COcclusion::aActiveOccluders, (size_t)COcclusion::NumActiveOccluders }) {
            for (auto& line : std::span{ occl.m_aLines, occl.m_cLinesCount }) {
                const auto vecEnd = line.m_vecOrigin + line.m_vecDirection * line.m_fLength;
                CLines::ImmediateLine2D(line.m_vecOrigin, vecEnd, white, white);
            }
        }
    }
}
#endif
