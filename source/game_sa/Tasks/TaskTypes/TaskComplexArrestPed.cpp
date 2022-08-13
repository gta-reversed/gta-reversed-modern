#include "StdInc.h"

#include "extensions/utility.hpp"

#include "TaskComplexArrestPed.h"
#include "TaskComplexFallAndGetUp.h"
#include "TaskSimpleWaitUntilPedIsOutCar.h"
// #include "TaskSimpleArrestPed.h"
#include "TaskComplexKillPedOnFoot.h"
// #include "TaskComplexDestroyCar.h"
// #include "TaskComplexSeekEntity.h"
// #include "TaskComplexDragPedFromCar.h"
// #include "TaskComplexOpenDriverDoor.h"
// #include "TaskComplexOpenPassengerDoor.h"

#include "eTargetDoor.h"

void CTaskComplexArrestPed::InjectHooks() {
    RH_ScopedClass(CTaskComplexArrestPed);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x68B990);
    RH_ScopedInstall(Destructor, 0x68BA00);
    RH_ScopedInstall(MakeAbortable, 0x68BA60);
    // ~+ RH_ScopedInstall(CreateNextSubTask, 0x690220);
    RH_ScopedInstall(CreateFirstSubTask, 0x6907A0);
    RH_ScopedInstall(ControlSubTask, 0x68D350);
    // + RH_ScopedInstall(CreateSubTask, 0x68CF80);
}

// 0x68B990
CTaskComplexArrestPed::CTaskComplexArrestPed(CPed* ped) : CTaskComplex() {
    m_PedToArrest = ped;
    m_Vehicle = nullptr;
    CEntity::SafeRegisterRef(m_PedToArrest);
}

// 0x68BA00
CTaskComplexArrestPed::~CTaskComplexArrestPed() {
    CEntity::SafeCleanUpRef(m_PedToArrest);
}

// 0x68BA60
bool CTaskComplexArrestPed::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

