/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CPedIntelligence.h"

#include "CPedType.h"
#include "CTaskSimpleCarDriveTimed.h"
#include "CTaskSimpleStandStill.h"
#include "CTaskComplexFacial.h"
#include "CTaskComplexEnterCar.h"
#include "CTaskSimpleGoTo.h"
#include "CTaskComplexKillPedOnFoot.h"
#include "CTaskSimplePlayerOnFoot.h"
#include "CTaskComplexWander.h"

float& CPedIntelligence::STEALTH_KILL_RANGE = *reinterpret_cast<float*>(0x8D2398); // 2.5f
float& CPedIntelligence::LIGHT_AI_LEVEL_MAX = *reinterpret_cast<float*>(0x8D2380); // 0.3f
float& CPedIntelligence::flt_8D2384 = *reinterpret_cast<float*>(0x8D2384); // 30.0f
float& CPedIntelligence::flt_8D2388 = *reinterpret_cast<float*>(0x8D2388); // 50.0f

void CPedIntelligence::InjectHooks()
{
    ReversibleHooks::Install("CPedIntelligence", "GetPedEntities",0x4893E0, &CPedIntelligence::GetPedEntities);
    ReversibleHooks::Install("CPedIntelligence", "SetPedDecisionMakerType",0x600B50, &CPedIntelligence::SetPedDecisionMakerType);
    ReversibleHooks::Install("CPedIntelligence", "SetPedDecisionMakerTypeInGroup",0x600BB0, &CPedIntelligence::SetPedDecisionMakerTypeInGroup);
    ReversibleHooks::Install("CPedIntelligence", "RestorePedDecisionMakerType",0x600BC0, &CPedIntelligence::RestorePedDecisionMakerType);
    ReversibleHooks::Install("CPedIntelligence", "SetHearingRange",0x600BE0, &CPedIntelligence::SetHearingRange);
    ReversibleHooks::Install("CPedIntelligence", "SetSeeingRange",0x600BF0, &CPedIntelligence::SetSeeingRange);
    ReversibleHooks::Install("CPedIntelligence", "IsInSeeingRange",0x600C60, &CPedIntelligence::IsInSeeingRange);
    ReversibleHooks::Install("CPedIntelligence", "FindRespectedFriendInInformRange",0x600CF0, &CPedIntelligence::FindRespectedFriendInInformRange);
    ReversibleHooks::Install("CPedIntelligence", "IsRespondingToEvent",0x600DB0, &CPedIntelligence::IsRespondingToEvent);
    ReversibleHooks::Install("CPedIntelligence", "AddTaskPhysResponse",0x600DC0, &CPedIntelligence::AddTaskPhysResponse);
    ReversibleHooks::Install("CPedIntelligence", "AddTaskEventResponseTemp",0x600DE0, &CPedIntelligence::AddTaskEventResponseTemp);
    ReversibleHooks::Install("CPedIntelligence", "AddTaskEventResponseNonTemp",0x600E00, &CPedIntelligence::AddTaskEventResponseNonTemp);;
    ReversibleHooks::Install("CPedIntelligence", "AddTaskPrimaryMaybeInGroup",0x600E20, &CPedIntelligence::AddTaskPrimaryMaybeInGroup);
    ReversibleHooks::Install("CPedIntelligence", "FindTaskByType",0x600EE0, &CPedIntelligence::FindTaskByType);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskFighting",0x600F30, &CPedIntelligence::GetTaskFighting);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskUseGun",0x600F70, &CPedIntelligence::GetTaskUseGun);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskThrow",0x600FB0, &CPedIntelligence::GetTaskThrow);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskHold",0x600FF0, &CPedIntelligence::GetTaskHold);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskSwim",0x601070, &CPedIntelligence::GetTaskSwim);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskDuck",0x6010A0, &CPedIntelligence::GetTaskDuck);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskJetPack",0x601110, &CPedIntelligence::GetTaskJetPack);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskInAir",0x601150, &CPedIntelligence::GetTaskInAir);
    ReversibleHooks::Install("CPedIntelligence", "GetTaskClimb",0x601180, &CPedIntelligence::GetTaskClimb);
    ReversibleHooks::Install("CPedIntelligence", "GetUsingParachute",0x6011B0, &CPedIntelligence::GetUsingParachute);
    ReversibleHooks::Install("CPedIntelligence", "SetTaskDuckSecondary",0x601230, &CPedIntelligence::SetTaskDuckSecondary);
    ReversibleHooks::Install("CPedIntelligence", "ClearTaskDuckSecondary",0x601390, &CPedIntelligence::ClearTaskDuckSecondary);
    ReversibleHooks::Install("CPedIntelligence", "ClearTasks",0x601420, &CPedIntelligence::ClearTasks);
    ReversibleHooks::Install("CPedIntelligence", "FlushImmediately",0x601640, &CPedIntelligence::FlushImmediately);
    ReversibleHooks::Install("CPedIntelligence", "GetEffectInUse",0x6018D0, &CPedIntelligence::GetEffectInUse);
    ReversibleHooks::Install("CPedIntelligence", "SetEffectInUse",0x6018E0, &CPedIntelligence::SetEffectInUse);
    ReversibleHooks::Install("CPedIntelligence", "ProcessAfterProcCol",0x6018F0, &CPedIntelligence::ProcessAfterProcCol);
    ReversibleHooks::Install("CPedIntelligence", "ProcessAfterPreRender",0x6019B0, &CPedIntelligence::ProcessAfterPreRender);
    ReversibleHooks::Install("CPedIntelligence", "ProcessEventHandler",0x601BB0, &CPedIntelligence::ProcessEventHandler);
    ReversibleHooks::Install("CPedIntelligence", "IsFriendlyWith",0x601BC0, &CPedIntelligence::IsFriendlyWith);
    ReversibleHooks::Install("CPedIntelligence", "IsThreatenedBy",0x601C30, &CPedIntelligence::IsThreatenedBy);
    ReversibleHooks::Install("CPedIntelligence", "Respects",0x601C90, &CPedIntelligence::Respects);
    ReversibleHooks::Install("CPedIntelligence", "IsInACarOrEnteringOne",0x601CC0, &CPedIntelligence::IsInACarOrEnteringOne);
    ReversibleHooks::Install("CPedIntelligence", "AreFriends",0x601D10, &CPedIntelligence::AreFriends);
    ReversibleHooks::Install("CPedIntelligence", "GetMoveStateFromGoToTask",0x601D70, &CPedIntelligence::GetMoveStateFromGoToTask);
    ReversibleHooks::Install("CPedIntelligence", "FlushIntelligence",0x601DA0, &CPedIntelligence::FlushIntelligence);
    ReversibleHooks::Install("CPedIntelligence", "TestForStealthKill",0x601E00, &CPedIntelligence::TestForStealthKill);
    ReversibleHooks::Install("CPedIntelligence", "RecordEventForScript",0x602050, &CPedIntelligence::RecordEventForScript);
    ReversibleHooks::Install("CPedIntelligence", "IsInterestingEntity",0x6020A0, &CPedIntelligence::IsInterestingEntity);
    ReversibleHooks::Install("CPedIntelligence", "LookAtInterestingEntities",0x6020D0, &CPedIntelligence::LookAtInterestingEntities);
    ReversibleHooks::Install("CPedIntelligence", "IsPedGoingForCarDoor",0x602350, &CPedIntelligence::IsPedGoingForCarDoor);
    ReversibleHooks::Install("CPedIntelligence", "CanSeeEntityWithLights",0x605550, &CPedIntelligence::CanSeeEntityWithLights);
    ReversibleHooks::Install("CPedIntelligence", "ProcessStaticCounter",0x605650, &CPedIntelligence::ProcessStaticCounter);
    ReversibleHooks::Install("CPedIntelligence", "ProcessFirst",0x6073A0, &CPedIntelligence::ProcessFirst);
    ReversibleHooks::Install("CPedIntelligence", "Process",0x608260, &CPedIntelligence::Process);
    ReversibleHooks::Install("CPedIntelligence", "GetActivePrimaryTask",0x4B85B0, &CPedIntelligence::GetActivePrimaryTask);
}

