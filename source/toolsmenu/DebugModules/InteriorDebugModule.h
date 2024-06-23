#pragma once

#include "DebugModule.h"

namespace notsa {
namespace debugmodules {
class Interior final : public DebugModule {
public:
    void RenderWindow() override;
    void RenderMenuEntry() override;
    // There's also `void Update()`, but you'll rarely need that one

private:
    bool m_IsOpen{}; // Main window's state
    bool m_ShowClosest{};
};
}; // namespace debugmodules
}; // namespace notsa
