/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

float& CWeapon::ms_fExtinguisherAimAngle = *(float*)0x8D610C;
bool& CWeapon::bPhotographHasBeenTaken = *(bool*)0xC8A7C0;
bool& CWeapon::ms_bTakePhoto = *(bool*)0xC8A7C1;
CColModel& CWeapon::ms_PelletTestCol = *(CColModel*)0xC8A7DC;
float& fPlayerAimScale = *(float*)0x8D6110;
float& fPlayerAimScaleDist = *(float*)0x8D6114;
float& fPlayerAimRotRate = *(float*)0x8D6118;
float& SHOTGUN_SPREAD_RATE = *(float*)0x8D611C;
uint32_t& SHOTGUN_NUM_PELLETS = *(uint32_t*)0x8D6120;
uint32_t& SPAS_NUM_PELLETS = *(uint32_t*)0x8D6124;
float& PELLET_COL_SCALE_RATIO_MULT = *(float*)0x8D6128;
float* fReloadAnimSampleFraction = (float*)0x8D612C;

void CWeapon::InjectHooks() {
    ReversibleHooks::Install("CWeapon", "Constructor", 0x73B430, &CWeapon::Constructor);
    ReversibleHooks::Install("CWeapon", "Shutdown", 0x73A380, &CWeapon::Shutdown);
    ReversibleHooks::Install("CWeapon", "Reload", 0x73AEB0, &CWeapon::Reload);
    ReversibleHooks::Install("CWeapon", "IsTypeMelee", 0x73B1C0, &CWeapon::IsTypeMelee);
    ReversibleHooks::Install("CWeapon", "IsType2Handed", 0x73B1E0, &CWeapon::IsType2Handed);
    ReversibleHooks::Install("CWeapon", "IsTypeProjectile", 0x73B210, &CWeapon::IsTypeProjectile);
    ReversibleHooks::Install("CWeapon", "HasWeaponAmmoToBeUsed", 0x73B2A0, &CWeapon::HasWeaponAmmoToBeUsed);
    ReversibleHooks::Install("CWeapon", "CanBeUsedFor2Player", 0x73B240, (bool (*)(eWeaponType weaponType))&CWeapon::CanBeUsedFor2Player);
    ReversibleHooks::Install("CWeapon", "InitialiseWeapons", 0x73A300, &CWeapon::InitialiseWeapons);
    ReversibleHooks::Install("CWeapon", "ShutdownWeapons", 0x73A330, &CWeapon::ShutdownWeapons);
    ReversibleHooks::Install("CWeapon", "UpdateWeapons", 0x73A360, &CWeapon::UpdateWeapons);
    ReversibleHooks::Install("CWeapon", "AddGunshell", 0x73A3E0, &CWeapon::AddGunshell);
    ReversibleHooks::Install("CWeapon", "ProcessLineOfSight", 0x73B300, &CWeapon::ProcessLineOfSight);
    ReversibleHooks::Install("CWeapon", "StopWeaponEffect", 0x73B360, &CWeapon::StopWeaponEffect);
    ReversibleHooks::Install("CWeapon", "TargetWeaponRangeMultiplier", 0x73B380, &CWeapon::TargetWeaponRangeMultiplier);
    ReversibleHooks::Install("CWeapon", "Initialise", 0x73B4A0, &CWeapon::Initialise);
    ReversibleHooks::Install("CWeapon", "DoWeaponEffect", 0x73E690, &CWeapon::DoWeaponEffect);
    ReversibleHooks::Install("CWeapon", "FireSniper", 0x73AAC0, &CWeapon::FireSniper);
}

// 0x73A300
void CWeapon::InitialiseWeapons() {
    CWeaponInfo::Initialise();
    CShotInfo::Initialise();
    CExplosion::Initialise();
    CProjectileInfo::Initialise();
    CBulletInfo::Initialise();

    bPhotographHasBeenTaken = false;
    ms_bTakePhoto = false;
}

