#include "StdInc.h"

#include "EventDeadPed.h"

#include "IKChainManager_c.h"

void CEventDeadPed::InjectHooks()
{
    Install("CEventDeadPed", "Constructor", 0x4ADEA0, &CEventDeadPed::Constructor);
    Install("CEventDeadPed", "AffectsPed_Reversed", 0x4B4830, &CEventDeadPed::AffectsPed_Reversed);
    Install("CEventDeadPed", "CloneEditable_Reversed", 0x4B6E70, &CEventDeadPed::CloneEditable_Reversed);
}

CEventDeadPed::CEventDeadPed(CPed* ped, bool bUnknown, uint32 deathTimeInMs)
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

// 0x4ADEA0
CEventDeadPed* CEventDeadPed::Constructor(CPed* ped, bool bUnknown, uint32 deathTimeInMs)
{
    this->CEventDeadPed::CEventDeadPed(ped, bUnknown, deathTimeInMs);
    return this;
}

// 0x4B4830
bool CEventDeadPed::AffectsPed(CPed* ped)
{
    return CEventDeadPed::AffectsPed_Reversed(ped);
}

// 0x4B6E70
CEventEditableResponse* CEventDeadPed::CloneEditable()
{
    return CEventDeadPed::CloneEditable_Reversed();
}

bool CEventDeadPed::AffectsPed_Reversed(CPed* ped)
{
    if (m_ped && ped != m_ped && ped->IsAlive()) {
        if(!g_ikChainMan.IsLooking(ped) || g_ikChainMan.GetLookAtEntity(ped) != m_ped) {
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
