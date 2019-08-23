#include "StdInc.h"

/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "CPad.h"

// mouse states
CMouseControllerState& CPad::PCTempMouseControllerState = *(CMouseControllerState*)0xB73404;
CMouseControllerState& CPad::NewMouseControllerState = *(CMouseControllerState*)0xB73418;
CMouseControllerState& CPad::OldMouseControllerState = *(CMouseControllerState*)0xB7342C;


// Converted from thiscall void CPad::UpdateMouse(void) 0x53F3C0
void CPad::UpdateMouse() {
    plugin::CallMethod<0x53F3C0, CPad*>(this);
}

// Converted from thiscall void CPad::ReconcileTwoControllersInput(CControllerState const&controllerA,CControllerState const&controllerB) 0x53F530
void CPad::ReconcileTwoControllersInput(CControllerState const& controllerA, CControllerState const& controllerB) {
    plugin::CallMethod<0x53F530, CPad*, CControllerState const&, CControllerState const&>(this, controllerA, controllerB);
}

// Converted from thiscall void CPad::SetDrunkInputDelay(int delay) 0x53F910
void CPad::SetDrunkInputDelay(int delay) {
    plugin::CallMethod<0x53F910, CPad*, int>(this, delay);
}

// Converted from thiscall void CPad::StartShake(short time,uchar frequency,uint) 0x53F920
void CPad::StartShake(short time, unsigned char frequency, unsigned int arg2) {
    plugin::CallMethod<0x53F920, CPad*, short, unsigned char, unsigned int>(this, time, frequency, arg2);
}

// Converted from thiscall void CPad::StartShake_Distance(short time,uchar frequency,float x,float y,float z) 0x53F9A0
void CPad::StartShake_Distance(short time, unsigned char frequency, float x, float y, float z) {
    plugin::CallMethod<0x53F9A0, CPad*, short, unsigned char, float, float, float>(this, time, frequency, x, y, z);
}

// Converted from thiscall void CPad::StartShake_Train(float x,float y) 0x53FA70
void CPad::StartShake_Train(float x, float y) {
    plugin::CallMethod<0x53FA70, CPad*, float, float>(this, x, y);
}

// Converted from thiscall void CPad::ProcessPCSpecificStuff(void) 0x53FB40
void CPad::ProcessPCSpecificStuff() {
    plugin::CallMethod<0x53FB40, CPad*>(this);
}

// Converted from thiscall void CPad::StopShaking(short) 0x53FB50
void CPad::StopShaking(short arg0) {
    plugin::CallMethod<0x53FB50, CPad*, short>(this, arg0);
}

// Converted from cdecl CPad* CPad::GetPad(int padNumber) 0x53FB70
CPad* CPad::GetPad(int padNumber) {
    return plugin::CallAndReturn<CPad*, 0x53FB70, int>(padNumber);
}

// Converted from thiscall short CPad::GetSteeringLeftRight(void) 0x53FB80
short CPad::GetSteeringLeftRight() {
    return plugin::CallMethodAndReturn<short, 0x53FB80, CPad*>(this);
}

// Converted from thiscall short CPad::GetSteeringUpDown(void) 0x53FBD0
short CPad::GetSteeringUpDown() {
    return plugin::CallMethodAndReturn<short, 0x53FBD0, CPad*>(this);
}

short CPad::GetPedWalkLeftRight(CPed* pPed) {
    return plugin::CallMethodAndReturn<short, 0x540DC0, CPad*, CPed*>(this, pPed);
}

short CPad::GetPedWalkUpDown(CPed* pPed) {
    return plugin::CallMethodAndReturn<short, 0x540E20, CPad*, CPed*>(this, pPed);
}

// Converted from thiscall short CPad::GetPedWalkLeftRight(void) 0x53FC90
short CPad::GetPedWalkLeftRight() {
    return plugin::CallMethodAndReturn<short, 0x53FC90, CPad*>(this);
}

// Converted from thiscall short CPad::GetPedWalkUpDown(void) 0x53FD30
short CPad::GetPedWalkUpDown() {
    return plugin::CallMethodAndReturn<short, 0x53FD30, CPad*>(this);
}

// Converted from thiscall bool CPad::GetLookLeft(void) 0x53FDD0
bool CPad::GetLookLeft() {
    return plugin::CallMethodAndReturn<bool, 0x53FDD0, CPad*>(this);
}

// Converted from thiscall bool CPad::GetLookRight(void) 0x53FE10
bool CPad::GetLookRight() {
    return plugin::CallMethodAndReturn<bool, 0x53FE10, CPad*>(this);
}

