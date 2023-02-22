/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Vehicle.h"

#include "Buoyancy.h"
#include "CarCtrl.h"
#include "VehicleSaveStructure.h"
#include "Radar.h"
#include "RideAnims.h"
#include "Rope.h"
#include "Ropes.h"
#include "IKChainManager_c.h"

float& CVehicle::WHEELSPIN_TARGET_RATE = *(float*)0x8D3498;          // 1.0f
float& CVehicle::WHEELSPIN_INAIR_TARGET_RATE = *(float*)0x8D349C;    // 10.0f
float& CVehicle::WHEELSPIN_RISE_RATE = *(float*)0x8D34A0;            // 0.95f
float& CVehicle::WHEELSPIN_FALL_RATE = *(float*)0x8D34A4;            // 0.7f
float& CVehicle::m_fAirResistanceMult = *(float*)0x8D34A8;           // 2.5f
float& CVehicle::ms_fRailTrackResistance = *(float*)0x8D34AC;        // 0.003f
float& CVehicle::ms_fRailTrackResistanceDefault = *(float*)0x8D34B0; // 0.003f
bool& CVehicle::bDisableRemoteDetonation = *(bool*)0xC1CC00;
bool& CVehicle::bDisableRemoteDetonationOnContact = *(bool*)0xC1CC01;
bool& CVehicle::m_bEnableMouseSteering = *(bool*)0xC1CC02;
bool& CVehicle::m_bEnableMouseFlying = *(bool*)0xC1CC03;
CColModel* (&CVehicle::m_aSpecialColVehicle)[4] = *(CColModel*(*)[4])0xC1CC08;
bool& CVehicle::ms_forceVehicleLightsOff = *(bool*)0xC1CC18;
bool& CVehicle::s_bPlaneGunsEjectShellCasings = *(bool*)0xC1CC19;
CColModel (&CVehicle::m_aSpecialColModel)[4] = *(CColModel(*)[4])0xC1CC78;

float& fBurstTyreMod = *(float*)0x8D34B4;                // 0.13f
float& fBurstSpeedMax = *(float*)0x8D34B8;               // 0.3f
float& CAR_NOS_EXTRA_SKID_LOSS = *(float*)0x8D34BC;      // 0.9f
float& WS_TRAC_FRAC_LIMIT = *(float*)0x8D34C0;           // 0.3f
float& WS_ALREADY_SPINNING_LOSS = *(float*)0x8D34C4;     // 0.2f
float& fBurstBikeTyreMod = *(float*)0x8D34C8;            // 0.05f
float& fBurstBikeSpeedMax = *(float*)0x8D34CC;           // 0.12f
float& fTweakBikeWheelTurnForce = *(float*)0x8D34D0;     // 2.0f
float& AUTOGYRO_ROTORSPIN_MULT = *(float*)0x8D34D4;      // 0.006f
float& AUTOGYRO_ROTORSPIN_MULTLIMIT = *(float*)0x8D34D8; // 0.25f
float& AUTOGYRO_ROTORSPIN_DAMP = *(float*)0x8D34DC;      // 0.997f
float& AUTOGYRO_ROTORLIFT_MULT = *(float*)0x8D34E0;      // 4.5f
float& AUTOGYRO_ROTORLIFT_FALLOFF = *(float*)0x8D34E4;   // 0.75f
float& AUTOGYRO_ROTORTILT_ANGLE = *(float*)0x8D34E8;     // 0.25f
float& ROTOR_SEMI_THICKNESS = *(float*)0x8D34EC;         // 0.05f
float* gfSpeedMult = (float*)0x8D34F8;                   // float fSpeedMult[5] = { 0.8f, 0.75f, 0.85f, 0.9f, 0.85f, 0.85f }
float& fDamagePosSpeedShift = *(float*)0x8D3510;         // 0.4f
float& DIFF_LIMIT = *(float*)0x8D35B4;                   // 0.8f
float& DIFF_SPRING_MULT_X = *(float*)0x8D35B8;           // 0.05f
float& DIFF_SPRING_MULT_Y = *(float*)0x8D35BC;           // 0.05f
float& DIFF_SPRING_MULT_Z = *(float*)0x8D35C0;           // 0.1f
float& DIFF_SPRING_COMPRESS_MULT = *(float*)0x8D35C4;    // 2.0f
CVector (&VehicleGunOffset)[14] = *(CVector(*)[14])0x8D35D4; // maybe [12]

void CVehicle::InjectHooks() {
    RH_ScopedClass(CVehicle);
    RH_ScopedCategory("Vehicle");

    RH_ScopedVirtualInstall(SetModelIndex, 0x6D6A40);
    RH_ScopedVirtualInstall(DeleteRwObject, 0x6D6410);
    RH_ScopedVirtualInstall(SpecialEntityPreCollisionStuff, 0x6D6640);
    RH_ScopedVirtualInstall(SpecialEntityCalcCollisionSteps, 0x6D0E90);
    RH_ScopedVirtualInstall(SetupLighting, 0x553F20);
    RH_ScopedVirtualInstall(RemoveLighting, 0x5533D0);
    RH_ScopedVirtualInstall(PreRender, 0x6D6480);
    RH_ScopedVirtualInstall(Render, 0x6D0E60);
    RH_ScopedVirtualInstall(ProcessOpenDoor, 0x6D56C0);

    // It can't be properly unhooked, original function assumes that CVehicle::GetVehicleAppearance doesn't spoil ECX register, and calls
    // it without making sure that the pointer in it still points to current instance. While it worked for original function, we can't
    // force the compiler to keep ECX unchanged through function execution
    RH_ScopedVirtualInstall(ProcessDrivingAnims, 0x6DF4A0, {.enabled = true, .locked = true});

    RH_ScopedVirtualInstall(GetHeightAboveRoad, 0x6D63F0);
    RH_ScopedVirtualInstall(CanPedStepOutCar, 0x6D1F30);
    RH_ScopedVirtualInstall(CanPedJumpOutCar, 0x6D2030);
    RH_ScopedVirtualInstall(GetTowHitchPos, 0x6DFB70);
    RH_ScopedVirtualInstall(GetTowBarPos, 0x6DFBE0);
    RH_ScopedVirtualInstall(Save, 0x5D4760);
    RH_ScopedVirtualInstall(Load, 0x5D2900);
    RH_ScopedInstall(Shutdown, 0x6D0B40);
    RH_ScopedInstall(GetRemapIndex, 0x6D0B70);
    RH_ScopedInstall(SetRemap, 0x6D0C00);
    RH_ScopedInstall(SetCollisionLighting, 0x6D0CA0);
    RH_ScopedInstall(UpdateLightingFromStoredPolys, 0x6D0CC0);
    RH_ScopedInstall(CalculateLightingFromCollision, 0x6D0CF0);
    RH_ScopedInstall(ProcessWheel, 0x6D6C00);
    RH_ScopedOverloadedInstall(IsPassenger, "Ped", 0x6D1BD0, bool(CVehicle::*)(CPed*) const);
    RH_ScopedOverloadedInstall(IsPassenger, "Int", 0x6D1C00, bool(CVehicle::*)(int32) const);
    RH_ScopedOverloadedInstall(IsDriver, "Ped", 0x6D1C40, bool(CVehicle::*)(CPed*) const);
    RH_ScopedOverloadedInstall(IsDriver, "Int", 0x6D1C60, bool(CVehicle::*)(int32) const);
    RH_ScopedInstall(ProcessBoatControl, 0x6DBCE0);
    RH_ScopedInstall(ChangeLawEnforcerState, 0x6D2330);
    RH_ScopedInstall(GetVehicleAppearance, 0x6D1080);
    RH_ScopedInstall(DoHeadLightBeam, 0x6E0E20);
    RH_ScopedInstall(GetPlaneNumGuns, 0x6D3F30, { .reversed = false }); // register problem?

    RH_ScopedInstall(CustomCarPlate_TextureCreate, 0x6D10E0, { .reversed = false });
    RH_ScopedInstall(CustomCarPlate_TextureDestroy, 0x6D1150, { .reversed = false });
    RH_ScopedInstall(CanBeDeleted, 0x6D1180);
    RH_ScopedInstall(ProcessWheelRotation, 0x6D1230);
    RH_ScopedInstall(CanVehicleBeDamaged, 0x6D1280, { .reversed = false });
    RH_ScopedInstall(ProcessDelayedExplosion, 0x6D1340, { .reversed = false });
    RH_ScopedOverloadedInstall(AddPassenger, "any-seat", 0x6D13A0, bool(CVehicle::*)(CPed*), { .reversed = false });
    RH_ScopedOverloadedInstall(AddPassenger, "at-set", 0x6D14D0, bool(CVehicle::*)(CPed*, uint8), { .reversed = false });
    RH_ScopedInstall(RemovePassenger, 0x6D1610, { .reversed = false });
    RH_ScopedInstall(SetDriver, 0x6D16A0, { .reversed = false });
    RH_ScopedInstall(RemoveDriver, 0x6D1950, { .reversed = false });
    RH_ScopedInstall(SetUpDriver, 0x6D1A50, { .reversed = false });
    RH_ScopedInstall(SetupPassenger, 0x6D1AA0, { .reversed = false });
    RH_ScopedInstall(KillPedsInVehicle, 0x6D1C80, { .reversed = false });
    RH_ScopedInstall(IsUpsideDown, 0x6D1D90);
    RH_ScopedInstall(IsOnItsSide, 0x6D1DD0);
    RH_ScopedInstall(CanPedOpenLocks, 0x6D1E20, { .reversed = false });
    RH_ScopedInstall(CanDoorsBeDamaged, 0x6D1E60, { .reversed = false });
    RH_ScopedInstall(CanPedEnterCar, 0x6D1E80, { .reversed = false });
    RH_ScopedInstall(ProcessCarAlarm, 0x6D21F0, { .reversed = false });
    RH_ScopedGlobalInstall(DestroyVehicleAndDriverAndPassengers, 0x6D2250, { .reversed = false });
    RH_ScopedInstall(IsVehicleNormal, 0x6D22F0);
    RH_ScopedInstall(IsLawEnforcementVehicle, 0x6D2370);
    RH_ScopedInstall(ExtinguishCarFire, 0x6D2460);
    RH_ScopedInstall(ActivateBomb, 0x6D24F0, { .reversed = false });
    RH_ScopedInstall(ActivateBombWhenEntered, 0x6D2570, { .reversed = false });
    RH_ScopedInstall(CarHasRoof, 0x6D25D0, { .reversed = false });
    RH_ScopedInstall(HeightAboveCeiling, 0x6D2600, { .reversed = false });
    RH_ScopedInstall(SetComponentVisibility, 0x6D2700, { .reversed = false });
    RH_ScopedInstall(ApplyBoatWaterResistance, 0x6D2740);
    RH_ScopedInstall(SetComponentAtomicAlpha, 0x6D2960);
    RH_ScopedInstall(UpdateClumpAlpha, 0x6D2980, { .reversed = false });
    RH_ScopedInstall(UpdatePassengerList, 0x6D29E0, { .reversed = false });
    RH_ScopedInstall(PickRandomPassenger, 0x6D2A10, { .reversed = false });
    RH_ScopedInstall(AddDamagedVehicleParticles, 0x6D2A80);
    RH_ScopedInstall(MakeDirty, 0x6D2BF0);
    RH_ScopedInstall(AddWheelDirtAndWater, 0x6D2D50, { .reversed = false });
    RH_ScopedInstall(SetGettingInFlags, 0x6D3000);
    RH_ScopedInstall(SetGettingOutFlags, 0x6D3020);
    RH_ScopedInstall(ClearGettingInFlags, 0x6D3040);
    RH_ScopedInstall(ClearGettingOutFlags, 0x6D3060);
    RH_ScopedInstall(SetWindowOpenFlag, 0x6D3080);
    RH_ScopedInstall(ClearWindowOpenFlag, 0x6D30B0);
    RH_ScopedInstall(SetVehicleUpgradeFlags, 0x6D30E0, { .reversed = false });
    RH_ScopedInstall(ClearVehicleUpgradeFlags, 0x6D3210, { .reversed = false });
    RH_ScopedInstall(CreateUpgradeAtomic, 0x6D3510, { .reversed = false });
    RH_ScopedInstall(RemoveUpgrade, 0x6D3630);
    RH_ScopedInstall(GetUpgrade, 0x6D3650);
    RH_ScopedInstall(CreateReplacementAtomic, 0x6D3700, { .reversed = false });
    RH_ScopedInstall(AddReplacementUpgrade, 0x6D3830, { .reversed = false });
    RH_ScopedInstall(RemoveReplacementUpgrade, 0x6D39E0, { .reversed = false });
    RH_ScopedInstall(GetReplacementUpgrade, 0x6D3A50);
    RH_ScopedInstall(RemoveAllUpgrades, 0x6D3AB0);
    RH_ScopedInstall(GetSpareHasslePosId, 0x6D3AE0, { .reversed = false });
    RH_ScopedInstall(SetHasslePosId, 0x6D3B30, { .reversed = false });
    RH_ScopedInstall(InitWinch, 0x6D3B60, { .reversed = false });
    RH_ScopedInstall(UpdateWinch, 0x6D3B80, { .reversed = false });
    RH_ScopedInstall(RemoveWinch, 0x6D3C70, { .reversed = false });
    RH_ScopedInstall(RenderDriverAndPassengers, 0x6D3D60);
    RH_ScopedInstall(PreRenderDriverAndPassengers, 0x6D3DB0);
    RH_ScopedInstall(GetPlaneGunsAutoAimAngle, 0x6D3E00);
    RH_ScopedInstall(SetFiringRateMultiplier, 0x6D4010);
    RH_ScopedInstall(GetFiringRateMultiplier, 0x6D4090);
    RH_ScopedInstall(GetPlaneGunsRateOfFire, 0x6D40E0);
    RH_ScopedInstall(GetPlaneGunsPosition, 0x6D4290, { .reversed = false });
    RH_ScopedInstall(GetPlaneOrdnanceRateOfFire, 0x6D4590, { .reversed = false });
    RH_ScopedInstall(GetPlaneOrdnancePosition, 0x6D46E0);
    RH_ScopedInstall(SelectPlaneWeapon, 0x6D4900, { .reversed = false });
    RH_ScopedInstall(DoPlaneGunFireFX, 0x6D4AD0, { .reversed = false });
    RH_ScopedInstall(FirePlaneGuns, 0x6D4D30, { .reversed = false });
    RH_ScopedInstall(FireUnguidedMissile, 0x6D5110, { .reversed = false });
    RH_ScopedInstall(CanBeDriven, 0x6D5400);
    RH_ScopedInstall(ReactToVehicleDamage, 0x6D5490, { .reversed = false });
    RH_ScopedInstall(GetVehicleLightsStatus, 0x6D55C0, { .reversed = false });
    RH_ScopedInstall(CanPedLeanOut, 0x6D5CF0, { .reversed = false });
    RH_ScopedInstall(SetVehicleCreatedBy, 0x6D5D70, { .reversed = false });
    RH_ScopedInstall(SetupRender, 0x6D64F0, { .reversed = false });
    RH_ScopedInstall(ProcessBikeWheel, 0x6D73B0, { .reversed = false });
    RH_ScopedInstall(FindTyreNearestPoint, 0x6D7BC0, { .reversed = false });
    RH_ScopedInstall(InflictDamage, 0x6D7C90, { .reversed = false });
    RH_ScopedInstall(KillPedsGettingInVehicle, 0x6D82F0, { .reversed = false });
    RH_ScopedInstall(UsesSiren, 0x6D8470);
    RH_ScopedInstall(IsSphereTouchingVehicle, 0x6D84D0);
    RH_ScopedInstall(FlyingControl, 0x6D85F0, { .reversed = false });
    RH_ScopedInstall(BladeColSectorList, 0x6DAF00, { .reversed = false });
    RH_ScopedInstall(SetComponentRotation, 0x6DBA30, { .reversed = false });
    RH_ScopedInstall(SetTransmissionRotation, 0x6DBBB0);
    RH_ScopedInstall(DoBoatSplashes, 0x6DD130, { .reversed = false });
    RH_ScopedInstall(DoSunGlare, 0x6DD6F0, { .reversed = false });
    RH_ScopedInstall(AddWaterSplashParticles, 0x6DDF60, { .reversed = false });
    RH_ScopedInstall(AddExhaustParticles, 0x6DE240);
    RH_ScopedInstall(AddSingleWheelParticles, 0x6DE880, { .reversed = false });
    RH_ScopedInstall(GetSpecialColModel, 0x6DF3D0, { .reversed = false });
    RH_ScopedInstall(RemoveVehicleUpgrade, 0x6DF930, { .reversed = false });
    RH_ScopedInstall(AddUpgrade, 0x6DFA20, { .reversed = false });
    RH_ScopedInstall(UpdateTrailerLink, 0x6DFC50, { .reversed = false });
    RH_ScopedInstall(UpdateTractorLink, 0x6E0050, { .reversed = false });
    RH_ScopedInstall(ScanAndMarkTargetForHeatSeekingMissile, 0x6E0400, { .reversed = false });
    RH_ScopedInstall(FireHeatSeakingMissile, 0x6E05C0, { .reversed = false });
    RH_ScopedInstall(PossiblyDropFreeFallBombForPlayer, 0x6E07E0, { .reversed = false });
    RH_ScopedInstall(ProcessSirenAndHorn, 0x6E0950, { .reversed = false });
    RH_ScopedInstall(DoHeadLightEffect, 0x6E0A50, { .reversed = false });
    RH_ScopedInstall(DoHeadLightReflectionSingle, 0x6E1440, { .reversed = false });
    RH_ScopedInstall(DoHeadLightReflectionTwin, 0x6E1600, { .reversed = false });
    RH_ScopedInstall(DoHeadLightReflection, 0x6E1720, { .reversed = false });
    RH_ScopedInstall(DoTailLightEffect, 0x6E1780, { .reversed = false });
    RH_ScopedInstall(DoVehicleLights, 0x6E1A60, { .reversed = false });
    RH_ScopedInstall(FillVehicleWithPeds, 0x6E2900, { .reversed = false });
    RH_ScopedInstall(DoBladeCollision, 0x6E2E50, { .reversed = false });
    RH_ScopedInstall(AddVehicleUpgrade, 0x6E3290, { .reversed = false });
    RH_ScopedInstall(SetupUpgradesAfterLoad, 0x6E3400, { .reversed = false });
    RH_ScopedInstall(GetPlaneWeaponFiringStatus, 0x6E3440, { .reversed = false });
    RH_ScopedInstall(ProcessWeapons, 0x6E3950, { .reversed = false });
    RH_ScopedInstall(DoFixedMachineGuns, 0x73F400, { .reversed = false });
    RH_ScopedInstall(FireFixedMachineGuns, 0x73DF00, { .reversed = false });
    RH_ScopedInstall(DoDriveByShootings, 0x741FD0, { .reversed = false });
    RH_ScopedInstall(ReleasePickedUpEntityWithWinch, 0x6D3CB0);
    RH_ScopedInstall(PickUpEntityWithWinch, 0x6D3CD0);
    RH_ScopedInstall(QueryPickedUpEntityWithWinch, 0x6D3CF0);
    RH_ScopedInstall(GetRopeHeightForHeli, 0x6D3D10);
    RH_ScopedInstall(SetRopeHeightForHeli, 0x6D3D30);

}

