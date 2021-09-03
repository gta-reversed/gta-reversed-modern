#pragma once 
#include "CTaskComplex.h"

class CTaskComplexSequence;

enum ePartnerState : int8
{
    PARTNER_STATE_UNK_1 = 1
};

class CTaskComplexPartner : public CTaskComplex
{
public:
    int32 field_C;
    int32 field_10;
    char m_commandName[32];
    int32 m_taskId;
    CPed* m_partner;
    float m_distanceMultiplier;
    CVector m_point;
    CVector m_targetPoint;
    bool m_leadSpeaker;
    ePartnerState m_partnerState;
    int8 m_firstToTargetFlag;
    int8 m_updateDirectionCount;
    bool m_taskCompleted;
    bool m_makePedAlwaysFacePartner;
    char m_animBlockName[16];
    bool m_requiredAnimsStreamedIn;
    int8 padding;

    static void InjectHooks();

    CTaskComplexPartner(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, int8 updateDirectionCount, CVector point);
    ~CTaskComplexPartner();
private:
    CTaskComplexPartner* Constructor(const char* commandName, CPed* partner, bool leadSpeaker, float distanceMultiplier, bool makePedAlwaysFacePartner, int8 updateDirectionCount, CVector point);
public:
    eTaskType GetId() override { return TASK_COMPLEX_PARTNER; }
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    virtual void StreamRequiredAnims();
    virtual void RemoveStreamedAnims();
};

VALIDATE_SIZE(CTaskComplexPartner, 0x70);
