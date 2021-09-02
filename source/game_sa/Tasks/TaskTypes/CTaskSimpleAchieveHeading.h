#pragma once
#include "CTaskSimple.h"

class CTaskSimpleAchieveHeading : public CTaskSimple
{
public:
    int32 field_8;
    int32 field_C;
    int32 field_10;
    int32 field_14;

    CTaskSimpleAchieveHeading(float fAngle, float arg2, float arg3);
    ~CTaskSimpleAchieveHeading() override;

    bool ProcessPed(class CPed* ped) override;
    CTask* Clone() override;
    eTaskType GetId() override { return TASK_SIMPLE_ACHIEVE_HEADING; }
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
};

VALIDATE_SIZE(CTaskSimpleAchieveHeading, 0x18);
