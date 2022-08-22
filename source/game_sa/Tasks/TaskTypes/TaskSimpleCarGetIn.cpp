#include "StdInc.h"

#include "TaskSimpleCarGetIn.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleCarGetIn::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarGetIn, 0x86ed50, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x646690);
    RH_ScopedInstall(Destructor, 0x646710);
    RH_ScopedInstall(StartAnim, 0x64B2D0);
    RH_ScopedInstall(FinishAnimCarGetInCB, 0x6467F0);
    RH_ScopedVMTInstall(Clone, 0x649BD0);
    RH_ScopedVMTInstall(GetTaskType, 0x646700);
    RH_ScopedVMTInstall(MakeAbortable, 0x646780);
    RH_ScopedVMTInstall(ProcessPed, 0x64DB30);
    RH_ScopedVMTInstall(SetPedPosition, 0x6467A0);
}

// 0x646690
CTaskSimpleCarGetIn::CTaskSimpleCarGetIn(CVehicle* vehicle, uint32 door, CTaskUtilityLineUpPedWithCar* task) :
    CTaskSimple(),
    m_TargetVehicle{ vehicle },
    m_nTargetDoor{ door },
    m_Utility{ task }
{
    CEntity::SafeRegisterRef(m_TargetVehicle);
}

// 0x646710
CTaskSimpleCarGetIn::~CTaskSimpleCarGetIn() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
}

void CTaskSimpleCarGetIn::FinishAnimCarGetInCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleCarGetIn*>(data);
    self->m_bIsFinished = true;
    self->m_Anim = nullptr;
}

// 0x64B2D0
void CTaskSimpleCarGetIn::StartAnim(const CPed* ped) {
    const auto [groupId, animId] = [this] {
        const auto animId = [this]{
            switch (m_nTargetDoor) {
            case TARGET_DOOR_FRONT_RIGHT: return ANIM_ID_CAR_GETIN_RHS_0;
            case TARGET_DOOR_REAR_RIGHT:  return ANIM_ID_CAR_GETIN_RHS_1;
            case TARGET_DOOR_DRIVER:      return ANIM_ID_CAR_GETIN_LHS_0;
            case TARGET_DOOR_REAR_LEFT:   return ANIM_ID_CAR_GETIN_LHS_1;
            case TARGET_DOOR_UNK2:        return ANIM_ID_CAR_GETIN_BIKE_FRONT;
            default: NOTSA_UNREACHABLE(); return ANIM_ID_UNDEFINED;
            }
        }();

        // todo: shadow var
        const auto groupId = [this, animId]{
            const auto groupId = (AssocGroupId)m_TargetVehicle->GetAnimGroup().GetGroup(animId);
            if (groupId == AssocGroupId::ANIM_GROUP_CONVCARANIMS) {
                if (m_nTargetDoor == TARGET_DOOR_DRIVER) {
                    if (m_TargetVehicle->IsDoorMissing(TARGET_DOOR_DRIVER) || !m_TargetVehicle->IsDoorClosed(TARGET_DOOR_DRIVER)) {
                        return ANIM_GROUP_STDCARAMIMS;
                    }
                }
            }
            return groupId;
        }();

        return std::make_tuple(groupId, animId);
    }();

    m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, groupId, animId, 4.f);
    m_Anim->SetFinishCallback(FinishAnimCarGetInCB, this);

    /*
    m_Anim->SetFinishCallback([](CAnimBlendAssociation* anim, void* data) {
        const auto self = static_cast<CTaskSimpleCarGetIn*>(data);
        self->m_bIsFinished = true;
        self->m_Anim = nullptr;
    }, this);
    */
}

// 0x646780
bool CTaskSimpleCarGetIn::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: {
        if (m_Anim) {
            m_Anim->m_fBlendDelta = -1000.f;
        }
        return true;
    }
    }
    return false;
}

// 0x64DB30
bool CTaskSimpleCarGetIn::ProcessPed(CPed* ped) {
    if (!m_TargetVehicle) {
        return true;
    }

    if (m_bIsFinished) {
        ped->RemoveWeaponWhenEnteringVehicle(false);
        if (CCheat::IsActive(CHEAT_SMASH_N_BOOM) && ped->IsPlayer() && m_TargetVehicle) { // This stuff later is de-activated in `CTaskSimpleCarGetOut`
            m_TargetVehicle->physicalFlags.bBulletProof = m_TargetVehicle->physicalFlags.bExplosionProof = true;
            m_TargetVehicle->vehicleFlags.bCanBeDamaged = false;
        }
        return true;
    }

    if (!m_Anim) {
        StartAnim(ped);
    }

    // Apply move force for BMX like vehicles
    if (m_TargetVehicle && m_TargetVehicle->IsSubBMX() && m_Anim && (m_Anim->m_nFlags & ANIMATION_STARTED)) {
        switch (m_Anim->m_nAnimId) {
        case ANIM_ID_CAR_GETIN_LHS_0:
        case ANIM_ID_CAR_GETIN_RHS_0:
        case ANIM_ID_CAR_GETIN_LHS_1:
        case ANIM_ID_CAR_GETIN_RHS_1: {
            // 10.0f and 0.01f are static.
            if (10.0f / 30.f < m_Anim->m_fCurrentTime) {
                m_TargetVehicle->ApplyMoveForce(m_TargetVehicle->GetForward() * CTimer::GetTimeStep() * m_TargetVehicle->m_fMass * 0.01f);
            }
            break;
        }
        }
    }


    return false;
}

// 0x6467A0
bool CTaskSimpleCarGetIn::SetPedPosition(CPed* ped) {
    m_Utility->ProcessPed(ped, m_TargetVehicle, m_Anim);
    return true;
}
