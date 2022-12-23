#pragma once
#include "CommandParser/Parser.hpp"

/*!
* Various CLEO game commands
*/

bool IsGameVersionOriginal() {
    return false;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_GAME_VERSION_ORIGINAL, IsGameVersionOriginal);
