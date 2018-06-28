/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

/*
    https://www.gtamodding.com/wiki/Decision_Maker
*/

enum eDecisionTypes {
    DECISION_ON_FOOT = 0,
    DECISION_IN_VEHICLE = 1
};

enum eDecisionRelationship {
    DECISION_RELATIONSHIP_NEUTRAL = 0,
    DECISION_RELATIONSHIP_PLAYER = 1,
    DECISION_RELATIONSHIP_FRIEND = 2,
    DECISION_RELATIONSHIP_THREAT = 3
};

class  CDecision {
public:
    int m_anTaskTypes[6]; // see eTaskType
    unsigned char m_anResponseChances[6][4]; // 4 different relationships : see eDecisionRelationship
    unsigned char m_anTypeFlags[2][6]; // 2 different types : see eDecisionTypes

    inline CDecision() { // @0x6040C0
        //SetDefault();
    }
};

VALIDATE_SIZE(CDecision, 0x3C);