// 0x4893E0
CEntity** CPedIntelligence::GetPedEntities()
{
    return m_entityScanner.m_apEntities;
}

// 0x600B50
void CPedIntelligence::SetPedDecisionMakerType(int32 newType) {
    int32 oldType = m_nDecisionMakerType;
    if (oldType)
    {
        if (!newType)
        {
            m_nDecisionMakerTypeInGroup = oldType;
        }
        m_nDecisionMakerType = newType;
    }
    else
    {
        m_nDecisionMakerTypeInGroup = newType;
    }
    if (m_nDecisionMakerType == DM_EVENT_PED_ENTERED_MY_VEHICLE)
    {
        m_fDmRadius = 5.0f;
        m_nDmNumPedsToScan = 15;
    }
}

// 0x600BB0
void CPedIntelligence::SetPedDecisionMakerTypeInGroup(int32 newType) {
    m_nDecisionMakerTypeInGroup = newType;
}

// 0x600BC0
void CPedIntelligence::RestorePedDecisionMakerType() {
    if (!m_nDecisionMakerType)
    {
        m_nDecisionMakerType = m_nDecisionMakerTypeInGroup;
    }
}

// 0x600BE0
void CPedIntelligence::SetHearingRange(float range) {
    m_fHearingRange = range;
}

// 0x600BF0
void CPedIntelligence::SetSeeingRange(float range) {
    m_fSeeingRange = range;
}

// Unused
// 0x600C00
bool CPedIntelligence::IsInHearingRange(const CVector& posn) {
    return plugin::CallMethodAndReturn<bool, 0x600C00, CPedIntelligence*, CVector const&>(this, posn);
}

// 0x600C60
bool CPedIntelligence::IsInSeeingRange(const CVector& posn) {
    CVector distance = posn - m_pPed->GetPosition();
    if (m_fSeeingRange * m_fSeeingRange > distance.SquaredMagnitude()) {
        if (DotProduct(distance, m_pPed->GetForward()) > 0.0f)
            return true;
    }
    return false;
}

// 0x600CF0
bool CPedIntelligence::FindRespectedFriendInInformRange() {
    uint32 acquaintances = m_pPed->m_acquaintance.GetAcquaintances(0);
    for (uint32 pedScanIndex = 0; pedScanIndex < m_nDmNumPedsToScan; pedScanIndex++) {
        CPed* pPedEntity = (CPed*)m_entityScanner.m_apEntities[pedScanIndex];
        if (pPedEntity) {
            if (CPedType::GetPedFlag(pPedEntity->m_nPedType) & acquaintances) {
                CVector distance = m_pPed->GetPosition() - pPedEntity->GetPosition();
                if ((m_fDmRadius * m_fDmRadius) > distance.SquaredMagnitude())
                    return true;
            }
        }
    }
    return false;
}

// 0x600DB0
bool CPedIntelligence::IsRespondingToEvent(eEventType eventType) {
    return m_eventHandler.m_history.IsRespondingToEvent(eventType);
}

// (CTask *task, bool arg2)
// 0x600DC0
void CPedIntelligence::AddTaskPhysResponse(CTask* pTask, int32 unUsed) {
    m_TaskMgr.SetTask(pTask, 0, unUsed);
}

// (CTask *task, bool arg2)
// 0x600DE0
void CPedIntelligence::AddTaskEventResponseTemp(CTask* pTask, int32 unUsed) {
    m_TaskMgr.SetTask(pTask, 1, unUsed);
}

// (CTask *task,bool arg2)
// 0x600E00
void CPedIntelligence::AddTaskEventResponseNonTemp(CTask* pTask, int32 unUsed) {
    m_TaskMgr.SetTask(pTask, 2, unUsed);
}

