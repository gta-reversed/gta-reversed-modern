/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "Pad.h"

#include "CDebugMenu.h"

// mouse states
CMouseControllerState& CPad::PCTempMouseControllerState = *(CMouseControllerState*)0xB73404;
CMouseControllerState& CPad::NewMouseControllerState = *(CMouseControllerState*)0xB73418;
CMouseControllerState& CPad::OldMouseControllerState = *(CMouseControllerState*)0xB7342C;

CKeyboardState& CPad::TempKeyState = *(CKeyboardState*)0xB72CB0;
CKeyboardState& CPad::OldKeyState = *(CKeyboardState*)0xB72F20;
CKeyboardState& CPad::NewKeyState = *(CKeyboardState*)0xB73190;

CPad (&CPad::Pads)[MAX_PADS] = *(CPad(*)[MAX_PADS])0xB73458;

bool& CPad::bInvertLook4Pad = *(bool*)0xB73402;
char& CPad::padNumber = *(char*)0xB73400;

static bool& byte_B73403 = *(bool*)0xB73403; // TODO: Find out what modifies this, as it has no value by default..
static bool& byte_8CD782 = *(bool*)0x8CD782; // true by default, left here for documentation purposes, as it's used in multiple CPad functions
static char& byte_B73401 = *(char*)0xB73401; // unused, unknown

