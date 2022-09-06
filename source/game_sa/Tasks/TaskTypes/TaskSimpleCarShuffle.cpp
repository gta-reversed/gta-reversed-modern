#include "StdInc.h"
#include "TaskSimpleCarShuffle.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleCarShuffle::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarShuffle, 0x86ed74, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x646810);
    RH_ScopedInstall(Destructor, 0x646890);

    RH_ScopedInstall(FinishAnimCarShuffleCB, 0x646970);
    RH_ScopedInstall(StartAnim, 0x64B3E0);

    RH_ScopedVMTInstall(Clone, 0x649C40);
    RH_ScopedVMTInstall(GetTaskType, 0x646880);
    RH_ScopedVMTInstall(MakeAbortable, 0x646900);
    RH_ScopedVMTInstall(ProcessPed, 0x64DC40);
    RH_ScopedVMTInstall(SetPedPosition, 0x646920);
}

// 0x646810
CTaskSimpleCarShuffle::CTaskSimpleCarShuffle(CVehicle* veh, eTargetDoor targetDoor, CTaskUtilityLineUpPedWithCar* lineUpUtility) :
    m_veh{veh},
    m_targetDoor{targetDoor},
    m_lineUpUtility{ lineUpUtility }
{
    CEntity::SafeRegisterRef(m_veh);
}

CTaskSimpleCarShuffle::CTaskSimpleCarShuffle(const CTaskSimpleCarShuffle& o) :
    CTaskSimpleCarShuffle{o.m_veh, o.m_targetDoor, o.m_lineUpUtility}
{
}

// 0x646890
CTaskSimpleCarShuffle::~CTaskSimpleCarShuffle() {
    CEntity::SafeCleanUpRef(m_veh);
    if (m_anim) {
        m_anim->SetDefaultFinishCallback();
    }
}

// 0x646970
void CTaskSimpleCarShuffle::FinishAnimCarShuffleCB(CAnimBlendAssociation* assoc, void* task) {
    const auto self = CTask::Cast<CTaskSimpleCarShuffle>(task);
    self->m_animHasFinished = true;
    self->m_anim = nullptr;
}

// 0x64B3E0
void CTaskSimpleCarShuffle::StartAnim(CPed const* ped) {
    m_anim = CAnimManager::BlendAnimation(ped->m_pRwClump, (AssocGroupId)m_veh->GetAnimGroup().GetGroup(ANIM_ID_CAR_SHUFFLE_RHS_1), ANIM_ID_CAR_SHUFFLE_RHS_1, 1000.f);
    m_anim->SetFinishCallback(FinishAnimCarShuffleCB, this);
}

// 0x646900
bool CTaskSimpleCarShuffle::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    if (priority == ABORT_PRIORITY_IMMEDIATE) {
        if (m_anim) {
            m_anim->m_fBlendDelta = -1000.f;
        }
        return true;
    }
    return false;
}

// 0x64DC40
bool CTaskSimpleCarShuffle::ProcessPed(CPed* ped) {
    if (!!m_veh || m_animHasFinished) {
        return true;
    }
    if (!m_anim) {
        StartAnim(ped);
    }
    return false;
}

// 0x646920
bool CTaskSimpleCarShuffle::SetPedPosition(CPed* ped) {
    if (!ped->bInVehicle || m_anim && m_anim->m_fBlendAmount > 0.9f) {
        m_lineUpUtility->ProcessPed(ped, m_veh, m_anim);
    } else {
        ped->SetPedPositionInCar();
    }
    return true;
}