// 0x6D5F10
CVehicle::CVehicle(eVehicleCreatedBy createdBy) : CPhysical(), m_vehicleAudio(), m_autoPilot() {
    // plugin::CallMethod<0x6D5F10, CVehicle*, uint8>(this, createdBy);
    // return;

    m_bHasPreRenderEffects = true;
    m_nType = ENTITY_TYPE_VEHICLE;

    m_fRawSteerAngle = 0.0f;
    m_f2ndSteerAngle = 0.0f;
    m_nCurrentGear = 1;
    m_fGearChangeCount = 0.0f;
    m_fWheelSpinForAudio = 0.0f;
    m_nCreatedBy = createdBy;
    m_nForcedRandomRouteSeed = 0;

    m_nVehicleUpperFlags = 0;
    m_nVehicleLowerFlags = 0;
    vehicleFlags.bFreebies = true;
    vehicleFlags.bIsHandbrakeOn = true;
    vehicleFlags.bEngineOn = true;
    vehicleFlags.bCanBeDamaged = true;
    vehicleFlags.bParking = false;
    vehicleFlags.bRestingOnPhysical = false;
    vehicleFlags.bCreatedAsPoliceVehicle = false;
    vehicleFlags.bVehicleCanBeTargettedByHS = true;
    vehicleFlags.bWinchCanPickMeUp = true;
    vehicleFlags.bPetrolTankIsWeakPoint = true;
    vehicleFlags.bConsideredByPlayer = true;
    vehicleFlags.bDoesProvideCover = true;
    vehicleFlags.bUsedForReplay = false;
    vehicleFlags.bDontSetColourWhenRemapping = false;
    vehicleFlags.bUseCarCheats = false;
    vehicleFlags.bHasBeenResprayed = false;
    vehicleFlags.bNeverUseSmallerRemovalRange = false;
    vehicleFlags.bDriverLastFrame = false;

    auto fRand = static_cast<float>(CGeneral::GetRandomNumber()) / static_cast<float>(RAND_MAX);
    vehicleFlags.bCanPark = fRand < 0.0F; //BUG: Seemingly never true, CGeneral::GetRandomNumber() strips the sign bit to always be 0

    CCarCtrl::UpdateCarCount(this, false);
    m_nExtendedRemovalRange = 0;
    m_fHealth = 1000.0f;
    m_pDriver = nullptr;
    m_nNumPassengers = 0;
    m_nMaxPassengers = 8;
    m_nNumGettingIn = 0;
    m_nGettingInFlags = 0;
    m_nGettingOutFlags = 0;

    m_nBombOnBoard = 0;
    m_nOverrideLights = eVehicleOverrideLightsState::NO_CAR_LIGHT_OVERRIDE;
    m_nWinchType = 0;
    m_nGunsCycleIndex = 0;
    physicalFlags.bCanBeCollidedWith = true;

    m_nLastWeaponDamageType = -1;
    m_vehicleSpecialColIndex = -1;

    m_pWhoInstalledBombOnMe = nullptr;
    m_wBombTimer = 0;
    m_pWhoDetonatedMe = nullptr;
    m_nTimeWhenBlowedUp = 0;

    m_nPacMansCollected = 0;
    m_pFire = nullptr;
    m_nGunFiringTime = 0;
    m_nCopsInCarTimer = 0;
    m_nUsedForCover = 0;
    m_nHornCounter = 0;
    m_nRandomIdRelatedToSiren = 0;
    m_nCarHornTimer = 0;
    field_4EC = 0;
    m_pTractor = nullptr;
    m_pTrailer = nullptr;
    m_nTimeTillWeNeedThisCar = 0;
    m_nAlarmState = 0;
    m_nDoorLock = eCarLock::CARLOCK_UNLOCKED;
    m_nProjectileWeaponFiringTime = 0;
    m_nAdditionalProjectileWeaponFiringTime = 0;
    m_nTimeForMinigunFiring = 0;
    m_pLastDamageEntity = nullptr;
    m_pEntityWeAreOn = nullptr;
    m_fVehicleRearGroundZ = 0.0f;
    m_fVehicleFrontGroundZ = 0.0f;
    field_511 = 0;
    field_512 = 0;
    m_comedyControlState = eComedyControlState::INACTIVE;
    m_FrontCollPoly.m_bIsActual = false;
    m_RearCollPoly.m_bIsActual = false;
    m_pHandlingData = nullptr;
    m_nHandlingFlagsIntValue = static_cast<eVehicleHandlingFlags>(0);
    m_autoPilot.m_nCarMission = MISSION_NONE;
    m_autoPilot.m_nTempAction = 0;
    m_autoPilot.m_nTimeToStartMission = CTimer::GetTimeInMS();
    m_autoPilot.carCtrlFlags.bAvoidLevelTransitions = false;
    m_nRemapTxd = -1;
    m_nPreviousRemapTxd = -1;
    m_pRemapTexture = nullptr;
    m_pOverheatParticle = nullptr;
    m_pFireParticle = nullptr;
    m_pDustParticle = nullptr;
    m_pCustomCarPlate = nullptr;
    m_anUpgrades.fill(-1);
    m_fWheelScale = 1.0f;
    m_nWindowsOpenFlags = 0;
    m_nNitroBoosts = 0;
    m_nHasslePosId = 0;
    m_nVehicleWeaponInUse = CAR_WEAPON_NOT_USED;
    m_fDirtLevel = (float)((CGeneral::GetRandomNumber() % 15));
    m_nCreationTime = CTimer::GetTimeInMS();
    SetCollisionLighting(tColLighting(0x48));
}

// 0x6E2B40
CVehicle::~CVehicle() {
    CReplay::RecordVehicleDeleted(this);
    m_nAlarmState = 0;
    DeleteRwObject(); // V1053 Calling the 'DeleteRwObject' virtual function in the destructor may lead to unexpected result at runtime.
    CRadar::ClearBlipForEntity(eBlipType::BLIP_CAR, GetVehiclePool()->GetRef(this));

    if (m_pDriver) {
        m_pDriver->FlagToDestroyWhenNextProcessed();
    }


    for (const auto passenger : GetPassengers()) {
        if (passenger) {
            passenger->FlagToDestroyWhenNextProcessed();
        }
    }

    if (m_pFire) {
        m_pFire->Extinguish();
        m_pFire = nullptr;
    }

    CCarCtrl::UpdateCarCount(this, true);
    if (vehicleFlags.bIsAmbulanceOnDuty) {
        --CCarCtrl::NumAmbulancesOnDuty;
        vehicleFlags.bIsAmbulanceOnDuty = false;
    }

    if (vehicleFlags.bIsFireTruckOnDuty) {
        --CCarCtrl::NumFireTrucksOnDuty;
        vehicleFlags.bIsFireTruckOnDuty = false;
    }

    if (m_vehicleSpecialColIndex > -1) {
        m_aSpecialColVehicle[m_vehicleSpecialColIndex] = nullptr;
        m_vehicleSpecialColIndex = -1;
    }

    for (auto particle : { m_pOverheatParticle, m_pFireParticle, m_pDustParticle }) {
        if (particle) {
            g_fxMan.DestroyFxSystem(particle);
            particle = nullptr;
        }
    }

    if (m_pCustomCarPlate) {
        RwTextureDestroy(m_pCustomCarPlate);
        m_pCustomCarPlate = nullptr;
    }

    const auto iRopeInd = CRopes::FindRope(reinterpret_cast<uint32>(this) + 1);
    if (iRopeInd >= 0) {
        CRopes::GetRope(iRopeInd).Remove();
    }

    if (!physicalFlags.bDestroyed && m_fHealth < 250.0F) {
        CDarkel::RegisterCarBlownUpByPlayer(*this, 0);
    }
}

void* CVehicle::operator new(unsigned size) {
    return GetVehiclePool()->New();
}

void CVehicle::operator delete(void* data) {
    GetVehiclePool()->Delete(static_cast<CVehicle*>(data));
}

void* CVehicle::operator new(unsigned size, int32 poolRef) {
    return GetVehiclePool()->NewAt(poolRef);
}

void CVehicle::operator delete(void* data, int32 poolRef) {
    GetVehiclePool()->Delete(static_cast<CVehicle*>(data));
}

// 0x6D6A40
void CVehicle::SetModelIndex(uint32 index) {
    return CVehicle::SetModelIndex_Reversed(index);
}
void CVehicle::SetModelIndex_Reversed(uint32 index) {
    CEntity::SetModelIndex(index);
    auto mi = CModelInfo::GetModelInfo(index)->AsVehicleModelInfoPtr();
    CustomCarPlate_TextureCreate(mi);
    for (auto i = 0u; i < std::size(m_anExtras); i++) {
        m_anExtras[i] = CVehicleModelInfo::ms_compsUsed[i];
    }
    m_nMaxPassengers = CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(index);
    switch (m_nModelIndex) {
    case MODEL_RCBANDIT:
    case MODEL_RCBARON:
    case MODEL_RCRAIDER:
    case MODEL_RCGOBLIN:
    case MODEL_RCTIGER:
        vehicleFlags.bIsRCVehicle = true;
        break;
    default:
        vehicleFlags.bCreatedAsPoliceVehicle = false;
        vehicleFlags.bIsRCVehicle = false;
        break;
    }

    // Set up weapons
    switch (m_nModelIndex) {
    case MODEL_RUSTLER:
    case MODEL_STUNT:
        m_nVehicleWeaponInUse = CAR_WEAPON_HEAVY_GUN;
        break;
    case MODEL_BEAGLE:
        m_nVehicleWeaponInUse = CAR_WEAPON_FREEFALL_BOMB;
        break;
    case MODEL_HYDRA:
    case MODEL_TORNADO:
        m_nVehicleWeaponInUse = CAR_WEAPON_LOCK_ON_ROCKET;
        break;
    }
}

// 0x6D6410
void CVehicle::DeleteRwObject() {
    CVehicle::DeleteRwObject_Reversed();
}
void CVehicle::DeleteRwObject_Reversed() {
    SetRemapTexDictionary(-1);
    RemoveAllUpgrades();
    CEntity::DeleteRwObject();
}

// 0x6D6640
void CVehicle::SpecialEntityPreCollisionStuff(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled,
    bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck) {
    CVehicle::SpecialEntityPreCollisionStuff_Reversed(colPhysical, bIgnoreStuckCheck, bCollisionDisabled, bCollidedEntityCollisionIgnored, bCollidedEntityUnableToMove, bThisOrCollidedEntityStuck);
}
void CVehicle::SpecialEntityPreCollisionStuff_Reversed(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled,
    bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck) {
    if (colPhysical->IsPed()
        && colPhysical->AsPed()->bKnockedOffBike
        && colPhysical->AsPed()->m_pVehicle == this)
    {
        bCollisionDisabled = true;
        return;
    }

    if (physicalFlags.bSubmergedInWater
        && m_nStatus != eEntityStatus::STATUS_PLAYER
        && (m_nStatus != eEntityStatus::STATUS_REMOTE_CONTROLLED && colPhysical->DoesNotCollideWithFlyers())) //Bug? Seems like it should check for it being heli
    {
        bCollisionDisabled = true;
        return;
    }

    if (m_pEntityIgnoredCollision == colPhysical || colPhysical->m_pEntityIgnoredCollision == this) {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.bSkipLineCol = true;
        return;
    }

    if (m_pAttachedTo == colPhysical) {
        bCollidedEntityCollisionIgnored = true;
        return;
    }

    if (colPhysical->m_pAttachedTo == this) {
        bCollisionDisabled = true;
        physicalFlags.bSkipLineCol = true;
        return;
    }

    if (physicalFlags.bDisableCollisionForce && colPhysical->physicalFlags.bDisableCollisionForce) {
        bCollisionDisabled = true;
        return;
    }

    if (m_bIsStuck
        && colPhysical->IsVehicle()
        && (colPhysical->AsVehicle()->physicalFlags.bDisableCollisionForce && !colPhysical->AsVehicle()->physicalFlags.bCollidable)
    ) {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.bSkipLineCol = true;
        return;
    }

    if (colPhysical->IsImmovable()) {
        if (bIgnoreStuckCheck)
            bCollidedEntityCollisionIgnored = true;
        else if (m_bIsStuck || colPhysical->m_bIsStuck)
            bThisOrCollidedEntityStuck = true;

        return;
    }

    if (colPhysical->IsObject())
    {
        if (colPhysical->AsObject()->IsFallenLampPost())
        {
            bCollisionDisabled = true;
            colPhysical->AsObject()->m_pEntityIgnoredCollision = this;
        }
        else
        {
            if (colPhysical->IsModelTempCollision())
            {
                bCollisionDisabled = true;
                return;
            }

            if (colPhysical->AsObject()->IsTemporary()
                || colPhysical->AsObject()->IsExploded()
                || !colPhysical->IsStatic())
            {
                if (IsConstructionVehicle())
                {
                    if (m_bIsStuck || colPhysical->m_bIsStuck)
                        bThisOrCollidedEntityStuck = true;
                }
                else if (!colPhysical->AsObject()->CanBeSmashed() && !IsBike())
                {
                    auto tempMat = CMatrix();
                    auto* cm = colPhysical->GetColModel();
                    auto& vecMax = cm->GetBoundingBox().m_vecMax;
                    if (vecMax.x < 1.0F && vecMax.y < 1.0F && vecMax.z < 1.0F)
                    {
                        const auto vecSize = cm->GetBoundingBox().GetSize();
                        const auto vecTransformed = *colPhysical->m_matrix * vecSize;

                        if (GetPosition().z > vecTransformed.z)
                            bCollidedEntityCollisionIgnored = true;
                        else
                        {
                            Invert(*m_matrix, tempMat);
                            if ((tempMat * vecTransformed).z < 0.0F)
                                bCollidedEntityCollisionIgnored = true;
                        }
                    }
                }
            }

            if (!bCollidedEntityCollisionIgnored
                && !bCollisionDisabled
                && !bThisOrCollidedEntityStuck
                && colPhysical->m_bIsStuck)
            {
                bCollidedEntityUnableToMove = true;
            }
            return;
        }
    }

    if (colPhysical->IsRCCar()) {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.bSkipLineCol = true;
        return;
    }

    if (IsRCCar() && (colPhysical->IsVehicle() || colPhysical->IsPed())) {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.bSkipLineCol = true;
        return;
    }

    if (colPhysical == m_pTractor || colPhysical == m_pTrailer) {
        bThisOrCollidedEntityStuck = true;
        physicalFlags.bSkipLineCol = true;
        return;
    }

    if (colPhysical->m_bIsStuck) {
        bCollidedEntityUnableToMove = true;
        return;
    }
}

// 0x6D0E90
uint8 CVehicle::SpecialEntityCalcCollisionSteps(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2) {
    return CVehicle::SpecialEntityCalcCollisionSteps_Reversed(bProcessCollisionBeforeSettingTimeStep, unk2);
}
uint8 CVehicle::SpecialEntityCalcCollisionSteps_Reversed(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2) {
    if (physicalFlags.bDisableCollisionForce)
        return 1;

    const auto fMoveSquared = m_vecMoveSpeed.SquaredMagnitude() * sq(CTimer::GetTimeStep());
    if (fMoveSquared < 0.16F)
        return 1;

    auto fMove = sqrt(fMoveSquared);
    if (m_nStatus != eEntityStatus::STATUS_PLAYER)
    {
        if (fMoveSquared <= 0.32F)
            fMove *= (10.0F / 4.0F);
        else
            fMove *= (10.0F / 3.0F);
    }
    else if (IsBike())
        fMove *= (10.0F / 1.5F);
    else
        fMove *= (10.0F / 2.0F);

    auto& bbox = CEntity::GetColModel()->GetBoundingBox();
    auto fLongestDir = std::fabs(DotProduct(m_vecMoveSpeed, GetForward()) * CTimer::GetTimeStep() / bbox.GetLength());
    fLongestDir = std::max(fLongestDir, std::fabs(DotProduct(m_vecMoveSpeed, GetRight()) * CTimer::GetTimeStep() / bbox.GetWidth()));
    fLongestDir = std::max(fLongestDir, std::fabs(DotProduct(m_vecMoveSpeed, GetUp()) * CTimer::GetTimeStep() / bbox.GetHeight()));

    if (IsBike())
        fLongestDir *= 1.5F;

    if (fLongestDir < 1.0F)
        bProcessCollisionBeforeSettingTimeStep = true;
    else if (fLongestDir < 2.0F)
        unk2 = true;

    return static_cast<uint8>(ceil(fMove));
}

// 0x6D6480
void CVehicle::PreRender() {
    return CVehicle::PreRender_Reversed();
}
void CVehicle::PreRender_Reversed() {
    if (!IsTrain())
        CalculateLightingFromCollision();

    PreRenderDriverAndPassengers();
    if (CModelInfo::GetModelInfo(m_nModelIndex)->m_n2dfxCount)
        CEntity::ProcessLightsForEntity();

    m_renderLights.m_bRightFront = false;
    m_renderLights.m_bLeftFront = false;
    m_renderLights.m_bRightRear = false;
    m_renderLights.m_bLeftRear = false;

    const auto fCoeff = CPhysical::GetLightingFromCol(false) * 0.4F;
    GetVehicleModelInfo()->SetEnvMapCoeff(fCoeff);
}

