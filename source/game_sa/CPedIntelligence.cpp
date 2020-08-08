/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

float& CPedIntelligence::STEALTH_KILL_RANGE = *reinterpret_cast<float*>(0x8D2398);
float& CPedIntelligence::LIGHT_AI_LEVEL_MAX = *reinterpret_cast<float*>(0x8D2380);
float& CPedIntelligence::flt_8D2384 = *reinterpret_cast<float*>(0x8D2384);
float& CPedIntelligence::flt_8D2388 = *reinterpret_cast<float*>(0x8D2388);

void CPedIntelligence::InjectHooks()
{
    HookInstall(0x4893E0, &CPedIntelligence::GetPedEntities);
    HookInstall(0x600B50, &CPedIntelligence::SetPedDecisionMakerType);
    HookInstall(0x600BB0, &CPedIntelligence::SetPedDecisionMakerTypeInGroup);
    HookInstall(0x600BC0, &CPedIntelligence::RestorePedDecisionMakerType);
    HookInstall(0x600BE0, &CPedIntelligence::SetHearingRange);
    HookInstall(0x600BF0, &CPedIntelligence::SetSeeingRange);
    HookInstall(0x600C60, &CPedIntelligence::IsInSeeingRange);
    HookInstall(0x600CF0, &CPedIntelligence::FindRespectedFriendInInformRange);
    HookInstall(0x600DB0, &CPedIntelligence::IsRespondingToEvent);
    HookInstall(0x600DC0, &CPedIntelligence::AddTaskPhysResponse);
    HookInstall(0x600DE0, &CPedIntelligence::AddTaskEventResponseTemp);
    HookInstall(0x600E00, &CPedIntelligence::AddTaskEventResponseNonTemp);;
    HookInstall(0x600E20, &CPedIntelligence::AddTaskPrimaryMaybeInGroup);
    HookInstall(0x600EE0, &CPedIntelligence::FindTaskByType);
    HookInstall(0x600F30, &CPedIntelligence::GetTaskFighting);
    HookInstall(0x600F70, &CPedIntelligence::GetTaskUseGun);
    HookInstall(0x600FB0, &CPedIntelligence::GetTaskThrow);
    HookInstall(0x600FF0, &CPedIntelligence::GetTaskHold);
    HookInstall(0x601070, &CPedIntelligence::GetTaskSwim);
    HookInstall(0x6010A0, &CPedIntelligence::GetTaskDuck);
    HookInstall(0x601110, &CPedIntelligence::GetTaskJetPack);
    HookInstall(0x601150, &CPedIntelligence::GetTaskInAir);
    HookInstall(0x601180, &CPedIntelligence::GetTaskClimb);
    HookInstall(0x6011B0, &CPedIntelligence::GetUsingParachute);
    HookInstall(0x601230, &CPedIntelligence::SetTaskDuckSecondary);
    HookInstall(0x601390, &CPedIntelligence::ClearTaskDuckSecondary);
    HookInstall(0x601420, &CPedIntelligence::ClearTasks);
    HookInstall(0x601640, &CPedIntelligence::FlushImmediately);
    HookInstall(0x6018D0, &CPedIntelligence::GetEffectInUse);
    HookInstall(0x6018E0, &CPedIntelligence::SetEffectInUse);
    HookInstall(0x6018F0, &CPedIntelligence::ProcessAfterProcCol);
    HookInstall(0x6019B0, &CPedIntelligence::ProcessAfterPreRender);
    HookInstall(0x601BB0, &CPedIntelligence::ProcessEventHandler);
    HookInstall(0x601BC0, &CPedIntelligence::IsFriendlyWith);
    HookInstall(0x601C30, &CPedIntelligence::IsThreatenedBy);
    HookInstall(0x601C90, &CPedIntelligence::Respects);
    HookInstall(0x601CC0, &CPedIntelligence::IsInACarOrEnteringOne);
    HookInstall(0x601D10, &CPedIntelligence::AreFriends);
    HookInstall(0x601D70, &CPedIntelligence::GetMoveStateFromGoToTask);
    HookInstall(0x601DA0, &CPedIntelligence::FlushIntelligence);
    HookInstall(0x601E00, &CPedIntelligence::TestForStealthKill);
    HookInstall(0x602050, &CPedIntelligence::RecordEventForScript);
    HookInstall(0x6020A0, &CPedIntelligence::IsInterestingEntity);
    HookInstall(0x6020D0, &CPedIntelligence::LookAtInterestingEntities);
    HookInstall(0x602350, &CPedIntelligence::IsPedGoingForCarDoor);
    HookInstall(0x605550, &CPedIntelligence::CanSeeEntityWithLights);
    HookInstall(0x605650, &CPedIntelligence::ProcessStaticCounter);
    HookInstall(0x6073A0, &CPedIntelligence::ProcessFirst);
    HookInstall(0x608260, &CPedIntelligence::Process);
    HookInstall(0x4B85B0, &CPedIntelligence::GetActivePrimaryTask);
}

