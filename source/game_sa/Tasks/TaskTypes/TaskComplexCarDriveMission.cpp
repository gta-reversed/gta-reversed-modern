#include "StdInc.h"
#include "TaskComplexCarDriveMission.h"
#include "CarCtrl.h"

void CTaskComplexCarDriveMission::InjectHooks() {
    RH_ScopedClass(CTaskComplexCarDriveMission);
    RH_ScopedCategory("Tasks/TaskTypes");

    RH_ScopedInstall(Constructor, 0x63CC30);
    RH_ScopedInstall(Destructor, 0x63CCC0);

    RH_ScopedInstall(Clone_Reversed, 0x63DD70);
    RH_ScopedInstall(GetTaskType_Reversed, 0x63CCB0);
    RH_ScopedInstall(SetUpCar_Reversed, 0x63CD20);
}

// 0x63CC30
CTaskComplexCarDriveMission::CTaskComplexCarDriveMission(CVehicle* pVehicle, CVehicle* pTargetVehicle, eCarMission carDriveMission, eCarDrivingStyle carDrivingStyle, float fSpeed) :
    CTaskComplexCarDrive{pVehicle, fSpeed, -1, carDrivingStyle},
    m_targetVehicle{pTargetVehicle},
    m_carMission{(uint32)carDriveMission}
{
}

// NOTSA
CTaskComplexCarDriveMission::CTaskComplexCarDriveMission(const CTaskComplexCarDriveMission& o) :
    CTaskComplexCarDriveMission{o.m_pVehicle, o.m_targetVehicle, (eCarMission)o.m_carMission, (eCarDrivingStyle)o.m_carDrivingStyle, o.m_fSpeed}
{
}

// 0x63CD20
void CTaskComplexCarDriveMission::SetUpCar() {
    auto& autopilot = m_pVehicle->m_autoPilot;

    m_nbTrafficBehavior = autopilot.m_nCarDrivingStyle;
    m_nbTrafficBehavior = autopilot.m_nCarDrivingStyle;
    m_nbDriverBehavior = autopilot.m_nCarMission;
    m_nSpeed = autopilot.m_nCruiseSpeed;
    m_bSavedVehicleBehavior = true;

    CCarCtrl::JoinCarWithRoadSystem(m_pVehicle);
    m_pVehicle->m_nStatus = STATUS_PHYSICS;

    autopilot.m_nCarMission = (eCarMission)m_carMission;
    autopilot.m_nCruiseSpeed = (uint32)m_fSpeed;
    autopilot.m_speed = (float)autopilot.m_nCruiseSpeed;
    autopilot.m_nCarDrivingStyle = (eCarDrivingStyle)m_carDrivingStyle;
    autopilot.m_pTargetCar = m_targetVehicle;
    autopilot.m_nTimeToStartMission = CTimer::m_snTimeInMilliseconds;

    CEntity::SafeRegisterRef(autopilot.m_pTargetCar);

    m_pVehicle->vehicleFlags.bWinchCanPickMeUp = !!!m_pVehicle->vehicleFlags.bEngineBroken; // !!! - Fixes warning (And acts like a single !)
}
