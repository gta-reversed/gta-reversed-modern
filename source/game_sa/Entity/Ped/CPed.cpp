/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

void CPed::InjectHooks() {
    // Constructors
    // ReversibleHooks::Install("CPed", "CPed", 0x5E8030, &CPed::Constructor);

    // Destructors
    // ReversibleHooks::Install("CPed", "~CPed", 0x5E8620, static_cast<CPed*(CPed::*)()>(&CPed::Destructor));

    // Static functions
    // ReversibleHooks::Install("CPed", "operator delete", 0x5E4760, &CPed::operator delete);
    // ReversibleHooks::Install("CPed", "operator new", 0x5E4720, &CPed::operator new);
    // ReversibleHooks::Install("CPed", "SpawnFlyingComponent", 0x5F0190, &CPed::SpawnFlyingComponent);
    // ReversibleHooks::Install("CPed", "PedCanPickUpPickUp", 0x455560, &CPed::PedCanPickUpPickUp);
    // ReversibleHooks::Install("CPed", "Update", 0x5DEBE0, &CPed::Update);
    ReversibleHooks::Install("CPed", "Initialise", 0x5DEBB0, &CPed::Initialise);
    // ReversibleHooks::Install("CPed", "UpdateStatLeavingVehicle", 0x5E01B0, &CPed::UpdateStatLeavingVehicle);
    // ReversibleHooks::Install("CPed", "UpdateStatEnteringVehicle", 0x5E01A0, &CPed::UpdateStatEnteringVehicle);
    // ReversibleHooks::Install("CPed", "ShoulderBoneRotation", 0x5DF560, &CPed::ShoulderBoneRotation);
    // ReversibleHooks::Install("CPed", "RestoreHeadingRateCB", 0x5DFD70, &CPed::RestoreHeadingRateCB);

    // Methods
    // ReversibleHooks::Install("CPed", "PedIsInvolvedInConversation", 0x43AB90, &CPed::PedIsInvolvedInConversation);
    ReversibleHooks::Install("CPed", "ClearWeapons", 0x5E6320, &CPed::ClearWeapons);
    // ReversibleHooks::Install("CPed", "ClearWeapon", 0x5E62B0, &CPed::ClearWeapon);
    // ReversibleHooks::Install("CPed", "SetCurrentWeapon", 0x5E6280, static_cast<void(CPed::*)(eWeaponType)>(&CPed::SetCurrentWeapon));
    // ReversibleHooks::Install("CPed", "SetCurrentWeapon", 0x5E61F0, static_cast<void(CPed::*)(int32_t)>(&CPed::SetCurrentWeapon));
    // ReversibleHooks::Install("CPed", "GiveWeapon", 0x5E6080, &CPed::GiveWeapon);
    // ReversibleHooks::Install("CPed", "TakeOffGoggles", 0x5E6010, &CPed::TakeOffGoggles);
    // ReversibleHooks::Install("CPed", "AddWeaponModel", 0x5E5ED0, &CPed::AddWeaponModel);
    // ReversibleHooks::Install("CPed", "PlayFootSteps", 0x5E57F0, &CPed::PlayFootSteps);
    // ReversibleHooks::Install("CPed", "DoFootLanded", 0x5E5380, &CPed::DoFootLanded);
    // ReversibleHooks::Install("CPed", "ClearAll", 0x5E5320, &CPed::ClearAll);
    // ReversibleHooks::Install("CPed", "CalculateNewOrientation", 0x5E52E0, &CPed::CalculateNewOrientation);
    // ReversibleHooks::Install("CPed", "CalculateNewVelocity", 0x5E4C50, &CPed::CalculateNewVelocity);
    // ReversibleHooks::Install("CPed", "SetCharCreatedBy", 0x5E47E0, &CPed::SetCharCreatedBy);
    // ReversibleHooks::Install("CPed", "SetPedState", 0x5E4500, &CPed::SetPedState);
    // ReversibleHooks::Install("CPed", "GiveObjectToPedToHold", 0x5E4390, &CPed::GiveObjectToPedToHold);
    // ReversibleHooks::Install("CPed", "ClearLookFlag", 0x5E1950, &CPed::ClearLookFlag);
    // ReversibleHooks::Install("CPed", "WorkOutHeadingForMovingFirstPerson", 0x5E1A00, &CPed::WorkOutHeadingForMovingFirstPerson);
    // ReversibleHooks::Install("CPed", "UpdatePosition", 0x5E1B10, &CPed::UpdatePosition);
    // ReversibleHooks::Install("CPed", "MakeTyresMuddySectorList", 0x6AE0D0, &CPed::MakeTyresMuddySectorList);
    ReversibleHooks::Install("CPed", "IsPedInControl", 0x5E3960, &CPed::IsPedInControl);
    // ReversibleHooks::Install("CPed", "RemoveWeaponModel", 0x5E3990, &CPed::RemoveWeaponModel);
    // ReversibleHooks::Install("CPed", "RemoveWeaponWhenEnteringVehicle", 0x5E6370, &CPed::RemoveWeaponWhenEnteringVehicle);
    // ReversibleHooks::Install("CPed", "AddGogglesModel", 0x5E3A90, &CPed::AddGogglesModel);
    // ReversibleHooks::Install("CPed", "SetWeaponSkill", 0x5E3C10, &CPed::SetWeaponSkill);
    // ReversibleHooks::Install("CPed", "ClearLook", 0x5E3FF0, &CPed::ClearLook);
    // ReversibleHooks::Install("CPed", "TurnBody", 0x5E4000, &CPed::TurnBody);
    // ReversibleHooks::Install("CPed", "IsPointerValid", 0x5E4220, &CPed::IsPointerValid);
    // ReversibleHooks::Install("CPed", "GetBonePosition", 0x5E4280, &CPed::GetBonePosition);
    // ReversibleHooks::Install("CPed", "PutOnGoggles", 0x5E3AE0, &CPed::PutOnGoggles);
    // ReversibleHooks::Install("CPed", "SortPeds", 0x5E17E0, &CPed::SortPeds);
    // ReversibleHooks::Install("CPed", "ReplaceWeaponWhenExitingVehicle", 0x5E6490, &CPed::ReplaceWeaponWhenExitingVehicle);
    // ReversibleHooks::Install("CPed", "KillPedWithCar", 0x5F0360, &CPed::KillPedWithCar);
    // ReversibleHooks::Install("CPed", "IsPedHeadAbovePos", 0x5F02C0, &CPed::IsPedHeadAbovePos);
    // ReversibleHooks::Install("CPed", "RemoveWeaponAnims", 0x5F0250, &CPed::RemoveWeaponAnims);
    // ReversibleHooks::Install("CPed", "DoesLOSBulletHitPed", 0x5F01A0, &CPed::DoesLOSBulletHitPed);
    // ReversibleHooks::Install("CPed", "RemoveBodyPart", 0x5F0140, &CPed::RemoveBodyPart);
    // ReversibleHooks::Install("CPed", "Say", 0x5EFFE0, &CPed::Say);
    // ReversibleHooks::Install("CPed", "SayScript", 0x5EFFB0, &CPed::SayScript);
    // ReversibleHooks::Install("CPed", "CanPedHoldConversation", 0x5EFFA0, &CPed::CanPedHoldConversation);
    // ReversibleHooks::Install("CPed", "EnablePedSpeechForScriptSpeech", 0x5EFF90, &CPed::EnablePedSpeechForScriptSpeech);
    // ReversibleHooks::Install("CPed", "DisablePedSpeechForScriptSpeech", 0x5EFF80, &CPed::DisablePedSpeechForScriptSpeech);
    // ReversibleHooks::Install("CPed", "EnablePedSpeech", 0x5EFF70, &CPed::EnablePedSpeech);
    // ReversibleHooks::Install("CPed", "DisablePedSpeech", 0x5EFF60, &CPed::DisablePedSpeech);
    // ReversibleHooks::Install("CPed", "GetPedTalking", 0x5EFF50, &CPed::GetPedTalking);
    ReversibleHooks::Install("CPed", "GiveWeaponWhenJoiningGang", 0x5E8BE0, &CPed::GiveWeaponWhenJoiningGang);
    // ReversibleHooks::Install("CPed", "GiveDelayedWeapon", 0x5E89B0, &CPed::GiveDelayedWeapon);
    ReversibleHooks::Install("CPed", "GetWeaponSkill", 0x5E6580, static_cast<eWeaponSkill(CPed::*)()>(&CPed::GetWeaponSkill));
    // ReversibleHooks::Install("CPed", "PreRenderAfterTest", 0x5E65A0, &CPed::PreRenderAfterTest);
    // ReversibleHooks::Install("CPed", "SetIdle", 0x5E7980, &CPed::SetIdle);
    // ReversibleHooks::Install("CPed", "SetLook", 0x5E79B0, static_cast<int32_t(CPed::*)(float)>(&CPed::SetLook));
    // ReversibleHooks::Install("CPed", "SetLook", 0x5E7A60, static_cast<int32_t(CPed::*)(CEntity *)>(&CPed::SetLook));
    // ReversibleHooks::Install("CPed", "Look", 0x5E7B20, &CPed::Look);
    ReversibleHooks::Install("CPed", "ReplaceWeaponForScriptedCutscene", 0x5E6530, &CPed::ReplaceWeaponForScriptedCutscene);
    ReversibleHooks::Install("CPed", "RemoveWeaponForScriptedCutscene", 0x5E6550, &CPed::RemoveWeaponForScriptedCutscene);
    ReversibleHooks::Install("CPed", "GiveWeaponAtStartOfFight", 0x5E8AB0, &CPed::GiveWeaponAtStartOfFight);
    ReversibleHooks::Install("CPed", "ProcessBuoyancy", 0x5E1FA0, &CPed::ProcessBuoyancy);
    // ReversibleHooks::Install("CPed", "PositionPedOutOfCollision", 0x5E0820, &CPed::PositionPedOutOfCollision);
    // ReversibleHooks::Install("CPed", "GrantAmmo", 0x5DF220, &CPed::GrantAmmo);
    ReversibleHooks::Install("CPed", "GetWeaponSlot", 0x5DF200, &CPed::GetWeaponSlot);
    // ReversibleHooks::Install("CPed", "PositionAnyPedOutOfCollision", 0x5E13C0, &CPed::PositionAnyPedOutOfCollision);
    // ReversibleHooks::Install("CPed", "CanBeDeletedEvenInVehicle", 0x5DF150, &CPed::CanBeDeletedEvenInVehicle);
    // ReversibleHooks::Install("CPed", "CanBeDeleted", 0x5DF100, &CPed::CanBeDeleted);
    ReversibleHooks::Install("CPed", "CanStrafeOrMouseControl", 0x5DF090, &CPed::CanStrafeOrMouseControl);
    ReversibleHooks::Install("CPed", "CanBeArrested", 0x5DF060, &CPed::CanBeArrested);
    // ReversibleHooks::Install("CPed", "CanSetPedState", 0x5DF030, &CPed::CanSetPedState);
    ReversibleHooks::Install("CPed", "CanPedReturnToState", 0x5DF000, &CPed::CanPedReturnToState);
    // ReversibleHooks::Install("CPed", "UseGroundColModel", 0x5DEFE0, &CPed::UseGroundColModel);
    // ReversibleHooks::Install("CPed", "IsPedShootable", 0x5DEFD0, &CPed::IsPedShootable);
    // ReversibleHooks::Install("CPed", "GetLocalDirection", 0x5DEF60, &CPed::GetLocalDirection);
    // ReversibleHooks::Install("CPed", "ClearAimFlag", 0x5DEF20, &CPed::ClearAimFlag);
    // ReversibleHooks::Install("CPed", "SetAimFlag", 0x5DEED0, static_cast<int8_t(CPed::*)(CEntity *)>(&CPed::SetAimFlag));
    // ReversibleHooks::Install("CPed", "SetLookFlag", 0x5DEE40, static_cast<int8_t(CPed::*)(CEntity *, bool, bool)>(&CPed::SetLookFlag));
    // ReversibleHooks::Install("CPed", "SetLookFlag", 0x5DEDC0, static_cast<int8_t(CPed::*)(float, bool, bool)>(&CPed::SetLookFlag));
    // ReversibleHooks::Install("CPed", "CanUseTorsoWhenLooking", 0x5DED90, &CPed::CanUseTorsoWhenLooking);
    // ReversibleHooks::Install("CPed", "PedIsReadyForConversation", 0x43ABA0, &CPed::PedIsReadyForConversation);
    // ReversibleHooks::Install("CPed", "CreateDeadPedMoney", 0x4590F0, &CPed::CreateDeadPedMoney);
    // ReversibleHooks::Install("CPed", "CreateDeadPedPickupCoors", 0x459180, &CPed::CreateDeadPedPickupCoors);
    // ReversibleHooks::Install("CPed", "CreateDeadPedWeaponPickups", 0x4591D0, &CPed::CreateDeadPedWeaponPickups);
    // ReversibleHooks::Install("CPed", "IsWearingGoggles", 0x479D10, &CPed::IsWearingGoggles);
    // ReversibleHooks::Install("CPed", "SetAmmo", 0x5DF290, &CPed::SetAmmo);
    // ReversibleHooks::Install("CPed", "SetStayInSamePlace", 0x481090, &CPed::SetStayInSamePlace);
    // ReversibleHooks::Install("CPed", "SetPedStats", 0x5DEBC0, &CPed::SetPedStats);
    // ReversibleHooks::Install("CPed", "SetMoveState", 0x5DEC00, &CPed::SetMoveState);
    // ReversibleHooks::Install("CPed", "SetMoveAnimSpeed", 0x5DEC10, &CPed::SetMoveAnimSpeed);
    // ReversibleHooks::Install("CPed", "StopNonPartialAnims", 0x5DED10, &CPed::StopNonPartialAnims);
    // ReversibleHooks::Install("CPed", "RestartNonPartialAnims", 0x5DED50, &CPed::RestartNonPartialAnims);
    // ReversibleHooks::Install("CPed", "DoWeHaveWeaponAvailable", 0x5DF300, &CPed::DoWeHaveWeaponAvailable);
    // ReversibleHooks::Install("CPed", "RemoveGogglesModel", 0x5DF170, &CPed::RemoveGogglesModel);
    // ReversibleHooks::Install("CPed", "SetGunFlashAlpha", 0x5DF400, &CPed::SetGunFlashAlpha);
    // ReversibleHooks::Install("CPed", "CanSeeEntity", 0x5E0730, &CPed::CanSeeEntity);
    // ReversibleHooks::Install("CPed", "SetPedDefaultDecisionMaker", 0x5E06E0, &CPed::SetPedDefaultDecisionMaker);
    // ReversibleHooks::Install("CPed", "GetWalkAnimSpeed", 0x5E04B0, &CPed::GetWalkAnimSpeed);
    // ReversibleHooks::Install("CPed", "StopPlayingHandSignal", 0x5E0480, &CPed::StopPlayingHandSignal);
    // ReversibleHooks::Install("CPed", "IsPlayingHandSignal", 0x5E0460, &CPed::IsPlayingHandSignal);
    // ReversibleHooks::Install("CPed", "CanThrowEntityThatThisPedIsHolding", 0x5E0400, &CPed::CanThrowEntityThatThisPedIsHolding);
    // ReversibleHooks::Install("CPed", "DropEntityThatThisPedIsHolding", 0x5E0360, &CPed::DropEntityThatThisPedIsHolding);
    // ReversibleHooks::Install("CPed", "GetEntityThatThisPedIsHolding", 0x5E02E0, &CPed::GetEntityThatThisPedIsHolding);
    // ReversibleHooks::Install("CPed", "GetHoldingTask", 0x5E0290, &CPed::GetHoldingTask);
    // ReversibleHooks::Install("CPed", "ReleaseCoverPoint", 0x5E0270, &CPed::ReleaseCoverPoint);
    // ReversibleHooks::Install("CPed", "DoGunFlash", 0x5DF340, &CPed::DoGunFlash);
    // ReversibleHooks::Install("CPed", "GetTransformedBonePosition", 0x5E01C0, &CPed::GetTransformedBonePosition);
    ReversibleHooks::Install("CPed", "IsAlive", 0x5E0170, &CPed::IsAlive);
    // ReversibleHooks::Install("CPed", "DeadPedMakesTyresBloody", 0x6B4200, &CPed::DeadPedMakesTyresBloody);
    // ReversibleHooks::Install("CPed", "Undress", 0x5E00F0, &CPed::Undress);
    // ReversibleHooks::Install("CPed", "SetLookTimer", 0x5DF8D0, &CPed::SetLookTimer);
    // ReversibleHooks::Install("CPed", "RestoreHeadingRate", 0x5DFD60, &CPed::RestoreHeadingRate);
    // ReversibleHooks::Install("CPed", "Dress", 0x5E0130, &CPed::Dress);
    ReversibleHooks::Install("CPed", "IsPlayer", 0x5DF8F0, &CPed::IsPlayer);
    // ReversibleHooks::Install("CPed", "GetBikeRidingSkill", 0x5DF510, &CPed::GetBikeRidingSkill);
    // ReversibleHooks::Install("CPed", "SetPedPositionInCar", 0x5DF910, &CPed::SetPedPositionInCar);
    // ReversibleHooks::Install("CPed", "SetRadioStation", 0x5DFD90, &CPed::SetRadioStation);
    // ReversibleHooks::Install("CPed", "PositionAttachedPed", 0x5DFDF0, &CPed::PositionAttachedPed);
    // ReversibleHooks::Install("CPed", "ResetGunFlashAlpha", 0x5DF4E0, &CPed::ResetGunFlashAlpha);

    // Virtual methods
    // ReversibleHooks::Install("CPed", "SetModelIndex", 0x5E4880, &CPed::SetModelIndex_Reversed);
    // ReversibleHooks::Install("CPed", "DeleteRwObject", 0x5DEBF0, &CPed::DeleteRwObject_Reversed);
    // ReversibleHooks::Install("CPed", "ProcessControl", 0x5E8CD0, &CPed::ProcessControl_Reversed);
    // ReversibleHooks::Install("CPed", "Teleport", 0x5E4110, &CPed::Teleport_Reversed);
    // ReversibleHooks::Install("CPed", "SpecialEntityPreCollisionStuff", 0x5E3C30, &CPed::SpecialEntityPreCollisionStuff_Reversed);
    // ReversibleHooks::Install("CPed", "SpecialEntityCalcCollisionSteps", 0x5E3E90, &CPed::SpecialEntityCalcCollisionSteps_Reversed);
    // ReversibleHooks::Install("CPed", "PreRender", 0x5E8A20, &CPed::PreRender_Reversed);
    // ReversibleHooks::Install("CPed", "Render", 0x5E7680, &CPed::Render_Reversed);
    // ReversibleHooks::Install("CPed", "SetupLighting", 0x553F00, &CPed::SetupLighting_Reversed);
    // ReversibleHooks::Install("CPed", "RemoveLighting", 0x5533B0, &CPed::RemoveLighting_Reversed);
    // ReversibleHooks::Install("CPed", "FlagToDestroyWhenNextProcessed", 0x5E7B70, &CPed::FlagToDestroyWhenNextProcessed_Reversed);
    // ReversibleHooks::Install("CPed", "ProcessEntityCollision", 0x5E2530, &CPed::ProcessEntityCollision_Reversed);
    // ReversibleHooks::Install("CPed", "SetMoveAnim", 0x5E4A00, &CPed::SetMoveAnim_Reversed);
    // ReversibleHooks::Install("CPed", "Save", 0x5D5730, &CPed::Save_Reversed);
    // ReversibleHooks::Install("CPed", "Load", 0x5D4640, &CPed::Load_Reversed);
}

