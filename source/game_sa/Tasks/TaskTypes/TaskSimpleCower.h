#pragma once

#include "TaskSimpleRunAnim.h"

class CTaskSimpleCower;
class CPed;

class CTaskSimpleCower : public CTaskSimpleRunAnim {
public:
    constexpr static auto Type = TASK_SIMPLE_COWER;

    CTaskSimpleCower() : CTaskSimpleRunAnim{ ANIM_GROUP_DEFAULT, ANIM_ID_HANDSCOWER, 4.0f, Type, "Cower", false } {} // 0x48DE70
    ~CTaskSimpleCower() override = default; // 0x48E900

    CTask* Clone() override { return new CTaskSimpleCower{}; }
    virtual bool IsInterruptable(const CPed* ped) { return false; } // NOTE: Possible leftover from `CTaskSimpleRunAnim`?

    static void InjectHooks();
    CTaskSimpleCower* Constructor() { this->CTaskSimpleCower::CTaskSimpleCower(); return this; }
    CTaskSimpleCower* Destructor() { this->CTaskSimpleCower::~CTaskSimpleCower(); return this; }
};
