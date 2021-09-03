#include "CTaskComplex.h"
#include "CTaskTimer.h"

class CPed;

class CTaskComplexWaitForPed : public CTaskComplex
{
public:
    CPed* m_ped;
    float m_radius;
    uint32 m_timeInMs;
    bool m_bRotateOtherPedsToWaitingPed;
private:
    char padding[3];
    CTaskTimer m_timer;
    int32 m_framesToWaitForSettingRotation;
};

VALIDATE_SIZE(CTaskComplexWaitForPed, 0x2C);
