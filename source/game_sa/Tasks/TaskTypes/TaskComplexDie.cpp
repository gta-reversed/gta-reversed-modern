#include "StdInc.h"

#include "TaskComplexDie.h"

#include "TaskComplexDieInCar.h"
#include "TaskSimpleDie.h"
#include "TaskSimpleDrown.h"
#include "TaskComplexFallToDeath.h"
#include "TaskComplexLeaveCar.h"
#include "TaskSimpleDrownInCar.h"

// 0x630040
CTaskComplexDie::CTaskComplexDie(eWeaponType nWeaponType,
                                 AssocGroupId animGroup,
                                 AnimationId animID,
                                 float fBlendDelta,
                                 float fAnimSpeed,
                                 bool bBeingKilledByStealth,
                                 bool bFallingToDeath, eFallDir nFallToDeathDir,
                                 bool bFallToDeathOverRailing) : CTaskComplex()
{
    m_nWeaponType           = nWeaponType;
    m_nAnimID               = animID;
    m_fBlendDelta           = fBlendDelta;
    m_nAnimGroup            = animGroup;
    m_fAnimSpeed            = fAnimSpeed;
    bBeingKilledByStealth   = bBeingKilledByStealth;
    bFallingToDeath         = bFallingToDeath;
    bFallToDeathOverRailing = bFallToDeathOverRailing;
    m_nFallToDeathDir       = nFallToDeathDir;
};

// 0x636060
CTask* CTaskComplexDie::Clone() {
    return new CTaskComplexDie(
        m_nWeaponType,
        m_nAnimGroup,
        m_nAnimID,
        m_fBlendDelta,
        m_fAnimSpeed,
        bBeingKilledByStealth,
        bFallingToDeath,
        m_nFallToDeathDir,
        bFallToDeathOverRailing
    );
}

// 0x6300D0
bool CTaskComplexDie::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return (priority == ABORT_PRIORITY_URGENT || priority == ABORT_PRIORITY_IMMEDIATE) && m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x630100
void CTaskComplexDie::SayDeathSample(CPed* ped) {
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
            ped->m_pedAudio.AddAudioEvent(119, 0.0f, 1.0, ped, 0, 0, 0);
        break;
    default:
        ped->Say(343);
        break;
    }
}

// 0x6301E0
CTask* CTaskComplexDie::CreateNextSubTask(CPed* ped) {
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
    }
    // todo: warning C4715: 'CTaskComplexDie::CreateNextSubTask': not all control paths return a value
}

// 0x6302D0
CTask* CTaskComplexDie::CreateFirstSubTask(CPed* ped) {
    SayDeathSample(ped);
    if (m_nWeaponType != WEAPON_DROWNING
        || !ped->bInVehicle
        || ped->bForceDieInCar
        || ped->m_pVehicle && (ped->m_pVehicle->IsSubPlane() || ped->m_pVehicle->IsSubHeli())
    ) {
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
        else if (bFallingToDeath)
        {
            const auto GetFallDirection = [=]() -> CVector {
                switch (m_nFallToDeathDir) {
                case eFallDir::FORWARD:
                    return ped->m_matrix->GetForward();
                case eFallDir::LEFT:
                    return ped->m_matrix->GetRight() * -1.0f;
                case eFallDir::BACKWARD:
                    return ped->m_matrix->GetForward() * -1.0f;
                case eFallDir::RIGHT:
                    return ped->m_matrix->GetRight();
                default:
                    // Originally not initialized
                    // Just to return something so compiler doesn't cry
                    return {};
                }
            };
            return new CTaskComplexFallToDeath(static_cast<int32>(m_nFallToDeathDir), GetFallDirection(), bFallToDeathOverRailing, false);
        } else {
            return new CTaskSimpleDie(m_nAnimGroup, m_nAnimID, m_fBlendDelta, m_fAnimSpeed);
        }
    }

    return new CTaskComplexLeaveCar(ped->m_pVehicle, 0, 0, false, true);
}
