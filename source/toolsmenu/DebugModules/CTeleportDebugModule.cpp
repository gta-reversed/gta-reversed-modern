#include "StdInc.h"

#ifdef EXTRA_DEBUG_FEATURES
#include "CTeleportDebugModule.h"
#include "Utility.h"
#include "CDebugMenu.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <iterator>
#include <string>
#include <string_view>
#include <chrono>
#include "Radar.h"
#include "extensions/enumerate.hpp"

namespace rng = std::ranges;
using namespace ImGui;

struct SavedLocation {
    std::string name{};
    CVector     pos{};
    eAreaCodes  areaCode{ eAreaCodes::AREA_CODE_NORMAL_WORLD };
    bool        findGround{ true };
    bool        selected{};

    SavedLocation() = default;
    SavedLocation(const char* iName, CVector vec, eAreaCodes code, bool bFindGround) : name(iName), pos(vec), areaCode(code), findGround(bFindGround) {}
    SavedLocation(const char* iName, CVector vec) : name(iName), pos(vec) {}

    static constexpr size_t GetSaveSize() {
        return /*name*/30 + sizeof(pos) + sizeof(areaCode) + sizeof(findGround) + sizeof(selected);
    }
};

static std::vector<SavedLocation> s_SavedLocations{};
static bool                       s_findZGround{ true };
static SavedLocation              s_prevLocation{};
static char                       s_nameFilter[1024]{};

