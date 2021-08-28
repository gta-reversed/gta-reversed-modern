/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool CPedPlacement::FindZCoorForPed(CVector* pos) {
    return plugin::CallAndReturn<bool, 0x616920, CVector*>(pos);
}

bool CPedPlacement::IsPositionClearForPed(CVector const* pos, float radius, int maxNumObjects, CEntity** pObjectList, unsigned char bCheckVehicles, unsigned char bCheckPeds, unsigned char bCheckObjects) {
    return plugin::CallAndReturn<bool, 0x616860, CVector const*, float, int, CEntity**, unsigned char, unsigned char, unsigned char>(pos, radius, maxNumObjects, pObjectList, bCheckVehicles, bCheckPeds, bCheckObjects);
}

CVehicle* CPedPlacement::IsPositionClearOfCars(CVector const* pos) {
    return plugin::CallAndReturn<CVehicle*, 0x6168E0, CVector const*>(pos);
}

CVehicle* CPedPlacement::IsPositionClearOfCars(CPed const* ped) {
    return plugin::CallAndReturn<CVehicle*, 0x616A40, CPed const*>(ped);
}