void CPad::InjectHooks() {
    HookInstall(0x541DD0, CPad::UpdatePads); // changes logic of the function and shouldn't be toggled on/off

    using namespace ReversibleHooks;
    // Install("CPad", "CPad", 0x541D80, &CPad::Constructor);
    // Install("CPad", "CPad~", 0x53ED60, &CPad::Destructor);
    Install("CPad", "Initialise", 0x541D90, &CPad::Initialise);
    Install("CPad", "ClearKeyBoardHistory", 0x53F1E0, &CPad::ClearKeyBoardHistory);
    Install("CPad", "ClearMouseHistory", 0x541BD0, &CPad::ClearMouseHistory);
    Install("CPad", "Clear", 0x541A70, &CPad::Clear);
    Install("CPad", "Update", 0x541C40, &CPad::Update);
    // Install("CPad", "UpdateMouse", 0x53F3C0, &CPad::UpdateMouse);
    // Install("CPad", "ProcessPad", 0x746A10, &CPad::ProcessPad);
    Install("CPad", "ProcessPCSpecificStuff", 0x53FB40, &CPad::ProcessPCSpecificStuff);
    Install("CPad", "ReconcileTwoControllersInput", 0x53F530, &CPad::ReconcileTwoControllersInput);
    Install("CPad", "SetTouched", 0x53F200, &CPad::SetTouched);
    Install("CPad", "GetTouchedTimeDelta", 0x53F210, &CPad::GetTouchedTimeDelta);
    Install("CPad", "StartShake", 0x53F920, &CPad::StartShake);
    Install("CPad", "StartShake_Distance", 0x53F9A0, &CPad::StartShake_Distance);
    // Install("CPad", "StartShake_Train", 0x53FA70, &CPad::StartShake_Train);
    Install("CPad", "StopShaking", 0x53FB50, &CPad::StopShaking);
    Install("CPad", "GetCarGunLeftRight", 0x53FC50, &CPad::GetCarGunLeftRight);
    Install("CPad", "GetCarGunUpDown", 0x53FC10, &CPad::GetCarGunUpDown);
    Install("CPad", "GetSteeringLeftRight", 0x53FB80, &CPad::GetSteeringLeftRight);
    Install("CPad", "GetCarGunFired", 0x53FF90, &CPad::GetCarGunFired);
    Install("CPad", "CarGunJustDown", 0x53FFE0, &CPad::CarGunJustDown);
    Install("CPad", "GetSteeringUpDown", 0x53FBD0, &CPad::GetSteeringUpDown);
    Install("CPad", "GetPedWalkLeftRight_ped", 0x540DC0, static_cast<int16 (CPad::*)(CPed*) const>(&CPad::GetPedWalkLeftRight));
    Install("CPad", "GetPedWalkLeftRight", 0x53FC90, static_cast<int16 (CPad::*)() const>(&CPad::GetPedWalkLeftRight));
    Install("CPad", "GetPedWalkUpDown_ped", 0x540E20, static_cast<int16 (CPad::*)(CPed*) const>(&CPad::GetPedWalkUpDown));
    Install("CPad", "GetPedWalkUpDown", 0x53FD30, static_cast<int16 (CPad::*)() const>(&CPad::GetPedWalkUpDown));
    Install("CPad", "GetLookLeft", 0x53FDD0, &CPad::GetLookLeft);
    Install("CPad", "GetLookRight", 0x53FE10, &CPad::GetLookRight);
    Install("CPad", "GetLookBehindForCar", 0x53FE70, &CPad::GetLookBehindForCar);
    Install("CPad", "GetLookBehindForPed", 0x53FEC0, &CPad::GetLookBehindForPed);
    Install("CPad", "GetHorn", 0x53FEE0, &CPad::GetHorn);
    Install("CPad", "HornJustDown", 0x53FF30, &CPad::HornJustDown);
    Install("CPad", "GetHandBrake", 0x540040, &CPad::GetHandBrake);
    Install("CPad", "GetBrake", 0x540080, &CPad::GetBrake);
    Install("CPad", "GetExitVehicle", 0x5400D0, &CPad::GetExitVehicle);
    Install("CPad", "ExitVehicleJustDown", 0x540120, &CPad::ExitVehicleJustDown);
    Install("CPad", "GetMeleeAttack", 0x540340, &CPad::GetMeleeAttack);
    Install("CPad", "MeleeAttackJustDown", 0x540390, &CPad::MeleeAttackJustDown);
    Install("CPad", "GetAccelerate", 0x5403F0, &CPad::GetAccelerate);
    Install("CPad", "GetAccelerateJustDown", 0x540440, &CPad::GetAccelerateJustDown);
    Install("CPad", "CycleWeaponLeftJustDown", 0x540610, &CPad::CycleWeaponLeftJustDown);
    Install("CPad", "CycleWeaponRightJustDown", 0x540640, &CPad::CycleWeaponRightJustDown);
    Install("CPad", "GetTarget", 0x540670, &CPad::GetTarget);
    Install("CPad", "GetSprint", 0x5407A0, &CPad::GetSprint);
    Install("CPad", "SprintJustDown", 0x5407F0, &CPad::SprintJustDown);
    Install("CPad", "GetDisplayVitalStats", 0x5408B0, &CPad::GetDisplayVitalStats);
    Install("CPad", "CollectPickupJustDown", 0x540A70, &CPad::CollectPickupJustDown);
    Install("CPad", "GetForceCameraBehindPlayer", 0x540AE0, &CPad::GetForceCameraBehindPlayer);
    Install("CPad", "SniperZoomIn", 0x540B30, &CPad::SniperZoomIn);
    Install("CPad", "SniperZoomOut", 0x540B80, &CPad::SniperZoomOut);
    Install("CPad", "WeaponJustDown", 0x540250, &CPad::WeaponJustDown);
    Install("CPad", "GetEnterTargeting", 0x5406B0, &CPad::GetEnterTargeting);
    Install("CPad", "GetWeapon", 0x540180, &CPad::GetWeapon);
    Install("CPad", "AimWeaponLeftRight", 0x541040, &CPad::AimWeaponLeftRight);
    Install("CPad", "AimWeaponUpDown", 0x5410C0, &CPad::AimWeaponUpDown);

    Install("CPad", "NextStationJustUp", 0x5405B0, &CPad::NextStationJustUp);
    Install("CPad", "LastStationJustUp", 0x5405E0, &CPad::LastStationJustUp);
    Install("CPad", "GetHydraulicJump", 0x53FF70, &CPad::GetHydraulicJump);
    Install("CPad", "GetDuck", 0x540700, &CPad::GetDuck);
    Install("CPad", "DuckJustDown", 0x540720, &CPad::DuckJustDown);
    Install("CPad", "GetJump", 0x540750, &CPad::GetJump);
    Install("CPad", "JumpJustDown", 0x540770, &CPad::JumpJustDown);
    Install("CPad", "ShiftTargetLeftJustDown", 0x540850, &CPad::ShiftTargetLeftJustDown);
    Install("CPad", "ShiftTargetRightJustDown", 0x540880, &CPad::ShiftTargetRightJustDown);
    Install("CPad", "GetGroupControlForward", 0x541190, &CPad::GetGroupControlForward);
    Install("CPad", "GetGroupControlBack", 0x5411B0, &CPad::GetGroupControlBack);
    Install("CPad", "ConversationYesJustDown", 0x5411D0, &CPad::ConversationYesJustDown);
    Install("CPad", "ConversationNoJustDown", 0x541200, &CPad::ConversationNoJustDown);
    Install("CPad", "GroupControlForwardJustDown", 0x541230, &CPad::GroupControlForwardJustDown);
    Install("CPad", "GroupControlBackJustDown", 0x541260, &CPad::GroupControlBackJustDown);
}

