/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Physical.h"
#include "AEPedAudioEntity.h"
#include "AEPedSpeechAudioEntity.h"
#include "AEWeaponAudioEntity.h"
#include "PedIntelligence.h"
#include "PlayerPedData.h"
#include "AnimBlendFrameData.h"
#include "Acquaintance.h"
#include "PedIK.h"
#include "Weapon.h"
#include "Vector2D.h"
#include "AnimBlendAssociation.h"
#include "Fire.h"
#include "PedGroups.h"

#include "AnimationEnums.h"
#include "eWeaponType.h"
#include "eWeaponSkill.h"
#include "ePedState.h"
#include "ePedStats.h"
#include "ePedType.h"

class CPedGroup;
class CCivilianPed;
class CEmergencyPed;

static bool IsPedTypeGang(ePedType type) {
    switch (type) {
        case PED_TYPE_GANG1:
        case PED_TYPE_GANG2:
        case PED_TYPE_GANG3:
        case PED_TYPE_GANG4:
        case PED_TYPE_GANG5:
        case PED_TYPE_GANG6:
        case PED_TYPE_GANG7:
        case PED_TYPE_GANG8:
        case PED_TYPE_GANG9:
        case PED_TYPE_GANG10: {
            return true;
        }
    }
    return false;
}

enum ePedNode : int32 {
    PED_NODE_UPPER_TORSO     = 1,
    PED_NODE_HEAD            = 2,
    PED_NODE_LEFT_ARM        = 3,
    PED_NODE_RIGHT_ARM       = 4,
    PED_NODE_LEFT_HAND       = 5,
    PED_NODE_RIGHT_HAND      = 6,
    PED_NODE_LEFT_LEG        = 7,
    PED_NODE_RIGHT_LEG       = 8,
    PED_NODE_LEFT_FOOT       = 9,
    PED_NODE_RIGHT_FOOT      = 10,
    PED_NODE_RIGHT_LOWER_LEG = 11,
    PED_NODE_LEFT_LOWER_LEG  = 12,
    PED_NODE_LEFT_LOWER_ARM  = 13,
    PED_NODE_RIGHT_LOWER_ARM = 14,
    PED_NODE_LEFT_CLAVICLE   = 15,
    PED_NODE_RIGHT_CLAVICLE  = 16,
    PED_NODE_NECK            = 17,
    PED_NODE_JAW             = 18,

    TOTAL_PED_NODES
};

enum ePedPieceTypes {
    PED_PIECE_UNKNOWN = 0,
    PED_PIECE_TORSO = 3,
    PED_PIECE_ASS = 4,
    PED_PIECE_LEFT_ARM = 5,
    PED_PIECE_RIGHT_ARM = 6,
    PED_PIECE_LEFT_LEG = 7,
    PED_PIECE_RIGHT_LEG = 8,
    PED_PIECE_HEAD = 9
};

enum ePedCreatedBy : uint8 {
    PED_UNKNOWN = 0,
    PED_GAME = 1,
    PED_MISSION = 2,
};

enum eMoveState {
    PEDMOVE_NONE = 0,
    PEDMOVE_STILL,
    PEDMOVE_TURN_L,
    PEDMOVE_TURN_R,
    PEDMOVE_WALK,
    PEDMOVE_JOG,
    PEDMOVE_RUN,
    PEDMOVE_SPRINT
};

enum eFightingStyle : int8 {
    STYLE_STANDARD = 4,
    STYLE_BOXING,
    STYLE_KUNG_FU,
    STYLE_KNEE_HEAD,
    // various melee weapon styles
    STYLE_GRAB_KICK = 15,
    STYLE_ELBOWS = 16,
};

class CObject;
class CVehicle;
class CPedStat;
class CPedStats;

