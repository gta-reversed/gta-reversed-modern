#pragma once
#include "Messages.h"
#include "Hud.h"
#include "CommandParser/Parser.hpp"

/*!
* Various text commands
*/

void ClearSmallPrints() {
    CMessages::ClearSmallMessagesOnly();
}
REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_SMALL_PRINTS, ClearSmallPrints);

void ClearHelp() {
    CHud::SetHelpMessage(nullptr, true, false, false);
}
REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_HELP, ClearHelp);

void FlashHudObject(eHudItem item) {
    CHud::m_ItemToFlash = item;
}
REGISTER_COMMAND_HANDLER(COMMAND_FLASH_HUD_OBJECT, FlashHudObject);

// NOTSA: time: int32 -> uint32
void PrintBig(const char* key, uint32 time, uint32 flags) {
    const auto text = TheText.Get(key);
    CMessages::AddBigMessage(text, time, static_cast<eMessageStyle>(flags - 1));
}
REGISTER_COMMAND_HANDLER(COMMAND_PRINT_BIG, PrintBig);

void Print(const char* key, uint32 time, uint32 flags) {
    const auto text = TheText.Get(key);
    if (!text || strncmp(text, "~z~", 3u) != 0 || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessage(text, time, flags, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
}
REGISTER_COMMAND_HANDLER(COMMAND_PRINT, Print);

void PrintNow(const char* key, uint32 time, uint32 flags) {
    const auto text = TheText.Get(key);
    if (!text || strncmp(text, "~z~", 3u) != 0 || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessageJumpQ(text, time, flags, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
}
REGISTER_COMMAND_HANDLER(COMMAND_PRINT_NOW, PrintNow);

void ClearThisPrintBigNow(uint16 item) {
    CMessages::ClearThisPrintBigNow(static_cast<eMessageStyle>(item - 1));
}
REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_THIS_PRINT_BIG_NOW, ClearThisPrintBigNow);

void ClearPrints() {
    CMessages::ClearMessages(false);
}
REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_PRINTS, ClearPrints);
