#include "StdInc.h"

#include "EventCreatePartnerTask.h"

void CEventCreatePartnerTask::InjectHooks()
{
    RH_ScopedClass(CEventCreatePartnerTask);
    RH_ScopedCategory("Events");

    RH_ScopedInstall(Constructor, 0x5F6190);
}

CEventCreatePartnerTask::CEventCreatePartnerTask(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier)
{
    m_randomNumber       = randomNumber;
    m_leadSpeaker        = leadSpeaker;
    m_distanceMultiplier = distanceMultiplier;
    m_partner            = partner;
    CEntity::SafeRegisterRef(m_partner);
}

CEventCreatePartnerTask::~CEventCreatePartnerTask()
{
    CEntity::SafeCleanUpRef(m_partner);
}

CEventCreatePartnerTask* CEventCreatePartnerTask::Constructor(int32 randomNumber, CPed* partner, bool leadSpeaker, float distanceMultiplier)
{
    this->CEventCreatePartnerTask::CEventCreatePartnerTask(randomNumber, partner, leadSpeaker, distanceMultiplier);
    return this;
}
