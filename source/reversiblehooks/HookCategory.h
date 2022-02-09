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

    // Accessors
    auto OverallState()           const { return m_overallState; }

    auto ItemsState()             const { return m_itemsState; }

    auto SubcategoriesState()     const { return m_subcatsState; }

    const auto& Name()            const { return m_name; }

    const auto& SubCategories()   const { return m_subCategories; }
    auto&       SubCategories()         { return m_subCategories; }

    const auto& Items()           const { return m_items; }
    auto&       Items()                 { return m_items; }

    // Adds one item to this category and deals with possible state change
    void AddItem(Item item) {
        assert(!FindItem(item->Name())); // Make sure there are no duplicate names :D

        // Lexographically sorted insert 
        const auto& emplacedItem = *m_items.emplace(
            rng::upper_bound(m_items, item->Name(), {}, [](auto&& v) { return v->Name(); }),
            std::move(item)
        );
        OnOneItemStateChange(emplacedItem); // Deal with possible state change introduced by item
    }

    // Enable/disable all items at once (subcategories' items included)
    void SetAllItemsEnabled(bool enabled) {
        SetAllItemsEnabled_Internal(enabled);
    }

    // Enable/disable all items at once (subcategories' items excluded)
    void SetOurItemsEnabled(bool enabled) {
        for (auto& v : m_items) {
            v->State(enabled);
        }

        m_itemsState = enabled ? HooksState::ALL : HooksState::NONE;
        ReCalculateOverallStateAndMaybeNotify();
    }

    // Set one item's state - Calling `item->SetState` isn't advised as the category's state won't be updated.
    void SetItemEnabled(Item& item, bool enabled) {
        if (enabled != item->Hooked()) {
            item->State(enabled);
            OnOneItemStateChange(item);
        }
    }

    // Find item by name (function name)
    Item FindItem(std::string_view name) {
        const auto it = rng::find_if(m_items, [&](const auto& c) { return c->Name() == name; });
        return it == m_items.end() ? nullptr : *it;
    }

    // Find subcategory by name - Only checks for top-level children
    HookCategory* FindSubcategory(std::string_view name) {
        const auto it = rng::find_if(m_subCategories, [&](const auto& c) { return c.Name() == name; });
        return it == m_subCategories.end() ? nullptr : &*it;
    }

    // Find subcategory by name - Only checks for top-level children
    // If none found a sub-category will be created with the given name.
    auto& FindOrCreateSubcategory(std::string_view name) {
        if (auto* cat = FindSubcategory(name))
            return *cat; // Return found

        // Insert it - It will be sorted later
        return m_subCategories.emplace_back(std::string{ name }, this);
    }

    // Iterates over all items, including those in all subcategories
    // NOTE: Make sure the function doesn't add/remove items/subcategories!
    //       (Underlaying storages are vectors, which don't like being modifies while they're being iterated over)
    template<typename Fn>
    void ForEachItem(Fn&& fn) {
        for (auto& item : m_items) {
            std::invoke(fn, item);
        }
        for (auto& cat : m_subCategories) {
            cat.ForEachItem(fn);
        }
    }

    // Called when `InjectHooksMain` has finished - That is, all hooks have been injected.
    // From this point on no items/categories should be added/removed.
    void OnInjectionEnd() {
        // Re-sort all categories (uses operator<=> defined below)
        m_subCategories.sort();

        // Propagte to all child
        for (auto&& cat : m_subCategories) {
            cat.OnInjectionEnd();
        }
    }

