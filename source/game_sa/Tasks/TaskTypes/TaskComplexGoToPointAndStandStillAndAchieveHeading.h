#pragma once

#include "TaskComplex.h"

class CVector;

class CTaskComplexGoToPointAndStandStillAndAchieveHeading : public CTaskComplex {
private:
    int32   dwordC;
    CVector dword10;
    float   float1C;
    float   float20;
    float   float24;
    float   float28;
    uint8   m_nFlags;

public:
    static constexpr auto Type = TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL_AND_ACHIEVE_HEADING;

    CTaskComplexGoToPointAndStandStillAndAchieveHeading(int32 a2, const CVector& a3, float a4, float a5, float a6, float a7);
    ~CTaskComplexGoToPointAndStandStillAndAchieveHeading() override = default; // 0x668D40

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexGoToPointAndStandStillAndAchieveHeading(dwordC, dword10, float20, float1C, float24, float28); } // 0x66CFD0
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateSubTask(eTaskType taskType);

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexGoToPointAndStandStillAndAchieveHeading* Constructor(int32 a2, CVector const& a3, float a4, float a5, float a6, float a7) { this->CTaskComplexGoToPointAndStandStillAndAchieveHeading::CTaskComplexGoToPointAndStandStillAndAchieveHeading(a2, a3, a4, a5, a6, a7); return this; }
    CTaskComplexGoToPointAndStandStillAndAchieveHeading* Destructor() { this->CTaskComplexGoToPointAndStandStillAndAchieveHeading::~CTaskComplexGoToPointAndStandStillAndAchieveHeading(); return this; }
};