// 0x690220
CTask* CTaskComplexArrestPed::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690220, CTaskComplexArrestPed*, CPed*>(this, ped);

    if (!m_PedToArrest)
        return CreateSubTask(TASK_FINISHED, ped);

    auto taskType = m_pSubTask->GetTaskType();
    if (m_PedToArrest->bIsBeingArrested && taskType != TASK_SIMPLE_ARREST_PED) {
        /*
        if (taskType == TASK_COMPLEX_SEEK_ENTITY && ((int)this->m_pSubTask[9].__vftable & 4) != 0) {
            return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);
        } else {
            return CreateSubTask(TASK_COMPLEX_SEEK_ENTITY, ped);
        }
        */
    }

    if (taskType > TASK_COMPLEX_SEEK_ENTITY) {
        auto v27 = taskType - 1000;
        if (v27) {
            auto v28 = v27 - 3;
            if (v28 && v28 != 97)
                return nullptr;
        } else {
            if (m_PedToArrest->m_fHealth <= 0.0f)
                return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);

            auto v15 = m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_FALL_AND_GET_UP);
            if (v15 && static_cast<CTaskComplexFallAndGetUp*>(v15)->IsFalling()) {
                auto a1 = m_PedToArrest->GetPosition() - ped->GetPosition();
                auto v36 = std::fabs(a1.z);
                a1.z = 0.0f;
                if (v36 > 2.0f || sq(3.0f) < a1.SquaredMagnitude()) {
                    return CreateSubTask(TASK_COMPLEX_SEEK_ENTITY, ped);
                }
                static_cast<CTaskComplexFallAndGetUp*>(v15)->SetDownTime(100'000);
                return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);
            }

            if (ped->m_nPedType == PED_TYPE_COP)
                return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);

            if (!m_PedToArrest->IsPlayer())
                return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);

            auto wanted = m_PedToArrest->m_pPlayerData ? m_PedToArrest->m_pPlayerData->m_pWanted : nullptr;
            if (!wanted->m_nCopsInPursuit) // C* missing check for nullptr
                return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
        }
        return CreateSubTask(TASK_FINISHED, ped);
    }

    switch (taskType) {
    case TASK_COMPLEX_SEEK_ENTITY: { // TASK_COMPLEX_SEEK_ENTITY ~ == TASK_COMPLEX_DRAG_PED_FROM_CAR almost copypasta
        auto v15 = m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_FALL_AND_GET_UP);
        /*
        if (!v15 || !static_cast<CTaskComplexFallAndGetUp*>(v15)->IsFalling() || ((int)this->m_pSubTask[9].__vftable & 4) == 0) {
            return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
        }
        */
        auto a1 = m_PedToArrest->GetPosition() - ped->GetPosition();
        auto v26 = std::fabs(a1.z);
        a1.z = 0.0f;
        if (v26 <= 2.0f && sq(3.0f) >= a1.SquaredMagnitude()) {
            static_cast<CTaskComplexFallAndGetUp*>(v15)->SetDownTime(100'000);
            return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);
        }
        return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
    }
    case TASK_COMPLEX_DRAG_PED_FROM_CAR: {
        auto v15 = m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_FALL_AND_GET_UP);
        /*
        if (!v15 || !static_cast<CTaskComplexFallAndGetUp*>(v15)->IsFalling() || ((int)this->m_pSubTask[2].__vftable & 4) != 0) {
            return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
        }
        */
        auto a1 = m_PedToArrest->GetPosition() - ped->GetPosition();
        auto v26 = std::fabs(a1.z);
        a1.z = 0.0f;
        if (v26 <= 2.0f && sq(3.0f) >= a1.SquaredMagnitude()) {
            static_cast<CTaskComplexFallAndGetUp*>(v15)->SetDownTime(100'000);
            return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);
        }
        return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
    }
    case TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR: { // TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR == TASK_COMPLEX_CAR_OPEN_PASSENGER_DOOR copypasta
        /*
        if (((int)this->m_pSubTask[2].__vftable & 2) != 0) {
            if (m_PedToArrest->m_pVehicle) {
                if (!m_PedToArrest->m_pVehicle->CanPedOpenLocks(ped)) {
                    m_Vehicle = m_PedToArrest->m_pVehicle;
                }
            }
        }
        */

        if (!m_PedToArrest->IsAlive())
            return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);

        /*
        if (!m_PedToArrest->bInVehicle || ((int)this->m_pSubTask[2].__vftable & 2) != 0)
            return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
        */

        auto task = m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR);
        if (task) {
            return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
        } else {
            return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);
        }
    }
    case TASK_COMPLEX_CAR_OPEN_PASSENGER_DOOR: {
        /*
        if (((int)this->m_pSubTask[2].__vftable & 2) != 0) {
            if (m_PedToArrest->m_pVehicle) {
                if (!m_PedToArrest->m_pVehicle->CanPedOpenLocks(ped)) {
                    m_Vehicle = m_PedToArrest->m_pVehicle;
                }
            }
        }
        */

        if (!m_PedToArrest->IsAlive())
            return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);

        /*
        if (!m_PedToArrest->bInVehicle || ((int)this->m_pSubTask[2].__vftable & 2) != 0)
            return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
        */

        auto task = m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR);
        if (task) {
            return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
        } else {
            return CreateSubTask(TASK_SIMPLE_ARREST_PED, ped);
        }
    }
    case TASK_SIMPLE_WAIT_UNTIL_PED_OUT_CAR:
        return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
    default:
        return nullptr;
    }
}

void MakeSurePedHasWeaponInHand(CPed* ped) {
    // Make sure ped has an actual weapon in their hand
    if (!ped->GetActiveWeapon().IsTypeMelee())
        return;

    if (ped->DoWeHaveWeaponAvailable(WEAPON_SHOTGUN)) { // Use shotgun (if available)
        ped->SetCurrentWeapon(WEAPON_SHOTGUN);
        return;
    }

    // Otherwise a pistol
    if (!ped->DoWeHaveWeaponAvailable(WEAPON_PISTOL)) { // Make sure they have one
        ped->GiveWeapon(WEAPON_PISTOL, 10, 0);
    }
    ped->SetCurrentWeapon(WEAPON_PISTOL);
}

CTask* CTaskComplexArrestPed::CreateFirstSubTask(CPed* ped) {
    if (!m_PedToArrest) {
        return nullptr;
    }

    m_bSubTaskNeedsToBeCreated = false;

    if (!m_PedToArrest->bInVehicle) {
        return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
    }

    if (m_PedToArrest->m_pVehicle->IsBike() || m_PedToArrest->m_pVehicle->IsSubQuad()) { // Just drag ped from a bike/quad
        return CreateSubTask(TASK_COMPLEX_DRAG_PED_FROM_CAR, ped);
    }

    if (m_PedToArrest->m_pVehicle->IsSubBoat()) { // If they're in a boat, just destroy it
        MakeSurePedHasWeaponInHand(ped);
        return CreateSubTask(TASK_COMPLEX_DESTROY_CAR, ped);
    } else {
        if (m_PedToArrest->m_pVehicle->IsUpsideDown() || m_PedToArrest->m_pVehicle->IsOnItsSide()) {
            return CreateSubTask(TASK_COMPLEX_DESTROY_CAR, ped);
        }
        return CreateSubTask(TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR, ped);
    }
}

