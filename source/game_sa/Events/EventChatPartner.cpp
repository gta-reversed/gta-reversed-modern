#include "StdInc.h"

#include "EventChatPartner.h"

// 0x4AECD0
CEventChatPartner::CEventChatPartner(bool leadSpeaker, CPed* partner) : CEvent() {
    m_leadSpeaker = leadSpeaker;
    m_partner = partner;
    CEntity::SafeRegisterRef(m_partner);
}

// 0x4AED60
CEventChatPartner::~CEventChatPartner() {
    CEntity::SafeCleanUpRef(m_partner);
}

// 0x4AEDC0
bool CEventChatPartner::AffectsPed(CPed* ped) {
    return ped->IsAlive() && m_partner;
}
