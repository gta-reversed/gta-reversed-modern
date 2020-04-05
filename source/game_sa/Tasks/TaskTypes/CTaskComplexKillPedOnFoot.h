/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTaskComplex.h"
#include "CTaskTimer.h"
#include "CPed.h"

class  CTaskComplexKillPedOnFoot : public CTaskComplex {
public:
    unsigned char  m_nFlags;
    CPed    *m_pTarget;
    unsigned int   m_nAttackFlags;
    unsigned int   m_nActionDelay;
    unsigned int   m_nActionChance;
    char field_20;
    unsigned int   m_nLaunchTime;
    signed int     m_nTime;
    CTaskTimer     m_taskTimer;

    CTaskComplexKillPedOnFoot();
};

VALIDATE_SIZE(CTaskComplexKillPedOnFoot, 0x38);
