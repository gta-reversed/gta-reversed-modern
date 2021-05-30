/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

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
int& CVehicle::m_nLastControlInput = *(int*)0xC1CC04;
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
// VTABLE
    ReversibleHooks::Install("CVehicle", "SetModelIndex", 0x6D6A40, &CVehicle::SetModelIndex_Reversed);
    ReversibleHooks::Install("CVehicle", "DeleteRwObject", 0x6D6410, &CVehicle::DeleteRwObject_Reversed);
    ReversibleHooks::Install("CVehicle", "SpecialEntityPreCollisionStuff", 0x6D6640, &CVehicle::SpecialEntityPreCollisionStuff_Reversed);
    ReversibleHooks::Install("CVehicle", "SpecialEntityCalcCollisionSteps", 0x6D0E90, &CVehicle::SpecialEntityCalcCollisionSteps_Reversed);
    ReversibleHooks::Install("CVehicle", "SetupLighting", 0x553F20, &CVehicle::SetupLighting_Reversed);
    ReversibleHooks::Install("CVehicle", "RemoveLighting", 0x5533D0, &CVehicle::RemoveLighting_Reversed);
    ReversibleHooks::Install("CVehicle", "PreRender", 0x6D6480, &CVehicle::PreRender_Reversed);
    ReversibleHooks::Install("CVehicle", "Render", 0x6D0E60, &CVehicle::Render_Reversed);
    ReversibleHooks::Install("CVehicle", "ProcessOpenDoor", 0x6D56C0, &CVehicle::ProcessOpenDoor_Reversed);
    ReversibleHooks::Install("CVehicle", "ProcessDrivingAnims", 0x6DF4A0, &CVehicle::ProcessDrivingAnims_Reversed);
    ReversibleHooks::Install("CVehicle", "GetHeightAboveRoad", 0x6D63F0, &CVehicle::GetHeightAboveRoad_Reversed);
    ReversibleHooks::Install("CVehicle", "CanPedStepOutCar", 0x6D1F30, &CVehicle::CanPedStepOutCar_Reversed);
    ReversibleHooks::Install("CVehicle", "CanPedJumpOutCar", 0x6D2030, &CVehicle::CanPedJumpOutCar_Reversed);
    ReversibleHooks::Install("CVehicle", "GetTowHitchPos", 0x6DFB70, &CVehicle::GetTowHitchPos_Reversed);
    ReversibleHooks::Install("CVehicle", "GetTowBarPos", 0x6DFBE0, &CVehicle::GetTowBarPos_Reversed);
    ReversibleHooks::Install("CVehicle", "Save", 0x5D4760, &CVehicle::Save_Reversed);
    ReversibleHooks::Install("CVehicle", "Load", 0x5D2900, &CVehicle::Load_Reversed);

// CLASS
    ReversibleHooks::Install("CVehicle", "Shutdown", 0x6D0B40, &CVehicle::Shutdown);
    ReversibleHooks::Install("CVehicle", "GetRemapIndex", 0x6D0B70, &CVehicle::GetRemapIndex);
    ReversibleHooks::Install("CVehicle", "SetRemapTexDictionary", 0x6D0BC0, &CVehicle::SetRemapTexDictionary);
    ReversibleHooks::Install("CVehicle", "SetRemap", 0x6D0C00, &CVehicle::SetRemap);
    ReversibleHooks::Install("CVehicle", "SetCollisionLighting", 0x6D0CA0, &CVehicle::SetCollisionLighting);
    ReversibleHooks::Install("CVehicle", "UpdateLightingFromStoredPolys", 0x6D0CC0, &CVehicle::UpdateLightingFromStoredPolys);
    ReversibleHooks::Install("CVehicle", "CalculateLightingFromCollision", 0x6D0CF0, &CVehicle::CalculateLightingFromCollision);
    ReversibleHooks::Install("CVehicle", "ProcessWheel", 0x6D6C00, &CVehicle::ProcessWheel);
    ReversibleHooks::Install("CVehicle", "IsDriver_Ped", 0x6D1C40, (bool(CVehicle::*)(CPed*))(&CVehicle::IsDriver));
    ReversibleHooks::Install("CVehicle", "IsDriver_Int", 0x6D1C60, (bool(CVehicle::*)(int))(&CVehicle::IsDriver));
    ReversibleHooks::Install("CVehicle", "AddExhaustParticles", 0x6DE240, &CVehicle::AddExhaustParticles);
    ReversibleHooks::Install("CVehicle", "ApplyBoatWaterResistance", 0x6D2740, &CVehicle::ApplyBoatWaterResistance);
    ReversibleHooks::Install("CVehicle", "ProcessBoatControl", 0x6DBCE0, &CVehicle::ProcessBoatControl);
    ReversibleHooks::Install("CVehicle", "ChangeLawEnforcerState", 0x6D2330, &CVehicle::ChangeLawEnforcerState);

}

CVehicle::CVehicle(unsigned char createdBy) : CPhysical(), m_vehicleAudio(), m_autoPilot()
{
    //plugin::CallMethod<0x6D5F10, CVehicle*, unsigned char>(this, createdBy);
    m_bHasPreRenderEffects = true;
    m_nType = eEntityType::ENTITY_TYPE_VEHICLE;

    m_fRawSteerAngle = 0.0;
    m_fSteerAngle = 0.0;
    m_f2ndSteerAngle = 0.0;
    m_nCurrentGear = 1;
    m_fGearChangeCount = 0.0;
    m_fWheelSpinForAudio = 0.0;
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
    m_nDoorLock = 1;
    m_nProjectileWeaponFiringTime = 0;
    m_nAdditionalProjectileWeaponFiringTime = 0;
    m_nTimeForMinigunFiring = 0;
    m_pLastDamageEntity = nullptr;
    m_pEntityWeAreOn = nullptr;
    m_fVehicleRearGroundZ = 0.0;
    m_fVehicleFrontGroundZ = 0.0;
    field_511 = 0;
    field_512 = 0;
    m_comedyControlState = 0;
    m_FrontCollPoly.m_bIsActual = false;
    m_RearCollPoly.m_bIsActual = false;
    m_pHandlingData = nullptr;
    m_nHandlingFlagsIntValue = static_cast<eVehicleHandlingFlags>(0);
    m_autoPilot.m_nCarMission = MISSION_NONE;
    m_autoPilot.m_nTempAction = 0;
    m_autoPilot.m_nTimeToStartMission = CTimer::m_snTimeInMilliseconds;
    m_autoPilot.carCtrlFlags.bAvoidLevelTransitions = false;
    m_nRemapTxd = -1;
    m_nPreviousRemapTxd = -1;
    m_pRemapTexture = nullptr;
    m_pOverheatParticle = nullptr;
    m_pFireParticle = nullptr;
    m_pDustParticle = nullptr;
    m_pCustomCarPlate = nullptr;
   
    memset(m_anUpgrades, 0xFFu, sizeof(m_anUpgrades));
    m_fWheelScale = 1.0;
    m_nWindowsOpenFlags = 0;
    m_nNitroBoosts = 0;
    m_nHasslePosId = 0;
    m_nVehicleWeaponInUse = 0;
    m_fDirtLevel = (rand() % 15);
    m_nCreationTime = CTimer::m_snTimeInMilliseconds;
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

    const auto iRopeInd = CRopes::FindRope(reinterpret_cast<uint32_t>(this) + 1);
    if (iRopeInd >= 0)
        CRopes::GetRope(iRopeInd).Remove();

    if (!physicalFlags.bDestroyed && m_fHealth < 250.0F)
        CDarkel::RegisterCarBlownUpByPlayer(this, 0);
}

void* CVehicle::operator new(unsigned int size) {
    return CPools::ms_pVehiclePool->New();
}

void CVehicle::operator delete(void* data) {
    CPools::ms_pVehiclePool->Delete(static_cast<CVehicle*>(data));
}

