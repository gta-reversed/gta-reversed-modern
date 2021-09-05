#pragma once
#include "CTaskComplex.h"

class CTaskComplexCrossRoadLookAndAchieveHeading : public CTaskComplex
{
public:
    CTaskComplexCrossRoadLookAndAchieveHeading* Constructor(uint32 durationInMs, float fTargetHeading);
};