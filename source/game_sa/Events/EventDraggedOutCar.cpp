#include "StdInc.h"

#include "EventDraggedOutCar.h"

void CEventDraggedOutCar::InjectHooks() {
    RH_ScopedClass(CEventDraggedOutCar);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4AD250);
    RH_ScopedInstall(AffectsPed, 0x4AD3A0);
    RH_ScopedInstall(AffectsPedGroup, 0x4AD3C0);
    RH_ScopedVirtualInstall(CloneEditable, 0x4B6DC0);
}

// // 0x4AD250
CEventDraggedOutCar::CEventDraggedOutCar(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat) : CEventEditableResponse() {
    m_carjacker = carjacker;
    m_vehicle   = vehicle;
    m_IsDriverSeat = IsDriverSeat;
    CEntity::SafeRegisterRef(m_vehicle);
    CEntity::SafeRegisterRef(m_carjacker);
}

CEventDraggedOutCar::~CEventDraggedOutCar() {
    CEntity::SafeCleanUpRef(m_vehicle);
    CEntity::SafeCleanUpRef(m_carjacker);
}

CEventDraggedOutCar* CEventDraggedOutCar::Constructor(CVehicle* vehicle, CPed* carjacker, bool IsDriverSeat) {
    this->CEventDraggedOutCar::CEventDraggedOutCar(vehicle, carjacker, IsDriverSeat);
    return this;
}

// 0x4AD3A0
bool CEventDraggedOutCar::AffectsPed(CPed* ped) {
    return ped->IsAlive() && m_carjacker;
}

// 0x4AD3C0
bool CEventDraggedOutCar::AffectsPedGroup(CPedGroup* pedGroup) {
    return FindPlayerPed() == pedGroup->GetMembership().GetLeader();
}

// 0x4B6DC0
CEventEditableResponse* CEventDraggedOutCar::CloneEditable() {
    return CEventDraggedOutCar::CloneEditable_Reversed();
}
CEventEditableResponse* CEventDraggedOutCar::CloneEditable_Reversed() {
    return new CEventDraggedOutCar(m_vehicle, m_carjacker, m_IsDriverSeat);
}
