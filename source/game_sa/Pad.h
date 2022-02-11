/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "rw/skeleton.h"

#include "KeyboardState.h"
#include "MouseControllerState.h"
#include "ControllerState.h"

// Taken from GTA3 Script Compiler (miss2.exe)
enum {
    PAD1 = 0,
    PAD2 = 1,

    MAX_PADS
};

#define KEY_IS_PRESSED(btn)    (NewKeyState.btn && !OldKeyState.btn)

#define BUTTON_IS_PRESSED(btn) (NewState.btn && !OldState.btn)
#define BUTTON_IS_DOWN(btn)    (NewState.btn)
#define BUTTON_JUST_UP(btn)    (!NewState.btn && OldState.btn)

class CPed;

class CPad {
public:
    CControllerState NewState;
    CControllerState OldState;
    int16            SteeringLeftRightBuffer[10];
    int32            DrunkDrivingBufferUsed;
    CControllerState PCTempKeyState;
    CControllerState PCTempJoyState;
    CControllerState PCTempMouseState;
    char             Phase;
    char             _pad109;
    int16            Mode;
    int16            ShakeDur;

    union {
        struct {
            uint16 unk1 : 1; // eCamMode::MODE_1STPERSON leftover?
            uint16 unk2 : 1; // unused
            uint16 bPlayerAwaitsInGarage : 1;
            uint16 bPlayerOnInteriorTransition : 1;
            uint16 unk3 : 1; // unused
            uint16 bPlayerSafe : 1;
            uint16 bPlayerTalksOnPhone : 1; // bPlayerSafeForPhoneCall?
            uint16 bPlayerSafeForCutscene : 1;
            uint16 bPlayerSkipsToDestination : 1; // bPlayerSafeForDestination?
        };
        uint16 DisablePlayerControls;
    };

    char     ShakeFreq;
    char     bHornHistory[5];
    char     iCurrHornHistory;
    char     JustOutOfFrontEnd;
    bool     bApplyBrakes;
    bool     bDisablePlayerEnterCar;
    bool     bDisablePlayerDuck;
    bool     bDisablePlayerFireWeapon;
    bool     bDisablePlayerFireWeaponWithL1;
    bool     bDisablePlayerCycleWeapon;
    bool     bDisablePlayerJump;
    bool     bDisablePlayerDisplayVitalStats;
    uint32   LastTimeTouched;
    int32    AverageWeapon;
    int32    AverageEntries;
    float    NoShakeBeforeThis;
    char     NoShakeFreq;
    char    _pad131[3];

public:
    // Static variables

    static CMouseControllerState& PCTempMouseControllerState;
    static CMouseControllerState& NewMouseControllerState;
    static CMouseControllerState& OldMouseControllerState;

    static CKeyboardState& TempKeyState;
    static CKeyboardState& OldKeyState;
    static CKeyboardState& NewKeyState;

    static CPad (&Pads)[MAX_PADS];

    static bool& bInvertLook4Pad;
    static char& padNumber;

public:
    static void InjectHooks();

    // Functions list : Not finished
    CPad();
    ~CPad() = default; // 0x53ED60

    static void Initialise();
    static void ClearKeyBoardHistory();
    static void ClearMouseHistory();
    void Clear(bool enablePlayerControls, bool resetPhase);

    void Update(int32 pad);
    static void UpdatePads();
    void UpdateMouse();
    static void ProcessPad(bool numPad);
    void ProcessPCSpecificStuff();
    CControllerState& ReconcileTwoControllersInput(CControllerState& out, const CControllerState& controllerA, const CControllerState& controllerB);

    void SetTouched();
    uint32 GetTouchedTimeDelta() const;

    void SetDrunkInputDelay(int32 delay) { DrunkDrivingBufferUsed = delay; } // 0x53F910

    void StartShake(int16 time, uint8 frequency, uint32 arg2);
    void StartShake_Distance(int16 time, uint8 frequency, CVector pos);
    void StartShake_Train(const CVector2D& point);
    void StopShaking(int16 arg0);

