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
#include "Radar.h"
#include "VehicleSaveStructure.h"
#include "Rope.h"
#include "Ropes.h"

float& CVehicle::WHEELSPIN_TARGET_RATE = *(float*)0x8D3498;
float& CVehicle::WHEELSPIN_INAIR_TARGET_RATE = *(float*)0x8D349C;
float& CVehicle::WHEELSPIN_RISE_RATE = *(float*)0x8D34A0;
float& CVehicle::WHEELSPIN_FALL_RATE = *(float*)0x8D34A4;
float& CVehicle::m_fAirResistanceMult = *(float*)0x8D34A8;
float& CVehicle::ms_fRailTrackResistance = *(float*)0x8D34AC;
float& CVehicle::ms_fRailTrackResistanceDefault = *(float*)0x8D34B0;
bool& CVehicle::bDisableRemoteDetonation = *(bool*)0xC1CC00;
bool& CVehicle::bDisableRemoteDetonationOnContact = *(bool*)0xC1CC01;
bool& CVehicle::m_bEnableMouseSteering = *(bool*)0xC1CC02;
bool& CVehicle::m_bEnableMouseFlying = *(bool*)0xC1CC03;
int32& CVehicle::m_nLastControlInput = *(int32*)0xC1CC04;
CColModel** CVehicle::m_aSpecialColVehicle = (CColModel * *)0xC1CC08;
bool& CVehicle::ms_forceVehicleLightsOff = *(bool*)0xC1CC18;
bool& CVehicle::s_bPlaneGunsEjectShellCasings = *(bool*)0xC1CC19;
CColModel (&CVehicle::m_aSpecialColModel)[4] = *(CColModel(*)[4])0xC1CC78;
tHydrualicData(&CVehicle::m_aSpecialHydraulicData)[4] = *(tHydrualicData(*)[4])0xC1CB60;

float& fBurstTyreMod = *(float*)0x8D34B4;
float& fBurstSpeedMax = *(float*)0x8D34B8;
float& CAR_NOS_EXTRA_SKID_LOSS = *(float*)0x8D34BC;
float& WS_TRAC_FRAC_LIMIT = *(float*)0x8D34C0;
float& WS_ALREADY_SPINNING_LOSS = *(float*)0x8D34C4;
float& fBurstBikeTyreMod = *(float*)0x8D34C8;
float& fBurstBikeSpeedMax = *(float*)0x8D34CC;
float& fTweakBikeWheelTurnForce = *(float*)0x8D34D0;
float& AUTOGYRO_ROTORSPIN_MULT = *(float*)0x8D34D4;
float& AUTOGYRO_ROTORSPIN_MULTLIMIT = *(float*)0x8D34D8;
float& AUTOGYRO_ROTORSPIN_DAMP = *(float*)0x8D34DC;
float& AUTOGYRO_ROTORLIFT_MULT = *(float*)0x8D34E0;
float& AUTOGYRO_ROTORLIFT_FALLOFF = *(float*)0x8D34E4;
float& AUTOGYRO_ROTORTILT_ANGLE = *(float*)0x8D34E8;
float& ROTOR_SEMI_THICKNESS = *(float*)0x8D34EC;
float* fSpeedMult = (float*)0x8D34F8;
float& fDamagePosSpeedShift = *(float*)0x8D3510;
float& DIFF_LIMIT = *(float*)0x8D35B4;
float& DIFF_SPRING_MULT_X = *(float*)0x8D35B8;
float& DIFF_SPRING_MULT_Y = *(float*)0x8D35BC;
float& DIFF_SPRING_MULT_Z = *(float*)0x8D35C0;
float& DIFF_SPRING_COMPRESS_MULT = *(float*)0x8D35C4;
CVector* VehicleGunOffset = (CVector*)0x8D35D4;
char*& HandlingFilename = *(char**)0x8D3970;
char(*VehicleNames)[14] = (char(*)[14])0x8D3978;

void CVehicle::InjectHooks()
{
    RH_ScopedClass(CVehicle);
    RH_ScopedCategory("Vehicle/Ped");

    RH_ScopedInstall(SetModelIndex_Reversed, 0x6D6A40);
    RH_ScopedInstall(DeleteRwObject_Reversed, 0x6D6410);
    RH_ScopedInstall(SpecialEntityPreCollisionStuff_Reversed, 0x6D6640);
    RH_ScopedInstall(SpecialEntityCalcCollisionSteps_Reversed, 0x6D0E90);
    RH_ScopedInstall(SetupLighting_Reversed, 0x553F20);
    RH_ScopedInstall(RemoveLighting_Reversed, 0x5533D0);
    RH_ScopedInstall(PreRender_Reversed, 0x6D6480);
    RH_ScopedInstall(Render_Reversed, 0x6D0E60);
    RH_ScopedInstall(ProcessOpenDoor_Reversed, 0x6D56C0);
    RH_ScopedInstall(ProcessDrivingAnims_Reversed, 0x6DF4A0);
    RH_ScopedInstall(GetHeightAboveRoad_Reversed, 0x6D63F0);
    RH_ScopedInstall(CanPedStepOutCar_Reversed, 0x6D1F30);
    RH_ScopedInstall(CanPedJumpOutCar_Reversed, 0x6D2030);
    RH_ScopedInstall(GetTowHitchPos_Reversed, 0x6DFB70);
    RH_ScopedInstall(GetTowBarPos_Reversed, 0x6DFBE0);
    RH_ScopedInstall(Save_Reversed, 0x5D4760);
    RH_ScopedInstall(Load_Reversed, 0x5D2900);
    RH_ScopedInstall(Shutdown, 0x6D0B40);
    RH_ScopedInstall(GetRemapIndex, 0x6D0B70);
    RH_ScopedInstall(SetRemap, 0x6D0C00);
    RH_ScopedInstall(SetCollisionLighting, 0x6D0CA0);
    RH_ScopedInstall(UpdateLightingFromStoredPolys, 0x6D0CC0);
    RH_ScopedInstall(CalculateLightingFromCollision, 0x6D0CF0);
    RH_ScopedInstall(ProcessWheel, 0x6D6C00);
    RH_ScopedOverloadedInstall(IsDriver, "Ped", 0x6D1C40, bool(CVehicle::*)(CPed*));
    RH_ScopedOverloadedInstall(IsDriver, "Int", 0x6D1C60, bool(CVehicle::*)(int32));
    RH_ScopedInstall(AddExhaustParticles, 0x6DE240);
    RH_ScopedInstall(ApplyBoatWaterResistance, 0x6D2740);
    RH_ScopedInstall(ProcessBoatControl, 0x6DBCE0);
    RH_ScopedInstall(ChangeLawEnforcerState, 0x6D2330);
    RH_ScopedInstall(GetVehicleAppearance, 0x6D1080);
    RH_ScopedInstall(DoHeadLightBeam, 0x6E0E20);

}

CVehicle::CVehicle(eVehicleCreatedBy createdBy) : CPhysical(), m_vehicleAudio(), m_autoPilot()
{
    //plugin::CallMethod<0x6D5F10, CVehicle*, uint8>(this, createdBy);
    m_bHasPreRenderEffects = true;
    m_nType = ENTITY_TYPE_VEHICLE;

    m_fRawSteerAngle = 0.0f;
    m_fSteerAngle = 0.0f;
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

    auto fRand = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
    vehicleFlags.bCanPark = fRand < 0.0F; //BUG: Seemingly never true, rand() strips the sign bit to always be 0

    CCarCtrl::UpdateCarCount(this, false);
    m_nExtendedRemovalRange = 0;
    m_fHealth = 1000.0;
    m_pDriver = nullptr;
    m_nNumPassengers = 0;
    m_nMaxPassengers = 8;
    m_nNumGettingIn = 0;
    m_nGettingInFlags = 0;
    m_nGettingOutFlags = 0;

    for (size_t i = 0; i < m_nMaxPassengers; ++i)
        m_apPassengers[i] = nullptr;

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
    field_518 = 0;
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
    m_comedyControlState = 0;
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

    memset(m_anUpgrades, 0xFFu, sizeof(m_anUpgrades));
    m_fWheelScale = 1.0f;
    m_nWindowsOpenFlags = 0;
    m_nNitroBoosts = 0;
    m_nHasslePosId = 0;
    m_nVehicleWeaponInUse = 0;
    m_fDirtLevel = (float)((rand() % 15));
    m_nCreationTime = CTimer::GetTimeInMS();
    CVehicle::SetCollisionLighting(0x48);
}

CVehicle::~CVehicle()
{
    CReplay::RecordVehicleDeleted(this);
    m_nAlarmState = 0;
    CVehicle::DeleteRwObject();
    CRadar::ClearBlipForEntity(eBlipType::BLIP_CAR, CPools::ms_pVehiclePool->GetRef(this));

    if (m_pDriver)
        m_pDriver->FlagToDestroyWhenNextProcessed();

    for (auto i = 0; i < m_nMaxPassengers; ++i)
        if (m_apPassengers[i])
            m_apPassengers[i]->FlagToDestroyWhenNextProcessed();

    if (m_pFire)
    {
        m_pFire->Extinguish();
        m_pFire = nullptr;
    }

    CCarCtrl::UpdateCarCount(this, true);
    if (vehicleFlags.bIsAmbulanceOnDuty)
    {
        --CCarCtrl::NumAmbulancesOnDuty;
        vehicleFlags.bIsAmbulanceOnDuty = false;
    }

    if (vehicleFlags.bIsFireTruckOnDuty)
    {
        --CCarCtrl::NumFireTrucksOnDuty;
        vehicleFlags.bIsFireTruckOnDuty = false;
    }

    if (m_vehicleSpecialColIndex > -1)
    {
        CVehicle::m_aSpecialColVehicle[m_vehicleSpecialColIndex] = nullptr;
        m_vehicleSpecialColIndex = -1;
    }

    if (m_pOverheatParticle)
    {
        g_fxMan.DestroyFxSystem(m_pOverheatParticle);
        m_pOverheatParticle = nullptr;
    }

    if (m_pFireParticle)
    {
        g_fxMan.DestroyFxSystem(m_pFireParticle);
        m_pFireParticle = nullptr;
    }

    if (m_pDustParticle)
    {
        g_fxMan.DestroyFxSystem(m_pDustParticle);
        m_pDustParticle = nullptr;
    }

    if (m_pCustomCarPlate)
    {
        RwTextureDestroy(m_pCustomCarPlate);
        m_pCustomCarPlate = nullptr;
    }

    const auto iRopeInd = CRopes::FindRope(reinterpret_cast<uint32>(this) + 1);
    if (iRopeInd >= 0)
        CRopes::GetRope(iRopeInd).Remove();

    if (!physicalFlags.bDestroyed && m_fHealth < 250.0F)
        CDarkel::RegisterCarBlownUpByPlayer(this, 0);
}

