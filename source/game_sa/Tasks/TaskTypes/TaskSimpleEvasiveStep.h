#pragma once

#include "TaskSimple.h"
class CEntity;

class CTaskSimpleEvasiveStep : public CTaskSimple {
public:
    CEntity* m_Entity;
    bool     m_bFinished;
    CAnimBlendAssociation *m_Assoc;

public:
    static constexpr auto Type = TASK_SIMPLE_EVASIVE_STEP;

    explicit CTaskSimpleEvasiveStep(CEntity* entity);
    ~CTaskSimpleEvasiveStep() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleEvasiveStep(m_Entity); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    void StartAnim(CPed* ped);
    static void FinishAnimEvasiveStepCB(CAnimBlendAssociation *assoc, void* data);
};
VALIDATE_SIZE(CTaskSimpleEvasiveStep, 0x14);
