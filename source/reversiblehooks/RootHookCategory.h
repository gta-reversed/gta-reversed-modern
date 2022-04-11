#pragma once

#include "HookCategory.h"
#include <string_view>
#include "Utility.h"

namespace ReversibleHooks {

// For simplicity we have a `Root` category, which contains all other categories (even `Global`)
// There shouldn't be more than one root category
// Root category shouldn't contain any items (This is a small design issue tbh - For now: don't add items to it, just categories(to which you add items))
class RootHookCategory : public HookCategory {
public:
    RootHookCategory() :
        HookCategory{ RH_RootCategoryName, nullptr } // Root has no parent
    {
        m_isOpen = true; // Root should be opened by default
    }

    RootHookCategory(const RootHookCategory&) = delete;
    RootHookCategory(RootHookCategory&&)      = delete; 

    /*!
    * @brief Get category (if it doesn't exist create it) according to \a categoryPath
    * @returns The last category in \a categoryPath
    * 
    * @param categoryPath A `/` separated category list - Eg.: `Entity/Ped` (The hook should be added to the `Entity` category's `Ped` sub-category).
    */
    auto FindCategoryForItem(std::string_view categoryPath) {
        assert(!categoryPath.empty()); // Should never be empty. To add to global category use `RH_ScopedCategoryGlobal()`

        HookCategory* cat = this; // Start with us (the root category)

        for (auto&& catName : SplitStringView(categoryPath, "/")) {
            cat = &cat->FindOrCreateSubcategory(catName);
        }

        assert(cat != this); // Make sure item doesn't get added into us (As the root category should have no items)
        return cat;
    }

    void AddItemToNamedCategory(std::string_view categoryPath, Item hook) {
        FindCategoryForItem(categoryPath)->AddItem(std::move(hook)); // The last category is where we add the item to
    }
};

}; // namespace ReversibleHooks 
