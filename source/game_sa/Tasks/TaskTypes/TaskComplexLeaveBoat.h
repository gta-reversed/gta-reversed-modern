#pragma once

#include "TaskComplex.h"

class CVehicle;

class NOTSA_EXPORT_VTABLE CTaskComplexLeaveBoat : public CTaskComplex {
public:
    CVehicle* m_TargetVehicle;
    uint32 m_DelayTimeMs;

public:
    constexpr static auto Type = TASK_COMPLEX_LEAVE_BOAT;

    CTaskComplexLeaveBoat(CVehicle* vehicle, uint32 delay);
    ~CTaskComplexLeaveBoat() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexLeaveBoat(m_TargetVehicle, m_DelayTimeMs); }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType);

    static void InjectHooks();
    CTaskComplexLeaveBoat* Constructor(CVehicle* vehicle, uint32 delay) { this->CTaskComplexLeaveBoat::CTaskComplexLeaveBoat(vehicle, delay); return this; }
    CTaskComplexLeaveBoat* Destructor() { this->CTaskComplexLeaveBoat::~CTaskComplexLeaveBoat(); return this; }
};
VALIDATE_SIZE(CTaskComplexLeaveBoat, 0x14);
