#include "StdInc.h"

#include "DebugModules.h"
#include "imgui.h"

#include "Collision/CollisionDebugModule.h"
#include "Cheat/CheatDebugModule.h"
#include "Vehicle/VehicleDebugModule.h"
#include "Ped/PedSpawnerModule.h"
#include "Ped/PedDebugModule.h"
#include "Script/MissionDebugModule.h"
#include "Audio/CutsceneTrackManagerDebugModule.h"
#include "Audio/AmbienceTrackManagerDebugModule.h"
#include "Audio/PoliceScannerAudioEntityDebugModule.h"
#include "CStreamingDebugModule.h"
#include "CPickupsDebugModule.h"
#include "CDarkelDebugModule.h"
#include "CVehicleRecordingDebugModule.h"
#include "HooksDebugModule.h"
#include "CTeleportDebugModule.h"
#include "FXDebugModule.h"
#include "Pools/PoolsDebugModule.h"
#include "TimecycEditor.h"
#include "CullZonesDebugModule.h"
#include "Text/TextDebugModule.h"

bool DebugModules::m_ShowFPS = false;
bool DebugModules::m_ShowExtraDebugFeatures = false;
static PedDebugModule::Module s_PedDebugModule{};

void DebugModules::Initialise(ImGuiContext* ctx) {
    TeleportDebugModule::Initialise(*ctx);
    VehicleDebugModule::Initialise();
    PedSpawnerModule::Initialise();
    MissionDebugModule::Initialise();
    FXDebugModule::Initialise();
}

void SpawnTab() {
    if (ImGui::BeginTabBar("")) {
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

static bool m_showMenu;
void DebugModules::DisplayMainWindow() {
    if (CTimer::GetIsPaused()) {
        return;
    }

    ImGui::SetNextWindowSize(ImVec2(484, 420), ImGuiCond_FirstUseEver);
    ImGui::Begin("Debug Window", &m_showMenu);
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }

    if (ImGui::BeginTabBar("Debug Tabs")) {
        if (ImGui::BeginTabItem("Spawn")) {
            SpawnTab();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Teleport")) {
            TeleportDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Cheats")) {
            CheatDebugModule::ProcessImgui();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Missions")) {
            MissionDebugModule::ProcessImgui();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Rendering")) {
            ProcessRenderTool();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Hooks")) {
            HooksDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }
        if (ImGui::BeginTabItem("Other")) {
            ImGui::Checkbox("Debug Scripts", &CTheScripts::DbgFlag);
            if (ImGui::Button("[CTheScripts] Print List Sizes")) { CTheScripts::PrintListSizes(); }
            ImGui::Checkbox("Display FPS window", &m_ShowFPS);
            ImGui::SliderInt("Max FPS", &RsGlobal.frameLimit, 0, 360);
            ImGui::Checkbox("Display Debug modules window", &m_ShowExtraDebugFeatures);
            if (ImGui::Button("Streamer: ReInit")) {
                CStreaming::ReInit();
            }
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
    ImGui::End();
}

void DebugModules::DisplayFramePerSecond() {
    if (!m_ShowFPS)
        return;

    // Top-left framerate display overlay window.
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::SetNextWindowSize({ 265, 20 });
    ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("FPS: %.2f [RsGlobal.frameLimit=%i]", ImGui::GetIO().Framerate, RsGlobal.frameLimit);
    ImGui::End();
}

void DebugModules::DisplayExtraDebugFeatures() {
    if (!m_ShowExtraDebugFeatures)
        return;

    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(484, 420), ImGuiCond_FirstUseEver);
    ImGui::Begin("Extra debug", nullptr);
    ProcessExtraDebugFeatures();
    ImGui::End();
}

void DebugModules::ProcessRenderTool() {
    if (ImGui::CollapsingHeader("Post Processing")) {
        FXDebugModule::ProcessImgui();
    }
    if (ImGui::CollapsingHeader("Collision")) {
        CollisionDebugModule::ProcessImgui();
    }
}

void DebugModules::ProcessExtraDebugFeatures() {
    if (ImGui::BeginTabBar("Modules")) {
        if (ImGui::BeginTabItem("OCCL/CULL")) {
            if (ImGui::CollapsingHeader("Occlusion")) {
                COcclusionDebugModule::ProcessImGui();
            }
            if (ImGui::CollapsingHeader("Cull Zones")) {
                CullZonesDebugModule::ProcessImGui();
            }
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Audio")) {
            if (ImGui::CollapsingHeader("Cutscene Track Manager")) {
                CutsceneTrackManagerDebugModule::ProcessImGui();
            }

            if (ImGui::CollapsingHeader("Ambience Track Manager")) {
                AmbienceTrackManagerDebugModule::ProcessImGui();
            }

            if (ImGui::CollapsingHeader("Police Scanner Audio Entity")) {
                PoliceScannerAudioEntityDebugModule::ProcessImGui();
            }

            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Streaming")) {
            CStreamingDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Pickups")) {
            CPickupsDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Pools")) {
            PoolsDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Timecyc")) {
            TimeCycleDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Peds")) {
            s_PedDebugModule.ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Text")) {
            TextDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Rampage")) {
            CDarkelDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Vehicle Recordings")) {
            CVehicleRecordingDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        ImGui::EndTabBar();
    }
}

void DebugModules::ProcessRender(bool showMenu) {
    if (showMenu) {
        DisplayMainWindow();
    }
    DisplayFramePerSecond();
    DisplayExtraDebugFeatures();
    TeleportDebugModule::ProcessInput();
    s_PedDebugModule.ProcessRender();
}
