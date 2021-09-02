#include "CTaskComplexPartner.h"

class CTaskComplexPartnerGreet : public CTaskComplexPartner
{
public:
    int32 field_70;
    int32 m_handShakeType;

    static void InjectHooks();

    CTaskComplexPartnerGreet(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int32 handShakeType, CVector point);
    ~CTaskComplexPartnerGreet() {};
private:
    CTaskComplexPartnerGreet* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int32 handShakeType, CVector point);
public:
    CTask* Clone() override { return new CTaskComplexPartnerGreet(m_commandName, m_partner, m_leadSpeaker, m_distanceMultiplier, m_handShakeType, m_point); }
    eTaskType GetId() override { return TASK_COMPLEX_PARTNER_GREET; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    void StreamRequiredAnims() override;
    virtual CTaskComplexSequence* GetPartnerSequence();
};

VALIDATE_SIZE(CTaskComplexPartnerGreet, 0x78);
