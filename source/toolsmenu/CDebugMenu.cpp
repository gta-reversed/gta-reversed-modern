#include "StdInc.h"

#include "CDebugMenu.h"
#include "imgui.h"
#include "imgui_impl_rw.h"
#include "imgui_stdlib.h"
#include "imgui_internal.h"
#include "CDebugMenuToolInput.h"

#include <windows.h>
#include <sstream>

#include "toolsmenu\DebugModules\Collision\Collision.h"

CDebugMenuToolInput CDebugMenu::m_vehicleToolInput;
CDebugMenuToolInput CDebugMenu::m_pedToolInput;
CDebugMenuToolInput CDebugMenu::m_missionToolInput;
bool CDebugMenu::m_bStartMission = false;
int32 CDebugMenu::m_missionToStartId = 0;
bool CDebugMenu::m_imguiInitialised = false;
bool CDebugMenu::m_showMenu = false;
bool CDebugMenu::m_showFPS = false;
bool CDebugMenu::m_showExtraDebugFeatures = false;
CSprite2d CDebugMenu::m_mouseSprite;
ImGuiIO* CDebugMenu::io = {};

// https://stackoverflow.com/a/19839371
bool findStringCaseInsensitive(const std::string& strHaystack, const std::string& strNeedle) {
    auto it = std::search(
      strHaystack.begin(), strHaystack.end(),
      strNeedle.begin(), strNeedle.end(),
      [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
    );
    return (it != strHaystack.end());
}

void CDebugMenu::ImguiInitialise() {
    if (m_imguiInitialised) {
        return;
    }

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    io = &ImGui::GetIO();
    io->WantCaptureMouse = true;
    io->WantCaptureKeyboard = true;
    io->WantSetMousePos = true;
    io->ConfigFlags = ImGuiConfigFlags_NavEnableSetMousePos;
    io->DisplaySize = ImVec2((float)RsGlobal.maximumWidth, (float)RsGlobal.maximumHeight);
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    // HWND& hwnd = *(HWND*)0xC97C1C;
    // ImGui_ImplWin32_Init(hwnd);
    ImGui_ImplRW_Init(GetD3DDevice());
    printf("Imgui initialized\n");

    // Mouse
    int txd = CTxdStore::AddTxdSlot("imgui_mouse");
    if (CTxdStore::LoadTxd(txd, "models\\fronten_pc.txd")) {
        CTxdStore::AddRef(txd);
        CTxdStore::PushCurrentTxd();
        CTxdStore::SetCurrentTxd(txd);
        m_mouseSprite.SetTexture((char*)"mouse", (char*)"mousea");
    } else {
        printf("Failed to load fronten_pc.txd\n");
    }
    CTxdStore::PopCurrentTxd();

    // Keyboard section
    io->KeyMap[ImGuiKey_Tab] = VK_TAB;
    io->KeyMap[ImGuiKey_LeftArrow] = VK_LEFT;
    io->KeyMap[ImGuiKey_RightArrow] = VK_RIGHT;
    io->KeyMap[ImGuiKey_UpArrow] = VK_UP;
    io->KeyMap[ImGuiKey_DownArrow] = VK_DOWN;
    io->KeyMap[ImGuiKey_PageUp] = VK_PRIOR;
    io->KeyMap[ImGuiKey_PageDown] = VK_NEXT;
    io->KeyMap[ImGuiKey_Home] = VK_HOME;
    io->KeyMap[ImGuiKey_End] = VK_END;
    io->KeyMap[ImGuiKey_Insert] = VK_INSERT;
    io->KeyMap[ImGuiKey_Delete] = VK_DELETE;
    io->KeyMap[ImGuiKey_Backspace] = VK_BACK;
    io->KeyMap[ImGuiKey_Space] = VK_SPACE;
    io->KeyMap[ImGuiKey_Enter] = VK_RETURN;
    io->KeyMap[ImGuiKey_Escape] = VK_ESCAPE;
    io->KeyMap[ImGuiKey_KeyPadEnter] = VK_RETURN;
    io->KeyMap[ImGuiKey_A] = 'A';
    io->KeyMap[ImGuiKey_C] = 'C';
    io->KeyMap[ImGuiKey_V] = 'V';
    io->KeyMap[ImGuiKey_X] = 'X';
    io->KeyMap[ImGuiKey_Y] = 'Y';
    io->KeyMap[ImGuiKey_Z] = 'Z';

    m_vehicleToolInput.Initialise(256, &m_vehiclesMap);
    m_pedToolInput.Initialise(256, &m_pedsMap);
    m_missionToolInput.Initialise(256, &m_missionsMap);
    m_imguiInitialised = true;
}

void CDebugMenu::ImguiInputUpdate() {
    if (!m_showMenu)
        return;

    // Update display size, in case of window resize after imgui was already initialized
    io->DisplaySize = ImVec2((float)RsGlobal.maximumWidth, (float)RsGlobal.maximumHeight);

    // Partially taken from https://github.com/Juarez12/re3/blob/f1a7aeaa0f574813ed3cec8a085e2f310aa3a366/src/imgui/ImGuiIII.cpp

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

    // Mouse

    CPad* pad = CPad::GetPad(0);
    pad->DisablePlayerControls = true;

    m_MousePos.x += CPad::NewMouseControllerState.X;
    m_MousePos.y -= CPad::NewMouseControllerState.Y;

    if (m_MousePos.x < 0.0f)
        m_MousePos.x = 0.0f;
    if (m_MousePos.y < 0.0f)
        m_MousePos.y = 0.0f;
    if (m_MousePos.x >= (float)RsGlobal.maximumWidth)
        m_MousePos.x = (float)RsGlobal.maximumWidth;
    if (m_MousePos.y >= (float)RsGlobal.maximumHeight)
        m_MousePos.y = (float)RsGlobal.maximumHeight;

    if (CPad::NewMouseControllerState.wheelDown)
        io->MouseWheel -= (20.0F * io->DeltaTime);

    if (CPad::NewMouseControllerState.wheelUp)
        io->MouseWheel += (20.0F * io->DeltaTime);

    io->MousePos = ImVec2(m_MousePos.x, m_MousePos.y);
    io->MouseDown[0] = CPad::NewMouseControllerState.lmb;
    io->MouseDown[1] = CPad::NewMouseControllerState.mmb;
    io->MouseDown[2] = CPad::NewMouseControllerState.rmb;

    CPad::NewMouseControllerState.X = 0.0f;
    CPad::NewMouseControllerState.Y = 0.0f;
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

void CDebugMenu::ProcessCheatTool() {
    if (ImGui::CollapsingHeader("Player")) {
        if (ImGui::RadioButton("Adrenaline", false)) {
            CCheat::AdrenalineCheat();
        }
        if (ImGui::RadioButton("Health Money Armour", false)) {
            CCheat::MoneyArmourHealthCheat();
        }
        if (ImGui::RadioButton("Weapon 1", false)) {
            CCheat::WeaponCheat1();
        }
        if (ImGui::RadioButton("Weapon 2", false)) {
            CCheat::WeaponCheat2();
        }
        if (ImGui::RadioButton("Weapon 3", false)) {
            CCheat::WeaponCheat3();
        }
        if (ImGui::RadioButton("Weapon Skills", false)) {
            CCheat::WeaponSkillsCheat();
        }
        if (ImGui::RadioButton("Never wanted", false)) {
            CCheat::NotWantedCheat();
        }
        if (ImGui::RadioButton("Wanted", false)) {
            CCheat::WantedCheat();
        }
        if (ImGui::RadioButton("Wanted Up", false)) {
            CCheat::WantedLevelUpCheat();
        }
        if (ImGui::RadioButton("Wanted Down", false)) {
            CCheat::WantedLevelDownCheat();
        }
        if (ImGui::RadioButton("Health", false)) {
            CCheat::HealthCheat();
        }
        if (ImGui::RadioButton("Muscle", false)) {
            CCheat::MuscleCheat();
        }
        if (ImGui::RadioButton("Skinny", false)) {
            CCheat::SkinnyCheat();
        }
        if (ImGui::RadioButton("Fat", false)) {
            CCheat::FatCheat();
        }
        if (ImGui::RadioButton("Stamina", false)) {
            CCheat::StaminaCheat();
        }
        if (ImGui::RadioButton("Vehicle Skills", false)) {
            CCheat::VehicleSkillsCheat();
        }
    }

    if (ImGui::CollapsingHeader("Vehicle")) {
        if (ImGui::RadioButton("Apache", false)) {
            CCheat::ApacheCheat();
        }
        if (ImGui::RadioButton("Vortex", false)) {
            CCheat::VortexCheat();
        }
        if (ImGui::RadioButton("Dozer", false)) {
            CCheat::DozerCheat();
        }
        if (ImGui::RadioButton("Flyboy", false)) {
            CCheat::FlyboyCheat();
        }
        if (ImGui::RadioButton("Golf Cart", false)) {
            CCheat::GolfcartCheat();
        }
        if (ImGui::RadioButton("Hearse", false)) {
            CCheat::HearseCheat();
        }
        if (ImGui::RadioButton("Love fist", false)) {
            CCheat::LovefistCheat();
        }
        if (ImGui::RadioButton("Monster Truck", false)) {
            CCheat::MonsterTruckCheat();
        }
        if (ImGui::RadioButton("Quad", false)) {
            CCheat::QuadCheat();
        }
        if (ImGui::RadioButton("Stock Car 1", false)) {
            CCheat::StockCarCheat();
        }
        if (ImGui::RadioButton("Stock Car 2", false)) {
            CCheat::StockCar2Cheat();
        }
        if (ImGui::RadioButton("Stock Car 3", false)) {
            CCheat::StockCar3Cheat();
        }
        if (ImGui::RadioButton("Stock Car 4", false)) {
            CCheat::StockCar4Cheat();
        }
        if (ImGui::RadioButton("Stunt Plane", false)) {
            CCheat::StuntPlaneCheat();
        }
        if (ImGui::RadioButton("Tank", false)) {
            CCheat::TankCheat();
        }
        if (ImGui::RadioButton("Tanker", false)) {
            CCheat::TankerCheat();
        }
        if (ImGui::RadioButton("Trashmaster", false)) {
            CCheat::TrashmasterCheat();
        }
    }

    if (ImGui::CollapsingHeader("Weather")) {
        if (ImGui::RadioButton("Cloudy Weather", false)) {
            CCheat::CloudyWeatherCheat();
        }
        if (ImGui::RadioButton("Extra Sunny Weather", false)) {
            CCheat::ExtraSunnyWeatherCheat();
        }
        if (ImGui::RadioButton("Sunny Weather", false)) {
            CCheat::SunnyWeatherCheat();
        }
        if (ImGui::RadioButton("Fast time", false)) {
            CCheat::FastTimeCheat();
        }
        if (ImGui::RadioButton("Foggy Weather", false)) {
            CCheat::FoggyWeatherCheat();
        }
        if (ImGui::RadioButton("Rainy Weather", false)) {
            CCheat::RainyWeatherCheat();
        }
        if (ImGui::RadioButton("Sandstorm", false)) {
            CCheat::SandstormCheat();
        }
        if (ImGui::RadioButton("Slow Time", false)) {
            CCheat::SlowTimeCheat();
        }
        if (ImGui::RadioButton("Storm", false)) {
            CCheat::StormCheat();
        }
        if (ImGui::RadioButton("Dusk", false)) {
            CCheat::DuskCheat();
        }
    }

    if (ImGui::CollapsingHeader("Misc")) {
        if (ImGui::RadioButton("Blow Up Cars", false)) {
            CCheat::BlowUpCarsCheat();
        }
        if (ImGui::RadioButton("Jetpack", false)) {
            CCheat::JetpackCheat();
        }
        if (ImGui::RadioButton("DriveBy", false)) {
            CCheat::DrivebyCheat();
        }
        if (ImGui::RadioButton("All Cars Are Great", false)) {
            CCheat::AllCarsAreGreatCheat();
        }
        if (ImGui::RadioButton("All Cars Are Shit", false)) {
            CCheat::AllCarsAreShitCheat();
        }
        if (ImGui::RadioButton("Black Cars", false)) {
            CCheat::BlackCarsCheat();
        }
        if (ImGui::RadioButton("Beach Party", false)) {
            CCheat::BeachPartyCheat();
        }
        if (ImGui::RadioButton("Countryside Invasion", false)) {
            CCheat::CountrysideInvasionCheat();
        }
        if (ImGui::RadioButton("Elvis Lives Matter", false)) {
            CCheat::ElvisLivesCheat();
        }
        if (ImGui::RadioButton("Everyone Attacks Player", false)) {
            CCheat::EverybodyAttacksPlayerCheat();
        }
        if (ImGui::RadioButton("Funhouse", false)) {
            CCheat::FunhouseCheat();
        }
        if (ImGui::RadioButton("Gang Land", false)) {
            CCheat::GangLandCheat();
        }
        if (ImGui::RadioButton("Gangs", false)) {
            CCheat::GangsCheat();
        }
        if (ImGui::RadioButton("Love Conquers All", false)) {
            CCheat::LoveConquersAllCheat();
        }
        if (ImGui::RadioButton("Love fist", false)) {
            CCheat::LovefistCheat();
        }
        if (ImGui::RadioButton("Mayhem", false)) {
            CCheat::MayhemCheat();
        }
        if (ImGui::RadioButton("Midnight", false)) {
            CCheat::MidnightCheat();
        }
        if (ImGui::RadioButton("Ninja", false)) {
            CCheat::NinjaCheat();
        }
        if (ImGui::RadioButton("Parachute", false)) {
            CCheat::ParachuteCheat();
        }
        if (ImGui::RadioButton("Pink Cars", false)) {
            CCheat::PinkCarsCheat();
        }
        if (ImGui::RadioButton("Predator", false)) {
            CCheat::PredatorCheat();
        }
        if (ImGui::RadioButton("Riot", false)) {
            CCheat::RiotCheat();
        }
        if (ImGui::RadioButton("Village People", false)) {
            CCheat::VillagePeopleCheat();
        }
    }

    if (ImGui::RadioButton("Reset Cheats", false)) {
        CCheat::ResetCheats();
    }
}

void CDebugMenu::SpawnPed(int32 modelID, CVector position) {
    CStreaming::RequestModel(modelID, STREAMING_MISSION_REQUIRED | STREAMING_KEEP_IN_MEMORY);
    CStreaming::LoadAllRequestedModels(false);
    CPed* ped = new CCivilianPed(CPopulation::IsFemale(modelID) ? PED_TYPE_CIVFEMALE : PED_TYPE_CIVMALE, modelID);
    if (ped) {
        ped->SetOrientation(0.0f, 0.0f, 0.0f);
        ped->SetPosn(position);
        CWorld::Add(ped);
        ped->PositionAnyPedOutOfCollision();
    }
}

void CDebugMenu::ProcessPedTool() {
    ImGui::PushItemWidth(465.0f);
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
    if (ImGui::InputText(" ", &m_pedToolInput.GetInputBuffer(), input_text_flags)) {
        reclaim_focus = true;
    }
    ImGui::PopItemWidth();

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    m_pedToolInput.Process();

    ImGui::BeginChild("##pedstool", ImVec2(0, 310));
    const auto w = ImGui::GetWindowWidth();
    static bool widthSet = false;
    ImGui::Columns(2);
    if (!widthSet) {
        widthSet = true;
        ImGui::SetColumnWidth(0, w * 0.2f);
        ImGui::SetColumnWidth(1, w * 0.8f);
    }
    ImGui::TextUnformatted("ID");
    ImGui::NextColumn();
    ImGui::TextUnformatted("Name");
    ImGui::NextColumn();
    ImGui::Separator();
    static int32 selectedId = -1;
    for (const auto& x : m_pedToolInput.GetGridListMap()) {
        const int32 id = x.first;
        const std::string& name = x.second;
        ImGui::PushID(id);

        ImGui::Text("%i", id);
        ImGui::NextColumn();
        if (ImGui::Selectable(name.c_str(), selectedId == id, ImGuiSelectableFlags_SpanAllColumns)) {
            selectedId = id;
        }
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0) && selectedId != -1)
            SpawnPed(selectedId, FindPlayerPed()->TransformFromObjectSpace(CVector(2.0f, 2.0f, 0.0f)));
        ImGui::NextColumn();
        ImGui::PopID();
    }
    ImGui::EndColumns();
    ImGui::EndChild();
    ImGui::Separator();

    ImGui::SetCursorPosX(117);
    if (ImGui::Button("SPAWN PED", ImVec2(250, 0)) && selectedId != -1) {
        SpawnPed(selectedId, FindPlayerPed()->TransformFromObjectSpace(CVector(2.0f, 2.0f, 0.0f)));
    }
}

