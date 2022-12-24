#pragma once

#include <DebugModule.h>

class CPickupsDebugModule : public DebugModuleSingleWindow {
public:
    CPickupsDebugModule();

    void RenderMainWindow() override final;
    void RenderMenuEntry() override final;
};