// Converted from thiscall bool CPad::GetLookBehindForCar(void) 0x53FE70
bool CPad::GetLookBehindForCar() {
    return plugin::CallMethodAndReturn<bool, 0x53FE70, CPad*>(this);
}

// Converted from thiscall bool CPad::GetLookBehindForPed(void) 0x53FEC0
bool CPad::GetLookBehindForPed() {
    return plugin::CallMethodAndReturn<bool, 0x53FEC0, CPad*>(this);
}

// Converted from thiscall bool CPad::GetHorn(void) 0x53FEE0
bool CPad::GetHorn() {
    return plugin::CallMethodAndReturn<bool, 0x53FEE0, CPad*>(this);
}

// Converted from thiscall bool CPad::HornJustDown(void) 0x53FF30
bool CPad::HornJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x53FF30, CPad*>(this);
}

// Converted from thiscall bool CPad::GetHydraulicJump(void) 0x53FF70
bool CPad::GetHydraulicJump() {
    return plugin::CallMethodAndReturn<bool, 0x53FF70, CPad*>(this);
}

// Converted from thiscall short CPad::GetCarGunFired(void) 0x53FF90
short CPad::GetCarGunFired() {
    return plugin::CallMethodAndReturn<short, 0x53FF90, CPad*>(this);
}

// Converted from thiscall short CPad::CarGunJustDown(void) 0x53FFE0
short CPad::CarGunJustDown() {
    return plugin::CallMethodAndReturn<short, 0x53FFE0, CPad*>(this);
}

// Converted from thiscall short CPad::GetHandBrake(void) 0x540040
short CPad::GetHandBrake() {
    return plugin::CallMethodAndReturn<short, 0x540040, CPad*>(this);
}

// Converted from thiscall short CPad::GetBrake(void) 0x540080
short CPad::GetBrake() {
    return plugin::CallMethodAndReturn<short, 0x540080, CPad*>(this);
}

// Converted from thiscall bool CPad::GetExitVehicle(void) 0x5400D0
bool CPad::GetExitVehicle() {
    return plugin::CallMethodAndReturn<bool, 0x5400D0, CPad*>(this);
}

// Converted from thiscall bool CPad::ExitVehicleJustDown(void) 0x540120
bool CPad::ExitVehicleJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540120, CPad*>(this);
}

// Converted from thiscall uchar CPad::GetMeleeAttack(void) 0x540340
unsigned char CPad::GetMeleeAttack() {
    return plugin::CallMethodAndReturn<unsigned char, 0x540340, CPad*>(this);
}

// Converted from thiscall uchar CPad::MeleeAttackJustDown(void) 0x540390
unsigned char CPad::MeleeAttackJustDown() {
    return plugin::CallMethodAndReturn<unsigned char, 0x540390, CPad*>(this);
}

// Converted from thiscall short CPad::GetAccelerate(void) 0x5403F0
short CPad::GetAccelerate() {
    return plugin::CallMethodAndReturn<short, 0x5403F0, CPad*>(this);
}

// Converted from thiscall bool CPad::GetAccelerateJustDown(void) 0x540440
bool CPad::GetAccelerateJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540440, CPad*>(this);
}

// Converted from thiscall bool CPad::NextStationJustUp(void) 0x5405B0
bool CPad::NextStationJustUp() {
    return plugin::CallMethodAndReturn<bool, 0x5405B0, CPad*>(this);
}

// Converted from thiscall bool CPad::LastStationJustUp(void) 0x5405E0
bool CPad::LastStationJustUp() {
    return plugin::CallMethodAndReturn<bool, 0x5405E0, CPad*>(this);
}

// Converted from thiscall bool CPad::CycleWeaponLeftJustDown(void) 0x540610
bool CPad::CycleWeaponLeftJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540610, CPad*>(this);
}

// Converted from thiscall bool CPad::CycleWeaponRightJustDown(void) 0x540640
bool CPad::CycleWeaponRightJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540640, CPad*>(this);
}

// Converted from thiscall bool CPad::GetTarget(void) 0x540670
bool CPad::GetTarget() {
    return plugin::CallMethodAndReturn<bool, 0x540670, CPad*>(this);
}

// Converted from thiscall bool CPad::GetDuck(void) 0x540700
bool CPad::GetDuck() {
    return plugin::CallMethodAndReturn<bool, 0x540700, CPad*>(this);
}

// Converted from thiscall bool CPad::DuckJustDown(void) 0x540720
bool CPad::DuckJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540720, CPad*>(this);
}

