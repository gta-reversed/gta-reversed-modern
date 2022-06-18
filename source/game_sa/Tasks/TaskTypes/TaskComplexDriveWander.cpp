#include "StdInc.h"

#include "TaskComplexDriveWander.h"
#include "CarCtrl.h"

// 0x63CB10
CTaskComplexCarDriveWander::CTaskComplexCarDriveWander(CVehicle* vehicle, eCarDrivingStyle carDrivingStyle, float fSpeed)
    : CTaskComplexCarDrive(vehicle, fSpeed, -1, carDrivingStyle)
{
    // NOP
}

// 0x63CB60
void CTaskComplexCarDriveWander::SetUpCar() {
    m_nOldCarDrivingStyle = m_pVehicle->m_autoPilot.m_nCarDrivingStyle;
    m_nCarMission         = m_pVehicle->m_autoPilot.m_nCarMission;
    m_nSpeed              = m_pVehicle->m_autoPilot.m_nCruiseSpeed;
    m_bSavedVehicleBehavior = true;
    if (!CCarCtrl::bCarIsBeingCreated) {
        CCarCtrl::JoinCarWithRoadSystem(m_pVehicle);
        m_pVehicle->m_nStatus = STATUS_PHYSICS;
        m_pVehicle->m_autoPilot.m_nCarMission = MISSION_CRUISE;
        m_pVehicle->m_autoPilot.m_nCruiseSpeed = (uint8)m_fSpeed;
        m_pVehicle->m_autoPilot.m_speed = m_pVehicle->m_autoPilot.m_nCruiseSpeed;
        m_pVehicle->m_autoPilot.m_nCarDrivingStyle = static_cast<eCarDrivingStyle>(m_nCarDrivingStyle);
    }
    if (m_pVehicle->vehicleFlags.bEngineBroken) {
        m_pVehicle->vehicleFlags.bEngineOn = false;
        m_pVehicle->vehicleFlags.bIsLawEnforcer = false;
    } else {
        m_pVehicle->vehicleFlags.bEngineOn = true;
    }
    m_pVehicle->m_autoPilot.m_nTimeToStartMission = CTimer::GetTimeInMS();
}

// 0x643240
CTask* CTaskComplexCarDriveWander::CreateSubTaskCannotGetInCar(CPed* ped) {
    return CTaskComplexCarDrive::CreateSubTask(TASK_COMPLEX_WANDER, ped);
}
