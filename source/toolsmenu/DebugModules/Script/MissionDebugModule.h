#pragma once

#include <DebugModule.h>

class MissionDebugModule : public SingleWindowDebugModule {
public:
    MissionDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};

