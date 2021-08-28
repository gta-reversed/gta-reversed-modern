#pragma once

#include "CTaskSimpleRunNamedAnim.h"
#include "CVector.h"

class  CTaskSimpleSlideToCoord : public CTaskSimpleRunNamedAnim {
public:
    CTaskSimpleSlideToCoord(CVector const&, float, float);
    CTaskSimpleSlideToCoord(int, char, char, float, char, char);

public:
    unsigned __int8 unkn[28];

public:
    static void InjectHooks();

    CTask* Clone() override;
    eTaskType GetId() override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    bool ProcessPed(CPed* ped) override;

private:
    CTask* Clone_Reversed();
    eTaskType GetId_Reversed();
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    bool ProcessPed_Reversed(CPed* ped);
};

VALIDATE_SIZE(CTaskSimpleSlideToCoord, 0x80);
