/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eEventType.h"
#include "TaskManager.h"
#include "EventHandler.h"
#include "EventGroup.h"
#include "EntityScanner.h"
#include "TaskTimer.h"
#include "EventScanner.h"
#include "PedStuckChecker.h"
#include "VehicleScanner.h"
#include "MentalHealth.h"

class CPed;
class CEntity;
class CPlayerPed;

class CTaskSimpleUseGun;
class CTaskSimpleFight;
class CTaskSimpleHoldEntity;
class CTaskSimpleThrowProjectile;
class CTaskSimpleSwim;
class CTaskSimpleDuck;
class CTaskSimpleClimb;
class CTaskSimpleJetPack;
class CTaskSimpleInAir;

class CPedIntelligence {
public:
    CPed*            m_pPed{};
    CTaskManager     m_TaskMgr{ m_pPed };
    CEventHandler    m_eventHandler{ m_pPed };
    CEventGroup      m_eventGroup{ m_pPed };
    int32            m_nDecisionMakerType{-1};
    int32            m_nDecisionMakerTypeInGroup{-1};
    float            m_fHearingRange{15.f};
    float            m_fSeeingRange{15.f};
    uint32           m_nDmNumPedsToScan{3};
    float            m_fDmRadius{15.f};
    float            field_CC{30.f};
    char             field_D0{-1};
    uint8            m_nEventId{};
    uint8            m_nEventPriority{};
    char             field_D3{};
    CVehicleScanner  m_vehicleScanner{};
    CEntityScanner   m_entityScanner{};
    CMentalHealth    m_mentalHealth{};
    char             field_188{};
    CEventScanner    m_eventScanner{};
    bool             field_260{};
    CPedStuckChecker m_pedStuckChecker{};
    int32            m_AnotherStaticCounter{};
    int32            m_StaticCounter{};
    CVector          m_vecLastPedPosDuringDamageEntity{};
    CEntity*         m_apInterestingEntities[3]{};

    static float& STEALTH_KILL_RANGE;
    static float& LIGHT_AI_LEVEL_MAX;
    static float& flt_8D2384;
    static float& flt_8D2388;

public:
    static void InjectHooks();

    static void* operator new(unsigned size);
    static void operator delete(void* object);

    CPedIntelligence(CPed* ped);

    CEntity** GetPedEntities();
    void SetPedDecisionMakerType(int32 newType);
    auto GetPedDecisionMakerType() const { return m_nDecisionMakerType; }
    void SetPedDecisionMakerTypeInGroup(int32 newType);
    void RestorePedDecisionMakerType();
    void SetHearingRange(float range);
    void SetSeeingRange(float range);
    bool IsInHearingRange(const CVector& posn);
    bool IsInSeeingRange(const CVector& posn);
    bool FindRespectedFriendInInformRange();
    bool IsRespondingToEvent(eEventType eventType);
    void AddTaskPhysResponse(CTask* task, int32 unUsed);
    void AddTaskEventResponseTemp(CTask* task, int32 unUsed);
    void AddTaskEventResponseNonTemp(CTask* task, int32 unUsed);
    void AddTaskPrimaryMaybeInGroup(CTask* task, bool bAffectsPed);
    CTask* FindTaskByType(int32 taskId);
    CTaskSimpleFight* GetTaskFighting();
    CTaskSimpleUseGun* GetTaskUseGun();
    CTaskSimpleThrowProjectile* GetTaskThrow();
    CTask* GetTaskHold(bool bIgnoreCheckingForSimplestActiveTask);
    CTaskSimpleSwim* GetTaskSwim();
    CTaskSimpleDuck* GetTaskDuck(bool bIgnoreCheckingForSimplestActiveTask);
    CTaskSimpleJetPack* GetTaskJetPack();
    CTaskSimpleInAir* GetTaskInAir();
    CTaskSimpleClimb* GetTaskClimb();
    bool GetUsingParachute();
    void SetTaskDuckSecondary(uint16 nLengthOfDuck);
    void ClearTaskDuckSecondary();
    void ClearTasks(bool bClearPrimaryTasks, bool bClearSecondaryTasks);
    void FlushImmediately(bool bSetPrimaryDefaultTask);
    C2dEffect* GetEffectInUse();
    void SetEffectInUse(C2dEffect* effect);
    void ProcessAfterProcCol();
    void ProcessAfterPreRender();
    void ProcessEventHandler();
    bool IsFriendlyWith(const CPed& ped) const;
    bool IsThreatenedBy(const CPed& ped) const;
    bool Respects(CPed* ped);
    bool IsInACarOrEnteringOne();
    static bool AreFriends(const CPed& ped1, const CPed& ped2);
    bool IsPedGoingSomewhereOnFoot();
    int32 GetMoveStateFromGoToTask();
    void FlushIntelligence();
    bool TestForStealthKill(CPed* pTarget, bool bFullTest);
    void RecordEventForScript(int32 eventId, int32 eventPriority);
    bool HasInterestingEntites();
    bool IsInterestingEntity(CEntity* entity);
    void LookAtInterestingEntities();
    void RemoveAllInterestingEntities();
    bool IsPedGoingForCarDoor();
    float CanSeeEntityWithLights(CEntity* entity, int32 unUsed);
    void ProcessStaticCounter();
    void ProcessFirst();
    void Process();
    CTask* GetActivePrimaryTask();
    float GetPedFOVRange();

    void SetDmRadius(float r) { m_fDmRadius = r; }
    void SetNumPedsToScan(uint32 n) { m_nDmNumPedsToScan = n; }

    // NOTSA
    bool IsUsingGun() {
        if (GetTaskUseGun()) {
            return true;
        }
        if (auto simplestTask = m_TaskMgr.GetSimplestActiveTask()) {
            if (simplestTask->GetTaskType() == TASK_SIMPLE_GANG_DRIVEBY) {
                return true;
            }
        }
        return false;
    }

private:
    CPedIntelligence* Constructor(CPed* ped);
    CPedIntelligence* Destructor();
};

VALIDATE_SIZE(CPedIntelligence, 0x294);