// 0x73A330
void CWeapon::ShutdownWeapons() {
    CWeaponInfo::Shutdown();
    CShotInfo::Shutdown();
    CExplosion::Shutdown();
    CProjectileInfo::Shutdown();
    CBulletInfo::Shutdown();

    ms_PelletTestCol.RemoveCollisionVolumes();
}

// 0x73A360
void CWeapon::UpdateWeapons() {
    CShotInfo::Update();
    CExplosion::Update();
    CProjectileInfo::Update();
    CBulletInfo::Update();
}

// 0x73A380
void CWeapon::Shutdown() 
{
    int32_t weaponModelID1 = CWeaponInfo::GetWeaponInfo(m_nType, eWeaponSkill::WEAPSKILL_STD)->m_nModelId1;
    int32_t weaponModelID2 = CWeaponInfo::GetWeaponInfo(m_nType, eWeaponSkill::WEAPSKILL_STD)->m_nModelId2;

    if (weaponModelID1 != -1)
        CModelInfo::ms_modelInfoPtrs[weaponModelID1]->RemoveRef();
    
    if (weaponModelID2 != -1)
        CModelInfo::ms_modelInfoPtrs[weaponModelID2]->RemoveRef();

    m_nType = eWeaponType::WEAPON_UNARMED;
    m_nState = eWeaponState::WEAPONSTATE_READY;
    m_nTotalAmmo = 0;
    m_nAmmoInClip = 0;
    m_nTimeForNextShot = 0;
}

// 0x73A3E0
void CWeapon::AddGunshell(CEntity* creator, CVector& position, const CVector2D& direction, float size) {
    if (!creator || !creator->GetIsOnScreen())
        return;

    // originally squared
    if (DistanceBetweenPoints(TheCamera.GetPosition(), creator->GetPosition()) > 10.0f)
        return;

    CVector velocity(direction.x, direction.y, CGeneral::GetRandomNumberInRange(0.4f, 1.6f));

    FxPrtMult_c fxprt(0.5f, 0.5f, 0.5f, 1.0f, size, 1.0f, 1.0f);

    switch (m_nType) {
    case eWeaponType::WEAPON_SPAS12_SHOTGUN:
    case eWeaponType::WEAPON_SHOTGUN:
        fxprt.SetColor(0.6f, 0.1f, 0.1f);
    }

    g_fx.m_pPrtGunshell->AddParticle(&position, &velocity, 0.0f, &fxprt, -1.0f, 1.2f, 0.6f, 0);
}

// Converted from cdecl void CWeapon::GenerateDamageEvent(CPed *victim,CEntity *creator,eWeaponType weaponType,int32_t damageFactor,ePedPieceTypes pedPiece,int32_t direction) 0x73A530
void CWeapon::GenerateDamageEvent(CPed* victim, CEntity* creator, eWeaponType weaponType, int32_t damageFactor, ePedPieceTypes pedPiece, int32_t direction) {
    plugin::Call<0x73A530, CPed*, CEntity*, eWeaponType, int32_t, ePedPieceTypes, int32_t>(victim, creator, weaponType, damageFactor, pedPiece, direction);
}

// Converted from thiscall bool CWeapon::LaserScopeDot(CVector *outCoord,float *outSize) 0x73A8D0
bool CWeapon::LaserScopeDot(CVector* outCoord, float* outSize) {
    return plugin::CallMethodAndReturn<bool, 0x73A8D0, CWeapon*, CVector*, float*>(this, outCoord, outSize);
}

