#pragma once

#include "CDecision.h"

class CPed;
class CPedGroup;
class CDecisionMaker;

class CDecisionMakerTypesFileLoader
{
public:
    static void InjectHooks();

    static void GetPedDMName(std::int32_t index, char* name);
    static void GetGrpDMName(std::int32_t index, char* name);
    static void LoadDefaultDecisionMaker();
    static void LoadDecisionMaker(const char* filepath, eDecisionTypes decisionMakerType, bool bUseMissionCleanup);
    static void LoadDecisionMaker(const char* filepath, CDecisionMaker* decisionMaker);
};

class CDecisionMakerTypes {
public:
    static void InjectHooks();

    static void AddDecisionMaker(CDecisionMakerTypes* decisionMakerTypes, CDecisionMaker* decisionMaker, eDecisionTypes decisionMakerType, bool bUseMissionCleanup);
    static CDecisionMakerTypes* GetInstance();

    void MakeDecision(CPed* ped, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
        int taskId2, int taskId3, int taskId4, bool bDecisionMakerTypeInGroup, short* taskId, short* field_10);
    int MakeDecision(CPedGroup* pPedGroup, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
        int taskId2, int taskId3, int taskId4);
    void AddEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventType, std::int32_t taskId, float* responseChances, std::int32_t* flags);
    void FlushDecisionMakerEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventId);
};
