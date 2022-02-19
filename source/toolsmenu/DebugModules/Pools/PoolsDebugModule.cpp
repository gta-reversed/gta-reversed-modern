#include "StdInc.h"

#include "imgui.h"

#include "PoolsDebugModule.h"

// #include "Attractors\PedAttractor.h"
#include "EntryExitManager.h"
#include "StuntJumpManager.h"

namespace PoolsDebugModule {

void Draw(auto* pool, const char* name) {
    ImGui::TableNextRow();
    ImGui::PushID(&pool);

    ImGui::TableNextColumn();
    ImGui::Text("%s", name);

    ImGui::TableNextColumn();
    ImGui::Text("%d", pool->GetSize());

    ImGui::TableNextColumn();
        
    const float percentage = pool->GetNoOfUsedSpaces() > 0 ? static_cast<float>(pool->GetNoOfUsedSpaces() / static_cast<float>(pool->GetSize())) : 0.0f;
    ImGui::PushStyleColor(ImGuiCol_Text, { 2.0f * percentage, 2.0f * (1.0f - percentage), 0.0f, 1.0f });
    ImGui::Text("%d", pool->GetNoOfUsedSpaces());
    ImGui::PopStyleColor();

    ImGui::TableNextColumn();
    ImGui::Text(pool->m_bIsLocked ? "true" : "false");

    ImGui::PopID();
};

void ProcessImGui() {
    if (ImGui::BeginTable("PoolsDebugModule", 4, ImGuiTableFlags_SizingFixedFit | ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersOuter | ImGuiTableFlags_BordersV | ImGuiTableFlags_ContextMenuInBody)) {
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Size");
        ImGui::TableSetupColumn("Active objects");
        ImGui::TableSetupColumn("Is Locked");
        ImGui::TableHeadersRow();

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

        Draw(CCustomCarEnvMapPipeline::m_gEnvMapPipeMatDataPool, "Env Map Pipe Mat Data");
        Draw(CCustomCarEnvMapPipeline::m_gEnvMapPipeAtmDataPool, "Env Map Pipe Atm Data");
        Draw(CCustomCarEnvMapPipeline::m_gSpecMapPipeMatDataPool, "Spec Map Pipe Mat Data");

        ImGui::EndTable();
    }
}

void ProcessRender() {

}

}
