#include "StdInc.h"

#include "CDebugMenu.h"
#include "TaskComplexFollowPointRoute.h"
#include "TaskComplexExtinguishFires.h"
#include "TaskComplexStealCar.h"
#include "TaskComplexScreamInCarThenLeave.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

#include <Windows.h>
#include <extensions/ScriptCommands.h>
#include "DebugModules/DebugModules.h"

bool CDebugMenu::m_Initialised = false;
bool CDebugMenu::m_ShowMenu = false;
ImGuiIO* io;

void CDebugMenu::ImGuiInitialise() {
    if (m_Initialised) {
        return;
    }

    IMGUI_CHECKVERSION();
    ImGuiContext* ctx = ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->WantCaptureMouse = true;
    io->WantCaptureKeyboard = true;
    io->WantSetMousePos = true;
    io->MouseDrawCursor = false;
    io->ConfigFlags = ImGuiConfigFlags_NavEnableSetMousePos;
    io->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);

    ImGui_ImplWin32_Init(PSGLOBAL(window));
    ImGui_ImplDX9_Init(GetD3DDevice());

    DebugModules::Initialise(ctx);

    m_Initialised = true;
    printf("ImGui initialized\n");
}

void CDebugMenu::Shutdown() {
    printf("CDebugMenu::Shutdown\n");

    ImGui_ImplDX9_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UpdateKeyboard() {
    static BYTE KeyStates[256];

    //VERIFY(SUCCEEDED());
    GetKeyboardState(KeyStates);

    for (auto i = 0; i < 256; i++) {
        if (KeyStates[i] & 0x80 && !io->KeysDown[i]) {
            io->KeysDown[i] = true;

            char res[2] = {0};
            if (ToAscii(i, MapVirtualKey(i, 0), (const BYTE*)KeyStates, (LPWORD)res, 0) == 1) {
                io->AddInputCharactersUTF8(res);
            }
        } else if (!(KeyStates[i] & 0x80) && io->KeysDown[i]) {
            io->KeysDown[i] = false;
        }
    }
    io->KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
    io->KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
    io->KeyAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
    io->KeySuper = false;
};

void UpdateMouse() {
    static ImVec2 m_MousePos;

    const auto WHEEL_SPEED = 20.0f;

    CPad::GetPad()->DisablePlayerControls = true;

    m_MousePos.x += CPad::NewMouseControllerState.X;
    m_MousePos.y -= CPad::NewMouseControllerState.Y;

    m_MousePos.x = std::clamp(m_MousePos.x, 0.0f, SCREEN_WIDTH);
    m_MousePos.y = std::clamp(m_MousePos.y, 0.0f, SCREEN_HEIGHT);

    io->MousePos = ImVec2(m_MousePos.x, m_MousePos.y);

    if (CPad::NewMouseControllerState.wheelDown)
        io->MouseWheel -= (WHEEL_SPEED * io->DeltaTime);

    if (CPad::NewMouseControllerState.wheelUp)
        io->MouseWheel += (WHEEL_SPEED * io->DeltaTime);

    io->MouseDown[ImGuiMouseButton_Left]   = CPad::NewMouseControllerState.lmb;
    io->MouseDown[ImGuiMouseButton_Right]  = CPad::NewMouseControllerState.mmb;
    io->MouseDown[ImGuiMouseButton_Middle] = CPad::NewMouseControllerState.rmb;

    CPad::NewMouseControllerState.X = 0.0f;
    CPad::NewMouseControllerState.Y = 0.0f;
};

// Partially taken from https://github.com/GTAModding/re3/blob/f1a7aeaa0f574813ed3cec8a085e2f310aa3a366/src/imgui/ImGuiIII.cpp
void CDebugMenu::ImGuiInputUpdate() {
    if (!m_ShowMenu)
        return;

    UpdateKeyboard();
    UpdateMouse();
}

static void DebugCode() {
    CPad* pad = CPad::GetPad();

    const auto player = FindPlayerPed();

    if (CDebugMenu::Visible() || CPad::NewKeyState.lctrl || CPad::NewKeyState.rctrl)
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
        //for (auto& ped : GetPedPool()->GetAllValid()) {
        //    if (&ped != player) {
        //        ped.GiveWeapon(WEAPON_EXTINGUISHER, 10000, false);
        //        ped.SetCurrentWeapon(WEAPON_EXTINGUISHER);
        //        ped.GetTaskManager().SetTask(new CTaskComplexExtinguishFires{}, TASK_PRIMARY_PRIMARY);
        //    }
        //}

        //const auto veh = player->GetIntelligence()->GetVehicleScanner().GetClosestVehicleInRange();
        const auto veh = player->m_pVehicle;
        player->GetTaskManager().SetTask(new CTaskComplexLeaveCarAsPassengerWait{veh}, TASK_PRIMARY_PRIMARY);
    }

    if (pad->IsStandardKeyJustPressed('9')) {
        player->GetTaskManager().SetTask(new CTaskComplexScreamInCarThenLeave{ player->m_pVehicle, TARGET_DOOR_DRIVER }, TASK_PRIMARY_PRIMARY);
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
        CTimer::Resume();
    }
    if (pad->IsStandardKeyJustPressed('6')) {
        AudioEngine.m_FrontendAE.AddAudioEvent(AE_FRONTEND_BULLET_PASS_RIGHT_FRONT);
    }
    if (pad->IsStandardKeyJustPressed('7')) {
        AudioEngine.m_FrontendAE.AddAudioEvent(AE_FRONTEND_BULLET_PASS_RIGHT_REAR);
    }
}

void CDebugMenu::ImGuiDrawLoop() {
    CPad* pad = CPad::GetPad();
    if (pad->DebugMenuJustPressed()) {
        m_ShowMenu = !m_ShowMenu;
        io->MouseDrawCursor = m_ShowMenu;
        pad->bPlayerSafe = m_ShowMenu;
    }

    DebugCode();
    ReversibleHooks::CheckAll(); // Hot Code Reloading

    io->DeltaTime = CTimer::GetTimeStepInSeconds();
    io->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT); // Update display size, in case of window resize after imgui was already initialized

    ImGui_ImplDX9_NewFrame();
    ImGui::NewFrame();

    DebugModules::ProcessRender(m_ShowMenu);

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    ImGui_ImplDX9_InvalidateDeviceObjects();
}