// 0x73AAC0
bool CWeapon::FireSniper(CPed* creator, CEntity* victim, CVector* target) {
    CCam& activeCam = TheCamera.GetActiveCamera();

    if (FindPlayerPed() == creator) {
        switch (activeCam.m_nMode) {
        case MODE_M16_1STPERSON:
        case MODE_SNIPER:
        case MODE_CAMERA:
        case MODE_ROCKETLAUNCHER:
        case MODE_ROCKETLAUNCHER_HS:
        case MODE_M16_1STPERSON_RUNABOUT:
        case MODE_SNIPER_RUNABOUT:
        case MODE_ROCKETLAUNCHER_RUNABOUT:
        case MODE_ROCKETLAUNCHER_RUNABOUT_HS:
            break;
        default:
            return false;
        }
    }

    // todo: make sense of literals.
    float vecFrontZ_Y = activeCam.m_vecFront.z * 0.145 - activeCam.m_vecFront.y * 0.98940003;

    if (vecFrontZ_Y > 0.99699998)
        CCoronas::MoonSize = (CCoronas::MoonSize + 1) % 8;

    CVector velocity = activeCam.m_vecFront;
    velocity.Normalise();
    velocity *= 16.0f;

    CBulletInfo::AddBullet(creator, m_nType, activeCam.m_vecSource, velocity);

    // recoil effect for players
    if (creator->IsPlayer()) {
        CVector creatorPos = FindPlayerCoors();
        CPad* creatorPad = CPad::GetPad(creator->m_nPedType);

        creatorPad->StartShake_Distance(240, 128, creatorPos.x, creatorPos.y, creatorPos.z);
        CamShakeNoPos(&TheCamera, 0.2f);
    }

    if (creator->m_nType == PED_TYPE_PLAYER_UNUSED)
        CCrime::ReportCrime(CRIME_FIRE_WEAPON, creator, creator);
    else if (creator->m_nType == PED_TYPE_PLAYER_NETWORK && creator->field_460)
        CCrime::ReportCrime(CRIME_FIRE_WEAPON, creator, creator->field_460);

    CVector targetPoint = velocity * 40.0f + activeCam.m_vecSource;
    bool hasNoSound = m_nType == eWeaponType::WEAPON_PISTOL_SILENCED || m_nType == eWeaponType::WEAPON_TEARGAS;
    CEventGroup* eventGroup = GetEventGlobalGroup();

    CEventGunShot gs(creator, activeCam.m_vecSource, targetPoint, hasNoSound);
    eventGroup->Add(static_cast<CEvent*>(&gs), false);

    CEventGunShotWhizzedBy gsw(creator, activeCam.m_vecSource, targetPoint, hasNoSound);
    eventGroup->Add(static_cast<CEvent*>(&gsw), false);

    g_InterestingEvents.Add((CInterestingEvents::EType)22, creator); // todo: enum

    return true;
}

// 0x73AEB0
void CWeapon::Reload(CPed* owner) {
    if (!m_nTotalAmmo)
        return;

    uint32_t ammo = GetWeaponInfo(owner).m_nAmmoClip;
    m_nAmmoInClip = std::min(ammo, m_nTotalAmmo);
}

// Converted from cdecl void FireOneInstantHitRound(CVector *startPoint,CVector *endPoint,int32_t intensity) 0x73AF00
void FireOneInstantHitRound(CVector* startPoint, CVector* endPoint, int32_t intensity) {
    plugin::Call<0x73AF00, CVector*, CVector*, int32_t>(startPoint, endPoint, intensity);
}

bool CWeapon::IsTypeMelee() {
    return CWeaponInfo::GetWeaponInfo(m_nType, eWeaponSkill::WEAPSKILL_STD)->m_nWeaponFire == eWeaponFire::WEAPON_FIRE_MELEE;
}

bool CWeapon::IsType2Handed() {
    switch (m_nType) {
    case eWeaponType::WEAPON_M4: 
    case eWeaponType::WEAPON_AK47:
    case eWeaponType::WEAPON_SPAS12_SHOTGUN:
    case eWeaponType::WEAPON_SHOTGUN:
    case eWeaponType::WEAPON_SNIPERRIFLE:
    case eWeaponType::WEAPON_FLAMETHROWER:
    case eWeaponType::WEAPON_COUNTRYRIFLE:
        return true;
    }

    return false;
}

bool CWeapon::IsTypeProjectile() {
    switch (m_nType) {
    case eWeaponType::WEAPON_GRENADE:
    case eWeaponType::WEAPON_REMOTE_SATCHEL_CHARGE:
    case eWeaponType::WEAPON_TEARGAS:
    case eWeaponType::WEAPON_MOLOTOV:
    case eWeaponType::WEAPON_FREEFALL_BOMB:
        return true;
    }

    return false;
}

