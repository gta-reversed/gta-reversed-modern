/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "eWeaponType.h"
#include "FxSystem_c.h"
#include "CVector2D.h"
#include "CColPoint.h"

enum ePedPieceTypes;

enum eWeaponState : unsigned int
{
    WEAPONSTATE_READY = 0,
    WEAPONSTATE_FIRING,
    WEAPONSTATE_RELOADING,
    WEAPONSTATE_OUT_OF_AMMO,
    WEAPONSTATE_MELEE_MADECONTACT
};

class CPed;
class CVehicle;
class CColModel;

class  CWeapon {
public:
    eWeaponType m_nType;
    eWeaponState m_nState;
	unsigned int m_nAmmoInClip;
	unsigned int m_nTotalAmmo;
	unsigned int m_nTimeForNextShot;
	char field_14;
	char field_15;
	char field_16;
	char field_17;
    FxSystem_c *m_pFxSystem; // flamethrower, spraycan, extinguisher particle

    static float &ms_fExtinguisherAimAngle; // default -0.34907
    static bool &bPhotographHasBeenTaken;
    static bool &ms_bTakePhoto;
    static CColModel &ms_PelletTestCol;

    static void InjectHooks();

    CWeapon(eWeaponType weaponType, int ammo);
    void Shutdown();
    void AddGunshell(CEntity* creator, CVector const& position, CVector2D const& direction, float size);
    bool LaserScopeDot(CVector* outCoord, float* outSize);
    bool FireSniper(CPed* creator, CEntity* victim, CVector* target);
    void Reload(CPed* owner);
    bool IsTypeMelee();
    bool IsType2Handed();
    bool IsTypeProjectile();
    bool HasWeaponAmmoToBeUsed();
    void StopWeaponEffect();
    void Initialise(eWeaponType weaponType, int ammo, CPed* owner);
    void DoBulletImpact(CEntity* owner, CEntity* victim, CVector* startPoint, CVector* endPoint, CColPoint* colPoint, int arg5);
    bool TakePhotograph(CEntity* owner, CVector* point);
    void SetUpPelletCol(int numPellets, CEntity* owner, CEntity* victim, CVector& point, CColPoint& colPoint, CMatrix& outMatrix);
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
    static void GenerateDamageEvent(CPed* victim, CEntity* creator, eWeaponType weaponType, int damageFactor, ePedPieceTypes pedPiece, int direction);
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

    CWeapon(plugin::dummy_func_t) {}
};

VALIDATE_SIZE(CWeapon, 0x1C);

extern float &fPlayerAimScale; // default 0.75
extern float &fPlayerAimScaleDist; // default 5.0
extern float &fPlayerAimRotRate; // default 0.0062832
extern float &SHOTGUN_SPREAD_RATE; // default 0.05
extern unsigned int &SHOTGUN_NUM_PELLETS; // default 15
extern unsigned int &SPAS_NUM_PELLETS; // default 4
extern float &PELLET_COL_SCALE_RATIO_MULT; // default 1.3
extern float *fReloadAnimSampleFraction; // default { 0.5, 0.7, 0.75, 0.75, 0.7 }

void FireOneInstantHitRound(CVector* startPoint, CVector* endPoint, int intensity);
