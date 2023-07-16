#include "StdInc.h"

#include "TheScripts.h"
#include "UpsideDownCarCheck.h"
#include "Lines.h"
#include "FireManager.h"
#include "PedGroups.h"
#include "Checkpoint.h"
#include "Checkpoints.h"
#include "LoadingScreen.h"
// #include "Scripted2dEffects.h"
#include "Shadows.h"

void CTheScripts::InjectHooks() {
    // Has to have these, because there seems to be something going on with the variable init order
    // For now I just changed it to use static addresses, not sure whats going on..
    assert((void*)0xA49960 == (void*)&MainSCMBlock[0]);
    assert((void*)(0xA7A6A0) == (void*)&MissionBlock[0]);

    RH_ScopedClass(CTheScripts);
    RH_ScopedCategory("Scripts");

    RH_ScopedInstall(Init, 0x468D50, { .reversed = false });
    RH_ScopedOverloadedInstall(StartNewScript, "", 0x464C20, CRunningScript* (*)(uint8*));
    // RH_ScopedOverloadedInstall(StartNewScript, "index", 0x464C90, CRunningScript* (*)(uint8*, uint16));
    RH_ScopedInstall(StartTestScript, 0x464D40);
    RH_ScopedInstall(AddToBuildingSwapArray, 0x481140);
    RH_ScopedInstall(UndoBuildingSwaps, 0x481290);
    RH_ScopedInstall(IsPedStopped, 0x486110);
    RH_ScopedInstall(HasCarModelBeenSuppressed, 0x46A810);
    RH_ScopedInstall(HasVehicleModelBeenBlockedByScript, 0x46A890);
    RH_ScopedInstall(Process, 0x46A000);
}

// 0x468D50
void CTheScripts::Init() {
    plugin::Call<0x468D50>();
}

// 0x470960
void CTheScripts::InitialiseAllConnectLodObjects() {
    for (auto& pair : ScriptConnectLodsObjects) {
        pair = tScriptConnectLodsObject(); // InitialiseConnectLodObjects();
    }
}

// 0x470940
void CTheScripts::InitialiseConnectLodObjects(uint16 index) {
    ScriptConnectLodsObjects[index] = tScriptConnectLodsObject();
}

// 0x474730
void CTheScripts::InitialiseSpecialAnimGroupsAttachedToCharModels() {
    for (auto& group : ScriptAttachedAnimGroups) {
        group = tScriptAttachedAnimGroup(); // InitialiseSpecialAnimGroup();
    }
}

// 0x474710
void CTheScripts::InitialiseSpecialAnimGroup(uint16 index) {
    ScriptAttachedAnimGroups[index] = tScriptAttachedAnimGroup();
}

// 0x486720
void CTheScripts::ReadObjectNamesFromScript() {
    plugin::Call<0x486720>();
}

// 0x486780
void CTheScripts::UpdateObjectIndices() {
    plugin::Call<0x486780>();
}

// 0x4867C0
void CTheScripts::ReadMultiScriptFileOffsetsFromScript() {
    plugin::Call<0x4867C0>();
}

// signature changed (CVector)
// 0x4935A0
uint32 CTheScripts::AddScriptCheckpoint(CVector at, CVector pointTo, float radius, int32 type) {
    return plugin::CallAndReturn<uint32, 0x4935A0, CVector, CVector, float, int32>(at, pointTo, radius, type);
}

// 0x492F90
uint32 CTheScripts::AddScriptEffectSystem(FxSystem_c* system) {
    return plugin::CallAndReturn<uint32, 0x492F90, FxSystem_c*>(system);
}

// signature changed (CVector)
// 0x493000
uint32 CTheScripts::AddScriptSearchLight(CVector start, CEntity* entity, CVector target, float targetRadius, float baseRadius) {
    return plugin::CallAndReturn<uint32, 0x493000, CVector, CEntity*, CVector, float, float>(start, entity, target, targetRadius, baseRadius);
}

// 0x483B30
uint32 CTheScripts::AddScriptSphere(uint32 id, CVector posn, float radius) {
    return plugin::CallAndReturn<uint32, 0x483B30, uint32, CVector, float>(id, posn, radius);
}

