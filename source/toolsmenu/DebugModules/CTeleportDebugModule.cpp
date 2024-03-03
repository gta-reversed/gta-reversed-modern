#include "StdInc.h"

#include "CTeleportDebugModule.h"
#include "Utility.h"
#include "UIRenderer.h"
#include "DebugModule.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <iterator>
#include <string>
#include <string_view>
#include <chrono>
#include "Radar.h"
#include "extensions/enumerate.hpp"

using namespace ImGui;

void TeleportDebugModule::RenderMenuEntry() {
    if (BeginMenu("Tools")) {
        if (MenuItem("Teleporter")) {
            m_isOpen = true;
        }
        ImGui::EndMenu();
    }
}

void TeleportDebugModule::RenderWindow() {
    if (m_isOpen) {
        if (Begin("Teleporter", &m_isOpen)) {
            SetNextWindowSize({ 415.f, 290.f }, ImGuiCond_FirstUseEver);
            RenderTeleporterWindow();
        }
        End();
    }
}

void TeleportDebugModule::Update() {
    ProcessShortcuts();
}

void TeleportDebugModule::OnImGuiInitialised(ImGuiContext* ctx) {
    AddSettingsHandler(ctx);
}

static CVector GetPositionWithGroundHeight(const CVector2D& pos) {
    return { pos.x, pos.y, CWorld::FindGroundZForCoord(pos.x, pos.y) + 2.f };
}

// Teleport to exact coordinates
void TeleportDebugModule::TeleportTo(const CVector& pos, eAreaCodes areaCode) {
    CStreaming::LoadSceneCollision(pos);
    CStreaming::LoadScene(pos);

    auto player = FindPlayerPed();
    player->m_nAreaCode = areaCode;
    CGame::currArea = areaCode;
    CStreaming::RemoveBuildingsNotInArea(areaCode);
    CTimeCycle::StopExtraColour(false);

    if (auto vehicle = FindPlayerVehicle()) {
        vehicle->Teleport(pos, true);
    } else {
        player->Teleport(pos, true);
    }

    // Teleport player's group too
    if (auto group = CPedGroups::GetPedsGroup(player)) {
        if (group->GetMembership().CountMembersExcludingLeader()) {
            group->Teleport(&pos);
        }
    }
}

void TeleportDebugModule::DoTeleportTo(CVector pos, eAreaCodes areaCode) {
    // Save previous location for teleporting back.
    s_prevLocation.pos      = FindPlayerPed()->GetPosition();
    s_prevLocation.areaCode = FindPlayerPed()->m_nAreaCode;
    s_prevLocation.selected = true; // mark the position is saved.

    TeleportDebugModule::TeleportTo(pos, areaCode);
}

void TeleportDebugModule::RenderSavedPositions() {
    auto visibleItems = GetVisibleItems();

    if (!BeginTable("Saved Positions", 5, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_ScrollY)) {
        return;
    }

    TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Position", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Area code", ImGuiTableColumnFlags_WidthFixed);
    TableSetupColumn("Ground", ImGuiTableColumnFlags_WidthFixed);

    TableHeadersRow();

    // Draw visible items
    for (auto it = visibleItems.begin(); it != visibleItems.end(); it++) {
        auto& item = *it;

        PushID(&item);
        BeginGroup();

        TableNextRow();
        TableNextColumn();

        Text("%d", std::distance(visibleItems.begin(), it) + 1); // Index

        if (TableNextColumn(); Selectable(item.name.c_str(), item.selected, ImGuiSelectableFlags_SpanAllColumns)) {
            // Here we implement the common Windows like select stuff
            // Shift held  - Select everything in-between previous selected and this
            // CTRL  held  - Mark this as selected, but don't unselect others
            // no modifier - Usual behaviour, mark this as selected, but unselect others

            if (GetIO().KeyShift) { // Select all visible items in-between
                const auto other = rng::find_if(visibleItems, [](auto& l) { return l.selected; }); // Find other selected
                if (other != visibleItems.end()) {
                    const auto [b, e] = std::minmax(other, it, [](auto ai, auto bi) {return ai.base() < bi.base(); });
                    rng::for_each(b, e, [](auto& l) { l.selected = true; }); // Select all in-between
                }
            } else if (!GetIO().KeyCtrl) { // Unselect all others
                rng::for_each(s_SavedLocations, [](auto& l) { l.selected = false; });
            }
            item.selected = true;
        }

        // Teleport on double click
        if (IsItemHovered() && IsMouseDoubleClicked(0)) {
            DoTeleportTo(item.findGround ? GetPositionWithGroundHeight(item.pos) : item.pos, item.areaCode);
        }

        // Position text
        TableNextColumn();
        if (item.findGround)
            Text("%.2f %.2f", item.pos.x, item.pos.y);
        else
            Text("%.2f %.2f %.2f", item.pos.x, item.pos.y, item.pos.z);

        // Area code ID text
        TableNextColumn(); Text("%d %s", item.areaCode, (item.areaCode == AREA_CODE_NORMAL_WORLD) ? "(outside)" : "");

        // Ground text
        TableNextColumn(); Text("%s", item.findGround ? "Yes" : "No");

        EndGroup();
        PopID();
    }

    EndTable();

    // Selected item deletion
    if (GetIO().KeysDown[VK_DELETE]) {
        const auto [b, e] = rng::remove_if(visibleItems, [](auto& l) { return l.selected; });
        s_SavedLocations.erase(b.base(), e.base());
    }
}

