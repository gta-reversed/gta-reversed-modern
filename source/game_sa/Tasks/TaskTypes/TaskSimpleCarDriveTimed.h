#pragma once
#include "TaskSimpleCarDrive.h"

class CVehicle;

class CTaskSimpleCarDriveTimed : public CTaskSimpleCarDrive
{
    CTaskSimpleCarDriveTimed() = delete;
public:
    int32 m_nTime;
    CTaskTimer m_nTimer;
private:
    CTaskSimpleCarDriveTimed* Constructor(CVehicle* pVehicle, int32 nTime);
public:
    CTaskSimpleCarDriveTimed(CVehicle* pVehicle, int32 nTime);
    ~CTaskSimpleCarDriveTimed() override;

    bool ProcessPed(class CPed* ped) override;
    CTask* Clone() override;
    eTaskType GetTaskType() override { return TASK_SIMPLE_CAR_DRIVE_TIMED; }
};

VALIDATE_SIZE(CTaskSimpleCarDriveTimed, 0x70);
