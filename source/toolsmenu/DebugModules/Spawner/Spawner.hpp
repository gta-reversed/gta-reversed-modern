#pragma once

#include <DebugModule.h>

class SpawnerDebugModule : public DebugModule {
public:
    SpawnerDebugModule();

    void RenderWindow() override;
    void RenderMenuEntry() override;
private:
    void RenderSpawnerWindow();
private:
    bool m_wndIsOpen{};
};