void CVehicle::SetModelIndex(unsigned int index)
{
    return CVehicle::SetModelIndex_Reversed(index);
}
void CVehicle::SetModelIndex_Reversed(unsigned int index)
{
    CEntity::SetModelIndex(index);
    auto pVehModelInfo = reinterpret_cast<CVehicleModelInfo*>(CModelInfo::GetModelInfo(index));
    CVehicle::CustomCarPlate_TextureCreate(pVehModelInfo);

    for (size_t i = 0; i <= 1; ++i)
        m_anExtras[i] = CVehicleModelInfo::ms_compsUsed[i];

    m_nMaxPassengers = CVehicleModelInfo::GetMaximumNumberOfPassengersFromNumberOfDoors(index);
    switch (m_nModelIndex)
    {
    case eModelID::MODEL_RCBANDIT:
    case eModelID::MODEL_RCBARON:
    case eModelID::MODEL_RCRAIDER:
    case eModelID::MODEL_RCGOBLIN:
    case eModelID::MODEL_RCTIGER:
        vehicleFlags.bIsRCVehicle = true;
        break;
    default:
        vehicleFlags.bIsRCVehicle = false;
        break;
    }

    //Set up weapons
    switch (m_nModelIndex)
    {
    case eModelID::MODEL_RUSTLER:
    case eModelID::MODEL_STUNT:
        m_nVehicleWeaponInUse = eCarWeapon::CAR_WEAPON_HEAVY_GUN;
        break;
    case eModelID::MODEL_BEAGLE:
        m_nVehicleWeaponInUse = eCarWeapon::CAR_WEAPON_FREEFALL_BOMB;
        break;
    case eModelID::MODEL_HYDRA:
    case eModelID::MODEL_TORNADO:
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

void CVehicle::SpecialEntityPreCollisionStuff(CEntity* colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled,
    bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck)
{
    CVehicle::SpecialEntityPreCollisionStuff_Reversed(colEntity, bIgnoreStuckCheck, bCollisionDisabled, bCollidedEntityCollisionIgnored, bCollidedEntityUnableToMove, bThisOrCollidedEntityStuck);
}
void CVehicle::SpecialEntityPreCollisionStuff_Reversed(CEntity* colEntity, bool bIgnoreStuckCheck, bool* bCollisionDisabled,
    bool* bCollidedEntityCollisionIgnored, bool* bCollidedEntityUnableToMove, bool* bThisOrCollidedEntityStuck)
{
    if (colEntity->IsPed()
        && colEntity->AsPed()->bKnockedOffBike
        && colEntity->AsPed()->m_pVehicle == this)
    {
        *bCollisionDisabled = true;
        return;
    }

    if (physicalFlags.bSubmergedInWater
        && m_nStatus != eEntityStatus::STATUS_PLAYER
        && (m_nStatus != eEntityStatus::STATUS_HELI && colEntity->DoesNotCollideWithFlyers())) //Bug? Seems like it should check for it being heli
    {
        *bCollisionDisabled = true;
        return;
    }

    if (m_pEntityIgnoredCollision == colEntity || colEntity->AsPhysical()->m_pEntityIgnoredCollision == this)
    {
        *bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (m_pAttachedTo == colEntity)
    {
        *bCollidedEntityCollisionIgnored = true;
        return;
    }

    if (colEntity->AsPhysical()->m_pAttachedTo == this)
    {
        *bCollisionDisabled = true;
        physicalFlags.b13 = true;
        return;
    }

    if (physicalFlags.bDisableCollisionForce && colEntity->AsPhysical()->physicalFlags.bDisableCollisionForce)
    {
        *bCollisionDisabled = true;
        return;
    }

    if (m_bIsStuck
        && colEntity->IsVehicle()
        && (colEntity->AsVehicle()->physicalFlags.bDisableCollisionForce && !colEntity->AsVehicle()->physicalFlags.bCollidable))
    {
        *bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (colEntity->AsPhysical()->IsImmovable())
    {
        if (bIgnoreStuckCheck)
            *bCollidedEntityCollisionIgnored = true;
        else if (m_bIsStuck || colEntity->m_bIsStuck)
            *bThisOrCollidedEntityStuck = true;

        return;
    }

    if (colEntity->IsObject())
    {
        if (colEntity->AsObject()->IsFallenLampPost())
        {
            *bCollisionDisabled = true;
            colEntity->AsObject()->m_pEntityIgnoredCollision = this;
        }
        else
        {
            if (colEntity->IsModelTempCollision())
            {
                *bCollisionDisabled = true;
                return;
            }

            if (colEntity->AsObject()->IsTemporary()
                || colEntity->AsObject()->IsExploded()
                || !colEntity->IsStatic())
            {
                if (IsConstructionVehicle())
                {
                    if (m_bIsStuck || colEntity->m_bIsStuck)
                        *bThisOrCollidedEntityStuck = true;
                }
                else if (!colEntity->AsObject()->CanBeSmashed() && !IsBike())
                {
                    auto tempMat = CMatrix();
                    auto* pColModel = colEntity->GetColModel();
                    auto& vecMax = pColModel->GetBoundingBox().m_vecMax;
                    if (vecMax.x < 1.0F && vecMax.y < 1.0F && vecMax.z < 1.0F)
                    {
                        const auto vecSize = pColModel->GetBoundingBox().GetSize();
                        const auto vecTransformed = *colEntity->m_matrix * vecSize;

                        if (GetPosition().z > vecTransformed.z)
                            *bCollidedEntityCollisionIgnored = true;
                        else
                        {
                            Invert(*m_matrix, tempMat);
                            if ((tempMat * vecTransformed).z < 0.0F)
                                *bCollidedEntityCollisionIgnored = true;
                        }
                    }
                }
            }

            if (!*bCollidedEntityCollisionIgnored
                && !*bCollisionDisabled
                && !*bThisOrCollidedEntityStuck
                && colEntity->m_bIsStuck)
            {
                *bCollidedEntityUnableToMove = true;
            }
            return;
        }
    }

    if (colEntity->IsRCCar())
    {
        *bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (IsRCCar() && (colEntity->IsVehicle() || colEntity->IsPed()))
    {
        *bCollidedEntityCollisionIgnored = true;
        physicalFlags.b13 = true;
        return;
    }

    if (colEntity == m_pTractor || colEntity == m_pTrailer)
    {
        *bThisOrCollidedEntityStuck = true;
        physicalFlags.b13 = true;
        return;
    }

    if (colEntity->m_bIsStuck)
    {
        *bCollidedEntityUnableToMove = true;
        return;
    }
}

unsigned char CVehicle::SpecialEntityCalcCollisionSteps(bool* bProcessCollisionBeforeSettingTimeStep, bool* unk2)
{
    return CVehicle::SpecialEntityCalcCollisionSteps_Reversed(bProcessCollisionBeforeSettingTimeStep, unk2);
}
unsigned char CVehicle::SpecialEntityCalcCollisionSteps_Reversed(bool* bProcessCollisionBeforeSettingTimeStep, bool* unk2)
{
    if (physicalFlags.bDisableCollisionForce)
        return 1;

    const auto fMoveSquared = m_vecMoveSpeed.SquaredMagnitude() * pow(CTimer::ms_fTimeStep, 2.0F);
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

    auto& pBnd = CEntity::GetColModel()->GetBoundingBox();
    auto fLongestDir = fabs(DotProduct(m_vecMoveSpeed, GetForward()) * CTimer::ms_fTimeStep / pBnd.GetLength());
    fLongestDir = std::max(fLongestDir, fabs(DotProduct(m_vecMoveSpeed, GetRight()) * CTimer::ms_fTimeStep / pBnd.GetWidth()));
    fLongestDir = std::max(fLongestDir, fabs(DotProduct(m_vecMoveSpeed, GetUp()) * CTimer::ms_fTimeStep / pBnd.GetHeight()));

    if (IsBike())
        fLongestDir *= 1.5F;

    if (fLongestDir < 1.0F)
        *bProcessCollisionBeforeSettingTimeStep = true;
    else if (fLongestDir < 2.0F)
        *unk2 = true;

    return static_cast<uint8_t>(ceil(fMove));
}

void CVehicle::PreRender()
{
    return CVehicle::PreRender_Reversed();
}
void CVehicle::PreRender_Reversed()
{
    if (!IsTrain())
        CVehicle::CalculateLightingFromCollision();

    CVehicle::PreRenderDriverAndPassengers();
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
    auto* pVehInfo = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    const auto iDirtLevel = static_cast<int>(m_fDirtLevel) & 0xF;
    CVehicleModelInfo::SetDirtTextures(pVehInfo, iDirtLevel);

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

// Converted from void CVehicle::ProcessOpenDoor(CPed *ped,uint doorComponentId,uint,uint,float) 0x871EF0
void CVehicle::ProcessOpenDoor(CPed* ped, unsigned int doorComponentId, unsigned int arg2, unsigned int nAnimID, float fTime)
{
    CVehicle::ProcessOpenDoor_Reversed(ped, doorComponentId, arg2, nAnimID, fTime);
}
void CVehicle::ProcessOpenDoor_Reversed(CPed* ped, unsigned int doorComponentId, unsigned int animGroup, unsigned int animId, float fTime)
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

    if (this->IsDoorMissing(iCheckedDoor))
        return;

    float fAnimStart, fAnimEnd;
    switch (animId)
    {
    case ANIM_ID_CAR_OPEN_LHS:
    case ANIM_ID_CAR_OPEN_RHS:
    case ANIM_ID_CAR_OPEN_LHS_1:
    case ANIM_ID_CAR_OPEN_RHS_1:
        {
        CVehicleAnimGroupData::GetInOutTimings(m_pHandlingData->m_nAnimGroup, eInOutTimingMode::OPEN_OUT, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, false);
        else if (fTime > fAnimEnd)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = this->GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                this->OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
        }

    case ANIM_ID_CAR_CLOSE_LHS_0:
    case ANIM_ID_CAR_CLOSE_RHS_0:
    case ANIM_ID_CAR_CLOSE_LHS_1:
    case ANIM_ID_CAR_CLOSE_RHS_1:
    {
        CVehicleAnimGroupData::GetInOutTimings(m_pHandlingData->m_nAnimGroup, eInOutTimingMode::CLOSE_OUT, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimEnd)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = 1.0F - invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = this->GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                this->OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
    }

    case ANIM_ID_CAR_CLOSEDOOR_LHS_0:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_0:
    case ANIM_ID_CAR_CLOSEDOOR_LHS_1:
    case ANIM_ID_CAR_CLOSEDOOR_RHS_1:
        {
        CVehicleAnimGroupData::GetInOutTimings(m_pHandlingData->m_nAnimGroup, eInOutTimingMode::CLOSE_IN, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimEnd)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = 1.0F - invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = this->GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                this->OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
        }

    case ANIM_ID_CAR_GETOUT_LHS_0:
    case ANIM_ID_CAR_GETOUT_RHS_0:
    case ANIM_ID_CAR_GETOUT_LHS_1:
    case ANIM_ID_CAR_GETOUT_RHS_1:
        {
        CVehicleAnimGroupData::GetInOutTimings(m_pHandlingData->m_nAnimGroup, eInOutTimingMode::OPEN_IN, &fAnimStart, &fAnimEnd);
        if (fTime < fAnimStart)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimEnd)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = this->GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                this->OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
        }

    case ANIM_ID_CAR_JACKEDLHS:
    case ANIM_ID_CAR_JACKEDRHS:
        if (fTime < 0.1F)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > 0.4F)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > 0.1F && fTime < 0.4F)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, (fTime - 0.1F) * (10.0F / 3.0F), true);

        return;

    case ANIM_ID_CAR_FALLOUT_LHS:
    case ANIM_ID_CAR_FALLOUT_RHS:
        if (fTime < 0.1F)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > 0.4F)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > 0.1F && fTime < 0.4F)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, (fTime - 0.1F) * (10.0F / 3.0F), true);

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
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
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
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimEnd)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 1.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd)
        {
            const auto fNewRatio = invLerp(fAnimStart, fAnimEnd, fTime);
            const auto fCurRatio = this->GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                this->OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
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
            fAnimStart = 0.05;
            fAnimEnd = 0.3;
            fAnimEnd2 = 0.475F;
            break;
        default:
            assert(false); // Shouldn't ever enter this
            break;
        }

        if (fTime > fAnimEnd2)
            this->OpenDoor(ped, doorComponentId, iCheckedDoor, 0.0F, true);
        else if (fTime > fAnimStart && fTime < fAnimEnd) {
            const auto fNewRatio = invLerp(fAnimStart, 0.2F, fTime);
            const auto fCurRatio = this->GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio < fNewRatio)
                this->OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }
        else if (fTime > fAnimEnd && fTime < fAnimEnd2)
        {
            const auto fNewRatio = 1.0F - invLerp(fAnimEnd, fAnimEnd2, fTime);
            const auto fCurRatio = this->GetDooorAngleOpenRatio(iCheckedDoor);
            if (fCurRatio > fNewRatio)
                this->OpenDoor(ped, doorComponentId, iCheckedDoor, fNewRatio, true);
        }

        return;
    }
    }
}