bool showPlayerInfo;
void CDebugMenu::ShowPlayerInfo() {
    if (!showPlayerInfo)
        return;
    CPlayerPed* pLocalPlayer = FindPlayerPed();
    if (pLocalPlayer != nullptr) {
        ImGui::Begin("Player Information");

        float pos[3] = {pLocalPlayer->GetPosition().x, pLocalPlayer->GetPosition().y, pLocalPlayer->GetPosition().z};
        ImGui::InputFloat3("position", pos, "%.4f", ImGuiInputTextFlags_ReadOnly);

        ImGui::End();
    }
}

void CDebugMenu::ProcessVehicleTool() {
    ImGui::PushItemWidth(465.0f);
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
    if (ImGui::InputText(" ", &m_vehicleToolInput.GetInputBuffer(), input_text_flags)) {
        reclaim_focus = true;
    }
    ImGui::PopItemWidth();

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    m_vehicleToolInput.Process();

    ImGui::BeginChild("##vehiclestool", ImVec2(0, 310));
    const auto w = ImGui::GetWindowWidth();
    static bool widthSet = false;
    ImGui::Columns(2);
    if (!widthSet) {
        widthSet = true;
        ImGui::SetColumnWidth(0, w * 0.2f);
        ImGui::SetColumnWidth(1, w * 0.8f);
    }
    ImGui::TextUnformatted("ID");
    ImGui::NextColumn();
    ImGui::TextUnformatted("Name");
    ImGui::NextColumn();
    ImGui::Separator();
    static int32 selectedId = -1;
    for (const auto& x : m_vehicleToolInput.GetGridListMap()) {
        const int32 id = x.first;
        const std::string& name = x.second;
        ImGui::PushID(id);

        ImGui::Text("%i", id);
        ImGui::NextColumn();
        if (ImGui::Selectable(name.c_str(), selectedId == id, ImGuiSelectableFlags_SpanAllColumns)) {
            selectedId = id;
        }
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0) && selectedId != -1)
            CCheat::VehicleCheat(static_cast<eModelID>(selectedId));
        ImGui::NextColumn();
        ImGui::PopID();
    }
    ImGui::EndColumns();
    ImGui::EndChild();
    ImGui::Separator();

    ImGui::SetCursorPosX(117);
    if (ImGui::Button("SPAWN VEHICLE", ImVec2(250, 0)) && selectedId != -1) {
        CCheat::VehicleCheat(static_cast<eModelID>(selectedId));
    }
}