CEntity** CPedIntelligence::GetPedEntities()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CEntity**, 0x4893E0, CPedIntelligence*>(this);
#else
    return m_entityScanner.m_apEntities;
#endif
}

// Converted from thiscall void CPedIntelligence::SetPedDecisionMakerType(int newtype) 0x600B50
void CPedIntelligence::SetPedDecisionMakerType(int newType) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600B50, CPedIntelligence*, int>(this, newType);
#else
    int oldType = m_nDecisionMakerType;
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
        m_fDmRadius = 5.0;
        m_nDmNumPedsToScan = 15;
    }
#endif
}

// Converted from thiscall void CPedIntelligence::SetPedDecisionMakerTypeInGroup(int newtype) 0x600BB0 
void CPedIntelligence::SetPedDecisionMakerTypeInGroup(int newType) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600BB0, CPedIntelligence*, int>(this, newType);
#else
    m_nDecisionMakerTypeInGroup = newType;
#endif
}

// Converted from thiscall void CPedIntelligence::RestorePedDecisionMakerType(void) 0x600BC0 
void CPedIntelligence::RestorePedDecisionMakerType() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600BC0, CPedIntelligence*>(this);
#else
    if (!m_nDecisionMakerType)
    {
        m_nDecisionMakerType = m_nDecisionMakerTypeInGroup;
    }
#endif
}

// Converted from thiscall void CPedIntelligence::SetHearingRange(float range) 0x600BE0 
void CPedIntelligence::SetHearingRange(float range) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600BE0, CPedIntelligence*, float>(this, range);
#else
    m_fHearingRange = range;
#endif
}

// Converted from thiscall void CPedIntelligence::SetSeeingRange(float range) 0x600BF0 
void CPedIntelligence::SetSeeingRange(float range) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600BF0, CPedIntelligence*, float>(this, range);
#else
    m_fSeeingRange = range;
#endif
}

// Unused
bool CPedIntelligence::IsInHearingRange(CVector const& posn) {
    return plugin::CallMethodAndReturn<bool, 0x600C00, CPedIntelligence*, CVector const&>(this, posn);
}

bool CPedIntelligence::IsInSeeingRange(CVector const& posn) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x600C60, CPedIntelligence*, CVector const&>(this, posn);
#else
    CVector distance = posn - m_pPed->GetPosition();
    if (m_fSeeingRange * m_fSeeingRange > distance.SquaredMagnitude()) {
        if (DotProduct(distance, m_pPed->GetForward()) > 0.0f)
            return true;
    }
    return false;
#endif
}

bool CPedIntelligence::FindRespectedFriendInInformRange() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x600CF0, CPedIntelligence*>(this);
#else
    unsigned int acquaintances = m_pPed->m_acquaintance.GetAcquaintances(0);
    for (unsigned int pedScanIndex = 0; pedScanIndex < m_nDmNumPedsToScan; pedScanIndex++) {
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
#endif
}

bool CPedIntelligence::IsRespondingToEvent(eEventType eventType) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x600DB0, CPedIntelligence*, eEventType>(this, eventType);
#else
    return m_eventHandler.m_history.IsRespondingToEvent(eventType);
#endif
}

// Converted from thiscall void CPedIntelligence::AddTaskPhysResponse(CTask *task,bool arg2) 0x600DC0 
void CPedIntelligence::AddTaskPhysResponse(CTask* pTask, int unUsed) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600DC0, CPedIntelligence*, CTask*, int>(this, pTask, unUsed);
#else
    m_TaskMgr.SetTask(pTask, 0, unUsed);
#endif
}

// Converted from thiscall void CPedIntelligence::AddTaskEventResponseTemp(CTask *task,bool arg2) 0x600DE0 
void CPedIntelligence::AddTaskEventResponseTemp(CTask* pTask, int unUsed) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600DE0, CPedIntelligence*, CTask*, int>(this, pTask, unUsed);
#else
    m_TaskMgr.SetTask(pTask, 1, unUsed);
#endif
}

// Converted from thiscall void CPedIntelligence::AddTaskEventResponseNonTemp(CTask *task,bool arg2) 0x600E00 
void CPedIntelligence::AddTaskEventResponseNonTemp(CTask* pTask, int unUsed) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600E00, CPedIntelligence*, CTask*, int>(this, pTask, unUsed);
#else
    m_TaskMgr.SetTask(pTask, 2, unUsed);
#endif
}

