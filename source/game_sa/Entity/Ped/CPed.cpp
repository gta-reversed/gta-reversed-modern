/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CPed::InjectHooks()
{
    HookInstall(0x5E3960, &CPed::IsPedInControl);
    HookInstall(0x5E0170, &CPed::IsAlive);
    HookInstall(0x5E6320, &CPed::ClearWeapons);
    HookInstall(0x5DF200, &CPed::GetWeaponSlot);
    HookInstall(0x5DF060, &CPed::CanBeArrested);
    HookInstall(0x5DF090, &CPed::CanStrafeOrMouseControl);
    HookInstall(0x5DF000, &CPed::CanPedReturnToState); 
    HookInstall(0x5E8BE0, &CPed::GiveWeaponWhenJoiningGang);
    HookInstall(0x5E6580, (char(CPed::*)()) &CPed::GetWeaponSkill);
    HookInstall(0x5E6530, &CPed::ReplaceWeaponForScriptedCutscene);
    HookInstall(0x5E6550, &CPed::RemoveWeaponForScriptedCutscene);
}

CPed::CPed(ePedType pedtype) : CPhysical(plugin::dummy), m_aWeapons{ plugin::dummy, plugin::dummy, plugin::dummy,
plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy,
plugin::dummy, plugin::dummy, plugin::dummy }
{
    ((void(__thiscall *)(CPed*, ePedType))0x5E8030)(this, pedtype);
}

// Converted from thiscall void* CPed::operator new(uint size) 0x5E4720
void* CPed::operator new(unsigned int size) {
    return ((void* (__cdecl *)(unsigned int))0x5E4720)(size);
}

// Converted from thiscall void CPed::operator delete(void *data) 0x5E4760
void CPed::operator delete(void* data) {
    ((void(__cdecl *)(void*))0x5E4760)(data);
}

// Converted from void CPed::SetMoveAnim(void) 0x5E4A00
void CPed::SetMoveAnim()
{
    ((void(__thiscall *)(CPed*))(*(void ***)this)[24])(this);
}

// Converted from bool CPed::Save(void) 0x5D5730
bool CPed::Save()
{
    return ((bool(__thiscall *)(CPed*))(*(void ***)this)[25])(this);
}

// Converted from bool CPed::Load(void) 0x5D4640
bool CPed::Load()
{
    return ((bool(__thiscall *)(CPed*))(*(void ***)this)[26])(this);
}

// Converted from thiscall bool CPed::PedIsInvolvedInConversation(void) 0x43AB90
bool CPed::PedIsInvolvedInConversation()
{
    return ((bool(__thiscall *)(CPed*))0x43AB90)(this);
}

// Converted from thiscall bool CPed::PedIsReadyForConversation(bool) 0x43ABA0
bool CPed::PedIsReadyForConversation(bool arg0)
{
    return ((bool(__thiscall *)(CPed*, bool))0x43ABA0)(this, arg0);
}

// Converted from thiscall bool CPed::PedCanPickUpPickUp(void) 0x455560
bool CPed::PedCanPickUpPickUp()
{
    return ((bool(__thiscall *)(CPed*))0x455560)(this);
}

// Converted from thiscall void CPed::CreateDeadPedMoney(void) 0x4590F0
void CPed::CreateDeadPedMoney()
{
    ((void(__thiscall *)(CPed*))0x4590F0)(this);
}

// Converted from thiscall void CPed::CreateDeadPedPickupCoors(float *pX,float *pY,float *pZ) 0x459180
void CPed::CreateDeadPedPickupCoors(float* pX, float* pY, float* pZ)
{
    ((void(__thiscall *)(CPed*, float*, float*, float*))0x459180)(this, pX, pY, pZ);
}

// Converted from thiscall void CPed::CreateDeadPedWeaponPickups(void) 0x4591D0
void CPed::CreateDeadPedWeaponPickups()
{
    ((void(__thiscall *)(CPed*))0x4591D0)(this);
}

// Converted from cdecl void CPed::Initialise(void) 0x5DEBB0
void CPed::Initialise()
{
    ((void(__cdecl *)())0x5DEBB0)();
}

// Converted from thiscall void CPed::SetPedStats(ePedStats statsType) 0x5DEBC0
void CPed::SetPedStats(ePedStats statsType)
{
    ((void(__thiscall *)(CPed*, ePedStats))0x5DEBC0)(this, statsType);
}

// Converted from thiscall void CPed::Update(void) 0x5DEBE0
void CPed::Update()
{
    ((void(__thiscall *)(CPed*))0x5DEBE0)(this);
}

// Converted from thiscall void CPed::SetMoveState(eMoveState moveState) 0x5DEC00
void CPed::SetMoveState(eMoveState moveState)
{
    ((void(__thiscall *)(CPed*, eMoveState))0x5DEC00)(this, moveState);
}

// Converted from thiscall void CPed::SetMoveAnimSpeed(CAnimBlendAssociation *association) 0x5DEC10
void CPed::SetMoveAnimSpeed(CAnimBlendAssociation* association)
{
    ((void(__thiscall *)(CPed*, CAnimBlendAssociation*))0x5DEC10)(this, association);
}

