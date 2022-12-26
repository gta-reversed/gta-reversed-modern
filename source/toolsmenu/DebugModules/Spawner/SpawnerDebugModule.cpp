#include <StdInc.h>

#include <imgui.h>

#include "SpawnerDebugModule.hpp"
#include "PedSpawner.h"
#include "VehicleSpawner.h"

using namespace ImGui;

SpawnerDebugModule::SpawnerDebugModule()  {
    VehicleDebugModule::Initialise();
    PedSpawnerModule::Initialise();
}
void SpawnerDebugModule::RenderWindow() {
    const notsa::ui::ScopedWindow window{ "Spawner", { 485.f, 400.f }, m_IsOpen };
    if (!m_IsOpen) {
        return;
    }

    if (ImGui::BeginTabBar("Spawner")) {
        if (ImGui::BeginTabItem("Ped")) {
            PedSpawnerModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicle")) {
            VehicleDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

void SpawnerDebugModule::RenderMenuEntry() {
    notsa::ui::DoNestedMenuIL({ "Tools" }, [&] {
        ImGui::MenuItem("Spawner", nullptr, &m_IsOpen);
    });
}
