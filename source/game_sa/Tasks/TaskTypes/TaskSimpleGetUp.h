#pragma once

#include "TaskSimple.h"

class CTaskSimpleGetUp : public CTaskSimple {
public:
    uint8                  m_bIsFinished;
    uint8                  m_bAnimFinished;
    CAnimBlendAssociation* m_pAnim;

public:
    CTaskSimpleGetUp();
    ~CTaskSimpleGetUp() override;

    CTask* Clone() override { return new CTaskSimpleGetUp(); }
    eTaskType GetTaskType() override { return TASK_SIMPLE_GET_UP; }
    bool ProcessPed(class CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleGetUp* Constructor();

    bool ProcessPed_Reversed(class CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool StartAnim(CPed* ped);

    static void FinishGetUpAnimCB(CAnimBlendAssociation* blendAssoc, void* data); //data is CTaskSimpleGetUp

    static CColPoint(&m_aColPoints)[32];
};

VALIDATE_SIZE(CTaskSimpleGetUp, 0x10);
