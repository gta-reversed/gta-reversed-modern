#pragma once

#include "TaskSimpleCarDrive.h"

class CVehicle;

class CTaskSimpleCarDriveTimed : public CTaskSimpleCarDrive {
public:
    int32      m_nTime;
    CTaskTimer m_nTimer;

public:
    CTaskSimpleCarDriveTimed() = delete;
    CTaskSimpleCarDriveTimed(CVehicle* pVehicle, int32 nTime);
    ~CTaskSimpleCarDriveTimed() override = default;

    eTaskType GetTaskType() override { return TASK_SIMPLE_CAR_DRIVE_TIMED; }
    CTask* Clone() override;
    bool ProcessPed(class CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleCarDriveTimed* Constructor(CVehicle* pVehicle, int32 nTime);
};

VALIDATE_SIZE(CTaskSimpleCarDriveTimed, 0x70);
