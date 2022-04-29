#include "StdInc.h"

#include "TaskComplexKillPedOnFoot.h"

void CTaskComplexKillPedOnFoot::InjectHooks() {
    RH_ScopedClass(CTaskComplexKillPedOnFoot);
    RH_ScopedCategory("Tasks/TaskTypes");
    RH_ScopedInstall(Constructor, 0x620E30);
}

CTaskComplexKillPedOnFoot::CTaskComplexKillPedOnFoot(CPed* target, int32 time, int32 pedFlags, int32 delay, int32 chance, int8 a7) : CTaskComplex() {
    m_bit_1        = true;
    m_bit_2        = true;
    m_bit_3        = true;
    m_bit_4        = false;
    m_bit_5        = false;
    m_bit_6        = false;
    m_bit_7        = false;
    m_bit_8        = true; // maybe this is unused
    m_target       = target;
    m_pedFlags     = pedFlags;
    m_actionDelay  = delay;
    m_actionChance = chance;
    field_20       = a7;
    m_time         = time;

    CEntity::SafeRegisterRef(m_target);

    m_startTime = CTimer::GetTimeInMS();
}

CTaskComplexKillPedOnFoot::~CTaskComplexKillPedOnFoot()
{
    CEntity::SafeCleanUpRef(m_target);
}

CTaskComplexKillPedOnFoot* CTaskComplexKillPedOnFoot::Constructor(CPed* target, int32 time, int32 pedFlags, int32 delay, int32 chance, int8 a7) {
    this->CTaskComplexKillPedOnFoot::CTaskComplexKillPedOnFoot(target, time, pedFlags, delay, chance, a7);
    return this;
}

bool CTaskComplexKillPedOnFoot::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x625E40, CTaskComplexKillPedOnFoot*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}

CTask* CTaskComplexKillPedOnFoot::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62B150, CTaskComplexKillPedOnFoot*, CPed*>(this, ped);
}

CTask* CTaskComplexKillPedOnFoot::CreateFirstSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x62B490, CTaskComplexKillPedOnFoot*, CPed*>(this, ped);
}

CTask* CTaskComplexKillPedOnFoot::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x626260, CTaskComplexKillPedOnFoot*, CPed*>(this, ped);
}

CTask* CTaskComplexKillPedOnFoot::CreateSubTask(int32 taskId, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x625E70, CTaskComplexKillPedOnFoot*, int32, CPed*>(this, taskId, ped);
}
