#pragma once

class CPed;
class CPedGroup;

class CDecisionMakerTypesFileLoader
{
public:
    static void GetPedDMName(std::int32_t index, char* name);
    static void GetGrpDMName(std::int32_t index, char* name);
    static std::int32_t LoadDecisionMaker(const char* filepath, std::int8_t decisionMakerType, bool bUseMissionCleanup);
};

class CDecisionMakerTypes {
public:
    static CDecisionMakerTypes* GetInstance();
    void MakeDecision(CPed* ped, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
        int taskId2, int taskId3, int taskId4, bool bDecisionMakerTypeInGroup, short* taskId, short* field_10);
    int MakeDecision(CPedGroup* pPedGroup, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
        int taskId2, int taskId3, int taskId4);
    void AddEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventType, std::int32_t taskId, float* responseChances, std::int32_t* flags);
    void FlushDecisionMakerEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventId);
};
