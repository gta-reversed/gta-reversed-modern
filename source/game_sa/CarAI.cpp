/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "CarAI.h"
#include "CarCtrl.h"
#include "CullZones.h"
#include "TaskComplexCopInCar.h"
#include "TaskComplexDriveFireTruck.h"
#include "TaskComplexMedicTreatInjuredPed.h"
#include "TaskComplexKillPedFromBoat.h"
#include "TaskComplexLeaveCar.h"
#include "TaskSimpleCarDrive.h"
#include "TaskSimpleCarSetPedOut.h"
#include "Timer.h"
#include "eWeaponType.h"

void CCarAI::InjectHooks() {
    RH_ScopedClass(CCarAI);
    RH_ScopedCategory("AI");

    RH_ScopedInstall(AddAmbulanceOccupants, 0x41C4A0);
    RH_ScopedInstall(AddFiretruckOccupants, 0x41C600);
    RH_ScopedInstall(AddPoliceCarOccupants, 0x41C070);
    RH_ScopedInstall(BackToCruisingIfNoWantedLevel, 0x41BFA0);
    RH_ScopedInstall(CarHasReasonToStop, 0x41C050);
    RH_ScopedInstall(EntitiesGoHeadOn, 0x41CD00);
    RH_ScopedInstall(FindPoliceBikeMissionForWantedLevel, 0x41CA40);
    RH_ScopedInstall(FindPoliceBoatMissionForWantedLevel, 0x41CA50);
    RH_ScopedInstall(FindPoliceCarMissionForWantedLevel, 0x41C9D0);
    RH_ScopedInstall(FindPoliceCarSpeedForWantedLevel, 0x41CAA0);
    RH_ScopedInstall(FindSwitchDistanceClose, 0x41BF50, { .reversed = false });
    RH_ScopedInstall(FindSwitchDistanceFar, 0x41BF70, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoors, 0x41CE30, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoorsAccurate, 0x41D0E0, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoorsRacing, 0x41D210, { .reversed = false });
    RH_ScopedInstall(GetCarToGoToCoorsStraightLine, 0x41CFB0, { .reversed = false });
    RH_ScopedInstall(GetCarToParkAtCoors, 0x41D350, { .reversed = false });
    RH_ScopedInstall(MakeWayForCarWithSiren, 0x41D660, { .reversed = false });
    RH_ScopedInstall(MellowOutChaseSpeed, 0x41D3D0, { .reversed = false });
    RH_ScopedInstall(MellowOutChaseSpeedBoat, 0x41CB70);
    RH_ScopedInstall(TellCarToBlockOtherCar, 0x41C900, { .reversed = false });
    RH_ScopedInstall(TellCarToFollowOtherCar, 0x41C960, { .reversed = false });
    RH_ScopedInstall(TellCarToRamOtherCar, 0x41C8A0, { .reversed = false });
    RH_ScopedInstall(TellOccupantsToLeaveCar, 0x41C760);
    RH_ScopedInstall(UpdateCarAI, 0x41DA30, { .reversed = false });
}

// 0x41C4A0
void CCarAI::AddAmbulanceOccupants(CVehicle* vehicle) {
    CPed* driver    = vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
    CPed* passenger = vehicle->SetupPassenger(1, PED_TYPE_NONE, false, false);

    driver->GetTaskManager().SetTask(new CTaskSimpleCarDrive{ vehicle }, TASK_PRIMARY_DEFAULT);
    driver->GetTaskManager().SetTask(new CTaskComplexMedicTreatInjuredPed{ vehicle, passenger, true }, TASK_PRIMARY_PRIMARY);
    passenger->GetTaskManager().SetTask(new CTaskSimpleCarDrive{ vehicle }, TASK_PRIMARY_DEFAULT);
    passenger->GetTaskManager().SetTask(new CTaskComplexMedicTreatInjuredPed{ vehicle, driver, false }, TASK_PRIMARY_PRIMARY);
}

