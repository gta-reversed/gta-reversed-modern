#include <StdInc.h>

#include <imgui.h>

#include "Spawner.hpp"
#include "PedSpawner.h"
#include "VehicleSpawner.h"

using namespace ImGui;

SpawnerDebugModule::SpawnerDebugModule() {
    VehicleDebugModule::Initialise();
    PedSpawnerModule::Initialise();
}

void SpawnerDebugModule::RenderWindow() {
    if (m_wndIsOpen) {
        SetNextWindowSize({ 500.f, 400.f }, ImGuiCond_FirstUseEver);
        if (Begin("Spawner", &m_wndIsOpen)) {
            RenderSpawnerWindow();
        }
        End();
    }
}

void SpawnerDebugModule::RenderMenuEntry() {
    if (BeginMenu("Tools")) {
        if (MenuItem("Spawner")) {
            m_wndIsOpen = true;
        }
        ImGui::EndMenu();
    }
}

void SpawnerDebugModule::RenderSpawnerWindow() {
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