// Converted from void CVehicle::ProcessDrivingAnims(CPed *driver,uchar) 0x871F38
void CVehicle::ProcessDrivingAnims(CPed* driver, unsigned char bBlend)
{
    CVehicle::ProcessDrivingAnims_Reversed(driver, bBlend);
}
void CVehicle::ProcessDrivingAnims_Reversed(CPed* driver, unsigned char bBlend)
{
    if (m_bOffscreen || !driver->IsPlayer())
        return;

    auto* pRadioTuneAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, eAnimID::ANIM_ID_CAR_TUNE_RADIO);
    if (bBlend)
        pRadioTuneAnim = CAnimManager::BlendAnimation(driver->m_pRwClump, eAnimGroup::ANIM_GROUP_DEFAULT, eAnimID::ANIM_ID_CAR_TUNE_RADIO, 4.0F);

    if (pRadioTuneAnim)
        return;

    CRideAnims* pUsedAnims;
    auto const fSpeed = m_vecMoveSpeed.Magnitude();

    if (vehicleFlags.bLowVehicle)
        pUsedAnims = &aDriveAnimIdsLow;
    else if (IsBoat() && !m_pHandlingData->m_bSitInBoat)
        pUsedAnims = &aDriveAnimIdsBoat;
    else if (CVehicleAnimGroupData::UsesKartDrivingAnims(m_pHandlingData->m_nAnimGroup))
        pUsedAnims = &aDriveAnimIdsKart;
    else if (CVehicleAnimGroupData::UsesTruckDrivingAnims(m_pHandlingData->m_nAnimGroup))
        pUsedAnims = &aDriveAnimIdsTruck;
    else
    {
        const auto fDrivingSkill = CStats::GetStatValue(eStats::STAT_DRIVING_SKILL);
        if (fDrivingSkill < 50.0F)
        {
            if (fSpeed <= 0.4F)
                pUsedAnims = &aDriveAnimIdsBadSlow;
            else
                pUsedAnims = &aDriveAnimIdsBad;
        }
        else if (fDrivingSkill < 100.0F)
        {
            if (fSpeed <= 0.4F)
                pUsedAnims = &aDriveAnimIdsStdSlow;
            else
                pUsedAnims = &aDriveAnimIdsStd;
        }
        else
        {
            if (fSpeed <= 0.4F)
                pUsedAnims = &aDriveAnimIdsProSlow;
            else
                pUsedAnims = &aDriveAnimIdsPro;
        }
    }

    auto* pIdleAnim      = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, pUsedAnims->m_aAnims[eRideAnim::RIDE_IDLE]);
    auto* pLookLeftAnim  = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, pUsedAnims->m_aAnims[eRideAnim::RIDE_LOOK_LEFT]);
    auto* pLookRightAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, pUsedAnims->m_aAnims[eRideAnim::RIDE_LOOK_RIGHT]);
    auto* pLookBackAnim  = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, pUsedAnims->m_aAnims[eRideAnim::RIDE_LOOK_BACK]);

    if (!pIdleAnim)
    {
        if (RpAnimBlendClumpGetAssociation(driver->m_pRwClump, eAnimID::ANIM_ID_CAR_SIT))
        {
            CAnimManager::BlendAnimation(driver->m_pRwClump, eAnimGroup::ANIM_GROUP_DEFAULT, pUsedAnims->m_aAnims[eRideAnim::RIDE_IDLE], 4.0F);
            
        }
        return;
    }

    if (pIdleAnim->m_fBlendAmount < 1.0F)
        return;

    if (pLookBackAnim
        && TheCamera.GetActiveCamera().m_nMode == eCamMode::MODE_1STPERSON
        && TheCamera.GetActiveCamera().m_nDirectionWasLooking == eLookingDirection::LOOKING_DIRECTION_BEHIND)
    {
        pLookBackAnim->m_fBlendDelta = -1000.0F;
    }

    auto* pDriveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBY_L);
    if (!pDriveByAnim)
        pDriveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBY_R);
    if (!pDriveByAnim)
        pDriveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBYL_L);
    if (!pDriveByAnim)
        pDriveByAnim = RpAnimBlendClumpGetAssociation(driver->m_pRwClump, ANIM_ID_DRIVEBYL_R);

    if (!vehicleFlags.bLowVehicle
        && m_fGasPedal < 0.0F
        && !pDriveByAnim
        && GetVehicleAppearance() != VEHICLE_APPEARANCE_HELI
        && GetVehicleAppearance() != VEHICLE_APPEARANCE_PLANE)
    {
        if ((TheCamera.GetActiveCamera().m_nMode != eCamMode::MODE_1STPERSON
            || TheCamera.GetActiveCamera().m_nDirectionWasLooking != eLookingDirection::LOOKING_DIRECTION_BEHIND)
            && (!pLookBackAnim || pLookBackAnim->m_fBlendAmount < 1.0F && pLookBackAnim->m_fBlendDelta <= 0.0F))
        {
            CAnimManager::BlendAnimation(driver->m_pRwClump, eAnimGroup::ANIM_GROUP_DEFAULT, pUsedAnims->m_aAnims[eRideAnim::RIDE_LOOK_BACK], 4.0F);
        }
        return;
    }

    if (m_fSteerAngle == 0.0F || pDriveByAnim)
    {
        if (pLookLeftAnim)
            pLookLeftAnim->m_fBlendDelta = -4.0F;
        if (pLookRightAnim)
            pLookRightAnim->m_fBlendDelta = -4.0F;
        if (pLookBackAnim)
            pLookBackAnim->m_fBlendDelta = -4.0F;

        return;
    }

    auto fUsedAngle = fabs(m_fSteerAngle / 0.61F);
    fUsedAngle = clamp(fUsedAngle, 0.0F, 1.0F);

    if (m_fSteerAngle < 0)
    {
        if (pLookLeftAnim)
        {
            pLookLeftAnim->m_fBlendAmount = 0.0F;
            pLookLeftAnim->m_fBlendDelta = 0.0F;
        }
        if (pLookRightAnim)
        {
            pLookRightAnim->m_fBlendAmount = fUsedAngle;
            pLookRightAnim->m_fBlendDelta = 0.0F;
        }
        else
            CAnimManager::BlendAnimation(driver->m_pRwClump, eAnimGroup::ANIM_GROUP_DEFAULT, pUsedAnims->m_aAnims[eRideAnim::RIDE_LOOK_RIGHT], 4.0F);
    }
    else
    {
        if (pLookLeftAnim)
        {
            pLookLeftAnim->m_fBlendAmount = fUsedAngle;
            pLookLeftAnim->m_fBlendDelta = 0.0F;
        }
        if (pLookRightAnim)
        {
            pLookRightAnim->m_fBlendAmount = 0.0F;
            pLookRightAnim->m_fBlendDelta = 0.0F;
        }
        else
            CAnimManager::BlendAnimation(driver->m_pRwClump, eAnimGroup::ANIM_GROUP_DEFAULT, pUsedAnims->m_aAnims[eRideAnim::RIDE_LOOK_LEFT], 4.0F);
    }

    if (pLookBackAnim)
        pLookBackAnim->m_fBlendDelta = -4.0F;;
}

// Converted from float CVehicle::GetHeightAboveRoad(void) 0x871F54
float CVehicle::GetHeightAboveRoad()
{
    return CVehicle::GetHeightAboveRoad_Reversed();
}
float CVehicle::GetHeightAboveRoad_Reversed()
{
    return CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMin.z * -1.0F;
}

// Converted from bool CVehicle::CanPedStepOutCar(bool) 0x871F64
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

// Converted from bool CVehicle::CanPedJumpOutCar(CPed *ped) 0x871F68
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
    if (!IsPlane()
        && !IsHeli()
        && (!IsAutomobile() || m_matrix->GetUp().z >= 0.3F || m_nLastCollisionTime <= CTimer::m_snTimeInMilliseconds - 1000))
    {
        return fHorSpeedSquared >= 0.1F && fHorSpeedSquared <= 0.5F;
    }

    if (fHorSpeedSquared >= 0.1F)
        return true;

    if (this->CanPedStepOutCar(false))
        return false;

    m_vecTurnSpeed *= 0.9F; //BUG(PRONE): We are modifying vehicle move and turn speeds in function that seems that it should be const
    auto const fMoveSpeedSquared = m_vecMoveSpeed.SquaredMagnitude();
    if (fMoveSpeedSquared / 100.0F > pow(CTimer::ms_fTimeStep, 2.0F) * pow(0.008F, 2.0F))
    {
        m_vecMoveSpeed *= 0.9F;
        return false;
    }

    auto fMoveMult = CTimer::ms_fTimeStep / sqrt(fMoveSpeedSquared) * 0.016F;
    fMoveMult = std::max(0.0F, 1.0F - fMoveMult);
    m_vecMoveSpeed *= fMoveMult;
    return false;
}

// Converted from bool CVehicle::GetTowHitchPos(CVector &posnOut,bool,CVehicle*) 0x871F6C
bool CVehicle::GetTowHitchPos(CVector& posnOut, bool bCheckModelInfo, CVehicle* veh)
{
    return CVehicle::GetTowHitchPos_Reversed(posnOut, bCheckModelInfo, veh);
}
bool CVehicle::GetTowHitchPos_Reversed(CVector& posnOut, bool bCheckModelInfo, CVehicle* veh)
{
    if (!bCheckModelInfo)
        return false;

    auto const fColFront = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMax.y;
    posnOut.Set(0.0F, fColFront + 1.0F, 0.0F);
    posnOut = *m_matrix * posnOut;
    return true;
}

// Converted from bool CVehicle::GetTowBarPos(CVector &posnOut,bool,CVehicle*) 0x871F70
bool CVehicle::GetTowBarPos(CVector& posnOut, bool bCheckModelInfo, CVehicle* veh)
{
    return CVehicle::GetTowBarPos_Reversed(posnOut, bCheckModelInfo, veh);
}
bool CVehicle::GetTowBarPos_Reversed(CVector& posnOut, bool bCheckModelInfo, CVehicle* veh)
{
    if (!bCheckModelInfo)
        return false;

    auto const fColRear = CModelInfo::GetModelInfo(m_nModelIndex)->GetColModel()->GetBoundingBox().m_vecMin.y;
    posnOut.Set(0.0F, fColRear - 1.0F, 0.0F);
    posnOut = *m_matrix * posnOut;
    return true;
}

// Converted from bool CVehicle::Save(void) 0x871F80
bool CVehicle::Save()
{
    return CVehicle::Save_Reversed();
}
bool CVehicle::Save_Reversed()
{
    uint32_t iStructSize = sizeof(CVehicleSaveStructure);
    auto iSaveStruct = CVehicleSaveStructure();
    iSaveStruct.Construct(this);
    CGenericGameStorage::SaveDataToWorkBuffer(&iStructSize, sizeof(uint32_t)); // Unused, game ignores it on load and uses const value
    CGenericGameStorage::SaveDataToWorkBuffer(&iSaveStruct, iStructSize);
    return true;
}

// Converted from bool CVehicle::Load(void) 0x871F84
bool CVehicle::Load()
{
    return CVehicle::Load_Reversed();
}
bool CVehicle::Load_Reversed()
{
    uint32_t iStructSize;
    auto iSaveStruct = CVehicleSaveStructure();
    CGenericGameStorage::LoadDataFromWorkBuffer(&iStructSize, sizeof(uint32_t));
    CGenericGameStorage::LoadDataFromWorkBuffer(&iSaveStruct, sizeof(CVehicleSaveStructure)); //BUG: Should use the value readen line above this, not constant
    iSaveStruct.Extract(this);
    return true;
}

