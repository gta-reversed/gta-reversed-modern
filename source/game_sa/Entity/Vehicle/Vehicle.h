/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Physical.h"
#include "AEVehicleAudioEntity.h"
#include "tHandlingData.h"
#include "tFlyingHandlingData.h"
#include "AutoPilot.h"
#include "eVehicleHandlingFlags.h"
#include "StoredCollPoly.h"
#include "VehicleModelInfo.h"
#include "tBoatHandlingData.h"
#include "PtrList.h"
#include "RideAnimData.h"
#include "DamageManager.h"
#include "FxSystem_c.h"
#include "Fire.h"

/*  Thanks to MTA team for https://github.com/multitheftauto/mtasa-blue/blob/master/Client/game_sa/CVehicleSA.cpp */

class CWeapon;
class CPed;
class CPlane;
class CHeli;

enum eCarWeapon {
    CAR_WEAPON_NOT_USED,
    CAR_WEAPON_HEAVY_GUN,
    CAR_WEAPON_FREEFALL_BOMB,
    CAR_WEAPON_LOCK_ON_ROCKET,
    CAR_WEAPON_DOUBLE_ROCKET
};

enum eCarLock : uint32 {
    CARLOCK_NOT_USED,
    CARLOCK_UNLOCKED,
    CARLOCK_LOCKED,
    CARLOCK_LOCKOUT_PLAYER_ONLY,
    CARLOCK_LOCKED_PLAYER_INSIDE,
    CARLOCK_COP_CAR,
    CARLOCK_FORCE_SHUT_DOORS,
    CARLOCK_SKIP_SHUT_DOORS
};

enum eVehicleAppearance {
    VEHICLE_APPEARANCE_NONE = 0,
    VEHICLE_APPEARANCE_AUTOMOBILE = 1,
    VEHICLE_APPEARANCE_BIKE = 2,
    VEHICLE_APPEARANCE_HELI = 3,
    VEHICLE_APPEARANCE_BOAT = 4,
    VEHICLE_APPEARANCE_PLANE = 5,
};

enum eVehicleLightsFlags {
    VEHICLE_LIGHTS_TWIN = 1,
    VEHICLE_LIGHTS_IGNORE_DAMAGE = 4,
    VEHICLE_LIGHTS_DISABLE_FRONT = 16,
    VEHICLE_LIGHTS_DISABLE_REAR = 32
};

enum eVehicleCreatedBy : uint8 {
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

enum eVehicleOverrideLightsState {
    NO_CAR_LIGHT_OVERRIDE = 0,
    FORCE_CAR_LIGHTS_OFF = 1,
    FORCE_CAR_LIGHTS_ON = 2
};

enum eCarPiece {
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

enum eRotationAxis {
    AXIS_X = 0,
    AXIS_Y = 1,
    AXIS_Z = 2
};

typedef int32 eOrdnanceType;
typedef int32 eBikeWheelSpecial;

enum eFlightModel : int32 {
    FLIGHT_MODEL_BARON = 1,
    FLIGHT_MODEL_RC = 2,
    FLIGHT_MODEL_PLANE = 3, // also used for cars
    FLIGHT_MODEL_BOAT = 5,
    FLIGHT_MODEL_HELI = 6, // also used for hydra
};

enum tWheelState : int32 {
    WHEEL_STATE_NORMAL,	  // standing still or rolling normally
    WHEEL_STATE_SPINNING, // rotating but not moving
    WHEEL_STATE_SKIDDING,
    WHEEL_STATE_FIXED,	  // not rotating
};

struct tHydrualicData {
    // applied when the vehicle is moving
    // or when hopping keys are pressed (numpad keys)
    float m_fSuspensionNormalUpperLimit;
    float m_fSuspensionNormalLowerLimit;

    // applied when the suspension is extended, like when you press the horn button (caps lock on pc)
    // or when numpad keys are pressed
    float m_fSuspensionExtendedUpperLimit;
    float m_fSuspensionExtendedLowerLimit;

