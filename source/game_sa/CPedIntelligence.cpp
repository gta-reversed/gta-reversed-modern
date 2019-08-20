/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/

#include "StdInc.h"

// Converted from thiscall void CPedIntelligence::SetPedDecisionMakerType(int newtype) 0x600B50
void CPedIntelligence::SetPedDecisionMakerType(int newtype) {
    plugin::CallMethod<0x600B50, CPedIntelligence*, int>(this, newtype);
}

// Converted from thiscall void CPedIntelligence::SetPedDecisionMakerTypeInGroup(int newtype) 0x600BB0 
void CPedIntelligence::SetPedDecisionMakerTypeInGroup(int newtype) {
    plugin::CallMethod<0x600BB0, CPedIntelligence*, int>(this, newtype);
}

// Converted from thiscall void CPedIntelligence::RestorePedDecisionMakerType(void) 0x600BC0 
void CPedIntelligence::RestorePedDecisionMakerType() {
    plugin::CallMethod<0x600BC0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::SetHearingRange(float range) 0x600BE0 
void CPedIntelligence::SetHearingRange(float range) {
    plugin::CallMethod<0x600BE0, CPedIntelligence*, float>(this, range);
}

// Converted from thiscall void CPedIntelligence::SetSeeingRange(float range) 0x600BF0 
void CPedIntelligence::SetSeeingRange(float range) {
    plugin::CallMethod<0x600BF0, CPedIntelligence*, float>(this, range);
}

// Converted from thiscall bool CPedIntelligence::IsInHearingRange(CVector const& posn) 0x600C00 
bool CPedIntelligence::IsInHearingRange(CVector const& posn) {
    return plugin::CallMethodAndReturn<bool, 0x600C00, CPedIntelligence*, CVector const&>(this, posn);
}

// Converted from thiscall bool CPedIntelligence::IsInSeeingRange(CVector const& posn) 0x600C60 
bool CPedIntelligence::IsInSeeingRange(CVector const& posn) {
    return plugin::CallMethodAndReturn<bool, 0x600C60, CPedIntelligence*, CVector const&>(this, posn);
}

// Converted from thiscall bool CPedIntelligence::FindRespectedFriendInInformRange(void) 0x600CF0 
bool CPedIntelligence::FindRespectedFriendInInformRange() {
    return plugin::CallMethodAndReturn<bool, 0x600CF0, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsRespondingToEvent(int event) 0x600DB0 
bool CPedIntelligence::IsRespondingToEvent(int event) {
    return plugin::CallMethodAndReturn<bool, 0x600DB0, CPedIntelligence*, int>(this, event);
}

// Converted from thiscall void CPedIntelligence::AddTaskPhysResponse(CTask *task,bool arg2) 0x600DC0 
void CPedIntelligence::AddTaskPhysResponse(CTask* task, bool arg2) {
    plugin::CallMethod<0x600DC0, CPedIntelligence*, CTask*, bool>(this, task, arg2);
}

// Converted from thiscall void CPedIntelligence::AddTaskEventResponseTemp(CTask *task,bool arg2) 0x600DE0 
void CPedIntelligence::AddTaskEventResponseTemp(CTask* task, bool arg2) {
    plugin::CallMethod<0x600DE0, CPedIntelligence*, CTask*, bool>(this, task, arg2);
}

// Converted from thiscall void CPedIntelligence::AddTaskEventResponseNonTemp(CTask *task,bool arg2) 0x600E00 
void CPedIntelligence::AddTaskEventResponseNonTemp(CTask* task, bool arg2) {
    plugin::CallMethod<0x600E00, CPedIntelligence*, CTask*, bool>(this, task, arg2);
}

// Converted from thiscall void CPedIntelligence::AddTaskPrimaryMaybeInGroup(CTask *task,bool arg2) 0x600E20 
void CPedIntelligence::AddTaskPrimaryMaybeInGroup(CTask* task, bool arg2) {
    plugin::CallMethod<0x600E20, CPedIntelligence*, CTask*, bool>(this, task, arg2);
}

// Converted from thiscall CTask* CPedIntelligence::FindTaskByType(int type) 0x600EE0 
CTask* CPedIntelligence::FindTaskByType(int type) {
    return plugin::CallMethodAndReturn<CTask*, 0x600EE0, CPedIntelligence*, int>(this, type);
}

// Converted from thiscall CTaskSimpleFight* CPedIntelligence::GetTaskFighting(void) 0x600F30 
CTaskSimpleFight* CPedIntelligence::GetTaskFighting() {
    return plugin::CallMethodAndReturn<CTaskSimpleFight*, 0x600F30, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun(void) 0x600F70 
CTaskSimpleUseGun* CPedIntelligence::GetTaskUseGun() {
    return plugin::CallMethodAndReturn<CTaskSimpleUseGun*, 0x600F70, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow(void) 0x600FB0 
CTaskSimpleThrowProjectile* CPedIntelligence::GetTaskThrow() {
    return plugin::CallMethodAndReturn<CTaskSimpleThrowProjectile*, 0x600FB0, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleHoldEntity* CPedIntelligence::GetTaskHold(bool arg1) 0x600FF0 
CTaskSimpleHoldEntity* CPedIntelligence::GetTaskHold(bool arg1) {
    return plugin::CallMethodAndReturn<CTaskSimpleHoldEntity*, 0x600FF0, CPedIntelligence*, bool>(this, arg1);
}

// Converted from thiscall CTaskSimpleSwim* CPedIntelligence::GetTaskSwim(void) 0x601070 
CTaskSimpleSwim* CPedIntelligence::GetTaskSwim() {
    return plugin::CallMethodAndReturn<CTaskSimpleSwim*, 0x601070, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool arg1) 0x6010A0 
CTaskSimpleDuck* CPedIntelligence::GetTaskDuck(bool arg1) {
    return plugin::CallMethodAndReturn<CTaskSimpleDuck*, 0x6010A0, CPedIntelligence*, bool>(this, arg1);
}

// Converted from thiscall CTaskSimpleJetPack* CPedIntelligence::GetTaskJetPack(void) 0x601110 
CTaskSimpleJetPack* CPedIntelligence::GetTaskJetPack() {
    return plugin::CallMethodAndReturn<CTaskSimpleJetPack*, 0x601110, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleInAir* CPedIntelligence::GetTaskInAir(void) 0x601150 
CTaskSimpleInAir* CPedIntelligence::GetTaskInAir() {
    return plugin::CallMethodAndReturn<CTaskSimpleInAir*, 0x601150, CPedIntelligence*>(this);
}

// Converted from thiscall CTaskSimpleClimb* CPedIntelligence::GetTaskClimb(void) 0x601180 
CTaskSimpleClimb* CPedIntelligence::GetTaskClimb() {
    return plugin::CallMethodAndReturn<CTaskSimpleClimb*, 0x601180, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::GetUsingParachute(void) 0x6011B0 
bool CPedIntelligence::GetUsingParachute() {
    return plugin::CallMethodAndReturn<bool, 0x6011B0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::SetTaskDuckSecondary(ushort arg1) 0x601230 
void CPedIntelligence::SetTaskDuckSecondary(unsigned short arg1) {
    plugin::CallMethod<0x601230, CPedIntelligence*, unsigned short>(this, arg1);
}

// Converted from thiscall void CPedIntelligence::ClearTaskDuckSecondary(void) 0x601390 
void CPedIntelligence::ClearTaskDuckSecondary() {
    plugin::CallMethod<0x601390, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::ClearTasks(bool arg1,bool arg2) 0x601420 
void CPedIntelligence::ClearTasks(bool arg1, bool arg2) {
    plugin::CallMethod<0x601420, CPedIntelligence*, bool, bool>(this, arg1, arg2);
}

// Converted from thiscall void CPedIntelligence::FlushImmediately(bool arg1) 0x601640 
void CPedIntelligence::FlushImmediately(bool arg1) {
    plugin::CallMethod<0x601640, CPedIntelligence*, bool>(this, arg1);
}

// Converted from thiscall C2dEffect* CPedIntelligence::GetEffectInUse(void) 0x6018D0 
C2dEffect* CPedIntelligence::GetEffectInUse() {
    return plugin::CallMethodAndReturn<C2dEffect*, 0x6018D0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::SetEffectInUse(C2dEffect *arg1) 0x6018E0 
void CPedIntelligence::SetEffectInUse(C2dEffect* arg1) {
    plugin::CallMethod<0x6018E0, CPedIntelligence*, C2dEffect*>(this, arg1);
}

// Converted from thiscall void CPedIntelligence::ProcessAfterProcCol(void) 0x6018F0 
void CPedIntelligence::ProcessAfterProcCol() {
    plugin::CallMethod<0x6018F0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::ProcessAfterPreRender(void) 0x6019B0 
void CPedIntelligence::ProcessAfterPreRender() {
    plugin::CallMethod<0x6019B0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::ProcessEventHandler(void) 0x601BB0 
void CPedIntelligence::ProcessEventHandler() {
    plugin::CallMethod<0x601BB0, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsFriendlyWith(CPed const& ped) 0x601BC0 
bool CPedIntelligence::IsFriendlyWith(CPed const& ped) {
    return plugin::CallMethodAndReturn<bool, 0x601BC0, CPedIntelligence*, CPed const&>(this, ped);
}

// Converted from thiscall bool CPedIntelligence::IsThreatenedBy(CPed const& ped) 0x601C30 
bool CPedIntelligence::IsThreatenedBy(CPed const& ped) {
    return plugin::CallMethodAndReturn<bool, 0x601C30, CPedIntelligence*, CPed const&>(this, ped);
}

// Converted from thiscall bool CPedIntelligence::Respects(CPed const& ped) 0x601C90 
bool CPedIntelligence::Respects(CPed const& ped) {
    return plugin::CallMethodAndReturn<bool, 0x601C90, CPedIntelligence*, CPed const&>(this, ped);
}

// Converted from thiscall bool CPedIntelligence::IsInACarOrEnteringOne(void) 0x601CC0 
bool CPedIntelligence::IsInACarOrEnteringOne() {
    return plugin::CallMethodAndReturn<bool, 0x601CC0, CPedIntelligence*>(this);
}

// Converted from cdecl bool CPedIntelligence::AreFriends(CPed const& ped1,CPed const& ped2) 0x601D10 
bool CPedIntelligence::AreFriends(CPed const& ped1, CPed const& ped2) {
    return plugin::CallAndReturn<bool, 0x601D10, CPed const&, CPed const&>(ped1, ped2);
}

// Converted from thiscall bool CPedIntelligence::IsPedGoingSomewhereOnFoot(void) 0x601D50 
bool CPedIntelligence::IsPedGoingSomewhereOnFoot() {
    return plugin::CallMethodAndReturn<bool, 0x601D50, CPedIntelligence*>(this);
}

// Converted from thiscall int* CPedIntelligence::GetMoveStateFromGoToTask(void) 0x601D70 
int* CPedIntelligence::GetMoveStateFromGoToTask() {
    return plugin::CallMethodAndReturn<int*, 0x601D70, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::FlushIntelligence(void) 0x601DA0 
void CPedIntelligence::FlushIntelligence() {
    plugin::CallMethod<0x601DA0, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::TestForStealthKill(CPed *pPed,bool arg2) 0x601E00 
bool CPedIntelligence::TestForStealthKill(CPed* pPed, bool arg2) {
    return plugin::CallMethodAndReturn<bool, 0x601E00, CPedIntelligence*, CPed*, bool>(this, pPed, arg2);
}

// Converted from thiscall void CPedIntelligence::RecordEventForScript(int EventID,int EventPriority) 0x602050 
void CPedIntelligence::RecordEventForScript(int EventID, int EventPriority) {
    plugin::CallMethod<0x602050, CPedIntelligence*, int, int>(this, EventID, EventPriority);
}

// Converted from thiscall bool CPedIntelligence::HasInterestingEntites(void) 0x602080 
bool CPedIntelligence::HasInterestingEntites() {
    return plugin::CallMethodAndReturn<bool, 0x602080, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsInterestingEntity(CEntity *pEntity) 0x6020A0 
bool CPedIntelligence::IsInterestingEntity(CEntity* pEntity) {
    return plugin::CallMethodAndReturn<bool, 0x6020A0, CPedIntelligence*, CEntity*>(this, pEntity);
}

// Converted from thiscall void CPedIntelligence::LookAtInterestingEntities(void) 0x6020D0 
void CPedIntelligence::LookAtInterestingEntities() {
    plugin::CallMethod<0x6020D0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::RemoveAllInterestingEntities(void) 0x602320 
void CPedIntelligence::RemoveAllInterestingEntities() {
    plugin::CallMethod<0x602320, CPedIntelligence*>(this);
}

// Converted from thiscall bool CPedIntelligence::IsPedGoingForCarDoor(void) 0x602350 
bool CPedIntelligence::IsPedGoingForCarDoor() {
    return plugin::CallMethodAndReturn<bool, 0x602350, CPedIntelligence*>(this);
}

// Converted from thiscall float CPedIntelligence::CanSeeEntityWithLights(CEntity const*pEntity,bool arg2) 0x605550 
float CPedIntelligence::CanSeeEntityWithLights(CEntity const* pEntity, bool arg2) {
    return plugin::CallMethodAndReturn<float, 0x605550, CPedIntelligence*, CEntity const*, bool>(this, pEntity, arg2);
}

// Converted from thiscall void CPedIntelligence::ProcessStaticCounter(void) 0x605650 
void CPedIntelligence::ProcessStaticCounter() {
    plugin::CallMethod<0x605650, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::ProcessFirst(void) 0x6073A0 
void CPedIntelligence::ProcessFirst() {
    plugin::CallMethod<0x6073A0, CPedIntelligence*>(this);
}

// Converted from thiscall void CPedIntelligence::Process(void) 0x608260 
void CPedIntelligence::Process() {
    plugin::CallMethod<0x608260, CPedIntelligence*>(this);
}

// Converted from cdecl void CPedIntelligence::operator delete(void * arg1) 0x6074E0 
void CPedIntelligence::operator delete(void* arg1) {
    plugin::Call<0x6074E0, void*>(arg1);
}