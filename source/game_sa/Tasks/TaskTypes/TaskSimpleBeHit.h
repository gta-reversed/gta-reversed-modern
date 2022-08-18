#pragma once

#include "TaskSimple.h"
#include "Base.h"
#include "AnimationEnums.h"
#include "Ped.h" // ePedPieceTypes

class CAnimBlendAssociation;

class CTaskSimpleBeHit : public CTaskSimple {
public:
    CPed* m_attacker{}; // 8
    bool m_finishedOrAborted{}; // 0xC
    bool m_hasBlendedAnim{}; // 0xD
    AnimationId m_animId{}; // 0x10
    AssocGroupId m_nAnimGroup{}; // 0x14
    ePedPieceTypes m_pedPiece{}; // 0x18
    int32 m_dmgHealth{}; // 0x1C
    int32 m_dmgArmor{}; // 0x20
    CAnimBlendAssociation * m_anim{}; // 0x24

public:
    static void InjectHooks();

    constexpr static auto Type = eTaskType::TASK_SIMPLE_BE_HIT;

    CTaskSimpleBeHit(CPed * ped, ePedPieceTypes pedPieceType, int32 damageArmor, int32 damageHealth);
    CTaskSimpleBeHit(const CTaskSimpleBeHit& o);
    ~CTaskSimpleBeHit();

    static void FinishAnimBeHitCB(CAnimBlendAssociation * a1, void * task);

    void StartAnim(CPed * a2);

    CTask* Clone() override { return new CTaskSimpleBeHit{ *this }; }
    eTaskType GetTaskType() override { return Type; }
    bool MakeAbortable(CPed * ped, eAbortPriority priority, CEvent const* event) override;
    bool ProcessPed(CPed * ped) override;

private: // Wrappers for hooks

// 0x620780
CTaskSimpleBeHit* Constructor(CPed * ped, ePedPieceTypes pedPieceType, int32 damageArmor, int32 damageHealth) {
    this->CTaskSimpleBeHit::CTaskSimpleBeHit(ped, pedPieceType, damageArmor, damageHealth);
    return this;
}

// 0x620810
CTaskSimpleBeHit* Destructor() {
    this->CTaskSimpleBeHit::~CTaskSimpleBeHit();
    return this;
}

};
VALIDATE_SIZE(CTaskSimpleBeHit, 0x28);