bool CWeapon::CanBeUsedFor2Player(eWeaponType weaponType) {
    switch (weaponType) {
    case eWeaponType::WEAPON_CHAINSAW:
    case eWeaponType::WEAPON_SNIPERRIFLE:
    case eWeaponType::WEAPON_RLAUNCHER:
    case eWeaponType::WEAPON_PARACHUTE:
        return false;
    }

    return true;
}

bool CWeapon::HasWeaponAmmoToBeUsed() {
    switch (m_nType) {
    case eWeaponType::WEAPON_UNARMED:
    case eWeaponType::WEAPON_BRASSKNUCKLE:
    case eWeaponType::WEAPON_GOLFCLUB:
    case eWeaponType::WEAPON_NIGHTSTICK:
    case eWeaponType::WEAPON_KNIFE:
    case eWeaponType::WEAPON_BASEBALLBAT:
    case eWeaponType::WEAPON_KATANA:
    case eWeaponType::WEAPON_CHAINSAW:
    case eWeaponType::WEAPON_DILDO1:
    case eWeaponType::WEAPON_DILDO2:
    case eWeaponType::WEAPON_VIBE1:
    case eWeaponType::WEAPON_VIBE2:
    case eWeaponType::WEAPON_FLOWERS:
    case eWeaponType::WEAPON_PARACHUTE:
        return true;
    }

    return m_nTotalAmmo != 0;
}

// 0x73B300
bool CWeapon::ProcessLineOfSight(const CVector& startPoint, const CVector& endPoint, CColPoint& outColPoint, CEntity*& outEntity, eWeaponType weaponType, CEntity* arg5,
                                 bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool arg11, bool doIgnoreCameraCheck) {
    CBirds::HandleGunShot(&startPoint, &endPoint);
    CShadows::GunShotSetsOilOnFire(&startPoint, &endPoint);

    return CWorld::ProcessLineOfSight(startPoint, endPoint, outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, false, doIgnoreCameraCheck, true);
}

// 0x73B360
void CWeapon::StopWeaponEffect() {
    if (!m_pFxSystem || m_nType == eWeaponType::WEAPON_MOLOTOV)
        return;

    m_pFxSystem->Kill();
    m_pFxSystem = nullptr;
}

// 0x73B380
float CWeapon::TargetWeaponRangeMultiplier(CEntity* victim, CEntity* weaponOwner) {
    if (!victim || !weaponOwner)
        return 1.0f;

   switch (victim->m_nType) {
   case eEntityType::ENTITY_TYPE_VEHICLE: {
       if (!victim->AsVehicle()->IsBike())
           return 3.0f;
       break;
   }
   case eEntityType::ENTITY_TYPE_PED: {
       CPed* pedVictim = static_cast<CPed*>(victim);

       if (pedVictim->m_pVehicle && !pedVictim->m_pVehicle->IsBike()) {
           return 3.0f;
       }

       if (CEntity* pAttachedTo = pedVictim->m_pAttachedTo) {
           if (pAttachedTo->IsVehicle() && !static_cast<CVehicle*>(pAttachedTo)->IsBike())
               return 3.0f;
       }
       break;
   }
   }

   if (!weaponOwner->IsPed() || !static_cast<CPed*>(weaponOwner)->IsPlayer())
       return 1.0f;

 }

// 0x73B430
CWeapon::CWeapon(eWeaponType weaponType, int32_t ammo) {
    m_nType = weaponType;
    m_nState = eWeaponState::WEAPONSTATE_READY;
    m_nAmmoInClip = 0;
    m_nTotalAmmo = std::min(ammo, 99999);

    Reload();

    m_nTimeForNextShot = 0;
    field_14 = 0;
    m_pFxSystem = nullptr;
    m_bNoModel = false;
}

CWeapon* CWeapon::Constructor(eWeaponType weaponType, int32_t ammo) {
    this->CWeapon::CWeapon(weaponType, ammo);

    return this;
}

