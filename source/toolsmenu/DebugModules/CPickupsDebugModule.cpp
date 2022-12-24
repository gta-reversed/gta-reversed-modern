#include "StdInc.h"

#include "CPickupsDebugModule.h"
#include "CTeleportDebugModule.h"

#include "imgui.h"
#include "Pickup.h"
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

using namespace ImGui;

int16 DrawTable(bool filterInvisible, bool filterInactive) {
    if (!BeginTable("Pickups", 6, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_ScrollY)) {
        return -1;
    }
    TableSetupColumn("Id", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Type", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Model Id", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Visible", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Revenue Value", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Ammo", ImGuiTableColumnFlags_WidthFixed);
    TableHeadersRow();

    static int16 selectedPickupId{-1};

    for (const auto& [i, pickup] : notsa::enumerate(CPickups::aPickUps)) {
        if (filterInvisible && !pickup.IsVisible() || filterInactive && pickup.m_nPickupType == PICKUP_NONE) {
            continue;
        }

        PushID(i);
        BeginGroup();
        TableNextRow();

        TableNextColumn();
        Text("%d", i);

        if (TableNextColumn(); Selectable(PICKUP_TYPES_NAME_MAP.at(pickup.m_nPickupType).c_str(), selectedPickupId == i, ImGuiSelectableFlags_SpanAllColumns)) {
            selectedPickupId = i;
        }

        // Teleport on double click
        if (IsItemHovered() && IsMouseDoubleClicked(0)) {
            TeleportDebugModule::TeleportTo(pickup.GetPosn(), FindPlayerPed()->m_nAreaCode);
        }

        TableNextColumn();
        Text("%d", pickup.m_nModelIndex);

        TableNextColumn();
        TextUnformatted(pickup.m_nFlags.bVisible ? "T" : "F");

        TableNextColumn();
        if (pickup.m_fRevenueValue != 0.0f) {
            Text("%.2f", pickup.m_fRevenueValue);
        } else {
            Text("-");
        }

        TableNextColumn();
        if (pickup.m_nAmmo != 0u) {
            Text("%u", pickup.m_nAmmo);
        } else {
            Text("-");
        }

        EndGroup();
        PopID();
    }
    EndTable();

    return selectedPickupId;
}

void CPickupsDebugModule::RenderMainWindow() {
    BeginGroup();

    static int16 selectedPickup = -1;
    if (selectedPickup != -1) {
        static bool markSelectedPickup = true;
        Checkbox("Mark selected pickup", &markSelectedPickup);

        const auto& pickup = CPickups::aPickUps[selectedPickup];

        Text("ID: %d", selectedPickup);

        const auto posn = pickup.GetPosn();
        Text("Coords: %.2f %.2f %.2f", posn.x, posn.y, posn.z);

        if (Button("Teleport Player")) {
            TeleportDebugModule::TeleportTo(posn);
        }

        if (markSelectedPickup) {
            CVector screenCoors{};
            if (CalcScreenCoors(posn, &screenCoors)) {
                CSprite2d::DrawRect({screenCoors, 5.0f}, pickup.m_nFlags.bDisabled ? CRGBA{255, 0, 0, 255} : CRGBA{0, 255, 0, 255});
            }
        }
    }

    Separator();
    static bool filterInactive = true, filterInvisible = false;
    Checkbox("Hide inactive (i.e. type=NONE)", &filterInactive);
    SameLine();
    Checkbox("Hide invisible", &filterInvisible);

    EndGroup();

    selectedPickup = DrawTable(filterInvisible, filterInactive);
}

CPickupsDebugModule::CPickupsDebugModule() :
    DebugModuleSingleWindow{ "Pickups", {400.f, 600.f} }
{
}

void CPickupsDebugModule::RenderMenuEntry() {
    if (ImGui::BeginMenu("Extra")) {
        if (ImGui::MenuItem("Pickups")) {
            SetMainWindowOpen(true);
        }
        ImGui::EndMenu();
    }
}