void CVehicle::Render() {
    return CVehicle::Render_Reversed();
}
void CVehicle::Render_Reversed() {
    auto* mi = GetVehicleModelInfo();
    const auto iDirtLevel = static_cast<int32>(m_fDirtLevel) & 0xF;
    CVehicleModelInfo::SetDirtTextures(mi, iDirtLevel);

    CEntity::Render();
}

bool CVehicle::SetupLighting() {
    return CVehicle::SetupLighting_Reversed();
}
bool CVehicle::SetupLighting_Reversed() {
    ActivateDirectional();
    return CRenderer::SetupLightingForEntity(this);
}

void CVehicle::RemoveLighting(bool bRemove) {
    CVehicle::RemoveLighting_Reversed(bRemove);
}
void CVehicle::RemoveLighting_Reversed(bool bRemove) {
    if (!physicalFlags.bDestroyed)
        CPointLights::RemoveLightsAffectingObject();

    SetAmbientColours();
    DeActivateDirectional();
}

// 0x871EF0
void CVehicle::ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime) {
    CVehicle::ProcessOpenDoor_Reversed(ped, doorComponentId, animGroup, animId, fTime);
}
void CVehicle::ProcessOpenDoor_Reversed(CPed* ped, uint32 doorComponentId_, uint32 animGroup, uint32 animId, float fTime) {
    auto doorComponentId = (int32)doorComponentId_; // silence warns, todo: OpenDoor receives int32, why?
    eDoors iCheckedDoor = [&] {
        switch (doorComponentId) {
        case COMPONENT_DOOR_RF:
            return DOOR_RIGHT_FRONT;
        case COMPONENT_DOOR_LR:
            return DOOR_RIGHT_REAR;
        case COMPONENT_DOOR_RR:
            return DOOR_LEFT_FRONT;
        case COMPONENT_WING_LF:
            return DOOR_LEFT_REAR;
        default:
            assert(false); // Shouldn't get here
            return static_cast<eDoors>(fTime);
        }
    }();

    if (IsDoorMissing(iCheckedDoor)) {
        return;
    }

    const auto group = static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup);
    float fAnimStart, fAnimEnd;
    switch (animId) {
    case ANIM_ID_CAR_OPEN_LHS:
    case ANIM_ID_CAR_OPEN_RHS:
    case ANIM_ID_CAR_OPEN_LHS_1:
    case ANIM_ID_CAR_OPEN_RHS_1: {
        CVehicleAnimGroupData::GetInOutTimings(group, eInOutTimingMode::OPEN_START, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, false);
        } else if (fTime > fAnimEnd) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        } else if (fTime > fAnimStart && fTime < fAnimEnd) {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio) {
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
            }
        }

        return;
    }
    case ANIM_ID_CAR_CLOSE_LHS_0:
    case ANIM_ID_CAR_CLOSE_RHS_0:
    case ANIM_ID_CAR_CLOSE_LHS_1:
    case ANIM_ID_CAR_CLOSE_RHS_1: {
        CVehicleAnimGroupData::GetInOutTimings(group, eInOutTimingMode::CLOSE_STOP, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        } else if (fTime > fAnimEnd) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        } else if (fTime > fAnimStart && fTime < fAnimEnd) {
            const auto fNewRatio = 1.0F - invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio) {
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
            }
        }
        return;
    }
    case ANIM_ID_CAR_CLOSEDOOR_LHS_0:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_0:
    case ANIM_ID_CAR_CLOSEDOOR_LHS_1:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_1: {
        CVehicleAnimGroupData::GetInOutTimings(group, eInOutTimingMode::OPEN_STOP, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        } else if (fTime > fAnimEnd) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        } else if (fTime > fAnimStart && fTime < fAnimEnd) {
            const auto fNewRatio = 1.0F - invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio) {
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
            }
        }
        return;
    }
    case ANIM_ID_CAR_GETOUT_LHS_0:
    case ANIM_ID_CAR_GETOUT_RHS_0:
    case ANIM_ID_CAR_GETOUT_LHS_1:
    case ANIM_ID_CAR_GETOUT_RHS_1: {
        CVehicleAnimGroupData::GetInOutTimings(group, eInOutTimingMode::CLOST_START, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        } else if (fTime > fAnimEnd) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        } else if (fTime > fAnimStart && fTime < fAnimEnd) {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio) {
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
            }
        }
        return;
    }
    case ANIM_ID_CAR_JACKEDLHS:
    case ANIM_ID_CAR_JACKEDRHS:
        if (fTime < 0.1F) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        } else if (fTime > 0.4F) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        } else if (fTime > 0.1F && fTime < 0.4F) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, (fTime - 0.1F) * (10.0F / 3.0F), true);
        }
        return;

    case ANIM_ID_CAR_FALLOUT_LHS:
    case ANIM_ID_CAR_FALLOUT_RHS:
        if (fTime < 0.1F) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        } else if (fTime > 0.4F) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        } else if (fTime > 0.1F && fTime < 0.4F) {
            OpenDoor(ped, doorComponentId, iCheckedDoor, (fTime - 0.1F) * (10.0F / 3.0F), true);
        }

        return;

    case ANIM_ID_CAR_PULLOUT_LHS:
    case ANIM_ID_CAR_PULLOUT_RHS:
    case ANIM_ID_UNKNOWN_15:
        switch (animGroup) {
        case ANIM_GROUP_STDCARAMIMS:
        case ANIM_GROUP_LOWCARAMIMS:
        case ANIM_GROUP_TRKCARANIMS:
        case ANIM_GROUP_COACHCARANIMS:
        case ANIM_GROUP_BUSCARANIMS:
        case ANIM_GROUP_CONVCARANIMS:
        case ANIM_GROUP_MTRKCARANIMS:
        case ANIM_GROUP_STDTALLCARAMIMS:
        case ANIM_GROUP_BFINJCARAMIMS:
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        }
        return;

    case ANIM_ID_CAR_ROLLOUT_LHS:
    case ANIM_ID_CAR_ROLLOUT_RHS: {
        switch (animGroup) {
        case ANIM_GROUP_STDCARAMIMS:
        case ANIM_GROUP_LOWCARAMIMS:
        case ANIM_GROUP_TRKCARANIMS:
        case ANIM_GROUP_RUSTPLANEANIMS:
        case ANIM_GROUP_COACHCARANIMS:
        case ANIM_GROUP_CONVCARANIMS:
        case ANIM_GROUP_MTRKCARANIMS:
        case ANIM_GROUP_STDTALLCARAMIMS:
        case ANIM_GROUP_BFINJCARAMIMS:
            fAnimStart = 0.01F;
            fAnimEnd = 0.1F;
            break;
        default:
            assert(false); // Shouldn't ever enter this
            break;
        }

        if (fTime < fAnimStart)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimEnd)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd) {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio) {
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
            }
        }

        return;
    }

    case ANIM_ID_CAR_ROLLDOOR: {
        float fAnimEnd2;
        switch (animGroup) {
        case ANIM_GROUP_STDCARAMIMS:
        case ANIM_GROUP_LOWCARAMIMS:
        case ANIM_GROUP_TRKCARANIMS:
        case ANIM_GROUP_RUSTPLANEANIMS:
        case ANIM_GROUP_COACHCARANIMS:
        case ANIM_GROUP_CONVCARANIMS:
        case ANIM_GROUP_MTRKCARANIMS:
        case ANIM_GROUP_STDTALLCARAMIMS:
        case ANIM_GROUP_BFINJCARAMIMS:
            fAnimStart = 0.05f;
            fAnimEnd = 0.3f;
            fAnimEnd2 = 0.475f;
            break;
        default:
            assert(false); // Shouldn't ever enter this
            break;
        }

        if (fTime > fAnimEnd2)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd) {
            const auto fNewRatio = invLerp(fAnimStart, 0.2F, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio) {
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
            }
        } else if (fTime > fAnimEnd && fTime < fAnimEnd2) {
            const auto fNewRatio = 1.0F - invLerp(fAnimEnd, fAnimEnd2, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio > fNewRatio)
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
    }
    }
}

// 0x6DF4A0
void CVehicle::ProcessDrivingAnims(CPed* driver, bool blend) {
    CVehicle::ProcessDrivingAnims_Reversed(driver, blend);
}
void CVehicle::ProcessDrivingAnims_Reversed(CPed* driver, bool blend) {
    if (m_bOffscreen || !driver->IsPlayer())
        return;

    auto* radioTuneAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_CAR_TUNE_RADIO);
    if (blend) {
        radioTuneAnim = CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CAR_TUNE_RADIO, 4.0F);
    }

    if (radioTuneAnim)
        return;

    CRideAnims* usedAnims;
    if (vehicleFlags.bLowVehicle)
        usedAnims = &aDriveAnimIdsLow;
    else if (IsBoat() && !m_pHandlingData->m_bSitInBoat)
        usedAnims = &aDriveAnimIdsBoat;
    else if (CVehicleAnimGroupData::UsesKartDrivingAnims(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup)))
        usedAnims = &aDriveAnimIdsKart;
    else if (CVehicleAnimGroupData::UsesTruckDrivingAnims(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup)))
        usedAnims = &aDriveAnimIdsTruck;
    else {
        const auto fDrivingSkill = CStats::GetStatValue(eStats::STAT_DRIVING_SKILL);
        const auto fSpeed = m_vecMoveSpeed.Magnitude();
        if (fDrivingSkill < 50.0F) {
            usedAnims = fSpeed <= 0.4F ? &aDriveAnimIdsBadSlow : &aDriveAnimIdsBad;
        } else if (fDrivingSkill < 100.0F) {
            usedAnims = fSpeed <= 0.4F ? &aDriveAnimIdsStdSlow : &aDriveAnimIdsStd;
        } else {
            usedAnims = fSpeed <= 0.4F ? &aDriveAnimIdsProSlow : &aDriveAnimIdsPro;
        }
    }

    // 0x6DF620
    auto* idleAnim      = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->idle);
    auto* lookLeftAnim  = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->left);
    auto* lookRightAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->right);
    auto* lookBackAnim  = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->back);

    if (!idleAnim) {
        if (RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_CAR_SIT)) {
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->idle, 4.0F);
        }
        return;
    }

    if (idleAnim->m_fBlendAmount < 1.0F)
        return;

    if (lookBackAnim
        && CCamera::GetActiveCamera().m_nMode == eCamMode::MODE_1STPERSON
        && CCamera::GetActiveCamera().m_nDirectionWasLooking == eLookingDirection::LOOKING_DIRECTION_BEHIND
    ) {
        lookBackAnim->m_fBlendDelta = -1000.0F;
    }

    // 0x6DF6DA
    auto* driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBY_L);
    if (!driveByAnim) driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBY_R);
    if (!driveByAnim) driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBYL_L);
    if (!driveByAnim) driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBYL_R);

    if (!vehicleFlags.bLowVehicle
        && m_fGasPedal < 0.0F
        && !driveByAnim
        && GetVehicleAppearance() != VEHICLE_APPEARANCE_HELI
        && GetVehicleAppearance() != VEHICLE_APPEARANCE_PLANE
    ) {
        if ((CCamera::GetActiveCamera().m_nMode != eCamMode::MODE_1STPERSON
            || CCamera::GetActiveCamera().m_nDirectionWasLooking != eLookingDirection::LOOKING_DIRECTION_BEHIND)
            && (!lookBackAnim || lookBackAnim->m_fBlendAmount < 1.0F && lookBackAnim->m_fBlendDelta <= 0.0F)
        ) {
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->back, 4.0F);
        }
        return;
    }

    if (m_fSteerAngle == 0.0F || driveByAnim) {
        if (lookLeftAnim)  lookLeftAnim->m_fBlendDelta  = -4.0F;
        if (lookRightAnim) lookRightAnim->m_fBlendDelta = -4.0F;
        if (lookBackAnim)  lookBackAnim->m_fBlendDelta  = -4.0F;
        return;
    }

    auto fUsedAngle = std::fabs(m_fSteerAngle / 0.61F);
    fUsedAngle = std::clamp(fUsedAngle, 0.0F, 1.0F);

    if (m_fSteerAngle < 0) {
        if (lookLeftAnim) {
            lookLeftAnim->m_fBlendAmount = 0.0F;
            lookLeftAnim->m_fBlendDelta  = 0.0F;
        }
        if (lookRightAnim) {
            lookRightAnim->m_fBlendAmount = fUsedAngle;
            lookRightAnim->m_fBlendDelta  = 0.0F;
        } else {
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->right, 4.0F);
        }
    } else {
        if (lookRightAnim) {
            lookRightAnim->m_fBlendAmount = 0.0f;
            lookRightAnim->m_fBlendDelta = 0.0F;
        }
        if (lookLeftAnim) {
            lookLeftAnim->m_fBlendAmount = fUsedAngle;
            lookLeftAnim->m_fBlendDelta = 0.0F;
        } else {
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->left, 4.0F);
        }
    }

    if (lookBackAnim) {
        lookBackAnim->m_fBlendDelta = -4.0F;
    }
}

// 0x871F54
float CVehicle::GetHeightAboveRoad() {
    return CVehicle::GetHeightAboveRoad_Reversed();
}
float CVehicle::GetHeightAboveRoad_Reversed() {
    return CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMin.z * -1.0F;
}

// 0x6D1F30
bool CVehicle::CanPedStepOutCar(bool bIgnoreSpeedUpright) const {
    return CVehicle::CanPedStepOutCar_Reversed(bIgnoreSpeedUpright);
}
bool CVehicle::CanPedStepOutCar_Reversed(bool bIgnoreSpeedUpright) const {
    auto const fUpZ = m_matrix->GetUp().z;
    if (std::fabs(fUpZ) <= 0.1F) {
        if (std::fabs(m_vecMoveSpeed.z) > 0.05F || m_vecMoveSpeed.Magnitude2D() > 0.01F || m_vecTurnSpeed.SquaredMagnitude() > 0.0004F) { // 0.02F / 50.0f
            return false;
        }
        return true;
    }

    if (IsBoat())
        return true;

    if (bIgnoreSpeedUpright)
        return m_vecTurnSpeed.SquaredMagnitude() > 0.0004F;

    return m_vecMoveSpeed.Magnitude2D() <= 0.01F &&
           std::fabs(m_vecMoveSpeed.z) <= 0.05F &&
           m_vecTurnSpeed.SquaredMagnitude() <= 0.0004F;
}

// 0x6D2030
bool CVehicle::CanPedJumpOutCar(CPed* ped) {
    return CVehicle::CanPedJumpOutCar_Reversed(ped);
}
bool CVehicle::CanPedJumpOutCar_Reversed(CPed* ped) {
    if (IsBike())
    {
        if (!m_apPassengers[0] || ped == m_apPassengers[0])
            return m_vecMoveSpeed.SquaredMagnitude2D() >= 0.07F;

        return false;
    }

    const auto fHorSpeedSquared = m_vecMoveSpeed.SquaredMagnitude2D();
    if (!IsSubPlane()
        && !IsSubHeli()
        && (!IsAutomobile() || m_matrix->GetUp().z >= 0.3F || m_nLastCollisionTime <= CTimer::GetTimeInMS() - 1000))
    {
        return fHorSpeedSquared >= 0.1F && fHorSpeedSquared <= 0.5F;
    }

    if (fHorSpeedSquared >= 0.1F)
        return true;

    if (CanPedStepOutCar(false))
        return false;

    m_vecTurnSpeed *= 0.9F; // BUG(PRONE): We are modifying vehicle move and turn speeds in function that seems that it should be const
    auto const fMoveSpeedSquared = m_vecMoveSpeed.SquaredMagnitude();
    if (fMoveSpeedSquared / 100.0F > sq(CTimer::GetTimeStep()) * sq(0.008F))
    {
        m_vecMoveSpeed *= 0.9F;
        return false;
    }

    auto fMoveMult = CTimer::GetTimeStep() / std::sqrt(fMoveSpeedSquared) * 0.016F;
    fMoveMult = std::max(0.0F, 1.0F - fMoveMult);
    m_vecMoveSpeed *= fMoveMult;
    return false;
}

// 0x871F6C
bool CVehicle::GetTowHitchPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) {
    return CVehicle::GetTowHitchPos_Reversed(outPos, bCheckModelInfo, vehicle);
}
bool CVehicle::GetTowHitchPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) {
    if (!bCheckModelInfo)
        return false;

    auto const fColFront = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMax.y;
    outPos.Set(0.0F, fColFront + 1.0F, 0.0F);
    outPos = *m_matrix * outPos;
    return true;
}

// 0x871F70
bool CVehicle::GetTowBarPos(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) {
    return CVehicle::GetTowBarPos_Reversed(outPos, bCheckModelInfo, vehicle);
}
bool CVehicle::GetTowBarPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* vehicle) {
    if (!bCheckModelInfo)
        return false;

    auto const fColRear = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMin.y;
    outPos.Set(0.0F, fColRear - 1.0F, 0.0F);
    outPos = *m_matrix * outPos;
    return true;
}

// 0x871F80
bool CVehicle::Save() {
    return CVehicle::Save_Reversed();
}
bool CVehicle::Save_Reversed() {
    uint32 size = sizeof(CVehicleSaveStructure);
    CVehicleSaveStructure data;
    data.Construct(this);
    CGenericGameStorage::SaveDataToWorkBuffer(&size, sizeof(uint32)); // Unused, game ignores it on load and uses const value
    CGenericGameStorage::SaveDataToWorkBuffer(&data, size);
    return true;
}

// 0x871F84
bool CVehicle::Load() {
    return CVehicle::Load_Reversed();
}
bool CVehicle::Load_Reversed() {
    uint32 size;
    CVehicleSaveStructure data;
    CGenericGameStorage::LoadDataFromWorkBuffer(&size, sizeof(uint32));
    CGenericGameStorage::LoadDataFromWorkBuffer(&data, sizeof(CVehicleSaveStructure)); // BUG: Should use the value readen line above this, not constant
    data.Extract(this);
    return true;
}

