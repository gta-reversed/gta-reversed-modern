#include "StdInc.h"

#include "EventVehicleDamage.h"

#include "PedType.h"

void CEventVehicleDamage::InjectHooks()
{
    RH_ScopedClass(CEventVehicleDamage);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B18D0);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B1A00);
    RH_ScopedVirtualInstall(IsCriminalEvent, 0x4B1A90);
    RH_ScopedVirtualInstall(ReportCriminalEvent, 0x4B50B0);
    RH_ScopedVirtualInstall(GetSourceEntity, 0x4B1A70);
}

// 0x4B18D0
CEventVehicleDamage::CEventVehicleDamage(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
    m_attacker = attacker;
    m_vehicle = vehicle;
    m_weaponType = weaponType;
    CEntity::SafeRegisterRef(m_vehicle);
    CEntity::SafeRegisterRef(m_attacker);
}

CEventVehicleDamage::~CEventVehicleDamage()
{
    CEntity::SafeCleanUpRef(m_vehicle);
    CEntity::SafeCleanUpRef(m_attacker);
}

CEventVehicleDamage* CEventVehicleDamage::Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
    this->CEventVehicleDamage::CEventVehicleDamage(vehicle, attacker, weaponType);
    return this;
}

// 0x4B1A00
bool CEventVehicleDamage::AffectsPed(CPed* ped)
{
    return CEventVehicleDamage::AffectsPed_Reversed(ped);
}

// 0x4B1A90
bool CEventVehicleDamage::IsCriminalEvent()
{
    return CEventVehicleDamage::IsCriminalEvent_Reversed();
}

// 0x4B50B0
void CEventVehicleDamage::ReportCriminalEvent(CPed* ped)
{
    return CEventVehicleDamage::ReportCriminalEvent_Reversed(ped);
}

// 0x4B1A70
CEntity* CEventVehicleDamage::GetSourceEntity() const
{
    return CEventVehicleDamage::GetSourceEntity_Reversed();
}

bool CEventVehicleDamage::AffectsPed_Reversed(CPed* ped)
{
    if (ped->IsAlive() && m_attacker) {
        if (!ped->IsInVehicleThatHasADriver())
            return m_vehicle && ped->m_pVehicle == m_vehicle;
    }
    return false;
}

bool CEventVehicleDamage::IsCriminalEvent_Reversed()
{
    if (m_attacker) {
        switch (m_attacker->m_nType) {
        case ENTITY_TYPE_PED:
            return m_attacker->AsPed()->IsPlayer();
        case ENTITY_TYPE_VEHICLE:
            return m_attacker->AsVehicle()->m_pDriver == FindPlayerPed();
        }
    }
    return false;
}

void CEventVehicleDamage::ReportCriminalEvent_Reversed(CPed* ped)
{
    if (IsCriminalEvent() && m_attacker) {
        bool bPoliceDontReallyCare = CPedType::PoliceDontCareAboutCrimesAgainstPedType(ped->m_nPedType);
        if (ped->m_nPedType == PED_TYPE_COP) 
            FindPlayerWanted()->RegisterCrime(eCrimeType::CRIME_VEHICLE_DAMAGE, m_attacker->GetPosition(), ped, bPoliceDontReallyCare);
    }
}

CEntity* CEventVehicleDamage::GetSourceEntity_Reversed() const
{
    if (m_attacker && m_attacker->IsVehicle()) {
        CVehicle* vehicle = m_attacker->AsVehicle();
        if (vehicle->m_pDriver)
            return vehicle->m_pDriver;
    }
    return m_attacker;
}