class CPed : public CPhysical {
protected:
    CPed(plugin::dummy_func_t) : CPhysical(), m_aWeapons{ plugin::dummy, plugin::dummy, plugin::dummy,
        plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy,
        plugin::dummy, plugin::dummy, plugin::dummy } {}
public:
    CAEPedAudioEntity       m_pedAudio;
    CAEPedSpeechAudioEntity m_pedSpeech;
    CAEWeaponAudioEntity    m_weaponAudio;
    char                    field_43C[36];
    CPed*                   field_460;
    char                    field_464[4];
    int32                   field_468;
    union {
        /* https://github.com/multitheftauto/mtasa-blue/blob/master/Client/game_sa/CPedSA.h */
        struct {
            // 1st byte starts here (m_nPedFlags)
            uint32 bIsStanding : 1;            // is ped standing on something
            uint32 bWasStanding : 1;           // was ped standing on something
            uint32 bIsLooking : 1;             // is ped looking at something or in a direction
            uint32 bIsRestoringLook : 1;       // is ped restoring head position from a look
            uint32 bIsAimingGun : 1;           // is ped aiming gun
            uint32 bIsRestoringGun : 1;        // is ped moving gun back to default posn
            uint32 bCanPointGunAtTarget : 1;   // can ped point gun at target
            uint32 bIsTalking : 1;             // is ped talking(see Chat())

            uint32 bInVehicle : 1;             // is in a vehicle
            uint32 bIsInTheAir : 1;            // is in the air
            uint32 bIsLanding : 1;             // is landing after being in the air
            uint32 bHitSomethingLastFrame : 1; // has been in a collision last fram
            uint32 bIsNearCar : 1;             // has been in a collision last fram
            uint32 bRenderPedInCar : 1;        // has been in a collision last fram
            uint32 bUpdateAnimHeading : 1;     // update ped heading due to heading change during anim sequence
            uint32 bRemoveHead : 1;            // waiting on AntiSpazTimer to remove head

            uint32 bFiringWeapon : 1;         // is pulling trigger
            uint32 bHasACamera : 1;           // does ped possess a camera to document accidents
            uint32 bPedIsBleeding : 1;        // Ped loses a lot of blood if true
            uint32 bStopAndShoot : 1;         // Ped cannot reach target to attack with fist, need to use gun
            uint32 bIsPedDieAnimPlaying : 1;  // is ped die animation finished so can dead now
            uint32 bStayInSamePlace : 1;      // when set, ped stays put
            uint32 bKindaStayInSamePlace : 1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
            uint32 bBeingChasedByPolice : 1;  // use nodes for route find

            uint32 bNotAllowedToDuck : 1;     // Is this ped allowed to duck at all?
            uint32 bCrouchWhenShooting : 1;   // duck behind cars etc
            uint32 bIsDucking : 1;            // duck behind cars etc
            uint32 bGetUpAnimStarted : 1;     // don't want to play getup anim if under something
            uint32 bDoBloodyFootprints : 1;   // uint32 bIsLeader :1;
            uint32 bDontDragMeOutCar : 1;
            uint32 bStillOnValidPoly : 1; // set if the polygon the ped is on is still valid for collision
            uint32 bAllowMedicsToReviveMe : 1;

            // 5th byte starts here (m_nSecondPedFlags)
            uint32 bResetWalkAnims : 1;
            uint32 bOnBoat : 1;               // flee but only using nodes
            uint32 bBusJacked : 1;            // flee but only using nodes
            uint32 bFadeOut : 1;              // set if you want ped to fade out
            uint32 bKnockedUpIntoAir : 1;     // has ped been knocked up into the air by a car collision
            uint32 bHitSteepSlope : 1;        // has ped collided/is standing on a steep slope (surface type)
            uint32 bCullExtraFarAway : 1;     // special ped only gets culled if it's extra far away (for roadblocks)
            uint32 bTryingToReachDryLand : 1; // has ped just exited boat and trying to get to dry land

