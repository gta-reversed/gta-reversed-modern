/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "TaskUtilityLineUpPedWithCar.h"
class Vehicle;

class CTaskSimpleCarSetPedInAsPassenger : public CTaskSimple {
public:
    bool                          m_bIsFinished;
    CAnimBlendAssociation*        m_pAnim;
    CVehicle*                     m_pTargetVehicle;
    int32                         m_nTargetDoor;
    CTaskUtilityLineUpPedWithCar* m_pUtility;
    bool                          m_bWarpingInToCar;
    uint8                         m_nDoorFlagsToClear;
    uint8                         m_nNumGettingInToClear;

public:
    static constexpr auto Type = TASK_SIMPLE_CAR_SET_PED_IN_AS_PASSENGER;

    CTaskSimpleCarSetPedInAsPassenger(CVehicle* targetVehicle, int32 nTargetDoor, CTaskUtilityLineUpPedWithCar* utility = nullptr);
    ~CTaskSimpleCarSetPedInAsPassenger() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return false; }
    bool ProcessPed(CPed* ped) override;
};
VALIDATE_SIZE(CTaskSimpleCarSetPedInAsPassenger, 0x20);