// 0x73B4A0
void CWeapon::Initialise(eWeaponType weaponType, int32_t ammo, CPed* owner) {
    m_nType = weaponType;
    m_nState = eWeaponState::WEAPONSTATE_READY;
    m_nAmmoInClip = 0;
    m_nTotalAmmo = std::min(ammo, 99999);

    Reload(owner);

    m_nTimeForNextShot = 0;

    int32_t model1 = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::WEAPSKILL_STD)->m_nModelId1;
    int32_t model2 = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::WEAPSKILL_STD)->m_nModelId2;

    if (model1 != -1)
        CModelInfo::ms_modelInfoPtrs[model1]->AddRef();

    if (model2 != -1)
        CModelInfo::ms_modelInfoPtrs[model2]->AddRef();

    m_pFxSystem = nullptr;
    m_bNoModel = false;
}

// Converted from thiscall void CWeapon::DoBulletImpact(CEntity *owner,CEntity *victim,CVector *startPoint,CVector *endPoint,CColPoint *colPoint,int32_t) 0x73B550
void CWeapon::DoBulletImpact(CEntity* owner, CEntity* victim, CVector* startPoint, CVector* endPoint, CColPoint* colPoint, int32_t arg5) {
    plugin::CallMethod<0x73B550, CWeapon*, CEntity*, CEntity*, CVector*, CVector*, CColPoint*, int32_t>(this, owner, victim, startPoint, endPoint, colPoint, arg5);
}

// Converted from thiscall bool CWeapon::TakePhotograph(CEntity *owner, CVector *point) 0x73C1F0
bool CWeapon::TakePhotograph(CEntity* owner, CVector* point) {
    return plugin::CallMethodAndReturn<bool, 0x73C1F0, CWeapon*, CEntity*, CVector*>(this, owner, point);
}

// Converted from thiscall void CWeapon::SetUpPelletCol(int32_t numPellets,CEntity *owner,CEntity *victim,CVector &point,CColPoint &colPoint,CMatrix &outMatrix) 0x73C710
void CWeapon::SetUpPelletCol(int32_t numPellets, CEntity* owner, CEntity* victim, CVector& point, CColPoint& colPoint, CMatrix& outMatrix) {
    plugin::CallMethod<0x73C710, CWeapon*, int32_t, CEntity*, CEntity*, CVector&, CColPoint&, CMatrix&>(this, numPellets, owner, victim, point, colPoint, outMatrix);
}

// Converted from thiscall void CWeapon::FireInstantHitFromCar2(CVector startPoint,CVector endPoint,CVehicle *vehicle,CEntity *owner) 0x73CBA0
void CWeapon::FireInstantHitFromCar2(CVector startPoint, CVector endPoint, CVehicle* vehicle, CEntity* owner) {
    plugin::CallMethod<0x73CBA0, CWeapon*, CVector, CVector, CVehicle*, CEntity*>(this, startPoint, endPoint, vehicle, owner);
}

// Converted from cdecl void CWeapon::DoDoomAiming(CEntity *owner,CVector *start,CVector *end) 0x73CDC0
void CWeapon::DoDoomAiming(CEntity* owner, CVector* start, CVector* end) {
    plugin::Call<0x73CDC0, CEntity*, CVector*, CVector*>(owner, start, end);
}

// Converted from cdecl void CWeapon::DoTankDoomAiming(CEntity *vehicle,CEntity *owner,CVector *startPoint,CVector *endPoint) 0x73D1E0
void CWeapon::DoTankDoomAiming(CEntity* vehicle, CEntity* owner, CVector* startPoint, CVector* endPoint) {
    plugin::Call<0x73D1E0, CEntity*, CEntity*, CVector*, CVector*>(vehicle, owner, startPoint, endPoint);
}

