#pragma once

#include <imgui.h>

class DebugModule {
public:
    virtual ~DebugModule() = default;

    //! Called once on imgui initalisation
    virtual void OnImGuiInitialised(ImGuiContext* ctx) { /*nothing*/ }
    
    //! Called once every frame
    virtual void Update() { /*nothing*/ }

    //! Render 3D stuff here (lines, etc...). If rendered elsewhere they (probably) won't be visible.
    virtual void Render3D() { /*nothing*/ };

    //! Module's window should be rendered here
    virtual void RenderWindow() = 0;

    //! Module's entry in the main menu should be rendered here
    virtual void RenderMenuEntry() = 0;
};

//! Class representing a debug module with a single window
class DebugModuleSingleWindow : public DebugModule {
public:
    DebugModuleSingleWindow(const char* wndName, ImVec2 wndDefaultSize) :
        m_wndName{ wndName },
        m_wndDefaultSize{ wndDefaultSize }
    {
    }

    //! Override this for your single main window
    virtual void RenderMainWindow() = 0;

    void RenderWindow() override final;

protected:
    void SetMainWindowOpen(bool open) { m_wndIsOpen = open; }

private:
    ImVec2      m_wndDefaultSize{};
    const char* m_wndName{};
    bool        m_wndIsOpen{};
};