    int16 GetCarGunLeftRight() const;
    int16 GetCarGunUpDown() const;
    int16 GetCarGunFired() const;
    int16 CarGunJustDown() const;

    int16 GetSteeringLeftRight();
    int16 GetSteeringUpDown() const;
    void GetSteeringMode(); // Android

    int16 GetPedWalkLeftRight(CPed* ped) const;
    int16 GetPedWalkLeftRight() const;
    int16 GetPedWalkUpDown(CPed* ped) const;
    int16 GetPedWalkUpDown() const;

    bool GetLookLeft() const;
    bool GetLookRight() const;

    bool GetHorn() const;
    bool HornJustDown() const;

    int16 GetBrake() const;
    int16 GetHandBrake() const;

    bool GetExitVehicle() const;
    bool ExitVehicleJustDown() const;

    uint8 GetMeleeAttack(bool bCheckButtonCircleStateOnly) const;
    uint8 MeleeAttackJustDown(bool bCheckButtonCircleStateOnly) const;
    int16 GetAccelerate() const;
    bool GetAccelerateJustDown() const;
    bool CycleWeaponLeftJustDown() const;
    bool CycleWeaponRightJustDown() const;
    bool GetTarget() const;
    bool GetSprint() const;
    bool SprintJustDown() const;
    int16 GetDisplayVitalStats(CPed* ped) const;
    bool CollectPickupJustDown() const;
    bool GetForceCameraBehindPlayer() const;
    bool SniperZoomIn() const;
    bool SniperZoomOut() const;

    bool WeaponJustDown(CPed* ped) const;
    bool GetEnterTargeting() const;
    int32 GetWeapon(CPed* ped) const;
    int16 AimWeaponLeftRight(CPed* ped) const;
    int16 AimWeaponUpDown(CPed* ped) const;

    static CPad* GetPad(int32 nPadNumber)                     { return &Pads[nPadNumber]; }                                                                    // 0x53FB70

    bool NextStationJustUp() const noexcept                   { return !DisablePlayerControls && IsDPadUpJustUp(); }                                           // 0x5405B0
    bool LastStationJustUp() const noexcept                   { return !DisablePlayerControls && IsDPadDownJustUp(); }                                         // 0x5405E0
    bool GetLookBehindForCar() const noexcept;                                                                                                                 // 0x53FE70
    bool GetLookBehindForPed() const noexcept                 { return !DisablePlayerControls && BUTTON_IS_DOWN(ShockButtonR); }                               // 0x53FEC0
    bool GetHydraulicJump() const noexcept                    { return !DisablePlayerControls && BUTTON_IS_DOWN(ShockButtonR); }                               // 0x53FF70
    bool GetDuck() const noexcept                             { return !DisablePlayerControls && !bDisablePlayerDuck && BUTTON_IS_DOWN(ShockButtonL); }        // 0x540700
    bool DuckJustDown() const noexcept                        { return !DisablePlayerControls && !bDisablePlayerDuck && IsLeftShockPressed(); }                // 0x540720
    bool GetJump() const noexcept                             { return !DisablePlayerControls && !bDisablePlayerDuck && BUTTON_IS_DOWN(ButtonSquare); }        // 0x540750
    bool JumpJustDown() const noexcept                        { return !DisablePlayerControls && !bDisablePlayerDuck && IsSquarePressed(); }                   // 0x540770
    bool ShiftTargetLeftJustDown() const noexcept             { return !DisablePlayerControls && IsLeftShoulder2Pressed(); }                                   // 0x540850
    bool ShiftTargetRightJustDown() const noexcept            { return !DisablePlayerControls && IsRightShoulder2Pressed(); }                                  // 0x540880
    bool GetGroupControlForward() const noexcept              { return !DisablePlayerControls && BUTTON_IS_DOWN(DPadUp); }                                     // 0x541190
    bool GetGroupControlBack() const noexcept                 { return !DisablePlayerControls && BUTTON_IS_DOWN(DPadDown); }                                   // 0x5411B0
    bool ConversationYesJustDown() const noexcept             { return !DisablePlayerControls && IsDPadRightPressed(); }                                       // 0x5411D0
    bool ConversationNoJustDown() const noexcept              { return !DisablePlayerControls && IsDPadLeftPressed(); }                                        // 0x541200
    bool GroupControlForwardJustDown() const noexcept         { return !DisablePlayerControls && IsDPadUpPressed(); }                                          // 0x541230
    bool GroupControlBackJustDown() const noexcept            { return !DisablePlayerControls && IsDPadDownPressed(); }                                        // 0x541260

