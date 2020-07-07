/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskSimple.h"
#include "CPed.h"
#include "CAnimBlendAssociation.h"

class CTaskSimpleStealthKill : public CTaskSimple
{
public:
    bool m_bKeepTargetAlive;
    CPed *m_pTarget;
    std::int32_t m_nAssocGroupId;
    bool m_bIsAborting;
    bool m_bIsFinished;
    CAnimBlendAssociation *m_pAnim;
    unsigned int m_nTime;

    static void InjectHooks();

    CTaskSimpleStealthKill(bool bKeepTargetAlive, CPed* pTarget, int nAssocGroupId);
    CTaskSimpleStealthKill* Constructor(bool bKeepTargetAlive, CPed* pTarget, int nAssocGroupId);
    bool ProcessPed(CPed* ped) override;
    bool ProcessPed_Reversed(CPed* ped);
    CTask* Clone() override;
    CTask* Clone_Reversed();
    eTaskType GetId() override;
    eTaskType GetId_Reversed() { return TASK_SIMPLE_STEALTH_KILL; };
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, class CEvent* _event) override;
    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, class CEvent* _event);
    void ManageAnim(CPed* ped);

    static void FinishAnimStealthKillCB(CAnimBlendAssociation* pAnimAssoc, void* vpTaskSimpleStealthKill);
};

VALIDATE_SIZE(CTaskSimpleStealthKill, 0x20);