// Converted from stdcall void CVehicle::Shutdown(void) 0x6D0B40
void CVehicle::Shutdown()
{
    for (auto& specialColModel : CVehicle::m_aSpecialColModel)
        if (specialColModel.m_pColData)
            specialColModel.RemoveCollisionVolumes();
}

// Converted from thiscall int CVehicle::GetRemapIndex(void) 0x6D0B70
int CVehicle::GetRemapIndex()
{
    auto* modelInfo = CModelInfo::GetModelInfo(m_nModelIndex)->AsVehicleModelInfoPtr();
    if (modelInfo->GetNumRemaps() <= 0)
        return -1;

    for (auto i = 0; i < modelInfo->GetNumRemaps(); ++i)
        if (modelInfo->m_anRemapTxds[i] == m_nPreviousRemapTxd)
            return i;

    return -1;
}

// Converted from thiscall void CVehicle::SetRemapTexDictionary(int txdId) 0x6D0BC0
void CVehicle::SetRemapTexDictionary(int txdId)
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

// Converted from thiscall void CVehicle::SetRemap(int remapIndex) 0x6D0C00
void CVehicle::SetRemap(int remapIndex)
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

// Converted from thiscall void CVehicle::SetCollisionLighting(uchar lighting) 0x6D0CA0
void CVehicle::SetCollisionLighting(tColLighting lighting)
{
    for (auto& colLighting : m_anCollisionLighting)
        colLighting = lighting;
}

// Converted from thiscall void CVehicle::UpdateLightingFromStoredPolys(void) 0x6D0CC0
void CVehicle::UpdateLightingFromStoredPolys()
{
    m_anCollisionLighting[0] = m_FrontCollPoly.m_nLighting;
    m_anCollisionLighting[1] = m_FrontCollPoly.m_nLighting;
    m_anCollisionLighting[2] = m_RearCollPoly.m_nLighting;
    m_anCollisionLighting[2] = m_RearCollPoly.m_nLighting;
}

// Converted from thiscall void CVehicle::CalculateLightingFromCollision(void) 0x6D0CF0
void CVehicle::CalculateLightingFromCollision()
{
    float fAvgLight = 0.0F;
    for (auto& colLighting : m_anCollisionLighting)
        fAvgLight += colLighting.GetCurrentLighting();

    fAvgLight /= 4.0F;
    m_fContactSurfaceBrightness = fAvgLight;

}

// Converted from thiscall void CVehicle::ResetAfterRender(void) 0x6D0E20
void CVehicle::ResetAfterRender()
{
    ((void(__thiscall*)(CVehicle*))0x6D0E20)(this);
}

// Converted from thiscall int CVehicle::GetVehicleAppearance(void) 0x6D1080
int CVehicle::GetVehicleAppearance()
{
    return ((int(__thiscall*)(CVehicle*))0x6D1080)(this);
}

// Converted from thiscall bool CVehicle::CustomCarPlate_TextureCreate(CVehicleModelInfo *model) 0x6D10E0
bool CVehicle::CustomCarPlate_TextureCreate(CVehicleModelInfo* model)
{
    return plugin::CallMethodAndReturn<bool, 0x6D10E0, CVehicle*, CVehicleModelInfo*>(this, model);
}

// Converted from thiscall void CVehicle::CustomCarPlate_TextureDestroy(void) 0x6D1150
void CVehicle::CustomCarPlate_TextureDestroy()
{
    ((void(__thiscall*)(CVehicle*))0x6D1150)(this);
}

// Converted from thiscall bool CVehicle::CanBeDeleted(void) 0x6D1180
bool CVehicle::CanBeDeleted()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1180)(this);
}

// Converted from thiscall float CVehicle::ProcessWheelRotation(tWheelState wheelState,CVector const&,CVector const&,float) 0x6D1230
float CVehicle::ProcessWheelRotation(tWheelState wheelState, CVector const& arg1, CVector const& arg2, float arg3)
{
    return ((float(__thiscall*)(CVehicle*, tWheelState, CVector const&, CVector const&, float))0x6D1230)(this, wheelState, arg1, arg2, arg3);
}

// Converted from thiscall bool CVehicle::CanVehicleBeDamaged(CEntity *damager,eWeaponType weapon,uchar *) 0x6D1280
bool CVehicle::CanVehicleBeDamaged(CEntity* damager, eWeaponType weapon, unsigned char* arg2)
{
    return ((bool(__thiscall*)(CVehicle*, CEntity*, eWeaponType, unsigned char*))0x6D1280)(this, damager, weapon, arg2);
}

// Converted from thiscall void CVehicle::ProcessDelayedExplosion(void) 0x6D1340
void CVehicle::ProcessDelayedExplosion()
{
    ((void(__thiscall*)(CVehicle*))0x6D1340)(this);
}

// Converted from thiscall bool CVehicle::AddPassenger(CPed *passenger) 0x6D13A0
bool CVehicle::AddPassenger(CPed* passenger)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D13A0)(this, passenger);
}

// Converted from thiscall bool CVehicle::AddPassenger(CPed *passenger,uchar seatNumber) 0x6D14D0
bool CVehicle::AddPassenger(CPed* passenger, unsigned char seatNumber)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*, unsigned char))0x6D14D0)(this, passenger, seatNumber);
}

// Converted from thiscall void CVehicle::RemovePassenger(CPed *passenger) 0x6D1610
void CVehicle::RemovePassenger(CPed* passenger)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D1610)(this, passenger);
}

// Converted from thiscall void CVehicle::SetDriver(CPed *driver) 0x6D16A0
void CVehicle::SetDriver(CPed* driver)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D16A0)(this, driver);
}

// Converted from thiscall void CVehicle::RemoveDriver(bool) 0x6D1950
void CVehicle::RemoveDriver(bool arg0)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6D1950)(this, arg0);
}

// Converted from thiscall CPed* CVehicle::SetUpDriver(int pedType,bool,bool) 0x6D1A50
CPed* CVehicle::SetUpDriver(int pedType, bool arg1, bool arg2)
{
    return ((CPed * (__thiscall*)(CVehicle*, int, bool, bool))0x6D1A50)(this, pedType, arg1, arg2);
}

// Converted from thiscall CPed* CVehicle::SetupPassenger(int seatNumber,int pedType,bool,bool) 0x6D1AA0
CPed* CVehicle::SetupPassenger(int seatNumber, int pedType, bool arg2, bool arg3)
{
    return ((CPed * (__thiscall*)(CVehicle*, int, int, bool, bool))0x6D1AA0)(this, seatNumber, pedType, arg2, arg3);
}

// Converted from thiscall bool CVehicle::IsPassenger(CPed *ped) 0x6D1BD0
bool CVehicle::IsPassenger(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1BD0)(this, ped);
}

// Converted from thiscall bool CVehicle::IsPassenger(int modelIndex) 0x6D1C00
bool CVehicle::IsPassenger(int modelIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int))0x6D1C00)(this, modelIndex);
}

bool CVehicle::IsDriver(CPed* ped)
{
    if (ped)
        return ped == m_pDriver;
    return false;
}

bool CVehicle::IsDriver(int modelIndex)
{
    return m_pDriver && m_pDriver->m_nModelIndex == modelIndex;
}

// Converted from thiscall void CVehicle::KillPedsInVehicle(void) 0x6D1C80
void CVehicle::KillPedsInVehicle()
{
    ((void(__thiscall*)(CVehicle*))0x6D1C80)(this);
}

// Converted from thiscall bool CVehicle::IsUpsideDown(void) 0x6D1D90
bool CVehicle::IsUpsideDown()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1D90)(this);
}

// Converted from thiscall bool CVehicle::IsOnItsSide(void) 0x6D1DD0
bool CVehicle::IsOnItsSide()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1DD0)(this);
}

// Converted from thiscall bool CVehicle::CanPedOpenLocks(CPed *ped) 0x6D1E20
bool CVehicle::CanPedOpenLocks(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D1E20)(this, ped);
}

// Converted from thiscall bool CVehicle::CanDoorsBeDamaged(void) 0x6D1E60
bool CVehicle::CanDoorsBeDamaged()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1E60)(this);
}

// Converted from thiscall bool CVehicle::CanPedEnterCar(void) 0x6D1E80
bool CVehicle::CanPedEnterCar()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D1E80)(this);
}

// Converted from thiscall void CVehicle::ProcessCarAlarm(void) 0x6D21F0
void CVehicle::ProcessCarAlarm()
{
    ((void(__thiscall*)(CVehicle*))0x6D21F0)(this);
}

// Converted from stdcall void DestroyVehicleAndDriverAndPassengers(CVehicle *vehicle) 0x6D2250
void DestroyVehicleAndDriverAndPassengers(CVehicle* vehicle)
{
    ((void(__cdecl*)(CVehicle*))0x6D2250)(vehicle);
}

// Converted from thiscall bool CVehicle::IsVehicleNormal(void) 0x6D22F0
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

// Converted from thiscall bool CVehicle::IsLawEnforcementVehicle(void) 0x6D2370
bool CVehicle::IsLawEnforcementVehicle()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D2370)(this);
}

// Converted from thiscall bool CVehicle::ShufflePassengersToMakeSpace(void) 0x6D2450
bool CVehicle::ShufflePassengersToMakeSpace()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D2450)(this);
}

// Converted from thiscall void CVehicle::ExtinguishCarFire(void) 0x6D2460
void CVehicle::ExtinguishCarFire()
{
    ((void(__thiscall*)(CVehicle*))0x6D2460)(this);
}

// Converted from thiscall void CVehicle::ActivateBomb(void) 0x6D24F0
void CVehicle::ActivateBomb()
{
    ((void(__thiscall*)(CVehicle*))0x6D24F0)(this);
}

// Converted from thiscall void CVehicle::ActivateBombWhenEntered(void) 0x6D2570
void CVehicle::ActivateBombWhenEntered()
{
    ((void(__thiscall*)(CVehicle*))0x6D2570)(this);
}

// Converted from thiscall bool CVehicle::CarHasRoof(void) 0x6D25D0
bool CVehicle::CarHasRoof()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D25D0)(this);
}

// Converted from thiscall float CVehicle::HeightAboveCeiling(float,eFlightModel) 0x6D2600
float CVehicle::HeightAboveCeiling(float arg0, eFlightModel arg1)
{
    return ((float(__thiscall*)(CVehicle*, float, eFlightModel))0x6D2600)(this, arg0, arg1);
}

// Converted from stdcall RwObject* SetVehicleAtomicVisibilityCB(RwObject *object,void *data) 0x6D2690
RwObject* SetVehicleAtomicVisibilityCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D2690)(object, data);
}

// Converted from stdcall RwFrame* SetVehicleAtomicVisibilityCB(RwFrame *component,void *data) 0x6D26D0
RwFrame* SetVehicleAtomicVisibilityCB(RwFrame* component, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D26D0)(component, data);
}

