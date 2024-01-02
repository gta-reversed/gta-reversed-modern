#pragma once

#include "TaskSimple.h"

class CTaskSimpleEvasiveDive : public CTaskSimple {
public:
    CVehicle* m_Vehicle;
    bool      m_bFinished;
    CAnimBlendAssociation* m_Assoc;

public:
    static constexpr auto Type = TASK_SIMPLE_EVASIVE_DIVE;

    CTaskSimpleEvasiveDive(CVehicle *vehicle);
    ~CTaskSimpleEvasiveDive() override;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskSimpleEvasiveDive(m_Vehicle); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;

    void StartAnim(CPed* ped);
    static void FinishAnimEvasiveDiveCB(CAnimBlendAssociation *assoc, void* data);
};
VALIDATE_SIZE(CTaskSimpleEvasiveDive, 0x14);
