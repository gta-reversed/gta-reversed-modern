#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CVehicle;

class CTaskComplexHitPedWithCar : public CTaskComplex {
public:
    CVehicle* m_vehicle;
    float     m_damageIntensity;
    int32     m_hitSide;
    float     field_18;
    CVector   m_evasiveStepMoveDirection;
};
