#include "StdInc.h"

#include "DebugModules.h"
#include "imgui.h"

#include "Collision\CollisionDebugModule.h"
#include "Cheat\CheatDebugModule.h"
#include "Vehicle\VehicleDebugModule.h"
#include "Ped\PedDebugModule.h"
#include "Script\MissionDebugModule.h"
#include "Audio\CutsceneTrackManagerDebugModule.h"
#include "Audio\AmbienceTrackManagerDebugModule.h"
#include "CStreamingDebugModule.h"
#include "CPickupsDebugModule.h"
#include "HooksDebugModule.h"
#include "CTeleportDebugModule.h"
#include "FXDebugModule.h"
#include "Pools\PoolsDebugModule.h"
#include "TimecycEditor.h"

bool DebugModules::m_ShowFPS = false;
bool DebugModules::m_ShowExtraDebugFeatures = false;

void DebugModules::Initialise(ImGuiContext* ctx) {
    TeleportDebugModule::Initialise(*ctx);
    VehicleDebugModule::Initialise();
    PedDebugModule::Initialise();
    MissionDebugModule::Initialise();
    FXDebugModule::Initialise();
}

void SpawnTab() {
    if (ImGui::BeginTabBar("")) {
        if (ImGui::BeginTabItem("Ped")) {
            PedDebugModule::ProcessImGui();
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
    ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
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
        if (ImGui::BeginTabItem("Occlusion")) {
            COcclusionDebugModule::ProcessImGui();
            ImGui::EndTabItem();
        }

        if (ImGui::BeginTabItem("Audio")) {
            ImGui::Text("Cutscene Track Manager");
            CutsceneTrackManagerDebugModule::ProcessImGui();

            ImGui::NewLine();
            ImGui::Text("Ambience Track Manager");
            AmbienceTrackManagerDebugModule::ProcessImGui();
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

        ImGui::EndTabBar();
    }
}

void DebugModules::Display(bool showMenu) {
    if (showMenu) {
        DisplayMainWindow();
    }
    DisplayFramePerSecond();
    DisplayExtraDebugFeatures();
    TeleportDebugModule::ProcessInput();
}
