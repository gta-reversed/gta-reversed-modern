#pragma once

#include <DebugModule.h>

class MissionDebugModule : public DebugModuleSingleWindow {
public:
    MissionDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};

