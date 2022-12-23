#pragma once

#include "Vehicle.h"
#include "CommandParser/Parser.hpp"

/*!
* Various CLEO car commands
*/

uint8 GetCarNumberOfGears(CVehicle& vehicle) {
    return vehicle.m_pHandlingData->m_transmissionData.m_nNumberOfGears;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_CAR_NUMBER_OF_GEARS, GetCarNumberOfGears);

uint8 GetCarCurrentGear(CVehicle& vehicle) {
    return vehicle.m_nCurrentGear;
}
REGISTER_COMMAND_HANDLER(COMMAND_GET_CAR_CURRENT_GEAR, GetCarNumberOfGears);

bool IsCarSirenOn(CVehicle& vehicle) {
    return vehicle.vehicleFlags.bSirenOrAlarm;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CAR_SIREN_ON, IsCarSirenOn);

bool IsCarEngineOn(CVehicle& vehicle) {
    return vehicle.vehicleFlags.bEngineOn;
}
REGISTER_COMMAND_HANDLER(COMMAND_IS_CAR_ENGINE_ON, IsCarEngineOn);

void SetCarEngineOn(CVehicle& vehicle, bool state) {
    vehicle.vehicleFlags.bEngineOn = state;
}
REGISTER_COMMAND_HANDLER(COMMAND_CLEO_SET_CAR_ENGINE_ON, SetCarEngineOn);

