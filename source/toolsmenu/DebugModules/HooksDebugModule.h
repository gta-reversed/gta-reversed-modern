#pragma once

#include <DebugModule.h>

class HooksDebugModule : public SingleWindowDebugModule {
public:
    HooksDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;

private:

};
