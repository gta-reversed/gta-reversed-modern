#include "StdInc.h"

void CTaskComplexUseSwatRope::InjectHooks()
{
    ReversibleHooks::Install("CTaskComplexUseSwatRope", "Constructor", 0x659470, &CTaskComplexUseSwatRope::Constructor);
    ReversibleHooks::Install("CTaskComplexUseSwatRope", "CreateSubTask", 0x659620, &CTaskComplexUseSwatRope::CreateSubTask);
    //VTABLE
    ReversibleHooks::Install("CTaskComplexUseSwatRope", "Clone", 0x659C30, &CTaskComplexUseSwatRope::Clone_Reversed);
    ReversibleHooks::Install("CTaskComplexUseSwatRope", "CreateFirstSubTask", 0x65A440, &CTaskComplexUseSwatRope::CreateFirstSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexUseSwatRope", "CreateNextSubTask", 0x65A3E0, &CTaskComplexUseSwatRope::CreateNextSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexUseSwatRope", "ControlSubTask", 0x65A460, &CTaskComplexUseSwatRope::ControlSubTask_Reversed);
    ReversibleHooks::Install("CTaskComplexUseSwatRope", "MakeAbortable", 0x659530, &CTaskComplexUseSwatRope::MakeAbortable_Reversed);
}

CTaskComplexUseSwatRope* CTaskComplexUseSwatRope::Constructor(unsigned int ropeId, CHeli* pHeli)
{
    this->CTaskComplexUseSwatRope::CTaskComplexUseSwatRope(ropeId, pHeli);
    return this;
}

// 0x659470
CTaskComplexUseSwatRope::CTaskComplexUseSwatRope(unsigned int ropeId, CHeli* pHeli)
{
    m_nRopeId = ropeId;
    m_pHeli = pHeli;
    m_fCoorAlongRope = 0.0F;
    m_bIsOnHeli = true;

    m_pHeli->RegisterReference(reinterpret_cast<CEntity * *>(&m_pHeli));
}

CTaskComplexUseSwatRope::CTaskComplexUseSwatRope(unsigned int ropeId)
{
    m_nRopeId = ropeId;
    m_pHeli = nullptr;
    m_fCoorAlongRope = 0.0F;
    m_bIsOnHeli = false;
}

// 0x65A3C0
CTaskComplexUseSwatRope::~CTaskComplexUseSwatRope()
{
    if (m_bIsOnHeli)
        m_pHeli->CleanUpOldReference(reinterpret_cast<CEntity * *>(&m_pHeli));
}

// 0x659C30
CTask* CTaskComplexUseSwatRope::Clone()
{
    return Clone_Reversed();
}

// 0x659530
bool CTaskComplexUseSwatRope::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    return MakeAbortable_Reversed(ped, priority, _event);
}

// 0x65A3E0
CTask* CTaskComplexUseSwatRope::CreateNextSubTask(CPed* ped)
{
    return CreateNextSubTask_Reversed(ped);
}

// 0x65A440
CTask* CTaskComplexUseSwatRope::CreateFirstSubTask(CPed* ped)
{
    return CreateFirstSubTask_Reversed(ped);
}

// 0x65A460
CTask* CTaskComplexUseSwatRope::ControlSubTask(CPed* ped)
{
    return ControlSubTask_Reversed(ped);
}

CTask* CTaskComplexUseSwatRope::Clone_Reversed()
{
    if (m_bIsOnHeli)
        return new CTaskComplexUseSwatRope(m_nRopeId, m_pHeli);
    else
        return new CTaskComplexUseSwatRope(m_nRopeId);
}

bool CTaskComplexUseSwatRope::MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event)
{
    eEventType eventType = _event->GetEventType();

    if ((priority == ABORT_PRIORITY_IMMEDIATE
        || eventType == EVENT_DEATH
        || eventType == EVENT_HEALTH_REALLY_LOW
        || eventType == EVENT_ON_FIRE
        || eventType == EVENT_IN_WATER
        || eventType == EVENT_WATER_CANNON
        || eventType == EVENT_VEHICLE_DAMAGE_WEAPON
        || eventType == EVENT_VEHICLE_DAMAGE_COLLISION
        || ped->m_fHealth <= 20.0F
        )
        && m_pSubTask->MakeAbortable(ped, priority, _event)
        )
    {
        ped->bIsStanding = false;
        ped->m_bUsesCollision = true;
        ped->m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
        return true;
    }
    else
        return false;
}

CTask* CTaskComplexUseSwatRope::CreateNextSubTask_Reversed(CPed* ped)
{
    eTaskType subTaskType = m_pSubTask->GetId();

    if (subTaskType == TASK_NONE || subTaskType == TASK_SIMPLE_PAUSE)
        return CreateSubTask(TASK_FINISHED, ped);

    if (subTaskType == TASK_SIMPLE_ABSEIL)
        return CreateSubTask(TASK_SIMPLE_PAUSE, ped);

    return nullptr;
}

CTask* CTaskComplexUseSwatRope::CreateFirstSubTask_Reversed(CPed* ped)
{
    return CreateSubTask(TASK_SIMPLE_ABSEIL, ped);
}

CTask* CTaskComplexUseSwatRope::ControlSubTask_Reversed(CPed* ped)
{
    if (m_bIsOnHeli)
        if (!m_pHeli
            || m_pHeli->m_autoPilot.m_nCarMission == MISSION_CRASH_HELI_AND_BURN
            || m_pHeli->m_fHealth <= 0.0F
            )
            if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0))
            {
                ped->bIsStanding = false;
                ped->m_bUsesCollision = true;
                ped->m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
                return nullptr;
            }

    eTaskType subTaskType = m_pSubTask->GetId();

    if (subTaskType == TASK_SIMPLE_PAUSE || subTaskType == TASK_SIMPLE_ABSEIL)
    {
        CVector groundCoord = ped->GetPosition();
        CPedPlacement::FindZCoorForPed(&groundCoord);
        if (ped->GetPosition().z - 2.0F < groundCoord.z && m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, 0))
            return CreateSubTask(TASK_NONE, ped);

        m_fCoorAlongRope += CTimer::ms_fTimeStep * 0.003F;
        CVector posn;
        if (CRopes::FindCoorsAlongRope(m_nRopeId, m_fCoorAlongRope, &posn, 0))
        {
            ped->SetPosn(posn);
            ped->m_fAimingRotation = ped->m_fCurrentRotation - CTimer::ms_fTimeStep * 0.05F;
            ped->m_vecMoveSpeed.z = -0.03f;
            ped->Say(177, 0, 1.0F, false, false, false);
        }
    }

    return m_pSubTask;
}

// 0x659620
CTask* CTaskComplexUseSwatRope::CreateSubTask(eTaskType taskType, CPed* ped)
{
    switch (taskType)
    {
    case TASK_SIMPLE_ABSEIL:
        return new CTaskSimpleAbseil();
    case TASK_SIMPLE_PAUSE:
        return new CTaskSimplePause(100000);
    case TASK_NONE:
        return new CTaskSimpleNone();
    case TASK_FINISHED:
        ped->m_bUsesCollision = true;
        ped->m_vecMoveSpeed.Set(0.0F, 0.0F, 0.0F);
    default:
        return nullptr;
    }
}



