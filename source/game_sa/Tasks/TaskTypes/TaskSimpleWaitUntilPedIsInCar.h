#pragma once

#include "TaskSimple.h"

class CEvent;
class CPed;

class NOTSA_EXPORT_VTABLE CTaskSimpleWaitUntilPedIsInCar : public CTaskSimple {
public:
    CPed* m_TargetPed;
    bool  m_bIsWalkingToDoor;

public:
    constexpr static auto Type = TASK_SIMPLE_WAIT_UNTIL_PED_IN_CAR;

    CTaskSimpleWaitUntilPedIsInCar(CPed* targetPed); // 0x649620
    ~CTaskSimpleWaitUntilPedIsInCar() override; // 0x6496A0

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleWaitUntilPedIsInCar(m_TargetPed); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; }
    bool ProcessPed(CPed* ped) override;

    static void InjectHooks();
    CTaskSimpleWaitUntilPedIsInCar* Constructor(CPed* pedToWaitFor) { this->CTaskSimpleWaitUntilPedIsInCar::CTaskSimpleWaitUntilPedIsInCar(pedToWaitFor); return this; }
    CTaskSimpleWaitUntilPedIsInCar* Destructor() { this->CTaskSimpleWaitUntilPedIsInCar::~CTaskSimpleWaitUntilPedIsInCar(); return this; }
};
VALIDATE_SIZE(CTaskSimpleWaitUntilPedIsInCar, 0x10);