namespace TeleportDebugModule {

CVector GetPositionWithGroundHeight(const CVector2D& pos) {
    return { pos.x, pos.y, CWorld::FindGroundZForCoord(pos.x, pos.y) + 2.f };
}

// Teleport to exact coordinates
void TeleportTo(const CVector& pos, eAreaCodes areaCode) {
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

    CPedGroup* group = CPedGroups::GetPedsGroup(player);
    if (group) {
        auto& member = group->GetMembership();
        if (member.CountMembersExcludingLeader())
            group->Teleport(&pos);
    }
}

void DoTeleportTo(CVector pos, eAreaCodes areaCode = eAreaCodes::AREA_CODE_NORMAL_WORLD) {
    // Save previous location for teleporting back.
    s_prevLocation.pos = FindPlayerPed()->GetPosition();
    s_prevLocation.areaCode = FindPlayerPed()->m_nAreaCode;
    s_prevLocation.selected = true; // mark the position is saved.

    TeleportTo(pos, areaCode);
}

void ProcessImGui() {
    const auto& AlignRight = [&](float pad) {
        return GetWindowContentRegionMax().x - pad;
    };

    static CVector pos{};
    PushItemWidth(140.f);
    InputFloat3("Coords", reinterpret_cast<float(&)[3]>(pos), "%.3f"); // Kinda hacky, but it's okay, if this was to break, we'd have bigger problems anyways.
    PopItemWidth();

    static int areaCode{};
    PushItemWidth(30.f);
    SameLine(); InputInt("Area", &areaCode, 0);
    PopItemWidth();

    // Name input
    static char name[1024]{};
    PushItemWidth(AlignRight(CalcTextSize("Name").x + 275.0f));
    SameLine(); InputText("Name", name, std::size(name));
    PopItemWidth();

    Checkbox("Ground for Z", &s_findZGround);

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
            areaCode = AREA_CODE_NORMAL_WORLD;
            pos = CVector{ // todo: see CWorld::IsInWorldBounds
               CGeneral::GetRandomNumberInRange(-3072.0f, 3072.0f),
               CGeneral::GetRandomNumberInRange(-3072.0f, 3072.0f),
               0.0f
            };
        }
        else if (GetIO().KeyShift) { // Teleport to marker set on the map
            // Code from CLEO4 library
            auto hMarker = FrontEndMenuManager.m_nTargetBlipIndex;
            auto pMarker = &CRadar::ms_RadarTrace[LOWORD(hMarker)];

            if (hMarker && pMarker) {
                forceGround = true;
                areaCode = AREA_CODE_NORMAL_WORLD;
                pos = CVector{
                    pMarker->m_vPosition.x,
                    pMarker->m_vPosition.y,
                    0.0f
                };
            }
        }
        DoTeleportTo((s_findZGround || forceGround) ? GetPositionWithGroundHeight(pos) : pos, static_cast<eAreaCodes>(areaCode));
    }
    HoveredItemTooltip("Hold `ALT` to teleport to a random position\nHold `SHIFT` to teleport to marker marked on the map");

    // Save position button
    SameLine(AlignRight(36.0f));
    if (Button("Save", { 36.0f, 19.0f })) {
        const auto posToSave{ GetIO().KeyCtrl ? FindPlayerPed()->GetPosition() : GetPositionWithGroundHeight(pos) };
        const auto areaToSave{ GetIO().KeyCtrl ? FindPlayerPed()->m_nAreaCode : static_cast<eAreaCodes>(areaCode) };
        const auto nameToSave{ name[0] ? name : ((areaToSave == AREA_CODE_NORMAL_WORLD) ? CTheZones::GetZoneName(posToSave) : "<Unnamed>")};

        // Either use given name or current zone name
        s_SavedLocations.emplace(s_SavedLocations.begin(), nameToSave, posToSave, areaToSave, s_findZGround);

        if (!GetIO().KeyAlt) {
            name[0] = 0; // Clear input
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
        const std::string_view searchInputSV{ s_nameFilter };

        // Filter views stuff
        const auto IsItemVisible = [&](auto& l) { return searchInputSV.empty() || StringContainsString(l.name, searchInputSV, false); };
        const auto visibleFilter = std::views::filter(IsItemVisible);
        auto visibleItems = s_SavedLocations | visibleFilter;

        // Saved positions table
        if (BeginTable("Saved Positions", 5, ImGuiTableFlags_Resizable | ImGuiTableFlags_Reorderable | ImGuiTableFlags_BordersInnerH | ImGuiTableFlags_ScrollY)) {
            TableSetupColumn("Index", ImGuiTableColumnFlags_WidthFixed);
            TableSetupColumn("Name", ImGuiTableColumnFlags_WidthFixed);
            TableSetupColumn("Position", ImGuiTableColumnFlags_WidthFixed);
            TableSetupColumn("Area code", ImGuiTableColumnFlags_WidthFixed);
            TableSetupColumn("Ground", ImGuiTableColumnFlags_WidthFixed);
            TableHeadersRow();

            // Draw visible items
            for (auto it = visibleItems.begin(); it != visibleItems.end(); it++) {
                auto& v = *it;
                auto idx = std::distance(visibleItems.begin(), it) + 1;

                PushID(&v);
                BeginGroup();
                TableNextRow();
                TableNextColumn(); Text("%d", idx);

                if (TableNextColumn(); Selectable(v.name.c_str(), v.selected, ImGuiSelectableFlags_SpanAllColumns)) {
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
                    v.selected = true;
                }

                // Teleport on double click
                if (IsItemHovered() && IsMouseDoubleClicked(0)) {
                    DoTeleportTo(v.findGround ? GetPositionWithGroundHeight(v.pos) : v.pos, v.areaCode);
                }

                // Position text
                TableNextColumn();
                if (v.findGround)
                    Text("%.2f %.2f", v.pos.x, v.pos.y);
                else
                    Text("%.2f %.2f %.2f", v.pos.x, v.pos.y, v.pos.z);

                // Area code ID text
                TableNextColumn(); Text("%d %s", v.areaCode, (v.areaCode == AREA_CODE_NORMAL_WORLD) ? "(outside)" : "");

                // Ground text
                TableNextColumn(); Text("%s", v.findGround ? "Yes" : "No");

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
    }
}

void ProcessInput() {
    if (CDebugMenu::Visible() || !CPad::NewKeyState.lctrl)
        return;

    CPad* pad = CPad::GetPad(0);
    if (pad->IsStandardKeyJustDown('0') && s_prevLocation.selected)
        DoTeleportTo(s_prevLocation.pos, s_prevLocation.areaCode);

    // prepare filter stuff
    const std::string_view searchInputSV{ s_nameFilter };
    const auto IsItemVisible = [&](auto& l) { return searchInputSV.empty() || StringContainsString(l.name, searchInputSV, false); };
    const auto visibleFilter = std::views::filter(IsItemVisible);

    auto visibleItems = s_SavedLocations | visibleFilter;
    auto posIdx{-1};

    for (auto i = '1'; i < 'A'; i++) {
        if (pad->IsStandardKeyJustDown(i)) {
            posIdx = i - '1';
            break;
        }
    }
    if (posIdx == -1) return;

    for (auto&& [i, pos] : notsa::enumerate(visibleItems)) {
        if (i == posIdx) {
            DoTeleportTo(pos.findGround ? GetPositionWithGroundHeight(pos.pos) : pos.pos, pos.areaCode);
            break;
        }
    }
}

namespace SettingsHandler {
    // Clear all settings
    void ClearAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler) {
        UNUSED(ctx);
        UNUSED(handler);

        //s_SavedLocations.clear();
    }

    // Called after every read entry line
    // `entry` is a pointer returned from `ReadOpenFn` (we don't use it in this case)
    void ReadLine(ImGuiContext* ctx, ImGuiSettingsHandler* handler, void* entry, const char* line) {
        UNUSED(ctx);
        UNUSED(handler);

        const auto version = reinterpret_cast<int>(entry);
        char name[1024]{};
        CVector pos{};

        switch (version) {
        case 2: {
            int area{};
            int findGround{1};

            // [^\t\n] -> https://stackoverflow.com/questions/2854488
            if (sscanf(line, "%f, %f, %f, %d, %d, %[^\t\n]", &pos.x, &pos.y, &pos.z, &area, &findGround, name) == 6) {
                s_SavedLocations.emplace_back(name, pos, static_cast<eAreaCodes>(area), static_cast<bool>(findGround));
            } else if (line[0] && line[0] != '\n') { // Report failed reads on non-empty lines only
                std::cerr << "Failed to load saved location from ini: `" << line << "`\n";
            }
        } break;
        case 1: {
            if (sscanf(line, "%f, %f, %f, %[^\t\n]", &pos.x, &pos.y, &pos.z, name) == 4) {
                s_SavedLocations.emplace_back(name, pos);
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
    void WriteAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler, ImGuiTextBuffer* out_buf) {
        UNUSED(ctx);
        UNUSED(handler);

        out_buf->reserve(s_SavedLocations.size() * SavedLocation::GetSaveSize());
        out_buf->append("[SavedLocations][Version 2]\n");
        for (const auto& l : s_SavedLocations) {
            out_buf->appendf("%.3f, %.3f, %.3f, %d, %d, %s\n", l.pos.x, l.pos.y, l.pos.z, l.areaCode, l.findGround, l.name.c_str());
        }
    }

    void* ReadOpen(ImGuiContext* ctx, ImGuiSettingsHandler* handler, const char* name) {
        UNUSED(ctx);
        UNUSED(handler);

        int version{2};
        sscanf(name, "Version %d", &version);
        return (void*)version; // Has to return a non-null value, otherwise `ReadLine` won't be called
    }

    void ApplyAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler) {
        UNUSED(ctx);
        UNUSED(handler);

        if (s_SavedLocations.empty()) {
            s_SavedLocations = {
                { "Map centre", { 0.f,     0.f,      0.f   }, AREA_CODE_NORMAL_WORLD, true },
                { "CJ's House", { 2495.2f, -1686.0f, 13.6f }, AREA_CODE_NORMAL_WORLD, true },
                { "SF Airport", { 2495.1f, 1658.2f,  13.5f }, AREA_CODE_NORMAL_WORLD, true }
            };
        }
    }
}; // namespace SettingsHandler

void Initialise(ImGuiContext& ctx) {
    ImGuiSettingsHandler ini_handler;
    ini_handler.TypeName = "SavedLocations";
    ini_handler.TypeHash = ImHashStr("SavedLocations");
    ini_handler.ClearAllFn = SettingsHandler::ClearAll;
    ini_handler.ReadOpenFn = SettingsHandler::ReadOpen;
    ini_handler.ReadLineFn = SettingsHandler::ReadLine;
    ini_handler.ApplyAllFn = SettingsHandler::ApplyAll;
    ini_handler.WriteAllFn = SettingsHandler::WriteAll;
    ctx.SettingsHandlers.push_back(ini_handler);
}
}; // namespace TeleportDebugModule
#endif