// Converted from thiscall void CPed::StopNonPartialAnims(void) 0x5DED10
void CPed::StopNonPartialAnims()
{
    ((void(__thiscall *)(CPed*))0x5DED10)(this);
}

// Converted from thiscall void CPed::RestartNonPartialAnims(void) 0x5DED50
void CPed::RestartNonPartialAnims()
{
    ((void(__thiscall *)(CPed*))0x5DED50)(this);
}

// Converted from thiscall bool CPed::CanUseTorsoWhenLooking(void) 0x5DED90
bool CPed::CanUseTorsoWhenLooking()
{
    return ((bool(__thiscall *)(CPed*))0x5DED90)(this);
}

// Converted from thiscall void CPed::SetLookFlag(float lookHeading,bool likeUnused,bool) 0x5DEDC0
void CPed::SetLookFlag(float lookHeading, bool likeUnused, bool arg2)
{
    ((void(__thiscall *)(CPed*, float, bool, bool))0x5DEDC0)(this, lookHeading, likeUnused, arg2);
}

// Converted from thiscall void CPed::SetLookFlag(CEntity *lookingTo,bool likeUnused,bool) 0x5DEE40
void CPed::SetLookFlag(CEntity* lookingTo, bool likeUnused, bool arg2)
{
    ((void(__thiscall *)(CPed*, CEntity*, bool, bool))0x5DEE40)(this, lookingTo, likeUnused, arg2);
}

// Converted from thiscall void CPed::SetAimFlag(CEntity *aimingTo) 0x5DEED0
void CPed::SetAimFlag(CEntity* aimingTo)
{
    ((void(__thiscall *)(CPed*, CEntity*))0x5DEED0)(this, aimingTo);
}

// Converted from thiscall void CPed::ClearAimFlag(void) 0x5DEF20
void CPed::ClearAimFlag()
{
    ((void(__thiscall *)(CPed*))0x5DEF20)(this);
}

// Converted from thiscall int CPed::GetLocalDirection(CVector2D const&) 0x5DEF60
int CPed::GetLocalDirection(CVector2D const& arg0)
{
    return ((int(__thiscall *)(CPed*, CVector2D const&))0x5DEF60)(this, arg0);
}

// Converted from thiscall bool CPed::IsPedShootable(void) 0x5DEFD0
bool CPed::IsPedShootable()
{
    return ((bool(__thiscall *)(CPed*))0x5DEFD0)(this);
}

// Converted from thiscall bool CPed::UseGroundColModel(void) 0x5DEFE0
bool CPed::UseGroundColModel()
{
    return ((bool(__thiscall *)(CPed*))0x5DEFE0)(this);
}

bool CPed::CanPedReturnToState()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CPed*))0x5DF000)(this);
#else
    return 
        m_nPedState <= PEDSTATE_STATES_NO_AI && 
        m_nPedState != PEDSTATE_AIMGUN &&
        m_nPedState != PEDSTATE_ATTACK && 
        m_nPedState != PEDSTATE_FIGHT && 
        m_nPedState != PEDSTATE_EVADE_STEP &&
        m_nPedState != PEDSTATE_SNIPER_MODE && 
        m_nPedState != PEDSTATE_LOOK_ENTITY;
#endif 
}

// Converted from thiscall bool CPed::CanSetPedState(void) 0x5DF030
bool CPed::CanSetPedState()
{
    return ((bool(__thiscall *)(CPed*))0x5DF030)(this);
}

bool CPed::CanBeArrested()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CPed*))0x5DF060)(this);
#else
    return 
        m_nPedState != PEDSTATE_DIE &&
        m_nPedState != PEDSTATE_DEAD && 
        m_nPedState != PEDSTATE_ARRESTED && 
        m_nPedState != PEDSTATE_ENTER_CAR && 
        m_nPedState != PEDSTATE_EXIT_CAR;
#endif
}

bool CPed::CanStrafeOrMouseControl()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall*)(CPed*))0x5DF090)(this);
#else
    return 
        m_nPedState == PEDSTATE_IDLE || 
        m_nPedState == PEDSTATE_FLEE_ENTITY ||
        m_nPedState == PEDSTATE_FLEE_POSITION || 
        m_nPedState == PEDSTATE_NONE || 
        m_nPedState == PEDSTATE_AIMGUN || 
        m_nPedState == PEDSTATE_ATTACK || 
        m_nPedState == PEDSTATE_FIGHT || 
        m_nPedState == PEDSTATE_JUMP ||
        m_nPedState == PEDSTATE_ANSWER_MOBILE;
#endif
}

// Converted from thiscall bool CPed::CanBeDeleted(void) 0x5DF100
bool CPed::CanBeDeleted()
{
    return ((bool(__thiscall *)(CPed*))0x5DF100)(this);
}

// Converted from thiscall bool CPed::CanBeDeletedEvenInVehicle(void) 0x5DF150
bool CPed::CanBeDeletedEvenInVehicle()
{
    return ((bool(__thiscall *)(CPed*))0x5DF150)(this);
}

// Converted from thiscall void CPed::RemoveGogglesModel(void) 0x5DF170
void CPed::RemoveGogglesModel()
{
    ((void(__thiscall *)(CPed*))0x5DF170)(this);
}

