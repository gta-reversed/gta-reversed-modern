/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "ePedType.h"
#include "CPhysical.h"
#include "CAEPedAudioEntity.h"
#include "CAEPedSpeechAudioEntity.h"
#include "CAEWeaponAudioEntity.h"
#include "CPedIntelligence.h"
#include "CPlayerData.h"
#include "AnimBlendFrameData.h"
#include "CPedAcquaintance.h"
#include "CPedIK.h"
#include "CWeapon.h"
#include "CVector2D.h"
#include "eWeaponType.h"
#include "ePedState.h"
#include "CAnimBlendAssociation.h"
#include "CFire.h"
#include "CPedGroups.h"

enum ePedCreatedBy
{
    PED_UNKNOWN = 0,
    PED_GAME = 1,
    PED_MISSION = 2,
};

enum ePedStats {

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

enum eFightingStyle
{
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

class  CPed : public CPhysical {
protected:
    CPed(plugin::dummy_func_t) : CPhysical(plugin::dummy), m_aWeapons{ plugin::dummy, plugin::dummy, plugin::dummy,
        plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy,
        plugin::dummy, plugin::dummy, plugin::dummy } {}
public:
    CAEPedAudioEntity			m_pedAudio;
    CAEPedSpeechAudioEntity		m_pedSpeech;
    CAEWeaponAudioEntity		m_weaponAudio;
    char field_43C[36];
    char field_460[8];
    int field_468;
    union {
        /* https://code.google.com/p/mtasa-blue/source/browse/tags/1.3.4/MTA10/game_sa/CPedSA.h */
        struct {
            // 1st byte starts here (m_nPedFlags)
            unsigned int bIsStanding : 1; // is ped standing on something
            unsigned int bWasStanding : 1; // was ped standing on something
            unsigned int bIsLooking : 1; // is ped looking at something or in a direction
            unsigned int bIsRestoringLook : 1; // is ped restoring head postion from a look
            unsigned int bIsAimingGun : 1; // is ped aiming gun
            unsigned int bIsRestoringGun : 1; // is ped moving gun back to default posn
            unsigned int bCanPointGunAtTarget : 1; // can ped point gun at target
            unsigned int bIsTalking : 1; // is ped talking(see Chat())

            unsigned int bInVehicle : 1; // is in a vehicle
            unsigned int bIsInTheAir : 1; // is in the air
            unsigned int bIsLanding : 1; // is landing after being in the air
            unsigned int bHitSomethingLastFrame : 1; // has been in a collision last fram
            unsigned int bIsNearCar : 1; // has been in a collision last fram
            unsigned int bRenderPedInCar : 1; // has been in a collision last fram
            unsigned int bUpdateAnimHeading : 1; // update ped heading due to heading change during anim sequence
            unsigned int bRemoveHead : 1; // waiting on AntiSpazTimer to remove head

            unsigned int bFiringWeapon : 1; // is pulling trigger
            unsigned int bHasACamera : 1; // does ped possess a camera to document accidents
            unsigned int bPedIsBleeding : 1; // Ped loses a lot of blood if true
            unsigned int bStopAndShoot : 1; // Ped cannot reach target to attack with fist, need to use gun
            unsigned int bIsPedDieAnimPlaying : 1; // is ped die animation finished so can dead now
            unsigned int bStayInSamePlace : 1; // when set, ped stays put
            unsigned int bKindaStayInSamePlace : 1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
            unsigned int bBeingChasedByPolice : 1; // use nodes for routefind

            unsigned int bNotAllowedToDuck : 1; // Is this ped allowed to duck at all?
            unsigned int bCrouchWhenShooting : 1; // duck behind cars etc
            unsigned int bIsDucking : 1; // duck behind cars etc
            unsigned int bGetUpAnimStarted : 1; // don't want to play getup anim if under something
            unsigned int bDoBloodyFootprints : 1; // unsigned int bIsLeader :1;
            unsigned int bDontDragMeOutCar : 1;
            unsigned int bStillOnValidPoly : 1; // set if the polygon the ped is on is still valid for collision
            unsigned int bAllowMedicsToReviveMe : 1;

