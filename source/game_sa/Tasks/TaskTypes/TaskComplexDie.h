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
            uint32 m_bBeingKilledByStealth : 1;
            uint32 m_bFallingToDeath : 1;
            uint32 m_bFallToDeathOverRailing : 1;
        };
    };
    eFallDir m_nFallToDeathDir;

public:
    static constexpr auto Type = TASK_COMPLEX_DIE;

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

    eTaskType GetTaskType() override { return Type; } // 0x6300B0
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed*) override { return m_pSubTask; } // 0x630580
    CTask* Clone() override;

    void SayDeathSample(CPed* ped) const;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexDie* Constructor(eWeaponType nWeaponType, AssocGroupId animGroup, AnimationId animID, float fBlendDelta, float fAnimSpeed, bool bBeingKilledByStealth, bool bFallingToDeath, eFallDir nFallToDeathDir, bool bFallToDeathOverRailing);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* Clone_Reversed();
};

VALIDATE_SIZE(CTaskComplexDie, 0x28);
