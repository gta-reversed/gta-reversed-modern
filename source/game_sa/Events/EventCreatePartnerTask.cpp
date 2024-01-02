#include "StdInc.h"

#include "EventCreatePartnerTask.h"

// 0x5F6190
CEventCreatePartnerTask::CEventCreatePartnerTask(int32 type, CPed* partner, bool isLeadSpeaker, float meetDist) :
    m_type{type},
    m_partner{partner},
    m_isLeadSpeaker{isLeadSpeaker},
    m_meetDist{meetDist}
{
    CEntity::SafeRegisterRef(m_partner);
}

// 0x5F6200
CEventCreatePartnerTask::~CEventCreatePartnerTask() {
    CEntity::SafeCleanUpRef(m_partner);
}
