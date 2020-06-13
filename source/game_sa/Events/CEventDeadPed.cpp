#include "StdInc.h"

void CEventDeadPed::InjectHooks()
{
    HookInstall(0x4ADEA0, &CEventDeadPed::Constructor);
    HookInstall(0x4B4830, &CEventDeadPed::AffectsPed_Reversed);
    HookInstall(0x4B6E70, &CEventDeadPed::CloneEditable_Reversed);
}

CEventDeadPed::CEventDeadPed(CPed* ped, bool bUnknown, std::uint32_t deathTimeInMs)
{
    m_ped = ped;
    field_18 = bUnknown;
    m_deathTimeInMs = deathTimeInMs;
    if (m_ped)
        m_ped->RegisterReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventDeadPed::~CEventDeadPed()
{
    if (m_ped)
        m_ped->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_ped));
}

CEventDeadPed* CEventDeadPed::Constructor(CPed* ped, bool bUnknown, std::uint32_t deathTimeInMs)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventDeadPed*, 0x4ADEA0, CEvent*, CPed*, bool, std::uint32_t>(this, ped, bUnknown, deathTimeInMs);
#else
    this->CEventDeadPed::CEventDeadPed(ped, bUnknown, deathTimeInMs);
    return this;
#endif
}

bool CEventDeadPed::AffectsPed(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x4B4830, CEvent*, CPed*>(this, ped);
#else
    return CEventDeadPed::AffectsPed_Reversed(ped);
#endif
}

CEventEditableResponse* CEventDeadPed::CloneEditable()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEventEditableResponse*, 0x4B6E70, CEvent*>(this);
#else
    return CEventDeadPed::CloneEditable_Reversed();
#endif
}


bool CEventDeadPed::AffectsPed_Reversed(CPed* ped)
{
    if (m_ped && ped != m_ped && ped->IsAlive()) {
        if(!g_ikChainMan->IsLooking(ped) || g_ikChainMan->GetLookAtEntity(ped) != m_ped) {
            if (!m_ped->physicalFlags.bSubmergedInWater) {
                CVector distance = m_ped->GetPosition() - ped->GetPosition();
                if (m_ped->bKilledByStealth) {
                    const float squaredMagnitude = distance.SquaredMagnitude();
                    if (DotProduct(distance, ped->GetForward()) >= 0.0f && squaredMagnitude <= 8.0f * 8.0f)
                        return 20.0f * 20.0f > squaredMagnitude;
                }
            }
        }
    }
    return false;
}

CEventEditableResponse* CEventDeadPed::CloneEditable_Reversed()
{
    return new CEventDeadPed(m_ped, field_18, m_deathTimeInMs);
}
