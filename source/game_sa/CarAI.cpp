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
    RH_ScopedInstall(FindSwitchDistanceClose, 0x41BF50);
    RH_ScopedInstall(FindSwitchDistanceFar, 0x41BF70);
    RH_ScopedInstall(GetCarToGoToCoors, 0x41CE30);
    RH_ScopedInstall(GetCarToGoToCoorsAccurate, 0x41D0E0);
    RH_ScopedInstall(GetCarToGoToCoorsRacing, 0x41D210);
    RH_ScopedInstall(GetCarToGoToCoorsStraightLine, 0x41CFB0);
    RH_ScopedInstall(GetCarToParkAtCoors, 0x41D350);
    RH_ScopedInstall(MakeWayForCarWithSiren, 0x41D660);
    RH_ScopedInstall(MellowOutChaseSpeed, 0x41D3D0, { .reversed = false });
    RH_ScopedInstall(MellowOutChaseSpeedBoat, 0x41CB70);
    RH_ScopedInstall(TellCarToBlockOtherCar, 0x41C900, { .reversed = false });
    RH_ScopedInstall(TellCarToFollowOtherCar, 0x41C960);
    RH_ScopedInstall(TellCarToRamOtherCar, 0x41C8A0);
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
    vehicle->vehicleFlags.bOccupantsHaveBeenGenerated = true;

    switch (vehicle->m_nModelIndex) {
    case MODEL_ENFORCER:
    case MODEL_FBIRANCH:
        vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
        for (int32 i = 0; i < 3; i++) {
            vehicle->SetupPassenger(i, PED_TYPE_NONE, false, false);
        }
        break;
    case MODEL_PREDATOR:
        if (FindPlayerPed()->GetWantedLevel() > 1) {
            const auto drvr = vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
            CTaskSimpleCarSetPedOut{ vehicle, TARGET_DOOR_DRIVER, true }.ProcessPed(drvr);
            drvr->AttachPedToEntity(vehicle, CVector(0.f, 0.f, 0.f), 0, TWO_PI, WEAPON_PISTOL);
            drvr->bStayInSamePlace = true;
            drvr->GetTaskManager().SetTask(
                new CTaskComplexKillPedFromBoat{ FindPlayerPed() },
                TASK_PRIMARY_PRIMARY
            );
        }
        vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
        break;
    case MODEL_RHINO:
    case MODEL_COPBIKE:
        vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
        break;
    case MODEL_BARRACKS:
    case MODEL_COPCARLA:
    case MODEL_COPCARSF:
    case MODEL_COPCARVG:
    case MODEL_COPCARRU:
        const auto drvr = vehicle->SetUpDriver(PED_TYPE_NONE, false, false);
        const auto plyrWantedLvl = FindPlayerPed()->GetWantedLevel();
        if (plyrWantedLvl > 1) {
            // The player's in some serious gourmet shit now... Let's give the cop a partner too!
            const auto psgr = vehicle->SetupPassenger(0, PED_TYPE_NONE, false, false);

            // Give one of them a weapon
            if (plyrWantedLvl > 2) {
                if (CGeneral::RandomBool(25.0f)) {
                    drvr->GiveDelayedWeapon(WEAPON_SHOTGUN, 1000);
                } else if (CGeneral::RandomBool(25.0f)) {
                    psgr->GiveDelayedWeapon(WEAPON_SHOTGUN, 1000);
                }
            }

            // Now set the tasks for them
            const auto SetPedTasks = [vehicle](CPed* ped, CPed* partner, bool isDriver) {
                ped->GetIntelligence()->ClearTasks(true, true);
                ped->GetTaskManager().SetTask(
                    new CTaskComplexCopInCar{ vehicle, partner, FindPlayerPed(), isDriver },
                    TASK_PRIMARY_PRIMARY,
                    true
                );
            };
            SetPedTasks(drvr, psgr, true);
            SetPedTasks(psgr, drvr, false);
        } else if (arg2 || CGeneral::RandomBool(50.0f)) {
            vehicle->SetupPassenger(0, PED_TYPE_NONE, false, false);
        }
        break;
    }
}