    // applied when the vehicle is at rest (idle/not moving)
    // and does NOT apply if numpad keys are pressed (car hopping)
    float m_fSuspensionNormalIdleUpperLimit;
    float m_fSuspensionNormalIdleLowerLimit;
    float m_wheelSuspension[4];
};

VALIDATE_SIZE(tHydrualicData, 0x28);

class CVehicle : public CPhysical {
public:
    CVehicle(plugin::dummy_func_t) : CPhysical() {} //TODO: Remove
    CVehicle(eVehicleCreatedBy createdBy);
    ~CVehicle() override;
    static void* operator new(uint32 size);
    static void operator delete(void* data);
public:
    CAEVehicleAudioEntity m_vehicleAudio;
    tHandlingData*        m_pHandlingData;
    tFlyingHandlingData*  m_pFlyingHandlingData;
    union {
        eVehicleHandlingFlags m_nHandlingFlagsIntValue;
        struct {
            uint32 b1gBoost : 1;
            uint32 b2gBoost : 1;
            uint32 bNpcAntiRoll : 1;
            uint32 bNpcNeutralHandl : 1;
            uint32 bNoHandbrake : 1;
            uint32 bSteerRearwheels : 1;
            uint32 bHbRearwheelSteer : 1;
            uint32 bAltSteerOpt : 1;
            uint32 bWheelFNarrow2 : 1;
            uint32 bWheelFNarrow : 1;
            uint32 bWheelFWide : 1;
            uint32 bWheelFWide2 : 1;
            uint32 bWheelRNarrow2 : 1;
            uint32 bWheelRNarrow : 1;
            uint32 bWheelRWide : 1;
            uint32 bWheelRWide2 : 1;
            uint32 bHydraulicGeom : 1;
            uint32 bHydraulicInst : 1;
            uint32 bHydraulicNone : 1;
            uint32 bNosInst : 1;
            uint32 bOffroadAbility : 1;
            uint32 bOffroadAbility2 : 1;
            uint32 bHalogenLights : 1;
            uint32 bProcRearwheelFirst : 1;
            uint32 bUseMaxspLimit : 1;
            uint32 bLowRider : 1;
            uint32 bStreetRacer : 1;
            uint32 bSwingingChassis : 1;
        } handlingFlags;
    };
    CAutoPilot m_autoPilot;
    union {
        struct {
            uint32 m_nVehicleUpperFlags;
            uint32 m_nVehicleLowerFlags;
        };
        struct {
            uint32 bIsLawEnforcer : 1;               // Is this guy chasing the player at the moment
            uint32 bIsAmbulanceOnDuty : 1;           // Ambulance trying to get to an accident
            uint32 bIsFireTruckOnDuty : 1;           // Firetruck trying to get to a fire
            uint32 bIsLocked : 1;                    // Is this guy locked by the script (cannot be removed)
            uint32 bEngineOn : 1;                    // For sound purposes. Parked cars have their engines switched off (so do destroyed cars)
            uint32 bIsHandbrakeOn : 1;               // How's the handbrake doing ?
            uint32 bLightsOn : 1;                    // Are the lights switched on ?
            uint32 bFreebies : 1;                    // Any freebies left in this vehicle ?

            uint32 bIsVan : 1;                       // Is this vehicle a van (doors at back of vehicle)
            uint32 bIsBus : 1;                       // Is this vehicle a bus
            uint32 bIsBig : 1;                       // Is this vehicle a bus
            uint32 bLowVehicle : 1;                  // Need this for sporty type cars to use low getting-in/out anims
            uint32 bComedyControls : 1;              // Will make the car hard to control (hopefully in a funny way)
            uint32 bWarnedPeds : 1;                  // Has scan and warn peds of danger been processed?
            uint32 bCraneMessageDone : 1;            // A crane message has been printed for this car allready
            uint32 bTakeLessDamage : 1;              // This vehicle is stronger (takes about 1/4 of damage)

            uint32 bIsDamaged : 1;                   // This vehicle has been damaged and is displaying all its components
            uint32 bHasBeenOwnedByPlayer : 1;        // To work out whether stealing it is a crime
            uint32 bFadeOut : 1;                     // Fade vehicle out
            uint32 bIsBeingCarJacked : 1;            // Fade vehicle out
            uint32 bCreateRoadBlockPeds : 1;         // If this vehicle gets close enough we will create peds (coppers or gang members) round it
            uint32 bCanBeDamaged : 1;                // Set to FALSE during cut scenes to avoid explosions
            uint32 bOccupantsHaveBeenGenerated : 1;  // Is true if the occupants have already been generated. (Shouldn't happen again)
            uint32 bGunSwitchedOff : 1;              // Level designers can use this to switch off guns on boats

            uint32 bVehicleColProcessed : 1;         // Has ProcessEntityCollision been processed for this car?
            uint32 bIsCarParkVehicle : 1;            // Car has been created using the special CAR_PARK script command
            uint32 bHasAlreadyBeenRecorded : 1;      // Used for replays
            uint32 bPartOfConvoy : 1;
            uint32 bHeliMinimumTilt : 1;             // This heli should have almost no tilt really
            uint32 bAudioChangingGear : 1;           // sounds like vehicle is changing gear
            uint32 bIsDrowning : 1;                  // is vehicle occupants taking damage in water (i.e. vehicle is dead in water)
            uint32 bTyresDontBurst : 1;              // If this is set the tyres are invincible

            uint32 bCreatedAsPoliceVehicle : 1;      // True if this guy was created as a police vehicle (enforcer, policecar, miamivice car etc)
            uint32 bRestingOnPhysical : 1;           // Don't go static cause car is sitting on a physical object that might get removed
            uint32 bParking : 1;
            uint32 bCanPark : 1;
            uint32 bFireGun : 1;                     // Does the ai of this vehicle want to fire it's gun?
            uint32 bDriverLastFrame : 1;             // Was there a driver present last frame ?
            uint32 bNeverUseSmallerRemovalRange : 1; // Some vehicles (like planes) we don't want to remove just behind the camera.
            uint32 bIsRCVehicle : 1;                 // Is this a remote controlled (small) vehicle. True whether the player or AI controls it.

