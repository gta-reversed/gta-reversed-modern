#include "StdInc.h"

#include "CPickupsDebugModule.h"

#include "imgui.h"
#include "Pickups.h"

// std::unordered_map<uint8, std::string>
constexpr struct { ePickupType type; std::string_view name; } PICKUP_TYPES_NAME_MAP[] = {
    { PICKUP_NONE,                     "NONE",                     },
    { PICKUP_IN_SHOP,                  "IN_SHOP",                  },
    { PICKUP_ON_STREET,                "ON_STREET",                },
    { PICKUP_ONCE,                     "ONCE",                     },
    { PICKUP_ONCE_TIMEOUT,             "ONCE_TIMEOUT",             },
    { PICKUP_ONCE_TIMEOUT_SLOW,        "ONCE_TIMEOUT_SLOW",        },
    { PICKUP_COLLECTABLE1,             "COLLECTABLE1",             },
    { PICKUP_IN_SHOP_OUT_OF_STOCK,     "IN_SHOP_OUT_OF_STOCK",     },
    { PICKUP_MONEY,                    "MONEY",                    },
    { PICKUP_MINE_INACTIVE,            "MINE_INACTIVE",            },
    { PICKUP_MINE_ARMED,               "MINE_ARMED",               },
    { PICKUP_NAUTICAL_MINE_INACTIVE,   "NAUTICAL_MINE_INACTIVE",   },
    { PICKUP_NAUTICAL_MINE_ARMED,      "NAUTICAL_MINE_ARMED",      },
    { PICKUP_FLOATINGPACKAGE,          "FLOATINGPACKAGE",          },
    { PICKUP_FLOATINGPACKAGE_FLOATING, "FLOATINGPACKAGE_FLOATING", },
    { PICKUP_ON_STREET_SLOW,           "ON_STREET_SLOW",           },
    { PICKUP_ASSET_REVENUE,            "ASSET_REVENUE",            },
    { PICKUP_PROPERTY_LOCKED,          "PROPERTY_LOCKED",          },
    { PICKUP_PROPERTY_FORSALE,         "PROPERTY_FORSALE",         },
    { PICKUP_MONEY_DOESNTDISAPPEAR,    "MONEY_DOESNTDISAPPEAR",    },
    { PICKUP_SNAPSHOT,                 "SNAPSHOT",                 },
    { PICKUP_2P,                       "2P",                       },
    { PICKUP_ONCE_FOR_MISSION,         "ONCE_FOR_MISSION",         }
};

namespace CPickupsDebugModule {

void ProcessImGui() {
    using namespace ImGui;

    if (Button("Hide All")) {
        for (auto& pickup : CPickups::aPickUps) {
            pickup.m_nFlags.bVisible = false;
        }
    }
    if (Button("Show All")) {
        for (auto& pickup : CPickups::aPickUps) {
            pickup.m_nFlags.bVisible = true;
            // pickup.m_nFlags.bDisabled = false;
        }
    }

    if (ImGui::BeginTable("Pickups Near Player", 1, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)) {
        for (auto i = 0; auto& pickup : CPickups::aPickUps) {
            if (!pickup.m_pObject)
                continue;

            ImGui::PushID(i);

            const auto posn = UncompressLargeVector(pickup.m_vecPos);
            ImGui::TableNextColumn();
            Text("%.2f %.2f %.2f", posn.x, posn.y, posn.z);

            ImGui::PopID();
            i++;
        }
        ImGui::EndTable();
    }

    if (ImGui::BeginTable("Pickups", 5, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders)) {
        for (auto i = 0; auto& pickup : CPickups::aPickUps) {
            ImGui::PushID(i);

            ImGui::TableNextColumn(); Text("#%d", i);

            const auto posn = UncompressLargeVector(pickup.m_vecPos);
            ImGui::TableNextColumn(); Text("%.2f %.2f %.2f", posn.x, posn.y, posn.z);

            ImGui::TableNextColumn();
            if (Button("Teleport")) { // todo: see CStreamingDebugModule (refactor)
                CStreaming::LoadSceneCollision({posn.x, posn.y, 100.f});
                FindPlayerPed()->Teleport({posn.x, posn.y, CWorld::FindGroundZForCoord(posn.x, posn.y) + 2.f}, true);
            }

            ImGui::TableNextColumn();
            Text("%d", pickup.m_nFlags.bVisible);

            ImGui::TableNextColumn();
            if (Button("Change Visibility")) {
                pickup.m_nFlags.bVisible ^= true;
            }

            ImGui::PopID();
            i++;
        }
        ImGui::EndTable();
    }
}

void ProcessRender() {

}

};
