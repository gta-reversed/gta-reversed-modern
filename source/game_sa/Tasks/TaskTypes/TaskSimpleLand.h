#pragma once

#include "TaskSimple.h"

class CTaskSimpleLand : public CTaskSimple {
    CAnimBlendAssociation* m_pAnim;
    AnimationId            m_nAnimId;
    union {
        struct
        {
            uint8 bIsFinished : 1;
            uint8 bNoAnimation : 1;
            uint8 bPedNotUpdated : 1;
        };
        uint8 m_nFlags;
    };

public:
    static constexpr auto Type = TASK_SIMPLE_LAND;

    explicit CTaskSimpleLand(AnimationId nAnimId);
    ~CTaskSimpleLand() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskSimpleLand(m_nAnimId); }
    bool ProcessPed(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;

    bool LeftFootLanded();
    bool RightFootLanded();

    static void FinishAnimCB(CAnimBlendAssociation* anim, void* data);

    static void InjectHooks();
    CTaskSimpleLand* Constructor(AnimationId nAnimId);
    bool ProcessPed_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
};
VALIDATE_SIZE(CTaskSimpleLand, 0x14);
