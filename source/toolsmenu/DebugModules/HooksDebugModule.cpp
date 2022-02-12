#include "StdInc.h"

#include <reversiblehooks/RootHookCategory.h>
#include "HooksDebugModule.h"
#include "Utility.h"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <TristateCheckbox.h>
#include <string>
#include <ranges>
#include <optional>

namespace RH = ReversibleHooks;
namespace rng = std::ranges;
using namespace ImGui;

// TODO: Comment this out. Used to experiment with VS's CTRL + T behaviour
namespace lvl1 {
    void fn1();
    namespace lvl2 {
        void fn2();
        void lvl2fn();
        namespace lvl3 {
            void fn3();

            namespace lvl4 {
                void fn4();

                namespace noname {

                };
            };

            namespace noname {

            };
        };
        namespace noname {

        };
    };
};

namespace Entity {
    namespace Vehicle {
        namespace Automobile {

        };
    };
};

// Matches must be in order. It doesn't matter if a sub-category in-between doesn't match
// Eg.:
// - `lvl::noname` will match both `lvl1::lvl2::noname` and `lvl1::lvl2::lvl3::noname`
// - `lvl::lvl::noname` will still match both
// - `lvl::lvl::lvl::noname` will only match `lvl1::lvl2::lvl3::noname`
// Last token is always used for matching namespace/function (in our case hook) names
// if last token is empty just ignore it in the case of functions, but take into account for
// namespaces.
// Eg.: `lvl1` should show all functions/namespaces with the name containing `lvl1`, but
// `lvl1::` should only show children/functions of namespaces whose name contains `lvl`
// If a sub-category in-between doesn't match don't show it's functions, but only namespaces that match
// Eg.: `lvl2::lvl` should only show 

static std::string HooksFilterContent;
struct FilterTool {
    static constexpr std::string_view HOOKNAME_SEP{ "::" };
    static constexpr std::string_view NAMESPACE_SEP{ "/" };

    std::string m_input{};          // Used as char buffer for the ImGUI input - Will only ever contain letters (a-zA-Z)
    bool        m_caseSensitive{};

    // Contains `m_input`'s tokens split by `::`
    // If there was a trailing `::` an empty string is emplaced to the end
    std::vector<std::string_view> m_namespaceTokens{};

    std::string_view m_hookFilter{}; // Filter of function name

    void ClearFilters() {
        m_namespaceTokens.clear(); // Clear only, so allocated memory is kept
        m_hookFilter = {};
    }

    bool IsFilterActive() {
        return !m_namespaceTokens.empty() || !m_hookFilter.empty();
    }

    bool IsNamespaceFilterActive() {
        return !m_namespaceTokens.empty();
    }

    bool IsHookFilterActive() {
        return !m_hookFilter.empty();
    }

    bool IsBaseRootNamespace() {
        return m_namespaceTokens.size() >= 1 && m_namespaceTokens.front().empty();
    }

    void OnInputUpdate() {
        const std::string_view inputsv{ m_input };

        ClearFilters();

        if (inputsv.empty()) {
            return; // No filters
        }

        // We copy VS's CTRL + T behaviour. I'm lazy to explain it :D
        // Try it for yourself. There's a little code above for it, uncomment it.

        {   
            const auto sepPos = inputsv.rfind(HOOKNAME_SEP);

            // First half contains the namespace filter tokens
            for (auto t : SplitStringView(inputsv.substr(0, sepPos), NAMESPACE_SEP)) {
                m_namespaceTokens.emplace_back(t);
            }

            // Second half (if any) contains the hook/function name filter
            if (sepPos != std::string_view::npos) {
                m_hookFilter = inputsv.substr(sepPos + HOOKNAME_SEP.size());
            }
        }


        //if (m_namespaceTokens.size() < 2) { // If less than 2 tokens there was no `NAMESPACE_SEP` - That's fine.
        //    return;
        //}

        // In case user passes in a string with multiple `NAMESPACE_SEP` with nothing inbetween we will have quite a few empty tokens.
        // We have have to remove all the leading empty tokens up until the last empty one.
        while (m_namespaceTokens.size() >= 2 && m_namespaceTokens[0].empty() && m_namespaceTokens[1].empty()) {
            m_namespaceTokens.erase(m_namespaceTokens.begin());
        }

        // If we're using the root namespace only but there's no hook filter we paractically dont't filter anything
        // Example user inputs: `/`, `/::`, `::`
        if (IsBaseRootNamespace() && m_namespaceTokens.size() == 1 && !IsHookFilterActive()) {
            ClearFilters();
        }

        //// If there are exactly 2 tokens and both sides are empty there's nothing to filter.
        //if (m_namespaceTokens.size() == 2) { 
        //    if (rng::all_of(m_namespaceTokens, [](auto&& t) { return t.empty(); })) {
        //        ClearFilters();
        //        return;
        //    }
        //}
    }