// Converted from cdecl void CWeapon::DoDriveByAutoAiming(CEntity *owner,CVehicle *vehicle,CVector *startPoint,CVector *endPoint,bool canAimVehicles) 0x73D720
void CWeapon::DoDriveByAutoAiming(CEntity* owner, CVehicle* vehicle, CVector* startPoint, CVector* endPoint, bool canAimVehicles) {
    plugin::Call<0x73D720, CEntity*, CVehicle*, CVector*, CVector*, bool>(owner, vehicle, startPoint, endPoint, canAimVehicles);
}

// Converted from thiscall void CWeapon::Update(CPed *owner) 0x73DB40
void CWeapon::Update(CPed* owner) {
    plugin::CallMethod<0x73DB40, CWeapon*, CPed*>(this, owner);
}

// 0x73DEF0
bool CWeapon::CanBeUsedFor2Player() {
    return CanBeUsedFor2Player(m_nType);
}

// Converted from cdecl void CWeapon::FindNearestTargetEntityWithScreenCoors(float screenX,float screenY,float range,CVector point,float *outX,float *outY) 0x73E240
void CWeapon::FindNearestTargetEntityWithScreenCoors(float screenX, float screenY, float range, CVector point, float* outX, float* outY) {
    plugin::Call<0x73E240, float, float, float, CVector, float*, float*>(screenX, screenY, range, point, outX, outY);
}

// Converted from cdecl float CWeapon::EvaluateTargetForHeatSeekingMissile(CEntity *entity,CVector &posn,CVector &direction,float distanceMultiplier,bool fromVehicle,CEntity *lastEntity) 0x73E560
float CWeapon::EvaluateTargetForHeatSeekingMissile(CEntity* entity, CVector& posn, CVector& direction, float distanceMultiplier, bool fromVehicle, CEntity* lastEntity) {
    return plugin::CallAndReturn<float, 0x73E560, CEntity*, CVector&, CVector&, float, bool, CEntity*>(entity, posn, direction, distanceMultiplier, fromVehicle, lastEntity);
}

// 0x73E690
void CWeapon::DoWeaponEffect(CVector origin, CVector target) {
    char fxName[32];

    switch (m_nType) {
    case eWeaponType::WEAPON_FLAMETHROWER:
        strcpy(fxName, "flamethrower");
        break;
    case eWeaponType::WEAPON_EXTINGUISHER:
        strcpy(fxName, "extinguisher");
        break;
    case eWeaponType::WEAPON_SPRAYCAN:
        strcpy(fxName, "spraycan");
        break;
    default:
        return StopWeaponEffect();
    }

    RwMatrix* mat = RwMatrixCreate();
    g_fx.CreateMatFromVec(mat, &origin, &target);

    if (m_pFxSystem) {
        m_pFxSystem->SetMatrix(mat);
        m_pFxSystem->SetConstTime(1, 1.0f);
    } else {
        m_pFxSystem = g_fxMan.CreateFxSystem(fxName, &CVector{ 0.0f, 0.0f, 0.0f }, mat, false);

        if (!m_pFxSystem) {
            RwMatrixDestroy(mat);
            return;
        }

        m_pFxSystem->CopyParentMatrix();
        m_pFxSystem->Play();
        m_pFxSystem->SetMustCreatePrts(true);
        m_pFxSystem->SetConstTime(1, 1.0f);
    }

    RwMatrixDestroy(mat);
}

// Converted from thiscall bool CWeapon::FireAreaEffect(CEntity *firingEntity,CVector *origin, CEntity *targetEntity, CVector *target) 0x73E800
bool CWeapon::FireAreaEffect(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target) {
    return plugin::CallMethodAndReturn<bool, 0x73E800, CWeapon*, CEntity*, CVector*, CEntity*, CVector*>(this, firingEntity, origin, targetEntity, target);
}

// Converted from thiscall bool CWeapon::FireInstantHitFromCar(CVehicle *vehicle,bool leftSide,bool rightSide) 0x73EC40
bool CWeapon::FireInstantHitFromCar(CVehicle* vehicle, bool leftSide, bool rightSide) {
    return plugin::CallMethodAndReturn<bool, 0x73EC40, CWeapon*, CVehicle*, bool, bool>(this, vehicle, leftSide, rightSide);
}

