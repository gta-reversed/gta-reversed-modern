/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "TaskSimpleIKChain.h"

class CTaskSimpleIKManager : public CTaskSimple {
public:
    CTaskSimpleIKChain* m_pIKChainTasks[4];
    bool                m_bAborting;

public:
    static constexpr auto Type = TASK_SIMPLE_IK_MANAGER;

    CTaskSimpleIKManager();
};

VALIDATE_SIZE(CTaskSimpleIKManager, 0x1C);