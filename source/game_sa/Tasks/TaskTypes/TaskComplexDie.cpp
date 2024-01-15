#include "StdInc.h"

#include "TaskComplexDie.h"

#include "TaskComplexDieInCar.h"
#include "TaskSimpleDie.h"
#include "TaskSimpleDrown.h"
#include "TaskComplexFallToDeath.h"
#include "TaskComplexLeaveCar.h"
#include "TaskSimpleDrownInCar.h"

void CTaskComplexDie::InjectHooks() {
    RH_ScopedClass(CTaskComplexDie);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x630040);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x6300D0);
    RH_ScopedInstall(SayDeathSample, 0x630100);
    RH_ScopedInstall(CreateNextSubTask_Reversed, 0x6301E0);
    RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x6302D0);
}

CTaskComplexDie* CTaskComplexDie::Constructor(eWeaponType nWeaponType, AssocGroupId animGroup, AnimationId animID, float fBlendDelta, float fAnimSpeed, bool bBeingKilledByStealth, bool bFallingToDeath, eDirection nFallToDeathDir, bool bFallToDeathOverRailing) { this->CTaskComplexDie::CTaskComplexDie(nWeaponType, animGroup, animID, fBlendDelta, fAnimSpeed, bBeingKilledByStealth, bFallingToDeath, nFallToDeathDir, bFallToDeathOverRailing); return this; }
bool CTaskComplexDie::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) { return MakeAbortable_Reversed(ped, priority, event); }
CTask* CTaskComplexDie::CreateNextSubTask(CPed* ped) { return CreateNextSubTask_Reversed(ped); }
CTask* CTaskComplexDie::CreateFirstSubTask(CPed* ped) { return CreateFirstSubTask_Reversed(ped); }

// 0x630040
CTaskComplexDie::CTaskComplexDie(
    eWeaponType nWeaponType,
    AssocGroupId animGroup,
    AnimationId animID,
    float fBlendDelta,
    float fAnimSpeed,
    bool bBeingKilledByStealth,
    bool bFallingToDeath,
    eDirection nFallToDeathDir,
    bool bFallToDeathOverRailing
) {
    m_nWeaponType             = nWeaponType;
    m_nAnimID                 = animID;
    m_fBlendDelta             = fBlendDelta;
    m_nAnimGroup              = animGroup;
    m_fAnimSpeed              = fAnimSpeed;
    m_bBeingKilledByStealth   = bBeingKilledByStealth;
    m_bFallingToDeath         = bFallingToDeath;
    m_bFallToDeathOverRailing = bFallToDeathOverRailing;
    m_nFallToDeathDir         = nFallToDeathDir;
};

// 0x6300D0
bool CTaskComplexDie::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_URGENT:
    case ABORT_PRIORITY_IMMEDIATE:
        return m_pSubTask->MakeAbortable(ped, priority, event);
    default:
        return false;
    }
}

// 0x630100
void CTaskComplexDie::SayDeathSample(CPed* ped) const {
    switch (m_nWeaponType) {
    case WEAPON_RAMMEDBYCAR:
    case WEAPON_RUNOVERBYCAR:
        ped->Say(342);
        break;
    case WEAPON_EXPLOSION:
        return;
    case WEAPON_DROWNING:
        ped->Say(341);
        break;
    case WEAPON_FALL:
        ped->Say(342);
        if (CLocalisation::Blood())
            ped->m_pedAudio.AddAudioEvent(AE_PED_CRUNCH, 0.0f, 1.0f, ped);
        break;
    default:
        ped->Say(343);
        break;
    }
}

// 0x6301E0
CTask* CTaskComplexDie::CreateNextSubTask_Reversed(CPed* ped) {
    switch (m_pSubTask->GetTaskType()) {
    case TASK_SIMPLE_DIE:
    case TASK_SIMPLE_DROWN:
    case TASK_COMPLEX_DIE_IN_CAR:
    case TASK_SIMPLE_DROWN_IN_CAR: {
        ped->bKilledByStealth = true;
        return nullptr;
    }
    case TASK_COMPLEX_LEAVE_CAR: {
        return ped->bInVehicle ? new CTaskSimpleDrownInCar() : CreateFirstSubTask(ped);
    }
    default:
        return nullptr;
    }
}

// 0x6302D0
CTask* CTaskComplexDie::CreateFirstSubTask_Reversed(CPed* ped) {
    SayDeathSample(ped);

    if (m_nWeaponType == WEAPON_DROWNING && ped->bInVehicle && !ped->bForceDieInCar) {
        if (ped->m_pVehicle && (ped->m_pVehicle->IsSubPlane() || ped->m_pVehicle->IsSubHeli())) {
            return nullptr;
        }
        return new CTaskComplexLeaveCar(ped->m_pVehicle, 0, 0, false, true);
    }

    ped->SetPedState(PEDSTATE_DIE);
    ped->GetIntelligence()->ClearTasks(false, true);

    if (ped->bInVehicle) // repeated branch
    {
        return new CTaskComplexDieInCar(WEAPON_UNARMED);
    }
    else if (m_nWeaponType == WEAPON_DROWNING)
    {
        return new CTaskSimpleDrown();
    }
    else if (m_bFallingToDeath)
    {
        const auto fallDirection = [&]() -> CVector {
            switch (m_nFallToDeathDir) {
            case eDirection::FORWARD:  return ped->m_matrix->GetForward();
            case eDirection::LEFT:     return ped->m_matrix->GetRight()   * -1.0f;
            case eDirection::BACKWARD: return ped->m_matrix->GetForward() * -1.0f;
            case eDirection::RIGHT:    return ped->m_matrix->GetRight();
            default:
                NOTSA_UNREACHABLE("Originally not initialized");
                return {};
            }
        }();
        return new CTaskComplexFallToDeath(static_cast<int32>(m_nFallToDeathDir), fallDirection, m_bFallToDeathOverRailing, false);
    }

    return new CTaskSimpleDie(m_nAnimGroup, m_nAnimID, m_fBlendDelta, m_fAnimSpeed);
}
