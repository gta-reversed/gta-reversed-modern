#pragma once
#include "Ped.h"
#include "CommandParser/Parser.hpp"
/*!
* Various ped commands
*/

REGISTER_COMMAND_HANDLER(COMMAND_SET_DEATH_WEAPONS_PERSIST, [](CPed& ped, bool enable) { ped.bDeathPickupsPersist = enable; });

REGISTER_COMMAND_HANDLER(COMMAND_IGNORE_HEIGHT_DIFFERENCE_FOLLOWING_NODES, [](CPed& ped, bool ignore) { ped.bIgnoreHeightDifferenceFollowingNodes = ignore; });

REGISTER_COMMAND_HANDLER(COMMAND_SHUT_ALL_CHARS_UP, [](bool disable) {
    (disable ? CAEPedSpeechAudioEntity::DisableAllPedSpeech : CAEPedSpeechAudioEntity::EnableAllPedSpeech)();
});

REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR, [](CPed& ped, bool enable) { ped.bGetOutUpsideDownCar = enable; });