// 0x481140
void CTheScripts::AddToBuildingSwapArray(CBuilding* building, int32 oldModelId, int32 newModelId) {
    if (building->m_nIplIndex)
        return;

    for (auto& swap : BuildingSwapArray) {
        if (swap.m_pCBuilding == building) {
            if (newModelId == swap.m_nOldModelIndex) {
                swap.Clear();
            } else
                swap.m_nNewModelIndex = newModelId;

            return;
        }
    }

    for (auto& swap : BuildingSwapArray) {
        if (!swap.m_pCBuilding) {
            swap = tBuildingSwap(building, newModelId, oldModelId);
            return;
        }
    }
}

// 0x481200
void CTheScripts::AddToInvisibilitySwapArray(CEntity* entity, bool bVisible) {
    plugin::Call<0x481200, CEntity*, bool>(entity, bVisible);
}

// 0x470980
void CTheScripts::AddToListOfConnectedLodObjects(CObject* obj1, CObject* obj2) {
    plugin::Call<0x470980, CObject*, CObject*>(obj1, obj2);
}

// 0x474750
void CTheScripts::AddToListOfSpecialAnimGroupsAttachedToCharModels(int32 modelId, Const char* ifpName) {
    plugin::Call<0x474750, int32, const char*>(modelId, ifpName);
}

// 0x470390
void CTheScripts::AddToSwitchJumpTable(int32 switchValue, int32 switchLabelLocalAddress) {
    SwitchJumpTable[NumberOfEntriesInSwitchTable].m_nSwitchValue        = switchValue;
    SwitchJumpTable[NumberOfEntriesInSwitchTable].m_nSwitchLabelAddress = switchLabelLocalAddress;
    NumberOfEntriesInSwitchTable++;
}

// 0x46B200, unused | inlined?
void CTheScripts::AddToVehicleModelsBlockedByScript(int32 modelIndex) {

}

// 0x46AB60
void CTheScripts::AddToWaitingForScriptBrainArray(CEntity* entity, int16 specialModelIndex) {
    return plugin::Call<0x46AB60, CEntity*, int16>(entity, specialModelIndex);
}

// 0x4866C0
void CTheScripts::CleanUpThisObject(CObject* obj) {
    if (!obj)
        return;

    if (obj->IsMissionObject()) {
        obj->m_nObjectType    = OBJECT_TEMPORARY;
        obj->m_nRemovalTime   = CTimer::GetTimeInMS() + 200'00'000;
        obj->m_nRefModelIndex = -1;
        obj->objectFlags.bChangesVehColor = false;
        CObject::nNoTempObjects++;
    }
}

// 0x486300
void CTheScripts::CleanUpThisPed(CPed* ped) {
    plugin::Call<0x486300, CPed*>( ped);
}

// 0x486670
void CTheScripts::CleanUpThisVehicle(CVehicle* vehicle) {
    plugin::Call<0x486670, CVehicle*>(vehicle);
}

// 0x46A840
void CTheScripts::ClearAllVehicleModelsBlockedByScript() {
    memset(&VehicleModelsBlockedByScript, 255, sizeof(VehicleModelsBlockedByScript));
}

// 0x46A7C0
void CTheScripts::ClearAllSuppressedCarModels() {
    memset(&SuppressedVehicleModels, 255, sizeof(SuppressedVehicleModels));
}

// 0x486B00
void CTheScripts::ClearSpaceForMissionEntity(const CVector& pos, CEntity* entity) {
    plugin::Call<0x486B00, const CVector&, CEntity*>(pos, entity);
}

// 0x5D3390
void CTheScripts::DoScriptSetupAfterPoolsHaveLoaded() {
    plugin::Call<0x5D3390>();
}

// 0x4839A0
int32 CTheScripts::GetActualScriptThingIndex(int32 index, eScriptThingType type) {
    return plugin::CallAndReturn<int32, 0x4839A0, int32, eScriptThingType>(index, type);
}

// 0x483720
int32 CTheScripts::GetNewUniqueScriptThingIndex(int32 index, eScriptThingType type) {
    return plugin::CallAndReturn<uint32, 0x483720, int32, char>(index, type);
}

// 0x464D20
int32 CTheScripts::GetScriptIndexFromPointer(CRunningScript* thread) {
    return (thread - ScriptsArray.data()) / sizeof(CRunningScript);
}

/*!
 * @param type always SCRIPT_THING_PED_GROUP
 * @addr 0x4810C0
 */
