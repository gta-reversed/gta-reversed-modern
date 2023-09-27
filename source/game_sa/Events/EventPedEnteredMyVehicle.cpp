#include "StdInc.h"

#include "EventPedEnteredMyVehicle.h"

// 0x4AEAC0
CEventPedEnteredMyVehicle::CEventPedEnteredMyVehicle(CPed* pedThatEntered, CVehicle* vehicle, eTargetDoor targetDoor) :
    m_Vehicle{vehicle},
    m_PedThatEntered{pedThatEntered},
    m_TargetDoor{targetDoor}
{
    CEntity::SafeRegisterRef(m_PedThatEntered);
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x4AEB90
CEventPedEnteredMyVehicle::~CEventPedEnteredMyVehicle() {
    CEntity::SafeCleanUpRef(m_PedThatEntered);
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x4AEC00
bool CEventPedEnteredMyVehicle::AffectsPed(CPed* ped) {
    return ped->IsAlive()
        && ped->m_pVehicle
        && ped->bInVehicle
        && ped->m_pVehicle == m_Vehicle
        && m_PedThatEntered;
}
