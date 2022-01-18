#include "StdInc.h"

CControllerConfigManager& ControlsManager = *(CControllerConfigManager *) 0xB70198;

void CControllerConfigManager::InjectHooks() {
//    ReversibleHooks::Install("CControllerConfigManager", "CControllerConfigManager", 0x531EE0, &CControllerConfigManager::Constructor);
//    ReversibleHooks::Install("CControllerConfigManager", "SaveSettings", 0x52D200, &CControllerConfigManager::SaveSettings);
//    ReversibleHooks::Install("CControllerConfigManager", "InitDefaultControlConfiguration", 0x530640, &CControllerConfigManager::InitDefaultControlConfiguration);
//    ReversibleHooks::Install("CControllerConfigManager", "InitialiseControllerActionNameArray", 0x52D260, &CControllerConfigManager::InitialiseControllerActionNameArray);
//    ReversibleHooks::Install("CControllerConfigManager", "ReInitControls", 0x531F20, &CControllerConfigManager::ReInitControls);
//    ReversibleHooks::Install("CControllerConfigManager", "StoreMouseButtonState", 0x52DA30, &CControllerConfigManager::StoreMouseButtonState);
//    ReversibleHooks::Install("CControllerConfigManager", "UpdateJoyInConfigMenus_ButtonDown", 0x52DAB0, &CControllerConfigManager::UpdateJoyInConfigMenus_ButtonDown);
//    ReversibleHooks::Install("CControllerConfigManager", "AffectControllerStateOn_ButtonDown_DebugStuff", 0x52DC10, &CControllerConfigManager::AffectControllerStateOn_ButtonDown_DebugStuff);
//    ReversibleHooks::Install("CControllerConfigManager", "UpdateJoyInConfigMenus_ButtonUp", 0x52DC20, &CControllerConfigManager::UpdateJoyInConfigMenus_ButtonUp);
//    ReversibleHooks::Install("CControllerConfigManager", "AffectControllerStateOn_ButtonUp_DebugStuff", 0x52DD80, &CControllerConfigManager::AffectControllerStateOn_ButtonUp_DebugStuff);
//    ReversibleHooks::Install("CControllerConfigManager", "ClearSimButtonPressCheckers", 0x52DD90, &CControllerConfigManager::ClearSimButtonPressCheckers);
//    ReversibleHooks::Install("CControllerConfigManager", "GetJoyButtonJustUp", 0x52D1C0, &CControllerConfigManager::GetJoyButtonJustUp);
//    ReversibleHooks::Install("CControllerConfigManager", "GetJoyButtonJustDown", 0x52D1E0, &CControllerConfigManager::GetJoyButtonJustDown);
//    ReversibleHooks::Install("CControllerConfigManager", "GetIsKeyboardKeyDown", 0x52DDB0, &CControllerConfigManager::GetIsKeyboardKeyDown);
//    ReversibleHooks::Install("CControllerConfigManager", "GetIsKeyboardKeyJustDown", 0x52E450, &CControllerConfigManager::GetIsKeyboardKeyJustDown);
//    ReversibleHooks::Install("CControllerConfigManager", "GetIsMouseButtonDown", 0x52EF30, &CControllerConfigManager::GetIsMouseButtonDown);
//    ReversibleHooks::Install("CControllerConfigManager", "GetIsMouseButtonUp", 0x52F020, &CControllerConfigManager::GetIsMouseButtonUp);
//    ReversibleHooks::Install("CControllerConfigManager", "GetIsMouseButtonJustUp", 0x52F110, &CControllerConfigManager::GetIsMouseButtonJustUp);
//    ReversibleHooks::Install("CControllerConfigManager", "GetIsKeyBlank", 0x52F2A0, &CControllerConfigManager::GetIsKeyBlank);
//    ReversibleHooks::Install("CControllerConfigManager", "GetActionType", 0x52F2F0, &CControllerConfigManager::GetActionType);
//    ReversibleHooks::Install("CControllerConfigManager", "GetControllerSettingTextMouse", 0x52F390, &CControllerConfigManager::GetControllerSettingTextMouse);
//    ReversibleHooks::Install("CControllerConfigManager", "GetControllerSettingTextJoystick", 0x52F450, &CControllerConfigManager::GetControllerSettingTextJoystick);
//    ReversibleHooks::Install("CControllerConfigManager", "ClearSettingsAssociatedWithAction", 0x52FD70, &CControllerConfigManager::ClearSettingsAssociatedWithAction);
//    ReversibleHooks::Install("CControllerConfigManager", "MakeControllerActionsBlank", 0x530500, &CControllerConfigManager::MakeControllerActionsBlank);
//    ReversibleHooks::Install("CControllerConfigManager", "AffectPadFromKeyBoard", 0x531140, &CControllerConfigManager::AffectPadFromKeyBoard);
//    ReversibleHooks::Install("CControllerConfigManager", "AffectPadFromMouse", 0x5314A0, &CControllerConfigManager::AffectPadFromMouse);
//    ReversibleHooks::Install("CControllerConfigManager", "DeleteMatchingActionInitiators", 0x531C90, &CControllerConfigManager::DeleteMatchingActionInitiators);
}

