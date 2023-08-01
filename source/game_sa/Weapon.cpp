/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Weapon.h"

#include "WeaponInfo.h"
#include "CreepingFire.h"
#include "BulletInfo.h"
#include "InterestingEvents.h"
#include "Shadows.h"
#include "Birds.h"

float& CWeapon::ms_fExtinguisherAimAngle = *(float*)0x8D610C;
bool& CWeapon::bPhotographHasBeenTaken = *(bool*)0xC8A7C0;
bool& CWeapon::ms_bTakePhoto = *(bool*)0xC8A7C1;
CColModel& CWeapon::ms_PelletTestCol = *(CColModel*)0xC8A7DC;
float& fPlayerAimScale = *(float*)0x8D6110;
float& fPlayerAimScaleDist = *(float*)0x8D6114;
float& fPlayerAimRotRate = *(float*)0x8D6118;
float& SHOTGUN_SPREAD_RATE = *(float*)0x8D611C;
uint32& SHOTGUN_NUM_PELLETS = *(uint32*)0x8D6120;
uint32& SPAS_NUM_PELLETS = *(uint32*)0x8D6124;
float& PELLET_COL_SCALE_RATIO_MULT = *(float*)0x8D6128;
float* fReloadAnimSampleFraction = (float*)0x8D612C;

void CWeapon::InjectHooks() {
    RH_ScopedClass(CWeapon);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Constructor, 0x73B430);
    RH_ScopedInstall(Shutdown, 0x73A380);
    RH_ScopedInstall(Reload, 0x73AEB0);
    RH_ScopedInstall(IsTypeMelee, 0x73B1C0);
    RH_ScopedInstall(IsType2Handed, 0x73B1E0);
    RH_ScopedInstall(IsTypeProjectile, 0x73B210);
    RH_ScopedInstall(HasWeaponAmmoToBeUsed, 0x73B2A0);
    RH_ScopedOverloadedInstall(CanBeUsedFor2Player, "", 0x73B240, bool (*)(eWeaponType weaponType));
    RH_ScopedInstall(InitialiseWeapons, 0x73A300);
    RH_ScopedInstall(ShutdownWeapons, 0x73A330);
    RH_ScopedInstall(UpdateWeapons, 0x73A360);
    RH_ScopedInstall(AddGunshell, 0x73A3E0);
    RH_ScopedInstall(ProcessLineOfSight, 0x73B300);
    RH_ScopedInstall(StopWeaponEffect, 0x73B360);
    RH_ScopedInstall(TargetWeaponRangeMultiplier, 0x73B380);
    RH_ScopedInstall(Initialise, 0x73B4A0);
    RH_ScopedInstall(DoWeaponEffect, 0x73E690);
    RH_ScopedInstall(FireSniper, 0x73AAC0);
    RH_ScopedInstall(TakePhotograph, 0x73C1F0);
    RH_ScopedInstall(DoDoomAiming, 0x73CDC0);
    RH_ScopedInstall(FireInstantHitFromCar2, 0x73CBA0, { .reversed = false });
}

// 0x73B430
CWeapon::CWeapon(eWeaponType weaponType, int32 ammo) {
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

CWeapon* CWeapon::Constructor(eWeaponType weaponType, int32 ammo) {
    this->CWeapon::CWeapon(weaponType, ammo);
    return this;
}

// 0x73B4A0
void CWeapon::Initialise(eWeaponType weaponType, int32 ammo, CPed* owner) {
    m_nType = weaponType;
    m_nState = eWeaponState::WEAPONSTATE_READY;
    m_nAmmoInClip = 0;
    m_nTotalAmmo = std::min(ammo, 99999);

    Reload(owner);

    m_nTimeForNextShot = 0;

    int32 model1 = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::STD)->m_nModelId1;
    int32 model2 = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::STD)->m_nModelId2;

    if (model1 != -1)
        CModelInfo::GetModelInfo(model1)->AddRef();

    if (model2 != -1)
        CModelInfo::GetModelInfo(model2)->AddRef();

    m_pFxSystem = nullptr;
    m_bNoModel = false;
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