            // 5th byte starts here (m_nSecondPedFlags)
            unsigned int bResetWalkAnims : 1;
            unsigned int bOnBoat : 1; // flee but only using nodes
            unsigned int bBusJacked : 1; // flee but only using nodes
            unsigned int bFadeOut : 1; // set if you want ped to fade out
            unsigned int bKnockedUpIntoAir : 1; // has ped been knocked up into the air by a car collision
            unsigned int bHitSteepSlope : 1; // has ped collided/is standing on a steep slope (surface type)
            unsigned int bCullExtraFarAway : 1; // special ped only gets culled if it's extra far away (for roadblocks)
            unsigned int bTryingToReachDryLand : 1; // has ped just exited boat and trying to get to dry land

            unsigned int bCollidedWithMyVehicle : 1;
            unsigned int bRichFromMugging : 1; // ped has lots of cash cause they've been mugging people
            unsigned int bChrisCriminal : 1; // Is a criminal as killed during Chris' police mission (should be counted as such)
            unsigned int bShakeFist : 1; // test shake hand at look entity
            unsigned int bNoCriticalHits : 1; // ped cannot be killed by a single bullet
            unsigned int bHasAlreadyBeenRecorded : 1; // Used for replays
            unsigned int bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
            unsigned int bFleeWhenStanding : 1; //

            unsigned int bMiamiViceCop : 1;  //
            unsigned int bMoneyHasBeenGivenByScript : 1; //
            unsigned int bHasBeenPhotographed : 1;  //
            unsigned int bIsDrowning : 1;
            unsigned int bDrownsInWater : 1;
            unsigned int bHeadStuckInCollision : 1;
            unsigned int bDeadPedInFrontOfCar : 1;
            unsigned int bStayInCarOnJack : 1;

            unsigned int bDontFight : 1;
            unsigned int bDoomAim : 1;
            unsigned int bCanBeShotInVehicle : 1;
            unsigned int bPushedAlongByCar : 1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
            unsigned int bNeverEverTargetThisPed : 1;
            unsigned int bThisPedIsATargetPriority : 1;
            unsigned int bCrouchWhenScared : 1;
            unsigned int bKnockedOffBike : 1;

            // 9th byte starts here (m_nThirdPedFlags)
            unsigned int bDonePositionOutOfCollision : 1;
            unsigned int bDontRender : 1;
            unsigned int bHasBeenAddedToPopulation : 1;
            unsigned int bHasJustLeftCar : 1;
            unsigned int bIsInDisguise : 1;
            unsigned int bDoesntListenToPlayerGroupCommands : 1;
            unsigned int bIsBeingArrested : 1;
            unsigned int bHasJustSoughtCover : 1;

            unsigned int bKilledByStealth : 1;
            unsigned int bDoesntDropWeaponsWhenDead : 1;
            unsigned int bCalledPreRender : 1;
            unsigned int bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
            unsigned int bPartOfAttackWave : 1;
            unsigned int bClearRadarBlipOnDeath : 1;
            unsigned int bNeverLeavesGroup : 1; // flag that we want to test 3 extra spheres on col model
            unsigned int bTestForBlockedPositions : 1; // this sets these indicator flags for various posisions on the front of the ped

            unsigned int bRightArmBlocked : 1;
            unsigned int bLeftArmBlocked : 1;
            unsigned int bDuckRightArmBlocked : 1;
            unsigned int bMidriffBlockedForJump : 1;
            unsigned int bFallenDown : 1;
            unsigned int bUseAttractorInstantly : 1;
            unsigned int bDontAcceptIKLookAts : 1;
            unsigned int bHasAScriptBrain : 1;

            unsigned int bWaitingForScriptBrainToLoad : 1;
            unsigned int bHasGroupDriveTask : 1;
            unsigned int bCanExitCar : 1;
            unsigned int CantBeKnockedOffBike : 2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
            unsigned int bHasBeenRendered : 1;
            unsigned int bIsCached : 1;
            unsigned int bPushOtherPeds : 1; // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to get in a car)
            unsigned int bPedThirdFlags32 : 1; // unknown

