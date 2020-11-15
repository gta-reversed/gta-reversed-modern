/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CPhysical.h"
#include "CAEVehicleAudioEntity.h"
#include "tHandlingData.h"
#include "tFlyingHandlingData.h"
#include "CAutoPilot.h"
#include "eVehicleHandlingFlags.h"
#include "CStoredCollPoly.h"
#include "CVehicleModelInfo.h"
#include "tBoatHandlingData.h"
#include "CPtrList.h"
#include "CRideAnimData.h"
#include "CDamageManager.h"
#include "FxSystem_c.h"
#include "CFire.h"

/*  Thanks to MTA team for https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CVehicleSA.h */

enum eCarWeapon {
    CAR_WEAPON_NOT_USED,
    CAR_WEAPON_HEAVY_GUN,
    CAR_WEAPON_FREEFALL_BOMB,
    CAR_WEAPON_LOCK_ON_ROCKET,
    CAR_WEAPON_DOUBLE_ROCKET
};

enum eCarLock {
    CARLOCK_NOT_USED,
    CARLOCK_UNLOCKED,
    CARLOCK_LOCKED,
    CARLOCK_LOCKOUT_PLAYER_ONLY,
    CARLOCK_LOCKED_PLAYER_INSIDE,
    CARLOCK_COP_CAR,
    CARLOCK_FORCE_SHUT_DOORS,
    CARLOCK_SKIP_SHUT_DOORS
};

enum eVehicleType {
    VEHICLE_NONE = -1,
    VEHICLE_AUTOMOBILE = 0,
    VEHICLE_MTRUCK,
    VEHICLE_QUAD,
    VEHICLE_HELI,
    VEHICLE_PLANE,
    VEHICLE_BOAT,
    VEHICLE_TRAIN,
    VEHICLE_FHELI,
    VEHICLE_FPLANE,
    VEHICLE_BIKE,
    VEHICLE_BMX,
    VEHICLE_TRAILER
};

enum eVehicleApperance {
    VEHICLE_APPEARANCE_AUTOMOBILE = 1,
    VEHICLE_APPEARANCE_BIKE,
    VEHICLE_APPEARANCE_HELI,
    VEHICLE_APPEARANCE_BOAT,
    VEHICLE_APPEARANCE_PLANE,
};

enum eVehicleLightsFlags {
    VEHICLE_LIGHTS_TWIN = 1,
    VEHICLE_LIGHTS_IGNORE_DAMAGE = 4,
    VEHICLE_LIGHTS_DISABLE_FRONT = 16,
    VEHICLE_LIGHTS_DISABLE_REAR = 32
};

enum eVehicleCreatedBy {
    RANDOM_VEHICLE = 1,
    MISSION_VEHICLE = 2,
    PARKED_VEHICLE = 3,
    PERMANENT_VEHICLE = 4
};

enum eBombState {
    BOMB_TIMED_NOT_ACTIVATED = 1,
    BOMB_IGNITION = 2,
    BOMB_STICKY = 3,
    BOMB_TIMED_ACTIVATED = 4,
    BOMB_IGNITION_ACTIVATED = 5
};

enum eCarPiece
{
    CAR_PIECE_DEFAULT = 0,
    CAR_PIECE_BONNET,
    CAR_PIECE_BOOT,
    CAR_PIECE_BUMP_FRONT,
    CAR_PIECE_BUMP_REAR,
    CAR_PIECE_DOOR_LF,
    CAR_PIECE_DOOR_RF,
    CAR_PIECE_DOOR_LR,
    CAR_PIECE_DOOR_RR,
    CAR_PIECE_WING_LF,
    CAR_PIECE_WING_RF,
    CAR_PIECE_WING_LR,
    CAR_PIECE_WING_RR,
    CAR_PIECE_WHEEL_LF, // front wheel for 2 wheel bike
    CAR_PIECE_WHEEL_RF,
    CAR_PIECE_WHEEL_RL, // rear wheel for 2 wheel bike
    CAR_PIECE_WHEEL_RR,
    CAR_PIECE_WINDSCREEN = 19,
};

#if 0
enum eOrdnanceType;
enum eFlightModel;
enum eDoors;
enum eBikeWheelSpecial;
#else
typedef int eOrdnanceType;
typedef int eFlightModel;
typedef int eBikeWheelSpecial;
#endif

class CWeapon;
class CPed;
typedef int tWheelState;


