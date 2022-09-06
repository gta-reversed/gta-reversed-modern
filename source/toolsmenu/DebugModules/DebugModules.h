#pragma once

#include <imgui.h>

class DebugModules {
public:
    static bool m_ShowFPS;
    static bool m_ShowExtraDebugFeatures;
    static bool m_ShowPlayerInfo;

    static void Initialise(ImGuiContext* ctx);
    static void DisplayMainWindow();
    static void DisplayFramePerSecond();
    static void DisplayExtraDebugFeatures();
    static void ProcessRenderTool();
    static void ProcessExtraDebugFeatures();

    static void ProcessRender(bool showMenu);
};
