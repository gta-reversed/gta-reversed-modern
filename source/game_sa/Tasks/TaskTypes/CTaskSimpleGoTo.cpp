#include "StdInc.h"

float& CTaskSimpleGoTo::ms_fLookAtThresholdDotProduct = *(float*)0xC18D48;

void CTaskSimpleGoTo::InjectHooks() {
    HookInstall(0x6679C0, &CTaskSimpleGoTo::Constructor, 7);
    HookInstall(0x667A10, &CTaskSimpleGoTo::HasCircledTarget, 7);
    HookInstall(0x667AD0, &CTaskSimpleGoTo::SetUpIK, 7);
    HookInstall(0x667CA0, &CTaskSimpleGoTo::QuitIK, 7);
}

CTaskSimpleGoTo::CTaskSimpleGoTo(int moveState, const CVector& targetPoint, float fRadius) 
{
    m_moveState = moveState;
    m_vecTargetPoint = targetPoint;
    m_fRadius = fRadius;
    m_GoToFlags = 0;
}

CTaskSimpleGoTo::~CTaskSimpleGoTo()
{
    // nothing here
}

CTaskSimpleGoTo* CTaskSimpleGoTo::Constructor(int moveState, const CVector& targetPoint, float fRadius) 
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTaskSimpleGoTo*, 0x6679C0, CTask*, int, const CVector&, float>
        (this, moveState, targetPoint, fRadius);
#else
    this->CTaskSimpleGoTo::CTaskSimpleGoTo(moveState, targetPoint, fRadius);
    return this;
#endif
}


bool CTaskSimpleGoTo::HasCircledTarget(CPed* pPed) 
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<bool, 0x667A10, CTask*, CPed*>(this, pPed);
#else
    const CVector& pedPos = pPed->GetPosition();
    if (!pPed->bIgnoreHeightCheckOnGotoPointTask && fabs(pedPos.z - m_vecTargetPoint.z) >= 2.0f)
        return false;
    if (m_vecTargetPoint.x > pedPos.x)
        gotoFlags.m_b01 = true;
    else if (m_vecTargetPoint.x < pedPos.x)
        gotoFlags.m_b02 = true;
    if (m_vecTargetPoint.y > pedPos.y)
        gotoFlags.m_b03 = true;
    else if (m_vecTargetPoint.y < pedPos.y) 
        gotoFlags.m_b04 = true;
    if (gotoFlags.m_b01 && gotoFlags.m_b02 && gotoFlags.m_b03 && gotoFlags.m_b04)
        return true;
    return false;
#endif
}

void CTaskSimpleGoTo::SetUpIK(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethod<0x667AD0, CTask*, CPed*>(this, pPed);
#else
    if (pPed->GetIsOnScreen() && !gotoFlags.m_bIsIKChainSet
        && !g_ikChainMan->GetLookAtEntity(pPed)
        && !pPed->m_pIntelligence->m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_IK)
        && (pPed != FindPlayerPed(-1) || CPad::GetPad(0)->DisablePlayerControls)) {
        if (!m_pParentTask ||
            m_pParentTask->GetId() != TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING &&
            m_pParentTask->GetId() != TASK_COMPLEX_AVOID_ENTITY) {
            CVector vecDistance = m_vecTargetPoint - pPed->GetPosition();
            if (vecDistance.SquaredMagnitude() > 9.0f) {
                CVector direction(vecDistance);
                direction.Normalise();
                if (DotProduct(&direction, &pPed->GetForward()) < ms_fLookAtThresholdDotProduct) {
                    CVector position = direction + direction;
                    position.x += m_vecTargetPoint.x;
                    position.y += m_vecTargetPoint.y;
                    position.z += pPed->GetPosition().z + 0.61f;
                    g_ikChainMan->LookAt("TaskGoTo", pPed, 0, 5000, BONE_UNKNOWN, (RwV3d*)&position, 0, 0.25f, 500, 3, false);
                    gotoFlags.m_bIsIKChainSet = true;
                }
            }
        }
    }
#endif
}

void CTaskSimpleGoTo::QuitIK(CPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethod<0x667CA0, CTask*, CPed*>(this, pPed);
#else
    if (gotoFlags.m_bIsIKChainSet && g_ikChainMan->IsLooking(pPed))
        g_ikChainMan->AbortLookAt(pPed, 250);
#endif
}