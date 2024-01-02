#pragma once

#include "TaskComplex.h"

class CTaskComplexPolicePursuit : public CTaskComplex {
public:
    uint8 m_nFlags;
    CPed* m_pursuer;
    CPed* m_persecuted;

public:
    static constexpr auto Type = TASK_COMPLEX_POLICE_PURSUIT;

    CTaskComplexPolicePursuit();
    CTaskComplexPolicePursuit(const CTaskComplexPolicePursuit&);
    ~CTaskComplexPolicePursuit() override;

    eTaskType GetTaskType() const override { return Type; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override { return m_pSubTask->MakeAbortable(ped, priority, event); } // 0x68BAB0
    CTask* Clone() const override { return new CTaskComplexPolicePursuit{*this}; } // 0x68CDD0
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
    bool PersistPursuit(CPed* ped);
    bool SetPursuit(CPed* ped);
    void ClearPursuit(CPed* ped);
    void SetWeapon(CPed* ped);

public:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexPolicePursuit* Constructor();

    CTask*  Clone_Reversed() const;
    eTaskType GetTaskType_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexPolicePursuit, 0x18);
