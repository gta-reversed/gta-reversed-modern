#include "StdInc.h"

#include "app_input.h"
#include "platform.h"

void AppInputInjectHooks() {
    RH_ScopedCategory("App");
    RH_ScopedNamespaceName("Input");

    RH_ScopedGlobalInstall(AttachInputDevices, 0x744A20);

    RH_ScopedGlobalInstall(HandleKeyDown, 0x743DF0, {.reversed = false});
    RH_ScopedGlobalInstall(HandleKeyUp, 0x7443C0, {.reversed = false});
    RH_ScopedGlobalInstall(KeyboardHandler, 0x744880, {.reversed = false});
    RH_ScopedGlobalInstall(HandlePadButtonDown, 0x7448B0, {.reversed = false});
    RH_ScopedGlobalInstall(HandlePadButtonUp, 0x744930, {.reversed = false});
    RH_ScopedGlobalInstall(PadHandler, 0x7449F0, {.reversed = false});
}

// 0x744A20
bool AttachInputDevices() {
    RsInputDeviceAttach(rsKEYBOARD, KeyboardHandler);
    RsInputDeviceAttach(rsPAD, PadHandler);
    return true;
}

// 0x743DF0
RsEventStatus HandleKeyDown(RsKeyStatus* param) {
    return plugin::CallAndReturn<RsEventStatus, 0x743DF0, RsKeyStatus*>(param);
}

// 0x7443C0
RsEventStatus HandleKeyUp(RsKeyStatus* param) {
    return plugin::CallAndReturn<RsEventStatus, 0x7443C0, RsKeyStatus*>(param);
}

// 0x744880
RsEventStatus KeyboardHandler(RsEvent event, void* param) {
    switch (event) {
    case rsPADBUTTONDOWN:
        return HandleKeyDown((RsKeyStatus*)param);
    case rsPADBUTTONUP:
        return HandleKeyUp((RsKeyStatus*)param);
    default:
        return rsEVENTNOTPROCESSED;
    }
}

// 0x7448B0
RsEventStatus HandlePadButtonDown(RsKeyStatus* param) {
    return plugin::CallAndReturn<RsEventStatus, 0x7448B0, RsKeyStatus*>(param);
}

// 0x744930
RsEventStatus HandlePadButtonUp(RsKeyStatus* param) {
    return plugin::CallAndReturn<RsEventStatus, 0x744930, RsKeyStatus*>(param);
}

// 0x7449F0
RsEventStatus PadHandler(RsEvent event, void* param) {
    switch (event) {
    case rsPADBUTTONDOWN:
        return HandlePadButtonDown((RsKeyStatus*)param);
    case rsPADBUTTONUP:
        return HandlePadButtonUp((RsKeyStatus*)param);
    default:
        return rsEVENTNOTPROCESSED;
    }
}