void* CVehicle::operator new(uint32 size) {
    return CPools::ms_pVehiclePool->New();
}

void CVehicle::operator delete(void* data) {
    CPools::ms_pVehiclePool->Delete(static_cast<CVehicle*>(data));
}

void CVehicle::SetModelIndex(uint32 index)
{
    return CVehicle::SetModelIndex_Reversed(index);
}
void CVehicle::SetModelIndex_Reversed(uint32 index)
{
    CEntity::SetModelIndex(index);
    auto vehModelInfo = CModelInfo::GetModelInfo(index)->AsVehicleModelInfoPtr();
    CustomCarPlate_TextureCreate(vehModelInfo);

    for (size_t i = 0; i <= 1; ++i)
        m_anExtras[i] = CVehicleModelInfo::ms_compsUsed[i];

    m_nMaxPassengers = CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(index);
    switch (m_nModelIndex)
    {
    case MODEL_RCBANDIT:
    case MODEL_RCBARON:
    case MODEL_RCRAIDER:
    case MODEL_RCGOBLIN:
    case MODEL_RCTIGER:
        vehicleFlags.bIsRCVehicle = true;
        break;
    default:
        vehicleFlags.bIsRCVehicle = false;
        break;
    }

    //Set up weapons
    switch (m_nModelIndex)
    {
    case MODEL_RUSTLER:
    case MODEL_STUNT:
        m_nVehicleWeaponInUse = eCarWeapon::CAR_WEAPON_HEAVY_GUN;
        break;
    case MODEL_BEAGLE:
        m_nVehicleWeaponInUse = eCarWeapon::CAR_WEAPON_FREEFALL_BOMB;
        break;
    case MODEL_HYDRA:
    case MODEL_TORNADO:
        m_nVehicleWeaponInUse = eCarWeapon::CAR_WEAPON_LOCK_ON_ROCKET;
        break;
    }
}

void CVehicle::DeleteRwObject()
{
    CVehicle::DeleteRwObject_Reversed();
}

void CVehicle::DeleteRwObject_Reversed()
{
    if (m_nPreviousRemapTxd != -1)
    {
        m_pRemapTexture = nullptr;
        CTxdStore::RemoveRef(m_nPreviousRemapTxd);
        m_nPreviousRemapTxd = -1;
        m_nRemapTxd = -1;
    }

    RpClumpForAllAtomics(m_pRwClump, RemoveAllUpgradesCB, nullptr);
    memset(m_anUpgrades, 0xFFu, sizeof(m_anUpgrades));
    CEntity::DeleteRwObject();
}