CTask* CTaskComplexArrestPed::ControlSubTask(CPed* ped) {
    // Automatically make ped say something on function return
    const notsa::AutoCallOnDestruct Have_A_Nice_Day_Sir{
        [this, ped] {
            if (m_PedToArrest && m_PedToArrest->IsPlayer()) {
                if (FindPlayerWanted()->m_nCopsInPursuit == 1) {
                    ped->Say(199);
                }
            }
        }
    };

    // Tries to abort current sub-task and replace it with `taskType`.
    const auto TryReplaceSubTask = [this, ped](auto taskType) {
        // Inverted `if` and got rid of `taskType == TASK_NONE` (in which case `m_pSubTask` was returned always)
        if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
            return CreateSubTask(taskType, ped);
        } else {
            return m_pSubTask;
        }
    };

    const auto DoDestroyCarTask = [&] {
        MakeSurePedHasWeaponInHand(ped);
        return TryReplaceSubTask(TASK_COMPLEX_DESTROY_CAR);
    };

    // 0x68D370, 0x68D37F
    if (!m_PedToArrest || m_PedToArrest->m_fHealth <= 0.f) {
        return TryReplaceSubTask(TASK_FINISHED);
    }

    // 0x68D39F
    if (m_bSubTaskNeedsToBeCreated) {
        if (m_pSubTask->MakeAbortable(ped, ABORT_PRIORITY_URGENT, nullptr)) {
            m_pSubTask->AsComplex()->CreateFirstSubTask(ped);
        }
        return m_pSubTask;
    }

    // 0x68D3CB
    if (m_PedToArrest->bIsBeingArrested) {
        switch (m_pSubTask->GetTaskType()) {
        case TASK_SIMPLE_ARREST_PED:
        case TASK_COMPLEX_SEEK_ENTITY:
            break;
        default:
            return TryReplaceSubTask(TASK_COMPLEX_SEEK_ENTITY);
        }
    }

    switch (m_pSubTask->GetTaskType()) {
    case TASK_COMPLEX_DRAG_PED_FROM_CAR: // 0x68D49D
    case TASK_COMPLEX_DESTROY_CAR: { // 0x68D5F6
        if (!m_PedToArrest->bInVehicle) { // If not in vehicle anymore, try to kill them
            return TryReplaceSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT);
        }
        break;
    }
    case TASK_COMPLEX_KILL_PED_ON_FOOT: { // 0x68D626
        // See if ped is falling, and is close enough
        if (const auto task = static_cast<CTaskComplexFallAndGetUp*>(m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_FALL_AND_GET_UP))) {
            if (task->IsFalling()) {
                const auto dir = ped->GetPosition() - m_PedToArrest->GetPosition();
                if (std::abs(dir.z) <= 2.f && dir.SquaredMagnitude() <= sq(3.0f)) {
                    task->SetDownTime(100'000);
                    return TryReplaceSubTask(TASK_SIMPLE_ARREST_PED);
                }
            }

            // Getting up already/not close enough
            return TryReplaceSubTask(TASK_COMPLEX_SEEK_ENTITY);
        }

        if (!m_PedToArrest->bInVehicle || !m_PedToArrest->m_pVehicle) {
            break;
        }

        // Ped has gotten into a vehicle, we need a different task!

        if (   m_PedToArrest->m_pVehicle->IsBoat()
            || m_PedToArrest->m_pVehicle->IsSubPlane()
            || m_PedToArrest->m_pVehicle->IsSubHeli()
        ) {
            return DoDestroyCarTask();
        }

        if (!ped->GetActiveWeapon().IsTypeMelee()) {
            if (!FindPlayerWanted()->IsClosestCop(ped, 2)) {
                return DoDestroyCarTask();
            }
        }

        if (m_PedToArrest->m_pVehicle != m_Vehicle) {
            if (m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR)) {
                if (m_PedToArrest->m_pVehicle->IsBike() || m_PedToArrest->m_pVehicle->IsSubQuad()) {
                    return TryReplaceSubTask(TASK_COMPLEX_DRAG_PED_FROM_CAR);
                }

                if (!m_PedToArrest->m_pVehicle->IsUpsideDown() && !m_PedToArrest->m_pVehicle->IsOnItsSide()) {
                    return TryReplaceSubTask(TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR);
                }

                return DoDestroyCarTask();
            }
        }

        break;
    }
    case TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR: { // 0x68D424
        if (m_PedToArrest->bInVehicle) {
            // Maybe wait until ped gets out of the car..
            if (const auto task = m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR)) {
                if (ped->IsEntityInRange(m_PedToArrest, 5.f)) {
                    return TryReplaceSubTask(TASK_SIMPLE_WAIT_UNTIL_PED_OUT_CAR);
                }
            }

            // Ped can't open driver door, but we can open front right door?
            if (!m_PedToArrest->m_pVehicle->IsRoomForPedToLeaveCar(TARGET_DOOR_DRIVER, nullptr)) {
                if (m_PedToArrest->m_pVehicle->IsRoomForPedToLeaveCar(TARGET_DOOR_FRONT_RIGHT, nullptr)) {
                    return TryReplaceSubTask(TASK_COMPLEX_CAR_OPEN_PASSENGER_DOOR);
                }
            }
        }

        // Ped not in vehicle any more vehicle, just kill 'em
        return TryReplaceSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT);
    }
    case TASK_COMPLEX_CAR_OPEN_PASSENGER_DOOR: { // 0x68D510
        // Pretty much the copy of the above, with minor changes (See change 1,2)

        if (m_PedToArrest->bInVehicle) {
            // Maybe wait until ped gets out of the car..
            if (const auto task = m_PedToArrest->GetTaskManager().FindActiveTaskByType(TASK_COMPLEX_LEAVE_CAR)) {
                if (ped->IsEntityInRange(m_PedToArrest, 5.f)) {
                    return TryReplaceSubTask(TASK_SIMPLE_WAIT_UNTIL_PED_OUT_CAR);
                }
            }

            // Ped can't open passenger door, but driver door can be opened by us? - Change 1
            if (!m_PedToArrest->m_pVehicle->IsRoomForPedToLeaveCar(TARGET_DOOR_FRONT_RIGHT, nullptr)) {
                if (m_PedToArrest->m_pVehicle->IsRoomForPedToLeaveCar(TARGET_DOOR_DRIVER, nullptr)) {
                    return TryReplaceSubTask(TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR);
                }
            }
        }

        // Change 2
        return DoDestroyCarTask();
    }
    }

    // Just continue with current sub-task
    return m_pSubTask;
}