void TeleportDebugModule::RenderTeleporterWindow() {
    const auto& AlignRight = [&](float pad) {
        return GetWindowContentRegionMax().x - pad;
    };

    PushItemWidth(140.f);
    InputFloat3("Coords", reinterpret_cast<float(&)[3]>(m_input.pos), "%.3f");
    PopItemWidth();

    PushItemWidth(30.f);
    SameLine(); InputInt("Area", &m_input.areaCode, 0);
    PopItemWidth();

    PushItemWidth(AlignRight(CalcTextSize("Name").x + 275.0f));
    SameLine(); InputText("Name", m_input.name, std::size(m_input.name));
    PopItemWidth();

    Checkbox("Z = Ground Z", &s_findZGround);

    // Helper to draw tooltip over hovered item
    const auto HoveredItemTooltip = [](auto text) {
        if (IsItemHovered()) {
            BeginTooltip();
            TextUnformatted(text);
            EndTooltip();
        }
    };

    // Teleport button
    SameLine(AlignRight(64.0f + 9.0f + 36.0f)); // [teleport] + space + [save]
    if (Button("Teleport", { 64.0f, 19.0f })) {
        // Not finding ground for Z doesn't make sense with the two. So do it anyways.
        bool forceGround = false;

        if (GetIO().KeyAlt) { // Random position
            forceGround = true;
            m_input.areaCode = AREA_CODE_NORMAL_WORLD;
            m_input.pos = CVector{ // todo: see CWorld::IsInWorldBounds
               CGeneral::GetRandomNumberInRange(-3072.0f, 3072.0f),
               CGeneral::GetRandomNumberInRange(-3072.0f, 3072.0f),
               0.0f
            };
        } else if (GetIO().KeyShift) { // Teleport to marker set on the map
            // Code from CLEO4 library
            auto hMarker = FrontEndMenuManager.m_nTargetBlipIndex;
            auto pMarker = &CRadar::ms_RadarTrace[LOWORD(hMarker)];

            if (hMarker && pMarker) {
                forceGround = true;
                m_input.areaCode = AREA_CODE_NORMAL_WORLD;
                m_input.pos = CVector{
                    pMarker->m_vPosition.x,
                    pMarker->m_vPosition.y,
                    0.0f
                };
            }
        }
        DoTeleportTo(
            (s_findZGround || forceGround)
                ? GetPositionWithGroundHeight(m_input.pos)
                : m_input.pos,
            static_cast<eAreaCodes>(m_input.areaCode)
        );
    }
    HoveredItemTooltip("Hold `ALT` to teleport to a random position\nHold `SHIFT` to teleport to marker marked on the map");

    // Save position button
    SameLine(AlignRight(36.0f));
    if (Button("Save", { 36.0f, 19.0f })) {
        const auto posToSave{ GetIO().KeyCtrl ? FindPlayerPed()->GetPosition() : GetPositionWithGroundHeight(m_input.pos) };
        const auto areaToSave{ GetIO().KeyCtrl ? FindPlayerPed()->m_nAreaCode : static_cast<eAreaCodes>(m_input.areaCode) };
        const auto nameToSave{ m_input.name[0] ? m_input.name : ((areaToSave == AREA_CODE_NORMAL_WORLD) ? GxtCharToUTF8(CTheZones::GetZoneName(posToSave)) : "<Unnamed>")};

        // Either use given name or current zone name
        s_SavedLocations.emplace(s_SavedLocations.begin(), nameToSave, posToSave, areaToSave, s_findZGround);

        if (!GetIO().KeyAlt) {
            m_input.name[0] = 0; // Clear input
        }
    }
    HoveredItemTooltip("Hold `ALT` to prevent name input from getting cleared\nHold `CTRL` to save current position");

    // Current position display
    {
        const auto pos = FindPlayerCoors();
        Text("Current Pos: %.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
        if (SameLine(); Button("Copy")) {
            char buf[256];
            sprintf_s(buf, "%.3f, %.3f, %.3f", pos.x, pos.y, pos.z);
            SetClipboardText(buf);
        }
    }


    if (!s_SavedLocations.empty()) {
        // Search tool input
        PushItemWidth(AlignRight(CalcTextSize("Search").x + 11.0f));
        InputText("Search", s_nameFilter, std::size(s_nameFilter), ImGuiInputTextFlags_CharsUppercase | ImGuiInputTextFlags_AutoSelectAll);

        // Finally, render saved positions
        RenderSavedPositions();
    }
}

//
// Settings saving/loading
//

// Called after every read entry line
void TeleportDebugModule::Settings_ReadLine(ImGuiContext* ctx, ImGuiSettingsHandler* handler, void* entry, const char* line) {
    UNUSED(ctx);

    const auto self    = (TeleportDebugModule*)handler->UserData;
    const auto version = reinterpret_cast<int>(entry);

    char name[1024]{};
    CVector pos{};

    switch (version) {
    case 2: {
        int area{};
        int findGround{1};

        // [^\t\n] -> https://stackoverflow.com/questions/2854488
        if (sscanf_s(line, "%f, %f, %f, %d, %d, %[^\t\n]", &pos.x, &pos.y, &pos.z, &area, &findGround, SCANF_S_STR(name)) == 6) {
            self->s_SavedLocations.emplace_back(name, pos, static_cast<eAreaCodes>(area), static_cast<bool>(findGround));
        } else if (line[0] && line[0] != '\n') { // Report failed reads on non-empty lines only
            std::cerr << "Failed to load saved location from ini: `" << line << "`\n";
        }
    } break;
    case 1: {
        if (sscanf_s(line, "%f, %f, %f, %[^\t\n]", &pos.x, &pos.y, &pos.z, SCANF_S_STR(name)) == 4) {
            self->s_SavedLocations.emplace_back(name, pos);
        } else if (line[0] && line[0] != '\n') {
            std::cerr << "Failed to load saved location from ini: `" << line << "`\n";
        }
        break;
    }
    default:
        std::cerr << "Invalid teleport tool version: " << version << std::endl;
        break;
    }
}

// Write all settings to buffer (ini file)
void TeleportDebugModule::Settings_WriteAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler, ImGuiTextBuffer* out_buf) {
    UNUSED(ctx);

    const auto self = (TeleportDebugModule*)handler->UserData;

    out_buf->reserve(std::accumulate(self->s_SavedLocations.begin(), self->s_SavedLocations.end(), 0, [](int a, auto& sl) { return a + (int)sl.GetTextSerializedSize(); }));
    out_buf->append("[SavedLocations][Version 2]\n");
    for (const auto& l : self->s_SavedLocations) {
        out_buf->appendf("%.3f, %.3f, %.3f, %d, %d, %s\n", l.pos.x, l.pos.y, l.pos.z, l.areaCode, l.findGround, l.name.c_str());
    }
}

