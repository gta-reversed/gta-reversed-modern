#include "StdInc.h"

#include "TaskComplexArrestPed.h"

void CTaskComplexArrestPed::InjectHooks() {
    RH_ScopedClass(CTaskComplexArrestPed);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x68B990);
    RH_ScopedInstall(Destructor, 0x68BA00);

    RH_ScopedInstall(MakeAbortable, 0x68BA60);
    //RH_ScopedInstall(CreateNextSubTask, 0x690220);
    RH_ScopedInstall(CreateFirstSubTask, 0x6907A0);
    //RH_ScopedInstall(ControlSubTask, 0x68D350);
    //RH_ScopedInstall(CreateSubTask, 0x68CF80);
}

// 0x68B990
CTaskComplexArrestPed::CTaskComplexArrestPed(CPed* ped) :
    m_pedToArrest{ped}
{
    if (ped) {
        ped->RegisterReference(reinterpret_cast<CEntity**>(&m_pedToArrest));
    }
}

CTaskComplexArrestPed::~CTaskComplexArrestPed() {
    if (m_pedToArrest)
        m_pedToArrest->CleanUpOldReference(reinterpret_cast<CEntity**>(&m_pedToArrest));
}

bool CTaskComplexArrestPed::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return m_pSubTask->MakeAbortable(ped, priority, event);
}

CTask* CTaskComplexArrestPed::CreateNextSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x690220, CTaskComplexArrestPed*, CPed*>(this, ped);
    /*if (!m_pedToArrest) {
        return CreateSubTask(TASK_FINISHED, ped);
    }

    if (m_pedToArrest->bIsBeingArrested) {
        switch (m_pSubTask->GetTaskType()) {
        case TASK_SIMPLE_ARREST_PED:
            break;
        case TASK_COMPLEX_SEEK_ENTITY: { // TODO: Missing 
            if ()
        }
        }
        if (m_pSubTask->GetTaskType() != TASK_SIMPLE_ARREST_PED) {

        }
    }*/
}

CTask* CTaskComplexArrestPed::CreateFirstSubTask(CPed* ped) {
    if (!m_pedToArrest) {
        return nullptr;
    }

    m_subTaskNeedsToBeCreated = false;

    if (!m_pedToArrest->bInVehicle) {
        return CreateSubTask(TASK_COMPLEX_KILL_PED_ON_FOOT, ped);
    }

    if (m_pedToArrest->m_pVehicle->IsBike() || m_pedToArrest->m_pVehicle->IsSubQuad()) { // Just drag ped from a bike/quad
        return CreateSubTask(TASK_COMPLEX_DRAG_PED_FROM_CAR, ped);
    }

    if (m_pedToArrest->m_pVehicle->IsSubBoat()) { // If they're in a boat, just destroy it
        if (ped->GetActiveWeapon().IsTypeMelee()) { // Make sure ped has an actual weapon in their hand
            if (ped->DoWeHaveWeaponAvailable(WEAPON_SHOTGUN)) { // Use shotgun (if available)
                ped->SetCurrentWeapon(WEAPON_SHOTGUN);
            } else { // Otherwise a pistol
                if (!ped->DoWeHaveWeaponAvailable(WEAPON_PISTOL)) { // Make sure they have one
                    ped->GiveWeapon(WEAPON_PISTOL, 10, 0);
                }
                ped->SetCurrentWeapon(WEAPON_PISTOL);
            }
        }
        return CreateSubTask(TASK_COMPLEX_DESTROY_CAR, ped);
    } else {
        if (m_pedToArrest->m_pVehicle->IsUpsideDown() || m_pedToArrest->m_pVehicle->IsOnItsSide()) {
            return CreateSubTask(TASK_COMPLEX_DESTROY_CAR, ped);
        }
        return CreateSubTask(TASK_COMPLEX_CAR_OPEN_DRIVER_DOOR, ped);
    }
}

CTask* CTaskComplexArrestPed::ControlSubTask(CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68D350, CTaskComplexArrestPed*, CPed*>(this, ped);
}

CTask* CTaskComplexArrestPed::CreateSubTask(int32 taskId, CPed* ped) {
    return plugin::CallMethodAndReturn<CTask*, 0x68CF80, CTaskComplexArrestPed*, int32, CPed*>(this, taskId, ped);
}
