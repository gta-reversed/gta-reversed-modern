#include "StdInc.h"

#include "TaskSimpleCarJumpOut.h"
#include "TaskSimpleCarSetPedOut.h"
#include "PedPlacement.h"

void CTaskSimpleCarJumpOut::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarJumpOut, 0x86ee70, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x64BE40);
    RH_ScopedInstall(Destructor, 0x647490);
    RH_ScopedGlobalInstall(FinishAnimCarJumpOutCB, 0x647700);
    RH_ScopedInstall(ComputeAnimID_ToHook, 0x647690);
    RH_ScopedInstall(StartAnim, 0x64BF00);
    RH_ScopedVMTInstall(Clone, 0x64D220);
    RH_ScopedVMTInstall(GetTaskType, 0x647500);
    RH_ScopedVMTInstall(MakeAbortable, 0x647510);
    RH_ScopedVMTInstall(ProcessPed, 0x64DD60);
    RH_ScopedVMTInstall(SetPedPosition, 0x647590);
}

// 0x64BE40
CTaskSimpleCarJumpOut::CTaskSimpleCarJumpOut(CVehicle* targetVehicle, uint32 targetDoor, CTaskUtilityLineUpPedWithCar* utility) :
    CTaskSimple(),
    m_TargetVehicle{ targetVehicle },
    m_nTargetDoor{ targetDoor },
    m_Utility{ utility },
    m_fStartCarSpeed{ targetVehicle ? targetVehicle->GetMoveSpeed().Magnitude() : 0.f }
{
    CEntity::SafeCleanUpRef(m_TargetVehicle);
}

// 0x647490
CTaskSimpleCarJumpOut::~CTaskSimpleCarJumpOut() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
    if (m_Anim) {
        m_Anim->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x647700
void CTaskSimpleCarJumpOut::FinishAnimCarJumpOutCB(CAnimBlendAssociation* anim, void* data) {
    const auto self = static_cast<CTaskSimpleCarJumpOut*>(data);
    self->m_bIsFinished = true;
    self->m_Anim = nullptr;
}

// 0x64BF00
void CTaskSimpleCarJumpOut::StartAnim(const CPed* ped) {
    const auto [groupId, animId] = ComputeAnimID();
    m_Anim = CAnimManager::BlendAnimation(ped->m_pRwClump, groupId, animId, 8.f);
    m_Anim->SetFinishCallback(FinishAnimCarJumpOutCB, this);
}

// Signature changed, `ComputeAnimID_Wrapper` is hooked instead.
// 0X647690
auto CTaskSimpleCarJumpOut::ComputeAnimID() -> std::pair<AssocGroupId, AnimationId> {
    const auto animId = [this] {
        switch (m_nTargetDoor) {
        case TARGET_DOOR_FRONT_RIGHT:
        case TARGET_DOOR_REAR_RIGHT:
            return ANIM_ID_CAR_ROLLOUT_RHS;;
        case TARGET_DOOR_DRIVER:
        case TARGET_DOOR_REAR_LEFT:
            return ANIM_ID_CAR_ROLLOUT_LHS;
        default:
            NOTSA_UNREACHABLE();
            return ANIM_ID_UNDEFINED;
        }
    }();
    return { (AssocGroupId)m_TargetVehicle->GetAnimGroup().GetGroup(animId), animId };
}

// 0x647510
bool CTaskSimpleCarJumpOut::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    switch (priority) {
    case ABORT_PRIORITY_IMMEDIATE: {
        if (m_Anim) {
            m_Anim->m_fBlendDelta = -1000.f;
        }
        return true;
    }
    case ABORT_PRIORITY_URGENT: {
        if (event && m_Anim && !ped->bInVehicle) {
            switch (event->GetEventType()) {
            case EVENT_IN_AIR:
            case EVENT_IN_WATER: {
                m_Anim->m_fBlendDelta = -2.f;
                m_bIsFinished = true;
                return true;
            }
            }
        }
        break;
    }
    }
    return false;
}

