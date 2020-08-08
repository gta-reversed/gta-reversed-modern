#include "CTaskComplexPartner.h"

class CTaskComplexPartnerShove : public CTaskComplexPartner
{
public:
    std::int32_t field_70;
    static void InjectHooks();

    CTaskComplexPartnerShove(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, std::int8_t updateDirectionCount, CVector point);
    ~CTaskComplexPartnerShove() {};
private:
    CTaskComplexPartnerShove* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, std::int8_t updateDirectionCount, CVector point);
public:
    CTask* Clone() override { return new CTaskComplexPartnerShove(m_commandName, m_partner, m_leadSpeaker, m_distanceMultiplier, m_updateDirectionCount, m_point); }
    eTaskType GetId() override { return TASK_COMPLEX_PARTNER_SHOVE; }
    virtual CTaskComplexSequence* GetPartnerSequence();
};

VALIDATE_SIZE(CTaskComplexPartnerShove, 0x74);
