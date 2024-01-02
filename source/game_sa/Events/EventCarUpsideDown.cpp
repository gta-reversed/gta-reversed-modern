#include "StdInc.h"

#include "EventCarUpsideDown.h"

void CEventCarUpsideDown::InjectHooks() {
    RH_ScopedClass(CEventCarUpsideDown);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1CC0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B1DB0);
}

CEventCarUpsideDown* CEventCarUpsideDown::Constructor(CVehicle* vehicle) { this->CEventCarUpsideDown::CEventCarUpsideDown(vehicle); return this; }
bool CEventCarUpsideDown::AffectsPed(CPed* ped) { return CEventCarUpsideDown::AffectsPed_Reversed(ped); }

// 0x4B1CC0
CEventCarUpsideDown::CEventCarUpsideDown(CVehicle* vehicle) : CEvent() {
    m_vehicle = vehicle;
    CEntity::SafeRegisterRef(m_vehicle);
}

// 0x4B67F0
CEventCarUpsideDown::~CEventCarUpsideDown() {
#if FIX_BUGS
    CEntity::SafeCleanUpRef(m_vehicle);
#else
    CEntity::SafeRegisterRef(m_vehicle);
#endif
}

// 0x4B1DB0
bool CEventCarUpsideDown::AffectsPed_Reversed(CPed* ped) {
    if (ped->IsPlayer()) return false;
    if (ped->bGetOutUpsideDownCar == 0u) return false;
    if (ped->bInVehicle == 0u) return false;
    if (ped->IsCreatedByMission() && (!ped->m_pVehicle || ped->m_pVehicle->IsBoat())) return false;
    if (ped->m_pVehicle->IsBike() || ped->m_pVehicle->IsQuad()) return false;
    return ped->IsAlive();
}
