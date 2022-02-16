/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Ped.h"

#include "PedType.h"
#include "Buoyancy.h"
#include "TaskSimpleSwim.h"
#include "PedStats.h"
#include "Conversations.h"
#include "TaskSimpleLand.h"
#include "AEAudioUtility.h"
#include "PedClothesDesc.h"

void CPed::InjectHooks() {
    RH_ScopedClass(CPed);
    RH_ScopedCategory("Entity/Ped");

    // RH_ScopedInstall(Constructor, 0x5E8030);
    // Install("CPed", "~CPed", 0x5E8620, static_cast<CPed*(CPed::*)()>(&CPed::Destructor));

    // Install("CPed", "operator delete", 0x5E4760, &CPed::operator delete);
    // Install("CPed", "operator new", 0x5E4720, &CPed::operator new);
    RH_ScopedInstall(SpawnFlyingComponent, 0x5F0190);
    RH_ScopedInstall(PedCanPickUpPickUp, 0x455560);
    RH_ScopedInstall(Update, 0x5DEBE0);
    RH_ScopedInstall(Initialise, 0x5DEBB0);
    RH_ScopedInstall(UpdateStatLeavingVehicle, 0x5E01B0);
    RH_ScopedInstall(UpdateStatEnteringVehicle, 0x5E01A0);
    RH_ScopedInstall(ShoulderBoneRotation, 0x5DF560);
    RH_ScopedInstall(RestoreHeadingRateCB, 0x5DFD70);
    RH_ScopedInstall(PedIsInvolvedInConversation, 0x43AB90);
    RH_ScopedInstall(ClearWeapons, 0x5E6320);
    RH_ScopedInstall(ClearWeapon, 0x5E62B0);
    RH_ScopedOverloadedInstall(SetCurrentWeapon, "", 0x5E6280, void(CPed::*)(eWeaponType));
    RH_ScopedOverloadedInstall(SetCurrentWeapon, "", 0x5E61F0, void(CPed::*)(int32));
    RH_ScopedInstall(GiveWeapon, 0x5E6080);
    RH_ScopedInstall(TakeOffGoggles, 0x5E6010);
    RH_ScopedInstall(AddWeaponModel, 0x5E5ED0);
    RH_ScopedInstall(PlayFootSteps, 0x5E57F0);
    // RH_ScopedInstall(DoFootLanded, 0x5E5380);
    RH_ScopedInstall(ClearAll, 0x5E5320);
    RH_ScopedInstall(CalculateNewOrientation, 0x5E52E0);
    // RH_ScopedInstall(CalculateNewVelocity, 0x5E4C50);
    RH_ScopedInstall(SetCharCreatedBy, 0x5E47E0);
    RH_ScopedInstall(SetPedState, 0x5E4500);
    // RH_ScopedInstall(GiveObjectToPedToHold, 0x5E4390);
    // RH_ScopedInstall(ClearLookFlag, 0x5E1950);
    // RH_ScopedInstall(WorkOutHeadingForMovingFirstPerson, 0x5E1A00);
    // RH_ScopedInstall(UpdatePosition, 0x5E1B10);
    // RH_ScopedInstall(MakeTyresMuddySectorList, 0x6AE0D0);
    RH_ScopedInstall(IsPedInControl, 0x5E3960);
    // RH_ScopedInstall(RemoveWeaponModel, 0x5E3990);
    // RH_ScopedInstall(RemoveWeaponWhenEnteringVehicle, 0x5E6370);
    // RH_ScopedInstall(AddGogglesModel, 0x5E3A90);
    // RH_ScopedInstall(SetWeaponSkill, 0x5E3C10);
    // RH_ScopedInstall(ClearLook, 0x5E3FF0);
    // RH_ScopedInstall(TurnBody, 0x5E4000);
    // RH_ScopedInstall(IsPointerValid, 0x5E4220);
    // RH_ScopedInstall(GetBonePosition, 0x5E4280);
    // RH_ScopedInstall(PutOnGoggles, 0x5E3AE0);
    // RH_ScopedInstall(SortPeds, 0x5E17E0);
    // RH_ScopedInstall(ReplaceWeaponWhenExitingVehicle, 0x5E6490);
    // RH_ScopedInstall(KillPedWithCar, 0x5F0360);
    // RH_ScopedInstall(IsPedHeadAbovePos, 0x5F02C0);
    // RH_ScopedInstall(RemoveWeaponAnims, 0x5F0250);
    // RH_ScopedInstall(DoesLOSBulletHitPed, 0x5F01A0);
    // RH_ScopedInstall(RemoveBodyPart, 0x5F0140);
    // RH_ScopedInstall(Say, 0x5EFFE0);
    // RH_ScopedInstall(SayScript, 0x5EFFB0);
    // RH_ScopedInstall(CanPedHoldConversation, 0x5EFFA0);
    // RH_ScopedInstall(EnablePedSpeechForScriptSpeech, 0x5EFF90);
    // RH_ScopedInstall(DisablePedSpeechForScriptSpeech, 0x5EFF80);
    // RH_ScopedInstall(EnablePedSpeech, 0x5EFF70);
    // RH_ScopedInstall(DisablePedSpeech, 0x5EFF60);
    // RH_ScopedInstall(GetPedTalking, 0x5EFF50);
    RH_ScopedInstall(GiveWeaponWhenJoiningGang, 0x5E8BE0);
    // RH_ScopedInstall(GiveDelayedWeapon, 0x5E89B0);
    RH_ScopedOverloadedInstall(GetWeaponSkill, "", 0x5E6580, eWeaponSkill(CPed::*)());
    // RH_ScopedInstall(PreRenderAfterTest, 0x5E65A0);
    // RH_ScopedInstall(SetIdle, 0x5E7980);
    // RH_ScopedOverloadedInstall(SetLook, "", 0x5E79B0, int32(CPed::*)(float));
    // RH_ScopedOverloadedInstall(SetLook, "", 0x5E7A60, int32(CPed::*)(CEntity *));
    // RH_ScopedInstall(Look, 0x5E7B20);
    RH_ScopedInstall(ReplaceWeaponForScriptedCutscene, 0x5E6530);
    RH_ScopedInstall(RemoveWeaponForScriptedCutscene, 0x5E6550);
    RH_ScopedInstall(GiveWeaponAtStartOfFight, 0x5E8AB0);
    RH_ScopedInstall(ProcessBuoyancy, 0x5E1FA0);
    // RH_ScopedInstall(PositionPedOutOfCollision, 0x5E0820);
    // RH_ScopedInstall(GrantAmmo, 0x5DF220);
    RH_ScopedInstall(GetWeaponSlot, 0x5DF200);
    // RH_ScopedInstall(PositionAnyPedOutOfCollision, 0x5E13C0);
    // RH_ScopedInstall(CanBeDeletedEvenInVehicle, 0x5DF150);
    // RH_ScopedInstall(CanBeDeleted, 0x5DF100);
    RH_ScopedInstall(CanStrafeOrMouseControl, 0x5DF090);
    RH_ScopedInstall(CanBeArrested, 0x5DF060);
    // RH_ScopedInstall(CanSetPedState, 0x5DF030);
    RH_ScopedInstall(CanPedReturnToState, 0x5DF000);
    // RH_ScopedInstall(UseGroundColModel, 0x5DEFE0);
    // RH_ScopedInstall(IsPedShootable, 0x5DEFD0);
    // RH_ScopedInstall(GetLocalDirection, 0x5DEF60);
    // RH_ScopedInstall(ClearAimFlag, 0x5DEF20);
    // RH_ScopedOverloadedInstall(SetAimFlag, "", 0x5DEED0, int8(CPed::*)(CEntity *));
    // RH_ScopedOverloadedInstall(SetLookFlag, "", 0x5DEE40, int8(CPed::*)(CEntity *, bool, bool));
    // RH_ScopedOverloadedInstall(SetLookFlag, "", 0x5DEDC0, int8(CPed::*)(float, bool, bool));
    // RH_ScopedInstall(CanUseTorsoWhenLooking, 0x5DED90);
    // RH_ScopedInstall(PedIsReadyForConversation, 0x43ABA0);
    // RH_ScopedInstall(CreateDeadPedMoney, 0x4590F0);
    // RH_ScopedInstall(CreateDeadPedPickupCoors, 0x459180);
    // RH_ScopedInstall(CreateDeadPedWeaponPickups, 0x4591D0);
    // RH_ScopedInstall(IsWearingGoggles, 0x479D10);
    // RH_ScopedInstall(SetAmmo, 0x5DF290);
    // RH_ScopedInstall(SetStayInSamePlace, 0x481090);
    // RH_ScopedInstall(SetPedStats, 0x5DEBC0);
    // RH_ScopedInstall(SetMoveState, 0x5DEC00);
    // RH_ScopedInstall(SetMoveAnimSpeed, 0x5DEC10);
    // RH_ScopedInstall(StopNonPartialAnims, 0x5DED10);
    // RH_ScopedInstall(RestartNonPartialAnims, 0x5DED50);
    // RH_ScopedInstall(DoWeHaveWeaponAvailable, 0x5DF300);
    // RH_ScopedInstall(RemoveGogglesModel, 0x5DF170);
    // RH_ScopedInstall(SetGunFlashAlpha, 0x5DF400);
    // RH_ScopedInstall(CanSeeEntity, 0x5E0730);
    // RH_ScopedInstall(SetPedDefaultDecisionMaker, 0x5E06E0);
    // RH_ScopedInstall(GetWalkAnimSpeed, 0x5E04B0);
    // RH_ScopedInstall(StopPlayingHandSignal, 0x5E0480);
    // RH_ScopedInstall(IsPlayingHandSignal, 0x5E0460);
    // RH_ScopedInstall(CanThrowEntityThatThisPedIsHolding, 0x5E0400);
    // RH_ScopedInstall(DropEntityThatThisPedIsHolding, 0x5E0360);
    // RH_ScopedInstall(GetEntityThatThisPedIsHolding, 0x5E02E0);
    // RH_ScopedInstall(GetHoldingTask, 0x5E0290);
    // RH_ScopedInstall(ReleaseCoverPoint, 0x5E0270);
    // RH_ScopedInstall(DoGunFlash, 0x5DF340);
    // RH_ScopedInstall(GetTransformedBonePosition, 0x5E01C0);
    RH_ScopedInstall(IsAlive, 0x5E0170);
    // RH_ScopedInstall(DeadPedMakesTyresBloody, 0x6B4200);
    // RH_ScopedInstall(Undress, 0x5E00F0);
    // RH_ScopedInstall(SetLookTimer, 0x5DF8D0);
    // RH_ScopedInstall(RestoreHeadingRate, 0x5DFD60);
    // RH_ScopedInstall(Dress, 0x5E0130);
    RH_ScopedInstall(IsPlayer, 0x5DF8F0);
    // RH_ScopedInstall(GetBikeRidingSkill, 0x5DF510);
    // RH_ScopedInstall(SetPedPositionInCar, 0x5DF910);
    // RH_ScopedInstall(SetRadioStation, 0x5DFD90);
    // RH_ScopedInstall(PositionAttachedPed, 0x5DFDF0);
    // RH_ScopedInstall(ResetGunFlashAlpha, 0x5DF4E0);
    // RH_ScopedInstall(SetModelIndex_Reversed, 0x5E4880);
    // RH_ScopedInstall(DeleteRwObject_Reversed, 0x5DEBF0);
    // RH_ScopedInstall(ProcessControl_Reversed, 0x5E8CD0);
    // RH_ScopedInstall(Teleport_Reversed, 0x5E4110);
    // RH_ScopedInstall(SpecialEntityPreCollisionStuff_Reversed, 0x5E3C30);
    // RH_ScopedInstall(SpecialEntityCalcCollisionSteps_Reversed, 0x5E3E90);
    // RH_ScopedInstall(PreRender_Reversed, 0x5E8A20);
    // RH_ScopedInstall(Render_Reversed, 0x5E7680);
    // RH_ScopedInstall(SetupLighting_Reversed, 0x553F00);
    // RH_ScopedInstall(RemoveLighting_Reversed, 0x5533B0);
    // RH_ScopedInstall(FlagToDestroyWhenNextProcessed_Reversed, 0x5E7B70);
    // RH_ScopedInstall(ProcessEntityCollision_Reversed, 0x5E2530);
    // RH_ScopedInstall(SetMoveAnim_Reversed, 0x5E4A00);
    // RH_ScopedInstall(Save_Reversed, 0x5D5730);
    // RH_ScopedInstall(Load_Reversed, 0x5D4640);
}

