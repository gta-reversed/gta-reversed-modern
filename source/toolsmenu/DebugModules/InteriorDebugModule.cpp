#include <StdInc.h>
#include "InteriorDebugModule.h"
#include "InteriorManager_c.h"
using namespace ImGui;

static const char* TYPE_TEXT[] = {
    "SHOP", "OFFICE", "LOUNGE", "BEDROOM", "KITCHEN", "BATHROOM", "OFFLICENSE",
    "HOTELROOM", "MISC", "TESTROOM"
};

namespace notsa {
namespace debugmodules {
void Interior::RenderWindow() {
    const ::notsa::ui::ScopedWindow window{ "Interior", {}, m_IsOpen };
    if (!m_IsOpen) {
        return;
    }
    // Your window's content here

    BeginGroup();
    static int32 s_InteriorIdx{};
    InputInt("Interior index:", &s_InteriorIdx, 1, 1);
    s_InteriorIdx = std::clamp(s_InteriorIdx, 0, (int32)std::size(g_interiorMan.m_Interiors));

    auto& i = g_interiorMan.m_Interiors[s_InteriorIdx];

    if (i.m_ID) {
        Text("Interior ID: %d\nGroup: 0x%8x\nArea code: %d\n", i.m_ID, i.m_Group, i.m_AreaCode);

        auto& p = i.m_Props;
        if (p) {
            Text("Props:\nType: %s\nGroup ID: %d\nWidth: %d\nHeight: %d\nDepth: %d\n"
                 "Door: %d\n Seed: %d\nStatus: %d\nRot: %.2f",
                 p->m_IntType,
                 p->m_groupId,
                 p->m_width,
                 p->m_height,
                 p->m_depth,
                 p->m_door,
                 p->m_seed,
                 p->m_rot);
        } else {
            Text("Props: <nil>");
        }
    } else {
        Text("nil");
    }

    EndGroup();
}

void Interior::RenderMenuEntry() {
    notsa::ui::DoNestedMenuIL({ "Extra" }, [&] {
        ImGui::MenuItem("Interior", nullptr, &m_IsOpen);
    });
}
}; // namespace debugmodules
}; // namespace notsa
