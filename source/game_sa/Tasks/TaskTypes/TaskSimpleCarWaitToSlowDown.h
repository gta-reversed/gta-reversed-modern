#pragma once

#include "TaskSimple.h"

class CVehicle;

// VMT: 0x86ed98 | Size: 9
class NOTSA_EXPORT_VTABLE CTaskSimpleCarWaitToSlowDown : public CTaskSimple {
public:
    enum class SlowDownType {
        PED_STEP_OUT_OR_JUMP,
        PED_STEP_OUT,
        DONE,
    };
public:
    CVehicle*    m_veh = {};
    uint32       m_door = {};
    SlowDownType m_type = {};

public:
    constexpr static auto Type = eTaskType::TASK_SIMPLE_CAR_WAIT_TO_SLOW_DOWN;

    static void InjectHooks();

    CTaskSimpleCarWaitToSlowDown(CVehicle* veh, SlowDownType type);
    ~CTaskSimpleCarWaitToSlowDown();

    CTask* Clone() { return new CTaskSimpleCarWaitToSlowDown{*this}; }
    eTaskType GetTaskType() { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event);
    bool ProcessPed(CPed* ped);
    bool SetPedPosition(CPed* ped);

private: // Wrappers for hooks
    // 0x646990
    CTaskSimpleCarWaitToSlowDown* Constructor(CVehicle* veh, SlowDownType type) {
        this->CTaskSimpleCarWaitToSlowDown::CTaskSimpleCarWaitToSlowDown(veh, type);
        return this;
    }

    // 0x646A00
    CTaskSimpleCarWaitToSlowDown* Destructor() {
        this->CTaskSimpleCarWaitToSlowDown::~CTaskSimpleCarWaitToSlowDown();
        return this;
    }
};