// 0x600E20
void CPedIntelligence::AddTaskPrimaryMaybeInGroup(CTask* pTask, bool bAffectsPed) {
    CPedGroup* pPegGroup = CPedGroups::GetPedsGroup(m_pPed);
    if (m_pPed->IsPlayer() || !pPegGroup)
    {
        CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, pTask, bAffectsPed);
        m_eventGroup.Add(&eventScriptCommand, false);
    }
    else
    {
        pPegGroup->m_groupIntelligence.SetScriptCommandTask(m_pPed, pTask);
        delete pTask;
    }
}

// 0x600EE0
CTask* CPedIntelligence::FindTaskByType(int32 taskId) {
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* result = pTaskManager->FindTaskByType(TASK_PRIMARY_DEFAULT, taskId);
    if (!result)
    {
        result = pTaskManager->FindTaskByType(TASK_PRIMARY_PRIMARY, taskId);
        if (!result)
        {
            result = pTaskManager->FindTaskByType(TASK_PRIMARY_EVENT_RESPONSE_TEMP, taskId);
            if (!result)
            {
                result = pTaskManager->FindTaskByType(TASK_PRIMARY_EVENT_RESPONSE_NONTEMP, taskId);
            }
        }
    }
    return result;
}

// 0x600F30
CTaskSimpleFight* CPedIntelligence::GetTaskFighting() {
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pTaskSecondary = pTaskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pTaskSecondary && pTaskSecondary->GetTaskType() == TASK_SIMPLE_FIGHT)
    {
        return (CTaskSimpleFight*)pTaskSecondary;
    }
    return nullptr;
}

// 0x600F70
CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun() {
    CTask* pTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pTask && pTask->GetTaskType() == TASK_SIMPLE_USE_GUN)
    {
        return (CTaskSimpleUseGun*)pTask;
    }
    return nullptr;
}

// 0x600FB0
CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow() {
    CTask* pTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pTask && pTask->GetTaskType() == TASK_SIMPLE_THROW)
    {
        return (CTaskSimpleThrowProjectile*)pTask;
    }
    return nullptr;
}

// 0x600FF0
CTask* CPedIntelligence::GetTaskHold(bool bIgnoreCheckingForSimplestActiveTask) {
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pTaskSecondary = pTaskManager->GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (pTaskSecondary)
    {
        if (pTaskSecondary->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY)
        {
            return pTaskSecondary;
        }
    }
    if (bIgnoreCheckingForSimplestActiveTask)
    {
        return nullptr;
    }

    CTask* pActiveSimplestTask = pTaskManager->GetSimplestActiveTask();
    if (!pActiveSimplestTask
        || pActiveSimplestTask->GetTaskType() != TASK_SIMPLE_PICKUP_ENTITY
        && pActiveSimplestTask->GetTaskType() != TASK_SIMPLE_PUTDOWN_ENTITY)
    {
        return nullptr;
    }
    return pActiveSimplestTask;
}

// 0x601070
CTaskSimpleSwim* CPedIntelligence::GetTaskSwim() {
    CTask* pTask = m_TaskMgr.GetSimplestActiveTask();
    if (pTask && pTask->GetTaskType() == TASK_SIMPLE_SWIM)
    {
        return (CTaskSimpleSwim*)pTask;
    }
    return nullptr;
}

// 0x6010A0
CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool bIgnoreCheckingForSimplestActiveTask) {
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pSecondaryTask = (CTask*)pTaskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);
    if (pSecondaryTask && pSecondaryTask->GetTaskType() == TASK_SIMPLE_DUCK)
    {
        return (CTaskSimpleDuck*)pSecondaryTask;
    }

    if (bIgnoreCheckingForSimplestActiveTask)
    {
        return nullptr;
    }

    CTask* pActiveSimplestTask = pTaskManager->GetSimplestActiveTask();
    if (!pActiveSimplestTask || pActiveSimplestTask->GetTaskType() != TASK_SIMPLE_DUCK)
    {
        return nullptr;
    }
    return (CTaskSimpleDuck*)pActiveSimplestTask;
}

// 0x601110
CTaskSimpleJetPack* CPedIntelligence::GetTaskJetPack() {
    if (m_pPed->IsPlayer())
    {
        CTask* pTask = m_TaskMgr.GetSimplestActiveTask();
        if (pTask && pTask->GetTaskType() == TASK_SIMPLE_JETPACK)
        {
            return (CTaskSimpleJetPack*)pTask;
        }
    }
    return nullptr;
}

// 0x601150
CTaskSimpleInAir* CPedIntelligence::GetTaskInAir() {
    CTask* pTask = m_TaskMgr.GetSimplestActiveTask();
    if (pTask && pTask->GetTaskType() == TASK_SIMPLE_IN_AIR)
    {
        return (CTaskSimpleInAir*)pTask;
    }
    return nullptr;
}

// 0x601180
CTaskSimpleClimb* CPedIntelligence::GetTaskClimb() {
    auto pTask = (CTaskSimpleClimb*)m_TaskMgr.GetSimplestActiveTask();
    if (pTask && pTask->GetTaskType() == TASK_SIMPLE_CLIMB)
    {
        return pTask;
    }
    return nullptr;
}

// 0x6011B0
bool CPedIntelligence::GetUsingParachute() {
    CWeapon* pActiveWeapon = &m_pPed->m_aWeapons[m_pPed->m_nActiveWeaponSlot];
    if (pActiveWeapon->m_nType != WEAPON_PARACHUTE)
    {
        return false;
    }

    CPed* pPed = m_pPed;
    if (pPed->bIsStanding)
    {
        return false;
    }

    if (pPed->physicalFlags.bSubmergedInWater)
    {
        return false;
    }

    auto pAnimAssoc = RpAnimBlendClumpGetFirstAssociation(pPed->m_pRwClump, ANIM_FLAG_PARTIAL);
    if (!pAnimAssoc)
    {
        return false;
    }

    int32 blockID = pAnimAssoc->m_pHierarchy->m_nAnimBlockId;
    if (_stricmp(CAnimManager::ms_aAnimBlocks[blockID].szName, "parachute") != 0)
    {
        while (true)
        {
            pAnimAssoc = RpAnimBlendGetNextAssociation(pAnimAssoc);
            if (!pAnimAssoc)
            {
                return false;
            }
        }
    }
    return true;
}

