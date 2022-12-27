#pragma once
#include "MenuManager.h"
#include "Pad.h"
#include "CommandParser/Parser.hpp"
using namespace notsa::script;
/*!
* Various player pad commands
*/

REGISTER_COMMAND_HANDLER(COMMAND_IS_BUTTON_PRESSED, [](CRunningScript& S, int16 playerIndex, eButtonId button) {
    return S.GetPadState(playerIndex, button) && !CPad::GetPad(0)->JustOutOfFrontEnd;
});

REGISTER_COMMAND_HANDLER(COMMAND_GET_PC_MOUSE_MOVEMENT, ([]() -> MultiRet<float, float> {
    // TODO(izzotop): check ASM
    return {CPad::NewMouseControllerState.X, CPad::NewMouseControllerState.Y};
}));

REGISTER_COMMAND_HANDLER(COMMAND_IS_PC_USING_JOYPAD, []() { return FrontEndMenuManager.m_nController != 0; });

REGISTER_COMMAND_HANDLER(COMMAND_IS_MOUSE_USING_VERTICAL_INVERSION, []() { return CMenuManager::bInvertMouseY != 0; });

REGISTER_COMMAND_HANDLER(COMMAND_HAS_GAME_JUST_RETURNED_FROM_FRONTEND, []() { return CPad::GetPad(0)->JustOutOfFrontEnd; });
