#pragma once

#include <Windows.h>
#include <dinput.h>

namespace WinInput {

bool Initialise();
void InitialiseMouse(bool exclusive);
void InitialiseJoys();
BOOL CALLBACK EnumDevicesCallback(LPCDIDEVICEINSTANCEA pInst, LPVOID);

}; // namespace WinInput
