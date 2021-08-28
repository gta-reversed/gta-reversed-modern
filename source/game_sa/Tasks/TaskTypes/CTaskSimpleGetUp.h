#pragma once
#include "CTaskSimple.h"

class CTaskSimpleGetUp : public CTaskSimple
{
public:
    unsigned char m_bIsFinished;
    unsigned char m_bAnimFinished;
    unsigned char _pad_A[2];
    CAnimBlendAssociation* m_pAnim;
private:
    CTaskSimpleGetUp* Constructor();
public:
    CTaskSimpleGetUp();
    ~CTaskSimpleGetUp() override;

    static void InjectHooks();

    CTask* Clone() override { return new CTaskSimpleGetUp(); }
    eTaskType GetId() override { return TASK_SIMPLE_GET_UP; }
    bool ProcessPed(class CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;

    bool ProcessPed_Reversed(class CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);
    bool StartAnim(CPed* ped);

    static void FinishGetUpAnimCB(CAnimBlendAssociation* pBlendAssoc, void* data); //data is CTaskSimpleGetUp

    static CColPoint(&m_aColPoints)[32];
};

VALIDATE_SIZE(CTaskSimpleGetUp, 0x10);
