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
CTaskSimpleFightingControl::CTaskSimpleFightingControl(CEntity* entityToFight, float fAngle, float fRange) :
    CTaskSimple(),
    m_bIsFinished{ false },
    m_nComboSet{ 0 },
    m_nNextAttackTime{ 0 },
    m_nBlockCounter{ 0 },
    m_fAttackFreq{ 1.0f },
    m_TargetEntity{ entityToFight },
    m_fAttackAngle{ fAngle },
    m_fAttackRange{ fRange }
{
    assert(entityToFight);
    CEntity::SafeRegisterRef(m_TargetEntity);
}

// 0x61DCA0
CTaskSimpleFightingControl::~CTaskSimpleFightingControl() {
    CEntity::SafeCleanUpRef(m_TargetEntity);
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
