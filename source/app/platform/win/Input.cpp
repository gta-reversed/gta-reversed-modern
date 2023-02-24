#include "StdInc.h"

#include "Input.h"
#include "ControllerConfigManager.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace WinInput {
void InjectHooks() {
    RH_ScopedCategory("Win");
    RH_ScopedNamespaceName("Input");

    RH_ScopedGlobalInstall(Initialise, 0x7487CF, {.reversed = false}); // <-- hooking it crashes the game
    RH_ScopedGlobalInstall(InitialiseMouse, 0x7469A0);
    RH_ScopedGlobalInstall(InitialiseJoys, 0x7485C0, {.reversed = false});
    RH_ScopedGlobalInstall(EnumDevicesCallback, 0x747020);
}

// 0x746990
bool CreateInput() {
    static IID riidltf = *(IID*)0x8588B4;

    if (!PSGLOBAL(diInterface) ||
        FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, riidltf, (LPVOID*)&PSGLOBAL(diInterface), nullptr))) {
        return false;
    }
    return true;
}

// 0x7487CF
bool Initialise() {
    ControlsManager.MakeControllerActionsBlank();
    ControlsManager.InitDefaultControlConfiguration();

    if (!CreateInput()) {
        return false;
    }

    InitialiseMouse(false);
    InitialiseJoys();
    return true;
}

// 0x7469A0
void InitialiseMouse(bool exclusive) {
    HRESULT hr;
    if (FAILED(hr = PSGLOBAL(diInterface)->CreateDevice(GUID_SysMouse, &PSGLOBAL(diMouse), 0))) {
        DEV_LOG("FAILED(hr=0x{:x}) in input->CreateDevice\n", hr);
        return;
    }

    if (FAILED(hr = PSGLOBAL(diMouse)->SetDataFormat(&c_dfDIMouse2))) {
        DEV_LOG("FAILED(hr=0x{:x}) in mouse->SetDataFormat\n", hr);
        return;
    }

    DWORD dwFlags = DISCL_FOREGROUND | (exclusive ? DISCL_EXCLUSIVE : DISCL_NONEXCLUSIVE);
    if (FAILED(hr = PSGLOBAL(diMouse)->SetCooperativeLevel(PSGLOBAL(window), dwFlags))) {
        DEV_LOG("FAILED(hr=0x{:x}) in mouse->SetCooperativeLevel\n", hr);
        return;
    }

    PSGLOBAL(diMouse)->Acquire();
}

// 0x7485C0
void InitialiseJoys() {
    plugin::Call<0x7485C0>();
}

// 0x747020
BOOL CALLBACK EnumDevicesCallback(LPCDIDEVICEINSTANCEA inst, LPVOID) {
    static int32 snJoyCount = 0;

    LPDIRECTINPUTDEVICE8* joy = [] {
        switch (snJoyCount) {
        case 0:
            return &PSGLOBAL(diDevice1);
        case 1:
            return &PSGLOBAL(diDevice2);
        default:
            NOTSA_UNREACHABLE();
        }
    }();

    if (SUCCEEDED(PSGLOBAL(diInterface)->CreateDevice(inst->guidInstance, joy, nullptr))) {
        return TRUE;
    }

    if (SUCCEEDED((*joy)->SetDataFormat(&c_dfDIJoystick2))) {
        (*joy)->Release();
        return TRUE;
    }

    ++snJoyCount;

    if (FAILED((*joy)->SetCooperativeLevel(PSGLOBAL(window), DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))) {
        (*joy)->Release();
        return TRUE;
    }

    return snJoyCount != 2; // todo: CJoySticks, JOYPAD_COUNT
}

const CMouseControllerState& GetMouseButtonMask() {
    return plugin::CallAndReturn<const CMouseControllerState&, 0x53F2D0>();
}
} // namespace WinInput