// 0x6D6640
void CVehicle::SpecialEntityPreCollisionStuff(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled,
    bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck)
{
    CVehicle::SpecialEntityPreCollisionStuff_Reversed(colPhysical, bIgnoreStuckCheck, bCollisionDisabled, bCollidedEntityCollisionIgnored, bCollidedEntityUnableToMove, bThisOrCollidedEntityStuck);
}
void CVehicle::SpecialEntityPreCollisionStuff_Reversed(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled,
    bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck)
{
    if (colPhysical->IsPed()
        && colPhysical->AsPed()->bKnockedOffBike
        && colPhysical->AsPed()->m_pVehicle == this)
    {
        bCollisionDisabled = true;
        return;
    }

    if (physicalFlags.bSubmergedInWater
        && m_nStatus != eEntityStatus::STATUS_PLAYER
        && (m_nStatus != eEntityStatus::STATUS_HELI && colPhysical->DoesNotCollideWithFlyers())) //Bug? Seems like it should check for it being heli
    {
        bCollisionDisabled = true;
        return;
    }

    if (m_pEntityIgnoredCollision == colPhysical || colPhysical->m_pEntityIgnoredCollision == this)
    {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (m_pAttachedTo == colPhysical)
    {
        bCollidedEntityCollisionIgnored = true;
        return;
    }

    if (colPhysical->m_pAttachedTo == this)
    {
        bCollisionDisabled = true;
        physicalFlags.b13 = true;
        return;
    }

    if (physicalFlags.bDisableCollisionForce && colPhysical->physicalFlags.bDisableCollisionForce)
    {
        bCollisionDisabled = true;
        return;
    }

    if (m_bIsStuck
        && colPhysical->IsVehicle()
        && (colPhysical->AsVehicle()->physicalFlags.bDisableCollisionForce && !colPhysical->AsVehicle()->physicalFlags.bCollidable))
    {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (colPhysical->IsImmovable())
    {
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

    if (colPhysical->IsRCCar())
    {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (IsRCCar() && (colPhysical->IsVehicle() || colPhysical->IsPed()))
    {
        bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (colPhysical == m_pTractor || colPhysical == m_pTrailer)
    {
        bThisOrCollidedEntityStuck = true;
        physicalFlags.b13 = true;
        return;
    }

    if (colPhysical->m_bIsStuck)
    {
        bCollidedEntityUnableToMove = true;
        return;
    }
}

// 0x6D0E90
uint8 CVehicle::SpecialEntityCalcCollisionSteps(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2)
{
    return CVehicle::SpecialEntityCalcCollisionSteps_Reversed(bProcessCollisionBeforeSettingTimeStep, unk2);
}
uint8 CVehicle::SpecialEntityCalcCollisionSteps_Reversed(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2)
{
    if (physicalFlags.bDisableCollisionForce)
        return 1;

    const auto fMoveSquared = m_vecMoveSpeed.SquaredMagnitude() * pow(CTimer::GetTimeStep(), 2.0F);
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
    auto fLongestDir = fabs(DotProduct(m_vecMoveSpeed, GetForward()) * CTimer::GetTimeStep() / bbox.GetLength());
    fLongestDir = std::max(fLongestDir, fabs(DotProduct(m_vecMoveSpeed, GetRight()) * CTimer::GetTimeStep() / bbox.GetWidth()));
    fLongestDir = std::max(fLongestDir, fabs(DotProduct(m_vecMoveSpeed, GetUp()) * CTimer::GetTimeStep() / bbox.GetHeight()));

    if (IsBike())
        fLongestDir *= 1.5F;

    if (fLongestDir < 1.0F)
        bProcessCollisionBeforeSettingTimeStep = true;
    else if (fLongestDir < 2.0F)
        unk2 = true;

    return static_cast<uint8>(ceil(fMove));
}

// 0x6D6480
void CVehicle::PreRender()
{
    return CVehicle::PreRender_Reversed();
}
void CVehicle::PreRender_Reversed()
{
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
    CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr()->SetEnvMapCoeff(fCoeff);
}

void CVehicle::Render()
{
    return CVehicle::Render_Reversed();
}
void CVehicle::Render_Reversed()
{
    auto* vehicleMI = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    const auto iDirtLevel = static_cast<int32>(m_fDirtLevel) & 0xF;
    CVehicleModelInfo::SetDirtTextures(vehicleMI, iDirtLevel);

    CEntity::Render();
}

bool CVehicle::SetupLighting()
{
    return CVehicle::SetupLighting_Reversed();
}
bool CVehicle::SetupLighting_Reversed()
{
    ActivateDirectional();
    return CRenderer::SetupLightingForEntity(this);
}

void CVehicle::RemoveLighting(bool bRemove)
{
    CVehicle::RemoveLighting_Reversed(bRemove);
}
void CVehicle::RemoveLighting_Reversed(bool bRemove)
{
    if (!physicalFlags.bDestroyed)
        CPointLights::RemoveLightsAffectingObject();

    SetAmbientColours();
    DeActivateDirectional();
}

// 0x871EF0
void CVehicle::ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime)
{
    CVehicle::ProcessOpenDoor_Reversed(ped, doorComponentId, animGroup, animId, fTime);
}
void CVehicle::ProcessOpenDoor_Reversed(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime)
{
    eDoors iCheckedDoor;
    switch (doorComponentId)
    {
    case COMPONENT_DOOR_RF:
        iCheckedDoor = DOOR_RIGHT_FRONT;
        break;
    case COMPONENT_DOOR_LR:
        iCheckedDoor = DOOR_RIGHT_REAR;
        break;
    case COMPONENT_DOOR_RR:
        iCheckedDoor = DOOR_LEFT_FRONT;
        break;
    case COMPONENT_WING_LF:
        iCheckedDoor = DOOR_LEFT_REAR;
        break;
    default:
        assert(false); //Shouldn't get here
        iCheckedDoor = static_cast<eDoors>(fTime);
    }

    if (IsDoorMissing(iCheckedDoor))
        return;

    float fAnimStart, fAnimEnd;
    switch (animId)
    {
    case ANIM_ID_CAR_OPEN_LHS:
    case ANIM_ID_CAR_OPEN_RHS:
    case ANIM_ID_CAR_OPEN_LHS_1:
    case ANIM_ID_CAR_OPEN_RHS_1:
        {
        CVehicleAnimGroupData::GetInOutTimings(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup), eInOutTimingMode::OPEN_OUT, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, false);
        else if (fTime > fAnimEnd)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
        }

    case ANIM_ID_CAR_CLOSE_LHS_0:
    case ANIM_ID_CAR_CLOSE_RHS_0:
    case ANIM_ID_CAR_CLOSE_LHS_1:
    case ANIM_ID_CAR_CLOSE_RHS_1:
    {
        CVehicleAnimGroupData::GetInOutTimings(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup), eInOutTimingMode::CLOSE_OUT, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimEnd)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = 1.0F - invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
    }

    case ANIM_ID_CAR_CLOSEDOOR_LHS_0:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_0:
    case ANIM_ID_CAR_CLOSEDOOR_LHS_1:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_1:
        {
        CVehicleAnimGroupData::GetInOutTimings(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup), eInOutTimingMode::CLOSE_IN, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimEnd)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = 1.0F - invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
        }

    case ANIM_ID_CAR_GETOUT_LHS_0:
    case ANIM_ID_CAR_GETOUT_RHS_0:
    case ANIM_ID_CAR_GETOUT_LHS_1:
    case ANIM_ID_CAR_GETOUT_RHS_1:
        {
        CVehicleAnimGroupData::GetInOutTimings(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup), eInOutTimingMode::OPEN_IN, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimEnd)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
        }

    case ANIM_ID_CAR_JACKEDLHS:
    case ANIM_ID_CAR_JACKEDRHS:
        if (fTime < 0.1F)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > 0.4F)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > 0.1F && fTime < 0.4F)
            OpenDoor(ped, doorComponentId, iCheckedDoor, (fTime - 0.1F) * (10.0F / 3.0F), true);

        return;

    case ANIM_ID_CAR_FALLOUT_LHS:
    case ANIM_ID_CAR_FALLOUT_RHS:
        if (fTime < 0.1F)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > 0.4F)
            OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > 0.1F && fTime < 0.4F)
            OpenDoor(ped, doorComponentId, iCheckedDoor, (fTime - 0.1F) * (10.0F / 3.0F), true);

        return;

    case ANIM_ID_CAR_PULLOUT_LHS:
    case ANIM_ID_CAR_PULLOUT_RHS:
    case ANIM_ID_UNKNOWN_15:
        switch (animGroup)
        {
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
    case ANIM_ID_CAR_ROLLOUT_RHS:
    {
        switch (animGroup)
        {
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
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
    }

    case ANIM_ID_CAR_ROLLDOOR: {
        float fAnimEnd2;
        switch (animGroup)
        {
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
            if (fCurRatio < fNewRatio)
                OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }
        else if (fTime > fAnimEnd && fTime < fAnimEnd2)
        {
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
void CVehicle::ProcessDrivingAnims(CPed* driver, uint8 bBlend)
{
    CVehicle::ProcessDrivingAnims_Reversed(driver, bBlend);
}
void CVehicle::ProcessDrivingAnims_Reversed(CPed* driver, uint8 bBlend)
{
    if (m_bOffscreen || !driver->IsPlayer())
        return;

    auto* radioTuneAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_CAR_TUNE_RADIO);
    if (bBlend)
        radioTuneAnim = CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_CAR_TUNE_RADIO, 4.0F);

    if (radioTuneAnim)
        return;

    CRideAnims* usedAnims;
    auto const fSpeed = m_vecMoveSpeed.Magnitude();

    if (vehicleFlags.bLowVehicle)
        usedAnims = &aDriveAnimIdsLow;
    else if (IsBoat() && !m_pHandlingData->m_bSitInBoat)
        usedAnims = &aDriveAnimIdsBoat;
    else if (CVehicleAnimGroupData::UsesKartDrivingAnims(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup)))
        usedAnims = &aDriveAnimIdsKart;
    else if (CVehicleAnimGroupData::UsesTruckDrivingAnims(static_cast<AssocGroupId>(m_pHandlingData->m_nAnimGroup)))
        usedAnims = &aDriveAnimIdsTruck;
    else
    {
        const auto fDrivingSkill = CStats::GetStatValue(eStats::STAT_DRIVING_SKILL);
        if (fDrivingSkill < 50.0F)
        {
            if (fSpeed <= 0.4F)
                usedAnims = &aDriveAnimIdsBadSlow;
            else
                usedAnims = &aDriveAnimIdsBad;
        }
        else if (fDrivingSkill < 100.0F)
        {
            if (fSpeed <= 0.4F)
                usedAnims = &aDriveAnimIdsStdSlow;
            else
                usedAnims = &aDriveAnimIdsStd;
        }
        else
        {
            if (fSpeed <= 0.4F)
                usedAnims = &aDriveAnimIdsProSlow;
            else
                usedAnims = &aDriveAnimIdsPro;
        }
    }

    auto* idleAnim      = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->m_aAnims[eRideAnim::RIDE_IDLE]);
    auto* lookLeftAnim  = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->m_aAnims[eRideAnim::RIDE_LOOK_LEFT]);
    auto* lookRightAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->m_aAnims[eRideAnim::RIDE_LOOK_RIGHT]);
    auto* lookBackAnim  = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, usedAnims->m_aAnims[eRideAnim::RIDE_LOOK_BACK]);

    if (!idleAnim)
    {
        if (RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_CAR_SIT))
        {
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->m_aAnims[eRideAnim::RIDE_IDLE], 4.0F);
        }
        return;
    }

    if (idleAnim->m_fBlendAmount < 1.0F)
        return;

    if (lookBackAnim
        && CCamera::GetActiveCamera().m_nMode == eCamMode::MODE_1STPERSON
        && CCamera::GetActiveCamera().m_nDirectionWasLooking == eLookingDirection::LOOKING_DIRECTION_BEHIND)
    {
        lookBackAnim->m_fBlendDelta = -1000.0F;
    }

    auto* driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBY_L);
    if (!driveByAnim)
        driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBY_R);
    if (!driveByAnim)
        driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBYL_L);
    if (!driveByAnim)
        driveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBYL_R);

    if (!vehicleFlags.bLowVehicle
        && m_fGasPedal < 0.0F
        && !driveByAnim
        && GetVehicleAppearance() != VEHICLE_APPEARANCE_HELI
        && GetVehicleAppearance() != VEHICLE_APPEARANCE_PLANE)
    {
        if ((CCamera::GetActiveCamera().m_nMode != eCamMode::MODE_1STPERSON
            || CCamera::GetActiveCamera().m_nDirectionWasLooking != eLookingDirection::LOOKING_DIRECTION_BEHIND)
            && (!lookBackAnim || lookBackAnim->m_fBlendAmount < 1.0F && lookBackAnim->m_fBlendDelta <= 0.0F))
        {
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->m_aAnims[eRideAnim::RIDE_LOOK_BACK], 4.0F);
        }
        return;
    }

    if (m_fSteerAngle == 0.0F || driveByAnim)
    {
        if (lookLeftAnim)
            lookLeftAnim->m_fBlendDelta = -4.0F;
        if (lookRightAnim)
            lookRightAnim->m_fBlendDelta = -4.0F;
        if (lookBackAnim)
            lookBackAnim->m_fBlendDelta = -4.0F;

        return;
    }

    auto fUsedAngle = fabs(m_fSteerAngle / 0.61F);
    fUsedAngle = clamp(fUsedAngle, 0.0F, 1.0F);

    if (m_fSteerAngle < 0)
    {
        if (lookLeftAnim)
        {
            lookLeftAnim->m_fBlendAmount = 0.0F;
            lookLeftAnim->m_fBlendDelta = 0.0F;
        }
        if (lookRightAnim)
        {
            lookRightAnim->m_fBlendAmount = fUsedAngle;
            lookRightAnim->m_fBlendDelta = 0.0F;
        }
        else
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->m_aAnims[eRideAnim::RIDE_LOOK_RIGHT], 4.0F);
    }
    else
    {
        if (lookLeftAnim)
        {
            lookLeftAnim->m_fBlendAmount = fUsedAngle;
            lookLeftAnim->m_fBlendDelta = 0.0F;
        }
        if (lookRightAnim)
        {
            lookRightAnim->m_fBlendAmount = 0.0F;
            lookRightAnim->m_fBlendDelta = 0.0F;
        }
        else
            CAnimManager::BlendAnimation(driver->m_pRwClump, ANIM_GROUP_DEFAULT, usedAnims->m_aAnims[eRideAnim::RIDE_LOOK_LEFT], 4.0F);
    }

    if (lookBackAnim)
        lookBackAnim->m_fBlendDelta = -4.0F;
}

// 0x871F54
float CVehicle::GetHeightAboveRoad()
{
    return CVehicle::GetHeightAboveRoad_Reversed();
}
float CVehicle::GetHeightAboveRoad_Reversed()
{
    return CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMin.z * -1.0F;
}

// 0x6D1F30
bool CVehicle::CanPedStepOutCar(bool bIgnoreSpeedUpright)
{
    return CVehicle::CanPedStepOutCar_Reversed(bIgnoreSpeedUpright);
}
bool CVehicle::CanPedStepOutCar_Reversed(bool bIgnoreSpeedUpright)
{
    auto const fUpZ = m_matrix->GetUp().z;
    if (fabs(fUpZ) <= 0.1F)
    {
        if (fabs(m_vecMoveSpeed.z) > 0.05F
            || m_vecMoveSpeed.Magnitude2D() > 0.01F
            || m_vecTurnSpeed.SquaredMagnitude() > 0.0004F) { // 0.02F * 0.02F

            return false;
        }

        return true;
    }

    if (IsBoat())
        return true;

    if (bIgnoreSpeedUpright)
        return m_vecTurnSpeed.SquaredMagnitude() > 0.0004F;

    return m_vecMoveSpeed.Magnitude2D() <= 0.01F && fabs(m_vecMoveSpeed.z) <= 0.05F && m_vecTurnSpeed.SquaredMagnitude() <= 0.0004F;

}

// 0x6D2030
bool CVehicle::CanPedJumpOutCar(CPed* ped)
{
    return CVehicle::CanPedJumpOutCar_Reversed(ped);
}
bool CVehicle::CanPedJumpOutCar_Reversed(CPed* ped)
{
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

    m_vecTurnSpeed *= 0.9F; //BUG(PRONE): We are modifying vehicle move and turn speeds in function that seems that it should be const
    auto const fMoveSpeedSquared = m_vecMoveSpeed.SquaredMagnitude();
    if (fMoveSpeedSquared / 100.0F > pow(CTimer::GetTimeStep(), 2.0F) * pow(0.008F, 2.0F))
    {
        m_vecMoveSpeed *= 0.9F;
        return false;
    }

    auto fMoveMult = CTimer::GetTimeStep() / sqrt(fMoveSpeedSquared) * 0.016F;
    fMoveMult = std::max(0.0F, 1.0F - fMoveMult);
    m_vecMoveSpeed *= fMoveMult;
    return false;
}