class CVehicle : public CPhysical {
protected:
    CVehicle(plugin::dummy_func_t) : CPhysical(plugin::dummy) {}
public:
    CAEVehicleAudioEntity      m_vehicleAudio;
    tHandlingData             *m_pHandlingData;
    tFlyingHandlingData       *m_pFlyingHandlingData;
    union{
        eVehicleHandlingFlags  m_nHandlingFlagsIntValue;
        struct {
            unsigned int b1gBoost : 1;
            unsigned int b2gBoost : 1;
            unsigned int bNpcAntiRoll : 1;
            unsigned int bNpcNeutralHandl : 1;
            unsigned int bNoHandbrake : 1;
            unsigned int bSteerRearwheels : 1;
            unsigned int bHbRearwheelSteer : 1;
            unsigned int bAltSteerOpt : 1;
            unsigned int bWheelFNarrow2 : 1;
            unsigned int bWheelFNarrow : 1;
            unsigned int bWheelFWide : 1;
            unsigned int bWheelFWide2 : 1;
            unsigned int bWheelRNarrow2 : 1;
            unsigned int bWheelRNarrow : 1;
            unsigned int bWheelRWide : 1;
            unsigned int bWheelRWide2 : 1;
            unsigned int bHydraulicGeom : 1;
            unsigned int bHydraulicInst : 1;
            unsigned int bHydraulicNone : 1;
            unsigned int bNosInst : 1;
            unsigned int bOffroadAbility : 1;
            unsigned int bOffroadAbility2 : 1;
            unsigned int bHalogenLights : 1;
            unsigned int bProcRearwheelFirst : 1;
            unsigned int bUseMaxspLimit : 1;
            unsigned int bLowRider : 1;
            unsigned int bStreetRacer : 1;
            unsigned int bSwingingChassis : 1;
        } handlingFlags;
    };
    CAutoPilot                 m_autoPilot;
    union {
        struct {
            unsigned int bIsLawEnforcer : 1; // Is this guy chasing the player at the moment
            unsigned int bIsAmbulanceOnDuty : 1; // Ambulance trying to get to an accident
            unsigned int bIsFireTruckOnDuty : 1; // Firetruck trying to get to a fire
            unsigned int bIsLocked : 1; // Is this guy locked by the script (cannot be removed)
            unsigned int bEngineOn : 1; // For sound purposes. Parked cars have their engines switched off (so do destroyed cars)
            unsigned int bIsHandbrakeOn : 1; // How's the handbrake doing ?
            unsigned int bLightsOn : 1; // Are the lights switched on ?
            unsigned int bFreebies : 1; // Any freebies left in this vehicle ?

            unsigned int bIsVan : 1; // Is this vehicle a van (doors at back of vehicle)
            unsigned int bIsBus : 1; // Is this vehicle a bus
            unsigned int bIsBig : 1; // Is this vehicle a bus
            unsigned int bLowVehicle : 1; // Need this for sporty type cars to use low getting-in/out anims
            unsigned int bComedyControls : 1; // Will make the car hard to control (hopefully in a funny way)
            unsigned int bWarnedPeds : 1; // Has scan and warn peds of danger been processed?
            unsigned int bCraneMessageDone : 1; // A crane message has been printed for this car allready
            unsigned int bTakeLessDamage : 1; // This vehicle is stronger (takes about 1/4 of damage)

            unsigned int bIsDamaged : 1; // This vehicle has been damaged and is displaying all its components
            unsigned int bHasBeenOwnedByPlayer : 1;// To work out whether stealing it is a crime
            unsigned int bFadeOut : 1; // Fade vehicle out
            unsigned int bIsBeingCarJacked : 1; // Fade vehicle out
            unsigned int bCreateRoadBlockPeds : 1;// If this vehicle gets close enough we will create peds (coppers or gang members) round it
            unsigned int bCanBeDamaged : 1; // Set to FALSE during cut scenes to avoid explosions
            unsigned int bOccupantsHaveBeenGenerated : 1; // Is true if the occupants have already been generated. (Shouldn't happen again)
            unsigned int bGunSwitchedOff : 1; // Level designers can use this to switch off guns on boats

            unsigned int bVehicleColProcessed : 1;// Has ProcessEntityCollision been processed for this car?
            unsigned int bIsCarParkVehicle : 1; // Car has been created using the special CAR_PARK script command
            unsigned int bHasAlreadyBeenRecorded : 1; // Used for replays
            unsigned int bPartOfConvoy : 1;
            unsigned int bHeliMinimumTilt : 1; // This heli should have almost no tilt really
            unsigned int bAudioChangingGear : 1; // sounds like vehicle is changing gear
            unsigned int bIsDrowning : 1; // is vehicle occupants taking damage in water (i.e. vehicle is dead in water)
            unsigned int bTyresDontBurst : 1; // If this is set the tyres are invincible

