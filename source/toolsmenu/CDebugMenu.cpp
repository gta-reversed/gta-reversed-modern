#include "StdInc.h"

#include "CDebugMenu.h"
#include "Utility.h"

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_dx9.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>

#include <Windows.h>
#include <sstream>

#include "toolsmenu\DebugModules\Collision\CollisionDebugModule.h"
#include "toolsmenu\DebugModules\Cheat\CheatDebugModule.h"
#include "toolsmenu\DebugModules\Vehicle\VehicleDebugModule.h"
#include "toolsmenu\DebugModules\Ped\PedDebugModule.h"
#include "toolsmenu\DebugModules\Script\MissionDebugModule.h"
#include "toolsmenu\DebugModules\Audio\CutsceneTrackManagerDebugModule.h"
#include "toolsmenu\DebugModules\Audio\AmbienceTrackManagerDebugModule.h"
#include "toolsmenu\DebugModules\CStreamingDebugModule.h"
#include "toolsmenu\DebugModules\CPickupsDebugModule.h"
#include "toolsmenu\DebugModules\HooksDebugModule.h"
#include "toolsmenu\DebugModules\CTeleportDebugModule.h"
#include "toolsmenu\DebugModules\FXDebugModule.h"

bool CDebugMenu::m_imguiInitialised = false;
bool CDebugMenu::m_showMenu = false;
bool CDebugMenu::m_showFPS = false;
bool CDebugMenu::m_showExtraDebugFeatures = false;
CSprite2d CDebugMenu::m_mouseSprite;
ImGuiIO* CDebugMenu::io = {};

static ImVec2 m_MousePos;

void CDebugMenu::ImguiInitialise() {
    if (m_imguiInitialised) {
        return;
    }

    IMGUI_CHECKVERSION();

    auto& ctx = *ImGui::CreateContext();

    io = &ImGui::GetIO();
    io->WantCaptureMouse = true;
    io->WantCaptureKeyboard = true;
    io->WantSetMousePos = true;
    io->ConfigFlags = ImGuiConfigFlags_NavEnableSetMousePos;
    io->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);

    ImGui_ImplWin32_Init(*(HWND*)0xC97C1C);
    ImGui_ImplDX9_Init(GetD3DDevice());

    printf("Imgui initialized\n");

    LoadMouseSprite();

    TeleportDebugModule::Initialise(ctx);
    VehicleDebugModule::Initialise();
    PedDebugModule::Initialise();
    MissionDebugModule::Initialise();
    FXDebugModule::Initialise();
    m_imguiInitialised = true;
}

void CDebugMenu::LoadMouseSprite() {
    auto txd = CTxdStore::AddTxdSlot("imgui_mouse");
    if (CTxdStore::LoadTxd(txd, "models\\fronten_pc.txd")) {
        CTxdStore::AddRef(txd);
        CTxdStore::PushCurrentTxd();
        CTxdStore::SetCurrentTxd(txd);
        m_mouseSprite.SetTexture((char*)"mouse", (char*)"mousea");
    } else {
        printf("Failed to load fronten_pc.txd\n");
    }
    CTxdStore::PopCurrentTxd();
}

void CDebugMenu::Shutdown() {
    printf("CDebugMenu::Shutdown\n");
    m_showMenu = false;
    if (m_imguiInitialised)
        ImGui::DestroyContext();

    m_mouseSprite.Delete();
    int32 slot = CTxdStore::FindTxdSlot("imgui_mouse");
    if (slot != -1)
        CTxdStore::RemoveTxdSlot(slot);
}

void CDebugMenu::ImguiInputUpdate() {
    if (!m_showMenu)
        return;

    // Update display size, in case of window resize after imgui was already initialized
    io->DisplaySize = ImVec2(SCREEN_WIDTH, SCREEN_HEIGHT);

    // Partially taken from https://github.com/GTAModding/re3/blob/f1a7aeaa0f574813ed3cec8a085e2f310aa3a366/src/imgui/ImGuiIII.cpp

    const auto UpdateKeyboard = []() {
        static BYTE KeyStates[256];

        GetKeyboardState(KeyStates);

        for (int i = 0; i < 256; i++) {
            if (KeyStates[i] & 0x80 && !io->KeysDown[i]) {
                io->KeysDown[i] = true;

                char res[2] = {0};
                if (ToAscii(i, MapVirtualKey(i, 0), (const BYTE*)KeyStates, (LPWORD)res, 0) == 1) {
                    io->AddInputCharactersUTF8(res);
                }
            } else if (!(KeyStates[i] & 0x80) && io->KeysDown[i])
                io->KeysDown[i] = false;
        }
        io->KeyCtrl = (GetKeyState(VK_CONTROL) & 0x8000) != 0;
        io->KeyShift = (GetKeyState(VK_SHIFT) & 0x8000) != 0;
        io->KeyAlt = (GetKeyState(VK_MENU) & 0x8000) != 0;
        io->KeySuper = false;
    };

    const auto UpdateMouse = []() {
        CPad* pad = CPad::GetPad(0);
        pad->DisablePlayerControls = true;

        m_MousePos.x += CPad::NewMouseControllerState.X;
        m_MousePos.y -= CPad::NewMouseControllerState.Y;

        m_MousePos.x = clamp(m_MousePos.x, 0.0f, SCREEN_WIDTH);
        m_MousePos.y = clamp(m_MousePos.y, 0.0f, SCREEN_HEIGHT);

        io->MousePos = ImVec2(m_MousePos.x, m_MousePos.y);

        if (CPad::NewMouseControllerState.wheelDown)
            io->MouseWheel -= (20.0F * io->DeltaTime);

        if (CPad::NewMouseControllerState.wheelUp)
            io->MouseWheel += (20.0F * io->DeltaTime);

        io->MouseDown[0] = CPad::NewMouseControllerState.lmb;
        io->MouseDown[1] = CPad::NewMouseControllerState.mmb;
        io->MouseDown[2] = CPad::NewMouseControllerState.rmb;

        CPad::NewMouseControllerState.X = 0.0f;
        CPad::NewMouseControllerState.Y = 0.0f;
    };

    UpdateKeyboard();
    UpdateMouse();
}