// 0x6D0B40
void CVehicle::Shutdown() {
    for (auto& specialColModel : m_aSpecialColModel) {
        if (specialColModel.m_pColData) {
            specialColModel.RemoveCollisionVolumes();
        }
    }
}

// -1 if no remap index
// 0x6D0B70
int32 CVehicle::GetRemapIndex() {
    auto* mi = GetVehicleModelInfo();
    if (mi->GetNumRemaps() <= 0) {
        return -1;
    }

    for (auto i = 0; i < mi->GetNumRemaps(); ++i) {
        if (mi->m_anRemapTxds[i] == m_nPreviousRemapTxd) {
            return i;
        }
    }
    return -1;
}

// 0x6D0BC0
void CVehicle::SetRemapTexDictionary(int32 txdId) {
    if (txdId != m_nPreviousRemapTxd) {
        if (txdId == -1) {
            m_pRemapTexture = nullptr;
            CTxdStore::RemoveRef(m_nPreviousRemapTxd);
            m_nPreviousRemapTxd = -1;
        }
        m_nRemapTxd = txdId;
    }
}

// index for m_awRemapTxds[] array
// 0x6D0C00
void CVehicle::SetRemap(int32 remapIndex) {
    if (remapIndex == -1) {
        SetRemapTexDictionary(-1);
    } else {
        auto const infoRemapInd = GetVehicleModelInfo()->m_anRemapTxds[remapIndex];
        SetRemapTexDictionary(infoRemapInd);
    }
}

// 0x6D0CA0
void CVehicle::SetCollisionLighting(tColLighting lighting) {
    std::ranges::fill(m_anCollisionLighting, lighting);
}

// 0x6D0CC0
void CVehicle::UpdateLightingFromStoredPolys() {
    m_anCollisionLighting[0] = m_FrontCollPoly.m_nLighting;
    m_anCollisionLighting[1] = m_FrontCollPoly.m_nLighting;

    m_anCollisionLighting[2] = m_RearCollPoly.m_nLighting;
    m_anCollisionLighting[3] = m_RearCollPoly.m_nLighting;
}

// 0x6D0CF0
void CVehicle::CalculateLightingFromCollision() {
    float fAvgLight = 0.0F;
    for (auto& colLighting : m_anCollisionLighting) {
        fAvgLight += colLighting.GetCurrentLighting();
    }

    fAvgLight /= 4.0F;
    m_fContactSurfaceBrightness = fAvgLight;

}

// 0x6D0E20
void CVehicle::ResetAfterRender() {
    ((void(__thiscall*)(CVehicle*))0x6D0E20)(this);
}

// 0x6D1080
eVehicleAppearance CVehicle::GetVehicleAppearance() const {
    uint32 flags = (
        m_pHandlingData->m_nModelFlags &
        (
            VEHICLE_HANDLING_MODEL_IS_BOAT |
            VEHICLE_HANDLING_MODEL_IS_PLANE |
            VEHICLE_HANDLING_MODEL_IS_HELI |
            VEHICLE_HANDLING_MODEL_IS_BIKE
        )
    );

    if (flags <= VEHICLE_HANDLING_MODEL_IS_HELI) {
        switch (flags) {
        case VEHICLE_HANDLING_MODEL_IS_HELI:
            return VEHICLE_APPEARANCE_HELI;
        case VEHICLE_HANDLING_MODEL_NONE:
            return VEHICLE_APPEARANCE_AUTOMOBILE;
        case VEHICLE_HANDLING_MODEL_IS_BIKE:
            return VEHICLE_APPEARANCE_BIKE;
        }
        return VEHICLE_APPEARANCE_NONE;
    }

    if (flags == VEHICLE_HANDLING_MODEL_IS_PLANE)
        return VEHICLE_APPEARANCE_PLANE;

    if (flags != VEHICLE_HANDLING_MODEL_IS_BOAT)
        return VEHICLE_APPEARANCE_NONE;

    return VEHICLE_APPEARANCE_BOAT;
}

// returns false if vehicle model has no car plate material
// 0x6D10E0
bool CVehicle::CustomCarPlate_TextureCreate(CVehicleModelInfo* model) {
    return plugin::CallMethodAndReturn<bool, 0x6D10E0, CVehicle*, CVehicleModelInfo*>(this, model);
}

// 0x6D1150
void CVehicle::CustomCarPlate_TextureDestroy() {
    ((void(__thiscall*)(CVehicle*))0x6D1150)(this);
}

// 0x6D1180
bool CVehicle::CanBeDeleted() {
    if (m_nNumGettingIn || m_nGettingOutFlags)
        return false;

    if (m_pDriver) {
        if (m_pDriver->IsCreatedByMission())
            return false;

        if (!m_pDriver->IsStateDriving() && !m_pDriver->IsStateDead())
            return false;
    }

    for (auto passenger : m_apPassengers) {
        if (passenger) {
            if (passenger->IsCreatedByMission())
                return false;

            if (!passenger->IsStateDriving() && !passenger->IsStateDead()) // OG: checked twice
                return false;
        }
    }

    switch (m_nCreatedBy) {
    case MISSION_VEHICLE:
    case PERMANENT_VEHICLE:
        return false;
    default:
        return true;
    }
}

// 0x6D1230
float CVehicle::ProcessWheelRotation(tWheelState wheelState, const CVector& arg1, const CVector& arg2, float arg3) {
    if (wheelState == WHEEL_STATE_SPINNING)
        return -1.1f;

    if (wheelState == WHEEL_STATE_FIXED)
        return 0.0f;

    const auto angle = DotProduct(arg1, arg2) / arg3;
    return -angle;
}

// 0x6D1280
bool CVehicle::CanVehicleBeDamaged(CEntity* damager, eWeaponType weapon, bool& bDamagedDueToFireOrExplosionOrBullet) {
    if (!vehicleFlags.bCanBeDamaged)
        return false;

    const auto player = FindPlayerPed();
    const auto vehicle = FindPlayerVehicle();
    if (   m_nStatus != STATUS_PLAYER
        && physicalFlags.bInvulnerable
        && damager != player
        && damager != vehicle
    ) {
        return false;
    }

    if (player && damager == player && player->m_pAttachedTo == this)
        return false;

    bDamagedDueToFireOrExplosionOrBullet = false;
    if (CanPhysicalBeDamaged(weapon, &bDamagedDueToFireOrExplosionOrBullet)) {
        return !bDamagedDueToFireOrExplosionOrBullet || m_nStatus != STATUS_PLAYER || m_fHealth >= 250.0f;
    } else {
        return false;
    }
}

// 0x6D1340
void CVehicle::ProcessDelayedExplosion() {
    ((void(__thiscall*)(CVehicle*))0x6D1340)(this);
}

// 0x6D13A0
bool CVehicle::AddPassenger(CPed* passenger) {
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D13A0)(this, passenger);
}

// 0x6D14D0
bool CVehicle::AddPassenger(CPed* passenger, uint8 seatNumber) {
    return ((bool(__thiscall*)(CVehicle*, CPed*, uint8))0x6D14D0)(this, passenger, seatNumber);
}

// 0x6D1610
void CVehicle::RemovePassenger(CPed* passenger) {
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D1610)(this, passenger);
}

// 0x6D16A0
void CVehicle::SetDriver(CPed* driver) {
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D16A0)(this, driver);
}

// 0x6D1950
void CVehicle::RemoveDriver(bool arg0) {
    ((void(__thiscall*)(CVehicle*, bool))0x6D1950)(this, arg0);
}

// 0x6D1A50
CPed* CVehicle::SetUpDriver(int32 pedType, bool arg1, bool arg2) {
    return ((CPed * (__thiscall*)(CVehicle*, int32, bool, bool))0x6D1A50)(this, pedType, arg1, arg2);
}

// 0x6D1AA0
CPed* CVehicle::SetupPassenger(int32 seatNumber, int32 pedType, bool arg2, bool arg3) {
    return ((CPed * (__thiscall*)(CVehicle*, int32, int32, bool, bool))0x6D1AA0)(this, seatNumber, pedType, arg2, arg3);
}

// 0x6D1BD0
bool CVehicle::IsPassenger(CPed* ped) const {
    if (!ped)
        return false;

    for (const auto& passenger : m_apPassengers) {
        if (passenger == ped) {
            return true;
        }
    }
    return false;
}

// 0x6D1C00
bool CVehicle::IsPassenger(int32 modelIndex) const {
    for (const auto& passenger : m_apPassengers) {
        if (passenger && passenger->m_nModelIndex == modelIndex) {
            return true;
        }
    }
    return false;
}

bool CVehicle::IsPedOfModelInside(eModelID model) const {
    return IsDriver(model) || IsPassenger(model);
}

bool CVehicle::IsDriver(CPed* ped) const {
    return ped ? ped == m_pDriver : false;
}

bool CVehicle::IsDriver(int32 modelIndex) const {
    return m_pDriver && m_pDriver->m_nModelIndex == modelIndex;
}

bool CVehicle::IsDriverAPlayer() const {
    return m_pDriver && m_pDriver->IsPlayer();
}

// 0x6D1C80
void CVehicle::KillPedsInVehicle() {
    ((void(__thiscall*)(CVehicle*))0x6D1C80)(this);
}

// 0x6D1D90
bool CVehicle::IsUpsideDown() const {
    return m_matrix->GetUp().z <= -0.9f;
}

// 0x6D1DD0
bool CVehicle::IsOnItsSide() const {
    return m_matrix->GetRight().z >= 0.8f || m_matrix->GetRight().z <= -0.8f;
}

// 0x6D1E20
bool CVehicle::CanPedOpenLocks(CPed* ped) {
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1E20)(this, ped);
}

// 0x6D1E60
bool CVehicle::CanDoorsBeDamaged() {
    return ((bool(__thiscall*)(CVehicle*))0x6D1E60)(this);
}

// 0x6D1E80
bool CVehicle::CanPedEnterCar() {
    return ((bool(__thiscall*)(CVehicle*))0x6D1E80)(this);
}

// 0x6D21F0
void CVehicle::ProcessCarAlarm() {
    ((void(__thiscall*)(CVehicle*))0x6D21F0)(this);
}

// 0x6D2250
void DestroyVehicleAndDriverAndPassengers(CVehicle* vehicle) {
    ((void(__cdecl*)(CVehicle*))0x6D2250)(vehicle);
}

// 0x6D22F0
bool CVehicle::IsVehicleNormal() {
    if (m_pDriver
        && !m_nNumPassengers
        && m_nStatus != STATUS_WRECKED
        && GetVehicleModelInfo()->m_nVehicleClass != VEHICLE_CLASS_IGNORE
    ) {
        return true;
    }
    return false;
}

// 0x6D2330
void CVehicle::ChangeLawEnforcerState(bool bIsEnforcer) {
    if (bIsEnforcer) {
        if (!vehicleFlags.bIsLawEnforcer) {
            vehicleFlags.bIsLawEnforcer = true;
            ++CCarCtrl::NumLawEnforcerCars;
        }
    }
    else if (vehicleFlags.bIsLawEnforcer){
        vehicleFlags.bIsLawEnforcer = false;
        --CCarCtrl::NumLawEnforcerCars;
    }
}

// 0x6D2370
bool CVehicle::IsLawEnforcementVehicle() const {
    switch (m_nModelIndex) {
    case MODEL_ENFORCER:
    case MODEL_PREDATOR:
    case MODEL_RHINO:
    case MODEL_BARRACKS:
    case MODEL_FBIRANCH:
    case MODEL_COPBIKE:
    case MODEL_FBITRUCK:
    case MODEL_COPCARLA:
    case MODEL_COPCARSF:
    case MODEL_COPCARVG:
    case MODEL_COPCARRU:
    case MODEL_SWATVAN:
        return true;
    default:
        return false;
    }
}

// unused
// 0x6D2450
bool CVehicle::ShufflePassengersToMakeSpace() {
    return true;
}

// 0x6D2460
void CVehicle::ExtinguishCarFire() {
    if (m_nStatus != STATUS_WRECKED) {
        if (m_fHealth <= 300.0f)
            m_fHealth = 300.0f;
    }

    if (m_pFire) {
        m_pFire->createdByScript = false;
        m_pFire->Extinguish();
        m_pFire = nullptr;
    }

    if (IsAutomobile()) {
        if (AsAutomobile()->m_damageManager.GetEngineStatus() >= 225) {
            AsAutomobile()->m_damageManager.SetEngineStatus(215);
        }
        AsAutomobile()->m_fBurnTimer = 0.0f;
    }
}

// 0x6D24F0
void CVehicle::ActivateBomb() {
    ((void(__thiscall*)(CVehicle*))0x6D24F0)(this);
}

// 0x6D2570
void CVehicle::ActivateBombWhenEntered() {
    ((void(__thiscall*)(CVehicle*))0x6D2570)(this);
}

// 0x6D25D0
bool CVehicle::CarHasRoof() {
    return ((bool(__thiscall*)(CVehicle*))0x6D25D0)(this);
}

// 0x6D2600
float CVehicle::HeightAboveCeiling(float arg0, eFlightModel arg1) {
    return ((float(__thiscall*)(CVehicle*, float, eFlightModel))0x6D2600)(this, arg0, arg1);
}

// 0x6D2690
RwObject* SetVehicleAtomicVisibilityCB(RwObject* object, void* data) {
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D2690)(object, data);
}

// 0x6D26D0
RwFrame* SetVehicleAtomicVisibilityCB(RwFrame* component, void* data) {
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D26D0)(component, data);
}

// 0x6D2700
void CVehicle::SetComponentVisibility(RwFrame* component, uint32 visibilityState) { // see eAtomicComponentFlag
    ((void(__thiscall*)(CVehicle*, RwFrame*, uint32))0x6D2700)(this, component, visibilityState);
}

// 0x6D2740
void CVehicle::ApplyBoatWaterResistance(tBoatHandlingData* boatHandling, float fImmersionDepth) {
    float fSpeedMult = sq(fImmersionDepth) * m_pHandlingData->m_fSuspensionForceLevel * m_fMass / 1000.0F;
    if (m_nModelIndex == MODEL_SKIMMER) {
        fSpeedMult *= 30.0F;
    }

    auto fMoveDotProduct = DotProduct(m_vecMoveSpeed, GetForward());
    fSpeedMult *= sq(fMoveDotProduct) + 0.05F;
    fSpeedMult += 1.0F;
    fSpeedMult = std::fabs(fSpeedMult);
    fSpeedMult = 1.0F / fSpeedMult;

    float fUsedTimeStep = CTimer::GetTimeStep() * 0.5F;
    auto vecSpeedMult = Pow(boatHandling->m_vecMoveRes * fSpeedMult, fUsedTimeStep);

    CVector vecMoveSpeedMatrixDotProduct = Multiply3x3(m_vecMoveSpeed, GetMatrix());
    m_vecMoveSpeed = vecMoveSpeedMatrixDotProduct * vecSpeedMult;

    auto fMassMult = (vecSpeedMult.y - 1.0F) * m_vecMoveSpeed.y * m_fMass;
    CVector vecTransformedMoveSpeed = Multiply3x3(GetMatrix(), m_vecMoveSpeed);
    m_vecMoveSpeed = vecTransformedMoveSpeed;

    auto vecDown = GetUp() * -1.0F;
    auto vecTurnForce = GetForward() * fMassMult;
    ApplyTurnForce(vecTurnForce, vecDown);

    if (m_vecMoveSpeed.z <= 0.0F)
        m_vecMoveSpeed.z *= ((1.0F - vecSpeedMult.z) * 0.5F + vecSpeedMult.z);
    else
        m_vecMoveSpeed.z *= vecSpeedMult.z;
}

// 0x6D2950
RpMaterial* SetCompAlphaCB(RpMaterial* material, void* data) {
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x6D2950)(material, data);
}

// 0x6D2960
void CVehicle::SetComponentAtomicAlpha(RpAtomic* atomic, int32 alpha) {
    auto geometry = atomic->geometry;
    geometry->flags |= rpGEOMETRYMODULATEMATERIALCOLOR;
    RpGeometryForAllMaterials(geometry, SetCompAlphaCB, reinterpret_cast<void*>(alpha));
}

CVehicleModelInfo* CVehicle::GetVehicleModelInfo() const {
    return CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
}

CVector CVehicle::GetDummyPositionObjSpace(eVehicleDummy dummy) const {
    return GetVehicleModelInfo()->GetModelDummyPosition(dummy);
}

// if bWorldSpace is true, returns the position in world-space
// otherwise in model-space
CVector CVehicle::GetDummyPosition(eVehicleDummy dummy, bool bWorldSpace) {
    CVector pos = GetDummyPositionObjSpace(dummy);
    if (bWorldSpace)
        pos = GetMatrix() * pos; // transform to world-space
    return pos;
}

// 0x6D2980
void CVehicle::UpdateClumpAlpha() {
    ((void(__thiscall*)(CVehicle*))0x6D2980)(this);
}

// 0x6D29E0
void CVehicle::UpdatePassengerList() {
    ((void(__thiscall*)(CVehicle*))0x6D29E0)(this);
}

// 0x6D2A10
CPed* CVehicle::PickRandomPassenger() {
    return ((CPed * (__thiscall*)(CVehicle*))0x6D2A10)(this);
}

// 0x6D2A80
void CVehicle::AddDamagedVehicleParticles() {
    if (IsSubPlane())
        return;

    if (m_fHealth >= 650.0f || m_fHealth < 250.0f || physicalFlags.bSubmergedInWater) {
        FxSystem_c::SafeKillAndClear(m_pOverheatParticle);
        return;
    }

    RwMatrix* matrix = nullptr;
    if (m_pRwAtomic) {
        matrix = RwFrameGetMatrix(RpAtomicGetFrame(m_pRwAtomic));
    }

    if (!m_pOverheatParticle && matrix) {
        CVector point = GetVehicleModelInfo()->GetModelDummyPosition(DUMMY_ENGINE);
        const auto systemName = m_pHandlingData->m_transmissionData.m_nEngineType == 'E' ? "overheat_car_electric" : "overheat_car";
        m_pOverheatParticle = g_fxMan.CreateFxSystem(systemName, &point, matrix, false);
        if (m_pOverheatParticle) {
            m_pOverheatParticle->Play();
        }
    }

    if (m_pOverheatParticle) {
        m_pOverheatParticle->SetConstTime(1u, 1.0f - (m_fHealth - 250.0f) / 400.0f);
        CVector velocity = m_vecMoveSpeed * 50.0f;
        m_pOverheatParticle->SetVelAdd(&velocity);
    }
}