            unsigned int bCreatedAsPoliceVehicle : 1;// True if this guy was created as a police vehicle (enforcer, policecar, miamivice car etc)
            unsigned int bRestingOnPhysical : 1; // Dont go static cause car is sitting on a physical object that might get removed
            unsigned int bParking : 1;
            unsigned int bCanPark : 1;
            unsigned int bFireGun : 1; // Does the ai of this vehicle want to fire it's gun?
            unsigned int bDriverLastFrame : 1; // Was there a driver present last frame ?
            unsigned int bNeverUseSmallerRemovalRange : 1;// Some vehicles (like planes) we don't want to remove just behind the camera.
            unsigned int bIsRCVehicle : 1; // Is this a remote controlled (small) vehicle. True whether the player or AI controls it.

            unsigned int bAlwaysSkidMarks : 1; // This vehicle leaves skidmarks regardless of the wheels' states.
            unsigned int bEngineBroken : 1; // Engine doesn't work. Player can get in but the vehicle won't drive
            unsigned int bVehicleCanBeTargetted : 1;// The ped driving this vehicle can be targetted, (for Torenos plane mission)
            unsigned int bPartOfAttackWave : 1; // This car is used in an attack during a gang war
            unsigned int bWinchCanPickMeUp : 1; // This car cannot be picked up by any ropes.
            unsigned int bImpounded : 1; // Has this vehicle been in a police impounding garage
            unsigned int bVehicleCanBeTargettedByHS : 1;// Heat seeking missiles will not target this vehicle.
            unsigned int bSirenOrAlarm : 1; // Set to TRUE if siren or alarm active, else FALSE

            unsigned int bHasGangLeaningOn : 1;
            unsigned int bGangMembersForRoadBlock : 1;// Will generate gang members if NumPedsForRoadBlock > 0
            unsigned int bDoesProvideCover : 1; // If this is false this particular vehicle can not be used to take cover behind.
            unsigned int bMadDriver : 1; // This vehicle is driving like a lunatic
            unsigned int bUpgradedStereo : 1; // This vehicle has an upgraded stereo
            unsigned int bConsideredByPlayer : 1; // This vehicle is considered by the player to enter
            unsigned int bPetrolTankIsWeakPoint : 1;// If false shootong the petrol tank will NOT Blow up the car
            unsigned int bDisableParticles : 1; // Disable particles from this car. Used in garage.

