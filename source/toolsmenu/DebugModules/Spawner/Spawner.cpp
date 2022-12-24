#include <StdInc.h>

#include <imgui.h>

#include "Spawner.hpp"
#include "PedSpawner.h"
#include "VehicleSpawner.h"

using namespace ImGui;

SpawnerDebugModule::SpawnerDebugModule() :
    DebugModuleSingleWindow{"Spawner", {485.f, 400.f}}
{
    VehicleDebugModule::Initialise();
    PedSpawnerModule::Initialise();
}

void SpawnerDebugModule::RenderMenuEntry() {
    if (BeginMenu("Tools")) {
        if (MenuItem("Spawner")) {
            SetMainWindowOpen(true);
        }
        ImGui::EndMenu();
    }
}

void SpawnerDebugModule::RenderMainWindow() {
    if (ImGui::BeginTabBar("spawner")) {
        if (ImGui::BeginTabItem("Ped")) {
            PedSpawnerModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicle")) {
            VehicleDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar();
}