// 0x6D2BF0
void CVehicle::MakeDirty(CColPoint& colPoint) {
    if (g_surfaceInfos.IsWater(colPoint.m_nSurfaceTypeB) || CWeather::IsRainy()) {
        if (m_fDirtLevel <= 1.0f) {
            return;
        }
        m_fDirtLevel = m_fDirtLevel - CTimer::ms_fTimeStep * 0.01f;
        return;
    }

    if (g_surfaceInfos.MakesCarDirty(colPoint.m_nSurfaceTypeB)) {
        if (m_vecMoveSpeed.Magnitude2D() <= 0.06f) {
            return;
        }
        m_fDirtLevel = std::clamp(m_fDirtLevel + CTimer::GetTimeStep() * 0.003f, m_fDirtLevel, 15.0f); // todo: check
        return;
    }

    if (g_surfaceInfos.MakesCarClean(colPoint.m_nSurfaceTypeB)) {
        if (m_vecMoveSpeed.Magnitude2D() <= 0.04f || m_fDirtLevel <= 4.0f) {
            return;
        }
        m_fDirtLevel = std::clamp(m_fDirtLevel - CTimer::GetTimeStepInSeconds(), 4.0f, m_fDirtLevel); // todo: check
    }
}

// 0x6D2D50
bool CVehicle::AddWheelDirtAndWater(CColPoint& colPoint, uint32 arg1, uint8 arg2, uint8 arg3) {
    return ((bool(__thiscall*)(CVehicle*, CColPoint&, uint32, uint8, uint8))0x6D2D50)(this, colPoint, arg1, arg2, arg3);
}

// 0x6D3000
void CVehicle::SetGettingInFlags(uint8 doorId) {
    m_nGettingInFlags |= doorId;
}

// 0x6D3020
void CVehicle::SetGettingOutFlags(uint8 doorId) {
    m_nGettingOutFlags |= doorId;
}

// 0x6D3040
void CVehicle::ClearGettingInFlags(uint8 doorId) {
    m_nGettingInFlags &= ~doorId;
}

// 0x6D3060
void CVehicle::ClearGettingOutFlags(uint8 doorId) {
    m_nGettingOutFlags &= ~doorId;
}

// 0x6D3080
void CVehicle::SetWindowOpenFlag(uint8 doorId) {
    auto frameFromId = CClumpModelInfo::GetFrameFromId(m_pRwClump, doorId);
    if (frameFromId) {
        RwFrameForAllObjects(frameFromId, CVehicleModelInfo::SetAtomicFlagCB, (void*)ATOMIC_IS_DOOR_WINDOW_OPENED);
    }
}

// 0x6D30B0
void CVehicle::ClearWindowOpenFlag(uint8 doorId) {
    auto frameFromId = CClumpModelInfo::GetFrameFromId(m_pRwClump, doorId);
    if (frameFromId) {
        RwFrameForAllObjects(frameFromId, CVehicleModelInfo::ClearAtomicFlagCB, (void*)ATOMIC_IS_DOOR_WINDOW_OPENED);
    }
}

// 0x6D30E0
bool CVehicle::SetVehicleUpgradeFlags(int32 upgradeModelIndex, int32 componentIndex, int32& resultModelIndex) {
    return ((bool(__thiscall*)(CVehicle*, int32, int32, int32&))0x6D30E0)(this, upgradeModelIndex, componentIndex, resultModelIndex);
}

// 0x6D3210
bool CVehicle::ClearVehicleUpgradeFlags(int32 arg0, int32 componentIndex) {
    return ((bool(__thiscall*)(CVehicle*, int32, int32))0x6D3210)(this, arg0, componentIndex);
}

// 0x6D3300
RpAtomic* RemoveUpgradeCB(RpAtomic* atomic, void* data) {
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3300)(atomic, data);
}

// 0x6D3370
RpAtomic* FindUpgradeCB(RpAtomic* atomic, void* data) {
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3370)(atomic, data);
}

// 0x6D33B0
RwObject* RemoveObjectsCB(RwObject* object, void* data) {
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D33B0)(object, data);
}

// 0x6D3420
RwFrame* RemoveObjectsCB(RwFrame* component, void* data) {
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D3420)(component, data);
}

// 0x6D3450
RwObject* CopyObjectsCB(RwObject* object, void* data) {
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3450)(object, data);
}

// 0x6D3490
RwObject* FindReplacementUpgradeCB(RwObject* object, void* data) {
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3490)(object, data);
}

// 0x6D34D0
RpAtomic* RemoveAllUpgradesCB(RpAtomic* atomic, void* data) {
    auto* mi = CVisibilityPlugins::GetAtomicModelInfo(atomic);
    if (mi) {
        RpClumpRemoveAtomic(atomic->clump, atomic);
        RpAtomicDestroy(atomic);
        mi->RemoveRef();
    }
    return atomic;
}

// 0x6D3510
RpAtomic* CVehicle::CreateUpgradeAtomic(CBaseModelInfo* model, const UpgradePosnDesc* upgradePosn, RwFrame* parentComponent, bool isDamaged) {
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, const UpgradePosnDesc*, RwFrame*, bool))0x6D3510)(this, model, upgradePosn, parentComponent, isDamaged);
}

// 0x6D3630
void CVehicle::RemoveUpgrade(int32 upgradeId) {
    RpClumpForAllAtomics(m_pRwClump, RemoveUpgradeCB, &upgradeId);
}

// 0x6D3650
int32 CVehicle::GetUpgrade(int32 upgradeId) {
    struct { int32 upgradeId; RpAtomic* atomic; } data = { upgradeId, nullptr };
    RpClumpForAllAtomics(m_pRwClump, FindUpgradeCB, &data);
    if (data.atomic) {
        return CVisibilityPlugins::GetModelInfoIndex(data.atomic);
    }

    switch (upgradeId) {
    case 15:
        if (handlingFlags.bNosInst) {
            return ModelIndices::MI_NITRO_BOTTLE_SMALL;
        }
        break;
    case 16:
        if (handlingFlags.bHydraulicInst) {
            return ModelIndices::MI_HYDRAULICS;
        }
        break;
    case 17:
        if (vehicleFlags.bUpgradedStereo) {
            return ModelIndices::MI_STEREO_UPGRADE;
        }
        break;
    }
    return -1;

}

// 0x6D3700
RpAtomic* CVehicle::CreateReplacementAtomic(CBaseModelInfo* model, RwFrame* component, int32 arg2, bool bDamaged, bool bIsWheel) {
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, RwFrame*, int32, bool, bool))0x6D3700)(this, model, component, arg2, bDamaged, bIsWheel);
}

// 0x6D3830
void CVehicle::AddReplacementUpgrade(int32 modelIndex, int32 nodeId) {
    ((void(__thiscall*)(CVehicle*, int32, int32))0x6D3830)(this, modelIndex, nodeId);
}

// 0x6D39E0
void CVehicle::RemoveReplacementUpgrade(int32 nodeId) {
    ((void(__thiscall*)(CVehicle*, int32))0x6D39E0)(this, nodeId);
}

// 0x6D3A50
int32 CVehicle::GetReplacementUpgrade(int32 nodeId) {
    auto frame = CClumpModelInfo::GetFrameFromId(m_pRwClump, nodeId);
    struct { int32 nodeId; RpAtomic* atomic; } data = { nodeId, nullptr };
    RwFrameForAllObjects(frame, FindReplacementUpgradeCB, &data);
    if (data.atomic)
        return CVisibilityPlugins::GetModelInfoIndex(data.atomic);
    else
        return -1;
}

// 0x6D3AB0
void CVehicle::RemoveAllUpgrades() {
    RpClumpForAllAtomics(m_pRwClump, RemoveAllUpgradesCB, nullptr);
    m_anUpgrades.fill(-1);
}

// 0x6D3AE0
int32 CVehicle::GetSpareHasslePosId() {
    return ((int32(__thiscall*)(CVehicle*))0x6D3AE0)(this);
}

// 0x6D3B30
void CVehicle::SetHasslePosId(int32 hasslePos, bool enable) {
    ((void(__thiscall*)(CVehicle*, int32, bool))0x6D3B30)(this, hasslePos, enable);
}

// 0x6D3B60
void CVehicle::InitWinch(int32 arg0) {
    ((void(__thiscall*)(CVehicle*, int32))0x6D3B60)(this, arg0);
}

// 0x6D3B80
void CVehicle::UpdateWinch() {
    ((void(__thiscall*)(CVehicle*))0x6D3B80)(this);
}

// 0x6D3C70
void CVehicle::RemoveWinch() {
    return plugin::CallMethod<0x6D3C70, CVehicle*>(this);

    const auto ropeIndex = GetRopeIndex();
    if (ropeIndex >= 0)
        CRopes::GetRope(ropeIndex).Remove();

    // todo: m_nBombLightsWinchFlags &= 0x9Fu;
}

CVector CVehicle::GetDriverSeatDummyPositionOS() const {
    return GetDummyPositionObjSpace(
        IsBoat() ? DUMMY_LIGHT_FRONT_MAIN : DUMMY_SEAT_FRONT
    );
}

CVector CVehicle::GetDriverSeatDummyPositionWS() {
    return GetMatrix() * GetDriverSeatDummyPositionOS();
}

// NOTSA
int32 CVehicle::GetRopeIndex() {
    return CRopes::FindRope(m_nFlags + 1); // yep, flags + 1
}

CVehicleAnimGroup& CVehicle::GetAnimGroup() const {
    return CVehicleAnimGroupData::GetVehicleAnimGroup(m_pHandlingData->m_nAnimGroup);
}

AssocGroupId CVehicle::GetAnimGroupId() const {
    return (AssocGroupId)((int32)ANIM_GROUP_STDCARAMIMS + (int32)m_pHandlingData->m_nAnimGroup);
}

// 0x6D3CB0
void CVehicle::ReleasePickedUpEntityWithWinch() {
    return CRopes::GetRope(GetRopeIndex()).ReleasePickedUpObject();
}

// 0x6D3CD0
void CVehicle::PickUpEntityWithWinch(CEntity* entity) {
    return CRopes::GetRope(GetRopeIndex()).PickUpObject(entity);
}

// 0x6D3CF0
CEntity* CVehicle::QueryPickedUpEntityWithWinch() {
    return CRopes::GetRope(GetRopeIndex()).m_pRopeAttachObject;
}

// 0x6D3D10
float CVehicle::GetRopeHeightForHeli() {
    return CRopes::GetRope(GetRopeIndex()).m_fSegmentLength;
}

// 0x6D3D30
void CVehicle::SetRopeHeightForHeli(float height) {
    CRopes::GetRope(GetRopeIndex()).m_fSegmentLength = height;
}

// 0x6D3D60
void CVehicle::RenderDriverAndPassengers() {
    if (m_pDriver && m_pDriver->m_nPedState == PEDSTATE_DRIVING) {
        m_pDriver->Render();
    }

    for (auto& passenger : m_apPassengers) {
        if (passenger && passenger->m_nPedState == PEDSTATE_DRIVING) {
            passenger->Render();
        }
    }
}

// 0x6D3DB0
void CVehicle::PreRenderDriverAndPassengers() {
    if (m_pDriver && m_pDriver->m_nPedState == PEDSTATE_DRIVING) {
        m_pDriver->PreRenderAfterTest();
    }

    for (auto& passenger : m_apPassengers) {
        if (passenger && passenger->m_nPedState == PEDSTATE_DRIVING) {
            passenger->PreRenderAfterTest();
        }
    }
}

// 0x6D3E00
float CVehicle::GetPlaneGunsAutoAimAngle() {
    switch (m_nModelIndex) {
    case MODEL_HUNTER:
        return 25.0f;
    case MODEL_SEASPAR:
        return 10.0f;
    case MODEL_RCBARON:
        return 30.0f;
    case MODEL_RUSTLER:
        return 15.0f;
    case MODEL_MAVERICK:
        return 15.0f;
    case MODEL_POLMAV:
        return 15.0f;
    case MODEL_HYDRA:
        return 15.0f;
    case MODEL_CARGOBOB:
        return 15.0f;
    case MODEL_RCTIGER:
        return 20.0f;
    case MODEL_TORNADO:
        return 15.0f;
    default:
        return 0.0f;
    }
}

// 0x6D3F30
int32 CVehicle::GetPlaneNumGuns() {
    switch (m_nModelIndex) {
    case MODEL_HUNTER:
    case MODEL_SEASPAR:
    case MODEL_RCBARON:
    case MODEL_MAVERICK:
    case MODEL_POLMAV:
    case MODEL_CARGOBOB:
        return 1;
    case MODEL_RUSTLER:
        return 6;
    case MODEL_HYDRA:
    case MODEL_TORNADO:
        return 2;
    default:
        return 0;
    }
}

// 0x6D4010
void CVehicle::SetFiringRateMultiplier(float multiplier) {
    multiplier = std::clamp(multiplier, 0.0f, 15.9375f);
    switch (m_nVehicleSubType) {
    case VEHICLE_TYPE_PLANE:
        AsPlane()->m_nFiringMultiplier = uint8(multiplier * 16.0f);
        break;
    case VEHICLE_TYPE_HELI:
        AsHeli()->m_nFiringMultiplier = uint8(multiplier * 16.0f);
        break;
    }
}

// 0x6D4090
float CVehicle::GetFiringRateMultiplier() {
    switch (m_nVehicleSubType) {
    case VEHICLE_TYPE_PLANE:
        return float(AsPlane()->m_nFiringMultiplier) / 16.0f;
    case VEHICLE_TYPE_HELI:
        return float(AsHeli()->m_nFiringMultiplier) / 16.0f;
    default:
        return 1.0f;
    }
}

// 0x6D40E0
uint32 CVehicle::GetPlaneGunsRateOfFire() {
    const auto mult = GetFiringRateMultiplier();
    switch (m_nModelIndex) {
    case MODEL_SEASPAR:
    case MODEL_RCBARON:
        return uint32(40.0f / mult);
    case MODEL_RUSTLER:
        return uint32(80.0f / mult);
    case MODEL_HYDRA:
        return uint32(17.0f / mult);
    case MODEL_CARGOBOB:
        return uint32(100.0f / mult);
    case MODEL_TORNADO:
        return uint32(45.0f / mult);
    default:
        return uint32(60.0f / mult);
    }
}

// 0x6D4290
CVector CVehicle::GetPlaneGunsPosition(int32 gunId) {
    CVector result;
    ((void(__thiscall*)(CVehicle*, CVector*, int32))0x6D4290)(this, &result, gunId);
    return result;
}

// 0x6D4590
uint32 CVehicle::GetPlaneOrdnanceRateOfFire(eOrdnanceType type) {
    const auto mult = GetFiringRateMultiplier();
    switch (m_nModelIndex) {
    case MODEL_HUNTER:
        return (uint32)((float)500 / mult);
    case MODEL_SEASPAR:
    case MODEL_RUSTLER:
        return (uint32)((float)1000 / mult);
    case MODEL_HYDRA:
        return (uint32)((float)(type != 1 ? 1000 : 500) / mult); // todo: heat trap / missile?
    default:
        return (uint32)((float)350 / mult);
    }
}

// 0x6D46E0
CVector CVehicle::GetPlaneOrdnancePosition(eOrdnanceType type) {
    // CVector result;
    // ((void(__thiscall*)(CVehicle*, CVector*, eOrdnanceType))0x6D46E0)(this, &result, type);
    // return result;

    const auto pos = GetVehicleModelInfo()->GetModelDummyPosition(DUMMY_VEHICLE_GUN);
    if (!pos->IsZero()) {
        return pos;
    }

    constexpr CVector HUNTER_ORDNANCE_POS  = { 2.17f, 1.00f, -0.80f }; // 0x8D3640
    constexpr CVector RUSTLER_ORDNANCE_POS = { 2.19f, 1.50f, -0.58f }; // 0x8D364C
    constexpr CVector HYDRA_1_ORDNANCE_POS = { 3.70f, 0.98f, -1.02f }; // 0x8D3658
    constexpr CVector HYDRA_2_ORDNANCE_POS = { 3.92f, 0.98f, -1.02f }; // 0x8D3664

    constexpr CVector SEASPAR_ORDNANCE_POS = { }; // 0xC1CC38;
    constexpr CVector RCBARON_ORDNANCE_POS = { }; // 0xC1CC50;
    constexpr CVector TORNADO_ORDNANCE_POS = { }; // 0xC1CC44;

    switch (m_nModelIndex) {
    case MODEL_HUNTER:
        return HUNTER_ORDNANCE_POS;
    case MODEL_SEASPAR:
        return SEASPAR_ORDNANCE_POS;
    case MODEL_RCBARON:
        return RCBARON_ORDNANCE_POS;
        break;
    case MODEL_RUSTLER:
        return RUSTLER_ORDNANCE_POS;
    case MODEL_HYDRA:
        if (type == 1) {
            return HYDRA_1_ORDNANCE_POS;
        } else if (type == 2) {
            return HYDRA_2_ORDNANCE_POS;
        }
        return pos;
    case MODEL_TORNADO:
        return TORNADO_ORDNANCE_POS;
    default:
        return {};
    }
}

