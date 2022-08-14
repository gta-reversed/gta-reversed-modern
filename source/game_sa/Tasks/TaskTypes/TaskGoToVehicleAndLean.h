#pragma once

#include "TaskComplex.h"
class CVehicle;

class CTaskGoToVehicleAndLean : public CTaskComplex {
public:
    CVehicle* m_Vehicle;
    int32     m_LeanAnimDurationInMs;
    int8      m_LeanOnVehicle;
    int8      field_15;
    uint8     field_16[2];

public:
    static constexpr auto Type = TASK_COMPLEX_GOTO_VEHICLE_AND_LEAN;

    CTaskGoToVehicleAndLean(CVehicle* vehicle, int32 leanAnimDurationInMs);
    ~CTaskGoToVehicleAndLean() override;

    eTaskType GetTaskType() override { return Type; } // 0x660ED0
    CTask* Clone() override { return new CTaskGoToVehicleAndLean(m_Vehicle, m_LeanAnimDurationInMs); } // 0x6621B0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskGoToVehicleAndLean* Constructor(CVehicle* vehicle, int32 leanAnimDurationInMs) { this->CTaskGoToVehicleAndLean::CTaskGoToVehicleAndLean(vehicle, leanAnimDurationInMs); return this; }
    CTaskGoToVehicleAndLean* Destructor() { this->CTaskGoToVehicleAndLean::~CTaskGoToVehicleAndLean(); return this; }
};
VALIDATE_SIZE(CTaskGoToVehicleAndLean, 0x18);
