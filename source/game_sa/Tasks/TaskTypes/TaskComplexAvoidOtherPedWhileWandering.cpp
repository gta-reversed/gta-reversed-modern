#include "StdInc.h"

#include "TaskComplexAvoidOtherPedWhileWandering.h"

void CTaskComplexAvoidOtherPedWhileWandering::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexAvoidOtherPedWhileWandering, 0x86fec4, 11);
    RH_ScopedCategory("Tasks/TaskTypes"); // TODO: Change this to the appropriate category!

    RH_ScopedInstall(Constructor, 0x66A100);
    RH_ScopedInstall(Destructor, 0x66A1D0);

    RH_ScopedInstall(QuitIK, 0x66A230, { .reversed = false });
    RH_ScopedInstall(ComputeSphere, 0x66A320, { .reversed = false });
    RH_ScopedInstall(ComputeRouteRoundSphere, 0x66A7B0, { .reversed = false });
    RH_ScopedInstall(SetUpIK, 0x66A850, { .reversed = false });
    RH_ScopedInstall(NearbyPedsInSphere, 0x671FE0, { .reversed = false });
    RH_ScopedInstall(ComputeAvoidSphere, 0x672080, { .reversed = false });
    RH_ScopedInstall(ComputeDetourTarget, 0x672180, { .reversed = false });

    RH_ScopedVMTInstall(Clone, 0x66D050);
    RH_ScopedVMTInstall(GetTaskType, 0x66A1C0);
    RH_ScopedVMTInstall(MakeAbortable, 0x66A260, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask, 0x66A2C0, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x674610, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x6721B0, { .reversed = false });
}

// 0x66A100
CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(
    CPed* pedToAvoid,
    const CVector& targetPoint,
    eMoveState moveState
) :
    m_PedToAvoid{pedToAvoid},
    m_TargetPt{targetPoint},
    m_DetourTargetPt{targetPoint}
{
    CEntity::SafeRegisterRef(m_PedToAvoid);
}

CTaskComplexAvoidOtherPedWhileWandering::CTaskComplexAvoidOtherPedWhileWandering(const CTaskComplexAvoidOtherPedWhileWandering& o) :
    CTaskComplexAvoidOtherPedWhileWandering{m_PedToAvoid, m_TargetPt, m_moveState}
{
    m_bMovingTarget = o.m_bMovingTarget;
}

// 0x66A1D0
CTaskComplexAvoidOtherPedWhileWandering::~CTaskComplexAvoidOtherPedWhileWandering() {
    CEntity::SafeCleanUpRef(m_PedToAvoid);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x6721B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x66A260, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x66A2C0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

CTask* CTaskComplexAvoidOtherPedWhileWandering::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x674610, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::QuitIK(CPed* ped) {
    return plugin::CallMethod<0x66A230, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::NearbyPedsInSphere(CColSphere* colSphere, CPed* ped) {
    return plugin::CallMethodAndReturn<uint8, 0x66A320, CTaskComplexAvoidOtherPedWhileWandering*, CColSphere*, CPed*>(this, colSphere, ped);
}

void CTaskComplexAvoidOtherPedWhileWandering::SetUpIK(CPed* ped) {
    return plugin::CallMethod<0x66A850, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeSphere(CPed* ped, CColSphere* colSphere, CPed** pedsToCheck, CPed** pedsInSphere) {
    return plugin::CallMethodAndReturn<bool, 0x671FE0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*, CPed**, CPed**>(this, ped, colSphere, pedsToCheck, pedsInSphere);
}

void CTaskComplexAvoidOtherPedWhileWandering::ComputeAvoidSphere(CPed* ped, CColSphere* colSphere) {
    return plugin::CallMethod<0x672080, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colSphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeRouteRoundSphere(CPed* ped, CColSphere* colSphere) {
    return plugin::CallMethodAndReturn<bool, 0x66A7B0, CTaskComplexAvoidOtherPedWhileWandering*, CPed*, CColSphere*>(this, ped, colSphere);
}

bool CTaskComplexAvoidOtherPedWhileWandering::ComputeDetourTarget(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x672180, CTaskComplexAvoidOtherPedWhileWandering*, CPed*>(this, ped);
}
