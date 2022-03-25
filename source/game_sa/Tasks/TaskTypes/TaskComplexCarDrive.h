#pragma once

#include "TaskComplex.h"
#include "Enums/eCarMission.h"
#include "Enums/eCarDrivingStyle.h"

class CVehicle;

class CTaskComplexCarDrive : public CTaskComplex {
public:
    CVehicle* m_pVehicle;
    float m_fSpeed;
    int m_carModelIndexToCreate;
    int m_carDrivingStyle; // `eCarDrivingStyle`, sadly we cant use it as the member type, because the underlaying type isn't int32
    char field_1C; // Not padding
    int8 m_nbTrafficBehavior;
    int8 m_nbDriverBehavior;
    int8 m_nSpeed;
    bool m_bSavedVehicleBehavior;

public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE;

    explicit CTaskComplexCarDrive(CVehicle* vehicle);
    CTaskComplexCarDrive(CVehicle* vehicle, float arg2, int32 arg3, eCarDrivingStyle carDrivingStyle);
    ~CTaskComplexCarDrive() override;

    CTask*    Clone() override;
    eTaskType GetTaskType() override { return Type; }

    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    virtual void   SetUpCar();
    virtual CTask* CreateSubTaskCannotGetInCar(CPed* ped);
    virtual CTask* Drive(CPed* ped);
};
VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);
