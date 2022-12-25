#include "StdInc.h"

#include "DebugModules.h"
#include "imgui.h"

#include "Collision/CollisionDebugModule.h"
#include "Cheat/CheatDebugModule.h"
#include "Ped/PedDebugModule.h"
#include "Script/MissionDebugModule.h"
#include "Audio/CutsceneTrackManagerDebugModule.h"
#include "Audio/AmbienceTrackManagerDebugModule.h"
#include "Audio/PoliceScannerAudioEntityDebugModule.h"
#include "CStreamingDebugModule.h"
#include "CPickupsDebugModule.h"
#include "CDarkelDebugModule.h"
#include "HooksDebugModule.h"
#include "CTeleportDebugModule.h"
#include "FXDebugModule.h"
#include "Pools/PoolsDebugModule.h"
#include "TimecycEditor.h"
#include "CullZonesDebugModule.h"
#include "Text/TextDebugModule.h"

#include "Spawner/Spawner.hpp"

bool DebugModules::m_ShowFPS = false;
bool DebugModules::m_ShowExtraDebugFeatures = false;

void DebugModules::Update(bool cursorVisible) {
    for (auto& module : m_modules) {
        module->Update();
    }

    ImGui::BeginMainMenuBar();
    for (auto& module : m_modules) {
        module->RenderMenuEntry();
    }
    ImGui::EndMainMenuBar();

    for (auto& module : m_modules) {
        module->RenderWindow();
    }
}

void DebugModules::Render3D() {
    for (auto& module : m_modules) {
        module->Render3D();
    }
}

void DebugModules::Initialise(ImGuiContext* ctx) {
    m_imctx = ctx;

    // "Tools" menu
    Add<TeleportDebugModule>();
    Add<SpawnerDebugModule>();
    Add<MissionDebugModule>();
    Add<CheatDebugModule>();

    // "Settings" menu
    Add<HooksDebugModule>();
    Add<FXDebugModule>();

    // "Visualization" menu
    Add<CollisionDebugModule>();
    Add<PedDebugModule>();

    // "Stats" menu
    Add<PoolsDebugModule>();
    Add<CStreamingDebugModule>();

    // "Extra" menu (Put your extra debug modules here, unless they might be useful in general)
    Add<DarkelDebugModule>();
    Add<CPickupsDebugModule>();
    Add<PoliceScannerAudioEntityDebugModule>();
    Add<AmbienceTrackManagerDebugModule>();
    Add<CutsceneTrackManagerDebugModule>();

    // Stuff that is present in multiple menus
    Add<TimeCycleDebugModule>(); // Visualization + Extra
    Add<CullZonesDebugModule>(); // Visualization + Extra
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
}

void DebugModules::ProcessExtraDebugFeatures() {
    if (ImGui::BeginTabBar("Modules")) {
        if (ImGui::BeginTabItem("OCCL/CULL")) {
            if (ImGui::CollapsingHeader("Occlusion")) {
                COcclusionDebugModule::ProcessImGui();
            }
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
}
