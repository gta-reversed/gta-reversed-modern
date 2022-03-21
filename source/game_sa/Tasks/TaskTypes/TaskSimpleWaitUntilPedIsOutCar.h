#pragma once

#include "Base.h"
#include "Vector.h"

#include "TaskSimple.h"

class CPed;

class CTaskSimpleWaitUntilPedIsOutCar : public CTaskSimple {
public:
    CPed*   m_pedToWaitFor{};                      // 0x8
    bool    m_isNotGoingTowardsPos{true}; // 0xC
    CVector m_pos{};                      // 0x10

public:
    static constexpr auto Type = TASK_SIMPLE_WAIT_UNTIL_PED_OUT_CAR;

    static void InjectHooks();

    CTaskSimpleWaitUntilPedIsOutCar(CPed * ped, CVector const& pos);
    ~CTaskSimpleWaitUntilPedIsOutCar();

    CTask * Clone() override;
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override { return true; }
    bool ProcessPed(CPed * ped) override;

private: // Wrappers for hooks
    CTaskSimpleWaitUntilPedIsOutCar* Constructor(CPed * ped, CVector const& pos) {
        this->CTaskSimpleWaitUntilPedIsOutCar::CTaskSimpleWaitUntilPedIsOutCar(ped, pos);
        return this;
    }

    CTaskSimpleWaitUntilPedIsOutCar* Destructor() {
        this->CTaskSimpleWaitUntilPedIsOutCar::~CTaskSimpleWaitUntilPedIsOutCar();
        return this;
    }

    CTask * Clone_Reversed() { return CTaskSimpleWaitUntilPedIsOutCar::Clone(); }
    eTaskType GetTaskType_Reversed() { return CTaskSimpleWaitUntilPedIsOutCar::GetTaskType(); }
    bool MakeAbortable_Reversed(CPed * ped, eAbortPriority priority, CEvent const* event) { return CTaskSimpleWaitUntilPedIsOutCar::MakeAbortable(ped, priority, event); }
    bool ProcessPed_Reversed(CPed * ped) { return CTaskSimpleWaitUntilPedIsOutCar::ProcessPed(ped); }
};
VALIDATE_SIZE(CTaskSimpleWaitUntilPedIsOutCar, 0x1C);
