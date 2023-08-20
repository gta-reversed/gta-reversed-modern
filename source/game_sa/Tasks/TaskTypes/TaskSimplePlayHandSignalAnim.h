#pragma once

#include "TaskSimpleAnim.h"
class CHandObject;

class NOTSA_EXPORT_VTABLE CTaskSimplePlayHandSignalAnim : public CTaskSimpleAnim {
public:
    AnimationId  m_nAnimationBlockIndex;
    float        m_fBlendFactor;
    bool         m_bUseFatHands;
    CHandObject* m_pLeftHandObject;
    CHandObject* m_pRightHandObject; // always 0

public:
    static constexpr auto Type = TASK_SIMPLE_HANDSIGNAL_ANIM;

    CTaskSimplePlayHandSignalAnim(AnimationId animationId, float fBlendFactor, bool bFatHands, bool bHoldLastFrame);
    ~CTaskSimplePlayHandSignalAnim() override;

    eTaskType GetTaskType() const override { return Type; } // 0x61AEA0;
    CTask* Clone() const override { return new CTaskSimplePlayHandSignalAnim(m_nAnimationBlockIndex, m_fBlendFactor, m_bUseFatHands, m_bHoldLastFrame); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override { return CTaskSimpleAnim::MakeAbortable(ped, priority, event); }
    bool ProcessPed(CPed* ped) override;

    void StartAnim(CPed* ped);

    static void InjectHooks();
    bool ProcessPed_Reversed(CPed* ped);
};
VALIDATE_SIZE(CTaskSimplePlayHandSignalAnim, 0x24);
