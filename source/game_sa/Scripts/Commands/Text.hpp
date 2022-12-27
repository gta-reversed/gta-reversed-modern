#pragma once
#include "Messages.h"
#include "Hud.h"
#include "CommandParser/Parser.hpp"

/*!
* Various text commands
*/

REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_SMALL_PRINTS, CMessages::ClearSmallMessagesOnly);

REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_HELP, []() { CHud::SetHelpMessage(nullptr, true, false, false); });

REGISTER_COMMAND_HANDLER(COMMAND_FLASH_HUD_OBJECT, [](eHudItem item) { CHud::m_ItemToFlash = item; });

// NOTSA: time: int32 -> uint32
REGISTER_COMMAND_HANDLER(COMMAND_PRINT_BIG, [](const char* key, uint32 time, uint32 flags) {
    const auto text = TheText.Get(key);
    CMessages::AddBigMessage(text, time, static_cast<eMessageStyle>(flags - 1));
});

REGISTER_COMMAND_HANDLER(COMMAND_PRINT, [](const char* key, uint32 time, uint32 flags) {
    const auto text = TheText.Get(key);
    if (!text || strncmp(text, "~z~", 3u) != 0 || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessage(text, time, flags, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
});

REGISTER_COMMAND_HANDLER(COMMAND_PRINT_NOW, [](const char* key, uint32 time, uint32 flags) {
    const auto text = TheText.Get(key);
    if (!text || strncmp(text, "~z~", 3u) != 0 || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessageJumpQ(text, time, flags, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
});

REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_THIS_PRINT_BIG_NOW, [](uint16 item) { CMessages::ClearThisPrintBigNow(static_cast<eMessageStyle>(item - 1)); });

REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_PRINTS, []() { CMessages::ClearMessages(false); });