            uint32 bAlwaysSkidMarks : 1;             // This vehicle leaves skidmarks regardless of the wheels' states.
            uint32 bEngineBroken : 1;                // Engine doesn't work. Player can get in but the vehicle won't drive
            uint32 bVehicleCanBeTargetted : 1;       // The ped driving this vehicle can be targetted, (for Torenos plane mission)
            uint32 bPartOfAttackWave : 1;            // This car is used in an attack during a gang war
            uint32 bWinchCanPickMeUp : 1;            // This car cannot be picked up by any ropes.
            uint32 bImpounded : 1;                   // Has this vehicle been in a police impounding garage
            uint32 bVehicleCanBeTargettedByHS : 1;   // Heat seeking missiles will not target this vehicle.
            uint32 bSirenOrAlarm : 1;                // Set to TRUE if siren or alarm active, else FALSE

            uint32 bHasGangLeaningOn : 1;
            uint32 bGangMembersForRoadBlock : 1;     // Will generate gang members if NumPedsForRoadBlock > 0
            uint32 bDoesProvideCover : 1;            // If this is false this particular vehicle can not be used to take cover behind.
            uint32 bMadDriver : 1;                   // This vehicle is driving like a lunatic
            uint32 bUpgradedStereo : 1;              // This vehicle has an upgraded stereo
            uint32 bConsideredByPlayer : 1;          // This vehicle is considered by the player to enter
            uint32 bPetrolTankIsWeakPoint : 1;       // If false shootong the petrol tank will NOT Blow up the car
            uint32 bDisableParticles : 1;            // Disable particles from this car. Used in garage.

            uint32 bHasBeenResprayed : 1;            // Has been resprayed in a respray garage. Reset after it has been checked.
            uint32 bUseCarCheats : 1;                // If this is true will set the car cheat stuff up in ProcessControl()
            uint32 bDontSetColourWhenRemapping : 1;  // If the texture gets remapped we don't want to change the colour with it.
            uint32 bUsedForReplay : 1;               // This car is controlled by replay and should be removed when replay is done.
        } vehicleFlags;
    };

