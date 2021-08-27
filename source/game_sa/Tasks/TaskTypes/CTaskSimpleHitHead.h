#pragma once
#include "CTaskSimple.h"

class CTaskSimpleHitHead : public CTaskSimple
{
public:
    unsigned char m_bIsFinished;
    unsigned char _pad[3];
    CAnimBlendAssociation* m_pAnim;

private:
    CTaskSimpleHitHead* Constructor();
public:
    CTaskSimpleHitHead();
    ~CTaskSimpleHitHead() override;

    static void InjectHooks();

    CTask* Clone() override { return new CTaskSimpleHitHead(); }
    eTaskType GetId() override { return TASK_SIMPLE_HIT_HEAD; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;
    static void FinishAnimCB(CAnimBlendAssociation* pAnim, void* data);

    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleHitHead, 0x10);