void CPedIntelligence::AddTaskPrimaryMaybeInGroup(CTask* pTask, bool bAffectsPed) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600E20, CPedIntelligence*, CTask*, bool>(this, pTask, bAffectsPed);
#else
    CPedGroup* pPegGroup = CPedGroups::GetPedsGroup(m_pPed);
    if (m_pPed->IsPlayer() || !pPegGroup)
    {
        CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, pTask, bAffectsPed);
        m_eventGroup.Add(&eventScriptCommand, false);
    }
    else
    {
        pPegGroup->m_groupIntelligence.SetScriptCommandTask(m_pPed, pTask);
        if (pTask)
        {
            delete pTask;
        }
    }
#endif
}

// Converted from thiscall CTask* CPedIntelligence::FindTaskByType(int type) 0x600EE0 
CTask* CPedIntelligence::FindTaskByType(int taskId) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x600EE0, CPedIntelligence*, int>(this, taskId);
#else
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
#endif
}

// Converted from thiscall CTaskSimpleFight* CPedIntelligence::GetTaskFighting(void) 0x600F30 
CTaskSimpleFight* CPedIntelligence::GetTaskFighting() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleFight*, 0x600F30, CPedIntelligence*>(this);
#else
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pTaskSecondary = pTaskManager->GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pTaskSecondary && pTaskSecondary->GetId() == TASK_SIMPLE_FIGHT)
    {
        return (CTaskSimpleFight*)pTaskSecondary;
    }
    return nullptr;
#endif
}

// Converted from thiscall CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun(void) 0x600F70 
CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleUseGun*, 0x600F70, CPedIntelligence*>(this);
#else
    CTask* pTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pTask && pTask->GetId() == TASK_SIMPLE_USE_GUN)
    {
        return (CTaskSimpleUseGun*)pTask;
    }
    return nullptr;
#endif
}

// Converted from thiscall CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow(void) 0x600FB0 
CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleThrowProjectile*, 0x600FB0, CPedIntelligence*>(this);
#else
    CTask* pTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pTask && pTask->GetId() == TASK_SIMPLE_THROW)
    {
        return (CTaskSimpleThrowProjectile*)pTask;
    }
    return nullptr;
#endif
}

CTask* CPedIntelligence::GetTaskHold(bool bIgnoreCheckingForSimplestActiveTask) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x600FF0, CPedIntelligence*, bool>(this, bIgnoreCheckingForSimplestActiveTask);
#else
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pTaskSecondary = pTaskManager->GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (pTaskSecondary)
    {
        if (pTaskSecondary->GetId() == TASK_SIMPLE_HOLD_ENTITY)
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
        || pActiveSimplestTask->GetId() != TASK_SIMPLE_PICKUP_ENTITY
        && pActiveSimplestTask->GetId() != TASK_SIMPLE_PUTDOWN_ENTITY)
    {
        return nullptr;
    }
    return pActiveSimplestTask;
#endif
}

// Converted from thiscall CTaskSimpleSwim* CPedIntelligence::GetTaskSwim(void) 0x601070 
CTaskSimpleSwim* CPedIntelligence::GetTaskSwim() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleSwim*, 0x601070, CPedIntelligence*>(this);
#else
    CTask* pTask = m_TaskMgr.GetSimplestActiveTask();
    if (pTask && pTask->GetId() == TASK_SIMPLE_SWIM)
    {
        return (CTaskSimpleSwim*)pTask;
    }
    return nullptr;
#endif
}

// Converted from thiscall CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool arg1) 0x6010A0 
CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool bIgnoreCheckingForSimplestActiveTask) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleDuck*, 0x6010A0, CPedIntelligence*, bool>(this, bIgnoreCheckingForSimplestActiveTask);
#else
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pSecondaryTask = (CTask*)pTaskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);
    if (pSecondaryTask && pSecondaryTask->GetId() == TASK_SIMPLE_DUCK)
    {
        return (CTaskSimpleDuck*)pSecondaryTask;
    }

    if (bIgnoreCheckingForSimplestActiveTask)
    {
        return nullptr;
    }

    CTask* pActiveSimplestTask = pTaskManager->GetSimplestActiveTask();
    if (!pActiveSimplestTask || pActiveSimplestTask->GetId() != TASK_SIMPLE_DUCK)
    {
        return nullptr;
    }
    return (CTaskSimpleDuck*)pActiveSimplestTask;
#endif
}

CTaskSimpleJetPack* CPedIntelligence::GetTaskJetPack() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleJetPack*, 0x601110, CPedIntelligence*>(this);
#else
    if (m_pPed->IsPlayer())
    {
        CTask* pTask = m_TaskMgr.GetSimplestActiveTask();
        if (pTask && pTask->GetId() == TASK_SIMPLE_JETPACK)
        {
            return (CTaskSimpleJetPack*)pTask;
        }
    }
    return nullptr;
#endif
}

