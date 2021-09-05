#include "StdInc.h"

void CTaskComplexWanderCop::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexWanderCop", "CTaskComplexWanderCop", 0x460C80, &CTaskComplexWanderCop::Constructor);
    ReversibleHooks::Install("CTaskComplexWanderCop", "Clone", 0x460CE0, &CTaskComplexWanderCop::Clone_Reversed);
    ReversibleHooks::Install("CTaskComplexWanderCop", "CreateNextSubTask", 0x674860, &CTaskComplexWanderCop::CreateNextSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexWanderCop", "CreateFirstSubTask", 0x674750, &CTaskComplexWanderCop::CreateFirstSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexWanderCop", "ControlSubTask", 0x674D80, &CTaskComplexWanderCop::ControlSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexWanderCop", "ScanForStuff", 0x6702B0, &CTaskComplexWanderCop::ScanForStuff_Reversed);
    ReversibleHooks::Install("CTaskComplexWanderCop", "LookForCarAlarms", 0x66B1B0, &CTaskComplexWanderCop::LookForCarAlarms);
    ReversibleHooks::Install("CTaskComplexWanderCop", "LookForStolenCopCars", 0x66B290, &CTaskComplexWanderCop::LookForStolenCopCars);
    ReversibleHooks::Install("CTaskComplexWanderCop", "LookForCriminals", 0x66B300, &CTaskComplexWanderCop::LookForCriminals);
    ReversibleHooks::Install("CTaskComplexWanderCop", "ShouldPursuePlayer", 0x66B160, &CTaskComplexWanderCop::ShouldPursuePlayer);
}

CTaskComplexWanderCop::CTaskComplexWanderCop(int32 moveState, uint8 dir) : CTaskComplexWander(moveState, dir, true, 0.5) {
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

CTaskComplexWanderCop::~CTaskComplexWanderCop() { 
    CTask* pTask = (CTask*)m_pTaskComplexMoveGoToPointAndStandStill;
    if (pTask)
        delete pTask;
}

CTaskComplexWanderCop* CTaskComplexWanderCop::Constructor(int32 moveState, uint8 dir) {
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTaskComplexWanderCop*, 0x460C80, CTaskComplexWanderCop*, int32, uint8>(this, moveState, dir);
#else
    this->CTaskComplexWanderCop::CTaskComplexWanderCop(moveState, dir);
    return this;
#endif
}


CTask* CTaskComplexWanderCop::Clone() {
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x460CE0, CTaskComplexWander*>(this);
#else
    return new CTaskComplexWanderCop(m_nMoveState, m_nDir);
#endif
}

CTask* CTaskComplexWanderCop::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674860, CTaskComplexWander*, CPed*>(this, ped);
#else
    return CreateNextSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexWanderCop::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674750, CTaskComplexWander*, CPed*>(this, ped);
#else
    return CreateFirstSubTask_Reversed(ped);
#endif
}

CTask* CTaskComplexWanderCop::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674D80, CTaskComplexWander*, CPed*>(this, ped);
#else
    return ControlSubTask_Reversed(ped);
#endif
}

int32 CTaskComplexWanderCop::GetWanderType()
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((int32(__thiscall*)(CTaskComplex*))0x460D50)(this);
#else
    return CTaskComplexWanderCop::GetWanderType_Reversed();
#endif
}


