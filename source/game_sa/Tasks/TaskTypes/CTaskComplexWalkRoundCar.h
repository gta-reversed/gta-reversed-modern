#include "CTaskComplex.h"
#include "CTaskTimer.h"
#include "CMatrix.h"

class CVehicle;
class CPointRoute;

class CTaskComplexWalkRoundCar : public CTaskComplex
{
public:
    std::int8_t m_moveState;
    union {
        struct {
            std::uint8_t m_isPedGoingForCarDoor : 1;
            std::uint8_t m_firstSubTaskNeedsToBeCreated : 1;
        };
        std::uint8_t m_flags1;
    };
    union {
        struct {
        std::uint8_t m_flags2_01 : 1;
        std::uint8_t m_flags2_02 : 1;
        std::uint8_t m_flags2_03 : 1;
        std::uint8_t m_flags2_04 : 1;
        };
        std::uint8_t m_flags2;
    };
private:
    std::uint8_t pad16;
public:
    CVector m_targetPoint;
    CVehicle* m_vehicle;
    CPointRoute* m_pointRoute;
    CTaskTimer m_timer;
    CMatrix m_matrix;

    void SetNewVehicle(CVehicle* vehicle, std::uint8_t flags);
};

VALIDATE_SIZE(CTaskComplexWalkRoundCar, 0x78);
