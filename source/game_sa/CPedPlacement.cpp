/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool CPedPlacement::FindZCoorForPed(CVector* pos) {
    return plugin::CallAndReturnDynGlobal<bool, CVector*>(0x616920, pos);
}

bool CPedPlacement::IsPositionClearForPed(CVector const* pos, float radius, int maxNumObjects, CEntity** pObjectList, unsigned char bCheckVehicles, unsigned char bCheckPeds, unsigned char bCheckObjects) {
    return plugin::CallAndReturnDynGlobal<bool, CVector const*, float, int, CEntity**, unsigned char, unsigned char, unsigned char>(0x616860, pos, radius, maxNumObjects, pObjectList, bCheckVehicles, bCheckPeds, bCheckObjects);
}

CVehicle* CPedPlacement::IsPositionClearOfCars(CVector const* pos) {
    return plugin::CallAndReturnDynGlobal<CVehicle*, CVector const*>(0x6168E0, pos);
}

CVehicle* CPedPlacement::IsPositionClearOfCars(CPed const* ped) {
    return plugin::CallAndReturnDynGlobal<CVehicle*, CPed const*>(0x616A40, ped);
}