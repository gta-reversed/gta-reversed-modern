/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eWeaponType.h"
#include "Vector2D.h"
#include "eWeaponSkill.h"

class FxSystem_c;
class CColPoint;

enum ePedPieceTypes;

enum eWeaponState : uint32 {
    WEAPONSTATE_READY = 0,
    WEAPONSTATE_FIRING,
    WEAPONSTATE_RELOADING,
    WEAPONSTATE_OUT_OF_AMMO,
    WEAPONSTATE_MELEE_MADECONTACT
};

/* Source: https://wiki.multitheftauto.com/wiki/GetPedWeaponSlot */
enum class eWeaponSlot : uint32 {
    UNARMED,
    MELEE,
    HANDGUN,
    SHOTGUN,
    SMG,        // Used for drive-by's
    RIFLE,
    SNIPER,
    HEAVY,
    THROWN,
    SPECIAL,
    GIFT,
    PARACHUTE,
    DETONATOR,
};
constexpr auto NUM_WEAPON_SLOTS = static_cast<size_t>(eWeaponSlot::DETONATOR) + 1u;

class CPed;
class CVehicle;
class CColModel;
class CWeaponInfo;

class CWeapon {
public:
    eWeaponType  m_nType;
    eWeaponState m_nState;
    uint32       m_nAmmoInClip;
    uint32       m_nTotalAmmo;
    uint32       m_nTimeForNextShot;
    uint8        field_14;
    bool         m_bNoModel; // Used in case of goggles (infrared/nightvision) : When they're put on the weapon model isn't and shouldn't be loaded.
    uint8        field_16;
    uint8        field_17;
    FxSystem_c*  m_pFxSystem; // flamethrower, spraycan, extinguisher particle

    static float&     ms_fExtinguisherAimAngle; // default -0.34907 rad. (-pi/8)
    static bool&      bPhotographHasBeenTaken;
    static bool&      ms_bTakePhoto;
    static CColModel& ms_PelletTestCol;

public:
    CWeapon() { // 0x441E00
        field_14    = 0;
        m_bNoModel  = false;
        m_pFxSystem = nullptr;
    };
    CWeapon(eWeaponType weaponType, int32 ammo);
    CWeapon(const CWeapon&) = delete;

    void Initialise(eWeaponType weaponType, int32 ammo, CPed* owner);
    static void InitialiseWeapons();
    void Shutdown();
    static void ShutdownWeapons();

    void AddGunshell(CEntity* creator, CVector& position, const CVector2D& direction, float size);
    bool LaserScopeDot(CVector* outCoord, float* outSize);
    bool FireSniper(CPed* shooter, CEntity* victim, CVector* target);
    void Reload(CPed* owner = nullptr);

    bool IsTypeMelee();
    bool IsType2Handed();
    bool IsTypeProjectile();

    bool HasWeaponAmmoToBeUsed();
    void StopWeaponEffect();
    void DoBulletImpact(CEntity* owner, CEntity* victim, CVector* startPoint, CVector* endPoint, CColPoint* colPoint, int32 arg5);
    bool TakePhotograph(CEntity* owner, CVector* point);
    void SetUpPelletCol(int32 numPellets, CEntity* owner, CEntity* victim, CVector& point, CColPoint& colPoint, CMatrix& outMatrix);
    bool CanBeUsedFor2Player();

    // outX and outY will be placed in [-1;1] ranges
    void DoWeaponEffect(CVector origin, CVector target);

    bool FireAreaEffect(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target);
    bool FireInstantHitFromCar(CVehicle* vehicle, bool leftSide, bool rightSide);
    void FireFromCar(CVehicle* vehicle, bool leftSide, bool rightSide);
    void FireInstantHitFromCar2(CVector startPoint, CVector endPoint, CVehicle* vehicle, CEntity* owner);
    bool FireInstantHit(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity = nullptr, CVector* target = nullptr, CVector* originForDriveBy = nullptr, bool arg6 = false, bool muzzle = false);
    bool FireProjectile(CEntity* firingEntity, CVector* origin, CEntity* targetEntity = nullptr, CVector* target = nullptr, float force = 0.f);
    bool FireM16_1stPerson(CEntity* owner);
    bool Fire(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy);

    void Update(CPed* owner);
    static void UpdateWeapons();

    static bool GenerateDamageEvent(CPed* victim, CEntity* creator, eWeaponType weaponType, int32 damageFactor, ePedPieceTypes pedPiece, uint8 direction);
    static bool CanBeUsedFor2Player(eWeaponType weaponType);
    static float TargetWeaponRangeMultiplier(CEntity* victim, CEntity* weaponOwner);
    static void DoDoomAiming(CEntity* owner, CVector* start, CVector* end);
    static void DoTankDoomAiming(CEntity* vehicle, CEntity* owner, CVector* startPoint, CVector* endPoint);
    static void DoDriveByAutoAiming(CEntity* owner, CVehicle* vehicle, CVector* startPoint, CVector* endPoint, bool canAimVehicles);
    static void FindNearestTargetEntityWithScreenCoors(float screenX, float screenY, float range, CVector point, float* outX, float* outY);
    static float EvaluateTargetForHeatSeekingMissile(CEntity* entity, CVector& posn, CVector& direction, float distanceMultiplier, bool fromVehicle, CEntity* lastEntity);
    static bool CheckForShootingVehicleOccupant(CEntity** pCarEntity, CColPoint* colPoint, eWeaponType weaponType, const CVector& origin, const CVector& target);
    static CEntity* PickTargetForHeatSeekingMissile(CVector origin, CVector direction, float distanceMultiplier, CEntity* ignoreEntity, bool fromVehicle, CEntity* lastEntity);
    static bool ProcessLineOfSight(const CVector& startPoint, const CVector& endPoint, CColPoint& outColPoint, CEntity*& outEntity, eWeaponType weaponType, CEntity* arg5, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool arg11, bool doIgnoreCameraCheck);

    CWeaponInfo& GetWeaponInfo(CPed* owner = nullptr) const;
    CWeaponInfo& GetWeaponInfo(eWeaponSkill skill) const;

private:
    void KillFx(); // NOTSA

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CWeapon* Constructor(eWeaponType weaponType, int32 ammo);
};

VALIDATE_SIZE(CWeapon, 0x1C);

extern float &fPlayerAimScale; // default 0.75
extern float &fPlayerAimScaleDist; // default 5.0
extern float &fPlayerAimRotRate; // default 0.0062832
extern float &SHOTGUN_SPREAD_RATE; // default 0.05
extern uint32 &SHOTGUN_NUM_PELLETS; // default 15
extern uint32 &SPAS_NUM_PELLETS; // default 4
extern float &PELLET_COL_SCALE_RATIO_MULT; // default 1.3
extern float *fReloadAnimSampleFraction; // default { 0.5, 0.7, 0.75, 0.75, 0.7 }

void FireOneInstantHitRound(CVector* startPoint, CVector* endPoint, int32 intensity);
