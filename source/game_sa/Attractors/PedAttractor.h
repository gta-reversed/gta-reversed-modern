#pragma once

#include "Plugins\TwoDEffectPlugin\2dEffect.h"
#include "PedTaskPair.h"
#include "SArray.h"
#include <Enums/eMoveState.h>

class CEntity;
class CPed;
class CTask;

class NOTSA_EXPORT_VTABLE CPedAttractor {
public:
    C2dEffectPedAttractor* m_Fx;
    CEntity*               m_Entity;
    SArray<CPed*>          m_AttractPeds;
    SArray<CPed*>          m_ArrivedPeds;
    SArray<CPedTaskPair>   m_PedTaskPairs;
    int32                  m_MaxNumPeds;
    float                  m_Spacing;
    float                  m_AchieveQueueTime;
    float                  m_AchieveQueueShuffleTime;
    float                  m_ArriveRange;
    float                  m_HeadingRange;
    float                  m_DeltaPos;
    float                  m_DeltaHeading;
    CVector                m_Pos;
    CVector                m_QueueDir;
    CVector                m_UseDir;
    eMoveState             m_MoveState;
    char                   m_ScriptName[8];

    inline static SArray<CTask>& ms_tasks = *reinterpret_cast<SArray<CTask>*>(0xC0985C);

public:
    static void InjectHooks();

    void* operator new(unsigned size);
    void  operator delete(void* object);

    CPedAttractor(C2dEffect* effect, CEntity* entity, int32 a3, int32 a4, float a5, float time2, float time1, float a8, float a9, float range, float a11, float a12);

    virtual ePedAttractorType GetType() const { return PED_ATTRACTOR_UNDEFINED; }

    // 0x5EC410, 0x5EC4B0
    virtual ~CPedAttractor();

    void SetTaskForPed(CPed* ped, CTask* task);
    bool RegisterPed(CPed* ped);
    bool DeRegisterPed(CPed* ped);

    bool IsRegisteredWithPed(const CPed* ped);

    virtual bool IsAtHeadOfQueue(CPed* ped);

    CTask* GetTaskForPed(CPed* ped);
    uint32 GetTailOfQueue();
    int32 GetQueueSlot(const CPed*);
    size_t GetNoOfRegisteredPeds() const { return m_AttractPeds.size() + m_ArrivedPeds.size(); }
    CPed* GetHeadOfQueue(); // Replace with `GetArrivedPeds().begin()`

    // 0x
    int32 ComputeFreeSlot();
    float ComputeDeltaPos() const;
    float ComputeDeltaHeading() const;

    void ComputeAttractTime(int32 slotIdx, bool hasArrived, float& outTime) const;

    virtual void ComputeAttractPos(int32 pedId, CVector& outPos);
    virtual void ComputeAttractHeading(int32 bQueue, float& heading);
    virtual void BroadcastDeparture(CPed* ped);

    bool BroadcastArrival(CPed* ped);
    void AbortPedTasks();

    auto& GetAttractPeds() { return m_AttractPeds; }
    auto& GetArrivedPeds() { return m_ArrivedPeds; }
    auto  GetEffect() const { return m_Fx; }
    auto GetEntity() const { return m_Entity; }
};

VALIDATE_SIZE(CPedAttractor, 0x8C);