// 0x601230
void CPedIntelligence::SetTaskDuckSecondary(uint16 nLengthOfDuck) {
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pSecondaryTask = pTaskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);

    if (pSecondaryTask)
    {
        if (pSecondaryTask->GetTaskType() == TASK_SIMPLE_DUCK)
        {
            auto pDuckTask = (CTaskSimpleDuck*)pSecondaryTask;
            if (pDuckTask->m_nDuckControlType == DUCK_SCRIPT_CONTROLLED)
            {
                return;
            }
        }
    }

    auto pTaskSimpleDuck = (CTaskSimpleDuck*)CTask::operator new(40);
    if (pTaskSimpleDuck)
    {
        pTaskSimpleDuck->Constructor(DUCK_TASK_CONTROLLED, nLengthOfDuck, -1);
    }

    pTaskManager->SetTaskSecondary(pTaskSimpleDuck, TASK_SECONDARY_DUCK);

    CTask* pSecondaryAttackTask = pTaskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pSecondaryAttackTask && pSecondaryAttackTask->GetTaskType() == TASK_SIMPLE_USE_GUN)
    {
        auto pTaskUseGun = (CTaskSimpleUseGun*)pSecondaryAttackTask;
        pTaskUseGun->ClearAnim(m_pPed);
    }

    auto pDuckTask = (CTaskSimpleDuck*)pTaskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);
    pDuckTask->ProcessPed(m_pPed);
}

// 0x601390
void CPedIntelligence::ClearTaskDuckSecondary() {
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pSecondaryDuck = pTaskManager->GetTaskSecondary(1);
    if (pSecondaryDuck)
    {
        pSecondaryDuck->MakeAbortable(m_pPed, ABORT_PRIORITY_LEISURE, nullptr);
        CPlayerPedData * pPlayerData = m_pPed->m_pPlayerData;
        if (pPlayerData)
        {
            pPlayerData->m_fMoveBlendRatio = 0.0;
        }
        else
        {
            m_pPed->SetMoveState(PEDMOVE_STILL);
        }

        CTask* pTask = pTaskManager->GetTaskSecondary(0);
        if (pTask)
        {
            if (pTask->GetTaskType() == TASK_SIMPLE_USE_GUN)
            {
                if (pTaskManager->GetTaskSecondary(0))
                {
                    CTaskSimpleUseGun* pTaskUseGun = GetTaskUseGun();
                    pTaskUseGun->ClearAnim(m_pPed);
                }
            }
        }
    }
}

// 0x601420
void CPedIntelligence::ClearTasks(bool bClearPrimaryTasks, bool bClearSecondaryTasks) {
    if (bClearPrimaryTasks)
    {
        if (m_pPed->bInVehicle && m_pPed->m_pVehicle)
        {
            if (!m_eventGroup.HasScriptCommandOfTaskType(TASK_SIMPLE_CAR_DRIVE))
            {
                CTask* pDriveTask = nullptr;
                if (m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_DEFAULT]->GetTaskType() == TASK_SIMPLE_CAR_DRIVE)
                {
                    pDriveTask = static_cast<CTask*>(new CTaskSimpleCarDriveTimed(m_pPed->m_pVehicle, 0));
                }
                else
                {
                    auto pTaskSimpleCarDrive = (CTaskSimpleCarDrive*)CTask::operator new(96);
                    if (pTaskSimpleCarDrive)
                    {
                        pTaskSimpleCarDrive->Constructor(m_pPed->m_pVehicle, nullptr, false);
                    }
                    pDriveTask = static_cast<CTask*>(pTaskSimpleCarDrive);
                }
                CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, pDriveTask, false);
                m_eventGroup.Add(&eventScriptCommand, false);
            }
        }
        else if (!m_eventGroup.HasScriptCommandOfTaskType(TASK_SIMPLE_STAND_STILL))
        {
            auto pTaskSimpleStandStill = new CTaskSimpleStandStill(0, false, false, 8.0f);
            CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, pTaskSimpleStandStill, false);
            m_eventGroup.Add(&eventScriptCommand, false);
        }

        m_eventHandler.HandleEvents();
        m_TaskMgr.ManageTasks();
        CPedScriptedTaskRecord::Process();
    }

    if (bClearSecondaryTasks)
    {
        for (int32 secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
        {
            if (secondaryTaskIndex != TASK_SECONDARY_FACIAL_COMPLEX)
            {
                CTask* pSecondaryTask = m_TaskMgr.GetTaskSecondary(secondaryTaskIndex);
                if (pSecondaryTask)
                {
                    if (pSecondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_URGENT, nullptr))
                    {
                        m_TaskMgr.SetTaskSecondary(nullptr, secondaryTaskIndex);
                    }
                    else
                    {
                        pSecondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_LEISURE, nullptr);
                    }
                }
            }
        }
    }
}

