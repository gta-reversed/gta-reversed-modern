#include "StdInc.h"

#include "TaskComplexFallToDeath.h"
#include "TaskSimpleInAir.h"

// 0x679040
CTaskComplexFallToDeath::CTaskComplexFallToDeath(int32 direction, const CVector& posn, bool a4, bool a5) : CTaskComplex() {
    m_Posn = posn;
    m_nAnimId         = ANIM_ID_UNDEFINED;
    m_nAnimId1        = ANIM_ID_UNDEFINED;
    m_nFallToDeathDir = static_cast<eFallDir>(direction);
    b0x1              = false;
    b0x2              = false;
    b0x4              = false;
    b0x8              = a4;
    b0x10             = a5;
}

// 0x6790C0
bool CTaskComplexFallToDeath::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (priority != ABORT_PRIORITY_IMMEDIATE)
        return false;

    for (auto& animId : { m_nAnimId, m_nAnimId1 }) {
        if (animId != ANIM_ID_UNDEFINED) {
            if (const auto& association = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, animId))
                association->m_fBlendDelta = -1000.0f;
        }
    }

    return true;
}

// 0x679510
CTask* CTaskComplexFallToDeath::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x679510, CTaskComplexFallToDeath*, CPed*>(this, ped);
}

// 0x679120
CTask* CTaskComplexFallToDeath::CreateFirstSubTask(CPed* ped) {
    ped->bIsStanding = false;
    ped->ApplyMoveForce({
        ms_LateralForceMagnitude * m_Posn.x,
        ms_LateralForceMagnitude * m_Posn.y,
        b0x8 ? ms_OverRailingVerticalForce : ms_NoRailingVerticalForce
    });

    // what?
    switch (m_nFallToDeathDir) {
    case eFallDir::FORWARD:
        m_nAnimId = ANIM_ID_KO_SKID_BACK;
        break;
    case eFallDir::LEFT:
        m_nAnimId = ANIM_ID_KO_SPIN_L;
        break;
    case eFallDir::BACKWARD:
        m_nAnimId = ANIM_ID_KO_SKID_FRONT;
        break;
    case eFallDir::RIGHT:
        m_nAnimId = ANIM_ID_KO_SPIN_R;
        break;
    default:
        break;
    }

    if (m_nAnimId >= ANIM_ID_WALK && m_nAnimId < ANIM_ID_ROADCROSS)
        CAnimManager::BlendAnimation(ped->m_pRwClump, nullptr, m_nAnimId, 1000.0f);

    return new CTaskSimpleInAir(false, true, false);
}

// 0x679270
CTask* CTaskComplexFallToDeath::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x679270, CTaskComplexFallToDeath*, CPed*>(this, ped);
}
