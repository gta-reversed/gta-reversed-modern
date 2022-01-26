#include "StdInc.h"

#include "TaskComplexWanderCop.h"

#include "TaskSimpleStandStill.h"
#include "TaskComplexPolicePursuit.h"

void CTaskComplexWanderCop::InjectHooks()
{
    RH_ScopedClass(CTaskComplexWanderCop);
    RH_ScopedCategory("Task/TaskTypes");
    RH_ScopedInstall(Constructor, 0x460C80);
    RH_ScopedInstall(Clone_Reversed, 0x460CE0);
    RH_ScopedInstall(CreateNextSubTask_Reversed, 0x674860);
    RH_ScopedInstall(CreateFirstSubTask_Reversed, 0x674750);
    RH_ScopedInstall(ControlSubTask_Reversed, 0x674D80);
    RH_ScopedInstall(ScanForStuff_Reversed, 0x6702B0);
    RH_ScopedInstall(LookForCarAlarms, 0x66B1B0);
    RH_ScopedInstall(LookForStolenCopCars, 0x66B290);
    RH_ScopedInstall(LookForCriminals, 0x66B300);
    RH_ScopedInstall(ShouldPursuePlayer, 0x66B160);
}

// todo: 0x460C80, time ctor
CTaskComplexWanderCop::CTaskComplexWanderCop(int32 moveState, uint8 dir) : CTaskComplexWander(moveState, dir, true, 0.5f) {
    m_pTaskComplexMoveGoToPointAndStandStill = 0;
    m_nScanForStuffTimer.m_nStartTime = 0;
    m_nScanForStuffTimer.m_nInterval = 0;
    m_nScanForStuffTimer.m_bStarted = 0;
    m_nScanForStuffTimer.m_bStopped = 0;
    m_nTimePassedSinceLastLookedForCriminals = 0;
    m_nTimePassedSinceLastLookedForCarAlarmsAndStolenCopCars = 0;
    m_pLastCriminalPedLookedFor = 0;
    m_nSubTaskCreatedTimer.m_nStartTime = 0;
    m_nSubTaskCreatedTimer.m_nInterval = 0;
    m_nSubTaskCreatedTimer.m_bStarted = 0;
    m_nSubTaskCreatedTimer.m_bStopped = 0;
}

// 0x460D60
CTaskComplexWanderCop::~CTaskComplexWanderCop() { 
    CTask* task = (CTask*)m_pTaskComplexMoveGoToPointAndStandStill;
    delete task;
}

// 0x460C80
CTaskComplexWanderCop* CTaskComplexWanderCop::Constructor(int32 moveState, uint8 dir) {
    this->CTaskComplexWanderCop::CTaskComplexWanderCop(moveState, dir);
    return this;
}

// 0x460CE0
CTask* CTaskComplexWanderCop::Clone() {
    return new CTaskComplexWanderCop(m_nMoveState, m_nDir);
}

// 0x674860
CTask* CTaskComplexWanderCop::CreateNextSubTask(CPed* ped)
{
    return CreateNextSubTask_Reversed(ped);
}

// 0x674750
CTask* CTaskComplexWanderCop::CreateFirstSubTask(CPed* ped)
{
    return CreateFirstSubTask_Reversed(ped);
}

// 0x674D80
CTask* CTaskComplexWanderCop::ControlSubTask(CPed* ped)
{
    return ControlSubTask_Reversed(ped);
}

// 0x460D50
int32 CTaskComplexWanderCop::GetWanderType()
{
    return CTaskComplexWanderCop::GetWanderType_Reversed();
}

// 0x6702B0
void CTaskComplexWanderCop::ScanForStuff(CPed* ped)
{
    return ScanForStuff_Reversed(ped);
}

CTask* CTaskComplexWanderCop::Clone_Reversed() {
    return new CTaskComplexWanderCop(m_nMoveState, m_nDir);
}