void TeleportDebugModule::Settings_ApplyAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler) {
    UNUSED(ctx);

    const auto self = (TeleportDebugModule*)handler->UserData;

    // Add some default locations
    if (self->s_SavedLocations.empty()) {
        self->s_SavedLocations = {
            { "Map centre", { 0.f,     0.f,      0.f   }, AREA_CODE_NORMAL_WORLD, true },
            { "CJ's House", { 2495.2f, -1686.0f, 13.6f }, AREA_CODE_NORMAL_WORLD, true },
            { "SF Airport", { 2495.1f, 1658.2f,  13.5f }, AREA_CODE_NORMAL_WORLD, true }
        };
    }
}

void TeleportDebugModule::ProcessShortcuts() { 
    if (GetIO().MouseDrawCursor) { // Cursor visible => Ignore
        return;
    }

    const auto pad = CPad::GetPad(0);

    // Key `0` is previous location, so teleport to it (if set)
    if (pad->IsStandardKeyJustDown('0') && s_prevLocation.selected) {
        DoTeleportTo(s_prevLocation.pos, s_prevLocation.areaCode);
    }

    // Keys `1` - `9` are saved locations (Corresponding to the nth (currently) visible location (in the table))
    for (auto k = 0; k < 9; k++) {
        if (!pad->IsStandardKeyJustDown('1' + k)) {
            continue;
        }

        // Find `i`th visible element and teleport to it
        for (auto&& [itemIdx, loc] : notsa::enumerate(GetVisibleItems())) {
            if (k == itemIdx) {
                DoTeleportTo(loc.findGround ? GetPositionWithGroundHeight(loc.pos) : loc.pos, loc.areaCode);
                break;
            }
        }

        return;
    }
}

void ClearAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler) {
    UNUSED(ctx);
    UNUSED(handler);
}

void* ReadOpen(ImGuiContext* ctx, ImGuiSettingsHandler* handler, const char* name) {
    UNUSED(ctx);
    UNUSED(handler);

    int version{2};
    VERIFY(sscanf_s(name, "Version %d", &version) == 1);
    return (void*)version; // Has to return a non-null value, otherwise `ReadLine` won't be called
}

void TeleportDebugModule::AddSettingsHandler(ImGuiContext* ctx) {
    ImGuiSettingsHandler ih;
    ih.TypeName   = "SavedLocations";
    ih.TypeHash   = ImHashStr("SavedLocations");
    ih.ClearAllFn = ClearAll;
    ih.ReadOpenFn = ReadOpen;
    ih.ReadLineFn = Settings_ReadLine;
    ih.ApplyAllFn = Settings_ApplyAll;
    ih.WriteAllFn = Settings_WriteAll;
    ih.UserData = this;
    ctx->SettingsHandlers.push_back(ih);
}