CTaskSimpleInAir* CPedIntelligence::GetTaskInAir() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleInAir*, 0x601150, CPedIntelligence*>(this);
#else
    CTask* pTask = m_TaskMgr.GetSimplestActiveTask();
    if (pTask && pTask->GetId() == TASK_SIMPLE_IN_AIR)
    {
        return (CTaskSimpleInAir*)pTask;
    }
    return nullptr;
#endif
}

// Converted from thiscall CTaskSimpleClimb* CPedIntelligence::GetTaskClimb(void) 0x601180 
CTaskSimpleClimb* CPedIntelligence::GetTaskClimb() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTaskSimpleClimb*, 0x601180, CPedIntelligence*>(this);
#else
    auto pTask = (CTaskSimpleClimb*)m_TaskMgr.GetSimplestActiveTask();
    if (pTask && pTask->GetId() == TASK_SIMPLE_CLIMB)
    {
        return pTask;
    }
    return nullptr;
#endif
}

// Converted from thiscall bool CPedIntelligence::GetUsingParachute(void) 0x6011B0 
bool CPedIntelligence::GetUsingParachute() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x6011B0, CPedIntelligence*>(this);
#else
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

    int blockID = pAnimAssoc->m_pHierarchy->m_nAnimBlockId;
    if (stricmp(CAnimManager::ms_aAnimBlocks[blockID].szName, "parachute"))
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
#endif
}

// Converted from thiscall void CPedIntelligence::SetTaskDuckSecondary(ushort arg1) 0x601230 
void CPedIntelligence::SetTaskDuckSecondary(unsigned short nLengthOfDuck) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x601230, CPedIntelligence*, unsigned short>(this, nLengthOfDuck);
#else
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pSecondaryTask = pTaskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);

    if (pSecondaryTask)
    {
        if (pSecondaryTask->GetId() == TASK_SIMPLE_DUCK)
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
    if (pSecondaryAttackTask && pSecondaryAttackTask->GetId() == TASK_SIMPLE_USE_GUN)
    {
        auto pTaskUseGun = (CTaskSimpleUseGun*)pSecondaryAttackTask;
        pTaskUseGun->ClearAnim(m_pPed);
    }

    auto pDuckTask = (CTaskSimpleDuck*)pTaskManager->GetTaskSecondary(TASK_SECONDARY_DUCK);
    pDuckTask->ProcessPed(m_pPed);
#endif
}

// Converted from thiscall void CPedIntelligence::ClearTaskDuckSecondary(void) 0x601390 
void CPedIntelligence::ClearTaskDuckSecondary() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x601390, CPedIntelligence*>(this);
#else
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pSecondaryDuck = pTaskManager->GetTaskSecondary(1);
    if (pSecondaryDuck)
    {
        pSecondaryDuck->MakeAbortable(m_pPed, ABORT_PRIORITY_LEISURE, 0);
        CPlayerData* pPlayerData = m_pPed->m_pPlayerData;
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
            if (pTask->GetId() == TASK_SIMPLE_USE_GUN)
            {
                if (pTaskManager->GetTaskSecondary(0))
                {
                    CTaskSimpleUseGun* pTaskUseGun = GetTaskUseGun();
                    pTaskUseGun->ClearAnim(m_pPed);
                }
            }
        }
    }
#endif
}

// Converted from thiscall void CPedIntelligence::ClearTasks(bool arg1,bool arg2) 0x601420 
void CPedIntelligence::ClearTasks(bool bClearPrimaryTasks, bool bClearSecondaryTasks) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x601420, CPedIntelligence*, bool, bool>(this, bClearPrimaryTasks, bClearSecondaryTasks);
#else
    if (bClearPrimaryTasks)
    {
        if (m_pPed->bInVehicle && m_pPed->m_pVehicle)
        {
            if (!m_eventGroup.HasScriptCommandOfTaskType(TASK_SIMPLE_CAR_DRIVE))
            {
                CTask* pDriveTask = nullptr;
                if (m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_DEFAULT]->GetId() == TASK_SIMPLE_CAR_DRIVE)
                {
                    auto pTaskSimpleCarDriveTimed = (CTaskSimpleCarDriveTimed*)CTask::operator new(112);
                    if (pTaskSimpleCarDriveTimed)
                    {
                        pTaskSimpleCarDriveTimed->Constructor(m_pPed->m_pVehicle, 0);
                    }
                    pDriveTask = static_cast<CTask*>(pTaskSimpleCarDriveTimed);
                }
                else
                {
                    auto pTaskSimpleCarDrive = (CTaskSimpleCarDrive*)CTask::operator new(96);
                    if (pTaskSimpleCarDrive)
                    {
                        pTaskSimpleCarDrive->Constructor(m_pPed->m_pVehicle, 0, 0);
                    }
                    pDriveTask = static_cast<CTask*>(pTaskSimpleCarDrive);
                }
                CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, pDriveTask, 0);
                m_eventGroup.Add(&eventScriptCommand, false);
            }
        }
        else if (!m_eventGroup.HasScriptCommandOfTaskType(TASK_SIMPLE_STAND_STILL))
        {
            auto pTaskSimpleStandStill = new CTaskSimpleStandStill(0, 0, 0, 8.0f);
            CEventScriptCommand eventScriptCommand(TASK_PRIMARY_PRIMARY, pTaskSimpleStandStill, 0);
            m_eventGroup.Add(&eventScriptCommand, 0);
        }

        m_eventHandler.HandleEvents();
        m_TaskMgr.ManageTasks();
        CPedScriptedTaskRecord::Process();
    }

    if (bClearSecondaryTasks)
    {
        for (int secondaryTaskIndex = 0; secondaryTaskIndex < 6; secondaryTaskIndex++)
        {
            if (secondaryTaskIndex != TASK_SECONDARY_FACIAL_COMPLEX)
            {
                CTask* pSecondaryTask = m_TaskMgr.GetTaskSecondary(secondaryTaskIndex);
                if (pSecondaryTask)
                {
                    if (pSecondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_URGENT, 0))
                    {
                        m_TaskMgr.SetTaskSecondary(0, secondaryTaskIndex);
                    }
                    else
                    {
                        pSecondaryTask->MakeAbortable(m_pPed, ABORT_PRIORITY_LEISURE, 0);
                    }
                }
            }
        }
    }
