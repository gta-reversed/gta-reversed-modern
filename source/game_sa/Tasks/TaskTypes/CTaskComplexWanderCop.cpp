#include "StdInc.h"

CTaskComplexWanderCop* CTaskComplexWanderCop::Constructor(int moveState, unsigned char dir)
{
    return plugin::CallMethodAndReturn<CTaskComplexWanderCop*, 0x460C80, CTaskComplexWanderCop*, int, unsigned char>(this, moveState, dir);
}

CTask* CTaskComplexWanderCop::CreateNextSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674860, CTaskComplexWander*, CPed*>(this, ped);
#else
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
#endif
}

CTask* CTaskComplexWanderCop::CreateFirstSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674750, CTaskComplexWander*, CPed*>(this, ped);
#else
    CCopPed* pPed = (CCopPed*)ped;
    if (pPed->m_nPedType != PED_TYPE_COP)
    {
        return CTaskComplexWander::CreateFirstSubTask(pPed);
    }
    if (pPed->m_bDontPursuit)
    {
        auto pTaskSimpleStandStill = (CTaskSimpleStandStill*)CTask::operator new(32);
        if (pTaskSimpleStandStill)
        {
            pTaskSimpleStandStill->Constructor(100000, 1, 0, 8.0);
            return pTaskSimpleStandStill;
        }
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
#endif
}

CTask* CTaskComplexWanderCop::ControlSubTask(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return plugin::CallMethodAndReturn<CTask*, 0x674D80, CTaskComplexWander*, CPed*>(this, ped);
#else
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
#endif
}

void CTaskComplexWanderCop::ScanForStuff(CPed* ped)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    return ((void(__thiscall*)(CTaskComplex*, CPed*))plugin::GetVMT(this, 12))(this, ped);
#else
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
#endif
}

void CTaskComplexWanderCop::LookForCarAlarms(CCopPed* pPed)
{
#ifdef USE_DEFAULT_FUNCTIONS 
    plugin::CallMethod<0x66B1B0, CTaskComplexWanderCop*, CPed*>(this, pPed);
#else
    CVehicle* pPlayerVehicle = FindPlayerVehicle(-1, 0);
    if (pPlayerVehicle && !pPlayerVehicle->m_nVehicleClass)
    {
        short alaramState = pPlayerVehicle->m_nAlarmState;
        if (alaramState)
        {
            if (alaramState != -1 && pPlayerVehicle->m_nStatus != STATUS_WRECKED)
            {
                CVector* pPedPos = &pPed->m_placement.m_vPosn;
                CMatrixLink* pPedMatrix = pPed->m_matrix;
                if (pPedMatrix)
                {
                    pPedPos = &pPedMatrix->pos;
                }

                CVector* pVehiclePos = &pPlayerVehicle->m_placement.m_vPosn;
                CMatrixLink* pVehicleMatrix = pPlayerVehicle->m_matrix;
                if (pVehicleMatrix)
                {
                    pVehiclePos = &pVehicleMatrix->pos;
                }

                float fX = pVehiclePos->x - pPedPos->x;
                float fY = pVehiclePos->y - pPedPos->y;
                float fZ = pVehiclePos->z - pPedPos->z;
                float result = fY * fY + fX * fX + fZ * fZ;
                if (result > 400.0f)
                {
                    FindPlayerPed(-1)->SetWantedLevelNoDrop(1);
                }
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
        if (pPlayerPed->m_pVehicle->m_nFlags.bIsLawEnforcer)
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
    CVector* pPedPos = &pPed->m_placement.m_vPosn;
    CMatrixLink* pPedMatrix = pPed->m_matrix;
    if (pPedMatrix)
    {
        pPedPos = &pPedMatrix->pos;
    }

    CPed* pCriminalPed = nullptr;
    for (int entityIndex = 0; entityIndex < 16; entityIndex++)
    {
        pCriminalPed = (CPed*)pPed->m_pIntelligence->m_entityScanner.m_apEntities[entityIndex];
        if (pCriminalPed)
        {
            int pedType = pCriminalPed->m_nPedType;
            if (pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10
                || pedType == PED_TYPE_CRIMINAL && pCriminalPed != m_pLastCriminalPedLookedFor)
            {
                CTask* pActiveTask = pCriminalPed->m_pIntelligence->m_TaskMgr.GetActiveTask();
                if (pActiveTask && pActiveTask->GetId() == GetId())
                {
                    CVector* pCriminalPos = &pCriminalPed->m_placement.m_vPosn;
                    CMatrixLink* pCriminalMatrix = pCriminalPed->m_matrix;
                    if (pCriminalMatrix)
                    {
                        pCriminalPos = &pCriminalMatrix->pos;
                    }
                    float fX = pCriminalPos->x - pPedPos->x;
                    float fY = pCriminalPos->y - pPedPos->y;
                    float fZ = pCriminalPos->z - pPedPos->z;
                    if (10.0 * 10.0 > fZ * fZ + fY * fY + fX * fX)
                    {
                        if (fZ * pPedPos->z + fY * pPedPos->y + fX * pPedPos->x > 0.0
                            && CWorld::GetIsLineOfSightClear(*pPedPos, *pCriminalPos, 1, 0, 0, 1, 0, 0, 0))
                        {
                            break;
                        }
                    }
                }
            }
        }
    }

    if (!pCriminalPed)
    {
        return;
    }

    CEventPedToChase eventPedToChase;
    eventPedToChase.Constructor(pCriminalPed);
    pPed->m_pIntelligence->m_eventGroup.Add(&eventPedToChase, 0);

    CEventPedToFlee eventPedToFlee;
    eventPedToFlee.Constructor(pPed);
    pCriminalPed->m_pIntelligence->m_eventGroup.Add(&eventPedToFlee, 0);

    // 30 seconds wait for next check
    m_nTimePassedSinceLastLookedForCriminals = CTimer::m_snTimeInMilliseconds + 30000;
    m_pLastCriminalPedLookedFor = pCriminalPed;

    eventPedToFlee.Destructor();
    eventPedToChase.Destructor();
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