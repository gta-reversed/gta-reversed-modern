#include "StdInc.h"

#include "DebugModules.h"
#include "imgui.h"

#include "./CollisionDebugModule.h"
#include "./CheatDebugModule.h"
#include "./PedDebugModule.h"
#include "./Script/MissionDebugModule.h"
#include "./Audio/CutsceneTrackManagerDebugModule.h"
#include "./Audio/AmbienceTrackManagerDebugModule.h"
#include "./Audio/PoliceScannerAudioEntityDebugModule.h"
#include "./CStreamingDebugModule.h"
#include "./CPickupsDebugModule.h"
#include "./CDarkelDebugModule.h"
#include "./HooksDebugModule.h"
#include "./CTeleportDebugModule.h"
#include "./FXDebugModule.h"
#include "./PoolsDebugModule.h"
#include "./TimeCycleDebugModule.h"
#include "./CullZonesDebugModule.h"
#include "./TextDebugModule.h"
#include "./Spawner/SpawnerDebugModule.hpp"
#include "./ImGuiDebugModule.hpp"
#include "./ScriptDebugModule.hpp"
#include "./CloudsDebugModule.hpp"
#include "./AudioZonesDebugModule.h"

DebugModules::DebugModules(ImGuiContext* ctx) :
    m_ImCtx(ctx)
{
    CreateModules();
}

void DebugModules::PreRenderUpdate() {
    for (auto& module : m_Modules) {
        module->Update();
    }
}

void DebugModules::Render2D() {
    ImGui::BeginMainMenuBar();
    for (auto& module : m_Modules) {
        module->RenderMenuEntry();
    }
    RenderMenuBarInfo();
    ImGui::EndMainMenuBar();

    for (auto& module : m_Modules) {
        module->RenderWindow();
    }
}

void DebugModules::Render3D() {
    ZoneScoped;

    for (auto& module : m_Modules) {
        module->Render3D();
    }
}

void DebugModules::CreateModules() {
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
    Add<notsa::debugmodules::ScriptDebugModule>();
    Add<notsa::debugmodules::CloudsDebugModule>();

    // Stuff that is present in multiple menus
    Add<TimeCycleDebugModule>(); // Visualization + Extra
    Add<CullZonesDebugModule>(); // Visualization + Extra
    Add<COcclusionDebugModule>(); // Visualization + Extra
    Add<AudioZonesDebugModule>(); // Visualization + Extra
    Add<notsa::debugmodules::ImGui>(); // Stats + Extra
}

void DebugModules::RenderMenuBarInfo() {
    const auto& io = ImGui::GetIO();

    ImGui::SameLine(ImGui::GetWindowWidth() - 280.f);

    // Draw this first, cause FPS fluctuates (and would move this text)
    ImGui::Text("F7 / Ctrl + M |");

    // TODO: V-Sync (Use IsVSyncActive()) - How to get VSync target FPS?
    //       Can't use `RsGlobal.frameLimit`, because there's an active vsync limit (coming from somewhere lol)
    const auto MaxFrameRate = FrontEndMenuManager.m_bPrefsFrameLimiter ? (float)RsGlobal.frameLimit : 60.f;
    const auto FrameRateProg = std::max(invLerp(MaxFrameRate * 0.30f, MaxFrameRate, io.Framerate), 0.f);
    ImGui::PushStyleColor(ImGuiCol_Text, { std::max(0.f, 1.f - FrameRateProg), std::min(1.f, FrameRateProg), 0.f, 1.f });
    ImGui::Text("%.1f FPS [%.2f ms]", io.Framerate, io.Framerate ? 1000.f / io.Framerate : 0.f); // Calculate frametime from framerate (to make the next less wobbly as the io.DeltaTime varies a lot otherwise)
    ImGui::PopStyleColor();
}
