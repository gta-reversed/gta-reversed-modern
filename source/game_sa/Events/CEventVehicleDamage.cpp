#include "StdInc.h"

void CEventVehicleDamage::InjectHooks()
{
    ReversibleHooks::Install("CEventVehicleDamage", "Constructor", 0x4B18D0, &CEventVehicleDamage::Constructor);
    ReversibleHooks::Install("CEventVehicleDamage", "AffectsPed_Reversed", 0x4B1A00, &CEventVehicleDamage::AffectsPed_Reversed);
    ReversibleHooks::Install("CEventVehicleDamage", "IsCriminalEvent_Reversed", 0x4B1A90, &CEventVehicleDamage::IsCriminalEvent_Reversed);
    ReversibleHooks::Install("CEventVehicleDamage", "ReportCriminalEvent_Reversed", 0x4B50B0, &CEventVehicleDamage::ReportCriminalEvent_Reversed);
    ReversibleHooks::Install("CEventVehicleDamage", "GetSourceEntity_Reversed", 0x4B1A70, &CEventVehicleDamage::GetSourceEntity_Reversed);
}

CEventVehicleDamage::CEventVehicleDamage(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
    m_attacker = attacker;
    m_vehicle = vehicle;
    m_weaponType = weaponType;
    if (m_vehicle)
        m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
    if (m_attacker)
        m_attacker->RegisterReference(&m_attacker);
}

CEventVehicleDamage::~CEventVehicleDamage()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
    if (m_attacker)
        m_attacker->CleanUpOldReference(&m_attacker);
}

CEventVehicleDamage* CEventVehicleDamage::Constructor(CVehicle* vehicle, CEntity* attacker, eWeaponType weaponType)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventVehicleDamage*, 0x4B18D0, CEvent*, CVehicle*, CEntity*, eWeaponType> (this, vehicle, attacker, weaponType);
#else

    this->CEventVehicleDamage::CEventVehicleDamage(vehicle, attacker, weaponType);
    return this;
#endif
}

bool CEventVehicleDamage::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1A00, CEvent*, CPed*>(this, ped);
#else
    return CEventVehicleDamage::AffectsPed_Reversed(ped);
#endif
}

bool CEventVehicleDamage::IsCriminalEvent()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1A90, CEvent*>(this);
#else
    return CEventVehicleDamage::IsCriminalEvent_Reversed();
#endif
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
        CPed* ped = static_cast<CPed*>(m_attacker);
        CVehicle* vehicle = static_cast<CVehicle*>(m_attacker);
        switch (m_attacker->m_nType)
        {
        case ENTITY_TYPE_PED:
            return ped->IsPlayer();
        case ENTITY_TYPE_VEHICLE:
            return vehicle->m_pDriver == FindPlayerPed(-1);
        }
    }
    return false;
}

void CEventVehicleDamage::ReportCriminalEvent_Reversed(CPed* ped)
{
    if (IsCriminalEvent() && m_attacker) {
        bool bPoliceDontReallyCare = CPedType::PoliceDontCareAboutCrimesAgainstPedType(ped->m_nPedType);
        if (ped->m_nPedType == PED_TYPE_COP) 
            FindPlayerWanted(-1)->RegisterCrime(eCrimeType::CRIME_VEHICLE_DAMAGE, m_attacker->GetPosition(), ped, bPoliceDontReallyCare);
    }
}

CEntity* CEventVehicleDamage::GetSourceEntity_Reversed() const
{
    if (m_attacker && m_attacker->m_nType == ENTITY_TYPE_VEHICLE) {
        CVehicle* vehicle = static_cast<CVehicle*>(m_attacker);
        if (vehicle->m_pDriver)
            return vehicle->m_pDriver;
    }
    return m_attacker;
}
