#include "StdInc.h"

#include "ControllerConfigManager.h"

CControllerConfigManager& ControlsManager = *(CControllerConfigManager *) 0xB70198;

void CControllerConfigManager::InjectHooks() {
    RH_ScopedClass(CControllerConfigManager);
    RH_ScopedCategoryGlobal();

//    RH_ScopedInstall(Constructor, 0x531EE0);
//    RH_ScopedInstall(LoadSettings, 0x530530);
//    RH_ScopedInstall(SaveSettings, 0x52D200);
//    RH_ScopedInstall(InitDefaultControlConfiguration, 0x530640);
//    RH_ScopedInstall(InitialiseControllerActionNameArray, 0x52D260);
//    RH_ScopedInstall(ReinitControls, 0x531F20);
//    RH_ScopedInstall(StoreMouseButtonState, 0x52DA30);
//    RH_ScopedInstall(UpdateJoyInConfigMenus_ButtonDown, 0x52DAB0);
//    RH_ScopedInstall(AffectControllerStateOn_ButtonDown_DebugStuff, 0x52DC10);
//    RH_ScopedInstall(UpdateJoyInConfigMenus_ButtonUp, 0x52DC20);
//    RH_ScopedInstall(AffectControllerStateOn_ButtonUp_DebugStuff, 0x52DD80);
//    RH_ScopedInstall(ClearSimButtonPressCheckers, 0x52DD90);
//    RH_ScopedInstall(GetJoyButtonJustUp, 0x52D1C0);
//    RH_ScopedInstall(GetJoyButtonJustDown, 0x52D1E0);
//    RH_ScopedInstall(GetIsKeyboardKeyDown, 0x52DDB0);
//    RH_ScopedInstall(GetIsKeyboardKeyJustDown, 0x52E450);
//    RH_ScopedInstall(GetIsMouseButtonDown, 0x52EF30);
//    RH_ScopedInstall(GetIsMouseButtonUp, 0x52F020);
//    RH_ScopedInstall(GetIsMouseButtonJustUp, 0x52F110);
//    RH_ScopedInstall(GetIsKeyBlank, 0x52F2A0);
//    RH_ScopedInstall(GetActionType, 0x52F2F0);
//    RH_ScopedInstall(GetControllerSettingTextMouse, 0x52F390);
//    RH_ScopedInstall(GetControllerSettingTextJoystick, 0x52F450);
//    RH_ScopedInstall(ClearSettingsAssociatedWithAction, 0x52FD70);
//    RH_ScopedInstall(MakeControllerActionsBlank, 0x530500);
//    RH_ScopedInstall(AffectPadFromKeyBoard, 0x531140);
//    RH_ScopedInstall(AffectPadFromMouse, 0x5314A0);
//    RH_ScopedInstall(DeleteMatchingActionInitiators, 0x531C90);
}

// 0x531EE0
CControllerConfigManager::CControllerConfigManager() {
    plugin::CallMethod<0x531EE0, CControllerConfigManager*>(this);
}

CControllerConfigManager* CControllerConfigManager::Constructor() {
    this->CControllerConfigManager::CControllerConfigManager();
    return this;
}

// 0x530530
bool CControllerConfigManager::LoadSettings(FILESTREAM file) {
    return plugin::CallMethodAndReturn<bool, 0x530530, CControllerConfigManager*, FILESTREAM>(this, file);
}

// 0x52D200
void CControllerConfigManager::SaveSettings(FILESTREAM file) {
    plugin::CallMethod<0x52D200, CControllerConfigManager*, FILE*>(this, file);
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
void CControllerConfigManager::ReinitControls() {
    plugin::CallMethod<0x531F20, CControllerConfigManager*>(this);
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
void CControllerConfigManager::DeleteMatchingActionInitiators(eControllerAction Action, int32 KeyToBeChecked, eControllerType ControllerTypeToBeChecked) {
    plugin::CallMethod<0x531C90, CControllerConfigManager*, eControllerAction, int32, eControllerType>(this, Action, KeyToBeChecked, ControllerTypeToBeChecked);
}
