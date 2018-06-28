/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "CEntity.h"
#include "CVehicle.h"
#include "CPed.h"

class  CPedPlacement {
public:
     static bool FindZCoorForPed(CVector *pos);
     static bool IsPositionClearForPed(CVector const *pos, float radius, int maxNumObjects, CEntity **pObjectList, unsigned char bCheckVehicles, unsigned char bCheckPeds, unsigned char bCheckObjects);
     static CVehicle *IsPositionClearOfCars(CVector const *pos);
     static CVehicle *IsPositionClearOfCars(CPed const *ped);
};

//#include "meta/meta.CPedPlacement.h"