int CPed::GetWeaponSlot(eWeaponType weaponType)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((int(__thiscall *)(CPed*, eWeaponType))0x5DF200)(this, weaponType);
#else
    return CWeaponInfo::GetWeaponInfo(weaponType, 1)->m_nSlot;
#endif
}

// Converted from thiscall void CPed::GrantAmmo(eWeaponType weaponType,uint ammo) 0x5DF220
void CPed::GrantAmmo(eWeaponType weaponType, unsigned int ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, unsigned int))0x5DF220)(this, weaponType, ammo);
}

// Converted from thiscall void CPed::SetAmmo(eWeaponType weaponType,uint ammo) 0x5DF290
void CPed::SetAmmo(eWeaponType weaponType, unsigned int ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, unsigned int))0x5DF290)(this, weaponType, ammo);
}

// Converted from thiscall bool CPed::DoWeHaveWeaponAvailable(eWeaponType weaponType) 0x5DF300
bool CPed::DoWeHaveWeaponAvailable(eWeaponType weaponType)
{
    return ((bool(__thiscall *)(CPed*, eWeaponType))0x5DF300)(this, weaponType);
}

// Converted from thiscall bool CPed::DoGunFlash(int,bool) 0x5DF340
bool CPed::DoGunFlash(int arg0, bool arg1)
{
    return ((bool(__thiscall *)(CPed*, int, bool))0x5DF340)(this, arg0, arg1);
}

// Converted from thiscall void CPed::SetGunFlashAlpha(bool rightHand) 0x5DF400
void CPed::SetGunFlashAlpha(bool rightHand)
{
    ((void(__thiscall *)(CPed*, bool))0x5DF400)(this, rightHand);
}

// Converted from thiscall void CPed::ResetGunFlashAlpha(void) 0x5DF4E0
void CPed::ResetGunFlashAlpha()
{
    ((void(__thiscall *)(CPed*))0x5DF4E0)(this);
}

// Converted from thiscall float CPed::GetBikeRidingSkill(void) 0x5DF510
float CPed::GetBikeRidingSkill()
{
    return ((float(__thiscall *)(CPed*))0x5DF510)(this);
}

// Converted from thiscall void CPed::ShoulderBoneRotation(RpClump *clump) 0x5DF560
void CPed::ShoulderBoneRotation(RpClump* clump)
{
    ((void(__thiscall *)(CPed*, RpClump*))0x5DF560)(this, clump);
}

// Converted from thiscall void CPed::SetLookTimer(uint time) 0x5DF8D0
void CPed::SetLookTimer(unsigned int time)
{
    ((void(__thiscall *)(CPed*, unsigned int))0x5DF8D0)(this, time);
}

// Converted from thiscall bool CPed::IsPlayer(void) 0x5DF8F0
bool CPed::IsPlayer()
{
    return ((bool(__thiscall *)(CPed*))0x5DF8F0)(this);
}

// Converted from thiscall void CPed::SetPedPositionInCar(void) 0x5DF910
void CPed::SetPedPositionInCar()
{
    ((void(__thiscall *)(CPed*))0x5DF910)(this);
}

// Converted from thiscall void CPed::RestoreHeadingRate(void) 0x5DFD60
void CPed::RestoreHeadingRate()
{
    ((void(__thiscall *)(CPed*))0x5DFD60)(this);
}

// Converted from cdecl void CPed::RestoreHeadingRateCB(CAnimBlendAssociation *,void *data) 0x5DFD70
void CPed::RestoreHeadingRateCB(CAnimBlendAssociation* association, void* data)
{
    ((void(__cdecl *)(CAnimBlendAssociation*, void*))0x5DFD70)(association, data);
}

// Converted from thiscall void CPed::SetRadioStation(void) 0x5DFD90
void CPed::SetRadioStation()
{
    ((void(__thiscall*)(CPed*))0x5DFD90)(this);
}

// Converted from thiscall void CPed::PositionAttachedPed(void) 0x5DFDF0
void CPed::PositionAttachedPed()
{
    ((void(__thiscall *)(CPed*))0x5DFDF0)(this);
}

// Converted from thiscall void CPed::Undress(char *modelName) 0x5E00F0
void CPed::Undress(char* modelName)
{
    ((void(__thiscall *)(CPed*, char*))0x5E00F0)(this, modelName);
}

// Converted from thiscall void CPed::Dress(void) 0x5E0130
void CPed::Dress()
{
    ((void(__thiscall *)(CPed*))0x5E0130)(this);
}

// Converted from thiscall bool CPed::IsAlive(void) 0x5E0170
// Checks if the Pedestrian is still alive.
bool CPed::IsAlive()
{
#ifdef USE_DEFAULT_FUNCTIONS

    return ((bool(__thiscall *)(CPed*))0x5E0170)(this);
#else
    return m_nPedState != PEDSTATE_DIE && m_nPedState != PEDSTATE_DEAD;
#endif
}

// Converted from thiscall void CPed::UpdateStatEnteringVehicle(void) 0x5E01A0
void CPed::UpdateStatEnteringVehicle()
{
    ((void(__thiscall *)(CPed*))0x5E01A0)(this);
}

// Converted from thiscall void CPed::UpdateStatLeavingVehicle(void) 0x5E01B0
void CPed::UpdateStatLeavingVehicle()
{
    ((void(__thiscall *)(CPed*))0x5E01B0)(this);
}

