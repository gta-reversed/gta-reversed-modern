#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CVehicle;

class CTaskComplexDestroyCar : public CTaskComplex {
public:
    bool      m_arg0;
    bool      m_arg1;
    CVehicle* m_VehicleToDestroy;
    uint32    dword14;
    uint32    dword18;
    uint32    dword1C;

public:
    static constexpr auto Type = TASK_COMPLEX_DESTROY_CAR;

    CTaskComplexDestroyCar(CVehicle* vehicleToDestroy, uint32 a3, uint32 a4, uint32 a5);
    ~CTaskComplexDestroyCar() override;

    eTaskType GetTaskType() override { return Type; } // 0x621C70
    CTask* Clone() override { return new CTaskComplexDestroyCar(m_VehicleToDestroy, dword14, dword18, dword1C); } // 0x623530
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType, CPed* ped = nullptr);

    static void InjectHooks();
    CTaskComplexDestroyCar* Constructor(CVehicle* vehicleToDestroy, uint32 a3, uint32 a4, uint32 a5) { this->CTaskComplexDestroyCar::CTaskComplexDestroyCar(vehicleToDestroy, a3, a4, a5); return this; }
    CTaskComplexDestroyCar* Destructor() { this->CTaskComplexDestroyCar::~CTaskComplexDestroyCar(); return this; }
};
VALIDATE_SIZE(CTaskComplexDestroyCar, 0x20);
