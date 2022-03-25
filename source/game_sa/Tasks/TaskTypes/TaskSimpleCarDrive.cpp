#include "StdInc.h"
#include "TaskSimpleCarDrive.h"
#include "TaskUtilityLineUpPedWithCar.h"
#include "IKChainManager_c.h"

void CTaskSimpleCarDrive::InjectHooks() {
    RH_ScopedClass(CTaskSimpleCarDrive);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63C340);
    RH_ScopedInstall(Destructor, 0x63C460);

    RH_ScopedInstall(TriggerIK, 0x63C500);
    //RH_ScopedInstall(UpdateBopping, 0x63C900);
    //RH_ScopedInstall(StartBopping, 0x642760);
    //RH_ScopedInstall(ProcessHeadBopping, 0x6428C0);
    //RH_ScopedInstall(ProcessArmBopping, 0x642AE0);
    //RH_ScopedInstall(ProcessBopping, 0x642E70);
    //RH_ScopedInstall(Clone_Reversed, 0x63DC20);
    RH_ScopedInstall(GetTaskType_Reversed, 0x63C450);
    //RH_ScopedInstall(MakeAbortable_Reversed, 0x63C670);
    //RH_ScopedInstall(ProcessPed_Reversed, 0x644470);
    //RH_ScopedInstall(SetPedPosition_Reversed, 0x63C770);
}

// 0x63C340
CTaskSimpleCarDrive::CTaskSimpleCarDrive(CVehicle* vehicle, CTaskUtilityLineUpPedWithCar* utilityTask, bool updateCurrentVehicle) :
    m_pVehicle{vehicle},
    m_bUpdateCurrentVehicle{updateCurrentVehicle},
    m_pTaskUtilityLineUpPedWithCar{ utilityTask ? new CTaskUtilityLineUpPedWithCar{CVector{}, 0, utilityTask->m_doorOpenPosType, utilityTask->m_doorIdx} : nullptr}
{
    CEntity::SafeRegisterRef(m_pVehicle);
}

// 0x63C500
void CTaskSimpleCarDrive::TriggerIK(CPed* ped) {
    if (!m_pVehicle) {
        return;
    }

    // Made an early-out of this, as this same code is used in both possible cases.
    if (g_ikChainMan.IsLooking(ped) || CGeneral::GetRandomNumberInRange(0, 100) >= 5) {
        return;
    }

    switch (m_pVehicle->m_autoPilot.m_nCarMission) {
    case MISSION_RAMPLAYER_FARAWAY:
    case MISSION_RAMPLAYER_CLOSE:
    case MISSION_BLOCKPLAYER_FARAWAY:
    case MISSION_BLOCKPLAYER_CLOSE:
    case MISSION_BLOCKPLAYER_HANDBRAKESTOP: { // Make ped look at player ped 
        g_ikChainMan.LookAt("DriveCar", ped, FindPlayerPed(), 3000, BONE_HEAD, nullptr, false, 0.25f, 500, 3, false);
        break;
    }
    case MISSION_RAMCAR_FARAWAY:
    case MISSION_RAMCAR_CLOSE: {
        if (const auto vehTargetCar = m_pVehicle->m_autoPilot.m_pTargetCar) {
            if (vehTargetCar->IsVehicle()) {
                if (const auto driver = vehTargetCar->m_pDriver) { // Make ped look at target car or it's driver (if any)
                    g_ikChainMan.LookAt("DriveCar", ped, driver, 3000, BONE_HEAD, nullptr, false, 0.25f, 500, 3, false);
                } else {
                    g_ikChainMan.LookAt("DriveCar", ped, vehTargetCar, 3000, BONE_UNKNOWN, nullptr, false, 0.25f, 500, 3, false);
                }
            }
        }
        break;
    }
    }
}

// 0x63C900
int32 CTaskSimpleCarDrive::UpdateBopping() {
    return plugin::CallMethodAndReturn<int32, 0x63C900, CTaskSimpleCarDrive*>(this);
}

// 0x642760
void CTaskSimpleCarDrive::StartBopping(CPed* ped) {
    plugin::CallMethod<0x642760, CTaskSimpleCarDrive*, CPed*>(this, ped);
}

// 0x6428C0
void CTaskSimpleCarDrive::ProcessHeadBopping(CPed* ped, uint8 a3, float a4) {
    plugin::CallMethod<0x6428C0, CTaskSimpleCarDrive*, CPed*, uint8, float>(this, ped, a3, a4);
}

// 0x642AE0
void CTaskSimpleCarDrive::ProcessArmBopping(CPed* pPed, uint8 a3, float a4) {
    plugin::CallMethod<0x642AE0, CTaskSimpleCarDrive*, CPed*, uint8, float>(this, pPed, a3, a4);
}

// 0x642E70
void CTaskSimpleCarDrive::ProcessBopping(CPed* a2, uint8 a3) {
    plugin::CallMethod<0x642E70, CTaskSimpleCarDrive*, CPed*, uint8>(this, a2, a3);
}

// 0x63DC20
CTask* CTaskSimpleCarDrive::Clone() {
    return plugin::CallMethodAndReturn< CTask*, 0x63DC20, CTaskSimpleCarDrive*>(this);
}

// 0x63C670
bool CTaskSimpleCarDrive::MakeAbortable(CPed* ped, eAbortPriority priority, CEvent const* event) {
    return plugin::CallMethodAndReturn<bool, 0x63C670, CTaskSimpleCarDrive*, CPed*, eAbortPriority, CEvent const*>(this, ped, priority, event);
}

// 0x644470
bool CTaskSimpleCarDrive::ProcessPed(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x644470, CTaskSimpleCarDrive*, CPed*>(this, ped);
}

// 0x63C770
bool CTaskSimpleCarDrive::SetPedPosition(CPed* ped) {
    return plugin::CallMethodAndReturn<bool, 0x63C770, CTaskSimpleCarDrive*, CPed*>(this, ped);
}