// Converted from thiscall void CPed::GetTransformedBonePosition(RwV3d &inOffsetOutPosn,uint boneId,bool updateSkinBones) 0x5E01C0
void CPed::GetTransformedBonePosition(RwV3d& inOffsetOutPosn, unsigned int boneId, bool updateSkinBones)
{
    ((void(__thiscall *)(CPed*, RwV3d&, unsigned int, bool))0x5E01C0)(this, inOffsetOutPosn, boneId, updateSkinBones);
}

// Converted from thiscall void CPed::ReleaseCoverPoint(void) 0x5E0270
void CPed::ReleaseCoverPoint()
{
    ((void(__thiscall *)(CPed*))0x5E0270)(this);
}

// Converted from thiscall CTask* CPed::GetHoldingTask(void) 0x5E0290
CTask* CPed::GetHoldingTask()
{
    return ((CTask* (__thiscall *)(CPed*))0x5E0290)(this);
}

// Converted from thiscall CEntity* CPed::GetEntityThatThisPedIsHolding(void) 0x5E02E0
CEntity* CPed::GetEntityThatThisPedIsHolding()
{
    return ((CEntity* (__thiscall *)(CPed*))0x5E02E0)(this);
}

// Converted from thiscall void CPed::DropEntityThatThisPedIsHolding(uchar) 0x5E0360
void CPed::DropEntityThatThisPedIsHolding(unsigned char arg0)
{
    ((void(__thiscall *)(CPed*, unsigned char))0x5E0360)(this, arg0);
}

// Converted from thiscall bool CPed::CanThrowEntityThatThisPedIsHolding(void) 0x5E0400
bool CPed::CanThrowEntityThatThisPedIsHolding()
{
    return ((bool(__thiscall *)(CPed*))0x5E0400)(this);
}

// Converted from thiscall bool CPed::IsPlayingHandSignal(void) 0x5E0460
bool CPed::IsPlayingHandSignal()
{
    return ((bool(__thiscall *)(CPed*))0x5E0460)(this);
}

// Converted from thiscall void CPed::StopPlayingHandSignal(void) 0x5E0480
void CPed::StopPlayingHandSignal()
{
    ((void(__thiscall *)(CPed*))0x5E0480)(this);
}

// Converted from thiscall float CPed::GetWalkAnimSpeed(void) 0x5E04B0
float CPed::GetWalkAnimSpeed()
{
    return ((float(__thiscall *)(CPed*))0x5E04B0)(this);
}

// Converted from thiscall void CPed::SetPedDefaultDecisionMaker(void) 0x5E06E0
void CPed::SetPedDefaultDecisionMaker()
{
    ((void(__thiscall *)(CPed*))0x5E06E0)(this);
}

// Converted from thiscall bool CPed::CanSeeEntity(CEntity *entity,float limitAngle) 0x5E0730
bool CPed::CanSeeEntity(CEntity* entity, float limitAngle)
{
    return ((bool(__thiscall *)(CPed*, CEntity*, float))0x5E0730)(this, entity, limitAngle);
}

// Converted from thiscall bool CPed::PositionPedOutOfCollision(int,CVehicle *,bool) 0x5E0820
bool CPed::PositionPedOutOfCollision(int arg0, CVehicle* arg1, bool arg2)
{
    return ((bool(__thiscall *)(CPed*, int, CVehicle*, bool))0x5E0820)(this, arg0, arg1, arg2);
}

// Converted from thiscall bool CPed::PositionAnyPedOutOfCollision(void) 0x5E13C0
bool CPed::PositionAnyPedOutOfCollision()
{
    return ((bool(__thiscall *)(CPed*))0x5E13C0)(this);
}

// Converted from thiscall bool CPed::OurPedCanSeeThisEntity(CEntity *entity,bool isSpotted) 0x5E1660
bool CPed::OurPedCanSeeThisEntity(CEntity* entity, bool isSpotted)
{
    return ((bool(__thiscall *)(CPed*, CEntity*, bool))0x5E1660)(this, entity, isSpotted);
}

// Converted from thiscall void CPed::SortPeds(CPed** pedList,int,int) 0x5E17E0
void CPed::SortPeds(CPed** pedList, int arg1, int arg2)
{
    ((void(__thiscall *)(CPed*, CPed**, int, int))0x5E17E0)(this, pedList, arg1, arg2);
}

// Converted from thiscall void CPed::ClearLookFlag(void) 0x5E1950
void CPed::ClearLookFlag()
{
    ((void(__thiscall *)(CPed*))0x5E1950)(this);
}

// Converted from thiscall float CPed::WorkOutHeadingForMovingFirstPerson(float heading) 0x5E1A00
float CPed::WorkOutHeadingForMovingFirstPerson(float heading)
{
    return ((float(__thiscall *)(CPed*, float))0x5E1A00)(this, heading);
}

// Converted from thiscall void CPed::UpdatePosition(void) 0x5E1B10
void CPed::UpdatePosition()
{
    ((void(__thiscall *)(CPed*))0x5E1B10)(this);
}

// Converted from thiscall void CPed::ProcessBuoyancy(void) 0x5E1FA0
void CPed::ProcessBuoyancy()
{
    ((void(__thiscall *)(CPed*))0x5E1FA0)(this);
}

