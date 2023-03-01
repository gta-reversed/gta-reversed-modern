#pragma once

#include <Windows.h>
#include <dinput.h>

namespace WinInput {

void InjectHooks();
bool Initialise();
void InitialiseMouse(bool exclusive);
void InitialiseJoys();
BOOL CALLBACK EnumDevicesCallback(LPCDIDEVICEINSTANCEA pInst, LPVOID);

CMouseControllerState GetMouseState();

}; // namespace WinInput
