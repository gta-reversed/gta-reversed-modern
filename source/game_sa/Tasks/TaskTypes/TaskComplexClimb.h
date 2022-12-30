#pragma once

#include "TaskComplexJump.h"

class CTaskComplexClimb : public CTaskComplexJump {
public:
    static constexpr auto Type = TASK_COMPLEX_CLIMB;

    CTaskComplexClimb() : CTaskComplexJump(COMPLEX_JUMP_TYPE_CLIMB) {}; // 0x46A630
    ~CTaskComplexClimb() override = default; // 0x46A6E0

    CTask* Clone() override { return new CTaskComplexClimb(); } // 0x46A6B0
    eTaskType GetTaskType() override { return Type; } // 0x46A6C0
};