void CDebugMenu::InitializeAndStartNewScript() {
    CTheScripts::WipeLocalVariableMemoryForMissionScript();
    CRunningScript* script = CTheScripts::StartNewScript(&CTheScripts::ScriptSpace[200000]);
    script->m_bUseMissionCleanup = true;
    script->m_bIsMission = true;
    script->m_pBaseIP = &CTheScripts::ScriptSpace[200000];
    CTheScripts::bAlreadyRunningAMissionScript = true;
    CGameLogic::ClearSkip(false);
}

bool CDebugMenu::StartMission(int32 missionId, bool bDoMissionCleanUp) {
    if (!m_bStartMission && CTheScripts::IsPlayerOnAMission()) {
        if (CCutsceneMgr::ms_cutsceneLoadStatus == 2) {
            CCutsceneMgr::DeleteCutsceneData();
        }
        CTheScripts::FailCurrentMission = 2;
    }
    if (CTheScripts::FailCurrentMission > 0) {
        m_bStartMission = true;
        m_missionToStartId = missionId;
        return true;
    }
    m_bStartMission = false;
    CTheScripts::bPlayerIsOffTheMap = false;
    CGame::currArea = 0;
    CPlayerPed* player = FindPlayerPed();
    FindPlayerPed()->m_nAreaCode = AREA_CODE_NORMAL_WORLD;
    if (!CGame::currArea) {
        player->m_pEnex = nullptr;
        CEntryExitManager::ms_entryExitStackPosn = 0;
        CTimeCycle::StopExtraColour(false);
    }

    if (bDoMissionCleanUp)
        CTheScripts::MissionCleanUp.Process();

    if (CTheScripts::NumberOfExclusiveMissionScripts > 0) {
        if (missionId <= 65532)
            return false;
        missionId = 0xFFFF - missionId;
    }
    CTimer::Suspend();
    int offsetToMission = CTheScripts::MultiScriptArray[missionId];
    CFileMgr::ChangeDir("\\");
    if (CGame::bMissionPackGame) {
        size_t bytesRead = 0;
        while (FrontEndMenuManager.CheckMissionPackValidMenu()) {
            CFileMgr::SetDirMyDocuments();
            sprintf(gString, "MPACK//MPACK%d//SCR.SCM", CGame::bMissionPackGame);
            FILE* file = CFileMgr::OpenFile(gString, "rb");
            if (file) {
                CFileMgr::Seek(file, offsetToMission, 0);
                bytesRead = CFileMgr::Read(file, &CTheScripts::ScriptSpace[200000], 69000);
                CFileMgr::CloseFile(file);
                if (bytesRead >= 1) {
                    InitializeAndStartNewScript();
                    break;
                }
            } else if (bytesRead >= 1) {
                break;
            }
        }
    }
    CFileMgr::SetDir(gta_empty_string);
    if (!CGame::bMissionPackGame) {
        FILE* file = CFileMgr::OpenFile("data\\script\\main.scm", "rb");
        CFileMgr::Seek(file, offsetToMission, 0);
        CFileMgr::Read(file, &CTheScripts::ScriptSpace[200000], 69000);
        CFileMgr::CloseFile(file);
        InitializeAndStartNewScript();
    }
    CTimer::Resume();
    return true;
}

