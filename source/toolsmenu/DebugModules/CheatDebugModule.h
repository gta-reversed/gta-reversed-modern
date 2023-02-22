#pragma once

#include "DebugModule.h"

class CheatDebugModule final : public DebugModule {
public:
    void RenderWindow() override;
    void RenderMenuEntry() override;
    void Update() override;

private:
    bool m_IsOpen{ false };
    bool m_GodMode{};
};
