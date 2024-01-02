#include "StdInc.h"

#include "EventPedToFlee.h"

// 0x4AF240
CEventPedToFlee::CEventPedToFlee(CPed* ped) {
    m_ped = ped;
    CEntity::SafeRegisterRef(m_ped);
}

// 0x4AF2D0
CEventPedToFlee::~CEventPedToFlee() {
    CEntity::SafeCleanUpRef(m_ped);
}

// 0x4B73D0
CEvent* CEventPedToFlee::Clone() {
    return new CEventPedToFlee(m_ped);
}
