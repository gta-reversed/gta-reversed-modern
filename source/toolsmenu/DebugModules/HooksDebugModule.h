#pragma once

#include <DebugModule.h>

class HooksDebugModule : public DebugModuleSingleWindow {
public:
    HooksDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};