CPed::CPed(ePedType pedtype) : CPhysical(), m_aWeapons{ plugin::dummy, plugin::dummy, plugin::dummy,
plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy,
plugin::dummy, plugin::dummy, plugin::dummy }
{
    ((void(__thiscall *)(CPed*, ePedType))0x5E8030)(this, pedtype);
}

// 0x5E4720
void* CPed::operator new(uint32 size) {
    return ((void* (__cdecl *)(uint32))0x5E4720)(size);
}

// 0x5E4760
void CPed::operator delete(void* data) {
    ((void(__cdecl *)(void*))0x5E4760)(data);
}

// 0x5E4A00
void CPed::SetMoveAnim()
{
    ((void(__thiscall *)(CPed*))(*(void ***)this)[24])(this);
}

// 0x5D5730
bool CPed::Save()
{
    return ((bool(__thiscall *)(CPed*))(*(void ***)this)[25])(this);
}

// 0x5D4640
bool CPed::Load()
{
    return plugin::CallMethodAndReturn<bool, 0x5D4640, CPed*>(this);
}

// 0x43AB90
bool CPed::PedIsInvolvedInConversation()
{
    return this == CPedToPlayerConversations::m_pPed;
}

// 0x43ABA0
bool CPed::PedIsReadyForConversation(bool arg0)
{
    return ((bool(__thiscall *)(CPed*, bool))0x43ABA0)(this, arg0);
}

// 0x455560
bool CPed::PedCanPickUpPickUp()
{
    auto& taskmgr = FindPlayerPed(0)->GetTaskManager();
    return !taskmgr.FindActiveTaskByType(TASK_COMPLEX_ENTER_CAR_AS_DRIVER)
        && !taskmgr.FindActiveTaskByType(TASK_COMPLEX_USE_MOBILE_PHONE);
}

// 0x4590F0
void CPed::CreateDeadPedMoney()
{
    ((void(__thiscall *)(CPed*))0x4590F0)(this);
}

// 0x459180
void CPed::CreateDeadPedPickupCoors(float* pX, float* pY, float* pZ)
{
    ((void(__thiscall *)(CPed*, float*, float*, float*))0x459180)(this, pX, pY, pZ);
}

// 0x4591D0
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
    // auto index = static_cast<int32>(statsType);
    // m_pStats = &CPedStats::ms_apPedStats[index];
}

// 0x5DEBE0
void CPed::Update()
{
    // NOP
}

// 0x5DEC00
void CPed::SetMoveState(eMoveState moveState)
{
    ((void(__thiscall *)(CPed*, eMoveState))0x5DEC00)(this, moveState);
}

// 0x5DEC10
void CPed::SetMoveAnimSpeed(CAnimBlendAssociation* association)
{
    ((void(__thiscall *)(CPed*, CAnimBlendAssociation*))0x5DEC10)(this, association);
}

// 0x5DED10
void CPed::StopNonPartialAnims()
{
    ((void(__thiscall *)(CPed*))0x5DED10)(this);
}

// 0x5DED50
void CPed::RestartNonPartialAnims()
{
    ((void(__thiscall *)(CPed*))0x5DED50)(this);
}

// 0x5DED90
bool CPed::CanUseTorsoWhenLooking()
{
    return ((bool(__thiscall *)(CPed*))0x5DED90)(this);
}

// 0x5DEDC0
void CPed::SetLookFlag(float lookHeading, bool likeUnused, bool arg2)
{
    ((void(__thiscall *)(CPed*, float, bool, bool))0x5DEDC0)(this, lookHeading, likeUnused, arg2);
}

// 0x5DEE40
void CPed::SetLookFlag(CEntity* lookingTo, bool likeUnused, bool arg2)
{
    ((void(__thiscall *)(CPed*, CEntity*, bool, bool))0x5DEE40)(this, lookingTo, likeUnused, arg2);
}

