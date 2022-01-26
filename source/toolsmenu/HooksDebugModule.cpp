#include "StdInc.h"

#include "HooksDebugModule.h"
#include <imgui.h>
#include <imgui_stdlib.h>
#include <TristateCheckbox.h>
#include <string>

namespace rng = std::ranges;
using namespace ImGui;

// https://stackoverflow.com/a/19839371
// TODO: When #85 is merged remove this
bool findStringCaseInsensitive(const std::string& strHaystack, const std::string& strNeedle) {
    auto it = std::search(
        strHaystack.begin(), strHaystack.end(),
        strNeedle.begin(), strNeedle.end(),
        [](char ch1, char ch2) { return std::toupper(ch1) == std::toupper(ch2); }
    );
    return (it != strHaystack.end());
}

namespace HooksDebugModule {
void ProcessImGui() {
    static std::string HooksFilterContent;

    PushItemWidth(GetWindowContentRegionMax().x - 10.f);
    const bool reclaimFocus = InputText(" ", &HooksFilterContent, ImGuiInputTextFlags_EnterReturnsTrue);
    PopItemWidth();

    // Auto-focus on window apparition
    SetItemDefaultFocus();
    if (reclaimFocus)
        SetKeyboardFocusHere(-1); // Auto focus previous widget

    if (!BeginChild("##hookstool")) {
        EndChild();
        return;
    }

    AlignTextToFramePadding();
    
    const auto& allHooks = ReversibleHooks::GetAllHooks();

    // Buttons for disabling/enabling all hooks at once
    {

        const auto SwitchAllButton = [&](auto toState, auto btnText, auto tooltipTxt) {
            PushID(btnText); // Should be fine

            if (SameLine(); Button(btnText)) {
                for (auto& [clsName, clsHooks] : allHooks) {
                    for (auto& hook : clsHooks) {
                        hook->SetState(toState);
                    }
                }
            }

            if (IsItemHovered())
                SetTooltip(tooltipTxt);

            PopID();
        };

        SwitchAllButton(true, "Enable all", "Enable all hooks matching search criteria");
        SwitchAllButton(false, "Disable all", "Disable all hooks matching search criteria");
    }

    // Draw all hooks matching filter requirements
    for (auto& [clsName, clsHooks] : allHooks) {
        if (!HooksFilterContent.empty() && !findStringCaseInsensitive(clsName, HooksFilterContent))
            continue;

        PushID(clsName.c_str());

        // TODO: Cache this value somewhere, for now we have to do it this way
        ImTristate state{};
        const auto IsHookEnabled = [](auto& h) { return h->m_bIsHooked; };
        if (rng::any_of(clsHooks, IsHookEnabled)) {
            state = rng::all_of(clsHooks, IsHookEnabled) ? ImTristate::ENABLED : ImTristate::MIXED;
        } else {
            state = ImTristate::DISABLED;
        }

        // TODO/NOTE: The Tree's label is a workaround for a class's name being shorter than the visual checkbox (otherwise the checkbox can't be clicked)
        const bool treeOpen = TreeNodeEx("##         ", ImGuiTreeNodeFlags_AllowItemOverlap | ImGuiTreeNodeFlags_FramePadding | ImGuiTreeNodeFlags_SpanFullWidth);
        
        // Draw tree name + checkbox for it
        if (SameLine(); CheckboxTristate(clsName.c_str(), state)) {
            for (auto& hook : clsHooks) {
                hook->SetState(state == ImTristate::ENABLED); // Change state of all hooks to new state (which at this point is either ENABLED or DISABLED)
            }
        }

        if (treeOpen) {
            for (auto& hook : clsHooks) {
                PushID(hook.get()); // Use hook's address as unique ID - Hooks aren't dynamically created, so this should really be unique

                // Draw hook type (`S` - simple or `V` - virtual)
                {
                    PushStyleVar(ImGuiStyleVar_Alpha, GetStyle().Alpha * 0.5f);
                    AlignTextToFramePadding();
                    Text(hook->m_eHookType == eReversibleHookType::Simple ? "S" : "V");
                    PopStyleVar();
                }

                // State checkbox
                {
                    PushID("State");
                    if (SameLine(); Checkbox(hook->m_sFunctionName.c_str(), &hook->m_bImguiHooked)) {
                        hook->SetState(hook->m_bImguiHooked); // Checkbox pressed, so switch hook to new state
                    }
                    PopID(); // State checkbox
                }
                PopID(); // This hook
            }
            TreePop();
        }
        PopID(); // ClassName
    }
    EndChild();
}

void ProcessRender() {
}
};
