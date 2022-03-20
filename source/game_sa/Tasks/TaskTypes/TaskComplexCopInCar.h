#pragma once

#include "TaskComplex.h"
#include "TaskTimer.h"

class CPed;
class CVehicle;

class CTaskComplexCopInCar : public CTaskComplex {
public:
    CVehicle* m_pVehicle{};             // 0xC
    CPed* m_cop{};                      // 0x10 - Same as `ped` that's passed to all functions (So basically the ped this task belongs to)
    CPed* m_suspect{};                  // 0x14 
    CTaskTimer m_timer1{};              // 0x18
    CTaskTimer m_timer2{};              // 0x24
    uint8 m_suspectDeadOrLost : 1{};    // 0x30 - 0st bit - Seems to be related to cop1's existance, something like `isCop1Alive`
    uint8 m_flag0x2 : 1{};              // 0x30 - 1nd bit
    uint8 m_flag0x4 : 1{true};          // 0x30 - 2rd bit
    uint8 m_isSuspectInCar : 1{};       // 0x30 - 3th bit

public:
    static constexpr auto Type = TASK_COMPLEX_COP_IN_CAR;

    static void InjectHooks();

    CTaskComplexCopInCar(CVehicle* vehicle, CPed* cop1, CPed* cop2, bool flag_0x1);
    CTaskComplexCopInCar(const CTaskComplexCopInCar&); // NOTSA: `Clone()` helper
    ~CTaskComplexCopInCar() override;

    CTask* CreateSubTask(eTaskType taskType, CPed* copPed);

    CTask* Clone() override { return new CTaskComplexCopInCar{ *this }; }
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private: // Wrappers for hooks
    CTaskComplexCopInCar* Constructor(CVehicle* vehicle, CPed* cop1, CPed* cop2, bool flag_0x1) {
        this->CTaskComplexCopInCar::CTaskComplexCopInCar(vehicle, cop1, cop2, flag_0x1);
        return this;
    }

    CTaskComplexCopInCar* Destructor() {
        this->CTaskComplexCopInCar::~CTaskComplexCopInCar();
        return this;
    }

    CTask* Clone_Reversed() {
        return CTaskComplexCopInCar::Clone();
    }
    eTaskType GetTaskType_Reversed() {
        return CTaskComplexCopInCar::GetTaskType();
    }
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent const* event) {
        return CTaskComplexCopInCar::MakeAbortable(ped, priority, event);
    }
    CTask* CreateNextSubTask_Reversed(CPed* ped) {
        return CTaskComplexCopInCar::CreateNextSubTask(ped);
    }
    CTask* CreateFirstSubTask_Reversed(CPed* ped) {
        return CTaskComplexCopInCar::CreateFirstSubTask(ped);
    }
    CTask* ControlSubTask_Reversed(CPed* ped) {
        return CTaskComplexCopInCar::ControlSubTask(ped);
    }
};
VALIDATE_SIZE(CTaskComplexCopInCar, 0x34);
