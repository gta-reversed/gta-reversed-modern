#pragma once

#include <DebugModule.h>

class FXDebugModule : public SingleWindowDebugModule {
public:
    FXDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};