    // KEYBOARD
    bool IsStandardKeyJustDown(uint8 key) const noexcept      { return NewKeyState.standardKeys[key] && OldKeyState.standardKeys[key]; }                       //
    bool IsStandardKeyJustPressed(uint8 key) const noexcept   { return NewKeyState.standardKeys[key] && OldKeyState.standardKeys[key]; }                       // 0x4D59B0
    bool IsLeftCtrlJustPressed() const noexcept               { return KEY_IS_PRESSED(lctrl); }                                                                //
    bool IsRightCtrlJustPressed() const noexcept              { return KEY_IS_PRESSED(rctrl); }                                                                //
    bool IsCtrlJustDown() const noexcept                      { return IsLeftCtrlJustPressed() || IsRightCtrlJustPressed() ? true : false; }                   //
    bool IsLeftCtrlJustDown() const noexcept                  { return NewKeyState.lctrl && OldKeyState.lctrl; }                                               //
    bool IsRightCtrlJustDown() const noexcept                 { return NewKeyState.rctrl && OldKeyState.rctrl; }                                               //
    bool IsCtrlPressed() const noexcept                       { return IsLeftCtrlJustDown() || IsRightCtrlJustDown() ? true : false; }                         //
    bool IsPadEnterJustPressed() const noexcept               { return KEY_IS_PRESSED(enter); }                                                                //
    bool IsReturnJustPressed() const noexcept                 { return KEY_IS_PRESSED(extenter); }                                                             //
    bool IsEnterJustPressed() const noexcept                  { return IsPadEnterJustPressed() || IsReturnJustPressed(); }                                     // 0x4D5980
    bool IsMenuKeyJustPressed() const noexcept                { return KEY_IS_PRESSED(lmenu); }                                                                // 0x744D50
    bool IsTabJustPressed() const noexcept                    { return KEY_IS_PRESSED(tab); }                                                                  // 0x744D90

    // PAD
    bool IsCrossPressed() const noexcept                      { return BUTTON_IS_PRESSED(ButtonCross); }                                                       // 0x4D59E0
    bool IsCirclePressed() const noexcept                     { return BUTTON_IS_PRESSED(ButtonCircle); }                                                      // 0x53EF60
    bool IsTrianglePressed() const noexcept                   { return BUTTON_IS_PRESSED(ButtonTriangle); }                                                    // 0x53EF40
    bool IsSquarePressed() const noexcept                     { return BUTTON_IS_PRESSED(ButtonSquare); }                                                      // 0x53EF20

    bool IsLeftShockPressed() const noexcept                  { return BUTTON_IS_PRESSED(ShockButtonL); }                                                      // 0x509840
    bool IsRightShockPressed() const noexcept                 { return BUTTON_IS_PRESSED(ShockButtonR); }                                                      //

    bool IsRightStickYPressed() const noexcept                { return BUTTON_IS_PRESSED(RightStickY); }                                                       // 0x53ED90

    bool IsStartPressed() const noexcept                      { return BUTTON_IS_PRESSED(Start); }                                                             //
    bool IsSelectPressed() const noexcept                     { return BUTTON_IS_PRESSED(Select); }                                                            // 0x53EF00

