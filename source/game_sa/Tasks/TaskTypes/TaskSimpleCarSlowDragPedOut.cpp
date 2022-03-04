#include "StdInc.h"
#include "TaskSimpleCarSlowDragPedOut.h"

void CTaskSimpleCarSlowDragPedOut::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCarSlowDragPedOut);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x647FE0);
    RH_ScopedInstall(Destructor, 0x648070);

    RH_ScopedGlobalInstall(FinishAnimCarSlowDragPedOutCB, 0x648180);
    RH_ScopedInstall(ComputeAnimID_Wrapper, 0x648100);
    //RH_ScopedInstall(StartAnim, 0x64C010);
    //RH_ScopedInstall(Clone_Reversed, 0x649FD0);
    //RH_ScopedInstall(GetTaskType_Reversed, 0x648060);
    //RH_ScopedInstall(MakeAbortable_Reversed, 0x64BFB0);
    //RH_ScopedInstall(ProcessPed_Reversed, 0x64E060);
    //RH_ScopedInstall(SetPedPosition_Reversed, 0x6480E0);
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
    plugin::CallMethod<0x64C010, CTaskSimpleCarSlowDragPedOut*, CPed*>(this, ped);
}

// 0x64BFB0
bool CTaskSimpleCarSlowDragPedOut::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x64BFB0, CTaskSimpleCarSlowDragPedOut*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x64E060
bool CTaskSimpleCarSlowDragPedOut::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x64E060, CTaskSimpleCarSlowDragPedOut*, CPed*>(this, ped);
}

// 0x6480E0
bool CTaskSimpleCarSlowDragPedOut::SetPedPosition(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x6480E0, CTaskSimpleCarSlowDragPedOut*, CPed*>(this, ped);
}

void CTaskSimpleCarSlowDragPedOut::ComputeAnimID_Wrapper(AssocGroupId& animGrp, AnimationId& animId) {
    std::tie(animGrp, animId) = ComputeAnimID();
}