            unsigned int bHasBeenResprayed : 1; // Has been resprayed in a respray garage. Reset after it has been checked.
            unsigned int bUseCarCheats : 1; // If this is true will set the car cheat stuff up in ProcessControl()
            unsigned int bDontSetColourWhenRemapping : 1;// If the texture gets remapped we don't want to change the colour with it.
            unsigned int bUsedForReplay : 1; // This car is controlled by replay and should be removed when replay is done.
        } vehicleFlags;
        unsigned int m_nVehicleUpperFlags;
        unsigned int m_nVehicleLowerFlags;
    };
    unsigned int m_nCreationTime;
    unsigned char  m_nPrimaryColor;
    unsigned char  m_nSecondaryColor;
    unsigned char  m_nTertiaryColor;
    unsigned char  m_nQuaternaryColor;
    char   m_anExtras[2];
    short  m_anUpgrades[15];
    float    m_fWheelScale;
    short m_nAlarmState;
    short  m_nForcedRandomRouteSeed; // if this is non-zero the random wander gets deterministic
    CPed *m_pDriver;
    CPed *m_apPassengers[8];
    unsigned char  m_nNumPassengers;
    unsigned char  m_nNumGettingIn;
    unsigned char  m_nGettingInFlags;
    unsigned char  m_nGettingOutFlags;
    unsigned char  m_nMaxPassengers;
    unsigned char  m_nWindowsOpenFlags; // initialised, but not used?
    unsigned char  m_nNitroBoosts;
    unsigned char  m_nSpecialColModel;
    CEntity *m_pEntityWeAreOn; // we get it from CWorld::ProcessVerticalLine or ProcessEntityCollision, it's entity under us, 
                               //only static entities (buildings or roads)
    CFire *m_pFire;
    float  m_fSteerAngle;
    float  m_f2ndSteerAngle; // used for steering 2nd set of wheels or elevators etc..
    float  m_fGasPedal;
    float  m_fBreakPedal;
    unsigned char  m_nCreatedBy; // see eVehicleCreatedBy
    short m_nExtendedRemovalRange; // when game wants to delete a vehicle, it gets min(m_wExtendedRemovalRange, 170.0)
    unsigned char m_nBombOnBoard : 3; // 0 = None
                              // 1 = Timed
                              // 2 = On ignition
                              // 3 = remotely set ?
                              // 4 = Timed Bomb has been activated
                              // 5 = On ignition has been activated
    unsigned char m_nOverrideLights : 2; // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
    unsigned char m_nWinchType : 2; // Does this vehicle use a winch?
    unsigned char m_nGunsCycleIndex : 2; // Cycle through alternate gun hardpoints on planes/helis
    unsigned char m_nOrdnanceCycleIndex : 2; // Cycle through alternate ordnance hardpoints on planes/helis
    unsigned char m_nUsedForCover; // Has n number of cops hiding/attempting to hid behind it
    unsigned char m_nAmmoInClip; // Used to make the guns on boat do a reload (20 by default).
    unsigned char m_nPacMansCollected; // initialised, but not used?
    unsigned char m_nPedsPositionForRoadBlock; // 0, 1 or 2
    unsigned char m_nNumCopsForRoadBlock;
    float   m_fDirtLevel; // Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible
    unsigned char m_nCurrentGear;
    float   m_fGearChangeCount; // used as parameter for cTransmission::CalculateDriveAcceleration, but doesn't change
    float   m_fWheelSpinForAudio;
    float   m_fHealth; // 1000.0f = full health. 0 -> explode
    CVehicle *m_pTractor;
    CVehicle *m_pTrailer;
    CPed *m_pWhoInstalledBombOnMe;
    unsigned int m_nTimeTillWeNeedThisCar; // game won't try to delete this car while this time won't reach
    unsigned int m_nGunFiringTime; // last time when gun on vehicle was fired (used on boats)
    unsigned int m_nTimeWhenBlowedUp; // game will delete vehicle when 60 seconds after this time will expire
    short  m_nCopsInCarTimer; // timer for police car (which is following player) occupants to stay in car. If this timer reachs 
                             // some value, they will leave a car. The timer increases each frame if player is stopped in car, 
                             // otherway it resets
    short  m_wBombTimer;     // goes down with each frame
    CPed *m_pWhoDetonatedMe; // if vehicle was detonated, game copies m_pWhoInstalledBombOnMe here
    float  m_fVehicleFrontGroundZ; // we get these values from CCollision::IsStoredPolyStillValidVerticalLine
    float  m_fVehicleRearGroundZ;  // or CWorld::ProcessVerticalLine
    char field_4EC; // initialised, but not used?
    char field_4ED[11]; // possibly non-used data?
    unsigned int m_nDoorLock; // see enum eCarLock
    unsigned int m_nProjectileWeaponFiringTime; // manual-aimed projectiles for hunter, lock-on projectile for hydra
    unsigned int m_nAdditionalProjectileWeaponFiringTime; // manual-aimed projectiles for hydra
    unsigned int m_nTimeForMinigunFiring; // minigun on hunter
    unsigned char m_nLastWeaponDamageType; // see eWeaponType, -1 if no damage
    CEntity *m_pLastDamageEntity;
    char field_510; // not used?
    char field_511; // initialised, but not used?
    char field_512; // initialised, but not used?
    char m_nVehicleWeaponInUse; // see enum eCarWeapon
    unsigned int     m_nHornCounter;
    char field_518; // random id related to siren
    char field_519; // car horn related
    char field_51A;
    char       m_nHasslePosId;
    CStoredCollPoly m_FrontCollPoly; // poly which is under front part of car
    CStoredCollPoly m_RearCollPoly; // poly which is under rear part of car
    unsigned char      m_anCollisionLighting[4]; // left front, left rear, right front, right rear
    FxSystem_c *m_pOverheatParticle;
    FxSystem_c *m_pFireParticle;
    FxSystem_c *m_pDustParticle;
    union{
        unsigned char     m_nRenderLightsFlags;
        struct{
            unsigned char m_bRightFront : 1;
            unsigned char m_bLeftFront : 1;
            unsigned char m_bRightRear : 1;
            unsigned char m_bLeftRear : 1;
        } m_renderLights;
    };
    RwTexture *m_pCustomCarPlate;
    CVehicle *field_58C;
    unsigned int     m_nVehicleClass; // see enum eVehicleClass
    unsigned int     m_nVehicleSubClass;
    short      m_nPreviousRemapTxd;
    short      m_nRemapTxd;
    RwTexture *m_pRemapTexture;

    static float &WHEELSPIN_TARGET_RATE; // 1.0
    static float &WHEELSPIN_INAIR_TARGET_RATE; // 10.0
    static float &WHEELSPIN_RISE_RATE; // 0.95
    static float &WHEELSPIN_FALL_RATE; // 0.7
    static float &m_fAirResistanceMult; // 2.5
    static float &ms_fRailTrackResistance; // 0.003
    static float &ms_fRailTrackResistanceDefault; // 0.003
    static bool &bDisableRemoteDetonation;
    static bool &bDisableRemoteDetonationOnContact;
    static bool &m_bEnableMouseSteering;
    static bool &m_bEnableMouseFlying;
    static int &m_nLastControlInput;
    static CColModel **m_aSpecialColVehicle; // CColModel *CVehicle::m_aSpecialColVehicle[4]
    static bool &ms_forceVehicleLightsOff;
    static bool &s_bPlaneGunsEjectShellCasings;
    static CColModel *m_aSpecialColModel; // static CColModel m_aSpecialColModel[4]