// 0x5DEED0
void CPed::SetAimFlag(CEntity* aimingTo)
{
    ((void(__thiscall *)(CPed*, CEntity*))0x5DEED0)(this, aimingTo);
}

// 0x5DEF20
void CPed::ClearAimFlag()
{
    ((void(__thiscall *)(CPed*))0x5DEF20)(this);
}

// 0x5DEF60
int32 CPed::GetLocalDirection(const CVector2D& arg0)
{
    return ((int32(__thiscall *)(CPed*, const CVector2D&))0x5DEF60)(this, arg0);
}

// 0x5DEFD0
bool CPed::IsPedShootable()
{
    return ((bool(__thiscall *)(CPed*))0x5DEFD0)(this);
}

// 0x5DEFE0
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

// 0x5DF030
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

// 0x5DF100
bool CPed::CanBeDeleted()
{
    return ((bool(__thiscall *)(CPed*))0x5DF100)(this);
}

// 0x5DF150
bool CPed::CanBeDeletedEvenInVehicle()
{
    return ((bool(__thiscall *)(CPed*))0x5DF150)(this);
}

// 0x5DF170
void CPed::RemoveGogglesModel()
{
    ((void(__thiscall *)(CPed*))0x5DF170)(this);
}

int32 CPed::GetWeaponSlot(eWeaponType weaponType)
{
    return CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::STD)->m_nSlot;
}

// 0x5DF220
void CPed::GrantAmmo(eWeaponType weaponType, uint32 ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, uint32))0x5DF220)(this, weaponType, ammo);
}

// 0x5DF290
void CPed::SetAmmo(eWeaponType weaponType, uint32 ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, uint32))0x5DF290)(this, weaponType, ammo);
}

// 0x5DF300
bool CPed::DoWeHaveWeaponAvailable(eWeaponType weaponType)
{
    return ((bool(__thiscall *)(CPed*, eWeaponType))0x5DF300)(this, weaponType);
}

// 0x5DF340
bool CPed::DoGunFlash(int32 arg0, bool arg1)
{
    return ((bool(__thiscall *)(CPed*, int32, bool))0x5DF340)(this, arg0, arg1);
}

// 0x5DF400
void CPed::SetGunFlashAlpha(bool rightHand)
{
    ((void(__thiscall *)(CPed*, bool))0x5DF400)(this, rightHand);
}

// 0x5DF4E0
void CPed::ResetGunFlashAlpha()
{
    ((void(__thiscall *)(CPed*))0x5DF4E0)(this);
}

// 0x5DF510
float CPed::GetBikeRidingSkill()
{
    return ((float(__thiscall *)(CPed*))0x5DF510)(this);
}

// 0x5DF560
void CPed::ShoulderBoneRotation(RpClump* clump) {
    auto GetMatrixOf = [matrixArray = RpHAnimHierarchyGetMatrixArray(GetAnimHierarchyFromClump(clump))](ePedBones bone) mutable -> RwMatrix& {
        return matrixArray[(size_t)bone];
    };

    constexpr struct { ePedBones breast, upperArm, clavicle; } bones[]{
        {ePedBones::BONE_L_BREAST, ePedBones::BONE_L_UPPER_ARM, ePedBones::BONE_L_CLAVICLE},
        {ePedBones::BONE_R_BREAST, ePedBones::BONE_R_UPPER_ARM, ePedBones::BONE_R_CLAVICLE},
    };

    // Update left, and right sides
    for (auto [breast, upperArm, clavicle] : bones) {
        auto& breastRwMat = GetMatrixOf(breast);

        // Update matrix of l_breast to be the same as l_upper_arm's
        breastRwMat = GetMatrixOf(upperArm);

        CMatrix breastMat{ &breastRwMat };
        CMatrix clavicleMat{ &GetMatrixOf(clavicle) };

        // Transform matrix from left_clavicle's space to left_breast's
        breastMat *= Invert(clavicleMat); 

        // Half it's X rotation

        float x, y, z;
        breastMat.ConvertToEulerAngles(&x, &y, &z, ORDER_ZYX | SWAP_XZ);
        // Originally there is an `if` check of a static bool value, which is always true.
        x /= 2.f;
        breastMat.ConvertFromEulerAngles(x, y, z, ORDER_ZYX | SWAP_XZ);

        // Transform it back into it's own space
        breastMat *= clavicleMat;

        // Finally, update it's RW associated matrix
        breastMat.UpdateRW();      
    }
}

// 0x5DF8D0
void CPed::SetLookTimer(uint32 time)
{
    ((void(__thiscall *)(CPed*, uint32))0x5DF8D0)(this, time);
}

// 0x5DF8F0
bool CPed::IsPlayer() const
{
    return m_nPedType == PED_TYPE_PLAYER1 || m_nPedType == PED_TYPE_PLAYER2;
}

// 0x5DF910
void CPed::SetPedPositionInCar()
{
    ((void(__thiscall *)(CPed*))0x5DF910)(this);
}

// 0x5DFD60
void CPed::RestoreHeadingRate()
{
    ((void(__thiscall *)(CPed*))0x5DFD60)(this);
}

// 0x5DFD70
void CPed::RestoreHeadingRateCB(CAnimBlendAssociation* assoc, void* data) {
    UNUSED(assoc);

    auto& ped = *((CPed*)data);
    ped.m_fHeadingChangeRate = ped.m_pStats->m_fHeadingChangeRate;
}

// 0x5DFD90
void CPed::SetRadioStation()
{
    ((void(__thiscall*)(CPed*))0x5DFD90)(this);
}

// 0x5DFDF0
void CPed::PositionAttachedPed()
{
    ((void(__thiscall *)(CPed*))0x5DFDF0)(this);
}

// 0x5E00F0
void CPed::Undress(char* modelName)
{
    ((void(__thiscall *)(CPed*, char*))0x5E00F0)(this, modelName);
}

// 0x5E0130
void CPed::Dress()
{
    ((void(__thiscall *)(CPed*))0x5E0130)(this);
}

// 0x5E0170
// Checks if the Pedestrian is still alive.
bool CPed::IsAlive()
{
    return m_nPedState != PEDSTATE_DIE && m_nPedState != PEDSTATE_DEAD;
}

// 0x5E01A0
void CPed::UpdateStatEnteringVehicle()
{
    // NOP
}

// 0x5E01B0
void CPed::UpdateStatLeavingVehicle()
{
    // NOP
}

// 0x5E01C0
void CPed::GetTransformedBonePosition(RwV3d& inOffsetOutPosn, uint32 boneId, bool updateSkinBones)
{
    ((void(__thiscall *)(CPed*, RwV3d&, uint32, bool))0x5E01C0)(this, inOffsetOutPosn, boneId, updateSkinBones);
}

// 0x5E0270
void CPed::ReleaseCoverPoint()
{
    ((void(__thiscall *)(CPed*))0x5E0270)(this);
}

// 0x5E0290
CTask* CPed::GetHoldingTask()
{
    return ((CTask* (__thiscall *)(CPed*))0x5E0290)(this);
}

// 0x5E02E0
CEntity* CPed::GetEntityThatThisPedIsHolding()
{
    return ((CEntity* (__thiscall *)(CPed*))0x5E02E0)(this);
}

// 0x5E0360
void CPed::DropEntityThatThisPedIsHolding(uint8 arg0)
{
    ((void(__thiscall *)(CPed*, uint8))0x5E0360)(this, arg0);
}

// 0x5E0400
bool CPed::CanThrowEntityThatThisPedIsHolding()
{
    return ((bool(__thiscall *)(CPed*))0x5E0400)(this);
}

// 0x5E0460
bool CPed::IsPlayingHandSignal()
{
    return ((bool(__thiscall *)(CPed*))0x5E0460)(this);
}

// 0x5E0480
void CPed::StopPlayingHandSignal()
{
    ((void(__thiscall *)(CPed*))0x5E0480)(this);
}

// 0x5E04B0
float CPed::GetWalkAnimSpeed()
{
    return ((float(__thiscall *)(CPed*))0x5E04B0)(this);
}

// 0x5E06E0
void CPed::SetPedDefaultDecisionMaker()
{
    ((void(__thiscall *)(CPed*))0x5E06E0)(this);
}