// 0x68CF80
CTask* CTaskComplexArrestPed::CreateSubTask(int32 taskId, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68CF80, CTaskComplexArrestPed*, int32, CPed*>(this, taskId, ped);
    /*
    switch (taskId) {
    case TASK_SIMPLE_ARREST_PED:
        if (m_PedToArrest->m_pVehicle) {
            if (m_PedToArrest->m_pVehicle->IsDriver(m_PedToArrest)) {
                m_PedToArrest->m_pVehicle->vehicleFlags.bIsHandbrakeOn = true;
                m_PedToArrest->m_pVehicle->m_nStatus = STATUS_PLANE; // todo: What does that mean??
            }
        }
        return new CTaskSimpleArrestPed(m_PedToArrest);

    case TASK_COMPLEX_KILL_PED_ON_FOOT:
        return new CTaskComplexKillPedOnFoot(m_PedToArrest, -1, 0, 0, 0, 1);

    case TASK_COMPLEX_DESTROY_CAR:
        return new CTaskComplexDestroyCar(m_PedToArrest->m_pVehicle, 0, 0, 0);

    case TASK_COMPLEX_SEEK_ENTITY: {
        float radius = m_PedToArrest->bIsBeingArrested ? 4.0f : 3.0f;
        return new CTaskComplexSeekEntity<CEntitySeekPosCalculatorStandard>(m_PedToArrest, 50'000, 1000, radius, 2.0f, 2.0f, 1, 1);
    }
    case TASK_COMPLEX_DRAG_PED_FROM_CAR:
        return new CTaskComplexDragPedFromCar(m_PedToArrest, 100'000);

    case TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR:
        return new CTaskComplexOpenDriverDoor(m_PedToArrest->m_pVehicle);

    case TASK_COMPLEX_CAR_OPEN_PASSENGER_DOOR:
        return new CTaskComplexOpenPassengerDoor(m_PedToArrest->m_pVehicle, 8);

    case TASK_SIMPLE_WAIT_UNTIL_PED_OUT_CAR:
        auto out = m_PedToArrest->GetPosition() - ped->GetPosition();
        return new CTaskSimpleWaitUntilPedIsOutCar(m_PedToArrest, &out);

    default:
        return nullptr;
    }
    */
}