// 0x871F6C
bool CVehicle::GetTowHitchPos(CVector& outPos, bool bCheckModelInfo, CVehicle* veh)
{
    return CVehicle::GetTowHitchPos_Reversed(outPos, bCheckModelInfo, veh);
}
bool CVehicle::GetTowHitchPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* veh)
{
    if (!bCheckModelInfo)
        return false;

    auto const fColFront = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMax.y;
    outPos.Set(0.0F, fColFront + 1.0F, 0.0F);
    outPos = *m_matrix * outPos;
    return true;
}

// 0x871F70
bool CVehicle::GetTowBarPos(CVector& outPos, bool bCheckModelInfo, CVehicle* veh)
{
    return CVehicle::GetTowBarPos_Reversed(outPos, bCheckModelInfo, veh);
}
bool CVehicle::GetTowBarPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* veh)
{
    if (!bCheckModelInfo)
        return false;

    auto const fColRear = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMin.y;
    outPos.Set(0.0F, fColRear - 1.0F, 0.0F);
    outPos = *m_matrix * outPos;
    return true;
}

// 0x871F80
bool CVehicle::Save()
{
    return CVehicle::Save_Reversed();
}
bool CVehicle::Save_Reversed()
{
    uint32 iStructSize = sizeof(CVehicleSaveStructure);
    auto iSaveStruct = CVehicleSaveStructure();
    iSaveStruct.Construct(this);
    CGenericGameStorage::SaveDataToWorkBuffer(&iStructSize, sizeof(uint32)); // Unused, game ignores it on load and uses const value
    CGenericGameStorage::SaveDataToWorkBuffer(&iSaveStruct, iStructSize);
    return true;
}

// 0x871F84
bool CVehicle::Load()
{
    return CVehicle::Load_Reversed();
}
bool CVehicle::Load_Reversed()
{
    uint32 iStructSize;
    auto iSaveStruct = CVehicleSaveStructure();
    CGenericGameStorage::LoadDataFromWorkBuffer(&iStructSize, sizeof(uint32));
    CGenericGameStorage::LoadDataFromWorkBuffer(&iSaveStruct, sizeof(CVehicleSaveStructure)); //BUG: Should use the value readen line above this, not constant
    iSaveStruct.Extract(this);
    return true;
}

// 0x6D0B40
void CVehicle::Shutdown()
{
    for (auto& specialColModel : m_aSpecialColModel)
        if (specialColModel.m_pColData)
            specialColModel.RemoveCollisionVolumes();
}

// 0x6D0B70
int32 CVehicle::GetRemapIndex()
{
    auto* modelInfo = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    if (modelInfo->GetNumRemaps() <= 0)
        return -1;

    for (auto i = 0; i < modelInfo->GetNumRemaps(); ++i)
        if (modelInfo->m_anRemapTxds[i] == m_nPreviousRemapTxd)
            return i;

    return -1;
}

// unused, arg0 should be const char*
// 0x6D0BC0
void CVehicle::SetRemapTexDictionary(int32 txdId)
{
    if (txdId == m_nPreviousRemapTxd)
        return;

    if (txdId == -1)
    {
        m_pRemapTexture = nullptr;
        CTxdStore::RemoveRef(m_nPreviousRemapTxd);
        m_nPreviousRemapTxd = -1;
    }

    m_nRemapTxd = txdId;
}

// 0x6D0C00
void CVehicle::SetRemap(int32 remapIndex)
{
    if (remapIndex == -1)
    {
        if (m_nPreviousRemapTxd == -1)
            return;

        m_pRemapTexture = nullptr;
        CTxdStore::RemoveRef(m_nPreviousRemapTxd);
        m_nPreviousRemapTxd = -1;
        m_nRemapTxd = -1;
    }
    else
    {
        auto const infoRemapInd = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr()->m_anRemapTxds[remapIndex];
        if (infoRemapInd == m_nPreviousRemapTxd)
            return;

        if (infoRemapInd == -1)
        {
            m_pRemapTexture = nullptr;
            CTxdStore::RemoveRef(m_nPreviousRemapTxd);
            m_nPreviousRemapTxd = -1;
        }

        m_nRemapTxd = infoRemapInd;
    }
}

// 0x6D0CA0
void CVehicle::SetCollisionLighting(tColLighting lighting)
{
    for (auto& colLighting : m_anCollisionLighting)
        colLighting = lighting;
}

// 0x6D0CC0
void CVehicle::UpdateLightingFromStoredPolys()
{
    m_anCollisionLighting[0] = m_FrontCollPoly.m_nLighting;
    m_anCollisionLighting[1] = m_FrontCollPoly.m_nLighting;
    m_anCollisionLighting[2] = m_RearCollPoly.m_nLighting;
    m_anCollisionLighting[2] = m_RearCollPoly.m_nLighting;
}

// 0x6D0CF0
void CVehicle::CalculateLightingFromCollision()
{
    float fAvgLight = 0.0F;
    for (auto& colLighting : m_anCollisionLighting)
        fAvgLight += colLighting.GetCurrentLighting();

    fAvgLight /= 4.0F;
    m_fContactSurfaceBrightness = fAvgLight;

}

// 0x6D0E20
void CVehicle::ResetAfterRender()
{
    ((void(__thiscall*)(CVehicle*))0x6D0E20)(this);
}

// 0x6D1080
eVehicleAppearance CVehicle::GetVehicleAppearance() {
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

// 0x6D10E0
bool CVehicle::CustomCarPlate_TextureCreate(CVehicleModelInfo* model)
{
    return plugin::CallMethodAndReturn<bool, 0x6D10E0, CVehicle*, CVehicleModelInfo*>(this, model);
}

// 0x6D1150
void CVehicle::CustomCarPlate_TextureDestroy()
{
    ((void(__thiscall*)(CVehicle*))0x6D1150)(this);
}

// 0x6D1180
bool CVehicle::CanBeDeleted()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1180)(this);
}

// 0x6D1230
float CVehicle::ProcessWheelRotation(tWheelState wheelState, const CVector& arg1, const CVector& arg2, float arg3)
{
    return ((float(__thiscall*)(CVehicle*, tWheelState, const CVector&, const CVector&, float))0x6D1230)(this, wheelState, arg1, arg2, arg3);
}

// 0x6D1280
bool CVehicle::CanVehicleBeDamaged(CEntity* damager, eWeaponType weapon, uint8* arg2)
{
    return ((bool(__thiscall*)(CVehicle*, CEntity*, eWeaponType, uint8*))0x6D1280)(this, damager, weapon, arg2);
}

// 0x6D1340
void CVehicle::ProcessDelayedExplosion()
{
    ((void(__thiscall*)(CVehicle*))0x6D1340)(this);
}

// 0x6D13A0
bool CVehicle::AddPassenger(CPed* passenger)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D13A0)(this, passenger);
}

// 0x6D14D0
bool CVehicle::AddPassenger(CPed* passenger, uint8 seatNumber)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*, uint8))0x6D14D0)(this, passenger, seatNumber);
}

// 0x6D1610
void CVehicle::RemovePassenger(CPed* passenger)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D1610)(this, passenger);
}

// 0x6D16A0
void CVehicle::SetDriver(CPed* driver)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D16A0)(this, driver);
}

// 0x6D1950
void CVehicle::RemoveDriver(bool arg0)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6D1950)(this, arg0);
}

// 0x6D1A50
CPed* CVehicle::SetUpDriver(int32 pedType, bool arg1, bool arg2)
{
    return ((CPed * (__thiscall*)(CVehicle*, int32, bool, bool))0x6D1A50)(this, pedType, arg1, arg2);
}

// 0x6D1AA0
CPed* CVehicle::SetupPassenger(int32 seatNumber, int32 pedType, bool arg2, bool arg3)
{
    return ((CPed * (__thiscall*)(CVehicle*, int32, int32, bool, bool))0x6D1AA0)(this, seatNumber, pedType, arg2, arg3);
}

// 0x6D1BD0
bool CVehicle::IsPassenger(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1BD0)(this, ped);
}

// 0x6D1C00
bool CVehicle::IsPassenger(int32 modelIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int32))0x6D1C00)(this, modelIndex);
}

bool CVehicle::IsDriver(CPed* ped)
{
    return ped ? ped == m_pDriver : false;
}

bool CVehicle::IsDriver(int32 modelIndex)
{
    return m_pDriver && m_pDriver->m_nModelIndex == modelIndex;
}

// 0x6D1C80
void CVehicle::KillPedsInVehicle()
{
    ((void(__thiscall*)(CVehicle*))0x6D1C80)(this);
}

// 0x6D1D90
bool CVehicle::IsUpsideDown()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1D90)(this);
}

// 0x6D1DD0
bool CVehicle::IsOnItsSide()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1DD0)(this);
}

// 0x6D1E20
bool CVehicle::CanPedOpenLocks(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1E20)(this, ped);
}

// 0x6D1E60
bool CVehicle::CanDoorsBeDamaged()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1E60)(this);
}

// 0x6D1E80
bool CVehicle::CanPedEnterCar()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1E80)(this);
}

// 0x6D21F0
void CVehicle::ProcessCarAlarm()
{
    ((void(__thiscall*)(CVehicle*))0x6D21F0)(this);
}

// 0x6D2250
void DestroyVehicleAndDriverAndPassengers(CVehicle* vehicle)
{
    ((void(__cdecl*)(CVehicle*))0x6D2250)(vehicle);
}

// 0x6D22F0
bool CVehicle::IsVehicleNormal()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D22F0)(this);
}

void CVehicle::ChangeLawEnforcerState(bool bIsEnforcer)
{
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
bool CVehicle::IsLawEnforcementVehicle()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D2370)(this);
}

// unused
// 0x6D2450
bool CVehicle::ShufflePassengersToMakeSpace()
{
    return true;
}

// 0x6D2460
void CVehicle::ExtinguishCarFire()
{
    ((void(__thiscall*)(CVehicle*))0x6D2460)(this);
}

// 0x6D24F0
void CVehicle::ActivateBomb()
{
    ((void(__thiscall*)(CVehicle*))0x6D24F0)(this);
}

// 0x6D2570
void CVehicle::ActivateBombWhenEntered()
{
    ((void(__thiscall*)(CVehicle*))0x6D2570)(this);
}