    void ProcessImGui() {
        // Required to disallow spaces and other stuff - Makes processing input significiantly easier.
        const auto AlphaOnlyFilter = [](ImGuiInputTextCallbackData* data) {
            return std::isalpha((uint8_t)data->EventChar);
        };

        PushItemWidth(GetWindowContentRegionMax().x - 10.f);
        if (InputText(" ", &m_input, 0, AlphaOnlyFilter)) {
            OnInputUpdate();
            DoFilter(RH::GetRootCategory());
        }
        PopItemWidth();
    }

    // Make all sub-categories and items visible again
    void MakeAllVisibleAndOpen(RH::HookCategory& cat, bool open) {
        cat.Visible(true);
        cat.Open(open);

        cat.m_anyItemsVisible = true;
        for (auto& i : cat.Items()) {
            i->m_isVisible = true;
        }

        for (auto& sc : cat.SubCategories()) {
            MakeAllVisibleAndOpen(sc, open);
        }
    }

    std::pair<bool, bool> DoFilter_Internal(RH::HookCategory& cat, size_t depth = 0) {
        //assert(!m_namespaceTokens.empty()); // Otherwise .size() - 1 will underflow

        // Will be set to the appropriate values on return
        cat.Visible(false);
        cat.Open(false);

        // Process all sub-categories, and return if any category is pair<visible, open>
        const auto ProcessSubCategories = [&, this] {
            bool anyVisible{}, anyOpen{};
            for (auto& sc : cat.SubCategories()) {
                const auto [visible, open] = DoFilter_Internal(sc, depth + 1);
                anyVisible |= visible;
                anyOpen |= open;
            }
            return std::make_pair(anyVisible, anyOpen);
        };

        // If `doFilter` argument is `false` all items are set visible, and `false` is returned
        // otherwise items are filtered and true if returned if at least 1 item is visible.
        const auto ProcessItems = [&](bool doFilter) {
            if (doFilter) { // Filter items
                cat.m_anyItemsVisible = false;
                for (auto& i : cat.Items()) {
                    i->m_isVisible = StringContainsString(i->Name(), m_hookFilter, m_caseSensitive);
                    cat.m_anyItemsVisible |= i->m_isVisible;
                }
                return cat.m_anyItemsVisible;
            } else { // Otherwise make sure all items are visible
                if (cat.Items().empty()) { // No items, make sure flag is set correctly.
                    cat.m_anyItemsVisible = false;
                } 

                cat.m_anyItemsVisible = true;
                for (auto& i : cat.Items()) {
                    i->m_isVisible = true; 
                }
                return true;
            }
        };

        // When using root namespace our visibility is decided by our sub-categories' items and our items, if none of them are visible we aren't either,
        // otherwise current filters also impact our visibility.
        if (IsNamespaceFilterActive()) {
            if (IsBaseRootNamespace()) {
                const auto ProcessFilter = [&, this]() -> std::pair<bool, bool> {
                    if (depth == 0) { // Special case - Root namespace depth, no need to check any tokens
                        assert(m_namespaceTokens.front().empty()); // This codepath should be unreachable unless first token is empty
                        return { true, true }; // Root should always be opened
                    } else if (depth < m_namespaceTokens.size()) {
                        return { StringContainsString(cat.Name(), m_namespaceTokens[depth], m_caseSensitive), true };
                    } else { // Our parents fully matched the tokens, they just want to make us visible, but not open
                        //assert(cat.Parent()->Visible()); // Should be unreachable unless parent is visible at this point
                        return { true, false };
                    }
                };

                const auto [byFilterVisible, byFilterOpen] = ProcessFilter();
                if (!byFilterVisible) {
                    return {};
                }

                const auto [anySCVisible, anySCOpen] = ProcessSubCategories();
                if (!byFilterVisible && !anySCVisible) {
                    return {};
                }

                (void)ProcessItems(depth + 1 == m_namespaceTokens.size()); // Only filter bottom level namespace's functions

                const bool open    = anySCOpen || byFilterOpen;
                const bool visible = open || anySCVisible || byFilterVisible;

                cat.Visible(visible);
                cat.Open(open);

                return { visible, open };
            } else {
                const auto ProcessFilter = [&, this]() -> bool {
                    // Not in the root namespace
                    // All tokens should match in order reverse order starting at us, eg.:
                    // Entity::Ped::CPed
                    //              <This is `cat`>
                    // So, in order to be visible, `cat`s name should contain `CPed`
                    // it's parent's name should contain `Ped` and it's parent's name should contain `Entity`

                    // Parents: Root-Entity-Ped-CPed
                    // Depth:   0     1       2    3   <= Also number of tokens
                    // Tokens:        Entity::Ped::CPed
                    if (depth < m_namespaceTokens.size()) { // Not enough categories to possibly staisfy all tokens
                        return false;
                    }

                    for (auto iterCat{ &cat }; auto&& token : m_namespaceTokens | rng::views::reverse) {
                        if (!StringContainsString(iterCat->Name(), token, m_caseSensitive)) { // Couldn't statify all tokens - Remember: `contains` always returns true if `token.empty()`
                            return false;
                        }
                        iterCat = iterCat->Parent();
                    }

                    return true;
                };

                const auto byFilterVisible = ProcessFilter();
                const auto itemsVisible = ProcessItems(byFilterVisible);
                const auto [anySCVisible, anySCOpen] = ProcessSubCategories();

                const bool open    = anySCOpen || byFilterVisible || (byFilterVisible && (anySCVisible || itemsVisible));
                const bool visible = open || byFilterVisible || anySCVisible;

                /*if (cat.Name() == "CAudioEngine") {
                    __debugbreak();
                }*/

                cat.Visible(visible);
                cat.Open(open);

                return { visible, open };
            }
;       } else {
            // Filter hook names

            const auto itemsVisible = ProcessItems(true);
            const auto [anySCVisible, anySCOpen] = ProcessSubCategories();

            // We should be open if we have visible items, or any of our
            // sc's is open (otherwise that sc wouldn't appear to the user)
            const auto open = itemsVisible || anySCOpen;

            const bool visible = open || anySCVisible;

            cat.Visible(visible);
            cat.Open(open);

            return {visible, open};
        }
    }