CTask* CTaskComplexWanderCop::CreateNextSubTask_Reversed(CPed* ped)
{
    CCopPed* pPed = (CCopPed*)ped;
    if (pPed->m_nPedType != PED_TYPE_COP)
    {
        return CTaskComplexWander::CreateNextSubTask(pPed);
    }

    if (pPed->m_bDontPursuit)
    {
        return nullptr;
    }

    if (m_pSubTask->GetTaskType() == TASK_COMPLEX_POLICE_PURSUIT)
    {
        m_nSubTaskCreatedTimer.m_nStartTime = CTimer::GetTimeInMS();
        m_nSubTaskCreatedTimer.m_nInterval = 3000;
        m_nSubTaskCreatedTimer.m_bStarted = 1;
        if (m_pTaskComplexMoveGoToPointAndStandStill)
        {
            return ((CTask*)m_pTaskComplexMoveGoToPointAndStandStill)->Clone();
        }
        else
        {
            return CTaskComplexWander::CreateFirstSubTask(pPed);
        }
}
    else
    {
        CTask* pTaskGotoStandStill = (CTask*)m_pTaskComplexMoveGoToPointAndStandStill;
        if (pTaskGotoStandStill && m_pSubTask->GetTaskType() == pTaskGotoStandStill->GetTaskType())
        {
            return nullptr;
        }
        else
        {
            if (m_pTaskComplexMoveGoToPointAndStandStill)
            {
                return ((CTask*)m_pTaskComplexMoveGoToPointAndStandStill)->Clone();
            }
            else
            {
                return CTaskComplexWander::CreateNextSubTask(pPed);
            }
        }
    }
    return nullptr;
}

CTask* CTaskComplexWanderCop::CreateFirstSubTask_Reversed(CPed* ped)
{
    CCopPed* cop = (CCopPed*)ped;
    if (cop->m_nPedType != PED_TYPE_COP)
    {
        return CTaskComplexWander::CreateFirstSubTask(cop);
    }
    if (cop->m_bDontPursuit)
    {
        auto pTaskSimpleStandStill = new CTaskSimpleStandStill(100000, 1, 0, 8.0);
        if (pTaskSimpleStandStill) 
            return pTaskSimpleStandStill;
        return nullptr;
    }
    if (!ShouldPursuePlayer(cop))
    {
        if (m_pTaskComplexMoveGoToPointAndStandStill)
        {
            return ((CTask*)m_pTaskComplexMoveGoToPointAndStandStill)->Clone();
        }
        return CTaskComplexWander::CreateFirstSubTask(cop);
    }
    auto pTaskComplexPolicePursuit = (CTaskComplexPolicePursuit*)CTask::operator new(24);
    if (!pTaskComplexPolicePursuit)
    {
        return nullptr;
    }
    pTaskComplexPolicePursuit->Constructor();
    return (CTask*)pTaskComplexPolicePursuit;
}

CTask* CTaskComplexWanderCop::ControlSubTask_Reversed(CPed* ped)
{
    CCopPed* pPed = (CCopPed*)ped;
    if (pPed->m_nPedType != PED_TYPE_COP)
    {
        return CTaskComplexWander::ControlSubTask(pPed);
    }
    if (!ShouldPursuePlayer(pPed))
    {
        if (m_pSubTask->GetTaskType() == TASK_COMPLEX_POLICE_PURSUIT)
        {
            return m_pSubTask;
        }
        if (m_pTaskComplexMoveGoToPointAndStandStill)
        {
            return m_pSubTask;
        }

        return CTaskComplexWander::ControlSubTask(pPed);
    }
    if (m_nSubTaskCreatedTimer.m_bStarted && !m_nSubTaskCreatedTimer.IsOutOfTime()
        || !m_pSubTask->MakeAbortable(pPed, ABORT_PRIORITY_URGENT, 0))
    {
        return m_pSubTask;
    }

    auto pTaskComplexPolicePursuit = (CTaskComplexPolicePursuit*)CTask::operator new(24);
    if (pTaskComplexPolicePursuit)
    {
        pTaskComplexPolicePursuit->Constructor();
        return pTaskComplexPolicePursuit;
    }
    return nullptr;
}

