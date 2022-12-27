#pragma once
#include "Ped.h"
#include "CommandParser/Parser.hpp"
/*!
* Various ped commands
*/

void SetDeathWeaponPersist(CPed& ped, bool enable) {
    ped.bDeathPickupsPersist = enable;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_DEATH_WEAPONS_PERSIST, SetDeathWeaponPersist);

void IgnoreHeightDifferenceFollowingNodes(CPed& ped, bool ignore) {
    ped.bIgnoreHeightDifferenceFollowingNodes = ignore;
}
REGISTER_COMMAND_HANDLER(COMMAND_IGNORE_HEIGHT_DIFFERENCE_FOLLOWING_NODES, IgnoreHeightDifferenceFollowingNodes);

void ShutAllCharsUp(bool disable) {
    (disable ? CAEPedSpeechAudioEntity::DisableAllPedSpeech : CAEPedSpeechAudioEntity::EnableAllPedSpeech)();
}
REGISTER_COMMAND_HANDLER(COMMAND_SHUT_ALL_CHARS_UP, ShutAllCharsUp);

void SetCharGetOutUpsideDownCar(CPed& ped, bool enable) {
    ped.bGetOutUpsideDownCar = enable;
}
REGISTER_COMMAND_HANDLER(COMMAND_SET_CHAR_GET_OUT_UPSIDE_DOWN_CAR, SetCharGetOutUpsideDownCar);
