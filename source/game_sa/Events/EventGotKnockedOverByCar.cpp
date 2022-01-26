#include "StdInc.h"

void CEventGotKnockedOverByCar::InjectHooks()
{
    RH_ScopedClass(CEventGotKnockedOverByCar);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B1B60);
    RH_ScopedInstall(AffectsPed_Reversed, 0x4B1C70);
    RH_ScopedInstall(CloneEditable_Reversed, 0x4B7960);
}

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
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventGotKnockedOverByCar*, 0x4B1B60, CEvent*, CVehicle*>(this, vehicle);
#else
    this->CEventGotKnockedOverByCar::CEventGotKnockedOverByCar(vehicle);
    return this;
#endif
}

bool CEventGotKnockedOverByCar::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B1C70, CEvent*, CPed*>(this, ped);
#else
    return CEventGotKnockedOverByCar::AffectsPed_Reversed(ped);
#endif
}

CEventEditableResponse* CEventGotKnockedOverByCar::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x4B7960, CEvent*>(this);
#else
    return CEventGotKnockedOverByCar::CloneEditable_Reversed();
#endif
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
