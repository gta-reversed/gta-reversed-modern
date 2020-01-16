/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"

class CTaskTimer 
{
public:
    unsigned int m_nStartTime;
    unsigned int m_nInterval;
    bool m_bStarted;
    bool m_bStopped;
private:
    char _pad[2];
public:
    
    inline CTaskTimer(unsigned int start, unsigned int interval) { // @420E10
        m_nStartTime = start;
        m_nInterval = interval;
        m_bStarted = true;
    }

    inline CTaskTimer() {
        m_nStartTime = 0;
        m_nInterval = 0;
        m_bStarted = false;
        m_bStopped = false;
    }   
    
    CTaskTimer(plugin::dummy_func_t) {}

    bool IsOutOfTime();
};

VALIDATE_SIZE(CTaskTimer, 0xC);