// Converted from thiscall void CVehicle::SetComponentVisibility(RwFrame *component,uint visibilityState) 0x6D2700
void CVehicle::SetComponentVisibility(RwFrame* component, unsigned int visibilityState)
{
    ((void(__thiscall*)(CVehicle*, RwFrame*, unsigned int))0x6D2700)(this, component, visibilityState);
}

// Converted from thiscall void CVehicle::ApplyBoatWaterResistance(tBoatHandlingData *boatHandling,float) 0x6D2740
void CVehicle::ApplyBoatWaterResistance(tBoatHandlingData* boatHandling, float fImmersionDepth)
{
    float fSpeedMult = pow(fImmersionDepth, 2.0F) * m_pHandlingData->m_fSuspensionForceLevel * m_fMass / 1000.0F;
    if (m_nModelIndex == eModelID::MODEL_SKIMMER)
        fSpeedMult *= 30.0F;

    auto fMoveDotProduct = DotProduct(m_vecMoveSpeed, GetForward());
    fSpeedMult *= (pow(fMoveDotProduct, 2.0F) + 0.05F);
    fSpeedMult += 1.0F;
    fSpeedMult = fabs(fSpeedMult);
    fSpeedMult = 1.0F / fSpeedMult;

    float fUsedTimeStep = CTimer::ms_fTimeStep * 0.5F;
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

// Converted from stdcall RpMaterial* SetCompAlphaCB(RpMaterial *material,void *data) 0x6D2950
RpMaterial* SetCompAlphaCB(RpMaterial* material, void* data)
{
    return ((RpMaterial * (__cdecl*)(RpMaterial*, void*))0x6D2950)(material, data);
}

// Converted from thiscall void CVehicle::SetComponentAtomicAlpha(RpAtomic *atomic,int alpha) 0x6D2960
void CVehicle::SetComponentAtomicAlpha(RpAtomic* atomic, int alpha)
{
    ((void(__cdecl*)(RpAtomic*, int))0x6D2960)(atomic, alpha);
}

// Converted from thiscall void CVehicle::UpdateClumpAlpha(void) 0x6D2980
void CVehicle::UpdateClumpAlpha()
{
    ((void(__thiscall*)(CVehicle*))0x6D2980)(this);
}

// Converted from thiscall void CVehicle::UpdatePassengerList(void) 0x6D29E0
void CVehicle::UpdatePassengerList()
{
    ((void(__thiscall*)(CVehicle*))0x6D29E0)(this);
}

// Converted from thiscall CPed* CVehicle::PickRandomPassenger(void) 0x6D2A10
CPed* CVehicle::PickRandomPassenger()
{
    return ((CPed * (__thiscall*)(CVehicle*))0x6D2A10)(this);
}

// Converted from thiscall void CVehicle::AddDamagedVehicleParticles(void) 0x6D2A80
void CVehicle::AddDamagedVehicleParticles()
{
    ((void(__thiscall*)(CVehicle*))0x6D2A80)(this);
}

// Converted from thiscall void CVehicle::MakeDirty(CColPoint &colPoint) 0x6D2BF0
void CVehicle::MakeDirty(CColPoint& colPoint)
{
    ((void(__thiscall*)(CVehicle*, CColPoint&))0x6D2BF0)(this, colPoint);
}

// Converted from thiscall bool CVehicle::AddWheelDirtAndWater(CColPoint &colPoint,uint,uchar,uchar) 0x6D2D50
bool CVehicle::AddWheelDirtAndWater(CColPoint& colPoint, unsigned int arg1, unsigned char arg2, unsigned char arg3)
{
    return ((bool(__thiscall*)(CVehicle*, CColPoint&, unsigned int, unsigned char, unsigned char))0x6D2D50)(this, colPoint, arg1, arg2, arg3);
}

// Converted from thiscall void CVehicle::SetGettingInFlags(uchar doorId) 0x6D3000
void CVehicle::SetGettingInFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3000)(this, doorId);
}

// Converted from thiscall void CVehicle::SetGettingOutFlags(uchar doorId) 0x6D3020
void CVehicle::SetGettingOutFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3020)(this, doorId);
}

// Converted from thiscall void CVehicle::ClearGettingInFlags(uchar doorId) 0x6D3040
void CVehicle::ClearGettingInFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3040)(this, doorId);
}

// Converted from thiscall void CVehicle::ClearGettingOutFlags(uchar doorId) 0x6D3060
void CVehicle::ClearGettingOutFlags(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3060)(this, doorId);
}

// Converted from thiscall void CVehicle::SetWindowOpenFlag(uchar doorId) 0x6D3080
void CVehicle::SetWindowOpenFlag(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D3080)(this, doorId);
}

// Converted from thiscall void CVehicle::ClearWindowOpenFlag(uchar doorId) 0x6D30B0
void CVehicle::ClearWindowOpenFlag(unsigned char doorId)
{
    ((void(__thiscall*)(CVehicle*, unsigned char))0x6D30B0)(this, doorId);
}

// Converted from thiscall bool CVehicle::SetVehicleUpgradeFlags(int upgradeModelIndex,int componentIndex,int &resultModelIndex) 0x6D30E0
bool CVehicle::SetVehicleUpgradeFlags(int upgradeModelIndex, int componentIndex, int& resultModelIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int, int, int&))0x6D30E0)(this, upgradeModelIndex, componentIndex, resultModelIndex);
}

// Converted from thiscall bool CVehicle::ClearVehicleUpgradeFlags(int,int componentIndex) 0x6D3210
bool CVehicle::ClearVehicleUpgradeFlags(int arg0, int componentIndex)
{
    return ((bool(__thiscall*)(CVehicle*, int, int))0x6D3210)(this, arg0, componentIndex);
}

// Converted from stdcall RpAtomic* RemoveUpgradeCB(RpAtomic *atomic,void *data) 0x6D3300
RpAtomic* RemoveUpgradeCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3300)(atomic, data);
}

// Converted from stdcall RpAtomic* FindUpgradeCB(RpAtomic *atomic,void *data) 0x6D3370
RpAtomic* FindUpgradeCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D3370)(atomic, data);
}

// Converted from stdcall RwObject* RemoveObjectsCB(RwObject *object,void *data) 0x6D33B0
RwObject* RemoveObjectsCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D33B0)(object, data);
}

// Converted from stdcall RwFrame* RemoveObjectsCB(RwFrame *component,void *data) 0x6D3420
RwFrame* RemoveObjectsCB(RwFrame* component, void* data)
{
    return ((RwFrame * (__cdecl*)(RwFrame*, void*))0x6D3420)(component, data);
}

// Converted from stdcall RwObject* CopyObjectsCB(RwObject *object,void *data) 0x6D3450
RwObject* CopyObjectsCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3450)(object, data);
}

// Converted from stdcall RwObject* FindReplacementUpgradeCB(RwObject *object,void *data) 0x6D3490
RwObject* FindReplacementUpgradeCB(RwObject* object, void* data)
{
    return ((RwObject * (__cdecl*)(RwObject*, void*))0x6D3490)(object, data);
}

// Converted from stdcall RpAtomic* RemoveAllUpgradesCB(RpAtomic *atomic,void *data) 0x6D34D0
RpAtomic* RemoveAllUpgradesCB(RpAtomic* atomic, void* data)
{
    return ((RpAtomic * (__cdecl*)(RpAtomic*, void*))0x6D34D0)(atomic, data);
}

// Converted from thiscall RpAtomic* CVehicle::CreateUpgradeAtomic(CBaseModelInfo *model,UpgradePosnDesc const*upgradePosn,RwFrame *parentComponent,bool isDamaged) 0x6D3510
RpAtomic* CVehicle::CreateUpgradeAtomic(CBaseModelInfo* model, UpgradePosnDesc const* upgradePosn, RwFrame* parentComponent, bool isDamaged)
{
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, UpgradePosnDesc const*, RwFrame*, bool))0x6D3510)(this, model, upgradePosn, parentComponent, isDamaged);
}

// Converted from thiscall void CVehicle::RemoveUpgrade(int upgradeId) 0x6D3630
void CVehicle::RemoveUpgrade(int upgradeId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D3630)(this, upgradeId);
}

// Converted from thiscall int CVehicle::GetUpgrade(int upgradeId) 0x6D3650
int CVehicle::GetUpgrade(int upgradeId)
{
    return ((int(__thiscall*)(CVehicle*, int))0x6D3650)(this, upgradeId);
}

// Converted from thiscall RpAtomic* CVehicle::CreateReplacementAtomic(CBaseModelInfo *model,RwFrame *component,int,bool bDamaged,bool bIsWheel) 0x6D3700
RpAtomic* CVehicle::CreateReplacementAtomic(CBaseModelInfo* model, RwFrame* component, int arg2, bool bDamaged, bool bIsWheel)
{
    return ((RpAtomic * (__thiscall*)(CVehicle*, CBaseModelInfo*, RwFrame*, int, bool, bool))0x6D3700)(this, model, component, arg2, bDamaged, bIsWheel);
}

// Converted from thiscall void CVehicle::AddReplacementUpgrade(int modelIndex,int nodeId) 0x6D3830
void CVehicle::AddReplacementUpgrade(int modelIndex, int nodeId)
{
    ((void(__thiscall*)(CVehicle*, int, int))0x6D3830)(this, modelIndex, nodeId);
}

// Converted from thiscall void CVehicle::RemoveReplacementUpgrade(int nodeId) 0x6D39E0
void CVehicle::RemoveReplacementUpgrade(int nodeId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D39E0)(this, nodeId);
}

// Converted from thiscall void CVehicle::GetReplacementUpgrade(int nodeId) 0x6D3A50
void CVehicle::GetReplacementUpgrade(int nodeId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D3A50)(this, nodeId);
}

// Converted from thiscall void CVehicle::RemoveAllUpgrades(void) 0x6D3AB0
void CVehicle::RemoveAllUpgrades()
{
    ((void(__thiscall*)(CVehicle*))0x6D3AB0)(this);
}

// Converted from thiscall int CVehicle::GetSpareHasslePosId(void) 0x6D3AE0
int CVehicle::GetSpareHasslePosId()
{
    return ((int(__thiscall*)(CVehicle*))0x6D3AE0)(this);
}

// Converted from thiscall void CVehicle::SetHasslePosId(int hasslePos,bool enable) 0x6D3B30
void CVehicle::SetHasslePosId(int hasslePos, bool enable)
{
    ((void(__thiscall*)(CVehicle*, int, bool))0x6D3B30)(this, hasslePos, enable);
}

// Converted from thiscall void CVehicle::InitWinch(int) 0x6D3B60
void CVehicle::InitWinch(int arg0)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D3B60)(this, arg0);
}

// Converted from thiscall void CVehicle::UpdateWinch(void) 0x6D3B80
void CVehicle::UpdateWinch()
{
    ((void(__thiscall*)(CVehicle*))0x6D3B80)(this);
}

