#pragma once

#include "TaskComplex.h"
#include "Vehicle.h"

class CTaskComplexCarDrive : public CTaskComplex {
public:
    CVehicle* m_pVehicle;
    float     m_fSpeed;
    int32     field_14;
    int32     field_18;
    uint8     field_1C;
    uint8     m_nbTrafficBehavior;
    uint8     m_nbDriverBehavior;
    uint8     field_1F;
    uint8     m_bSavedVehicleBehavior;
    char      _pad_21[3];

public:
    explicit CTaskComplexCarDrive(CVehicle* vehicle);
    CTaskComplexCarDrive(CVehicle* vehicle, float arg2, int32 arg3, int32 arg4);
    ~CTaskComplexCarDrive() override;

    CTask*    Clone() override;
    eTaskType GetTaskType() override { return TASK_COMPLEX_CAR_DRIVE; }

    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    virtual void   SetUpCar();
    virtual CTask* CreateSubTaskCannotGetInCar(CPed* ped);
    virtual CTask* Drive(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);