// Converted from thiscall bool CPed::IsPedInControl(void) 0x5E3960
// Can Pedestrains be moved or not? Like in air or being dead.
bool CPed::IsPedInControl()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((bool(__thiscall *)(CPed*))0x5E3960)(this);
#else
    if (!bIsLanding && !bIsInTheAir)
    {
        if (m_nPedState != PEDSTATE_DIE && m_nPedState != PEDSTATE_DEAD && m_nPedState != PEDSTATE_ARRESTED)
            return true;
    }
    return false;
#endif
}

// Converted from thiscall void CPed::RemoveWeaponModel(int modelIndex) 0x5E3990
void CPed::RemoveWeaponModel(int modelIndex)
{
    ((void(__thiscall *)(CPed*, int))0x5E3990)(this, modelIndex);
}

// Converted from thiscall void CPed::AddGogglesModel(int modelIndex,bool *pGogglesType) 0x5E3A90
void CPed::AddGogglesModel(int modelIndex, bool* pGogglesType)
{
    ((void(__thiscall *)(CPed*, int, bool*))0x5E3A90)(this, modelIndex, pGogglesType);
}

// Converted from thiscall void CPed::PutOnGoggles(void) 0x5E3AE0
void CPed::PutOnGoggles()
{
    ((void(__thiscall *)(CPed*))0x5E3AE0)(this);
}

char CPed::GetWeaponSkill(eWeaponType weaponType)
{
#ifdef USE_DEFAULT_FUNCTIONS
  return ((char(__thiscall*)(CPed*, eWeaponType))0x5E3B60)(this, weaponType);
#else
    if ( weaponType < WEAPON_PISTOL || weaponType > WEAPON_TEC9 )
        return 1;
    if (!m_nPedType || m_nPedType == PED_TYPE_PLAYER2)
    {
        int skillStat = CWeaponInfo::GetSkillStatIndex(weaponType);
        CWeaponInfo* pGolfClubWeaponInfo = CWeaponInfo::GetWeaponInfo(weaponType, WEAPON_GOLFCLUB);
        float golfClubStatLevel = static_cast<float>(pGolfClubWeaponInfo->m_nReqStatLevel);
        if (golfClubStatLevel <= CStats::GetStatValue(skillStat))
            return 2;
        CWeaponInfo* brassKnuckleWeaponInfo = CWeaponInfo::GetWeaponInfo(weaponType, WEAPON_BRASSKNUCKLE);
        float brassKnuckleStatLevel = static_cast<float>(brassKnuckleWeaponInfo->m_nReqStatLevel);
        if (brassKnuckleStatLevel > CStats::GetStatValue(skillStat))
            return 0;
        return 1;
    }
    if (weaponType != WEAPON_PISTOL || m_nPedType != PED_TYPE_COP)
        return m_nWeaponSkill;
    return 3;
#endif // USE_DEFAULT_FUNCTIONS
}

// Converted from thiscall void CPed::SetWeaponSkill(eWeaponType weaponType,char skill) 0x5E3C10
void CPed::SetWeaponSkill(eWeaponType weaponType, char skill)
{
    ((void(__thiscall *)(CPed*, eWeaponType, char))0x5E3C10)(this, weaponType, skill);
}

// Converted from thiscall void CPed::ClearLook(void) 0x5E3FF0
void CPed::ClearLook()
{
    ((void(__thiscall *)(CPed*))0x5E3FF0)(this);
}

// Converted from thiscall bool CPed::TurnBody(void) 0x5E4000
bool CPed::TurnBody()
{
    return ((bool(__thiscall *)(CPed*))0x5E4000)(this);
}

// Converted from thiscall bool CPed::IsPointerValid(void) 0x5E4220
bool CPed::IsPointerValid()
{
    return ((bool(__thiscall *)(CPed*))0x5E4220)(this);
}

// Converted from thiscall void CPed::GetBonePosition(RwV3d &outPosition,uint boneId,bool updateSkinBones) 0x5E4280
void CPed::GetBonePosition(RwV3d& outPosition, unsigned int boneId, bool updateSkinBones)
{
    ((void(__thiscall *)(CPed*, RwV3d&, unsigned int, bool))0x5E4280)(this, outPosition, boneId, updateSkinBones);
}

// Converted from thiscall CObject* CPed::GiveObjectToPedToHold(int modelIndex,uchar replace) 0x5E4390
CObject* CPed::GiveObjectToPedToHold(int modelIndex, unsigned char replace)
{
    return ((CObject* (__thiscall *)(CPed*, int, unsigned char))0x5E4390)(this, modelIndex, replace);
}

// Converted from thiscall void CPed::SetPedState(ePedState pedState) 0x5E4500
void CPed::SetPedState(ePedState pedState)
{
    ((void(__thiscall *)(CPed*, ePedState))0x5E4500)(this, pedState);
}

// Converted from thiscall void CPed::SetCharCreatedBy(uchar createdBy) 0x5E47E0
void CPed::SetCharCreatedBy(unsigned char createdBy)
{
    ((void(__thiscall *)(CPed*, unsigned char))0x5E47E0)(this, createdBy);
}

