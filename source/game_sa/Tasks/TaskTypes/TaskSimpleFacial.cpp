#include "StdInc.h"

#include "TaskSimpleFacial.h"

// 0x690C70
CTaskSimpleFacial::CTaskSimpleFacial(eFacialExpression nFacialExpress, int32 nDuration) : CTaskSimple() {
    m_nDuration = nDuration;
    m_nFacialExpression = nFacialExpress;
}

// See Android, looks like **map**
// 0x690CC0
AnimationId CTaskSimpleFacial::GetAnimId(eFacialExpression expression) {
    switch (expression) {
    case eFacialExpression::SURP:      return ANIM_ID_FACSURP;
    case eFacialExpression::SURPM:     return ANIM_ID_FACSURPM;

    case eFacialExpression::URIOS:
    case eFacialExpression::URIOS_1:   return ANIM_ID_FACURIOS;

    case eFacialExpression::ANGER:
    case eFacialExpression::ANGER_1:   return ANIM_ID_FACANGER_0;

    case eFacialExpression::TALK:      return ANIM_ID_FACTALK;
    case eFacialExpression::GUM:       return ANIM_ID_FACGUM;
    default:                           return ANIM_ID_UNDEFINED;
    }
}

// 0x692E50
bool CTaskSimpleFacial::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    auto assoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, GetAnimId(m_nFacialExpression));
    if (assoc) {
        assoc->m_fBlendDelta = -4.0f;
    }
    return true;
}

// 0x692E80
bool CTaskSimpleFacial::ProcessPed(CPed* ped) {
    auto animId = CTaskSimpleFacial::GetAnimId(m_nFacialExpression);
    auto assoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, animId);

    if (RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_FACTALK)) {
        if (animId == ANIM_ID_FACTALK) {
            if (CGeneral::GetRandomNumberInRange(0, 100) < 40) {
                assoc->m_fSpeed = CGeneral::GetRandomNumberInRange(0.5f, 3.0f);
            }
            return false;
        }
        if (assoc) {
            assoc->SetFlag(ANIMATION_FREEZE_LAST_FRAME, true);
            assoc->m_fBlendDelta = -4.0f;
        }
        return true;
    }

    if (!m_Timer.m_bStarted) {
        if (!assoc) {
            CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, animId, 4.0f);
            m_Timer.m_nInterval = m_nDuration;
            m_Timer.m_nStartTime = CTimer::GetTimeInMS();
            m_Timer.m_bStarted = true;
            return false;
        }
        return true;
    }

    if (!assoc)
        return true;

    if (!m_Timer.IsOutOfTime())
        return false;

    assoc->m_fBlendDelta = -4.0f;
    return true;
}
