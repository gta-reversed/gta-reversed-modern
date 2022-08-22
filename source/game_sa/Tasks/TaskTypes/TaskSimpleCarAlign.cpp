#include "StdInc.h"
#include "TaskSimpleCarAlign.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleCarAlign::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCarAlign);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x645B40);
    RH_ScopedInstall(Destructor, 0x645BE0);
    RH_ScopedGlobalInstall(FinishAnimCarAlignCB, 0x645E40);
    RH_ScopedInstall(FixHeading, 0x645CB0);
    RH_ScopedInstall(StartAnim, 0x64AC00);
    RH_ScopedVirtualInstall2(Clone, 0x649930);
    RH_ScopedVirtualInstall2(GetTaskType, 0x645BD0);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x645C50);
    RH_ScopedVirtualInstall2(ProcessPed, 0x64D6D0);
    RH_ScopedVirtualInstall2(SetPedPosition, 0x645C70);
}

// 0x645B40
CTaskSimpleCarAlign::CTaskSimpleCarAlign(CVehicle* targetVehicle, CVector const& targetDoorPos, uint32 targetDoor, CTaskUtilityLineUpPedWithCar* utility) :
    CTaskSimple(),
    m_TargetVehicle{ targetVehicle },
    m_TargetDoorPos{ targetDoorPos },
    m_nTargetDoor{ targetDoor },
    m_Utility{ utility }
{
    CEntity::SafeRegisterRef(m_TargetVehicle);
}

// 0x645BE0
CTaskSimpleCarAlign::~CTaskSimpleCarAlign() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
    if (m_Anim) {
        m_Anim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x645E40
void CTaskSimpleCarAlign::FinishAnimCarAlignCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleCarAlign*>(data);
    self->m_Anim = nullptr;
    self->m_bIsFinished = true;
}

// 0x645CB0
void CTaskSimpleCarAlign::FixHeading(CPed* ped) {
    if (m_TargetVehicle || !m_TargetVehicle->IsAutomobile()) {
        return;
    }

    const auto carLeftOrRight = [this] {
        switch (m_nTargetDoor) {
        case 10:
        case 11:
            return m_TargetVehicle->GetRight() * -1.f; // Left
        default:
            return m_TargetVehicle->GetRight();
        }
    }();

    const auto pedFwd = ped->GetForwardVector();
    const auto dot = DotProduct(carLeftOrRight, pedFwd);
    if (dot <= 0.f || dot >= 0.1f) {
        return;
    }

    ped->m_fAimingRotation = ped->m_fCurrentRotation = CGeneral::LimitRadianAngle(CGeneral::GetRadianAngleBetweenPoints(pedFwd - carLeftOrRight * dot, {}));
}

// 0x64AC00
void CTaskSimpleCarAlign::StartAnim(CPed* ped) {
    const auto animId = [this, ped] {
        CVector doorOpenPos{};
        CCarEnterExit::GetPositionToOpenCarDoor(&doorOpenPos, m_TargetVehicle, m_nTargetDoor);
        const auto z = doorOpenPos.z - ped->GetPosition().z;
        switch (m_nTargetDoor) {
        case 10:
        case 11:
            return (z <= 4.4f) ? ANIM_ID_CAR_ALIGN_LHS : ANIM_ID_CAR_ALIGNHI_LHS;
        default:
            return (z <= 4.4f) ? ANIM_ID_CAR_ALIGN_RHS : ANIM_ID_CAR_ALIGNHI_RHS;
        }
    }();
    m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, (AssocGroupId)m_TargetVehicle->GetAnimGroup().GetGroup(animId), animId, 4.f);
    m_Anim->SetFinishCallback(FinishAnimCarAlignCB, this);
}

// 0x645C50
bool CTaskSimpleCarAlign::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: {
        if (m_Anim) {
            m_Anim->m_fBlendDelta = -1000.f;
        }
        return true;
    }
    default:
        return false;
    }
}

// 0x64D6D0
bool CTaskSimpleCarAlign::ProcessPed(CPed* ped) {
    if (m_bIsFinished || !m_TargetVehicle) {
        return true;
    }
    if (!m_Anim) {
        FixHeading(ped);
        StartAnim(ped);
    }
    return false;
}

// 0x645C70
bool CTaskSimpleCarAlign::SetPedPosition(CPed* ped) {
    CVector doorOpenPos{};
    CCarEnterExit::GetPositionToOpenCarDoor(&doorOpenPos, m_TargetVehicle, m_nTargetDoor);
    m_Utility->ProcessPed(ped, m_TargetVehicle, m_Anim);
    return true;
}
