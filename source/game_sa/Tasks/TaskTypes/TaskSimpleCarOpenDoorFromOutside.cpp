#include "StdInc.h"

#include "TaskSimpleCarOpenDoorFromOutside.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleCarOpenDoorFromOutside::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarOpenDoorFromOutside, 0x86ec9c, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x645E50);
    RH_ScopedInstall(Destructor, 0x645EE0);
    RH_ScopedInstall(FinishAnimCarOpenDoorFromOutsideCB, 0x646020);
    RH_ScopedInstall(ComputeAnimID, 0x645FA0);
    RH_ScopedInstall(StartAnim, 0x64AD90);
    RH_ScopedVMTInstall(Clone, 0x6499A0);
    RH_ScopedVMTInstall(GetTaskType, 0x645ED0);
    RH_ScopedVMTInstall(MakeAbortable, 0x64AD00);
    RH_ScopedVMTInstall(ProcessPed, 0x64D710);
    RH_ScopedVMTInstall(SetPedPosition, 0x645F80);
}

// 0x645E50
CTaskSimpleCarOpenDoorFromOutside::CTaskSimpleCarOpenDoorFromOutside(CVehicle* targetVehicle, int32 targetDoor, CTaskUtilityLineUpPedWithCar* utility, bool bQuitAfterOpeningDoor) :
    CTaskSimple(),
    m_TargetVehicle{ targetVehicle },
    m_nTargetDoor{ targetDoor },
    m_bQuitAfterOpeningDoor{ bQuitAfterOpeningDoor },
    m_Utility{ utility }
{
    CEntity::SafeRegisterRef(targetVehicle);
}

// 0x645EE0
CTaskSimpleCarOpenDoorFromOutside::~CTaskSimpleCarOpenDoorFromOutside() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
    if (m_Anim) {
        m_Anim->SetDefaultFinishCallback();
    }
    IfNotAlreadySetPlayerCanExitCarFlag();
}

// NOTSA?
void CTaskSimpleCarOpenDoorFromOutside::IfNotAlreadySetPlayerCanExitCarFlag() {
    if (m_bHasSetCanPlayerExitCarFlag) {
        m_bHasSetCanPlayerExitCarFlag = false;
        FindPlayerPed()->bCanExitCar = true;
    }
}

// 0x646020
void CTaskSimpleCarOpenDoorFromOutside::FinishAnimCarOpenDoorFromOutsideCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleCarOpenDoorFromOutside*>(data);
    self->m_Anim = nullptr;
    self->m_bIsFinished = true;
}

// Originally @ 0x645FA0, but we've modified it a little
auto CTaskSimpleCarOpenDoorFromOutside::ComputeAnimID() -> std::pair<AssocGroupId, AnimationId> {
    const auto animId = [this] {
        switch (m_nTargetDoor) {
        case TARGET_DOOR_FRONT_RIGHT: return ANIM_ID_CAR_OPEN_RHS;
        case TARGET_DOOR_REAR_RIGHT:  return ANIM_ID_CAR_OPEN_RHS_1;
        case TARGET_DOOR_DRIVER:      return ANIM_ID_CAR_OPEN_LHS;
        case TARGET_DOOR_REAR_LEFT:   return ANIM_ID_CAR_OPEN_LHS_1;
        default:
            NOTSA_UNREACHABLE();
            return ANIM_ID_UNDEFINED;
        }
    }();
    return { (AssocGroupId)m_TargetVehicle->GetAnimGroup().GetGroup(animId), animId };
}

// 0x645FA0
void CTaskSimpleCarOpenDoorFromOutside::ComputeAnimID_ToHook(AssocGroupId& group, AnimationId& animation) {
    std::tie(group, animation) = ComputeAnimID();
}

// 0x64AD90
void CTaskSimpleCarOpenDoorFromOutside::StartAnim(CPed* ped) {
    const auto [groupId, animId] = ComputeAnimID();
    m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, groupId, animId, 1000.f);
    m_Anim->SetFinishCallback(FinishAnimCarOpenDoorFromOutsideCB, this);
}

// 0x64AD00
bool CTaskSimpleCarOpenDoorFromOutside::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: {
        if (m_Anim) {
            m_Anim->m_fBlendDelta = -1000.f;
        }
        if (m_TargetVehicle) {
            const auto [groupId, animId] = ComputeAnimID();
            m_TargetVehicle->ProcessOpenDoor(ped, m_nTargetDoor, groupId, animId, 1.f);
        }
        IfNotAlreadySetPlayerCanExitCarFlag();
        return true;
    }
    default:
        return false;
    }
}

// 0x64D710
bool CTaskSimpleCarOpenDoorFromOutside::ProcessPed(CPed* ped) {
    if (m_bIsFinished) {
        return true;
    }

    if (!m_TargetVehicle) {
        return true;
    }

    if (m_TargetVehicle->GetAnimGroup().m_specialFlags.bDontOpenDoorWhenGettingIn) {
        const auto [groupId, animId] = ComputeAnimID();
        m_TargetVehicle->ProcessOpenDoor(ped, m_nTargetDoor, groupId, animId, 1.f);
        return true;
    }

    if (!m_Anim) {
        m_fDoorStartRatio = m_TargetVehicle->GetDooorAngleOpenRatio(m_nTargetDoor);
        StartAnim(ped);

        if (m_TargetVehicle && m_TargetVehicle->IsDriverAPlayer() && m_bQuitAfterOpeningDoor) { // NOTE/TODO: Inlined? Double check if `m_veh`
            if (ped && ped->IsCop()) {
#ifdef FIX_BUGS
                FindPlayerPed()->bCanExitCar = false; // See `IfNotAlreadySetPlayerCanExitCarFlag`
#else
                m_veh->m_pDriver->bCanExitCar = false;
#endif
                m_bHasSetCanPlayerExitCarFlag = true;
            }
        }
    }

    const auto doorOpenTiming = m_TargetVehicle->GetAnimGroup().GetInOutTiming(TIMING_START)[OPEN_OUT];
    if (m_TargetVehicle->IsAutomobile() || m_Anim->m_fCurrentTime >= doorOpenTiming) {
        const auto [groupId, animId] = ComputeAnimID();
        m_TargetVehicle->ProcessOpenDoor(ped, m_nTargetDoor, groupId, m_Anim->m_nAnimId, m_Anim->m_fCurrentTime);
        return false;
    }

    // Open the door visually
    const auto doorId = [this] {
        switch (m_nTargetDoor) {
        case TARGET_DOOR_FRONT_RIGHT: return DOOR_RIGHT_FRONT;
        case TARGET_DOOR_REAR_RIGHT:  return DOOR_RIGHT_REAR;
        case TARGET_DOOR_DRIVER:      return DOOR_LEFT_FRONT;
        case TARGET_DOOR_REAR_LEFT:   return DOOR_LEFT_REAR;
        default:
            NOTSA_UNREACHABLE();
            return (eDoors)0;
        }
    }();
    m_TargetVehicle->OpenDoor(ped, m_nTargetDoor, doorId, (1.f - m_Anim->m_fCurrentTime / doorOpenTiming) * m_fDoorStartRatio, false);

    return false;
}

// 0x645F80
bool CTaskSimpleCarOpenDoorFromOutside::SetPedPosition(CPed* ped) {
    m_Utility->ProcessPed(ped, m_TargetVehicle, m_Anim);
    return true;
}
