/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"

class  CDecisionSimple {
public:
    int m_anTasks[6]; // task types, see eTaskType
    float m_afChances[6];
    unsigned int m_nCount; // tasks count (max 6)

    void Set(int* taskTypes, unsigned char* chances, int count);
    void MakeDecision(int taskType, short& outTaskType, int& outDecisionIndex);
    void SetDefault();
};

VALIDATE_SIZE(CDecisionSimple, 0x34);