    uint32            m_nCreationTime;
    uint8             m_nPrimaryColor;
    uint8             m_nSecondaryColor;
    uint8             m_nTertiaryColor;
    uint8             m_nQuaternaryColor;
    char              m_anExtras[2];
    int16             m_anUpgrades[15];
    float             m_fWheelScale;
    int16             m_nAlarmState;
    int16             m_nForcedRandomRouteSeed; // if this is non-zero the random wander gets deterministic
    CPed*             m_pDriver;
    CPed*             m_apPassengers[8];
    uint8             m_nNumPassengers;
    uint8             m_nNumGettingIn;
    uint8             m_nGettingInFlags;
    uint8             m_nGettingOutFlags;
    uint8             m_nMaxPassengers;
    uint8             m_nWindowsOpenFlags; // initialised, but not used?
    uint8             m_nNitroBoosts;
    int8              m_vehicleSpecialColIndex;
    CEntity*          m_pEntityWeAreOn; // we get it from CWorld::ProcessVerticalLine or ProcessEntityCollision, it's entity under us,
                                        // only static entities (buildings or roads)
    CFire*            m_pFire;
    float             m_fSteerAngle;
    float             m_f2ndSteerAngle; // used for steering 2nd set of wheels or elevators etc..
    float             m_fGasPedal;
    float             m_fBreakPedal;
    eVehicleCreatedBy m_nCreatedBy;
    int16             m_nExtendedRemovalRange;        // when game wants to delete a vehicle, it gets min(m_wExtendedRemovalRange, 170.0)
    uint8             m_nBombOnBoard : 3;             // 0 = None
                                                      // 1 = Timed
                                                      // 2 = On ignition
                                                      // 3 = remotely set ?
                                                      // 4 = Timed Bomb has been activated
                                                      // 5 = On ignition has been activated
    uint8            m_nOverrideLights : 2;           // uses enum NO_CAR_LIGHT_OVERRIDE, FORCE_CAR_LIGHTS_OFF, FORCE_CAR_LIGHTS_ON
    uint8            m_nWinchType : 2;                // Does this vehicle use a winch?
    uint8            m_nGunsCycleIndex : 2;           // Cycle through alternate gun hardpoints on planes/helis
    uint8            m_nOrdnanceCycleIndex : 2;       // Cycle through alternate ordnance hardpoints on planes/helis
    uint8            m_nUsedForCover;                 // Has n number of cops hiding/attempting to hid behind it
    uint8            m_nAmmoInClip;                   // Used to make the guns on boat do a reload (20 by default).
    uint8            m_nPacMansCollected;             // initialised, but not used?
    uint8            m_nPedsPositionForRoadBlock;     // 0, 1 or 2
    uint8            m_nNumCopsForRoadBlock;
    float            m_fDirtLevel; // Dirt level of vehicle body texture: 0.0f=fully clean, 15.0f=maximum dirt visible
    uint8            m_nCurrentGear;
    float            m_fGearChangeCount; // used as parameter for cTransmission::CalculateDriveAcceleration, but doesn't change
    float            m_fWheelSpinForAudio;
    float            m_fHealth; // 1000.0f = full health. 0 -> explode
    CVehicle*        m_pTractor;
    CVehicle*        m_pTrailer;
    CPed*            m_pWhoInstalledBombOnMe;
    uint32           m_nTimeTillWeNeedThisCar;     // game won't try to delete this car while this time won't reach
    uint32           m_nGunFiringTime;             // last time when gun on vehicle was fired (used on boats)
    uint32           m_nTimeWhenBlowedUp;          // game will delete vehicle when 60 seconds after this time will expire
    int16            m_nCopsInCarTimer;            // timer for police car (which is following player) occupants to stay in car. If this timer reachs
                                            // some value, they will leave a car. The timer increases each frame if player is stopped in car,
                                            // otherway it resets
    int16           m_wBombTimer;           // goes down with each frame
    CPed*           m_pWhoDetonatedMe;      // if vehicle was detonated, game copies m_pWhoInstalledBombOnMe here
    float           m_fVehicleFrontGroundZ; // we get these values from CCollision::IsStoredPolyStillValidVerticalLine
    float           m_fVehicleRearGroundZ;  // or CWorld::ProcessVerticalLine
    char            field_4EC;              // initialised, but not used?
    char            field_4ED[11];          // possibly non-used data?
    eCarLock        m_nDoorLock;
    uint32          m_nProjectileWeaponFiringTime;           // manual-aimed projectiles for hunter, lock-on projectile for hydra
    uint32          m_nAdditionalProjectileWeaponFiringTime; // manual-aimed projectiles for hydra
    uint32          m_nTimeForMinigunFiring;                 // minigun on hunter
    uint8           m_nLastWeaponDamageType;                 // see eWeaponType, -1 if no damage
    CEntity*        m_pLastDamageEntity;
    char            field_510;             // not used?
    char            field_511;             // initialised, but not used?
    char            field_512;             // initialised, but not used?
    char            m_nVehicleWeaponInUse; // see enum eCarWeapon
    uint32          m_nHornCounter;
    char            field_518;       // random id related to siren
    char            m_nCarHornTimer; // car horn related
    char            m_comedyControlState;
    char            m_nHasslePosId;
    CStoredCollPoly m_FrontCollPoly;          // poly which is under front part of car
    CStoredCollPoly m_RearCollPoly;           // poly which is under rear part of car
    tColLighting    m_anCollisionLighting[4]; // left front, left rear, right front, right rear
    FxSystem_c*     m_pOverheatParticle;
    FxSystem_c*     m_pFireParticle;
    FxSystem_c*     m_pDustParticle;
    union {
        uint8 m_nRenderLightsFlags;
        struct {
            uint8 m_bRightFront : 1;
            uint8 m_bLeftFront : 1;
            uint8 m_bRightRear : 1;
            uint8 m_bLeftRear : 1;
        } m_renderLights;
    };
    RwTexture*   m_pCustomCarPlate;
    float        m_fRawSteerAngle;
    eVehicleType m_nVehicleType;    // Theory by forkerer:
    eVehicleType m_nVehicleSubType; // Hack to have stuff be 2 classes at once, like vortex which can act like a car and a boat
    int16        m_nPreviousRemapTxd;
    int16        m_nRemapTxd;
    RwTexture*   m_pRemapTexture;

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
    static int32 &m_nLastControlInput;
    static CColModel **m_aSpecialColVehicle; // CColModel *CVehicle::m_aSpecialColVehicle[4]
    static bool &ms_forceVehicleLightsOff;
    static bool &s_bPlaneGunsEjectShellCasings;
    static CColModel (&m_aSpecialColModel)[4]; // static CColModel m_aSpecialColModel[4]
    static tHydrualicData(&m_aSpecialHydraulicData)[4];

public:
    static void InjectHooks();

// VIRTUAL
    void SetModelIndex(uint32 index) override;
    void DeleteRwObject() override;
    void SpecialEntityPreCollisionStuff(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled, bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck) override;
    uint8 SpecialEntityCalcCollisionSteps(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2) override;
    void PreRender() override;
    void Render() override;
    bool SetupLighting() override;
    void RemoveLighting(bool bRemove) override;
    void FlagToDestroyWhenNextProcessed() override { /* Do nothing */ }