// Converted from thiscall void CVehicle::RemoveWinch(void) 0x6D3C70
void CVehicle::RemoveWinch()
{
    ((void(__thiscall*)(CVehicle*))0x6D3C70)(this);
}

// Converted from thiscall void CVehicle::ReleasePickedUpEntityWithWinch(void) 0x6D3CB0
void CVehicle::ReleasePickedUpEntityWithWinch()
{
    ((void(__thiscall*)(CVehicle*))0x6D3CB0)(this);
}

// Converted from thiscall void CVehicle::PickUpEntityWithWinch(CEntity *) 0x6D3CD0
void CVehicle::PickUpEntityWithWinch(CEntity* arg0)
{
    ((void(__thiscall*)(CVehicle*, CEntity*))0x6D3CD0)(this, arg0);
}

// Converted from thiscall CEntity* CVehicle::QueryPickedUpEntityWithWinch(void) 0x6D3CF0
CEntity* CVehicle::QueryPickedUpEntityWithWinch()
{
    return ((CEntity * (__thiscall*)(CVehicle*))0x6D3CF0)(this);
}

// Converted from thiscall float CVehicle::GetRopeHeightForHeli(void) 0x6D3D10
float CVehicle::GetRopeHeightForHeli()
{
    return ((float(__thiscall*)(CVehicle*))0x6D3D10)(this);
}

// Converted from thiscall void CVehicle::SetRopeHeightForHeli(float height) 0x6D3D30
void CVehicle::SetRopeHeightForHeli(float height)
{
    ((void(__thiscall*)(CVehicle*, float))0x6D3D30)(this, height);
}

// Converted from thiscall void CVehicle::RenderDriverAndPassengers(void) 0x6D3D60
void CVehicle::RenderDriverAndPassengers()
{
    ((void(__thiscall*)(CVehicle*))0x6D3D60)(this);
}

// Converted from thiscall void CVehicle::PreRenderDriverAndPassengers(void) 0x6D3DB0
void CVehicle::PreRenderDriverAndPassengers()
{
    ((void(__thiscall*)(CVehicle*))0x6D3DB0)(this);
}

// Converted from thiscall float CVehicle::GetPlaneGunsAutoAimAngle(void) 0x6D3E00
float CVehicle::GetPlaneGunsAutoAimAngle()
{
    return ((float(__thiscall*)(CVehicle*))0x6D3E00)(this);
}

// Converted from thiscall int CVehicle::GetPlaneNumGuns(void) 0x6D3F30
int CVehicle::GetPlaneNumGuns()
{
    return ((int(__thiscall*)(CVehicle*))0x6D3F30)(this);
}

// Converted from thiscall void CVehicle::SetFiringRateMultiplier(float multiplier) 0x6D4010
void CVehicle::SetFiringRateMultiplier(float multiplier)
{
    ((void(__thiscall*)(CVehicle*, float))0x6D4010)(this, multiplier);
}

// Converted from thiscall float CVehicle::GetFiringRateMultiplier(void) 0x6D4090
float CVehicle::GetFiringRateMultiplier()
{
    return ((float(__thiscall*)(CVehicle*))0x6D4090)(this);
}

// Converted from thiscall unsigned int CVehicle::GetPlaneGunsRateOfFire(void) 0x6D40E0
unsigned int CVehicle::GetPlaneGunsRateOfFire()
{
    return ((unsigned int(__thiscall*)(CVehicle*))0x6D40E0)(this);
}

// Converted from thiscall CVector CVehicle::GetPlaneGunsPosition(int gunId) 0x6D4290
CVector CVehicle::GetPlaneGunsPosition(int gunId)
{
    CVector result;
    ((void(__thiscall*)(CVehicle*, CVector*, int))0x6D4290)(this, &result, gunId);
    return result;
}

// Converted from thiscall unsigned int CVehicle::GetPlaneOrdnanceRateOfFire(eOrdnanceType ordnanceType) 0x6D4590
unsigned int CVehicle::GetPlaneOrdnanceRateOfFire(eOrdnanceType ordnanceType)
{
    return ((unsigned int(__thiscall*)(CVehicle*, eOrdnanceType))0x6D4590)(this, ordnanceType);
}

// Converted from thiscall CVector CVehicle::GetPlaneOrdnancePosition(eOrdnanceType ordnanceType) 0x6D46E0
CVector CVehicle::GetPlaneOrdnancePosition(eOrdnanceType ordnanceType)
{
    CVector result;
    ((void(__thiscall*)(CVehicle*, CVector*, eOrdnanceType))0x6D46E0)(this, &result, ordnanceType);
    return result;
}

// Converted from thiscall void CVehicle::SelectPlaneWeapon(bool bChange,eOrdnanceType ordnanceType) 0x6D4900
void CVehicle::SelectPlaneWeapon(bool bChange, eOrdnanceType ordnanceType)
{
    ((void(__thiscall*)(CVehicle*, bool, eOrdnanceType))0x6D4900)(this, bChange, ordnanceType);
}

// Converted from thiscall void CVehicle::DoPlaneGunFireFX(CWeapon *weapon,CVector &particlePos,CVector &gunshellPos,int particleIndex) 0x6D4AD0
void CVehicle::DoPlaneGunFireFX(CWeapon* weapon, CVector& particlePos, CVector& gunshellPos, int particleIndex)
{
    ((void(__thiscall*)(CVehicle*, CWeapon*, CVector&, CVector&, int))0x6D4AD0)(this, weapon, particlePos, gunshellPos, particleIndex);
}

// Converted from thiscall void CVehicle::FirePlaneGuns(void) 0x6D4D30
void CVehicle::FirePlaneGuns()
{
    ((void(__thiscall*)(CVehicle*))0x6D4D30)(this);
}

// Converted from thiscall void CVehicle::FireUnguidedMissile(eOrdnanceType ordnanceType,bool bCheckTime) 0x6D5110
void CVehicle::FireUnguidedMissile(eOrdnanceType ordnanceType, bool bCheckTime)
{
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6D5110)(this, ordnanceType, bCheckTime);
}

// Converted from thiscall bool CVehicle::CanBeDriven(void) 0x6D5400
bool CVehicle::CanBeDriven()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D5400)(this);
}

// Converted from thiscall void CVehicle::ReactToVehicleDamage(CPed *ped) 0x6D5490
void CVehicle::ReactToVehicleDamage(CPed* ped)
{
    ((void(__thiscall*)(CVehicle*, CPed*))0x6D5490)(this, ped);
}

// Converted from thiscall bool CVehicle::GetVehicleLightsStatus(void) 0x6D55C0
bool CVehicle::GetVehicleLightsStatus()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D55C0)(this);
}

// Converted from thiscall bool CVehicle::CanPedLeanOut(CPed *ped) 0x6D5CF0
bool CVehicle::CanPedLeanOut(CPed* ped)
{
    return ((bool(__thiscall*)(CVehicle*, CPed*))0x6D5CF0)(this, ped);
}

// Converted from thiscall void CVehicle::SetVehicleCreatedBy(int createdBy) 0x6D5D70
void CVehicle::SetVehicleCreatedBy(int createdBy)
{
    ((void(__thiscall*)(CVehicle*, int))0x6D5D70)(this, createdBy);
}

// Converted from thiscall void CVehicle::SetupRender(void) 0x6D64F0
void CVehicle::SetupRender()
{
    ((void(__thiscall*)(CVehicle*))0x6D64F0)(this);
}

void CVehicle::ProcessWheel(CVector& wheelFwd, CVector& wheelRight, CVector& wheelContactSpeed, CVector& wheelContactPoint,
    int wheelsOnGround, float thrust, float brake, float adhesion, int8_t wheelId, float* wheelSpeed, tWheelState* wheelState, uint16_t wheelStatus)
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

    adhesion *= CTimer::ms_fTimeStep;
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
            else if (IsPlane())
                brake = 0.0f;
            else if (brake < 500.0f)
                brake = 0.1f * gHandlingDataMgr.fWheelFriction / m_pHandlingData->m_fMass;
            else if (m_nModelIndex == MODEL_RCBANDIT)
                brake = 0.2f * gHandlingDataMgr.fWheelFriction / m_pHandlingData->m_fMass;
            else
                brake = gHandlingDataMgr.fWheelFriction / m_pHandlingData->m_fMass;
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

// Converted from thiscall void CVehicle::ProcessBikeWheel(CVector &,CVector &,CVector &,CVector &,int,float,float,float,float,char,float *,tWheelState *,eBikeWheelSpecial,ushort) 0x6D73B0
void CVehicle::ProcessBikeWheel(CVector& arg0, CVector& arg1, CVector& arg2, CVector& arg3, int arg4, float arg5, float arg6, float arg7, float arg8, char arg9, float* arg10, tWheelState* arg11, eBikeWheelSpecial arg12, unsigned short arg13)
{
    ((void(__thiscall*)(CVehicle*, CVector&, CVector&, CVector&, CVector&, int, float, float, float, float, char, float*, tWheelState*, eBikeWheelSpecial, unsigned short))0x6D73B0)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, arg10, arg11, arg12, arg13);
}

// Converted from thiscall int CVehicle::FindTyreNearestPoint(float x,float y) 0x6D7BC0
int CVehicle::FindTyreNearestPoint(float x, float y)
{
    return ((int(__thiscall*)(CVehicle*, float, float))0x6D7BC0)(this, x, y);
}

// Converted from thiscall void CVehicle::InflictDamage(CEntity *damager,eWeaponType weapon,float intensity,CVector coords) 0x6D7C90
void CVehicle::InflictDamage(CEntity* damager, eWeaponType weapon, float intensity, CVector coords)
{
    ((void(__thiscall*)(CVehicle*, CEntity*, eWeaponType, float, CVector))0x6D7C90)(this, damager, weapon, intensity, coords);
}

// Converted from thiscall void CVehicle::KillPedsGettingInVehicle(void) 0x6D82F0
void CVehicle::KillPedsGettingInVehicle()
{
    ((void(__thiscall*)(CVehicle*))0x6D82F0)(this);
}

// Converted from thiscall bool CVehicle::UsesSiren(void) 0x6D8470
bool CVehicle::UsesSiren()
{
    return ((bool(__thiscall*)(CVehicle*))0x6D8470)(this);
}

// Converted from thiscall bool CVehicle::IsSphereTouchingVehicle(float x,float y,float z,float radius) 0x6D84D0
bool CVehicle::IsSphereTouchingVehicle(float x, float y, float z, float radius)
{
    return ((bool(__thiscall*)(CVehicle*, float, float, float, float))0x6D84D0)(this, x, y, z, radius);
}