    void DoFilter(RH::HookCategory& cat) {
        if (IsFilterActive()) {
            DoFilter_Internal(cat);
        } else {
            MakeAllVisibleAndOpen(cat, false); // Make all visible, but closed
        }        
    }
} s_HookFilter;

bool IsFiltered() {
    return !HooksFilterContent.empty();
}

void RenderCategory(RH::HookCategory& cat) {
    if (!cat.Visible()) {
        return;
    }

    PushID(&cat); // NOTE: Won't work properly if `cat::m_items`s type is changed from `std::list`

    const auto& name = cat.Name();

    const auto TreeNodeWithCheckbox = [](auto label, ImTristate triState, bool& cbStateOut, bool& cbClicked, bool& open) {
        // TODO/NOTE: The Tree's label is a workaround for when the label is shorter than the visual checkbox (otherwise the checkbox can't be clicked)
        open = TreeNodeEx("##         ", ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanFullWidth);

        SameLine();

        // Checkbox + it's label will be the tree name
        cbClicked = CheckboxTristate(label, triState, cbStateOut);
    };

    bool isCategoryOpen{};

    // Disable all hooks in category at once
    {
        SetNextItemOpen(cat.Open());

        bool cbClicked{};
        bool cbState{};
        TreeNodeWithCheckbox(cat.Name().c_str(), cat.OverallState(), cbState, cbClicked, isCategoryOpen);
        if (cbClicked) {
            cat.SetAllItemsEnabled(cbState);
        }

        cat.Open(isCategoryOpen);

        // Save state if we haven't overwrote it
        /*if (!IsFiltered()) {
            cat.m_isCategoryOpen = isCategoryOpen;
        }*/
    }

    // Draw hooks, and subcategories
    if (isCategoryOpen) {
        // Draw hooks (if any)
        if (!cat.Items().empty()) {
            const auto DrawItems = [&] {
                for (auto& item : cat.Items()) {
                    if (!item->m_isVisible) {
                        continue;
                    }

                    PushID(item.get()); // Use hook's address as unique ID - Hooks aren't dynamically created, so this should really be unique

                    // Draw hook symbol (`S` or `V`)
                    {
                        PushStyleVar(ImGuiStyleVar_Alpha, GetStyle().Alpha * 0.5f);
                        AlignTextToFramePadding();
                        Text(item->Symbol());
                        PopStyleVar();
                    }

                    // State checkbox
                    {
                        PushID("state");
                        bool hooked{ item->Hooked() };
                        if (SameLine(); Checkbox(item->Name().c_str(), &hooked)) {
                            cat.SetItemEnabled(item, hooked);
                        }
                        PopID(); // State checkbox
                    }

                    PopID(); // This hook
                }
            };

            if (cat.SubCategories().empty()) { // If there are no subcategories we can draw all items directly
                DrawItems();
            } else { // Otherwise use a tree node + checkbox
                bool hooksNodeOpen{};
                bool cbState{};
                bool cbClicked{};
                TreeNodeWithCheckbox("Hooks", cat.ItemsState(), cbState, cbClicked, hooksNodeOpen);
                if (cbClicked) {
                    cat.SetOurItemsEnabled(cbState);
                }
                if (hooksNodeOpen) {
                    DrawItems();
                    TreePop();
                }
            }
        }

        // Draw subcategories
        for (auto& v : cat.SubCategories()) {
            RenderCategory(v);
        }

        TreePop();
    }

    PopID();
}

namespace HooksDebugModule {
void ProcessImGui() {
    s_HookFilter.ProcessImGui();

    if (BeginChild("##hookstool")) {
        RenderCategory(RH::GetRootCategory());
        EndChild();
    }
}

void ProcessRender() {
}
};
