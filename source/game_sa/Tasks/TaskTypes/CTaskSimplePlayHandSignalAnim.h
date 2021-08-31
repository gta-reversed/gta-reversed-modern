#pragma once

#include "CTaskSimpleAnim.h"
#include "CHandObject.h"

class CTaskSimplePlayHandSignalAnim : public CTaskSimpleAnim {
public:
    AnimationId  m_nAnimationBlockIndex;
    float        m_fBlendFactor;
    bool         m_bUseFatHands;
    CHandObject* m_pLeftHandObject;
    CHandObject* m_pRightHandObject; // always 0

public:
    CTaskSimplePlayHandSignalAnim(AnimationId animationId, float fBlendFactor, bool bFatHands, bool bHoldLastFrame);
    ~CTaskSimplePlayHandSignalAnim();

    CTask* Clone() override;
    eTaskType GetId() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    void StartAnim(CPed* pPed);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTask* Clone_Reversed();
    eTaskType GetId_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimplePlayHandSignalAnim, 0x24);
