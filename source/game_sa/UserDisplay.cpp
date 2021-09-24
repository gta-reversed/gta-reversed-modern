#include "StdInc.h"

#include "UserDisplay.h"
#include "CurrentVehicle.h"
#include "PlaceName.h"

CPlaceName& CUserDisplay::PlaceName = *(CPlaceName*)0xBA18F4;
COnscreenTimer& CUserDisplay::OnscnTimer = *(COnscreenTimer*)0xBA1788;
CCurrentVehicle& CUserDisplay::CurrentVehicle = *(CCurrentVehicle*)0xBA18FC;

void CUserDisplay::InjectHooks() {
    using namespace ReversibleHooks;
    Install("CUserDisplay", "Init", 0x571EE0, &CUserDisplay::Init);
    Install("CUserDisplay", "Process", 0x5720A0, &CUserDisplay::Process);
}

// 0x571EE0
void CUserDisplay::Init() {
    PlaceName.Init();
    OnscnTimer.Init();
    CurrentVehicle.Init();
}

// 0x5720A0
void CUserDisplay::Process() {
    PlaceName.Process();
    OnscnTimer.Process();
    CurrentVehicle.Process();
}
