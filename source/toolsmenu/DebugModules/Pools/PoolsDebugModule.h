#pragma once

#include <DebugModule.h>

class PoolsDebugModule : public DebugModuleSingleWindow {
public:
    PoolsDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};
