#pragma once

#include "CDecision.h"

class CPed;
class CPedGroup;
class CDecisionMaker;

class CDecisionMakerTypesFileLoader {
public:
    static void InjectHooks();

    static void GetPedDMName(int32 index, char* name);
    static void GetGrpDMName(int32 index, char* name);
    static void LoadDefaultDecisionMaker();
    static void LoadDecisionMaker(const char* filepath, eDecisionTypes decisionMakerType, bool bUseMissionCleanup);
    static void LoadDecisionMaker(const char* filepath, CDecisionMaker* decisionMaker);
};

class CDecisionMakerTypes {
public:
    static void InjectHooks();

    static void AddDecisionMaker(CDecisionMakerTypes* decisionMakerTypes, CDecisionMaker* decisionMaker, eDecisionTypes decisionMakerType, bool bUseMissionCleanup);
    static CDecisionMakerTypes* GetInstance();

    void MakeDecision(CPed* ped, int32 eventType, int32 eventSourceType, bool bIsPedInVehicle, int32 taskId1, int32 taskId2, int32 taskId3, int32 taskId4, bool bDecisionMakerTypeInGroup, int16* taskId, int16* field_10);
    int32 MakeDecision(CPedGroup* pPedGroup, int32 eventType, int32 eventSourceType, bool bIsPedInVehicle, int32 taskId1, int32 taskId2, int32 taskId3, int32 taskId4);
    void AddEventResponse(int32 decisionMakerIndex, int32 eventType, int32 taskId, float* responseChances, int32* flags);
    void FlushDecisionMakerEventResponse(int32 decisionMakerIndex, int32 eventId);
};
