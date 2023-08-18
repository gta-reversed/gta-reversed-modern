/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimple.h"
class CAnimBlendAssociation;
class CEntity;

class NOTSA_EXPORT_VTABLE CTaskSimpleThrowProjectile : public CTaskSimple {
public:
    bool                   m_bIsAborting;
    bool                   m_bFinished;
    bool                   m_bStarted;
    CAnimBlendAssociation* m_pAnim;
    CEntity*               m_pTarget;
    CVector                m_vecPosition;
    uint32                 m_nStartTime;

public:
    static constexpr auto Type = TASK_SIMPLE_THROW_PROJECTILE;

    CTaskSimpleThrowProjectile(CEntity* target, CVector posn);
    ~CTaskSimpleThrowProjectile() override;

    eTaskType GetTaskType() const override { return Type; } // 0x61F6F0
    CTask* Clone() const override { return new CTaskSimpleThrowProjectile(m_pTarget, m_vecPosition); } // 0x623030
    bool MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;
    bool ProcessPed(CPed* ped) override;

    bool ControlThrow(bool bUpdateStartTime, CEntity* entity, CVector* posn);
    void FinishAnimThrowProjectileCB(CAnimBlendAssociation* anim, void* data);
    void StartAnim(CPed* ped);

    static void InjectHooks();
    CTaskSimpleThrowProjectile* Constructor(CEntity* target, CVector posn);
};
VALIDATE_SIZE(CTaskSimpleThrowProjectile, 0x24);
