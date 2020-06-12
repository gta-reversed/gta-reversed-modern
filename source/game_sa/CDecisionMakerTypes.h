#pragma once

class CPed;
class CPedGroup;

class CDecisionMakerTypes {
public:
    static CDecisionMakerTypes* GetInstance();
    void MakeDecision(CPed* ped, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
        int taskId2, int taskId3, int taskId4, bool bDecisionMakerTypeInGroup, short* taskId, short* field_10);
    int MakeDecision(CPedGroup* pPedGroup, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
        int taskId2, int taskId3, int taskId4);
};
