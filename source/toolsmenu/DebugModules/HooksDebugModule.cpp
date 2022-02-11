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
    std::string m_input{}; // Used as char buffer for the ImGUI input - Will only ever contain letters (a-zA-Z)

    // Contains `m_input`'s tokens split by `::`
    // If there was a trailing `::` an empty string is emplaced to the end
    std::vector<std::string_view> m_tokens{};

    void ClearFilters() {
        m_tokens.clear(); // Clear only, so capacity is kept
    }

    bool IsFilterActive() {
        return !m_tokens.empty();
    }

    bool IsHookFilterActive() {
        // If token after last the `::` is empty there's hook names aren't filtered
        return !m_tokens.back().empty();
    }

    bool UsingRootNamespace() {
        // If user entered `::...` an empty string will be inserted to the front, thus
        // if front is empty we should be using the root namespace, but if, and only if
        // there are exacly 2 tokens (left side should be the empty namespace filter, right side should be the non-empty name filter)
        return m_tokens.size() == 2 && m_tokens.front().empty();
    }

    auto GetCategoryNameMatchType(std::string_view catName, std::string_view token) {
        using enum RH::HookCategory::NameMatchType;

        if (catName.empty()) {
            return PARTIAL; // Gotta return `PARTIAL` in this case, otherwise global namespace and stuff wouldn't work
        }

        if (catName == token) {
            return FULL;
        } else if(catName.contains(token)) {
            return PARTIAL;
        } else {
            return NONE;
        }
    }

    auto GetHookNameToken() {
        return m_tokens.back(); // Always use last token for hook name filtering
    }

    void OnInputUpdate() {
        const std::string_view inputsv{ m_input };

        ClearFilters();

        if (inputsv.empty()) {
            return; // No filters
        }

        // We copy VS's CTRL + T behaviour. I'm lazy to explain it :D
        // Try it for yourself. There's a little code above for it, uncomment it.

        // Leading `::` - Search in global namespace, have to insert an empty string first
        /*if (inputsv.starts_with("::")) {
            m_tokens.emplace_back("");
        }*/

        for (auto t : SplitStringView(inputsv, "::")) {
            m_tokens.emplace_back(t);
        }

        if (m_tokens.size() < 2) { // If less than 2 tokens there was no `::`
            return;
        }

        // In case user passes in a string like `::::::` we will have quite a few empty strings
        // We have have to remove all the leading empty tokens up until the last empty one.
        // In the above case we'd have 3x empty strings, so we would like to remove 2
        // (So that 1 will remain to indicate the root/global namespace)
        while (m_tokens.size() >= 2 && m_tokens[0].empty() && m_tokens[1].empty()) {
            m_tokens.erase(m_tokens.begin());
        }

        // If there's a trailing `::` we must insert an empty string
        // This will indicate that the prev. token shoud be used as a namespace filter only.
        // (As hooks are always filtered by the last token)
        if (inputsv.ends_with("::")) {
            m_tokens.emplace_back("");
        }

        // If there are exactly 2 tokens and both sides are empty there's nothing to filter.
        if (m_tokens.size() == 2) { 
            if (rng::all_of(m_tokens, [](auto&& t) { return t.empty(); })) {
                ClearFilters();
                return;
            }
        }
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
    void MakeAllVisible(RH::HookCategory& cat, bool open = true) {
        cat.Visible(true);
        cat.Open(open);

        cat.m_anyItemsVisible = true;
        for (auto& i : cat.Items()) {
            i->m_isVisible = true;
        }

        for (auto& sc : cat.SubCategories()) {
            MakeAllVisible(sc, open);
        }
    }

    bool DoFilter_Internal(RH::HookCategory& cat, size_t depth = 0) {
        assert(!m_tokens.empty()); // Otherwise .size() - 1 will underflow

        using enum RH::HookCategory::VisibilityState;

        cat.Visible(false); // Set it explicitly to invisible, later the code will set it to Open if necessary.

        bool anySubCatsVisible{};
        for (auto& sc : cat.SubCategories()) {
            anySubCatsVisible |= DoFilter_Internal(sc, depth + 1);
        }

        if (!anySubCatsVisible) {
            if (!UsingRootNamespace()) {
                for (auto iterCat{ &cat }; auto&& token : m_tokens | rng::views::reverse | rng::views::drop(1)) {
                    if (token.empty()) { // Might happen for first or last token - It's fine.
                        continue;
                    }

                    if (!iterCat->Name().contains(token)) { // Couldn't statify all tokens
                        return false;
                    }

                    iterCat = iterCat->Parent();
                    if (!iterCat) { // Not enough parents to statisfy all tokens
                        return false; 
                    }
                }

                if (depth == m_tokens.size() - 1) {

                }
            }
        }

        if (IsHookFilterActive()) { // Filter items
            cat.m_anyItemsVisible = false;
            for (auto& i : cat.Items()) {
                i->m_isVisible = i->Name().contains(GetHookNameToken());
                cat.m_anyItemsVisible |= i->m_isVisible;
            }
        } else { // Otherwise make sure all items are visible
            cat.m_anyItemsVisible = true;
            for (auto& i : cat.Items()) {
                i->m_isVisible = true; 
            }
        }

        //if (UsingRootNamespace()) { // When root category is used only items are filtered, so make a category visible only if it has visible items
        //    assert(IsHookFilterActive()); // Must be active at this point (otherwise filter wouldn't be invoked)
        //    cat.Visible(cat.m_anyItemsVisible);
        //    return cat.m_anyItemsVisible;
        //} else {
        //}
        const bool visible = anySubCatsVisible || cat.m_anyItemsVisible;
        cat.Visible(visible);
        cat.Open(visible);
        return visible;
    }

    void DoFilter(RH::HookCategory& cat) {
        if (IsFilterActive()) {
            DoFilter_Internal(cat);
        } else {
            MakeAllVisible(cat);
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
