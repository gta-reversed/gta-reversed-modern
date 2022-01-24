#pragma once

#include <imgui_internal.h>

//
// Dear ImGui tri-state checkbox - Based on https://github.com/ocornut/imgui/issues/2644#issuecomment-507023896
// Modified it a little for our needs
//

namespace ImGui {
    enum class ImTristate {
        ENABLED  = 1,
        DISABLED = 0,
        MIXED    = -1
    };

    // If `v_tristate` is `MIXED` and checkbox clicked: ENABLED
    // otherwise value is toggled (`ENABLED` -> `DISABLED` and `DISABLED` -> `ENABLED`)
    bool CheckboxTristate(const char* label, ImTristate& v_tristate)
    {
        bool ret;
        if (v_tristate == ImTristate::MIXED)
        {
            PushItemFlag(ImGuiItemFlags_MixedValue, true);
            bool b = false;
            ret = Checkbox(label, &b);
            if (ret)
                v_tristate = ImTristate::ENABLED;
            PopItemFlag();
        }
        else
        {
            bool b = (v_tristate != ImTristate::DISABLED);
            ret = Checkbox(label, &b);
            if (ret)
                v_tristate = b ? ImTristate::ENABLED : ImTristate::DISABLED;
        }
        return ret;
    }
};
