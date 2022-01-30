/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"
#include "CDebugMenu.h"

// mouse states
CMouseControllerState& CPad::PCTempMouseControllerState = *(CMouseControllerState*)0xB73404;
CMouseControllerState& CPad::NewMouseControllerState = *(CMouseControllerState*)0xB73418;
CMouseControllerState& CPad::OldMouseControllerState = *(CMouseControllerState*)0xB7342C;

CKeyboardState& CPad::TempKeyState = *(CKeyboardState*)0xB72CB0;
CKeyboardState& CPad::OldKeyState = *(CKeyboardState*)0xB72F20;
CKeyboardState& CPad::NewKeyState = *(CKeyboardState*)0xB73190;

CPad* CPad::Pads = (CPad*)0xB73458; // size is 2

bool& CPad::bInvertLook4Pad = *(bool*)0xB73402;

void CPad::InjectHooks() {
    RH_ScopedClass(CPad);
    RH_ScopedCategoryGlobal();

    HookInstall(0x541DD0, CPad::UpdatePads); // changes logic of the function and shouldn't be toggled on/off

    RH_ScopedInstall(isEnterJustPressed, 0x4D5980);
    RH_ScopedInstall(isStandardKeyJustPressed, 0x4D59B0);
    RH_ScopedInstall(isMenuKeyJustPressed, 0x744D50);
    RH_ScopedInstall(isTabJustPressed, 0x744D90);
    RH_ScopedInstall(Clear, 0x541A70);
}

// 0x541D90
void CPad::Initialise() {
    plugin::Call<0x541D90>();
}

// 0x53F3C0
void CPad::UpdateMouse() {
    plugin::CallMethod<0x53F3C0, CPad*>(this);
}

// 0x53F530
void CPad::ReconcileTwoControllersInput(CControllerState const& controllerA, CControllerState const& controllerB) {
    plugin::CallMethod<0x53F530, CPad*, CControllerState const&, CControllerState const&>(this, controllerA, controllerB);
}

// 0x53F910
void CPad::SetDrunkInputDelay(int32 delay) {
    plugin::CallMethod<0x53F910, CPad*, int32>(this, delay);
}

// 0x53F920
void CPad::StartShake(int16 time, uint8 frequency, uint32 arg2) {
    plugin::CallMethod<0x53F920, CPad*, int16, uint8, uint32>(this, time, frequency, arg2);
}

// 0x53F9A0
void CPad::StartShake_Distance(int16 time, uint8 frequency, float x, float y, float z) {
    plugin::CallMethod<0x53F9A0, CPad*, int16, uint8, float, float, float>(this, time, frequency, x, y, z);
}

// 0x53FA70
void CPad::StartShake_Train(float x, float y) {
    plugin::CallMethod<0x53FA70, CPad*, float, float>(this, x, y);
}

// dummy function
// 0x53FB40
void CPad::ProcessPCSpecificStuff() {
    plugin::CallMethod<0x53FB40, CPad*>(this);
}

// 0x53FB50
void CPad::StopShaking(int16 arg0) {
    plugin::CallMethod<0x53FB50, CPad*, int16>(this, arg0);
}

// 0x53FB70
CPad* CPad::GetPad(int32 padNumber) {
    return plugin::CallAndReturn<CPad*, 0x53FB70, int32>(padNumber);
}

int16 CPad::GetCarGunLeftRight()
{
    return plugin::CallMethodAndReturn<int16, 0x53FC50, CPad*>(this);
}

int16 CPad::GetCarGunUpDown()
{
    return plugin::CallMethodAndReturn<int16, 0x53FC10, CPad*>(this);
}

// 0x53FB80
int16 CPad::GetSteeringLeftRight() {
    return plugin::CallMethodAndReturn<int16, 0x53FB80, CPad*>(this);
}

// 0x53FBD0
int16 CPad::GetSteeringUpDown() {
    return plugin::CallMethodAndReturn<int16, 0x53FBD0, CPad*>(this);
}