// 0x41C600
void CCarAI::AddFiretruckOccupants(CVehicle* vehicle) {
    CPed* driver = vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
    CPed* passenger = vehicle->SetupPassenger(0, PED_TYPE_NONE, false, false);

    driver->GetTaskManager().SetTask(new CTaskSimpleCarDrive{ vehicle }, TASK_PRIMARY_DEFAULT);
    driver->GetTaskManager().SetTask(new CTaskComplexDriveFireTruck{ vehicle, passenger, true }, TASK_PRIMARY_PRIMARY);
    passenger->GetTaskManager().SetTask(new CTaskSimpleCarDrive{ vehicle }, TASK_PRIMARY_DEFAULT);
    passenger->GetTaskManager().SetTask(new CTaskComplexDriveFireTruck{ vehicle, driver, false }, TASK_PRIMARY_PRIMARY);
}

// 0x41C070
void CCarAI::AddPoliceCarOccupants(CVehicle* vehicle, bool arg2) {
    if (vehicle->vehicleFlags.bOccupantsHaveBeenGenerated) {
        return;
    }

    vehicle->vehicleFlags.bOccupantsHaveBeenGenerated = 1;
    switch (vehicle->m_nModelIndex) {
    case MODEL_ENFORCER:
    case MODEL_FBIRANCH:
        vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
        vehicle->SetupPassenger(0, PED_TYPE_NONE, false, false);
        vehicle->SetupPassenger(1, PED_TYPE_NONE, false, false);
        vehicle->SetupPassenger(2, PED_TYPE_NONE, false, false);
        return;
    case MODEL_PREDATOR:
        if (FindPlayerPed()->GetWantedLevel() > 1) {
            CPed* driver = vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
            CTaskSimpleCarSetPedOut{ vehicle, TARGET_DOOR_DRIVER, true }.ProcessPed(driver);
            driver->AttachPedToEntity(vehicle, CVector(0.0, 0.0, 0.0), 0, (float)6.2831855, WEAPON_PISTOL);
            driver->bStayInSamePlace = true;
            driver->GetTaskManager().SetTask(new CTaskComplexKillPedFromBoat{ FindPlayerPed() }, TASK_PRIMARY_PRIMARY);
        }
        vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
    case MODEL_RHINO:
    case MODEL_COPBIKE:
        vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
        return;
    case MODEL_BARRACKS:
    case MODEL_COPCARLA:
    case MODEL_COPCARSF:
    case MODEL_COPCARVG:
    case MODEL_COPCARRU:
        CPed*  driver      = vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
        uint32 wantedLevel = FindPlayerPed()->GetWantedLevel();
        if (wantedLevel > 1) {
            CPed* passenger = vehicle->SetupPassenger(0, PED_TYPE_NONE, false, false);
            if (wantedLevel > 2) {
                CPed* selectedPed;
                if (CGeneral::RandomBool(25.0f)) {
                    selectedPed = driver;
                }
                if (CGeneral::RandomBool(25.0f)) {
                    selectedPed = passenger;
                }
                if (selectedPed) {
                    selectedPed->GiveDelayedWeapon(WEAPON_SHOTGUN, 1000);
                }
            }
            driver->GetIntelligence()->ClearTasks(true, true);
            driver->GetTaskManager().SetTask(new CTaskComplexCopInCar{ vehicle, passenger, FindPlayerPed(), true }, TASK_PRIMARY_PRIMARY, true);
            passenger->GetIntelligence()->ClearTasks(true, true);
            driver->GetTaskManager().SetTask(new CTaskComplexCopInCar{ vehicle, driver, FindPlayerPed(), true }, TASK_PRIMARY_PRIMARY, false);
            return;
        }

        if (arg2 || CGeneral::RandomBool(50.0f)) {
            vehicle->SetupPassenger(0, PED_TYPE_NONE, false, false);
        }
    }
}

// 0x41BFA0
void CCarAI::BackToCruisingIfNoWantedLevel(CVehicle* vehicle) {
    if (!vehicle->vehicleFlags.bIsLawEnforcer) {
        return;
    }

    CWanted* wanted = FindPlayerWanted();
    if (!wanted->m_nWantedLevel || wanted->BackOff() || CCullZones::NoPolice()) {
        CCarCtrl::JoinCarWithRoadSystem(vehicle);
        vehicle->m_autoPilot.m_nCarMission = MISSION_CRUISE;
        vehicle->m_autoPilot.m_nCarDrivingStyle = DRIVING_STYLE_STOP_FOR_CARS;
        if (CCullZones::NoPolice()) {
            vehicle->m_autoPilot.m_nCarMission = MISSION_NONE;
        }
    }
}