// Converted from thiscall void CPed::CalculateNewVelocity(void) 0x5E4C50
void CPed::CalculateNewVelocity()
{
    ((void(__thiscall *)(CPed*))0x5E4C50)(this);
}

// Converted from thiscall void CPed::CalculateNewOrientation(void) 0x5E52E0
void CPed::CalculateNewOrientation()
{
    ((void(__thiscall *)(CPed*))0x5E52E0)(this);
}

// Converted from thiscall void CPed::ClearAll(void) 0x5E5320
void CPed::ClearAll()
{
    ((void(__thiscall *)(CPed*))0x5E5320)(this);
}

// Converted from thiscall void CPed::DoFootLanded(bool leftFoot,uchar) 0x5E5380
void CPed::DoFootLanded(bool leftFoot, unsigned char arg1)
{
    ((void(__thiscall *)(CPed*, bool, unsigned char))0x5E5380)(this, leftFoot, arg1);
}

// Converted from thiscall void CPed::PlayFootSteps(void) 0x5E57F0
void CPed::PlayFootSteps()
{
    ((void(__thiscall *)(CPed*))0x5E57F0)(this);
}

// Converted from thiscall void CPed::AddWeaponModel(int modelIndex) 0x5E5ED0
void CPed::AddWeaponModel(int modelIndex)
{
    ((void(__thiscall *)(CPed*, int))0x5E5ED0)(this, modelIndex);
}

// Converted from thiscall void CPed::TakeOffGoggles(void) 0x5E6010
void CPed::TakeOffGoggles()
{
    ((void(__thiscall *)(CPed*))0x5E6010)(this);
}

// Converted from thiscall void CPed::GiveWeapon(eWeaponType weaponType,uint ammo,bool likeUnused) 0x5E6080
void CPed::GiveWeapon(eWeaponType weaponType, unsigned int ammo, bool likeUnused)
{
    ((void(__thiscall *)(CPed*, eWeaponType, unsigned int, bool))0x5E6080)(this, weaponType, ammo, likeUnused);
}

// Converted from thiscall void CPed::SetCurrentWeapon(int slot) 0x5E61F0
void CPed::SetCurrentWeapon(int slot)
{
    ((void(__thiscall *)(CPed*, int))0x5E61F0)(this, slot);
}

// Converted from thiscall void CPed::SetCurrentWeapon(eWeaponType weaponType) 0x5E6280
void CPed::SetCurrentWeapon(eWeaponType weaponType)
{
    ((void(__thiscall *)(CPed*, eWeaponType))0x5E6280)(this, weaponType);
}

// Converted from thiscall void CPed::ClearWeapon(eWeaponType weaponType) 0x5E62B0
void CPed::ClearWeapon(eWeaponType weaponType)
{
    ((void(__thiscall*)(CPed*, eWeaponType))0x5E62B0)(this, weaponType);
}

// Converted from thiscall void CPed::ClearWeapons(void) 0x5E6320
// Clears every weapon from the pedestrian.
void CPed::ClearWeapons()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CPed*))0x5E6320)(this);
#else
    CPed::RemoveWeaponModel(-1);
    CPed::RemoveGogglesModel();
    for(unsigned int i = 0; i < 13; i++)
    {
        m_aWeapons[i].Shutdown();
    }
    CWeaponInfo* getWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_UNARMED, 1);
    SetCurrentWeapon(getWeaponInfo->m_nSlot);
#endif
}

// Converted from thiscall void CPed::RemoveWeaponWhenEnteringVehicle(int) 0x5E6370
void CPed::RemoveWeaponWhenEnteringVehicle(int arg0)
{
    ((void(__thiscall *)(CPed*, int))0x5E6370)(this, arg0);
}

// Converted from thiscall void CPed::ReplaceWeaponWhenExitingVehicle(void) 0x5E6490
void CPed::ReplaceWeaponWhenExitingVehicle()
{
    ((void(__thiscall *)(CPed*))0x5E6490)(this);
}

// Converted from thiscall void CPed::ReplaceWeaponForScriptedCutscene(void) 0x5E6530
void CPed::ReplaceWeaponForScriptedCutscene()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CPed*))0x5E6530)(this);
#else
    m_nSavedWeapon = m_aWeapons[m_nActiveWeaponSlot].m_nType;
    SetCurrentWeapon(0);
#endif
}

// Converted from thiscall void CPed::RemoveWeaponForScriptedCutscene(void) 0x5E6550
void CPed::RemoveWeaponForScriptedCutscene()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall *)(CPed*))0x5E6550)(this);
#else
    if (m_nSavedWeapon != WEAPON_UNIDENTIFIED)
    {
        CWeaponInfo* weaponInfo = CWeaponInfo::GetWeaponInfo(m_nSavedWeapon, 1);
        CPed::SetCurrentWeapon(weaponInfo->m_nSlot);
        m_nSavedWeapon = WEAPON_UNIDENTIFIED;
    }
#endif
}

char CPed::GetWeaponSkill()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return ((char(__thiscall*)(CPed*))0x5E6580)(this);
#else
    return CPed::GetWeaponSkill(m_aWeapons[m_nActiveWeaponSlot].m_nType);
#endif
}

