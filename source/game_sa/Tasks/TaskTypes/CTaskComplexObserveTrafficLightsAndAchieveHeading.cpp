#include "StdInc.h"


CTaskComplexObserveTrafficLightsAndAchieveHeading* CTaskComplexObserveTrafficLightsAndAchieveHeading::Constructor(unsigned int durationInMs, float fTargetHeading)
{
    return plugin::CallMethodAndReturn< CTaskComplexObserveTrafficLightsAndAchieveHeading*, 0x631910, 
        CTaskComplexObserveTrafficLightsAndAchieveHeading*, unsigned int, float>(this, durationInMs, fTargetHeading);
}