#pragma once
#include "CTaskComplex.h"

class CTaskComplexObserveTrafficLightsAndAchieveHeading : public CTaskComplex
{
public:
    CTaskComplexObserveTrafficLightsAndAchieveHeading* Constructor(unsigned int durationInMs, float fTargetHeading);
};