#endif
}

void CPedIntelligence::FlushImmediately(bool bSetPrimaryDefaultTask) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethod<0x601640, CPedIntelligence*, bool>(this, bSetPrimaryDefaultTask);
#else
    CTask* pPrimaryTask = m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_PRIMARY];
    CTaskComplex* pTaskComplexBeInGroup = nullptr;
    if (pPrimaryTask && pPrimaryTask->GetId() == TASK_COMPLEX_BE_IN_GROUP)
    {
        pTaskComplexBeInGroup = (CTaskComplex*)pPrimaryTask->Clone();
    }

    CTaskSimpleHoldEntity* pTaskSimpleHoldEntity = nullptr;
    CTask* pSecondaryTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (pSecondaryTask && pSecondaryTask->GetId() == TASK_SIMPLE_HOLD_ENTITY)
    {
        pTaskSimpleHoldEntity = (CTaskSimpleHoldEntity*)pSecondaryTask;
    }

    int objectType = -1;
    bool bIsEntityVisible = false;
    CObject* pObjectToHold = nullptr;
    CTaskSimpleHoldEntity* pTaskSimpleHoldEntityCloned = nullptr;
    if (pTaskSimpleHoldEntity && pTaskSimpleHoldEntity->GetId() == TASK_SIMPLE_HOLD_ENTITY)
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
    if (pTaskComplexFacial && pTaskComplexFacial->GetId() == TASK_COMPLEX_FACIAL)
    {
        pTaskComplexFacialCloned = static_cast<CTaskComplexFacial*>(pTaskComplexFacial->Clone());
    }

    m_eventGroup.Flush(1);
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
        m_TaskMgr.SetTask(0, TASK_PRIMARY_DEFAULT, 0);
        return;
    }
#endif
}

// Converted from thiscall C2dEffect* CPedIntelligence::GetEffectInUse(void) 0x6018D0 
C2dEffect* CPedIntelligence::GetEffectInUse() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<C2dEffect*, 0x6018D0, CPedIntelligence*>(this);
#else
    return m_eventScanner.m_attractorScanner.m_pEffectInUse;
#endif
}

// Converted from thiscall void CPedIntelligence::SetEffectInUse(C2dEffect *arg1) 0x6018E0 
void CPedIntelligence::SetEffectInUse(C2dEffect* arg1) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6018E0, CPedIntelligence*, C2dEffect*>(this, arg1);
#else
    m_eventScanner.m_attractorScanner.m_pEffectInUse = arg1;
#endif
}

// Converted from thiscall void CPedIntelligence::ProcessAfterProcCol(void) 0x6018F0 
void CPedIntelligence::ProcessAfterProcCol() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6018F0, CPedIntelligence*>(this);
#else
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
            RwObject* pRwObject = m_pPed->m_pRwObject;
            if (pRwObject)
            {
                RwMatrix* pRwMatrix = &((RwFrame*)pRwObject->parent)->modelling;
                if (m_pPed->m_matrix)
                {
                    m_pPed->m_matrix->UpdateRwMatrix(pRwMatrix);
                }
                else
                {
                    m_pPed->m_placement.UpdateRwMatrix(pRwMatrix);
                }
            }
            m_pPed->UpdateRwFrame();
        }
    }

    m_pPed->bCalledPreRender = 0;
    g_LoadMonitor.EndTimer(0);
#endif
}

