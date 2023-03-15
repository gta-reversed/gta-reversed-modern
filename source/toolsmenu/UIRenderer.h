#pragma once

#include "DebugModules/DebugModules.h"
#include <extensions/Singleton.hpp>

namespace notsa {
namespace ui {
class UIRenderer : public notsa::Singleton<UIRenderer> {
public:
    UIRenderer();
    ~UIRenderer();

    bool Visible() { return m_ShowMenu; }

    //! Request restart of render (done on before frame)
    void RequestReInit() { m_ReInitRequested = true; }

private:
    //! Render 3D stuff in the world (If rendered elsewhere it won't be visible)
    void Render3D();

    //! Render 2D stuff (Called after a new (ImGui) frame has been began)
    void Render2D();

    //! Update input (mouse and keyboard) if necessary 
    void UpdateInput();

    //! Called before a new (ImGui) frame is started (and after the previous one has ended)
    void PreRenderUpdate();

    //! The actual draw loop
    void DrawLoop();

    //! Random code you want to run (Called from `PreRenderUpdate`)
    void DebugCode();
private:
    friend void ::RenderEffects();  // For `Render3D()`
    friend void ::FrontendIdle();   // For `DrawLoop()` VVV
    friend void ::Idle(void*);      // For `DrawLoop()` Yes, called in 2 places, but they are never called in the same frame (As `Idle` is called when not in the menu only)
    friend void ::CPad::UpdatePads();

private:
    bool          m_Initialised{};
    bool          m_ShowMenu{};
    bool          m_ReInitRequested{};
    ImGuiContext* m_ImCtx{};
    ImGuiIO*      m_ImIO{};
    DebugModules  m_DebugModules{ m_ImCtx };
};
}; // namespace ui
}; // namespace notsa
