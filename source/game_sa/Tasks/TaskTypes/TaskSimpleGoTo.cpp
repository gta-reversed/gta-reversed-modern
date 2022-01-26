#include "StdInc.h"

#include "TaskSimpleGoTo.h"

#include "IKChainManager_c.h"

float& CTaskSimpleGoTo::ms_fLookAtThresholdDotProduct = *(float*)0xC18D48;

void CTaskSimpleGoTo::InjectHooks() {
    RH_ScopedInstall(Constructor, 0x6679C0);
    RH_ScopedInstall(HasCircledTarget, 0x667A10);
    RH_ScopedInstall(SetUpIK, 0x667AD0);
    RH_ScopedInstall(QuitIK, 0x667CA0);
}

CTaskSimpleGoTo::CTaskSimpleGoTo(int32 moveState, const CVector& targetPoint, float fRadius)
{
    m_moveState = moveState;
    m_vecTargetPoint = targetPoint;
    m_fRadius = fRadius;
    m_GoToFlags = 0;
}

// 0x6679C0
CTaskSimpleGoTo* CTaskSimpleGoTo::Constructor(int32 moveState, const CVector& targetPoint, float fRadius)
{
    this->CTaskSimpleGoTo::CTaskSimpleGoTo(moveState, targetPoint, fRadius);
    return this;
}

// 0x667A10
bool CTaskSimpleGoTo::HasCircledTarget(CPed* ped) 
{
    const CVector& pedPos = ped->GetPosition();
    if (!ped->bIgnoreHeightCheckOnGotoPointTask && fabs(pedPos.z - m_vecTargetPoint.z) >= 2.0f)
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
}

// 0x667AD0
void CTaskSimpleGoTo::SetUpIK(CPed* ped)
{
    if (ped->GetIsOnScreen() && !gotoFlags.m_bIsIKChainSet
        && !g_ikChainMan.GetLookAtEntity(ped)
        && !ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_IK)
        && (ped != FindPlayerPed(-1) || CPad::GetPad(0)->DisablePlayerControls)) {
        if (!m_pParentTask || m_pParentTask->GetTaskType() != TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING && m_pParentTask->GetTaskType() != TASK_COMPLEX_AVOID_ENTITY) {
            CVector vecDistance = m_vecTargetPoint - ped->GetPosition();
            if (vecDistance.SquaredMagnitude() > 9.0f) {
                CVector direction(vecDistance);
                direction.Normalise();
                if (DotProduct(&direction, &ped->GetForward()) < ms_fLookAtThresholdDotProduct) {
                    CVector position = direction + direction;
                    position.x += m_vecTargetPoint.x;
                    position.y += m_vecTargetPoint.y;
                    position.z += ped->GetPosition().z + 0.61f;
                    g_ikChainMan.LookAt("TaskGoTo", ped, nullptr, 5000, BONE_UNKNOWN, &position, false, 0.25f, 500, 3, false);
                    gotoFlags.m_bIsIKChainSet = true;
                }
            }
        }
    }
}

// 0x667CA0
void CTaskSimpleGoTo::QuitIK(CPed* ped)
{
    if (gotoFlags.m_bIsIKChainSet && g_ikChainMan.IsLooking(ped))
        g_ikChainMan.AbortLookAt(ped, 250);
}