// Converted from thiscall void CPedIntelligence::ProcessAfterPreRender(void) 0x6019B0 
void CPedIntelligence::ProcessAfterPreRender() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6019B0, CPedIntelligence*>(this);
#else
    g_LoadMonitor.StartTimer(0);

    CTask* pSecondaryTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (pSecondaryTask && pSecondaryTask->IsSimple())
    {
        CTaskSimple* pSimpleTask = (CTaskSimple*)pSecondaryTask;
        if (pSimpleTask->SetPedPosition(m_pPed))
        {
            CTask* pSecondaryAttackTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
            if (pSecondaryAttackTask && pSecondaryAttackTask->GetId() == TASK_SIMPLE_HOLD_ENTITY)
            {
                CTaskSimpleHoldEntity* pTaskSimpleHoldEntity = (CTaskSimpleHoldEntity*)pSecondaryAttackTask;
                pTaskSimpleHoldEntity->SetPedPosition(m_pPed);
            }
        }
    }

    CTask* pSecondaryAttackTask = m_TaskMgr.GetTaskSecondary(TASK_SECONDARY_ATTACK);
    if (pSecondaryAttackTask && pSecondaryAttackTask->GetId() == TASK_SIMPLE_USE_GUN)
    {
        CTaskSimpleUseGun* pTaskUseGun = (CTaskSimpleUseGun*)pSecondaryAttackTask;
        pTaskUseGun->SetPedPosition(m_pPed);
    }

    CWeapon* pActiveWeapon = &m_pPed->m_aWeapons[m_pPed->m_nActiveWeaponSlot];
    if (pActiveWeapon->m_nType == WEAPON_MOLOTOV && pActiveWeapon->m_pFxSystem)
    {
        RpHAnimHierarchy* pRpAnimHierarchy = GetAnimHierarchyFromSkinClump(m_pPed->m_pRwClump);
        int animIDIndex = RpHAnimIDGetIndex(pRpAnimHierarchy, 24); // 24 = BONE_R_HAND?
        RwMatrix* pMatrixArray = RpHAnimHierarchyGetMatrixArray(pRpAnimHierarchy);

        RwV3d pointIn = { 0.050000001f, 0.050000001f,  0.14f };
        RwV3d pointOut;
        RwV3dTransformPoint(&pointOut, &pointIn, &pMatrixArray[animIDIndex]);

        RwMatrix* pRwMatrix = nullptr;
        RwObject* pRwObject = m_pPed->m_pRwObject;
        if (pRwObject)
        {
            pRwMatrix = &((RwFrame*)pRwObject->parent)->modelling;
        }

        RwMatrix matrix;
        memcpy(&matrix, pRwMatrix, sizeof(matrix));
        matrix.pos = pointOut;
        RwMatrixUpdate(&matrix);
        pActiveWeapon->m_pFxSystem->SetMatrix(&matrix);
    }

    if (m_pPed->bInVehicle)
    {
        CVehicle* pVehicle = m_pPed->m_pVehicle;
        if (pVehicle)
        {
            if (pVehicle->m_nVehicleClass == CLASS_LEISUREBOAT)
            {
                CBike* pBike = (CBike*)pVehicle;
                pBike->FixHandsToBars(m_pPed);
            }
        }
    }

    g_LoadMonitor.EndTimer(0);
#endif
}

// Converted from thiscall void CPedIntelligence::ProcessEventHandler(void) 0x601BB0 
void CPedIntelligence::ProcessEventHandler() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x601BB0, CPedIntelligence*>(this);
#else
    m_eventHandler.HandleEvents();
#endif
}

// Converted from thiscall bool CPedIntelligence::IsFriendlyWith(CPed const& ped) 0x601BC0 
bool CPedIntelligence::IsFriendlyWith(CPed* pPed) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x601BC0, CPedIntelligence*, CPed*>(this, pPed);
#else
    unsigned int respect = m_pPed->m_acquaintance.m_nRespect;
    unsigned int like = m_pPed->m_acquaintance.m_nLike;
    unsigned int pedFlag = CPedType::GetPedFlag((ePedType)pPed->m_nPedType);
    return m_pPed->m_nPedType == pPed->m_nPedType || pedFlag & respect || pedFlag & like;
#endif
}

// Converted from thiscall bool CPedIntelligence::IsThreatenedBy(CPed const& ped) 0x601C30 
bool CPedIntelligence::IsThreatenedBy(CPed const& ped) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x601C30, CPedIntelligence*, CPed const&>(this, ped);
#else
    unsigned int dislike = m_pPed->m_acquaintance.m_nDislike;
    unsigned int hate = m_pPed->m_acquaintance.m_nHate;
    unsigned int pedTypeFlag = CPedType::GetPedFlag((ePedType)ped.m_nPedType);
    return pedTypeFlag & dislike || pedTypeFlag & hate;
#endif
}

