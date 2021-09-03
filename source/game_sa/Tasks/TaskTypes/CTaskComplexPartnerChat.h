#pragma once 
#include "CTaskComplexPartner.h"

class CTaskComplexPartnerChat : public CTaskComplexPartner
{
public:
    int32 field_70;
    bool m_conversationEnabled;
    char field_75;
    bool m_pedConversationLoaded;

    static void InjectHooks();

    CTaskComplexPartnerChat(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int8 updateDirectionCount, bool conversationEnabled, bool a8, CVector point);
    ~CTaskComplexPartnerChat();
private:
    CTaskComplexPartnerChat* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int8 updateDirectionCount, bool conversationEnabled, bool a8, CVector point);
public:
    CTask* Clone() override { return new CTaskComplexPartnerChat(m_commandName, m_partner, m_leadSpeaker,  m_distanceMultiplier, m_updateDirectionCount, m_conversationEnabled, field_75, m_point); }
    eTaskType GetId() override { return TASK_COMPLEX_PARTNER_CHAT; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    virtual CTaskComplexSequence* GetPartnerSequence();

};

VALIDATE_SIZE(CTaskComplexPartnerChat, 0x78);
