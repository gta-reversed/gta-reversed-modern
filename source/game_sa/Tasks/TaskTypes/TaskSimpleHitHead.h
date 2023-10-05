#pragma once

#include "TaskSimple.h"

class CTaskSimpleHitHead : public CTaskSimple {
public:
    bool m_bIsFinished;
    CAnimBlendAssociation* m_pAnim;

public:
    static constexpr auto Type = TASK_SIMPLE_HIT_HEAD;

    CTaskSimpleHitHead();
    ~CTaskSimpleHitHead() override;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskSimpleHitHead(); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;
    static void FinishAnimCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleHitHead* Constructor();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskSimpleHitHead, 0x10);
