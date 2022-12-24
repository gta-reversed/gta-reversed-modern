#pragma once

#include <DebugModule.h>

class DarkelDebugModule : public DebugModuleSingleWindow {
public:
    DarkelDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};
