#pragma once

#include <DebugModule.h>

class CheatDebugModule : public DebugModuleSingleWindow {
public:
    CheatDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};