int16 CPad::GetPedWalkLeftRight(CPed* pPed) {
    return plugin::CallMethodAndReturn<int16, 0x540DC0, CPad*, CPed*>(this, pPed);
}

int16 CPad::GetPedWalkUpDown(CPed* pPed) {
    return plugin::CallMethodAndReturn<int16, 0x540E20, CPad*, CPed*>(this, pPed);
}

// 0x53FC90
int16 CPad::GetPedWalkLeftRight() {
    return plugin::CallMethodAndReturn<int16, 0x53FC90, CPad*>(this);
}

// 0x53FD30
int16 CPad::GetPedWalkUpDown() {
    return plugin::CallMethodAndReturn<int16, 0x53FD30, CPad*>(this);
}

// 0x53FDD0
bool CPad::GetLookLeft() {
    return plugin::CallMethodAndReturn<bool, 0x53FDD0, CPad*>(this);
}

// 0x53FE10
bool CPad::GetLookRight() {
    return plugin::CallMethodAndReturn<bool, 0x53FE10, CPad*>(this);
}

// 0x53FE70
bool CPad::GetLookBehindForCar() {
    return plugin::CallMethodAndReturn<bool, 0x53FE70, CPad*>(this);
}

// 0x53FEC0
bool CPad::GetLookBehindForPed() {
    return plugin::CallMethodAndReturn<bool, 0x53FEC0, CPad*>(this);
}

// 0x53FEE0
bool CPad::GetHorn() {
    return plugin::CallMethodAndReturn<bool, 0x53FEE0, CPad*>(this);
}

// 0x53FF30
bool CPad::HornJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x53FF30, CPad*>(this);
}

// 0x53FF70
bool CPad::GetHydraulicJump() {
    return plugin::CallMethodAndReturn<bool, 0x53FF70, CPad*>(this);
}

// 0x53FF90
int16 CPad::GetCarGunFired() {
    return plugin::CallMethodAndReturn<int16, 0x53FF90, CPad*>(this);
}

// 0x53FFE0
int16 CPad::CarGunJustDown() {
    return plugin::CallMethodAndReturn<int16, 0x53FFE0, CPad*>(this);
}

// 0x540040
int16 CPad::GetHandBrake() {
    return plugin::CallMethodAndReturn<int16, 0x540040, CPad*>(this);
}

// 0x540080
int16 CPad::GetBrake() {
    return plugin::CallMethodAndReturn<int16, 0x540080, CPad*>(this);
}

// 0x5400D0
bool CPad::GetExitVehicle() {
    return plugin::CallMethodAndReturn<bool, 0x5400D0, CPad*>(this);
}

// 0x540120
bool CPad::ExitVehicleJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540120, CPad*>(this);
}

// 0x540340
uint8 CPad::GetMeleeAttack(bool bCheckButtonCircleStateOnly) {
    return plugin::CallMethodAndReturn<uint8, 0x540340, CPad*, bool>(this, bCheckButtonCircleStateOnly);
}

// 0x540390
uint8 CPad::MeleeAttackJustDown(bool bCheckButtonCircleStateOnly) {
    return plugin::CallMethodAndReturn<uint8, 0x540390, CPad*, bool>(this, bCheckButtonCircleStateOnly);
}

// 0x5403F0
int16 CPad::GetAccelerate() {
    return plugin::CallMethodAndReturn<int16, 0x5403F0, CPad*>(this);
}

// 0x540440
bool CPad::GetAccelerateJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540440, CPad*>(this);
}

// 0x5405B0
bool CPad::NextStationJustUp() {
    return plugin::CallMethodAndReturn<bool, 0x5405B0, CPad*>(this);
}

// 0x5405E0
bool CPad::LastStationJustUp() {
    return plugin::CallMethodAndReturn<bool, 0x5405E0, CPad*>(this);
}

// 0x540610
bool CPad::CycleWeaponLeftJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540610, CPad*>(this);
}

// 0x540640
bool CPad::CycleWeaponRightJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540640, CPad*>(this);
}

