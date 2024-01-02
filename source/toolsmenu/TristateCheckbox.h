#pragma once

#include <imgui_internal.h>

//
// Dear ImGui tri-state checkbox - Based on https://github.com/ocornut/imgui/issues/2644#issuecomment-507023896
// Modified it a little for our needs
//

namespace ImGui {
    enum class ImTristate {
        ALL   = 1,
        NONE  = 0,
        MIXED = -1
    };

    static bool CheckboxTristate(const char* label, ImTristate v_tristate, bool& state)
    {
        state = v_tristate == ImTristate::ALL;

        bool clicked;
        if (v_tristate == ImTristate::MIXED)
        {
            PushItemFlag(ImGuiItemFlags_MixedValue, true);
            clicked = Checkbox(label, &state);
            PopItemFlag();
        }
        else
        {
            clicked = Checkbox(label, &state);
        }
        return clicked;
    }
};