// 0x6D4900
void CVehicle::SelectPlaneWeapon(bool bChange, eOrdnanceType type) {
    return plugin::CallMethod<0x6D4900, CVehicle*, bool, eOrdnanceType>(this, bChange, type);

    switch (m_nModelIndex) {
    case MODEL_HUNTER: {
        m_nVehicleWeaponInUse = bChange ? CAR_WEAPON_HEAVY_GUN : m_nVehicleWeaponInUse;
        if (type != 1) {
            break;
        }
        m_nVehicleWeaponInUse = CAR_WEAPON_DOUBLE_ROCKET;
        break;
    }
    case MODEL_SEASPAR:
    case MODEL_RCBARON: {
        m_nVehicleWeaponInUse = bChange ? CAR_WEAPON_HEAVY_GUN : m_nVehicleWeaponInUse;
        break;
    }
    case MODEL_RUSTLER: {
        m_nVehicleWeaponInUse = bChange ? CAR_WEAPON_HEAVY_GUN : m_nVehicleWeaponInUse;
        if (type != 1) {
            break;
        }
        m_nVehicleWeaponInUse = CAR_WEAPON_FREEFALL_BOMB;
        break;
    }
    case MODEL_HYDRA: {
        m_nVehicleWeaponInUse = bChange ? CAR_WEAPON_HEAVY_GUN : m_nVehicleWeaponInUse;
        if (type == 1) {
            m_nVehicleWeaponInUse = CAR_WEAPON_DOUBLE_ROCKET;
        } else if (type == 2) {
            m_nVehicleWeaponInUse = CAR_WEAPON_LOCK_ON_ROCKET;
        }
        break;
    }
    case MODEL_TORNADO:
        m_nVehicleWeaponInUse = bChange ? CAR_WEAPON_HEAVY_GUN : m_nVehicleWeaponInUse;
        if (type == 1)
            m_nVehicleWeaponInUse = CAR_WEAPON_DOUBLE_ROCKET;
        break;
    default:
        return;
    }
}

// 0x6D4AD0
void CVehicle::DoPlaneGunFireFX(CWeapon* weapon, CVector& particlePos, CVector& gunshellPos, int32 particleIndex) {
    ((void(__thiscall*)(CVehicle*, CWeapon*, CVector&, CVector&, int32))0x6D4AD0)(this, weapon, particlePos, gunshellPos, particleIndex);
}

// 0x6D4D30
void CVehicle::FirePlaneGuns() {
    return plugin::CallMethod<0x6D4D30, CVehicle*>(this);

    if (!GetPlaneNumGuns())
        return;

    if (CTimer::GetTimeInMS() <= m_nGunFiringTime + GetPlaneGunsRateOfFire())
        return;

    uint8 frequency;
    bool bFire;
    eWeaponType weaponType;
    switch (m_nModelIndex) {
    case MODEL_HUNTER:
    case MODEL_CARGOBOB:
        bFire = false;
        frequency = 160;
        weaponType = WEAPON_MINIGUN;
        break;
    case MODEL_SEASPAR:
    case MODEL_RCBARON:
    case MODEL_MAVERICK:
    case MODEL_POLMAV:
        weaponType = WEAPON_M4;
        bFire = false;
        frequency = 92;
        break;
    case MODEL_RUSTLER:
        weaponType = WEAPON_M4;
        bFire = true;
        frequency = 224;
        /*
        m_nGunsFlags = m_nGunsFlags ^ (m_nGunsFlags ^ (m_nGunsFlags + 1)) & 3;
        if ((m_nGunsFlags & 3) == 3) {
            m_nGunsFlags = m_nGunsFlags & 0xFC;
        }
        */
        break;
    case MODEL_HYDRA:
    case MODEL_TORNADO:
        bFire = true;
        frequency = 128;
        weaponType = WEAPON_MINIGUN;
        break;
    default:
        return;
    }

    CVector planeGunsPos;
    auto weapon = CWeapon(weaponType, 5000);
    // GetPlaneGunsPosition(this, &planeGunsPos, m_nGunsFlags & 3);
    CVector posn = CTimer::GetTimeStep() * m_vecMoveSpeed + MultiplyMatrixWithVector(*m_matrix, &planeGunsPos);
    weapon.FireInstantHit(this, &posn, &posn, nullptr, nullptr, nullptr, false, false);

    if (bFire) {
        // DoPlaneGunFireFX(this, &weapon, &planeGunsPos, &posn, 2 * (m_nGunsFlags & 3));
        CVector PlaneGunsPosition;
        // GetPlaneGunsPosition(this, &PlaneGunsPosition, m_nGunsFlags & 3);
        PlaneGunsPosition.x = -PlaneGunsPosition.x;
        posn = CTimer::GetTimeStep() * m_vecMoveSpeed + MultiplyMatrixWithVector(*m_matrix, &PlaneGunsPosition);
        weapon.FireInstantHit(this, &posn, &posn, nullptr, nullptr, nullptr, false, false);
        // DoPlaneGunFireFX(this, &weapon, &PlaneGunsPosition, &posn, 2 * (m_nGunsFlags & 3) + 1);
    } else {
        // DoPlaneGunFireFX(this, &weapon, &planeGunsPos, &posn, m_nGunsFlags & 3);
    }

    if (m_nStatus == STATUS_FORCED_STOP) {
        CPad::GetPad(0)->StartShake(240, frequency, 0);
    } else if (m_pDriver && m_pDriver->IsPlayer()) {
        switch (m_pDriver->m_nPedType) {
        case PED_TYPE_PLAYER1:
            CPad::GetPad(0)->StartShake(240, frequency, 0);
            break;
        case PED_TYPE_PLAYER2:
            CPad::GetPad(1)->StartShake(240, frequency, 0);
            break;
        default:
            break;
        }
    }

    if (weaponType == WEAPON_MINIGUN) {
        weaponType = WEAPON_M4;
    }
    AudioEngine.ReportWeaponEvent(AE_WEAPON_FIRE_PLANE, weaponType, this);
    m_nGunFiringTime = CTimer::GetTimeInMS();
}

// 0x6D5110
void CVehicle::FireUnguidedMissile(eOrdnanceType type, bool bCheckTime) {
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6D5110)(this, type, bCheckTime);
}

// 0x6D5400
bool CVehicle::CanBeDriven() const {
    if (IsSubTrailer() || IsSubTrain() && AsTrain()->m_nTrackId || vehicleFlags.bIsRCVehicle) {
        return false;
    }
    return GetDriverSeatDummyPositionOS().SquaredMagnitude() > 0.0f;
}

// 0x6D5490
void CVehicle::ReactToVehicleDamage(CPed* ped) {
    return ((void(__thiscall*)(CVehicle*, CPed*))0x6D5490)(this, ped);

    const auto React = [=](CPed* ped, CEntity* target, int32 time) {
        g_ikChainMan.LookAt("ReactToVhclDam", ped, target, time, BONE_HEAD, nullptr, false, 0.25f, 500, 3, false);
    };

    // FIX_BUGS ?
    int32 t1 = (int32)(2000.f - CGeneral::GetRandomNumberInRange(-3000.0f, 0.0f));
    if (m_pDriver) {
        if (m_apPassengers[0]) {
            if (CGeneral::GetRandomNumber() >= 0x3FFF)
                React(m_pDriver, ped, t1);
            else
                React(m_pDriver, m_apPassengers[0], t1);
        } else {
            React(m_pDriver, ped, t1);
        }
    }

    int32 t2 = (int32)(2000.f - CGeneral::GetRandomNumberInRange(-3000.0f, 0.0f));
    if (m_apPassengers[0]) {
        if (CGeneral::GetRandomNumber() >= 0x3FFF)
            React(m_apPassengers[0], ped, t2);
        else
            React(m_apPassengers[0], m_pDriver, t2);
    }
}

// 0x6D55C0
bool CVehicle::GetVehicleLightsStatus() {
    return ((bool(__thiscall*)(CVehicle*))0x6D55C0)(this);
}

// 0x6D5CF0
bool CVehicle::CanPedLeanOut(CPed* ped) {
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D5CF0)(this, ped);
}

// 0x6D5D70
void CVehicle::SetVehicleCreatedBy(int32 createdBy) {
    ((void(__thiscall*)(CVehicle*, int32))0x6D5D70)(this, createdBy);
}

// 0x6D64F0
void CVehicle::SetupRender() {
    ((void(__thiscall*)(CVehicle*))0x6D64F0)(this);
}

// 0x6D6C00
void CVehicle::ProcessWheel(CVector& wheelFwd, CVector& wheelRight, CVector& wheelContactSpeed, CVector& wheelContactPoint,
    int32 wheelsOnGround, float thrust, float brake, float adhesion, int8 wheelId, float* wheelSpeed, tWheelState* wheelState, uint16 wheelStatus) {
    static bool& bBraking = *(bool*)0xC1CDAE; // false
    static bool& bDriving = *(bool*)0xC1CDAD; // false
    static bool& bAlreadySkidding = *(bool*)0xC1CDAC; // false

    float right = 0.0f;
    float fwd = 0.0f;
    float contactSpeedFwd = DotProduct(wheelFwd, wheelContactSpeed);
    float contactSpeedRight = DotProduct(wheelRight, wheelContactSpeed);

    bBraking = brake != 0.0f;
    bDriving = !bBraking;
    if (bDriving && thrust == 0.0f)
        bDriving = false;

    adhesion *= CTimer::GetTimeStep();
    if (*wheelState != WHEEL_STATE_NORMAL) {
        bAlreadySkidding = true;
        adhesion *= m_pHandlingData->m_fTractionLoss;
        if (*wheelState == WHEEL_STATE_SPINNING) {
            if (m_nStatus == STATUS_PLAYER || m_nStatus == STATUS_REMOTE_CONTROLLED)
                adhesion *= (1.0f - fabs(m_fGasPedal) * WS_ALREADY_SPINNING_LOSS);
        }
    }

    *wheelState = WHEEL_STATE_NORMAL;

    if (contactSpeedRight != 0.0f) {
        right = -(contactSpeedRight / wheelsOnGround);
        if (wheelStatus == WHEEL_STATUS_BURST) {
            float fwdspeed = std::min(contactSpeedFwd, fBurstSpeedMax);
            right += fwdspeed * CGeneral::GetRandomNumberInRange(-fBurstTyreMod, fBurstTyreMod) ;
        }
    }

    if (bDriving) {
        fwd = thrust;
        right = std::clamp(right, -adhesion, adhesion);
    }
    else if (contactSpeedFwd != 0.0f) {
        fwd = -contactSpeedFwd / wheelsOnGround;
        if (!bBraking && std::fabs(m_fGasPedal) < 0.01f) {
            if (IsBike())
                brake = gHandlingDataMgr.fWheelFriction * 0.6f / (m_pHandlingData->m_fMass + 200.0f);
            else if (IsSubPlane())
                brake = 0.0f;
            else {
                brake = gHandlingDataMgr.fWheelFriction / m_pHandlingData->m_fMass;

                if (brake > 500.0f)
                    brake *= 0.1f;
                else if (m_nModelIndex == MODEL_RCBANDIT)
                    brake *= 0.2f;
            }
        }
        if (brake > adhesion) {
            if (std::fabs(contactSpeedFwd) > 0.005f) {
                *wheelState = WHEEL_STATE_FIXED;
            }
        } else {
            fwd = std::clamp(fwd, -brake, brake);
        }
    }

    float speedSq = right * right + fwd * fwd;
    if (speedSq > adhesion * adhesion) {
        if (*wheelState != WHEEL_STATE_FIXED) {
            float tractionLimit = WS_TRAC_FRAC_LIMIT;
            if (contactSpeedFwd > 0.15f && (!wheelId || wheelId == CAR_WHEEL_FRONT_RIGHT)) {
                tractionLimit += tractionLimit;
            }
            if (bDriving && tractionLimit * adhesion < std::fabs(fwd))
                *wheelState = WHEEL_STATE_SPINNING;
            else
                *wheelState = WHEEL_STATE_SKIDDING;
        }
        float tractionLoss = m_pHandlingData->m_fTractionLoss;
        if (bAlreadySkidding) {
            tractionLoss = 1.0f;
        } else if (*wheelState == WHEEL_STATE_SPINNING) {
            if (m_nStatus == STATUS_PLAYER || m_nStatus == STATUS_REMOTE_CONTROLLED) {
                tractionLoss = tractionLoss * (1.0f - std::fabs(m_fGasPedal) * WS_ALREADY_SPINNING_LOSS);
            }
        }
        float l = sqrt(speedSq);
        fwd *= adhesion * tractionLoss / l;
        right *= adhesion * tractionLoss / l;
    }

    if (fwd != 0.0f || right != 0.0f) {
        bool separateTurnForce = false;
        CVector totalSpeed = fwd * wheelFwd + right * wheelRight;
        CVector turnDirection  = totalSpeed;

        if (m_pHandlingData->m_fSuspensionAntiDiveMultiplier > 0.0f) {
            if (bBraking) {
                separateTurnForce = true;
                turnDirection -= (m_pHandlingData->m_fSuspensionAntiDiveMultiplier * wheelFwd * fwd);
            }
            else if (bDriving) {
                separateTurnForce = true;
                turnDirection -= (0.5f * m_pHandlingData->m_fSuspensionAntiDiveMultiplier * wheelFwd * fwd);
            }
        }

        CVector direction = totalSpeed;
        float speed = totalSpeed.Magnitude();
        float turnSpeed = speed;
        if (separateTurnForce)
            turnSpeed = turnDirection.Magnitude();
        direction.Normalise();
        if (separateTurnForce)
            turnDirection.Normalise();
        else
            turnDirection = direction;

        float force = speed * m_fMass;
        float turnForce = turnSpeed * GetMass(wheelContactPoint, turnDirection);
        ApplyMoveForce(force * direction);
        ApplyTurnForce(turnForce * turnDirection, wheelContactPoint);
    }
}

// 0x6D73B0
void CVehicle::ProcessBikeWheel(CVector& wheelFwd, CVector& wheelRight, CVector& wheelContactSpeed, CVector& wheelContactPoint, int32 wheelsOnGround, float thrust, float brake,
                                float adhesion, float destabTraction, int8 wheelId, float* wheelSpeed, tWheelState* wheelState, eBikeWheelSpecial special, uint16 wheelStatus) {
    plugin::CallMethod<0x6D73B0, CVehicle*, CVector&, CVector&, CVector&, CVector&, int32, float, float, float, float, char, float*, tWheelState*, eBikeWheelSpecial, uint16>(
        this, wheelFwd, wheelRight, wheelContactSpeed, wheelContactPoint, wheelsOnGround, thrust, brake, destabTraction, adhesion, wheelId, wheelSpeed, wheelState, special,
        wheelStatus);
}

// return nearest wheel?
// 0x6D7BC0
int32 CVehicle::FindTyreNearestPoint(float x, float y) {
    return ((int32(__thiscall*)(CVehicle*, float, float))0x6D7BC0)(this, x, y);
}

// 0x6D7C90
void CVehicle::InflictDamage(CEntity* damager, eWeaponType weapon, float intensity, CVector coords) {
    ((void(__thiscall*)(CVehicle*, CEntity*, eWeaponType, float, CVector))0x6D7C90)(this, damager, weapon, intensity, coords);
}

// 0x6D82F0
void CVehicle::KillPedsGettingInVehicle() {
    ((void(__thiscall*)(CVehicle*))0x6D82F0)(this);
}

// 0x6D8470
bool CVehicle::UsesSiren() {
    switch (m_nModelIndex) {
    case MODEL_FIRETRUK:
    case MODEL_AMBULAN:
    case MODEL_MRWHOOP:
        return true;
    case MODEL_RHINO:
        return false;
    default:
        return IsLawEnforcementVehicle() != false;
    }
}

// 0x6D84D0
bool CVehicle::IsSphereTouchingVehicle(CVector posn, float radius) {
    const auto cm = GetColModel();
    const auto dist = posn - GetPosition();

    const auto dotRight = DotProduct(dist, GetRight());
    if (dotRight < cm->m_boundBox.m_vecMin.x - radius ||
        dotRight > cm->m_boundBox.m_vecMax.x + radius
    ) {
        return false;
    }

    const auto dotFwd = DotProduct(dist, GetForward());
    if (dotFwd < cm->m_boundBox.m_vecMin.y - radius ||
        dotFwd > cm->m_boundBox.m_vecMax.y + radius
    ) {
        return false;
    }

    const auto dotUp = DotProduct(dist, GetUp());
    if (dotUp < cm->m_boundBox.m_vecMin.z - radius ||
        dotUp > cm->m_boundBox.m_vecMax.z + radius
    ) {
        return false;
    }

    return true;
}

// 0x6D85F0
void CVehicle::FlyingControl(eFlightModel flightModel, float leftRightSkid, float steeringUpDown, float steeringLeftRight, float accelerationBreakStatus) {
    ((void(__thiscall*)(CVehicle*, eFlightModel, float, float, float, float))0x6D85F0)(this, flightModel, leftRightSkid, steeringUpDown, steeringLeftRight, accelerationBreakStatus);
}

// always return false?
// 0x6DAF00
void CVehicle::BladeColSectorList(CPtrList& ptrList, CColModel& colModel, CMatrix& matrix, int16 rotorType, float damageMult) {
    plugin::CallMethod<0x6DAF00, CVehicle*, CPtrList&, CColModel&, CMatrix&, int16, float>(this, ptrList, colModel, matrix, rotorType, damageMult);
}

// 0x6DBA30
void CVehicle::SetComponentRotation(RwFrame* component, eRotationAxis axis, float angle, bool bResetPosition) {
    plugin::CallMethod<0x6DBA30, CVehicle*, RwFrame*, eRotationAxis, float, bool>(this, component, axis, angle, bResetPosition);
}

// 0x6DBBB0
void CVehicle::SetTransmissionRotation(RwFrame* component, float angleL, float angleR, CVector wheelPos, bool isFront) {
    if (component) {
        CMatrix mat(&component->modelling);
        CVector savedPos = mat.GetPosition();
        float angleX = -std::atan2(
            (angleL + angleR) / 2.0f - wheelPos.z,
            mat.GetPosition().y - wheelPos.y
        );
        if (isFront) {
            angleX += PI;
        }
        mat.SetRotateX(angleX);
        mat.RotateY(std::atan2(angleL - angleR, std::fabs(wheelPos.x) + std::fabs(wheelPos.x)));
        mat.GetPosition() += savedPos;
        mat.UpdateRW();
    }
}