// 0x541D80
CPad::CPad() {
    Clear(true, true);
}

// 0x541D90
void CPad::Initialise() {
    for (auto& pad : Pads) {
        pad.Clear(true, true);
        pad.Mode = 0;
    }
    padNumber = 0;
    byte_B73401 = 0;
}

// 0x53F1E0
void CPad::ClearKeyBoardHistory() {
    NewKeyState.Clear();
    OldKeyState.Clear();
    TempKeyState.Clear();
}

// 0x541BD0
void CPad::ClearMouseHistory() {
    PCTempMouseControllerState.Clear();
    NewMouseControllerState.Clear();
    OldMouseControllerState.Clear();
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

    for (auto& buf : SteeringLeftRightBuffer) {
        buf = 0;
    }

    DrunkDrivingBufferUsed = 0;
    if (enablePlayerControls) {
        DisablePlayerControls = 0;
        bDisablePlayerEnterCar = false;
        bDisablePlayerDuck = false;
        bDisablePlayerFireWeapon = false;
        bDisablePlayerFireWeaponWithL1 = false;
        bDisablePlayerCycleWeapon = false;
        bDisablePlayerJump = false;
        bDisablePlayerDisplayVitalStats = false;
    }
    JustOutOfFrontEnd = 0;
    bApplyBrakes = false;

    for (auto& history : bHornHistory) {
        history = 0;
    }

    iCurrHornHistory = 0;
    AverageWeapon = 0;
    AverageEntries = 0;
    LastTimeTouched = 0;
    NoShakeBeforeThis = 0;
    NoShakeFreq = 0;
}

// 0x541C40
void CPad::Update(int32 pad) {
    OldState = NewState;

    // Writes directly into NewState
    ReconcileTwoControllersInput(NewState, PCTempKeyState, PCTempJoyState);
    ReconcileTwoControllersInput(NewState, PCTempMouseState, NewState);

    PCTempJoyState.Clear();
    PCTempKeyState.Clear();
    PCTempMouseState.Clear();

    if (NewState.CheckForInput()) {
        SetTouched();
    }

    iCurrHornHistory = (iCurrHornHistory + 1) % 5;
    bHornHistory[iCurrHornHistory] = GetHorn();

    // Shift right by 1
    std::rotate(
        std::begin(SteeringLeftRightBuffer),
        std::begin(SteeringLeftRightBuffer) + 1,
        std::end(SteeringLeftRightBuffer)
    );

    if (JustOutOfFrontEnd)
        JustOutOfFrontEnd--;
}

