#include "StdInc.h"

CTaskComplexCrossRoadLookAndAchieveHeading* CTaskComplexCrossRoadLookAndAchieveHeading::Constructor(uint32 durationInMs, float fTargetHeading)
{
    return plugin::CallMethodAndReturn<CTaskComplexCrossRoadLookAndAchieveHeading*, 0x631AE0, 
        CTaskComplexCrossRoadLookAndAchieveHeading*, uint32, float>(this, durationInMs, fTargetHeading);
}