// 0x41BFA0
void CCarAI::BackToCruisingIfNoWantedLevel(CVehicle* vehicle) {
    if (!vehicle->vehicleFlags.bIsLawEnforcer) {
        return;
    }

    CWanted* wanted = FindPlayerWanted();
    if (wanted->m_nWantedLevel > 0 && !wanted->BackOff() && !CCullZones::NoPolice()) {
        return;
    }

    CCarCtrl::JoinCarWithRoadSystem(vehicle);
    vehicle->m_autoPilot.m_nCarMission = MISSION_CRUISE;
    vehicle->m_autoPilot.m_nCarDrivingStyle = DRIVING_STYLE_STOP_FOR_CARS;
    if (CCullZones::NoPolice()) {
        vehicle->m_autoPilot.m_nCarMission = MISSION_NONE;
    }
}

// 0x41C050
void CCarAI::CarHasReasonToStop(CVehicle* vehicle) {
    vehicle->m_autoPilot.m_nTimeToStartMission = CTimer::m_snTimeInMilliseconds;
}

// 0x41CD00
bool CCarAI::EntitiesGoHeadOn(CEntity* entity1, CEntity* entity2) {
    CVector positionDiff = (entity1->GetPosition() - entity2->GetPosition()).Normalized();
    return entity1->GetForwardVector().Dot(positionDiff) <= -0.8f && entity2->GetForwardVector().Dot(positionDiff) >= 0.8f;
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
float CCarAI::GetCarToGoToCoors(CVehicle* veh, const CVector& coors, eCarDrivingStyle drivingStyle, bool setCruiseSpeed) {
    const auto ap = &veh->m_autoPilot;
    switch (ap->m_nCarMission) {
    case MISSION_PARK_PERPENDICULAR_0:
    case MISSION_PARK_PERPENDICULAR_1:
    case MISSION_PARK_PARALLEL_0:
    case MISSION_PARK_PARALLEL_1:
        break;
    case MISSION_GOTOCOORDS:
    case MISSION_GOTOCOORDS_STRAIGHT: {
        if (veh->GetPosition2D().EqualTo(coors, 5.f)) {
            break;
        }
        [[fallthrough]];
    }
    default: {
        ap->m_nCarDrivingStyle = drivingStyle;
        ap->ClearTempAction();
        if (setCruiseSpeed) {
            ap->m_nCruiseSpeed = 20;
        }
        ap->m_nTimeToStartMission = CTimer::GetTimeInMS();
        if (veh->GetStatus() != STATUS_GHOST) {
            veh->SetStatus(STATUS_PHYSICS);
        }
        ap->m_nCarMission = CCarCtrl::JoinCarWithRoadSystemGotoCoors(veh, coors, false, false)
            ? MISSION_GOTOCOORDS_STRAIGHT
            : MISSION_GOTOCOORDS;
        break;
    }
    }
    return (veh->GetPosition2D() - coors).Magnitude();
}

// 0x41D0E0
float CCarAI::GetCarToGoToCoorsAccurate(CVehicle* veh, const CVector& coors, eCarDrivingStyle drivingStyle, bool setCruiseSpeed) {
    const auto ap = &veh->m_autoPilot;

    switch (ap->m_nCarMission) {
    case MISSION_GOTOCOORDS_ACCURATE:
    case MISSION_GOTOCOORDS_STRAIGHT_ACCURATE: {
        if (!veh->GetPosition2D().EqualTo(coors, 2.f)) {
            ap->m_vecDestinationCoors = coors;
        }
        break;
    }
    default: { // Copy paste from `GetCarToGoToCoors`
        ap->m_nCarDrivingStyle = drivingStyle;
        ap->ClearTempAction();
        if (setCruiseSpeed) {
            ap->m_nCruiseSpeed = 20;
        }
        ap->m_nTimeToStartMission = CTimer::GetTimeInMS();
        if (veh->GetStatus() != STATUS_GHOST) {
            veh->SetStatus(STATUS_PHYSICS);
        }
        ap->m_nCarMission = CCarCtrl::JoinCarWithRoadSystemGotoCoors(veh, coors, false, false)
            ? MISSION_GOTOCOORDS_STRAIGHT_ACCURATE
            : MISSION_GOTOCOORDS_ACCURATE;
        break;
    }
    }

    return (veh->GetPosition2D() - coors).Magnitude();
}

// 0x41D210
float CCarAI::GetCarToGoToCoorsRacing(CVehicle* veh, const CVector& coors, eCarDrivingStyle drivingStyle, bool setCruiseSpeed) {
    const auto ap = &veh->m_autoPilot;

    switch (ap->m_nCarMission) {
    case MISSION_FOLLOW_PATH_RACING:
    case MISSION_GOTOCOORDS_STRAIGHT: {
        if (!veh->GetPosition2D().EqualTo(coors, 2.f)) {
            ap->m_vecDestinationCoors = coors;
        }
        break;
    }
    default: {
        ap->m_nCarDrivingStyle = drivingStyle;
        ap->ClearTempAction();
        if (setCruiseSpeed) {
            ap->m_nCruiseSpeed = 20;
        }
        ap->m_nTimeToStartMission = CTimer::GetTimeInMS();
        if (veh->GetStatus() != STATUS_GHOST) {
            veh->SetStatus(STATUS_PHYSICS);
        }
        ap->m_vecDestinationCoors = coors;
        ap->m_nCarMission         = MISSION_FOLLOW_PATH_RACING;
        CCarCtrl::JoinCarWithRoadSystemGotoCoors(veh, coors, false, false);
        break;
    }
    }

    return (veh->GetPosition2D() - coors).Magnitude();
}

// 0x41CFB0
float CCarAI::GetCarToGoToCoorsStraightLine(CVehicle* veh, const CVector& coors, eCarDrivingStyle drivingStyle, bool setCruiseSpeed) {
    const auto ap = &veh->m_autoPilot;

    switch (ap->m_nCarMission) {
    case MISSION_GOTOCOORDS_STRAIGHT: {
        if (!veh->GetPosition2D().EqualTo(coors, 2.f)) {
            ap->m_vecDestinationCoors = coors;
        }
        break;
    }
    default: {
        ap->m_nCarDrivingStyle = drivingStyle;
        ap->ClearTempAction();
        if (setCruiseSpeed) {
            ap->m_nCruiseSpeed = 20;
        }
        ap->m_nTimeToStartMission = CTimer::GetTimeInMS();
        if (veh->GetStatus() != STATUS_GHOST) {
            veh->SetStatus(STATUS_PHYSICS);
        }
        ap->m_vecDestinationCoors = coors;
        ap->m_nCarMission         = MISSION_GOTOCOORDS_STRAIGHT;
        // TODO/BUG: No `CCarCtrl::JoinCarWithRoadSystemGotoCoors` ?
        break;
    }
    }

    return (veh->GetPosition2D() - coors).Magnitude();
}

// 0x41D350
float CCarAI::GetCarToParkAtCoors(CVehicle* veh, const CVector& coors) {
    veh->vehicleFlags.bCanPark      = true;
    veh->m_autoPilot.m_nCruiseSpeed = 10;
    return (veh->GetPosition2D() - coors).Magnitude();
}

// 0x41D660
void CCarAI::MakeWayForCarWithSiren(CVehicle* carWithSiren) {
    float      carWithSirenSpeed2D;
    const auto carWithSirenMoveDir2D = CVector2D{ carWithSiren->GetMoveSpeed() }.Normalized(&carWithSirenSpeed2D);
    for (auto& v : GetVehiclePool()->GetAllValid()) {
        if (!v.IsAutomobile() && !v.IsBike()) {
            continue;
        }
        if (!notsa::contains({ STATUS_SIMPLE, STATUS_PHYSICS }, v.GetStatus())) {
            continue;
        }
        if (!v.IsCreatedBy(RANDOM_VEHICLE)) {
            continue;
        }
        if (v.vehicleFlags.bIsLawEnforcer) {
            continue;
        }
        if (v.m_pDriver && !v.m_pDriver->IsCreatedBy(PED_GAME)) {
            continue;
        }
        if (carWithSiren == &v) { // Thank god they remembered to check this!
            continue;
        }
        if (v.vehicleFlags.bIsFireTruckOnDuty || v.vehicleFlags.bIsAmbulanceOnDuty) {
            continue;
        }
        if (v.vehicleFlags.bMadDriver) {
            continue;
        }
        if (v.GetVehicleModelInfo()->m_nVehicleClass == VEHICLE_CLASS_BIG) {
            continue;
        }
        CVector dirToCarWithSiren = v.GetPosition() - carWithSiren->GetPosition();
        if (std::abs(dirToCarWithSiren.z) >= 5.f) { // TODO: Really should use a boundingbox height here instead....
            continue;
        }
        CVector2D dirToCarWithSiren2D{dirToCarWithSiren};
        const auto distToCarWithSiren = dirToCarWithSiren.Magnitude2D();
        if (distToCarWithSiren >= carWithSirenSpeed2D * 45.f + 40.f) {
            continue;
        }
        if (v.GetMoveSpeed().SquaredMagnitude2D() <= 0.05f) {
            continue;
        }
        const auto vehAP = &v.m_autoPilot;
        if (carWithSirenMoveDir2D.Dot(dirToCarWithSiren2D / distToCarWithSiren) <= 0.8f) { // 0x41D8A2
            if (dirToCarWithSiren2D.Dot(CVector2D{ v.GetMoveSpeed() }) < 0.f) { // Going in different directions?
                if (!notsa::contains({ TEMPACT_WAIT, TEMPACT_BRAKE }, vehAP->m_nTempAction)) {
                    vehAP->SetTempAction(TEMPACT_WAIT, 2'000);
                }
            }
        } else { // 0x41D8BD
            const auto goingSameDirDot = carWithSirenMoveDir2D.Dot(v.GetForward());
            if (goingSameDirDot > 0.7f || goingSameDirDot < -0.9f) { // 0x41D8DE
                if (!notsa::contains({ TEMPACT_SWIRVELEFT_STOP, TEMPACT_SWIRVERIGHT_STOP }, vehAP->m_nTempAction)) {
                    eAutoPilotTempAction a = carWithSirenMoveDir2D.Dot(dirToCarWithSiren2D) <= 0.f // 0x41D954
                        ? TEMPACT_SWIRVERIGHT_STOP
                        : TEMPACT_SWIRVELEFT_STOP;
                    if (goingSameDirDot < 0.f) {
                        a = a == TEMPACT_SWIRVELEFT_STOP
                            ? TEMPACT_SWIRVERIGHT_STOP
                            : TEMPACT_SWIRVELEFT_STOP;
                    }
                    if (a == TEMPACT_SWIRVERIGHT_STOP) {
                        a = TEMPACT_WAIT;
                    }
                    vehAP->SetTempAction(a, 2'500);
                }
                if (v.GetStatus() != STATUS_GHOST) {
                    v.SetStatus(STATUS_PHYSICS);
                }
            } else if (dirToCarWithSiren2D.Dot(v.GetMoveSpeed()) < 0.f) { // 0x41D910
                if (!notsa::contains({ TEMPACT_SWIRVELEFT_STOP, TEMPACT_SWIRVERIGHT_STOP }, vehAP->m_nTempAction)) {
                    vehAP->SetTempAction(TEMPACT_WAIT, 4'000);
                }
            }
        }
    }
}

// 0x41D3D0
void CCarAI::MellowOutChaseSpeed(CVehicle* vehicle) {
    float distance = (vehicle->GetPosition() - FindPlayerCoors()).Magnitude();
    bool  isPlayerSlowEnough = FindPlayerPed()->m_vecMoveSpeed.Magnitude() < 0.07f;
    if (FindPlayerVehicle()) {
        if (FindPlayerWanted()->m_nWantedLevel == 1) {
            if (distance < 10.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 15;
                return;
            }

            if (distance < 20.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 22;
                return;
            }

            vehicle->m_autoPilot.m_nCruiseSpeed = 25;
            return;
        } else if (FindPlayerWanted()->m_nWantedLevel == 2) {
            if (distance < 10.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 27;
                return;
            }

            if (distance < 20.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 30;
                return;
            }

            vehicle->m_autoPilot.m_nCruiseSpeed = 34;
            return;
        }
    } else {
        if (FindPlayerWanted()->m_nWantedLevel == 1) {
            if (distance < 20.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 5;
                return;
            }

            if (distance >= 20.0f && distance < 40.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 13;
                if (isPlayerSlowEnough && distance <= 30.0f && vehicle->m_autoPilot.m_nCruiseSpeed >= 10) {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 10;
                }
                return;
            }

            vehicle->m_autoPilot.m_nCruiseSpeed = 25;
            return;
        } else if (FindPlayerWanted()->m_nWantedLevel == 2) {
            if (distance < 20.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 5;
                return;
            }

            if (distance >= 20.0f && distance < 40.0f) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 18;
                if (isPlayerSlowEnough && distance <= 30.0f && vehicle->m_autoPilot.m_nCruiseSpeed >= 10) {
                    vehicle->m_autoPilot.m_nCruiseSpeed = 10;
                }
                return;
            }

            vehicle->m_autoPilot.m_nCruiseSpeed = 34;
            return;
        } else if (isPlayerSlowEnough && distance <= 30.0f && vehicle->m_autoPilot.m_nCruiseSpeed >= 10) {
                vehicle->m_autoPilot.m_nCruiseSpeed = 10;
        }
    }
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

// unused
// 0x41C900
void CCarAI::TellCarToBlockOtherCar(CVehicle* vehicle1, CVehicle* vehicle2) {
    /*
    vehicle1->m_autoPilot.m_pTargetCar = vehicle2;
    CEntity::SafeRegisterRef(vehicle1->m_autoPilot.m_pTargetCar);
    CCarCtrl::JoinCarWithRoadSystem(vehicle1);
    vehicle1->m_autoPilot.m_nCarMission = MISSION_BLOCKCAR_FARAWAY;
    vehicle1->vehicleFlags.bEngineOn    = !vehicle1->vehicleFlags.bEngineBroken;

    vehicle1->m_autoPilot.m_nCruiseSpeed = std::max(vehicle1->m_autoPilot.m_nCruiseSpeed, (uint8)6);
    */
    NOTSA_UNREACHABLE("Unused");
}

// 0x41C960
void CCarAI::TellCarToFollowOtherCar(CVehicle* follower, CVehicle* toFollow, float radius) {
    follower->m_autoPilot.m_pTargetCar = toFollow;
    CEntity::SafeRegisterRef(follower->m_autoPilot.m_pTargetCar);

    CCarCtrl::JoinCarWithRoadSystem(follower);

    follower->m_autoPilot.m_nCarMission     = MISSION_FOLLOW_CAR;
    follower->vehicleFlags.bEngineOn        = follower->vehicleFlags.bEngineBroken == 0;
    follower->m_autoPilot.m_nCruiseSpeed    = std::max(follower->m_autoPilot.m_nCruiseSpeed, (uint8)6);
    follower->m_autoPilot.m_ucCarFollowDist = (uint8)radius;
}

// unused
// 0x41C8A0
void CCarAI::TellCarToRamOtherCar(CVehicle* vehicle1, CVehicle* vehicle2) {
    /*
    vehicle1->m_autoPilot.m_pTargetCar = vehicle2;
    CEntity::SafeRegisterRef(vehicle1->m_autoPilot.m_pTargetCar);
    CCarCtrl::JoinCarWithRoadSystem(vehicle1);
    vehicle1->m_autoPilot.m_nCarMission = MISSION_RAMCAR_FARAWAY;
    vehicle1->vehicleFlags.bEngineOn    = !vehicle1->vehicleFlags.bEngineBroken;

    vehicle1->m_autoPilot.m_nCruiseSpeed = std::max(vehicle1->m_autoPilot.m_nCruiseSpeed, (uint8)6);
    */
    NOTSA_UNREACHABLE("Unused");
}

// 0x41C760
void CCarAI::TellOccupantsToLeaveCar(CVehicle* vehicle) {
    auto TellToLeaveCar = [vehicle](CPed* ped) {
        if (!ped) {
            return;
        }

        CTaskComplexCopInCar* task = ped->GetTaskManager().Find<CTaskComplexCopInCar>(false);
        if (task) {
            task->m_flag0x2 = 1;
        } else {
            ped->GetTaskManager().SetTask(new CTaskComplexLeaveCar{ vehicle, TARGET_DOOR_FRONT_LEFT, 0, true, false }, TASK_PRIMARY_PRIMARY, false);
        }
    };

    TellToLeaveCar(vehicle->m_pDriver);
    rng::for_each(vehicle->GetPassengers(), TellToLeaveCar);
}

// 0x41DA30
void CCarAI::UpdateCarAI(CVehicle* vehicle) {
    plugin::Call<0x41DA30, CVehicle*>(vehicle);
}
