/*
    Plugin-SDK file
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

    CTaskUtilityLineUpPedWithCar(const CVector& offsets, int32 nTime, int32 arg3, int32 arg4);
    CVector* GetLocalPositionToOpenCarDoor(int32 unused, CVehicle* vehicle, float arg3, CAnimBlendAssociation* animBlendAssoc);
    void ProcessPed(CPed* ped, CVehicle* vehicle, CAnimBlendAssociation* animBlendAssoc);
    RwV3d* GetPositionToOpenCarDoor(int32 unused, CVehicle* vehicle, float arg2, CAnimBlendAssociation* animBlendAssoc);
};

VALIDATE_SIZE(CTaskUtilityLineUpPedWithCar, 0x1C);