void CTaskComplexWanderCop::ScanForStuff(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((void(__thiscall*)(CTaskComplex*, CPed*))0x6702B0)(this, ped);
#else
    return ScanForStuff_Reversed(ped);
#endif
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

    if (m_pSubTask->GetId() == TASK_COMPLEX_POLICE_PURSUIT)
    {
        m_nSubTaskCreatedTimer.m_nStartTime = CTimer::m_snTimeInMilliseconds;
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
        if (pTaskGotoStandStill && m_pSubTask->GetId() == pTaskGotoStandStill->GetId())
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
    CCopPed* pPed = (CCopPed*)ped;
    if (pPed->m_nPedType != PED_TYPE_COP)
    {
        return CTaskComplexWander::CreateFirstSubTask(pPed);
    }
    if (pPed->m_bDontPursuit)
    {
        auto pTaskSimpleStandStill = new CTaskSimpleStandStill(100000, 1, 0, 8.0);
        if (pTaskSimpleStandStill) 
            return pTaskSimpleStandStill;
        return nullptr;
    }
    if (!ShouldPursuePlayer(pPed))
    {
        if (m_pTaskComplexMoveGoToPointAndStandStill)
        {
            return ((CTask*)m_pTaskComplexMoveGoToPointAndStandStill)->Clone();
        }
        return CTaskComplexWander::CreateFirstSubTask(pPed);
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
        if (m_pSubTask->GetId() == TASK_COMPLEX_POLICE_PURSUIT)
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
    CCopPed* pPed = (CCopPed*)ped;
    if (!m_nScanForStuffTimer.m_bStarted)
    {
        m_nScanForStuffTimer.m_nStartTime = CTimer::m_snTimeInMilliseconds;
        m_nScanForStuffTimer.m_nInterval = 50;
        m_nScanForStuffTimer.m_bStarted = 1;
    }
    if (GetId() != TASK_COMPLEX_POLICE_PURSUIT && m_nScanForStuffTimer.m_bStarted)
    {
        if (m_nScanForStuffTimer.m_bStopped)
        {
            m_nScanForStuffTimer.m_nStartTime = CTimer::m_snTimeInMilliseconds;
            m_nScanForStuffTimer.m_bStopped = 0;
        }

        if (CTimer::m_snTimeInMilliseconds >= (m_nScanForStuffTimer.m_nStartTime + m_nScanForStuffTimer.m_nInterval))
        {
            m_nScanForStuffTimer.m_nInterval = 50;
            m_nScanForStuffTimer.m_nStartTime = CTimer::m_snTimeInMilliseconds;
            m_nScanForStuffTimer.m_bStarted = 1;

            if (CTimer::m_snTimeInMilliseconds >= m_nTimePassedSinceLastLookedForCarAlarmsAndStolenCopCars)
            {
                LookForCarAlarms(pPed);
                LookForStolenCopCars(pPed);
            }

            if (CTimer::m_snTimeInMilliseconds >= m_nTimePassedSinceLastLookedForCriminals)
            {
                LookForCriminals(pPed);
            }
        }
    }
}

void CTaskComplexWanderCop::LookForCarAlarms(CCopPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    plugin::CallMethod<0x66B1B0, CTaskComplexWanderCop*, CPed*>(this, pPed);
#else
    CVehicle* pPlayerVehicle = FindPlayerVehicle(-1, 0);
    if (pPlayerVehicle && pPlayerVehicle->IsAutomobile()) {
        int16 alaramState = pPlayerVehicle->m_nAlarmState;
        if (alaramState) {
            if (alaramState != -1 && pPlayerVehicle->m_nStatus != STATUS_WRECKED) {
                CVector distance = pPlayerVehicle->GetPosition() - pPed->GetPosition();
                if (distance.SquaredMagnitude() < 400.0f)
                    FindPlayerPed(-1)->SetWantedLevelNoDrop(1);
            }
        }
    }
#endif
}

void CTaskComplexWanderCop::LookForStolenCopCars(CCopPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    plugin::CallMethod<0x66B290, CTaskComplexWanderCop*, CPed*>(this, pPed);
#else
    CPlayerPed* pPlayerPed = FindPlayerPed(-1);

    CWanted* pWanted = nullptr;
    if (pPlayerPed->m_pPlayerData)
    {
        pWanted = pPlayerPed->m_pPlayerData->m_pWanted;
    }

    if (pWanted && !pWanted->m_nWantedLevel && pPlayerPed->m_pVehicle)
    {
        if (pPlayerPed->m_pVehicle->vehicleFlags.bIsLawEnforcer)
        {
            pPlayerPed->SetWantedLevelNoDrop(1);
        }
    }
#endif
}

void CTaskComplexWanderCop::LookForCriminals(CCopPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    plugin::CallMethod<0x66B300, CTaskComplexWanderCop*, CPed*>(this, pPed);
#else
    CPed* pCriminalPed = nullptr;
    for (int32 entityIndex = 0; entityIndex < 16; entityIndex++)
    {
        pCriminalPed = (CPed*)pPed->m_pIntelligence->m_entityScanner.m_apEntities[entityIndex];
        if (pCriminalPed)
        {
            int32 pedType = pCriminalPed->m_nPedType;
            if (pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10
                || pedType == PED_TYPE_CRIMINAL && pCriminalPed != m_pLastCriminalPedLookedFor)
            {
                CTask* pActiveTask = pCriminalPed->m_pIntelligence->m_TaskMgr.GetActiveTask();
                if (pActiveTask && pActiveTask->GetId() == GetId())
                {
                    CVector distance = (pCriminalPed->GetPosition() - pPed->GetPosition());
                    if (10.0f * 10.0f > distance.SquaredMagnitude())
                    {
                        const float dot = DotProduct(distance, pPed->GetForward());
                        if (dot > 0.0f && CWorld::GetIsLineOfSightClear(pPed->GetPosition(), pCriminalPed->GetPosition(), 1, 0, 0, 1, 0, 0, 0))
                            break;
                    }
                }
            }
        }
    }

    if (!pCriminalPed)
    {
        return;
    }

    CEventPedToChase eventPedToChase(pCriminalPed);
    pPed->GetEventGroup().Add(&eventPedToChase, false);

    CEventPedToFlee eventPedToFlee(pPed);
    pCriminalPed->GetEventGroup().Add(&eventPedToFlee, false);

    // 30 seconds wait for next check
    m_nTimePassedSinceLastLookedForCriminals = CTimer::m_snTimeInMilliseconds + 30000;
    m_pLastCriminalPedLookedFor = pCriminalPed;
#endif
}

bool CTaskComplexWanderCop::ShouldPursuePlayer(CCopPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<bool, 0x66B160, CTaskComplexWanderCop*, CPed*>(this, pPed);
#else
    CWanted* pWantedPlayer = FindPlayerWanted(-1);
    if (pWantedPlayer->m_nWantedLevel > 0)
    {
        if (!m_pSubTask || m_pSubTask->GetId() != TASK_COMPLEX_POLICE_PURSUIT)
        {
            if (pWantedPlayer->CanCopJoinPursuit(pPed))
            {
                return true;
            }
        }
    }
    return false;
#endif
}
