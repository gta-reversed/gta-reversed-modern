#include "StdInc.h"

#include "EventSignalAtPed.h"

CEventSignalAtPed::CEventSignalAtPed(CPed* ped, int32 a, int8 b) {
    m_f10 = a;
    m_f14 = b;
    m_Ped = ped;
    CEntity::SafeRegisterRef(m_Ped);
}

CEventSignalAtPed::~CEventSignalAtPed() {
    CEntity::SafeCleanUpRef(m_Ped);
}

bool CEventSignalAtPed::AffectsPed(CPed* ped) {
    return true;
}

bool CEventSignalAtPed::IsValid(CPed* ped) {
    if (ped)
        return ped->IsAlive();
    else
        return CEvent::IsValid(nullptr);
}
