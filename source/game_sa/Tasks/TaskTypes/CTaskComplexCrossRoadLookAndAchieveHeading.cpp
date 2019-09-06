#include "StdInc.h"

CTaskComplexCrossRoadLookAndAchieveHeading* CTaskComplexCrossRoadLookAndAchieveHeading::Constructor(unsigned int durationInMs, float fTargetHeading)
{
    return plugin::CallMethodAndReturn<CTaskComplexCrossRoadLookAndAchieveHeading*, 0x631AE0, 
        CTaskComplexCrossRoadLookAndAchieveHeading*, unsigned int, float>(this, durationInMs, fTargetHeading);
}