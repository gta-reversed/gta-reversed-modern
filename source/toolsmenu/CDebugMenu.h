#pragma once

#include <imgui.h>

class CDebugMenu {
public:
    static void ImGuiInitialise();
    static void ImGuiInputUpdate();
    static void ImGuiDrawLoop();
    static void Shutdown();
    static void Render3D();

    static bool Visible() { return m_ShowMenu; }

private:
    static bool m_Initialised;
    static bool m_ShowMenu;
};