// 0x601640
void CPedIntelligence::FlushImmediately(bool bSetPrimaryDefaultTask) {
    CTask* pPrimaryTask = m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_PRIMARY];
    CTaskComplex* pTaskComplexBeInGroup = nullptr;
    if (pPrimaryTask && pPrimaryTask->GetTaskType() == TASK_COMPLEX_BE_IN_GROUP)
    {
        pTaskComplexBeInGroup = (CTaskComplex*)pPrimaryTask->Clone();
    }

    CTaskSimpleHoldEntity* pTaskSimpleHoldEntity = nullptr;
    CTask* pSecondaryTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (pSecondaryTask && pSecondaryTask->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY)
    {
        pTaskSimpleHoldEntity = (CTaskSimpleHoldEntity*)pSecondaryTask;
    }

    int32 objectType = -1;
    bool bIsEntityVisible = false;
    CObject* pObjectToHold = nullptr;
    CTaskSimpleHoldEntity* pTaskSimpleHoldEntityCloned = nullptr;
    if (pTaskSimpleHoldEntity && pTaskSimpleHoldEntity->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY)
    {
        pObjectToHold = (CObject*)pTaskSimpleHoldEntity->m_pEntityToHold;
        if (pObjectToHold)
        {
            if (pObjectToHold->m_nType == ENTITY_TYPE_OBJECT)
            {
                objectType = pObjectToHold->m_nObjectType;
                bIsEntityVisible = pObjectToHold->m_bIsVisible;
            }
            pTaskSimpleHoldEntityCloned = (CTaskSimpleHoldEntity*)pTaskSimpleHoldEntity->Clone();
        }
    }

    CTaskComplexFacial* pTaskComplexFacialCloned = nullptr;
    CTask* pTaskComplexFacial = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_FACIAL_COMPLEX);
    if (pTaskComplexFacial && pTaskComplexFacial->GetTaskType() == TASK_COMPLEX_FACIAL)
    {
        pTaskComplexFacialCloned = static_cast<CTaskComplexFacial*>(pTaskComplexFacial->Clone());
    }

    m_eventGroup.Flush(true);
    m_eventHandler.FlushImmediately();
    m_TaskMgr.FlushImmediately();
    CPedScriptedTaskRecord::Process();
    if (pTaskSimpleHoldEntityCloned)
    {
        if (objectType != -1)
        {
            pObjectToHold->m_nObjectType = objectType;
            pObjectToHold->m_bIsVisible = bIsEntityVisible;
        }
        m_TaskMgr.SetTaskSecondary((CTaskComplex*)pTaskSimpleHoldEntityCloned, TASK_SECONDARY_PARTIAL_ANIM);
        pTaskSimpleHoldEntityCloned->ProcessPed(m_pPed);
    }

    if (pTaskComplexFacialCloned)
    {
        m_TaskMgr.SetTaskSecondary(pTaskComplexFacialCloned, TASK_SECONDARY_FACIAL_COMPLEX);
    }

    if (bSetPrimaryDefaultTask)
    {
        if (m_pPed->IsPlayer())
        {
            auto pTaskSimplePlayerOnFoot = (CTaskSimplePlayerOnFoot*)CTask::operator new(28);
            if (pTaskSimplePlayerOnFoot)
            {
                pTaskSimplePlayerOnFoot->Constructor();
                m_TaskMgr.SetTask(pTaskSimplePlayerOnFoot, TASK_PRIMARY_DEFAULT, 0);
                return;
            }
        }
        else
        {
            if (m_pPed->m_nCreatedBy != 2)
            {
                auto pTaskComplexWander = CTaskComplexWander::GetWanderTaskByPedType(m_pPed);
                m_TaskMgr.SetTask(pTaskComplexWander, TASK_PRIMARY_DEFAULT, 0);
                return;
            }

            auto pTaskSimpleStandStill = new CTaskSimpleStandStill(0, true, false, 8.0f);
            if (pTaskSimpleStandStill) {
                m_TaskMgr.SetTask(pTaskSimpleStandStill, TASK_PRIMARY_DEFAULT, 0);
                return;
            }
        }
        m_TaskMgr.SetTask(nullptr, TASK_PRIMARY_DEFAULT, 0);
        return;
    }
}

// 0x6018D0
C2dEffect* CPedIntelligence::GetEffectInUse() {
    return m_eventScanner.m_attractorScanner.m_pEffectInUse;
}

// 0x6018E0
void CPedIntelligence::SetEffectInUse(C2dEffect* effect) {
    m_eventScanner.m_attractorScanner.m_pEffectInUse = effect;
}

// 0x6018F0
void CPedIntelligence::ProcessAfterProcCol() {
    g_LoadMonitor.StartTimer(0);

    CTaskSimple* pActiveSimplestTask = (CTaskSimple*)m_TaskMgr.GetSimplestActiveTask();
    if (pActiveSimplestTask && pActiveSimplestTask->IsSimple())
    {
        bool bPositionSet = pActiveSimplestTask->SetPedPosition(m_pPed);
        if (!bPositionSet)
        {
            CTaskSimple* pSimplestTask = (CTaskSimple*)m_TaskMgr.GetSimplestTask(TASK_PRIMARY_DEFAULT);
            if (pSimplestTask && pSimplestTask->IsSimple())
            {
                bPositionSet = pSimplestTask->SetPedPosition(m_pPed);
            }
        }

        if (bPositionSet)
        {
            m_pPed->UpdateRW();
            m_pPed->UpdateRwFrame();
        }
    }

    m_pPed->bCalledPreRender = 0;
    g_LoadMonitor.EndTimer(0);
}

