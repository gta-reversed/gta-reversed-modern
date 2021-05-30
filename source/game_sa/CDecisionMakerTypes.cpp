#include "StdInc.h"

void CDecisionMakerTypesFileLoader::InjectHooks() {

}

// 0x600860
void CDecisionMakerTypesFileLoader::GetPedDMName(std::int32_t index, char* name)
{
    plugin::Call<0x600860, std::int32_t, char*>(index, name);
}

// 0x600880
void CDecisionMakerTypesFileLoader::GetGrpDMName(std::int32_t index, char* name)
{
    plugin::Call<0x600880, std::int32_t, char*>(index, name);
}

// 0x5BF400
void CDecisionMakerTypesFileLoader::LoadDefaultDecisionMaker() {
    plugin::Call<0x5BF400>();
}

// 0x607D30
void CDecisionMakerTypesFileLoader::LoadDecisionMaker(const char* filepath, eDecisionTypes decisionMakerType, bool bUseMissionCleanup)
{
    CDecisionMaker decisionMaker;
    LoadDecisionMaker(filepath, &decisionMaker);
    CDecisionMakerTypes* pDecisionMakerTypes = CDecisionMakerTypes::GetInstance();
    CDecisionMakerTypes::AddDecisionMaker(pDecisionMakerTypes, &decisionMaker, decisionMakerType, bUseMissionCleanup);
}

// 0x6076B0
void CDecisionMakerTypesFileLoader::LoadDecisionMaker(const char *filepath, CDecisionMaker* decisionMaker) {
    plugin::Call<0x6076B0, const char*, CDecisionMaker*>(filepath, decisionMaker);
}

void CDecisionMakerTypes::InjectHooks() {

}

// 0x607050
void CDecisionMakerTypes::AddDecisionMaker(CDecisionMakerTypes* decisionMakerTypes, CDecisionMaker* decisionMaker, eDecisionTypes decisionMakerType, bool bUseMissionCleanup) {
    plugin::Call<0x607050, CDecisionMakerTypes*, CDecisionMaker*, eDecisionTypes, bool>(decisionMakerTypes, decisionMaker, decisionMakerType, bUseMissionCleanup);
}

// 0x4684F0
CDecisionMakerTypes* CDecisionMakerTypes::GetInstance() {
    return plugin::CallAndReturn<CDecisionMakerTypes*, 0x4684F0>();
}

// 0x606E70
void CDecisionMakerTypes::MakeDecision(CPed* ped, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1,
    int taskId2, int taskId3, int taskId4, bool bDecisionMakerTypeInGroup, short* taskId, short* field_10)
{
    plugin::CallMethod<0x606E70, CDecisionMakerTypes*, CPed*, int, int, bool, int, int, int, int, bool, short*, short*>
        (this, ped, eventType, eventSourceType, bIsPedInVehicle, taskId1, taskId2, taskId3, taskId4, bDecisionMakerTypeInGroup, taskId, field_10);
}

// 0x606F80
int CDecisionMakerTypes::MakeDecision(CPedGroup* pPedGroup, int eventType, int eventSourceType, bool bIsPedInVehicle, int taskId1, int taskId2, int taskId3, int taskId4) {
    return plugin::CallMethodAndReturn <int, 0x606F80, CDecisionMakerTypes*, CPedGroup*, int, int, bool, int, int, int, int>
        (this, pPedGroup, eventType, eventSourceType, bIsPedInVehicle, taskId1, taskId2, taskId3, taskId4);
}

// 0x6044C0
void CDecisionMakerTypes::AddEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventType, std::int32_t taskId, float* responseChances, std::int32_t* flags)
{
    plugin::CallMethod<0x6044C0, CDecisionMakerTypes*, std::int32_t, std::int32_t, std::int32_t, float*, std::int32_t*>
        (this, decisionMakerIndex, eventType, taskId, responseChances, flags);
}

// 0x604490
void CDecisionMakerTypes::FlushDecisionMakerEventResponse(std::int32_t decisionMakerIndex, std::int32_t eventId)
{
    plugin::CallMethod<0x604490, CDecisionMakerTypes*, std::int32_t, std::int32_t>(this, decisionMakerIndex, eventId);
}
