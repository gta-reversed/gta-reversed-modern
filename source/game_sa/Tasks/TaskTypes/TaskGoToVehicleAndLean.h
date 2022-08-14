#pragma once
#include "TaskComplex.h"
#include "Vehicle.h"

class CTaskGoToVehicleAndLean : public CTaskComplex {
public:
    CVehicle* m_vehicle = {}; // 0xC
    int32     m_leanAnimDurationInMs = {}; // 0x10
    int8      m_leanOnVehicle = {}; // 0x14
    int8      field_15 = {}; // 0x15
    uint8     field_16[2] = {}; // 0x16

public:
    static void InjectHooks();

    CTaskGoToVehicleAndLean(CVehicle* vehicle, int32 leanAnimDurationInMs);
    ~CTaskGoToVehicleAndLean();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GOTO_VEHICLE_AND_LEAN;

    virtual CTask*    Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool      MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask*    CreateNextSubTask(CPed* ped);
    virtual CTask*    CreateFirstSubTask(CPed* ped);
    virtual CTask*    ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x660E60
    CTaskGoToVehicleAndLean* Constructor(CVehicle* vehicle, int32 leanAnimDurationInMs) {
        this->CTaskGoToVehicleAndLean::CTaskGoToVehicleAndLean(vehicle, leanAnimDurationInMs);
        return this;
    }

    // 0x660EE0
    CTaskGoToVehicleAndLean* Destructor() {
        this->CTaskGoToVehicleAndLean::~CTaskGoToVehicleAndLean();
        return this;
    }
};
VALIDATE_SIZE(CTaskGoToVehicleAndLean, 0x18);