    bool IsDPadLeftPressed() const noexcept                   { return BUTTON_IS_PRESSED(DPadLeft); }                                                          // 0x53EEE0
    bool IsDPadRightPressed() const noexcept                  { return BUTTON_IS_PRESSED(DPadRight); }                                                         //
    bool IsDPadUpPressed() const noexcept                     { return BUTTON_IS_PRESSED(DPadUp); }                                                            // 0x53EE60
    bool IsDPadDownPressed() const noexcept                   { return BUTTON_IS_PRESSED(DPadDown); }                                                          // 0x53EEA0

    bool IsDPadLeftJustUp() const noexcept                    { return BUTTON_JUST_UP(DPadLeft); }                                                             //
    bool IsDPadRightJustUp() const noexcept                   { return BUTTON_JUST_UP(DPadRight); }                                                            //
    bool IsDPadUpJustUp() const noexcept                      { return BUTTON_JUST_UP(DPadUp); }                                                               // 0x53EE80
    bool IsDPadDownJustUp() const noexcept                    { return BUTTON_JUST_UP(DPadDown); }                                                             // 0x53EEC0

    bool IsLeftShoulder1Pressed() const noexcept              { return BUTTON_IS_PRESSED(LeftShoulder1); }                                                     // 0x53EDC0
    bool IsLeftShoulder1() const noexcept                     { return BUTTON_IS_DOWN(LeftShoulder1); }                                                        // 0x53EDB0

    bool IsLeftShoulder2JustUp() const noexcept               { return BUTTON_JUST_UP(LeftShoulder2); }                                                        // 0x53EE00
    bool IsLeftShoulder2Pressed() const noexcept              { return BUTTON_IS_PRESSED(LeftShoulder2); }                                                     // 0x53EDE0

    bool IsRightShoulder1Pressed() const noexcept             { return BUTTON_IS_PRESSED(RightShoulder1); }                                                    // 0x53EE20
    bool IsRightShoulder1Up() const noexcept                  { return BUTTON_JUST_UP(RightShoulder1); }                                                       //

    bool IsRightShoulder2Pressed() const noexcept             { return BUTTON_IS_PRESSED(RightShoulder2); }                                                    //
    bool IsRightShoulder2JustUp() const noexcept              { return BUTTON_JUST_UP(RightShoulder2); }                                                       // 0x53EE40

    bool IsLeftMouseButtonPressed() const noexcept            { return NewMouseControllerState.lmb && !OldMouseControllerState.lmb; }                          // 0x4D5A00

    int16 GetLeftStickX() const noexcept                      { return BUTTON_IS_DOWN(LeftStickX); }
    int16 GetLeftStickY() const noexcept                      { return BUTTON_IS_DOWN(LeftStickY); }
    int16 GetRightStickX() const noexcept                     { return BUTTON_IS_DOWN(RightStickX); }
    int16 GetRightStickY() const noexcept                     { return BUTTON_IS_DOWN(RightStickY); }

    bool f0x57C3A0()                                          { return !NewState.ButtonCross && OldState.ButtonCross; }                                         // 0x57C3A0
    bool f0x541170() const noexcept                           { return !DisablePlayerControls && NewState.DPadLeft != 0; }                                      // 0x541170
    bool f0x541150() const noexcept                           { return !DisablePlayerControls && NewState.DPadRight != 0; }                                     // 0x541150
    bool f0x57C380()                                          { return NewState.DPadLeft != 0; }                                                                // 0x57C380
    bool f0x57C390()                                          { return NewState.DPadRight != 0; }                                                               // 0x57C390
    // PAD END

