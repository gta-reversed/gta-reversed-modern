/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

float& CPedIntelligence::LIGHT_AI_LEVEL_MAX = *reinterpret_cast<float*>(0x8D2380);
float& CPedIntelligence::flt_8D2384 = *reinterpret_cast<float*>(0x8D2384);
float& CPedIntelligence::flt_8D2388 = *reinterpret_cast<float*>(0x8D2388);

// Converted from thiscall void CPedIntelligence::SetPedDecisionMakerType(int newtype) 0x600B50
void CPedIntelligence::SetPedDecisionMakerType(int newtype) {
    plugin::CallMethod<0x600B50, CPedIntelligence*, int>(this, newtype);
}

// Converted from thiscall void CPedIntelligence::SetPedDecisionMakerTypeInGroup(int newtype) 0x600BB0 
void CPedIntelligence::SetPedDecisionMakerTypeInGroup(int newtype) {
    plugin::CallMethod<0x600BB0, CPedIntelligence*, int>(this, newtype);
}

// Converted from thiscall void CPedIntelligence::RestorePedDecisionMakerType(void) 0x600BC0 
void CPedIntelligence::RestorePedDecisionMakerType() {
    plugin::CallMethod<0x600BC0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::SetHearingRange(float range) 0x600BE0 
void CPedIntelligence::SetHearingRange(float range) {
    plugin::CallMethod<0x600BE0, CPedIntelligence*, float>(this, range);
}

// Converted from thiscall void CPedIntelligence::SetSeeingRange(float range) 0x600BF0 
void CPedIntelligence::SetSeeingRange(float range) {
    plugin::CallMethod<0x600BF0, CPedIntelligence*, float>(this, range);
}

// Converted from thiscall bool CPedIntelligence::IsInHearingRange(CVector const& posn) 0x600C00 
bool CPedIntelligence::IsInHearingRange(CVector const& posn) {
    return plugin::CallMethodAndReturn<bool, 0x600C00, CPedIntelligence*, CVector const&>(this, posn);
}

// Converted from thiscall bool CPedIntelligence::IsInSeeingRange(CVector const& posn) 0x600C60 
bool CPedIntelligence::IsInSeeingRange(CVector* posn) {
    return plugin::CallMethodAndReturn<bool, 0x600C60, CPedIntelligence*, CVector*>(this, posn);
}

bool CPedIntelligence::FindRespectedFriendInInformRange() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<bool, 0x600CF0, CPedIntelligence*>(this);
#else

    unsigned int acquaintances = m_pPed->m_acquaintance.GetAcquaintances(0);
    for (unsigned int pedScanIndex = 0; pedScanIndex < 16; pedScanIndex++)
    {
        if (pedScanIndex >= m_nDmNumPedsToScan)
        {
            return 0;
        }
        CPed* pPedEntity = (CPed*)m_pedScanner.m_apEntities[pedScanIndex];
        if (pPedEntity)
        {
            if (CPedType::GetPedFlag((ePedType)pPedEntity->m_nPedType) & acquaintances)
            {
                CVector* pPedEntityPos = &pPedEntity->m_placement.m_vPosn;
                CMatrixLink* pPedEntityMatrix = pPedEntity->m_matrix;
                if (pPedEntityMatrix)
                {
                    pPedEntityPos = &pPedEntityMatrix->pos;
                }
                CMatrixLink* pPedMatrix = m_pPed->m_matrix;
                CVector* pPedPos = pPedMatrix ? &pPedMatrix->pos : &m_pPed->m_placement.m_vPosn;
                double fX = pPedPos->x - pPedEntityPos->x;
                double fY = pPedPos->y - pPedEntityPos->y;
                double fZ = pPedPos->z - pPedEntityPos->z;
                double result = fY * fY + fX * fX + fZ * fZ;
                if ((m_fDmRadius * m_fDmRadius) > result)
                {
                    return 1;
                }
            }
        }
    }
    return 0;
#endif
}

