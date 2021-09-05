#pragma once

#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"

class CTaskSimpleFall : public CTaskSimple {
public:
    bool                   m_bIsFinished;
    char                   _pad_9[3];
    AnimationId            m_nAnimId;
    AssocGroupId           m_nAnimGroup;
    CAnimBlendAssociation* m_pAnim;
    int32                    m_nTotalDownTime; // TODO: uint32?
    uint32               m_nCurrentDownTime;

    static uint32& m_nMaxPlayerDownTime;

public:
    CTaskSimpleFall(AnimationId nAnimId, AssocGroupId nAnimGroup, int32 nDownTime);
    ~CTaskSimpleFall() override;

    eTaskType GetId() override { return TASK_SIMPLE_FALL; }
    CTask* Clone() override { return new CTaskSimpleFall(m_nAnimId, m_nAnimGroup, m_nTotalDownTime); }
    bool ProcessPed(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    bool ProcessPed_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);

    bool StartAnim(CPed* ped);
    void ProcessFall(CPed* ped);
    static void FinishFallAnimCB(CAnimBlendAssociation* pAnim, void* data); // data is CTaskSimpleFall

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleFall* Constructor(AnimationId nAnimId, AssocGroupId nAnimGroup, int32 nDownTime);
};

VALIDATE_SIZE(CTaskSimpleFall, 0x20);
