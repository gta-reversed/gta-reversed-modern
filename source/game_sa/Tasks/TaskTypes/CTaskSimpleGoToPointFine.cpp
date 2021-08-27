#include "StdInc.h"

void CTaskSimpleGoToPointFine::InjectHooks()
{
    HookInstall(0x65EEB0, &CTaskSimpleGoToPointFine::Constructor);
    HookInstall(0x662040, &CTaskSimpleGoToPointFine::Clone_Reversed);
    HookInstall(0x663500, &CTaskSimpleGoToPointFine::MakeAbortable_Reversed);
    HookInstall(0x663540, &CTaskSimpleGoToPointFine::ProcessPed_Reversed);
    HookInstall(0x65EF80, &CTaskSimpleGoToPointFine::SetBlendedMoveAnim);
}

CTaskSimpleGoToPointFine::CTaskSimpleGoToPointFine(float fBlend, CVector targetPoint, float fRadius, int unused) :
    CTaskSimpleGoTo(PEDMOVE_WALK, targetPoint, fRadius)
{
    m_fBlend = fBlend;
}

CTaskSimpleGoToPointFine::~CTaskSimpleGoToPointFine()
{
    // nothing here
}

CTaskSimpleGoToPointFine* CTaskSimpleGoToPointFine::Constructor(float fBlend, CVector targetPoint, float fRadius, int unused)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTaskSimpleGoToPointFine*, 0x65EEB0, CTask*, float, CVector, float, int>
        (this, fBlend, targetPoint, fRadius, unused);
#else
    this->CTaskSimpleGoToPointFine::CTaskSimpleGoToPointFine(fBlend, targetPoint, fRadius, unused);
    return this;
#endif
}

CTask* CTaskSimpleGoToPointFine::Clone()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x662040, CTask*>(this);
#else
    return CTaskSimpleGoToPointFine::Clone_Reversed();
#endif
}

bool CTaskSimpleGoToPointFine::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<bool, 0x663500, CTask*, CPed*, int, const CEvent*>(this, ped, priority, event);
#else
    return CTaskSimpleGoToPointFine::MakeAbortable_Reversed(ped, priority, event);
#endif
}

bool CTaskSimpleGoToPointFine::ProcessPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<bool, 0x663540, CTask*, CPed*>(this, ped);
#else
    return CTaskSimpleGoToPointFine::ProcessPed_Reversed(ped);
#endif
}

CTask* CTaskSimpleGoToPointFine::Clone_Reversed()
{
    return new CTaskSimpleGoToPointFine(m_fBlend, m_vecTargetPoint, m_fRadius, 0);
}

bool CTaskSimpleGoToPointFine::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    QuitIK(ped);
    ped->SetMoveState(PEDMOVE_STILL);
    ped->SetMoveAnim();
    ped->SetMoveState(static_cast<eMoveState>(m_moveState));
    ped->SetMoveAnim();
    return true;
}

bool CTaskSimpleGoToPointFine::ProcessPed_Reversed(CPed* ped)
{
    CVector2D vecDistance = m_vecTargetPoint - ped->GetPosition();
    if (m_fRadius * m_fRadius >= vecDistance.SquaredMagnitude() || HasCircledTarget(ped)) {
        QuitIK(ped);
        ped->SetMoveState(PEDMOVE_STILL);
        ped->SetMoveAnim();
        ped->SetMoveState(static_cast<eMoveState>(m_moveState));
        ped->SetMoveAnim();
        return true;
    }
    SetBlendedMoveAnim(ped);
    float fAngleInRadians = CGeneral::GetRadianAngleBetweenPoints(vecDistance.x, vecDistance.y, 0.0f, 0.0f);
    ped->m_fAimingRotation = CGeneral::LimitRadianAngle(fAngleInRadians);
    SetUpIK(ped);
    return false;
}

