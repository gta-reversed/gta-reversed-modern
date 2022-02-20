#pragma once

#include <imgui.h>

#include "CDebugMenuToolInput.h"
#include "Vector.h"

class CDebugMenu {
public:
    static ImGuiIO* io;
    static void ImguiInitialise();
    static void ImguiInputUpdate();
    static void ImguiDrawLoop();
    static void ImGuiDrawMouse();
    static void Shutdown();

    static bool Visible() { return m_showMenu; }

private:
    static bool m_imguiInitialised;
    static bool m_showMenu;
    static bool m_showFPS;
    static bool m_showExtraDebugFeatures;
    static CSprite2d m_mouseSprite;

    static void ImguiDisplayFramePerSecond();
    static void ImguiDisplayExtraDebugFeatures();
    static void ImguiDisplayPlayerInfo();

#ifdef EXTRA_DEBUG_FEATURES
    static void ProcessExtraDebugFeatures();
#endif
    static void LoadMouseSprite();
};
