/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskComplex.h"

enum eComplexJumpType : uint32 {
    COMPLEX_JUMP_TYPE_JUMP  = 0,
    COMPLEX_JUMP_TYPE_CLIMB = 1
};

class CTaskComplexJump : public CTaskComplex {
public:
    eComplexJumpType m_nType;
    bool             m_bHighJump;

public:
    static constexpr auto Type = TASK_COMPLEX_JUMP;

    explicit CTaskComplexJump(eComplexJumpType type);
    ~CTaskComplexJump() override = default;

    eTaskType GetTaskType() const override { return Type; }
    CTask* Clone() const override;
    CTask* ControlSubTask(CPed* ped) override { return m_pSubTask; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    bool   MakeAbortable(CPed* ped, eAbortPriority priority = ABORT_PRIORITY_URGENT, const CEvent* event = nullptr) override;

private:
    friend void InjectHooksMain();
    static void InjectHooks();

    CTaskComplexJump* Constructor(eComplexJumpType jumpType);

    CTask*  Clone_Reversed() const;
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    bool   MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, const CEvent* event);

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
};

VALIDATE_SIZE(CTaskComplexJump, 0x14);
