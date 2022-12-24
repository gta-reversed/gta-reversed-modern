#pragma once

#include <DebugModule.h>

class SpawnerDebugModule : public DebugModuleSingleWindow {
public:
    SpawnerDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};
