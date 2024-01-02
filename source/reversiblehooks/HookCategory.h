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
    auto OverallState()         const { return m_overallState; }

    bool Disabled()             const { return m_allCatsDisabled && m_itemsDisabled; }
    bool ItemsDisabled()        const { return m_itemsDisabled; }

    auto ItemsState()           const { return m_itemsState; }
                                
    auto SubcategoriesState()   const { return m_subcatsState; }
                                
    const auto& Name()          const { return m_name; }
                                
    const auto& SubCategories() const { return m_subCategories; }
    auto&       SubCategories()       { return m_subCategories; }
                                
    const auto& Items()         const { return m_items; }
    auto&       Items()               { return m_items; }
                                
    auto Parent()               const { return m_parent; }

    bool Visible()              const { return m_isVisible; }
    void Visible(bool visible)        { m_isVisible = visible; }

    bool Open()                 const { return m_isOpen; }
    void Open(bool open)              { m_isOpen = open; }

    //! Add one item to this category (Deal with possible state change)
    void AddItem(Item item) {
        assert(!FindItem(item->Name())); // Make sure there are no duplicate names :D

        // Lexographically sorted insert 
        const auto& emplacedItem = *m_items.emplace(
            rng::upper_bound(m_items, item->Name(), {}, [](auto&& v) { return v->Name(); }),
            std::move(item)
        );

        OnOneItemStateChange(emplacedItem); // Deal with possible state change introduced by item
    }

    //! Enable/disable all items at once (subcategories' items included)
    void SetAllItemsEnabled(bool enabled) {
        SetAllItemsState_Internal(enabled);
    }

    //! Toggle state of all items (subcategories' items included)
    void ToggleAllItemsState() {
        if (OverallState() == HooksState::MIXED) {
            SetAllItemsState_Internal(m_triStateToggle);
            m_triStateToggle = !m_triStateToggle;
        } else {
            const auto newState = OverallState() != HooksState::ALL; // ALL => NONE; NONE => ALL
            SetAllItemsState_Internal(newState);
            m_triStateToggle = !newState;
        }
    }

    // Enable/disable all _our_ items at once (subcategories' items _excluded_)
    void SetOurItemsState(bool enabled) {
        SetOurItemsState_Internal(enabled);
        ReCalculateOverallStateAndMaybeNotify();
    }

    // Set one item's state - Calling `item->SetState` isn't advised as the category's state won't be updated.
    void SetItemEnabled(Item& item, bool enabled) {
        if (item->State(enabled)) { // State changed?
            OnOneItemStateChange(item);
        }
    }

    //! Find item by name (function name)
    Item FindItem(std::string_view name) {
        const auto it = rng::find_if(m_items, [&](const auto& c) { return c->Name() == name; });
        return it == m_items.end() ? nullptr : *it;
    }

    //! Find subcategory by name (Only checks for direct sub categories [No recursion])
    HookCategory* FindSubcategory(std::string_view name) {
        const auto it = rng::find_if(m_subCategories, [&](const auto& c) { return c.Name() == name; });
        return it == m_subCategories.end() ? nullptr : &*it;
    }

    //! Find subcategory by name - Only checks for top-level children
    //! If none found a sub-category will be created with the given name.
    auto& FindOrCreateSubcategory(std::string_view name) {
        if (auto* cat = FindSubcategory(name))
            return *cat; // Return found

        // Insert it - It will be sorted later
        return m_subCategories.emplace_back(std::string{ name }, this);
    }

    //! Iterates over all items, including those in all subcategories
    //! NOTE: Make sure the function doesn't add/remove items/subcategories!
    //!       (Underlaying storages are vectors, which don't like being modifies while they're being iterated over)
    template<typename Fn>
    void ForEachItem(Fn&& fn) {
        for (auto& item : m_items) {
            std::invoke(fn, item);
        }
        for (auto& cat : m_subCategories) {
            cat.ForEachItem(fn);
        }
    }

    /*!
    * @brief Iterate over all sub-categories recursively
    *
    * @param fn A functor taking a `HookCategory&` as it's first argument
    */
    template<typename Fn>
    void ForEachCategory(Fn&& fn) {
        std::invoke(fn, *this);
        for (auto& cat : m_subCategories) {
            cat.ForEachCategory(fn);
        }
    }

    //! Called when `InjectHooksMain` has finished - That is, all hooks have been injected.
    //! From this point on no items/categories should be added/removed.
    void OnInjectionEnd() {
        // Re-sort all categories (uses operator<=> defined below)
        m_subCategories.sort();

        // Propagte to all child
        for (auto&& cat : m_subCategories) {
            cat.OnInjectionEnd();
        }

        // Call this only after the above (Because by then all sub-categories have their disabled state calculated properly)
        CalculateIsDisabled();
    }

