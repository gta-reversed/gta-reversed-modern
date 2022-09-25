#pragma once

#include "TaskComplex.h"
#include "TaskTimer.h"
#include "Matrix.h"

class CVehicle;
class CPointRoute;

class CTaskComplexWalkRoundCar : public CTaskComplex {
public:
    int8 m_moveState;
    union {
        struct {
            uint8 m_isPedGoingForCarDoor : 1;
            uint8 m_firstSubTaskNeedsToBeCreated : 1;
        };
        uint8 m_flags1;
    };
    union {
        struct {
            uint8 m_flags2_01 : 1;
            uint8 m_flags2_02 : 1;
            uint8 m_flags2_03 : 1;
            uint8 m_flags2_04 : 1;
        };
        uint8 m_flags2;
    };

    char         _pad16;
    CVector      m_targetPoint;
    CVehicle*    m_vehicle;
    CPointRoute* m_pointRoute;
    CTaskTimer   m_timer;
    CMatrix      m_matrix;

public:
    static constexpr auto Type = TASK_COMPLEX_WALK_ROUND_CAR;

    void SetNewVehicle(CVehicle* vehicle, uint8 flags);
    bool IsGoingForDoor() const;
};

VALIDATE_SIZE(CTaskComplexWalkRoundCar, 0x78);
