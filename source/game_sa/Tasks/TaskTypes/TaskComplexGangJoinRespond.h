#pragma once

#include "TaskComplex.h"

class CPed;

class CTaskComplexGangJoinRespond : public CTaskComplex {
public:
    bool  byteC;
    bool  m_bAnimBlockRefAdded;
    int32 b10;

public:
    static constexpr auto Type = TASK_COMPLEX_GANG_JOIN_RESPOND;

    explicit CTaskComplexGangJoinRespond(uint8 a2);
    ~CTaskComplexGangJoinRespond() override;

    eTaskType GetTaskType() override { return Type; }
    CTask* Clone() override { return new CTaskComplexGangJoinRespond(byteC); } // 0x662290;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, const CEvent* event) override { return true; } // 0x661790;
    CTask* CreateNextSubTask(CPed* ped) override;
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* ControlSubTask(CPed* ped) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();
    CTaskComplexGangJoinRespond* Constructor(uint8 a2) { this->CTaskComplexGangJoinRespond::CTaskComplexGangJoinRespond(a2); return this; }
    CTaskComplexGangJoinRespond* Destructor() { this->CTaskComplexGangJoinRespond::~CTaskComplexGangJoinRespond(); return this; }
};
VALIDATE_SIZE(CTaskComplexGangJoinRespond, 0x14);