// 0x6DBCE0
void CVehicle::ProcessBoatControl(tBoatHandlingData* boatHandling, float* fLastWaterImmersionDepth, bool bCollidedWithWorld, bool bPostCollision) {
    CVector vecBuoyancyTurnPoint{};
    CVector vecBuoyancyForce{};
    if (!mod_Buoyancy.ProcessBuoyancyBoat(this, m_fBuoyancyConstant, &vecBuoyancyTurnPoint, &vecBuoyancyForce, bCollidedWithWorld)) {
        physicalFlags.bSubmergedInWater = false;
        if (IsSubBoat()) {
            AsBoat()->m_nBoatFlags.bOnWater = false;
        }
        return;
    }

    bool bOnWater = false;
    // FIX_BUGS ? vehicleFlags.bIsDrowning = false;
    if (CTimer::GetTimeStep() * m_fMass * 0.0008F >= vecBuoyancyForce.z) {
        physicalFlags.bSubmergedInWater = false;
    } else {
        physicalFlags.bSubmergedInWater = true;
        bOnWater = true;

        if (GetUp().z < -0.6F
            && std::fabs(m_vecMoveSpeed.x) < 0.05F
            && std::fabs(m_vecMoveSpeed.y) < 0.05F
        ) {
            vehicleFlags.bIsDrowning = true;
            if (m_pDriver) {
                m_pDriver->physicalFlags.bTouchingWater = true;
                if (m_pDriver->IsPlayer()) {
                    m_pDriver->AsPlayer()->HandlePlayerBreath(true, 1.0F);
                } else {
                    auto damageEvent = CEventDamage(this, CTimer::GetTimeInMS(), eWeaponType::WEAPON_DROWNING, PED_PIECE_TORSO, 0, false, true);
                    if (damageEvent.AffectsPed(m_pDriver)) {
                        auto pedDamageResponseCalc = CPedDamageResponseCalculator(this, CTimer::GetTimeStep(), eWeaponType::WEAPON_DROWNING, PED_PIECE_TORSO, false);
                        pedDamageResponseCalc.ComputeDamageResponse(m_pDriver, damageEvent.m_damageResponse, true);
                    } else {
                        damageEvent.m_damageResponse.m_bDamageCalculated = true;
                    }

                    m_pDriver->GetEventGroup().Add(&damageEvent, false);
                }
            }
        }
    }
    vehicleFlags.bIsDrowning = false; // see above

    // 0x6DBF0A
    auto vecUsedBuoyancyForce = vecBuoyancyForce;
    auto fImmersionDepth = mod_Buoyancy.m_fEntityWaterImmersion;
    if (m_nModelIndex == MODEL_SKIMMER
        && GetUp().z < -0.5F
        && std::fabs(m_vecMoveSpeed.x) < 0.2F
        && std::fabs(m_vecMoveSpeed.y) < 0.2F
    ) {
        vecUsedBuoyancyForce *= 0.03F;
    }
    CPhysical::ApplyMoveForce(vecUsedBuoyancyForce);

    if (bCollidedWithWorld) {
        CPhysical::ApplyTurnForce(vecBuoyancyForce * 0.4F, vecBuoyancyTurnPoint);
    }

    // 0x6DC00B
    if (m_nModelIndex == MODEL_SKIMMER) {
        auto fCheckedMass = CTimer::GetTimeStep() * m_fMass;
        if (m_f2ndSteerAngle != 0.0F
            || (GetForward().z < -0.5F
            && GetUp().z > -0.5F
            && m_vecMoveSpeed.z < -0.15F
            && fCheckedMass * 0.01F / 125.0F < vecBuoyancyForce.z
            && vecBuoyancyForce.z < fCheckedMass * 0.4F / 125.0F)
        ) {
            bOnWater = false;

            auto fTurnForceMult = GetForward().z * m_fTurnMass * -0.00017F * vecBuoyancyForce.z;
            CPhysical::ApplyTurnForce(GetForward() * fTurnForceMult, GetUp());

            auto fMoveForceMult = DotProduct(m_vecMoveSpeed, GetForward()) / -2.0f * m_fMass;
            CPhysical::ApplyMoveForce(GetForward() * fMoveForceMult);

            if (m_f2ndSteerAngle == 0.0F) { // todo: missing checks for CTimer 0x6DC195 ?
                m_f2ndSteerAngle = (float)CTimer::GetTimeInMS() + 300.0F;
            }
            else if (m_f2ndSteerAngle <= (float)CTimer::GetTimeInMS()) {
                m_f2ndSteerAngle = 0.0F;
            }
        }
    }

    // 0x6DC1E2
    if (!bPostCollision && bOnWater && GetUp().z > 0.0F) {
        auto fMoveForce = m_vecMoveSpeed.SquaredMagnitude() * boatHandling->m_fAqPlaneForce * CTimer::GetTimeStep() * vecBuoyancyForce.z * 0.5F;
        if (m_nModelIndex == MODEL_SKIMMER)
            fMoveForce *= (m_fGasPedal + 1.0F);
        else if (m_fGasPedal <= 0.05F)
            fMoveForce = 0.0F;
        else
            fMoveForce *= m_fGasPedal;

        auto fMaxMoveForce = CTimer::GetTimeStep() * boatHandling->m_fAqPlaneLimit * m_fMass / 125.0F;
        fMoveForce = std::min(fMoveForce, fMaxMoveForce);

        auto vecUsedMoveForce = GetUp() * fMoveForce;
        CPhysical::ApplyMoveForce(vecUsedMoveForce);

        auto vecOffset = GetForward() * boatHandling->m_fAqPlaneOffset;
        auto vecTurnPoint = vecBuoyancyTurnPoint - vecOffset;
        CPhysical::ApplyTurnForce(vecUsedMoveForce, vecTurnPoint);
    }

    CPad* pad = nullptr;
    if (m_nStatus == eEntityStatus::STATUS_PLAYER && m_pDriver && m_pDriver->IsPlayer()) {
        pad = m_pDriver->AsPlayer()->GetPadFromPlayer();
    }

    // 0x6DC3AF
    if (GetUp().z > -0.6F) {
        float fMoveSpeed = 1.0F;
        if (std::fabs(m_fGasPedal) <= 0.05F) {
            fMoveSpeed = m_vecMoveSpeed.Magnitude2D();
        }

        if (std::fabs(m_fGasPedal) > 0.05F || fMoveSpeed > 0.01F) {
            if (IsSubBoat() && bOnWater && fMoveSpeed > 0.05F) {
                //GetColModel(); Unused call
                AsBoat()->AddWakePoint(GetPosition());
            }

            auto fTraction = 1.0F;
            if (m_nStatus == eEntityStatus::STATUS_PLAYER) {
                auto fTractionLoss = DotProduct(m_vecMoveSpeed, GetForward()) * m_pHandlingData->m_fTractionBias;
                if (pad->GetHandBrake())
                    fTractionLoss *= 0.5F;

                fTraction = 1.0F - fTractionLoss;
                fTraction = std::clamp(fTraction, 0.0F, 1.0F);
            }

            auto fSteerAngleChange = -(fTraction * m_fSteerAngle);
            auto fSteerAngleSin = std::sin(fSteerAngleChange);
            auto fSteerAngleCos = std::cos(fSteerAngleChange);

            const auto& vecBoundingMin = CEntity::GetColModel()->m_boundBox.m_vecMin;
            CVector vecThrustPoint(0.0F, vecBoundingMin.y * boatHandling->m_fThrustY, vecBoundingMin.z * boatHandling->m_fThrustZ);
            auto vecTransformedThrustPoint = Multiply3x3(GetMatrix(), vecThrustPoint);

            auto vecWorldThrustPos = GetPosition() + vecTransformedThrustPoint;
            float fWaterLevel;
            CWaterLevel::GetWaterLevel(vecWorldThrustPos, fWaterLevel, true); // warn: result not checked
            if (vecWorldThrustPos.z - 0.5F >= fWaterLevel) {
                if (IsSubBoat())
                    AsBoat()->m_nBoatFlags.bMovingOnWater = false;
            }
            else {
                auto fThrustDepth = fWaterLevel - vecWorldThrustPos.z + 0.5F;
                fThrustDepth = std::min(sq(fThrustDepth), 1.0F);

                if (IsSubBoat())
                    AsBoat()->m_nBoatFlags.bMovingOnWater = true;

                bool bIsSlowingDown = false;
                auto fGasState = std::fabs(m_fGasPedal);
                if (fGasState < 0.01F || m_nModelIndex == MODEL_SKIMMER) {
                    bIsSlowingDown = true;
                }
                else {
                    if (fGasState < 0.5F)
                        bIsSlowingDown = true;

                    auto fSteerAngle = std::fabs(m_fSteerAngle);
                    CVector vecSteer(-fSteerAngleSin, fSteerAngleCos, -fSteerAngle);
                    CVector vecSteerMoveForce = Multiply3x3(GetMatrix(), vecSteer);
                    vecSteerMoveForce *= fThrustDepth * m_fGasPedal * 40.0F * m_pHandlingData->m_transmissionData.m_fEngineAcceleration * m_fMass;

                    if (vecSteerMoveForce.z > 0.2F)
                        vecSteerMoveForce.z = sq(1.2F - vecSteerMoveForce.z) + 0.2F;

                    if (bPostCollision) {
                        if (m_fGasPedal < 0.0F)
                            vecSteerMoveForce *= CVector(5.0F, 5.0F, 1.0F);

                        vecSteerMoveForce.z = std::max(0.0F, vecSteerMoveForce.z);
                        CPhysical::ApplyMoveForce(vecSteerMoveForce * CTimer::GetTimeStep());
                    }
                    else {
                        CPhysical::ApplyMoveForce(vecSteerMoveForce * CTimer::GetTimeStep());

                        auto vecTurnForcePoint = vecTransformedThrustPoint - (GetUp() * boatHandling->m_fThrustAppZ);
                        CPhysical::ApplyTurnForce(vecSteerMoveForce * CTimer::GetTimeStep(), vecTurnForcePoint);

                        auto fTractionSide = -DotProduct(vecSteerMoveForce, GetRight()) * m_pHandlingData->m_fTractionMultiplier;
                        auto vecTurnForceSide = GetRight() * fTractionSide * CTimer::GetTimeStep();
                        CPhysical::ApplyTurnForce(vecTurnForceSide, GetUp());
                    }

                    //This code does nothing
                    /*if (m_fGasPedal > 0.0F && m_nStatus == eEntityStatus::STATUS_PLAYER) {
                        const auto& vecBoundMin = GetColModel()->m_boundBox.m_vecMin;
                        CVector vecUnkn = CVector(0.0F, vecBoundingMin.y, 0.0F);
                        CVector vecUnknTransformed;
                        Multiply3x3(&vecUnknTransformed, GetMatrix(), &vecUnkn);
                    }*/
                }

                if (!bPostCollision && bIsSlowingDown) {
                    auto fTractionLoss = DotProduct(m_vecMoveSpeed, GetForward()) * m_pHandlingData->m_fTractionLoss;
                    fTractionLoss = std::min(fTractionLoss, m_fTurnMass * 0.01F);

                    if (fGasState > 0.01F) {
                        fTractionLoss *= (0.55F - fGasState);
                        if (m_nStatus == eEntityStatus::STATUS_PLAYER)
                            fTractionLoss *= 2.6F;
                        else
                            fTractionLoss *= 5.0F;
                    }

                    if (m_fGasPedal < 0.0f && fTractionLoss > 0.0f ||
                        m_fGasPedal > 0.0f && fTractionLoss < 0.0f
                    ) {
                        fTractionLoss *= -1.0F;
                    }

                    CVector vecTractionLoss(-fSteerAngleSin, 0.0F, 0.0F);
                    vecTractionLoss *= fTractionLoss;
                    CVector vecTractionLossTransformed = Multiply3x3(GetMatrix(), vecTractionLoss);
                    vecTractionLossTransformed *= fThrustDepth * CTimer::GetTimeStep();

                    CPhysical::ApplyMoveForce(vecTractionLossTransformed);
                    CPhysical::ApplyTurnForce(vecTractionLossTransformed, vecTransformedThrustPoint);

                    auto fUsedTimeStep = std::max(CTimer::GetTimeStep(), 0.01F);
                    auto vecTurn = GetRight() * fUsedTimeStep / fTraction * fTractionLoss * fSteerAngleSin * -0.75F;
                    CPhysical::ApplyTurnForce(vecTurn, GetUp());
                }
            }
        }
    }

    if (m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear != 0.0F) {
        auto right = GetForward().Cross(CVector::ZAxisVector());

        const auto mult =
              DotProduct(right, m_vecMoveSpeed)
            * m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear
            * CTimer::GetTimeStep()
            * fImmersionDepth
            * m_fMass
            * -0.1F;

        const auto x = right.x * 0.3F;
        right.x -= right.y * 0.3F;
        right.y += x;

        CPhysical::ApplyMoveForce(right * mult);
    }

    if (m_nStatus == eEntityStatus::STATUS_PLAYER && pad->GetHandBrake()) {
        auto fDirDotProd = DotProduct(m_vecMoveSpeed, GetForward());
        if (fDirDotProd > 0.0F) {
            auto fMoveForceMult = fDirDotProd * m_pHandlingData->m_fSuspensionLowerLimit * CTimer::GetTimeStep() * fImmersionDepth * m_fMass * -0.1F;
            auto vecMoveForce = GetForward() * fMoveForceMult;
            CPhysical::ApplyMoveForce(vecMoveForce);
        }
    }

    if (bOnWater && !bPostCollision && !bCollidedWithWorld) {
        ApplyBoatWaterResistance(boatHandling, fImmersionDepth);
    }

    // 0x6DCD63
    if ((m_nModelIndex != MODEL_SKIMMER || m_f2ndSteerAngle == 0.0F) && !bCollidedWithWorld) {
        auto vecTurnRes = Pow(boatHandling->m_vecTurnRes, CTimer::GetTimeStep());
        m_vecTurnSpeed = Multiply3x3(m_vecTurnSpeed, GetMatrix());
        m_vecTurnSpeed.y *= vecTurnRes.y;
        m_vecTurnSpeed.z *= vecTurnRes.z;

        float fMult = vecTurnRes.x / (sq(m_vecTurnSpeed.x) * 1000.0F + 1.0F) * m_vecTurnSpeed.x - m_vecTurnSpeed.x;
        fMult *= m_fTurnMass;
        auto vecTurnForce = GetUp() * fMult;

        m_vecTurnSpeed = Multiply3x3(GetMatrix(), m_vecTurnSpeed);
        auto vecCentreOfMass = Multiply3x3(GetMatrix(), m_vecCentreOfMass);
        auto vecTurnPoint = GetForward() + vecCentreOfMass;
        CPhysical::ApplyTurnForce(vecTurnForce, vecTurnPoint);
    }

    // Handle wave collision
    if (!bPostCollision && bOnWater && GetUp().z > 0.0F) {
        auto fWaveMult = floorf((fImmersionDepth - *fLastWaterImmersionDepth) * 10000.0F);
        auto fAudioVolume = fWaveMult * boatHandling->m_fWaveAudioMult;
        if (fAudioVolume > 200.0F)
            m_vehicleAudio.AddAudioEvent(eAudioEvents::AE_BOAT_HIT_WAVE, fAudioVolume);

        if (fWaveMult > 200.0F) {
            auto fZComp = m_vecMoveSpeed.SquaredMagnitude() * fWaveMult / 1000.0F;
            CVector vecWaveMoveForce(0.0F, 0.0F, fZComp);

            vecWaveMoveForce.z = std::min(vecWaveMoveForce.z, m_pHandlingData->m_fBrakeDeceleration - m_vecMoveSpeed.z);
            vecWaveMoveForce.z = std::max(vecWaveMoveForce.z, 0.0F);

            auto fMoveDotProd = DotProduct(m_vecMoveSpeed, GetForward());
            auto fTurnForceMult = fWaveMult * m_pHandlingData->m_fBrakeBias * -0.01F;

            auto vecMoveForce = GetForward() * fTurnForceMult * fMoveDotProd;
            vecWaveMoveForce += vecMoveForce;
            vecWaveMoveForce *= m_fMass;

            CPhysical::ApplyMoveForce(vecWaveMoveForce);
            CPhysical::ApplyTurnForce(vecWaveMoveForce, vecBuoyancyTurnPoint);
        }
    }

    *fLastWaterImmersionDepth = fImmersionDepth;
    if (IsSubBoat()) {
        AsBoat()->m_vecWaterDamping = vecBuoyancyForce;
        AsBoat()->m_nBoatFlags.bOnWater = bOnWater;
    }
    else if (IsAutomobile()) {
        this->AsAutomobile()->m_fDoomHorizontalRotation = vecBuoyancyForce.Magnitude();
    }
}

// 0x6DD130
void CVehicle::DoBoatSplashes(float fWaterDamping) {
    return plugin::CallMethod<0x6DD130, CVehicle*, float>(this, fWaterDamping);

    const auto speedDist = m_vecMoveSpeed.SquaredMagnitude();
    if (speedDist <= 0.0025f || GetUp().z <= 0.0f || TheCamera.GetLookingForwardFirstPerson() || !IsVisible()) {
        return;
    }

    if (m_autoPilot.m_nCarMission == MISSION_CRUISE && (CTimer::m_FrameCounter & 2) != 0) {
        return;
    }

    auto vec = GetPosition() - TheCamera.GetPosition(); // -> DistanceBetweenPoints2D()
    vec.z = 0.0f;
    auto dist = vec.Magnitude();
    if (dist >= 80.0f)
        return;

    auto v9 = std::sqrt(speedDist) * 0.075f * fWaterDamping;
    if (m_nModelIndex == MODEL_SKIMMER) {
        v9 = std::min(v9 * 3.0f, 0.5f);
    } else if (v9 > 1.0f) {
        v9 = 1.0f;
    }

    if (v9 <= 0.15f) {
        return;
    }

    auto v48 = v9 * 0.75f;
    if (m_autoPilot.m_nCarMission == MISSION_CRUISE) {
        auto v10 = v48 + v48;
        if (v10 >= 1.0f)
            v48 = 1.0f;
        else
            v48 = v10;
    }

    auto alpha0 = std::min(v48 * 128.0f, 64.0f);
    if (dist > 50.0f) {
        alpha0 *= (80.0f - dist) * 0.033f;
    }

    FxPrtMult_c particleData(1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f);

    auto alpha = alpha0 / 255.0f;
    particleData.m_Color.alpha = alpha >= 1.0f ? 1.0f : alpha;

    auto v12 = v48 * 10.0f;
    auto size = v12 + 0.75f * 0.1f;
    particleData.m_fSize = size >= 1.0f ? 1.0f : size;

    auto life = CGeneral::GetRandomNumberInRange(0.8f, 1.2f) * (v48 + v48 + 0.3f) * 0.2f;
    particleData.m_fLife = life >= 1.0f ? 1.0f : life;

    const CVector& colMin = GetColModel()->GetBoundingBox().m_vecMin;
    const CVector& colMax = GetColModel()->GetBoundingBox().m_vecMax;

    auto X_MULT = 0.7f;
    auto Z_MULT = 0.0f;
    if (m_nModelIndex == MODEL_SKIMMER) {
        X_MULT = 0.25f; // 0x8D3678
        Z_MULT = 0.85f; // 0x8D3674
    }

    auto baseVel = CVector{ -GetForward().x, -GetRight().y, -GetRight().z };

    CVector p0 = { colMin.x * X_MULT, colMax.y / 2.0f, colMin.z * Z_MULT };
    p0 = MultiplyMatrixWithVector(*m_matrix, &p0);
    auto vel0 = baseVel * CGeneral::GetRandomNumberInRange(0.8f, 1.2f);
    vel0 -= GetRight() * CGeneral::GetRandomNumberInRange(0.3f, 0.7f); // minus
    vel0 += GetUp() * CGeneral::GetRandomNumberInRange(0.8f, 1.2f);
    vel0 *= v12;
    g_fx.m_BoatSplash->AddParticle(&p0, &vel0, 0.0f, &particleData, -1.0f, 1.2f, 0.6f, false);

    CVector p1 = { colMax.x * X_MULT, colMax.y / 2.0f, colMin.z * Z_MULT };
    p1 = MultiplyMatrixWithVector(*m_matrix, &p1);
    auto vel1 = baseVel * CGeneral::GetRandomNumberInRange(0.8f, 1.2f);
    vel1 += GetRight() * CGeneral::GetRandomNumberInRange(0.3f, 0.7f);  // plus
    vel1 += GetUp() * CGeneral::GetRandomNumberInRange(0.8f, 1.2f);
    vel1 *= v12;
    g_fx.m_BoatSplash->AddParticle(&p1, &vel1, 0.0f, &particleData, -1.0f, 1.2f, 0.6f, false);
}

