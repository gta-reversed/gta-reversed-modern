/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CPed::InjectHooks()
{
    ReversibleHooks::Install("CPed", "IsPedInControl", 0x5E3960, &CPed::IsPedInControl);
    ReversibleHooks::Install("CPed", "IsAlive", 0x5E0170, &CPed::IsAlive);
    ReversibleHooks::Install("CPed", "ClearWeapons", 0x5E6320, &CPed::ClearWeapons);
    ReversibleHooks::Install("CPed", "GetWeaponSlot", 0x5DF200, &CPed::GetWeaponSlot);
    ReversibleHooks::Install("CPed", "CanBeArrested", 0x5DF060, &CPed::CanBeArrested);
    ReversibleHooks::Install("CPed", "CanStrafeOrMouseControl", 0x5DF090, &CPed::CanStrafeOrMouseControl);
    ReversibleHooks::Install("CPed", "CanPedReturnToState", 0x5DF000, &CPed::CanPedReturnToState);
    ReversibleHooks::Install("CPed", "GiveWeaponWhenJoiningGang", 0x5E8BE0, &CPed::GiveWeaponWhenJoiningGang);
    ReversibleHooks::Install("CPed", "GetWeaponSkill_char", 0x5E6580, (char(CPed::*)()) &CPed::GetWeaponSkill);
    ReversibleHooks::Install("CPed", "ReplaceWeaponForScriptedCutscene", 0x5E6530, &CPed::ReplaceWeaponForScriptedCutscene);
    ReversibleHooks::Install("CPed", "RemoveWeaponForScriptedCutscene", 0x5E6550, &CPed::RemoveWeaponForScriptedCutscene);
    ReversibleHooks::Install("CPed", "GiveWeaponAtStartOfFight", 0x5E8AB0, &CPed::GiveWeaponAtStartOfFight);
    ReversibleHooks::Install("CPed", "ProcessBuoyancy", 0x5E1FA0, &CPed::ProcessBuoyancy);
    ReversibleHooks::Install("CPed", "Initialise", 0x5DEBB0, &CPed::Initialise);
    ReversibleHooks::Install("CPed", "IsPlayer", 0x5DF8F0, &CPed::IsPlayer);
}

