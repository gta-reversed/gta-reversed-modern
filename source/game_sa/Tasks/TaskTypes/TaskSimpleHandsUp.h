#pragma once

#include "TaskSimpleRunTimedAnim.h"

class CPed;
class CTaskSimpleHandsUp;

class NOTSA_EXPORT_VTABLE CTaskSimpleHandsUp : public CTaskSimpleRunTimedAnim {
public:
    constexpr static auto Type = TASK_SIMPLE_HANDS_UP;

    explicit CTaskSimpleHandsUp(uint32 duration) : CTaskSimpleRunTimedAnim(ANIM_GROUP_DEFAULT, ANIM_ID_HANDSUP, 4.0f, -4.0f, duration, Type, "HandsUp", 0) {}
    ~CTaskSimpleHandsUp() override = default;

    CTask* Clone() override { return new CTaskSimpleHandsUp(m_nDurationMs); }
    virtual bool IsInterruptable(CPed const* ped) { return false; }

    static void InjectHooks();
    CTaskSimpleHandsUp* Constructor(int32 nTime) { this->CTaskSimpleHandsUp::CTaskSimpleHandsUp(nTime); return this; }
    CTaskSimpleHandsUp* Destructor() { this->CTaskSimpleHandsUp::~CTaskSimpleHandsUp(); return this; }
};