// 0x5E0730
bool CPed::CanSeeEntity(CEntity* entity, float limitAngle)
{
    return ((bool(__thiscall *)(CPed*, CEntity*, float))0x5E0730)(this, entity, limitAngle);
}

// 0x5E0820
bool CPed::PositionPedOutOfCollision(int32 exitDoor, CVehicle* vehicle, bool findClosestNode)
{
    return ((bool(__thiscall *)(CPed*, int32, CVehicle*, bool))0x5E0820)(this, exitDoor, vehicle, findClosestNode);
}

// 0x5E13C0
bool CPed::PositionAnyPedOutOfCollision()
{
    return ((bool(__thiscall *)(CPed*))0x5E13C0)(this);
}

// 0x5E1660
bool CPed::OurPedCanSeeThisEntity(CEntity* entity, bool isSpotted)
{
    return ((bool(__thiscall *)(CPed*, CEntity*, bool))0x5E1660)(this, entity, isSpotted);
}

// 0x5E17E0
void CPed::SortPeds(CPed** pedList, int32 arg1, int32 arg2)
{
    ((void(__thiscall *)(CPed*, CPed**, int32, int32))0x5E17E0)(this, pedList, arg1, arg2);
}

// 0x5E1A00
float CPed::WorkOutHeadingForMovingFirstPerson(float heading)
{
    return ((float(__thiscall *)(CPed*, float))0x5E1A00)(this, heading);
}

// 0x5E1B10
void CPed::UpdatePosition()
{
    ((void(__thiscall *)(CPed*))0x5E1B10)(this);
}

