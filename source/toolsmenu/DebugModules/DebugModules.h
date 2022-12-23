#pragma once

#include <imgui.h>
#include "DebugModule.h"

class DebugModules {
    using ModulePtr = std::unique_ptr<DebugModule>;
public:
    //! Process stuff (Including rendering)
    void Update(bool cursorVisible);

    //! Add a new module
    template<std::derived_from<DebugModule> T>
    void Add() {
        auto& module = m_modules.emplace_back(std::make_unique<T>());
        module->OnImGuiInitialised(m_imctx);
    }

private:
    std::vector<ModulePtr> m_modules{};
    ImGuiContext*          m_imctx{};
    bool                   m_menuOpen{};

public:

    static bool m_ShowFPS;
    static bool m_ShowExtraDebugFeatures;
    static bool m_ShowPlayerInfo;

    void Initialise(ImGuiContext* ctx);
    static void DisplayMainWindow();
    static void DisplayFramePerSecond();
    static void DisplayExtraDebugFeatures();
    static void ProcessRenderTool();
    static void ProcessExtraDebugFeatures();

    static void ProcessRender(bool showMenu);
};