            uint32 bCollidedWithMyVehicle : 1;
            uint32 bRichFromMugging : 1;        // ped has lots of cash cause they've been mugging people
            uint32 bChrisCriminal : 1;          // Is a criminal as killed during Chris' police mission (should be counted as such)
            uint32 bShakeFist : 1;              // test shake hand at look entity
            uint32 bNoCriticalHits : 1;         // ped cannot be killed by a single bullet
            uint32 bHasAlreadyBeenRecorded : 1; // Used for replays
            uint32 bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
            uint32 bFleeWhenStanding : 1;       //

            uint32 bMiamiViceCop : 1;
            uint32 bMoneyHasBeenGivenByScript : 1;
            uint32 bHasBeenPhotographed : 1;
            uint32 bIsDrowning : 1;
            uint32 bDrownsInWater : 1;
            uint32 bHeadStuckInCollision : 1;
            uint32 bDeadPedInFrontOfCar : 1;
            uint32 bStayInCarOnJack : 1;

            uint32 bDontFight : 1;
            uint32 bDoomAim : 1;
            uint32 bCanBeShotInVehicle : 1;
            uint32 bPushedAlongByCar : 1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
            uint32 bNeverEverTargetThisPed : 1;
            uint32 bThisPedIsATargetPriority : 1;
            uint32 bCrouchWhenScared : 1;
            uint32 bKnockedOffBike : 1;

            // 9th byte starts here (m_nThirdPedFlags)
            uint32 bDonePositionOutOfCollision : 1;
            uint32 bDontRender : 1;
            uint32 bHasBeenAddedToPopulation : 1;
            uint32 bHasJustLeftCar : 1;
            uint32 bIsInDisguise : 1;
            uint32 bDoesntListenToPlayerGroupCommands : 1;
            uint32 bIsBeingArrested : 1;
            uint32 bHasJustSoughtCover : 1;

            uint32 bKilledByStealth : 1;
            uint32 bDoesntDropWeaponsWhenDead : 1;
            uint32 bCalledPreRender : 1;
            uint32 bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
            uint32 bPartOfAttackWave : 1;
            uint32 bClearRadarBlipOnDeath : 1;
            uint32 bNeverLeavesGroup : 1;        // flag that we want to test 3 extra spheres on col model
            uint32 bTestForBlockedPositions : 1; // this sets these indicator flags for various positions on the front of the ped

            uint32 bRightArmBlocked : 1;
            uint32 bLeftArmBlocked : 1;
            uint32 bDuckRightArmBlocked : 1;
            uint32 bMidriffBlockedForJump : 1;
            uint32 bFallenDown : 1;
            uint32 bUseAttractorInstantly : 1;
            uint32 bDontAcceptIKLookAts : 1;
            uint32 bHasAScriptBrain : 1;

            uint32 bWaitingForScriptBrainToLoad : 1;
            uint32 bHasGroupDriveTask : 1;
            uint32 bCanExitCar : 1;
            uint32 CantBeKnockedOffBike : 2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
            uint32 bHasBeenRendered : 1;
            uint32 bIsCached : 1;
            uint32 bPushOtherPeds : 1;   // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to get in a car)
            uint32 bPedThirdFlags32 : 1; // unknown

            // 13th byte starts here (m_nFourthPedFlags)
            uint32 bHasBulletProofVest : 1;
            uint32 bUsingMobilePhone : 1;
            uint32 bUpperBodyDamageAnimsOnly : 1;
            uint32 bStuckUnderCar : 1;
            uint32 bKeepTasksAfterCleanUp : 1; // If true ped will carry on with task even after cleanup
            uint32 bIsDyingStuck : 1;
            uint32 bIgnoreHeightCheckOnGotoPointTask : 1; // set when walking round buildings, reset when task quits
            uint32 bForceDieInCar : 1;

