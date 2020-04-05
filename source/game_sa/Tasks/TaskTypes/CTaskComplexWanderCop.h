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

    static void InjectHooks();

    CTaskComplexWanderCop(int moveState, unsigned char dir);
    ~CTaskComplexWanderCop();
    CTaskComplexWanderCop* Constructor(int moveState, unsigned char dir);

    CTask* Clone() override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    int GetWanderType() override;
    void ScanForStuff(CPed* ped) override;

    CTask* Clone_Reversed();
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* ControlSubTask_Reversed(CPed* ped);
    int GetWanderType_Reversed() { return WANDER_TYPE_COP; };
    void ScanForStuff_Reversed(CPed* ped);

    void LookForCarAlarms(CCopPed* pPed);
    void LookForStolenCopCars(CCopPed* pPed);
    void LookForCriminals(CCopPed* pPed);
    bool ShouldPursuePlayer(CCopPed* pPed);
};

VALIDATE_SIZE(CTaskComplexWanderCop, 0x50);