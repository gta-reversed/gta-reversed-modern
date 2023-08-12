#include "StdInc.h"

#include "TaskComplexWanderCop.h"

#include "TaskSimpleStandStill.h"
#include "TaskComplexPolicePursuit.h"

void CTaskComplexWanderCop::InjectHooks() {
    RH_ScopedClass(CTaskComplexWanderCop);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x460C80);
    RH_ScopedVirtualInstall(CreateNextSubTask, 0x674860);
    RH_ScopedVirtualInstall(CreateFirstSubTask, 0x674750);
    RH_ScopedVirtualInstall(ControlSubTask, 0x674D80);
    RH_ScopedVirtualInstall(ScanForStuff, 0x6702B0);
    RH_ScopedInstall(LookForCarAlarms, 0x66B1B0);
    RH_ScopedInstall(LookForStolenCopCars, 0x66B290);
    RH_ScopedInstall(LookForCriminals, 0x66B300);
    RH_ScopedInstall(ShouldPursuePlayer, 0x66B160);
}
CTaskComplexWanderCop* CTaskComplexWanderCop::Constructor(eMoveState moveState, uint8 dir) { this->CTaskComplexWanderCop::CTaskComplexWanderCop(moveState, dir); return this; }
CTask* CTaskComplexWanderCop::CreateNextSubTask(CPed* ped) { return CreateNextSubTask_Reversed(ped); }
CTask* CTaskComplexWanderCop::CreateFirstSubTask(CPed* ped) { return CreateFirstSubTask_Reversed(ped); }
CTask* CTaskComplexWanderCop::ControlSubTask(CPed* ped) { return ControlSubTask_Reversed(ped); }
void CTaskComplexWanderCop::ScanForStuff(CPed* ped) { return ScanForStuff_Reversed(ped); }

// 0x460D80
CTaskComplexWanderCop::CTaskComplexWanderCop(eMoveState moveState, uint8 dir) : CTaskComplexWander(moveState, dir, true, 0.5f) {
    m_pGoToPointAndStandStillTask = nullptr;
    m_nTimePassedSinceLastLookedForCriminals = 0;
    m_nTimePassedSinceLastLookedForCarAlarmsAndStolenCopCars = 0;
    m_pLastCriminalPedLookedFor = nullptr;
}

// 0x460D60
CTaskComplexWanderCop::~CTaskComplexWanderCop() {
    delete m_pGoToPointAndStandStillTask;
}

// 0x674860
CTask* CTaskComplexWanderCop::CreateNextSubTask_Reversed(CPed* ped) {
    if (ped->m_nPedType != PED_TYPE_COP)
        return CTaskComplexWander::CreateNextSubTask(ped);

    if (ped->AsCop()->m_bDontPursuit)
        return nullptr;

    if (m_pSubTask->GetTaskType() == TASK_COMPLEX_POLICE_PURSUIT) {
        m_nSubTaskCreatedTimer.m_nStartTime = CTimer::GetTimeInMS();
        m_nSubTaskCreatedTimer.m_nInterval = 3000;
        m_nSubTaskCreatedTimer.m_bStarted = true;
        if (m_pGoToPointAndStandStillTask) {
            return m_pGoToPointAndStandStillTask->Clone();
        } else {
            return CTaskComplexWander::CreateFirstSubTask(ped);
        }
    }

    if (m_pGoToPointAndStandStillTask && m_pSubTask->GetTaskType() == m_pGoToPointAndStandStillTask->GetTaskType()) {
        return nullptr;
    }

    if (m_pGoToPointAndStandStillTask) {
        return m_pGoToPointAndStandStillTask->Clone();
    } else {
        return CTaskComplexWander::CreateNextSubTask(ped);
    }
}