// Converted from thiscall bool CPedIntelligence::Respects(CPed const& ped) 0x601C90 
bool CPedIntelligence::Respects(CPed* pPed) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x601C90, CPedIntelligence*, CPed*>(this, pPed);
#else
    unsigned int respect = m_pPed->m_acquaintance.m_nRespect;
    unsigned int pedFlag = CPedType::GetPedFlag((ePedType)pPed->m_nPedType);
    return pedFlag & respect;
#endif
}

// Converted from thiscall bool CPedIntelligence::IsInACarOrEnteringOne(void) 0x601CC0 
bool CPedIntelligence::IsInACarOrEnteringOne() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x601CC0, CPedIntelligence*>(this);
#else
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
    return nullptr;
#endif
}

// Converted from cdecl bool CPedIntelligence::AreFriends(CPed const& ped1,CPed const& ped2) 0x601D10 
bool CPedIntelligence::AreFriends(CPed* ped1, CPed* ped2) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x601D10, CPed*, CPed*>(ped1, ped2);
#else
    return ped1->m_pIntelligence->IsFriendlyWith(ped2) || ped2->m_pIntelligence->IsFriendlyWith(ped1);
#endif
}

// unused
bool CPedIntelligence::IsPedGoingSomewhereOnFoot() {
    return plugin::CallMethodAndReturn<bool, 0x601D50, CPedIntelligence*>(this);
}

// Converted from thiscall int* CPedIntelligence::GetMoveStateFromGoToTask(void) 0x601D70 
int CPedIntelligence::GetMoveStateFromGoToTask() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<int, 0x601D70, CPedIntelligence*>(this);
#else
    auto pTask = (CTaskSimpleGoTo*)m_TaskMgr.GetSimplestActiveTask();
    if (pTask && CTask::IsGoToTask(pTask))
    {
        return pTask->m_moveState;
    }
    return PEDMOVE_STILL;
#endif
}

void CPedIntelligence::FlushIntelligence() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x601DA0, CPedIntelligence*>(this);
#else
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
#endif
}

// Converted from thiscall bool CPedIntelligence::TestForStealthKill(CPed *pPed,bool arg2) 0x601E00 
bool CPedIntelligence::TestForStealthKill(CPed* pTarget, bool bFullTest) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x601E00, CPedIntelligence*, CPed*, bool>(this, pTarget, bFullTest);
#else
    if (pTarget->bInVehicle)
        return false;
    CVector bonePosition;
    pTarget->GetBonePosition(bonePosition, BONE_HEAD, 0);
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
        if (pActiveTask->GetId() == TASK_COMPLEX_KILL_PED_ON_FOOT)
        {
            auto pTaskComplexKillPedOnFoot = (CTaskComplexKillPedOnFoot*)pActiveTask;
            if (pTaskComplexKillPedOnFoot->m_pTarget == m_pPed)
            {
                return false;
            }
        }
    }

    CEvent* pCurrentEvent = pTarget->GetEventHandlerHistory().GetCurrentEvent();
    if (pCurrentEvent && pCurrentEvent->GetSourceEntity() == m_pPed)
    {
        int acquaintancesID4 = pTarget->m_acquaintance.GetAcquaintances(4);
        int acquaintancesID3 = pTarget->m_acquaintance.GetAcquaintances(3);
        unsigned int pedFlag = CPedType::GetPedFlag(m_pPed->m_nPedType);

        bool bAcquaintancesFlagSet = ((acquaintancesID4 && (pedFlag & acquaintancesID4))
            || (acquaintancesID3 && (pedFlag & acquaintancesID3))
            );

        CPedGroup* pPedGroup = CPedGroups::GetPedsGroup(pTarget);
        if (bAcquaintancesFlagSet && pPedGroup) {
            CEventGroupEvent* eventGroupEvent = pPedGroup->GetIntelligence().m_oldEventGroupEvent;
            if (eventGroupEvent && eventGroupEvent->GetSourceEntity() == m_pPed && bAcquaintancesFlagSet)
                return false;
        }
    }
    return true;
#endif
}

// Converted from thiscall void CPedIntelligence::RecordEventForScript(int EventID,int EventPriority) 0x602050 
void CPedIntelligence::RecordEventForScript(int EventID, int EventPriority) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x602050, CPedIntelligence*, int, int>(this, EventID, EventPriority);
#else
    if (EventID != EVENT_SCRIPT_COMMAND && (!EventID || EventPriority > m_nEventPriority))
    {
        m_nEventId = EventID;
        m_nEventPriority = EventPriority;
    }
#endif
}