// 0x6019B0
void CPedIntelligence::ProcessAfterPreRender() {
    g_LoadMonitor.StartTimer(0);

    CTask* pSecondaryTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (pSecondaryTask && pSecondaryTask->IsSimple())
    {
        CTaskSimple* pSimpleTask = (CTaskSimple*)pSecondaryTask;
        if (pSimpleTask->SetPedPosition(m_pPed))
        {
            CTask* pSecondaryAttackTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
            if (pSecondaryAttackTask && pSecondaryAttackTask->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY)
            {
                CTaskSimpleHoldEntity* pTaskSimpleHoldEntity = (CTaskSimpleHoldEntity*)pSecondaryAttackTask;
                pTaskSimpleHoldEntity->SetPedPosition(m_pPed);
            }
        }
    }

    CTask* pSecondaryAttackTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pSecondaryAttackTask && pSecondaryAttackTask->GetTaskType() == TASK_SIMPLE_USE_GUN)
    {
        CTaskSimpleUseGun* pTaskUseGun = (CTaskSimpleUseGun*)pSecondaryAttackTask;
        pTaskUseGun->SetPedPosition(m_pPed);
    }

    CWeapon* pActiveWeapon = &m_pPed->m_aWeapons[m_pPed->m_nActiveWeaponSlot];
    if (pActiveWeapon->m_nType == WEAPON_MOLOTOV && pActiveWeapon->m_pFxSystem)
    {
        RpHAnimHierarchy* pRpAnimHierarchy = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);
        int32 animIDIndex = RpHAnimIDGetIndex(pRpAnimHierarchy, 24); // 24 = BONE_R_HAND?
        RwMatrix* pMatrixArray = RpHAnimHierarchyGetMatrixArray(pRpAnimHierarchy);

        RwV3d pointIn = { 0.05f, 0.05f,  0.14f };
        RwV3d pointOut;
        RwV3dTransformPoint(&pointOut, &pointIn, &pMatrixArray[animIDIndex]);

        RwMatrix* pRwMatrix = m_pPed->GetModellingMatrix();
        RwMatrix matrix;
        memcpy(&matrix, pRwMatrix, sizeof(matrix));
        matrix.pos = pointOut;
        RwMatrixUpdate(&matrix);
        pActiveWeapon->m_pFxSystem->SetMatrix(&matrix);
    }

    if (m_pPed->bInVehicle)
    {
        CVehicle* pVehicle = m_pPed->m_pVehicle;
        if (pVehicle && pVehicle->IsBike()) {
            CBike* pBike = (CBike*)pVehicle;
            pBike->FixHandsToBars(m_pPed);
        }
    }

    g_LoadMonitor.EndTimer(0);
}

// 0x601BB0
void CPedIntelligence::ProcessEventHandler() {
    m_eventHandler.HandleEvents();
}

// 0x601BC0
bool CPedIntelligence::IsFriendlyWith(CPed* pPed) {
    uint32 respect = m_pPed->m_acquaintance.m_nRespect;
    uint32 like = m_pPed->m_acquaintance.m_nLike;
    uint32 pedFlag = CPedType::GetPedFlag((ePedType)pPed->m_nPedType);
    return m_pPed->m_nPedType == pPed->m_nPedType || pedFlag & respect || pedFlag & like;
}

// 0x601C30
bool CPedIntelligence::IsThreatenedBy(CPed const& ped) {
    uint32 dislike = m_pPed->m_acquaintance.m_nDislike;
    uint32 hate = m_pPed->m_acquaintance.m_nHate;
    uint32 pedTypeFlag = CPedType::GetPedFlag((ePedType)ped.m_nPedType);
    return pedTypeFlag & dislike || pedTypeFlag & hate;
}

// 0x601C90
bool CPedIntelligence::Respects(CPed* pPed) {
    uint32 respect = m_pPed->m_acquaintance.m_nRespect;
    uint32 pedFlag = CPedType::GetPedFlag((ePedType)pPed->m_nPedType);
    return pedFlag & respect;
}

// 0x601CC0
bool CPedIntelligence::IsInACarOrEnteringOne() {
    auto pTaskComplexEnterCar = static_cast<CTaskComplexEnterCar*>(m_TaskMgr.FindActiveTaskByType(TASK_COMPLEX_ENTER_CAR_AS_DRIVER));
    if (pTaskComplexEnterCar)
    {
        return pTaskComplexEnterCar->m_pTargetVehicle;
    }

    pTaskComplexEnterCar = static_cast<CTaskComplexEnterCar*>(m_TaskMgr.FindActiveTaskByType(TASK_COMPLEX_ENTER_CAR_AS_PASSENGER));
    if (pTaskComplexEnterCar)
    {
        return pTaskComplexEnterCar->m_pTargetVehicle;
    }

    auto pTakSimpleCarDrive = static_cast<CTaskSimpleCarDrive*>(m_TaskMgr.FindActiveTaskByType(TASK_SIMPLE_CAR_DRIVE));
    if (pTakSimpleCarDrive)
    {
        return pTakSimpleCarDrive->m_pVehicle;
    }
    return false;
}

// 0x601D10
// (CPed const& ped1,CPed const& ped2)
bool CPedIntelligence::AreFriends(CPed* ped1, CPed* ped2) {
    return ped1->m_pIntelligence->IsFriendlyWith(ped2) || ped2->m_pIntelligence->IsFriendlyWith(ped1);
}

// unused
// 0x601D50
bool CPedIntelligence::IsPedGoingSomewhereOnFoot() {
    return plugin::CallMethodAndReturn<bool, 0x601D50, CPedIntelligence*>(this);
}

// 0x601D70
int32 CPedIntelligence::GetMoveStateFromGoToTask() {
    auto pTask = (CTaskSimpleGoTo*)m_TaskMgr.GetSimplestActiveTask();
    if (pTask && CTask::IsGoToTask(pTask))
    {
        return pTask->m_moveState;
    }
    return PEDMOVE_STILL;
}

// 0x601DA0
void CPedIntelligence::FlushIntelligence() {
    m_TaskMgr.Flush();
    m_eventHandler.m_physicalResponseTask = nullptr;
    m_eventHandler.m_eventResponseTask = nullptr;
    m_eventHandler.m_attackTask = nullptr;
    m_eventHandler.m_sayTask = nullptr;
    m_eventHandler.m_partialAnimTask = nullptr;
    m_eventHandler.m_history.ClearAllEvents();
    m_eventGroup.Flush(false);
    m_vehicleScanner.Clear();
    m_entityScanner.Clear();
    m_eventScanner.m_attractorScanner.Clear();
}