// Converted from thiscall void CVehicle::FlyingControl(eFlightModel flightModel,float,float,float,float) 0x6D85F0
void CVehicle::FlyingControl(eFlightModel flightModel, float leftRightSkid, float steeringUpDown, float steeringLeftRight, float accelerationBreakStatus)
{
    ((void(__thiscall*)(CVehicle*, eFlightModel, float, float, float, float))0x6D85F0)(this, flightModel, leftRightSkid, steeringUpDown, steeringLeftRight, accelerationBreakStatus);
}

// Converted from thiscall void CVehicle::BladeColSectorList(CPtrList &ptrList,CColModel &colModel,CMatrix &matrix,short,float) 0x6DAF00
void CVehicle::BladeColSectorList(CPtrList& ptrList, CColModel& colModel, CMatrix& matrix, short arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, CPtrList&, CColModel&, CMatrix&, short, float))0x6DAF00)(this, ptrList, colModel, matrix, arg3, arg4);
}

// Converted from thiscall void CVehicle::SetComponentRotation(RwFrame *component,int axis,float angle,bool bResetPosition) 0x6DBA30
void CVehicle::SetComponentRotation(RwFrame* component, int axis, float angle, bool bResetPosition)
{
    plugin::CallMethod<0x6DBA30, CVehicle*, RwFrame*, int, float, bool>(this, component, axis, angle, bResetPosition);
}

// Converted from thiscall void CVehicle::SetTransmissionRotation(RwFrame *component,float,float,CVector posn,bool isFront) 0x6DBBB0
void CVehicle::SetTransmissionRotation(RwFrame* component, float arg1, float arg2, CVector posn, bool isFront)
{
    ((void(__thiscall*)(CVehicle*, RwFrame*, float, float, CVector, bool))0x6DBBB0)(this, component, arg1, arg2, posn, isFront);
}

// Converted from thiscall void CVehicle::ProcessBoatControl(tBoatHandlingData *boatHandling,float &,bool,bool) 0x6DBCE0
void CVehicle::ProcessBoatControl(tBoatHandlingData* boatHandling, float* fLastWaterImmersionDepth, bool bCollidedWithWorld, bool bPostCollision)
{
    CVector vecBuoyancyTurnPoint;
    CVector vecBuoyancyForce;
    if (!mod_Buoyancy.ProcessBuoyancyBoat(this, m_fBuoyancyConstant, &vecBuoyancyTurnPoint, &vecBuoyancyForce, bCollidedWithWorld)) {
        physicalFlags.bSubmergedInWater = false;
        if (IsBoat())
            static_cast<CBoat*>(this)->m_nBoatFlags.bOnWater = false;

        return;
    }

    bool bOnWater = false;
    vehicleFlags.bIsDrowning = false;
    if (CTimer::ms_fTimeStep * m_fMass * 0.0008F >= vecBuoyancyForce.z) {
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
                    static_cast<CPlayerPed*>(m_pDriver)->HandlePlayerBreath(true, 1.0F);
                else
                {
                    auto pedDamageResponseCalc = CPedDamageResponseCalculator(this, CTimer::ms_fTimeStep, eWeaponType::WEAPON_DROWNING, ePedPieceTypes::PED_PIECE_TORSO, false);
                    auto damageEvent = CEventDamage(this, CTimer::m_snTimeInMilliseconds, eWeaponType::WEAPON_DROWNING, ePedPieceTypes::PED_PIECE_TORSO, 0, false, true);
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
    if (m_nModelIndex == eModelID::MODEL_SKIMMER
        && GetUp().z < -0.5F
        && fabs(m_vecMoveSpeed.x) < 0.2F
        && fabs(m_vecMoveSpeed.y) < 0.2F) {

        vecUsedBuoyancyForce *= 0.03F;
    }
    CPhysical::ApplyMoveForce(vecUsedBuoyancyForce);

    if (bCollidedWithWorld)
        CPhysical::ApplyTurnForce(vecBuoyancyForce * 0.4F, vecBuoyancyTurnPoint);

    if (m_nModelIndex == eModelID::MODEL_SKIMMER) {
        auto fCheckedMass = CTimer::ms_fTimeStep * m_fMass;
        if (m_f2ndSteerAngle != 0.0F
            || (GetForward().z < -0.5F
            && GetUp().z > -0.5F
            && m_vecMoveSpeed.z < -0.15F
            && fCheckedMass * 0.01F / 125.0F < vecBuoyancyForce.z
            && vecBuoyancyForce.z < fCheckedMass * 0.4F / 125.0F)) {

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
                m_f2ndSteerAngle = CTimer::m_snTimeInMilliseconds + 300.0F;
            }
            else if (m_f2ndSteerAngle <= CTimer::m_snTimeInMilliseconds) {
                m_f2ndSteerAngle = 0.0F;
            }
        }
    }

    if (!bPostCollision && bOnWater && GetUp().z > 0.0F) {
        auto fMoveForce = m_vecMoveSpeed.SquaredMagnitude() * boatHandling->m_fAqPlaneForce * CTimer::ms_fTimeStep * vecBuoyancyForce.z * 0.5F;
        if (m_nModelIndex == eModelID::MODEL_SKIMMER)
            fMoveForce *= (m_fGasPedal + 1.0F);
        else if (m_fGasPedal <= 0.05F)
            fMoveForce = 0.0F;
        else
            fMoveForce *= m_fGasPedal;

        auto fMaxMoveForce = CTimer::ms_fTimeStep * boatHandling->m_fAqPlaneLimit * m_fMass / 125.0F;
        fMoveForce = std::min(fMoveForce, fMaxMoveForce);

        auto vecUsedMoveForce = GetUp() * fMoveForce;
        CPhysical::ApplyMoveForce(vecUsedMoveForce);

        auto vecOffset = GetForward() * boatHandling->m_fAqPlaneOffset;
        auto vecTurnPoint = vecBuoyancyTurnPoint - vecOffset;
        CPhysical::ApplyTurnForce(vecUsedMoveForce, vecTurnPoint);
    }

    CPad* pPad = nullptr;
    if (m_nStatus == eEntityStatus::STATUS_PLAYER && m_pDriver && m_pDriver->IsPlayer()) {
        pPad = static_cast<CPlayerPed*>(m_pDriver)->GetPadFromPlayer();
    }

    if (GetUp().z > -0.6F) {
        float fMoveSpeed = 1.0F;
        if (fabs(m_fGasPedal) <= 0.05F)
            fMoveSpeed = CVector2D(m_vecMoveSpeed).Magnitude();

        if (fabs(m_fGasPedal) > 0.05F || fMoveSpeed > 0.01F) {
            if (IsBoat() && bOnWater && fMoveSpeed > 0.05F) {
                //GetColModel(); Unused call
                static_cast<CBoat*>(this)->AddWakePoint(GetPosition());
            }

            auto fTraction = 1.0F;
            if (m_nStatus == eEntityStatus::STATUS_PLAYER) {
                auto fTractionLoss = DotProduct(m_vecMoveSpeed, GetForward()) * m_pHandlingData->m_fTractionBias;
                if (pPad->GetHandBrake())
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
                if (IsBoat())
                    static_cast<CBoat*>(this)->m_nBoatFlags.bMovingOnWater = false;
            }
            else {
                auto fThrustDepth = fWaterLevel - vecWorldThrustPos.z + 0.5F;
                fThrustDepth = std::min(fThrustDepth * fThrustDepth, 1.0F);

                if (IsBoat())
                    static_cast<CBoat*>(this)->m_nBoatFlags.bMovingOnWater = true;

                bool bIsSlowingDown = false;
                auto fGasState = fabs(m_fGasPedal);
                if (fGasState < 0.01F || m_nModelIndex == eModelID::MODEL_SKIMMER) {
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
                        CPhysical::ApplyMoveForce(vecSteerMoveForce * CTimer::ms_fTimeStep);
                    }
                    else {
                        CPhysical::ApplyMoveForce(vecSteerMoveForce * CTimer::ms_fTimeStep);

                        auto vecTurnForcePoint = vecTransformedThrustPoint - (GetUp() * boatHandling->m_fThrustAppZ);
                        CPhysical::ApplyTurnForce(vecSteerMoveForce * CTimer::ms_fTimeStep, vecTurnForcePoint);

                        auto fTractionSide = -DotProduct(vecSteerMoveForce, GetRight()) * m_pHandlingData->m_fTractionMultiplier;
                        auto vecTurnForceSide = GetRight() * fTractionSide * CTimer::ms_fTimeStep;
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
                    vecTractionLossTransformed *= fThrustDepth * CTimer::ms_fTimeStep;

                    CPhysical::ApplyMoveForce(vecTractionLossTransformed);
                    CPhysical::ApplyTurnForce(vecTractionLossTransformed, vecTransformedThrustPoint);

                    auto fUsedTimestep = std::max(CTimer::ms_fTimeStep, 0.01F);
                    auto vecTurn = GetRight() * fUsedTimestep / fTraction * fTractionLoss * fSteerAngleSin * -0.75F;
                    CPhysical::ApplyTurnForce(vecTurn, GetUp());
                }
            }
        }
    }

    if (m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear != 0.0F) {
        auto vecCross = CVector();
        vecCross.Cross(GetForward(), CVector(0.0F, 0.0F, 1.0F));

        auto fMult = DotProduct(vecCross, m_vecMoveSpeed) * m_pHandlingData->m_fSuspensionBiasBetweenFrontAndRear * CTimer::ms_fTimeStep * fImmersionDepth * m_fMass * -0.1F;
        float fXTemp = vecCross.x * 0.3F;
        vecCross.x -= vecCross.y * 0.3F;
        vecCross.y += fXTemp;

        auto vecMoveForce = vecCross * fMult;
        CPhysical::ApplyMoveForce(vecMoveForce);
    }

    if (m_nStatus == eEntityStatus::STATUS_PLAYER && pPad->GetHandBrake()) {
        auto fDirDotProd = DotProduct(m_vecMoveSpeed, GetForward());
        if (fDirDotProd > 0.0F) {
            auto fMoveForceMult = fDirDotProd * m_pHandlingData->m_fSuspensionLowerLimit * CTimer::ms_fTimeStep * fImmersionDepth * m_fMass * -0.1F;
            auto vecMoveForce = GetForward() * fMoveForceMult;
            CPhysical::ApplyMoveForce(vecMoveForce);
        }
    }

    if (bOnWater && !bPostCollision && !bCollidedWithWorld) {
        CVehicle::ApplyBoatWaterResistance(boatHandling, fImmersionDepth);
    }

    if ((m_nModelIndex != eModelID::MODEL_SKIMMER || m_f2ndSteerAngle == 0.0F) && !bCollidedWithWorld) {
        auto vecTurnRes = Pow(boatHandling->m_vecTurnRes, CTimer::ms_fTimeStep);
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
    if (IsBoat()) {
        static_cast<CBoat*>(this)->m_vecWaterDamping = vecBuoyancyForce;
        static_cast<CBoat*>(this)->m_nBoatFlags.bOnWater = bOnWater;
    }
    else if (m_vehicleType == eVehicleType::VEHICLE_AUTOMOBILE){
        static_cast<CAutomobile*>(this)->m_fDoomHorizontalRotation = vecBuoyancyForce.Magnitude();
    }
}

// Converted from thiscall void CVehicle::DoBoatSplashes(float) 0x6DD130
void CVehicle::DoBoatSplashes(float fWaterDamping)
{
    plugin::CallMethod<0x6DD130, CVehicle*, float>(this, fWaterDamping);
}

// Converted from thiscall void CVehicle::DoSunGlare(void) 0x6DD6F0
void CVehicle::DoSunGlare()
{
    ((void(__thiscall*)(CVehicle*))0x6DD6F0)(this);
}

// Converted from thiscall void CVehicle::AddWaterSplashParticles(void) 0x6DDF60
void CVehicle::AddWaterSplashParticles()
{
    ((void(__thiscall*)(CVehicle*))0x6DDF60)(this);
}

// Converted from thiscall void CVehicle::AddExhaustParticles(void) 0x6DE240
void CVehicle::AddExhaustParticles()
{
    if (m_bOffscreen)
        return;
    float fSquaredMagnitude = (TheCamera.GetPosition() - GetPosition()).SquaredMagnitude();
    if (fSquaredMagnitude > 256.0f || fSquaredMagnitude > 64.0f
        && !((CTimer::m_FrameCounter + static_cast<std::uint8_t>(m_nModelIndex)) & 1))
    {
        return;
    }
    auto pVehicleModelInfo = static_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[m_nModelIndex]);
    CVector firstExhaustPos = pVehicleModelInfo->m_pVehicleStruct->m_avDummyPos[DUMMY_EXHAUST];
    CVector secondExhaustPos = firstExhaustPos;
    secondExhaustPos.x *= -1.0f;
    CMatrix entityMatrix (*m_matrix);
    bool bHasDoubleExhaust = m_pHandlingData->m_bDoubleExhaust;
    if (m_vehicleSubType == VEHICLE_BIKE) {
        CBike* pBike = static_cast<CBike*>(this);
        pBike->CalculateLeanMatrix();
        entityMatrix = pBike->m_mLeanMatrix;
        switch (m_nModelIndex)
        {
        case MODEL_FCR900:
            if (m_anExtras[0] == 1 || m_anExtras[0] == 2)
                bHasDoubleExhaust = true;
            break;
        case MODEL_NRG500:
            if (!m_anExtras[0] || m_anExtras[0] == 1)  
                secondExhaustPos = pVehicleModelInfo->m_pVehicleStruct->m_avDummyPos[DUMMY_EXHAUST_SECONDARY];
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
            std::int32_t numExhausts = 2;
            for (std::int32_t i = 0; i < 2; i++) {
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
                    if (rand() & 1) {
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

// Converted from thiscall bool CVehicle::AddSingleWheelParticles(tWheelState,uint,float,float,CColPoint *,CVector *,float,int,uint surfaceType,bool *bloodState,uint) 0x6DE880
bool CVehicle::AddSingleWheelParticles(tWheelState arg0, unsigned int arg1, float arg2, float arg3, CColPoint* arg4, CVector* arg5, float arg6, int arg7, unsigned int surfaceType, bool* bloodState, unsigned int arg10)
{
    return ((bool(__thiscall*)(CVehicle*, tWheelState, unsigned int, float, float, CColPoint*, CVector*, float, int, unsigned int, bool*, unsigned int))0x6DE880)(this, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, surfaceType, bloodState, arg10);
}

// Converted from thiscall bool CVehicle::GetSpecialColModel(void) 0x6DF3D0
bool CVehicle::GetSpecialColModel()
{
    return ((bool(__thiscall*)(CVehicle*))0x6DF3D0)(this);
}

// Converted from thiscall void CVehicle::RemoveVehicleUpgrade(int upgradeModelIndex) 0x6DF930
void CVehicle::RemoveVehicleUpgrade(int upgradeModelIndex)
{
    ((void(__thiscall*)(CVehicle*, int))0x6DF930)(this, upgradeModelIndex);
}

// Converted from thiscall void CVehicle::AddUpgrade(int modelIndex,int upgradeIndex) 0x6DFA20
void CVehicle::AddUpgrade(int modelIndex, int upgradeIndex)
{
    ((void(__thiscall*)(CVehicle*, int, int))0x6DFA20)(this, modelIndex, upgradeIndex);
}

// Converted from thiscall void CVehicle::UpdateTrailerLink(bool,bool) 0x6DFC50
void CVehicle::UpdateTrailerLink(bool arg0, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6DFC50)(this, arg0, arg1);
}

// Converted from thiscall void CVehicle::UpdateTractorLink(bool,bool) 0x6E0050
void CVehicle::UpdateTractorLink(bool arg0, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, bool, bool))0x6E0050)(this, arg0, arg1);
}

// Converted from thiscall CEntity* CVehicle::ScanAndMarkTargetForHeatSeekingMissile(CEntity *entity) 0x6E0400
CEntity* CVehicle::ScanAndMarkTargetForHeatSeekingMissile(CEntity* entity)
{
    return ((CEntity * (__thiscall*)(CVehicle*, CEntity*))0x6E0400)(this, entity);
}

// Converted from thiscall void CVehicle::FireHeatSeakingMissile(CEntity *targetEntity,eOrdnanceType ordnanceType,bool) 0x6E05C0
void CVehicle::FireHeatSeakingMissile(CEntity* targetEntity, eOrdnanceType ordnanceType, bool arg2)
{
    ((void(__thiscall*)(CVehicle*, CEntity*, eOrdnanceType, bool))0x6E05C0)(this, targetEntity, ordnanceType, arg2);
}

// Converted from thiscall void CVehicle::PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType,bool) 0x6E07E0
void CVehicle::PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType, bool arg1)
{
    ((void(__thiscall*)(CVehicle*, eOrdnanceType, bool))0x6E07E0)(this, ordnanceType, arg1);
}

// Converted from thiscall void CVehicle::ProcessSirenAndHorn(bool) 0x6E0950
void CVehicle::ProcessSirenAndHorn(bool arg0)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6E0950)(this, arg0);
}

