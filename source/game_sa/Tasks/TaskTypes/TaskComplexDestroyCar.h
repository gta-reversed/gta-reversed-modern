#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CVehicle;

class CTaskComplexDestroyCar : public CTaskComplex {
public:
    bool m_arg0 = {};
    bool m_arg1 = {};
    CVehicle* m_vehicleToDestroy = {};
    CVector m_vehPosn = {};

public:
    static void InjectHooks();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_DESTROY_CAR;

    CTaskComplexDestroyCar(CVehicle* vehicleToDestroy, CVector vehPosn);
    CTaskComplexDestroyCar(const CTaskComplexDestroyCar&);
    ~CTaskComplexDestroyCar() override;

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexDestroyCar{ *this }; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private: // Wrappers for hooks
    // 0x621C00
    CTaskComplexDestroyCar* Constructor(CVehicle* vehicleToDestroy, CVector vehPosn) { this->CTaskComplexDestroyCar::CTaskComplexDestroyCar(vehicleToDestroy, vehPosn); return this; }

    // 0x621CB0
    CTaskComplexDestroyCar* Destructor() { this->CTaskComplexDestroyCar::~CTaskComplexDestroyCar(); return this; }
};
VALIDATE_SIZE(CTaskComplexDestroyCar, 0x20);
