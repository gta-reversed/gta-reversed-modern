#include "StdInc.h"
#include "TaskSimpleFightingControl.h"

void CTaskSimpleFightingControl::InjectHooks() {
    RH_ScopedClass(CTaskSimpleFightingControl);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x61DC10);
    RH_ScopedInstall(Destructor, 0x61DCA0);

    RH_ScopedInstall(CalcMoveCommand, 0x624B50, {.enabled = false, .locked = true});

    RH_ScopedVirtualInstall2(Clone, 0x622EB0);
    RH_ScopedVirtualInstall2(GetTaskType, 0x61DC90);
    RH_ScopedVirtualInstall2(MakeAbortable, 0x61DD00, {.enabled = false, .locked = true});
    RH_ScopedVirtualInstall2(ProcessPed, 0x62A0A0, {.enabled = false, .locked = true});
}

// 0x61DC10
CTaskSimpleFightingControl::CTaskSimpleFightingControl(CEntity* entityToFight, float angleRad, float dist) :
    m_entity{entityToFight},
    m_angleRad{angleRad},
    m_dist{dist}
{
    assert(entityToFight);

    CEntity::SafeRegisterRef(m_entity);
}

// NOTSA
CTaskSimpleFightingControl::CTaskSimpleFightingControl(const CTaskSimpleFightingControl& o) :
    CTaskSimpleFightingControl{o.m_entity, o.m_angleRad, o.m_dist}
{
}

// 0x61DCA0
CTaskSimpleFightingControl::~CTaskSimpleFightingControl() {
    CEntity::SafeCleanUpRef(m_entity);
}

// 0x624B50
int16 CTaskSimpleFightingControl::CalcMoveCommand(CPed* ped) {
    return plugin::CallMethodAndReturn<int16, 0x624B50, CTaskSimpleFightingControl*, CPed*>(this, ped);
}

// 0x61DD00
bool CTaskSimpleFightingControl::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x61DD00, CTaskSimpleFightingControl*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x62A0A0
bool CTaskSimpleFightingControl::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x62A0A0, CTaskSimpleFightingControl*, CPed*>(this, ped);
}
