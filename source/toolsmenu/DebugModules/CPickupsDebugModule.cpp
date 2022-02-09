#include "StdInc.h"

#include "CPickupsDebugModule.h"
#include "CTeleportDebugModule.h"

#include "imgui.h"
#include "Pickups.h"
#include "extensions/enumerate.hpp"

using namespace ImGui;

const std::unordered_map<ePickupType, std::string> PICKUP_TYPES_NAME_MAP = {
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

void DrawTable(auto& pickups) {
    if (ImGui::BeginTable("Pickups", 6, ImGuiTableFlags_Resizable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders | ImGuiTableFlags_Sortable)) {
        ImGui::TableNextColumn(); ImGui::TableHeader("Id");
        ImGui::TableNextColumn(); ImGui::TableHeader("Type");
        ImGui::TableNextColumn(); ImGui::TableHeader("Model Id");
        ImGui::TableNextColumn(); ImGui::TableHeader("Visible");
        ImGui::TableNextColumn(); ImGui::TableHeader("Revenue Value");
        ImGui::TableNextColumn(); ImGui::TableHeader("Ammo");

        for (const auto& [i, pickup] : enumerate(pickups)) {
            ImGui::PushID(i);

            ImGui::TableNextColumn(); Text("%d", i);
            ImGui::TableNextColumn(); Text("%s", PICKUP_TYPES_NAME_MAP.at(pickup.m_nPickupType).c_str());
            ImGui::TableNextColumn(); Text("%d", pickup.m_nModelIndex);
            ImGui::TableNextColumn(); Text("%d", pickup.m_nFlags.bVisible);
            ImGui::TableNextColumn(); Text("%.2f", pickup.m_fRevenueValue);
            ImGui::TableNextColumn(); Text("%d", pickup.m_nAmmo);

            ImGui::PopID();
        }
    ImGui::EndTable();
    }
}

void ProcessImGui() {
    if (Button("Hide All")) {
        for (auto& pickup : CPickups::aPickUps) {
            pickup.m_nFlags.bVisible = false;
        }
    }
    SameLine();
    if (Button("Show All")) {
        for (auto& pickup : CPickups::aPickUps) {
            pickup.m_nFlags.bVisible = true;
            // pickup.m_nFlags.bDisabled = false;
        }
    }

    {
        BeginGroup();
        CPickup* pickup = &CPickups::aPickUps[12];

        std::ptrdiff_t index = pickup - CPickups::aPickUps.data(); // !sue
        Text("Id %d", index);

        const auto posn = UncompressLargeVector(pickup->m_vecPos);
        Text("Position %.2f %.2f %.2f", posn.x, posn.y, posn.z);
        if (Button("Teleport")) TeleportDebugModule::TeleportTo(posn);

        SameLine(); if (Button("Change Visibility")) pickup->m_nFlags.bVisible ^= true;

        EndGroup();
    }

    if (ImGui::BeginTabBar("Pickups")) {
        if (ImGui::BeginTabItem("All")) {
            DrawTable(CPickups::aPickUps);
            ImGui::EndTabItem();
        }

        auto IsVisible = [](CPickup& pickup) { return pickup.m_pObject; };
        auto filteredPickups = CPickups::aPickUps | std::views::filter(IsVisible);

        if (ImGui::BeginTabItem("Near Player")) {
            DrawTable(filteredPickups);
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
}

void ProcessRender() {

}

};
