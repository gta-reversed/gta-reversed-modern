#pragma once

#include "TaskComplex.h"

class CTaskComplexFallToDeath : public CTaskComplex {
public:
    CVector     m_posn;
    AnimationId m_nAnimId;
    int32       m_nAnimId1;
    int8        m_nType;
    union {
        struct {

        };
        uint8 m_nFlags;
    };

    static inline float& ms_NoRailingVerticalForce = *(float*)0x8D2F10;   // 4.5f
    static inline float& ms_OverRailingVerticalForce = *(float*)0x8D2F14; // 9.0f
    static inline float& ms_LateralForceMagnitude = *(float*)0x8D2F18;    // 6.0f

public:
    CTaskComplexFallToDeath(int32, const CVector&, bool, bool);
    ~CTaskComplexFallToDeath() override = default; // 0x6790B0, 0x67D550

    eTaskType GetTaskType() override { return TASK_COMPLEX_FALL_TO_DEATH; }; // 0x6790A0
    CTask* Clone() override { return new CTaskComplexFallToDeath(m_nType, m_posn, (m_nFlags & 8) != 0, (m_nFlags & 0x10) != 0); } // 0x67C480
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override;
    CTask* ControlSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
};
