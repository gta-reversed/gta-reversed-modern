#include "StdInc.h"

#include "TaskComplexEnterCar.h"

void CTaskComplexEnterCar::InjectHooks() {
    RH_ScopedVirtualClass(CTaskComplexEnterCar, 0x86e6f0, 12);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63A220);
    RH_ScopedInstall(Destructor, 0x63DFA0);

    RH_ScopedInstall(GetTargetPos, 0x63A300, { .reversed = false });
    //RH_ScopedInstall(SetVehicleFlags, 0x63AB90, { .reversed = false });
    RH_ScopedInstall(CreateSubTask, 0x63E040, { .reversed = false });

    RH_ScopedVMTInstall(MakeAbortable, 0x63A730, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask, 0x63E990, { .reversed = false });
    RH_ScopedVMTInstall(CreateFirstSubTask, 0x643A60, { .reversed = false });
    RH_ScopedVMTInstall(ControlSubTask, 0x63A890, { .reversed = false });
    RH_ScopedVMTInstall(CreateNextSubTask_AfterSimpleCarAlign, 0x63F970, { .reversed = false });
}

// 0x63A220
CTaskComplexEnterCar::CTaskComplexEnterCar(CVehicle* targetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor, bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff) : CTaskComplex() {
    m_nFlags                      = 0;
    m_bAsDriver                   = bAsDriver;
    m_bQuitAfterOpeningDoor       = bQuitAfterOpeningDoor;
    m_bQuitAfterDraggingPedOut    = bQuitAfterDraggingPedOut;
    m_bCarryOnAfterFallingOff     = bCarryOnAfterFallingOff;
    m_pTargetVehicle              = targetVehicle;
    m_nTargetDoor                 = 0;
    m_nTargetDoorOppositeToFlag   = 0;
    m_nTargetSeat                 = 0;
    m_nDraggedPedDownTime         = 0;
    m_nMoveState                  = PEDMOVE_RUN;
    m_nNumGettingInSet            = 0;
    m_nCamMovementChoice          = 0;
    m_pTaskUtilityLineUpPedWithCar= nullptr;
    m_bIsAborting                 = false;
    m_pDraggedPed                 = nullptr;
    m_nDoorFlagsSet               = 0;
    m_fCruiseSpeed                = -1.0f;
    //m_nEnterCarStartTime          = 0; // NOTSA

    CEntity::SafeRegisterRef(m_pTargetVehicle);
}

// 0x63DFA0
CTaskComplexEnterCar::~CTaskComplexEnterCar() {
    CEntity::SafeCleanUpRef(m_pTargetVehicle);

    delete m_pTaskUtilityLineUpPedWithCar;
    if (!m_pTargetVehicle)
        return;

    m_pTargetVehicle->m_nNumGettingIn -= m_nNumGettingInSet;
    m_pTargetVehicle->ClearGettingInFlags(m_nDoorFlagsSet);
}

// 0x63A730
bool CTaskComplexEnterCar::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x63A730, CTask*, CPed*, int32, const CEvent*>(this, ped, priority, event);
}

// 0x63E990
CTask* CTaskComplexEnterCar::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63E990, CTask*, CPed*>(this, ped);
}

// 0x643A60
CTask* CTaskComplexEnterCar::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x643A60, CTask*, CPed*>(this, ped);
}

// 0x63A890
CTask* CTaskComplexEnterCar::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63A890, CTask*, CPed*>(this, ped);
}

// 0x63E040
CTask* CTaskComplexEnterCar::CreateSubTask(eTaskType type, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63E040, CTaskComplexEnterCar*, eTaskType, CPed*>(this, type, ped);
}

// 0x63F970
CTask* CTaskComplexEnterCar::CreateNextSubTask_AfterSimpleCarAlign(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x63F970, CTask*, CPed*>(this, ped);
}

CVector CTaskComplexEnterCar::GetTargetPos() {
    CVector temp;
    plugin::CallMethod<0x63A300, CTaskComplexEnterCar*, CVector&>(this, temp);
    return temp;
}
