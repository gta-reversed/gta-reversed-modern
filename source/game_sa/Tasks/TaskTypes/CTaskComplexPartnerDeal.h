#pragma once 
#include "CTaskComplexPartner.h"

class CTaskComplexPartnerDeal : public CTaskComplexPartner
{
public:
    int32 field_70;

    static void InjectHooks();

    CTaskComplexPartnerDeal(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, CVector point);
    ~CTaskComplexPartnerDeal() {};
private:
    CTaskComplexPartnerDeal* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, CVector point);
public:
    CTask* Clone() override { return new CTaskComplexPartnerDeal(m_commandName, m_partner, m_leadSpeaker, m_distanceMultiplier, m_point); }
    eTaskType GetId() override { return TASK_COMPLEX_PARTNER_DEAL; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    void StreamRequiredAnims() override;
    virtual CTaskComplexSequence* GetPartnerSequence();
};

VALIDATE_SIZE(CTaskComplexPartnerDeal, 0x74);
