#pragma once
#include "CTaskComplex.h"

class CTaskComplexObserveTrafficLightsAndAchieveHeading : public CTaskComplex
{
public:
    CTaskComplexObserveTrafficLightsAndAchieveHeading* Constructor(uint32 durationInMs, float fTargetHeading);
};