            // 13th byte starts here (m_nFourthPedFlags)
            unsigned int bHasBulletProofVest : 1;
            unsigned int bUsingMobilePhone : 1;
            unsigned int bUpperBodyDamageAnimsOnly : 1;
            unsigned int bStuckUnderCar : 1;
            unsigned int bKeepTasksAfterCleanUp : 1; // If true ped will carry on with task even after cleanup
            unsigned int bIsDyingStuck : 1;
            unsigned int bIgnoreHeightCheckOnGotoPointTask : 1; // set when walking round buildings, reset when task quits
            unsigned int bForceDieInCar : 1;

            unsigned int bCheckColAboveHead : 1;
            unsigned int bIgnoreWeaponRange : 1;
            unsigned int bDruggedUp : 1;
            unsigned int bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
            unsigned int bSignalAfterKill : 1;
            unsigned int bCanClimbOntoBoat : 1;
            unsigned int bPedHitWallLastFrame : 1; // useful to store this so that AI knows (normal will still be available)
            unsigned int bIgnoreHeightDifferenceFollowingNodes : 1;

            unsigned int bMoveAnimSpeedHasBeenSetByTask : 1;
            unsigned int bGetOutUpsideDownCar : 1;
            unsigned int bJustGotOffTrain : 1;
            unsigned int bDeathPickupsPersist : 1;
            unsigned int bTestForShotInVehicle : 1;
            unsigned int bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
        };
        unsigned int m_nPedFlags;
        unsigned int m_nSecondPedFlags;
        unsigned int m_nThirdPedFlags;
        unsigned int m_nFourthPedFlags;
    };
    CPedIntelligence   *m_pIntelligence;
    CPlayerData        *m_pPlayerData;
    unsigned char       m_nCreatedBy; // see ePedCreatedBy
    char                field_485[3];
    AnimBlendFrameData *m_apBones[19];
    int        m_nAnimGroup;
    CVector2D           m_vecAnimMovingShiftLocal;
    CPedAcquaintance    m_acquaintance;
    RpClump            *m_pWeaponObject;
    RwFrame            *m_pGunflashObject;
    RwObject           *m_pGogglesObject;
    unsigned char      *m_pGogglesState;
    short               m_nWeaponGunflashAlphaMP1;
    short field_506;
    short               m_nWeaponGunflashAlphaMP2;
    short field_50A;
    CPedIK              m_pedIK;
    int field_52C;
    ePedState           m_nPedState; // see ePedState
    int                 m_nMoveState;
    int m_nSwimmingMoveState; // type is eMoveState and used for swimming in CTaskSimpleSwim::ProcessPed
    int field_53C;
    float               m_fHealth;
    float               m_fMaxHealth;
    float               m_fArmour;
    int field_54C;
    CVector2D           m_vecAnimMovingShift;
    float               m_fCurrentRotation;
    float               m_fAimingRotation;
    float               m_fHeadingChangeRate;
    float               m_fMoveAnim; // not sure about the name here
    CPed*               m_pSomePed; // not sure about the name here
    CVector field_56C;
    CVector field_578;
    CEntity            *m_pContactEntity;
    float field_588;
    CVehicle           *m_pVehicle;
    int field_590;
    int field_594;
    ePedType            m_nPedType;
    void               *m_pStats; // CPedStat *
    CWeapon             m_aWeapons[13];
    eWeaponType         m_nSavedWeapon; // when we need to hide ped weapon, we save it temporary here
    eWeaponType         m_nDelayedWeapon; // 'delayed' weapon is like an additional weapon, f.e., simple cop has a nitestick as current and pistol as delayed weapons
    unsigned int        m_nDelayedWeaponAmmo;
    unsigned char       m_nActiveWeaponSlot;
    unsigned char       m_nWeaponShootingRate;
    unsigned char       m_nWeaponAccuracy;
    CEntity            *m_pTargetedObject;
    int field_720;
    int field_724;
    int field_728;
    char                m_nWeaponSkill;
    char                m_nFightingStyle; // see eFightingStyle
    char                m_nAllowedAttackMoves;
    char field_72F;
    CFire              *m_pFire;
    int field_734;
    int field_738;
    int field_73C;
    int                 m_nWeaponModelId;
    int field_744;
    int field_748;
    int field_74C;
    int                 m_nDeathTime;
    char                m_nBodypartToRemove;
    char field_755;
    short               m_nMoneyCount;
    int field_758;
    int field_75C;
    char                m_nLastWeaponDamage;
    CEntity            *m_pLastEntityDamage;
    int field_768;
    CVector             m_vecTurretOffset;
    float               m_fTurretAngleA;
    float               m_fTurretAngleB;
    int                 m_nTurretPosnMode;
    int                 m_nTurretAmmo;
    void               *m_pCoverPoint; // CCoverPoint *
    void               *m_pEnex; // CEnEx *
    float               m_fRemovalDistMultiplier; // 1.0 by default
    short               m_nSpecialModelIndex;
    char field_796[2];
    int field_798;

