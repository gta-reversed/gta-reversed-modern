#pragma once

#include "TaskComplexCarDrive.h"

class CTaskComplexCarDriveWander : public CTaskComplexCarDrive {
public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE_WANDER;

    CTaskComplexCarDriveWander(CVehicle* vehicle, eCarDrivingStyle carDrivingStyle, float fSpeed);
    ~CTaskComplexCarDriveWander() override = default;

    CTask* Clone() override { return new CTaskComplexCarDrive(m_pVehicle, m_fSpeed, -1, static_cast<eCarDrivingStyle>(m_nCarDrivingStyle)); };
    eTaskType GetTaskType() override { return Type; }
    void SetUpCar() override;
    CTask* CreateSubTaskCannotGetInCar(CPed* ped) override;
};

VALIDATE_SIZE(CTaskComplexCarDrive, 0x24);
