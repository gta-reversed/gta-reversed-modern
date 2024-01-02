#pragma once

#include <imgui.h>
#include "DebugModule.h"

class DebugModules {
public:
    DebugModules(ImGuiContext* ctx);

    //! Pre-Render updates
    void PreRenderUpdate();

    //! Process stuff (Including rendering)
    void Render2D();

    //! Process 3D rendering
    void Render3D();

private:
    //! Creates all modules
    void CreateModules();

    //! Render menu bar stuff (FPS, etc)
    void RenderMenuBarInfo();

    //! Add a new module
    template<std::derived_from<DebugModule> T>
    void Add() {
        auto& module = m_Modules.emplace_back(std::make_unique<T>());
        module->OnImGuiInitialised(m_ImCtx);
    }

private:
    std::vector<std::unique_ptr<DebugModule>> m_Modules{};
    ImGuiContext*                             m_ImCtx{};
};