// 0x73A380
void CWeapon::Shutdown() {
    int32 weaponModelID1 = CWeaponInfo::GetWeaponInfo(m_nType, eWeaponSkill::STD)->m_nModelId1;
    int32 weaponModelID2 = CWeaponInfo::GetWeaponInfo(m_nType, eWeaponSkill::STD)->m_nModelId2;

    if (weaponModelID1 != -1)
        CModelInfo::GetModelInfo(weaponModelID1)->RemoveRef();

    if (weaponModelID2 != -1)
        CModelInfo::GetModelInfo(weaponModelID2)->RemoveRef();

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
    if (DistanceBetweenPoints(creator->GetPosition(), TheCamera.GetPosition()) > 10.0f)
        return;

    CVector velocity(direction.x, direction.y, CGeneral::GetRandomNumberInRange(0.4f, 1.6f));

    FxPrtMult_c fxprt(0.5f, 0.5f, 0.5f, 1.0f, size, 1.0f, 1.0f);

    switch (m_nType) {
    case eWeaponType::WEAPON_SPAS12_SHOTGUN:
    case eWeaponType::WEAPON_SHOTGUN:
        fxprt.SetColor(0.6f, 0.1f, 0.1f);
    }

    g_fx.m_GunShell->AddParticle(&position, &velocity, 0.0f, &fxprt, -1.0f, 1.2f, 0.6f, 0);
}

// 0x73A530
void CWeapon::GenerateDamageEvent(CPed* victim, CEntity* creator, eWeaponType weaponType, int32 damageFactor, ePedPieceTypes pedPiece, int32 direction) {
    plugin::Call<0x73A530, CPed*, CEntity*, eWeaponType, int32, ePedPieceTypes, int32>(victim, creator, weaponType, damageFactor, pedPiece, direction);
}

// 0x73A8D0
bool CWeapon::LaserScopeDot(CVector* outCoord, float* outSize) {
    return plugin::CallMethodAndReturn<bool, 0x73A8D0, CWeapon*, CVector*, float*>(this, outCoord, outSize);
}

// 0x73AAC0
bool CWeapon::FireSniper(CPed* shooter, CEntity* victim, CVector* target) {
    const CCam& activeCam = CCamera::GetActiveCamera();

    if (FindPlayerPed() == shooter) {
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
    float vecFrontZ_Y = activeCam.m_vecFront.z * 0.145f - activeCam.m_vecFront.y * 0.98940003f;

    if (vecFrontZ_Y > 0.99699998f)
        CCoronas::MoonSize = (CCoronas::MoonSize + 1) % 8;

    CVector velocity = activeCam.m_vecFront;
    velocity.Normalise();
    velocity *= 16.0f;

    CBulletInfo::AddBullet(shooter, m_nType, activeCam.m_vecSource, velocity);

    // recoil effect for players
    if (shooter->IsPlayer()) {
        CVector creatorPos = FindPlayerCoors();
        CPad* creatorPad = CPad::GetPad(shooter->m_nPedType);

        creatorPad->StartShake_Distance(240, 128, creatorPos);
        CamShakeNoPos(&TheCamera, 0.2f);
    }

    if (shooter->m_nType == ENTITY_TYPE_PED) {
        CCrime::ReportCrime(CRIME_FIRE_WEAPON, shooter, shooter);
    } else if (shooter->m_nType == ENTITY_TYPE_VEHICLE && shooter->field_460) {
        CCrime::ReportCrime(CRIME_FIRE_WEAPON, shooter, shooter->field_460);
    }

    CVector targetPoint = velocity * 40.0f + activeCam.m_vecSource;
    bool hasNoSound = m_nType == eWeaponType::WEAPON_PISTOL_SILENCED || m_nType == eWeaponType::WEAPON_TEARGAS;
    CEventGroup* eventGroup = GetEventGlobalGroup();

    CEventGunShot gs(shooter, activeCam.m_vecSource, targetPoint, hasNoSound);
    eventGroup->Add(static_cast<CEvent*>(&gs), false);

    CEventGunShotWhizzedBy gsw(shooter, activeCam.m_vecSource, targetPoint, hasNoSound);
    eventGroup->Add(static_cast<CEvent*>(&gsw), false);

    g_InterestingEvents.Add(CInterestingEvents::EType::INTERESTING_EVENT_22, shooter);

    return true;
}

// 0x73AEB0
void CWeapon::Reload(CPed* owner) {
    if (!m_nTotalAmmo)
        return;

    uint32 ammo = GetWeaponInfo(owner).m_nAmmoClip;
    m_nAmmoInClip = std::min(ammo, m_nTotalAmmo);
}

// 0x73B1C0
bool CWeapon::IsTypeMelee() {
    auto weaponInfo = CWeaponInfo::GetWeaponInfo(m_nType, eWeaponSkill::STD);
    return weaponInfo->m_nWeaponFire == eWeaponFire::WEAPON_FIRE_MELEE;
}

// 0x73B1E0
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

// 0x73B210
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

// 0x73B240
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

// 0x73B2A0
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
    CShadows::GunShotSetsOilOnFire(startPoint, endPoint);

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
    case ENTITY_TYPE_VEHICLE: {
        if (!victim->AsVehicle()->IsBike())
            return 3.0f;
        break;
    }
    case ENTITY_TYPE_PED: {
        CPed* pedVictim = victim->AsPed();

        if (pedVictim->m_pVehicle && !pedVictim->m_pVehicle->IsBike()) {
            return 3.0f;
        }

        if (CEntity* attachedTo = pedVictim->m_pAttachedTo) {
            if (attachedTo->IsVehicle() && !attachedTo->AsVehicle()->IsBike())
                return 3.0f;
        }
        break;
    }
    }

    if (!weaponOwner->IsPed() || !weaponOwner->AsPed()->IsPlayer())
        return 1.0f;

    switch (CCamera::GetActiveCamera().m_nMode) {
    case MODE_TWOPLAYER_IN_CAR_AND_SHOOTING:
        return 2.0f;
    case MODE_HELICANNON_1STPERSON:
        return 3.0f;
    }

    return 1.0f;
}

