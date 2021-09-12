#pragma once

#include <imgui.h>

#include "CDebugMenuToolInput.h"
#include "CVector.h"

class CDebugMenu {
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

private:
    static CDebugMenuToolInput m_vehicleToolInput;
    static CDebugMenuToolInput m_pedToolInput;
    static CDebugMenuToolInput m_missionToolInput;
    static bool m_bStartMission;
    static int32 m_missionToStartId;
    static bool m_imguiInitialised;
    static bool m_showMenu;
    static bool m_showFPS;
    static bool m_showExtraDebugFeatures;
    static CSprite2d m_mouseSprite;

    static void ImguiDisplayFramePerSecond();
    static void ImguiDisplayExtraDebugFeatures();
    static void ImguiDisplayPlayerInfo();
    static void ProcessCheatTool();
    static void SpawnPed(int32 modelID, CVector position);
    static void ProcessPedTool();
    static void ShowPlayerInfo();
    static void ProcessVehicleTool();
    static void InitializeAndStartNewScript();
    static bool StartMission(int32 missionId, bool bDoMissionCleanUp = true);
    static void ProcessMissionTool();
    static void ProcessRenderTool();
    static void PostFxTool();
    static void ProcessHooksTool();
#ifdef EXTRA_DEBUG_FEATURES
    static void ProcessExtraDebugFeatures();
#endif
    //static void ToggleHook();
    static void LoadMouseSprite();
};

bool findStringCaseInsensitive(const std::string& strHaystack, const std::string& strNeedle);
