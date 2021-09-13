#include "StdInc.h"

#include "CTaskComplexObserveTrafficLightsAndAchieveHeading.h"

CTaskComplexObserveTrafficLightsAndAchieveHeading* CTaskComplexObserveTrafficLightsAndAchieveHeading::Constructor(uint32 durationInMs, float fTargetHeading)
{
    return plugin::CallMethodAndReturn< CTaskComplexObserveTrafficLightsAndAchieveHeading*, 0x631910, 
        CTaskComplexObserveTrafficLightsAndAchieveHeading*, uint32, float>(this, durationInMs, fTargetHeading);
}