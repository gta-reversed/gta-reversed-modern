/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "RenderWare.h"

struct  DIJOYSTATE2 {
    int lX;
    int lY;
    int lZ;
    int lRx;
    int lRy;
    int lRz;
    int rglSlider[2];
    unsigned int rgdwPOV[4];
    unsigned char rgbButtons[128];
    int lVX;
    int lVY;
    int lVZ;
    int lVRx;
    int lVRy;
    int lVRz;
    int rglVSlider[2];
    int lAX;
    int lAY;
    int lAZ;
    int lARx;
    int lARy;
    int lARz;
    int rglASlider[2];
    int lFX;
    int lFY;
    int lFZ;
    int lFRx;
    int lFRy;
    int lFRz;
    int rglFSlider[2];
};

enum  e_ControllerAction {
    CA_PED_FIREWEAPON,
    CA_PED_FIREWEAPON_ALT,
    CA_PED_CYCLE_WEAPON_RIGHT,
    CA_PED_CYCLE_WEAPON_LEFT,
    CA_GO_FORWARD,
    CA_GO_BACK,
    CA_GO_LEFT,
    CA_GO_RIGHT,
    CA_PED_SNIPER_ZOOM_IN,
    CA_PED_SNIPER_ZOOM_OUT,
    CA_VEHICLE_ENTER_EXIT,
    CA_CAMERA_CHANGE_VIEW_ALL_SITUATIONS,
    CA_PED_JUMPING,
    CA_PED_SPRINT,
    CA_PED_LOOKBEHIND,
    CA_PED_DUCK,
    CA_PED_ANSWER_PHONE,
    CA_SNEAK_ABOUT,
    CA_VEHICLE_FIREWEAPON,
    CA_VEHICLE_FIREWEAPON_ALT,
    CA_VEHICLE_STEERLEFT,
    CA_VEHICLE_STEERRIGHT,
    CA_VEHICLE_STEERUP,
    CA_VEHICLE_STEERDOWN,
    CA_VEHICLE_ACCELERATE,
    CA_VEHICLE_BRAKE,
    CA_VEHICLE_RADIO_STATION_UP,
    CA_VEHICLE_RADIO_STATION_DOWN,
    CA_VEHICLE_HORN = 29,
    CA_TOGGLE_SUBMISSIONS,
    CA_VEHICLE_HANDBRAKE,
    CA_PED_1RST_PERSON_LOOK_LEFT,
    CA_PED_1RST_PERSON_LOOK_RIGHT,
    CA_VEHICLE_LOOKLEFT,
    CA_VEHICLE_LOOKRIGHT,
    CA_VEHICLE_LOOKBEHIND,
    CA_VEHICLE_MOUSELOOK,
    CA_VEHICLE_TURRETLEFT,
    CA_VEHICLE_TURRETRIGHT,
    CA_VEHICLE_TURRETUP,
    CA_VEHICLE_TURRETDOWN,
    CA_PED_CYCLE_TARGET_LEFT,
    CA_PED_CYCLE_TARGET_RIGHT,
    CA_PED_CENTER_CAMERA_BEHIND_PLAYER,
    CA_PED_LOCK_TARGET,
    CA_NETWORK_TALK,
    CA_CONVERSATION_YES,
    CA_CONVERSATION_NO,
    CA_GROUP_CONTROL_FWD,
    CA_GROUP_CONTROL_BWD,
    CA_PED_1RST_PERSON_LOOK_UP,
    CA_PED_1RST_PERSON_LOOK_DOWN,
    CA_TOGGLE_DPAD = 54,
    CA_SWITCH_DEBUG_CAM_ON,
    CA_TAKE_SCREEN_SHOT,
    CA_SHOW_MOUSE_POINTER_TOGGLE
};

enum  eControllerType {
    // 4 types
};

class  CControllerKey {
public:
    unsigned int keyCode;
    unsigned int priority;
};

class  CControllerAction {
public:
    CControllerKey keys[4];
};

class  CControllerConfigManager {
public:
    char field_0;
    char field_1;
    char field_2;
    char field_3;
    DIJOYSTATE2       m_prevPadState;
    DIJOYSTATE2       m_currPadState;
    char              m_aszEventNames[59][40];
    char field_B5C[17]; // pad button states
    char _pad1[3];
    CControllerAction m_actions[59];
    char field_12D0[16];
    char field_12E0;
    char _pad2[3];

    void SaveSettings(int file);
    bool LoadSettings(int file);
    bool GetIsKeyboardKeyDown(RsKeyCodes key);
    bool GetIsKeyboardKeyJustDown(RsKeyCodes key);
};

VALIDATE_SIZE(CControllerConfigManager, 0x12E4);

extern  CControllerConfigManager &ControlsManager;