    static void InjectHooks();

    // originally vtable functions

    virtual void ProcessControlCollisionCheck();
    virtual void ProcessControlInputs(unsigned char playerNum);
    // component index in m_apModelNodes array
    virtual void GetComponentWorldPosition(int componentId, CVector& posnOut);
    // component index in m_apModelNodes array
    virtual bool IsComponentPresent(int componentId);
    virtual void OpenDoor(CPed* ped, int componentId, eDoors door, float doorOpenRatio, bool playSound);
    virtual void ProcessOpenDoor(CPed* ped, unsigned int doorComponentId, unsigned int arg2, unsigned int arg3, float arg4);
    virtual float GetDooorAngleOpenRatio(unsigned int door);
    virtual float GetDooorAngleOpenRatio(eDoors door);
    virtual bool IsDoorReady(unsigned int door);
    virtual bool IsDoorReady(eDoors door);
    virtual bool IsDoorFullyOpen(unsigned int door);
    virtual bool IsDoorFullyOpen(eDoors door);
    virtual bool IsDoorClosed(unsigned int door);
    virtual bool IsDoorClosed(eDoors door);
    virtual bool IsDoorMissing(unsigned int door);
    virtual bool IsDoorMissing(eDoors door);
    // check if car has roof as extra
    virtual bool IsOpenTopCar();
    // remove ref to this entity
    virtual void RemoveRefsToVehicle(CEntity* entity);
    virtual void BlowUpCar(CEntity* damager, unsigned char bHideExplosion);
    virtual void BlowUpCarCutSceneNoExtras(bool bNoCamShake, bool bNoSpawnFlyingComps, bool bDetachWheels, bool bExplosionSound);
    virtual bool SetUpWheelColModel(CColModel* wheelCol);
    // returns false if it's not possible to burst vehicle's tyre or it is already damaged. bPhysicalEffect=true applies random moving force to vehicle
    virtual bool BurstTyre(unsigned char tyreComponentId, bool bPhysicalEffect);
    virtual bool IsRoomForPedToLeaveCar(unsigned int arg0, CVector* arg1);
    virtual void ProcessDrivingAnims(CPed* driver, unsigned char arg1);
    // get special ride anim data for bile or quad
    virtual CRideAnimData* GetRideAnimData();
    virtual void SetupSuspensionLines();
    virtual CVector* AddMovingCollisionSpeed(CVector* out, CVector& vecDistance);
    virtual void Fix();
    virtual void SetupDamageAfterLoad();
    virtual void DoBurstAndSoftGroundRatios();
    virtual float GetHeightAboveRoad();
    virtual void PlayCarHorn();
    virtual int GetNumContactWheels();
    virtual void VehicleDamage(float damageIntensity, unsigned short collisionComponent, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon);
    virtual bool CanPedStepOutCar(bool arg0);
    virtual bool CanPedJumpOutCar(CPed* ped);
    virtual bool GetTowHitchPos(CVector& posnOut, bool arg1, CVehicle* arg2);
    virtual bool GetTowBarPos(CVector& posnOut, bool arg1, CVehicle* arg2);
    // always return true
    virtual bool SetTowLink(CVehicle* arg0, bool arg1);
    virtual bool BreakTowLink();
    virtual float FindWheelWidth(bool bRear);
    // always return true
    virtual bool Save();
    // always return true
    virtual bool Load();

    //funcs

