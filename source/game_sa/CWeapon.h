/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "eWeaponType.h"
#include "FxSystem_c.h"
#include "CVector2D.h"
#include "CColPoint.h"

enum ePedPieceTypes;

enum eWeaponState : uint32_t {
    WEAPONSTATE_READY = 0,
    WEAPONSTATE_FIRING,
    WEAPONSTATE_RELOADING,
    WEAPONSTATE_OUT_OF_AMMO,
    WEAPONSTATE_MELEE_MADECONTACT
};

class CPed;
class CVehicle;
class CColModel;

class CWeapon {
public:
    eWeaponType  m_nType;
    eWeaponState m_nState;
    uint32_t     m_nAmmoInClip;
    uint32_t     m_nTotalAmmo;
    uint32_t     m_nTimeForNextShot;
    uint8_t      field_14;
    uint8_t      m_bNoModel;
    uint8_t      field_16;
    uint8_t      field_17;
    FxSystem_c*  m_pFxSystem; // flamethrower, spraycan, extinguisher particle

    static float&     ms_fExtinguisherAimAngle; // default -0.34907 rad. (-pi/8)
    static bool&      bPhotographHasBeenTaken;
    static bool&      ms_bTakePhoto;
    static CColModel& ms_PelletTestCol;

public:
    CWeapon(plugin::dummy_func_t) {}
    CWeapon(eWeaponType weaponType, int32_t ammo);

    void Shutdown();
    void AddGunshell(CEntity* creator, CVector& position, const CVector2D& direction, float size);
    bool LaserScopeDot(CVector* outCoord, float* outSize);
    bool FireSniper(CPed* creator, CEntity* victim, CVector* target);
    void Reload(CPed* owner = nullptr);
    bool IsTypeMelee();
    bool IsType2Handed();
    bool IsTypeProjectile();
    bool HasWeaponAmmoToBeUsed();
    void StopWeaponEffect();
    void Initialise(eWeaponType weaponType, int32_t ammo, CPed* owner);
    void DoBulletImpact(CEntity* owner, CEntity* victim, CVector* startPoint, CVector* endPoint, CColPoint* colPoint, int32_t arg5);
    bool TakePhotograph(CEntity* owner, CVector* point);
    void SetUpPelletCol(int32_t numPellets, CEntity* owner, CEntity* victim, CVector& point, CColPoint& colPoint, CMatrix& outMatrix);
    void FireInstantHitFromCar2(CVector startPoint, CVector endPoint, CVehicle* vehicle, CEntity* owner);
    void Update(CPed* owner);
    bool CanBeUsedFor2Player();
    // outX and outY will be placed in [-1;1] ranges
    void DoWeaponEffect(CVector origin, CVector target);
    bool FireAreaEffect(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target);
    bool FireInstantHitFromCar(CVehicle* vehicle, bool leftSide, bool rightSide);
    void FireFromCar(CVehicle* vehicle, bool leftSide, bool rightSide);
    bool FireInstantHit(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy, bool arg6, bool muzzle);
    bool FireProjectile(CEntity* firingEntity, CVector* origin, CEntity* targetEntity, CVector* target, float force);
    bool FireM16_1stPerson(CEntity* owner);
    bool Fire(CEntity* firingEntity, CVector* origin, CVector* muzzlePosn, CEntity* targetEntity, CVector* target, CVector* originForDriveBy);

    static void InitialiseWeapons();
    static void ShutdownWeapons();
    static void UpdateWeapons();
    static void GenerateDamageEvent(CPed* victim, CEntity* creator, eWeaponType weaponType, int32_t damageFactor, ePedPieceTypes pedPiece, int32_t direction);
    static bool CanBeUsedFor2Player(eWeaponType weaponType);
    static float TargetWeaponRangeMultiplier(CEntity* victim, CEntity* weaponOwner);
    static void DoDoomAiming(CEntity* owner, CVector* start, CVector* end);
    static void DoTankDoomAiming(CEntity* vehicle, CEntity* owner, CVector* startPoint, CVector* endPoint);
    static void DoDriveByAutoAiming(CEntity* owner, CVehicle* vehicle, CVector* startPoint, CVector* endPoint, bool canAimVehicles);
    static void FindNearestTargetEntityWithScreenCoors(float screenX, float screenY, float range, CVector point, float* outX, float* outY);
    static float EvaluateTargetForHeatSeekingMissile(CEntity* entity, CVector& posn, CVector& direction, float distanceMultiplier, bool fromVehicle, CEntity* lastEntity);
    static bool CheckForShootingVehicleOccupant(CEntity** pCarEntity, CColPoint* colPoint, eWeaponType weaponType, CVector const& origin, CVector const& target);
    static CEntity* PickTargetForHeatSeekingMissile(CVector origin, CVector direction, float distanceMultiplier, CEntity* ignoreEntity, bool fromVehicle, CEntity* lastEntity);
    static bool ProcessLineOfSight(CVector const& startPoint, CVector const& endPoint, CColPoint& outColPoint, CEntity*& outEntity, eWeaponType weaponType, CEntity* arg5, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool arg11, bool doIgnoreCameraCheck);

    inline CWeaponInfo& GetWeaponInfo(CPed* owner = nullptr);

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CWeapon* Constructor(eWeaponType weaponType, int32_t ammo);
};

VALIDATE_SIZE(CWeapon, 0x1C);

extern float &fPlayerAimScale; // default 0.75
extern float &fPlayerAimScaleDist; // default 5.0
extern float &fPlayerAimRotRate; // default 0.0062832
extern float &SHOTGUN_SPREAD_RATE; // default 0.05
extern uint32_t &SHOTGUN_NUM_PELLETS; // default 15
extern uint32_t &SPAS_NUM_PELLETS; // default 4
extern float &PELLET_COL_SCALE_RATIO_MULT; // default 1.3
extern float *fReloadAnimSampleFraction; // default { 0.5, 0.7, 0.75, 0.75, 0.7 }

void FireOneInstantHitRound(CVector* startPoint, CVector* endPoint, int32_t intensity);