// 0x541DD0
void CPad::UpdatePads() {
    GetPad(0)->UpdateMouse();
    ProcessPad(false);

    ControlsManager.ClearSimButtonPressCheckers();
    // NOTSA: Don't handle updates if the menu is open, so we don't affect gameplay inputting text
    if (!CDebugMenu::Visible()) {
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

// 0x53F3C0
void CPad::UpdateMouse() {
    plugin::CallMethod<0x53F3C0, CPad*>(this);
}

// 0x746A10
void CPad::ProcessPad(bool padNum) {
    ((void(__cdecl*)(bool))0x746A10)(padNum);
}

// 0x53FB40
void CPad::ProcessPCSpecificStuff() {
    // NOP
}

// 0x53F530
CControllerState& CPad::ReconcileTwoControllersInput(CControllerState& out, const CControllerState& controllerA, const CControllerState& controllerB) {
#define RECONCILE_BUTTON(button)                                                                                                                                                   \
    {                                                                                                                                                                              \
        if (controllerA.button || controllerB.button)                                                                                                                              \
            reconciledState.button = 255;                                                                                                                                          \
    }

#define RECONCILE_AXIS_POSITIVE(axis)                                                                                                                                              \
    {                                                                                                                                                                              \
        if (controllerA.axis >= 0 && controllerB.axis >= 0)                                                                                                                        \
            reconciledState.axis = std::max(controllerA.axis, controllerB.axis);                                                                                                   \
    }

#define RECONCILE_AXIS_NEGATIVE(axis)                                                                                                                                              \
    {                                                                                                                                                                              \
        if (controllerA.axis <= 0 && controllerB.axis <= 0)                                                                                                                        \
            reconciledState.axis = std::min(controllerA.axis, controllerB.axis);                                                                                                   \
    }

#define RECONCILE_AXIS(axis)                                                                                                                                                       \
    {                                                                                                                                                                              \
        RECONCILE_AXIS_POSITIVE(axis);                                                                                                                                             \
        RECONCILE_AXIS_NEGATIVE(axis);                                                                                                                                             \
    }

#define FIX_AXIS_DIR(axis)                                                                                                                                                         \
    {                                                                                                                                                                              \
        if (controllerA.axis > 0 && controllerB.axis < 0 || controllerA.axis < 0 && controllerB.axis > 0)                                                                          \
            reconciledState.axis = 0;                                                                                                                                              \
    }

#define FIX_RECON_DIR(pos, neg, axis)                                                                                                                                              \
    {                                                                                                                                                                              \
        if ((reconciledState.pos || reconciledState.axis < 0) && (reconciledState.neg || reconciledState.axis > 0)) {                                                              \
            reconciledState.pos = 0;                                                                                                                                               \
            reconciledState.neg = 0;                                                                                                                                               \
            reconciledState.axis = 0;                                                                                                                                              \
        }                                                                                                                                                                          \
    }

    static CControllerState reconciledState;
    reconciledState.Clear();

    RECONCILE_BUTTON(LeftShoulder1)
    RECONCILE_BUTTON(LeftShoulder2)
    RECONCILE_BUTTON(RightShoulder1)
    RECONCILE_BUTTON(RightShoulder2)
    RECONCILE_BUTTON(Start)
    RECONCILE_BUTTON(Select)
    RECONCILE_BUTTON(ButtonSquare)
    RECONCILE_BUTTON(ButtonTriangle)
    RECONCILE_BUTTON(ButtonCross)
    RECONCILE_BUTTON(ButtonCircle)
    RECONCILE_BUTTON(ShockButtonL)
    RECONCILE_BUTTON(ShockButtonR)
    RECONCILE_BUTTON(m_bChatIndicated)
    RECONCILE_BUTTON(m_bPedWalk)
    RECONCILE_BUTTON(m_bRadioTrackSkip)
    RECONCILE_BUTTON(m_bVehicleMouseLook)

    RECONCILE_AXIS(LeftStickX);
    RECONCILE_AXIS(LeftStickY);
    FIX_AXIS_DIR(LeftStickX);
    FIX_AXIS_DIR(LeftStickY);
    RECONCILE_AXIS(RightStickX);
    RECONCILE_AXIS(RightStickY);
    FIX_AXIS_DIR(RightStickX);
    FIX_AXIS_DIR(RightStickY);

    RECONCILE_BUTTON(DPadUp)
    RECONCILE_BUTTON(DPadDown)
    RECONCILE_BUTTON(DPadLeft)
    RECONCILE_BUTTON(DPadRight)

    FIX_RECON_DIR(DPadUp, DPadDown, LeftStickY);
    FIX_RECON_DIR(DPadLeft, DPadRight, LeftStickX);

    out = reconciledState;
    return out;

#undef RECONCILE_BUTTON
#undef RECONCILE_AXIS_POSITIVE
#undef RECONCILE_AXIS_NEGATIVE
#undef RECONCILE_AXIS
#undef FIX_AXIS_DIR
#undef FIX_RECON_DIR
}

// 0x53F200
void CPad::SetTouched() {
    LastTimeTouched = CTimer::GetTimeInMS();
}

// 0x53F210
uint32 CPad::GetTouchedTimeDelta() const {
    return CTimer::GetTimeInMS() - LastTimeTouched;
}

// 0x53F920
void CPad::StartShake(int16 time, uint8 freq, uint32 shakeDelayMs) {
    if (!FrontEndMenuManager.m_PrefsUseVibration || CCutsceneMgr::ms_running)
        return;

    if (freq) {
        if (CTimer::m_snTimeInMilliseconds >= NoShakeBeforeThis || freq > NoShakeFreq) {
            if (ShakeDur) {
                ShakeDur = time;
                ShakeFreq = freq;
            }
            NoShakeBeforeThis = shakeDelayMs + CTimer::m_snTimeInMilliseconds;
            NoShakeFreq = freq;
        }
    } else {
        ShakeDur = 0;
        ShakeFreq = 0;
    }
}

// originally 3x float instead of CVector
// 0x53F9A0
void CPad::StartShake_Distance(int16 time, uint8 freq, CVector pos) {
    if (!FrontEndMenuManager.m_PrefsUseVibration || CCutsceneMgr::ms_running)
        return;

    if ((TheCamera.GetPosition() - pos).Magnitude() < 70.0f) {
        if (freq) {
            if (time > ShakeDur) {
                ShakeDur = time;
                ShakeFreq = freq;
            }
        } else {
            ShakeDur = 0;
            ShakeFreq = 0;
        }
    }
}

/* todo:
// 0x53FA70
void CPad::StartShake_Train(const CVector2D& point) {
    if (!FrontEndMenuManager.m_PrefsUseVibration || CCutsceneMgr::ms_running)
        return;

    if (FindPlayerVehicle(-1) && FindPlayerVehicle(-1)->m_vehicleType == eVehicleType::VEHICLE_TRAIN)
        return;

    auto fDistSq = DistanceBetweenPointsSquared(TheCamera.GetPosition(), point);
    if (ShakeDur < 100 && fDistSq < 4900.0f) {
        ShakeDur = 100;
        ShakeFreq = static_cast<char>(70.0f - sqrt(fDistSq) + 30.0f);
    }
}
*/

// 0x53FB50
void CPad::StopShaking(int16 arg0) {
    // NOP
}

// 0x53FC50
int16 CPad::GetCarGunLeftRight() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
        return GetRightStickX();
    case 3:
        return (NewState.DPadRight - NewState.DPadLeft) / 2;
    }
    return 0;
}

