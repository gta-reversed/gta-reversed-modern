#include "StdInc.h"
#include "TaskSimpleCreateCarAndGetIn.h"

void CTaskSimpleCreateCarAndGetIn::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCreateCarAndGetIn);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6493E0);
    RH_ScopedInstall(Destructor, 0x64CEA0);

    RH_ScopedInstall(Clone_Reversed, 0x64A410);
    RH_ScopedInstall(GetTaskType_Reversed, 0x649430);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x649440);
    // RH_ScopedInstall(ProcessPed_Reversed, 0x64CF40);
}

// NOTSA
CTaskSimpleCreateCarAndGetIn::CTaskSimpleCreateCarAndGetIn(const CTaskSimpleCreateCarAndGetIn& o) :
    m_model{o.m_model},
    m_pos{o.m_pos}
{
}

// 0x6493E0
CTaskSimpleCreateCarAndGetIn::CTaskSimpleCreateCarAndGetIn(CVector const& pos, int32 model) :
    m_pos{pos},
    m_model{model}
{
}

// 0x64CEA0
CTaskSimpleCreateCarAndGetIn::~CTaskSimpleCreateCarAndGetIn() {
    if (m_createdVeh) {
        CTheScripts::CleanUpThisVehicle(m_createdVeh);
        CTheScripts::MissionCleanUp.RemoveEntityFromList(GetVehiclePool()->GetRef(m_createdVeh), MISSION_CLEANUP_ENTITY_TYPE_VEHICLE);
    }
}

// 0x64A410
CTask* CTaskSimpleCreateCarAndGetIn::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x64A410, CTaskSimpleCreateCarAndGetIn*>(this);
}

// 0x649440
bool CTaskSimpleCreateCarAndGetIn::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return true;
}

// 0x64CF40
bool CTaskSimpleCreateCarAndGetIn::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x64CF40, CTaskSimpleCreateCarAndGetIn*, CPed*>(this, ped);
}