// 0x73B550
void CWeapon::DoBulletImpact(CEntity* owner, CEntity* victim, CVector* startPoint, CVector* endPoint, CColPoint* colPoint, int32 arg5) {
    plugin::CallMethod<0x73B550, CWeapon*, CEntity*, CEntity*, CVector*, CVector*, CColPoint*, int32>(this, owner, victim, startPoint, endPoint, colPoint, arg5);
}

/*!
* @addr 0x73C1F0
* @brief Marks all peds and objects that are in range (125 units) and in frame (on the screen - 0.1 relative border) as photographed.
*
* @param owner Camera owner - unused.
* @param point Pos of the camflash effect
*/
bool CWeapon::TakePhotograph(CEntity* owner, CVector* point) {
    UNUSED(owner);

    if (point) {
        if (const auto fx = g_fxMan.CreateFxSystem("camflash", point, nullptr, false)) {
            fx->PlayAndKill();
        }
    }

    if (CCamera::GetActiveCamera().m_nMode != MODE_CAMERA) {
        return false;
    }

    CPickups::PictureTaken();
    bPhotographHasBeenTaken = true;
    ms_bTakePhoto = true;
    CStats::IncrementStat(STAT_PHOTOGRAPHS_TAKEN, 1.0f);

    // NOTSA - Optimization
    const auto& camMat = TheCamera.GetMatrix();
    const auto& camPos = camMat.GetPosition();

    const auto IsPosInRange = [&](const CVector& worldPos) {
        return (camPos - worldPos).SquaredMagnitude() >= sq(125.f); // NOTSA: Using squared mag.
    };

    // Check is in position in camera's frame
    const auto IsPosInCamFrame = [](const CVector& worldPos) {
        CVector pedHeadPos_Screen;
        if (float _w, _h; !CSprite::CalcScreenCoors(worldPos, &pedHeadPos_Screen, &_w, &_h, false, true)) {
            return false;
        }

        // TODO/BUG: Possibly buggy on bigger screens, because the border becomes too big (because of the relative multiplier) maybe?
        if (   (SCREEN_WIDTH * 0.1f >= pedHeadPos_Screen.x || pedHeadPos_Screen.x >= SCREEN_WIDTH * 0.9f)
            || (SCREEN_HEIGHT * 0.1f >= pedHeadPos_Screen.y || pedHeadPos_Screen.y >= SCREEN_HEIGHT * 0.9f)
        ) {
            return false;
        }

        return true;
    };

    const auto CheckIsLOSBlocked = [&, camFwd = camMat.GetForward()](const CVector& target, CEntity* ignore) {
        CColPoint _cp; // Unused
        CEntity* hitEntity{};
        if (!CWorld::ProcessLineOfSight(
            camPos + camFwd * 2.f,
            target,
            _cp,
            hitEntity,
            true,
            true,
            true,
            true,
            true,
            true,
            false,
            false
        ) || hitEntity == ignore) { // TODO: Here we could set CWorld::pIgnoreEntity to `&ped`, instead of this check.
            return false;
        }
        return true;
    };

    for (auto& ped : GetPedPool()->GetAllValid()) {
        if (IsPosInRange(ped.GetPosition())) {
            continue;
        }

        const auto pedHeadPos = ped.GetBonePosition(BONE_HEAD);

        if (!IsPosInCamFrame(pedHeadPos)) {
            continue;
        }

        if (!CheckIsLOSBlocked(
            pedHeadPos + Normalized(camPos - pedHeadPos) * 1.5f, // Point from ped's head towards camera
            &ped
        )) {
            ped.bHasBeenPhotographed = true;
        }
    }

    for (auto& obj : GetObjectPool()->GetAllValid()) {
        const auto& objPos = obj.GetPosition();

        if (!IsPosInRange(objPos) || !IsPosInCamFrame(objPos)) {
            continue;
        }

        if (!CheckIsLOSBlocked(objPos, &obj)) {
            obj.objectFlags.bIsPhotographed = true;
        }
    }

    return true;
}

