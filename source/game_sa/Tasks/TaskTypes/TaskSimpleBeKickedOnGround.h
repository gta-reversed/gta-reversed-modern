#pragma once

#include "TaskSimple.h"
class CAnimBlendAssociation;

class CTaskSimpleBeKickedOnGround : public CTaskSimple{
public:
    bool                   m_animHasFinished{};
    CAnimBlendAssociation* m_anim{};
public:
    static void InjectHooks();

    constexpr static auto Type = eTaskType::TASK_SIMPLE_BE_KICKED_ON_GROUND;

    CTaskSimpleBeKickedOnGround();
    ~CTaskSimpleBeKickedOnGround();

    static void FinishAnimBeKickedOnGroundCB(CAnimBlendAssociation* anim, void* data);
    void StartAnim(CPed* ped);

    CTask* Clone() override { return new CTaskSimpleBeKickedOnGround{ *this }; }
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed * ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed * ped) override;

private: // Wrappers for hooks
    // 0x61FC20
    CTaskSimpleBeKickedOnGround* Constructor() { this->CTaskSimpleBeKickedOnGround::CTaskSimpleBeKickedOnGround(); return this; }

    // 0x61FC50
    CTaskSimpleBeKickedOnGround* Destructor() { this->CTaskSimpleBeKickedOnGround::~CTaskSimpleBeKickedOnGround(); return this; }

};
VALIDATE_SIZE(CTaskSimpleBeKickedOnGround, 0x10);
