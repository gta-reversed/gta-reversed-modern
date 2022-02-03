/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once


#include "TaskSimple.h"
#include "Vehicle.h"
#include "TaskUtilityLineUpPedWithCar.h"

class CTaskSimpleCarSetPedInAsDriver : public CTaskSimple {
public:
    bool                          m_bIsFinished;
    CAnimBlendAssociation*        m_pAnim;
    CVehicle*                     m_pTargetVehicle;
    CTaskUtilityLineUpPedWithCar* m_pUtility;
    bool                          m_bWarpingInToCar;
    uint8                         m_nDoorFlagsToClear;
    uint8                         m_nNumGettingInToClear;

public:
    CTaskSimpleCarSetPedInAsDriver(CVehicle *targetVehicle, CTaskUtilityLineUpPedWithCar *utility);
    ~CTaskSimpleCarSetPedInAsDriver();

    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_CAR_SET_PED_IN_AS_DRIVER; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return false; }
    bool ProcessPed(CPed* ped) override;

};

VALIDATE_SIZE(CTaskSimpleCarSetPedInAsDriver, 0x1C);