// 0x6D25D0
bool CVehicle::CarHasRoof()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D25D0)(this);
}

// 0x6D2600
float CVehicle::HeightAboveCeiling(float arg0, eFlightModel arg1)
{
    return ((float(__thiscall*)(CVehicle*, float, eFlightModel))0x6D2600)(this, arg0, arg1);
}

// 0x6D2690
RwObject* SetVehicleAtomicVisibilityCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D2690)(object, data);
}

// 0x6D26D0
RwFrame* SetVehicleAtomicVisibilityCB(RwFrame* component, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D26D0)(component, data);
}

// 0x6D2700
void CVehicle::SetComponentVisibility(RwFrame* component, uint32 visibilityState)
{
    ((void(__thiscall*)(CVehicle*, RwFrame*, uint32))0x6D2700)(this, component, visibilityState);
}

// 0x6D2740
void CVehicle::ApplyBoatWaterResistance(tBoatHandlingData* boatHandling, float fImmersionDepth)
{
    float fSpeedMult = pow(fImmersionDepth, 2.0F) * m_pHandlingData->m_fSuspensionForceLevel * m_fMass / 1000.0F;
    if (m_nModelIndex == MODEL_SKIMMER)
        fSpeedMult *= 30.0F;

    auto fMoveDotProduct = DotProduct(m_vecMoveSpeed, GetForward());
    fSpeedMult *= (pow(fMoveDotProduct, 2.0F) + 0.05F);
    fSpeedMult += 1.0F;
    fSpeedMult = fabs(fSpeedMult);
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
RpMaterial* SetCompAlphaCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x6D2950)(material, data);
}

// 0x6D2960
void CVehicle::SetComponentAtomicAlpha(RpAtomic* atomic, int32 alpha)
{
    ((void(__cdecl*)(RpAtomic*, int32))0x6D2960)(atomic, alpha);
}

CVehicleModelInfo* CVehicle::GetVehicleModelInfo() {
    return CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
}

CVector CVehicle::GetDummyPosition(eVehicleDummies dummy, bool bWorldSpace) {
    CVector pos = GetVehicleModelInfo()->GetModelDummyPosition(dummy);
    if (bWorldSpace)
        pos = GetMatrix() * pos; // transform to world-space
    return pos;
}

// 0x6D2980
void CVehicle::UpdateClumpAlpha()
{
    ((void(__thiscall*)(CVehicle*))0x6D2980)(this);
}

// 0x6D29E0
void CVehicle::UpdatePassengerList()
{
    ((void(__thiscall*)(CVehicle*))0x6D29E0)(this);
}

// 0x6D2A10
CPed* CVehicle::PickRandomPassenger()
{
    return ((CPed * (__thiscall*)(CVehicle*))0x6D2A10)(this);
}

// 0x6D2A80
void CVehicle::AddDamagedVehicleParticles()
{
    ((void(__thiscall*)(CVehicle*))0x6D2A80)(this);
}

// 0x6D2BF0
void CVehicle::MakeDirty(CColPoint& colPoint)
{
    ((void(__thiscall*)(CVehicle*, CColPoint&))0x6D2BF0)(this, colPoint);
}

// 0x6D2D50
bool CVehicle::AddWheelDirtAndWater(CColPoint& colPoint, uint32 arg1, uint8 arg2, uint8 arg3)
{
    return ((bool(__thiscall*)(CVehicle*, CColPoint&, uint32, uint8, uint8))0x6D2D50)(this, colPoint, arg1, arg2, arg3);
}

// 0x6D3000
void CVehicle::SetGettingInFlags(uint8 doorId)
{
    ((void(__thiscall*)(CVehicle*, uint8))0x6D3000)(this, doorId);
}

// 0x6D3020
void CVehicle::SetGettingOutFlags(uint8 doorId)
{
    ((void(__thiscall*)(CVehicle*, uint8))0x6D3020)(this, doorId);
}

// 0x6D3040
void CVehicle::ClearGettingInFlags(uint8 doorId)
{
    ((void(__thiscall*)(CVehicle*, uint8))0x6D3040)(this, doorId);
}

// 0x6D3060
void CVehicle::ClearGettingOutFlags(uint8 doorId)
{
    ((void(__thiscall*)(CVehicle*, uint8))0x6D3060)(this, doorId);
}

// 0x6D3080
void CVehicle::SetWindowOpenFlag(uint8 doorId)
{
    ((void(__thiscall*)(CVehicle*, uint8))0x6D3080)(this, doorId);
}

// 0x6D30B0
void CVehicle::ClearWindowOpenFlag(uint8 doorId)
{
    ((void(__thiscall*)(CVehicle*, uint8))0x6D30B0)(this, doorId);
}

// 0x6D30E0
bool CVehicle::SetVehicleUpgradeFlags(int32 upgradeModelIndex, int32 componentIndex, int32& resultModelIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int32, int32, int32&))0x6D30E0)(this, upgradeModelIndex, componentIndex, resultModelIndex);
}

// 0x6D3210
bool CVehicle::ClearVehicleUpgradeFlags(int32 arg0, int32 componentIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int32, int32))0x6D3210)(this, arg0, componentIndex);
}

// 0x6D3300
RpAtomic* RemoveUpgradeCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3300)(atomic, data);
}

// 0x6D3370
RpAtomic* FindUpgradeCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3370)(atomic, data);
}

// 0x6D33B0
RwObject* RemoveObjectsCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D33B0)(object, data);
}

// 0x6D3420
RwFrame* RemoveObjectsCB(RwFrame* component, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D3420)(component, data);
}

// 0x6D3450
RwObject* CopyObjectsCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3450)(object, data);
}

// 0x6D3490
RwObject* FindReplacementUpgradeCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3490)(object, data);
}

// 0x6D34D0
RpAtomic* RemoveAllUpgradesCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D34D0)(atomic, data);
}

// 0x6D3510
RpAtomic* CVehicle::CreateUpgradeAtomic(CBaseModelInfo* model, const UpgradePosnDesc* upgradePosn, RwFrame* parentComponent, bool isDamaged)
{
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, const UpgradePosnDesc*, RwFrame*, bool))0x6D3510)(this, model, upgradePosn, parentComponent, isDamaged);
}

// 0x6D3630
void CVehicle::RemoveUpgrade(int32 upgradeId)
{
    ((void(__thiscall*)(CVehicle*, int32))0x6D3630)(this, upgradeId);
}

// 0x6D3650
int32 CVehicle::GetUpgrade(int32 upgradeId)
{
    return ((int32(__thiscall*)(CVehicle*, int32))0x6D3650)(this, upgradeId);
}

// 0x6D3700
RpAtomic* CVehicle::CreateReplacementAtomic(CBaseModelInfo* model, RwFrame* component, int32 arg2, bool bDamaged, bool bIsWheel)
{
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, RwFrame*, int32, bool, bool))0x6D3700)(this, model, component, arg2, bDamaged, bIsWheel);
}

// 0x6D3830
void CVehicle::AddReplacementUpgrade(int32 modelIndex, int32 nodeId)
{
    ((void(__thiscall*)(CVehicle*, int32, int32))0x6D3830)(this, modelIndex, nodeId);
}

// 0x6D39E0
void CVehicle::RemoveReplacementUpgrade(int32 nodeId)
{
    ((void(__thiscall*)(CVehicle*, int32))0x6D39E0)(this, nodeId);
}

// 0x6D3A50
void CVehicle::GetReplacementUpgrade(int32 nodeId)
{
    ((void(__thiscall*)(CVehicle*, int32))0x6D3A50)(this, nodeId);
}

// 0x6D3AB0
void CVehicle::RemoveAllUpgrades()
{
    ((void(__thiscall*)(CVehicle*))0x6D3AB0)(this);
}

// 0x6D3AE0
int32 CVehicle::GetSpareHasslePosId()
{
    return ((int32(__thiscall*)(CVehicle*))0x6D3AE0)(this);
}

// 0x6D3B30
void CVehicle::SetHasslePosId(int32 hasslePos, bool enable)
{
    ((void(__thiscall*)(CVehicle*, int32, bool))0x6D3B30)(this, hasslePos, enable);
}

// 0x6D3B60
void CVehicle::InitWinch(int32 arg0)
{
    ((void(__thiscall*)(CVehicle*, int32))0x6D3B60)(this, arg0);
}

// 0x6D3B80
void CVehicle::UpdateWinch()
{
    ((void(__thiscall*)(CVehicle*))0x6D3B80)(this);
}

// 0x6D3C70
void CVehicle::RemoveWinch()
{
    return plugin::CallMethod<0x6D3C70, CVehicle*>(this);

    const auto ropeIndex = GetRopeIndex();
    if (ropeIndex >= 0)
        CRopes::GetRope(ropeIndex).Remove();

    // todo: m_nBombLightsWinchFlags &= 0x9Fu;
}

// NOTSA
int32 CVehicle::GetRopeIndex() {
    return CRopes::FindRope(m_nFlags + 1); // yep, flags + 1
}

// 0x6D3CB0
void CVehicle::ReleasePickedUpEntityWithWinch()
{
    return CRopes::GetRope(GetRopeIndex()).ReleasePickedUpObject();
}

// 0x6D3CD0
void CVehicle::PickUpEntityWithWinch(CEntity* entity)
{
    return CRopes::GetRope(GetRopeIndex()).PickUpObject(entity);
}

// 0x6D3CF0
CEntity* CVehicle::QueryPickedUpEntityWithWinch()
{
    return CRopes::GetRope(GetRopeIndex()).m_pRopeAttachObject;
}

// 0x6D3D10
float CVehicle::GetRopeHeightForHeli()
{
    return CRopes::GetRope(GetRopeIndex()).m_fSegmentLength;
}

// 0x6D3D30
void CVehicle::SetRopeHeightForHeli(float height)
{
    CRopes::GetRope(GetRopeIndex()).m_fSegmentLength = height;
}

// 0x6D3D60
void CVehicle::RenderDriverAndPassengers()
{
    ((void(__thiscall*)(CVehicle*))0x6D3D60)(this);
}

// 0x6D3DB0
void CVehicle::PreRenderDriverAndPassengers()
{
    ((void(__thiscall*)(CVehicle*))0x6D3DB0)(this);
}