// 0x6DD6F0
void CVehicle::DoSunGlare() {
    ((void(__thiscall*)(CVehicle*))0x6DD6F0)(this);
}

// 0x6DDF60
void CVehicle::AddWaterSplashParticles() {
    ((void(__thiscall*)(CVehicle*))0x6DDF60)(this);
}

// 0x6DE240
void CVehicle::AddExhaustParticles() {
    if (m_bOffscreen)
        return;

    float dist = DistanceBetweenPointsSquared(GetPosition(), TheCamera.GetPosition());
    if (dist > 256.0f || dist > 64.0f && !((CTimer::GetFrameCounter() + m_nModelIndex) & 1)
    ) {
        return;
    }
    auto mi = GetVehicleModelInfo();
    CVector firstExhaustPos = mi->GetModelDummyPosition(DUMMY_EXHAUST);
    CVector secondExhaustPos = firstExhaustPos;
    secondExhaustPos.x *= -1.0f;
    CMatrix entityMatrix (*m_matrix);
    bool bHasDoubleExhaust = m_pHandlingData->m_bDoubleExhaust;
    if (IsSubBike()) {
        auto* bike = AsBike();
        bike->CalculateLeanMatrix();
        entityMatrix = bike->m_mLeanMatrix;
        switch (m_nModelIndex) {
        case MODEL_FCR900:
            if (m_anExtras[0] == 1 || m_anExtras[0] == 2)
                bHasDoubleExhaust = true;
            break;
        case MODEL_NRG500:
            if (!m_anExtras[0] || m_anExtras[0] == 1)
                secondExhaustPos = mi->GetModelDummyPosition(DUMMY_EXHAUST_SECONDARY);
            break;
        case MODEL_BF400:
            if (m_anExtras[0] == 2)
                bHasDoubleExhaust = true;
            break;
        }
    }

    if (firstExhaustPos == 0.0f) {
        return;
    }

    CVector vecParticleVelocity;
    if (DotProduct(GetForward(), m_vecMoveSpeed) >= 0.05f) {
        vecParticleVelocity = m_vecMoveSpeed * 30.0f;
    } else {
        static float randomFactor = CGeneral::GetRandomNumberInRange(-1.8f, -0.9f);
        vecParticleVelocity = randomFactor * GetForward();
    }

    firstExhaustPos = entityMatrix * firstExhaustPos;
    bool bFirstExhaustSubmergedInWater = false;
    bool bSecondExhaustSubmergedInWater = false;
    float pLevel = 0.0f;
    if (physicalFlags.bTouchingWater && CWaterLevel::GetWaterLevel(firstExhaustPos, pLevel, true) &&
        pLevel >= firstExhaustPos.z) {
        bFirstExhaustSubmergedInWater = true;
    }

    if (bHasDoubleExhaust) {
        secondExhaustPos = entityMatrix * secondExhaustPos;
        if (physicalFlags.bTouchingWater && CWaterLevel::GetWaterLevel(secondExhaustPos, pLevel, true) &&
            pLevel >= secondExhaustPos.z) {
            bSecondExhaustSubmergedInWater = true;
        }
    }

    if (CGeneral::GetRandomNumberInRange(1.0f, 3.0f) * (m_fGasPedal + 1.1f) <= 2.5f)
        return;

    float fMoveSpeed = m_vecMoveSpeed.Magnitude() * 0.5f;
    float particleAlpha = 0.0f;
    if (0.25f - fMoveSpeed >= 0.0f) {
        particleAlpha = 0.25f - fMoveSpeed;
    }
    float fLife = std::max(0.2f - fMoveSpeed, 0.0f);
    FxPrtMult_c fxPrt(0.9f, 0.9f, 1.0f, particleAlpha, 0.2f, 1.0f, fLife);

    for (auto i = 0; i < 2; i++) {
        FxSystem_c* firstExhaustFxSystem = g_fx.m_SmokeII3expand;
        if (bFirstExhaustSubmergedInWater) {
            fxPrt.m_Color.alpha = particleAlpha * 0.5f;
            fxPrt.m_fSize = 0.6f;
            firstExhaustFxSystem = g_fx.m_Bubble;
        }
        firstExhaustFxSystem->AddParticle(&firstExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
        if (bHasDoubleExhaust) {
            FxSystem_c* secondExhaustFxSystem = g_fx.m_SmokeII3expand;
            if (bSecondExhaustSubmergedInWater) {
                fxPrt.m_Color.alpha = particleAlpha * 0.5f;
                fxPrt.m_fSize = 0.6f;
                secondExhaustFxSystem = g_fx.m_Bubble;
            }
            secondExhaustFxSystem->AddParticle(&secondExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
        }

        if (m_fGasPedal > 0.5f && m_nCurrentGear < 3) {
            if (CGeneral::GetRandomNumber() % 2) {
                FxSystem_c* secondaryExhaustFxSystem = g_fx.m_SmokeII3expand;
                if (bFirstExhaustSubmergedInWater) {
                    fxPrt.m_Color.alpha = particleAlpha * 0.5f;
                    fxPrt.m_fSize = 0.6f;
                    secondaryExhaustFxSystem = g_fx.m_Bubble;
                }
                secondaryExhaustFxSystem->AddParticle(&firstExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
            } else if (bHasDoubleExhaust) {
                FxSystem_c* secondaryExhaustFxSystem = g_fx.m_SmokeII3expand;
                if (bSecondExhaustSubmergedInWater) {
                    fxPrt.m_Color.alpha = particleAlpha * 0.5f;
                    fxPrt.m_fSize = 0.6f;
                    secondaryExhaustFxSystem = g_fx.m_Bubble;
                }
                secondaryExhaustFxSystem->AddParticle(&secondExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
            }
        }
    }
}

// always return false?
// 0x6DE880
bool CVehicle::AddSingleWheelParticles(tWheelState wheelState, uint32 arg1, float arg2, float arg3, CColPoint* arg4, CVector* arg5, float arg6, int32 arg7, uint32 surfaceType, bool* bloodState, uint32 arg10) {
    return ((bool(__thiscall*)(CVehicle*, tWheelState, uint32, float, float, CColPoint*, CVector*, float, int32, uint32, bool*, uint32))0x6DE880)(this, wheelState, arg1, arg2, arg3, arg4, arg5, arg6, arg7, surfaceType, bloodState, arg10);
}

// 0x6DF3D0
bool CVehicle::GetSpecialColModel() {
    return ((bool(__thiscall*)(CVehicle*))0x6DF3D0)(this);
}

// 0x6DF930
void CVehicle::RemoveVehicleUpgrade(int32 upgradeModelIndex) {
    ((void(__thiscall*)(CVehicle*, int32))0x6DF930)(this, upgradeModelIndex);
}

// 0x6DFA20
void CVehicle::AddUpgrade(int32 modelIndex, int32 upgradeIndex) {
    ((void(__thiscall*)(CVehicle*, int32, int32))0x6DFA20)(this, modelIndex, upgradeIndex);
}

// 0x6DFC50
void CVehicle::UpdateTrailerLink(bool arg0, bool arg1) {
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6DFC50)(this, arg0, arg1);
}

// 0x6E0050
void CVehicle::UpdateTractorLink(bool arg0, bool arg1) {
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6E0050)(this, arg0, arg1);
}

// 0x6E0400
CEntity* CVehicle::ScanAndMarkTargetForHeatSeekingMissile(CEntity* entity) {
    return ((CEntity * (__thiscall*)(CVehicle*, CEntity*))0x6E0400)(this, entity);
}

// 0x6E05C0
void CVehicle::FireHeatSeakingMissile(CEntity* targetEntity, eOrdnanceType type, bool arg2) {
    ((void(__thiscall*)(CVehicle*, CEntity*, eOrdnanceType, bool))0x6E05C0)(this, targetEntity, type, arg2);
}

// 0x6E07E0
void CVehicle::PossiblyDropFreeFallBombForPlayer(eOrdnanceType type, bool arg1) {
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6E07E0)(this, type, arg1);
}

// 0x6E0950
void CVehicle::ProcessSirenAndHorn(bool arg0) {
    ((void(__thiscall*)(CVehicle*, bool))0x6E0950)(this, arg0);
}

// 0x6E0A50
bool CVehicle::DoHeadLightEffect(eVehicleDummy dummyId, CMatrix& vehicleMatrix, uint8 lightId, uint8 lightState) {
    return ((bool(__thiscall*)(CVehicle*, int32, CMatrix&, uint8, uint8))0x6E0A50)(this, dummyId, vehicleMatrix, lightId, lightState);
}

// 0x6E0E20
void CVehicle::DoHeadLightBeam(eVehicleDummy dummyId, CMatrix& matrix, bool arg2) {
    const auto* mi = GetVehicleModelInfo();
    CVector pointModelSpace = mi->GetModelDummyPosition(static_cast<eVehicleDummy>(2 * dummyId));
    if (dummyId == DUMMY_LIGHT_REAR_MAIN && pointModelSpace.IsZero())
        return;

    CVector point = matrix.GetPosition() + Multiply3x3(matrix, pointModelSpace);
    if (!arg2) {
        point -= 2 * pointModelSpace.x * matrix.GetRight();
    }
    const CVector pointToCamDir = Normalized(TheCamera.GetPosition() - point);
    const auto    alpha = (uint8)((1.0f - std::fabs(DotProduct(pointToCamDir, matrix.GetForward()))) * 32.0f);

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,    RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,             RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,            RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,            RWRSTATE(rwSHADEMODEGOURAUD));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,        RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATECULLMODE,             RWRSTATE(rwCULLMODECULLNONE));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTION,    RWRSTATE(rwALPHATESTFUNCTIONGREATER));
    RwRenderStateSet(rwRENDERSTATEALPHATESTFUNCTIONREF, RWRSTATE(FALSE));

    const float   angleMult   = ModelIndices::IsForklift((int32)m_nModelIndex) ? 0.5f : 0.15f;
    const CVector lightNormal = Normalized(matrix.GetForward() - matrix.GetUp() * angleMult);
    const CVector lightRight  = Normalized(CrossProduct(lightNormal, pointToCamDir));
    const CVector lightPos    = point - matrix.GetForward() * 0.1f;

    const CVector posn[] = {
        lightPos - lightRight * 0.05f,
        lightPos + lightRight * 0.05f,
        lightPos + lightNormal * 3.0f - lightRight * 0.5f,
        lightPos + lightNormal * 3.0f + lightRight * 0.5f,
        lightPos + lightNormal * 0.2f
    };
    const uint8 alphas[] = { alpha, alpha, 0, 0, alpha };

    RxObjSpace3DVertex vertices[5];
    for (auto i = 0u; i < std::size(vertices); i++) {
        const RwRGBA color = { 255, 255, 255, alphas[i] };
        RxObjSpace3DVertexSetPreLitColor(&vertices[i], &color);
        RxObjSpace3DVertexSetPos(&vertices[i], &posn[i]);
    }

    if (RwIm3DTransform(vertices, std::size(vertices), nullptr, rwIM3D_VERTEXRGBA | rwIM3D_VERTEXXYZ))
    {
        RxVertexIndex indices[] = { 0, 1, 4, 1, 3, 4, 2, 3, 4, 0, 2, 4 };
        RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, indices, std::size(indices));
        RwIm3DEnd();
    }

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,          RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,           RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,              RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,             RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,     RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATECULLMODE,              RWRSTATE(rwCULLMODECULLBACK));
}

// 0x6E1440
void CVehicle::DoHeadLightReflectionSingle(CMatrix& matrix, uint8 lightId) {
    ((void(__thiscall*)(CVehicle*, CMatrix&, uint8))0x6E1440)(this, matrix, lightId);
}

// 0x6E1600
void CVehicle::DoHeadLightReflectionTwin(CMatrix& matrix) {
    ((void(__thiscall*)(CVehicle*, CMatrix&))0x6E1600)(this, matrix);
}

// 0x6E1720
void CVehicle::DoHeadLightReflection(CMatrix& arg0, uint32 flags, uint8 left, uint8 right) {
    ((void(__thiscall*)(CVehicle*, CMatrix&, uint32, uint8, uint8))0x6E1720)(this, arg0, flags, left, right);
}

// 0x6E1780
bool CVehicle::DoTailLightEffect(int32 lightId, CMatrix& matrix, uint8 arg2, uint8 arg3, uint32 arg4, uint8 arg5) {
    return ((bool(__thiscall*)(CVehicle*, int32, CMatrix&, uint8, uint8, uint32, uint8))0x6E1780)(this, lightId, matrix, arg2, arg3, arg4, arg5);
}

// 0x6E1A60
void CVehicle::DoVehicleLights(CMatrix& matrix, eVehicleLightsFlags flags) {
    ((void(__thiscall*)(CVehicle*, CMatrix&, uint32))0x6E1A60)(this, matrix, flags);
}

// 0x6E2900
void CVehicle::FillVehicleWithPeds(bool bSetClothesToAfro) {
    ((void(__thiscall*)(CVehicle*, bool))0x6E2900)(this, bSetClothesToAfro);
}

// 0x6E2E50
void CVehicle::DoBladeCollision(CVector pos, CMatrix& matrix, int16 rotorType, float radius, float damageMult) {
    ((void(__thiscall*)(CVehicle*, CVector, CMatrix&, int16, float, float))0x6E2E50)(this, pos, matrix, rotorType, radius, damageMult);
}

// 0x6E3290
void CVehicle::AddVehicleUpgrade(int32 modelId) {
    ((void(__thiscall*)(CVehicle*, int32))0x6E3290)(this, modelId);
}

// 0x6E3400
void CVehicle::SetupUpgradesAfterLoad() {
    for (auto& upgrade : m_anUpgrades) {
        if (upgrade == -1)
            continue;

        auto savedUpgrade = upgrade;
        upgrade = -1;
        AddVehicleUpgrade(savedUpgrade);
    }
}

// 0x6E3440
void CVehicle::GetPlaneWeaponFiringStatus(bool& status, eOrdnanceType& ordnanceType) {
    ((void(__thiscall*)(CVehicle*, bool&, eOrdnanceType&))0x6E3440)(this, status, ordnanceType);
}

bool IsValidModForVehicle(uint32 modelId, CVehicle* vehicle) {
    return plugin::CallAndReturn<bool, 0x49B010, uint32, CVehicle*>(modelId, vehicle);
}

// 0x6E38F0
bool IsVehiclePointerValid(CVehicle* vehicle)
{
    return ((bool(__cdecl*)(CVehicle*))0x6E38F0)(vehicle);
}

// 0x6E3950
void CVehicle::ProcessWeapons() {
    ((void(__thiscall*)(CVehicle*))0x6E3950)(this);
}

// 0x73F400
void CVehicle::DoFixedMachineGuns() {
    if (CCamera::GetActiveCamera().m_nDirectionWasLooking != eLookingDirection::LOOKING_DIRECTION_FORWARD)
        return;

    auto pad = CPad::GetPad(m_pDriver && m_pDriver->m_nPedType == PED_TYPE_PLAYER2 ? 1 : 0);
    if (pad->GetCarGunFired() && !vehicleFlags.bGunSwitchedOff) {
        FireFixedMachineGuns();
    } else if (CTimer::GetTimeInMS() > m_nGunFiringTime + 1400) {
        m_nAmmoInClip = 20;
    }
}

// 0x73DF00
void CVehicle::FireFixedMachineGuns() {
    plugin::CallMethod<0x73DF00, CVehicle*>(this);
}

// 0x741FD0
void CVehicle::DoDriveByShootings() {
    plugin::CallMethod<0x741FD0, CVehicle*>(this);
}

// NOTSA
bool CVehicle::AreAnyOfPassengersFollowerOfGroup(const CPedGroup& group) {
    const auto end = m_apPassengers + m_nMaxPassengers;
    return std::find_if(m_apPassengers, end, [&](CPed* passenger) {
        return group.GetMembership().IsFollower(passenger);
    }) != end;
}

/*!
* @notsa
* @return The index of a passenger, or `std::nullopt` if the given ped isn't a passenger.
*/
auto CVehicle::GetPassengerIndex(const CPed* passenger) const -> std::optional<size_t> {
    const auto passengers = GetPassengers();
    const auto it = rng::find(passengers, passenger);
    if (it == passengers.end()) {
        return std::nullopt;
    }
    return (size_t)rng::distance(passengers.begin(), it);
}

