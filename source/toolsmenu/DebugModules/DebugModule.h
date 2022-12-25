#pragma once

#define IM_VEC2_CLASS_EXTRA \
    operator CVector2D() const { return {x, y}; } \
    ImVec2(const CVector2D& v) : x{v.x}, y{v.y} {} \

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

namespace notsa {
namespace ui {
struct ScopedWindow {
    ScopedWindow(const char* name, ImVec2 defaultSize, bool& open, ImGuiWindowFlags flags = 0) :
        m_needsEnd{open}
    {
        if (open) {
            ImGui::SetNextWindowSize(defaultSize, ImGuiCond_FirstUseEver);
            ImGui::Begin(name, &open, flags);
        }
    }

    ~ScopedWindow() {
        if (m_needsEnd) {
            ImGui::End();
        }
    }

private:
    bool m_needsEnd{};
};

template<typename T>
struct ScopedID {
    ScopedID(T id) { ImGui::PushID(id); }
    ~ScopedID() { ImGui::PopID(); }
};

//! Render a nested menu (A series of `BeginMenu` calls). If all `BeginMenu` calls return `true` the provided `OnAllVisibleFn` is called.
template<rng::input_range R, typename T>
void DoNestedMenu(R&& menuPath, T OnAllVisibleFn) {
    assert(menuPath.size() > 0); // Empty makes no sense

    int32 nopen{};
    for (auto name : menuPath) {
        if (!ImGui::BeginMenu(name)) {
            break;
        }
        nopen++;
    }
    if (nopen == rng::size(menuPath)) {
        std::invoke(OnAllVisibleFn);
    }
    while (nopen--) {
        ImGui::EndMenu();
    }
}

//! Initializer list version of `DoNestedMenu` (So no ugly `std::to_array` has to be used)
template<typename T>
void DoNestedMenuIL(std::initializer_list<const char*> menuPath, T OnAllVisibleFn) {
    DoNestedMenu(menuPath, OnAllVisibleFn);
}
}; // namespace ui
}; // namespace notsa
