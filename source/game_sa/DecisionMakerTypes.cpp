#include "StdInc.h"

#include "DecisionMakerTypes.h"

void CDecisionMakerTypesFileLoader::InjectHooks() {
    RH_ScopedClass(CDecisionMakerTypesFileLoader);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(ReStart, 0x607D00, {.reversed = false});
    RH_ScopedInstall(GetPedDMName, 0x600860, {.reversed = false});
    RH_ScopedInstall(GetGrpDMName, 0x600880, {.reversed = false});
    RH_ScopedInstall(LoadDefaultDecisionMaker, 0x5BF400, {.reversed = false});
    RH_ScopedOverloadedInstall(LoadDecisionMaker, "enum", 0x607D30, void(*)(const char*, eDecisionTypes, bool));
    RH_ScopedOverloadedInstall(LoadDecisionMaker, "ptr", 0x6076B0, void (*)(const char*, CDecisionMaker*), {.reversed = false});
}

// 0x607D00
void CDecisionMakerTypesFileLoader::ReStart() {
    plugin::Call<0x607D00>();
}

// 0x600860
void CDecisionMakerTypesFileLoader::GetPedDMName(int32 index, char* name) {
    plugin::Call<0x600860, int32, char*>(index, name);
}

// 0x600880
void CDecisionMakerTypesFileLoader::GetGrpDMName(int32 index, char* name) {
    plugin::Call<0x600880, int32, char*>(index, name);
}

// 0x5BF400
void CDecisionMakerTypesFileLoader::LoadDefaultDecisionMaker() {
    plugin::Call<0x5BF400>();
}

// 0x607D30
void CDecisionMakerTypesFileLoader::LoadDecisionMaker(const char* filepath, eDecisionTypes decisionMakerType, bool bUseMissionCleanup) {
    CDecisionMaker decisionMaker;
    LoadDecisionMaker(filepath, &decisionMaker);
    CDecisionMakerTypes::GetInstance()->AddDecisionMaker(&decisionMaker, decisionMakerType, bUseMissionCleanup);
}

// 0x6076B0
void CDecisionMakerTypesFileLoader::LoadDecisionMaker(const char* filepath, CDecisionMaker* decisionMaker) {
    plugin::Call<0x6076B0, const char*, CDecisionMaker*>(filepath, decisionMaker);
}

void CDecisionMakerTypes::InjectHooks() {
    RH_ScopedClass(CDecisionMakerTypes);
    RH_ScopedCategoryGlobal();
}

// 0x607050
void CDecisionMakerTypes::AddDecisionMaker(CDecisionMaker* decisionMaker, eDecisionTypes decisionMakerType, bool bUseMissionCleanup) {
    plugin::CallMethod<0x607050, CDecisionMakerTypes*, CDecisionMaker*, eDecisionTypes, bool>(this, decisionMaker, decisionMakerType, bUseMissionCleanup);
}

// 0x4684F0
CDecisionMakerTypes* CDecisionMakerTypes::GetInstance() {
    return plugin::CallAndReturn<CDecisionMakerTypes*, 0x4684F0>();
}

// 0x606E70
void CDecisionMakerTypes::MakeDecision(CPed* ped, int32 eventType, int32 eventSourceType, bool bIsPedInVehicle, int32 taskId1, int32 taskId2, int32 taskId3, int32 taskId4,
                                       bool bInGroup, int16& taskId, int16& field_10) {
    plugin::CallMethod<0x606E70, CDecisionMakerTypes*, CPed*, int32, int32, bool, int32, int32, int32, int32, bool, int16&, int16&>(
        this, ped, eventType, eventSourceType, bIsPedInVehicle, taskId1, taskId2, taskId3, taskId4, bInGroup, taskId, field_10);
}

// 0x606F80
int32 CDecisionMakerTypes::MakeDecision(CPedGroup* pedGroup, int32 eventType, int32 eventSourceType, bool bIsPedInVehicle, int32 taskId1, int32 taskId2, int32 taskId3,
                                        int32 taskId4) {
    return plugin::CallMethodAndReturn<int32, 0x606F80, CDecisionMakerTypes*, CPedGroup*, int32, int32, bool, int32, int32, int32, int32>(
        this, pedGroup, eventType, eventSourceType, bIsPedInVehicle, taskId1, taskId2, taskId3, taskId4);
}

// 0x6044C0
void CDecisionMakerTypes::AddEventResponse(int32 decisionMakerIndex, int32 eventType, int32 taskId, float* responseChances, int32* flags) {
    plugin::CallMethod<0x6044C0, CDecisionMakerTypes*, int32, int32, int32, float*, int32*>(this, decisionMakerIndex, eventType, taskId, responseChances, flags);
}

// 0x604490
void CDecisionMakerTypes::FlushDecisionMakerEventResponse(int32 decisionMakerIndex, int32 eventId) {
    plugin::CallMethod<0x604490, CDecisionMakerTypes*, int32, int32>(this, decisionMakerIndex, eventId);
}
