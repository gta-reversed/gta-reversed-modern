#include "StdInc.h"

#include "Input.h"
#include "ControllerConfigManager.h"
#include "Platform.h"
#include "VideoMode.h"
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

namespace WinInput {
void InjectHooks() {
    RH_ScopedCategory("Win");
    RH_ScopedNamespaceName("Input");

    //RH_ScopedGlobalInstall(Initialise, 0x7487CF, { .reversed = false }); 
    //RH_ScopedGlobalInstall(InitialiseMouse, 0x7469A0, { .reversed = false }); // Can't be hooked because it fails with ACCESS DENIED and crashes
    //RH_ScopedGlobalInstall(InitialiseJoys, 0x7485C0, {.reversed = false});
    RH_ScopedGlobalInstall(EnumDevicesCallback, 0x747020);
}

// 0x746990
HRESULT CreateInput() {
    if (PSGLOBAL(diInterface)) {
        return S_OK; // Already created
    }

    if (SUCCEEDED(DirectInput8Create(GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8, (LPVOID*)&PSGLOBAL(diInterface), nullptr))) {
        return S_OK;
    }

    return S_FALSE; 
}

// 0x7487CF
bool Initialise() {
    ControlsManager.MakeControllerActionsBlank();
    ControlsManager.InitDefaultControlConfiguration();

    if (FAILED(CreateInput())) {
        return false;
    }

    InitialiseMouse(false);
    InitialiseJoys();

    return true;
}

HRESULT ReleaseInput() {
    if (const auto ifc = PSGLOBAL(diInterface)) {
        return ifc->Release();
    }
    return S_OK; // Nothing to release
}

HRESULT Shutdown() {
    return ReleaseInput();
}

// 0x7469A0
void InitialiseMouse(bool exclusive) {
    WIN_FCHECK(PSGLOBAL(diInterface)->CreateDevice(GUID_SysMouse, &PSGLOBAL(diMouse), 0));
    WIN_FCHECK(PSGLOBAL(diMouse)->SetDataFormat(&c_dfDIMouse2));
    WIN_FCHECK(PSGLOBAL(diMouse)->SetCooperativeLevel(PSGLOBAL(window), DISCL_FOREGROUND | (exclusive ? DISCL_EXCLUSIVE : DISCL_NONEXCLUSIVE)));
    WIN_FCHECK(PSGLOBAL(diMouse)->Acquire());
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

// 0x53F2D0
CMouseControllerState GetMouseState() {
	CMouseControllerState state;

    if (!PSGLOBAL(diMouse)) {
		InitialiseMouse(!FrontEndMenuManager.m_bMenuActive && IsVideoModeExclusive());
    }

	if (PSGLOBAL(diMouse)) {
        DIDEVCAPS devCaps{ .dwSize = sizeof(DIDEVCAPS) };
		
		PSGLOBAL(diMouse)->GetCapabilities(&devCaps);
		switch (devCaps.dwButtons) {
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
		case 8:
			state.mmb = true;
            NOTSA_SWCFALLTHRU;
		case 2:
			state.rmb = true;
            NOTSA_SWCFALLTHRU;
		case 1:
			state.lmb = true;
		}

		if (devCaps.dwAxes == 3) {
			state.wheelUp = state.wheelDown = true;
		}
	}

	return state;
}

} // namespace WinInput
