#include "StdInc.h"

#include "TaskComplexPartnerChat.h"

void CTaskComplexPartnerChat::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexPartnerChat", "CTaskComplexPartnerChat", 0x684290, &CTaskComplexPartnerChat::Constructor);
}

CTaskComplexPartnerChat::CTaskComplexPartnerChat(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int8 updateDirectionCount, bool conversationEnabled, bool a8, CVector point) :
    CTaskComplexPartner(commandName, partner, leadSpeaker, distanceMultiplier, false, updateDirectionCount, point)
{
    m_taskId = TASK_COMPLEX_PARTNER_CHAT;
    m_pedConversationLoaded = 0;
    m_conversationEnabled = conversationEnabled;
    if (conversationEnabled)
        m_updateDirectionCount = 4;
    field_75 = a8;
    strcpy(m_commandName, commandName);
}

CTaskComplexPartnerChat::~CTaskComplexPartnerChat()
{
    if (m_conversationEnabled && m_pedConversationLoaded)
        CAEPedSpeechAudioEntity::ReleasePedConversation();
}

CTaskComplexPartnerChat* CTaskComplexPartnerChat::Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int8 updateDirectionCount, bool conversationEnabled, bool a8, CVector point)
{
    this->CTaskComplexPartnerChat::CTaskComplexPartnerChat(commandName, partner, leadSpeaker, distanceMultiplier, updateDirectionCount, conversationEnabled, a8, point);
    return this;
}


bool CTaskComplexPartnerChat::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return plugin::CallMethodAndReturn<bool, 0x682C60, CTask*, CPed*, int32, const CEvent*>(this, ped, priority, event);
}

CTaskComplexSequence* CTaskComplexPartnerChat::GetPartnerSequence()
{
    return plugin::CallMethodAndReturn<CTaskComplexSequence*, 0x684380, CTask*>(this);
}