    virtual void ProcessControlCollisionCheck(bool applySpeed) { /* Do nothing */ }
    virtual void ProcessControlInputs(uint8 playerNum) { /* Do nothing */ }
    // component index in m_apModelNodes array
    virtual void GetComponentWorldPosition(int32 componentId, CVector& outPos) { /* Do nothing */ }
    // component index in m_apModelNodes array
    virtual bool IsComponentPresent(int32 componentId) { return false; }
    virtual void OpenDoor(CPed* ped, int32 componentId, eDoors door, float doorOpenRatio, bool playSound) { /* Do nothing */ }
    virtual void ProcessOpenDoor(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime);
    virtual float GetDooorAngleOpenRatio(eDoors door) { return 0.0F; }
    virtual float GetDooorAngleOpenRatio(uint32 door) { return 0.0F; }
    virtual bool IsDoorReady(eDoors door) { return false; }
    virtual bool IsDoorReady(uint32 door) { return false; }
    virtual bool IsDoorFullyOpen(eDoors door) { return false; }
    virtual bool IsDoorFullyOpen(uint32 door) { return false; }
    virtual bool IsDoorClosed(eDoors door){ return false; }
    virtual bool IsDoorClosed(uint32 door){ return false; }
    virtual bool IsDoorMissing(eDoors door) { return false; }
    virtual bool IsDoorMissing(uint32 door){ return false; }
    // check if car has roof as extra
    virtual bool IsOpenTopCar(){ return false; }
    // remove ref to this entity
    virtual void RemoveRefsToVehicle(CEntity* entity) { /* Do nothing */ }
    virtual void BlowUpCar(CEntity* damager, uint8 bHideExplosion) { /* Do nothing */ }
    virtual void BlowUpCarCutSceneNoExtras(bool bNoCamShake, bool bNoSpawnFlyingComps, bool bDetachWheels, bool bExplosionSound) { /* Do nothing */ }
    virtual bool SetUpWheelColModel(CColModel* wheelCol) { return false; }
    // returns false if it's not possible to burst vehicle's tyre or it is already damaged. bPhysicalEffect=true applies random moving force to vehicle
    virtual bool BurstTyre(uint8 tyreComponentId, bool bPhysicalEffect) { return false; }
    virtual bool IsRoomForPedToLeaveCar(uint32 arg0, CVector* arg1) { return false; }
    virtual void ProcessDrivingAnims(CPed* driver, uint8 bBlend);
    // get special ride anim data for bile or quad
    virtual CRideAnimData* GetRideAnimData() { return nullptr; }
    virtual void SetupSuspensionLines() { /* Do nothing */ }
    virtual CVector AddMovingCollisionSpeed(CVector& point) { return {}; }
    virtual void Fix() { /* Do nothing */ } // 0x6D6390
    virtual void SetupDamageAfterLoad() { /* Do nothing */ }
    virtual void DoBurstAndSoftGroundRatios() { /* Do nothing */ }
    virtual float GetHeightAboveRoad();
    virtual void PlayCarHorn() { /* Do nothing */ }
    virtual int32 GetNumContactWheels() { return 4; }
    virtual void VehicleDamage(float damageIntensity, uint16 collisionComponent, CEntity* damager, CVector* vecCollisionCoors, CVector* vecCollisionDirection, eWeaponType weapon) { /* Do nothing */ }
    virtual bool CanPedStepOutCar(bool bIgnoreSpeedUpright);
    virtual bool CanPedJumpOutCar(CPed* ped);
    virtual bool GetTowHitchPos(CVector& outPos, bool bCheckModelInfo, CVehicle* veh);
    virtual bool GetTowBarPos(CVector& outPos, bool bCheckModelInfo, CVehicle* veh);
    virtual bool SetTowLink(CVehicle* targetVehicle, bool arg1) { return false; }
    virtual bool BreakTowLink() { return false; }
    virtual float FindWheelWidth(bool bRear) { return 0.25F; }
    virtual bool Save();
    virtual bool Load();

// VIRTUAL METHODS REVERSED
private:
    void SetModelIndex_Reversed(uint32 index);
    void DeleteRwObject_Reversed();
    void SpecialEntityPreCollisionStuff_Reversed(CPhysical* colPhysical,
                                                 bool bIgnoreStuckCheck,
                                                 bool& bCollisionDisabled,
                                                 bool& bCollidedEntityCollisionIgnored,
                                                 bool& bCollidedEntityUnableToMove,
                                                 bool& bThisOrCollidedEntityStuck);
    uint8 SpecialEntityCalcCollisionSteps_Reversed(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2);
    void PreRender_Reversed();
    void Render_Reversed();
    bool SetupLighting_Reversed();
    void RemoveLighting_Reversed(bool bRemove);
    void ProcessOpenDoor_Reversed(CPed* ped, uint32 doorComponentId, uint32 animGroup, uint32 animId, float fTime);
    void ProcessDrivingAnims_Reversed(CPed* driver, uint8 bBlend);
    float GetHeightAboveRoad_Reversed();
    bool CanPedStepOutCar_Reversed(bool bIgnoreSpeedUpright);
    bool CanPedJumpOutCar_Reversed(CPed* ped);
    bool GetTowHitchPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* veh);
    bool GetTowBarPos_Reversed(CVector& outPos, bool bCheckModelInfo, CVehicle* veh);
    bool Save_Reversed();
    bool Load_Reversed();