CPed::CPed(ePedType pedtype) : CPhysical(), m_aWeapons{ plugin::dummy, plugin::dummy, plugin::dummy,
plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy, plugin::dummy,
plugin::dummy, plugin::dummy, plugin::dummy }
{
    ((void(__thiscall *)(CPed*, ePedType))0x5E8030)(this, pedtype);
}

// 0x5E4720
void* CPed::operator new(unsigned int size) {
    return ((void* (__cdecl *)(unsigned int))0x5E4720)(size);
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
    return ((bool(__thiscall *)(CPed*))0x43AB90)(this);
}

// 0x43ABA0
bool CPed::PedIsReadyForConversation(bool arg0)
{
    return ((bool(__thiscall *)(CPed*, bool))0x43ABA0)(this, arg0);
}

// 0x455560
bool CPed::PedCanPickUpPickUp()
{
    return ((bool(__thiscall *)(CPed*))0x455560)(this);
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
    // auto index = static_cast<int>(statsType);
    // m_pStats = &CPedStats::ms_apPedStats[index];
}

// 0x5DEBE0
void CPed::Update()
{
    ((void(__thiscall *)(CPed*))0x5DEBE0)(this);
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
int CPed::GetLocalDirection(CVector2D const& arg0)
{
    return ((int(__thiscall *)(CPed*, CVector2D const&))0x5DEF60)(this, arg0);
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

int CPed::GetWeaponSlot(eWeaponType weaponType)
{
    return CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::WEAPSKILL_STD)->m_nSlot;
}

// 0x5DF220
void CPed::GrantAmmo(eWeaponType weaponType, unsigned int ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, unsigned int))0x5DF220)(this, weaponType, ammo);
}

