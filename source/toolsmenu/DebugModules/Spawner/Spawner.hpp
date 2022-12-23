#pragma once

#include <DebugModule.h>

class SpawnerDebugModule : public SingleWindowDebugModule {
public:
    SpawnerDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};