// 0x53FC10
int16 CPad::GetCarGunUpDown() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
        return GetRightStickY();
    case 3:
        return (NewState.DPadUp - NewState.DPadDown) / 2;
    }
    return 0;
}

// 0x53FB80
int16 CPad::GetSteeringLeftRight() {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
    case 3: {
        SteeringLeftRightBuffer[0] = GetLeftStickX();
        return SteeringLeftRightBuffer[DrunkDrivingBufferUsed];
    }
    }
    return 0;
}

// 0x53FF90
int16 CPad::GetCarGunFired() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 2: {
        if (BUTTON_IS_DOWN(ButtonCircle))
            return 1;

        if (!bDisablePlayerFireWeaponWithL1 && BUTTON_IS_DOWN(LeftShoulder1))
            return 2;
    }
    case 3:
        return NewState.RightShoulder1;
    }
    return false;
}

// 0x53FFE0
int16 CPad::CarGunJustDown() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 2: {
        if (IsCirclePressed())
            return 1;

        if (!bDisablePlayerFireWeaponWithL1 && IsLeftShoulder1Pressed())
            return 2;
        break;
    }
    case 3:
        return IsRightShoulder1Pressed();
    }
    return false;
}

// 0x53FBD0
int16 CPad::GetSteeringUpDown() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
    case 3:
        return GetLeftStickY();
    }
    return 0;
}

// 0x540DC0
int16 CPad::GetPedWalkLeftRight(CPed* ped) const {
    if (DisablePlayerControls)
        return 0;

    if (byte_B73403 || CCamera::m_bUseMouse3rdPerson) {
        if (ped && ped->m_pAttachedTo)
            return 0;

        if (byte_8CD782)
            return GetLeftStickX();

        return GetRightStickX();
    }

    return 0;
}

// 0x53FC90
int16 CPad::GetPedWalkLeftRight() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
    case 3:
        return GetLeftStickX();
    }
    return 0;
}

