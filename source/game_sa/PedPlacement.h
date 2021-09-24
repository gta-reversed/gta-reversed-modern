/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "CVector.h"
#include "CEntity.h"
#include "CVehicle.h"
#include "CPed.h"

class CPedPlacement {
public:
     static bool FindZCoorForPed(CVector *pos);
     static bool IsPositionClearForPed(CVector const *pos, float radius, int32 maxNumObjects, CEntity **pObjectList, uint8 bCheckVehicles, uint8 bCheckPeds, uint8 bCheckObjects);
     static CVehicle *IsPositionClearOfCars(CVector const *pos);
     static CVehicle *IsPositionClearOfCars(CPed const *ped);
};