// Converted from thiscall bool CVehicle::DoHeadLightEffect(int dummyId,CMatrix &vehicleMatrix,uchar lightId,uchar lightState) 0x6E0A50
bool CVehicle::DoHeadLightEffect(int dummyId, CMatrix& vehicleMatrix, unsigned char lightId, unsigned char lightState)
{
    return ((bool(__thiscall*)(CVehicle*, int, CMatrix&, unsigned char, unsigned char))0x6E0A50)(this, dummyId, vehicleMatrix, lightId, lightState);
}

// Converted from thiscall void CVehicle::DoHeadLightBeam(int,CMatrix &matrix,uchar) 0x6E0E20
void CVehicle::DoHeadLightBeam(int arg0, CMatrix& matrix, unsigned char arg2)
{
    ((void(__thiscall*)(CVehicle*, int, CMatrix&, unsigned char))0x6E0E20)(this, arg0, matrix, arg2);
}

// Converted from thiscall void CVehicle::DoHeadLightReflectionSingle(CMatrix &matrix,uchar lightId) 0x6E1440
void CVehicle::DoHeadLightReflectionSingle(CMatrix& matrix, unsigned char lightId)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, unsigned char))0x6E1440)(this, matrix, lightId);
}

// Converted from thiscall void CVehicle::DoHeadLightReflectionTwin(CMatrix &matrix) 0x6E1600
void CVehicle::DoHeadLightReflectionTwin(CMatrix& matrix)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&))0x6E1600)(this, matrix);
}

// Converted from thiscall void CVehicle::DoHeadLightReflection(CMatrix &,uint,uchar,uchar) 0x6E1720
void CVehicle::DoHeadLightReflection(CMatrix& arg0, unsigned int flags, unsigned char left, unsigned char right)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, unsigned int, unsigned char, unsigned char))0x6E1720)(this, arg0, flags, left, right);
}

// Converted from thiscall bool CVehicle::DoTailLightEffect(int lightId,CMatrix &matrix,uchar,uchar,uint,uchar) 0x6E1780
bool CVehicle::DoTailLightEffect(int lightId, CMatrix& matrix, unsigned char arg2, unsigned char arg3, unsigned int arg4, unsigned char arg5)
{
    return ((bool(__thiscall*)(CVehicle*, int, CMatrix&, unsigned char, unsigned char, unsigned int, unsigned char))0x6E1780)(this, lightId, matrix, arg2, arg3, arg4, arg5);
}

// Converted from thiscall void CVehicle::DoVehicleLights(CMatrix &matrix,uint flags) 0x6E1A60
void CVehicle::DoVehicleLights(CMatrix& matrix, unsigned int flags)
{
    ((void(__thiscall*)(CVehicle*, CMatrix&, unsigned int))0x6E1A60)(this, matrix, flags);
}

// Converted from thiscall void CVehicle::FillVehicleWithPeds(bool bSetClothesToAfro) 0x6E2900
void CVehicle::FillVehicleWithPeds(bool bSetClothesToAfro)
{
    ((void(__thiscall*)(CVehicle*, bool))0x6E2900)(this, bSetClothesToAfro);
}

// Converted from thiscall void CVehicle::DoBladeCollision(CVector,CMatrix &matrix,short,float,float) 0x6E2E50
void CVehicle::DoBladeCollision(CVector arg0, CMatrix& matrix, short arg2, float arg3, float arg4)
{
    ((void(__thiscall*)(CVehicle*, CVector, CMatrix&, short, float, float))0x6E2E50)(this, arg0, matrix, arg2, arg3, arg4);
}

// Converted from thiscall void CVehicle::AddVehicleUpgrade(int modelId) 0x6E3290
void CVehicle::AddVehicleUpgrade(int modelId)
{
    ((void(__thiscall*)(CVehicle*, int))0x6E3290)(this, modelId);
}

// Converted from thiscall void CVehicle::SetupUpgradesAfterLoad(void) 0x6E3400
void CVehicle::SetupUpgradesAfterLoad()
{
    ((void(__thiscall*)(CVehicle*))0x6E3400)(this);
}

// Converted from thiscall void CVehicle::GetPlaneWeaponFiringStatus(bool &status,eOrdnanceType &ordnanceType) 0x6E3440 0x6E38A0
void CVehicle::GetPlaneWeaponFiringStatus(bool& status, eOrdnanceType& ordnanceType)
{
    ((void(__thiscall*)(CVehicle*, bool&, eOrdnanceType&))0x6E3440)(this, status, ordnanceType);
}

// Converted from stdcall bool IsVehiclePointerValid(CVehicle *vehicle) 0x6E38F0
bool IsVehiclePointerValid(CVehicle* vehicle)
{
    return ((bool(__cdecl*)(CVehicle*))0x6E38F0)(vehicle);
}

// Converted from thiscall void CVehicle::ProcessWeapons(void) 0x6E3950
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
