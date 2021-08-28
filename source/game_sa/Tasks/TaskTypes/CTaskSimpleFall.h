#pragma once
#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"

class CTaskSimpleFall : public CTaskSimple
{
public:
    unsigned char m_bIsFinished;
    unsigned char _pad_9[3];
    eAnimID m_nAnimId;
    eAnimGroup m_nAnimGroup;
    CAnimBlendAssociation* m_pAnim;
    int m_nTotalDownTime;
    uint32_t m_nCurrentDownTime;

private:
    CTaskSimpleFall* Constructor(eAnimID nAnimId, eAnimGroup nAnimGroup, int nDownTime);
public:
    CTaskSimpleFall(eAnimID nAnimId, eAnimGroup nAnimGroup, int nDownTime);
    ~CTaskSimpleFall() override;

    static void InjectHooks();

    eTaskType GetId() override { return TASK_SIMPLE_FALL; }
    CTask* Clone() override { return new CTaskSimpleFall(m_nAnimId, m_nAnimGroup, m_nTotalDownTime); }
    bool ProcessPed(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;

    bool ProcessPed_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);

    bool StartAnim(CPed* ped);
    void ProcessFall(CPed* ped);
    static void FinishFallAnimCB(CAnimBlendAssociation* pAnim, void* data); // data is CTaskSimpleFall

    static unsigned int &m_nMaxPlayerDownTime;
};

VALIDATE_SIZE(CTaskSimpleFall, 0x20);
