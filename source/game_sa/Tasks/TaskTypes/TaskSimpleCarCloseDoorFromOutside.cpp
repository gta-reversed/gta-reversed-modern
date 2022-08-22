#include "StdInc.h"

#include "TaskSimpleCarCloseDoorFromOutside.h"
#include "TaskUtilityLineUpPedWithCar.h"
#include "PedPlacement.h"

void CTaskSimpleCarCloseDoorFromOutside::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarCloseDoorFromOutside, 0x86ed2c, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6464F0);
    RH_ScopedInstall(Destructor, 0x646570);
    RH_ScopedInstall(FinishAnimCarCloseDoorFromOutsideCB, 0x646680);
    RH_ScopedInstall(ComputeAnimID, 0x646600);
    RH_ScopedInstall(StartAnim, 0x64B080);
    RH_ScopedVMTInstall(Clone, 0x649B60);
    RH_ScopedVMTInstall(GetTaskType, 0x646560);
    RH_ScopedVMTInstall(MakeAbortable, 0x64B020);
    RH_ScopedVMTInstall(ProcessPed, 0x64DA90);
    RH_ScopedVMTInstall(SetPedPosition, 0x6465E0);
}

// 0x6464F0
CTaskSimpleCarCloseDoorFromOutside::CTaskSimpleCarCloseDoorFromOutside(CVehicle* targetVehicle, uint32 targetDoor, CTaskUtilityLineUpPedWithCar* utility) :
    CTaskSimple(),
    m_TargetVehicle{ targetVehicle },
    m_TargetDoor{ targetDoor },
    m_Utility{ utility }
{
    CEntity::SafeRegisterRef(m_TargetVehicle);
}

// 0x646570
CTaskSimpleCarCloseDoorFromOutside::~CTaskSimpleCarCloseDoorFromOutside() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
    if (m_Anim) {
        m_Anim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x646680
void CTaskSimpleCarCloseDoorFromOutside::FinishAnimCarCloseDoorFromOutsideCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleCarCloseDoorFromOutside*>(data);
    self->m_bIsFinished = true;
    self->m_Anim = nullptr;
}

// 0x646600
void CTaskSimpleCarCloseDoorFromOutside::ComputeAnimID(AssocGroupId& outGroup, AnimationId& outAnimId) {
    outAnimId = [this] {
        switch (m_TargetDoor) {
        case 8u:  return ANIM_ID_CAR_CLOSE_RHS_0;
        case 9u:  return ANIM_ID_CAR_CLOSE_RHS_1;
        case 10u: return ANIM_ID_CAR_CLOSE_LHS_0;
        case 11u: return ANIM_ID_CAR_CLOSE_LHS_1;
        default:  NOTSA_UNREACHABLE(); return ANIM_ID_UNDEFINED;
        }
    }();
    outGroup = (AssocGroupId)m_TargetVehicle->GetAnimGroup().GetGroup(outAnimId);
}

// NOTSA
auto CTaskSimpleCarCloseDoorFromOutside::ComputeAnimID_Helper() -> std::tuple<AssocGroupId, AnimationId> {
    AssocGroupId groupId;
    AnimationId  animId;
    ComputeAnimID(groupId, animId);
    return { groupId, animId };
}

// 0x64B080
void CTaskSimpleCarCloseDoorFromOutside::StartAnim(const CPed* ped) {
    const auto pedPos = ped->GetPosition();
    auto realPedPos{pedPos};
    CPedPlacement::FindZCoorForPed(realPedPos);

    if (pedPos.z - 1.f >= realPedPos.z) {
        m_bIsFinished = true;
        return;
    }

    m_TargetVehicle->m_nFakePhysics = false;
    m_TargetVehicle->m_vecMoveSpeed += CVector{ 0.001f, 0.001f, 0.001f };
    m_TargetVehicle->m_vecTurnSpeed += CVector{ 0.001f, 0.001f, 0.001f };


    if ([this, ped] {
        if (ped->IsPlayer()) {
            const auto player = static_cast<const CPlayerPed*>(ped);
            const auto pad    = player->GetPadFromPlayer();

            if (!pad->DisablePlayerControls && m_TargetVehicle->m_nDoorLock != CARLOCK_FORCE_SHUT_DOORS) {
                if (   pad->GetTarget()
                    || pad->GetLeftStickX() || pad->GetLeftStickY()
                    || pad->NewState.DPadUp || pad->NewState.DPadDown
                    || pad->NewState.DPadLeft || pad->NewState.DPadRight
                ) {
                    return true;
                }
            }

            if (m_TargetVehicle->m_pFire || m_TargetVehicle->IsAutomobile() && m_TargetVehicle->AsAutomobile()->m_damageManager.GetEngineStatus() >= 225) {
                return true;
            }
        }
        return false;
    }()) {
        if (m_TargetVehicle->IsAutomobile()) {
            m_TargetVehicle->AsAutomobile()->m_damageManager.SetDoorOpen((eDoors)m_TargetDoor);
        }
        m_bIsFinished = true;
    } else {
        const auto [groupId, animId] = ComputeAnimID_Helper();
        m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, groupId, animId, 1000.f);
        m_Anim->SetFinishCallback(FinishAnimCarCloseDoorFromOutsideCB, this);
    }
}

// NOTSA
void CTaskSimpleCarCloseDoorFromOutside::ProcessDoorOpen(const CPed* ped) {
    const auto [groupId, animId] = ComputeAnimID_Helper();
    m_TargetVehicle->ProcessOpenDoor(
        nullptr, m_TargetDoor,
        groupId,
        animId,
        1.f
    );
}

// 0x64B020
bool CTaskSimpleCarCloseDoorFromOutside::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: {
        if (m_Anim) {
            m_Anim->m_fBlendDelta = -1000.f;
        }
        if (m_TargetVehicle) {
            ProcessDoorOpen(ped);
        }
        return true;
    }
    default:
        return false;
    }
}

// 0x64DA90
bool CTaskSimpleCarCloseDoorFromOutside::ProcessPed(CPed* ped) {
    if (m_bIsFinished) {
        return true;
    }

    if (!m_TargetVehicle || m_TargetVehicle->GetAnimGroup().m_specialFlags.bDontCloseDoorAfterGettingOut) {
        return true;
    }

    if (!m_Anim) {
        StartAnim(ped);
        if (!m_Anim) {
            return true;
        }
    }

    const auto [groupId, animId] = ComputeAnimID_Helper();
    m_TargetVehicle->ProcessOpenDoor(ped, m_TargetDoor, groupId, animId, m_Anim->m_fCurrentTime);

    return false;
}

// 0x6465E0
bool CTaskSimpleCarCloseDoorFromOutside::SetPedPosition(CPed* ped) {
    m_Utility->ProcessPed(ped, m_TargetVehicle, m_Anim);
    return true;
}
