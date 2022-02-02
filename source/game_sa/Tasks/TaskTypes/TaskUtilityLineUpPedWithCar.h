/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "Ped.h"

class CTaskUtilityLineUpPedWithCar {
public:
    CVector vecOffsets;
    int32 field_C;
    int32 m_nTime;
    int32 field_14;
    int32 field_18;

    CTaskUtilityLineUpPedWithCar(CVector const& offsets, int32 nTime, int32 arg3, int32 arg4);
    CVector* GetLocalPositionToOpenCarDoor(int32 unused, CVehicle* pVehicle, float arg3, CAnimBlendAssociation* pAnimBlendAssoc);
    void ProcessPed(CPed* pPed, CVehicle* pVehicle, CAnimBlendAssociation* pAnimBlendAssoc);
    RwV3d* GetPositionToOpenCarDoor(int32 unused, CVehicle* pVehicle, float arg2, CAnimBlendAssociation* pAnimBlendAssoc);
};

VALIDATE_SIZE(CTaskUtilityLineUpPedWithCar, 0x1C);
