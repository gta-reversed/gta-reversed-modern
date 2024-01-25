#include "StdInc.h"
#include "EventLeanOnVehicle.h"


void CEventLeanOnVehicle::InjectHooks() {
    RH_ScopedClass(CEventLeanOnVehicle);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x65DAF0);
    RH_ScopedVirtualInstall(IsValid, 0x4B16C0);
}

// 0x65DAF0
CEventLeanOnVehicle* CEventLeanOnVehicle::Constructor(CVehicle* vehicle, int32 leanAnimDurationInMs) { this->CEventLeanOnVehicle::CEventLeanOnVehicle(vehicle, leanAnimDurationInMs); return this; }

// 0x4B16C0
bool CEventLeanOnVehicle::IsValid(CPed* ped) { return CEventLeanOnVehicle::IsValid_Reversed(ped); }

// 0x65DAF0
CEventLeanOnVehicle::CEventLeanOnVehicle(CVehicle* vehicle, int32 leanAnimDurationInMs) : CEvent() {
    m_vehicle = vehicle;
    m_leanAnimDurationInMs = leanAnimDurationInMs;
    CEntity::SafeRegisterRef(m_vehicle);
}

CEventLeanOnVehicle::~CEventLeanOnVehicle() {
    CEntity::SafeCleanUpRef(m_vehicle);
}

bool CEventLeanOnVehicle::IsValid_Reversed(CPed* ped) {
    if (ped)
        return ped->IsAlive();

    if (IsValid(ped))
        return true;

    return false;
}

