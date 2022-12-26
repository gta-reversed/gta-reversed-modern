#pragma once

#include <DebugModule.h>

class SpawnerDebugModule : public DebugModule{
public:
    SpawnerDebugModule();

    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    bool m_IsOpen{};
};
