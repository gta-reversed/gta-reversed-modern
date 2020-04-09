#include "StdInc.h"

CDecisionMakerTypes* CDecisionMakerTypes::GetInstance() {
    return plugin::CallAndReturn<CDecisionMakerTypes*, 0x4684F0>();
}

void CDecisionMakerTypes::MakeDecision(CPed* ped, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
    int taskId2, int taskId3, int taskId4, bool bDecisionMakerTypeInGroup, short* taskId, short* field_10) {
    plugin::CallMethod<0x606E70, CDecisionMakerTypes*, CPed*, int, int, bool, int, int, int, int, bool, short*, short*>
        (this, ped, eventType, eventSourceType, bIsPedInVehicle, taskId1, taskId2, taskId3, taskId4, bDecisionMakerTypeInGroup, taskId, field_10);
}

int CDecisionMakerTypes::MakeDecision(CPedGroup* pPedGroup, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
    int taskId2, int taskId3, int taskId4) {
    return plugin::CallMethodAndReturn <int, 0x606F80, CDecisionMakerTypes*, CPedGroup*, int, int, bool, int, int, int, int>
        (this, pPedGroup, eventType, eventSourceType, bIsPedInVehicle, taskId1, taskId2, taskId3, taskId4);
}