 // CLASS FUNCS
public:
    // -1 if no remap index
    int32 GetRemapIndex();
    void SetRemapTexDictionary(int32 txdId);
    // index for m_awRemapTxds[] array
    void SetRemap(int32 remapIndex);
    void SetCollisionLighting(tColLighting lighting);
    void UpdateLightingFromStoredPolys();
    void CalculateLightingFromCollision();
    void ResetAfterRender();
    eVehicleAppearance GetVehicleAppearance();
    // returns false if vehicle model has no car plate material
    bool CustomCarPlate_TextureCreate(CVehicleModelInfo* model);
    void CustomCarPlate_TextureDestroy();
    bool CanBeDeleted();
    float ProcessWheelRotation(tWheelState wheelState, const CVector& arg1, const CVector& arg2, float arg3);
    bool CanVehicleBeDamaged(CEntity* damager, eWeaponType weapon, uint8* arg2);
    void ProcessDelayedExplosion();
    bool AddPassenger(CPed* passenger);
    bool AddPassenger(CPed* passenger, uint8 seatNumber);
    void RemovePassenger(CPed* passenger);
    void SetDriver(CPed* driver);
    void RemoveDriver(bool arg0);
    CPed* SetUpDriver(int32 pedType, bool arg1, bool arg2);
    CPed* SetupPassenger(int32 seatNumber, int32 pedType, bool arg2, bool arg3);
    bool IsPassenger(CPed* ped);
    bool IsPassenger(int32 modelIndex);
    bool IsDriver(CPed* ped);
    bool IsDriver(int32 modelIndex);
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
    void ChangeLawEnforcerState(bool bIsEnforcer);
    bool IsLawEnforcementVehicle();
    static bool ShufflePassengersToMakeSpace();
    void ExtinguishCarFire();
    void ActivateBomb();
    void ActivateBombWhenEntered();
    bool CarHasRoof();
    float HeightAboveCeiling(float arg0, eFlightModel arg1);
    void SetComponentVisibility(RwFrame* component, uint32 visibilityState);
    void ApplyBoatWaterResistance(tBoatHandlingData* boatHandling, float fImmersionDepth);
    void UpdateClumpAlpha();
    void UpdatePassengerList();
    CPed* PickRandomPassenger();
    void AddDamagedVehicleParticles();
    void MakeDirty(CColPoint& colPoint);
    bool AddWheelDirtAndWater(CColPoint& colPoint, uint32 arg1, uint8 arg2, uint8 arg3);
    void SetGettingInFlags(uint8 doorId);
    void SetGettingOutFlags(uint8 doorId);
    void ClearGettingInFlags(uint8 doorId);
    void ClearGettingOutFlags(uint8 doorId);
    void SetWindowOpenFlag(uint8 doorId);
    void ClearWindowOpenFlag(uint8 doorId);
    bool SetVehicleUpgradeFlags(int32 upgradeModelIndex, int32 componentIndex, int32& resultModelIndex);
    bool ClearVehicleUpgradeFlags(int32 arg0, int32 componentIndex);
    RpAtomic* CreateUpgradeAtomic(CBaseModelInfo* model, const UpgradePosnDesc* upgradePosn, RwFrame* parentComponent, bool isDamaged);
    void RemoveUpgrade(int32 upgradeId);
    // return upgrade model id or -1 if not present
    int32 GetUpgrade(int32 upgradeId);
    RpAtomic* CreateReplacementAtomic(CBaseModelInfo* model, RwFrame* component, int32 arg2, bool bDamaged, bool bIsWheel);
    void AddReplacementUpgrade(int32 modelIndex, int32 nodeId);
    void RemoveReplacementUpgrade(int32 nodeId);
    // return upgrade model id or -1 if not present
    void GetReplacementUpgrade(int32 nodeId);
    void RemoveAllUpgrades();
    int32 GetSpareHasslePosId();
    void SetHasslePosId(int32 hasslePos, bool enable);
    void InitWinch(int32 arg0);
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
    int32 GetPlaneNumGuns();
    void SetFiringRateMultiplier(float multiplier);
    float GetFiringRateMultiplier();
    uint32 GetPlaneGunsRateOfFire();
    CVector GetPlaneGunsPosition(int32 gunId);
    uint32 GetPlaneOrdnanceRateOfFire(eOrdnanceType ordnanceType);
    CVector GetPlaneOrdnancePosition(eOrdnanceType ordnanceType);
    void SelectPlaneWeapon(bool bChange, eOrdnanceType ordnanceType);
    void DoPlaneGunFireFX(CWeapon* weapon, CVector& particlePos, CVector& gunshellPos, int32 particleIndex);
    void FirePlaneGuns();
    void FireUnguidedMissile(eOrdnanceType ordnanceType, bool bCheckTime);
    bool CanBeDriven();
    void ReactToVehicleDamage(CPed* ped);
    bool GetVehicleLightsStatus();
    bool CanPedLeanOut(CPed* ped);
    void SetVehicleCreatedBy(int32 createdBy);
    void SetupRender();
    void ProcessWheel(CVector& wheelFwd, CVector& wheelRight, CVector& wheelContactSpeed, CVector& wheelContactPoint,
        int32 wheelsOnGround, float thrust, float brake, float adhesion, int8 wheelId, float* wheelSpeed, tWheelState* wheelState, uint16 wheelStatus);
    void ProcessBikeWheel(CVector& arg0, CVector& arg1, CVector& arg2, CVector& arg3, int32 arg4, float arg5, float arg6, float arg7, float arg8, char arg9, float* arg10, tWheelState* arg11, eBikeWheelSpecial arg12, uint16 arg13);
    // return nearest wheel?
    int32 FindTyreNearestPoint(float x, float y);
    void InflictDamage(CEntity* damager, eWeaponType weapon, float intensity, CVector coords);
    void KillPedsGettingInVehicle();
    bool UsesSiren();
    bool IsSphereTouchingVehicle(float x, float y, float z, float radius);
    void FlyingControl(eFlightModel flightModel, float leftRightSkid, float steeringUpDown, float steeringLeftRight, float accelerationBreakStatus);
    // always return false?
    void BladeColSectorList(CPtrList& ptrList, CColModel& colModel, CMatrix& matrix, int16 arg3, float arg4);
    void SetComponentRotation(RwFrame* component, int32 axis, float angle, bool bResetPosition); // rotation axis: eRotationAxis
    void SetTransmissionRotation(RwFrame* component, float arg1, float arg2, CVector posn, bool isFront);
    void ProcessBoatControl(tBoatHandlingData* boatHandling, float* fWaterResistance, bool bCollidedWithWorld, bool bPostCollision);
    void DoBoatSplashes(float fWaterDamping);
    void DoSunGlare();
    void AddWaterSplashParticles();
    void AddExhaustParticles();
    // always return false?
    bool AddSingleWheelParticles(tWheelState arg0, uint32 arg1, float arg2, float arg3, CColPoint* arg4, CVector* arg5, float arg6, int32 arg7, uint32 surfaceType, bool* bloodState, uint32 arg10);
    bool GetSpecialColModel();
    void RemoveVehicleUpgrade(int32 upgradeModelIndex);
    void AddUpgrade(int32 modelIndex, int32 upgradeIndex);
    void UpdateTrailerLink(bool arg0, bool arg1);
    void UpdateTractorLink(bool arg0, bool arg1);
    CEntity* ScanAndMarkTargetForHeatSeekingMissile(CEntity* entity);
    void FireHeatSeakingMissile(CEntity* targetEntity, eOrdnanceType ordnanceType, bool arg2);
    void PossiblyDropFreeFallBombForPlayer(eOrdnanceType ordnanceType, bool arg1);
    void ProcessSirenAndHorn(bool arg0);
    bool DoHeadLightEffect(int32 dummyId, CMatrix& vehicleMatrix, uint8 lightId, uint8 lightState);
    void DoHeadLightBeam(int32 dummyId, CMatrix& matrix, bool arg2);
    void DoHeadLightReflectionSingle(CMatrix& matrix, uint8 lightId);
    void DoHeadLightReflectionTwin(CMatrix& matrix);
    void DoHeadLightReflection(CMatrix& matrix, uint32 flags, uint8 left, uint8 right);
    bool DoTailLightEffect(int32 lightId, CMatrix& matrix, uint8 arg2, uint8 arg3, uint32 arg4, uint8 arg5);
    // see eVehicleLightsFlags
    void DoVehicleLights(CMatrix& matrix, uint32 flags);
    void FillVehicleWithPeds(bool bSetClothesToAfro);
    void DoBladeCollision(CVector arg0, CMatrix& matrix, int16 arg2, float arg3, float arg4);
    void AddVehicleUpgrade(int32 modelId);
    void SetupUpgradesAfterLoad();
    void GetPlaneWeaponFiringStatus(bool& status, eOrdnanceType& ordnanceType);
    void ProcessWeapons();
    void DoFixedMachineGuns();
    void FireFixedMachineGuns();
    void DoDriveByShootings();