            uint32 bCheckColAboveHead : 1;
            uint32 bIgnoreWeaponRange : 1;
            uint32 bDruggedUp : 1;
            uint32 bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
            uint32 bSignalAfterKill : 1;
            uint32 bCanClimbOntoBoat : 1;
            uint32 bPedHitWallLastFrame : 1; // useful to store this so that AI knows (normal will still be available)
            uint32 bIgnoreHeightDifferenceFollowingNodes : 1;

            uint32 bMoveAnimSpeedHasBeenSetByTask : 1;
            uint32 bGetOutUpsideDownCar : 1;
            uint32 bJustGotOffTrain : 1;
            uint32 bDeathPickupsPersist : 1;
            uint32 bTestForShotInVehicle : 1;
            uint32 bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
        };
        uint32 m_nPedFlags;
        uint32 m_nSecondPedFlags;
        uint32 m_nThirdPedFlags;
        uint32 m_nFourthPedFlags;
    };
    CPedIntelligence*   m_pIntelligence;
    CPlayerPedData*     m_pPlayerData;
    ePedCreatedBy       m_nCreatedBy;
    char                field_485[3];
    AnimBlendFrameData* m_apBones[TOTAL_PED_NODES]; // for Index, see ePedNode
    AssocGroupId        m_nAnimGroup;
    CVector2D           m_vecAnimMovingShiftLocal;
    CAcquaintance m_acquaintance;
    RpClump*            m_pWeaponObject;
    RwFrame*            m_pGunflashObject;
    RwObject*           m_pGogglesObject;
    uint8*              m_pGogglesState;
    int16               m_nWeaponGunflashAlphaMP1;
    int16               field_506;
    int16               m_nWeaponGunflashAlphaMP2;
    int16               field_50A;
    CPedIK              m_pedIK;
    int32               field_52C;
    ePedState           m_nPedState;
    int32               m_nMoveState;
    int32               m_nSwimmingMoveState; // type is eMoveState and used for swimming in CTaskSimpleSwim::ProcessPed
    int32               field_53C;
    float               m_fHealth;
    float               m_fMaxHealth;
    float               m_fArmour;
    uint32              m_nTimeTillWeNeedThisPed;
    CVector2D           m_vecAnimMovingShift;
    float               m_fCurrentRotation;
    float               m_fAimingRotation;
    float               m_fHeadingChangeRate;
    float               m_fMoveAnim; // not sure about the name here
    CEntity*            m_standingOnEntity;
    CVector             field_56C;
    CVector             field_578;
    CEntity*            m_pContactEntity;
    float               field_588;
    CVehicle*           m_pVehicle;
    int32               field_590;
    int32               field_594;
    ePedType            m_nPedType;
    CPedStat*           m_pStats;
    CWeapon             m_aWeapons[13];
    eWeaponType         m_nSavedWeapon;   // when we need to hide ped weapon, we save it temporary here
    eWeaponType         m_nDelayedWeapon; // 'delayed' weapon is like an additional weapon, f.e., simple cop has a nitestick as current and pistol as delayed weapons
    uint32              m_nDelayedWeaponAmmo;
    uint8               m_nActiveWeaponSlot;
    uint8               m_nWeaponShootingRate;
    uint8               m_nWeaponAccuracy;
    CEntity*            m_pTargetedObject;
    int32               field_720;
    int32               field_724;
    int32               field_728;
    eWeaponSkill        m_nWeaponSkill;
    eFightingStyle      m_nFightingStyle;
    char                m_nAllowedAttackMoves;
    char                field_72F;
    CFire*              m_pFire;
    int32               field_734;
    int32               field_738;
    int32               field_73C;
    int32               m_nWeaponModelId;
    int32               field_744;
    int32               field_748;
    int32               field_74C;
    int32               m_nDeathTime;
    char                m_nBodypartToRemove;
    char                field_755;
    int16               m_nMoneyCount;
    int32               field_758;
    int32               field_75C;
    char                m_nLastWeaponDamage;
    CEntity*            m_pLastEntityDamage;
    int32               field_768;
    CVector             m_vecTurretOffset;
    float               m_fTurretAngleA;
    float               m_fTurretAngleB;
    int32               m_nTurretPosnMode;
    int32               m_nTurretAmmo;
    void*               m_pCoverPoint;            // CCoverPoint *
    void*               m_pEnex;                  // CEnEx *
    float               m_fRemovalDistMultiplier; // 1.0 by default
    int16               m_nSpecialModelIndex;
    char                field_796[2];
    int32               field_798;

public:
    // class virtual functions

