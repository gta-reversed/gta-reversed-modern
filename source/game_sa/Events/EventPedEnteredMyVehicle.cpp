#include "StdInc.h"

#include "EventPedEnteredMyVehicle.h"

// 0x4AEAC0
CEventPedEnteredMyVehicle::CEventPedEnteredMyVehicle(CPed* ped, CVehicle* vehicle, int32 nUnk) {
    m_Vehicle = vehicle;
    m_Ped = ped;
    m_nUnk = nUnk;
    m_Ped->RegisterReference(m_Ped);
    m_Vehicle->RegisterReference(m_Vehicle);
}

// 0x4AEB90
CEventPedEnteredMyVehicle::~CEventPedEnteredMyVehicle() {
    CEntity::SafeCleanUpRef(m_Ped);
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x4AEC00
bool CEventPedEnteredMyVehicle::AffectsPed(CPed* ped) {
    return ped->IsAlive()
        && ped->m_pVehicle
        && ped->bInVehicle
        && ped->m_pVehicle == m_Vehicle
        && m_Ped;
}
