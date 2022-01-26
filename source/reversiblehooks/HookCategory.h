#pragma once

#include "ReversibleHooks.h"
#include "SReversibleHook.h"

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

    explicit HookCategory(std::string name) :
        m_name{ std::move(name) }
    {
    }

    const void  AddItem(Item item)      { m_items.emplace_back(std::move(item)); }
    const auto& Name()            const { return m_name; }
    const auto& SubCategories()   const { return m_subCategories; }
    const auto& Items()           const { return m_items; }

    Item FindItem(std::string_view name) {
        const auto it = rng::find_if(m_items, [&](const auto& c) { return c->Name() == name; });
        return it == m_items.end() ? nullptr : *it;
    }

    // `name` - Name of category
    HookCategory* FindSubcategory(std::string_view name) {
        const auto it = rng::find_if(m_subCategories, [&](const auto& c) { return c.Name() == name; });
        return it == m_subCategories.end() ? nullptr : &*it;
    }

    auto& FindOrCreateSubcategory(std::string_view name) {
        if (auto cat = FindSubcategory(name))
            return *cat; // Return found
        return m_subCategories.emplace_back(name); // Create it
    }

    // Iterates over all items, including those in subcategories
    // Make sure the function doesn't add/remove items/sub-categories!
    // (Underlaying storages are vectors, which don't like being modifies while they're being iterated over)
    template<typename Fn>
    void ForEachItem(Fn fn) {
        for (auto& item : m_items) {
            std::invoke(fn, item);
        }
        for (auto& cat : m_subCategories) {
            cat.ForEachItem(fn);
        }
    }

    template<typename Fn>
    void ForEachItem(Fn fn) const {
        for (const auto& item : m_items) {
            std::invoke(fn, item);
        }
        for (const auto& cat : m_subCategories) {
            cat.ForEachItem(fn);
        }
    }

private:
    std::string               m_name{};          // Name of this category (Eg.: `Root`, `Global`, `Entity`)
    std::vector<HookCategory> m_subCategories{}; // Subcategories       
    std::vector<Item>         m_items{};         // Hooks in this category (`RootCategory` should have none)
};

}; // namespace ReversibleHooks 
