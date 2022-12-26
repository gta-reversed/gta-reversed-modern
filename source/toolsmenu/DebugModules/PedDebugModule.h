#pragma once

#include "DebugModule.h"

class PedDebugModule : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    void ProcessPed(struct PedInfo&);

private:
    float m_collapseToggleDist{ 20.f };
    float m_drawDist{ 200.f };
    bool  m_visible{};
    bool  m_autoCollapse{};
    bool  m_IsOpen{};
};
