#pragma once

#include "TaskComplex.h"
class CVehicle;

class CTaskComplexDestroyCar : public CTaskComplex {
public:
    bool      dword0C;
    CVehicle* m_Vehicle;
    uint32    dword14;
    uint32    dword18;
    uint32    dword1C;

public:
    static constexpr auto Type = TASK_COMPLEX_DESTROY_CAR;

    CTaskComplexDestroyCar(CVehicle* vehicle, uint32 a3, uint32 a4, uint32 a5);
    ~CTaskComplexDestroyCar() override;

    eTaskType GetTaskType() override { return Type; } // 0x621C70
    CTask* Clone() override { return new CTaskComplexDestroyCar(m_Vehicle, dword14, dword18, dword1C); } // 0x623530
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType, CPed* ped = nullptr);

    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    CTask* ControlSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskComplexDestroyCar, 0x20);
extern void CTaskComplexDestroyCar__InjectHooks();
