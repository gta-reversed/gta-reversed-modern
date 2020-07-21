#include "StdInc.h"

void CDecisionMakerTypesFileLoader::GetPedDMName(std::int32_t index, char* name)
{
    plugin::Call<0x600860, std::int32_t, char*>(index, name);
}

void CDecisionMakerTypesFileLoader::GetGrpDMName(std::int32_t index, char* name)
{
    plugin::Call<0x600880, std::int32_t, char*>(index, name);
}

std::int32_t CDecisionMakerTypesFileLoader::LoadDecisionMaker(const char* filepath, std::int8_t decisionMakerType, bool bUseMissionCleanup)
{
    return plugin::CallAndReturn<std::int32_t, 0x607D30, const char*, std::int8_t, bool>(filepath, decisionMakerType, bUseMissionCleanup);
}

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

void CDecisionMakerTypes::AddEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventType, std::int32_t taskId, float* responseChances, std::int32_t* flags)
{
    plugin::CallMethod<0x6044C0, CDecisionMakerTypes*, std::int32_t, std::int32_t, std::int32_t, float*, std::int32_t*>
        (this, decisionMakerIndex, eventType, taskId, responseChances, flags);
}

void CDecisionMakerTypes::FlushDecisionMakerEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventId)
{
    plugin::CallMethod<0x604490, CDecisionMakerTypes*, std::int32_t, std::int32_t>(this, decisionMakerIndex, eventId);
}