// 0x6D3E00
float CVehicle::GetPlaneGunsAutoAimAngle()
{
    return ((float(__thiscall*)(CVehicle*))0x6D3E00)(this);
}

// 0x6D3F30
int32 CVehicle::GetPlaneNumGuns()
{
    return ((int32(__thiscall*)(CVehicle*))0x6D3F30)(this);
}

// 0x6D4010
void CVehicle::SetFiringRateMultiplier(float multiplier)
{
    ((void(__thiscall*)(CVehicle*, float))0x6D4010)(this, multiplier);
}

// 0x6D4090
float CVehicle::GetFiringRateMultiplier()
{
    return ((float(__thiscall*)(CVehicle*))0x6D4090)(this);
}

// 0x6D40E0
uint32 CVehicle::GetPlaneGunsRateOfFire()
{
    return ((uint32(__thiscall*)(CVehicle*))0x6D40E0)(this);
}

// 0x6D4290
CVector CVehicle::GetPlaneGunsPosition(int32 gunId)
{
    CVector result;
    ((void(__thiscall*)(CVehicle*, CVector*, int32))0x6D4290)(this, &result, gunId);
    return result;
}

// 0x6D4590
uint32 CVehicle::GetPlaneOrdnanceRateOfFire(eOrdnanceType ordnanceType)
{
    return ((uint32(__thiscall*)(CVehicle*, eOrdnanceType))0x6D4590)(this, ordnanceType);
}

// 0x6D46E0
CVector CVehicle::GetPlaneOrdnancePosition(eOrdnanceType ordnanceType)
{
    CVector result;
    ((void(__thiscall*)(CVehicle*, CVector*, eOrdnanceType))0x6D46E0)(this, &result, ordnanceType);
    return result;
}

// 0x6D4900
void CVehicle::SelectPlaneWeapon(bool bChange, eOrdnanceType ordnanceType)
{
    ((void(__thiscall*)(CVehicle*, bool, eOrdnanceType))0x6D4900)(this, bChange, ordnanceType);
}

// 0x6D4AD0
void CVehicle::DoPlaneGunFireFX(CWeapon* weapon, CVector& particlePos, CVector& gunshellPos, int32 particleIndex)
{
    ((void(__thiscall*)(CVehicle*, CWeapon*, CVector&, CVector&, int32))0x6D4AD0)(this, weapon, particlePos, gunshellPos, particleIndex);
}

// 0x6D4D30
void CVehicle::FirePlaneGuns()
{
    ((void(__thiscall*)(CVehicle*))0x6D4D30)(this);
}

// 0x6D5110
void CVehicle::FireUnguidedMissile(eOrdnanceType ordnanceType, bool bCheckTime)
{
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6D5110)(this, ordnanceType, bCheckTime);
}

// 0x6D5400
bool CVehicle::CanBeDriven()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D5400)(this);
}

// 0x6D5490
void CVehicle::ReactToVehicleDamage(CPed* ped)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D5490)(this, ped);
}

// 0x6D55C0
bool CVehicle::GetVehicleLightsStatus()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D55C0)(this);
}

// 0x6D5CF0
bool CVehicle::CanPedLeanOut(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D5CF0)(this, ped);
}

// 0x6D5D70
void CVehicle::SetVehicleCreatedBy(int32 createdBy)
{
    ((void(__thiscall*)(CVehicle*, int32))0x6D5D70)(this, createdBy);
}

// 0x6D64F0
void CVehicle::SetupRender()
{
    ((void(__thiscall*)(CVehicle*))0x6D64F0)(this);
}

// 0x6D6C00
void CVehicle::ProcessWheel(CVector& wheelFwd, CVector& wheelRight, CVector& wheelContactSpeed, CVector& wheelContactPoint,
    int32 wheelsOnGround, float thrust, float brake, float adhesion, int8 wheelId, float* wheelSpeed, tWheelState* wheelState, uint16 wheelStatus)
{
    static bool bBraking = false;
    static bool bDriving = false;
    static bool bAlreadySkidding = false;

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
            if (m_nStatus == STATUS_PLAYER || m_nStatus == STATUS_HELI)
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
        right = clamp<float>(right, -adhesion, adhesion);
    }
    else if (contactSpeedFwd != 0.0f) {
        fwd = -contactSpeedFwd / wheelsOnGround;
        if (!bBraking && fabs(m_fGasPedal) < 0.01f) {
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
            if (fabs(contactSpeedFwd) > 0.005f)
                *wheelState = WHEEL_STATE_FIXED;
        }
        else {
            fwd = clamp<float>(fwd, -brake, brake);
        }
    }

    float speedSq = right * right + fwd * fwd;
    if (speedSq > adhesion * adhesion) {
        if (*wheelState != WHEEL_STATE_FIXED) {
            float tractionLimit = WS_TRAC_FRAC_LIMIT;
            if (contactSpeedFwd > 0.15f && (!wheelId || wheelId == CARWHEEL_FRONT_RIGHT))
                tractionLimit += tractionLimit;
            if (bDriving && tractionLimit * adhesion < fabs(fwd))
                *wheelState = WHEEL_STATE_SPINNING;
            else
                *wheelState = WHEEL_STATE_SKIDDING;
        }
        float tractionLoss = m_pHandlingData->m_fTractionLoss;
        if (bAlreadySkidding) {
            tractionLoss = 1.0f;
        }
        else if (*wheelState == WHEEL_STATE_SPINNING) {
            if (m_nStatus == STATUS_PLAYER || m_nStatus == STATUS_HELI)
                tractionLoss = tractionLoss * (1.0f - fabs(m_fGasPedal) * WS_ALREADY_SPINNING_LOSS);
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
void CVehicle::ProcessBikeWheel(CVector& arg0, CVector& arg1, CVector& arg2, CVector& arg3, int32 arg4, float arg5, float arg6, float arg7, float arg8, char arg9, float* arg10, tWheelState* arg11, eBikeWheelSpecial arg12, uint16 arg13)
{
    ((void(__thiscall*)(CVehicle*, CVector&, CVector&, CVector&, CVector&, int32, float, float, float, float, char, float*, tWheelState*, eBikeWheelSpecial, uint16))0x6D73B0)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
}

// 0x6D7BC0
int32 CVehicle::FindTyreNearestPoint(float x, float y)
{
    return ((int32(__thiscall*)(CVehicle*, float, float))0x6D7BC0)(this, x, y);
}

// 0x6D7C90
void CVehicle::InflictDamage(CEntity* damager, eWeaponType weapon, float intensity, CVector coords)
{
    ((void(__thiscall*)(CVehicle*, CEntity*, eWeaponType, float, CVector))0x6D7C90)(this, damager, weapon, intensity, coords);
}

// 0x6D82F0
void CVehicle::KillPedsGettingInVehicle()
{
    ((void(__thiscall*)(CVehicle*))0x6D82F0)(this);
}

// 0x6D8470
bool CVehicle::UsesSiren()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D8470)(this);
}

// 0x6D84D0
bool CVehicle::IsSphereTouchingVehicle(float x, float y, float z, float radius)
{
    return ((bool(__thiscall*)(CVehicle*, float, float, float, float))0x6D84D0)(this, x, y, z, radius);
}

// 0x6D85F0
void CVehicle::FlyingControl(eFlightModel flightModel, float leftRightSkid, float steeringUpDown, float steeringLeftRight, float accelerationBreakStatus)
{
    ((void(__thiscall*)(CVehicle*, eFlightModel, float, float, float, float))0x6D85F0)(this, flightModel, leftRightSkid, steeringUpDown, steeringLeftRight, accelerationBreakStatus);
}

// 0x6DAF00
void CVehicle::BladeColSectorList(CPtrList& ptrList, CColModel& colModel, CMatrix& matrix, int16 arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, CPtrList&, CColModel&, CMatrix&, int16, float))0x6DAF00)(this, ptrList, colModel, matrix, arg3, arg4);
}

// 0x6DBA30
void CVehicle::SetComponentRotation(RwFrame* component, int32 axis, float angle, bool bResetPosition)
{
    plugin::CallMethod<0x6DBA30, CVehicle*, RwFrame*, int32, float, bool>(this, component, axis, angle, bResetPosition);
}

// 0x6DBBB0
void CVehicle::SetTransmissionRotation(RwFrame* component, float arg1, float arg2, CVector posn, bool isFront)
{
    ((void(__thiscall*)(CVehicle*, RwFrame*, float, float, CVector, bool))0x6DBBB0)(this, component, arg1, arg2, posn, isFront);
}