void CTaskSimpleGoToPointFine::SetBlendedMoveAnim(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethod<0x65EF80, CTask*, CPed*>(this, ped);
#else
    auto pIdleAnimAssoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_IDLE);
    auto pWalkAnimAssoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_WALK);
    auto pRunAnimAssoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_RUN);
    auto pSprintAnimAssoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_SPRINT);
    auto pIdleTiredAnimAssoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, ANIM_ID_IDLE_TIRED);
    if (ped->bIsDucking && ped->m_pIntelligence->GetTaskDuck(false)) {
        float fMoveSpeedY = m_fBlend * 0.5f;
        if (fMoveSpeedY > 1.0f)
            fMoveSpeedY = 1.0f;
        CTaskSimpleDuck * pDuckTask = ped->m_pIntelligence->GetTaskDuck(false);
        pDuckTask->ControlDuckMove(0.0, -fMoveSpeedY);
        return;
    }
    if (ped->bResetWalkAnims) {
        if (pWalkAnimAssoc)
            pWalkAnimAssoc->SetCurrentTime(0.0f);
        if (pRunAnimAssoc)
            pRunAnimAssoc->SetCurrentTime(0.0f);
        if (pSprintAnimAssoc)
            pSprintAnimAssoc->SetCurrentTime(0.0f);
        ped->bResetWalkAnims = false;
    }
    if (m_fBlend == 0.0f) {
        if (!pIdleAnimAssoc)
            CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_IDLE, 4.0f);
        if (pWalkAnimAssoc)
            delete pWalkAnimAssoc;
        if (pRunAnimAssoc)
            delete pRunAnimAssoc;
        if (pSprintAnimAssoc)
            delete pSprintAnimAssoc;
        ped->m_nMoveState = PEDMOVE_STILL;
        m_moveState = PEDMOVE_STILL;
        return;
    }
    if (pIdleAnimAssoc) {
        if (pWalkAnimAssoc)
            pWalkAnimAssoc->SetCurrentTime(0.0f);
        if (pRunAnimAssoc)
            pRunAnimAssoc->SetCurrentTime(0.0f);
        delete pIdleAnimAssoc;
    }
    if (pIdleTiredAnimAssoc) {
        pIdleTiredAnimAssoc->m_fBlendDelta = -4.0f;
        delete pIdleTiredAnimAssoc;
    }
    eMoveState moveState = PEDMOVE_WALK;
    if (m_fBlend > 1.0f) {
        if (m_fBlend > 2.0f) {
            if (m_fBlend > 3.0f)
                return;
            if (pWalkAnimAssoc)
                delete pWalkAnimAssoc;
            if (!pRunAnimAssoc) {
                pRunAnimAssoc = CAnimManager::AddAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_RUN);
                pRunAnimAssoc->m_fBlendAmount = 0.0f;
                pRunAnimAssoc->m_fSpeed = 1.0f;
            }
            pRunAnimAssoc->m_nFlags |= ANIM_FLAG_STARTED;
            pRunAnimAssoc->m_fBlendDelta = 0.0f;
            pRunAnimAssoc->m_fBlendAmount = 3.0f - m_fBlend;
            if (!pSprintAnimAssoc)
            {
                pSprintAnimAssoc = CAnimManager::AddAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_SPRINT);
                pSprintAnimAssoc->m_fBlendAmount = 0.0f;
                pSprintAnimAssoc->m_fSpeed = 1.0f;
            }
            pSprintAnimAssoc->m_nFlags |= ANIM_FLAG_STARTED;
            pSprintAnimAssoc->m_fBlendDelta = 0.0f;
            moveState = PEDMOVE_SPRINT;
            pSprintAnimAssoc->m_fBlendAmount = m_fBlend - 2.0f;
        }
        else {
            if (!pWalkAnimAssoc) {
                pWalkAnimAssoc = CAnimManager::AddAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_WALK);
                pWalkAnimAssoc->m_fBlendAmount = 0.0f;
                pWalkAnimAssoc->m_fSpeed = 1.0f;
            }
            pWalkAnimAssoc->m_nFlags |= ANIM_FLAG_STARTED;
            pWalkAnimAssoc->m_fBlendDelta = 0.0f;
            pWalkAnimAssoc->m_fBlendAmount = 2.0f - m_fBlend;
            if (!pRunAnimAssoc)
            {
                pRunAnimAssoc = CAnimManager::AddAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_RUN);
                pRunAnimAssoc->m_fBlendAmount = 0.0f;
                pRunAnimAssoc->m_fSpeed = 1.0f;
            }
            pRunAnimAssoc->m_nFlags |= ANIM_FLAG_STARTED;
            pRunAnimAssoc->m_fBlendDelta = 0.0f;
            pRunAnimAssoc->m_fBlendAmount = m_fBlend - 1.0f;
            if (pSprintAnimAssoc)
                delete pSprintAnimAssoc;
            moveState = PEDMOVE_RUN;
        }
    }
    else {
        if (!pWalkAnimAssoc) {
            pWalkAnimAssoc = CAnimManager::AddAnimation(ped->m_pRwClump, ped->m_nAnimGroup, ANIM_ID_WALK);
            pWalkAnimAssoc->m_fBlendAmount = 0.0f;
            pWalkAnimAssoc->m_fSpeed = 1.0f;
        }
        pWalkAnimAssoc->m_nFlags |= ANIM_FLAG_STARTED;
        pWalkAnimAssoc->m_fBlendAmount = 1.0f;
        pWalkAnimAssoc->m_fBlendDelta = 0.0f;
        if (pRunAnimAssoc)
            delete pRunAnimAssoc;
        if (pSprintAnimAssoc)
            delete pSprintAnimAssoc;
    }
    ped->SetMoveState(moveState);
    ped->m_nSwimmingMoveState = moveState;
    m_moveState = moveState;
#endif
}
