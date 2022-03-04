#include "StdInc.h"
#include "TaskSimpleCarSlowDragPedOut.h"

void CTaskSimpleCarSlowDragPedOut::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCarSlowDragPedOut);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x647FE0);
    RH_ScopedInstall(Destructor, 0x648070);

    //RH_ScopedGlobalInstall(FinishAnimCarSlowDragPedOutCB, 0x648180);
    //RH_ScopedInstall(ComputeAnimID, 0x648100);
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
    plugin::Call<0x648180, CAnimBlendAssociation*, CTaskSimpleCarSlowDragPedOut*>(anim, self);
}

// 0x648100
void CTaskSimpleCarSlowDragPedOut::ComputeAnimID(AssocGroupId& animGrp, AnimationId& animId) {
    return plugin::CallMethod<0x648100, CTaskSimpleCarSlowDragPedOut*, AssocGroupId&, AnimationId&>(this, animGrp, animId);
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