// 0x41C050
void CCarAI::CarHasReasonToStop(CVehicle* vehicle) {
    vehicle->m_autoPilot.m_nTimeToStartMission = CTimer::m_snTimeInMilliseconds;
}

// 0x41CD00
bool CCarAI::EntitiesGoHeadOn(CEntity* entity1, CEntity* entity2) {
    CVector position1 = entity1->m_matrix ? entity1->m_matrix->GetPosition() : entity1->m_placement.m_vPosn;
    CVector position2 = entity2->m_matrix ? entity2->m_matrix->GetPosition() : entity2->m_placement.m_vPosn;
    CVector positionDiff = position1 - position2;
    positionDiff.Normalise();

    const CVector& forward1 = entity1->GetForwardVector();
    if (forward1.Dot(positionDiff) > -0.8f) {
        return false;
    }

    const CVector& forward2 = entity2->GetForwardVector();
    return forward2.Dot(positionDiff) >= 0.8f;
}

// 0x41CA40
eCarMission CCarAI::FindPoliceBikeMissionForWantedLevel() {
    return MISSION_POLICE_BIKE;
}

// 0x41CA50
eCarMission CCarAI::FindPoliceBoatMissionForWantedLevel() {
    const auto& wantedLevel = FindPlayerWanted()->m_nWantedLevel;
    if (wantedLevel < 2 || wantedLevel > 6)
        return FindPlayerVehicle() ? MISSION_BLOCKPLAYER_FARAWAY : MISSION_BOAT_CIRCLING_PLAYER;
    else
        return FindPlayerVehicle() ? MISSION_ATTACKPLAYER : MISSION_BOAT_CIRCLING_PLAYER;
}

// 0x41C9D0
eCarMission CCarAI::FindPoliceCarMissionForWantedLevel() {
    double probability = CGeneral::GetRandomNumberInRange(0.0, 1.0);
    switch (FindPlayerWanted()->m_nWantedLevel) {
    case 2:
        return CGeneral::RandomBool(75.0f) ? MISSION_BLOCKPLAYER_FARAWAY : MISSION_RAMPLAYER_FARAWAY;
    case 3:
        return CGeneral::RandomBool(50.0f) ? MISSION_BLOCKPLAYER_FARAWAY : MISSION_RAMPLAYER_FARAWAY;
    case 4:
    case 5:
    case 6:
        return CGeneral::RandomBool(25.0f) ? MISSION_BLOCKPLAYER_FARAWAY : MISSION_RAMPLAYER_FARAWAY;
    default:
        return MISSION_BLOCKPLAYER_FARAWAY;
    }
}

// 0x41CAA0
int32 CCarAI::FindPoliceCarSpeedForWantedLevel(CVehicle* vehicle) {
    const auto& maxVelocity = vehicle->m_pHandlingData->m_transmissionData.m_fMaxVelocity;
    switch (FindPlayerWanted()->m_nWantedLevel) {
    case 0:
        return (int32)CGeneral::GetRandomNumberInRange(12.0f, 16.0f);
    case 1:
        return 25;
    case 2:
        return 34;
    case 3:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 0.90f);
    case 4:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 1.20f);
    case 5:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 1.25f);
    case 6:
        return int32(maxVelocity * GAME_SPEED_TO_CAR_AI_SPEED * 1.30f);
    default:
        return 0;
    }
}

// 0x41BF50
float CCarAI::FindSwitchDistanceClose(CVehicle* vehicle) {
    return (float)vehicle->m_autoPilot.m_nStraightLineDistance;
}

// 0x41BF70
float CCarAI::FindSwitchDistanceFar(CVehicle* vehicle) {
    if (vehicle->vehicleFlags.bIsLawEnforcer)
        return 50.0f;
    else
        return FindSwitchDistanceClose(vehicle) + 5.0f;
}