// Converted from cdecl bool CWeapon::CheckForShootingVehicleOccupant(CEntity **pCarEntity,CColPoint *colPoint,eWeaponType weaponType,CVector const&origin,CVector const&target) 0x73F480
bool CWeapon::CheckForShootingVehicleOccupant(CEntity** pCarEntity, CColPoint* colPoint, eWeaponType weaponType, CVector const& origin, CVector const& target) {
    return plugin::CallAndReturn<bool, 0x73F480, CEntity**, CColPoint*, eWeaponType, CVector const&, CVector const&>(pCarEntity, colPoint, weaponType, origin, target);
}

// Converted from cdecl CEntity* CWeapon::PickTargetForHeatSeekingMissile(CVector origin,CVector direction,float distanceMultiplier,CEntity *ignoreEntity,bool fromVehicle,CEntity *lastEntity) 0x73F910
CEntity* CWeapon::PickTargetForHeatSeekingMissile(CVector origin, CVector direction, float distanceMultiplier, CEntity* ignoreEntity, bool fromVehicle, CEntity* lastEntity) {
    return plugin::CallAndReturn<CEntity*, 0x73F910, CVector, CVector, float, CEntity*, bool, CEntity*>(origin, direction, distanceMultiplier, ignoreEntity, fromVehicle, lastEntity);
}

// Converted from thiscall void CWeapon::FireFromCar(CVehicle *vehicle,bool leftSide,bool rightSide) 0x73FA20
void CWeapon::FireFromCar(CVehicle* vehicle, bool leftSide, bool rightSide) {
    plugin::CallMethod<0x73FA20, CWeapon*, CVehicle*, bool, bool>(this, vehicle, leftSide, rightSide);
}

// Converted from thiscall bool CWeapon::FireInstantHit(CEntity *firingEntity,CVector *origin, CVector *muzzlePosn, CEntity *targetEntity, CVector *target, CVector *originForDriveBy, bool, bool muzzle) 0x73FB10
bool CWeapon::FireInstantHit(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy, bool arg6, bool muzzle) {
    return plugin::CallMethodAndReturn<bool, 0x73FB10, CWeapon*, CEntity*, CVector*, CVector*, CEntity*, CVector*, CVector*, bool, bool>(this, firingEntity, origin, muzzlePosn, targetEntity, target, originForDriveBy, arg6, muzzle);
}

// Converted from thiscall bool CWeapon::FireProjectile(CEntity *firingEntity,CVector *origin, CEntity *targetEntity, CVector *target,float force) 0x741360
bool CWeapon::FireProjectile(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target, float force) {
    return plugin::CallMethodAndReturn<bool, 0x741360, CWeapon*, CEntity*, CVector*, CEntity*, CVector*, float>(this, firingEntity, origin, targetEntity, target, force);
}

// Converted from thiscall bool CWeapon::FireM16_1stPerson(CEntity *owner) 0x741C00
bool CWeapon::FireM16_1stPerson(CEntity* owner) {
    return plugin::CallMethodAndReturn<bool, 0x741C00, CWeapon*, CEntity*>(this, owner);
}

// Converted from thiscall bool CWeapon::Fire(CEntity *firingEntity,CVector *origin, CVector *muzzlePosn, CEntity *targetEntity, CVector *target, CVector *originForDriveBy) 0x742300
bool CWeapon::Fire(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy) {
    return plugin::CallMethodAndReturn<bool, 0x742300, CWeapon*, CEntity*, CVector*, CVector*, CEntity*, CVector*, CVector*>(this, firingEntity, origin, muzzlePosn, targetEntity,
                                                                                                                             target, originForDriveBy);
}

CWeaponInfo& CWeapon::GetWeaponInfo(CPed* owner) {
    const eWeaponSkill skill = owner ? owner->GetWeaponSkill(m_nType) : eWeaponSkill::WEAPSKILL_STD;

    return *CWeaponInfo::GetWeaponInfo(m_nType, skill);
}