    bool AreAnyOfPassengersFollowerOfGroup(const CPedGroup& group);

// STATIC FUNCS
    static void Shutdown();
    static void SetComponentAtomicAlpha(RpAtomic* atomic, int32 alpha);

public:
    // m_nVehicleType start
    bool IsVehicleTypeValid()     const { return m_nVehicleType != VEHICLE_TYPE_IGNORE; }
    bool IsAutomobile()           const { return m_nVehicleType == VEHICLE_TYPE_AUTOMOBILE; }
    bool IsMonsterTruck()         const { return m_nVehicleType == VEHICLE_TYPE_MTRUCK; }
    bool IsQuad()                 const { return m_nVehicleType == VEHICLE_TYPE_QUAD; }
    bool IsHeli()                 const { return m_nVehicleType == VEHICLE_TYPE_HELI; }
    bool IsPlane()                const { return m_nVehicleType == VEHICLE_TYPE_PLANE; }
    bool IsBoat()                 const { return m_nVehicleType == VEHICLE_TYPE_BOAT; }
    bool IsTrain()                const { return m_nVehicleType == VEHICLE_TYPE_TRAIN; }
    bool IsFakeAircraft()         const { return m_nVehicleType == VEHICLE_TYPE_FHELI || m_nVehicleType == VEHICLE_TYPE_FPLANE; }
    bool IsBike()                 const { return m_nVehicleType == VEHICLE_TYPE_BIKE; }
    bool IsBMX()                  const { return m_nVehicleType == VEHICLE_TYPE_BMX; }
    bool IsTrailer()              const { return m_nVehicleType == VEHICLE_TYPE_TRAILER; }
    // m_nVehicleType end

