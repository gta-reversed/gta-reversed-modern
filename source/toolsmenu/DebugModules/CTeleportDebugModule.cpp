#include "StdInc.h"

#ifdef EXTRA_DEBUG_FEATURES
#include "CTeleportDebugModule.h"
#include <imgui.h>

struct SavedLocation {
    std::string name{};
    CVector     pos{};
};
namespace {
    std::vector<SavedLocation> s_SavedLocations{};
};
namespace TeleportDebugModule {
void DoTeleportTo(CVector& pos, bool doAdjustToGroundZ = true) {
    CStreaming::LoadScene(pos);

    if (doAdjustToGroundZ) {
        //pos.z = TheCamera.CalculateGroundHeight(eGroundHeightType::EXACT_GROUND_HEIGHT) + 5.f;
        pos.z = CWorld::FindGroundZForCoord(pos.x, pos.y) + 2.f;
    }

    FindPlayerPed()->m_nAreaCode = eAreaCodes::AREA_CODE_NORMAL_WORLD;
    CGame::currArea = eAreaCodes::AREA_CODE_NORMAL_WORLD;
    FindPlayerPed()->Teleport(pos, true);
}

void ProcessImGui() {
    using namespace ImGui;

    static CVector pos{};

    PushItemWidth(200.f);
    InputFloat3("Teleport to", reinterpret_cast<float(&)[3]>(pos), "%.2f"); // Kinda hacky, but it's okay, if this was to break, we'd have bigger problems anyways.
    PopItemWidth();

    if (SameLine(); Button("Teleport")) {
        DoTeleportTo(pos);
    }

    if (SameLine(); Button("Save position")) {
        s_SavedLocations.emplace_back(CTheZones::GetZoneName(pos), pos);
    }

    if (SameLine(); Button("Random")) { // Set random coords
        pos = CVector{
            CGeneral::GetRandomNumberInRange(-3072.0f, 3072.0f),
            CGeneral::GetRandomNumberInRange(-3072.0f, 3072.0f),
            0.0f
        };

        if (GetIO().KeyAlt) { // Teleport as well if alt down
            DoTeleportTo(pos); 
        }
    }

    static auto selected{ -1 };
    if (!s_SavedLocations.empty() && BeginTable("Saved Positions", 2, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_BordersInnerH)) {
        TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
        TableSetupColumn("Position", ImGuiTableColumnFlags_WidthFixed);
        TableHeadersRow();

        for (auto i = 0u, e = s_SavedLocations.size(); i < e; i++) {
            auto& l = s_SavedLocations[i];

            PushID(l.name.c_str());
            BeginGroup();
            TableNextRow();

            if (TableNextColumn(); Selectable(l.name.c_str(), false, ImGuiSelectableFlags_SpanAllColumns | ImGuiSelectableFlags_AllowDoubleClick)) {
                //selected = i;
                if (IsMouseDoubleClicked(0)) {
                    DoTeleportTo(l.pos);
                }
            }
            TableNextColumn(); Text("%.2f %.2f %.2f", l.pos.x, l.pos.y, l.pos.z);

            EndGroup();
            PopID();
        }
        EndTable();
    }
}

void ProcessRender() {
}
}; // namespace TeleportDebugModule
#endif