    static void Shutdown();
    // -1 if no remap index
    int GetRemapIndex();
    void SetRemapTexDictionary(int txdId);
    // index for m_awRemapTxds[] array
    void SetRemap(int remapIndex);
    void SetCollisionLighting(unsigned char lighting);
    void UpdateLightingFromStoredPolys();
    void CalculateLightingFromCollision();
    void ResetAfterRender();
    // 2 - bike, 3 - heli, 4 - boat, 5 - plane
    int GetVehicleAppearance();
    // returns false if vehicle model has no car plate material
    bool CustomCarPlate_TextureCreate(CVehicleModelInfo* model);
    void CustomCarPlate_TextureDestroy();
    bool CanBeDeleted();
    float ProcessWheelRotation(tWheelState wheelState, CVector const& arg1, CVector const& arg2, float arg3);
    bool CanVehicleBeDamaged(CEntity* damager, eWeaponType weapon, unsigned char* arg2);
    void ProcessDelayedExplosion();
    bool AddPassenger(CPed* passenger);
    bool AddPassenger(CPed* passenger, unsigned char seatNumber);
    void RemovePassenger(CPed* passenger);
    void SetDriver(CPed* driver);
    void RemoveDriver(bool arg0);
    CPed* SetUpDriver(int pedType, bool arg1, bool arg2);
    CPed* SetupPassenger(int seatNumber, int pedType, bool arg2, bool arg3);
    bool IsPassenger(CPed* ped);
    bool IsPassenger(int modelIndex);
    bool IsDriver(CPed* ped);
    bool IsDriver(int modelIndex);
    void KillPedsInVehicle();
    // return this->m_pCoords->matrix.GetUp().z <= -0.9;
    bool IsUpsideDown();
    // return this->m_pCoords->matrix.GetRight().z >= 0.8 || this->m_pCoords->matrix.GetRight().z <= -0.8;
    bool IsOnItsSide();
    bool CanPedOpenLocks(CPed* ped);
    bool CanDoorsBeDamaged();
    bool CanPedEnterCar();
    void ProcessCarAlarm();
    bool IsVehicleNormal();
    void ChangeLawEnforcerState(unsigned char state);
    bool IsLawEnforcementVehicle();
    bool ShufflePassengersToMakeSpace();
    void ExtinguishCarFire();
    void ActivateBomb();
    void ActivateBombWhenEntered();
    bool CarHasRoof();
    float HeightAboveCeiling(float arg0, eFlightModel arg1);
    void SetComponentVisibility(RwFrame* component, unsigned int visibilityState);
    void ApplyBoatWaterResistance(tBoatHandlingData* boatHandling, float arg1);
    static void SetComponentAtomicAlpha(RpAtomic* atomic, int alpha);
    void UpdateClumpAlpha();
    void UpdatePassengerList();
    CPed* PickRandomPassenger();
    void AddDamagedVehicleParticles();
    void MakeDirty(CColPoint& colPoint);
    bool AddWheelDirtAndWater(CColPoint& colPoint, unsigned int arg1, unsigned char arg2, unsigned char arg3);
    void SetGettingInFlags(unsigned char doorId);
    void SetGettingOutFlags(unsigned char doorId);
    void ClearGettingInFlags(unsigned char doorId);
    void ClearGettingOutFlags(unsigned char doorId);
    void SetWindowOpenFlag(unsigned char doorId);
    void ClearWindowOpenFlag(unsigned char doorId);
    bool SetVehicleUpgradeFlags(int upgradeModelIndex, int componentIndex, int& resultModelIndex);
    bool ClearVehicleUpgradeFlags(int arg0, int componentIndex);
    RpAtomic* CreateUpgradeAtomic(CBaseModelInfo* model, UpgradePosnDesc const* upgradePosn, RwFrame* parentComponent, bool isDamaged);
    void RemoveUpgrade(int upgradeId);
    // return upgrade model id or -1 if not present
    int GetUpgrade(int upgradeId);
    RpAtomic* CreateReplacementAtomic(CBaseModelInfo* model, RwFrame* component, int arg2, bool bDamaged, bool bIsWheel);
    void AddReplacementUpgrade(int modelIndex, int nodeId);
    void RemoveReplacementUpgrade(int nodeId);
    // return upgrade model id or -1 if not present
    void GetReplacementUpgrade(int nodeId);
    void RemoveAllUpgrades();
    int GetSpareHasslePosId();
    void SetHasslePosId(int hasslePos, bool enable);
    void InitWinch(int arg0);
    void UpdateWinch();
    void RemoveWinch();
    void ReleasePickedUpEntityWithWinch();
    void PickUpEntityWithWinch(CEntity* arg0);
    CEntity* QueryPickedUpEntityWithWinch();
    float GetRopeHeightForHeli();
    void SetRopeHeightForHeli(float height);
    void RenderDriverAndPassengers();
    void PreRenderDriverAndPassengers();
    float GetPlaneGunsAutoAimAngle();
    int GetPlaneNumGuns();
    void SetFiringRateMultiplier(float multiplier);
    float GetFiringRateMultiplier();
    unsigned int GetPlaneGunsRateOfFire();
    CVector GetPlaneGunsPosition(int gunId);
    unsigned int GetPlaneOrdnanceRateOfFire(eOrdnanceType ordnanceType);
    CVector GetPlaneOrdnancePosition(eOrdnanceType ordnanceType);
    void SelectPlaneWeapon(bool bChange, eOrdnanceType ordnanceType);
    void DoPlaneGunFireFX(CWeapon* weapon, CVector& particlePos, CVector& gunshellPos, int particleIndex);
    void FirePlaneGuns();
    void FireUnguidedMissile(eOrdnanceType ordnanceType, bool bCheckTime);
    bool CanBeDriven();
    void ReactToVehicleDamage(CPed* ped);
    bool GetVehicleLightsStatus();
    bool CanPedLeanOut(CPed* ped);
    void SetVehicleCreatedBy(int createdBy);
    void SetupRender();
    void ProcessWheel(CVector& arg0, CVector& arg1, CVector& arg2, CVector& arg3, int arg4, float arg5, float arg6, float arg7, char arg8, float* arg9, tWheelState* arg10, unsigned short arg11);
    void ProcessBikeWheel(CVector& arg0, CVector& arg1, CVector& arg2, CVector& arg3, int arg4, float arg5, float arg6, float arg7, float arg8, char arg9, float* arg10, tWheelState* arg11, eBikeWheelSpecial arg12, unsigned short arg13);
    // return nearest wheel?
    int FindTyreNearestPoint(float x, float y);
    void InflictDamage(CEntity* damager, eWeaponType weapon, float intensity, CVector coords);
    void KillPedsGettingInVehicle();
    bool UsesSiren();
    bool IsSphereTouchingVehicle(float x, float y, float z, float radius);
    void FlyingControl(eFlightModel flightModel, float arg1, float arg2, float arg3, float arg4);
    // always return false?
    void BladeColSectorList(CPtrList& ptrList, CColModel& colModel, CMatrix& matrix, short arg3, float arg4);
    void SetComponentRotation(RwFrame* component, int axis, float angle, bool bResetPosition);
    void SetTransmissionRotation(RwFrame* component, float arg1, float arg2, CVector posn, bool isFront);
    void ProcessBoatControl(tBoatHandlingData* boatHandling, float& arg1, bool arg2, bool arg3);
    void DoBoatSplashes(float arg0);
    void DoSunGlare();
    void AddWaterSplashParticles();
    void AddExhaustParticles();
    // always return false?
    bool AddSingleWheelParticles(tWheelState arg0, unsigned int arg1, float arg2, float arg3, CColPoint* arg4, CVector* arg5, float arg6, int arg7, unsigned int surfaceType, bool* bloodState, unsigned int arg10);
    bool GetSpecialColModel();
    void RemoveVehicleUpgrade(int upgradeModelIndex);
    void AddUpgrade(int modelIndex, int upgradeIndex);
    void UpdateTrailerLink(bool arg0, bool arg1);
    void UpdateTractorLink(bool arg0, bool arg1);
    CEntity* ScanAndMarkTargetForHeatSeekingMissile(CEntity* entity);
    void FireHeatSeakingMissile(CEntity* targetEntity, eOrdnanceType ordnanceType, bool arg2);
    void PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType, bool arg1);
    void ProcessSirenAndHorn(bool arg0);
    bool DoHeadLightEffect(int dummyId, CMatrix& vehicleMatrix, unsigned char lightId, unsigned char lightState);
    void DoHeadLightBeam(int arg0, CMatrix& matrix, unsigned char arg2);
    void DoHeadLightReflectionSingle(CMatrix& matrix, unsigned char lightId);
    void DoHeadLightReflectionTwin(CMatrix& matrix);
    void DoHeadLightReflection(CMatrix& matrix, unsigned int flags, unsigned char left, unsigned char right);
    bool DoTailLightEffect(int lightId, CMatrix& matrix, unsigned char arg2, unsigned char arg3, unsigned int arg4, unsigned char arg5);
    // see eVehicleLightsFlags
    void DoVehicleLights(CMatrix& matrix, unsigned int flags);
    void FillVehicleWithPeds(bool bSetClothesToAfro);
    void DoBladeCollision(CVector arg0, CMatrix& matrix, short arg2, float arg3, float arg4);
    void AddVehicleUpgrade(int modelId);
    void SetupUpgradesAfterLoad();
    void GetPlaneWeaponFiringStatus(bool& status, eOrdnanceType& ordnanceType);
    void ProcessWeapons();
    bool IsFakeAircraft() { return m_nVehicleSubClass == VEHICLE_FHELI || m_nVehicleSubClass == VEHICLE_FPLANE; }
    bool IsPlane() { return m_nVehicleSubClass == VEHICLE_PLANE; }
    bool IsVehicleTypeValid() { return m_nVehicleSubClass != VEHICLE_NONE; }
    bool IsBoat() { return m_nVehicleClass == VEHICLE_BOAT; }
    bool IsBike() { return m_nVehicleClass == VEHICLE_BIKE; }
    bool IsQuad() { return m_nVehicleClass == VEHICLE_QUAD; }
    static void* operator new(unsigned int size);
    static void operator delete(void* data);

    inline unsigned char GetCreatedBy() { return m_nCreatedBy; }
    inline bool IsCreatedBy(eVehicleCreatedBy v) { return v == m_nCreatedBy; }
};