int32 CTheScripts::GetUniqueScriptThingIndex(int32 playerGroup, eScriptThingType type) {
    switch (type) {
    /* Android
    case SCRIPT_THING_DECISION_MAKER:
        CDecisionMakerTypes::GetInstance();
        return playerGroup | (CDecisionMakerTypes::ScriptReferenceIndex[playerGroup] << 16);
    */
    case SCRIPT_THING_PED_GROUP:
        return playerGroup | (CPedGroups::ScriptReferenceIndex[playerGroup] << 16);
    default:
        return OR_INTERRUPT;
    }
}

// 0x470370
void CTheScripts::ReinitialiseSwitchStatementData() {
    NumberOfEntriesStillToReadForSwitch = 0;
    ValueToCheckInSwitchStatement       = 0;
    SwitchDefaultExists                 = false;
    SwitchDefaultAddress                = nullptr;
    NumberOfEntriesInSwitchTable        = 0;
}

// unused
// 0x?
void CTheScripts::RemoveFromVehicleModelsBlockedByScript(int32 modelIndex) {
    for (auto& script : VehicleModelsBlockedByScript) {
        // ?
    }
}

// 0x46ABC0
void CTheScripts::RemoveFromWaitingForScriptBrainArray(CEntity* entity, int16 modelIndex) {
    plugin::Call<0x46ABC0, CEntity*, int16>(entity, modelIndex);
}

// 0x4936C0
void CTheScripts::RemoveScriptCheckpoint(int32 scriptIndex) {
    plugin::Call<0x4936C0, int32>(scriptIndex);
}

// 0x492FD0
void CTheScripts::RemoveScriptEffectSystem(int32 scriptIndex) {
    plugin::Call<0x492FD0, int32>(scriptIndex);
}

// 0x493160
void CTheScripts::RemoveScriptSearchLight(int32 scriptIndex) {
    plugin::Call<0x493160, int32>(scriptIndex);
}

// 0x483BA0
void CTheScripts::RemoveScriptSphere(int32 scriptIndex) {
    plugin::Call<0x483BA0>();
}

// 0x465A40
void CTheScripts::RemoveScriptTextureDictionary() {
    plugin::Call<0x465A40>();
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
            swap.Clear();
        }
    }
}

// 0x486110
bool CTheScripts::IsPedStopped(CPed* ped) {
    if (ped->IsInVehicle()) {
        return CTimer::GetTimeStep() / 100.f >= ped->m_pVehicle->m_fMovingSpeed;
    }
    if (!ped->IsPedStandingInPlace()) {
        return false;
    }
    if (ped->IsPlayer()) {
        if (RpAnimBlendClumpGetAssociation(ped->m_pRwClump, { ANIM_ID_RUN_STOP, ANIM_ID_RUN_STOPR, ANIM_ID_JUMP_LAUNCH, ANIM_ID_JUMP_GLIDE })) {
            return false;
        }
    }
    if (ped->bIsLanding || ped->bIsInTheAir || !ped->bIsStanding) {
        return false;
    }
    if (ped->m_vecAnimMovingShiftLocal.IsZero()) {
        return true;
    }
    return false;
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
    memset(&LocalVariablesForCurrentMission, 0, sizeof(LocalVariablesForCurrentMission));
}

// 0x46A810
bool CTheScripts::HasCarModelBeenSuppressed(eModelID carModelId) {
    return notsa::contains(SuppressedVehicleModels, carModelId);
}

// 0x46A890
bool CTheScripts::HasVehicleModelBeenBlockedByScript(eModelID carModelId) {
    return notsa::contains(VehicleModelsBlockedByScript, carModelId);
}

// 0x464D40
void CTheScripts::StartTestScript() {
    ZoneScoped;

    StartNewScript(MainSCMBlock);
}