// 0x601E00
bool CPedIntelligence::TestForStealthKill(CPed* pTarget, bool bFullTest) {
    if (pTarget->bInVehicle)
        return false;

    CVector bonePosition;
    pTarget->GetBonePosition(bonePosition, BONE_HEAD, false);
    if (pTarget->bIsDucking || pTarget->m_fHealth < 1.0f)
        return false;

    if (bonePosition.z < pTarget->GetPosition().z)
        return false;

    if (bFullTest)
        return true;

    if (pTarget->m_nMoveState >= PEDMOVE_RUN)
        return false;

    CVector distance = pTarget->GetPosition() - m_pPed->GetPosition();
    if (CPedIntelligence::STEALTH_KILL_RANGE * CPedIntelligence::STEALTH_KILL_RANGE < distance.SquaredMagnitude())
        return false;

    if (DotProduct(distance, pTarget->GetForward()) <= 0.0f)
        return false;

    CTask* pActiveTask = pTarget->GetTaskManager().GetActiveTask();
    if (pActiveTask)
    {
        if (pActiveTask->GetTaskType() == TASK_COMPLEX_KILL_PED_ON_FOOT)
        {
            auto pTaskComplexKillPedOnFoot = (CTaskComplexKillPedOnFoot*)pActiveTask;
            if (pTaskComplexKillPedOnFoot->m_target == m_pPed)
            {
                return false;
            }
        }
    }

    CEvent* pCurrentEvent = pTarget->GetEventHandlerHistory().GetCurrentEvent();
    if (pCurrentEvent && pCurrentEvent->GetSourceEntity() == m_pPed)
    {
        int32 acquaintancesID4 = pTarget->m_acquaintance.GetAcquaintances(4);
        int32 acquaintancesID3 = pTarget->m_acquaintance.GetAcquaintances(3);
        uint32 pedFlag = CPedType::GetPedFlag(m_pPed->m_nPedType);

        bool bAcquaintancesFlagSet = (
            (acquaintancesID4 && (pedFlag & acquaintancesID4)) ||
            (acquaintancesID3 && (pedFlag & acquaintancesID3))
        );
        CPedGroup* pPedGroup = CPedGroups::GetPedsGroup(pTarget);
        if (bAcquaintancesFlagSet && pPedGroup) {
            CEventGroupEvent* eventGroupEvent = pPedGroup->GetIntelligence().m_oldEventGroupEvent;
            if (eventGroupEvent && eventGroupEvent->GetSourceEntity() == m_pPed && bAcquaintancesFlagSet)
                return false;
        }
    }
    return true;
}

// 0x602050
void CPedIntelligence::RecordEventForScript(int32 EventID, int32 EventPriority) {
    if (EventID != EVENT_SCRIPT_COMMAND && (!EventID || EventPriority > m_nEventPriority))
    {
        m_nEventId = EventID;
        m_nEventPriority = EventPriority;
    }
}

// Unused
// 0x602080
bool CPedIntelligence::HasInterestingEntites() {
    return plugin::CallMethodAndReturn<bool, 0x602080, CPedIntelligence*>(this);
}

// 0x6020A0
bool CPedIntelligence::IsInterestingEntity(CEntity* pEntity) {
    for (uint32 i = 0; i < 3; i++)
    {
        if (m_apInterestingEntities[i] == pEntity)
        {
            return true;
        }
    }
    return false;
}

// 0x6020D0
void CPedIntelligence::LookAtInterestingEntities() {
    if (!m_pPed->bDontAcceptIKLookAts)
    {
        bool bInterestingEntityExists = false;
        for (uint32 i = 0; i < 3; i++)
        {
            if (m_apInterestingEntities[i])
            {
                bInterestingEntityExists = true;
                break;
            }
        }

        if (!bInterestingEntityExists)
        {
            return;
        }

        if (!g_ikChainMan->IsLooking(m_pPed) && m_pPed->GetIsOnScreen() && CGeneral::GetRandomNumberInRange(0, 100) == 50)
        {
            CEntity* outEntities[1024];
            int16 outCount = -1;
            CWorld::FindObjectsInRange(m_pPed->GetPosition(), 15.0f, false, &outCount, 1024, outEntities, false, true, true, true, false);
            if (outCount > 0)
            {
                int32 interestingEntityCount = 0;
                for (int32 i = 0; i < outCount; i++)
                {
                    CEntity* pEntity = outEntities[i];
                    if (IsInterestingEntity(pEntity))
                    {
                        outEntities[interestingEntityCount] = pEntity;
                        interestingEntityCount++;
                    }
                }
                if (interestingEntityCount)
                {
                    uint32 randomInterestingEntityIndex = CGeneral::GetRandomNumberInRange(0, interestingEntityCount);
                    uint32 randomTime = CGeneral::GetRandomNumberInRange(3000, 5000);
                    CPed* pInterestingEntity = (CPed*)outEntities[randomInterestingEntityIndex];

                    RwV3d position = { 0.0f, 0.0f, 0.0f };
                    g_ikChainMan->LookAt(
                        "InterestingEntities", m_pPed, pInterestingEntity, randomTime, BONE_UNKNOWN,
                        &position, false, 0.25f, 500, 3, false
                    );
                }
            }
        }
    }
}

// unused
// 0x602320
void CPedIntelligence::RemoveAllInterestingEntities() {
    plugin::CallMethod<0x602320, CPedIntelligence*>(this);
}

// 0x602350
bool CPedIntelligence::IsPedGoingForCarDoor() {
    CTaskSimple* pActiveSimplestTask = (CTaskSimple*)m_TaskMgr.GetSimplestActiveTask();
    if (pActiveSimplestTask)
    {
        if (pActiveSimplestTask->GetTaskType() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL)
        {
            return true;
        }

        CTask* pParentTask = pActiveSimplestTask->m_pParentTask;
        if (pParentTask)
        {
            if (pParentTask->GetTaskType() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL)
            {
                return true;
            }

            CTask* pGrandParentTask = pParentTask->m_pParentTask;
            if (pGrandParentTask && pGrandParentTask->GetTaskType() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL)
            {
                return true;
            }
        }

    }
    return false;
}

