/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CTimer.h"

class CTaskTimer 
{
public:
    unsigned int m_nStartTime;
    int m_nInterval;
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
    
    inline bool Start (int time) {
        if (time >= 0) {
            m_nStartTime = CTimer::m_snTimeInMilliseconds;
            m_nInterval = time;
            m_bStarted = true;
            return true;
        }
        return false;
    }

    inline bool Stop() {
        if(m_bStarted) {
            m_bStopped = true;
            m_nInterval -= CTimer::m_snTimeInMilliseconds - m_nStartTime;
            return true;
        }
        return false;
    }

    inline bool Reset() {
        if (m_bStarted) {
            if (m_bStopped) {
                m_nStartTime = CTimer::m_snTimeInMilliseconds;
                m_bStopped = false;
            }
            return true;
        }
        return false;
    }

    bool IsOutOfTime();
};

VALIDATE_SIZE(CTaskTimer, 0xC);