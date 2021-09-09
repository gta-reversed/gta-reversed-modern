#include "StdInc.h"

#ifdef EXTRA_DEBUG_FEATURES

#include "COcclusion.h"
#include "COccluder.h"

#include "imgui.h"

bool COcclusionDebugModule::DrawActiveOcclusions = false;
int COcclusionDebugModule::NumEntitiesSkipped = 0;

void COcclusionDebugModule::ProcessImgui() {
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
        for (int32 ind = 0; ind < COcclusion::NumActiveOccluders; ++ind) {
            auto& occl = COcclusion::aActiveOccluders[ind];
            for (auto i = 0; i < occl.m_cLinesCount; ++i) {
                auto& line = occl.m_aLines[i];
                const auto vecEnd = line.m_vecOrigin + line.m_vecDirection * line.m_fLength;
                const CRGBA white = {255, 255, 255, 255};
                CLines::ImmediateLine2D(line.m_vecOrigin, vecEnd, white, white);
            }
        }
    }
}
#endif
