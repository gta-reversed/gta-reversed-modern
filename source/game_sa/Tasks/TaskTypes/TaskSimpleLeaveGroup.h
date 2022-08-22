#pragma once

#include "TaskSimpleNone.h"

class CTaskSimpleLeaveGroup : public CTaskSimpleNone {
public:
    static void InjectHooks();

    CTaskSimpleLeaveGroup() = default; // 0x463540
    ~CTaskSimpleLeaveGroup() = default; // 0x463560
};
