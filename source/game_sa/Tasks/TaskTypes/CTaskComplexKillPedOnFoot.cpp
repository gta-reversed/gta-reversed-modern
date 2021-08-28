#include "StdInc.h"

void CTaskComplexKillPedOnFoot::InjectHooks()
{
    ReversibleHooks::Install(0x620E30, &CTaskComplexKillPedOnFoot::Constructor);
}

CTaskComplexKillPedOnFoot::CTaskComplexKillPedOnFoot(CPed* target, std::int32_t time, std::uint32_t pedFlags, std::int32_t delay, std::int32_t chance, std::int8_t a7)
{
    m_bit_1 = true;
    m_bit_2 = true;
    m_bit_3 = true;
    m_bit_4 = false;
    m_bit_5 = false;
    m_bit_6 = false;
    m_bit_7 = false;
    m_bit_8 = true; // maybe this is unused
    m_target = target;
    m_pedFlags = pedFlags;
    m_actionDelay = delay;
    m_actionChance = chance;
    field_20 = a7;
    m_time = time;
    if (m_target)
        m_target->RegisterReference(reinterpret_cast<CEntity**>(&m_target));
    m_startTime = CTimer::m_snTimeInMilliseconds;
}

CTaskComplexKillPedOnFoot::~CTaskComplexKillPedOnFoot()
{
    if (m_target)
        m_target->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_target));
}

CTaskComplexKillPedOnFoot* CTaskComplexKillPedOnFoot::Constructor(CPed* target, std::int32_t time, std::uint32_t pedFlags, std::int32_t delay, std::int32_t chance, std::int8_t a7)
{
    this->CTaskComplexKillPedOnFoot::CTaskComplexKillPedOnFoot(target, time, pedFlags, delay, chance, a7);
    return this;
}

bool CTaskComplexKillPedOnFoot::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event)
{
    return plugin::CallMethodAndReturn<bool, 0x625E40, CTaskComplexKillPedOnFoot*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexKillPedOnFoot::CreateNextSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x62B150, CTaskComplexKillPedOnFoot*, CPed*>(this, ped);
}

CTask* CTaskComplexKillPedOnFoot::CreateFirstSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x62B490, CTaskComplexKillPedOnFoot*, CPed*>(this, ped);
}

CTask* CTaskComplexKillPedOnFoot::ControlSubTask(CPed* ped)
{
    return plugin::CallMethodAndReturn<CTask*, 0x626260, CTaskComplexKillPedOnFoot*, CPed*>(this, ped);
}

void* CTaskComplexKillPedOnFoot::CreateSubTask(std::int32_t taskId, CPed* ped)
{
    return plugin::CallMethodAndReturn<void*, 0x625E70, CTaskComplexKillPedOnFoot*, std::int32_t, CPed*>(this, taskId, ped);
}