CPed::CPed(ePedType pedtype) : CPhysical(), m_aWeapons{ plugin::dummy, plugin::dummy, plugin::dummy,
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

// 0x5DEBB0
void CPed::Initialise() {
    CPedType::Initialise();
    CCarEnterExit::SetAnimOffsetForEnterOrExitVehicle();
}

// unused
// 0x5DEBC0
void CPed::SetPedStats(ePedStats statsType) {
    // auto index = static_cast<int>(statsType);
    // m_pStats = &CPedStats::ms_apPedStats[index];
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
    return
        m_nPedState <= PEDSTATE_STATES_NO_AI &&
        m_nPedState != PEDSTATE_AIMGUN &&
        m_nPedState != PEDSTATE_ATTACK &&
        m_nPedState != PEDSTATE_FIGHT &&
        m_nPedState != PEDSTATE_EVADE_STEP &&
        m_nPedState != PEDSTATE_SNIPER_MODE &&
        m_nPedState != PEDSTATE_LOOK_ENTITY;
}

// Converted from thiscall bool CPed::CanSetPedState(void) 0x5DF030
bool CPed::CanSetPedState()
{
    return ((bool(__thiscall *)(CPed*))0x5DF030)(this);
}

bool CPed::CanBeArrested()
{
    return
        m_nPedState != PEDSTATE_DIE &&
        m_nPedState != PEDSTATE_DEAD &&
        m_nPedState != PEDSTATE_ARRESTED &&
        m_nPedState != PEDSTATE_ENTER_CAR &&
        m_nPedState != PEDSTATE_EXIT_CAR;
}

bool CPed::CanStrafeOrMouseControl()
{
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
    return CWeaponInfo::GetWeaponInfo(weaponType, 1)->m_nSlot;
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

// 0x5DF560
void CPed::ShoulderBoneRotation(RpClump* clump)
{
    plugin::Call<0x5DF560, RpClump*>(clump);
}

// Converted from thiscall void CPed::SetLookTimer(uint time) 0x5DF8D0
void CPed::SetLookTimer(unsigned int time)
{
    ((void(__thiscall *)(CPed*, unsigned int))0x5DF8D0)(this, time);
}

// 0x5DF8F0
bool CPed::IsPlayer()
{
    return !m_nPedType || m_nPedType == PED_TYPE_PLAYER2;
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
    return m_nPedState != PEDSTATE_DIE && m_nPedState != PEDSTATE_DEAD;
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
bool CPed::PositionPedOutOfCollision(int exitDoor, CVehicle* vehicke, bool findClosestNode)
{
    return ((bool(__thiscall *)(CPed*, int, CVehicle*, bool))0x5E0820)(this, exitDoor, vehicke, findClosestNode);
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
    if (bInVehicle)
        return;

    float fBuoyancyMult = 1.1F;
    if (m_nPedState == ePedState::PEDSTATE_DEAD || m_nPedState == ePedState::PEDSTATE_DIE)
        fBuoyancyMult = 1.8F;

    float fBuoyancy = fBuoyancyMult * m_fMass / 125.0F;
    CVector vecBuoyancyTurnPoint;
    CVector vecBuoyancyForce;
    if (!mod_Buoyancy.ProcessBuoyancy(this, fBuoyancy, &vecBuoyancyTurnPoint, &vecBuoyancyForce)) {
        physicalFlags.bTouchingWater = false;
        auto pSwimTask = m_pIntelligence->GetTaskSwim();
        if (pSwimTask)
            pSwimTask->m_fSwimStopTime = 1000.0F;

        return;
    }

    if (bIsStanding) {
        auto& pStandingOnEntity = m_pContactEntity;
        if (pStandingOnEntity && pStandingOnEntity->m_nType == eEntityType::ENTITY_TYPE_VEHICLE) {
            auto pStandingOnVehicle = reinterpret_cast<CVehicle*>(pStandingOnEntity);
            if (pStandingOnVehicle->IsBoat() && !pStandingOnVehicle->physicalFlags.bDestroyed) {
                physicalFlags.bSubmergedInWater = false;
                auto pSwimTask = m_pIntelligence->GetTaskSwim();
                if (!pSwimTask)
                    return;

                pSwimTask->m_fSwimStopTime += CTimer::ms_fTimeStep;
                return;
            }
        }
    }

    if (m_pPlayerData) {
        const auto& vecPedPos = GetPosition();
        float fCheckZ = vecPedPos.z - 3.0F;
        CColPoint lineColPoint;
        CEntity* pColEntity;
        if (CWorld::ProcessVerticalLine(vecPedPos, fCheckZ, lineColPoint, pColEntity, false, true, false, false, false, false, nullptr)) {
            if (pColEntity->m_nType == eEntityType::ENTITY_TYPE_VEHICLE) {
                auto pColVehicle = reinterpret_cast<CVehicle*>(pColEntity);
                if (pColVehicle->IsBoat()
                    && !pColVehicle->physicalFlags.bDestroyed
                    && pColVehicle->GetMatrix().GetUp().z > 0.0F) {

                    physicalFlags.bSubmergedInWater = false;
                    return;
                }
            }
        }
    }

    // Those 4 are called for some reason
    /*
    CTimeCycle::GetAmbientRed();
    CTimeCycle::GetAmbientGreen();
    CTimeCycle::GetAmbientBlue();
    rand();
    */
    // Add splash particle if it's the first frame we're touching water, and
    // the movement of ped is downward, preventing particles from being created
    // if ped is standing still and water wave touches him
    if (!physicalFlags.bTouchingWater && m_vecMoveSpeed.z < -0.01F) {
        auto vecMoveDir = m_vecMoveSpeed * CTimer::ms_fTimeStep * 4.0F;
        auto vecSplashPos = GetPosition() + vecMoveDir;
        float fWaterZ;
        if (CWaterLevel::GetWaterLevel(vecSplashPos.x, vecSplashPos.y, vecSplashPos.z, &fWaterZ, true, nullptr)) {
            vecSplashPos.z = fWaterZ;
            g_fx.TriggerWaterSplash(vecSplashPos);
            AudioEngine.ReportWaterSplash(this, -100.0F, true);
        }
    }

    physicalFlags.bTouchingWater = true;
    physicalFlags.bSubmergedInWater = true;
    ApplyMoveForce(vecBuoyancyForce);

    if (CTimer::ms_fTimeStep / 125.0F < vecBuoyancyForce.z / m_fMass
        || GetPosition().z + 0.6F < mod_Buoyancy.m_fWaterLevel) {

        bIsStanding = false;
        bIsDrowning = true;

        bool bPlayerSwimmingOrClimbing = false;
        if (!IsPlayer()) {
            CEventInWater cEvent(0.75F);
            GetEventGroup().Add(&cEvent, false);
        }
        else {
            auto pSwimTask = m_pIntelligence->GetTaskSwim();
            if (pSwimTask) {
                pSwimTask->m_fSwimStopTime = 0.0F;
                bPlayerSwimmingOrClimbing = true;
            }
            else if (m_pIntelligence->GetTaskClimb()) {
                bPlayerSwimmingOrClimbing = true;
            }
            else {
                auto fAcceleration = vecBuoyancyForce.z / (CTimer::ms_fTimeStep * m_fMass / 125.0F);
                CEventInWater cEvent(fAcceleration);
                GetEventGroup().Add(&cEvent, false);
            }

            if (bPlayerSwimmingOrClimbing)
                return;
        }

        float fTimeStep = pow(0.9F, CTimer::ms_fTimeStep);
        m_vecMoveSpeed.x *= fTimeStep;
        m_vecMoveSpeed.y *= fTimeStep;
        if (m_vecMoveSpeed.z < 0.0F)
            m_vecMoveSpeed.z *= fTimeStep;

        return;
    }

    auto pSwimTask = m_pIntelligence->GetTaskSwim();
    if (bIsStanding && pSwimTask)
    {
        pSwimTask->m_fSwimStopTime += CTimer::ms_fTimeStep;
        return;
    }

    if (m_pPlayerData) {
        CVector vecHeadPos(0.0F, 0.0F, 0.1F);
        GetTransformedBonePosition(vecHeadPos, ePedBones::BONE_HEAD, false);
        if (vecHeadPos.z < mod_Buoyancy.m_fWaterLevel) {
            auto pPlayerPed = reinterpret_cast<CPlayerPed*>(this);
            pPlayerPed->HandlePlayerBreath(true, 1.0F);
        }
    }
}

// Can Pedestrians be moved or not? Like in air or being dead.
// 0x5E3960
bool CPed::IsPedInControl()
{
    if (!bIsLanding && !bIsInTheAir)
    {
        if (m_nPedState != PEDSTATE_DIE && m_nPedState != PEDSTATE_DEAD && m_nPedState != PEDSTATE_ARRESTED)
            return true;
    }
    return false;
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

// NOTSA
void CPed::GiveWeaponSet1() {
    GiveWeapon(WEAPON_BRASSKNUCKLE, 1, true);
    GiveWeapon(WEAPON_BASEBALLBAT, 1, true);
    GiveWeapon(WEAPON_MOLOTOV, 10, true);
    GiveWeapon(WEAPON_PISTOL, 100, true);
    GiveWeapon(WEAPON_SHOTGUN, 50, true);
    GiveWeapon(WEAPON_MICRO_UZI, 150, true);
    GiveWeapon(WEAPON_AK47, 120, true);
    GiveWeapon(WEAPON_COUNTRYRIFLE, 25, true);
    GiveWeapon(WEAPON_RLAUNCHER, 200, true);
    GiveWeapon(WEAPON_SPRAYCAN, 200, true);
}

// NOTSA
void CPed::GiveWeaponSet2() {
    GiveWeapon(WEAPON_KNIFE, 0, true);
    GiveWeapon(WEAPON_GRENADE, 10, true);
    GiveWeapon(WEAPON_DESERT_EAGLE, 40, true);
    GiveWeapon(WEAPON_SAWNOFF_SHOTGUN, 40, true);
    GiveWeapon(WEAPON_TEC9, 150, true);
    GiveWeapon(WEAPON_M4, 150, true);
    GiveWeapon(WEAPON_SNIPERRIFLE, 21, true);
    GiveWeapon(WEAPON_FLAMETHROWER, 500, true);
    GiveWeapon(WEAPON_EXTINGUISHER, 200, true);
}

// NOTSA
void CPed::GiveWeaponSet3() {
    GiveWeapon(WEAPON_CHAINSAW, 0, true);
    GiveWeapon(WEAPON_REMOTE_SATCHEL_CHARGE, 5, true);
    GiveWeapon(WEAPON_PISTOL_SILENCED, 40, true);
    GiveWeapon(WEAPON_SPAS12_SHOTGUN, 30, true);
    GiveWeapon(WEAPON_MP5, 100, true);
    GiveWeapon(WEAPON_M4, 150, true);
    GiveWeapon(WEAPON_RLAUNCHER_HS, 200, true);
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
    CPed::RemoveWeaponModel(-1);
    CPed::RemoveGogglesModel();
    for (auto & m_aWeapon : m_aWeapons)
    {
        m_aWeapon.Shutdown();
    }
    CWeaponInfo* getWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_UNARMED, 1);
    SetCurrentWeapon(getWeaponInfo->m_nSlot);
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
    m_nSavedWeapon = m_aWeapons[m_nActiveWeaponSlot].m_nType;
    SetCurrentWeapon(0);
}

// Converted from thiscall void CPed::RemoveWeaponForScriptedCutscene(void) 0x5E6550
void CPed::RemoveWeaponForScriptedCutscene()
{
    if (m_nSavedWeapon != WEAPON_UNIDENTIFIED)
    {
        CWeaponInfo* weaponInfo = CWeaponInfo::GetWeaponInfo(m_nSavedWeapon, 1);
        CPed::SetCurrentWeapon(weaponInfo->m_nSlot);
        m_nSavedWeapon = WEAPON_UNIDENTIFIED;
    }
}

char CPed::GetWeaponSkill()
{
    return CPed::GetWeaponSkill(m_aWeapons[m_nActiveWeaponSlot].m_nType);
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
    if (m_nCreatedBy != PED_MISSION && GetActiveWeapon().m_nType == eWeaponType::WEAPON_UNARMED)
    {
        const auto GiveRandomWeaponByType = [this](eWeaponType type, uint16_t maxRandom)
        {
            if ((m_nRandomSeed & 0x3FFu) >= maxRandom)
                return;

            if (m_nDelayedWeapon != eWeaponType::WEAPON_UNIDENTIFIED)
                return;

            GiveDelayedWeapon(type, 50);
            SetCurrentWeapon(GetWeaponSlot(type));
        };

        switch (m_nPedType)
        {
            case ePedType::PED_TYPE_GANG1:
            case ePedType::PED_TYPE_GANG2:
            case ePedType::PED_TYPE_GANG3:
            case ePedType::PED_TYPE_GANG4:
            case ePedType::PED_TYPE_GANG5:
            case ePedType::PED_TYPE_GANG6:
            case ePedType::PED_TYPE_GANG7:
            case ePedType::PED_TYPE_GANG8:
            case ePedType::PED_TYPE_GANG9:
            case ePedType::PED_TYPE_GANG10:
                GiveRandomWeaponByType(eWeaponType::WEAPON_PISTOL, 400);
                break;
            case ePedType::PED_TYPE_DEALER:
            case ePedType::PED_TYPE_CRIMINAL:
            case ePedType::PED_TYPE_PROSTITUTE:
                GiveRandomWeaponByType(eWeaponType::WEAPON_KNIFE, 200);
                GiveRandomWeaponByType(eWeaponType::WEAPON_PISTOL, 400);
                break;
            default:
                break;
        }
    }
}

void CPed::GiveWeaponWhenJoiningGang()
{
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