// Unused
bool CPedIntelligence::HasInterestingEntites() {
    return plugin::CallMethodAndReturn<bool, 0x602080, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsInterestingEntity(CEntity *pEntity) 0x6020A0 
bool CPedIntelligence::IsInterestingEntity(CEntity* pEntity) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x6020A0, CPedIntelligence*, CEntity*>(this, pEntity);
#else
    for (unsigned int i = 0; i < 3; i++)
    {
        if (m_apInterestingEntities[i] == pEntity)
        {
            return true;
        }
    }
    return false;
#endif
}

// Converted from thiscall void CPedIntelligence::LookAtInterestingEntities(void) 0x6020D0 
void CPedIntelligence::LookAtInterestingEntities() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6020D0, CPedIntelligence*>(this);
#else
    if (!m_pPed->bDontAcceptIKLookAts)
    {
        bool bInterestingEntityExists = false;
        for (unsigned int i = 0; i < 3; i++)
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
            short outCount = -1;
            CWorld::FindObjectsInRange(m_pPed->GetPosition(), 15.0f, 0, &outCount, 1024, outEntities, 0, 1, 1, 1, 0);
            if (outCount > 0)
            {
                int interestingEntityCount = 0;
                for (int i = 0; i < outCount; i++)
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
                    unsigned int randomInterestingEntityIndex = CGeneral::GetRandomNumberInRange(0, interestingEntityCount);
                    unsigned int randomTime = CGeneral::GetRandomNumberInRange(3000, 5000);
                    CPed* pInterestingEntity = (CPed*)outEntities[randomInterestingEntityIndex];

                    RwV3d position = { 0.0f, 0.0f, 0.0f };
                    g_ikChainMan->LookAt("InterestingEntities", m_pPed, pInterestingEntity, randomTime, BONE_UNKNOWN,
                        &position, 0, 0.25, 500, 3, 0);
                }
            }
        }
    }
#endif
}

// Unused 
void CPedIntelligence::RemoveAllInterestingEntities() {
    plugin::CallMethod<0x602320, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsPedGoingForCarDoor(void) 0x602350 
bool CPedIntelligence::IsPedGoingForCarDoor() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x602350, CPedIntelligence*>(this);
#else
    CTaskSimple* pActiveSimplestTask = (CTaskSimple*)m_TaskMgr.GetSimplestActiveTask();
    if (pActiveSimplestTask)
    {
        if (pActiveSimplestTask->GetId() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL)
        {
            return true;
        }

        CTask* pParentTask = pActiveSimplestTask->m_pParentTask;
        if (pParentTask)
        {
            if (pParentTask->GetId() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL)
            {
                return true;
            }

            CTask* pGrandParentTask = pParentTask->m_pParentTask;
            if (pGrandParentTask && pGrandParentTask->GetId() == TASK_COMPLEX_GO_TO_CAR_DOOR_AND_STAND_STILL)
            {
                return true;
            }
        }

    }
    return false;
#endif
}

// Converted from thiscall float CPedIntelligence::CanSeeEntityWithLights(CEntity const*pEntity,bool arg2) 0x605550 
float CPedIntelligence::CanSeeEntityWithLights(CEntity* pEntity, int unUsed) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<float, 0x605550, CPedIntelligence*, CEntity const*, bool>(this, pEntity, unUsed);
#else
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
#endif
}

// Converted from thiscall void CPedIntelligence::ProcessStaticCounter(void) 0x605650 
void CPedIntelligence::ProcessStaticCounter() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x605650, CPedIntelligence*>(this);
#else
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
    int moveState = pGotoTask->m_moveState;
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
#endif
}

// Converted from thiscall void CPedIntelligence::ProcessFirst(void) 0x6073A0 
void CPedIntelligence::ProcessFirst() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x6073A0, CPedIntelligence*>(this);
#else
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
        if (pVehicle)
        {
            if (pVehicle->m_nVehicleClass == CLASS_LEISUREBOAT)
            {
                CBike* pBike = static_cast<CBike*>(pVehicle);
                pBike->m_bPedLeftHandFixed = 0;
                pBike->m_bPedRightHandFixed = 0;
            }
        }
    }
    m_pPed->bMoveAnimSpeedHasBeenSetByTask = 0;
    g_LoadMonitor.EndTimer(0);
#endif
}

// Converted from thiscall void CPedIntelligence::Process(void) 0x608260 
void CPedIntelligence::Process() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x608260, CPedIntelligence*>(this);
#else
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
#endif
}

CTask* CPedIntelligence::GetActivePrimaryTask()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<CTask*, 0x4B85B0, CPedIntelligence*>(this);
#else
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
#endif
}

float CPedIntelligence::GetPedFOVRange()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<float, 0x4ABEA0, CPedIntelligence*>(this);
#else
    return std::max(m_fHearingRange, m_fSeeingRange);
#endif
}

// Converted from cdecl void CPedIntelligence::operator delete(void * arg1) 0x6074E0 
void CPedIntelligence::operator delete(void* arg1) {
    plugin::Call<0x6074E0, void*>(arg1);
}
