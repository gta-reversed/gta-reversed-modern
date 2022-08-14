#pragma once
#include "TaskComplex.h"

class CPed;

class CTaskComplexGangJoinRespond : public CTaskComplex {
public:
    static void InjectHooks();

    CTaskComplexGangJoinRespond(uint8 a2);
    ~CTaskComplexGangJoinRespond();

    static constexpr auto Type = eTaskType::TASK_COMPLEX_GANG_JOIN_RESPOND;

    virtual CTask* Clone();
    virtual eTaskType GetTaskType() { return Type; }
    virtual bool MakeAbortable(CPed* ped, int32 priority, CEvent const* event);
    virtual CTask* CreateNextSubTask(CPed* ped);
    virtual CTask* CreateFirstSubTask(CPed* ped);
    virtual CTask* ControlSubTask(CPed* ped);

private: // Wrappers for hooks
    // 0x6616F0
    CTaskComplexGangJoinRespond* Constructor(uint8 a2) {
        this->CTaskComplexGangJoinRespond::CTaskComplexGangJoinRespond(a2);
        return this;
    }

    // 0x661720
    CTaskComplexGangJoinRespond* Destructor() {
        this->CTaskComplexGangJoinRespond::~CTaskComplexGangJoinRespond();
        return this;
    }
};
