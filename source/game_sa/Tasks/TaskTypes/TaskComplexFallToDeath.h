#pragma once

#include "TaskComplex.h"

class CTaskComplexFallToDeath : public CTaskComplex {
public:
    enum class eFallDir : int8 { FORWARD, LEFT, BACKWARD, RIGHT };

    CVector     m_Posn;
    AnimationId m_nAnimId;
    AnimationId m_nAnimId1;
    eFallDir    m_nFallToDeathDir;
    union {
        struct {
            uint8 b0x1  : 1;
            uint8 b0x2  : 1;
            uint8 bFallToDeathOverRailing : 1;
            uint8 b0x8  : 1;
            uint8 b0x10 : 1;
        };
        uint8 m_nFlags;
    };

    static inline float ms_NoRailingVerticalForce   = 4.5f; // 0x8D2F10
    static inline float ms_OverRailingVerticalForce = 9.0f; // 0x8D2F14
    static inline float ms_LateralForceMagnitude    = 6.0f; // 0x8D2F18

public:
    CTaskComplexFallToDeath(int32 direction, const CVector& posn, bool a4, bool a5);
    ~CTaskComplexFallToDeath() override = default; // 0x6790B0, 0x67D550

    eTaskType GetTaskType() override { return TASK_COMPLEX_FALL_TO_DEATH; }; // 0x6790A0
    CTask* Clone() override { return new CTaskComplexFallToDeath(static_cast<int32>(m_nFallToDeathDir), m_Posn, b0x8, b0x10); } // 0x67C480
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexFallToDeath* Constructor(int32 direction, const CVector& posn, bool a4, bool a5);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);
    CTask* ControlSubTask_Reversed(CPed* ped);
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);

};
VALIDATE_SIZE(CTaskComplexFallToDeath, 0x24);
