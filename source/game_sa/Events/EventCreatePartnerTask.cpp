#include "StdInc.h"

void CEventCreatePartnerTask::InjectHooks()
{
    Install("CEventCreatePartnerTask", "CEventCreatePartnerTask", 0x5F6190, &CEventCreatePartnerTask::Constructor);
}

CEventCreatePartnerTask::CEventCreatePartnerTask(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier)
{
    m_randomNumber = randomNumber;
    m_leadSpeaker = leadSpeaker;
    m_partner = partner;
    m_distanceMultiplier = distanceMultiplier;
    if (partner)
        partner->RegisterReference(reinterpret_cast<CEntity**>(&m_partner));
}

CEventCreatePartnerTask::~CEventCreatePartnerTask()
{
    if (m_partner)
        m_partner->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_partner));
}

CEventCreatePartnerTask* CEventCreatePartnerTask::Constructor(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier)
{
    this->CEventCreatePartnerTask::CEventCreatePartnerTask(randomNumber, partner, leadSpeaker, distanceMultiplier);
    return this;
}