void CDebugMenu::ProcessMissionTool() {
    if (m_bStartMission) {
        StartMission(m_missionToStartId);
    }
    ImGui::PushItemWidth(465.0f);
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
    if (ImGui::InputText(" ", &m_missionToolInput.GetInputBuffer(), input_text_flags)) {
        reclaim_focus = true;
    }
    ImGui::PopItemWidth();

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    m_missionToolInput.Process();

    ImGui::BeginChild("##missionstool", ImVec2(0, 310));
    const auto w = ImGui::GetWindowWidth();
    static bool widthSet = false;
    ImGui::Columns(2);
    if (!widthSet) {
        widthSet = true;
        ImGui::SetColumnWidth(0, w * 0.2f);
        ImGui::SetColumnWidth(1, w * 0.8f);
    }
    ImGui::TextUnformatted("ID");
    ImGui::NextColumn();
    ImGui::TextUnformatted("Name");
    ImGui::NextColumn();
    ImGui::Separator();
    static int32 selectedId = -1;
    for (const auto& x : m_missionToolInput.GetGridListMap()) {
        const int32 id = x.first;
        const std::string& name = x.second;
        ImGui::PushID(id);

        ImGui::Text("%i", id);
        ImGui::NextColumn();
        if (ImGui::Selectable(name.c_str(), selectedId == id, ImGuiSelectableFlags_SpanAllColumns)) {
            selectedId = id;
        }
        if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0) && selectedId != -1) {
            CHud::SetHelpMessage("Starting Mission!", true, false, false);
            StartMission(selectedId);
        }
        ImGui::NextColumn();
        ImGui::PopID();
    }
    ImGui::EndColumns();
    ImGui::EndChild();
    ImGui::Separator();

    ImGui::SetCursorPosX(117);
    if (ImGui::Button("START MISSION", ImVec2(250, 0)) && selectedId != -1) {
        CHud::SetHelpMessage("Starting Mission!", true, false, false);
        StartMission(selectedId);
    }
}

void CDebugMenu::PostFxTool() {
    ImGui::Checkbox("In Cutscene",            &CPostEffects::m_bInCutscene);
    ImGui::Checkbox("Skip Post Process",      &CPostEffects::m_bDisableAllPostEffect);
    ImGui::Checkbox("Save Photo From Script", &CPostEffects::m_bSavePhotoFromScript);
    ImGui::Checkbox("Radiosity",              &CPostEffects::m_bRadiosity);
    ImGui::Checkbox("Night Vision",           &CPostEffects::m_bNightVision);
    ImGui::Checkbox("Infrared Vision",        &CPostEffects::m_bInfraredVision);
    ImGui::Checkbox("Grain",                  &CPostEffects::m_bGrainEnable);
    ImGui::Checkbox("Heat Haze FX",           &CPostEffects::m_bHeatHazeFX);
    ImGui::Checkbox("Darkness Filter",        &CPostEffects::m_bDarknessFilter);
    ImGui::Checkbox("CCTV",                   &CPostEffects::m_bCCTV);
    ImGui::Checkbox("SpeedFX Test Mode",      &CPostEffects::m_bSpeedFXTestMode);
    ImGui::Checkbox("Fog",                    &CPostEffects::m_bFog);
    ImGui::Checkbox("Water Depth Darkness",   &CPostEffects::m_bWaterDepthDarkness);
}

void CDebugMenu::ProcessRenderTool() {
    if (ImGui::CollapsingHeader("Post Processing")) {
        PostFxTool();
    }
    if (ImGui::CollapsingHeader("Collision")) {
        CollisionDebugModule::ProcessImgui();
    }
}

// TODO: The code is a mess, clean it up
void CDebugMenu::ProcessHooksTool() {
    static std::string HooksFilterContent;

    ImGui::PushItemWidth(465.0f);
    bool reclaim_focus = false;
    ImGuiInputTextFlags input_text_flags = ImGuiInputTextFlags_EnterReturnsTrue;
    if (ImGui::InputText(" ", &HooksFilterContent, input_text_flags)) {
        reclaim_focus = true;
    }
    ImGui::PopItemWidth();

    // Auto-focus on window apparition
    ImGui::SetItemDefaultFocus();
    if (reclaim_focus)
        ImGui::SetKeyboardFocusHere(-1); // Auto focus previous widget

    ImGui::BeginChild("##hookstool", ImVec2(0, 0));
    ImGui::SetNextItemOpen(true);
    ImGui::AlignTextToFramePadding();
    if (ImGui::TreeNode("Reversible Hooks")) {
        const auto& allHooks = ReversibleHooks::GetAllHooks();
        // Handle disabling/enabling of all hooks at once
        ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 40);

        std::string disabledAllStr = "all_disabled";
        ImGui::PushID(disabledAllStr.c_str());
        if (ImGui::Button("-")) {
            for (auto& classHooks : allHooks)
                for (auto& hook : classHooks.second)
                    if (hook->m_bIsHooked)
                        hook->Switch();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Disable all");
        ImGui::PopID();

        ImGui::SameLine();
        std::string enableAllStr = "all_enabled";
        ImGui::PushID(enableAllStr.c_str());
        if (ImGui::Button("+")) {
            for (auto& classHooks : allHooks)
                for (auto& hook : classHooks.second)
                    if (!hook->m_bIsHooked)
                        hook->Switch();
        }
        if (ImGui::IsItemHovered())
            ImGui::SetTooltip("Enable all");
        ImGui::PopID();
        // End of disabling/enabling of all hooks at once

        for (auto& classHooks : allHooks) {
            if (!HooksFilterContent.empty() && !findStringCaseInsensitive(classHooks.first, HooksFilterContent))
                continue;

            ImGui::AlignTextToFramePadding();
            bool treeOpen = ImGui::TreeNodeEx(classHooks.first.c_str(), ImGuiTreeNodeFlags_AllowItemOverlap);
            ImGui::SameLine(ImGui::GetWindowContentRegionMax().x - 40);

            std::string disabledStr = classHooks.first + "_disabled";
            ImGui::PushID(disabledStr.c_str());
            if (ImGui::Button("-")) {
                for (auto& hook : classHooks.second)
                    hook->m_bImguiHooked = false;
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Disable all");
            ImGui::PopID();

            ImGui::SameLine();
            std::string enableStr = classHooks.first + "_enabled";
            ImGui::PushID(enableStr.c_str());
            if (ImGui::Button("+")) {
                for (auto& hook : classHooks.second)
                    hook->m_bImguiHooked = true;
            }
            if (ImGui::IsItemHovered())
                ImGui::SetTooltip("Enable all");
            ImGui::PopID();

            for (auto& hook : classHooks.second)
                if (hook->m_bIsHooked != hook->m_bImguiHooked)
                    ReversibleHooks::Switch(hook);

            if (treeOpen) {
                for (auto& hook : classHooks.second) {
                    ImGui::PushStyleVar(ImGuiStyleVar_Alpha, ImGui::GetStyle().Alpha * 0.5f);
                    ImGui::AlignTextToFramePadding();
                    ImGui::Text(hook->m_eHookType == eReversibleHookType::Simple ? "S" : "V");
                    ImGui::PopStyleVar();
                    ImGui::SameLine();
                    ImGui::Checkbox(hook->m_sFunctionName.c_str(), &hook->m_bImguiHooked);
                }
                ImGui::TreePop();
            }
        }
        ImGui::TreePop();
    }
    ImGui::EndChild();
}

#ifdef EXTRA_DEBUG_FEATURES
void CDebugMenu::ProcessExtraDebugFeatures() {
    if (ImGui::BeginTabBar("Modules")) {
        if (ImGui::BeginTabItem("Occlussion")) {
            COcclusionDebugModule::ProcessImgui();
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
                // ImGui::Checkbox("Show Player Information", &showPlayerInfo);
                ProcessPedTool();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Vehicles")) {
                ProcessVehicleTool();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Cheats")) {
                ProcessCheatTool();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Missions")) {
                ProcessMissionTool();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Rendering")) {
                ProcessRenderTool();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Hooks")) {
                ProcessHooksTool();
                ImGui::EndTabItem();
            }
            if (ImGui::BeginTabItem("Other")) {
                ImGui::Checkbox("Display FPS window", &CDebugMenu::m_showFPS);
#ifdef EXTRA_DEBUG_FEATURES
                ImGui::Checkbox("Display Debug modules window", &CDebugMenu::m_showExtraDebugFeatures);
#endif
                ImGui::EndTabItem();
            }

            ImGui::EndTabBar();
        }
        ImGui::End();
    }
    ShowPlayerInfo();
}

