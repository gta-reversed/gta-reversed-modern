#pragma once

#include "TaskSimple.h"
class CAnimBlendAssociation;

class CTaskSimpleBeKickedOnGround : public CTaskSimple{
public:
    bool m_bIsFinished;
    CAnimBlendAssociation* m_Anim;

public:
    constexpr static auto Type = TASK_SIMPLE_BE_KICKED_ON_GROUND;

    CTaskSimpleBeKickedOnGround();
    ~CTaskSimpleBeKickedOnGround() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleBeKickedOnGround(); }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

    void StartAnim(CPed* ped);
    static void FinishAnimBeKickedOnGroundCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleBeKickedOnGround* Constructor() { this->CTaskSimpleBeKickedOnGround::CTaskSimpleBeKickedOnGround(); return this; }
    CTaskSimpleBeKickedOnGround* Destructor() { this->CTaskSimpleBeKickedOnGround::~CTaskSimpleBeKickedOnGround(); return this; }
};
VALIDATE_SIZE(CTaskSimpleBeKickedOnGround, 0x10);
