/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "rw/skeleton.h"

#include "KeyboardState.h"
#include "MouseControllerState.h"
#include "ControllerState.h"

enum ePadButton : uint32 {
    LEFTSTICKX,     // Left / Right	GO_LEFT / GO_RIGHT
    LEFTSTICKY,     // Forward / Backward	GO_FORWARD / GO_BACK
    RIGHTSTICKX,    // Special CTRL Left / Special CTRL Right	PED_1RST_PERSON_LOOK_LEFT / PED_1RST_PERSON_LOOK_RIGHT
    RIGHTSTICKY,    // Special CTRL Up / Special CTRL Down	PED_1RST_PERSON_LOOK_UP / PED_1RST_PERSON_LOOK_DOWN
    LEFTSHOULDER1,  // Action, Secondary Fire	PED_ANSWER_PHONE, PED_FIREWEAPON_ALT
    LEFTSHOULDER2,  // Previous Weapon / Zoom In	PED_CYCLE_WEAPON_LEFT / PED_SNIPER_ZOOM_IN
    RIGHTSHOULDER1, // Aim Weapon	PED_LOCK_TARGET
    RIGHTSHOULDER2, // Next Weapon / Zoom Out	PED_CYCLE_WEAPON_RIGHT / PED_SNIPER_ZOOM_OUT
    DPADUP,         // Group Control Forward	GROUP_CONTROL_FWD
    DPADDOWN,       // Group Control Backward	GROUP_CONTROL_BWD
    DPADLEFT,       // Conversation - No	CONVERSATION_NO
    DPADRIGHT,      // Conversation - Yes	CONVERSATION_YES
    START,          // Pause Menu
    SELECT,         // Change Camera	CAMERA_CHANGE_VIEW_ALL_SITUATIONS
    SQUARE,         // Jump	PED_JUMPING
    TRIANGLE,       // Enter Vehicle	VEHICLE_ENTER_EXIT
    CROSS,          // Sprint	PED_SPRINT
    CIRCLE,         // Fire Weapon	PED_FIREWEAPON
    LEFTSHOCK,      // Crouch	PED_DUCK
    RIGHTSHOCK,     // Look Behind	PED_LOOKBEHIND
    // --		Sneak	SNEAK_ABOUT
    // --		Cycle Target Left	PED_CYCLE_TARGET_LEFT
    // --		Cycle Target Right	PED_CYCLE_TARGET_RIGHT
    // --		Center Camera	PED_CENTER_CAMERA_BEHIND_PLAYER
};

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

    char  ShakeFreq;
    char  bHornHistory[5];
    char  iCurrHornHistory;
    char  JustOutOfFrontEnd;
    char  bApplyBrakes;
    char  bDisablePlayerEnterCar;
    char  bDisablePlayerDuck;
    char  bDisablePlayerFireWeapon;
    char  bDisablePlayerFireWeaponWithL1;
    char  bDisablePlayerCycleWeapon;
    char  bDisablePlayerJump;
    char  bDisablePlayerDisplayVitalStats;
    int32 LastTimeTouched;
    int32 AverageWeapon;
    int32 AverageEntries;
    int32 NoShakeBeforeThis;
    char  NoShakeFreq;
    char  _pad131[3];

public:
    // Static variables

    static CMouseControllerState& PCTempMouseControllerState;
    static CMouseControllerState& NewMouseControllerState;
    static CMouseControllerState& OldMouseControllerState;

    static CKeyboardState& TempKeyState;
    static CKeyboardState& OldKeyState;
    static CKeyboardState& NewKeyState;

    static CPad* Pads;

    static bool& bInvertLook4Pad;

public:
    static void InjectHooks();

    // Functions list : Not finished

    static void Initialise();
    void SetTouched();
    uint32 GetTouchedTimeDelta();
    void Update(int32 pad);
    void UpdateMouse();
    void ReconcileTwoControllersInput(CControllerState const& controllerA, CControllerState const& controllerB);
    void SetDrunkInputDelay(int32 delay);
    void StartShake(int16 time, uint8 frequency, uint32 arg2);
    void StartShake_Distance(int16 time, uint8 frequency, float x, float y, float z);
    void StartShake_Train(float x, float y);
    void ProcessPCSpecificStuff();
    void StopShaking(int16 arg0);
    static CPad* GetPad(int32 padNumber);
    int16 GetCarGunLeftRight();
    int16 GetCarGunUpDown();
    int16 GetSteeringLeftRight();
    int16 GetSteeringUpDown();
    int16 GetPedWalkLeftRight();
    int16 GetPedWalkUpDown();
    int16 GetPedWalkLeftRight(CPed* pPed);
    int16 GetPedWalkUpDown(CPed* pPed);
    bool GetLookLeft();
    bool GetLookRight();
    bool GetLookBehindForCar();
    bool GetLookBehindForPed();
    bool GetHorn();
    bool HornJustDown();
    bool GetHydraulicJump();
    int16 GetCarGunFired();
    int16 CarGunJustDown();
    int16 GetHandBrake();
    int16 GetBrake();
    bool GetExitVehicle();
    bool ExitVehicleJustDown();
    uint8 GetMeleeAttack(bool bCheckButtonCircleStateOnly);
    uint8 MeleeAttackJustDown(bool bCheckButtonCircleStateOnly);
    int16 GetAccelerate();
    bool GetAccelerateJustDown();
    bool NextStationJustUp();
    bool LastStationJustUp();
    bool CycleWeaponLeftJustDown();
    bool CycleWeaponRightJustDown();
    bool GetTarget();
    bool GetDuck();
    bool DuckJustDown();
    bool GetJump();
    bool JumpJustDown();
    bool GetSprint();
    bool SprintJustDown();
    bool ShiftTargetLeftJustDown();
    bool ShiftTargetRightJustDown();
    int16 GetDisplayVitalStats(class CPed* ped);
    bool CollectPickupJustDown();
    bool GetForceCameraBehindPlayer();
    bool SniperZoomIn();
    bool SniperZoomOut();
    bool GetGroupControlForward();
    bool GetGroupControlBack();
    bool ConversationYesJustDown();
    bool ConversationNoJustDown();
    bool GroupControlForwardJustDown();
    bool GroupControlBackJustDown();
    void Clear(bool enablePlayerControls, bool resetPhase);
    static void ProcessPad(bool numPad);
    static void UpdatePads();
    bool WeaponJustDown(CPed* pPed);
    bool GetEnterTargeting();
    int32 GetWeapon(CPed* pPed);
    int16 AimWeaponLeftRight(CPed* pPed);
    int16 AimWeaponUpDown(CPed* pPed);
    bool IsStandardKeyJustDown(uint8 key);
    bool IsCtrlJustDown();
    bool IsStandardKeyPressed(uint8 key);
    bool IsCtrlPressed();
    bool isEnterJustPressed();
    bool isStandardKeyJustPressed(uint8 key);
    bool isMenuKeyJustPressed();
    bool isTabJustPressed();
};

VALIDATE_SIZE(CPad, 0x134);