VALIDATE_SIZE(CVehicle, 0x5A0);

bool IsVehiclePointerValid(CVehicle* vehicle);
RpAtomic* RemoveUpgradeCB(RpAtomic* atomic, void* data);
RpAtomic* FindUpgradeCB(RpAtomic* atomic, void* data);
RwObject* RemoveObjectsCB(RwObject* object, void* data);
RwFrame* RemoveObjectsCB(RwFrame* component, void* data);
RwObject* CopyObjectsCB(RwObject* object, void* data);
RwObject* FindReplacementUpgradeCB(RwObject* object, void* data);
RpAtomic* RemoveAllUpgradesCB(RpAtomic* atomic, void* data);
RpMaterial* SetCompAlphaCB(RpMaterial* material, void* data);
RwObject* SetVehicleAtomicVisibilityCB(RwObject* object, void* data);
RwFrame* SetVehicleAtomicVisibilityCB(RwFrame* component, void* data);
void DestroyVehicleAndDriverAndPassengers(CVehicle* vehicle);

extern float &fBurstTyreMod; // 0.13
extern float &fBurstSpeedMax; // 0.3
extern float &CAR_NOS_EXTRA_SKID_LOSS; // 0.9
extern float &WS_TRAC_FRAC_LIMIT; // 0.3
extern float &WS_ALREADY_SPINNING_LOSS; // 0.2
extern float &fBurstBikeTyreMod; // 0.05
extern float &fBurstBikeSpeedMax; // 0.12
extern float &fTweakBikeWheelTurnForce; // 2.0
extern float &AUTOGYRO_ROTORSPIN_MULT; // 0.006
extern float &AUTOGYRO_ROTORSPIN_MULTLIMIT; // 0.25
extern float &AUTOGYRO_ROTORSPIN_DAMP; // 0.997
extern float &AUTOGYRO_ROTORLIFT_MULT; // 4.5
extern float &AUTOGYRO_ROTORLIFT_FALLOFF; // 0.75
extern float &AUTOGYRO_ROTORTILT_ANGLE; // 0.25
extern float &ROTOR_SEMI_THICKNESS; // 0.05
extern float *fSpeedMult; // float fSpeedMult[5] = {0.8, 0.75, 0.85, 0.9, 0.85, 0.85}
extern float &fDamagePosSpeedShift; // 0.4
extern unsigned int *aDriveAnimIdsLow; // unsigned int aDriveAnimIdsLow[4] = {61, 68, 69, 78}
extern unsigned int *aDriveAnimIdsBoat; // unsigned int aDriveAnimIdsBoat[4] = {81, 82, 83, 84}
extern unsigned int *aDriveAnimIdsBad; // unsigned int aDriveAnimIdsBad[4] = {62, 70, 71, 79}
extern unsigned int *aDriveAnimIdsBadSlow; // unsigned int aDriveAnimIdsBadSlow[4] = {62, 87, 88, 79}
extern unsigned int *aDriveAnimIdsStd; // unsigned int aDriveAnimIdsStd[4] = {60, 66, 67, 78}
extern unsigned int *aDriveAnimIdsStdSlow; // unsigned int aDriveAnimIdsStdSlow[4] = {60, 85, 86, 78}
extern unsigned int *aDriveAnimIdsPro; // unsigned int aDriveAnimIdsPro[4] = {63, 72, 73, 80}
extern unsigned int *aDriveAnimIdsProSlow; // unsigned int aDriveAnimIdsProSlow[4] = {63, 89, 90, 80}
extern unsigned int *aDriveAnimIdsTruck; // unsigned int aDriveAnimIdsTruck[4] = {91, 92, 93, 94}
extern unsigned int *aDriveAnimIdsKart; // unsigned int aDriveAnimIdsKart[4] = {95, 96, 97, 98}
extern float &DIFF_LIMIT; // 0.8
extern float &DIFF_SPRING_MULT_X; // 0.05
extern float &DIFF_SPRING_MULT_Y; // 0.05
extern float &DIFF_SPRING_MULT_Z; // 0.1
extern float &DIFF_SPRING_COMPRESS_MULT; // 2.0
extern CVector *VehicleGunOffset; // CVector VehicleGunOffset[12];
extern char *&HandlingFilename;
extern char(*VehicleNames)[14]; // char VehicleNames[100][14]; sorting is based on handling id