// 0x5DF290
void CPed::SetAmmo(eWeaponType weaponType, unsigned int ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, unsigned int))0x5DF290)(this, weaponType, ammo);
}

// 0x5DF300
bool CPed::DoWeHaveWeaponAvailable(eWeaponType weaponType)
{
    return ((bool(__thiscall *)(CPed*, eWeaponType))0x5DF300)(this, weaponType);
}

// 0x5DF340
bool CPed::DoGunFlash(int arg0, bool arg1)
{
    return ((bool(__thiscall *)(CPed*, int, bool))0x5DF340)(this, arg0, arg1);
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
void CPed::ShoulderBoneRotation(RpClump* clump)
{
    plugin::Call<0x5DF560, RpClump*>(clump);
}

// 0x5DF8D0
void CPed::SetLookTimer(unsigned int time)
{
    ((void(__thiscall *)(CPed*, unsigned int))0x5DF8D0)(this, time);
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
void CPed::RestoreHeadingRateCB(CAnimBlendAssociation* association, void* data)
{
    ((void(__cdecl *)(CAnimBlendAssociation*, void*))0x5DFD70)(association, data);
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
void CPed::GetTransformedBonePosition(RwV3d& inOffsetOutPosn, unsigned int boneId, bool updateSkinBones)
{
    ((void(__thiscall *)(CPed*, RwV3d&, unsigned int, bool))0x5E01C0)(this, inOffsetOutPosn, boneId, updateSkinBones);
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
void CPed::DropEntityThatThisPedIsHolding(unsigned char arg0)
{
    ((void(__thiscall *)(CPed*, unsigned char))0x5E0360)(this, arg0);
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
bool CPed::PositionPedOutOfCollision(int exitDoor, CVehicle* vehicke, bool findClosestNode)
{
    return ((bool(__thiscall *)(CPed*, int, CVehicle*, bool))0x5E0820)(this, exitDoor, vehicke, findClosestNode);
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
void CPed::SortPeds(CPed** pedList, int arg1, int arg2)
{
    ((void(__thiscall *)(CPed*, CPed**, int, int))0x5E17E0)(this, pedList, arg1, arg2);
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

// 0x5E3990
void CPed::RemoveWeaponModel(int modelIndex)
{
    ((void(__thiscall *)(CPed*, int))0x5E3990)(this, modelIndex);
}

// 0x5E3A90
void CPed::AddGogglesModel(int modelIndex, bool* pGogglesType)
{
    ((void(__thiscall *)(CPed*, int, bool*))0x5E3A90)(this, modelIndex, pGogglesType);
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
        return eWeaponSkill::WEAPSKILL_STD;

    if (!m_nPedType || m_nPedType == PED_TYPE_PLAYER2)
    {
        int skillStat = CWeaponInfo::GetSkillStatIndex(weaponType);
        CWeaponInfo* pGolfClubWeaponInfo = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::WEAPSKILL_PRO);
        float golfClubStatLevel = static_cast<float>(pGolfClubWeaponInfo->m_nReqStatLevel);
        if (golfClubStatLevel <= CStats::GetStatValue((eStats)skillStat))
            return eWeaponSkill::WEAPSKILL_PRO;

        CWeaponInfo* brassKnuckleWeaponInfo = CWeaponInfo::GetWeaponInfo(weaponType, eWeaponSkill::WEAPSKILL_STD);
        float brassKnuckleStatLevel = static_cast<float>(brassKnuckleWeaponInfo->m_nReqStatLevel);
        if (brassKnuckleStatLevel > CStats::GetStatValue((eStats)skillStat))
            return eWeaponSkill::WEAPSKILL_POOR;

        return eWeaponSkill::WEAPSKILL_STD;
    }

    if (weaponType != WEAPON_PISTOL || m_nPedType != PED_TYPE_COP)
        return m_nWeaponSkill;

    return eWeaponSkill::WEAPSKILL_COP;
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
void CPed::GetBonePosition(RwV3d& outPosition, unsigned int boneId, bool updateSkinBones)
{
    ((void(__thiscall *)(CPed*, RwV3d&, unsigned int, bool))0x5E4280)(this, outPosition, boneId, updateSkinBones);
}

// 0x5E4390
CObject* CPed::GiveObjectToPedToHold(int modelIndex, unsigned char replace)
{
    return ((CObject* (__thiscall *)(CPed*, int, unsigned char))0x5E4390)(this, modelIndex, replace);
}

// 0x5E4500
void CPed::SetPedState(ePedState pedState)
{
    ((void(__thiscall *)(CPed*, ePedState))0x5E4500)(this, pedState);
}

// 0x5E47E0
void CPed::SetCharCreatedBy(unsigned char createdBy)
{
    ((void(__thiscall *)(CPed*, unsigned char))0x5E47E0)(this, createdBy);
}

// 0x5E4C50
void CPed::CalculateNewVelocity()
{
    ((void(__thiscall *)(CPed*))0x5E4C50)(this);
}

// 0x5E52E0
void CPed::CalculateNewOrientation()
{
    ((void(__thiscall *)(CPed*))0x5E52E0)(this);
}

// 0x5E5320
void CPed::ClearAll()
{
    ((void(__thiscall *)(CPed*))0x5E5320)(this);
}

// 0x5E5380
void CPed::DoFootLanded(bool leftFoot, unsigned char arg1)
{
    ((void(__thiscall *)(CPed*, bool, unsigned char))0x5E5380)(this, leftFoot, arg1);
}

// 0x5E57F0
void CPed::PlayFootSteps()
{
    ((void(__thiscall *)(CPed*))0x5E57F0)(this);
}

// 0x5E5ED0
void CPed::AddWeaponModel(int modelIndex)
{
    ((void(__thiscall *)(CPed*, int))0x5E5ED0)(this, modelIndex);
}

// 0x5E6010
void CPed::TakeOffGoggles()
{
    ((void(__thiscall *)(CPed*))0x5E6010)(this);
}

// 0x5E6080
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

// 0x5E61F0
void CPed::SetCurrentWeapon(int slot)
{
    ((void(__thiscall *)(CPed*, int))0x5E61F0)(this, slot);
}

// 0x5E6280
void CPed::SetCurrentWeapon(eWeaponType weaponType)
{
    ((void(__thiscall *)(CPed*, eWeaponType))0x5E6280)(this, weaponType);
}

// 0x5E62B0
void CPed::ClearWeapon(eWeaponType weaponType)
{
    ((void(__thiscall*)(CPed*, eWeaponType))0x5E62B0)(this, weaponType);
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
    CWeaponInfo* getWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_UNARMED, eWeaponSkill::WEAPSKILL_STD);
    SetCurrentWeapon(getWeaponInfo->m_nSlot);
}

// 0x5E6370
void CPed::RemoveWeaponWhenEnteringVehicle(int arg0)
{
    ((void(__thiscall *)(CPed*, int))0x5E6370)(this, arg0);
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
        CWeaponInfo* weaponInfo = CWeaponInfo::GetWeaponInfo(m_nSavedWeapon, eWeaponSkill::WEAPSKILL_STD);
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
CEntity* CPed::AttachPedToEntity(CEntity* entity, CVector offset, unsigned short arg2, float arg3, eWeaponType weaponType)
{
    return ((CEntity* (__thiscall *)(CPed*, CEntity*, CVector, unsigned short, float, eWeaponType))0x5E7CB0)(this, entity, offset, arg2, arg3, weaponType);
}

// 0x5E7E60
CEntity* CPed::AttachPedToBike(CEntity* entity, CVector offset, unsigned short arg2, float arg3, float arg4, eWeaponType weaponType)
{
    return ((CEntity* (__thiscall *)(CPed*, CEntity*, CVector, unsigned short, float, float, eWeaponType))0x5E7E60)(this, entity, offset, arg2, arg3, arg4, weaponType);
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
void CPed::GiveDelayedWeapon(eWeaponType weaponType, unsigned int ammo)
{
    ((void(__thiscall *)(CPed*, eWeaponType, unsigned int))0x5E89B0)(this, weaponType, ammo);
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
            SetCurrentWeapon(CWeaponInfo::GetWeaponInfo(WEAPON_AK47, eWeaponSkill::WEAPSKILL_STD)->m_nSlot);
        }
        else {
            CWeaponInfo* pWeaponInfo = nullptr;
            if (CCheat::m_aCheatsActive[eCheats::CHEAT_ROCKET_MAYHEM]) {
                GiveDelayedWeapon(WEAPON_RLAUNCHER, 200);
                pWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_RLAUNCHER, eWeaponSkill::WEAPSKILL_STD);
            }
            else {
                CPed::GiveDelayedWeapon(WEAPON_PISTOL, 200);
                pWeaponInfo = CWeaponInfo::GetWeaponInfo(WEAPON_PISTOL, eWeaponSkill::WEAPSKILL_STD);
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
void CPed::DisablePedSpeech(short arg0)
{
    ((void(__thiscall *)(CPed*, short))0x5EFF60)(this, arg0);
}

// 0x5EFF70
void CPed::EnablePedSpeech()
{
    ((void(__thiscall *)(CPed*))0x5EFF70)(this);
}

// 0x5EFF80
void CPed::DisablePedSpeechForScriptSpeech(short arg0)
{
    ((void(__thiscall *)(CPed*, short))0x5EFF80)(this, arg0);
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
void CPed::SayScript(int arg0, unsigned char arg1, unsigned char arg2, unsigned char arg3)
{
    ((void(__thiscall *)(CPed*, int, unsigned char, unsigned char, unsigned char))0x5EFFB0)(this, arg0, arg1, arg2, arg3);
}

// 0x5EFFE0
void CPed::Say(unsigned short arg0, unsigned int arg1, float arg2, unsigned char arg3, unsigned char arg4, unsigned char arg5)
{
    ((void(__thiscall *)(CPed*, unsigned short, unsigned int, float, unsigned char, unsigned char, unsigned char))0x5EFFE0)(this, arg0, arg1, arg2, arg3, arg4, arg5);
}

// 0x5F0060
RwObject* SetPedAtomicVisibilityCB(RwObject* rwObject, void* data)
{
    return ((RwObject* (__cdecl *)(RwObject*, void*))0x5F0060)(rwObject, data);
}

// 0x5F0140
void CPed::RemoveBodyPart(int boneId, char localDir)
{
    ((void(__thiscall *)(CPed*, int, char))0x5F0140)(this, boneId, localDir);
}

// 0x5F0190
void CPed::SpawnFlyingComponent(int arg0, char arg1)
{
    ((void(__thiscall *)(CPed*, int, char))0x5F0190)(this, arg0, arg1);
}

// 0x5F01A0
bool CPed::DoesLOSBulletHitPed(CColPoint& colPoint)
{
    return ((bool(__thiscall *)(CPed*, CColPoint&))0x5F01A0)(this, colPoint);
}

// 0x5F0250
void CPed::RemoveWeaponAnims(int likeUnused, float blendDelta)
{
    ((void(__thiscall *)(CPed*, int, float))0x5F0250)(this, likeUnused, blendDelta);
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
