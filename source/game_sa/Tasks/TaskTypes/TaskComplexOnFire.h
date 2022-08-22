#pragma once

#include "TaskComplex.h"

class CPedDamageResponse;
class CTask;
class CPed;

/*!
 * Task sequence: COMPLEX_SMART_FLEE_ENTITY (until dead) -> COMPLEX_DIE
 */
class NOTSA_EXPORT_VTABLE CTaskComplexOnFire : public CTaskComplex {
public:
    constexpr static auto Type = eTaskType::TASK_COMPLEX_ON_FIRE;

    CTaskComplexOnFire() = default;           // 0x633390
    ~CTaskComplexOnFire() override = default; // 0x6333C0

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexOnFire(); }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

    CTask* CreateSubTask(eTaskType taskType);
    static void ComputeFireDamage(CPed* ped, CPedDamageResponse& resp);

    static void InjectHooks();
    CTaskComplexOnFire* Constructor() { this->CTaskComplexOnFire::CTaskComplexOnFire(); return this; }
    CTaskComplexOnFire* Destructor() { this->CTaskComplexOnFire::~CTaskComplexOnFire(); return this; }
};
