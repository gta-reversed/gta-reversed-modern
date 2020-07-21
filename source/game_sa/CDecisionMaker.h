/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CDecision.h"
#include "eDecisionMakerEvents.h"

class CDecisionMaker
{
public:
    CDecision m_decision[DM_TOTAL_NUM_EVENTS];

    inline CDecisionMaker() { // @0x4650A0
        for (unsigned int i = 0; i < DM_TOTAL_NUM_EVENTS; ++i) {
            //m_decision[i].SetDefault();
        }
    }
};

VALIDATE_SIZE(CDecisionMaker, 0x99C);
