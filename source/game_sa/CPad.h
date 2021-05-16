/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "rw/skeleton.h"
#include "CKeyboardState.h"
#include "CMouseControllerState.h"
#include "CControllerState.h"

enum ePadButton : unsigned int {
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
    short SteeringLeftRightBuffer[10];
    int DrunkDrivingBufferUsed;
    CControllerState PCTempKeyState;
    CControllerState PCTempJoyState;
    CControllerState PCTempMouseState;
    char Phase;
    char _pad109;
    short Mode;
    short ShakeDur;

    union {
        struct {
            unsigned short unk1 : 1; // eCamMode::MODE_1STPERSON leftover?
            unsigned short unk2 : 1; // unused
            unsigned short bPlayerAwaitsInGarage : 1;
            unsigned short bPlayerOnInteriorTransition : 1;
            unsigned short unk3 : 1; // unused
            unsigned short bPlayerSafe : 1;
            unsigned short bPlayerTalksOnPhone : 1; // bPlayerSafeForPhoneCall?
            unsigned short bPlayerSafeForCutscene : 1;
            unsigned short bPlayerSkipsToDestination : 1; // bPlayerSafeForDestination?
        };
        unsigned short DisablePlayerControls;
    };

    char ShakeFreq;
    char bHornHistory[5];
    char iCurrHornHistory;
    char JustOutOfFrontEnd;
    char bApplyBrakes;
    char bDisablePlayerEnterCar;
    char bDisablePlayerDuck;
    char bDisablePlayerFireWeapon;
    char bDisablePlayerFireWeaponWithL1;
    char bDisablePlayerCycleWeapon;
    char bDisablePlayerJump;
    char bDisablePlayerDisplayVitalStats;
    int LastTimeTouched;
    int AverageWeapon;
    int AverageEntries;
    int NoShakeBeforeThis;
    char NoShakeFreq;
    char _pad131[3];

public:
    // Static variables

    static CMouseControllerState& PCTempMouseControllerState;
    static CMouseControllerState& NewMouseControllerState;
    static CMouseControllerState& OldMouseControllerState;

    static CKeyboardState& TempKeyState;
    static CKeyboardState& OldKeyState;
    static CKeyboardState& NewKeyState;

    static CPad* Pads;

    static void InjectHooks();

    // Functions list : Not finished

    static void Initialise();
    void SetTouched();
    unsigned int GetTouchedTimeDelta();
    void Update(int pad);
    void UpdateMouse();
    void ReconcileTwoControllersInput(CControllerState const& controllerA, CControllerState const& controllerB);
    void SetDrunkInputDelay(int delay);
    void StartShake(short time, unsigned char frequency, unsigned int arg2);
    void StartShake_Distance(short time, unsigned char frequency, float x, float y, float z);
    void StartShake_Train(float x, float y);
    void ProcessPCSpecificStuff();
    void StopShaking(short arg0);
    static CPad* GetPad(int padNumber);
    int16_t GetCarGunLeftRight();
    int16_t GetCarGunUpDown();
    short GetSteeringLeftRight();
    short GetSteeringUpDown();
    short GetPedWalkLeftRight();
    short GetPedWalkUpDown();
    short GetPedWalkLeftRight(CPed* pPed);
    short GetPedWalkUpDown(CPed* pPed);
    bool GetLookLeft();
    bool GetLookRight();
    bool GetLookBehindForCar();
    bool GetLookBehindForPed();
    bool GetHorn();
    bool HornJustDown();
    bool GetHydraulicJump();
    short GetCarGunFired();
    short CarGunJustDown();
    short GetHandBrake();
    short GetBrake();
    bool GetExitVehicle();
    bool ExitVehicleJustDown();
    unsigned char GetMeleeAttack(bool bCheckButtonCircleStateOnly);
    unsigned char MeleeAttackJustDown(bool bCheckButtonCircleStateOnly);
    short GetAccelerate();
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
    short GetDisplayVitalStats(class CPed* ped);
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
    int GetWeapon(CPed* pPed);
    short AimWeaponLeftRight(CPed* pPed);
    short AimWeaponUpDown(CPed* pPed);
    bool IsStandardKeyJustDown(std::uint8_t key);
    bool IsCtrlJustDown();
    bool IsStandardKeyPressed(std::uint8_t key);
    bool IsCtrlPressed();
    bool isEnterJustPressed();
    bool isStandardKeyJustPressed(std::uint8_t key);
    bool isMenuKeyJustPressed();
    bool isTabJustPressed();
};

VALIDATE_SIZE(CPad, 0x134);