// Converted from thiscall bool CPedIntelligence::IsRespondingToEvent(int event) 0x600DB0 
bool CPedIntelligence::IsRespondingToEvent(int event) {
    return plugin::CallMethodAndReturn<bool, 0x600DB0, CPedIntelligence*, int>(this, event);
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

// Converted from thiscall void CPedIntelligence::AddTaskPrimaryMaybeInGroup(CTask *task,bool arg2) 0x600E20 
void CPedIntelligence::AddTaskPrimaryMaybeInGroup(CTask* pTask, bool bUnknown) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallMethod<0x600E20, CPedIntelligence*, CTask*, bool>(this, pTask, bUnknown);
#else
    CPedGroup* pPegGroup = CPedGroups::GetPedsGroup(m_pPed);
    if (m_pPed->IsPlayer() || !pPegGroup)
    {
        CEventScriptCommand eventScriptCommand;
        eventScriptCommand.Constructor(3, pTask, bUnknown);
        m_eventGroup.Add((CEvent*)& eventScriptCommand, 0);
        eventScriptCommand.Destructor();
    }
    else
    {
        pPegGroup->m_groupIntelligence.SetScriptCommandTask(m_pPed, pTask);
        if (pTask)
        {
            pTask->DeletingDestructor(1);
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
    return plugin::CallMethodAndReturn<CTaskSimpleFight*, 0x600F30, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun(void) 0x600F70 
CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun() {
    return plugin::CallMethodAndReturn<CTaskSimpleUseGun*, 0x600F70, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow(void) 0x600FB0 
CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow() {
    return plugin::CallMethodAndReturn<CTaskSimpleThrowProjectile*, 0x600FB0, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleHoldEntity* CPedIntelligence::GetTaskHold(bool arg1) 0x600FF0 
CTaskSimpleHoldEntity* CPedIntelligence::GetTaskHold(bool arg1) {
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x600FF0, CPedIntelligence*, bool>(this, arg1);
}

// Converted from thiscall CTaskSimpleSwim* CPedIntelligence::GetTaskSwim(void) 0x601070 
CTaskSimpleSwim* CPedIntelligence::GetTaskSwim() {
    return plugin::CallMethodAndReturn<CTaskSimpleSwim*, 0x601070, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool arg1) 0x6010A0 
CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool arg1) {
    return plugin::CallMethodAndReturn<CTaskSimpleDuck*, 0x6010A0, CPedIntelligence*, bool>(this, arg1);
}

// Converted from thiscall CTaskSimpleJetPack* CPedIntelligence::GetTaskJetPack(void) 0x601110 
CTaskSimpleJetPack* CPedIntelligence::GetTaskJetPack() {
    return plugin::CallMethodAndReturn<CTaskSimpleJetPack*, 0x601110, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleInAir* CPedIntelligence::GetTaskInAir(void) 0x601150 
CTaskSimpleInAir* CPedIntelligence::GetTaskInAir() {
    return plugin::CallMethodAndReturn<CTaskSimpleInAir*, 0x601150, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleClimb* CPedIntelligence::GetTaskClimb(void) 0x601180 
CTaskSimpleClimb* CPedIntelligence::GetTaskClimb() {
    return plugin::CallMethodAndReturn<CTaskSimpleClimb*, 0x601180, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::GetUsingParachute(void) 0x6011B0 
bool CPedIntelligence::GetUsingParachute() {
    return plugin::CallMethodAndReturn<bool, 0x6011B0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::SetTaskDuckSecondary(ushort arg1) 0x601230 
void CPedIntelligence::SetTaskDuckSecondary(unsigned short arg1) {
    plugin::CallMethod<0x601230, CPedIntelligence*, unsigned short>(this, arg1);
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
        CEventScriptCommand eventScriptCommand;

        if (m_pPed->bInVehicle && m_pPed->m_pVehicle)
        {
            if (!m_eventGroup.HasScriptCommandOfTaskType(TASK_SIMPLE_CAR_DRIVE))
            {
                if (m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_DEFAULT]->GetId() == TASK_SIMPLE_CAR_DRIVE)
                {
                    auto pTaskSimpleCarDriveTimed = (CTaskSimpleCarDriveTimed*)CTask::operator new(112);
                    if (pTaskSimpleCarDriveTimed)
                    {
                        pTaskSimpleCarDriveTimed->Constructor(m_pPed->m_pVehicle, 0);
                    }
                    eventScriptCommand.Constructor(3, (CTask*)pTaskSimpleCarDriveTimed, 0);
                }
                else
                {
                    auto pTaskSimpleCarDrive = (CTaskSimpleCarDrive*)CTask::operator new(96);
                    if (pTaskSimpleCarDrive)
                    {
                        pTaskSimpleCarDrive->Constructor(m_pPed->m_pVehicle, 0, 0);
                    }
                    eventScriptCommand.Constructor(3, (CTask*)pTaskSimpleCarDrive, 0);
                }
                m_eventGroup.Add((CEvent*)& eventScriptCommand, 0);
                eventScriptCommand.Destructor();
            }
        }
        else if (!m_eventGroup.HasScriptCommandOfTaskType(TASK_SIMPLE_STAND_STILL))
        {
            auto pTaskSimpleStandStill = (CTaskSimpleStandStill*)CTask::operator new(32);
            if (pTaskSimpleStandStill)
            {
                pTaskSimpleStandStill = pTaskSimpleStandStill->Constructor(0, 0, 0, 8.0);
            }

            eventScriptCommand.Constructor(3, (CTask*)pTaskSimpleStandStill, 0);
            m_eventGroup.Add((CEvent*)& eventScriptCommand, 0);
            eventScriptCommand.Destructor();
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
    plugin::CallMethod<0x601640, CPedIntelligence*, bool>(this, bSetPrimaryDefaultTask);
#else
    bool bIsEntityVisible = false;

    CTask* pPrimaryTask = m_TaskMgr.m_aPrimaryTasks[TASK_PRIMARY_PRIMARY];
    CTaskSimpleHoldEntity* pTaskSimpleHoldEntityCloned = nullptr;
    CTaskComplex* pTaskComplexBeInGroup = nullptr;
    if (pPrimaryTask && pPrimaryTask->GetId() == TASK_COMPLEX_BE_IN_GROUP)
    {
        pTaskComplexBeInGroup = (CTaskComplex*)pPrimaryTask->Clone();
    }

    CTaskSimpleHoldEntity* pTaskSimpleHoldEntity = nullptr;
    CTaskManager* pTaskManager = &m_TaskMgr;
    CTask* pSecondaryTask = pTaskManager->GetTaskSecondary(TASK_SECONDARY_PARTIAL_ANIM);
    if (pSecondaryTask && pSecondaryTask->GetId() == TASK_SIMPLE_HOLD_ENTITY)
    {
        pTaskSimpleHoldEntity = (CTaskSimpleHoldEntity*)pSecondaryTask;
    }

    int objectType = -1;
    CObject* pObjectToHold = nullptr;
    if (pTaskSimpleHoldEntity)
    {
        if (pTaskSimpleHoldEntity->GetId() == TASK_SIMPLE_HOLD_ENTITY)
        {
            pObjectToHold = pTaskSimpleHoldEntity->m_pObjectToHold;
            if (pObjectToHold)
            {
                if (pObjectToHold->m_nType == ENTITY_TYPE_OBJECT)
                {
                    objectType = pObjectToHold->m_nObjectType;
                    bIsEntityVisible = pObjectToHold->m_bIsVisible;
                    pTaskSimpleHoldEntityCloned = (CTaskSimpleHoldEntity*)pTaskSimpleHoldEntity->Clone();
                }
                else
                {
                    pTaskSimpleHoldEntityCloned = (CTaskSimpleHoldEntity*)pTaskSimpleHoldEntity->Clone();
                    bIsEntityVisible = bSetPrimaryDefaultTask;
                }
            }
        }
    }

    if (objectType == -1)
    {
        // seriously? 
        bIsEntityVisible = bSetPrimaryDefaultTask;
    }

    pSecondaryTask = pTaskManager->GetTaskSecondary(TASK_SECONDARY_FACIAL_COMPLEX);
    CTaskComplex* pTaskComplexFacial = nullptr;
    if (pSecondaryTask && pSecondaryTask->GetId() == TASK_COMPLEX_FACIAL)
    {
        pTaskComplexFacial = (CTaskComplex*)pSecondaryTask->Clone();
    }

    m_eventGroup.Flush(true);
    m_eventHandler.FlushImmediately();
    pTaskManager->FlushImmediately();
    CPedScriptedTaskRecord::Process();
    if (pTaskComplexBeInGroup)
    {
        CPedGroup* pPedGroup = CPedGroups::GetPedsGroup(m_pPed);
        if (!pPedGroup || m_pPed->IsPlayer())
        {
            pTaskComplexBeInGroup->DeletingDestructor(1);
        }
        else
        {
            pPedGroup->m_groupIntelligence.ComputeDefaultTasks(m_pPed);
            pTaskManager->SetTask(pTaskComplexBeInGroup, TASK_PRIMARY_PRIMARY, 0);
        }
    }
    if (pTaskSimpleHoldEntityCloned)
    {
        if (objectType != -1)
        {
            pTaskSimpleHoldEntityCloned->m_pObjectToHold->m_nObjectType = objectType;
            if (bIsEntityVisible)
            {
                pTaskSimpleHoldEntityCloned->m_pObjectToHold->m_bIsVisible = 1;
            }
        }
        pTaskManager->SetTaskSecondary(pTaskSimpleHoldEntityCloned, TASK_SECONDARY_PARTIAL_ANIM);
        pTaskSimpleHoldEntityCloned->ProcessPed(m_pPed);
    }
    if (pTaskComplexFacial)
    {
        pTaskManager->SetTaskSecondary(pTaskComplexFacial, TASK_SECONDARY_FACIAL_COMPLEX);
    }
    if (bSetPrimaryDefaultTask)
    {
        if (m_pPed->IsPlayer())
        {
            auto pTaskSimplePlayerOnFoot = (CTaskSimplePlayerOnFoot*)CTask::operator new(28);
            if (pTaskSimplePlayerOnFoot)
            {
                pTaskSimplePlayerOnFoot->Constructor();
                pTaskManager->SetTask(pTaskSimplePlayerOnFoot, TASK_PRIMARY_DEFAULT, 0);
                return;
            }
        }
        else
        {
            if (m_pPed->m_nCreatedBy != 2)
            {
                auto pTaskComplexWander = CTaskComplexWander::GetWanderTaskByPedType(m_pPed);
                pTaskManager->SetTask(pTaskComplexWander, TASK_PRIMARY_DEFAULT, 0);
                return;
            }

            auto pTaskSimpleStandStill = (CTaskSimpleStandStill*)CTask::operator new(32);
            if (pTaskSimpleStandStill)
            {
                pTaskSimpleStandStill->Constructor(0, 1, 0, 8.0);
                pTaskManager->SetTask(pTaskSimpleStandStill, TASK_PRIMARY_DEFAULT, 0);
                return;
            }
        }
        pTaskManager->SetTask(0, TASK_PRIMARY_DEFAULT, 0);
        return;
    }
#endif
}

// Converted from thiscall C2dEffect* CPedIntelligence::GetEffectInUse(void) 0x6018D0 
C2dEffect* CPedIntelligence::GetEffectInUse() {
    return plugin::CallMethodAndReturn<C2dEffect*, 0x6018D0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::SetEffectInUse(C2dEffect *arg1) 0x6018E0 
void CPedIntelligence::SetEffectInUse(C2dEffect* arg1) {
    plugin::CallMethod<0x6018E0, CPedIntelligence*, C2dEffect*>(this, arg1);
}

// Converted from thiscall void CPedIntelligence::ProcessAfterProcCol(void) 0x6018F0 
void CPedIntelligence::ProcessAfterProcCol() {
    plugin::CallMethod<0x6018F0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::ProcessAfterPreRender(void) 0x6019B0 
void CPedIntelligence::ProcessAfterPreRender() {
    plugin::CallMethod<0x6019B0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::ProcessEventHandler(void) 0x601BB0 
void CPedIntelligence::ProcessEventHandler() {
    plugin::CallMethod<0x601BB0, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsFriendlyWith(CPed const& ped) 0x601BC0 
bool CPedIntelligence::IsFriendlyWith(CPed const& ped) {
    return plugin::CallMethodAndReturn<bool, 0x601BC0, CPedIntelligence*, CPed const&>(this, ped);
}

// Converted from thiscall bool CPedIntelligence::IsThreatenedBy(CPed const& ped) 0x601C30 
bool CPedIntelligence::IsThreatenedBy(CPed const& ped) {
    return plugin::CallMethodAndReturn<bool, 0x601C30, CPedIntelligence*, CPed const&>(this, ped);
}

// Converted from thiscall bool CPedIntelligence::Respects(CPed const& ped) 0x601C90 
bool CPedIntelligence::Respects(CPed const& ped) {
    return plugin::CallMethodAndReturn<bool, 0x601C90, CPedIntelligence*, CPed const&>(this, ped);
}

// Converted from thiscall bool CPedIntelligence::IsInACarOrEnteringOne(void) 0x601CC0 
bool CPedIntelligence::IsInACarOrEnteringOne() {
    return plugin::CallMethodAndReturn<bool, 0x601CC0, CPedIntelligence*>(this);
}

// Converted from cdecl bool CPedIntelligence::AreFriends(CPed const& ped1,CPed const& ped2) 0x601D10 
bool CPedIntelligence::AreFriends(CPed const& ped1, CPed const& ped2) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturn<bool, 0x601D10, CPed const&, CPed const&>(ped1, ped2);
#else
    return ped1.m_pIntelligence->IsFriendlyWith(ped2) || ped2.m_pIntelligence->IsFriendlyWith(ped1);
#endif
}

// Converted from thiscall bool CPedIntelligence::IsPedGoingSomewhereOnFoot(void) 0x601D50 
bool CPedIntelligence::IsPedGoingSomewhereOnFoot() {
    return plugin::CallMethodAndReturn<bool, 0x601D50, CPedIntelligence*>(this);
}

// Converted from thiscall int* CPedIntelligence::GetMoveStateFromGoToTask(void) 0x601D70 
int* CPedIntelligence::GetMoveStateFromGoToTask() {
    return plugin::CallMethodAndReturn<int*, 0x601D70, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::FlushIntelligence(void) 0x601DA0 
void CPedIntelligence::FlushIntelligence() {
    plugin::CallMethod<0x601DA0, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::TestForStealthKill(CPed *pPed,bool arg2) 0x601E00 
bool CPedIntelligence::TestForStealthKill(CPed* pPed, bool arg2) {
    return plugin::CallMethodAndReturn<bool, 0x601E00, CPedIntelligence*, CPed*, bool>(this, pPed, arg2);
}

// Converted from thiscall void CPedIntelligence::RecordEventForScript(int EventID,int EventPriority) 0x602050 
void CPedIntelligence::RecordEventForScript(int EventID, int EventPriority) {
    plugin::CallMethod<0x602050, CPedIntelligence*, int, int>(this, EventID, EventPriority);
}

// Converted from thiscall bool CPedIntelligence::HasInterestingEntites(void) 0x602080 
bool CPedIntelligence::HasInterestingEntites() {
    return plugin::CallMethodAndReturn<bool, 0x602080, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsInterestingEntity(CEntity *pEntity) 0x6020A0 
bool CPedIntelligence::IsInterestingEntity(CEntity* pEntity) {
    return plugin::CallMethodAndReturn<bool, 0x6020A0, CPedIntelligence*, CEntity*>(this, pEntity);
}

// Converted from thiscall void CPedIntelligence::LookAtInterestingEntities(void) 0x6020D0 
void CPedIntelligence::LookAtInterestingEntities() {
    plugin::CallMethod<0x6020D0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::RemoveAllInterestingEntities(void) 0x602320 
void CPedIntelligence::RemoveAllInterestingEntities() {
    plugin::CallMethod<0x602320, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsPedGoingForCarDoor(void) 0x602350 
bool CPedIntelligence::IsPedGoingForCarDoor() {
    return plugin::CallMethodAndReturn<bool, 0x602350, CPedIntelligence*>(this);
}

// Converted from thiscall float CPedIntelligence::CanSeeEntityWithLights(CEntity const*pEntity,bool arg2) 0x605550 
double CPedIntelligence::CanSeeEntityWithLights(CEntity * pEntity, int unUsed) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallMethodAndReturn<double, 0x605550, CPedIntelligence*, CEntity const*, bool>(this, pEntity, unUsed);
#else
    if (pEntity->m_nType != ENTITY_TYPE_PED)
    {
        return LIGHT_AI_LEVEL_MAX;
    }
    CPed* pPedEntity = static_cast<CPed*>(pEntity);
    if (!pPedEntity->IsPlayer())
    {
        return LIGHT_AI_LEVEL_MAX;
    }
    double fLightingTotal = pPedEntity->GetLightingTotal();
    if (fLightingTotal > LIGHT_AI_LEVEL_MAX)
    {
        return LIGHT_AI_LEVEL_MAX;
    }

    CVector* pPedPos = &m_pPed->m_placement.m_vPosn;
    CMatrixLink* pPedMatrix = m_pPed->m_matrix;
    if (pPedMatrix)
    {
        pPedPos = &pPedMatrix->pos;
    }

    CMatrixLink* pEntityMatrix = pPedEntity->m_matrix;
    CVector* pEntityPos = &pPedEntity->m_placement.m_vPosn;
    if (pEntityMatrix)
    {
        pEntityPos = &pEntityMatrix->pos;
    }
    double fX = pEntityPos->x - pPedPos->x;
    double fY = pEntityPos->y - pPedPos->y;
    double fZ = pEntityPos->z - pPedPos->z;
    float entitya = sqrt(fZ * fZ + fX * fX + fY * fY) - 0.69999999;
    double result = fLightingTotal * fLightingTotal - entitya / flt_8D2384 * LIGHT_AI_LEVEL_MAX * LIGHT_AI_LEVEL_MAX;
    if (result <= 0.0)
    {
        result = result * result - entitya / flt_8D2388 * LIGHT_AI_LEVEL_MAX * LIGHT_AI_LEVEL_MAX;
        if (result <= 0.0)
        {
            result = 0.0;
        }
        else
        {
            result = result * -1.0;
        }
    }
    return result;
#endif
}

// Converted from thiscall void CPedIntelligence::ProcessStaticCounter(void) 0x605650 
void CPedIntelligence::ProcessStaticCounter() {
    plugin::CallMethod<0x605650, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::ProcessFirst(void) 0x6073A0 
void CPedIntelligence::ProcessFirst() {
    plugin::CallMethod<0x6073A0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::Process(void) 0x608260 
void CPedIntelligence::Process() {
    plugin::CallMethod<0x608260, CPedIntelligence*>(this);
}

CTask* CPedIntelligence::GetActivePrimaryTask()
{
    return plugin::CallMethodAndReturn<CTask*, 0x4B85B0, CPedIntelligence*>(this);
}

// Converted from cdecl void CPedIntelligence::operator delete(void * arg1) 0x6074E0 
void CPedIntelligence::operator delete(void* arg1) {
    plugin::Call<0x6074E0, void*>(arg1);
}