// 0x73C710
void CWeapon::SetUpPelletCol(int32 numPellets, CEntity* owner, CEntity* victim, CVector& point, CColPoint& colPoint, CMatrix& outMatrix) {
    plugin::CallMethod<0x73C710, CWeapon*, int32, CEntity*, CEntity*, CVector&, CColPoint&, CMatrix&>(this, numPellets, owner, victim, point, colPoint, outMatrix);
}

// 0x73CBA0
void CWeapon::FireInstantHitFromCar2(CVector startPoint, CVector endPoint, CVehicle* vehicle, CEntity* owner) {
    return plugin::CallMethod<0x73CBA0, CWeapon*, CVector, CVector, CVehicle*, CEntity*>(this, startPoint, endPoint, vehicle, owner);

    const auto player = FindPlayerPed();
    CWeaponInfo::GetWeaponInfo(m_nType, eWeaponSkill::STD);
    CCrime::ReportCrime(CRIME_FIRE_WEAPON, player, player);

    CEntity* entity;
    if (owner) {
        entity = owner;
    } else {
        entity = vehicle;
    }
    CEventGunShot event(entity, startPoint, endPoint, m_nType == WEAPON_PISTOL_SILENCED || m_nType == WEAPON_TEARGAS);
    GetEventGlobalGroup()->Add(&event);
    g_InterestingEvents.Add(CInterestingEvents::EType::INTERESTING_EVENT_22, owner);

    CVector direction{};
    CPointLights::AddLight(PLTYPE_POINTLIGHT, startPoint, direction, 3.0f, 0.25f, 0.22f, 0.0f, 0, false, nullptr);
    CWorld::bIncludeBikers = true;
    CWorld::pIgnoreEntity = vehicle;
    CBirds::HandleGunShot(&startPoint, &endPoint);
    CShadows::GunShotSetsOilOnFire(startPoint, endPoint);

    CEntity* victim{};
    CColPoint outColPoint{};
    CWorld::ProcessLineOfSight(&startPoint, &endPoint, outColPoint, victim, true, true, true, true, true, false, false, true);
    CWorld::ResetLineTestOptions();
    DoBulletImpact(owner, victim, &startPoint, &endPoint, &outColPoint, 0);
}