// 0x540E20
int16 CPad::GetPedWalkUpDown(CPed* ped) const {
    if (DisablePlayerControls)
        return 0;

    if (byte_B73403 || CCamera::m_bUseMouse3rdPerson) {
        if (ped && ped->m_pAttachedTo)
            return 0;

        if (byte_8CD782)
            return GetLeftStickY();

        return GetRightStickY();
    }

    return 0;
}

// 0x53FD30
int16 CPad::GetPedWalkUpDown() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
    case 3:
        return GetLeftStickY();
    }
    return 0;
}

// 0x53FDD0
bool CPad::GetLookLeft() const {
    if (DisablePlayerControls)
        return false;

    if (IsLeftShoulder2Pressed())
        return false;

    if (IsRightShoulder2JustUp())
        return false;

    return NewState.LeftShoulder2 && !NewState.RightShoulder2;
}

// 0x53FE10
bool CPad::GetLookRight() const {
    if (DisablePlayerControls)
        return false;

    if (IsRightShoulder2Pressed())
        return false;

    if (IsRightShoulder2JustUp())
        return false;

    return NewState.RightShoulder2 && !NewState.LeftShoulder2;
}

bool CPad::GetLookBehindForCar() const noexcept {
    if (DisablePlayerControls)
        return false;

    return (NewState.LeftShoulder2 || OldState.LeftShoulder2) && (NewState.RightShoulder2 || OldState.RightShoulder2);
}

// 0x53FEE0
bool CPad::GetHorn() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 3:
        return NewState.ShockButtonL;
    case 1:
        return NewState.LeftShoulder1;
    case 2:
        return NewState.RightShoulder1;
    }
    return false;
}

// 0x53FF30
bool CPad::HornJustDown() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 3:
        return IsLeftShockPressed();
    case 1:
        return IsLeftShoulder1Pressed();
    case 2:
        return IsRightShoulder1Pressed();
    }
    return false;
}

// 0x540040
int16 CPad::GetHandBrake() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
        return NewState.RightShoulder1;
    case 2:
        return NewState.ButtonTriangle;
    case 3:
        return NewState.LeftShoulder1;
    }
    return 0;
}

// 0x540080
int16 CPad::GetBrake() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
        return NewState.ButtonSquare;
    case 3:
        int16 axis = 2 * GetRightStickY();
        return axis < 0 ? 0 : axis;
    }
    return 0;
}

// 0x5400D0
bool CPad::GetExitVehicle() const {
    if (DisablePlayerControls || bDisablePlayerEnterCar)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 3:
        return NewState.ButtonTriangle;
    case 2:
        return NewState.LeftShoulder1;
    }
    return false;
}

// 0x540120
bool CPad::ExitVehicleJustDown() const {
    if (DisablePlayerControls || bDisablePlayerEnterCar)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 3:
        return IsTrianglePressed();
    case 2:
        return IsLeftShoulder1Pressed();
    }
    return false;
}

// 0x540340
uint8 CPad::GetMeleeAttack(bool bCheckButtonCircleStateOnly) const {
    if (DisablePlayerControls)
        return 0;

    if (NewState.ButtonCircle)
        return 1;

    if (!bCheckButtonCircleStateOnly) {
        if (NewState.ButtonCross)
            return 2;

        if (NewState.ButtonSquare)
            return 3;

        if (NewState.ButtonTriangle)
            return 4;
    }

    return 0;
}

// 0x540390
uint8 CPad::MeleeAttackJustDown(bool bCheckButtonCircleStateOnly) const {
    if (DisablePlayerControls)
        return 0;

    if (IsCirclePressed())
        return 1;

    if (!bCheckButtonCircleStateOnly)
        return 0;

    if (IsCrossPressed())
        return 2;

    if (BUTTON_IS_DOWN(ButtonSquare))
        return 3;

    if (IsTrianglePressed())
        return 4;

    return 0;
}

// 0x5403F0
int16 CPad::GetAccelerate() const {
    if (DisablePlayerControls)
        return 0;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
        return NewState.ButtonCross;
    case 3: {
        int16 axis = -2 * GetRightStickY();
        return axis < 0 ? 0 : axis;
    }
    }
    return 0;
}

// 0x540440
bool CPad::GetAccelerateJustDown() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
        return IsCrossPressed();
    case 3:
        return IsRightStickYPressed();
    }
    return false;
}