// 0x540670
bool CPad::GetTarget() {
    return plugin::CallMethodAndReturn<bool, 0x540670, CPad*>(this);
}

// 0x540700
bool CPad::GetDuck() {
    return plugin::CallMethodAndReturn<bool, 0x540700, CPad*>(this);
}

// 0x540720
bool CPad::DuckJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540720, CPad*>(this);
}

// 0x540750
bool CPad::GetJump() {
    return plugin::CallMethodAndReturn<bool, 0x540750, CPad*>(this);
}

// 0x540770
bool CPad::JumpJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540770, CPad*>(this);
}

// 0x5407A0
bool CPad::GetSprint() {
    return plugin::CallMethodAndReturn<bool, 0x5407A0, CPad*>(this);
}

// 0x5407F0
bool CPad::SprintJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x5407F0, CPad*>(this);
}

// 0x540850
bool CPad::ShiftTargetLeftJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540850, CPad*>(this);
}

// 0x540880
bool CPad::ShiftTargetRightJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540880, CPad*>(this);
}

// 0x5408B0
int16 CPad::GetDisplayVitalStats(CPed* ped) {
    return plugin::CallMethodAndReturn<int16, 0x5408B0, CPad*, CPed*>(this, ped);
}

// 0x540A70
bool CPad::CollectPickupJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x540A70, CPad*>(this);
}

// 0x540AE0
bool CPad::GetForceCameraBehindPlayer() {
    return plugin::CallMethodAndReturn<bool, 0x540AE0, CPad*>(this);
}

// 0x540B30
bool CPad::SniperZoomIn() {
    return plugin::CallMethodAndReturn<bool, 0x540B30, CPad*>(this);
}

// 0x540B80
bool CPad::SniperZoomOut() {
    return plugin::CallMethodAndReturn<bool, 0x540B80, CPad*>(this);
}

// 0x541190
bool CPad::GetGroupControlForward() {
    return plugin::CallMethodAndReturn<bool, 0x541190, CPad*>(this);
}

// 0x5411B0
bool CPad::GetGroupControlBack() {
    return plugin::CallMethodAndReturn<bool, 0x5411B0, CPad*>(this);
}

// 0x5411D0
bool CPad::ConversationYesJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x5411D0, CPad*>(this);
}

// 0x541200
bool CPad::ConversationNoJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x541200, CPad*>(this);
}

// 0x541230
bool CPad::GroupControlForwardJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x541230, CPad*>(this);
}

// 0x541260
bool CPad::GroupControlBackJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x541260, CPad*>(this);
}

// 0x541A70
void CPad::Clear(bool enablePlayerControls, bool resetPhase) {
    NewState.Clear();
    OldState.Clear();
    PCTempKeyState.Clear();
    PCTempJoyState.Clear();
    PCTempMouseState.Clear();

    NewKeyState.Clear();
    OldKeyState.Clear();
    TempKeyState.Clear();

    NewMouseControllerState.Clear();
    OldMouseControllerState.Clear();
    PCTempMouseControllerState.Clear();

    if (resetPhase) {
        Phase = 0;
    }
    ShakeFreq = 0;
    ShakeDur = 0;

    for (auto& buf: SteeringLeftRightBuffer) {
        buf = 0;
    }

    DrunkDrivingBufferUsed = 0;
    if (enablePlayerControls) {
        DisablePlayerControls = 0;
        bDisablePlayerEnterCar = 0;
        bDisablePlayerDuck = 0;
        bDisablePlayerFireWeapon = 0;
        bDisablePlayerFireWeaponWithL1 = 0;
        bDisablePlayerCycleWeapon = 0;
        bDisablePlayerJump = 0;
        bDisablePlayerDisplayVitalStats = 0;
    }
    JustOutOfFrontEnd = 0;
    bApplyBrakes = 0;

    for (auto& history: bHornHistory) {
        history = 0;
    }

    iCurrHornHistory = 0;
    AverageWeapon = 0;
    AverageEntries = 0;
    LastTimeTouched = 0;
    NoShakeBeforeThis = 0;
    NoShakeFreq = 0;
}