// 0x64DD60
bool CTaskSimpleCarJumpOut::ProcessPed(CPed* ped) {
    if (m_bIsFinished) {
        return true;
    }

    if (!m_TargetVehicle) {
        return true;
    }

    // Start calculating animation shift for ped in certain vehicles
    if ([this]{
        if (!m_Anim) {
            return true;
        }

        if (m_TargetVehicle->IsBike() || m_TargetVehicle->IsSubQuad()) {
            return m_Anim->m_fCurrentTime < 0.7333333f; // TODO: Magic?
        } else if (m_TargetVehicle->IsAutomobile()) {
            return m_Anim->m_fCurrentTime < 0.45f;
        }

        return false;
    }()) {
        m_fStartCarSpeed *= std::pow(0.96f, CTimer::GetTimeStep());
        ped->m_vecAnimMovingShiftLocal.y += m_fStartCarSpeed * CTimer::GetTimeStep();
    }

    // Not in vehicle anymore?
    if (!ped->bInVehicle) { // Inverted
        if (m_TargetVehicle && m_TargetVehicle->IsAutomobile()) { // 0x64DE0E
            ped->m_pedIK.bUseArm = true;
            ped->bFallenDown = true;
        }
        return !m_Anim;
    }

    // Anim not playing yet?
    if (!m_Anim) { // Inverted - 0x64DE56
        StartAnim(ped);
        return false;
    }

    // Start opening the door - 0x64DE74
    const auto GetDoorOpenTimeThreshold = [this] {
        if (m_TargetVehicle->IsBike() || m_TargetVehicle->IsSubQuad()) {
            return 0.35f;
        } else if (m_TargetVehicle->IsPlane()) {
            return 0.15f;
        }
        return 0.07f;
    };
    if (GetDoorOpenTimeThreshold() >= m_Anim->m_fCurrentTime) {
        if (m_TargetVehicle->IsAutomobile()) {
            const auto [grpId, animId] = ComputeAnimID(); // 0x64E00D
            m_TargetVehicle->ProcessOpenDoor(ped, m_nTargetDoor, grpId, animId, m_Anim->m_fCurrentTime);
        }
        return false;
    }

    // 0x64DEC0
    {
        CTaskSimpleCarSetPedOut getOutTask{m_TargetVehicle, m_nTargetDoor, true };
        getOutTask.m_nDoorFlagsToClear = m_nDoorFlagsToClear;
        getOutTask.m_nNumGettingInToClear = m_nNumGettingInToClear;
        getOutTask.ProcessPed(ped);
    }

    CCarEnterExit::RemoveCarSitAnim(ped);

    // Change rotation of ped
    {
        const auto rot = m_TargetVehicle->GetHeading();
        ped->m_fAimingRotation = ped->m_fCurrentRotation = m_TargetVehicle->IsTotallyUpsideDown() ? CGeneral::LimitRadianAngle(rot + PI) : rot;
        ped->SetHeading(ped->m_fCurrentRotation);
    }
    ped->GetMoveSpeed() = m_TargetVehicle->GetMoveSpeed();
    ped->m_pEntityIgnoredCollision = m_TargetVehicle;
    ped->bKnockedOffBike = true;
    if (m_TargetVehicle->IsAutomobile()) {
        m_TargetVehicle->AsAutomobile()->m_damageManager.SetDoorOpen((eDoors)m_nTargetDoor);
    }

    return false;
}

// 0x647590
bool CTaskSimpleCarJumpOut::SetPedPosition(CPed* ped) {
    if (!ped->bInVehicle) {
        return false;
    }

    ped->SetPedPositionInCar();

    // Do some Z position interpolation for ped for specific anim types
    if (m_Anim) {
        switch (m_Anim->m_nAnimId) {
        case ANIM_ID_CAR_ROLLOUT_RHS:
        case ANIM_ID_CAR_ROLLOUT_LHS: {
            const auto pedPos = ped->GetPosition();
            auto pedPosAdj{ pedPos };

            CWorld::pIgnoreEntity = ped;
            CPedPlacement::FindZCoorForPed(pedPosAdj);
            CWorld::pIgnoreEntity = nullptr;

            if (pedPosAdj.z > pedPos.z) {
                const auto timeDivider = [this] {
                    if (m_TargetVehicle->IsBike() || m_TargetVehicle->IsSubQuad()) {
                        return 0.27f;
                    }
                    return 0.07f;
                }();
                ped->GetMatrix().GetPosition().z += m_Anim->m_fCurrentTime / timeDivider * (pedPosAdj.z - pedPos.z);
            }
            break;
        }
        }
    }

    return true;
}
