#include "StdInc.h"

#include "TaskSimpleCarWaitForDoorNotToBeInUse.h"

void CTaskSimpleCarWaitForDoorNotToBeInUse::InjectHooks() {
    RH_ScopedVirtualClass(CTaskSimpleCarWaitForDoorNotToBeInUse, 0x86edbc, 9);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x646B70);
    RH_ScopedInstall(Destructor, 0x646C00);
    RH_ScopedVMTInstall(Clone, 0x649D20);
    RH_ScopedVMTInstall(GetTaskType, 0x646BE0);
    RH_ScopedVMTInstall(MakeAbortable, 0x646BF0);
    RH_ScopedVMTInstall(ProcessPed, 0x646C90);
    RH_ScopedVMTInstall(SetPedPosition, 0x646CC0);
}

/*!
* @addr 0x646B70
* @brief Wait until either of the 2 doors are ready
* @param targetVehicle The vehicle whose door we have to wait for
* @param targetDoor Main door to wait for
* @param targetDoorOpposite Alternative door
*/
CTaskSimpleCarWaitForDoorNotToBeInUse::CTaskSimpleCarWaitForDoorNotToBeInUse(CVehicle* targetVehicle, int32 targetDoor, int32 targetDoorOpposite) :
    CTaskSimple(),
    m_TargetVehicle{targetVehicle},
    m_nTargetDoor{ targetDoor },
    m_nTargetDoorOpposite{ targetDoorOpposite }
{
    CEntity::SafeRegisterRef(m_TargetVehicle);
}

// 0x646C00
CTaskSimpleCarWaitForDoorNotToBeInUse::~CTaskSimpleCarWaitForDoorNotToBeInUse() {
    CEntity::SafeCleanUpRef(m_TargetVehicle);
}

// 0x646BF0
bool CTaskSimpleCarWaitForDoorNotToBeInUse::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return true;
}

// 0x646C90
bool CTaskSimpleCarWaitForDoorNotToBeInUse::ProcessPed(CPed* ped) {
    return !m_TargetVehicle || m_TargetVehicle->AnyOfDoorsReady(m_nTargetDoor, m_nTargetDoorOpposite);
}

// 0x646CC0
bool CTaskSimpleCarWaitForDoorNotToBeInUse::SetPedPosition(CPed* ped) {
    if (ped->IsInVehicle(m_TargetVehicle)) {
        ped->SetPedPositionInCar();
    }
    return true;
}
