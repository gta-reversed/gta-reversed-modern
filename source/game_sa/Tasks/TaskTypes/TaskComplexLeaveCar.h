/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"
#include "Vehicle.h"
#include "TaskUtilityLineUpPedWithCar.h"

class CTaskComplexLeaveCar : public CTaskComplex {
public:
    CVehicle*                     m_pTargetVehicle;
    int32                         m_nTargetDoor;
    int32                         m_nDelayTime;
    bool                          m_bSensibleLeaveCar;
    bool                          m_bForceGetOut;
    bool                          m_bDie;
    char                          _pad1;
    CTaskUtilityLineUpPedWithCar* m_pTaskUtilityLineUpPedWithCar;
    uint8                         m_nDoorFlagsSet;
    uint8                         m_nNumGettingInSet;
    char                          _pad2[2];
    int32                         m_nDieAnimID;
    float                         m_fDieAnimBlendDelta;
    float                         m_fDieAnimSpeed;
    bool                          m_bIsInAir;
    char                          _pad3[3];

public:
    CTaskComplexLeaveCar(CVehicle* pTargetVehicle, int32 nTargetDoor, int32 nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut);
    ~CTaskComplexLeaveCar();

    CTask*    Clone() override;
    eTaskType GetTaskType() override { return TASK_COMPLEX_LEAVE_CAR; }
    bool   MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexLeaveCar* Constructor(CVehicle* pTargetVehicle, int32 nTargetDoor, int32 nDelayTime, bool bSensibleLeaveCar, bool bForceGetOut);
};

VALIDATE_SIZE(CTaskComplexLeaveCar, 0x34);
