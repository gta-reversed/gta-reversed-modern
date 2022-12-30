/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
#include "Ped.h"
#include "AnimBlendAssociation.h"

class NOTSA_EXPORT_VTABLE CTaskSimpleStealthKill : public CTaskSimple {
public:
    bool                   m_bKeepTargetAlive;
    CPed*                  m_pTarget;
    AssocGroupId           m_nAssocGroupId;
    bool                   m_bIsAborting;
    bool                   m_bIsFinished;
    CAnimBlendAssociation* m_pAnim;
    uint32                 m_nTime;

public:
    static constexpr auto Type = TASK_SIMPLE_STEALTH_KILL;

    CTaskSimpleStealthKill(bool keepTargetAlive, CPed* target, AssocGroupId groupId);

    bool ProcessPed(CPed* ped) override;
    CTask* Clone() override;
    eTaskType GetTaskType() override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override;
    void ManageAnim(CPed* ped);

    static void FinishAnimStealthKillCB(CAnimBlendAssociation* pAnimAssoc, void* vpTaskSimpleStealthKill);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleStealthKill* Constructor(bool keepTargetAlive, CPed* target, AssocGroupId groupId);

    bool ProcessPed_Reversed(CPed* ped);
    CTask* Clone_Reversed();
    eTaskType GetId_Reversed() { return TASK_SIMPLE_STEALTH_KILL; };
    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event);
};

VALIDATE_SIZE(CTaskSimpleStealthKill, 0x20);

