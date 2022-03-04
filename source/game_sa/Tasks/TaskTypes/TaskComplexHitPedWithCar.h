#pragma once

#include "TaskComplex.h"
#include "Vector.h"

class CVehicle;

class CTaskComplexHitPedWithCar : public CTaskComplex {
public:
    static constexpr auto Type = TASK_COMPLEX_HIT_PED_WITH_CAR;

    CVehicle* m_vehicle;
    float     m_damageIntensity;
    int32     m_hitSide;
    float     field_18;
    CVector   m_evasiveStepMoveDirection;
};
