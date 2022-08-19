#include "StdInc.h"

#include "EventSeenPanickedPed.h"

void CEventSeenPanickedPed::InjectHooks() {
    RH_ScopedClass(CEventSeenPanickedPed);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x4B2080);
    RH_ScopedVirtualInstall(AffectsPed, 0x4B53C0);
}

CEventSeenPanickedPed* CEventSeenPanickedPed::Constructor(CPed* ped) { this->CEventSeenPanickedPed::CEventSeenPanickedPed(ped); return this; }
bool CEventSeenPanickedPed::AffectsPed(CPed* ped) { return CEventSeenPanickedPed::AffectsPed_Reversed(ped); }

// 0x4B2080
CEventSeenPanickedPed::CEventSeenPanickedPed(CPed* ped) : CEventEditableResponse() {
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

// 0x4B2130
CEventSeenPanickedPed::~CEventSeenPanickedPed() {
    CEntity::SafeCleanUpRef(m_ped);
}

// 0x4B53C0
bool CEventSeenPanickedPed::AffectsPed_Reversed(CPed* ped) {
    if (!ped->IsPlayer() && m_ped && m_ped != ped) {
        CEvent* currentEvent = m_ped->GetEventHandlerHistory().GetCurrentEvent();
        if (currentEvent && currentEvent->GetSourceEntity()) {
            CVector distance = ped->GetPosition() - m_ped->GetPosition();
            return distance.SquaredMagnitude() < 100.0f;
        }
    }
    return false;
}