// 0x531EE0
CControllerConfigManager::CControllerConfigManager() {
    plugin::Call<0x531EE0>();
}

CControllerConfigManager* CControllerConfigManager::Constructor() {
    this->CControllerConfigManager::CControllerConfigManager();
    return this;
}

// 0x52D200
void CControllerConfigManager::SaveSettings(FILE* file) {
    plugin::Call<0x52D200, FILE*>(file);
}

// 0x530640
void CControllerConfigManager::InitDefaultControlConfiguration() {
    plugin::CallMethod<0x530640, CControllerConfigManager*>(this);
}

// 0x52D260
void CControllerConfigManager::InitialiseControllerActionNameArray() {
    plugin::CallMethod<0x52D260, CControllerConfigManager*>(this);
}

// 0x531F20
void CControllerConfigManager::ReInitControls() {
    plugin::Call<0x531F20>();
}

// unused
// 0x52DA30
void CControllerConfigManager::StoreMouseButtonState(eMouseButtons button, bool state) {
    switch (button) {
        case MOUSE_BUTTON_LEFT:
            CPad::PCTempMouseControllerState.lmb = state;
            break;
        case MOUSE_BUTTON_MIDDLE:
            CPad::PCTempMouseControllerState.mmb = state;
            break;
        case MOUSE_BUTTON_RIGHT:
            CPad::PCTempMouseControllerState.rmb = state;
            break;
        case MOUSE_BUTTON_WHEEL_UP:
            CPad::PCTempMouseControllerState.wheelUp = state;
            break;
        case MOUSE_BUTTON_WHEEL_DOWN:
            CPad::PCTempMouseControllerState.wheelDown = state;
            break;
        case MOUSE_BUTTON_WHEEL_XBUTTON1:
            CPad::PCTempMouseControllerState.bmx1 = state;
            break;
        case MOUSE_BUTTON_WHEEL_XBUTTON2:
            CPad::PCTempMouseControllerState.bmx2 = state;
            break;
        case MOUSE_BUTTON_NONE:
            break;
    }
}

// 0x52DAB0
void CControllerConfigManager::UpdateJoyInConfigMenus_ButtonDown(ePadButton button, int32 padNumber) {
    plugin::CallMethod<0x52DAB0, CControllerConfigManager*, ePadButton, int32>(this, button, padNumber);
}

// unused
// 0x52DC10
void CControllerConfigManager::AffectControllerStateOn_ButtonDown_DebugStuff(int32, eControllerType) {
    // NOP
}

// 0x52DC20
void CControllerConfigManager::UpdateJoyInConfigMenus_ButtonUp(ePadButton button, int32 padNumber) {
    plugin::CallMethod<0x52DC20, CControllerConfigManager*, ePadButton, int32>(this, button, padNumber);
}

// unused
// 0x52DD80
void CControllerConfigManager::AffectControllerStateOn_ButtonUp_DebugStuff(int32, eControllerType) {
    // NOP
}

// 0x52DD90
void CControllerConfigManager::ClearSimButtonPressCheckers() {
    plugin::CallMethod<0x52DD90, CControllerConfigManager*>(this);
}

// unused
// 0x52D1C0
bool CControllerConfigManager::GetJoyButtonJustUp() {
    return plugin::CallMethodAndReturn<bool, 0x52D1C0, CControllerConfigManager*>(this);
}

// 0x52D1E0
bool CControllerConfigManager::GetJoyButtonJustDown() {
    return plugin::CallMethodAndReturn<bool, 0x52D1E0, CControllerConfigManager*>(this);
}

// 0x52DDB0
bool CControllerConfigManager::GetIsKeyboardKeyDown(RsKeyCodes key) {
    return plugin::CallMethodAndReturn<bool, 0x52DDB0, CControllerConfigManager*, RsKeyCodes>(this, key);
}

// 0x52E450
bool CControllerConfigManager::GetIsKeyboardKeyJustDown(RsKeyCodes key) {
    return plugin::CallMethodAndReturn<bool, 0x52E450, CControllerConfigManager*, RsKeyCodes>(this, key);
}

// 0x52EF30
bool CControllerConfigManager::GetIsMouseButtonDown(RsKeyCodes key) {
    return plugin::CallMethodAndReturn<bool, 0x52EF30, CControllerConfigManager*, RsKeyCodes>(this, key);
}

// 0x52F020
bool CControllerConfigManager::GetIsMouseButtonUp(RsKeyCodes key) {
    return plugin::CallMethodAndReturn<bool, 0x52F020, CControllerConfigManager*, RsKeyCodes>(this, key);
}

// 0x52F110
bool CControllerConfigManager::GetIsMouseButtonJustUp(RsKeyCodes key) {
    return plugin::CallMethodAndReturn<bool, 0x52F110, CControllerConfigManager*, RsKeyCodes>(this, key);
}

// unused
// 0x52F2A0
bool CControllerConfigManager::GetIsKeyBlank(int32 a1, eControllerType controller) {
    return plugin::CallMethodAndReturn<bool, 0x52F2A0, CControllerConfigManager*, int32, eControllerType>(this, a1, controller);
}