void CDebugMenu::ImguiDisplayFramePerSecond() {
    if (!m_showFPS)
        return;

    // Top-left framerate display overlay window.
    ImGui::SetNextWindowPos(ImVec2(10, 10));
    ImGui::Begin("FPS", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize);
    ImGui::Text("FPS: %.2f", ImGui::GetIO().Framerate);
    ImGui::End();
}

void CDebugMenu::ImguiDisplayExtraDebugFeatures() {
    if (!m_showExtraDebugFeatures)
        return;

#ifdef EXTRA_DEBUG_FEATURES
    ImGui::SetNextWindowCollapsed(true, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(484, 420), ImGuiCond_FirstUseEver);
    ImGui::Begin("Extra debug", nullptr);
    ProcessExtraDebugFeatures();
    ImGui::End();
#endif
}

void CDebugMenu::ImGuiDrawMouse() {
    if (!m_showMenu || !m_mouseSprite.m_pTexture)
        return;

    CRect mouseRect = CRect(io->MousePos.x, io->MousePos.y, (float)CMenuManager::StretchX(18.0f) + io->MousePos.x, (float)CMenuManager::StretchX(18.0f) + io->MousePos.y);
    m_mouseSprite.Draw(mouseRect, CRGBA(255, 255, 255, 255));
}

bool showPlayerInfo;
void CDebugMenu::ShowPlayerInfo() {
    if (!showPlayerInfo)
        return;

    CPlayerPed* player = FindPlayerPed();
    if (!player)
        return;

    ImGui::Begin("Player Information");

    auto playerPos = player->GetPosition();
    float pos[3] = { playerPos.x, playerPos.y, playerPos.z};
    ImGui::InputFloat3("position", pos, "%.4f", ImGuiInputTextFlags_ReadOnly);

    ImGui::End();
}

void CDebugMenu::ProcessRenderTool() {
    if (ImGui::CollapsingHeader("Post Processing")) {
        FXDebugModule::ProcessImgui();
    }
    if (ImGui::CollapsingHeader("Collision")) {
        CollisionDebugModule::ProcessImgui();
    }
}

#ifdef EXTRA_DEBUG_FEATURES
void CDebugMenu::ProcessExtraDebugFeatures() {
    if (ImGui::BeginTabBar("Modules")) {
        if (ImGui::BeginTabItem("Occlussion")) {
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

        ImGui::EndTabBar();
    }
}
#endif

void CDebugMenu::ImguiDisplayPlayerInfo() {
    if (CTimer::GetIsPaused()) {
        return;
    }

    if (m_showMenu && FindPlayerPed()) {
        TeleportDebugModule::ProcessImGui();

        ImGui::SetNextWindowSize(ImVec2(484, 420), ImGuiCond_FirstUseEver);
        ImGui::Begin("Debug Window", &m_showMenu, ImGuiWindowFlags_NoResize);
        if (ImGui::BeginMenuBar()) {
            if (ImGui::BeginMenu("File")) {
                ImGui::EndMenu();
            }
            ImGui::EndMenuBar();
        }

        if (ImGui::BeginTabBar("Debug Tabs")) {
            if (ImGui::BeginTabItem("Peds")) {
                //ImGui::Checkbox("Show Player Information", &showPlayerInfo);
                PedDebugModule::ProcessImgui();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Vehicles")) {
                VehicleDebugModule::ProcessImgui();
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
                ImGui::Checkbox("Display FPS window", &CDebugMenu::m_showFPS);
#ifdef EXTRA_DEBUG_FEATURES
                ImGui::Checkbox("Display Debug modules window", &CDebugMenu::m_showExtraDebugFeatures);
#endif
                if (ImGui::Button("Streamer: ReInit")) {
                    CStreaming::ReInit();
                }
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }
    ShowPlayerInfo();
}

static void DebugCode() {
    if (CDebugMenu::Visible() || CPad::NewKeyState.lctrl || CPad::NewKeyState.rctrl)
        return;

    CPad* pad = CPad::GetPad(0);
    if (pad->IsStandardKeyJustDown('1')) {
        printf("");
        CCheat::JetpackCheat();
    }
    if (pad->IsStandardKeyJustDown('2')) {
        printf("");
        CCheat::MoneyArmourHealthCheat();
    }
}

void CDebugMenu::ImguiDrawLoop() {
    CPad* pad = CPad::GetPad(0);
    auto bF7JustPressed = (CPad::NewKeyState.FKeys[6] && !CPad::OldKeyState.FKeys[6]);
    if ((pad->IsCtrlPressed() && pad->IsStandardKeyJustDown('M')) || bF7JustPressed) {
        m_showMenu = !m_showMenu;
        pad->bPlayerSafe = m_showMenu;
    }

    DebugCode();
    ReversibleHooks::CheckAll();

    io->DeltaTime = CTimer::GetTimeStep() * 0.02f;

    ImGui_ImplDX9_NewFrame();
    ImGui::NewFrame();

    CDebugMenu::ImguiDisplayExtraDebugFeatures();
    ImguiDisplayPlayerInfo();
    ImguiDisplayFramePerSecond();
    HooksDebugModule::ProcessRender();
    FXDebugModule::ProcessRender();
    TeleportDebugModule::ProcessInput();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
}
