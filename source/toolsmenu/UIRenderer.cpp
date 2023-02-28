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

    m_ImIO->WantCaptureMouse    = true;
    m_ImIO->WantCaptureKeyboard = true;
    m_ImIO->WantSetMousePos     = true;
    m_ImIO->MouseDrawCursor     = false;
    m_ImIO->ConfigFlags         = ImGuiConfigFlags_NavEnableSetMousePos | ImGuiConfigFlags_NavEnableKeyboard | ImGuiConfigFlags_NavEnableGamepad;
    m_ImIO->DisplaySize         = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);

    ImGui_ImplWin32_Init(PSGLOBAL(window));
    ImGui_ImplDX9_Init(GetD3DDevice());

    DEV_LOG("I say hello!");
}

UIRenderer::~UIRenderer() {
    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext(m_ImCtx);

    DEV_LOG("Good bye!");
}

void UIRenderer::UpdateInputMouse() {
    const auto WHEEL_SPEED = 20.0f;

    CPad::GetPad()->DisablePlayerControls = true;

    // Update position
    auto& MousePos = m_ImIO->MousePos;
    MousePos.x += CPad::NewMouseControllerState.X;
    MousePos.y -= CPad::NewMouseControllerState.Y;

    MousePos.x = std::clamp(MousePos.x, 0.0f, SCREEN_WIDTH);
    MousePos.y = std::clamp(MousePos.y, 0.0f, SCREEN_HEIGHT);

    if (CPad::NewMouseControllerState.wheelDown)
        m_ImIO->MouseWheel -= (WHEEL_SPEED * m_ImIO->DeltaTime);

    if (CPad::NewMouseControllerState.wheelUp)
        m_ImIO->MouseWheel += (WHEEL_SPEED * m_ImIO->DeltaTime);

    m_ImIO->MouseDown[ImGuiMouseButton_Left]   = CPad::NewMouseControllerState.lmb;
    m_ImIO->MouseDown[ImGuiMouseButton_Right]  = CPad::NewMouseControllerState.rmb;
    m_ImIO->MouseDown[ImGuiMouseButton_Middle] = CPad::NewMouseControllerState.mmb;

    CPad::NewMouseControllerState.X = 0.0f;
    CPad::NewMouseControllerState.Y = 0.0f;
}

void UIRenderer::UpdateInputKeyboard() {
    
    /*
    BYTE KeyStates[256];

    VERIFY(GetKeyboardState(KeyStates));

    const auto IsKeyDown = [&](auto key) { return (KeyStates[key] & 0x80) != 0; };

    for (auto key = 0; key < 256; key++) {
        // Check if there was a state change
        if (IsKeyDown(key) == m_ImIO->KeysDown[key]) {
            continue;
        }

        // There was!
        if (IsKeyDown(key)) { // Key is now down
            m_ImIO->KeysDown[key] = true;

            char ResultUTF8[16] = {0};
            if (ToAscii(key, MapVirtualKey(key, 0), KeyStates, (LPWORD)ResultUTF8, 0)) {
                m_ImIO->AddInputCharactersUTF8(ResultUTF8);
            }
        } else { // Key is now released
            m_ImIO->KeysDown[key] = false;
        }
    }

    m_ImIO->KeyCtrl  = IsKeyDown(VK_CONTROL);
    m_ImIO->KeyShift = IsKeyDown(VK_SHIFT);
    m_ImIO->KeyAlt   = IsKeyDown(VK_MENU);
    m_ImIO->KeySuper = false;
    */
}

void UIRenderer::UpdateInput() {
    if (!Visible()) {
        return;
    }
    //UpdateInputMouse();
    //UpdateInputKeyboard();
}

void UIRenderer::PreRenderUpdate() {
    m_ImIO->DeltaTime   = CTimer::GetTimeStepInSeconds();
    m_ImIO->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT); // Update display size, in case of window resize after imgui was already initialized

    m_DebugModules.PreRenderUpdate();
    DebugCode();
    ReversibleHooks::CheckAll();

    if (const auto pad = CPad::GetPad(); pad->DebugMenuJustPressed()) {
        m_ShowMenu              = !m_ShowMenu;
        m_ImIO->MouseDrawCursor = m_ShowMenu;
        pad->bPlayerSafe        = m_ShowMenu;
    }
}

void UIRenderer::DrawLoop() {
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
    ImGui_ImplDX9_InvalidateDeviceObjects();
}

void UIRenderer::Render2D() {
    m_DebugModules.Render2D();
}

void UIRenderer::Render3D() {
    m_DebugModules.Render3D();
}

void UIRenderer::DebugCode() {
    CPad* pad = CPad::GetPad();

    const auto player = FindPlayerPed();

    if (UIRenderer::Visible() || CPad::NewKeyState.lctrl || CPad::NewKeyState.rctrl)
        return;

    if (pad->IsStandardKeyJustPressed('8')) {

        CPointRoute route{};

        const auto r = 10.f;
        const auto totalAngle = PI * 2.f;
        for (auto a = 0.f; a < totalAngle; a += totalAngle / 8.f) {
            route.AddPoints(player->GetPosition() + CVector{std::cosf(a), std::sinf(a), 0.f} *r);
        }

        player->GetTaskManager().SetTask(
            new CTaskComplexFollowPointRoute{
                PEDMOVE_SPRINT,
                route,
                CTaskComplexFollowPointRoute::Mode::ONE_WAY,
                3.f,
                3.f,
                false,
                true,
                true
            },
            TASK_PRIMARY_PRIMARY
        );
    }

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
    if (pad->IsStandardKeyJustPressed('4')) {
        CTimer::Suspend();
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
        AudioEngine.m_FrontendAE.AddAudioEvent(AE_FRONTEND_BULLET_PASS_RIGHT_FRONT);
    }
    if (pad->IsStandardKeyJustPressed('7')) {
        AudioEngine.m_FrontendAE.AddAudioEvent(AE_FRONTEND_BULLET_PASS_RIGHT_REAR);
    }
}
}; // namespace ui
}; // namespace notsa
