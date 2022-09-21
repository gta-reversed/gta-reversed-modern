#include "StdInc.h"

#include "Input.h"
#include "ControllerConfigManager.h"

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

static auto g_input = static_cast<IDirectInput8A*>(PSGLOBAL(diInterface));
static auto g_mouse = static_cast<IDirectInputDevice8*>(PSGLOBAL(diMouse));
static auto g_joy1  = static_cast<IDirectInputDevice8*>(PSGLOBAL(diDevice1));
static auto g_joy2  = static_cast<IDirectInputDevice8*>(PSGLOBAL(diDevice2));

namespace WinInput {

void InjectHooks() {
    RH_ScopedNamespaceName("Input");
    RH_ScopedCategory("app");

}

// 0x746990
bool CreateInput() {
    static IID riidltf = *(IID*)0x8588B4;

    if (!PSGLOBAL(diInterface) ||
        FAILED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, riidltf /* IID_IDirectInput8 */, reinterpret_cast<LPVOID*>(g_input), nullptr))) {
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
    if (FAILED(hr = g_input->CreateDevice(GUID_SysMouse, &g_mouse, 0))) {
        DEV_LOG("FAILED(hr=0x%x) in input->CreateDevice\n", hr);
        return;
    }

    if (FAILED(hr = g_mouse->SetDataFormat(&c_dfDIMouse2))) {
        DEV_LOG("FAILED(hr=0x%x) in mouse->SetDataFormat\n", hr);
        return;
    }

    DWORD dwFlags = DISCL_FOREGROUND | (exclusive ? DISCL_EXCLUSIVE : DISCL_NONEXCLUSIVE);
    if (FAILED(hr = g_mouse->SetCooperativeLevel(PSGLOBAL(window), dwFlags))) {
        DEV_LOG("FAILED(hr=0x%x) in mouse->SetCooperativeLevel\n", hr);
        return;
    }

    g_mouse->Acquire();
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
            return &g_joy1;
        case 1:
            return &g_joy2;
        default:
            NOTSA_UNREACHABLE();
        }
    }();

    if (SUCCEEDED(g_input->CreateDevice(inst->guidInstance, joy, nullptr))) {
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

}
