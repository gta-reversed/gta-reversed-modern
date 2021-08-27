#pragma once

#include "PluginBase.h"
#include "CTaskSimpleAnim.h"
#include "CHandObject.h"

class  CTaskSimplePlayHandSignalAnim : public CTaskSimpleAnim {
    CTaskSimplePlayHandSignalAnim(int animationId, float fBlendFactor, bool bFatHands, bool bHoldLastFrame);
    ~CTaskSimplePlayHandSignalAnim();
public:
    int m_nAnimationBlockIndex;
    float m_fBlendFactor;
    bool m_bUseFatHands;
    CHandObject* m_pLeftHandObject;
    CHandObject* m_pRightHandObject; // always 0

public:
    static void InjectHooks();

    CTask* Clone() override;
    eTaskType GetId() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

private:
    CTask* Clone_Reversed();
    eTaskType GetId_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);

public:
    void StartAnim(CPed* pPed);
};

VALIDATE_SIZE(CTaskSimplePlayHandSignalAnim, 0x24);
