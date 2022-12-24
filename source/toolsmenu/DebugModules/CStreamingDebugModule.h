#pragma once

#include <DebugModule.h>

class CStreamingDebugModule : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    bool m_IsOpen{ false };
};
