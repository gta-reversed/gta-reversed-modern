#pragma once

#include <imgui.h>

class CDebugMenu {
public:
    static void ImGuiInitialise();
    static void ImGuiInputUpdate();
    static void ImGuiDrawLoop();
    static void Shutdown();

    static bool Visible() { return m_ShowMenu; }

private:
    static bool m_Initialised;
    static bool m_ShowMenu;
};
