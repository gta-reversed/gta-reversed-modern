#pragma once

#include <DebugModule.h>

class CPickupsDebugModule : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    void DrawTable();

private:
    bool  m_IsOpen{};
    bool  m_FilterInactive{true};
    bool  m_FilterInvisible{};
    int32 m_SelectedPickupIdx{};
};