/*!
* @addr 0x73CDC0
* @brief Find closest entity in range that is visible to `owner` (Eg.: Is in [-PI/8, PI/8] angle) and modify `end->z` to be pointing at it. idk..
*
* @param end out Z axis is modified
*/
void CWeapon::DoDoomAiming(CEntity* owner, CVector* start, CVector* end) {
    int16 inRangeCount{};
    std::array<CEntity*, 16> objInRange{};
    CWorld::FindObjectsInRange(*start, (*start - *end).Magnitude(), true, &inRangeCount, (int16)objInRange.size(), objInRange.data(), false, true, true, false, false);

    CEntity* closestEntity{};
    float    closestDist{ 10'000 };
    for (auto entity : std::span{ objInRange.begin(), (size_t)inRangeCount }) {
        if (entity == owner || owner->AsPed()->CanSeeEntity(entity, PI / 8.f)) { // todo: add check owner->IsPed() NOTSA
            continue;
        }

        switch (entity->GetStatus()) {
        case STATUS_TRAIN_MOVING:
        case STATUS_TRAIN_NOT_MOVING:
        case STATUS_WRECKED:
            continue;
        }

        const auto dir = entity->GetPosition() - owner->GetPosition();
        if (const auto dist2D = dir.Magnitude2D(); std::abs(dir.z) * 1.5f < dist2D) {
            const auto dist3D = std::hypot(dist2D, dir.z);
            if (dist3D < closestDist) {
                closestEntity = entity;
                closestDist = dist3D;
            }
        }
    }

    if (closestDist < 9000.f) {
        // assert(closestEntity); // We should have one, because by default `closestDist` is FLT_MAX (originally 10 000)

        {
            CEntity*  _hitEntity{}; // Unused
            CColPoint _cp;          // Unused
            if (CWorld::ProcessLineOfSight(*start, closestEntity->GetPosition(), _cp, _hitEntity, true, false, false, false, false, false, false, true)) {
                return;
            }
        }

        float targetZ = closestEntity->GetPosition().z + 0.3f;
        if (closestEntity->IsPed() && closestEntity->AsPed()->bIsDucking) {
            targetZ -= 0.8f; // Effectively only -0.5 relative to the original Z
        }
        const auto t = (*start - *end).Magnitude2D() / (*start - closestEntity->GetPosition()).Magnitude2D();
        end->z = start->z + (targetZ - start->z) * t; // Re-ordered a little
    }
}

// 0x73D1E0
void CWeapon::DoTankDoomAiming(CEntity* vehicle, CEntity* owner, CVector* startPoint, CVector* endPoint) {
    plugin::Call<0x73D1E0, CEntity*, CEntity*, CVector*, CVector*>(vehicle, owner, startPoint, endPoint);
}

// 0x73D720
void CWeapon::DoDriveByAutoAiming(CEntity* owner, CVehicle* vehicle, CVector* startPoint, CVector* endPoint, bool canAimVehicles) {
    plugin::Call<0x73D720, CEntity*, CVehicle*, CVector*, CVector*, bool>(owner, vehicle, startPoint, endPoint, canAimVehicles);
}

// 0x73DB40
void CWeapon::Update(CPed* owner) {
    plugin::CallMethod<0x73DB40, CWeapon*, CPed*>(this, owner);
}

// 0x73A360
void CWeapon::UpdateWeapons() {
    ZoneScoped;

    CShotInfo::Update();
    CExplosion::Update();
    CProjectileInfo::Update();
    CBulletInfo::Update();
}

// 0x73DEF0
bool CWeapon::CanBeUsedFor2Player() {
    return CanBeUsedFor2Player(m_nType);
}

// 0x73E240
void CWeapon::FindNearestTargetEntityWithScreenCoors(float screenX, float screenY, float range, CVector point, float* outX, float* outY) {
    plugin::Call<0x73E240, float, float, float, CVector, float*, float*>(screenX, screenY, range, point, outX, outY);
}

// 0x73E560
float CWeapon::EvaluateTargetForHeatSeekingMissile(CEntity* entity, CVector& posn, CVector& direction, float distanceMultiplier, bool fromVehicle, CEntity* lastEntity) {
    return plugin::CallAndReturn<float, 0x73E560, CEntity*, CVector&, CVector&, float, bool, CEntity*>(entity, posn, direction, distanceMultiplier, fromVehicle, lastEntity);
}

// 0x73E690
void CWeapon::DoWeaponEffect(CVector origin, CVector target) {
    char fxName[32]{};
    switch (m_nType) {
    case eWeaponType::WEAPON_FLAMETHROWER:
        strcpy_s(fxName, "flamethrower");
        break;
    case eWeaponType::WEAPON_EXTINGUISHER:
        strcpy_s(fxName, "extinguisher");
        break;
    case eWeaponType::WEAPON_SPRAYCAN:
        strcpy_s(fxName, "spraycan");
        break;
    default:
        return StopWeaponEffect();
    }

    RwMatrix* mat = RwMatrixCreate();
    g_fx.CreateMatFromVec(mat, &origin, &target);

    if (m_pFxSystem) {
        m_pFxSystem->SetMatrix(mat);
    } else {
        CVector posn{};
        m_pFxSystem = g_fxMan.CreateFxSystem(fxName, &posn, mat, false);

        if (!m_pFxSystem) {
            RwMatrixDestroy(mat);
            return;
        }

        m_pFxSystem->CopyParentMatrix();
        m_pFxSystem->Play();
        m_pFxSystem->SetMustCreatePrts(true);
    }
    m_pFxSystem->SetConstTime(1, 1.0f);

    RwMatrixDestroy(mat);
}

// 0x73E800
bool CWeapon::FireAreaEffect(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target) {
    return plugin::CallMethodAndReturn<bool, 0x73E800, CWeapon*, CEntity*, CVector*, CEntity*, CVector*>(this, firingEntity, origin, targetEntity, target);
}

// 0x73EC40
bool CWeapon::FireInstantHitFromCar(CVehicle* vehicle, bool leftSide, bool rightSide) {
    return plugin::CallMethodAndReturn<bool, 0x73EC40, CWeapon*, CVehicle*, bool, bool>(this, vehicle, leftSide, rightSide);
}

// 0x73F480
bool CWeapon::CheckForShootingVehicleOccupant(CEntity** pCarEntity, CColPoint* colPoint, eWeaponType weaponType, const CVector& origin, const CVector& target) {
    return plugin::CallAndReturn<bool, 0x73F480, CEntity**, CColPoint*, eWeaponType, const CVector&, const CVector&>(pCarEntity, colPoint, weaponType, origin, target);
}

// 0x73F910
CEntity* CWeapon::PickTargetForHeatSeekingMissile(CVector origin, CVector direction, float distanceMultiplier, CEntity* ignoreEntity, bool fromVehicle, CEntity* lastEntity) {
    return plugin::CallAndReturn<CEntity*, 0x73F910, CVector, CVector, float, CEntity*, bool, CEntity*>(origin, direction, distanceMultiplier, ignoreEntity, fromVehicle, lastEntity);
}

// 0x73FA20
void CWeapon::FireFromCar(CVehicle* vehicle, bool leftSide, bool rightSide) {
    plugin::CallMethod<0x73FA20, CWeapon*, CVehicle*, bool, bool>(this, vehicle, leftSide, rightSide);
}

// 0x73FB10
bool CWeapon::FireInstantHit(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy, bool arg6, bool muzzle) {
    return plugin::CallMethodAndReturn<bool, 0x73FB10, CWeapon*, CEntity*, CVector*, CVector*, CEntity*, CVector*, CVector*, bool, bool>(this, firingEntity, origin, muzzlePosn, targetEntity, target, originForDriveBy, arg6, muzzle);
}

// 0x741360
bool CWeapon::FireProjectile(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target, float force) {
    return plugin::CallMethodAndReturn<bool, 0x741360, CWeapon*, CEntity*, CVector*, CEntity*, CVector*, float>(this, firingEntity, origin, targetEntity, target, force);
}

// 0x741C00
bool CWeapon::FireM16_1stPerson(CEntity* owner) {
    return plugin::CallMethodAndReturn<bool, 0x741C00, CWeapon*, CEntity*>(this, owner);
}

// 0x742300
bool CWeapon::Fire(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy) {
    return plugin::CallMethodAndReturn<bool, 0x742300, CWeapon*, CEntity*, CVector*, CVector*, CEntity*, CVector*, CVector*>(this, firingEntity, origin, muzzlePosn, targetEntity,
                                                                                                                             target, originForDriveBy);
}

CWeaponInfo& CWeapon::GetWeaponInfo(CPed* owner) const {
    return GetWeaponInfo(owner ? owner->GetWeaponSkill(m_nType) : eWeaponSkill::STD);
}

CWeaponInfo& CWeapon::GetWeaponInfo(eWeaponSkill skill) const {
    return *CWeaponInfo::GetWeaponInfo(m_nType, skill);
}

// 0x73AF00
void FireOneInstantHitRound(CVector* startPoint, CVector* endPoint, int32 intensity) {
    plugin::Call<0x73AF00, CVector*, CVector*, int32>(startPoint, endPoint, intensity);
}
