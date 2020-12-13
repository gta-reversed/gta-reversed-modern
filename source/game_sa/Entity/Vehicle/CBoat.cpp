#include "StdInc.h"

CBoat** CBoat::apFrameWakeGeneratingBoats; // static CBoat *apFrameWakeGeneratingBoats[4]
float& CBoat::MAX_WAKE_LENGTH = *(float*)0x8D3938; // 50.0
float& CBoat::MIN_WAKE_INTERVAL = *(float*)0x8D393C; // 2.0
float& CBoat::WAKE_LIFETIME = *(float*)0x8D3940; // 150.0
float& CBoat::fShapeLength = *(float*)0x8D3944; // 0.4
float& CBoat::fShapeTime = *(float*)0x8D3948; // 0.05
float& CBoat::fRangeMult = *(float*)0x8D394C; // 0.6

void CBoat::InjectHooks()
{
}