    // class virtual functions

    // Process applied anim
    virtual void SetMoveAnim();
    // always returns true
    virtual bool Save();
    // always returns true
    virtual bool Load();

    // class functions
    static void InjectHooks();

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
    int GetLocalDirection(CVector2D const& arg0);
    bool IsPedShootable();
    bool UseGroundColModel();
    bool CanPedReturnToState();
    bool CanSetPedState();
    bool CanBeArrested();
    bool CanStrafeOrMouseControl();
    bool CanBeDeleted();
    bool CanBeDeletedEvenInVehicle();
    void RemoveGogglesModel();
    int GetWeaponSlot(eWeaponType weaponType);
    void GrantAmmo(eWeaponType weaponType, unsigned int ammo);
    void SetAmmo(eWeaponType weaponType, unsigned int ammo);
    bool DoWeHaveWeaponAvailable(eWeaponType weaponType);
    bool DoGunFlash(int arg0, bool arg1);
    void SetGunFlashAlpha(bool rightHand);
    void ResetGunFlashAlpha();
    float GetBikeRidingSkill();
    void ShoulderBoneRotation(RpClump* clump);
    void SetLookTimer(unsigned int time);
    bool IsPlayer();
    void SetPedPositionInCar();
    void RestoreHeadingRate();
    static void RestoreHeadingRateCB(CAnimBlendAssociation* association, void* data);
    void SetRadioStation();
    void PositionAttachedPed();
    void Undress(char* modelName);
    void Dress();
    bool IsAlive();
    // dummy function
    void UpdateStatEnteringVehicle();
    // dummy function
    void UpdateStatLeavingVehicle();
    void GetTransformedBonePosition(RwV3d& inOffsetOutPosn, unsigned int boneId, bool updateSkinBones);
    void ReleaseCoverPoint();
    CTask* GetHoldingTask();
    CEntity* GetEntityThatThisPedIsHolding();
    void DropEntityThatThisPedIsHolding(unsigned char arg0);
    bool CanThrowEntityThatThisPedIsHolding();
    bool IsPlayingHandSignal();
    void StopPlayingHandSignal();
    float GetWalkAnimSpeed();
    void SetPedDefaultDecisionMaker();
    // limitAngle in radians
    bool CanSeeEntity(CEntity* entity, float limitAngle);
    bool PositionPedOutOfCollision(int arg0, CVehicle* arg1, bool arg2);
    bool PositionAnyPedOutOfCollision();
    bool OurPedCanSeeThisEntity(CEntity* entity, bool isSpotted);
    void SortPeds(CPed** pedList, int arg1, int arg2);
    void ClearLookFlag();
    float WorkOutHeadingForMovingFirstPerson(float heading);
    void UpdatePosition();
    void ProcessBuoyancy();
    bool IsPedInControl();
    void RemoveWeaponModel(int modelIndex);
    void AddGogglesModel(int modelIndex, bool* pGogglesType);
    void PutOnGoggles();
    char GetWeaponSkill(eWeaponType weaponType);
    void SetWeaponSkill(eWeaponType weaponType, char skill);
    void ClearLook();
    bool TurnBody();
    bool IsPointerValid();
    void GetBonePosition(RwV3d& outPosition, unsigned int boneId, bool updateSkinBones);
    CObject* GiveObjectToPedToHold(int modelIndex, unsigned char replace);
    void SetPedState(ePedState pedState);
    //1 = default, 2 = scm/mission script
    void SetCharCreatedBy(unsigned char createdBy);
    void CalculateNewVelocity();
    void CalculateNewOrientation();
    void ClearAll();
    void DoFootLanded(bool leftFoot, unsigned char arg1);
    void PlayFootSteps();
    void AddWeaponModel(int modelIndex);
    void TakeOffGoggles();
    void GiveWeapon(eWeaponType weaponType, unsigned int ammo, bool likeUnused);
    void SetCurrentWeapon(int slot);
    void SetCurrentWeapon(eWeaponType weaponType);
    void ClearWeapon(eWeaponType weaponType);
    void ClearWeapons();
    void RemoveWeaponWhenEnteringVehicle(int arg0);
    void ReplaceWeaponWhenExitingVehicle();
    void ReplaceWeaponForScriptedCutscene();
    void RemoveWeaponForScriptedCutscene();
    char GetWeaponSkill();
    void PreRenderAfterTest();
    void SetIdle();
    void SetLook(float heading);
    void SetLook(CEntity* entity);
    void Look();
    CEntity* AttachPedToEntity(CEntity* entity, CVector offset, unsigned short arg2, float arg3, eWeaponType weaponType);
    CEntity* AttachPedToBike(CEntity* entity, CVector offset, unsigned short arg2, float arg3, float arg4, eWeaponType weaponType);
    void DettachPedFromEntity();
    void SetAimFlag(float heading);
    bool CanWeRunAndFireWithWeapon();
    void RequestDelayedWeapon();
    void GiveDelayedWeapon(eWeaponType weaponType, unsigned int ammo);
    void GiveWeaponAtStartOfFight();
    void GiveWeaponWhenJoiningGang();
    bool GetPedTalking();
    void DisablePedSpeech(short arg0);
    void EnablePedSpeech();
    void DisablePedSpeechForScriptSpeech(short arg0);
    void EnablePedSpeechForScriptSpeech();
    void CanPedHoldConversation();
    void SayScript(int arg0, unsigned char arg1, unsigned char arg2, unsigned char arg3);
    void Say(unsigned short arg0, unsigned int arg1, float arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5);
    void RemoveBodyPart(int boneId, char localDir);
    void SpawnFlyingComponent(int arg0, char arg1);
    bool DoesLOSBulletHitPed(CColPoint& colPoint);
    void RemoveWeaponAnims(int likeUnused, float blendDelta);
    bool IsPedHeadAbovePos(float zPos);
    void KillPedWithCar(CVehicle* car, float fDamageIntensity, bool bPlayDeadAnimation);
    void MakeTyresMuddySectorList(CPtrList& ptrList);
    void DeadPedMakesTyresBloody();
	void SetModelIndex(unsigned int modelIndex);
    bool IsInVehicleThatHasADriver();

