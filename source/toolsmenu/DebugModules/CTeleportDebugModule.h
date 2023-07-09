#pragma once

#include "DebugModule.h"
#include "Utility.h"

struct ImGuiSettingsHandler;

class TeleportDebugModule : public DebugModule {
public:
    void OnImGuiInitialised(ImGuiContext* ctx) override;
    void RenderWindow() override;
    void RenderMenuEntry() override;
    void Update() override;

    //! Teleport player [and it's group] to the exact position
    static void TeleportTo(CVector pos, eAreaCodes areaCode = eAreaCodes::AREA_CODE_NORMAL_WORLD);

    //! Similar to `TeleportTo`, but finds the ground position
    static void TeleportToGround(CVector2D pos, eAreaCodes areaCode = eAreaCodes::AREA_CODE_NORMAL_WORLD);

private:
    void DoTeleportTo(CVector pos, eAreaCodes areaCode);
    void RenderSavedPositions();
    void RenderTeleporterWindow();
    auto GetVisibleItems() {
        return s_SavedLocations | rng::views::filter(
                 [
                     filter = std::string_view{ s_nameFilter }
                 ](auto& l) {
                     return filter.empty() || StringContainsString(l.name, filter, false);
                 }
            );
    }

    void AddSettingsHandler(ImGuiContext* ctx);
    static void Settings_ReadLine(ImGuiContext* ctx, ImGuiSettingsHandler* handler, void* entry, const char* line);
    static void Settings_WriteAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler, ImGuiTextBuffer* out_buf);
    static void Settings_ApplyAll(ImGuiContext* ctx, ImGuiSettingsHandler* handler);

    void ProcessShortcuts();
private:
    struct SavedLocation {
        SavedLocation() = default;

        SavedLocation(const char* name, CVector pos, eAreaCodes code, bool bFindGround) :
            name(name),
            pos(pos),
            areaCode(code),
            findGround(bFindGround)
        {
        }

        SavedLocation(const char* name, CVector pos) :
            name(name),
            pos(pos)
        {
        }

        //! Size of serialized text data [in bytes]
        size_t GetTextSerializedSize() {
            return name.size() + sizeof(pos) * 3 * 8 + sizeof(areaCode) * 4 + sizeof(findGround) * 4;
        }

    public:
        std::string name{};
        CVector     pos{};
        eAreaCodes  areaCode{ eAreaCodes::AREA_CODE_NORMAL_WORLD };
        bool        findGround{ true };
        bool        selected{};
    };

private:
    bool                       m_isOpen{false};
    bool                       m_isVisible{};
    std::vector<SavedLocation> s_SavedLocations{};
    bool                       s_findZGround{ true };
    SavedLocation              s_prevLocation{};
    char                       s_nameFilter[256]{};

    // UI Input stuff
    struct {
        char    name[256]{};
        CVector pos{};
        int     areaCode{};
    } m_input;
};
