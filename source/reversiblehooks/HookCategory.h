#pragma once

#include "ReversibleHooks.h"
#include "ReversibleHook/Base.h"
#include <TristateCheckbox.h>
#include <ranges>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>

namespace rng = std::ranges;

namespace ReversibleHooks {
class HookCategory {
public:
    using Item = std::shared_ptr<ReversibleHook::Base>;
    using HooksState = ImGui::ImTristate; // Don't really want to deal with enum conversions so this should do.
    //enum class HooksState {
    //    ALL  = 1, // All hooked
    //    NONE = 0, // None hooked
    //    SOME = -1 // Some hooked
    //};

public:
    HookCategory(std::string name, HookCategory* parent) :
        m_name{ std::move(name) },
        m_parent{parent}
    {
    }

    auto OverallState()           const { return m_overallState; }
    auto ItemsState()             const { return m_itemsState; }
    auto SubcategoriesState()     const { return m_subcatsState; }

    const auto& SubCategories()   const { return m_subCategories; }
    auto& SubCategories()               { return m_subCategories; }

    const auto& Name()            const { return m_name; }
    const auto& Items()           const { return m_items; }
    auto& Items()                       { return m_items; }

    // Adds one item to this category and deals with possible state change
    void AddItem(Item item) {
        auto& emplaced = m_items.emplace_back(std::move(item));
        OnItemStateChange(); // Deal with possible state change introduced by item
    }

    // Enable/disable all items at once (subcategories' items included)
    void SetAllItemsEnabled(bool enabled) {
        SetAllItemsEnabled_Internal(enabled);
    }

    // Enable/disable all items at once (subcategories' items excluded)
    void SetOurItemsEnabled(bool enabled) {
        for (auto& v : m_items) {
            v->SetState(enabled);
        }

        m_itemsState = enabled ? HooksState::ALL : HooksState::NONE;
        ReCalculateOverallStateAndMaybeNotify();
    }

    // Set one item's state - Calling `item->SetState` isn't advised as the category's state won't be updated.
    void SetItemEnabled(Item& item, bool enabled) {
        if (enabled != item->Hooked()) {
            item->SetState(enabled);
            OnItemStateChange();
        }
    }

    // Find item by name (function name)
    Item FindItem(std::string_view name) {
        const auto it = rng::find_if(m_items, [&](const auto& c) { return c->Name() == name; });
        return it == m_items.end() ? nullptr : *it;
    }

    // Find subcategory by name - Only checks for children
    HookCategory* FindSubcategory(std::string_view name) {
        const auto it = rng::find_if(m_subCategories, [&](const auto& c) { return c.Name() == name; });
        return it == m_subCategories.end() ? nullptr : &*it;
    }

    // Find subcategory by name - Only checks for children
    // If none found a category will be created with the given name.
    auto& FindOrCreateSubcategory(std::string_view name) {
        if (auto cat = FindSubcategory(name))
            return *cat; // Return found
        return m_subCategories.emplace_back(std::string{ name }, this); // Create it
    }

    // Iterates over all items, including those in all subcategories
    // NOTE: Make sure the function doesn't add/remove items/subcategories!
    //       (Underlaying storages are vectors, which don't like being modifies while they're being iterated over)
    template<typename Fn>
    void ForEachItem(Fn fn) {
        for (auto& item : m_items) {
            std::invoke(fn, item);
        }
        for (auto& cat : m_subCategories) {
            cat.ForEachItem(fn);
        }
    }

private:
    // `dontNotify` - Since we modify all subcategories ourselves it's not needed that all our children to notify us.
    void SetAllItemsEnabled_Internal(bool enabled, bool dontNotify = false) {
        for (auto& item : m_items) {
            item->SetState(enabled);
        }

        for (auto& cat : m_subCategories) {
            cat.SetAllItemsEnabled_Internal(enabled, true);
        }

        const auto state = enabled ? HooksState::ALL : HooksState::NONE;
        m_itemsState = state;
        m_subcatsState = state;
        ReCalculateOverallStateAndMaybeNotify(!dontNotify);
    }

    // Recalculates overall state, and if changed, notifies parent
    // Should be called after either `m_subcatsState` or `m_itemsState` changes
    // Returns true if state has changed
    bool ReCalculateOverallStateAndMaybeNotify(bool notify = true) {
        const auto Calculate = [this] {
            using enum HooksState;
            if (m_items.empty()) {
                return m_subcatsState;
            }

            if (m_subCategories.empty()) {
                return m_itemsState;
            }

            if (m_subcatsState == m_itemsState)
                return m_subcatsState; // Both equal, we can return either - Either both NONE or ALL

            return SOME; // They differ 
        };

        const auto prev = m_overallState;
        m_overallState = Calculate();

        const bool changed = prev != m_overallState;

        if (notify && changed) {
            if (m_parent) { // Now, notify parent (so they can update their state)
                m_parent->OnSubcategoryStateChanged(*this);
            }
        }

        return changed;
    }

    // Called when a sub-category's state changes - Will propagate to parent if this affected our overall state
    void OnSubcategoryStateChanged(HookCategory& cat) {
        using enum HooksState;

        const auto fullyHookedCount = rng::count_if(m_subCategories, [](const auto& v) -> bool { return v.OverallState() == HooksState::ALL; });
        m_subcatsState =
            fullyHookedCount == m_subCategories.size() ? ALL  : // Has to be before the the `NONE` case (in case `m_subCategories.empty()`)
            fullyHookedCount == 0                      ? NONE :
                                                         SOME;
        ReCalculateOverallStateAndMaybeNotify();
    }

    // Only called from `SetItemEnabled` and `AddItem`
    void OnItemStateChange() {
        using enum HooksState;

        const auto hookedCount = rng::count_if(m_items, [](const auto& v) -> bool { return v->Hooked(); });
        m_itemsState =
            hookedCount == m_items.size() ? HooksState::ALL : // Has to be before the the `NONE` case (in case `m_items.empty()`)
            hookedCount == 0              ? HooksState::NONE :
                                            HooksState::SOME;

        ReCalculateOverallStateAndMaybeNotify();
    }

public:
    // Stuff required for the Hooks tool
    HooksState                m_itemsState{ HooksState::ALL };    // Collective state of all items
    HooksState                m_subcatsState{ HooksState::ALL };  // Collective state of all subcategories
    HooksState                m_overallState{ HooksState::ALL };  // Overall state - Combination of the above 2 
    bool                      m_isVisible{true};                  // Updated each time the search box is updated. Indicates whenever we should be visible in the GUI.
private:

    HookCategory*             m_parent{};        // Category we belong to - In case of `RootHookCategory` this is always `nullptr`.
    std::string               m_name{};          // Name of this category (Eg.: `Root`, `Global`, `Entity`)
    std::list<HookCategory>   m_subCategories{}; // Subcategories - It has to be a list, because we have links between categories
    std::vector<Item>         m_items{};         // Hooks in this category (`RootCategory` should have none)
};

}; // namespace ReversibleHooks 
