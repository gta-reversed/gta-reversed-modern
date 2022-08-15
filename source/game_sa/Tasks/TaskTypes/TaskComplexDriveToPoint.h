#pragma once

#include "TaskComplexCarDrive.h"
class CVehicle;

class CTaskComplexDriveToPoint : public CTaskComplexCarDrive {
public:
    CVector m_Point;
    int32   field_30;
    int32   field_34;
    int32   field_38;

public:
    static constexpr auto Type = TASK_COMPLEX_CAR_DRIVE_TO_POINT;

    CTaskComplexDriveToPoint(CVehicle* vehicle, CVector& point, float speed, int32 arg4, int32 arg5, float arg6, int32 arg7);
    ~CTaskComplexDriveToPoint() override = default;

    eTaskType GetTaskType() override { return Type;}
    CTask* Clone() override { return new CTaskComplexDriveToPoint(m_pVehicle, m_Point, m_fSpeed, field_30, m_carModelIndexToCreate, field_34, m_nCarDrivingStyle); }

    CTask* CreateSubTaskCannotGetInCar(CPed* ped);
};
VALIDATE_SIZE(CTaskComplexDriveToPoint, 0x3C);
