#include "StdInc.h"

#include "TaskSimpleCarCloseDoorFromInside.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleCarCloseDoorFromInside::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarCloseDoorFromInside, 0x86ed08, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x646300);
    RH_ScopedInstall(Destructor, 0x646380);
    RH_ScopedGlobalInstall(FinishAnimCarCloseDoorFromInsideCB, 0x646490);
    RH_ScopedInstall(ComputeAnimID, 0x646410);
    RH_ScopedInstall(StartAnim, 0x64AFB0);
    RH_ScopedVMTInstall(Clone, 0x649AF0);
    RH_ScopedVMTInstall(GetTaskType, 0x646370);
    RH_ScopedVMTInstall(MakeAbortable, 0x64AF50);
    RH_ScopedVMTInstall(ProcessPed, 0x64D9A0);
    RH_ScopedVMTInstall(SetPedPosition, 0x6463F0);
}

// 0x646300
CTaskSimpleCarCloseDoorFromInside::CTaskSimpleCarCloseDoorFromInside(CVehicle* targetVehicle, uint32 door, CTaskUtilityLineUpPedWithCar* utility) :
    CTaskSimple(),
    m_TargetVehicle{ targetVehicle },
    m_nTargetDoor{ door },
    m_Utility{ utility }
{
    CEntity::SafeRegisterRef(m_TargetVehicle);
}

// 0x646380
CTaskSimpleCarCloseDoorFromInside::~CTaskSimpleCarCloseDoorFromInside() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
    if (m_Anim) {
        m_Anim->SetDeleteCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x646490
void CTaskSimpleCarCloseDoorFromInside::FinishAnimCarCloseDoorFromInsideCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleCarCloseDoorFromInside*>(data);

    self->m_bIsFinished = true;

    if (self->m_TargetVehicle) {
        self->ProcessDoorOpen(nullptr);
    }

    // The anim has just finished and they do this? Maybe inlined?
    if (self->m_Anim) {
        self->m_Anim->m_fBlendDelta = -1000.f;
    }
    self->m_Anim = nullptr;
}

// 0x646410
void CTaskSimpleCarCloseDoorFromInside::ComputeAnimID(AssocGroupId& outGroup, AnimationId& outAnimId) {
    outAnimId = [this] {
        switch (m_nTargetDoor) {
        case 8u:  return ANIM_ID_CAR_CLOSEDOOR_RHS_0;
        case 9u:  return ANIM_ID_CAR_CLOSEDOOR_RHS_1;
        case 10u: return ANIM_ID_CAR_CLOSEDOOR_LHS_0;
        case 11u: return ANIM_ID_CAR_CLOSEDOOR_LHS_1;
        default:  NOTSA_UNREACHABLE(); return ANIM_ID_UNDEFINED;
        }
    }();
    outGroup = (AssocGroupId)m_TargetVehicle->GetAnimGroup().GetGroup(outAnimId);
}

// NOTSA
auto CTaskSimpleCarCloseDoorFromInside::ComputeAnimID_Helper() -> std::tuple<AssocGroupId, AnimationId> {
    AssocGroupId groupId;
    AnimationId  animId;
    ComputeAnimID(groupId, animId);
    return { groupId, animId };
}

// 0x64AFB0
void CTaskSimpleCarCloseDoorFromInside::StartAnim(const CPed* ped) {
    const auto [groupId, animId] = ComputeAnimID_Helper();
    m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, groupId, animId, 1000.f);
    m_Anim->SetFinishCallback(FinishAnimCarCloseDoorFromInsideCB, this);
}

// NOTSA
void CTaskSimpleCarCloseDoorFromInside::ProcessDoorOpen(const CPed* ped) {
    const auto [groupId, animId] = ComputeAnimID_Helper();
    m_TargetVehicle->ProcessOpenDoor(nullptr, m_nTargetDoor, groupId, animId, 1.f);
}

// 0x64AF50
bool CTaskSimpleCarCloseDoorFromInside::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
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

// 0x64D9A0
bool CTaskSimpleCarCloseDoorFromInside::ProcessPed(CPed* ped) {
    if (m_bIsFinished) {
        return true;
    }

    if (!m_TargetVehicle) {
        return true;
    }

    if (m_TargetVehicle->GetAnimGroup().m_specialFlags.bDontCloseDoorAfterGettingIn) {
        ProcessDoorOpen(ped);
        return true;
    }

    if (!m_Anim) {
        if (ped->m_nPedState == PEDSTATE_ARRESTED) {
            return true;
        }
        StartAnim(ped);
    }

    const auto animId = (AnimationId)m_Anim->m_nAnimId;
    m_TargetVehicle->ProcessOpenDoor(ped, m_nTargetDoor, (AssocGroupId)m_TargetVehicle->GetAnimGroup().GetGroup(animId), animId, m_Anim->m_fCurrentTime);

    return false;
}

// 0x6463F0
bool CTaskSimpleCarCloseDoorFromInside::SetPedPosition(CPed* ped) {
    m_Utility->ProcessPed(ped, m_TargetVehicle, m_Anim);
    return true;
}
