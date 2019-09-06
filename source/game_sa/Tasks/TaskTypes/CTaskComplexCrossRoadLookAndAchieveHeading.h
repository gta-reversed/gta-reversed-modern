#pragma once
#include "CTaskComplex.h"

class CTaskComplexCrossRoadLookAndAchieveHeading : public CTaskComplex
{
public:
    CTaskComplexCrossRoadLookAndAchieveHeading* Constructor(unsigned int durationInMs, float fTargetHeading);
};