// Converted from thiscall void CPed::PreRenderAfterTest(void) 0x5E65A0
void CPed::PreRenderAfterTest()
{
    ((void(__thiscall *)(CPed*))0x5E65A0)(this);
}

// Converted from thiscall void CPed::SetIdle(void) 0x5E7980
void CPed::SetIdle()
{
    ((void(__thiscall *)(CPed*))0x5E7980)(this);
}

// Converted from thiscall void CPed::SetLook(float heading) 0x5E79B0
void CPed::SetLook(float heading)
{
    ((void(__thiscall *)(CPed*, float))0x5E79B0)(this, heading);
}

// Converted from thiscall void CPed::SetLook(CEntity *entity) 0x5E7A60
void CPed::SetLook(CEntity* entity)
{
    ((void(__thiscall *)(CPed*, CEntity*))0x5E7A60)(this, entity);
}

// Converted from thiscall void CPed::Look(void) 0x5E7B20
void CPed::Look()
{
    ((void(__thiscall *)(CPed*))0x5E7B20)(this);
}

// Converted from thiscall CEntity* CPed::AttachPedToEntity(CEntity *entity,CVector offset,ushort,float,eWeaponType weaponType) 0x5E7CB0
CEntity* CPed::AttachPedToEntity(CEntity* entity, CVector offset, unsigned short arg2, float arg3, eWeaponType weaponType)
{
    return ((CEntity* (__thiscall *)(CPed*, CEntity*, CVector, unsigned short, float, eWeaponType))0x5E7CB0)(this, entity, offset, arg2, arg3, weaponType);
}

// Converted from thiscall CEntity* CPed::AttachPedToBike(CEntity *entity,CVector offset,ushort,float,float,eWeaponType weaponType) 0x5E7E60
CEntity* CPed::AttachPedToBike(CEntity* entity, CVector offset, unsigned short arg2, float arg3, float arg4, eWeaponType weaponType)
{
    return ((CEntity* (__thiscall *)(CPed*, CEntity*, CVector, unsigned short, float, float, eWeaponType))0x5E7E60)(this, entity, offset, arg2, arg3, arg4, weaponType);
}

// Converted from thiscall void CPed::DettachPedFromEntity(void) 0x5E7EC0
void CPed::DettachPedFromEntity()
{
    ((void(__thiscall *)(CPed*))0x5E7EC0)(this);
}

// Converted from thiscall void CPed::SetAimFlag(float heading) 0x5E8830
void CPed::SetAimFlag(float heading)
{
    ((void(__thiscall *)(CPed*, float))0x5E8830)(this, heading);
}

// Converted from thiscall bool CPed::CanWeRunAndFireWithWeapon(void) 0x5E88E0
bool CPed::CanWeRunAndFireWithWeapon()
{
    return ((bool(__thiscall *)(CPed*))0x5E88E0)(this);
}

// Converted from thiscall void CPed::RequestDelayedWeapon(void) 0x5E8910
void CPed::RequestDelayedWeapon()
{
    ((void(__thiscall *)(CPed*))0x5E8910)(this);
}

// Converted from thiscall void CPed::GiveDelayedWeapon(eWeaponType weaponType,uint ammo) 0x5E89B0
void CPed::GiveDelayedWeapon(eWeaponType weaponType, unsigned int ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, unsigned int))0x5E89B0)(this, weaponType, ammo);
}

// Converted from cdecl bool IsPedPointerValid(CPed *ped) 0x5E8A30
bool IsPedPointerValid(CPed* ped)
{
    return ((bool(__cdecl *)(CPed*))0x5E8A30)(ped);
}

// Converted from thiscall void CPed::GiveWeaponAtStartOfFight(void) 0x5E8AB0
void CPed::GiveWeaponAtStartOfFight()
{
    ((void(__thiscall *)(CPed*))0x5E8AB0)(this);
}

void CPed::GiveWeaponWhenJoiningGang()
{
#ifdef USE_DEFAULT_FUNCTIONS
    ((void(__thiscall*)(CPed*))0x5E8BE0)(this);
#else
    if (m_aWeapons[m_nActiveWeaponSlot].m_nType == WEAPON_UNARMED && m_nDelayedWeapon == WEAPON_UNIDENTIFIED) {
        if (CCheat::m_aCheatsActive[eCheats::CHEAT_NO_ONE_CAN_STOP_US]) {
            GiveDelayedWeapon(WEAPON_AK47, 200);
            SetCurrentWeapon(CWeaponInfo::GetWeaponInfo(WEAPON_AK47, 1)->m_nSlot);
        }
        else {
            CWeaponInfo* pWeaponInfo = nullptr;
            if (CCheat::m_aCheatsActive[eCheats::CHEAT_ROCKET_MAYHEM]) {
                GiveDelayedWeapon(WEAPON_RLAUNCHER, 200);
                pWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_RLAUNCHER, 1);
            }
            else {
                CPed::GiveDelayedWeapon(WEAPON_PISTOL, 200);
                pWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_PISTOL, 1);
            }
            CPed::SetCurrentWeapon(pWeaponInfo->m_nSlot);
        }
    }
#endif
}

// Converted from thiscall bool CPed::GetPedTalking(void) 0x5EFF50
bool CPed::GetPedTalking()
{
    return ((bool(__thiscall *)(CPed*))0x5EFF50)(this);
}

