#pragma once

/*
Plugin-SDK (Grand Theft Auto San Andreas) header file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "CTaskComplex.h"

enum eComplexJumpType : unsigned int
{
    COMPLEX_JUMP_TYPE_JUMP = 0,
    COMPLEX_JUMP_TYPE_CLIMB = 1
};

class CTaskComplexJump : public CTaskComplex {
public:
    eComplexJumpType m_nType;
    bool m_bHighJump;

private:
    CTaskComplexJump* Constructor(eComplexJumpType jumpType);
public:
    CTaskComplexJump(eComplexJumpType type);
    ~CTaskComplexJump() override {}

    static void InjectHooks();

    eTaskType GetId() override { return TASK_COMPLEX_JUMP; }
    CTask* Clone() override;
    CTask* ControlSubTask(CPed* ped) override { return m_pSubTask; }
    CTask* CreateFirstSubTask(CPed* ped) override;
    CTask* CreateNextSubTask(CPed* ped) override;
    bool MakeAbortable(CPed* ped, eAbortPriority priority, CEvent* _event) override;

    CTask* Clone_Reversed();
    CTask* CreateFirstSubTask_Reversed(CPed* ped);
    CTask* CreateNextSubTask_Reversed(CPed* ped);
    bool MakeAbortable_Reversed(CPed* ped, eAbortPriority priority, CEvent* _event);

    CTask* CreateSubTask(eTaskType taskType, CPed* ped);
};

VALIDATE_SIZE(CTaskComplexJump, 0x14);
