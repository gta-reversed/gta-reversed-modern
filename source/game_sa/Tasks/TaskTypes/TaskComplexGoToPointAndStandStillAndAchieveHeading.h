#pragma once
#include "TaskComplex.h"

class CVector;

class CTaskComplexGoToPointAndStandStillAndAchieveHeading : public CTaskComplex {
public:
    static void InjectHooks();

    ~CTaskComplexGoToPointAndStandStillAndAchieveHeading();
    CTaskComplexGoToPointAndStandStillAndAchieveHeading(int32 a2, CVector const& a3, float a4, float a5, float a6, float a7);

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GO_TO_POINT_AND_STAND_STILL_AND_ACHIEVE_HEADING;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x668CD0
    CTaskComplexGoToPointAndStandStillAndAchieveHeading* Constructor(int32 a2, CVector const& a3, float a4, float a5, float a6, float a7) {
        this->CTaskComplexGoToPointAndStandStillAndAchieveHeading::CTaskComplexGoToPointAndStandStillAndAchieveHeading(a2, a3, a4, a5, a6, a7);
        return this;
    }

    // 0x668D40
    CTaskComplexGoToPointAndStandStillAndAchieveHeading* Destructor() {
        this->CTaskComplexGoToPointAndStandStillAndAchieveHeading::~CTaskComplexGoToPointAndStandStillAndAchieveHeading();
        return this;
    }
};
