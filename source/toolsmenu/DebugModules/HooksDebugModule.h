#pragma once

#include "DebugModule.h"

namespace ReversibleHooks {
class HookCategory;
};

class HooksDebugModule : public DebugModule {
    enum class SlideSetterMode {
        NONE,
        SETTER, // This mode turns into either `TURN_OFF` OR `TURN_ON` as soon as it's possible
        TURN_ON,
        TURN_OFF,
        TOGGLE
    };
public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

private:
    void RenderCategoryItems(ReversibleHooks::HookCategory& cat);
    void RenderCategory(ReversibleHooks::HookCategory& cat);
    bool HandleSlideSetterForItem(bool& inOutState); // Returns if state changed

private:
    bool m_IsOpen{};
    struct {
        SlideSetterMode Mode;
    } m_SlideSetter{};
};
