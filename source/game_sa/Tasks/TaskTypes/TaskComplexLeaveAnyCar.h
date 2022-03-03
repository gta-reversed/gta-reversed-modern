#pragma once

#include "TaskComplex.h"

class CTaskComplexLeaveAnyCar : CTaskComplex {
public:
    int32 m_delayTime{};        // 0xC
    bool  m_sensibleLeaveCar{}; // 0x10
    bool  m_forceGetOut{};      // 0x11

public:
    constexpr static auto Type = TASK_COMPLEX_LEAVE_ANY_CAR;

    static void InjectHooks();

    CTaskComplexLeaveAnyCar(int32 delayTime, bool sensibleLeaveCar, bool forceGetOut);
    CTaskComplexLeaveAnyCar(const CTaskComplexLeaveAnyCar&) = default; // NOTSA - For `Clone()`
    ~CTaskComplexLeaveAnyCar() = default;

    CTask* Clone() override { return new CTaskComplexLeaveAnyCar{*this}; }
    eTaskType GetTaskType() override { return Type; }
    CTask * CreateNextSubTask(CPed * ped) override { return nullptr; }
    CTask * CreateFirstSubTask(CPed * ped) override;
    CTask * ControlSubTask(CPed * ped) override { return m_pSubTask; }
private:
    CTaskComplexLeaveAnyCar* Constructor(int32 delayTime, bool sensibleLeaveCar, bool forceGetOut) {
        this->CTaskComplexLeaveAnyCar::CTaskComplexLeaveAnyCar(delayTime, sensibleLeaveCar, forceGetOut);
        return this;
    }

    CTaskComplexLeaveAnyCar* Destructor() {
        this->CTaskComplexLeaveAnyCar::~CTaskComplexLeaveAnyCar();
        return this;
    }

     CTask * Clone_Reversed() { return CTaskComplexLeaveAnyCar::Clone(); }
     eTaskType GetTaskType_Reversed() { return CTaskComplexLeaveAnyCar::GetTaskType(); }
     CTask * CreateNextSubTask_Reversed(CPed * ped) { return CTaskComplexLeaveAnyCar::CreateNextSubTask(ped); }
     CTask * CreateFirstSubTask_Reversed(CPed * ped) { return CTaskComplexLeaveAnyCar::CreateFirstSubTask(ped); }
     CTask * ControlSubTask_Reversed(CPed * ped) { return CTaskComplexLeaveAnyCar::ControlSubTask(ped); }
};
VALIDATE_SIZE(CTaskComplexLeaveAnyCar, 0x14);