    void SetModelIndex(uint32 modelIndex) override;
    void DeleteRwObject() override;
    void ProcessControl() override;
    void Teleport(CVector destination, bool resetRotation) override;
    void SpecialEntityPreCollisionStuff(CPhysical* colPhysical, bool bIgnoreStuckCheck, bool& bCollisionDisabled, bool& bCollidedEntityCollisionIgnored, bool& bCollidedEntityUnableToMove, bool& bThisOrCollidedEntityStuck) override;
    uint8 SpecialEntityCalcCollisionSteps(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2) override;
    void PreRender() override;
    void Render() override;
    bool SetupLighting() override;
    void RemoveLighting(bool bRemove) override;
    void FlagToDestroyWhenNextProcessed() override;
    int32 ProcessEntityCollision(CPhysical* entity, CColPoint* colpoint) override;

    // Process applied anim 0x86C3B4
    virtual void SetMoveAnim();
    // always returns true 0x86C3B8
    virtual bool Save();
    // always returns true 0x86C3BC
    virtual bool Load();

    // class functions
    static void InjectHooks();

    static void* operator new(uint32 size);
    static void operator delete(void* data);

    CPed(ePedType);

    bool PedIsInvolvedInConversation();
    bool PedIsReadyForConversation(bool arg0);
    bool PedCanPickUpPickUp();
    void CreateDeadPedMoney();
    void CreateDeadPedPickupCoors(float* pX, float* pY, float* pZ);
    void CreateDeadPedWeaponPickups();
    static void Initialise();
    void SetPedStats(ePedStats statsType);
    void Update();
    void SetMoveState(eMoveState moveState);
    void SetMoveAnimSpeed(CAnimBlendAssociation* association);
    void StopNonPartialAnims();
    void RestartNonPartialAnims();
    bool CanUseTorsoWhenLooking();
    void SetLookFlag(float lookHeading, bool likeUnused, bool arg2);
    void SetLookFlag(CEntity* lookingTo, bool likeUnused, bool arg2);
    void SetAimFlag(CEntity* aimingTo);
    void ClearAimFlag();
    // Gets point direction relatively to ped
    int32 GetLocalDirection(const CVector2D& arg0);
    bool IsPedShootable();
    bool UseGroundColModel();
    bool CanPedReturnToState();
    bool CanSetPedState();
    bool CanBeArrested();
    bool CanStrafeOrMouseControl();
    bool CanBeDeleted();
    bool CanBeDeletedEvenInVehicle();
    void RemoveGogglesModel();
    int32 GetWeaponSlot(eWeaponType weaponType);
    void GrantAmmo(eWeaponType weaponType, uint32 ammo);
    void SetAmmo(eWeaponType weaponType, uint32 ammo);
    bool DoWeHaveWeaponAvailable(eWeaponType weaponType);
    bool DoGunFlash(int32 arg0, bool arg1);
    void SetGunFlashAlpha(bool rightHand);
    void ResetGunFlashAlpha();
    float GetBikeRidingSkill();
    static void ShoulderBoneRotation(RpClump* clump);
    void SetLookTimer(uint32 time);
    bool IsPlayer() const;
    void SetPedPositionInCar();
    void RestoreHeadingRate();
    static void RestoreHeadingRateCB(CAnimBlendAssociation* association, void* data);
    void SetRadioStation();
    void PositionAttachedPed();
    void Undress(char* modelName);
    void Dress();
    bool IsAlive();
    void UpdateStatEnteringVehicle();
    void UpdateStatLeavingVehicle();
    void GetTransformedBonePosition(RwV3d& inOffsetOutPosn, uint32 boneId, bool updateSkinBones);
    void ReleaseCoverPoint();
    CTask* GetHoldingTask();
    CEntity* GetEntityThatThisPedIsHolding();
    void DropEntityThatThisPedIsHolding(uint8 arg0);
    bool CanThrowEntityThatThisPedIsHolding();
    bool IsPlayingHandSignal();
    void StopPlayingHandSignal();
    float GetWalkAnimSpeed();
    void SetPedDefaultDecisionMaker();
    // limitAngle in radians
    bool CanSeeEntity(CEntity* entity, float limitAngle);
    bool PositionPedOutOfCollision(int32 exitDoor, CVehicle* vehicle, bool findClosestNode);
    bool PositionAnyPedOutOfCollision();
    bool OurPedCanSeeThisEntity(CEntity* entity, bool isSpotted);
    void SortPeds(CPed** pedList, int32 arg1, int32 arg2);
    void ClearLookFlag();
    float WorkOutHeadingForMovingFirstPerson(float heading);
    void UpdatePosition();
    void ProcessBuoyancy();
    bool IsPedInControl();
    void RemoveWeaponModel(int32 modelIndex);
    void AddGogglesModel(int32 modelIndex, bool* pGogglesType);
    void PutOnGoggles();
    eWeaponSkill GetWeaponSkill(eWeaponType weaponType);
    void SetWeaponSkill(eWeaponType weaponType, char skill);
    void ClearLook();
    bool TurnBody();
    bool IsPointerValid();
    void GetBonePosition(RwV3d& outPosition, uint32 boneId, bool updateSkinBones);
    CObject* GiveObjectToPedToHold(int32 modelIndex, uint8 replace);
    void SetPedState(ePedState pedState);
    //1 = default, 2 = scm/mission script
    void SetCharCreatedBy(uint8 createdBy);
    void CalculateNewVelocity();
    void CalculateNewOrientation();
    void ClearAll();
    void DoFootLanded(bool leftFoot, uint8 arg1);
    void PlayFootSteps();
    void AddWeaponModel(int32 modelIndex);
    void TakeOffGoggles();
    void GiveWeapon(eWeaponType weaponType, uint32 ammo, bool likeUnused);
    void GiveWeaponSet1();
    void GiveWeaponSet2();
    void GiveWeaponSet3();
    void SetCurrentWeapon(int32 slot);
    void SetCurrentWeapon(eWeaponType weaponType);
    void ClearWeapon(eWeaponType weaponType);
    void ClearWeapons();
    void RemoveWeaponWhenEnteringVehicle(int32 arg0);
    void ReplaceWeaponWhenExitingVehicle();
    void ReplaceWeaponForScriptedCutscene();
    void RemoveWeaponForScriptedCutscene();
    eWeaponSkill GetWeaponSkill();
    void PreRenderAfterTest();
    void SetIdle();
    void SetLook(float heading);
    void SetLook(CEntity* entity);
    void Look();
    CEntity* AttachPedToEntity(CEntity* entity, CVector offset, uint16 arg2, float arg3, eWeaponType weaponType);
    CEntity* AttachPedToBike(CEntity* entity, CVector offset, uint16 arg2, float arg3, float arg4, eWeaponType weaponType);
    void DettachPedFromEntity();
    void SetAimFlag(float heading);
    bool CanWeRunAndFireWithWeapon();
    void RequestDelayedWeapon();
    void GiveDelayedWeapon(eWeaponType weaponType, uint32 ammo);
    void GiveWeaponAtStartOfFight();
    void GiveWeaponWhenJoiningGang();
    bool GetPedTalking();
    void DisablePedSpeech(int16 arg0);
    void EnablePedSpeech();
    void DisablePedSpeechForScriptSpeech(int16 arg0);
    void EnablePedSpeechForScriptSpeech();
    void CanPedHoldConversation();
    void SayScript(int32 arg0, uint8 arg1, uint8 arg2, uint8 arg3);
    void Say(uint16 arg0, uint32 arg1 = 0, float arg2 = 1.0f, uint8 arg3 = 0, uint8 arg4 = 0, uint8 arg5 = 0);
    void RemoveBodyPart(int32 boneId, char localDir);
    void SpawnFlyingComponent(int32 arg0, char arg1);
    bool DoesLOSBulletHitPed(CColPoint& colPoint);
    void RemoveWeaponAnims(int32 likeUnused, float blendDelta);
    bool IsPedHeadAbovePos(float zPos);
    void KillPedWithCar(CVehicle* car, float fDamageIntensity, bool bPlayDeadAnimation);
    void MakeTyresMuddySectorList(CPtrList& ptrList);
    void DeadPedMakesTyresBloody();
    bool IsInVehicleThatHasADriver();
    void SetArmour(float v) { m_fArmour = v; }
    void SetWeaponShootingRange(uint8 r) { m_nWeaponShootingRate = r; }
    void SetWeaponAccuracy(uint8 acc) { m_nWeaponAccuracy = acc; }

