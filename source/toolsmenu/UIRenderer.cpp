#include "StdInc.h"

#include "UIRenderer.h"
#include "TaskComplexFollowPointRoute.h"
#include "TaskComplexExtinguishFires.h"
#include "TaskComplexStealCar.h"
#include "TaskComplexFleeAnyMeans.h"
#include "TaskComplexDriveWander.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

#include <Windows.h>
#include <extensions/ScriptCommands.h>
#include "DebugModules/DebugModules.h"

namespace notsa {
namespace ui {
UIRenderer::UIRenderer() :
    m_ImCtx{ ImGui::CreateContext() },
    m_ImIO{ &m_ImCtx->IO }
{
    IMGUI_CHECKVERSION();

    m_ImIO->ConfigFlags = ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad | ImGuiConfigFlags_DockingEnable | ImGuiConfigFlags_ViewportsEnable;
    m_ImIO->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);
    m_ImIO->NavActive   = false;

    ImGui_ImplWin32_Init(PSGLOBAL(window));
    ImGui_ImplDX9_Init(GetD3DDevice());

    DEV_LOG("I say hello!");
}

UIRenderer::~UIRenderer() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext(m_ImCtx);

    //DEV_LOG("Good bye!");
}

void UIRenderer::PreRenderUpdate() {
    ZoneScoped;

    m_ImIO->DeltaTime   = CTimer::GetTimeStepInSeconds();
    m_ImIO->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT); // Update display size, in case of window resize after imgui was already initialized

    m_DebugModules.PreRenderUpdate();
    DebugCode();
    ReversibleHooks::CheckAll();

    // A delay of a frame has to be added, otherwise the release of F7 wont be processed
    // and the menu will close
    const auto Shortcut = [](ImGuiKeyChord chord) {
        return ImGui::Shortcut(chord, ImGuiKeyOwner_Any, ImGuiInputFlags_RouteAlways);
    };
    if (Shortcut(ImGuiKey_F7) || Shortcut(ImGuiKey_M | ImGuiMod_Ctrl)) {
        m_InputActive                         = !m_InputActive;
        m_ImIO->MouseDrawCursor               = m_InputActive;
        m_ImIO->NavActive                     = m_InputActive;
        CPad::GetPad()->DisablePlayerControls = m_InputActive;
        CPad::GetPad()->Clear(m_InputActive, true);
    }
}

void UIRenderer::PostRenderUpdate() {
    m_ImIO->NavActive = m_InputActive; // ImGUI clears `NavActive` every frame, so have to set it here.
}

void UIRenderer::DrawLoop() {
    ZoneScoped;

    if (m_ReInitRequested) {
        ResetSingleton(); // This will destruct the current object so we gotta stop here.
        return;
    }

    PreRenderUpdate();
    ImGui_ImplWin32_NewFrame();
    ImGui_ImplDX9_NewFrame();
    ImGui::NewFrame();

    Render2D();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    //ImGui_ImplDX9_InvalidateDeviceObjects();

    PostRenderUpdate();

    // Update and Render additional Platform Windows
    if (m_ImIO->ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
    }
}

void UIRenderer::Render2D() {
    ZoneScoped;

    m_DebugModules.Render2D();
}

void UIRenderer::Render3D() {
    ZoneScoped;

    m_DebugModules.Render3D();
}

void UIRenderer::DebugCode() {
    CPad* pad = CPad::GetPad();

    const auto player = FindPlayerPed();

    if (UIRenderer::Visible() || CPad::NewKeyState.lctrl || CPad::NewKeyState.rctrl)
        return;

    //if (pad->IsStandardKeyJustPressed('8')) {
    //
    //    CPointRoute route{};
    //
    //    const auto r = 10.f;
    //    const auto totalAngle = PI * 2.f;
    //    for (auto a = 0.f; a < totalAngle; a += totalAngle / 8.f) {
    //        route.AddPoints(player->GetPosition() + CVector{std::cosf(a), std::sinf(a), 0.f} *r);
    //    }
    //
    //    player->GetTaskManager().SetTask(
    //        new CTaskComplexFollowPointRoute{
    //            PEDMOVE_SPRINT,
    //            route,
    //            CTaskComplexFollowPointRoute::Mode::ONE_WAY,
    //            3.f,
    //            3.f,
    //            false,
    //            true,
    //            true
    //        },
    //        TASK_PRIMARY_PRIMARY
    //    );
    //}

    if (pad->IsStandardKeyJustPressed('0')) {
        if (const auto veh = FindPlayerVehicle()) {
            veh->Fix();
            veh->AsAutomobile()->SetRandomDamage(false);
        }
    }

    if (pad->IsStandardKeyJustPressed('9')) {
        if (const auto veh = FindPlayerVehicle()) {
            veh->Fix();
            veh->AsAutomobile()->SetRandomDamage(true);
        }
    }

    if (pad->IsStandardKeyJustPressed('1')) {
        CCheat::JetpackCheat();
    }
    if (pad->IsStandardKeyJustPressed('2')) {
        CCheat::MoneyArmourHealthCheat();
    }
    if (pad->IsStandardKeyJustPressed('3')) {
        CCheat::VehicleCheat(MODEL_INFERNUS);
    }
    if (pad->IsStandardKeyJustDown('8')) {
        TheCamera.AddShakeSimple(10000.f, 1, 10.f);
        DEV_LOG("Hey");
    }
    if (pad->IsStandardKeyJustPressed('5')) {
        if (const auto veh = FindPlayerVehicle()) {
            player->GetTaskManager().SetTask(
                new CTaskComplexCarDriveWander{veh, eCarDrivingStyle::DRIVING_STYLE_PLOUGH_THROUGH, 100.f},
                TASK_PRIMARY_PRIMARY
            );
        }
    }
    if (pad->IsStandardKeyJustPressed('6')) {
        CMessages::AddBigMessage("PRESS ~k~~PED_ANSWER_PHONE~ TO FUCK", 1000, eMessageStyle::STYLE_BOTTOM_RIGHT);
    }
    if (pad->IsStandardKeyJustPressed('7')) {
        CMessages::AddMessageWithNumberQ("PRESS ~k~~PED_ANSWER_PHONE~TO FUCK ~1~~1~~1~", 1000, 0, 1, 2, 3, 4, 5, 6);
    }

    if (pad->IsStandardKeyJustPressed('8')) {
        CMessages::AddToPreviousBriefArray("PRESS ~k~~PED_ANSWER_PHONE~ TO FUCK");
    }
}
}; // namespace ui
}; // namespace notsa
