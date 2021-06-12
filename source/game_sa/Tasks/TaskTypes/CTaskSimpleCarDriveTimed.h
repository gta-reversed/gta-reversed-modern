#pragma once
#include "CTaskSimpleCarDrive.h"

class CVehicle;

class CTaskSimpleCarDriveTimed : public CTaskSimpleCarDrive
{
    CTaskSimpleCarDriveTimed() = delete;
public:
    int m_nTime;
    CTaskTimer m_nTimer;
private:
    CTaskSimpleCarDriveTimed* Constructor(CVehicle* pVehicle, int nTime);
public:
    CTaskSimpleCarDriveTimed(CVehicle* pVehicle, int nTime);
    ~CTaskSimpleCarDriveTimed() override;

    bool ProcessPed(class CPed* ped) override;
    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_CAR_DRIVE_TIMED; }
};

VALIDATE_SIZE(CTaskSimpleCarDriveTimed, 0x70);
