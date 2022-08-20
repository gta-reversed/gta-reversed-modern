#include "StdInc.h"

#include "app_input.h"

#include "platform.h"

void AppInputInjectHooks() {
    RH_ScopedNamespaceName("Input");
    RH_ScopedCategory("app");

    RH_ScopedGlobalInstall(HandleKeyDown, 0x743DF0);
    RH_ScopedGlobalInstall(HandleKeyUp, 0x7443C0);
    RH_ScopedGlobalInstall(KeyboardHandler, 0x744880);
    RH_ScopedGlobalInstall(HandlePadButtonDown, 0x7448B0);
    RH_ScopedGlobalInstall(HandlePadButtonUp, 0x744930);
    RH_ScopedGlobalInstall(PadHandler, 0x7449F0);
    RH_ScopedGlobalInstall(AttachInputDevices, 0x744A20);
}

// 0x743DF0
RsEventStatus HandleKeyDown(void* param) {
    auto keyStatus = static_cast<RsKeyStatus*>(param);
    return plugin::CallAndReturn<RsEventStatus, 0x743DF0, RsKeyStatus*>(keyStatus);
}

// 0x7443C0
RsEventStatus HandleKeyUp(void* param) {
    auto keyStatus = static_cast<RsKeyStatus*>(param);
    return plugin::CallAndReturn<RsEventStatus, 0x7443C0, RsKeyStatus*>(keyStatus);
}

// 0x744880
RsEventStatus KeyboardHandler(RsEvent event, void* param) {
    switch (event) {
    case rsPADBUTTONDOWN:
        return HandleKeyDown(param);
    case rsPADBUTTONUP:
        return HandleKeyUp(param);
    default:
        return rsEVENTNOTPROCESSED;
    }
}

// 0x7448B0
RsEventStatus HandlePadButtonDown(void* param) {
    auto keyStatus = static_cast<RsKeyStatus*>(param);
    return plugin::CallAndReturn<RsEventStatus, 0x7448B0, RsKeyStatus*>(keyStatus);
}

// 0x744930
RsEventStatus HandlePadButtonUp(void* param) {
    auto keyStatus = static_cast<RsKeyStatus*>(param);
    return plugin::CallAndReturn<RsEventStatus, 0x744930, RsKeyStatus*>(keyStatus);
}

// 0x7449F0
RsEventStatus PadHandler(RsEvent event, void* param) {
    switch (event) {
    case rsPADBUTTONDOWN:
        return HandlePadButtonDown(param);
    case rsPADBUTTONUP:
        return HandlePadButtonUp(param);
    default:
        return rsEVENTNOTPROCESSED;
    }
}

// 0x744A20
bool AttachInputDevices() {
    RsInputDeviceAttach(rsKEYBOARD, KeyboardHandler);
    RsInputDeviceAttach(rsPAD, PadHandler);
    return true;
}