// 0x540610
bool CPad::CycleWeaponLeftJustDown() const {
    if (DisablePlayerControls || bDisablePlayerCycleWeapon)
        return false;

    return IsLeftShoulder2Pressed();
}

// 0x540640
bool CPad::CycleWeaponRightJustDown() const {
    if (DisablePlayerControls || bDisablePlayerCycleWeapon)
        return false;

    return IsRightShoulder2Pressed();
}

// 0x540670
bool CPad::GetTarget() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
        return NewState.RightShoulder1;
    case 3:
        return NewState.LeftShoulder1;
    }
    return false;
}

// 0x5407A0
bool CPad::GetSprint() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 3:
        return NewState.ButtonCross;
    case 2:
        return NewState.ButtonCircle;
    }
    return false;
}

// 0x5407F0
bool CPad::SprintJustDown() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 3:
        return IsCrossPressed();
    case 2:
        return IsCirclePressed();
    }
    return false;
}

// 0x5408B0
int16 CPad::GetDisplayVitalStats(CPed* ped) const {
    if (DisablePlayerControls || bDisablePlayerDisplayVitalStats)
        return false;

    if (ped && ped->GetIntelligence()->IsUsingGun())
        return false;

    return Mode <= 3 && NewState.LeftShoulder1;
}

// 0x540A70
bool CPad::CollectPickupJustDown() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
        return IsLeftShoulder1Pressed();
    case 2:
        return IsTrianglePressed();
    case 3:
        return IsCirclePressed();
    }
    return false;
}

// 0x540AE0
bool CPad::GetForceCameraBehindPlayer() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
        return BUTTON_IS_DOWN(LeftShoulder1);
    case 2:
        return BUTTON_IS_DOWN(ButtonTriangle);
    case 3:
        return BUTTON_IS_DOWN(ButtonCircle);
    }
    return false;
}

// 0x540B30
bool CPad::SniperZoomIn() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 3:
        return BUTTON_IS_DOWN(LeftShoulder2) || BUTTON_IS_DOWN(ButtonSquare);
    case 2:
        return BUTTON_IS_DOWN(ButtonTriangle);
    }
    return false;
}

// 0x540B80
bool CPad::SniperZoomOut() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 3:
        return BUTTON_IS_DOWN(RightShoulder2) || BUTTON_IS_DOWN(ButtonCross);
    case 2:
        return BUTTON_IS_DOWN(ButtonSquare);
    }
    return false;
}

// 0x540250
bool CPad::WeaponJustDown(CPed* ped) const {
    if (DisablePlayerControls || bDisablePlayerDisplayVitalStats)
        return false;

    switch (Mode) {
    case 0:
    case 1: {
        if (IsCirclePressed())
            return true;

        if (bDisablePlayerFireWeaponWithL1)
            return false;

        if (!IsLeftShoulder1Pressed())
            return false;

        if (ped && (ped->m_pAttachedTo || ped->GetIntelligence()->IsUsingGun()))
            return true;

        break;
    }
    case 2:
        return IsCrossPressed();
    case 3:
        return IsRightShoulder1Pressed();
    default:
        return false;
    }
}

// 0x5406B0
bool CPad::GetEnterTargeting() const {
    if (DisablePlayerControls)
        return false;

    switch (Mode) {
    case 0:
    case 1:
    case 2:
        return IsRightShoulder1Pressed();
    case 3:
        return IsLeftShoulder1Pressed();
    }
    return false;
}

// 0x540180
int32 CPad::GetWeapon(CPed* ped) const {
    if (DisablePlayerControls || bDisablePlayerFireWeapon)
        return 0;

    switch (Mode) {
    case 0:
    case 1: {
        if (!bDisablePlayerFireWeaponWithL1) {
            if (ped && (ped->m_pAttachedTo || ped->GetIntelligence()->IsUsingGun())) {
                return NewState.ButtonCircle + NewState.LeftShoulder1;
            }
        }
        return NewState.ButtonCircle;
    }
    case 2:
        return NewState.ButtonCross;
    case 3:
        return NewState.RightShoulder1;
    }
    return 0;
}

// 0x541040
int16 CPad::AimWeaponLeftRight(CPed* ped) const {
    if (DisablePlayerControls)
        return 0;

    if (!CCamera::m_bUseMouse3rdPerson && ped) {
        if (ped->m_pAttachedTo || ped->IsInVehicleAsPassenger()) {
            if (fabs(GetRightStickX()) < fabs(GetLeftStickX())) {
                return GetLeftStickX();
            }
        }
    }
    return GetRightStickX();
}