    CVehicle* GetVehicleIfInOne() { return bInVehicle ? m_pVehicle : nullptr; }
    uint8 GetCreatedBy() { return m_nCreatedBy; }
    bool IsCreatedBy(ePedCreatedBy v) const noexcept { return v == m_nCreatedBy; }
    bool IsCreatedByMission() const noexcept { return IsCreatedBy(ePedCreatedBy::PED_MISSION); }
    CPedStuckChecker& GetStuckChecker() { return m_pIntelligence->m_pedStuckChecker; }
    int32 GetGroupId() { return m_pPlayerData->m_nPlayerGroup; }
    CPedGroup& GetGroup() { return CPedGroups::GetGroup(m_pPlayerData->m_nPlayerGroup); }
    CPedIntelligence* GetIntelligence() { return m_pIntelligence; }
    CPedIntelligence* GetIntelligence() const { return m_pIntelligence; }
    CTaskManager& GetTaskManager() { return m_pIntelligence->m_TaskMgr; }
    CEventGroup& GetEventGroup() { return m_pIntelligence->m_eventGroup; }
    CEventHandler& GetEventHandler() { return m_pIntelligence->m_eventHandler; }
    CEventHandlerHistory& GetEventHandlerHistory() { return m_pIntelligence->m_eventHandler.m_history; }
    CWeapon& GetWeaponInSlot(uint32_t slot) noexcept { return m_aWeapons[slot]; }
    CWeapon& GetActiveWeapon() noexcept { return GetWeaponInSlot(m_nActiveWeaponSlot); }
    void SetSavedWeapon(eWeaponType weapon) { m_nSavedWeapon = weapon; }
    bool IsStateDriving() const noexcept { return m_nPedState == PEDSTATE_DRIVING; }
    bool IsInVehicleAsPassenger() const noexcept;

    CCopPed*       AsCop()       { return reinterpret_cast<CCopPed*>(this); }
    CCivilianPed*  AsCivilian()  { return reinterpret_cast<CCivilianPed*>(this); }
    CEmergencyPed* AsEmergency() { return reinterpret_cast<CEmergencyPed*>(this); }
    CPlayerPed*    AsPlayer()    { return reinterpret_cast<CPlayerPed*>(this); }

    bool IsFollowerOfGroup(const CPedGroup& group);
};

RwObject* SetPedAtomicVisibilityCB(RwObject* rwObject, void* data);
bool IsPedPointerValid(CPed* ped);
