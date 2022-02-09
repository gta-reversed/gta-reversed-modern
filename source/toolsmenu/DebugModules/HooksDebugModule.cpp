#include "StdInc.h"

#include <reversiblehooks/RootHookCategory.h>
#include "HooksDebugModule.h"
#include "Utility.h"

#include <imgui.h>
#include <imgui_stdlib.h>
#include <TristateCheckbox.h>
#include <string>
#include <ranges>

namespace RH = ReversibleHooks;
namespace rng = std::ranges;
using namespace ImGui;


static std::string HooksFilterContent;

// Applies current filter on the given category (first call should always be the root)
// Returns if the given category is visible or not
// A category is visible if either:
// - Any of it's subcategories are visible
// - It's matches the search criteria
bool ApplyFilterToCategory(RH::HookCategory& cat) {
    bool anySubCatsVisible{};
    for (auto& v : cat.SubCategories()) {
        if (ApplyFilterToCategory(v)) {
            anySubCatsVisible = true;
        }
    }
    cat.m_isVisible = anySubCatsVisible || HooksFilterContent.empty() || findStringCaseInsensitive(cat.Name(), HooksFilterContent);
    return cat.m_isVisible;
}

void RenderCategory(RH::HookCategory& cat) {
    if (!cat.m_isVisible) {
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
        SetNextItemOpen(HooksFilterContent.empty() ? cat.m_isCategoryOpen : true); // When the search tool is in use open all tree nodes

        bool cbClicked{};
        bool cbState{};
        TreeNodeWithCheckbox(cat.Name().c_str(), cat.OverallState(), cbState, cbClicked, isCategoryOpen);
        if (cbClicked) {
            cat.SetAllItemsEnabled(cbState);
        }
    }

    // Draw hooks, and subcategories
    if (isCategoryOpen) {
        // Draw hooks (if any)
        if (!cat.Items().empty()) {
            const auto DrawItems = [&] {
                for (auto& item : cat.Items()) {
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
    // Search tool input
    {
        PushItemWidth(GetWindowContentRegionMax().x - 10.f);
        if (InputText(" ", &HooksFilterContent)) {
            // Auto-focus on window apparition
            //SetItemDefaultFocus();
            //if (filterChanged)
            //    SetKeyboardFocusHere(-1); // Auto focus previous widget

            // Re-apply filter 
            ApplyFilterToCategory(RH::GetRootCategory());
        }
        PopItemWidth();
    }

    if (BeginChild("##hookstool")) {
        RenderCategory(RH::GetRootCategory());
        EndChild();
    }
}

void ProcessRender() {
}
};
