#include "StdInc.h"

#include "EventGotKnockedOverByCar.h"

void CEventGotKnockedOverByCar::InjectHooks()
{
    RH_ScopedClass(CEventGotKnockedOverByCar);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1B60);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B1C70);
    RH_ScopedInstall(CloneEditable_Reversed, 0x4B7960);
}

// 0x4B1B60
CEventGotKnockedOverByCar::CEventGotKnockedOverByCar(CVehicle* vehicle)
{
    m_vehicle = vehicle;
    if (m_vehicle)
        m_vehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventGotKnockedOverByCar::~CEventGotKnockedOverByCar()
{
    if (m_vehicle)
        m_vehicle->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_vehicle));
}

CEventGotKnockedOverByCar* CEventGotKnockedOverByCar::Constructor(CVehicle* vehicle)
{
    this->CEventGotKnockedOverByCar::CEventGotKnockedOverByCar(vehicle);
    return this;
}

// 0x4B1C70
bool CEventGotKnockedOverByCar::AffectsPed(CPed* ped)
{
    return CEventGotKnockedOverByCar::AffectsPed_Reversed(ped);
}

// 0x4B7960
CEventEditableResponse* CEventGotKnockedOverByCar::CloneEditable()
{
    return CEventGotKnockedOverByCar::CloneEditable_Reversed();
}

bool CEventGotKnockedOverByCar::AffectsPed_Reversed(CPed* ped)
{
    if (m_vehicle && !ped->IsPlayer())
        return ped->IsAlive();
    return false;
}

CEventEditableResponse* CEventGotKnockedOverByCar::CloneEditable_Reversed()
{
    return new CEventGotKnockedOverByCar(m_vehicle);
}
