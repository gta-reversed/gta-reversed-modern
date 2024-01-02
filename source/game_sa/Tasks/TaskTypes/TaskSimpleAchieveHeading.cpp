#include "StdInc.h"

#include "TaskSimpleAchieveHeading.h"
#include "IKChainManager_c.h"

// 0x667E20
CTaskSimpleAchieveHeading::CTaskSimpleAchieveHeading(float fAngle, float changeRateMult, float maxHeading) : CTaskSimple() {
    m_b1              = false;
    m_fAngle          = fAngle;
    m_fChangeRateMult = changeRateMult;
    m_fMaxHeading     = maxHeading;
}

// 0x668060
bool CTaskSimpleAchieveHeading::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x668060, CTaskSimpleAchieveHeading*, CPed*>(this, ped); // untested

    if (ped->bInVehicle)
        return true;

    ped->RestoreHeadingRate();
    ped->m_fHeadingChangeRate *= m_fChangeRateMult;
    ped->SetMoveState(PEDMOVE_STILL);
    ped->SetMoveAnim();
    ped->m_fAimingRotation = m_fAngle;

    const auto c = std::fabs(m_fAngle - ped->m_fCurrentRotation);
    const auto b = CGeneral::LimitRadianAngle(c);
    if (std::fabs(b) < m_fMaxHeading) {
        ped->m_fAimingRotation = ped->m_fCurrentRotation;
        ped->RestoreHeadingRate();
        QuitIK(ped);
        return true;
    }
    SetUpIK(ped);
    return false;
}

// 0x667EB0
bool CTaskSimpleAchieveHeading::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    QuitIK(ped);

    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE:
        ped->m_fAimingRotation = ped->m_fCurrentRotation;
        ped->RestoreHeadingRate();
        return true;
    default:
        m_fMaxHeading = TWO_PI;
        ped->m_fAimingRotation = ped->m_fCurrentRotation;
        return false;
    }
}

// 0x667E80
void CTaskSimpleAchieveHeading::QuitIK(CPed* ped) const {
    if (m_b1 && g_ikChainMan.IsLooking(ped)) {
        g_ikChainMan.AbortLookAt(ped, 250);
    }
}

// 0x667F20
void CTaskSimpleAchieveHeading::SetUpIK(CPed* ped) {
    return plugin::CallMethod<0x667F20, CTaskSimpleAchieveHeading*, CPed*>(this, ped); // untested

    if (ped == FindPlayerPed() && !CPad::GetPad()->DisablePlayerControls)
        return;

    if (!ped->GetIsOnScreen())
        return;

    if (m_b1 || g_ikChainMan.GetLookAtEntity(ped) || ped->GetTaskManager().GetTaskSecondary(TASK_SECONDARY_IK))
        return;

    if (m_pParentTask && m_pParentTask->GetTaskType() == TASK_COMPLEX_AVOID_OTHER_PED_WHILE_WANDERING || m_pParentTask->GetTaskType() == TASK_COMPLEX_AVOID_ENTITY)
        return;

    auto pos = CVector{
        std::sin(m_fAngle) + std::sin(m_fAngle),
        std::cos(m_fAngle) + std::cos(m_fAngle),
        0.61f
    } + ped->GetPosition();
    g_ikChainMan.LookAt("TaskAchvHeading", ped, nullptr, 5000, BONE_UNKNOWN, &pos, false, 0.25f, 500, 3, false);
    m_b1 = true;
}

// unknown addr
void CTaskSimpleAchieveHeading::SetHeading(float heading, float maxHeading, float changeRateMult) {
    m_fAngle          = heading;
    m_fChangeRateMult = changeRateMult;
    m_fMaxHeading     = maxHeading;
}
