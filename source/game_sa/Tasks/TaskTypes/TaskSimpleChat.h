#pragma once

#include "TaskSimpleRunTimedAnim.h"

class CPed;

class  CTaskSimpleChat : public CTaskSimpleRunTimedAnim {
public:
    static constexpr auto Type = TASK_SIMPLE_CHAT;

    static void InjectHooks();

    CTaskSimpleChat(uint32 duration);
    CTaskSimpleChat(const CTaskSimpleChat& o);
    ~CTaskSimpleChat();

    virtual CTask* Clone() { return new CTaskSimpleChat{ *this }; }
    virtual bool   IsInterruptable(CPed const* ped) { return false; }
 
private:
    // 0x5F7FD0
    CTaskSimpleChat* Destructor() {
        this->CTaskSimpleChat::~CTaskSimpleChat();
        return this;
    }
};