static void Spawn_RC_Cars() {
    CPad* pad = CPad::GetPad(0);
    auto player = FindPlayerPed();
    if (player) {
        int32_t vehicleId = -1;

        if (pad->IsStandardKeyJustDown('1'))
            vehicleId = MODEL_RCBANDIT;
        else if (pad->IsStandardKeyJustDown('2'))
            vehicleId = MODEL_RCTIGER;
        else if (pad->IsStandardKeyJustDown('3'))
            vehicleId = MODEL_RCBARON;

        if (vehicleId != -1) {
            CStreaming::RequestModel(vehicleId, STREAMING_GAME_REQUIRED);
            CStreaming::LoadAllRequestedModels(false);
            CVector pos = player->GetPosition() + CVector(2.0f, 1.0f, 1.0f);
            CRemote::GivePlayerRemoteControlledCar(pos, player->GetHeading(), vehicleId);
            CVehicle::bDisableRemoteDetonation = true;
            CVehicle::bDisableRemoteDetonationOnContact = true;
            printf("spawned rc car\n");
        }
    }
}

static void DebugCode() {
    CPad* pad = CPad::GetPad(0);
    if (pad->IsStandardKeyJustDown('1')) {
        printf("");
        CCheat::TankerCheat();
    }
    if (pad->IsStandardKeyJustDown('2')) {
        printf("");
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


    io->DeltaTime = CTimer::ms_fTimeStep * 0.02f;

    ImGui_ImplRW_NewFrame();
    ImGui::NewFrame();

    CDebugMenu::ImguiDisplayExtraDebugFeatures();
    ImguiDisplayPlayerInfo();
    ImguiDisplayFramePerSecond();

    ImGui::EndFrame();
    ImGui::Render();
    ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
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


CDebugMenuToolInput::ToolMap CDebugMenu::m_vehiclesMap{
    { 400, "Landstalker" },
    { 401, "Bravura" },
    { 402, "Buffalo" },
    { 403, "Linerunner" },
    { 404, "Perennial" },
    { 405, "Sentinel" },
    { 406, "Dumper" },
    { 407, "Fire Truck" },
    { 408, "Trashmaster" },
    { 409, "Stretch" },
    { 410, "Manana" },
    { 411, "Infernus" },
    { 412, "Voodoo" },
    { 413, "Pony" },
    { 414, "Mule" },
    { 415, "Cheetah" },
    { 416, "Ambulance" },
    { 417, "Leviathan" },
    { 418, "Moonbeam" },
    { 419, "Esperanto" },
    { 420, "Taxi" },
    { 421, "Washington" },
    { 422, "Bobcat" },
    { 423, "Mr. Whoopee" },
    { 424, "BF Injection" },
    { 425, "Hunter" },
    { 426, "Premier" },
    { 427, "Enforcer" },
    { 428, "Securicar" },
    { 429, "Banshee" },
    { 430, "Predator" },
    { 431, "Bus" },
    { 432, "Rhino" },
    { 433, "Barracks" },
    { 434, "Hotknife" },
    { 435, "Trailer 1" },
    { 436, "Previon" },
    { 437, "Coach" },
    { 438, "Cabbie" },
    { 439, "Stallion" },
    { 440, "Rumpo" },
    { 441, "RC Bandit" },
    { 442, "Romero" },
    { 443, "Packer" },
    { 444, "Monster" },
    { 445, "Admiral" },
    { 446, "Squalo" },
    { 447, "Seasparrow" },
    { 448, "Pizzaboy" },
    { 449, "Tram" },
    { 450, "Trailer 2" },
    { 451, "Turismo" },
    { 452, "Speeder" },
    { 453, "Reefer" },
    { 454, "Tropic" },
    { 455, "Flatbed" },
    { 456, "Yankee" },
    { 457, "Caddy" },
    { 458, "Solair" },
    { 459, "Berkley's RC Van" },
    { 460, "Skimmer" },
    { 461, "PCJ-600" },
    { 462, "Faggio" },
    { 463, "Freeway" },
    { 464, "RC Baron" },
    { 465, "RC Raider" },
    { 466, "Glendale" },
    { 467, "Oceanic" },
    { 468, "Sanchez" },
    { 469, "Sparrow" },
    { 470, "Patriot" },
    { 471, "Quadbike" },
    { 472, "Coastguard" },
    { 473, "Dinghy" },
    { 474, "Hermes" },
    { 475, "Sabre" },
    { 476, "Rustler" },
    { 477, "ZR-350" },
    { 478, "Walton" },
    { 479, "Regina" },
    { 480, "Comet" },
    { 481, "BMX" },
    { 482, "Burrito" },
    { 483, "Camper" },
    { 484, "Marquis" },
    { 485, "Baggage" },
    { 486, "Dozer" },
    { 487, "Maverick" },
    { 488, "News Chopper" },
    { 489, "Rancher" },
    { 490, "FBI Rancher" },
    { 491, "Virgo" },
    { 492, "Greenwood" },
    { 493, "Jetmax" },
    { 494, "Hotring Racer" },
    { 495, "Sandking" },
    { 496, "Blista Compact" },
    { 497, "Police Maverick" },
    { 498, "Boxville" },
    { 499, "Benson" },
    { 500, "Mesa" },
    { 501, "RC Goblin" },
    { 502, "Hotring Racer 3" },
    { 503, "Hotring Racer 2" },
    { 504, "Bloodring Banger" },
    { 505, "Rancher Lure" },
    { 506, "Super GT" },
    { 507, "Elegant" },
    { 508, "Journey" },
    { 509, "Bike" },
    { 510, "Mountain Bike" },
    { 511, "Beagle" },
    { 512, "Cropduster" },
    { 513, "Stuntplane" },
    { 514, "Tanker" },
    { 515,"Roadtrain" },
    { 516, "Nebula" },
    { 517, "Majestic" },
    { 518, "Buccaneer" },
    { 519, "Shamal" },
    { 520, "Hydra" },
    { 521, "FCR-900" },
    { 522, "NRG-500" },
    { 523, "HPV1000" },
    { 524, "Cement Truck" },
    { 525, "Towtruck" },
    { 526, "Fortune" },
    { 527, "Cadrona" },
    { 528, "FBI Truck" },
    { 529, "Willard" },
    { 530, "Forklift" },
    { 531, "Tractor" },
    { 532, "Combine Harvester" },
    { 533, "Feltzer" },
    { 534, "Remington" },
    { 535, "Slamvan" },
    { 536, "Blade" },
    { 537, "Freight" },
    { 538, "Streak" },
    { 539, "Vortex" },
    { 540, "Vincent" },
    { 541, "Bullet" },
    { 542, "Clover" },
    { 543, "Sadler" },
    { 544, "Fire Truck Ladder" },
    { 545, "Hustler" },
    { 546, "Intruder" },
    { 547, "Primo" },
    { 548, "Cargobob" },
    { 549, "Tampa" },
    { 550, "Sunrise" },
    { 551, "Merit" },
    { 552, "Utility Van" },
    { 553, "Nevada" },
    { 554, "Yosemite" },
    { 555, "Windsor" },
    { 556, "Monster 2" },
    { 557, "Monster 3" },
    { 558, "Uranus" },
    { 559, "Jester" },
    { 560, "Sultan" },
    { 561, "Stratum" },
    { 562, "Elegy" },
    { 563, "Raindance" },
    { 564, "RC Tiger" },
    { 565, "Flash" },
    { 566, "Tahoma" },
    { 567, "Savanna" },
    { 568, "Bandito", },
    { 569, "Freight Train Flatbed" },
    { 570, "Streak Train Trailer" },
    { 571, "Kart" },
    { 572, "Mower" },
    { 573, "Dune" },
    { 574, "Sweeper" },
    { 575, "Broadway" },
    { 576, "Tornado" },
    { 577, "AT-400" },
    { 578,  "DFT-30" },
    { 579, "Huntley" },
    { 580,"Stafford" },
    { 581, "BF-400" },
    { 582, "Newsvan" },
    { 583,"Tug" },
    { 584,"Trailer (Tanker Commando)" },
    { 585, "Emperor" },
    { 586,"Wayfarer" },
    { 587,"Euros" },
    { 588,"Hotdog" },
    { 589,"Club" },
    { 590,"Box Freight" },
    { 591,"Trailer 3" },
    { 592,"Andromada" },
    { 593,"Dodo" },
    { 594,"RC Cam" },
    { 595,"Launch" },
    { 596,"Police LS" },
    { 597,"Police SF" },
    { 598,"Police LV" },
    { 599,"Police Ranger" },
    { 600, "Picador" },
    { 601,"S.W.A.T." },
    { 602,"Alpha" },
    { 603, "Phoenix" },
    { 604,"Glendale Damaged" },
    { 605,"Sadler Damaged" },
    { 606,"Baggage Trailer (covered)" },
    { 607, "Baggage Trailer (Uncovered)" },
    { 608, "Trailer (Stairs)" },
    { 609, "Boxville Mission" },
    { 610, "Farm Trailer" },
    { 611, "Street Clean Trailer" }
};

CDebugMenuToolInput::ToolMap CDebugMenu::m_pedsMap{
    { 0, "CJ"},
    { 1,   "Truth" },
    { 2,   "Maccer" },
    { 7,   "Male 01 (Special" },
    { 9,   "Black Female Old Rich" },
    { 10,  "Black Female Old Street" },
    { 11,  "(Las Vegas) Black Female Young Croupier" },
    { 12,  "Black Female Young Rich" },
    { 13,  "Black Female Young Street" },
    { 14,  "Black Male Old Rich" },
    { 15,  "Black Male Old Street" },
    { 16,  "Black Male Young Airport" },
    { 17,  "Black Male Young Business" },
    { 18,  "Black Male Young Beach" },
    { 19,  "Black Male Young Disk Jockey" },
    { 20,  "Black Male Young Rich" },
    { 21,  "Black Male Young Criminal" },
    { 22,  "Black Male Young Street" },
    { 23,  "White Male Young BMX Rider" },
    { 24,  "Madd Doggs Bodyguard 1" },
    { 25,  "Madd Doggs Bodyguard 2" },
    { 26,  "White Male Young Backpacker" },
    { 27,  "White Male Young Construction Worker" },
    { 28,  "Black Male Young Drug Dealer" },
    { 29,  "White Male Young Drug Dealer" },
    { 30,  "Hispanic Male Young Drug Dealer" },
    { 31,  "Desert White Female Old Low Class?" },
    { 32,  "Desert Male Female Old Low Class 1?" },
    { 33,  "Desert Male Female Old Low Class 2?" },
    { 34,  "Desert Male Female Young Low Class 1?" },
    { 35,  "Hispanic Male Old Gardener" },
    { 36,  "White Male Young Golfer 1" },
    { 37,  "White Male Young Golfer 2" },
    { 38,  "Hispanic Female Old Rich" },
    { 39,  "Hispanic Female Old Street" },
    { 40,  "Hispanic Female Young Rich" },
    { 41,  "Hispanic Female Young Street" },
    { 43,  "Hispanic Male Old Rich" },
    { 44,  "Hispanic Male Old Street" },
    { 45,  "Hispanic Male Young Beach" },
    { 46,  "Hispanic Male Young Rich" },
    { 47,  "Hispanic Male Young Criminal" },
    { 48,  "Hispanic Male Young Street" },
    { 49,  "Oriental Male Old Kung Fu" },
    { 50,  "White Male Young Mechanic" },
    { 51,  "Black Male Young Mountain Biker" },
    { 52,  "White Male Young Mountain Biker" },
    { 53,  "Oriental Female Old Rich" },
    { 54,  "Oriental Female Old Street" },
    { 55,  "Oriental Female Young Rich" },
    { 56,  "Oriental Female Young Street" },
    { 57,  "Oriental Male Old Rich" },
    { 58,  "Oriental Male Old Street" },
    { 59,  "Oriental Male Young Rich" },
    { 60,  "Oriental Male Young Street" },
    { 61,  "White Male Young Pilot" },
    { 62,  "White Male Old Pyjamas" },
    { 63,  "Black Female Young Prostitute" },
    { 64,  "Hispanic Female Young Prostitute" },
    { 66,  "Black Male Young Pool 1" },
    { 67,  "Black Male Young Pool 2" },
    { 68,  "White Male Old Preacher" },
    { 69,  "(San Fransisco) Black Female Young Street" },
    { 70,  "White Male Old Scientist" },
    { 71,  "White Male Young Security Guard" },
    { 72,  "(San Fransisco) White Male Young Hippie 1" },
    { 73,  "(San Fransisco) White Male Young Hippie 2" },
    { 75,  "(San Fransisco) White Female Old Prostitute" },
    { 76,  "White Female Young Stewardess" },
    { 77,  "(San Fransisco) White Male Old Tramp 1" },
    { 78,  "White Male Old Tramp 1" },
    { 79,  "Black Male Old Tramp 1" },
    { 80,  "(Las Vegas) Black Male Young Boxer" },
    { 81,  "(Las Vegas) White Male Young Boxer" },
    { 82,  "(Las Vegas) Hispanic Male Young Elvis" },
    { 83,  "(Las Vegas) Black Male Young Elvis" },
    { 84,  "(Las Vegas) Indian Male Young Elvis" },
    { 85,  "(Las Vegas) White Female Young Prostitute" },
    { 87,  "(Las Vegas) White, Female, Young, Stripper 1" },
    { 88,  "White Female Old Rich" },
    { 89,  "White Female Old Street" },
    { 90,  "White Female Young Jogger" },
    { 91,  "White Female Young Rich" },
    { 92,  "White Female Young Rollerblader" },
    { 93,  "White Female Young Street" },
    { 94,  "White Male Old Rich" },
    { 95,  "White Male Old Street" },
    { 96,  "White Male Young Jogger" },
    { 97,  "White Male Young Lifeguard" },
    { 98,  "White Male Young Rich" },
    { 99,  "White Male Young Rollerblader" },
    { 100, "White Male Young Criminal" },
    { 101, "White Male Young Street" },
    { 102, "Ballas Gang Member 1" },
    { 103, "Ballas Gang Member 2" },
    { 104, "Ballas Gang Member 3" },
    { 105, "Grove Street Famalies Gang Member 1" },
    { 106, "Grove Street Famalies Gang Member 2" },
    { 107, "Grove Street Famalies Gang Member 3" },
    { 108, "Los Santos Vagos Gang Member 1" },
    { 109, "Los Santos Vagos Gang Member 2" },
    { 110, "Los Santos Vagos Gang Member 3" },
    { 111, "Mafia Gang Member A" },
    { 112, "Mafia Gang Member B" },
    { 113, "Mafia Boss" },
    { 114, "Vagos Los Aztecas Gang Member 1" },
    { 115, "Vagos Los Aztecas Gang Member 2" },
    { 116, "Vagos Los Aztecas Gang Member 3" },
    { 117, "Triad Gang Member A" },
    { 118, "Triad Gang Member B" },
    { 120, "Triad Boss" },
    { 121, "Da Nang Boys Gang Member 1" },
    { 122, "Da Nang Boys Gang Member 2" },
    { 123, "Da Nang Boys Gang Member 3" },
    { 124, "(Las Vegas) Mafia Gang Member 1" },
    { 125, "(Las Vegas) Mafia Gang Member 2" },
    { 126, "(Las Vegas) Mafia Gang Member 3" },
    { 127, "(Las Vegas) Mafia Gang Member 4" },
    { 128, "(Desert) Native Male, Young, Low Class?" },
    { 129, "(Desert) Native Female, Old Low Class 1?" },
    { 130, "(Desert) Native Female, Old Low Class 2?" },
    { 131, "(Desert) Native Female Young, Low Class?" },
    { 132, "(Desert) Native Male Old Low Class 1?" },
    { 133, "(Desert) Native Male Old Low Class 2?" },
    { 134, "(San Fransisco) Black Male Old Tramp 2" },
    { 135, "(San Fransisco) White Male Old Tramp 2" },
    { 136, "(San Fransisco) White Male Young Tramp 3" },
    { 137, "(San Fransisco) White Male Old Tramp 3" },
    { 138, "(San Fransisco) White Female Young Beach" },
    { 139, "(San Fransisco) Black Female Young Beach" },
    { 140, "(San Fransisco) Hispanic Female Young Beach" },
    { 141, "(San Fransisco) Oriental Female Young Business" },
    { 142, "(San Fransisco) Black Male Young Street" },
    { 143, "(San Fransisco) Black Male Young Criminal" },
    { 144, "Black Male Young Crack Guard?" },
    { 145, "White Female Young Crack" },
    { 146, "Hispanic Male Young Crack Meth?" },
    { 147, "White Male Young Business" },
    { 148, "Black Female Young Business" },
    { 150, "White Female Young Business" },
    { 151, "(Desert) White Female Young Low Class 1?" },
    { 152, "White Female Young Prostitute" },
    { 153, "White Male Young Construction Worker B" },
    { 154, "White Male Young Beach" },
    { 155, "White Male Young Pizza Stack Employee" },
    { 156, "Black Male Old Barber (Old Reece)" },
    { 157, "(Country) White Female Young Hillbilly" },
    { 158, "(Country) White Male Old FR?" },
    { 159, "(Country) White Male Old Hilbilly 1" },
    { 159, "(Country) White Male Old Hilbilly 2" },
    { 160, "(Country) White Male Young FR?" },
    { 161, "(Country) White Male Young, FR?" },
    { 162, "(Country) White Male Young, Hillbilly 1" },
    { 163, "Black Male Young Bouncer" },
    { 164, "White Male Young Bouncer" },
    { 165, "White Male Old Men In Black" },
    { 166, "Black Male Young Men In Black" },
    { 167, "White Male Young Clucking Bell Employee" },
    { 168, "Black Male Old Chilli Stall Owner" },
    { 169, "(San Fransisco) Oriental Female Young Rich" },
    { 170, "(San Fransisco) Oriental Male Young Street" },
    { 171, "(Las Vegas) White Male Young Blackjack Dealer" },
    { 172, "(Las Vegas) White Female Young Croupier" },
    { 173, "San Fransisco Rifa Gang Member 1" },
    { 174, "San Fransisco Rifa Gang Member 2" },
    { 175, "San Fransisco Rifa Gang Member 3" },
    { 176, "Black Male Young Barber" },
    { 177, "White Male Young Barber" },
    { 178, "White Female Young Sexy" },
    { 179, "White Male Young Ammunation Guy" },
    { 180, "Black Male Young Tattoo" },
    { 181, "(Vegas) White Male Young Criminal" },
    { 182, "(Vegas) Black Male Old Cab Driver" },
    { 183, "(Vegas) Black Male Young Criminal" },
    { 184, "(Vegas) Hispanic Male Young Criminal" },
    { 185, "(San Fransisco) Black Male Young Rich" },
    { 186, "(San Fransisco) Oriental Male Young Rich" },
    { 187, "(San Fransisco) Oriental Male Young Business" },
    { 188, "(San Fransisco) White Male Young Street" },
    { 189, "White Male Young Valet" },
    { 190, "Barbara Schternvart" },
    { 191, "Helena Wankstein" },
    { 192, "Michelle Cannes" },
    { 193, "Katie Zhan" },
    { 194, "Millie Perkins" },
    { 195, "Denise Robinson" },
    { 196, "(Country) White Femal, Old, FR?" },
    { 197, "(Country) White Female Old Hillbilly" },
    { 198, "(Country) White Female Young FR1?" },
    { 199, "(Country) White Female Young FR2?" },
    { 200, "(Country) White Male Young Hillbilly 2" },
    { 201, "(Desert) White Female Young LC2?" },
    { 202, "(Desert) White Male Young LC2?" },
    { 203, "Oriental Male Young Karate Trainer" },
    { 204, "White Male Young Karate Trainer" },
    { 205, "White Female Young Burger Shot Employee" },
    { 206, "(Las Vegas) White Male Young Cab Driver" },
    { 207, "(Las Vegas) Hispanic Female Young Prostitute" },
    { 209, "Oriental Male Old Noodle Stall Owner" },
    { 210, "Oriental Male Old Boat School Instructor" },
    { 211, "White Female Old CLOT? (Bar Steward)" },
    { 212, "(Las Vegas) White Male Old Tramp 1" },
    { 213, "(Las Vegas) White Male Old Tramp 2" },
    { 214, "(Las Vegas) White Female Young Waiter (Maria)" },
    { 215, "(San Fransisco) Black Female Old Rich" },
    { 216, "(San Fransisco) White Female Young Rich" },
    { 217, "White Male Young CLOT? (Bar Stuard)" },
    { 218, "(San Fransisco) Black Female Old Street" },
    { 219, "(San Fransisco) Black Female Young Rich" },
    { 220, "(San Fransisco) Black Male Old Cab Driver" },
    { 221, "(San Fransisco) Black Male Old Rich" },
    { 222, "(San Fransisco) Black Male Old Street" },
    { 223, "(San Fransisco) Hispanic Male Young Criminal" },
    { 224, "(San Fransisco) Oriental Female Old Rich" },
    { 225, "(San Fransisco) Oriental Female Old Street" },
    { 226, "(San Fransisco) Oriental Female Young Street" },
    { 227, "(San Fransisco) Oriental Male Old Business" },
    { 228, "(San Fransisco) Oriental Male Old Rich" },
    { 229, "(San Fransisco) Oriental Male Old Street" },
    { 230, "(San Fransisco) White Male Old Tramp 5" },
    { 231, "(San Fransisco) White Female Old Rich" },
    { 232, "(San Fransisco) White Female Old Street" },
    { 233, "(San Fransisco) White Female Young Street" },
    { 234, "(San Fransisco) White Male Old Cab Driver" },
    { 235, "(San Fransisco) White Male Old Rich" },
    { 236, "(San Fransisco) White Male Old Street" },
    { 237, "(San Fransisco) Hispanic Female Young Prostitute" },
    { 238, "(San Fransisco) Black Female Young Prostitute" },
    { 239, "(San Fransisco) White Male Old Tramp 4" },
    { 240, "(San Fransisco) White Male Young Rich" },
    { 241, "(San Fransisco) Male Young Street" },
    { 242, "(San Fransisco) Male Young Street 2" },
    { 243, "(San Fransisco) Female Young Prostitute" },
    { 244, "(Las Vegas) Black Female Young Street 2" },
    { 245, "(Las Vegas) Black Female Young Prostitute" },
    { 246, "(Las Vegas) Hispanic Female Young Street 3" },
    { 247, "Biker A" },
    { 248, "Biker B" },
    { 249, "Black, Male, Young, Pimp" },
    { 250, "(San Fransisco) White Male Young Criminal" },
    { 251, "White Female Young Lifeguard" },
    { 252, "White Male Young Valet 2" },
    { 253, "Black Male Old Security Guard" },
    { 254, "Biker / Drug Dealer" },
    { 255, "White Male Young Chauffeur" },
    { 256, "(San Fransisco) Black Female Young Stripper" },
    { 257, "(San Fransisco) White Female Young Stripper" },
    { 258, "Heckler 1" },
    { 259, "Heckler 2" },
    { 260, "Black Male Young Construction Worker" },
    { 261, "White Male Young Cab Driver 1" },
    { 262, "Black Male Old Cab Driver" },
    { 263, "(Vegas) White Female Young Waiter 2" },
    { 264, "White Male Old Ice Cream Man" },
    { 274, "Los Angeles Emergency Medical Technician 1" },
    { 275, "Las Vegas Emergency Medical Technician 1" },
    { 276, "San Fransisco Emergency Medical Technician 1" },
    { 277, "Los Angeles Fire Department Firefighter 1" },
    { 278, "Las Vegas Fire Department Firefighter 1" },
    { 279, "San Fransisco Fire Department Firefighter 1" },
    { 280, "Los Angeles Police Department Cop 1" },
    { 281, "San Fransisco Police Department Cop 1" },
    { 282, "Las Vegas Police Department Cop 1" },
    { 283, "Country Sheriff" },
    { 284, "Los Angeles Police Department Motorbike Cop 1" },
    { 285, "S.W.A.T Officer" },
    { 286, "FBI Agent" },
    { 287, "Army Officer" },
    { 288, "Desert Sheriff" },
    // These are cutscene specific
    { 290, "Special Actor 1" },
    { 291, "Special Actor 2" },
    { 292, "Special Actor 3" },
    { 293, "Special Actor 4" },
    { 294, "Special Actor 5" },
    { 295, "Special Actor 6" },
    { 296, "Special Actor 7" },
    { 297, "Special Actor 8" },
    { 298, "Special Actor 9" },
    { 299, "Special Actor 10" }
};

CDebugMenuToolInput::ToolMap CDebugMenu::m_missionsMap{
    {0    ,"Initial 1"},
    {1    ,"Initial 2"},
    {2    ,"Intro"},
    {3    ,"Video Game: They Crawled From Uranus"},
    {4    ,"Video Game: Dualuty"},
    {5    ,"Video Game: Go Go Space Monkey"},
    {6    ,"Video Game: Let's Get Ready To Bumble"},
    {7    ,"Video Game: Inside Track Betting"},
    {8    ,"Pool"},
    {9    ,"Lowrider (Bet And Dance)"},
    {10   ,"Beefy Baron"},
    {11   ,"Big Smoke"},
    {12   ,"Ryder"},
    {13   ,"Tagging Up Turf"},
    {14   ,"Cleaning The Hood"},
    {15   ,"Drive-Thru"},
    {16   ,"Nines And AK's"},
    {17   ,"Drive-By"},
    {18   ,"Sweet's Girl"},
    {19   ,"Cesar Vialpando"},
    {20   ,"Los Sepulcros"},
    {21   ,"Doberman"},
    {22   ,"Burning Desire"},
    {23   ,"Gray Imports"},
    {24   ,"Home Invasion"},
    {25   ,"Catalyst"},
    {26   ,"Robbing Uncle Sam"},
    {27   ,"OG Loc"},
    {28   ,"Running Dog"},
    {29   ,"Wrong Side of the Tracks"},
    {30   ,"Just Business"},
    {31   ,"Life's a Beach"},
    {32   ,"Madd Dogg's Rhymes"},
    {33   ,"Management Issues"},
    {34   ,"House Party"},
    {35   ,"Race Tournament / 8-track / Dirt Track"},
    {36   ,"Lowrider (High Stakes)"},
    {37   ,"Reuniting The Families"},
    {38   ,"The Green Sabre"},
    {39   ,"Badlands"},
    {40   ,"First Date"},
    {41   ,"Local Liquor Store"},
    {42   ,"Small Town Bank"},
    {43   ,"Tanker Commander"},
    {44   ,"Against All Odds"},
    {45   ,"King in Exile"},
    {46   ,"Body Harvest"},
    {47   ,"Are you going to San Fierro?"},
    {48   ,"Wu Zi Mu / Farewell, My Love..."},
    {49   ,"Wear Flowers In Your Hai"},
    {50   ,"Deconstruction"},
    {51   ,"555 WE TIP"},
    {52   ,"Snail Trail"},
    {53   ,"Mountain Cloud Boys"},
    {54   ,"Ran Fa Li"},
    {55   ,"Lure"},
    {56   ,"Amphibious Assault"},
    {57   ,"The Da Nang Thang"},
    {58   ,"Photo Opportunity"},
    {59   ,"Jizzy"},
    {60   ,"Outrider"},
    {61   ,"Ice Cold Killa"},
    {62   ,"Toreno's Last Flight"},
    {63   ,"Yay Ka-Boom-Boom"},
    {64   ,"Pier 69"},
    {65   ,"T-Bone Mendez"},
    {66   ,"Mike Toreno"},
    {67   ,"Zeroing In"},
    {68   ,"Test Drive"},
    {69   ,"Customs Fast Track "},
    {70   ,"Puncture Wounds"},
    {71   ,"Back to School"},
    {72   ,"Air Raid"},
    {73   ,"Supply Lines..."},
    {74   ,"New Model Army "},
    {75   ,"Monster"},
    {76   ,"Highjack"},
    {77   ,"Interdiction"},
    {78   ,"Verdant Meadows"},
    {79   ,"N.O.E."},
    {80   ,"Stowaway"},
    {81   ,"Black Project"},
    {82   ,"Green Goo"},
    {83   ,"Learning to Fly"},
    {84   ,"Fender Ketchup"},
    {85   ,"Explosive Situation"},
    {86   ,"You've Had Your Chips"},
    {87   ,"Fish in a Barrel "},
    {88   ,"Don Peyote"},
    {89   ,"Intensive Care"},
    {90   ,"The Meat Business"},
    {91   ,"Freefall"},
    {92   ,"Saint Mark's Bistro"},
    {93   ,"Misappropriation"},
    {94   ,"High Noon"},
    {95   ,"Madd Dogg"},
    {96   ,"Architectural Espionage "},
    {97   ,"Key To Her Heart"},
    {98   ,"Dam And Blast"},
    {99   ,"Cop Wheels"},
    {100  ,"Up, Up and Away!"},
    {101  ,"Breaking the Bank at Caligula's"},
    {102  ,"A Home In The Hills"},
    {103  ,"Vertical Bird"},
    {104  ,"Home Coming "},
    {105  ,"Cut Throat Business"},
    {106  ,"Beat Down on B Dup "},
    {107  ,"Grove 4 Life"},
    {108  ,"Riot"},
    {109  ,"Los Desperados"},
    {110  ,"End Of The Line (1)"},
    {111  ,"End Of The Line (2)"},
    {112  ,"End Of The Line (3)"},
    {113  ,"Shooting range"},
    {114  ,"Los Santos Gym Fight School"},
    {115  ,"San Fierro Gym Fight School"},
    {116  ,"Las Venturas Gym Fight School"},
    {117  ,"Trucking"},
    {118  ,"Quarry"},
    {119  ,"Boat School"},
    {120  ,"Bike School"},
    {121  ,"Taxi-Driver Sub-Mission"},
    {122  ,"Paramedic Sub-Mission"},
    {123  ,"Firefighter Sub-Mission"},
    {124  ,"Vigilante Sub-Mission"},
    {125  ,"Burglary Sub-Mission"},
    {126  ,"Freight Train Sub-Mission"},
    {127  ,"Pimping Sub-Mission"},
    {128  ,"Arena Mission: Blood Ring"},
    {129  ,"Arena Mission: Kickstart"},
    {130  ,"Beat the Cock!"},
    {131  ,"Courier"},
    {132  ,"The Chiliad Challenge"},
    {133  ,"BMX / NRG-500 STUNT Mission"},
    {134  ,"Buy Properties Mission"}
};
