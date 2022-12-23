#pragma once

#include <imgui.h>

class DebugModule {
public:
    virtual ~DebugModule() = default;

    //! Called once on imgui initalisation
    virtual void OnImGuiInitialised(ImGuiContext* ctx) { /*nothing*/ }
    
    //! Called once every frame
    virtual void Update() { /*nothing*/ }

    //! Module's main window should be rendered here
    virtual void RenderWindow() = 0;

    //! Module's entry in the main menu should be rendered here
    virtual void RenderMenuEntry() = 0;
};
