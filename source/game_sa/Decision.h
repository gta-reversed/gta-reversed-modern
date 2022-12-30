/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

/*
    https://gtamods.com/wiki/Decision_Maker
*/

enum eTaskType : int32;

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

class CDecision {
public:
    eTaskType m_anTaskTypes[6];
    uint8     m_anResponseChances[6][4]; // 4 different relationships : see eDecisionRelationship
    uint8     m_anTypeFlags[2][6];       // 2 different types : see eDecisionTypes

public:
    static void InjectHooks();

    CDecision();

    void SetDefault();
};

VALIDATE_SIZE(CDecision, 0x3C);
