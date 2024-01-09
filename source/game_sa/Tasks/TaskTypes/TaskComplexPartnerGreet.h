#include "TaskComplexPartner.h"

class CTaskComplexPartnerGreet : public CTaskComplexPartner {
public:
    int32 field_70;
    int32 m_handShakeType;

public:
    static constexpr auto Type = TASK_COMPLEX_PARTNER_GREET;

    CTaskComplexPartnerGreet(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int32 handShakeType, CVector point);
    ~CTaskComplexPartnerGreet() override = default;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override { return new CTaskComplexPartnerGreet(m_commandName, m_partner, m_leadSpeaker, m_distanceMultiplier, m_handShakeType, m_point); }
    CTask* CreateFirstSubTask(CPed* ped) override;
    void StreamRequiredAnims() override;
    virtual CTaskComplexSequence* GetPartnerSequence();

    static void InjectHooks();
    CTaskComplexPartnerGreet* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, int32 handShakeType, CVector point);
};
VALIDATE_SIZE(CTaskComplexPartnerGreet, 0x78);
