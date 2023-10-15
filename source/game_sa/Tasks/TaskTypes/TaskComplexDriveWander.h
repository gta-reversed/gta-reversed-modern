#pragma once

#include "TaskComplexCarDrive.h"

// todo: rename -> TaskComplexCarDriveWander.h

class CTaskComplexCarDriveWander : public CTaskComplexCarDrive {
public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE_WANDER;

    CTaskComplexCarDriveWander(CVehicle* vehicle, eCarDrivingStyle carDrivingStyle, float fSpeed);
    ~CTaskComplexCarDriveWander() override = default;

    CTask* Clone() const override { return new CTaskComplexCarDrive(m_Veh, m_CruiseSpeed, MODEL_INVALID, static_cast<eCarDrivingStyle>(m_CarDrivingStyle)); };
    eTaskType GetTaskType() const override { return Type; }
    void SetUpCar() override;
    CTask* CreateSubTaskCannotGetInCar(CPed* ped) override;
};

VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);