CPad* GetPad(int32 padNumber)
{
    return &CPad::Pads[padNumber];
}

void CPad::ProcessPad(bool padNum)
{
    ((void(__cdecl*)(bool))0x746A10)(padNum);
}

void CPad::Update(int32 pad)
{
    ((void(__thiscall*)(CPad*, int32))0x541C40)(this, pad);
}

// 0x541DD0
void CPad::UpdatePads() {
    GetPad(0)->UpdateMouse();
    CPad::ProcessPad(false);
    ControlsManager.ClearSimButtonPressCheckers();

    // NOTSA: Don't handle updates if the menu is open, so we don't affect gameplay inputting text
    if (!CDebugMenu::Visible())
    {
        ControlsManager.AffectPadFromKeyBoard();
        ControlsManager.AffectPadFromMouse();
        GetPad(0)->Update(0);
        GetPad(1)->Update(0);
    }

    OldKeyState = NewKeyState;
    NewKeyState = TempKeyState;
    CDebugMenu::ImguiInitialise();
    CDebugMenu::ImguiInputUpdate();
}

void CPad::SetTouched()
{
    plugin::CallMethod<0x53F200, CPad*>(this);
}

uint32 CPad::GetTouchedTimeDelta()
{
    return plugin::CallMethodAndReturn<uint32, 0x53F210, CPad*>(this);
}

bool CPad::WeaponJustDown(CPed* pPed)
{
    return plugin::CallMethodAndReturn<bool, 0x540250, CPad*, CPed*>(this, pPed);
}

bool CPad::GetEnterTargeting()
{
    return plugin::CallMethodAndReturn<bool, 0x5406B0, CPad*>(this);
}

int32 CPad::GetWeapon(CPed* pPed)
{
    return plugin::CallMethodAndReturn<int32, 0x540180, CPad*, CPed*>(this, pPed);
}

int16 CPad::AimWeaponLeftRight(CPed* pPed)
{
    return plugin::CallMethodAndReturn<int16, 0x541040, CPad*, CPed*>(this, pPed);
}

int16 CPad::AimWeaponUpDown(CPed* pPed)
{
    return plugin::CallMethodAndReturn<int16, 0x5410C0, CPad*, CPed*>(this, pPed);
}

bool CPad::IsStandardKeyJustDown(uint8 key)
{
    return plugin::CallMethodAndReturn<bool, 0x4D59B0, CPad*, uint8>(this, key);
}

bool CPad::IsCtrlJustDown()
{
    if (NewKeyState.lctrl && !OldKeyState.lctrl)
        return true;
    if (NewKeyState.rctrl && !OldKeyState.rctrl)
        return true;
    return false;
}

bool CPad::IsStandardKeyPressed(uint8 key)
{
    return NewKeyState.standardKeys[key] && OldKeyState.standardKeys[key];
}

bool CPad::IsCtrlPressed()
{
    if (NewKeyState.lctrl && OldKeyState.lctrl)
        return true;
    if (NewKeyState.rctrl && OldKeyState.rctrl)
        return true;
    return false;
}

// 0x4D5980
bool CPad::isEnterJustPressed() {
    return NewKeyState.enter && !OldKeyState.enter || NewKeyState.extenter && !OldKeyState.extenter;
}

// 0x4D59B0
bool CPad::isStandardKeyJustPressed(uint8 key) {
    return NewKeyState.standardKeys[key] && !OldKeyState.standardKeys[key];;
}

// 0x744D50
bool CPad::isMenuKeyJustPressed() {
    return NewKeyState.lmenu && !OldKeyState.lmenu || NewKeyState.rmenu && !OldKeyState.rmenu;
}

// 0x744D90
bool CPad::isTabJustPressed() {
    return NewKeyState.tab && !OldKeyState.tab;
}
