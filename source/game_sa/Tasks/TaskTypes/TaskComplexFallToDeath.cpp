#include "StdInc.h"

#include "TaskComplexFallToDeath.h"
#include "TaskSimpleInAir.h"

// 0x679040
CTaskComplexFallToDeath::CTaskComplexFallToDeath(int32 type, const CVector& posn, bool a4, bool a5) {
    m_posn     = posn;
    m_nAnimId  = ANIM_ID_UNDEFINED;
    m_nAnimId1 = ANIM_ID_UNDEFINED;
    m_nType    = type;
    // todo: m_nFlags   = m_nFlags & 0xE0 | (8 * (a4 | (2 * a5)));
}

// 0x6790C0
bool CTaskComplexFallToDeath::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (priority != ABORT_PRIORITY_IMMEDIATE)
        return false;

    // anim 1
    if (m_nAnimId != ANIM_ID_UNDEFINED) {
        auto association = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_nAnimId);
        if (association)
            association->m_fBlendDelta = -1000.0f;
    }

    // anim 2
    if (m_nAnimId1 != ANIM_ID_UNDEFINED) {
        auto association = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_nAnimId1);
        if (association)
            association->m_fBlendDelta = -1000.0f;
    }

    return true;
}

// 0x679510
CTask* CTaskComplexFallToDeath::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x679510, CTaskComplexFallToDeath*, CPed*>(this, ped);
}

// 0x679120
CTask* CTaskComplexFallToDeath::CreateFirstSubTask(CPed* ped) {
    ped->m_nPedFlags &= ~1u; // bIsStanding = false;
    ped->ApplyMoveForce({
        ms_LateralForceMagnitude * m_posn.x,
        ms_LateralForceMagnitude * m_posn.y,
        (m_nFlags & 8) != 0 ? ms_OverRailingVerticalForce : ms_NoRailingVerticalForce
    });

    switch (m_nType) {
    case 0:
        m_nAnimId = ANIM_ID_KO_SKID_BACK;
        break;
    case 1:
        m_nAnimId = ANIM_ID_KO_SPIN_L;
        break;
    case 2:
        m_nAnimId = ANIM_ID_KO_SKID_FRONT;
        break;
    case 3:
        m_nAnimId = ANIM_ID_KO_SPIN_R;
        break;
    default:
        break;
    }

    if (m_nAnimId >= 0 && m_nAnimId < 4)
        CAnimManager::BlendAnimation(ped->m_pRwClump, nullptr, m_nAnimId, 1000.0f);

    return new CTaskSimpleInAir(false, true, false);
}

// 0x679270
CTask* CTaskComplexFallToDeath::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x679270, CTaskComplexFallToDeath*, CPed*>(this, ped);
}
