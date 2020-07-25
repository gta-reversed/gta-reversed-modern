#include "StdInc.h"

CControllerConfigManager& ControlsManager = *(CControllerConfigManager*)0xB70198;

void CControllerConfigManager::ClearSimButtonPressCheckers()
{
    ((void(__thiscall*)(CControllerConfigManager*))0x52DD90)(this);
}

void CControllerConfigManager::AffectPadFromKeyBoard()
{
    ((void(__thiscall*)(CControllerConfigManager*))0x531140)(this);
}

void CControllerConfigManager::AffectPadFromMouse()
{
    ((void(__thiscall*)(CControllerConfigManager*))0x5314A0)(this);
}