// 0x6DBCE0
void CVehicle::ProcessBoatControl(tBoatHandlingData* boatHandling, float* fLastWaterImmersionDepth, bool bCollidedWithWorld, bool bPostCollision)
{
    CVector vecBuoyancyTurnPoint;
    CVector vecBuoyancyForce;
    if (!mod_Buoyancy.ProcessBuoyancyBoat(this, m_fBuoyancyConstant, &vecBuoyancyTurnPoint, &vecBuoyancyForce, bCollidedWithWorld)) {
        physicalFlags.bSubmergedInWater = false;
        if (IsSubBoat())
            AsBoat()->m_nBoatFlags.bOnWater = false;

        return;
    }

    bool bOnWater = false;
    vehicleFlags.bIsDrowning = false;
    if (CTimer::GetTimeStep() * m_fMass * 0.0008F >= vecBuoyancyForce.z) {
        physicalFlags.bSubmergedInWater = false;
    }
    else {
        physicalFlags.bSubmergedInWater = true;
        bOnWater = true;

        if (GetUp().z < -0.6F
            && fabs(m_vecMoveSpeed.x) < 0.05F
            && fabs(m_vecMoveSpeed.y) < 0.05F) {

            vehicleFlags.bIsDrowning = true;
            if (m_pDriver) {
                m_pDriver->physicalFlags.bTouchingWater = true;
                if (m_pDriver->IsPlayer())
                    m_pDriver->AsPlayer()->HandlePlayerBreath(true, 1.0F);
                else
                {
                    auto pedDamageResponseCalc = CPedDamageResponseCalculator(this, CTimer::GetTimeStep(), eWeaponType::WEAPON_DROWNING, PED_PIECE_TORSO, false);
                    auto damageEvent = CEventDamage(this, CTimer::GetTimeInMS(), eWeaponType::WEAPON_DROWNING, PED_PIECE_TORSO, 0, false, true);
                    if (damageEvent.AffectsPed(m_pDriver))
                        pedDamageResponseCalc.ComputeDamageResponse(m_pDriver, &damageEvent.m_damageResponse, true);
                    else
                        damageEvent.m_damageResponse.m_bDamageCalculated = true;

                    m_pDriver->GetEventGroup().Add(&damageEvent, false);
                }
            }
        }
    }

    auto vecUsedBuoyancyForce = vecBuoyancyForce;
    auto fImmersionDepth = mod_Buoyancy.m_fEntityWaterImmersion;
    if (m_nModelIndex == MODEL_SKIMMER
        && GetUp().z < -0.5F
        && fabs(m_vecMoveSpeed.x) < 0.2F
        && fabs(m_vecMoveSpeed.y) < 0.2F) {

        vecUsedBuoyancyForce *= 0.03F;
    }
    CPhysical::ApplyMoveForce(vecUsedBuoyancyForce);

    if (bCollidedWithWorld)
        CPhysical::ApplyTurnForce(vecBuoyancyForce * 0.4F, vecBuoyancyTurnPoint);

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
            auto vecTurnForceUsed = GetForward();
            vecTurnForceUsed *= fTurnForceMult;
            CPhysical::ApplyTurnForce(vecTurnForceUsed, GetUp());

            auto fMoveForceMult = DotProduct(m_vecMoveSpeed, GetForward()) * -0.5F * m_fMass;
            auto vecMoveForceUsed = GetForward();
            vecMoveForceUsed *= fMoveForceMult;
            CPhysical::ApplyMoveForce(vecMoveForceUsed);

            if (m_f2ndSteerAngle == 0.0F) {
                m_f2ndSteerAngle = CTimer::GetTimeInMS() + 300.0F;
            }
            else if (m_f2ndSteerAngle <= CTimer::GetTimeInMS()) {
                m_f2ndSteerAngle = 0.0F;
            }
        }
    }

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

    if (GetUp().z > -0.6F) {
        float fMoveSpeed = 1.0F;
        if (fabs(m_fGasPedal) <= 0.05F)
            fMoveSpeed = CVector2D(m_vecMoveSpeed).Magnitude();

        if (fabs(m_fGasPedal) > 0.05F || fMoveSpeed > 0.01F) {
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
                fTraction = clamp(fTraction, 0.0F, 1.0F);
            }

            auto fSteerAngleChange = -(fTraction * m_fSteerAngle);
            auto fSteerAngleSin = sin(fSteerAngleChange);
            auto fSteerAngleCos = cos(fSteerAngleChange);

            const auto& vecBoundingMin = CEntity::GetColModel()->m_boundBox.m_vecMin;
            CVector vecThrustPoint(0.0F, vecBoundingMin.y * boatHandling->m_fThrustY, vecBoundingMin.z * boatHandling->m_fThrustZ);
            auto vecTransformedThrustPoint = Multiply3x3(GetMatrix(), vecThrustPoint);

            auto vecWorldThrustPos = GetPosition() + vecTransformedThrustPoint;
            float fWaterLevel;
            CWaterLevel::GetWaterLevel(vecWorldThrustPos.x, vecWorldThrustPos.y, vecWorldThrustPos.z, &fWaterLevel, 1, nullptr);
            if (vecWorldThrustPos.z - 0.5F >= fWaterLevel) {
                if (IsSubBoat())
                    AsBoat()->m_nBoatFlags.bMovingOnWater = false;
            }
            else {
                auto fThrustDepth = fWaterLevel - vecWorldThrustPos.z + 0.5F;
                fThrustDepth = std::min(fThrustDepth * fThrustDepth, 1.0F);

                if (IsSubBoat())
                    AsBoat()->m_nBoatFlags.bMovingOnWater = true;

                bool bIsSlowingDown = false;
                auto fGasState = fabs(m_fGasPedal);
                if (fGasState < 0.01F || m_nModelIndex == MODEL_SKIMMER) {
                    bIsSlowingDown = true;
                }
                else {
                    if (fGasState < 0.5F)
                        bIsSlowingDown = true;

                    auto fSteerAngle = fabs(m_fSteerAngle);
                    CVector vecSteer(-fSteerAngleSin, fSteerAngleCos, -fSteerAngle);
                    CVector vecSteerMoveForce = Multiply3x3(GetMatrix(), vecSteer);
                    vecSteerMoveForce *= fThrustDepth * m_fGasPedal * 40.0F * m_pHandlingData->m_transmissionData.m_fEngineAcceleration * m_fMass;

                    if (vecSteerMoveForce.z > 0.2F)
                        vecSteerMoveForce.z = pow(1.2F - vecSteerMoveForce.z, 2.0F) + 0.2F;

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

                    auto fGasState = fabs(m_fGasPedal);
                    if (fGasState > 0.01F) {
                        fTractionLoss *= (0.55F - fGasState);
                        if (m_nStatus == eEntityStatus::STATUS_PLAYER)
                            fTractionLoss *= 2.6F;
                        else
                            fTractionLoss *= 5.0F;
                    }

                    if (m_fGasPedal < 0.0F && fTractionLoss > 0.0F
                        || m_fGasPedal > 0.0F && fTractionLoss < 0.0F) {

                        fTractionLoss *= -1.0F;
                    }

                    CVector vecTractionLoss(-fSteerAngleSin, 0.0F, 0.0F);
                    vecTractionLoss *= fTractionLoss;
                    CVector vecTractionLossTransformed = Multiply3x3(GetMatrix(), vecTractionLoss);
                    vecTractionLossTransformed *= fThrustDepth * CTimer::GetTimeStep();

                    CPhysical::ApplyMoveForce(vecTractionLossTransformed);
                    CPhysical::ApplyTurnForce(vecTractionLossTransformed, vecTransformedThrustPoint);

                    auto fUsedTimestep = std::max(CTimer::GetTimeStep(), 0.01F);
                    auto vecTurn = GetRight() * fUsedTimestep / fTraction * fTractionLoss * fSteerAngleSin * -0.75F;
                    CPhysical::ApplyTurnForce(vecTurn, GetUp());
                }
            }
        }
    }

    if (m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear != 0.0F) {
        auto vecCross = CVector();
        vecCross.Cross(GetForward(), CVector(0.0F, 0.0F, 1.0F));

        auto fMult = DotProduct(vecCross, m_vecMoveSpeed) * m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear * CTimer::GetTimeStep() * fImmersionDepth * m_fMass * -0.1F;
        float fXTemp = vecCross.x * 0.3F;
        vecCross.x -= vecCross.y * 0.3F;
        vecCross.y += fXTemp;

        auto vecMoveForce = vecCross * fMult;
        CPhysical::ApplyMoveForce(vecMoveForce);
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

    if ((m_nModelIndex != MODEL_SKIMMER || m_f2ndSteerAngle == 0.0F) && !bCollidedWithWorld) {
        auto vecTurnRes = Pow(boatHandling->m_vecTurnRes, CTimer::GetTimeStep());
        m_vecTurnSpeed = Multiply3x3(m_vecTurnSpeed, GetMatrix());
        m_vecTurnSpeed.y *= vecTurnRes.y;
        m_vecTurnSpeed.z *= vecTurnRes.z;

        float fMult = vecTurnRes.x / (pow(m_vecTurnSpeed.x, 2.0F) * 1000.0F + 1.0F) * m_vecTurnSpeed.x - m_vecTurnSpeed.x;
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
void CVehicle::DoBoatSplashes(float fWaterDamping)
{
    plugin::CallMethod<0x6DD130, CVehicle*, float>(this, fWaterDamping);
}

// 0x6DD6F0
void CVehicle::DoSunGlare()
{
    ((void(__thiscall*)(CVehicle*))0x6DD6F0)(this);
}

// 0x6DDF60
void CVehicle::AddWaterSplashParticles()
{
    ((void(__thiscall*)(CVehicle*))0x6DDF60)(this);
}

// 0x6DE240
void CVehicle::AddExhaustParticles()
{
    if (m_bOffscreen)
        return;
    float fSquaredMagnitude = (TheCamera.GetPosition() - GetPosition()).SquaredMagnitude();
    if (fSquaredMagnitude > 256.0f || fSquaredMagnitude > 64.0f
        && !((CTimer::GetFrameCounter() + static_cast<uint8>(m_nModelIndex)) & 1))
    {
        return;
    }
    auto mi = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    CVector firstExhaustPos = mi->m_pVehicleStruct->m_avDummyPos[DUMMY_EXHAUST];
    CVector secondExhaustPos = firstExhaustPos;
    secondExhaustPos.x *= -1.0f;
    CMatrix entityMatrix (*m_matrix);
    bool bHasDoubleExhaust = m_pHandlingData->m_bDoubleExhaust;
    if (IsSubBike()) {
        auto* bike = AsBike();
        bike->CalculateLeanMatrix();
        entityMatrix = bike->m_mLeanMatrix;
        switch (m_nModelIndex)
        {
        case MODEL_FCR900:
            if (m_anExtras[0] == 1 || m_anExtras[0] == 2)
                bHasDoubleExhaust = true;
            break;
        case MODEL_NRG500:
            if (!m_anExtras[0] || m_anExtras[0] == 1)
                secondExhaustPos = mi->m_pVehicleStruct->m_avDummyPos[DUMMY_EXHAUST_SECONDARY];
            break;
        case MODEL_BF400:
            if (m_anExtras[0] == 2)
                bHasDoubleExhaust = true;
            break;
        }
    }
    if (firstExhaustPos != 0.0f) {
        CVector vecParticleVelocity;
        if (DotProduct(GetForward(), m_vecMoveSpeed) >= 0.05f) {
            vecParticleVelocity = m_vecMoveSpeed * 30.0f;
        }
        else  {
            static float randomFactor = CGeneral::GetRandomNumberInRange(-1.8f, -0.9f);
            vecParticleVelocity = randomFactor * GetForward();
        }
        firstExhaustPos = entityMatrix * firstExhaustPos;
        bool bFirstExhaustSubmergedInWater = false;
        bool bSecondExhaustSubmergedInWater = false;
        float pLevel = 0.0f;
        if (physicalFlags.bTouchingWater
            && CWaterLevel::GetWaterLevel(firstExhaustPos.x, firstExhaustPos.y, firstExhaustPos.z, &pLevel, true, nullptr)
            && pLevel >= firstExhaustPos.z)
        {
            bFirstExhaustSubmergedInWater = true;
        }
        if (bHasDoubleExhaust) {
            secondExhaustPos = entityMatrix * secondExhaustPos;
            if (physicalFlags.bTouchingWater
                && CWaterLevel::GetWaterLevel(secondExhaustPos.x, secondExhaustPos.y, secondExhaustPos.z, &pLevel, true, nullptr)
                && pLevel >= secondExhaustPos.z)
            {
                bSecondExhaustSubmergedInWater = true;
            }
        }
        if (CGeneral::GetRandomNumberInRange(1.0f, 3.0f) * (m_fGasPedal + 1.1f) > 2.5f) {
            float fMoveSpeed = m_vecMoveSpeed.Magnitude() * 0.5f;
            float particleAlpha = 0.0f;
            if (0.25f - fMoveSpeed >= 0.0f)
                particleAlpha = 0.25f - fMoveSpeed;
            float fLife = std::max(0.2f - fMoveSpeed, 0.0f);
            FxPrtMult_c fxPrt(0.9f, 0.9f, 1.0f, particleAlpha, 0.2f, 1.0f, fLife);
            int32 numExhausts = 2;
            for (int32 i = 0; i < 2; i++) {
                FxSystem_c* pFirstExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                if (bFirstExhaustSubmergedInWater) {
                    fxPrt.m_color.alpha = particleAlpha * 0.5f;
                    fxPrt.m_fSize = 0.6f;
                    pFirstExhaustFxSystem = g_fx.m_pPrtBubble;
                }
                pFirstExhaustFxSystem->AddParticle(&firstExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                if (bHasDoubleExhaust) {
                    FxSystem_c* pSecondExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                    if (bSecondExhaustSubmergedInWater)
                    {
                        fxPrt.m_color.alpha = particleAlpha * 0.5f;
                        fxPrt.m_fSize = 0.6f;
                        pSecondExhaustFxSystem = g_fx.m_pPrtBubble;
                    }
                    pSecondExhaustFxSystem->AddParticle(&secondExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                }
                if (m_fGasPedal > 0.5f && m_nCurrentGear < 3) {
                    if (rand() % 2) {
                        FxSystem_c* pSecondaryExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                        if (bFirstExhaustSubmergedInWater)
                        {
                            fxPrt.m_color.alpha = particleAlpha * 0.5f;
                            fxPrt.m_fSize = 0.6f;
                            pSecondaryExhaustFxSystem = g_fx.m_pPrtBubble;
                        }
                        pSecondaryExhaustFxSystem->AddParticle(&firstExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                    }
                    else if (bHasDoubleExhaust)
                    {
                        FxSystem_c* pSecondaryExhaustFxSystem = g_fx.m_pPrtSmokeII3expand;
                        if (bSecondExhaustSubmergedInWater)
                        {
                            fxPrt.m_color.alpha = particleAlpha * 0.5f;
                            fxPrt.m_fSize = 0.6f;
                            pSecondaryExhaustFxSystem = g_fx.m_pPrtBubble;
                        }
                        pSecondaryExhaustFxSystem->AddParticle(&secondExhaustPos, &vecParticleVelocity, 0.0f, &fxPrt, -1.0f, m_fContactSurfaceBrightness, 0.6f, 0);
                    }
                }
            }
        }
    }
}

// 0x6DE880
bool CVehicle::AddSingleWheelParticles(tWheelState arg0, uint32 arg1, float arg2, float arg3, CColPoint* arg4, CVector* arg5, float arg6, int32 arg7, uint32 surfaceType, bool* bloodState, uint32 arg10)
{
    return ((bool(__thiscall*)(CVehicle*, tWheelState, uint32, float, float, CColPoint*, CVector*, float, int32, uint32, bool*, uint32))0x6DE880)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, surfaceType, bloodState, arg10);
}

// 0x6DF3D0
bool CVehicle::GetSpecialColModel()
{
    return ((bool(__thiscall*)(CVehicle*))0x6DF3D0)(this);
}

// 0x6DF930
void CVehicle::RemoveVehicleUpgrade(int32 upgradeModelIndex)
{
    ((void(__thiscall*)(CVehicle*, int32))0x6DF930)(this, upgradeModelIndex);
}

// 0x6DFA20
void CVehicle::AddUpgrade(int32 modelIndex, int32 upgradeIndex)
{
    ((void(__thiscall*)(CVehicle*, int32, int32))0x6DFA20)(this, modelIndex, upgradeIndex);
}

// 0x6DFC50
void CVehicle::UpdateTrailerLink(bool arg0, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6DFC50)(this, arg0, arg1);
}

// 0x6E0050
void CVehicle::UpdateTractorLink(bool arg0, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6E0050)(this, arg0, arg1);
}

// 0x6E0400
CEntity* CVehicle::ScanAndMarkTargetForHeatSeekingMissile(CEntity* entity)
{
    return ((CEntity * (__thiscall*)(CVehicle*, CEntity*))0x6E0400)(this, entity);
}

// 0x6E05C0
void CVehicle::FireHeatSeakingMissile(CEntity* targetEntity, eOrdnanceType ordnanceType, bool arg2)
{
    ((void(__thiscall*)(CVehicle*, CEntity*, eOrdnanceType, bool))0x6E05C0)(this, targetEntity, ordnanceType, arg2);
}

// 0x6E07E0
void CVehicle::PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6E07E0)(this, ordnanceType, arg1);
}

