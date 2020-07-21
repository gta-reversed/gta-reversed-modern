#include "StdInc.h"

CTaskComplexEnterCar::CTaskComplexEnterCar(CVehicle* pTargetVehicle, bool bAsDriver, bool bQuitAfterOpeningDoor,
    bool bQuitAfterDraggingPedOut, bool bCarryOnAfterFallingOff)
{
    m_nFlags = 0;
    m_bAsDriver = bAsDriver;
    m_bQuitAfterOpeningDoor = bQuitAfterOpeningDoor;
    m_bQuitAfterDraggingPedOut = bQuitAfterDraggingPedOut;
    m_bCarryOnAfterFallingOff = bCarryOnAfterFallingOff;
    m_pTargetVehicle = pTargetVehicle;
    m_nTargetDoor = 0;
    m_nTargetDoorOppositeToFlag = 0;
    m_nTargetSeat = 0;
    m_nDraggedPedDownTime = 0;
    m_nMoveState = PEDMOVE_RUN;
    m_nNumGettingInSet = 0;
    m_nCamMovementChoice = 0;
    m_pTaskUtilityLineUpPedWithCar = 0;
    m_bIsAborting = 0;
    m_pDraggedPed = 0;
    m_nDoorFlagsSet = 0;
    m_fCruiseSpeed = -1.0f;
    if (pTargetVehicle)
        pTargetVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
}

CTaskComplexEnterCar::~CTaskComplexEnterCar()
{
    if (m_pTargetVehicle)
        m_pTargetVehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pTargetVehicle));
    delete m_pTaskUtilityLineUpPedWithCar;
    if (!m_pTargetVehicle)
        return;
    m_pTargetVehicle->m_nNumGettingIn -= m_nNumGettingInSet;
    m_pTargetVehicle->ClearGettingInFlags(m_nDoorFlagsSet);
}

bool CTaskComplexEnterCar::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return plugin::CallMethodAndReturn<bool, 0x63A730, CTask*, CPed*, int, CEvent*>(this, ped, priority, _event);
}

CTask* CTaskComplexEnterCar::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x63E990, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexEnterCar::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x643A60, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexEnterCar::ControlSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x63A890, CTask*, CPed*>(this, ped);
}

CTask* CTaskComplexEnterCar::CreateNextSubTask_AfterSimpleCarAlign(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x63F970, CTask*, CPed*>(this, ped);
}
