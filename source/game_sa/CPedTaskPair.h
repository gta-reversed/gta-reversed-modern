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


class  CPedTaskPair {
public:
    CPed *m_pPed;
    CTask *m_pTask;
    int field_8;

     void Flush();
};

VALIDATE_SIZE(CPedTaskPair, 0xC);

//#include "meta/meta.CPedTaskPair.h"
