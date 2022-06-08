#include "StdInc.h"

#include "EventCreatePartnerTask.h"

// 0x5F6190
CEventCreatePartnerTask::CEventCreatePartnerTask(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier) {
    m_randomNumber = randomNumber;
    m_leadSpeaker = leadSpeaker;
    m_distanceMultiplier = distanceMultiplier;
    m_partner = partner;
    CEntity::SafeRegisterRef(m_partner);
}

// 0x5F6200
CEventCreatePartnerTask::~CEventCreatePartnerTask() {
    CEntity::SafeCleanUpRef(m_partner);
}
