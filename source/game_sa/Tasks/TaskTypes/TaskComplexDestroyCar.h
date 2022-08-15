#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CVehicle;

class CTaskComplexDestroyCar : public CTaskComplex {
public:
    bool m_arg0 = {};                  // 0xC
    bool m_arg1 = {};                  // 0xD
    CVehicle* m_vehicleToDestroy = {}; // 0x10
    CVector m_vehPosn = {};             // 0x14

public:
    static void InjectHooks();

    ~CTaskComplexDestroyCar();
    CTaskComplexDestroyCar(CVehicle* vehicleToDestroy, CVector vehPosn);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_DESTROY_CAR;

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);

    CTask* Clone() override;
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private: // Wrappers for hooks
    // 0x621C00
    CTaskComplexDestroyCar* Constructor(CVehicle* vehicleToDestroy, CVector vehPosn) {
        this->CTaskComplexDestroyCar::CTaskComplexDestroyCar(vehicleToDestroy, vehPosn);
        return this;
    }

    // 0x621CB0
    CTaskComplexDestroyCar* Destructor() {
        this->CTaskComplexDestroyCar::~CTaskComplexDestroyCar();
        return this;
    }
};
VALIDATE_SIZE(CTaskComplexDestroyCar, 0x20);
