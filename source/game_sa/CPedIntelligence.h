/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskManager.h"
#include "CEventHandler.h"
#include "CEventGroup.h"
#include "CEntityScanner.h"
#include "CTaskTimer.h"
#include "CEventScanner.h"
#include "CTaskSimpleUseGun.h"
#include "CTaskSimpleJetpack.h"
#include "CTaskSimpleFight.h"
#include "CTaskSimpleHoldEntity.h"
#include "CTaskSimpleThrowProjectile.h"
#include "CTaskSimpleSwim.h"
#include "CTaskSimpleDuck.h"
#include "CTaskSimpleClimb.h"
#include "CTaskSimpleJetpack.h"
#include "CTaskSimpleInAir.h"

class  CPedIntelligence {
public:
    class CPed    *m_pPed;
    CTaskManager   m_TaskMgr;
    CEventHandler  m_eventHandler;
    CEventGroup    m_eventGroup;
    unsigned int   m_nDecisionMakerType;
    unsigned int   m_nDecisionMakerTypeInGroup;
    float          m_fHearingRange;
    float          m_fSeeingRange;
    unsigned int   m_nDmNumPedsToScan;
    float          m_fDmRadius;
    int field_CC;
    char field_D0;
    unsigned char  m_nEventId;
    unsigned char  m_nEventPriority;
    char field_D3;
    CEntityScanner m_vehicleScanner;
    CEntityScanner m_pedScanner;
    char field_174;
    char gap_175[3];
    CTaskTimer field_178;
    int field_184;
    char field_188;
    char gap_189[3];
    CEventScanner  m_eventScanner;
    char field_260;
    char gap_261[3];
    char field_264[16];
    int field_274;
    int field_278;
    char gap_27C[12];
    class CEntity *m_apInterestingEntities[3];
    
	void SetPedDecisionMakerType(int newtype);
	void SetPedDecisionMakerTypeInGroup(int newtype);
	void RestorePedDecisionMakerType();
	void SetHearingRange(float range);
	void SetSeeingRange(float range);
	bool IsInHearingRange(CVector const& posn);
	bool IsInSeeingRange(CVector* posn);
	bool FindRespectedFriendInInformRange();
	bool IsRespondingToEvent(int event);
	void AddTaskPhysResponse(CTask* task, bool arg2);
	void AddTaskEventResponseTemp(CTask* task, bool arg2);
	void AddTaskEventResponseNonTemp(CTask* task, bool arg2);
	void AddTaskPrimaryMaybeInGroup(CTask* task, bool arg2);
	CTask* FindTaskByType(int type);
	CTaskSimpleFight* GetTaskFighting();
	CTaskSimpleUseGun* GetTaskUseGun();
	CTaskSimpleThrowProjectile* GetTaskThrow();
	CTaskSimpleHoldEntity* GetTaskHold(bool arg1);
	CTaskSimpleSwim* GetTaskSwim();
	CTaskSimpleDuck* GetTaskDuck(bool arg1);
	CTaskSimpleJetPack* GetTaskJetPack();
	CTaskSimpleInAir* GetTaskInAir();
	CTaskSimpleClimb* GetTaskClimb();
	bool GetUsingParachute();
	void SetTaskDuckSecondary(unsigned short arg1);
	void ClearTaskDuckSecondary();
	void ClearTasks(bool arg1, bool arg2);
	void FlushImmediately(bool arg1);
	C2dEffect* GetEffectInUse();
	void SetEffectInUse(C2dEffect* arg1);
	void ProcessAfterProcCol();
	void ProcessAfterPreRender();
	void ProcessEventHandler();
	bool IsFriendlyWith(CPed const& ped);
	bool IsThreatenedBy(CPed const& ped);
	bool Respects(CPed const& ped);
	bool IsInACarOrEnteringOne();
	static bool AreFriends(CPed const& ped1, CPed const& ped2);
	bool IsPedGoingSomewhereOnFoot();
	int* GetMoveStateFromGoToTask();
	void FlushIntelligence();
	bool TestForStealthKill(CPed* pPed, bool arg2);
	void RecordEventForScript(int EventID, int EventPriority);
	bool HasInterestingEntites();
	bool IsInterestingEntity(CEntity* pEntity);
	void LookAtInterestingEntities();
	void RemoveAllInterestingEntities();
	bool IsPedGoingForCarDoor();
	float CanSeeEntityWithLights(CEntity const* pEntity, bool arg2);
	void ProcessStaticCounter();
	void ProcessFirst();
	void Process();
    CTask* GetActivePrimaryTask();
	static void operator delete(void* arg1);
};

VALIDATE_SIZE(CPedIntelligence, 0x294);
