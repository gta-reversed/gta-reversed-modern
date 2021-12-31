/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "Vector.h"
#include "Entity.h"
#include "Vehicle.h"
#include "Ped.h"

class CPedPlacement {
public:
    static void InjectHooks();
    static bool FindZCoorForPed(CVector& inoutPos);
    static bool IsPositionClearForPed(CVector const& pos, float radius, int32 maxHitEntities, CEntity **outHitEntities, bool bCheckVehicles, bool bCheckPeds, bool bCheckObjects);
    static CVehicle *IsPositionClearOfCars(CVector const *pos);
    static CVehicle *IsPositionClearOfCars(CPed const *ped);
};
