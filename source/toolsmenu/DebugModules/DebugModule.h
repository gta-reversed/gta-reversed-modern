#pragma once

#define IM_VEC2_CLASS_EXTRA \
    operator CVector2D() const { return {x, y}; } \
    ImVec2(const CVector2D& v) : x{v.x}, y{v.y} {} \

#include <imgui.h>
#include "../Utility.h" // TODO Remove this and add it individually to all places this headear is included in

// TODO: This really isn't the appropriate place for this
namespace notsa::events {
struct OnGameInit {
    enum class Stage {
        PRE,
        S1,
        S2,
        POST
    } stage;
    std::string_view datFile;
};

struct OnGameShutdown {
};
};

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
    virtual void RenderWindow() { /*nothing*/ }

    //! Module's entry in the main menu should be rendered here
    virtual void RenderMenuEntry() = 0;

    virtual void HandleEvent(const notsa::events::OnGameInit&) {}
    virtual void HandleEvent(const notsa::events::OnGameShutdown&) {}
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
