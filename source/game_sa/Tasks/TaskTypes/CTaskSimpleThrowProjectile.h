/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CTaskSimple.h"
#include "CAnimBlendAssociation.h"
#include "CEntity.h"

class CTaskSimpleThrowProjectile : public CTaskSimple {
public:
    bool                   m_bIsAborting;
    bool                   m_bFinished;
    bool                   m_bStarted;
    char                   _pad;
    CAnimBlendAssociation* m_pAnim;
    CEntity*               m_pTarget;
    CVector                m_vecPosition;
    uint32                 m_nStartTime;

public:
    CTaskSimpleThrowProjectile(CEntity* target, CVector posn);
    ~CTaskSimpleThrowProjectile() override;

    CTask* Clone() override { return new CTaskSimpleThrowProjectile(m_pTarget, m_vecPosition); }; // 0x623030
    eTaskType GetTaskType() { return TASK_SIMPLE_THROW; }; // 0x61F6F0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    bool ControlThrow(bool bUpdateStartTime, CEntity* entity, CVector* posn);
    void FinishAnimThrowProjectileCB(CAnimBlendAssociation* anim, void* data);
    void StartAnim(CPed* ped);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskSimpleThrowProjectile* Constructor(CEntity* target, CVector posn);
};

VALIDATE_SIZE(CTaskSimpleThrowProjectile, 0x24);