// (CEntity const* pEntity,bool arg2)
// 0x605550
float CPedIntelligence::CanSeeEntityWithLights(CEntity* pEntity, int32 unUsed) {
    if (pEntity->m_nType != ENTITY_TYPE_PED)
        return LIGHT_AI_LEVEL_MAX;

    CPed* pPedEntity = static_cast<CPed*>(pEntity);
    if (!pPedEntity->IsPlayer())
        return LIGHT_AI_LEVEL_MAX;

    float fLightingTotal = pPedEntity->GetLightingTotal();
    if (fLightingTotal > LIGHT_AI_LEVEL_MAX)
        return LIGHT_AI_LEVEL_MAX;

    const float fLightLevelSquared = LIGHT_AI_LEVEL_MAX * LIGHT_AI_LEVEL_MAX;
    float fMagnitude = (pPedEntity->GetPosition() - m_pPed->GetPosition()).Magnitude() - 0.7f;
    float result = fLightingTotal * fLightingTotal - fMagnitude / 30.0f * fLightLevelSquared;
    if (result <= 0.0f) {
        result = result * result - fMagnitude / 50.0f * fLightLevelSquared;
        if (result <= 0.0f)
            result = 0.0f;
        else
            result *= -1.0f;
    }
    return result;
}

// 0x605650
void CPedIntelligence::ProcessStaticCounter() {
    CTask* pActiveSimplestTask = m_TaskMgr.GetSimplestActiveTask();
    if (!pActiveSimplestTask || !CTask::IsGoToTask(pActiveSimplestTask))
    {
        if (m_StaticCounter == -2)
        {
            m_StaticCounter = 4;
        }
        else
        {
            m_StaticCounter++;
        }
        m_AnotherStaticCounter = 0;
        return;
    }

    auto pGotoTask = (CTaskSimpleGoTo*)pActiveSimplestTask;
    int32 moveState = pGotoTask->m_moveState;
    if (moveState != PEDMOVE_WALK && moveState != PEDMOVE_RUN && moveState != PEDMOVE_SPRINT)
    {
        if (m_StaticCounter == -2)
        {
            m_StaticCounter = 4;
        }
        else
        {
            m_StaticCounter++;
        }
        m_AnotherStaticCounter = 0;
        return;
    }

    if (m_pPed->m_pDamageEntity)
    {
        if (m_StaticCounter > 4u)
        {
            m_vecLastPedPosDuringDamageEntity = m_pPed->GetPosition();
        }
        m_StaticCounter = 0;
    }
    else
    {
        if (m_StaticCounter == -2)
        {
            m_StaticCounter = 4;
        }
        else
        {
            m_StaticCounter++;
        }
    }

    if (m_StaticCounter > 4u)
    {
        m_AnotherStaticCounter = 0;
        return;
    }
    if ((m_pPed->GetPosition() - m_vecLastPedPosDuringDamageEntity).SquaredMagnitude() < 0.0625f)
    {
        m_AnotherStaticCounter++;
    }
    else
    {
        m_AnotherStaticCounter = 0;
        m_vecLastPedPosDuringDamageEntity = m_pPed->GetPosition();
    }
}

// 0x6073A0
void CPedIntelligence::ProcessFirst() {
    g_LoadMonitor.StartTimer(0);
    ProcessStaticCounter();
    if (!m_pedStuckChecker.TestPedStuck(m_pPed, &m_eventGroup))
    {
        // Yes, this is very awkward. field_260 is just a boolean, and we are passing its address as a class instance,.
        // ScanForCollisionEvents might set it to false. The calling convention of the function was probably __cdecl,
        // but the compiler messed up and used ecx for it. The code works though. Just remember that 
        // CPedIntelligence::field_260 is just a boolean, not a class instance. Let's keep it this way for now.
        CCollisionEventScanner* ppCollisionEventScanner = (CCollisionEventScanner*)& field_260;
        ppCollisionEventScanner->ScanForCollisionEvents(m_pPed, &m_eventGroup);
    }
    if (m_pPed->m_fDamageIntensity > 0.0f)
    {
        CEntity* pDamageEntity = m_pPed->m_pDamageEntity;
        if (pDamageEntity && pDamageEntity->m_nType != ENTITY_TYPE_PED) {
            if (DotProduct(m_pPed->m_vecLastCollisionImpactVelocity, m_pPed->GetForward()) < -0.5f)
                m_pPed->bPedHitWallLastFrame = 1;
        }
    }

    if (m_pPed->bInVehicle)
    {
        CVehicle* pVehicle = m_pPed->m_pVehicle;
        if (pVehicle && pVehicle->IsBike()) {
            CBike* pBike = static_cast<CBike*>(pVehicle);
            pBike->m_bPedLeftHandFixed = false;
            pBike->m_bPedRightHandFixed = false;
        }
    }
    m_pPed->bMoveAnimSpeedHasBeenSetByTask = false;
    g_LoadMonitor.EndTimer(0);
}

// 0x608260
void CPedIntelligence::Process() {
    g_LoadMonitor.StartTimer(0);

    m_vehicleScanner.ScanForVehiclesInRange(m_pPed);

    if (m_pPed->IsAlive())
    {
        m_entityScanner.ScanForEntitiesInRange(1, m_pPed);
    }

    m_eventScanner.ScanForEvents(m_pPed);
    m_eventHandler.HandleEvents();
    m_TaskMgr.ManageTasks();

    auto pRecorder = CPlayerRelationshipRecorder::GetPlayerRelationshipRecorder();
    pRecorder->RecordRelationshipWithPlayer(m_pPed);
    LookAtInterestingEntities();

    g_LoadMonitor.EndTimer(0);
}

// 0x4B85B0
CTask* CPedIntelligence::GetActivePrimaryTask()
{
    CTask* pTask = m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_PHYSICAL_RESPONSE];
    if (!pTask)
    {
        pTask = m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_TEMP];
        if (!pTask)
        {
            pTask = m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_EVENT_RESPONSE_NONTEMP];
        }
    }
    return pTask;
}

// 0x4ABEA0
float CPedIntelligence::GetPedFOVRange()
{
    return std::max(m_fHearingRange, m_fSeeingRange);
}

// 0x6074A0
void* CPedIntelligence::operator new(uint32 size) {
    return CPools::ms_pPedIntelligencePool->New();
}

// 0x6074E0
void CPedIntelligence::operator delete(void* object) {
    plugin::Call<0x6074E0, void*>(object);
}