    bool IsSteeringInAnyDirection() { return GetSteeringLeftRight() || GetSteeringUpDown(); }
    int32 sub_541320() { return AverageWeapon / AverageEntries; } // 0x541320
    int32 sub_541290();
    bool sub_541170() const noexcept;
    bool sub_541150() const noexcept;
    static bool sub_540A40();
    static bool sub_540A10();
    static bool sub_5409E0();
    static bool sub_5409B0();
    static bool sub_540980();
    static bool sub_540950();
    bool sub_540530() const noexcept;
    bool sub_5404F0() const noexcept { return Mode == 1 && IsDPadDownPressed(); } // 0x5404F0, maybe wrong
    bool IsPhaseEqual11() const noexcept { return Phase == 11; } // 0x53FB60

    // 0x4E7F20 thiscall
    bool IsRadioTrackSkipPressed() { return NewState.m_bRadioTrackSkip && !OldState.m_bRadioTrackSkip; }
    bool sub_57C330() {
        return !NewKeyState.enter && OldKeyState.enter || !NewKeyState.extenter && OldKeyState.extenter;
    };
    static bool f0x57C360() { return NewKeyState.back && !OldKeyState.back; }
    
    static bool f0x57C3C0() { return !NewMouseControllerState.lmb && OldMouseControllerState.lmb;}
    static bool f0x57C3E0() { return NewMouseControllerState.mmb && !OldMouseControllerState.mmb;}
    static bool f0x57C400() { return NewMouseControllerState.wheelUp && !OldMouseControllerState.wheelUp;}
    static bool f0x57C420() { return NewMouseControllerState.wheelDown && !OldMouseControllerState.wheelDown;}
    static bool f0x57C440() { return NewMouseControllerState.bmx1 && !OldMouseControllerState.bmx1;}
    static bool f0x57C460() { return NewMouseControllerState.bmx2 && !OldMouseControllerState.bmx2; }
    static bool f0x45AF70() { return NewMouseControllerState.lmb; }
    static bool f0x45AF80() { return NewMouseControllerState.rmb; }
    bool f0x45AF90() {
        NewState.LeftStickX = NewMouseControllerState.X;
        NewState.RightStickX = NewMouseControllerState.Y;
    }

    bool f0x4D5970()        { return NewState.LeftShoulder1 == 0; }
    static bool f0x57C330() { return !NewKeyState.enter && OldKeyState.enter || !NewKeyState.extenter && OldKeyState.extenter; }

    static bool f0x53ED70(int8 pad) { padNumber = pad; }
    static bool f0x53ED80(int8 a1) { *(char*)0xB73401 = a1; } // see .cpp
    bool f0x541290() { } // weapon related

    // 0x541A60
    static bool UpdatePadsTillStable() { return true; }
};

VALIDATE_SIZE(CPad, 0x134);

/*
Android has 99 funcs

These are missing:
CheckPointSave(void)
CinemaCamera(void)
CraneReleaseJustDown(void)
CycleCameraModeDownJustDown(bool)
DiveJustDown(void)
DropItemJustDown(void)
EditCodesForControls(int *,int)
EditString(char *,int)
FixPadsAfterSave(void)
GetAbortClimb(void)
GetAutoClimb(void)
GetEscapeJustDown(void)
GetExitTargeting(void)
GetLeftAnalogue(CVector2D *)
GetNitroFired(void)
GetRightAnalogue(CVector2D *)
GetTurretLeft(void)
GetTurretRight(void)
IsFlyingRCVehicle(void)
LookAroundLeftRight(void)
LookAroundUpDown(void)
ProcessStoppie(void)
ProcessWheelie(float)
StopPadsShaking(void)
SwimJumpJustDown(void)
UpdatePadsTillStable(void)
UseBomb(void)
UseRocket(void)
WeaponUsesAttackButton(CPed *)
WeaponUsesTargetingButton(void)
WillBulletHitSomething(CPed *)

- bigger than one line, move to .cpp
bool 0x5404A0() { }
bool 0x53FE50() { }
bool 0x53FD70() { }
bool 0x541340() { }
bool 0x540F80() { }
bool 0x540E80() { }
bool 0x540CC0() { }
bool 0x540BD0() { }
bool 0x53FCD0() { }
 - end
*/