private:
    // Set all our and subcategories' items to the specified state.
    // `dontNotify` - Useful to avoid unnecessary parent notifications (Only the level 1 caller should notify it's parents)
    void SetAllItemsEnabled_Internal(bool enabled, bool notifyParent = true) {
        for (auto& item : m_items) {
            item->State(enabled);
        }

        for (auto& cat : m_subCategories) {
            cat.SetAllItemsEnabled_Internal(enabled, false); // No need to notify parents as we'll do that ourselves
        }

        const auto state = enabled ? HooksState::ALL : HooksState::NONE;
        m_itemsState = state;
        m_subcatsState = state;
        ReCalculateOverallStateAndMaybeNotify(notifyParent); // It's enough if only we notify our parent
    }

    // Recalculates overall state, and if changed, notifies parent.
    // Returns true if state changed
    bool ReCalculateOverallStateAndMaybeNotify(bool notifyParent = true) {
        const auto Calculate = [this] {
            if (m_items.empty()) {
                return m_subcatsState;
            }

            if (m_subCategories.empty()) {
                return m_itemsState;
            }

            if (m_subcatsState == m_itemsState) {
                return m_subcatsState; // Both equal, we can return either - Either both NONE or ALL
            }

            return HooksState::SOME; // They differ 
        };

        const auto prev = m_overallState;
        m_overallState = Calculate();

        const bool changed = prev != m_overallState;

        if (notifyParent && changed) {
            if (m_parent) { // Now, notify parent (so they can update their state)
                m_parent->OnSubcategoryStateChanged(*this);
            }
        }

        return changed;
    }

    // Helper function to recaulcate new state of collection when one item's state changes
    template<rng::input_range R, typename Fn>
    static HooksState CalculateCollectionOverallStateOnEntryChange(R&& collection, HooksState currentCollectiveState, HooksState itemState, Fn&& isHookedPredicate) {
        assert(!collection.empty()); // Logically impossible for the collection to be empty (It has to contain at least the entry whose state just changed)

        if (itemState == currentCollectiveState) {
            return currentCollectiveState; // No changes

        }

        // The collection consists of this entry alone,
        // so overall state is decided by it alone
        if (collection.size() == 1) {
            return itemState;
        }

        // Multiple entries at this point
        switch (currentCollectiveState) {
        case HooksState::ALL:
        case HooksState::NONE: {
            return HooksState::SOME; // At this point the state of the collection and item differ
        }
        case HooksState::SOME: { // Has to calculate it all again - TODO: Check if this is slow - If so, it can be optimized further
            const auto hookedCount = rng::count_if(collection, isHookedPredicate);
            if (hookedCount == 0) {
                return HooksState::NONE;
            } else if (hookedCount == collection.size()) {
                return HooksState::ALL;
            } else {
                return HooksState::SOME;
            }
        }
        }

        assert(0);
        return HooksState::SOME; // Theoritically unreachable - Had to put it here to avoid compiler warnings :D
    }

    // Called when a sub-category's overall state changes
    // (Will propagate to parent if it affected this category's overall state)
    void OnSubcategoryStateChanged(HookCategory& cat) {
        m_subcatsState = CalculateCollectionOverallStateOnEntryChange(
            m_subCategories,
            m_subcatsState,
            cat.OverallState(),
            [](const auto& v) { return v.OverallState() == HooksState::ALL; }
        );
        ReCalculateOverallStateAndMaybeNotify();
    }

    // Not always called - Only when an individual item's state changes
    // Also not called if item is modified from the outside
    // (Currently only called by `AddItem` and `SetItemEnabled`, but not from `SetAllItemsEnabled`)
    void OnOneItemStateChange(const Item& item) {
        m_itemsState = CalculateCollectionOverallStateOnEntryChange(
            m_items,
            m_itemsState,
            item->Hooked() ? HooksState::ALL : HooksState::NONE,
            [](const auto& v) { return v->Hooked(); }
        );
        ReCalculateOverallStateAndMaybeNotify();
    }

    // Main ordering criteria is the no. of top-level sub categories
    // Secondary criteria is the name
    friend std::weak_ordering operator<=>(const HookCategory& lhs, const HookCategory& rhs) {
        const auto numSubCatOrder = rhs.SubCategories().size() <=> lhs.SubCategories().size();
        if (std::is_eq(numSubCatOrder)) 
            return rhs.Name() <=> lhs.Name(); // Same number of sub-categories, order by name
        return numSubCatOrder; // Order by no. of sub-categories
    }
public:
    // Stuff required for the Hooks tool
    HooksState                m_itemsState{ HooksState::ALL };    // Collective state of all items (Can be ignored if `m_items.empty()` (In this case it's always NONE))
    HooksState                m_subcatsState{ HooksState::ALL };  // Collective state of all subcategories (Can be ignored if `m_subCategories.empty()` (In this case it's always NONE))
    HooksState                m_overallState{ HooksState::ALL };  // Overall state - Combination of the above 2 - Calculated by `ReCalculateOverallStateAndMaybeNotify`
    bool                      m_isVisible{true};                  // Updated each time the search box is updated. Indicates whenever we should be visible in the GUI.
private:

    HookCategory*             m_parent{};        // Category we belong to - In case of `RootHookCategory` this is always `nullptr`.
    std::string               m_name{};          // Name of this category (Eg.: `Root`, `Global`, `Entity`, etc...)
    std::list<HookCategory>   m_subCategories{}; // Subcategories - It has to be a list, because we have links between categories
    std::vector<Item>         m_items{};         // Hooks in this category (`RootCategory` should have none) - TODO: IMHO we don't really need to use smart pointers - could just store the hooks as objects instead
};

}; // namespace ReversibleHooks 
