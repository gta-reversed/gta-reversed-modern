/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Task.h"

class CPed;

class NOTSA_EXPORT_VTABLE CTaskComplex : public CTask {
public:
    CTask* m_pSubTask;

public:
    CTaskComplex();
    ~CTaskComplex() override;

    CTask* GetSubTask() override;
    bool IsSimple() override;
    bool MakeAbortable(class CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;

    virtual void SetSubTask(CTask* subTask);
    virtual CTask* CreateNextSubTask(CPed* ped) = 0;
    virtual CTask* CreateFirstSubTask(CPed* ped) = 0;
    virtual CTask* ControlSubTask(CPed* ped) = 0;
    // #vtable: 11
};
VALIDATE_SIZE(CTaskComplex, 0xC);
