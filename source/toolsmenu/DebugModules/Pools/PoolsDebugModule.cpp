#include "StdInc.h"

#include "PoolsDebugModule.h"

#include "EntryExitManager.h"
#include "StuntJumpManager.h"
#include "CustomCarEnvMapPipeline.h"

PoolsDebugModule::PoolsDebugModule() :
    DebugModuleSingleWindow("Pools Stats", {446.f, 512.f})
{
}

void PoolsDebugModule::RenderMainWindow() {
    if (!ImGui::BeginTable("PoolsDebugModule", 5, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
        return;
    }

    ImGui::TableSetupColumn("Name");
    ImGui::TableSetupColumn("Size");
    ImGui::TableSetupColumn("Active objects");
    ImGui::TableSetupColumn("Usage (%)");
    ImGui::TableSetupColumn("Locked");
    ImGui::TableHeadersRow();

    const auto Draw = [](auto* pool, const char* name) {
        ImGui::TableNextRow();
        ImGui::PushID(&pool);

        ImGui::TableNextColumn();
        ImGui::Text("%s", name);

        ImGui::TableNextColumn();
        ImGui::Text("%d", pool->GetSize());

        const auto used = pool->GetNoOfUsedSpaces();
        const auto percentage = static_cast<float>(used / static_cast<float>(pool->GetSize()));

        ImGui::TableNextColumn();
        ImGui::PushStyleColor(ImGuiCol_Text, { 1.0f * percentage, 1.0f - percentage, 0.0f, 1.0f });
        ImGui::Text("%d", used);

        ImGui::TableNextColumn();
        ImGui::Text("%.1f %%", percentage * 100.f);
        ImGui::PopStyleColor();

        ImGui::TableNextColumn();
        ImGui::Text(pool->m_bIsLocked ? "T" : "F");

        ImGui::PopID();
    };

    // CPools
    Draw(GetPedPool(), "Ped");
    Draw(GetVehiclePool(), "Vehicle");
    Draw(GetBuildingPool(), "Building");
    Draw(GetObjectPool(), "Object");
    Draw(GetDummyPool(), "Dummy");
    Draw(GetColModelPool(), "Col Model");
    Draw(GetTaskPool(), "Task");
    Draw(GetPedIntelligencePool(), "Ped Intelligence");
    Draw(GetPtrNodeSingleLinkPool(), "Ptr Node Single Link");
    Draw(GetPtrNodeDoubleLinkPool(), "Ptr Node Double Link");
    Draw(GetEntryInfoNodePool(), "Entry Info Node");
    Draw(GetPointRoutePool(), "Point Route");
    Draw(GetPatrolRoutePool(), "Patrol Route");
    Draw(GetEventPool(), "Event");
    Draw(GetNodeRoutePool(), "Node Route");
    Draw(GetTaskAllocatorPool(), "Task Allocator");
    Draw(GetPedAttractorPool(), "Ped Attractor");

    // Other pools
    Draw(CTxdStore::ms_pTxdPool, "TXD");
    Draw(CIplStore::ms_pPool, "IPL");
    Draw(CEntryExitManager::mp_poolEntryExits, "Entry Exits");
    Draw(CStuntJumpManager::mp_poolStuntJumps, "Stunt Jumps");
    Draw(CColStore::ms_pColPool, "Collision");
    Draw(CQuadTreeNode::ms_pQuadTreeNodePool, "Quad Tree Node");
    Draw(CVehicleModelInfo::CVehicleStructure::m_pInfoPool, "Vehicle Structure");

    Draw(CCustomCarEnvMapPipeline::m_gEnvMapPipeMatDataPool, "Env Map Pipe: Material Data");
    Draw(CCustomCarEnvMapPipeline::m_gEnvMapPipeAtmDataPool, "Env Map Pipe: Atomic Data");
    Draw(CCustomCarEnvMapPipeline::m_gSpecMapPipeMatDataPool, "Spec Map Pipe: Material Data");

    ImGui::EndTable();
}

void PoolsDebugModule::RenderMenuEntry() {
    if (ImGui::BeginMenu("Stats")) {
        if (ImGui::MenuItem("Pools")) {
            SetMainWindowOpen(true);
        }
        ImGui::EndMenu();
    }
}
