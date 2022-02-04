#pragma once

#include "TaskSimpleRunNamedAnim.h"
#include "Vector.h"

class CTaskSimpleSlideToCoord : public CTaskSimpleRunNamedAnim {
public:
    uint8 unkn[28];

public:
    CTaskSimpleSlideToCoord(const CVector&, float, float);
    CTaskSimpleSlideToCoord(int32, char, char, float, char, char);

    CTask* Clone() override;
    eTaskType GetTaskType() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTask* Clone_Reversed();
    eTaskType GetId_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleSlideToCoord, 0x80);
