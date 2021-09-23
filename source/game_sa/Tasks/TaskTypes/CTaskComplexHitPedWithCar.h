#pragma once

#include "CTaskComplex.h"
#include "CVector.h"

class CVehicle;

class CTaskComplexHitPedWithCar : public CTaskComplex {
public:
    CVehicle* m_vehicle;
    float     m_damageIntensity;
    int32     m_hitSide;
    float     field_18;
    CVector   m_evasiveStepMoveDirection;
};
