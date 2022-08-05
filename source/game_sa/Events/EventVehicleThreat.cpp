#include "StdInc.h"

#include "EventVehicleThreat.h"

// 0x4AFB50
CEventVehicleThreat::CEventVehicleThreat(CVehicle* vehicle) : CEventEditableResponse() {
    m_Vehicle = vehicle;
    CEntity::SafeRegisterRef(m_Vehicle);
}

// 0x4AFBF0
CEventVehicleThreat::~CEventVehicleThreat() {
    CEntity::SafeCleanUpRef(m_Vehicle);
}

// 0x4AFC50
bool CEventVehicleThreat::AffectsPed(CPed* ped) {
    return ped->IsAlive();
}
