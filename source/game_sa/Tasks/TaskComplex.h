/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Task.h"

class CPed;

class CTaskComplex : public CTask {
public:
    CTask* m_pSubTask;

public:
    CTaskComplex();
    ~CTaskComplex();

    CTask* GetSubTask() override;
    bool IsSimple() override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority, const CEvent* event) override; // Seems like priority defaults to `ABORT_PRIORITY_URGENT` and `event = nullptr`

    virtual void SetSubTask(CTask* subTask);
    virtual CTask* CreateNextSubTask(CPed* ped) = 0;
    virtual CTask* CreateFirstSubTask(CPed* ped) = 0;
    virtual CTask* ControlSubTask(CPed* ped) = 0;

private:
    CTaskComplex* Constructor();

    CTask* GetSubTask_Reversed() { return m_pSubTask; }
    bool IsSimple_Reversed() { return false; }
    bool MakeAbortable_Reversed(class CPed* ped, eAbortPriority priority, const CEvent* event);
};

VALIDATE_SIZE(CTaskComplex, 0xC);
