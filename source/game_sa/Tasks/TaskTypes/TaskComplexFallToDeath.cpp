#include "StdInc.h"

#include "TaskComplexFallToDeath.h"
#include "TaskSimpleInAir.h"
#include "TaskComplexDie.h"
#include "TaskSimpleLand.h"
#include "TaskSimpleDead.h"

void CTaskComplexFallToDeath::InjectHooks() {
    RH_ScopedClass(CTaskComplexFallToDeath);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x679040);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x6790C0);
    RH_ScopedInstall(ControlSubTask_Reversed, 0x679510);
    RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x679120);
    RH_ScopedInstall(CreateNextSubTask_Reversed, 0x679270);
}

CTaskComplexFallToDeath* CTaskComplexFallToDeath::Constructor(int32 direction, const CVector& posn, bool a4, bool a5) { this->CTaskComplexFallToDeath::CTaskComplexFallToDeath(direction, posn, a4, a5); return this; }
bool CTaskComplexFallToDeath::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) { return MakeAbortable_Reversed(ped, priority, event); }
CTask* CTaskComplexFallToDeath::ControlSubTask(CPed* ped) { return ControlSubTask_Reversed(ped); }
CTask* CTaskComplexFallToDeath::CreateFirstSubTask(CPed* ped) { return CreateFirstSubTask_Reversed(ped); }
CTask* CTaskComplexFallToDeath::CreateNextSubTask(CPed* ped) { return CreateNextSubTask_Reversed(ped); }

// 0x679040
CTaskComplexFallToDeath::CTaskComplexFallToDeath(int32 direction, const CVector& posn, bool bOverRailing, bool bTumble) :
    CTaskComplex(),
    m_NudgeDir{ static_cast<eFallDir>(direction) },
    m_NudgeVec{ posn },
    m_KnockedBackAnimID{ ANIM_ID_UNDEFINED },
    m_DeathAnimID{ ANIM_ID_UNDEFINED },
    m_bFallingOverRailing{ bOverRailing },
    m_bTumbleWhilstFalling{ bTumble }
{
}

void CTaskComplexFallToDeath::UpdateAnims(CPed* ped) {
    for (auto& animId : { m_KnockedBackAnimID, m_DeathAnimID }) {
        if (animId != ANIM_ID_UNDEFINED) {
            if (auto assoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, animId)) {
                assoc->m_fBlendDelta = -1000.0f;
            }
        }
    }
}

// 0x6790C0
bool CTaskComplexFallToDeath::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    if (priority != ABORT_PRIORITY_IMMEDIATE) {
        return false;
    }
    UpdateAnims(ped);
    return true;
}

// 0x679510
CTask* CTaskComplexFallToDeath::ControlSubTask_Reversed(CPed* ped) {
    // return plugin::CallMethodAndReturn<CTask*, 0x679510, CTaskComplexFallToDeath*, CPed*>(this, ped);

    if (ped->physicalFlags.bSubmergedInWater) {
        if (!m_bDying) {
            m_bDying = true;
            ped->bIsDrowning = true;
            return new CTaskComplexDie(WEAPON_DROWNING, ANIM_GROUP_DEFAULT, ANIM_ID_DROWN, 4.0f, 1.0f, false, false, eFallDir::FORWARD, false);
        }
    }

    if (!m_bReadyToDie || m_bDying || m_pSubTask->GetTaskType() == TASK_SIMPLE_DEAD) {
        return m_pSubTask;
    }

    if (std::fabsf(ped->m_vecMoveSpeed.z) >= 0.01f) { // todo: check
        return m_pSubTask;
    }

    m_bDying = true;
    m_bLandedWithImpact = true;

    UpdateAnims(ped);
    return new CTaskSimpleLand(ANIM_ID_KO_SKID_FRONT);
}

// 0x679120
CTask* CTaskComplexFallToDeath::CreateFirstSubTask_Reversed(CPed* ped) {
    ped->bIsStanding = false;
    ped->ApplyMoveForce({
        ms_LateralForceMagnitude * m_NudgeVec.x,
        ms_LateralForceMagnitude * m_NudgeVec.y, m_bFallingOverRailing ? ms_OverRailingVerticalForce : ms_NoRailingVerticalForce
    });

    m_KnockedBackAnimID = [&] {
        switch (m_NudgeDir) {
        case eFallDir::FORWARD:  return ANIM_ID_KO_SKID_BACK;
        case eFallDir::LEFT:     return ANIM_ID_KO_SPIN_L;
        case eFallDir::BACKWARD: return ANIM_ID_KO_SKID_FRONT;
        case eFallDir::RIGHT:    return ANIM_ID_KO_SPIN_R;
        default:
            NOTSA_UNREACHABLE("");
            return ANIM_ID_UNDEFINED;
        }
    }();

    if (m_KnockedBackAnimID >= ANIM_ID_WALK && m_KnockedBackAnimID < ANIM_ID_ROADCROSS) {
        CAnimManager::BlendAnimation(ped->m_pRwClump, nullptr, m_KnockedBackAnimID, 1000.0f);
    }

    return new CTaskSimpleInAir(false, true, false);
}

// 0x679270
CTask* CTaskComplexFallToDeath::CreateNextSubTask_Reversed(CPed* ped) {
    // return plugin::CallMethodAndReturn<CTask*, 0x679270, CTaskComplexFallToDeath*, CPed*>(this, ped);

    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_IN_AIR: {
        m_bLandedWithImpact = std::fabsf(ped->m_vecMoveSpeed.z) >= 0.1f; // todo: check
        return new CTaskSimpleLand(m_bLandedWithImpact ? ANIM_ID_KO_SKID_FRONT : ANIM_ID_UNDEFINED);
    }
    case TASK_SIMPLE_LAND: {
        if (!m_bReadyToDie) {
            if (std::fabsf(ped->m_vecMoveSpeed.z) < 0.01f && (!ped->m_pContactEntity || ped->m_pContactEntity->IsBuilding())) { // todo: check
                m_bReadyToDie = true;
                return new CTaskSimpleInAir(false, true, false);
            }
        }

        if (!m_bLandedWithImpact) {
            if (m_KnockedBackAnimID != ANIM_ID_UNDEFINED) {
                if (auto assoc = RpAnimBlendClumpGetAssociation(ped->m_pRwClump, m_KnockedBackAnimID)) {
                    assoc->m_fBlendDelta = -1000.0f;
                }
            }
            m_DeathAnimID = ANIM_ID_KO_SKID_FRONT;
            CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_KO_SKID_FRONT, 8.0f);
        }

        ped->GetIntelligence()->ClearTasks(false, true);
        return new CTaskSimpleDead(CTimer::GetTimeInMS(), false);
    }
    default:
        return nullptr;
    }
}
