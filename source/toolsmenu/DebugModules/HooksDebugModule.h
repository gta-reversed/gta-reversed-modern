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

private:
    class HookFilter {
        static constexpr std::string_view NAMESPACE_SEP{ "/" };
        static constexpr std::string_view HOOKNAME_SEP{ "::" };

    public:
        void Render();

        json Serialize() const;
        void Deserialize(const json& j);

    private:
        void ClearFilters();
        bool IsNamespaceFilterActive();
        bool IsHookFilterEmpty();
        bool IsHookFilterPresent();
        bool IsHookFilterActive();
        bool EitherFiltersActive();
        bool IsRelativeToRootNamespace();
        void MakeAllVisibleAndOpen(ReversibleHooks::HookCategory& cat, bool visible, bool open);
        auto DoFilter_Internal(ReversibleHooks::HookCategory& cat, size_t depth = 0) -> std::pair<bool, bool>;
        void DoFilter(ReversibleHooks::HookCategory& cat);
        void OnInputUpdate();

    private:
        //! Used as char buffer for the ImGUI input
        std::string m_Input{};

        //! Are the string checks case sensitive?
        //! It is used, but there's no GUI to change it for now. It is case-insensitive by default (false).
        bool m_IsCaseSensitive{};

        //! Contains all the tokens on the left side split by `NAMESPACE_SEP` of the input split by `HOOKNAME_SEP`
        //! Eg `m_input` => content:
        //! - `Name/Space/` => `Name`, `Space`, `` (<= empty string)
        //! - `Name/Space/::` => -||- (Same as the above example)
        //! - `/` - `` (empty string) - Indicates root namespace (See `IsRelativeToRootNamespace`)
        //! - `///` - 4 empty strings
        std::vector<std::string_view> m_NamespaceTokens{};

        //! Filter of hook name
        //! If `nullopt` means there was no `::` (HOOKNAME_SEP) in the user input
        //! otherwise if there was, it contains whatever was after it (Which might be nothing - So the string is empty)
        std::optional<std::string_view> m_HookFilter{};
    };

public:
    void RenderWindow() override final;
    void RenderMenuEntry() override final;

    json Serialize() const override final;
    void Deserialize(const json& j) override final;
    std::string_view GetID() const final override { return "HooksDebugModule"; }

private:
    void RenderCategoryItems(ReversibleHooks::HookCategory& cat);
    void RenderCategory(ReversibleHooks::HookCategory& cat);
    bool HandleSlideSetterForItem(bool& inOutState); // Returns if state changed

private:
    bool m_IsOpen{};
    struct {
        SlideSetterMode Mode;
    } m_SlideSetter{};
    HookFilter m_HookFilter{};
};
