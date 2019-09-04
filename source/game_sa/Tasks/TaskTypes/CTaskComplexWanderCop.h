#pragma once
#include "CTaskComplexWander.h"
#include "CTaskTimer.h"

class CTaskComplexMoveGoToPointAndStandStill;
class CPed;

class CTaskComplexWanderCop : public CTaskComplexWander
{
public:
    CTaskComplexMoveGoToPointAndStandStill* m_pTaskComplexMoveGoToPointAndStandStill;
    CTaskTimer m_nScanForStuffTimer;
    unsigned int m_nTimePassedSinceLastLookedForCriminals;
    unsigned int m_nTimePassedSinceLastLookedForCarAlarmsAndStolenCopCars;
    CPed* m_pLastCriminalPedLookedFor;
    CTaskTimer m_nSubTaskCreatedTimer;

    CTaskComplexWanderCop* Constructor(int moveState, unsigned char dir);

    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    void ScanForStuff(CPed* ped) override;

    void LookForCarAlarms(CCopPed* pPed);
    void LookForStolenCopCars(CCopPed* pPed);
    void LookForCriminals(CCopPed* pPed);
    bool ShouldPursuePlayer(CCopPed* pPed);
};

VALIDATE_SIZE(CTaskComplexWanderCop, 0x50);