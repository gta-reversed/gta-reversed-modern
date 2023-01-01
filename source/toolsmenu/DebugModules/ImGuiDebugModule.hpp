#pragma once

#include "DebugModule.h"

namespace notsa {
namespace debugmodules {
class ImGui : public DebugModule {
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    bool m_MetricsOpen{};
    bool m_AboutOpen{};
    bool m_DemoOpen{};
    bool m_RequestedRestart{};
};
}; // namespace debugmodules
}; // namespace notsa