// Converted from thiscall bool CPad::GetJump(void) 0x540750
bool CPad::GetJump() {
    return plugin::CallMethodAndReturn<bool, 0x540750, CPad*>(this);
}

// Converted from thiscall bool CPad::JumpJustDown(void) 0x540770
bool CPad::JumpJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540770, CPad*>(this);
}

// Converted from thiscall bool CPad::GetSprint(void) 0x5407A0
bool CPad::GetSprint() {
    return plugin::CallMethodAndReturn<bool, 0x5407A0, CPad*>(this);
}

// Converted from thiscall bool CPad::SprintJustDown(void) 0x5407F0
bool CPad::SprintJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x5407F0, CPad*>(this);
}

// Converted from thiscall bool CPad::ShiftTargetLeftJustDown(void) 0x540850
bool CPad::ShiftTargetLeftJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540850, CPad*>(this);
}

// Converted from thiscall bool CPad::ShiftTargetRightJustDown(void) 0x540880
bool CPad::ShiftTargetRightJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540880, CPad*>(this);
}

// Converted from thiscall short CPad::GetDisplayVitalStats(CPed *ped) 0x5408B0
short CPad::GetDisplayVitalStats(CPed* ped) {
    return plugin::CallMethodAndReturn<short, 0x5408B0, CPad*, CPed*>(this, ped);
}

// Converted from thiscall bool CPad::CollectPickupJustDown(void) 0x540A70
bool CPad::CollectPickupJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540A70, CPad*>(this);
}

// Converted from thiscall bool CPad::GetForceCameraBehindPlayer(void) 0x540AE0
bool CPad::GetForceCameraBehindPlayer() {
    return plugin::CallMethodAndReturn<bool, 0x540AE0, CPad*>(this);
}

// Converted from thiscall bool CPad::SniperZoomIn(void) 0x540B30
bool CPad::SniperZoomIn() {
    return plugin::CallMethodAndReturn<bool, 0x540B30, CPad*>(this);
}

// Converted from thiscall bool CPad::SniperZoomOut(void) 0x540B80
bool CPad::SniperZoomOut() {
    return plugin::CallMethodAndReturn<bool, 0x540B80, CPad*>(this);
}

// Converted from thiscall bool CPad::GetGroupControlForward(void) 0x541190
bool CPad::GetGroupControlForward() {
    return plugin::CallMethodAndReturn<bool, 0x541190, CPad*>(this);
}

// Converted from thiscall bool CPad::GetGroupControlBack(void) 0x5411B0
bool CPad::GetGroupControlBack() {
    return plugin::CallMethodAndReturn<bool, 0x5411B0, CPad*>(this);
}

// Converted from thiscall bool CPad::ConversationYesJustDown(void) 0x5411D0
bool CPad::ConversationYesJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x5411D0, CPad*>(this);
}

// Converted from thiscall bool CPad::ConversationNoJustDown(void) 0x541200
bool CPad::ConversationNoJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x541200, CPad*>(this);
}

// Converted from thiscall bool CPad::GroupControlForwardJustDown(void) 0x541230
bool CPad::GroupControlForwardJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x541230, CPad*>(this);
}

// Converted from thiscall bool CPad::GroupControlBackJustDown(void) 0x541260
bool CPad::GroupControlBackJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x541260, CPad*>(this);
}

// Converted from thiscall void CPad::Clear(bool enablePlayerControls, bool resetPhase) 0x541A70
void CPad::Clear(bool enablePlayerControls, bool resetPhase) {
    plugin::CallMethod<0x541A70, CPad*, bool, bool>(this, enablePlayerControls, resetPhase);
}

// Converted from thiscall void CPad::UpdatePads(void) 0x541DD0
void CPad::UpdatePads() {
    plugin::CallMethod<0x541DD0, CPad*>(this);
}

void CPad::SetTouched()
{
    plugin::CallMethod<0x53F200, CPad*>(this);
}

unsigned int CPad::GetTouchedTimeDelta()
{
    return plugin::CallMethodAndReturn<unsigned int, 0x53F210, CPad*>(this);
}

bool CPad::WeaponJustDown(CPed* pPed)
{
    return plugin::CallMethodAndReturn<bool, 0x540250, CPad*, CPed*>(this, pPed);
}

bool CPad::GetEnterTargeting()
{
    return plugin::CallMethodAndReturn<bool, 0x5406B0, CPad*>(this);
}

int CPad::GetWeapon(CPed* pPed)
{
    return plugin::CallMethodAndReturn<int, 0x540180, CPad*, CPed*>(this, pPed);
}