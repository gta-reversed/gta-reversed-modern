#include "StdInc.h"

#include "EventSexyVehicle.h"

// 0x4AF010
CEventSexyVehicle::CEventSexyVehicle(CVehicle* vehicle) : CEvent() {
    m_vehicle = vehicle;
    CEntity::SafeRegisterRef(m_vehicle);
}

// 0x4AF0A0
CEventSexyVehicle::~CEventSexyVehicle() {
    CEntity::SafeCleanUpRef(m_vehicle);
}

// 0x4AF100
bool CEventSexyVehicle::AffectsPed(CPed* ped) {
    return ped->IsAlive() && m_vehicle;
}
