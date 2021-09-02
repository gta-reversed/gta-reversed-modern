#include "CTaskComplex.h"
#include "CTaskTimer.h"
#include "CMatrix.h"

class CVehicle;
class CPointRoute;

class CTaskComplexWalkRoundCar : public CTaskComplex
{
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
private:
    uint8 pad16;
public:
    CVector m_targetPoint;
    CVehicle* m_vehicle;
    CPointRoute* m_pointRoute;
    CTaskTimer m_timer;
    CMatrix m_matrix;

    void SetNewVehicle(CVehicle* vehicle, uint8 flags);
};

VALIDATE_SIZE(CTaskComplexWalkRoundCar, 0x78);
