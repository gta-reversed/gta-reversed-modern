/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "TheScripts.h"
#include "UpsideDownCarCheck.h"

void CTheScripts::InjectHooks() {
    RH_ScopedClass(CTheScripts);
    RH_ScopedCategory("Scripts");

    // RH_ScopedInstall(Init, 0x468D50);
    RH_ScopedOverloadedInstall(StartNewScript, "", 0x464C20, CRunningScript* (*)(uint8*));
    // RH_ScopedOverloadedInstall(StartNewScript, "index", 0x464C90, CRunningScript* (*)(uint8*, uint16));
    RH_ScopedInstall(StartTestScript, 0x464D40);
    RH_ScopedInstall(AddToBuildingSwapArray, 0x481140);
    RH_ScopedInstall(UndoBuildingSwaps, 0x481290);
}

// 0x468D50
void CTheScripts::Init() {
    plugin::Call<0x468D50>();
}

void CTheScripts::AddToBuildingSwapArray(CBuilding* building, int32 oldModelId, int32 newModelId) {
    if (building->m_nIplIndex)
        return;

    for (auto& swap : BuildingSwapArray) {
        if (swap.m_pCBuilding == building) {
            if (newModelId == swap.m_nOldModelIndex) {
                swap.m_pCBuilding = nullptr;
                swap.m_nOldModelIndex = -1;
                swap.m_nNewModelIndex = -1;
            } else
                swap.m_nNewModelIndex = newModelId;

            return;
        }
    }

    for (auto& swap : BuildingSwapArray) {
        if (!swap.m_pCBuilding) {
            swap.m_pCBuilding = building;
            swap.m_nOldModelIndex = oldModelId;
            swap.m_nNewModelIndex = newModelId;
            return;
        }
    }
}

// 0x486670
void CTheScripts::CleanUpThisVehicle(CVehicle* vehicle) {
    plugin::Call<0x486670, CVehicle*>(vehicle);
}

// 0x486B00
void CTheScripts::ClearSpaceForMissionEntity(const CVector& pos, CEntity* entity) {
    plugin::Call<0x486B00, const CVector&, CEntity*>(pos, entity);
}

void CTheScripts::DoScriptSetupAfterPoolsHaveLoaded() {
    plugin::Call<0x5D3390>();
}

// 0x4839A0
int32 CTheScripts::GetActualScriptThingIndex(int32 index, uint8 type) {
    return plugin::CallAndReturn<int32, 0x4839A0, int32, uint8>(index, type);
}

// 0x483720
uint32 CTheScripts::GetNewUniqueScriptThingIndex(uint32 index, char type) {
    return plugin::CallAndReturn<uint32, 0x483720, uint32, char>(index, type);
}

// 0x464D20
int32 CTheScripts::GetScriptIndexFromPointer(CRunningScript* thread) {
    return (thread - CTheScripts::ScriptsArray) / sizeof(CRunningScript);
}

// 0x470370
void CTheScripts::ReinitialiseSwitchStatementData() {
    NumberOfEntriesStillToReadForSwitch = 0;
    ValueToCheckInSwitchStatement       = 0;
    SwitchDefaultExists                 = false;
    SwitchDefaultAddress                = nullptr;
    NumberOfEntriesInSwitchTable        = 0;
}

// 0x46ABC0
int32 CTheScripts::RemoveFromWaitingForScriptBrainArray(CEntity* a1, int16 modelIndex) {
    return plugin::CallAndReturn<int32, 0x46ABC0, CEntity*, int16>(a1, modelIndex);
}

// 0x486240
void CTheScripts::RemoveThisPed(CPed* ped) {
    plugin::Call<0x486240, CPed*>( ped);
}

// 0x464C20
CRunningScript* CTheScripts::StartNewScript(uint8* startIP) {
    CRunningScript* script = pIdleScripts;

    script->RemoveScriptFromList(&pIdleScripts);
    script->Init();
    script->SetCurrentIp(startIP);
    script->AddScriptToList(&pActiveScripts);
    script->SetActive(true);

    return script;
}

// 0x464C90
CRunningScript* StartNewScript(uint8* startIP, uint16 index) {
    return plugin::CallAndReturn<CRunningScript*, 0x464C90, uint8*, uint16>(startIP, index);
}

void CTheScripts::UndoBuildingSwaps() {
    for (auto& swap : BuildingSwapArray) {
        if (swap.m_pCBuilding) {
            swap.m_pCBuilding->ReplaceWithNewModel(swap.m_nOldModelIndex);
            swap.m_pCBuilding = nullptr;
            swap.m_nOldModelIndex = -1;
            swap.m_nNewModelIndex = -1;
        }
    }
}

// 0x464D50
bool CTheScripts::IsPlayerOnAMission() {
    return plugin::CallAndReturn<bool, 0x464D50>();
}

// 0x4861F0
bool CTheScripts::IsVehicleStopped(CVehicle* vehicle) {
    return plugin::CallAndReturn<bool, 0x4861F0, CVehicle*>(vehicle);
}

// 0x5D4FD0
bool CTheScripts::Load() {
    return plugin::CallAndReturn<bool, 0x5D4FD0>();
}

// 0x5D4C40
bool CTheScripts::Save() {
    return plugin::CallAndReturn<bool, 0x5D4C40>();
}

// 0x464BB0
void CTheScripts::WipeLocalVariableMemoryForMissionScript() {
    plugin::Call<0x464BB0>();
}

// 0x464D40
void CTheScripts::StartTestScript() {
    StartNewScript(ScriptSpace);
}

// 0x46A000
void CTheScripts::Process() {
    plugin::Call<0x46A000>();
}

// 0x4812D0
void CTheScripts::UndoEntityInvisibilitySettings() {
    plugin::Call<0x4812D0>();
}