// 0x5E1FA0
void CPed::ProcessBuoyancy()
{
    if (bInVehicle)
        return;

    float fBuoyancyMult = 1.1F;
    if (m_nPedState == PEDSTATE_DEAD || m_nPedState == PEDSTATE_DIE)
        fBuoyancyMult = 1.8F;

    float fBuoyancy = fBuoyancyMult * m_fMass / 125.0F;
    CVector vecBuoyancyTurnPoint;
    CVector vecBuoyancyForce;
    if (!mod_Buoyancy.ProcessBuoyancy(this, fBuoyancy, &vecBuoyancyTurnPoint, &vecBuoyancyForce)) {
        physicalFlags.bTouchingWater = false;
        auto swimTask = m_pIntelligence->GetTaskSwim();
        if (swimTask)
            swimTask->m_fSwimStopTime = 1000.0F;

        return;
    }

    if (bIsStanding) {
        auto& standingOnEntity = m_pContactEntity;
        if (standingOnEntity && standingOnEntity->IsVehicle()) {
            auto pStandingOnVehicle = standingOnEntity->AsVehicle();
            if (pStandingOnVehicle->IsBoat() && !pStandingOnVehicle->physicalFlags.bDestroyed) {
                physicalFlags.bSubmergedInWater = false;
                auto swimTask = m_pIntelligence->GetTaskSwim();
                if (!swimTask)
                    return;

                swimTask->m_fSwimStopTime += CTimer::GetTimeStep();
                return;
            }
        }
    }

    if (m_pPlayerData) {
        const auto& vecPedPos = GetPosition();
        float fCheckZ = vecPedPos.z - 3.0F;
        CColPoint lineColPoint;
        CEntity* colEntity;
        if (CWorld::ProcessVerticalLine(vecPedPos, fCheckZ, lineColPoint, colEntity, false, true, false, false, false, false, nullptr)) {
            if (colEntity->IsVehicle()) {
                auto colVehicle = colEntity->AsVehicle();
                if (colVehicle->IsBoat()
                    && !colVehicle->physicalFlags.bDestroyed
                    && colVehicle->GetMatrix().GetUp().z > 0.0F) {

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
        auto vecMoveDir = m_vecMoveSpeed * CTimer::GetTimeStep() * 4.0F;
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

    if (CTimer::GetTimeStep() / 125.0F < vecBuoyancyForce.z / m_fMass
        || GetPosition().z + 0.6F < mod_Buoyancy.m_fWaterLevel) {

        bIsStanding = false;
        bIsDrowning = true;

        bool bPlayerSwimmingOrClimbing = false;
        if (!IsPlayer()) {
            CEventInWater cEvent(0.75F);
            GetEventGroup().Add(&cEvent, false);
        }
        else {
            auto swimTask = m_pIntelligence->GetTaskSwim();
            if (swimTask) {
                swimTask->m_fSwimStopTime = 0.0F;
                bPlayerSwimmingOrClimbing = true;
            }
            else if (m_pIntelligence->GetTaskClimb()) {
                bPlayerSwimmingOrClimbing = true;
            }
            else {
                auto fAcceleration = vecBuoyancyForce.z / (CTimer::GetTimeStep() * m_fMass / 125.0F);
                CEventInWater cEvent(fAcceleration);
                GetEventGroup().Add(&cEvent, false);
            }

            if (bPlayerSwimmingOrClimbing)
                return;
        }

        float fTimeStep = pow(0.9F, CTimer::GetTimeStep());
        m_vecMoveSpeed.x *= fTimeStep;
        m_vecMoveSpeed.y *= fTimeStep;
        if (m_vecMoveSpeed.z < 0.0F)
            m_vecMoveSpeed.z *= fTimeStep;

        return;
    }

    auto swimTask = m_pIntelligence->GetTaskSwim();
    if (bIsStanding && swimTask)
    {
        swimTask->m_fSwimStopTime += CTimer::GetTimeStep();
        return;
    }

    if (m_pPlayerData) {
        CVector vecHeadPos(0.0F, 0.0F, 0.1F);
        GetTransformedBonePosition(vecHeadPos, ePedBones::BONE_HEAD, false);
        if (vecHeadPos.z < mod_Buoyancy.m_fWaterLevel) {
            AsPlayer()->HandlePlayerBreath(true, 1.0F);
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

// 0x5E3990
void CPed::RemoveWeaponModel(int32 modelIndex)
{
    ((void(__thiscall *)(CPed*, int32))0x5E3990)(this, modelIndex);
}

// 0x5E3A90
void CPed::AddGogglesModel(int32 modelIndex, bool* pGogglesType)
{
    ((void(__thiscall *)(CPed*, int32, bool*))0x5E3A90)(this, modelIndex, pGogglesType);
}

// 0x5E3AE0
void CPed::PutOnGoggles()
{
    ((void(__thiscall *)(CPed*))0x5E3AE0)(this);
}

eWeaponSkill CPed::GetWeaponSkill()
{
    return GetWeaponSkill(m_aWeapons[m_nActiveWeaponSlot].m_nType);
}

eWeaponSkill CPed::GetWeaponSkill(eWeaponType weaponType)
{
    if ( weaponType < WEAPON_PISTOL || weaponType > WEAPON_TEC9 )
        return eWeaponSkill::STD;

    if (!m_nPedType || m_nPedType == PED_TYPE_PLAYER2)
    {
        int32 skillStat = CWeaponInfo::GetSkillStatIndex(weaponType);
        CWeaponInfo* pGolfClubWeaponInfo = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::PRO);
        float golfClubStatLevel = static_cast<float>(pGolfClubWeaponInfo->m_fReqStatLevel);
        if (golfClubStatLevel <= CStats::GetStatValue((eStats)skillStat))
            return eWeaponSkill::PRO;

        CWeaponInfo* brassKnuckleWeaponInfo = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::STD);
        float brassKnuckleStatLevel = static_cast<float>(brassKnuckleWeaponInfo->m_fReqStatLevel);
        if (brassKnuckleStatLevel > CStats::GetStatValue((eStats)skillStat))
            return eWeaponSkill::POOR;

        return eWeaponSkill::STD;
    }

    if (weaponType != WEAPON_PISTOL || m_nPedType != PED_TYPE_COP)
        return m_nWeaponSkill;

    return eWeaponSkill::COP;
}

// 0x5E3C10
void CPed::SetWeaponSkill(eWeaponType weaponType, char skill)
{
    ((void(__thiscall *)(CPed*, eWeaponType, char))0x5E3C10)(this, weaponType, skill);
}

// 0x5E1950
void CPed::ClearLookFlag()
{
    ((void(__thiscall *)(CPed*))0x5E1950)(this);
}

// 0x5E3FF0
void CPed::ClearLook()
{
    ClearLookFlag();
}

// 0x5E4000
bool CPed::TurnBody()
{
    return ((bool(__thiscall *)(CPed*))0x5E4000)(this);
}

// 0x5E4220
bool CPed::IsPointerValid()
{
    return ((bool(__thiscall *)(CPed*))0x5E4220)(this);
}

// 0x5E4280
void CPed::GetBonePosition(RwV3d& outPosition, uint32 boneId, bool updateSkinBones)
{
    ((void(__thiscall *)(CPed*, RwV3d&, uint32, bool))0x5E4280)(this, outPosition, boneId, updateSkinBones);
}

// 0x5E4390
CObject* CPed::GiveObjectToPedToHold(int32 modelIndex, uint8 replace)
{
    return ((CObject* (__thiscall *)(CPed*, int32, uint8))0x5E4390)(this, modelIndex, replace);
}

// 0x5E4500
void CPed::SetPedState(ePedState pedState) {
    switch (state) {
    case ePedState ::PEDSTATE_DEAD:
    case ePedState ::PEDSTATE_DIE: {
        if (m_pCoverPoint) {
            CCoverPoint::ReleaseCoverPointForPed(m_pCoverPoint, this);
            m_pCoverPoint=  nullptr;
        }

        if (bClearRadarBlipOnDeath) {
            CRadar::ClearBlipForEntity(BLIP_CHAR, CPools::GetPedPool()->GetRef(this));
        }
        break;
    }
    }
    m_nPedState = pedState;
}

// 0x5E47E0
void CPed::SetCharCreatedBy(ePedCreatedBy createdBy) {
    m_nCreatedBy = createdBy;
    if (!IsPlayer()) {
        GetIntelligence()->SetPedDecisionMakerType(IsCreatedByMission() ? -1 : m_pStats->m_nDefaultDecisionMaker);
    } else {
        GetIntelligence()->SetPedDecisionMakerType(-2);
    }

    if (IsCreatedByMission()) {
        auto intel = GetIntelligence();

        intel->SetSeeingRange(30.f);
        intel->SetHearingRange(30.f);
        if (!IsPlayer()) {
            intel->m_fDmRadius = 0.f;
            intel->m_nDmNumPedsToScan = 0;
        }
    }
}

// 0x5E4C50
void CPed::CalculateNewVelocity()
{
    ((void(__thiscall *)(CPed*))0x5E4C50)(this);
}

// 0x5E52E0
void CPed::CalculateNewOrientation() {
    if (CReplay::Mode != REPLAY_MODE_1 && IsPedInControl()) {
        SetOrientation(0.f, 0.f, m_fCurrentRotation);
    }
}

// 0x5E5320
void CPed::ClearAll() {
    if (IsPedInControl() || IsStateDead()) {
        bRenderPedInCar = true;
        bHitSteepSlope = false;
        bCrouchWhenScared = false;
        m_nPedState = ePedState::PEDSTATE_NONE;
        m_nMoveState = eMoveState::PEDMOVE_NONE;
        m_pEntityIgnoredCollision = nullptr;
    }
}

// 0x5E5380
void CPed::DoFootLanded(bool leftFoot, uint8 arg1)
{
    ((void(__thiscall *)(CPed*, bool, uint8))0x5E5380)(this, leftFoot, arg1);
}

// 0x5E57F0
void CPed::PlayFootSteps() {
    auto& anim = *RpAnimBlendClumpGetFirstAssociation(m_pRwClump);

    const auto IsWalkRunSprintAnim = [&] {
        switch (anim.m_nAnimId) {
        case AnimationId::ANIM_ID_WALK:
        case AnimationId::ANIM_ID_RUN:
        case AnimationId::ANIM_ID_SPRINT: {
            return true;
        }
        }
        return false;
    };

    if (bDoBloodyFootprints) {
        if (m_nDeathTime && m_nDeathTime < 300) {
            m_nDeathTime -= 1;
            if (!m_nDeathTime) {
                bDoBloodyFootprints = false;
            }
        }
    }

    if (!bIsStanding) {
        return;
    }

    // 0x5E58FB, 0x5E5A0B, 0x5E5AB9, 0x5E5E64, 0x5E5D87
    const auto DoProcessLanding = [this] {
        if (bIsLanding) { // Redudant check.. probably inlined function?
            if (const auto task = GetTaskManager().GetSimplestActiveTask(); task->GetTaskType() == eTaskType::TASK_SIMPLE_LAND) {
                auto landedTask = task->As<CTaskSimpleLand>();
                if (landedTask->RightFootLanded()) {
                    DoFootLanded(false, true);
                } else if (landedTask->RightFootLanded()) {
                    DoFootLanded(true, true);
                }
            }
        }
    };

    // TODO: Is this inlined? What is this doing exactly? (Anim stuff)
    float blendAmount1{}, blendAmount2{};
    CAnimBlendAssociation* lastAssocWithFlag100{};
    auto* lastAssoc = &anim;
    do { // 0x5E58A1
        if (lastAssoc->m_nFlags & ANIM_FLAG_100) {
            blendAmount1 += lastAssoc->m_fBlendAmount;
            lastAssocWithFlag100 = lastAssoc;
        } else {
            if ((lastAssoc->m_nFlags & ANIM_FLAG_ADD_TO_BLEND) == 0) {
                if (lastAssoc->m_nAnimId != ANIM_ID_FIGHT_IDLE) {
                    if (lastAssoc->m_nFlags & ANIM_FLAG_PARTIAL || bIsDucking) {
                        blendAmount2 += lastAssoc->m_fBlendAmount;
                    }
                }
            }
        }
    } while (lastAssoc);


    if (!lastAssocWithFlag100 || blendAmount1 <= 0.5f || blendAmount2 >= 1.f) { // 0x5E58FB
        DoProcessLanding();
        return;
    }

    auto* lastAssocHier = lastAssoc->m_pHierarchy;

    float minAnimTime = lastAssocHier->m_fTotalTime / 15.f;
    float maxAnimTime = lastAssocHier->m_fTotalTime / 2.f + minAnimTime; // Weird.. Why adding `minAnimTime` to it?

    if (bIsDucking) {
        minAnimTime += 0.2f;
        maxAnimTime += 0.2f;
    }

    if (m_pStats == &CPedStats::ms_apPedStats[STAT_BURGULAR_STATUS]) { // 0X5E5968

        // NOTE: The number `15` seems to be reoccuring, it's used above as well.
        const float animTimeMult = lastAssoc->m_nAnimId != AnimationId::ANIM_ID_WALK ? 8.f / 15.f : 5.f / 15.f;

        float adhisionMult{ 1.f };
        switch (g_surfaceInfos->GetAdhesionGroup(m_nContactSurface)) {
        case eAdhesionGroup::ADHESION_GROUP_SAND: { // 0X5E599F
            if (rand() % 64) {
                m_vecAnimMovingShiftLocal *= 0.2f;
            }

            DoProcessLanding();
            return;
        }
        case eAdhesionGroup::ADHESION_GROUP_WET: { // 0X5E59B1
            m_vecAnimMovingShiftLocal *= 0.3f;
            DoProcessLanding();
            return;
        }
        case eAdhesionGroup::ADHESION_GROUP_LOOSE: { // 0x5E5A25
            if (rand() % 128) {
                m_vecAnimMovingShiftLocal *= 0.5f;
            }
            adhisionMult = 0.5f;
            break;
        }
        }

        if (m_pedAudio.field_7C) { // Move condition out here, but originally it was at 0x5E5AFA and 0x5E5A68
            const auto DoAddSkateAE = [&, this](eAudioEvents ae) {
                // 0x5E5AB4
                m_pedAudio.AddAudioEvent(
                    ae,
                    CAEAudioUtility::AudioLog10(adhisionMult) * 20.f,
                    lastAssoc->m_nAnimId == AnimationId::ANIM_ID_WALK ? 1.f : 0.75f
                );
            };

            if (   lastAssoc->m_fCurrentTime <= 0.f
                || lastAssoc->m_fCurrentTime - lastAssoc->m_fTimeStep > 0.f
            ) {
                if (   adhisionMult > 0.2f
                    && lastAssoc->m_fCurrentTime > animTimeMult
                    && lastAssoc->m_fCurrentTime - lastAssoc->m_fTimeStep <= animTimeMult
                ) {
                    // 0x5E5B46
                    DoAddSkateAE(eAudioEvents::AE_PED_SKATE_RIGHT);
                }
            } else {
                // 0x5E5AB4
                DoAddSkateAE(eAudioEvents::AE_PED_SKATE_LEFT);
            }
        }

        DoProcessLanding();
        return;
    }

    // 0x5E5E56 and 0x5E5D57.. Seems like inlined?
    const auto DoFootStepAE = [&, this](bool isLeftFoot) {
        if (m_pedAudio.field_7C) {
            const auto DoAddFootStepAE = [&, this](float volume, float speed) {
                m_pedAudio.AddAudioEvent(isLeftFoot ? eAudioEvents::AE_PED_FOOTSTEP_RIGHT : eAudioEvents::AE_PED_FOOTSTEP_LEFT, volume, speed);
            };

            if (bIsDucking) {
                DoAddFootStepAE(-18.f, 0.8f);
            } else {
                const auto DoAddMovingFootStepAE = [&, this](float volume, float speed) {
                    if (m_nAnimGroup == ANIM_GROUP_PLAYERSNEAK) {
                        DoAddFootStepAE(volume - 6.f, speed - 0.1f);
                    } else {
                        DoAddFootStepAE(volume, speed);
                    }
                };

                switch (m_nMoveState) {
                case eMoveState::PEDMOVE_RUN:
                    DoAddMovingFootStepAE(-6.f, 1.1f);
                    break;
                case eMoveState::PEDMOVE_SPRINT:
                    DoAddMovingFootStepAE(0.f, 1.2f);
                    break;
                default:
                    DoAddMovingFootStepAE(-12.f, 0.9f);
                    break;
                }
            }
        }
        DoFootLanded(isLeftFoot, IsWalkRunSprintAnim());
    };

    // 0x5E5B50
    if (   minAnimTime > lastAssoc->m_fCurrentTime
        || lastAssoc->m_fCurrentTime - lastAssoc->m_fTimeStep >= minAnimTime
    ) {
        // 0x5E5D8E
        if (lastAssoc->m_fCurrentTime >= (double)maxAnimTime
            && lastAssoc->m_fCurrentTime - lastAssoc->m_fTimeStep < maxAnimTime)
        {
            // 0x5E592B - 0x5E5E56
            DoFootStepAE(false); // Do right foot step AE
            DoProcessLanding();
            return;
        }
    }

    if (IsPlayer()) { // 0x5E5B79
        if (const auto pd = m_pPlayerData) {
            const auto DoEventSoundQuiet = [this](float volume) {
                // 0x5E5BCB
                CEventSoundQuiet event{ this, volume, (uint32)-1, {0.f, 0.f, 0.f}};
                GetEventGlobalGroup()->Add(&event);
            };

            const auto isWearingBalaclava = pd->m_pPedClothesDesc->GetIsWearingBalaclava();
            switch (m_nMoveState) {
            case eMoveState::PEDMOVE_JOG:   // 0x5E5BAD -- hehehe, 0x 5E5 - BAD
            case eMoveState::PEDMOVE_RUN: { // 0x5E5BB6
                // 0x5E5BDD
                if (pd->m_fMoveBlendRatio >= 2.f) {
                    DoEventSoundQuiet(isWearingBalaclava ? 55.f : 45.f);
                } else {
                    const auto DoEventSoundQuiet_MoveBlendFactor = [&](float moveBlendFactor) {
                        // 0x5E5C31
                        if (const auto volume = (pd->m_fMoveBlendRatio - 1.f) * moveBlendFactor + 30.f; volume > 0.f) {
                            DoEventSoundQuiet(volume);
                        }
                    };

                    // 0x05E5BF3
                    if (isWearingBalaclava && pd->m_fMoveBlendRatio > 1.1f) {
                        DoEventSoundQuiet_MoveBlendFactor(20.f);
                    } else if (pd->m_fMoveBlendRatio > 1.5f) {
                        DoEventSoundQuiet_MoveBlendFactor(15.f);
                    }
                }
                break;
            }
            case eMoveState::PEDMOVE_SPRINT: { // 0x5E5BBB 
                DoEventSoundQuiet(isWearingBalaclava ? 65.f : 55.f);
                break;
            }
            }
            if (pd->m_pPedClothesDesc->GetIsWearingBalaclava()) {
            }
        }
    }

    // 0x5E5C8D
    DoFootStepAE(true); // Do left foot step AE
    DoFootLanded(true, IsWalkRunSprintAnim());
    DoProcessLanding();
}


/*!
* @addr 0x5E5ED0
* @brief Create model for current active weapon. Also creates FX for molotov if `this->IsPlayer()`.
* @param modelIndex Model that should be created for the current weapon.
*/
void CPed::AddWeaponModel(int32 modelIndex) {
   if (modelIndex == -1) {
       return;
   }

   // Make sure this weapon is supposed to have a model
   // (May be set to false even if it does, eg.: in case of infrared or night googles, see `TakeOffGoggles`)
   auto& activeWep = GetActiveWeapon();
   if (activeWep.m_bNoModel) {
       return;
   }

   // Remove old model (if any)
   if (m_pWeaponObject) {
       RemoveWeaponModel(-1);
   }

   // Create clump for model
   auto& wepMI = *CModelInfo::GetModelInfo(modelIndex);
   m_pWeaponObject = (RpClump*)wepMI.CreateInstance();
   m_pGunflashObject = m_pWeaponObject ? CClumpModelInfo::GetFrameFromName(m_pWeaponObject, "gunflash") : nullptr;
   wepMI.AddRef();

   m_nWeaponModelId = modelIndex;

   // If player and model is molotov create FX for it.
   if (IsPlayer()) {
       if (activeWep.m_nType == eWeaponType::WEAPON_MOLOTOV
           && modelIndex == eModelID::MODEL_MOLOTOV
           && !activeWep.m_pFxSystem
        ) {
           CVector pos{ 0.f, 0.f, 0.f };
           activeWep.m_pFxSystem = g_fxMan.CreateFxSystem("molotov_flame", &pos, &GetBoneMatrix(ePedBones::BONE_R_HAND), false);
           if (const auto fx = activeWep.m_pFxSystem) {
               fx->SetLocalParticles(true);
               fx->CopyParentMatrix();
               fx->Play();
           }
       }
   }
}

// 0x5E6010
void CPed::TakeOffGoggles()
{
    auto& wepInSlot = GetWeaponInSlot(GetWeaponSlot(eWeaponType::WEAPON_INFRARED));

    // Game checks if wepInSlot.m_nType != UNARMED here, not sure why? Probably compiler mistake on switch case codegen..

    switch (wepInSlot.m_nType) {
    case eWeaponType::WEAPON_INFRARED:
    case eWeaponType::WEAPON_NIGHTVISION: {
        // Remove googles model
        RemoveGogglesModel();
        wepInSlot.m_bNoModel = false;

        // If it's the active weapon re-add it (? - Not sure)
        if (&wepInSlot == &GetActiveWeapon()) {
            AddWeaponModel(wepInSlot.GetWeaponInfo().m_nModelId1);
        }

        break;
    }
    }
}

// 0x5E6080
void CPed::GiveWeapon(eWeaponType weaponType, uint32 ammo, bool likeUnused) {
    const auto givenWepInfo = CWeaponInfo::GetWeaponInfo(weaponType);
    auto& wepInSlot = GetWeaponInSlot(givenWepInfo->m_nSlot);
    const auto wepSlot = (eWeaponSlot)givenWepInfo->m_nSlot;

    if (wepInSlot.m_nType != weaponType) { // Another weapon in the slot, remove it, and set this weapon

        // Remove previous weapon (and possibly add any ammo it had to `ammo`)
        if (wepInSlot.m_nType != eWeaponType::WEAPON_UNARMED) {
            switch (wepSlot) {
            case eWeaponSlot::SHOTGUN:
            case eWeaponSlot::SMG:
            case eWeaponSlot::RIFLE: {
                ammo += wepInSlot.m_nTotalAmmo;
                break;
            }
            }

            RemoveWeaponModel(wepInSlot.GetWeaponInfo().m_nModelId1);

            if (givenWepInfo->m_nSlot == CWeaponInfo::GetWeaponInfo(eWeaponType::WEAPON_INFRARED)->m_nSlot) {
                RemoveGogglesModel();
            }

            wepInSlot.Shutdown();
        }

        // Give new
        wepInSlot.Initialise(weaponType, ammo, this);

        // Now `wepInSlot` is the weapon we've given to the player

        if (givenWepInfo->m_nSlot == m_nActiveWeaponSlot && !bInVehicle) {
            AddWeaponModel(givenWepInfo->m_nModelId1);
        }
    } else { // Same weapon already in the slot, update its ammo count and `Reload()` it
        if (wepSlot == eWeaponSlot::GIFT) { // Gifts have no ammo :D
            return;
        }

        wepInSlot.m_nTotalAmmo = std::min(99'999u, wepInSlot.m_nTotalAmmo + ammo);
        wepInSlot.Reload(this);

        if (wepInSlot.m_nState == eWeaponState::WEAPONSTATE_OUT_OF_AMMO) {
            if (wepInSlot.m_nTotalAmmo > 0) {
                wepInSlot.m_nState = eWeaponState::WEAPONSTATE_READY;
            }
        }
    }

    if (wepInSlot.m_nState != eWeaponState::WEAPONSTATE_OUT_OF_AMMO) {
        wepInSlot.m_nState = eWeaponState::WEAPONSTATE_READY;
    }
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

// 0x5E61F0
void CPed::SetCurrentWeapon(int32 slot) {
    if (slot == -1) {
        return;
    }

    // Remove current weapon's model (if any)
    if (const auto currWepType = GetActiveWeapon().m_nType; currWepType != eWeaponType::WEAPON_UNARMED) {
        RemoveWeaponModel(CWeaponInfo::GetWeaponInfo(currWepType)->m_nModelId1);
    }

    // Set as active slot
    m_nActiveWeaponSlot = slot;

    // Set chosen weapon in player data
    if (const auto playerData = AsPlayer()->m_pPlayerData) {
        playerData->m_nChosenWeapon = slot;
    }

    // Load weapon in this slot (if any)
    if (const auto thisWepType = m_aWeapons[slot].m_nType; thisWepType != eWeaponType::WEAPON_UNARMED) {
        AddWeaponModel(CWeaponInfo::GetWeaponInfo(thisWepType)->m_nModelId1);
    }
}

// 0x5E6280
void CPed::SetCurrentWeapon(eWeaponType weaponType) {
    SetCurrentWeapon(CWeaponInfo::GetWeaponInfo(weaponType)->m_nSlot);
}

// 0x5E62B0
void CPed::ClearWeapon(eWeaponType weaponType)
{
    auto wepSlot = CWeaponInfo::GetWeaponInfo(weaponType)->m_nSlot;
    if (wepSlot == -1) {
        return; // Weapon has no slot. (How could this happen?)
    }

    auto& wep = m_aWeapons[wepSlot];
    if (wep.m_nType != weaponType) {
        return; // Slot doesn't contain the given weapon - Might happen as some weapons share slots.
    }

    if (m_nActiveWeaponSlot == wepSlot) {
        SetCurrentWeapon(eWeaponType::WEAPON_UNARMED);
    }

    wep.Shutdown();

    switch (weaponType) {
    case eWeaponType::WEAPON_NIGHTVISION:
    case eWeaponType::WEAPON_INFRARED:
        RemoveGogglesModel();
        break;
    }
}

// 0x5E6320
// Clears every weapon from the pedestrian.
void CPed::ClearWeapons()
{
    CPed::RemoveWeaponModel(-1);
    CPed::RemoveGogglesModel();
    for (auto & m_aWeapon : m_aWeapons)
    {
        m_aWeapon.Shutdown();
    }
    CWeaponInfo* getWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_UNARMED, eWeaponSkill::STD);
    SetCurrentWeapon(getWeaponInfo->m_nSlot);
}

// 0x5E6370
void CPed::RemoveWeaponWhenEnteringVehicle(int32 arg0)
{
    ((void(__thiscall *)(CPed*, int32))0x5E6370)(this, arg0);
}

// 0x5E6490
void CPed::ReplaceWeaponWhenExitingVehicle()
{
    ((void(__thiscall *)(CPed*))0x5E6490)(this);
}

// 0x5E6530
void CPed::ReplaceWeaponForScriptedCutscene()
{
    m_nSavedWeapon = m_aWeapons[m_nActiveWeaponSlot].m_nType;
    SetCurrentWeapon(0);
}

// 0x5E6550
void CPed::RemoveWeaponForScriptedCutscene()
{
    if (m_nSavedWeapon != WEAPON_UNIDENTIFIED)
    {
        CWeaponInfo* weaponInfo = CWeaponInfo::GetWeaponInfo(m_nSavedWeapon, eWeaponSkill::STD);
        CPed::SetCurrentWeapon(weaponInfo->m_nSlot);
        m_nSavedWeapon = WEAPON_UNIDENTIFIED;
    }
}

// 0x5E65A0
void CPed::PreRenderAfterTest()
{
    ((void(__thiscall *)(CPed*))0x5E65A0)(this);
}

// 0x5E7980
void CPed::SetIdle()
{
    ((void(__thiscall *)(CPed*))0x5E7980)(this);
}

// 0x5E79B0
void CPed::SetLook(float heading)
{
    ((void(__thiscall *)(CPed*, float))0x5E79B0)(this, heading);
}

// 0x5E7A60
void CPed::SetLook(CEntity* entity)
{
    ((void(__thiscall *)(CPed*, CEntity*))0x5E7A60)(this, entity);
}

// 0x5E7B20
void CPed::Look()
{
    ((void(__thiscall *)(CPed*))0x5E7B20)(this);
}

// 0x5E7CB0
CEntity* CPed::AttachPedToEntity(CEntity* entity, CVector offset, uint16 arg2, float arg3, eWeaponType weaponType)
{
    return ((CEntity* (__thiscall *)(CPed*, CEntity*, CVector, uint16, float, eWeaponType))0x5E7CB0)(this, entity, offset, arg2, arg3, weaponType);
}

// 0x5E7E60
CEntity* CPed::AttachPedToBike(CEntity* entity, CVector offset, uint16 arg2, float arg3, float arg4, eWeaponType weaponType)
{
    return ((CEntity* (__thiscall *)(CPed*, CEntity*, CVector, uint16, float, float, eWeaponType))0x5E7E60)(this, entity, offset, arg2, arg3, arg4, weaponType);
}

// 0x5E7EC0
void CPed::DettachPedFromEntity()
{
    ((void(__thiscall *)(CPed*))0x5E7EC0)(this);
}

// 0x5E8830
void CPed::SetAimFlag(float heading)
{
    ((void(__thiscall *)(CPed*, float))0x5E8830)(this, heading);
}

// 0x5E88E0
bool CPed::CanWeRunAndFireWithWeapon()
{
    return ((bool(__thiscall *)(CPed*))0x5E88E0)(this);
}

// 0x5E8910
void CPed::RequestDelayedWeapon()
{
    ((void(__thiscall *)(CPed*))0x5E8910)(this);
}

// 0x5E89B0
void CPed::GiveDelayedWeapon(eWeaponType weaponType, uint32 ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, uint32))0x5E89B0)(this, weaponType, ammo);
}

// 0x5E8A30
bool IsPedPointerValid(CPed* ped)
{
    return ((bool(__cdecl *)(CPed*))0x5E8A30)(ped);
}

// 0x5E8AB0
void CPed::GiveWeaponAtStartOfFight()
{
    if (m_nCreatedBy != PED_MISSION && GetActiveWeapon().m_nType == eWeaponType::WEAPON_UNARMED)
    {
        const auto GiveRandomWeaponByType = [this](eWeaponType type, uint16 maxRandom)
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
            case PED_TYPE_GANG1:
            case PED_TYPE_GANG2:
            case PED_TYPE_GANG3:
            case PED_TYPE_GANG4:
            case PED_TYPE_GANG5:
            case PED_TYPE_GANG6:
            case PED_TYPE_GANG7:
            case PED_TYPE_GANG8:
            case PED_TYPE_GANG9:
            case PED_TYPE_GANG10:
                GiveRandomWeaponByType(eWeaponType::WEAPON_PISTOL, 400);
                break;
            case PED_TYPE_DEALER:
            case PED_TYPE_CRIMINAL:
            case PED_TYPE_PROSTITUTE:
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
        if (CCheat::IsActive(CHEAT_NO_ONE_CAN_STOP_US)) {
            GiveDelayedWeapon(WEAPON_AK47, 200);
            SetCurrentWeapon(CWeaponInfo::GetWeaponInfo(WEAPON_AK47, eWeaponSkill::STD)->m_nSlot);
        }
        else {
            CWeaponInfo* pWeaponInfo = nullptr;
            if (CCheat::IsActive(CHEAT_ROCKET_MAYHEM)) {
                GiveDelayedWeapon(WEAPON_RLAUNCHER, 200);
                pWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_RLAUNCHER, eWeaponSkill::STD);
            }
            else {
                CPed::GiveDelayedWeapon(WEAPON_PISTOL, 200);
                pWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_PISTOL, eWeaponSkill::STD);
            }
            CPed::SetCurrentWeapon(pWeaponInfo->m_nSlot);
        }
    }
}

// 0x5EFF50
bool CPed::GetPedTalking()
{
    return ((bool(__thiscall *)(CPed*))0x5EFF50)(this);
}

// 0x5EFF60
void CPed::DisablePedSpeech(int16 arg0)
{
    ((void(__thiscall *)(CPed*, int16))0x5EFF60)(this, arg0);
}

// 0x5EFF70
void CPed::EnablePedSpeech()
{
    ((void(__thiscall *)(CPed*))0x5EFF70)(this);
}

// 0x5EFF80
void CPed::DisablePedSpeechForScriptSpeech(int16 arg0)
{
    ((void(__thiscall *)(CPed*, int16))0x5EFF80)(this, arg0);
}

// 0x5EFF90
void CPed::EnablePedSpeechForScriptSpeech()
{
    ((void(__thiscall *)(CPed*))0x5EFF90)(this);
}

// 0x5EFFA0
void CPed::CanPedHoldConversation()
{
    ((void(__thiscall *)(CPed*))0x5EFFA0)(this);
}

// 0x5EFFB0
void CPed::SayScript(int32 arg0, uint8 arg1, uint8 arg2, uint8 arg3)
{
    ((void(__thiscall *)(CPed*, int32, uint8, uint8, uint8))0x5EFFB0)(this, arg0, arg1, arg2, arg3);
}

// 0x5EFFE0
void CPed::Say(uint16 arg0, uint32 arg1, float arg2, uint8 arg3, uint8 arg4, uint8 arg5)
{
    ((void(__thiscall *)(CPed*, uint16, uint32, float, uint8, uint8, uint8))0x5EFFE0)(this, arg0, arg1, arg2, arg3, arg4, arg5);
}

// 0x5F0060
RwObject* SetPedAtomicVisibilityCB(RwObject* rwObject, void* data)
{
    return ((RwObject* (__cdecl *)(RwObject*, void*))0x5F0060)(rwObject, data);
}

// 0x5F0140
void CPed::RemoveBodyPart(int32 boneId, char localDir)
{
    ((void(__thiscall *)(CPed*, int32, char))0x5F0140)(this, boneId, localDir);
}

// 0x5F0190
void CPed::SpawnFlyingComponent(int32 arg0, char arg1)
{
    // NOP
}

// 0x5F01A0
bool CPed::DoesLOSBulletHitPed(CColPoint& colPoint)
{
    return ((bool(__thiscall *)(CPed*, CColPoint&))0x5F01A0)(this, colPoint);
}

// 0x5F0250
void CPed::RemoveWeaponAnims(int32 likeUnused, float blendDelta)
{
    ((void(__thiscall *)(CPed*, int32, float))0x5F0250)(this, likeUnused, blendDelta);
}

// 0x5F02C0
bool CPed::IsPedHeadAbovePos(float zPos)
{
    return ((bool(__thiscall *)(CPed*, float))0x5F02C0)(this, zPos);
}

// 0x5F0360
void CPed::KillPedWithCar(CVehicle* car, float fDamageIntensity, bool bPlayDeadAnimation)
{
    ((void(__thiscall *)(CPed*, CVehicle*, float, bool))0x5F0360)(this, car, fDamageIntensity, bPlayDeadAnimation);
}

// 0x6AE0D0
void CPed::MakeTyresMuddySectorList(CPtrList& ptrList)
{
    ((void(__thiscall *)(CPed*, CPtrList&))0x6AE0D0)(this, ptrList);
}

// 0x6B4200
void CPed::DeadPedMakesTyresBloody()
{
    ((void(__thiscall *)(CPed*))0x6B4200)(this);
}

bool CPed::IsInVehicleThatHasADriver()
{
    if (bInVehicle) {
        if (m_pVehicle && m_pVehicle->IsPassenger(this) && m_pVehicle->m_pDriver)
            return true;
    }
    return false;
}

bool CPed::IsFollowerOfGroup(const CPedGroup& group) {
    return group.GetMembership().IsFollower(this);
}

RwMatrix& CPed::GetBoneMatrix(ePedBones bone) const {
    const auto hierarchy = GetAnimHierarchyFromClump(m_pRwClump);
    return RpHAnimHierarchyGetMatrixArray(hierarchy)[(size_t)bone];
}

// 0x5E4880
void CPed::SetModelIndex(uint32 modelIndex)
{
    plugin::CallMethod<0x5E4880, CPed*, uint32>(this, modelIndex);
}

// 0x5DEBF0
void CPed::DeleteRwObject()
{
    CEntity::DeleteRwObject();
}

// 0x5E8CD0
void CPed::ProcessControl()
{
    plugin::CallMethod<0x5E8CD0, CPed*>(this);
}

// 0x5E4110 todo: CPed::Teleport(CVector)
void CPed::Teleport(CVector destination, bool resetRotation)
{
    plugin::CallMethod<0x5E4110, CPed*, CVector, bool>(this, destination, resetRotation);
}

// 0x5E3C30
void CPed::SpecialEntityPreCollisionStuff(CPhysical* colPhysical,
                                          bool  bIgnoreStuckCheck,
                                          bool& bCollisionDisabled,
                                          bool& bCollidedEntityCollisionIgnored,
                                          bool& bCollidedEntityUnableToMove,
                                          bool& bThisOrCollidedEntityStuck)
{
    plugin::CallMethod<0x5E3C30, CPed*, CPhysical*, bool, bool&, bool&, bool&, bool&>(this, colPhysical, bIgnoreStuckCheck, bCollisionDisabled, bCollidedEntityCollisionIgnored, bCollidedEntityUnableToMove, bThisOrCollidedEntityStuck);
}

// 0x5E3E90
uint8 CPed::SpecialEntityCalcCollisionSteps(bool& bProcessCollisionBeforeSettingTimeStep, bool& unk2)
{
    return plugin::CallMethodAndReturn<uint8, 0x5E3E90, CPed*, bool&, bool&>(this, bProcessCollisionBeforeSettingTimeStep, unk2);
}

// 0x5E8A20
void CPed::PreRender()
{
    if (m_nPedState != PEDSTATE_DRIVING)
        PreRenderAfterTest();
}

// 0x5E7680
void CPed::Render()
{
    plugin::CallMethod<0x5E7680, CPed*>(this);
}

// 0x553F00
bool CPed::SetupLighting()
{
  ActivateDirectional();
  return CRenderer::SetupLightingForEntity(this);
}

// 0x5533B0
void CPed::RemoveLighting(bool bRemove)
{
    plugin::CallMethod<0x5533B0, CPed*, bool>(this, bRemove);
}

// 0x5E7B70
void CPed::FlagToDestroyWhenNextProcessed()
{
    plugin::CallMethod<0x5E7B70, CPed*>(this);
}

// 0x5E2530
int32 CPed::ProcessEntityCollision(CEntity* entity, CColPoint* colPoint)
{
    return plugin::CallMethodAndReturn<int32, 0x5E2530, CPed*, CEntity*, CColPoint*>(this, entity, colPoint);
}

// NOTSA
bool CPed::IsInVehicleAsPassenger() const noexcept {
    return bInVehicle && m_pVehicle && m_pVehicle->m_pDriver != this;
}
