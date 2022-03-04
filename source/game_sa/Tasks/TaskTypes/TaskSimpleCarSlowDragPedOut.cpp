#include "StdInc.h"
#include "TaskSimpleCarSlowDragPedOut.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleCarSlowDragPedOut::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCarSlowDragPedOut);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x647FE0);
    RH_ScopedInstall(Destructor, 0x648070);

    RH_ScopedGlobalInstall(FinishAnimCarSlowDragPedOutCB, 0x648180);
    RH_ScopedInstall(ComputeAnimID_Wrapper, 0x648100);
    RH_ScopedInstall(StartAnim, 0x64C010);
    RH_ScopedInstall(Clone_Reversed, 0x649FD0);
    RH_ScopedInstall(GetTaskType_Reversed, 0x648060);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x64BFB0);
    RH_ScopedInstall(ProcessPed_Reversed, 0x64E060);
    RH_ScopedInstall(SetPedPosition_Reversed, 0x6480E0);
}

// 0x647FE0
CTaskSimpleCarSlowDragPedOut::CTaskSimpleCarSlowDragPedOut(CVehicle* veh, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar* lineUpPedWithCarTask, bool isPedStatic) :
    m_vehicle{veh},
    m_targetDoor{targetDoor},
    m_lineUpPedWithCarTask{lineUpPedWithCarTask},
    m_wasPedStatic{isPedStatic}
{
    if (veh) {
        veh->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
    }
}

CTaskSimpleCarSlowDragPedOut::CTaskSimpleCarSlowDragPedOut(const CTaskSimpleCarSlowDragPedOut& o) :
    CTaskSimpleCarSlowDragPedOut{ o.m_vehicle, o.m_targetDoor, o.m_lineUpPedWithCarTask, o.m_wasPedStatic }
{
}

// 0x648070
CTaskSimpleCarSlowDragPedOut::~CTaskSimpleCarSlowDragPedOut() {
    if (m_vehicle) {
        CEntity::ClearReference(m_vehicle);
    }
    if (m_animAssoc) {
        m_animAssoc->SetFinishCallback(CDefaultAnimCallback::DefaultAnimCB, nullptr);
    }
}

// 0x648180
void CTaskSimpleCarSlowDragPedOut::FinishAnimCarSlowDragPedOutCB(CAnimBlendAssociation* anim, void* taskPtr) {
    auto self = (CTaskSimpleCarSlowDragPedOut*)taskPtr; // `this` ptr of the instance that this anim belongs to
    self->m_animFinished = true;
    self->m_animAssoc = nullptr;
    if (self->m_vehicle) {
        // Open door
        const auto [grp, id] = self->ComputeAnimID();
        self->m_vehicle->ProcessOpenDoor(nullptr, self->m_targetDoor, grp, id, 1.f);

        // Mark door as opened (Not sure why it's done here, not in `ProcessOpenDoor`...)
        if (self->m_vehicle->IsAutomobile()) {
            self->m_vehicle->AsAutomobile()->m_damageManager.SetDoorOpen((eDoors)self->m_targetDoor);
        }
    }
}

// 0x648100
std::pair<AssocGroupId, AnimationId> CTaskSimpleCarSlowDragPedOut::ComputeAnimID() {
    const auto id = [this] {
        switch (m_targetDoor)
        {
        case TARGET_DOOR_FRONT_RIGHT:
        case TARGET_DOOR_REAR_RIGHT:
            return ANIM_ID_CAR_PULLOUT_RHS;

        case TARGET_DOOR_DRIVER:
        case TARGET_DOOR_REAR_LEFT:
            return ANIM_ID_CAR_PULLOUT_LHS;

        case TARGET_DOOR_UNK: // TODO: Figure this out
            return ANIM_ID_UNKNOWN_15;

        default:
            assert(0); // Not reachable
            return ANIM_ID_UNDEFINED;
        }
    }();
    return { (AssocGroupId)m_vehicle->GetAnimGroup().GetGroup(id), id };
}

// 0x64C010
void CTaskSimpleCarSlowDragPedOut::StartAnim(CPed* ped) {
    const auto [grp, id] = ComputeAnimID();
    m_animAssoc = CAnimManager::BlendAnimation(ped->m_pRwClump, grp, id, 1000.f);
    m_animAssoc->SetFinishCallback(FinishAnimCarSlowDragPedOutCB, this);
}

/*!
* @notsa
* @brief Return ped in the given seat (basically the ped we'll drag out)
*/
CPed* CTaskSimpleCarSlowDragPedOut::GetJackedPed() {
    return m_targetDoor == TARGET_DOOR_DRIVER ? m_vehicle->m_pDriver : m_vehicle->m_apPassengers[CCarEnterExit::ComputePassengerIndexFromCarDoor(m_vehicle, (int32)m_targetDoor)];
}

// 0x64BFB0
bool CTaskSimpleCarSlowDragPedOut::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const*) {
    if (priority == eAbortPriority::ABORT_PRIORITY_IMMEDIATE) {
        if (m_animAssoc) {
            m_animAssoc->m_fBlendDelta = -1000.f;
        }
        if (m_vehicle) {
            const auto [grp, id] = ComputeAnimID();
            m_vehicle->ProcessOpenDoor(ped, m_targetDoor, grp, id, 1.f);
        }
        return true;
    }
    return false;
}

// 0x64E060
bool CTaskSimpleCarSlowDragPedOut::ProcessPed(CPed* ped) {
    if (m_animFinished || !m_vehicle) {
        return true;
    }

    // Make sure we actually need to drag the ped out
    switch (m_vehicle->GetAnimGroupId()) {
    case ANIM_GROUP_COACHCARANIMS:
    case ANIM_GROUP_TANKCARANIMS:
        return true;
    case ANIM_GROUP_BUSCARANIMS: {
        if (m_targetDoor == TARGET_DOOR_FRONT_RIGHT) {
            return true;
        }
        break;
    }
    }

    // Play anim and make peds talk (if not already playing)
    if (!m_animAssoc) {
        StartAnim(ped);

        // Make peds say something
        if (m_vehicle) { // Redundant check, maybe inlined?
            if (const auto jackedPed = GetJackedPed()) {
                const auto DoTalk = [this](auto ped1, auto ped2) {
                    if (!SayJacked(ped1, m_vehicle)) {
                        SayJacking(ped2, ped1, m_vehicle);
                    }
                };
                if (rand() % 1024 <= 512) {
                    DoTalk(jackedPed, ped);
                } else {
                    DoTalk(ped, jackedPed);
                }
            }
        }
    }

    // Process door open ratio according to animation's current time
    const auto [grp, id] = ComputeAnimID();
    m_vehicle->ProcessOpenDoor(ped, m_targetDoor, grp, id, m_animAssoc->m_fCurrentTime);

    return false;
}

// 0x6480E0
bool CTaskSimpleCarSlowDragPedOut::SetPedPosition(CPed* ped) {
    m_lineUpPedWithCarTask->ProcessPed(ped, m_vehicle, m_animAssoc);
    return true;
}

void CTaskSimpleCarSlowDragPedOut::ComputeAnimID_Wrapper(AssocGroupId& animGrp, AnimationId& animId) {
    std::tie(animGrp, animId) = ComputeAnimID();
}
