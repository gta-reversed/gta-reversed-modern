#pragma once

#include "TaskComplex.h"

class CVehicle;

class CTaskComplexArrestPed : public CTaskComplex {
public:
    bool      m_subTaskNeedsToBeCreated;
    CPed*     m_pedToArrest;
    int32     field_14;
    int32     field_18;
    int32     field_1C;
    CVehicle* m_vehicle;

public:
    CTaskComplexArrestPed(CPed* ped);
    ~CTaskComplexArrestPed();

    CTask* Clone() override { return new CTaskComplexArrestPed(m_pedToArrest); }
    eTaskType GetTaskType() override { return TASK_COMPLEX_ARREST_PED; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(int32 taskId, CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexArrestPed* Constructor(CPed* ped) {
        this->CTaskComplexArrestPed::CTaskComplexArrestPed(ped);
        return this;
    }

    CTaskComplexArrestPed* Destructor() {
        this->CTaskComplexArrestPed::~CTaskComplexArrestPed();
        return this;
    }
};

VALIDATE_SIZE(CTaskComplexArrestPed, 0x24);
