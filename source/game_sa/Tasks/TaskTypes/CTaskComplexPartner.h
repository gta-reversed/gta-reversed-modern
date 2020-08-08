#pragma once 
#include "CTaskComplex.h"

class CTaskComplexSequence;

enum ePartnerState : std::int8_t
{
    PARTNER_STATE_UNK_1 = 1
};

class CTaskComplexPartner : public CTaskComplex
{
public:
    std::int32_t field_C;
    std::int32_t field_10;
    char m_commandName[32];
    std::int32_t m_taskId;
    CPed* m_partner;
    float m_distanceMultiplier;
    CVector m_point;
    CVector m_targetPoint;
    bool m_leadSpeaker;
    ePartnerState m_partnerState;
    std::int8_t m_firstToTargetFlag;
    std::int8_t m_updateDirectionCount;
    bool m_taskCompleted;
    bool m_makePedAlwaysFacePartner;
    char m_animBlockName[16];
    bool m_requiredAnimsStreamedIn;
    std::int8_t padding;

    static void InjectHooks();

    CTaskComplexPartner(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, std::int8_t updateDirectionCount, CVector point);
    ~CTaskComplexPartner();
private:
    CTaskComplexPartner* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, std::int8_t updateDirectionCount, CVector point);
public:
    eTaskType GetId() override { return TASK_COMPLEX_PARTNER; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    virtual void StreamRequiredAnims();
    virtual void RemoveStreamedAnims();
};

VALIDATE_SIZE(CTaskComplexPartner, 0x70);
