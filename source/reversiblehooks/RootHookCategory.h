#pragma once

#include "HookCategory.h"
#include <string_view>

namespace ReversibleHooks {

// For simplicity we have a `Root` category, which contains all other categories (even `Global`)
// There shouldn't be more than one root category
// Root category shouldn't contain any items (This is a small design issue tbh - For now: don't add items to it, just categories(to which you add items))
class RootHookCategory : public HookCategory {
public:
    RootHookCategory() :
        HookCategory{ RH_RootCategoryName, nullptr } // Root has no parent
    {
        m_isCategoryOpen = true; // Root should be opened by default
    }

    RootHookCategory(const RootHookCategory&) = delete;
    RootHookCategory(RootHookCategory&&)      = delete; 

    // `category` - A `/` separated category list - Eg.: `Entity/Ped` (The hook should be added to the `Entity` category's `Ped` sub-category)
    void AddItemToNamedCategory(std::string_view category, Item hook) {
        assert(!category.empty()); // Should never be empty. To add to global category use `RH_ScopedCategoryGlobal()`

        HookCategory* cat = this; // Start with us (the root category)

        for (auto it = category.begin();;) {
            const auto next = std::find(it, category.end(), '/');
            const auto off = (size_t)(it - category.begin());
            if (next == category.end()) {
                cat = &cat->FindOrCreateSubcategory(category.substr(off));
                break;
            } else {
                cat = &cat->FindOrCreateSubcategory(category.substr(off, (size_t)(next - category.begin()) - off));
                it = next + 1; // `+ 1` to skip separator
            }
        }

        //  TODO: Use this instead, once shit CI is fixed.
        //for (const auto& catName : category | rng::views::split('/')) {
        //    cat = &cat->FindOrCreateSubcategory(catName); // Find/create all sub-categories - TODO: C++23 - Use string_view range constructor here
        //}

        assert(cat != this); // Make sure item doesn't get added into us (As the root category should have no items)
        cat->AddItem(std::move(hook)); // The last category is where we add the item to
    }
};

}; // namespace ReversibleHooks 
