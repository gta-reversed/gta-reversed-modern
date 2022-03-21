#include "StdInc.h"
#include "TaskSimpleCarDrive.h"
#include "TaskUtilityLineUpPedWithCar.h"

void CTaskSimpleCarDrive::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCarDrive);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63C340);
    RH_ScopedInstall(Destructor, 0x63C460);

    //RH_ScopedInstall(TriggerIK, 0x63C500);
    //RH_ScopedInstall(UpdateBopping, 0x63C900);
    //RH_ScopedInstall(StartBopping, 0x642760);
    //RH_ScopedInstall(ProcessHeadBopping, 0x6428C0);
    //RH_ScopedInstall(ProcessArmBopping, 0x642AE0);
    //RH_ScopedInstall(ProcessBopping, 0x642E70);

    //RH_ScopedInstall(Clone_Reversed, 0x63DC20);
    //RH_ScopedInstall(GetTaskType_Reversed, 0x63C450);
    //RH_ScopedInstall(MakeAbortable_Reversed, 0x63C670);
    //RH_ScopedInstall(ProcessPed_Reversed, 0x644470);
    //RH_ScopedInstall(SetPedPosition_Reversed, 0x63C770);
}

CTaskSimpleCarDrive::CTaskSimpleCarDrive(CVehicle* vehicle, CTaskUtilityLineUpPedWithCar* utilityTask, bool updateCurrentVehicle) :
    m_pVehicle{vehicle},
    m_bUpdateCurrentVehicle{updateCurrentVehicle},
    m_pTaskUtilityLineUpPedWithCar{ utilityTask ? new CTaskUtilityLineUpPedWithCar{CVector{}, 0, utilityTask->m_doorOpenPosType, utilityTask->m_doorIdx} : nullptr}
{
    if (m_pVehicle) {
        m_pVehicle->RegisterReference(reinterpret_cast<CEntity**>(&m_pVehicle));
    }
}

bool CTaskSimpleCarDrive::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x644470, CTaskSimpleCarDrive*, CPed*>(this, ped);
}

CTask* CTaskSimpleCarDrive::Clone() {
    return plugin::CallMethodAndReturn<CTask*, 0x63DC20, CTaskSimpleCarDrive*>(this);
}

bool CTaskSimpleCarDrive::MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) {
    return plugin::CallMethodAndReturn<bool, 0x63DC20, CTaskSimpleCarDrive*, CPed*, eAbortPriority, const CEvent*>(this, ped, priority, event);
}