// 0x46A000
void CTheScripts::Process() {
    ZoneScoped;

    if (CReplay::Mode == MODE_PLAYBACK) {
        return;
    }

    CommandsExecuted = 0;

    UpsideDownCars.UpdateTimers();
    StuckCars.Process();
    MissionCleanUp.CheckIfCollisionHasLoadedForMissionObjects();
    CTheScripts::DrawScriptSpheres();
    CTheScripts::ProcessAllSearchLights();
    CTheScripts::ProcessWaitingForScriptBrainArray();

    if (CTheScripts::FailCurrentMission) {
        --CTheScripts::FailCurrentMission;
    }

    if (CTheScripts::UseTextCommands) {
        rng::fill(IntroTextLines, tScriptText{});
        NumberOfIntroTextLinesThisFrame = 0;

        rng::fill(IntroRectangles, tScriptRectangle{});
        NumberOfIntroRectanglesThisFrame = 0;

        CTheScripts::UseTextCommands = false;
    }

    const auto timeStepMS = (int32)CTimer::GetTimeStepInMS();
    LocalVariablesForCurrentMission[32].iParam += timeStepMS;
    LocalVariablesForCurrentMission[33].iParam += timeStepMS;

    CLoadingScreen::NewChunkLoaded();

    for (auto it = pActiveScripts; it;) {
        const auto next = it->m_pNext;

        for (auto& t : it->m_anTimers) {
            t += timeStepMS;
        }
        it->Process();

        it = next;
    }

    CLoadingScreen::NewChunkLoaded();

    for (auto& ped : GetPedPool()->GetAllValid()) {
        if (ped.IsCreatedByMission()) {
            ped.GetIntelligence()->RecordEventForScript(0, 0);
        }
    }
}

// 0x4939F0
void CTheScripts::ProcessAllSearchLights() {
    ZoneScoped;

    return plugin::Call<0x4939F0>();
}

void CTheScripts::ProcessWaitingForScriptBrainArray() {
    ZoneScoped;

    plugin::Call<0x46CF00>();
}

// 0x4812D0
void CTheScripts::UndoEntityInvisibilitySettings() {
    plugin::Call<0x4812D0>();
}

// 0x4646D0
void CTheScripts::PrintListSizes() {
    int active = 0;
    int idle = 0;

    for (CRunningScript* script = pActiveScripts; script; script = script->m_pNext) active++;
    for (CRunningScript* script = pIdleScripts; script; script = script->m_pNext) idle++;

    DEV_LOG("Scripts Active: {}, Idle: {}", active, idle);
}

uint32 DbgLineColour = 0x0000FFFF; // r = 0, g = 0, b = 255, a = 255