void CTaskComplexWanderCop::ScanForStuff_Reversed(CPed* ped)
{
    CCopPed* cop = (CCopPed*)ped;
    if (!m_nScanForStuffTimer.m_bStarted)
    {
        m_nScanForStuffTimer.m_nStartTime = CTimer::GetTimeInMS();
        m_nScanForStuffTimer.m_nInterval = 50;
        m_nScanForStuffTimer.m_bStarted = 1;
    }
    if (GetTaskType() != TASK_COMPLEX_POLICE_PURSUIT && m_nScanForStuffTimer.m_bStarted)
    {
        if (m_nScanForStuffTimer.m_bStopped)
        {
            m_nScanForStuffTimer.m_nStartTime = CTimer::GetTimeInMS();
            m_nScanForStuffTimer.m_bStopped = 0;
        }

        if (CTimer::GetTimeInMS() >= (m_nScanForStuffTimer.m_nStartTime + m_nScanForStuffTimer.m_nInterval))
        {
            m_nScanForStuffTimer.m_nInterval = 50;
            m_nScanForStuffTimer.m_nStartTime = CTimer::GetTimeInMS();
            m_nScanForStuffTimer.m_bStarted = 1;

            if (CTimer::GetTimeInMS() >= m_nTimePassedSinceLastLookedForCarAlarmsAndStolenCopCars)
            {
                LookForCarAlarms(cop);
                LookForStolenCopCars(cop);
            }

            if (CTimer::GetTimeInMS() >= m_nTimePassedSinceLastLookedForCriminals)
            {
                LookForCriminals(cop);
            }
        }
    }
}

// 0x66B1B0
void CTaskComplexWanderCop::LookForCarAlarms(CCopPed* ped)
{
    CVehicle* vehicle = FindPlayerVehicle(-1, 0);
    if (vehicle && vehicle->IsAutomobile()) {
        int16 alaramState = vehicle->m_nAlarmState;
        if (alaramState) {
            if (alaramState != -1 && vehicle->m_nStatus != STATUS_WRECKED) {
                CVector distance = vehicle->GetPosition() - ped->GetPosition();
                if (distance.SquaredMagnitude() < 400.0f)
                    FindPlayerPed(-1)->SetWantedLevelNoDrop(1);
            }
        }
    }
}

// 0x66B290
void CTaskComplexWanderCop::LookForStolenCopCars(CCopPed* ped)
{
    CPlayerPed* player = FindPlayerPed(-1);

    CWanted* wanted = nullptr;
    if (player->m_pPlayerData)
    {
        wanted = player->m_pPlayerData->m_pWanted;
    }

    if (wanted && !wanted->m_nWantedLevel && player->m_pVehicle)
    {
        if (player->m_pVehicle->vehicleFlags.bIsLawEnforcer)
        {
            player->SetWantedLevelNoDrop(1);
        }
    }
}

// 0x66B300
void CTaskComplexWanderCop::LookForCriminals(CCopPed* ped)
{
    CPed* criminalPed = nullptr;
    for (int32 entityIndex = 0; entityIndex < 16; entityIndex++)
    {
        criminalPed = (CPed*)ped->GetIntelligence()->m_entityScanner.m_apEntities[entityIndex];
        if (!criminalPed)
            continue;

        int32 pedType = criminalPed->m_nPedType;
        if (pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10
            || pedType == PED_TYPE_CRIMINAL && criminalPed != m_pLastCriminalPedLookedFor)
        {
            CTask* activeTask = criminalPed->GetTaskManager().GetActiveTask();
            if (activeTask && activeTask->GetTaskType() == GetTaskType())
            {
                CVector distance = (criminalPed->GetPosition() - ped->GetPosition());
                if (10.0f * 10.0f > distance.SquaredMagnitude())
                {
                    const float dot = DotProduct(distance, ped->GetForward());
                    if (dot > 0.0f && CWorld::GetIsLineOfSightClear(ped->GetPosition(), criminalPed->GetPosition(), 1, 0, 0, 1, 0, 0, 0))
                        break;
                }
            }
        }
    }

    if (!criminalPed)
        return;

    CEventPedToChase eventPedToChase(criminalPed);
    ped->GetEventGroup().Add(&eventPedToChase, false);

    CEventPedToFlee eventPedToFlee(ped);
    criminalPed->GetEventGroup().Add(&eventPedToFlee, false);

    // 30 seconds wait for next check
    m_nTimePassedSinceLastLookedForCriminals = CTimer::GetTimeInMS() + 30000;
    m_pLastCriminalPedLookedFor = criminalPed;
}

// 0x66B160
bool CTaskComplexWanderCop::ShouldPursuePlayer(CCopPed* pPed)
{
    CWanted* wanted = FindPlayerWanted(-1);
    if (wanted->m_nWantedLevel > 0)
    {
        if (!m_pSubTask || m_pSubTask->GetTaskType() != TASK_COMPLEX_POLICE_PURSUIT)
        {
            if (wanted->CanCopJoinPursuit(pPed))
            {
                return true;
            }
        }
    }
    return false;
}