// 0x6E0950
void CVehicle::ProcessSirenAndHorn(bool arg0)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6E0950)(this, arg0);
}

// 0x6E0A50
bool CVehicle::DoHeadLightEffect(int32 dummyId, CMatrix& vehicleMatrix, uint8 lightId, uint8 lightState)
{
    return ((bool(__thiscall*)(CVehicle*, int32, CMatrix&, uint8, uint8))0x6E0A50)(this, dummyId, vehicleMatrix, lightId, lightState);
}

// 0x6E0E20
void CVehicle::DoHeadLightBeam(int32 dummyId, CMatrix& matrix, bool arg2)
{
    const auto mi = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    CVector pointModelSpace = mi->m_pVehicleStruct->m_avDummyPos[2 * dummyId];
    if (dummyId == 1 && pointModelSpace.IsZero())
        return;

    CVector point = matrix.GetPosition() + Multiply3x3(matrix, pointModelSpace);
    if (!arg2) {
        point -= 2 * pointModelSpace.x * matrix.GetRight();
    }
    const CVector pointToCamDir = Normalized(TheCamera.GetPosition() - point);
    const auto    alpha = (uint8)((1.0f - fabs(DotProduct(pointToCamDir, matrix.GetForward()))) * 32.0f);

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
void CVehicle::DoHeadLightReflectionSingle(CMatrix& matrix, uint8 lightId)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, uint8))0x6E1440)(this, matrix, lightId);
}

// 0x6E1600
void CVehicle::DoHeadLightReflectionTwin(CMatrix& matrix)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&))0x6E1600)(this, matrix);
}

// 0x6E1720
void CVehicle::DoHeadLightReflection(CMatrix& arg0, uint32 flags, uint8 left, uint8 right)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, uint32, uint8, uint8))0x6E1720)(this, arg0, flags, left, right);
}

// 0x6E1780
bool CVehicle::DoTailLightEffect(int32 lightId, CMatrix& matrix, uint8 arg2, uint8 arg3, uint32 arg4, uint8 arg5)
{
    return ((bool(__thiscall*)(CVehicle*, int32, CMatrix&, uint8, uint8, uint32, uint8))0x6E1780)(this, lightId, matrix, arg2, arg3, arg4, arg5);
}

// 0x6E1A60
void CVehicle::DoVehicleLights(CMatrix& matrix, uint32 flags)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, uint32))0x6E1A60)(this, matrix, flags);
}

// 0x6E2900
void CVehicle::FillVehicleWithPeds(bool bSetClothesToAfro)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6E2900)(this, bSetClothesToAfro);
}

// 0x6E2E50
void CVehicle::DoBladeCollision(CVector arg0, CMatrix& matrix, int16 arg2, float arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, CVector, CMatrix&, int16, float, float))0x6E2E50)(this, arg0, matrix, arg2, arg3, arg4);
}

// 0x6E3290
void CVehicle::AddVehicleUpgrade(int32 modelId)
{
    ((void(__thiscall*)(CVehicle*, int32))0x6E3290)(this, modelId);
}

// 0x6E3400
void CVehicle::SetupUpgradesAfterLoad()
{
    ((void(__thiscall*)(CVehicle*))0x6E3400)(this);
}

// 0x6E38A0
void CVehicle::GetPlaneWeaponFiringStatus(bool& status, eOrdnanceType& ordnanceType)
{
    ((void(__thiscall*)(CVehicle*, bool&, eOrdnanceType&))0x6E3440)(this, status, ordnanceType);
}

// 0x6E38F0
bool IsVehiclePointerValid(CVehicle* vehicle)
{
    return ((bool(__cdecl*)(CVehicle*))0x6E38F0)(vehicle);
}

// 0x6E3950
void CVehicle::ProcessWeapons()
{
    ((void(__thiscall*)(CVehicle*))0x6E3950)(this);
}

void CVehicle::DoFixedMachineGuns()
{
    plugin::CallMethod<0x73F400, CVehicle*>(this);
}

void CVehicle::FireFixedMachineGuns()
{
    plugin::CallMethod<0x73DF00, CVehicle*>(this);
}

void CVehicle::DoDriveByShootings()
{
    plugin::CallMethod<0x741FD0, CVehicle*>(this);
}

// NOTSA
bool CVehicle::AreAnyOfPassengersFollowerOfGroup(const CPedGroup& group) {
    const auto end = m_apPassengers + m_nMaxPassengers;
    return std::find_if(m_apPassengers, end, [&](CPed* passenger) {
        return group.m_groupMembership.IsFollower(passenger);
    }) != end;
}
