#pragma once

#include "TaskSimpleRunTimedAnim.h"

class CPed;
class CTaskSimpleHandsUp;

class CTaskSimpleHandsUp : public CTaskSimpleRunTimedAnim {
public:
    constexpr static auto Type = TASK_SIMPLE_HANDS_UP;

    explicit CTaskSimpleHandsUp(uint32 duration) : CTaskSimpleRunTimedAnim(ANIM_GROUP_DEFAULT, ANIM_ID_HANDSUP, 4.0f, -4.0f, duration, Type, "HandsUp", false) {}
    ~CTaskSimpleHandsUp() override = default;

    CTask* Clone() override { return new CTaskSimpleHandsUp(m_nDurationMs); }
    virtual bool IsInterruptable(const CPed* ped) { return false; }
};