// 0x41CE30
float CCarAI::GetCarToGoToCoors(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41CE30, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41D0E0
float CCarAI::GetCarToGoToCoorsAccurate(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41D0E0, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41D210
float CCarAI::GetCarToGoToCoorsRacing(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41D210, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41CFB0
float CCarAI::GetCarToGoToCoorsStraightLine(CVehicle* vehicle, CVector* vec, int32 drivingStyle, bool bSpeedLimit20) {
    return plugin::CallAndReturn<float, 0x41CFB0, CVehicle*, CVector*, int32, bool>(vehicle, vec, drivingStyle, bSpeedLimit20);
}

// 0x41D350
float CCarAI::GetCarToParkAtCoors(CVehicle* vehicle, CVector* vec) {
    return plugin::CallAndReturn<float, 0x41D350, CVehicle*, CVector*>(vehicle, vec);
}

// 0x41D660
void CCarAI::MakeWayForCarWithSiren(CVehicle* vehicle) {
    plugin::Call<0x41D660, CVehicle*>(vehicle);
}

// 0x41D3D0
void CCarAI::MellowOutChaseSpeed(CVehicle* vehicle) {
    plugin::Call<0x41D3D0, CVehicle*>(vehicle);
}

// 0x41CB70
void CCarAI::MellowOutChaseSpeedBoat(CVehicle* vehicle) {
    switch (FindPlayerWanted()->m_nWantedLevel) {
    case 0:
        vehicle->m_autoPilot.m_nCruiseSpeed = 8;
        break;
    case 1:
        vehicle->m_autoPilot.m_nCruiseSpeed = 10;
        break;
    case 2:
        vehicle->m_autoPilot.m_nCruiseSpeed = 15;
        break;
    case 3:
        vehicle->m_autoPilot.m_nCruiseSpeed = 20;
        break;
    case 4:
        vehicle->m_autoPilot.m_nCruiseSpeed = 25;
        break;
    case 5:
        vehicle->m_autoPilot.m_nCruiseSpeed = 30;
        break;
    case 6:
        vehicle->m_autoPilot.m_nCruiseSpeed = 40;
        break;
    default:
        return;
    }
}

// 0x41C900
void CCarAI::TellCarToBlockOtherCar(CVehicle* vehicle1, CVehicle* vehicle2) {
    plugin::Call<0x41C900, CVehicle*, CVehicle*>(vehicle1, vehicle2);
}

// 0x41C960
void CCarAI::TellCarToFollowOtherCar(CVehicle* vehicle1, CVehicle* vehicle2, float radius) {
    plugin::Call<0x41C960, CVehicle*, CVehicle*, float>(vehicle1, vehicle2, radius);
}

// 0x41C8A0
void CCarAI::TellCarToRamOtherCar(CVehicle* vehicle1, CVehicle* vehicle2) {
    plugin::Call<0x41C8A0, CVehicle*, CVehicle*>(vehicle1, vehicle2);
}

// 0x41C760
void CCarAI::TellOccupantsToLeaveCar(CVehicle* vehicle) {
    auto tellToLeaveCar = [vehicle](CPed* ped) {
        if (!ped) {
            return;
        }

        CTaskComplexCopInCar* task = vehicle->m_pDriver->GetTaskManager().Find<CTaskComplexCopInCar>(false);
        if (task) {
            task->m_flag0x2 = 1;
        } else {
            vehicle->m_pDriver->GetTaskManager().SetTask(new CTaskComplexLeaveCar{ vehicle, TARGET_DOOR_FRONT_LEFT, 0, true, false }, TASK_PRIMARY_PRIMARY, false);
        }
    };

    tellToLeaveCar(vehicle->m_pDriver);

    if (vehicle->m_nMaxPassengers) {
        for (CPed* passenger : vehicle->GetPassengers()) {
            tellToLeaveCar(passenger);
        }
    }
}

// 0x41DA30
void CCarAI::UpdateCarAI(CVehicle* vehicle) {
    plugin::Call<0x41DA30, CVehicle*>(vehicle);
}