// 0x5410C0
int16 CPad::AimWeaponUpDown(CPed* ped) const {
    if (DisablePlayerControls)
        return 0;

    if (!CCamera::m_bUseMouse3rdPerson && ped) {
        if (ped->m_pAttachedTo || ped->IsInVehicleAsPassenger()) {
            if (fabs(GetRightStickY()) < fabs(GetLeftStickY())) {
                return bInvertLook4Pad ? -GetLeftStickY() : GetLeftStickY();
            }
        }
    }
    return bInvertLook4Pad ? -GetRightStickY() : GetRightStickY();
}

int32 CPad::sub_541290() {
    if (DisablePlayerControls || bDisablePlayerFireWeapon) {
        AverageWeapon = 0;
        AverageEntries = 1;
        return 0;
    }

    switch (Mode) {
    case 0:
    case 1:
        AverageWeapon = NewState.ButtonCircle;
        AverageEntries = 1;
        return NewState.ButtonCircle;
    case 2:
        AverageWeapon = NewState.ButtonCross;
        AverageEntries = 1;
        return NewState.ButtonCross;
    case 3:
        AverageWeapon = NewState.RightShoulder1;
        AverageEntries = 1;
        return NewState.RightShoulder1;
    default: {
        AverageWeapon = 0;
        AverageEntries = 1;
        return 0;
    }
    }
}

// 0x540A40
bool CPad::sub_540A40() {
    static int16 word_B73704 = *(int16*)0xB73704;
    auto leftStickX = GetPad(0)->GetLeftStickX();

    if (leftStickX || word_B73704 <= leftStickX) {
        word_B73704 = leftStickX;
        return false;
    } else {
        word_B73704 = leftStickX;
        return true;
    }
}

// 0x540A10
bool CPad::sub_540A10() {
    static int16 word_B73700 = *(int16*)0xB73700;
    auto leftStickX = GetPad(0)->GetLeftStickX();

    if (leftStickX || word_B73700 >= leftStickX) {
        word_B73700 = leftStickX;
        return false;
    } else {
        word_B73700 = leftStickX;
        return true;
    }
}

// 0x5409E0
bool CPad::sub_5409E0() {
    static int16 word_B736FC = *(int16*)0xB736FC;
    auto leftStickX = GetPad(0)->GetLeftStickX();

    if (leftStickX <= 15 || word_B736FC > 5) {
        word_B736FC = leftStickX;
        return false;
    } else {
        word_B736FC = leftStickX;
        return true;
    }
}

// 0x5409B0
bool CPad::sub_5409B0() {
    static int16 word_B736F8 = *(int16*)0xB736F8;
    auto leftStickX = GetPad(0)->GetLeftStickX();

    if (leftStickX >= -15 || word_B736F8 < -5) {
        word_B736F8 = leftStickX;
        return false;
    } else {
        word_B736F8 = leftStickX;
        return true;
    }
}

// 0x540980
bool CPad::sub_540980() {
    static int16 word_B736F4 = *(int16*)0xB736F4;
    auto leftStickY = GetPad(0)->GetLeftStickY();

    if (leftStickY <= 15 || word_B736F4 > 5) {
        word_B736F4 = leftStickY;
        return false;
    } else {
        word_B736F4 = leftStickY;
        return true;
    }
}

// 0x540950
bool CPad::sub_540950() {
    static int16 word_B736F0 = *(int16*)0xB736F0;
    auto leftStickY = GetPad(0)->GetLeftStickY();

    if (leftStickY >= -15 || word_B736F0 < -5) {
        word_B736F0 = leftStickY;
        return false;
    } else {
        word_B736F0 = leftStickY;
        return true;
    }
}

// 0x540530
bool CPad::sub_540530() const noexcept {
    switch (Mode) {
    case 0:
    case 2:
    case 3: {
        if (!NewState.Select)
            return sub_5404F0();

        if (OldState.Select == 0)
            return true;

        break;
    }
    case 1: {
        if (NewState.DPadUp && OldState.DPadUp == 0)
            return true;

        return sub_5404F0();
    }
    default:
        return false;
    }
}
