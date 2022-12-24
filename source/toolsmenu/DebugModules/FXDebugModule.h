#pragma once

#include <DebugModule.h>

class FXDebugModule : public DebugModuleSingleWindow {
public:
    FXDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};