    inline std::int32_t GetGroupId() { return m_pPlayerData->m_nPlayerGroup; }
    inline CPedGroup& GetGroup() { return CPedGroups::GetGroup(m_pPlayerData->m_nPlayerGroup); }
    inline CPedIntelligence* GetIntelligence() { return m_pIntelligence; }
    inline CTaskManager& GetTaskManager() { return m_pIntelligence->m_TaskMgr; }
    inline CEventGroup& GetEventGroup() { return m_pIntelligence->m_eventGroup; }
    inline CEventHandler& GetEventHandler() { return m_pIntelligence->m_eventHandler; }
    inline CEventHandlerHistory& GetEventHandlerHistory() { return m_pIntelligence->m_eventHandler.m_history; }
    inline CWeapon& GetActiveWeapon() { return m_aWeapons[m_nActiveWeaponSlot]; }
    inline RwMatrixTag* GetRwMatrix() { return m_pRwClump ? RwFrameGetMatrix(RpClumpGetFrame(m_pRwClump)) : nullptr; }

    static void* operator new(unsigned int size);
    static void operator delete(void* data);
};

VALIDATE_SIZE(CPed, 0x79C);

bool IsPedPointerValid(CPed* ped);
RwObject* SetPedAtomicVisibilityCB(RwObject* rwObject, void* data);
