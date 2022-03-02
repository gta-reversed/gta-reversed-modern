#include "StdInc.h"
#include "TaskSimpleCreateCarAndGetIn.h"
#include "PedPlacement.h"
#include "TaskSimpleStandStill.h"
#include "CarCtrl.h"
#include "TaskSimpleCarSetPedInAsDriver.h"

void CTaskSimpleCreateCarAndGetIn::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCreateCarAndGetIn);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x6493E0);
    RH_ScopedInstall(Destructor, 0x64CEA0);

    RH_ScopedInstall(Clone_Reversed, 0x64A410);
    RH_ScopedInstall(GetTaskType_Reversed, 0x649430);
    RH_ScopedInstall(MakeAbortable_Reversed, 0x649440);
    RH_ScopedInstall(ProcessPed_Reversed, 0x64CF40);
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
        CleanupCreatedVehicle();
    }
}

// 0x649440
bool CTaskSimpleCreateCarAndGetIn::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return true;
}

// 0x64CF40
bool CTaskSimpleCreateCarAndGetIn::ProcessPed(CPed* ped) {
    CVector nodePos{};
    if (!ThePaths.FindNodeCoorsForScript(nodePos, ThePaths.FindNodeClosestToCoors(m_pos))) {
        if (!m_waitTimeSet) {
            m_timeMs = CTimer::GetTimeInMS();
            m_waitTime = 2000;
            m_waitTimeSet = true;
        }
        if (m_resetWaitTime) {
            m_timeMs = CTimer::GetTimeInMS();
            m_resetWaitTime = false;
        }
        return CTimer::GetTimeInMS() >= m_timeMs + m_waitTime;
    }

    m_vehCreationPos = nodePos;
    m_waitTimeSet = false;

    // If vehicle is not created yet lets check if it can be created at all
    if (!m_createdVeh) {
        // Make sure position isn't visible by camera
        if (TheCamera.IsSphereVisible({ m_vehCreationPos, 3.f })) {
            return true;
        }

        // Also make sure peds position isn't visible by the camera
        if (TheCamera.IsSphereVisible({ ped->GetPosition(), ped->GetColModel()->GetBoundRadius() })) {
            return true;
        }

        // And make sure the ped isn't stuck or something
        if (!CPedPlacement::IsPositionClearForPed(ped->GetPosition(), 3.f, -1, 0, true, true, true)) {
            return true;
        }
    }

    // Weird..
    {
        CTaskSimpleStandStill task{ 0, 0, 0, 8.f };
        task.ProcessPed(ped);
    }

    // Make sure model is loaded
    if (!CStreaming::IsModelLoaded(m_model)) {
        CStreaming::RequestModel(m_model, STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED);
        return false;
    }

    // Create vehicle and set ped in as driver
    if (!m_createdVeh) {
        m_createdVeh = CCarCtrl::CreateCarForScript(m_model, m_vehCreationPos, true);

        CTaskSimpleCarSetPedInAsDriver task{ m_createdVeh, nullptr };
        task.ProcessPed(ped);
    }
 
    if (!m_createdVeh->IsStatic()) {
        return false;
    }

    // Veh is static now, so remove it, and signal task finish
    CleanupCreatedVehicle();
    return true;
}

void CTaskSimpleCreateCarAndGetIn::CleanupCreatedVehicle() {
    CTheScripts::CleanUpThisVehicle(m_createdVeh);
    CTheScripts::MissionCleanUp.RemoveEntityFromList(GetVehiclePool()->GetRef(m_createdVeh), MISSION_CLEANUP_ENTITY_TYPE_VEHICLE);
    m_createdVeh = nullptr;
}
