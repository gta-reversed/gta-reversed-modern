#pragma once

#include "TaskComplex.h"
#include "eWeaponType.h"
#include "Vehicle.h"

class CTaskComplexDie : public CTaskComplex {
public:
    enum class eFallDir : int32 { FORWARD, LEFT, BACKWARD, RIGHT };

    eWeaponType  m_nWeaponType;
    AssocGroupId m_nAnimGroup;
    AnimationId  m_nAnimID;
    float        m_fBlendDelta;
    float        m_fAnimSpeed;

    union {
        uint32 m_nFlags;
        struct {
            uint32 bBeingKilledByStealth : 1;
            uint32 bFallingToDeath : 1;
            uint32 bFallToDeathOverRailing : 1;
        };
    };
    eFallDir m_nFallToDeathDir;

public:
    CTaskComplexDie(
        eWeaponType nWeaponType,
        AssocGroupId animGroup,
        AnimationId animID,
        float fBlendDelta,
        float fAnimSpeed,
        bool bBeingKilledByStealth,
        bool bFallingToDeath,
        eFallDir nFallToDeathDir,
        bool bFallToDeathOverRailing
    );
    ~CTaskComplexDie() override = default; // 0x6300C0 0x637910

    eTaskType GetTaskType() override { return TASK_COMPLEX_DIE; } // 0x6300B0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed*) override { return m_pSubTask; } // 0x630580
    CTask* Clone() override;

    void SayDeathSample(CPed* ped);
};

VALIDATE_SIZE(CTaskComplexDie, 0x28);
