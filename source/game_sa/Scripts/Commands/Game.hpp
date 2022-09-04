#pragma once

#include "CommandParser/Parser.hpp"

/*!
* Various game realted commands
*/

void SetAllTaxisHaveNitro(bool enabled) {
    (enabled ? CCheat::ApplyCheat : CCheat::Disable)(CHEAT_ALL_TAXIS_NITRO);
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_ALL_TAXIS_HAVE_NITRO, SetAllTaxisHaveNitro);