private:
    /*!
    * @brief Calculates and caches disabled state
    * @returns If all items (including those of sub-category's) is disabled
    */
    void CalculateIsDisabled() {
        // Update subcategories first
        rng::for_each(m_subCategories, &HookCategory::CalculateIsDisabled);

        // Now update ourselves
        m_allCatsDisabled = rng::all_of(m_subCategories, [](HookCategory& cat) {  return cat.Disabled(); });
        m_itemsDisabled   = rng::all_of(m_items, [](const Item& item)  { return item->Locked(); });
    }

    /*!
    * @brief Change state of all entities
    * 
    * @param entities         The entities whos state is to be changed
    * @param currState        Current overall state
    * @param DoSetEntityState Function to change the state of one entity, should return whenever the (entity's) state has changed to the expected value.
    * @param GetEntityState   Function to get the state of an entity.
    * 
    * @return The new overall state
    */
    template<rng::input_range R>
    HooksState SetEntitiesState(R&& entities, HooksState currState, bool newState, auto&& DoSetEntityState, auto&& GetEntityState) {
        // Important early out to prevent ever returning `HooksState::ALL` with no entries
        if (rng::empty(entities)) {
            return HooksState::NONE;
        }

        const auto nchangedToState = (size_t)(rng::count_if(entities, DoSetEntityState));
        if (nchangedToState == rng::size(entities)) { // All changed to requested state
            return newState
                ? HooksState::ALL
                : HooksState::NONE;
        } else { // Not all has changed, recalculate state manually
            return CalculateEntitesOverallState(std::forward<R>(entities), GetEntityState);
        }
    }

    /*!
    * @brief Set all our and sub-categories' items to the specified state.
    *
    * @param newState The new state of all items
    * @param notifyParent If the parent should be notified, this should be true only for the top-level call
    * 
    * @return If the overall state has changed of the category
    */
    bool SetAllItemsState_Internal(bool newState, bool notifyParent = true) {
        SetOurItemsState_Internal(newState);
        SetAllCategoriesState_Internal(newState);
        return ReCalculateOverallStateAndMaybeNotify(notifyParent); // It's enough if only we notify our parent
    }

    /*!
    * @brief Set state of all items at once. NOTE: `ReCalculateOverallStateAndMaybeNotify` has to be called after.
    * @param enabled New state of items
    */
    void SetOurItemsState_Internal(bool enabled) {
        m_itemsState = SetEntitiesState(m_items, m_itemsState, enabled,
            [
                enabled,
                expectedState = enabled ? HooksState::ALL : HooksState::NONE
            ](Item& item) {
                (void)item->State(enabled);
                return item->Hooked() == enabled;
            },
            &GetItemHookState
        );
    }

    /*!
    * @brief Set state of all sub-categories at once. NOTE: `ReCalculateOverallStateAndMaybeNotify` has to be called after.
    * 
    * @param enabled New state of the sub-categories
    */
    void SetAllCategoriesState_Internal(bool enabled) {
        m_subcatsState = SetEntitiesState(m_subCategories, m_subcatsState, enabled,
            [
                enabled,
                expectedState = enabled ? HooksState::ALL : HooksState::NONE
            ](HookCategory& cat) {
                (void)cat.SetAllItemsState_Internal(enabled, false);
                return cat.OverallState() == expectedState;
            },
            &HookCategory::OverallState
        );
    }

    /*!
    * @brief Recalculates overall state, and if changed, notifies parent.
    *
    * @param notifyParent If the parent should be notified of the state change
    * 
    * @return If the overall state has changed
    */
    bool ReCalculateOverallStateAndMaybeNotify(bool notifyParent = true) {
        const auto prev = m_overallState;

        m_overallState = [this] {
            if (m_items.empty()) {
                return m_subcatsState;
            }

            if (m_subCategories.empty()) {
                return m_itemsState;
            }

            if (m_subcatsState == m_itemsState) {
                return m_subcatsState; // Both equal, we can return either - Either both NONE or ALL
            }

            return HooksState::MIXED; // They differ 
        }();

        const bool changed = prev != m_overallState;

        if (notifyParent && changed) {
            if (m_parent) { // Now, notify parent (so they can update their state)
                m_parent->OnSubcategoryStateChanged(*this);
            }
        }

        return changed;
    }
    
    template<rng::input_range R, typename Fn>
    static HooksState CalculateEntitesOverallState(R&& entities, Fn&& GetEntityState) {
        size_t ninactive{}, nactive{}, ntotal{};

        for (auto&& e : entities) {
            switch (std::invoke(GetEntityState, e)) {
            case HooksState::NONE:
                ninactive++;
                break;
            case HooksState::ALL:
                nactive++;
                break;
            }
            ntotal++;
        }

        if (ninactive == ntotal || ntotal == 0) {
            return HooksState::NONE;
        } else if (nactive == ntotal) {
            return HooksState::ALL;
        } else {
            return HooksState::MIXED;
        }
    }

    /*!
    * @brief Helper function to recaulcate new state of entities when one item's state changes
    *
    * @param entities The entitites to process (Items or Categories)
    * @param currOverallState Current overall state of the entities
    * @param entityState The changed entity's state
    * @param isActivePred The function used to check if an entity is hooked (active) or not (should return true/false respectively)
    */
    // Helper function to recaulcate new state of collection when one item's state changes
    template<rng::input_range R, typename Fn>
    static HooksState CalculateEntitiesOverallStateOnEntryChange(R&& entities, HooksState entitiesOverallState, HooksState entityState, Fn&& GetEntityState) {
        if (entityState == entitiesOverallState) {
            return entitiesOverallState; // No changes
        }

        if (entitiesOverallState != HooksState::MIXED) { // All entities have the same state
            return HooksState::MIXED; // This entity has changed so the state must be mixed now
        }

        return CalculateEntitesOverallState(std::forward<R>(entities), std::forward<Fn>(GetEntityState));
    }

    // Called when a sub-category's overall state changes
    // (Will propagate to parent if it affected this category's overall state)
    void OnSubcategoryStateChanged(HookCategory& cat) {
        m_subcatsState = CalculateEntitiesOverallStateOnEntryChange(
            m_subCategories,
            m_subcatsState,
            cat.OverallState(),
            [](const HookCategory& c) { return c.OverallState(); }
        );
        ReCalculateOverallStateAndMaybeNotify();
    }

    // Not always called - Only when an individual item's state changes
    // Also not called if item is modified from the outside
    // (Currently only called by `AddItem` and `SetItemEnabled`, but not from `SetAllItemsEnabled`)
    void OnOneItemStateChange(const Item& item) {
        m_itemsState = CalculateEntitiesOverallStateOnEntryChange(
            m_items,
            m_itemsState,
            GetItemHookState(item),
            GetItemHookState
        );
        ReCalculateOverallStateAndMaybeNotify();
    }

    static HooksState GetItemHookState(const Item& i) {
        return i->Hooked()
            ? HooksState::ALL
            : HooksState::NONE;
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
    HooksState                m_itemsState{ HooksState::ALL };   // Collective state of all items (Can be ignored if `m_items.empty()` (In this case it's always NONE))
    HooksState                m_subcatsState{ HooksState::ALL }; // Collective state of all subcategories (Can be ignored if `m_subCategories.empty()` (In this case it's always NONE))
    HooksState                m_overallState{ HooksState::ALL }; // Overall state - Combination of the above 2 - Calculated by `ReCalculateOverallStateAndMaybeNotify`
    bool                      m_isVisible{true};                 // Updated each time the search box is updated. Indicates whenever we should be visible in the GUI.
    bool                      m_isOpen{};                        // Is our tree currently open
    bool                      m_triStateToggle{};                // Used by the UI when m_overallState is mixed to decide what the next state should be
    bool                      m_anyItemsVisible{true};           // Used when searching
    bool                      m_allCatsDisabled{true};           // Are all owned sub-categories disabled
    bool                      m_itemsDisabled{true};             // Are all owned items disabled
private:

    HookCategory*             m_parent{};        // Category we belong to - In case of `RootHookCategory` this is always `nullptr`.
    std::string               m_name{};          // Name of this category (Eg.: `Root`, `Global`, `Entity`, etc...)
    std::list<HookCategory>   m_subCategories{}; // Subcategories - It has to be a list, because we have links between categories
    std::vector<Item>         m_items{};         // Hooks in this category (`RootCategory` should have none) - TODO: IMHO we don't really need to use smart pointers - could just store the hooks as objects instead
};

}; // namespace ReversibleHooks 
