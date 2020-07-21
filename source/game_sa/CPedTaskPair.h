/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPed.h"
#include "CTask.h"


class CPedTaskPair {
public:
    CPed *m_pPed;
    CTask *m_pTask;
    std::int32_t m_taskSlot;
    std::int32_t field_C;
    std::int8_t field_10;

    void Flush();
};

VALIDATE_SIZE(CPedTaskPair, 0x14);

//#include "meta/meta.CPedTaskPair.h"
