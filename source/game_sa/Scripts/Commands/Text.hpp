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

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_BIG>() { // 0x0BA
    char label[8];
    ReadTextLabelFromScript(label, 8);
    auto text = TheText.Get(label);
    CollectParameters(2);
    CMessages::AddBigMessage(text, ScriptParams[0].iParam, (eMessageStyle)(ScriptParams[1].iParam - 1));
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT>() { // 0x0BB
    char label[8];
    ReadTextLabelFromScript(label, 8);
    auto text = TheText.Get(label);
    CollectParameters(2);
    if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessage(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
    return OR_CONTINUE;
}

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_PRINT_NOW>() { // 0x0BC
    char label[8];
    ReadTextLabelFromScript(label, 8);
    auto text = TheText.Get(label);
    CollectParameters(2);
    if (!text || text[0] != '~' || text[1] != 'z' || text[2] != '~' || FrontEndMenuManager.m_bShowSubtitles)
        CMessages::AddMessageJumpQ(text, ScriptParams[0].iParam, ScriptParams[1].iParam, CTheScripts::bAddNextMessageToPreviousBriefs);
    CTheScripts::bAddNextMessageToPreviousBriefs = true;
    return OR_CONTINUE;
}

void ClearThisPrintBigNow(int16 item) {
    CMessages::ClearThisPrintBigNow(static_cast<eMessageStyle>(ScriptParams[0].u16Param - 1));
}
REGISTER_COMMAND_HANDLER(COMMAND_CLEAR_THIS_PRINT_BIG_NOW, ClearThisPrintBigNow);

template<>
OpcodeResult CRunningScript::ProcessCommand<COMMAND_CLEAR_PRINTS>() { // 0x0BE
    CMessages::ClearMessages(false);
    return OR_CONTINUE;
}