// 0x674750
CTask* CTaskComplexWanderCop::CreateFirstSubTask_Reversed(CPed* ped) {
    if (ped->m_nPedType != PED_TYPE_COP)
        return CTaskComplexWander::CreateFirstSubTask(ped);

    if (ped->AsCop()->m_bDontPursuit) {
        return new CTaskSimpleStandStill(100'000, true, false, 8.0f);
    }

    if (!ShouldPursuePlayer(ped)) {
        if (m_pGoToPointAndStandStillTask) {
            return m_pGoToPointAndStandStillTask->Clone();
        }
        return CTaskComplexWander::CreateFirstSubTask(ped);
    }

    return new CTaskComplexPolicePursuit();
}

// 0x674D80
CTask* CTaskComplexWanderCop::ControlSubTask_Reversed(CPed* ped) {
    if (ped->m_nPedType != PED_TYPE_COP)
        return CTaskComplexWander::ControlSubTask(ped);

    if (!ShouldPursuePlayer(ped)) {
        if (m_pSubTask->GetTaskType() == TASK_COMPLEX_POLICE_PURSUIT || m_pGoToPointAndStandStillTask) {
            return m_pSubTask;
        }
        return CTaskComplexWander::ControlSubTask(ped);
    }

    if (m_nSubTaskCreatedTimer.m_bStarted && !m_nSubTaskCreatedTimer.IsOutOfTime() || !m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
        return m_pSubTask;
    }

    return new CTaskComplexPolicePursuit();
}

// 0x6702B0
void CTaskComplexWanderCop::ScanForStuff_Reversed(CPed* ped) {
    if (!m_nScanForStuffTimer.m_bStarted) {
        m_nScanForStuffTimer.m_nStartTime = CTimer::GetTimeInMS();
        m_nScanForStuffTimer.m_nInterval = 50;
        m_nScanForStuffTimer.m_bStarted = true;
    }

    if (GetTaskType() == TASK_COMPLEX_POLICE_PURSUIT || !m_nScanForStuffTimer.m_bStarted)
        return;

    if (m_nScanForStuffTimer.m_bStopped) {
        m_nScanForStuffTimer.m_nStartTime = CTimer::GetTimeInMS();
        m_nScanForStuffTimer.m_bStopped = false;
    }

    if (CTimer::GetTimeInMS() >= (m_nScanForStuffTimer.m_nStartTime + m_nScanForStuffTimer.m_nInterval)) {
        m_nScanForStuffTimer.m_nInterval = 50;
        m_nScanForStuffTimer.m_nStartTime = CTimer::GetTimeInMS();
        m_nScanForStuffTimer.m_bStarted = true;

        if (CTimer::GetTimeInMS() >= m_nTimePassedSinceLastLookedForCarAlarmsAndStolenCopCars) {
            LookForCarAlarms(ped);
            LookForStolenCopCars(ped);
        }

        if (CTimer::GetTimeInMS() >= m_nTimePassedSinceLastLookedForCriminals) {
            LookForCriminals(ped);
        }
    }
}

// 0x66B1B0
void CTaskComplexWanderCop::LookForCarAlarms(CPed* ped) {
    CVehicle* vehicle = FindPlayerVehicle();
    if (!vehicle || !vehicle->IsAutomobile())
        return;

    if (!vehicle->m_nAlarmState || vehicle->m_nAlarmState == -1 || vehicle->m_nStatus == STATUS_WRECKED)
        return;

    float distance = DistanceBetweenPointsSquared(ped->GetPosition(), vehicle->GetPosition());
    if (distance < sq(20.0f)) {
        FindPlayerPed()->SetWantedLevelNoDrop(1);
    }
}

// 0x66B290
void CTaskComplexWanderCop::LookForStolenCopCars(CPed* ped) {
    CPlayerPed* player = FindPlayerPed();

    CWanted* wanted = nullptr;
    if (player->m_pPlayerData) {
        wanted = player->m_pPlayerData->m_pWanted;
    }

    if (wanted && !wanted->m_nWantedLevel && player->m_pVehicle) {
        if (player->m_pVehicle->vehicleFlags.bIsLawEnforcer) {
            player->SetWantedLevelNoDrop(1);
        }
    }
}

// 0x66B300
void CTaskComplexWanderCop::LookForCriminals(CPed* ped) {
    CPed* criminalPed = nullptr;
    for (auto& entity : ped->GetIntelligence()->m_pedScanner.m_apEntities) {
        criminalPed = entity->AsPed();
        if (!criminalPed)
            continue;

        auto pedType = criminalPed->m_nPedType;
        if (pedType >= PED_TYPE_GANG1 && pedType <= PED_TYPE_GANG10 || pedType == PED_TYPE_CRIMINAL && criminalPed != m_pLastCriminalPedLookedFor) {
            CTask* activeTask = criminalPed->GetTaskManager().GetActiveTask();
            if (activeTask && activeTask->GetTaskType() == GetTaskType()) {
                const auto& criminalPos = criminalPed->GetPosition();
                const auto& pedPos = ped->GetPosition();
                CVector distance = criminalPos - pedPos;
                if (distance.SquaredMagnitude() < sq(10.0f)) {
                    const float dot = DotProduct(distance, ped->GetForward());
                    if (dot > 0.0f && CWorld::GetIsLineOfSightClear(pedPos, criminalPos, true, false, false, true, false, false, false))
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
    m_nTimePassedSinceLastLookedForCriminals = CTimer::GetTimeInMS() + 30'000;
    m_pLastCriminalPedLookedFor = criminalPed;
}

// 0x66B160
bool CTaskComplexWanderCop::ShouldPursuePlayer(CPed* ped) {
    CWanted* wanted = FindPlayerWanted();
    if (wanted->m_nWantedLevel <= 0)
        return false;

    if (m_pSubTask && m_pSubTask->GetTaskType() == TASK_COMPLEX_POLICE_PURSUIT)
        return false;

    if (wanted->CanCopJoinPursuit(ped->AsCop())) {
        return true;
    }
    return false;
}