    // m_nVehicleSubType start
    bool IsSubVehicleTypeValid() const { return m_nVehicleSubType != VEHICLE_TYPE_IGNORE; }
    bool IsSubAutomobile()       const { return m_nVehicleSubType == VEHICLE_TYPE_AUTOMOBILE; }
    bool IsSubMonsterTruck()     const { return m_nVehicleSubType == VEHICLE_TYPE_MTRUCK; }
    bool IsSubQuad()             const { return m_nVehicleSubType == VEHICLE_TYPE_QUAD; }
    bool IsSubHeli()             const { return m_nVehicleSubType == VEHICLE_TYPE_HELI; }
    bool IsSubPlane()            const { return m_nVehicleSubType == VEHICLE_TYPE_PLANE; }
    bool IsSubBoat()             const { return m_nVehicleSubType == VEHICLE_TYPE_BOAT; }
    bool IsSubTrain()            const { return m_nVehicleSubType == VEHICLE_TYPE_TRAIN; }
    bool IsSubFakeAircraft()     const { return m_nVehicleSubType == VEHICLE_TYPE_FHELI || m_nVehicleSubType == VEHICLE_TYPE_FPLANE; }
    bool IsSubBike()             const { return m_nVehicleSubType == VEHICLE_TYPE_BIKE; }
    bool IsSubBMX()              const { return m_nVehicleSubType == VEHICLE_TYPE_BMX; }
    bool IsSubTrailer()          const { return m_nVehicleSubType == VEHICLE_TYPE_TRAILER; }

    bool IsSubRoadVehicle()      const { return !IsSubHeli() && !IsSubPlane() && !IsSubTrain(); }
    // m_nVehicleSubType end

    bool IsTransportVehicle()    const { return m_nModelIndex == MODEL_TAXI    || m_nModelIndex == MODEL_CABBIE; }
    bool IsAmphibiousHeli()      const { return m_nModelIndex == MODEL_SEASPAR || m_nModelIndex == MODEL_LEVIATHN; }
    bool IsConstructionVehicle() const { return m_nModelIndex == MODEL_DUMPER  || m_nModelIndex == MODEL_DOZER || m_nModelIndex == MODEL_FORKLIFT; }

    eVehicleCreatedBy GetCreatedBy()      { return m_nCreatedBy; }
    bool IsCreatedBy(eVehicleCreatedBy v) { return v == m_nCreatedBy; }

    bool CanUpdateHornCounter() { return m_nAlarmState == 0 || m_nAlarmState == -1 || m_nStatus == STATUS_WRECKED; }

    CPlane* AsPlane() { return reinterpret_cast<CPlane*>(this); }
    CHeli*  AsHeli()  { return reinterpret_cast<CHeli*>(this); }

public:
    // NOTSA functions

    CVehicleModelInfo* GetVehicleModelInfo();

    // if bWorldSpace is true, returns the position in world-space
    // otherwise in model-space
    CVector GetDummyPosition(eVehicleDummies dummy, bool bWorldSpace = true);
    int32 GetRopeIndex();
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
extern float &DIFF_LIMIT; // 0.8
extern float &DIFF_SPRING_MULT_X; // 0.05
extern float &DIFF_SPRING_MULT_Y; // 0.05
extern float &DIFF_SPRING_MULT_Z; // 0.1
extern float &DIFF_SPRING_COMPRESS_MULT; // 2.0
extern CVector *VehicleGunOffset; // CVector VehicleGunOffset[12];
extern char *&HandlingFilename;
extern char(*VehicleNames)[14]; // char VehicleNames[100][14]; sorting is based on handling id