// Converted from thiscall void CPed::DisablePedSpeech(short) 0x5EFF60
void CPed::DisablePedSpeech(short arg0)
{
    ((void(__thiscall *)(CPed*, short))0x5EFF60)(this, arg0);
}

// Converted from thiscall void CPed::EnablePedSpeech(void) 0x5EFF70
void CPed::EnablePedSpeech()
{
    ((void(__thiscall *)(CPed*))0x5EFF70)(this);
}

// Converted from thiscall void CPed::DisablePedSpeechForScriptSpeech(short) 0x5EFF80
void CPed::DisablePedSpeechForScriptSpeech(short arg0)
{
    ((void(__thiscall *)(CPed*, short))0x5EFF80)(this, arg0);
}

// Converted from thiscall void CPed::EnablePedSpeechForScriptSpeech(void) 0x5EFF90
void CPed::EnablePedSpeechForScriptSpeech()
{
    ((void(__thiscall *)(CPed*))0x5EFF90)(this);
}

// Converted from thiscall void CPed::CanPedHoldConversation(void) 0x5EFFA0
void CPed::CanPedHoldConversation()
{
    ((void(__thiscall *)(CPed*))0x5EFFA0)(this);
}

// Converted from thiscall void CPed::SayScript(int,uchar,uchar,uchar) 0x5EFFB0
void CPed::SayScript(int arg0, unsigned char arg1, unsigned char arg2, unsigned char arg3)
{
    ((void(__thiscall *)(CPed*, int, unsigned char, unsigned char, unsigned char))0x5EFFB0)(this, arg0, arg1, arg2, arg3);
}

// Converted from thiscall void CPed::Say(ushort,uint,float,uchar,uchar,uchar) 0x5EFFE0
void CPed::Say(unsigned short arg0, unsigned int arg1, float arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5)
{
    ((void(__thiscall *)(CPed*, unsigned short, unsigned int, float, unsigned char, unsigned char, unsigned char))0x5EFFE0)(this, arg0, arg1, arg2, arg3, arg4, arg5);
}

// Converted from cdecl RwObject* SetPedAtomicVisibilityCB(RwObject *rwObject,void *data) 0x5F0060
RwObject* SetPedAtomicVisibilityCB(RwObject* rwObject, void* data)
{
    return ((RwObject* (__cdecl *)(RwObject*, void*))0x5F0060)(rwObject, data);
}

// Converted from thiscall void CPed::RemoveBodyPart(int boneId,char localDir) 0x5F0140
void CPed::RemoveBodyPart(int boneId, char localDir)
{
    ((void(__thiscall *)(CPed*, int, char))0x5F0140)(this, boneId, localDir);
}

// Converted from thiscall void CPed::SpawnFlyingComponent(int,char) 0x5F0190
void CPed::SpawnFlyingComponent(int arg0, char arg1)
{
    ((void(__thiscall *)(CPed*, int, char))0x5F0190)(this, arg0, arg1);
}

// Converted from thiscall bool CPed::DoesLOSBulletHitPed(CColPoint &colPoint) 0x5F01A0
bool CPed::DoesLOSBulletHitPed(CColPoint& colPoint)
{
    return ((bool(__thiscall *)(CPed*, CColPoint&))0x5F01A0)(this, colPoint);
}

// Converted from thiscall void CPed::RemoveWeaponAnims(int likeUnused,float blendDelta) 0x5F0250
void CPed::RemoveWeaponAnims(int likeUnused, float blendDelta)
{
    ((void(__thiscall *)(CPed*, int, float))0x5F0250)(this, likeUnused, blendDelta);
}

// Converted from thiscall bool CPed::IsPedHeadAbovePos(float zPos) 0x5F02C0
bool CPed::IsPedHeadAbovePos(float zPos)
{
    return ((bool(__thiscall *)(CPed*, float))0x5F02C0)(this, zPos);
}

// Converted from thiscall void CPed::KillPedWithCar(CVehicle *car,float,bool) 0x5F0360
void CPed::KillPedWithCar(CVehicle* car, float fDamageIntensity, bool bPlayDeadAnimation)
{
    ((void(__thiscall *)(CPed*, CVehicle*, float, bool))0x5F0360)(this, car, fDamageIntensity, bPlayDeadAnimation);
}

// Converted from thiscall void CPed::MakeTyresMuddySectorList(CPtrList &ptrList) 0x6AE0D0
void CPed::MakeTyresMuddySectorList(CPtrList& ptrList)
{
    ((void(__thiscall *)(CPed*, CPtrList&))0x6AE0D0)(this, ptrList);
}

// Converted from thiscall void CPed::DeadPedMakesTyresBloody(void) 0x6B4200
void CPed::DeadPedMakesTyresBloody()
{
    ((void(__thiscall *)(CPed*))0x6B4200)(this);
}

void CPed::SetModelIndex(unsigned int modelIndex)
{
    ((void(__thiscall *)(CPed*, unsigned int))0x5E4880)(this, modelIndex);
}

bool CPed::IsInVehicleThatHasADriver()
{
    if (bInVehicle) {
        if (m_pVehicle && m_pVehicle->IsPassenger(this) && m_pVehicle->m_pDriver)
            return true;
    }
    return false;
}