// 0x52F2F0
eActionType CControllerConfigManager::GetActionType(eControllerAction action) {
    switch (action) {
        case CA_PED_FIREWEAPON:
        case CA_PED_FIREWEAPON_ALT:
        case CA_GO_FORWARD:
        case CA_GO_BACK:
        case CA_GO_LEFT:
        case CA_GO_RIGHT:
        case CA_PED_SNIPER_ZOOM_IN:
        case CA_PED_SNIPER_ZOOM_OUT:
        case CA_PED_1RST_PERSON_LOOK_LEFT:
        case CA_PED_1RST_PERSON_LOOK_RIGHT:
        case CA_PED_LOCK_TARGET:
        case CA_PED_1RST_PERSON_LOOK_UP:
        case CA_PED_1RST_PERSON_LOOK_DOWN:
            return ACTION_5;
        case CA_PED_CYCLE_WEAPON_RIGHT:
        case CA_PED_CYCLE_WEAPON_LEFT:
        case CA_PED_JUMPING:
        case CA_PED_SPRINT:
        case CA_PED_LOOKBEHIND:
        case CA_PED_DUCK:
        case CA_PED_ANSWER_PHONE:
        case CA_SNEAK_ABOUT:
        case CA_PED_CYCLE_TARGET_LEFT:
        case CA_PED_CYCLE_TARGET_RIGHT:
        case CA_PED_CENTER_CAMERA_BEHIND_PLAYER:
        case CA_CONVERSATION_YES:
        case CA_CONVERSATION_NO:
        case CA_GROUP_CONTROL_FWD:
        case CA_GROUP_CONTROL_BWD:
            return ACTION_1;
        case CA_VEHICLE_ENTER_EXIT:
            return ACTION_3;
        case CA_CAMERA_CHANGE_VIEW_ALL_SITUATIONS:
        case CA_NETWORK_TALK:
        case CA_TOGGLE_DPAD:
        case CA_SWITCH_DEBUG_CAM_ON:
        case CA_TAKE_SCREEN_SHOT:
        case CA_SHOW_MOUSE_POINTER_TOGGLE:
            return ACTION_4;
        case CA_VEHICLE_FIREWEAPON:
        case CA_VEHICLE_FIREWEAPON_ALT:
        case CA_VEHICLE_STEERLEFT:
        case CA_VEHICLE_STEERRIGHT:
        case CA_VEHICLE_STEERUP:
        case CA_VEHICLE_STEERDOWN:
        case CA_VEHICLE_ACCELERATE:
        case CA_VEHICLE_BRAKE:
        case CA_VEHICLE_RADIO_STATION_UP:
        case CA_VEHICLE_RADIO_STATION_DOWN:
        case CA_UNKNOWN_28:
        case CA_VEHICLE_HORN:
        case CA_TOGGLE_SUBMISSIONS:
        case CA_VEHICLE_HANDBRAKE:
        case CA_VEHICLE_LOOKLEFT:
        case CA_VEHICLE_LOOKRIGHT:
        case CA_VEHICLE_LOOKBEHIND:
        case CA_VEHICLE_MOUSELOOK:
        case CA_VEHICLE_TURRETLEFT:
        case CA_VEHICLE_TURRETRIGHT:
        case CA_VEHICLE_TURRETUP:
        case CA_VEHICLE_TURRETDOWN:
            return ACTION_2;
        default:
            return ACTION_6;
    }
}

// 0x52F390
char* CControllerConfigManager::GetControllerSettingTextMouse(eControllerAction action) {
    return plugin::CallMethodAndReturn<char*, 0x52F390, CControllerConfigManager*, eControllerAction>(this, action);
}

// 0x52F450
char* CControllerConfigManager::GetControllerSettingTextJoystick(eControllerAction action) {
    return plugin::CallMethodAndReturn<char*, 0x52F450, CControllerConfigManager*, eControllerAction>(this, action);
}

// 0x52FD70
void CControllerConfigManager::ClearSettingsAssociatedWithAction(eControllerAction action, eControllerType type) {
    plugin::CallMethod<0x52FD70, CControllerConfigManager*, eControllerAction, eControllerType>(this, action, type);
}

// 0x530500
void CControllerConfigManager::MakeControllerActionsBlank() {
    plugin::CallMethod<0x530500, CControllerConfigManager*>(this);
}

// 0x531140
void CControllerConfigManager::AffectPadFromKeyBoard() {
    plugin::CallMethod<0x531140, CControllerConfigManager*>(this);
}

// 0x5314A0
void CControllerConfigManager::AffectPadFromMouse() {
    plugin::CallMethod<0x5314A0, CControllerConfigManager*>(this);
}

// 0x531C90
void CControllerConfigManager::DeleteMatchingActionInitiators(eControllerAction action, int32 a2, eControllerType type) {
    plugin::CallMethod<0x531C90, CControllerConfigManager*, eControllerAction, int32, eControllerType>(this, action, a2, type);
}
