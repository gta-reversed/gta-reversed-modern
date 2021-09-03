/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "CPed.h"
#include "CTask.h"

class CPedTaskPair {
public:
    CPed*  m_pPed;
    CTask* m_pTask;
    int32  m_taskSlot;
    int32  field_C;
    int8   field_10;

public:
    static void InjectHooks();

    void Flush();
};
VALIDATE_SIZE(CPedTaskPair, 0x14);
