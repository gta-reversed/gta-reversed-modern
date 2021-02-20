#pragma once

#include "imgui.h"
#include "CDebugMenuToolInput.h"
#include "CVector.h"

class CDebugMenu
{
private:
    static CDebugMenuToolInput m_vehicleToolInput;
    static CDebugMenuToolInput m_pedToolInput;
    static CDebugMenuToolInput m_missionToolInput;
    static bool m_bStartMission;
    static std::int32_t m_missionToStartId;
    static bool m_imguiInitialised;
    static bool m_showMenu;
    static CSprite2d m_mouseSprite;

    static void ImguiDisplayFramePerSecond();
    static void ImguiDisplayPlayerInfo();
    static void ProcessCheatTool();
    static void SpawnPed(std::int32_t modelID, CVector position);
    static void ProcessPedTool();
    static void ShowPlayerInfo();
    static void ProcessVehicleTool();
    static void InitializeAndStartNewScript();
    static bool StartMission(std::int32_t missionId, bool bDoMissionCleanUp = true);
    static void ProcessMissionTool();
    static void ProcessHooksTool();
    //static void ToggleHook();
public:
    static ImGuiIO* io;
    static void ImguiInitialise();
    static void ImguiInputUpdate();
    static void ImguiDrawLoop();
    static void ImGuiDrawMouse();
    static void Shutdown();

    static bool Visible() { return m_showMenu; }

    static CDebugMenuToolInput::ToolMap m_vehiclesMap;
    static CDebugMenuToolInput::ToolMap m_pedsMap;
    static CDebugMenuToolInput::ToolMap m_missionsMap;
};

bool findStringCaseInsensitive(const std::string& strHaystack, const std::string& strNeedle);
