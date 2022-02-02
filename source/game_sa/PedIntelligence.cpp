/*
    Plugin-SDK (Grand Theft Auto San Andreas) file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "PedIntelligence.h"

#include "IKChainManager_c.h"
#include "PedType.h"
#include "TaskSimpleCarDriveTimed.h"
#include "TaskSimpleStandStill.h"
#include "TaskComplexFacial.h"
#include "TaskComplexEnterCar.h"
#include "TaskSimpleGoTo.h"
#include "TaskComplexKillPedOnFoot.h"
#include "TaskSimplePlayerOnFoot.h"
#include "TaskComplexWander.h"
#include "TaskSimpleUseGun.h"
#include "TaskSimpleHoldEntity.h"
#include "TaskSimpleDuck.h"
#include "TaskSimpleClimb.h"
#include "CollisionEventScanner.h"

float& CPedIntelligence::STEALTH_KILL_RANGE = *reinterpret_cast<float*>(0x8D2398); // 2.5f
float& CPedIntelligence::LIGHT_AI_LEVEL_MAX = *reinterpret_cast<float*>(0x8D2380); // 0.3f
float& CPedIntelligence::flt_8D2384 = *reinterpret_cast<float*>(0x8D2384); // 30.0f
float& CPedIntelligence::flt_8D2388 = *reinterpret_cast<float*>(0x8D2388); // 50.0f

void CPedIntelligence::InjectHooks()
{
    RH_ScopedClass(CPedIntelligence);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(GetPedEntities, 0x4893E0);
    RH_ScopedInstall(SetPedDecisionMakerType, 0x600B50);
    RH_ScopedInstall(SetPedDecisionMakerTypeInGroup, 0x600BB0);
    RH_ScopedInstall(RestorePedDecisionMakerType, 0x600BC0);
    RH_ScopedInstall(SetHearingRange, 0x600BE0);
    RH_ScopedInstall(SetSeeingRange, 0x600BF0);
    RH_ScopedInstall(IsInSeeingRange, 0x600C60);
    RH_ScopedInstall(FindRespectedFriendInInformRange, 0x600CF0);
    RH_ScopedInstall(IsRespondingToEvent, 0x600DB0);
    RH_ScopedInstall(AddTaskPhysResponse, 0x600DC0);
    RH_ScopedInstall(AddTaskEventResponseTemp, 0x600DE0);
    RH_ScopedInstall(AddTaskEventResponseNonTemp, 0x600E00);
    RH_ScopedInstall(AddTaskPrimaryMaybeInGroup, 0x600E20);
    RH_ScopedInstall(FindTaskByType, 0x600EE0);
    RH_ScopedInstall(GetTaskFighting, 0x600F30);
    RH_ScopedInstall(GetTaskUseGun, 0x600F70);
    RH_ScopedInstall(GetTaskThrow, 0x600FB0);
    RH_ScopedInstall(GetTaskHold, 0x600FF0);
    RH_ScopedInstall(GetTaskSwim, 0x601070);
    RH_ScopedInstall(GetTaskDuck, 0x6010A0);
    RH_ScopedInstall(GetTaskJetPack, 0x601110);
    RH_ScopedInstall(GetTaskInAir, 0x601150);
    RH_ScopedInstall(GetTaskClimb, 0x601180);
    RH_ScopedInstall(GetUsingParachute, 0x6011B0);
    RH_ScopedInstall(SetTaskDuckSecondary, 0x601230);
    RH_ScopedInstall(ClearTaskDuckSecondary, 0x601390);
    RH_ScopedInstall(ClearTasks, 0x601420);
    RH_ScopedInstall(FlushImmediately, 0x601640);
    RH_ScopedInstall(GetEffectInUse, 0x6018D0);
    RH_ScopedInstall(SetEffectInUse, 0x6018E0);
    RH_ScopedInstall(ProcessAfterProcCol, 0x6018F0);
    RH_ScopedInstall(ProcessAfterPreRender, 0x6019B0);
    RH_ScopedInstall(ProcessEventHandler, 0x601BB0);
    RH_ScopedInstall(IsFriendlyWith, 0x601BC0);
    RH_ScopedInstall(IsThreatenedBy, 0x601C30);
    RH_ScopedInstall(Respects, 0x601C90);
    RH_ScopedInstall(IsInACarOrEnteringOne, 0x601CC0);
    RH_ScopedInstall(AreFriends, 0x601D10);
    RH_ScopedInstall(GetMoveStateFromGoToTask, 0x601D70);
    RH_ScopedInstall(FlushIntelligence, 0x601DA0);
    RH_ScopedInstall(TestForStealthKill, 0x601E00);
    RH_ScopedInstall(RecordEventForScript, 0x602050);
    RH_ScopedInstall(IsInterestingEntity, 0x6020A0);
    RH_ScopedInstall(LookAtInterestingEntities, 0x6020D0);
    RH_ScopedInstall(IsPedGoingForCarDoor, 0x602350);
    RH_ScopedInstall(CanSeeEntityWithLights, 0x605550);
    RH_ScopedInstall(ProcessStaticCounter, 0x605650);
    RH_ScopedInstall(ProcessFirst, 0x6073A0);
    RH_ScopedInstall(Process, 0x608260);
    RH_ScopedInstall(GetActivePrimaryTask, 0x4B85B0);
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
    auto respect = m_pPed->m_acquaintance.GetAcquaintances(0); // todo: m_nRespect
    for (uint32 pedScanIndex = 0; pedScanIndex < m_nDmNumPedsToScan; pedScanIndex++) {
        CPed* pedEntity = (CPed*)m_entityScanner.m_apEntities[pedScanIndex];
        if (pedEntity) {
            if (CPedType::GetPedFlag(pedEntity->m_nPedType) & respect) {
                CVector distance = m_pPed->GetPosition() - pedEntity->GetPosition();
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
void CPedIntelligence::AddTaskPhysResponse(CTask* task, int32 unUsed) {
    m_TaskMgr.SetTask(task, TASK_PRIMARY_PHYSICAL_RESPONSE, unUsed);
}

// (CTask *task, bool arg2)
// 0x600DE0
void CPedIntelligence::AddTaskEventResponseTemp(CTask* task, int32 unUsed) {
    m_TaskMgr.SetTask(task, TASK_PRIMARY_EVENT_RESPONSE_TEMP, unUsed);
}

// (CTask *task,bool arg2)
// 0x600E00
void CPedIntelligence::AddTaskEventResponseNonTemp(CTask* task, int32 unUsed) {
    m_TaskMgr.SetTask(task, TASK_PRIMARY_EVENT_RESPONSE_NONTEMP, unUsed);
}

// 0x600E20
void CPedIntelligence::AddTaskPrimaryMaybeInGroup(CTask* task, bool bAffectsPed) {
    CPedGroup* pegGroup = CPedGroups::GetPedsGroup(m_pPed);
    if (m_pPed->IsPlayer() || !pegGroup)
    {
        CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, task, bAffectsPed);
        m_eventGroup.Add(&eventScriptCommand, false);
    }
    else
    {
        pegGroup->m_groupIntelligence.SetScriptCommandTask(m_pPed, task);
        delete task;
    }
}

// 0x600EE0
CTask* CPedIntelligence::FindTaskByType(int32 taskId) {
    CTaskManager* taskManager = &m_TaskMgr;
    CTask* result = taskManager->FindTaskByType(TASK_PRIMARY_DEFAULT, taskId);
    if (result)
        return result;

    result = taskManager->FindTaskByType(TASK_PRIMARY_PRIMARY, taskId);
    if (result)
        return result;

    result = taskManager->FindTaskByType(TASK_PRIMARY_EVENT_RESPONSE_TEMP, taskId);
    if (result)
        return result;

    return taskManager->FindTaskByType(TASK_PRIMARY_EVENT_RESPONSE_NONTEMP, taskId);
}

// 0x600F30
CTaskSimpleFight* CPedIntelligence::GetTaskFighting() {
    CTaskManager* taskManager = &m_TaskMgr;
    CTask* secondaryTask = taskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (secondaryTask && secondaryTask->GetTaskType() == TASK_SIMPLE_FIGHT) {
        return (CTaskSimpleFight*)secondaryTask;
    }
    return nullptr;
}

// 0x600F70
CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun() {
    CTask* task = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (task && task->GetTaskType() == TASK_SIMPLE_USE_GUN) {
        return (CTaskSimpleUseGun*)task;
    }
    return nullptr;
}

// 0x600FB0
CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow() {
    CTask* task = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (task && task->GetTaskType() == TASK_SIMPLE_THROW) {
        return (CTaskSimpleThrowProjectile*)task;
    }
    return nullptr;
}

// 0x600FF0
CTask* CPedIntelligence::GetTaskHold(bool bIgnoreCheckingForSimplestActiveTask) {
    CTaskManager* taskManager = &m_TaskMgr;
    CTask* secondaryTask = taskManager->GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (secondaryTask) {
        if (secondaryTask->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY) {
            return secondaryTask;
        }
    }

    if (bIgnoreCheckingForSimplestActiveTask) {
        return nullptr;
    }

    CTask* activeSimplestTask = taskManager->GetSimplestActiveTask();
    if (!activeSimplestTask
        || activeSimplestTask->GetTaskType() != TASK_SIMPLE_PICKUP_ENTITY
        && activeSimplestTask->GetTaskType() != TASK_SIMPLE_PUTDOWN_ENTITY)
    {
        return nullptr;
    }
    return activeSimplestTask;
}

// 0x601070
CTaskSimpleSwim* CPedIntelligence::GetTaskSwim() {
    CTask* task = m_TaskMgr.GetSimplestActiveTask();
    if (task && task->GetTaskType() == TASK_SIMPLE_SWIM) {
        return (CTaskSimpleSwim*)task;
    }
    return nullptr;
}

// 0x6010A0
CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool bIgnoreCheckingForSimplestActiveTask) {
    CTaskManager* taskManager = &m_TaskMgr;
    auto* secondaryTask = (CTask*)taskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);
    if (secondaryTask && secondaryTask->GetTaskType() == TASK_SIMPLE_DUCK)
    {
        return (CTaskSimpleDuck*)secondaryTask;
    }

    if (bIgnoreCheckingForSimplestActiveTask)
    {
        return nullptr;
    }

    CTask* activeSimplestTask = taskManager->GetSimplestActiveTask();
    if (!activeSimplestTask || activeSimplestTask->GetTaskType() != TASK_SIMPLE_DUCK)
    {
        return nullptr;
    }
    return (CTaskSimpleDuck*)activeSimplestTask;
}

// 0x601110
CTaskSimpleJetPack* CPedIntelligence::GetTaskJetPack() {
    if (m_pPed->IsPlayer()) {
        CTask* task = m_TaskMgr.GetSimplestActiveTask();
        if (task && task->GetTaskType() == TASK_SIMPLE_JETPACK) {
            return (CTaskSimpleJetPack*)task;
        }
    }
    return nullptr;
}

// 0x601150
CTaskSimpleInAir* CPedIntelligence::GetTaskInAir() {
    CTask* task = m_TaskMgr.GetSimplestActiveTask();
    if (task && task->GetTaskType() == TASK_SIMPLE_IN_AIR) {
        return (CTaskSimpleInAir*)task;
    }
    return nullptr;
}

// 0x601180
CTaskSimpleClimb* CPedIntelligence::GetTaskClimb() {
    auto task = (CTaskSimpleClimb*)m_TaskMgr.GetSimplestActiveTask();
    if (task && task->GetTaskType() == TASK_SIMPLE_CLIMB) {
        return task;
    }
    return nullptr;
}

// 0x6011B0
bool CPedIntelligence::GetUsingParachute() {
    CWeapon* activeWeapon = &m_pPed->GetActiveWeapon();
    if (activeWeapon->m_nType != WEAPON_PARACHUTE) {
        return false;
    }

    if (m_pPed->bIsStanding) {
        return false;
    }

    if (m_pPed->physicalFlags.bSubmergedInWater) {
        return false;
    }

    auto animAssoc = RpAnimBlendClumpGetFirstAssociation(m_pPed->m_pRwClump, ANIM_FLAG_PARTIAL);
    if (!animAssoc) {
        return false;
    }

    int32 blockID = animAssoc->m_pHierarchy->m_nAnimBlockId;
    if (_stricmp(CAnimManager::ms_aAnimBlocks[blockID].szName, "parachute") != 0) {
        while (true) {
            animAssoc = RpAnimBlendGetNextAssociation(animAssoc);
            if (!animAssoc) {
                return false;
            }
        }
    }
    return true;
}

// 0x601230
void CPedIntelligence::SetTaskDuckSecondary(uint16 nLengthOfDuck) {
    CTaskManager* taskManager = &m_TaskMgr;
    CTask* secondaryTask = taskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);

    if (secondaryTask) {
        if (secondaryTask->GetTaskType() == TASK_SIMPLE_DUCK) {
            auto duckTask = (CTaskSimpleDuck*)secondaryTask;
            if (duckTask->m_nDuckControlType == DUCK_SCRIPT_CONTROLLED) {
                return;
            }
        }
    }

    auto taskSimpleDuck = (CTaskSimpleDuck*)CTask::operator new(40);
    if (taskSimpleDuck)
    {
        taskSimpleDuck->Constructor(DUCK_TASK_CONTROLLED, nLengthOfDuck, -1);
    }
    taskManager->SetTaskSecondary(taskSimpleDuck, TASK_SECONDARY_DUCK);

    CTask* secondaryAttackTask = taskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (secondaryAttackTask && secondaryAttackTask->GetTaskType() == TASK_SIMPLE_USE_GUN)
    {
        auto taskUseGun = (CTaskSimpleUseGun*)secondaryAttackTask;
        taskUseGun->ClearAnim(m_pPed);
    }

    auto duckTask = (CTaskSimpleDuck*)taskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);
    duckTask->ProcessPed(m_pPed);
}

// 0x601390
void CPedIntelligence::ClearTaskDuckSecondary() {
    CTaskManager* taskManager = &m_TaskMgr;
    CTask* secondaryDuck = taskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);
    if (!secondaryDuck)
        return;

    secondaryDuck->MakeAbortable(m_pPed, ABORT_PRIORITY_LEISURE, nullptr);
    CPlayerPedData* playerData = m_pPed->m_pPlayerData;
    if (playerData) {
        playerData->m_fMoveBlendRatio = 0.0f;
    } else {
        m_pPed->SetMoveState(PEDMOVE_STILL);
    }

    if (CTask* task = taskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK)) {
        if (task->GetTaskType() == TASK_SIMPLE_USE_GUN) {
            if (taskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK)) {
                CTaskSimpleUseGun* taskUseGun = GetTaskUseGun();
                taskUseGun->ClearAnim(m_pPed);
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
                CTask* driveTask = nullptr;
                if (m_TaskMgr.GetTaskPrimary(TASK_PRIMARY_DEFAULT)->GetTaskType() == TASK_SIMPLE_CAR_DRIVE)
                {
                    driveTask = static_cast<CTask*>(new CTaskSimpleCarDriveTimed(m_pPed->m_pVehicle, 0));
                }
                else
                {
                    driveTask = new CTaskSimpleCarDrive(m_pPed->m_pVehicle, nullptr, false);
                }
                CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, driveTask, false);
                m_eventGroup.Add(&eventScriptCommand, false);
            }
        }
        else if (!m_eventGroup.HasScriptCommandOfTaskType(TASK_SIMPLE_STAND_STILL))
        {
            auto taskSimpleStandStill = new CTaskSimpleStandStill(0, false, false, 8.0f);
            CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, taskSimpleStandStill, false);
            m_eventGroup.Add(&eventScriptCommand, false);
        }

        m_eventHandler.HandleEvents();
        m_TaskMgr.ManageTasks();
        CPedScriptedTaskRecord::Process();
    }

    if (!bClearSecondaryTasks)
        return;

    for (int32 secondaryTaskIndex = 0; secondaryTaskIndex < TASK_SECONDARY_MAX; secondaryTaskIndex++) {
        if (secondaryTaskIndex == TASK_SECONDARY_FACIAL_COMPLEX)
            continue;

        CTask* secondaryTask = m_TaskMgr.GetTaskSecondary(secondaryTaskIndex);
        if (secondaryTask) {
            if (secondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_URGENT, nullptr)) {
                m_TaskMgr.SetTaskSecondary(nullptr, secondaryTaskIndex);
            } else {
                secondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_LEISURE, nullptr);
            }
        }
    }
}

// 0x601640
void CPedIntelligence::FlushImmediately(bool bSetPrimaryDefaultTask) {
    CTask* primaryTask = m_TaskMgr.GetTaskPrimary(TASK_PRIMARY_PRIMARY);
    CTaskComplex* pTaskComplexBeInGroup = nullptr;
    if (primaryTask && primaryTask->GetTaskType() == TASK_COMPLEX_BE_IN_GROUP) {
        pTaskComplexBeInGroup = (CTaskComplex*)primaryTask->Clone();
    }

    CTaskSimpleHoldEntity* taskSimpleHoldEntity = nullptr;
    CTask* secondaryTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (secondaryTask && secondaryTask->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY) {
        taskSimpleHoldEntity = (CTaskSimpleHoldEntity*)secondaryTask;
    }

    int32 objectType = -1;
    bool bIsEntityVisible = false;
    CObject* objectToHold = nullptr;
    CTaskSimpleHoldEntity* taskSimpleHoldEntityCloned = nullptr;
    if (taskSimpleHoldEntity && taskSimpleHoldEntity->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY) {
        objectToHold = (CObject*)taskSimpleHoldEntity->m_pEntityToHold;
        if (objectToHold) {
            if (objectToHold->IsObject()) {
                objectType = objectToHold->m_nObjectType;
                bIsEntityVisible = objectToHold->m_bIsVisible;
            }
            taskSimpleHoldEntityCloned = (CTaskSimpleHoldEntity*)taskSimpleHoldEntity->Clone();
        }
    }

    CTaskComplexFacial* taskComplexFacialCloned = nullptr;
    CTask* taskComplexFacial = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_FACIAL_COMPLEX);
    if (taskComplexFacial && taskComplexFacial->GetTaskType() == TASK_COMPLEX_FACIAL) {
        taskComplexFacialCloned = static_cast<CTaskComplexFacial*>(taskComplexFacial->Clone());
    }

    m_eventGroup.Flush(true);
    m_eventHandler.FlushImmediately();
    m_TaskMgr.FlushImmediately();
    CPedScriptedTaskRecord::Process();
    if (pTaskComplexBeInGroup) {
        auto pPedGroup = CPedGroups::GetPedsGroup(m_pPed);
        if (!pPedGroup || m_pPed->IsPlayer()) {
            delete pTaskComplexBeInGroup;
        }
        else {
            pPedGroup->m_groupIntelligence.ComputeDefaultTasks(m_pPed);
            m_TaskMgr.SetTask(pTaskComplexBeInGroup, 3, false);
        }
    }

    if (taskSimpleHoldEntityCloned) {
        if (objectType != -1) {
            objectToHold->m_nObjectType = objectType;
            objectToHold->m_bIsVisible = bIsEntityVisible;
        }
        m_TaskMgr.SetTaskSecondary((CTaskComplex*)taskSimpleHoldEntityCloned, TASK_SECONDARY_PARTIAL_ANIM);
        taskSimpleHoldEntityCloned->ProcessPed(m_pPed);
    }

    if (taskComplexFacialCloned) {
        m_TaskMgr.SetTaskSecondary(taskComplexFacialCloned, TASK_SECONDARY_FACIAL_COMPLEX);
    }

    if (bSetPrimaryDefaultTask) {
        if (m_pPed->IsPlayer()) {
            auto taskSimplePlayerOnFoot = new CTaskSimplePlayerOnFoot();
            m_TaskMgr.SetTask(taskSimplePlayerOnFoot, TASK_PRIMARY_DEFAULT, false);
            return;
        }
        else {
            if (m_pPed->m_nCreatedBy != PED_MISSION) {
                auto taskComplexWander = CTaskComplexWander::GetWanderTaskByPedType(m_pPed);
                m_TaskMgr.SetTask(taskComplexWander, TASK_PRIMARY_DEFAULT, false);
                return;
            }

            auto taskSimpleStandStill = new CTaskSimpleStandStill(0, true, false, 8.0f);
            m_TaskMgr.SetTask(taskSimpleStandStill, TASK_PRIMARY_DEFAULT, false);
            return;
        }
        m_TaskMgr.SetTask(nullptr, TASK_PRIMARY_DEFAULT, false);
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

    auto* activeSimplestTask = (CTaskSimple*)m_TaskMgr.GetSimplestActiveTask();
    if (activeSimplestTask && activeSimplestTask->IsSimple()) {
        bool bPositionSet = activeSimplestTask->SetPedPosition(m_pPed);
        if (!bPositionSet) {
            auto* simplestTask = (CTaskSimple*)m_TaskMgr.GetSimplestTask(TASK_PRIMARY_DEFAULT);
            if (simplestTask && simplestTask->IsSimple()) {
                bPositionSet = simplestTask->SetPedPosition(m_pPed);
            }
        }

        if (bPositionSet) {
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

    CTask* secondaryTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (secondaryTask && secondaryTask->IsSimple())
    {
        auto* simpleTask = (CTaskSimple*)secondaryTask;
        if (simpleTask->SetPedPosition(m_pPed))
        {
            CTask* secondaryAttackTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
            if (secondaryAttackTask && secondaryAttackTask->GetTaskType() == TASK_SIMPLE_HOLD_ENTITY)
            {
                static_cast<CTaskSimpleUseGun*>(secondaryAttackTask)->SetPedPosition(m_pPed);
            }
        }
    }

    CTask* secondaryAttackTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (secondaryAttackTask && secondaryAttackTask->GetTaskType() == TASK_SIMPLE_USE_GUN)
    {
        static_cast<CTaskSimpleUseGun*>(secondaryAttackTask)->SetPedPosition(m_pPed);
    }

    CWeapon* activeWeapon = &m_pPed->GetActiveWeapon();
    if (activeWeapon->m_nType == WEAPON_MOLOTOV && activeWeapon->m_pFxSystem)
    {
        RpHAnimHierarchy* animHierarchy = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);
        int32 animIDIndex = RpHAnimIDGetIndex(animHierarchy, 24); // 24 = BONE_R_HAND?
        RwMatrix* matrixArray = RpHAnimHierarchyGetMatrixArray(animHierarchy);

        RwV3d pointIn = { 0.05f, 0.05f,  0.14f };
        RwV3d pointOut;
        RwV3dTransformPoint(&pointOut, &pointIn, &matrixArray[animIDIndex]);

        RwMatrix matrix;
        memcpy(&matrix, m_pPed->GetModellingMatrix(), sizeof(matrix));
        matrix.pos = pointOut;
        RwMatrixUpdate(&matrix);
        activeWeapon->m_pFxSystem->SetMatrix(&matrix);
    }

    if (m_pPed->bInVehicle)
    {
        CVehicle* vehicle = m_pPed->m_pVehicle;
        if (vehicle && vehicle->IsBike()) {
            vehicle->AsBike()->FixHandsToBars(m_pPed);
        }
    }

    g_LoadMonitor.EndTimer(0);
}

// 0x601BB0
void CPedIntelligence::ProcessEventHandler() {
    m_eventHandler.HandleEvents();
}

// 0x601BC0
bool CPedIntelligence::IsFriendlyWith(const CPed& ped) const {
    auto respect = m_pPed->m_acquaintance.m_nRespect;
    auto like = m_pPed->m_acquaintance.m_nLike;
    auto pedFlag = CPedType::GetPedFlag((ePedType)ped.m_nPedType);
    return m_pPed->m_nPedType == ped.m_nPedType || pedFlag & respect || pedFlag & like;
}

// 0x601C30
bool CPedIntelligence::IsThreatenedBy(const CPed& ped) const {
    auto dislike = m_pPed->m_acquaintance.m_nDislike;
    auto hate = m_pPed->m_acquaintance.m_nHate;
    auto pedTypeFlag = CPedType::GetPedFlag((ePedType)ped.m_nPedType);
    return pedTypeFlag & dislike || pedTypeFlag & hate;
}

// 0x601C90
bool CPedIntelligence::Respects(CPed* pPed) {
    auto respect = m_pPed->m_acquaintance.m_nRespect;
    auto pedFlag = CPedType::GetPedFlag((ePedType)pPed->m_nPedType);
    return pedFlag & respect;
}

// 0x601CC0
bool CPedIntelligence::IsInACarOrEnteringOne() {
    if (auto taskComplexEnterCar = m_TaskMgr.FindActiveTaskByType(TASK_COMPLEX_ENTER_CAR_AS_DRIVER)) {
        return static_cast<CTaskComplexEnterCar*>(taskComplexEnterCar)->m_pTargetVehicle;
    }

    if (auto taskComplexEnterCar = m_TaskMgr.FindActiveTaskByType(TASK_COMPLEX_ENTER_CAR_AS_PASSENGER)) {
        return static_cast<CTaskComplexEnterCar*>(taskComplexEnterCar)->m_pTargetVehicle;
    }

    if (auto takSimpleCarDrive = m_TaskMgr.FindActiveTaskByType(TASK_SIMPLE_CAR_DRIVE)) {
        return static_cast<CTaskSimpleCarDrive*>(takSimpleCarDrive)->m_pVehicle;
    }

    return false;
}

// 0x601D10
bool CPedIntelligence::AreFriends(const CPed& ped1, const CPed& ped2) {
    return ped1.GetIntelligence()->IsFriendlyWith(ped2) || ped2.GetIntelligence()->IsFriendlyWith(ped1);
}

// unused
// 0x601D50
bool CPedIntelligence::IsPedGoingSomewhereOnFoot() {
    CTask* task = m_TaskMgr.GetSimplestActiveTask();
    if (task)
        return CTask::IsGoToTask(task);
    else
        return false;
}

// 0x601D70
int32 CPedIntelligence::GetMoveStateFromGoToTask() {
    auto task = (CTaskSimpleGoTo*)m_TaskMgr.GetSimplestActiveTask();
    if (task && CTask::IsGoToTask(task)) {
        return task->m_moveState;
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
bool CPedIntelligence::TestForStealthKill(CPed* target, bool bFullTest) {
    if (target->bInVehicle)
        return false;

    CVector bonePosition;
    target->GetBonePosition(bonePosition, BONE_HEAD, false);
    if (target->bIsDucking || target->m_fHealth < 1.0f)
        return false;

    if (bonePosition.z < target->GetPosition().z)
        return false;

    if (bFullTest)
        return true;

    if (target->m_nMoveState >= PEDMOVE_RUN)
        return false;

    CVector distance = target->GetPosition() - m_pPed->GetPosition();
    if (STEALTH_KILL_RANGE * STEALTH_KILL_RANGE < distance.SquaredMagnitude())
        return false;

    if (DotProduct(distance, target->GetForward()) <= 0.0f)
        return false;

    CTask* activeTask = target->GetTaskManager().GetActiveTask();
    if (activeTask) {
        if (activeTask->GetTaskType() == TASK_COMPLEX_KILL_PED_ON_FOOT) {
            auto pTaskComplexKillPedOnFoot = (CTaskComplexKillPedOnFoot*)activeTask;
            if (pTaskComplexKillPedOnFoot->m_target == m_pPed) {
                return false;
            }
        }
    }

    CEvent* currentEvent = target->GetEventHandlerHistory().GetCurrentEvent();
    if (currentEvent && currentEvent->GetSourceEntity() == m_pPed)
    {
        auto hate = target->m_acquaintance.GetAcquaintances(4); // todo: m_nHate
        auto dislike = target->m_acquaintance.GetAcquaintances(3); // todo: m_nDislike
        auto pedFlag = CPedType::GetPedFlag(m_pPed->m_nPedType);

        bool bAcquaintancesFlagSet = (
            (hate && (pedFlag & hate)) ||
            (dislike && (pedFlag & dislike))
        );
        CPedGroup* pedGroup = CPedGroups::GetPedsGroup(target);
        if (bAcquaintancesFlagSet && pedGroup) {
            CEventGroupEvent* eventGroupEvent = pedGroup->GetIntelligence().m_oldEventGroupEvent;
            if (eventGroupEvent && eventGroupEvent->GetSourceEntity() == m_pPed && bAcquaintancesFlagSet)
                return false;
        }
    }
    return true;
}

// 0x602050
void CPedIntelligence::RecordEventForScript(int32 eventId, int32 eventPriority) {
    if (eventId != EVENT_SCRIPT_COMMAND && (!eventId || eventPriority > m_nEventPriority))
    {
        m_nEventId = eventId;
        m_nEventPriority = eventPriority;
    }
}

// Unused
// 0x602080
bool CPedIntelligence::HasInterestingEntites() {
    return plugin::CallMethodAndReturn<bool, 0x602080, CPedIntelligence*>(this);
}

// 0x6020A0
bool CPedIntelligence::IsInterestingEntity(CEntity* entity) {
    for (CEntity* interestingEntity : m_apInterestingEntities) {
        if (interestingEntity == entity) {
            return true;
        }
    }
    return false;
}

// 0x6020D0
void CPedIntelligence::LookAtInterestingEntities() {
    if (m_pPed->bDontAcceptIKLookAts != false)
        return;

    bool bInterestingEntityExists = false;
    for (CEntity* interestingEntity : m_apInterestingEntities) {
        if (interestingEntity) {
            bInterestingEntityExists = true;
            break;
        }
    }

    if (!bInterestingEntityExists)
        return;

    if (g_ikChainMan.IsLooking(m_pPed) || !m_pPed->GetIsOnScreen() || CGeneral::GetRandomNumberInRange(0, 100) != 50)
        return;

    CEntity* outEntities[1024];
    int16 outCount = -1;
    CWorld::FindObjectsInRange(m_pPed->GetPosition(), 15.0f, false, &outCount, 1024, outEntities, false, true, true, true, false);
    if (outCount <= 0)
        return;

    int32 interestingEntityCount = 0;
    for (int32 i = 0; i < outCount; i++) {
        CEntity* entity = outEntities[i];
        if (IsInterestingEntity(entity)) {
            outEntities[interestingEntityCount] = entity;
            interestingEntityCount++;
        }
    }

    if (!interestingEntityCount)
        return;

    const int32 randomInterestingEntityIndex = CGeneral::GetRandomNumberInRange(0, interestingEntityCount);
    const int32 randomTime = CGeneral::GetRandomNumberInRange(3000, 5000);
    CPed* interestingEntity1 = (CPed*)outEntities[randomInterestingEntityIndex];

    CVector position = { 0.0f, 0.0f, 0.0f };
    g_ikChainMan.LookAt(
        "InterestingEntities",
        m_pPed,
        interestingEntity1,
        randomTime,
        BONE_UNKNOWN,
        &position,
        false,
        0.25f,
        500,
        3,
        false
    );
}

// unused
// 0x602320
void CPedIntelligence::RemoveAllInterestingEntities() {
    plugin::CallMethod<0x602320, CPedIntelligence*>(this);
}

// 0x602350
bool CPedIntelligence::IsPedGoingForCarDoor() {
    auto* activeSimplestTask = (CTaskSimple*)m_TaskMgr.GetSimplestActiveTask();
    if (activeSimplestTask) {
        if (activeSimplestTask->GetTaskType() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL) {
            return true;
        }

        CTask* parentTask = activeSimplestTask->m_pParentTask;
        if (parentTask) {
            if (parentTask->GetTaskType() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL) {
                return true;
            }

            CTask* grandParentTask = parentTask->m_pParentTask;
            if (grandParentTask && grandParentTask->GetTaskType() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL) {
                return true;
            }
        }
    }
    return false;
}

// should be (const CEntity* entity, bool unused)
// 0x605550
float CPedIntelligence::CanSeeEntityWithLights(CEntity* entity, int32 unUsed) {
    if (!entity->IsPed())
        return LIGHT_AI_LEVEL_MAX;

    CPed* ped = entity->AsPed();
    if (!ped->IsPlayer())
        return LIGHT_AI_LEVEL_MAX;

    float fLightingTotal = ped->GetLightingTotal();
    if (fLightingTotal > LIGHT_AI_LEVEL_MAX)
        return LIGHT_AI_LEVEL_MAX;

    const float fLightLevelSquared = LIGHT_AI_LEVEL_MAX * LIGHT_AI_LEVEL_MAX;
    float fMagnitude = (ped->GetPosition() - m_pPed->GetPosition()).Magnitude() - 0.7f;
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
    CTask* activeSimplestTask = m_TaskMgr.GetSimplestActiveTask();
    if (!activeSimplestTask || !CTask::IsGoToTask(activeSimplestTask)) {
        if (m_StaticCounter == -2) {
            m_StaticCounter = 4;
        } else {
            m_StaticCounter++;
        }
        m_AnotherStaticCounter = 0;
        return;
    }

    auto gotoTask = (CTaskSimpleGoTo*)activeSimplestTask;
    int32 moveState = gotoTask->m_moveState;
    if (moveState != PEDMOVE_WALK && moveState != PEDMOVE_RUN && moveState != PEDMOVE_SPRINT) {
        if (m_StaticCounter == -2) {
            m_StaticCounter = 4;
        } else {
            m_StaticCounter++;
        }
        m_AnotherStaticCounter = 0;
        return;
    }

    if (m_pPed->m_pDamageEntity) {
        if (m_StaticCounter > 4) {
            m_vecLastPedPosDuringDamageEntity = m_pPed->GetPosition();
        }
        m_StaticCounter = 0;
    } else {
        if (m_StaticCounter == -2) {
            m_StaticCounter = 4;
        } else {
            m_StaticCounter++;
        }
    }

    if (m_StaticCounter > 4) {
        m_AnotherStaticCounter = 0;
        return;
    }

    if ((m_pPed->GetPosition() - m_vecLastPedPosDuringDamageEntity).SquaredMagnitude() < 1 / 16) {
        m_AnotherStaticCounter++;
    } else {
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
        auto* ppCollisionEventScanner = (CCollisionEventScanner*)& field_260;
        ppCollisionEventScanner->ScanForCollisionEvents(m_pPed, &m_eventGroup);
    }

    if (m_pPed->m_fDamageIntensity > 0.0f)
    {
        CEntity* damageEntity = m_pPed->m_pDamageEntity;
        if (damageEntity && !damageEntity->IsPed()) {
            if (DotProduct(m_pPed->m_vecLastCollisionImpactVelocity, m_pPed->GetForward()) < -0.5f)
                m_pPed->bPedHitWallLastFrame = true;
        }
    }

    if (m_pPed->bInVehicle)
    {
        CVehicle* vehicle = m_pPed->m_pVehicle;
        if (vehicle && vehicle->IsBike()) {
            auto* bike = vehicle->AsBike();
            bike->m_bPedLeftHandFixed = false;
            bike->m_bPedRightHandFixed = false;
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
        m_entityScanner.ScanForEntitiesInRange(1, m_pPed);

    m_eventScanner.ScanForEvents(m_pPed);
    m_eventHandler.HandleEvents();
    m_TaskMgr.ManageTasks();

    auto recorder = CPlayerRelationshipRecorder::GetPlayerRelationshipRecorder();
    recorder->RecordRelationshipWithPlayer(m_pPed);
    LookAtInterestingEntities();

    g_LoadMonitor.EndTimer(0);
}

// 0x4B85B0
CTask* CPedIntelligence::GetActivePrimaryTask()
{
    CTask* task = m_TaskMgr.GetTaskPrimary(TASK_PRIMARY_PHYSICAL_RESPONSE);
    if (!task) {
        task = m_TaskMgr.GetTaskPrimary(TASK_PRIMARY_EVENT_RESPONSE_TEMP);
        if (!task) {
            task = m_TaskMgr.GetTaskPrimary(TASK_PRIMARY_EVENT_RESPONSE_NONTEMP);
        }
    }
    return task;
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
    CPools::ms_pPedIntelligencePool->Delete(static_cast<CPedIntelligence*>(object));
}