// Usage:
//  const auto pos = FindPlayerPed()->GetPosition() + CVector{ 0.0f, 0.f, 1.0f };
//  CTheScripts::DrawDebugSquare(pos.x + 5.f, pos.y, pos.x, pos.y + 5.f);
// 0x486840
void CTheScripts::DrawDebugSquare(float x1, float y1, float x2, float y2) {
    CColPoint colPoint{};
    CEntity*  colEntity;

    CVector p1 { x1, y1, -1000.0f };
    CWorld::ProcessVerticalLine(p1, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p1.z = colPoint.m_vecPoint.z + 2.0f;

    CVector p2 { x2, y1, -1000.0f };
    CWorld::ProcessVerticalLine(p2, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p2.z = colPoint.m_vecPoint.z + 2.0f;

    CVector p3 { x2, y2, -1000.0f };
    CWorld::ProcessVerticalLine(p3, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p3.z = colPoint.m_vecPoint.z + 2.0f;

    CVector p4 { x1, y2, -1000.0f };
    CWorld::ProcessVerticalLine(p4, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p4.z = colPoint.m_vecPoint.z + 2.0f; // FIX_BUGS: missing in original code 🤷

    ScriptDebugLine3D(p1, p2, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D(p2, p3, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D(p3, p4, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D(p4, p1, DbgLineColour, DbgLineColour);
}

// float infX, float infY, float sup.x, float supY, float rotSupX, float rotSupY, float rotInfX, float rotInfY
// 0x486990
void CTheScripts::DrawDebugAngledSquare(const CVector2D& inf, const CVector2D& sup, const CVector2D& rotSup, const CVector2D& rotInf) {
    CColPoint colPoint{};
    CEntity*  colEntity;

    CVector p1 { inf.x, inf.y, -1000.0f };
    CWorld::ProcessVerticalLine(p1, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p1.z = colPoint.m_vecPoint.z + 2.0f;

    CVector p2 { sup.x, sup.y, -1000.0f };
    CWorld::ProcessVerticalLine(p2, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p2.z = colPoint.m_vecPoint.z + 2.0f;

    CVector p3 { rotSup.x, rotSup.y, -1000.0f };
    CWorld::ProcessVerticalLine(p3, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p3.z = colPoint.m_vecPoint.z + 2.0f;

    CVector p4 { rotInf.x, rotInf.y, -1000.0f };
    CWorld::ProcessVerticalLine(p4, 1000.0f, colPoint, colEntity, true, false, false, false, true, false, nullptr);
    p4.z = colPoint.m_vecPoint.z + 2.0f;

    ScriptDebugLine3D(p1, p2, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D(p2, p3, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D(p3, p4, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D(p4, p1, DbgLineColour, DbgLineColour);
}

// (float infX, float infY, float infZ, float supX, float supY, float supZ)
void CTheScripts::DrawDebugCube(const CVector& inf, const CVector& sup) {
    ScriptDebugLine3D({ inf.x, inf.y, inf.z }, { sup.x, inf.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x, inf.y, inf.z }, { sup.x, sup.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x, sup.y, inf.z }, { inf.x, sup.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ inf.x, sup.y, inf.z }, { inf.x, inf.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ inf.x, inf.y, sup.z }, { sup.x, inf.y, sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x, inf.y, sup.z }, { sup.x, sup.y, sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x, sup.y, sup.z }, { inf.x, sup.y, sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ inf.x, sup.y, sup.z }, { inf.x, inf.y, sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ inf.x, inf.y, sup.z }, { inf.x, inf.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x, inf.y, sup.z }, { sup.x, inf.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x, sup.y, sup.z }, { sup.x, sup.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ inf.x, sup.y, sup.z }, { inf.x, sup.y, inf.z }, DbgLineColour, DbgLineColour);
}

// (float infX, float infY, float infZ, float supX, float supY, float supZ, float rotSup, float rotSup, float rotInf, float rotInf)
void CTheScripts::DrawDebugAngledCube(const CVector& inf, const CVector& sup, const CVector2D& rotSup, const CVector2D& rotInf) {
    ScriptDebugLine3D({ inf.x,    inf.y,    inf.z    }, { sup.x,    inf.y,    inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x,    inf.y,    inf.z    }, { rotSup.x, rotSup.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ rotSup.x, rotSup.y, inf.z    }, { rotInf.x, rotInf.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ rotInf.x, rotInf.y, inf.z    }, { inf.x,    inf.y,    inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ inf.x,    inf.y,    sup.z    }, { sup.x,    inf.y,    sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x,    inf.y,    sup.z    }, { rotSup.x, rotSup.y, sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ rotSup.x, rotSup.y, rotInf.x }, { rotInf.y, sup.y,    sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ rotInf.x, rotInf.y, sup.z    }, { inf.x,    inf.y,    sup.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ inf.x,    inf.y,    sup.z    }, { inf.x,    inf.y,    inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ sup.x,    inf.y,    sup.z    }, { sup.x,    inf.y,    inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ rotSup.x, rotSup.y, sup.z    }, { rotSup.x, rotSup.y, inf.z }, DbgLineColour, DbgLineColour);
    ScriptDebugLine3D({ rotInf.x, rotInf.y, sup.z    }, { rotInf.x, rotInf.y, inf.z }, DbgLineColour, DbgLineColour);
}

// 0x464980
void CTheScripts::DrawScriptSpritesAndRectangles(bool bDrawBeforeFade) {
    return plugin::Call<0x464980, bool>(bDrawBeforeFade);
}

// Usage:
//   const auto pos = FindPlayerPed()->GetPosition() + CVector{ 0.0f, 0.f, 1.0f };
//   CTheScripts::ScriptDebugCircle2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 50.f, 50.f, HudColour.GetRGB(HUD_COLOUR_RED).ToInt());
// 0x485C20
void CTheScripts::ScriptDebugCircle2D(float x, float y, float width, float height, CRGBA color) {
    return plugin::Call<0x485C20, float, float, float, float, CRGBA>(x, y, width, height, color);

    // untested
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,     RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));

    const auto iters = 16;
    auto part = (CTimer::GetTimeInMS() >> 6) % iters;
    for (auto i = 0; i < iters; i++) {
        RwIm2DVertex vertex{
            .x = std::sin((float)i * PI / 8.0f) * width + x,
            .y = std::cos((float)i * PI / 8.0f) * height + y
        };
        if (part == i)
            vertex.emissiveColor = (3 * color.g / 4) | (((3 * color.b / 4) | (((3 * color.a / 4) | ((3 * color.r / 4) << 8)) << 8)) << 8); // todo: (3 * color / 4).ToIntARGB();
        else
            vertex.emissiveColor = color.ToIntARGB();
        RwIm2DVertex vertices[2] = { vertex, vertex };
        RwIm2DRenderLine(vertices, std::size(vertices), 0, 1); // todo: RwIm2DRenderLine_BUGFIX
    }

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
}

// 0x4810E0
void CTheScripts::DrawScriptSpheres() {
    ZoneScoped;

    return plugin::Call<0x4810E0>();
    for (auto& script : ScriptSphereArray) {
        if (script.m_bUsed) {
            /* todo:
            C3dMarkers::PlaceMarkerSet(
                script.nId,
                MARKER3D_CYLINDER,
                script.vCoords,
                script.fRadius,
                SPHERE_MARKER_R, SPHERE_MARKER_G, SPHERE_MARKER_B, SPHERE_MARKER_A,
                SPHERE_MARKER_PULSE_PERIOD,
                SPHERE_MARKER_PULSE_FRACTION,
                0
            );
            */
        }
    }
}

// 0x485E00
void CTheScripts::HighlightImportantArea(uint32 id, float x1, float y1, float x2, float y2, float z) {
    CVector2D inf, sup;
    if (x1 < x2) {
        inf.x = x1;
        sup.x = x2;
    } else {
        inf.x = x2;
        sup.x = x1;
    }

    if (y1 < y2) {
        inf.y = y1;
        sup.y = y2;
    } else {
        inf.y = y2;
        sup.y = y1;
    }

    CVector center;
    center.x = (inf.x + sup.x) / 2;
    center.y = (inf.y + sup.y) / 2;
    center.z = (z <= MAP_Z_LOW_LIMIT) ? CWorld::FindGroundZForCoord(center.x, center.y) : z;
    CShadows::RenderIndicatorShadow(id, SHADOW_ADDITIVE, nullptr, center, sup.x - center.x, 0.0f, 0.0f, center.y - sup.y, 0);
}

// 0x485EF0
void CTheScripts::HighlightImportantAngledArea(uint32 id, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float z) {
    CVector2D inf, sup;
    float x, y;

    x = (x1 + x2) / 2;
    y = (y1 + y2) / 2;
    sup.x = inf.x = x;
    sup.y = inf.y = y;

    x = (x2 + x3) / 2;
    y = (y2 + y3) / 2;
    inf.x = std::min(inf.x, x);
    sup.x = std::max(sup.x, x);
    inf.y = std::min(inf.y, y);
    sup.y = std::max(sup.y, y);

    x = (x3 + x4) / 2;
    y = (y3 + y4) / 2;
    inf.x = std::min(inf.x, x);
    sup.x = std::max(sup.x, x);
    inf.y = std::min(inf.y, y);
    sup.y = std::max(sup.y, y);

    x = (x4 + x1) / 2;
    y = (y4 + y1) / 2;
    inf.x = std::min(inf.x, x);
    sup.x = std::max(sup.x, x);
    inf.y = std::min(inf.y, y);
    sup.y = std::max(sup.y, y);

    CVector center;
    center.x = (inf.x + sup.x) / 2;
    center.y = (inf.y + sup.y) / 2;
    center.z = (z <= MAP_Z_LOW_LIMIT) ? CWorld::FindGroundZForCoord(center.x, center.y) : z;
    CShadows::RenderIndicatorShadow(id, SHADOW_ADDITIVE, nullptr, &center, sup.x - center.x, 0.0f, 0.0f, center.y - sup.y, 0);
}

static uint16 NumScriptDebugLines;
static tStoredLine aStoredLines[MAX_NUM_STORED_LINES];

// 0x485DE0
void CTheScripts::ScriptDebugLine3D(const CVector& start, const CVector& end, uint32 color1, uint32 color2) {
#ifndef FINAL
    if (NumScriptDebugLines >= MAX_NUM_STORED_LINES)
        return;

    auto& line = aStoredLines[NumScriptDebugLines];
    line.vecInf = start;
    line.vecSup = end;
    line.color1 = color1;
    line.color2 = color2;
    NumScriptDebugLines++;
#endif
}

// 0x0 NOP
void CTheScripts::RenderTheScriptDebugLines() {
#ifndef FINAL
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(TRUE));
    for (auto& line : std::span{ aStoredLines, NumScriptDebugLines }) {
        CLines::RenderLineWithClipping(line.vecInf, line.vecSup, line.color1, line.color2);
    }
    NumScriptDebugLines = 0;
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
#endif
}

// 0x493E30
void CTheScripts::RenderAllSearchLights() {
    ZoneScoped;

    return plugin::Call<0x493E30>();
}
