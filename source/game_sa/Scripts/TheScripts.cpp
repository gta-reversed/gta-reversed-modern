#include "StdInc.h"

#include "TheScripts.h"
#include "UpsideDownCarCheck.h"
#include "Lines.h"
#include "FireManager.h"
#include "PedGroups.h"
#include "Checkpoint.h"
#include "Checkpoints.h"
#include "LoadingScreen.h"
#include "Scripted2dEffects.h"
#include "Shadows.h"
#include "VehicleRecording.h"

static inline bool gAllowScriptedFixedCameraCollision = false;

void CTheScripts::InjectHooks() {
    // Has to have these, because there seems to be something going on with the variable init order
    // For now I just changed it to use static addresses, not sure whats going on..
    assert((void*)0xA49960 == (void*)&MainSCMBlock[0]);
    assert((void*)(0xA7A6A0) == (void*)&MissionBlock[0]);

    RH_ScopedClass(CTheScripts);
    RH_ScopedCategory("Scripts");

    RH_ScopedInstall(Init, 0x468D50, { .reversed = true });
    RH_ScopedOverloadedInstall(StartNewScript, "last-idle", 0x464C20, CRunningScript* (*)(uint8*));
    RH_ScopedOverloadedInstall(StartNewScript, "indexed", 0x464C90, CRunningScript* (*)(uint8*, uint16));
    RH_ScopedInstall(StartTestScript, 0x464D40);
    RH_ScopedInstall(AddToBuildingSwapArray, 0x481140);
    RH_ScopedInstall(UndoBuildingSwaps, 0x481290);
    RH_ScopedInstall(IsPedStopped, 0x486110);
    RH_ScopedInstall(HasCarModelBeenSuppressed, 0x46A810);
    RH_ScopedInstall(HasVehicleModelBeenBlockedByScript, 0x46A890);
    RH_ScopedInstall(Process, 0x46A000);

    RH_ScopedInstall(ProcessAllSearchLights, 0x4939F0);

    RH_ScopedInstall(InitialiseAllConnectLodObjects, 0x470960);
    RH_ScopedInstall(InitialiseConnectLodObjects, 0x470940);
    RH_ScopedInstall(InitialiseSpecialAnimGroupsAttachedToCharModels, 0x474730);
    RH_ScopedInstall(InitialiseSpecialAnimGroup, 0x474710);

    RH_ScopedInstall(AddToSwitchJumpTable, 0x470390);
    RH_ScopedInstall(AddToVehicleModelsBlockedByScript, 0x46B200);

    RH_ScopedInstall(CleanUpThisObject, 0x4866C0);
    RH_ScopedInstall(CleanUpThisPed, 0x486300, {.reversed = false});
    RH_ScopedInstall(CleanUpThisVehicle, 0x486670, {.reversed = true});
    RH_ScopedInstall(ClearAllVehicleModelsBlockedByScript, 0x46A840);
    RH_ScopedInstall(ClearAllSuppressedCarModels, 0x46A7C0);
    RH_ScopedInstall(ClearSpaceForMissionEntity, 0x486B00, {.reversed = false});
    RH_ScopedInstall(WipeLocalVariableMemoryForMissionScript, 0x464BB0);

    RH_ScopedInstall(GetActualScriptThingIndex, 0x4839A0, {.reversed = false});
    RH_ScopedInstall(GetNewUniqueScriptThingIndex, 0x483720, {.reversed = false});
    RH_ScopedInstall(GetScriptIndexFromPointer, 0x464D20);
    RH_ScopedInstall(GetUniqueScriptThingIndex, 0x4810C0);

    RH_ScopedInstall(RemoveFromWaitingForScriptBrainArray, 0x46ABC0);
    RH_ScopedInstall(RemoveScriptCheckpoint, 0x4936C0);
    RH_ScopedInstall(RemoveScriptEffectSystem, 0x492FD0);
    RH_ScopedInstall(RemoveScriptSearchLight, 0x493160);
    RH_ScopedInstall(RemoveScriptSphere, 0x483BA0);
    RH_ScopedInstall(RemoveScriptTextureDictionary, 0x465A40);
    RH_ScopedInstall(RemoveThisPed, 0x486240);

    RH_ScopedInstall(ReadObjectNamesFromScript, 0x486720);
    RH_ScopedInstall(UpdateObjectIndices, 0x486780);

    RH_ScopedInstall(DrawScriptSpheres, 0x4810E0);

    RH_ScopedInstall(UndoEntityInvisibilitySettings, 0x4812D0);

    RH_ScopedInstall(IsPlayerOnAMission, 0x464D50);
    RH_ScopedInstall(IsVehicleStopped, 0x4861F0);
}

// 0x468D50
void CTheScripts::Init() {
    rng::fill(ScriptSpace, 0u);
    rng::fill(LocalVariablesForCurrentMission, tScriptParam{});

    CRunningScript* nextScript = nullptr;
    for (auto& script : ScriptsArray) {
        script.Init();
        script.m_pPrev = nullptr;
        script.m_pNext = nextScript;

        if (nextScript) {
            nextScript->m_pPrev = &script;
        }
        nextScript = &script;
    }
    pActiveScripts = nullptr;
    pIdleScripts   = nextScript;

    MissionCleanUp.Init();
    UpsideDownCars.Init();
    StuckCars.Init();
    ScriptsForBrains.Init();
    ScriptResourceManager.Initialise();
    rng::fill(EntitiesWaitingForScriptBrain, tScriptBrainWaitEntity{});

    if (CGame::bMissionPackGame) {
        while (FrontEndMenuManager.CheckMissionPackValidMenu()) {
            CFileMgr::SetDirMyDocuments();
            //notsa::format_to_sz(gString, "MPACK//MPACK{:d}//SCR.SCM", CGame::bMissionPackGame);
            const auto scr = std::format("MPACK//MPACK{:d}//SCR.SCM", CGame::bMissionPackGame);

            if (const auto file = CFileMgr::OpenFile(scr.c_str(), "rb")) {
                const auto read = CFileMgr::Read(file, ScriptSpace.data(), MAIN_SCRIPT_SIZE);
                CFileMgr::CloseFile(file);

                if (read >= 1) {
                    break;
                }
            }
        }
    } else {
        CFileMgr::SetDir("data\\script");

        const auto file = CFileMgr::OpenFile("main.scm", "rb");
        VERIFY(CFileMgr::Read(file, ScriptSpace.data(), MAIN_SCRIPT_SIZE) >= 1);
        CFileMgr::CloseFile(file);
    }
    CFileMgr::SetDir("");

    StoreVehicleIndex     = -1;
    StoreVehicleWasRandom = true;
    OnAMissionFlag        = false;
    LastMissionPassedTime = -1;
    LastRandomPedId       = -1;

    rng::fill(UsedObjectArray, tUsedObject{});
    ReadObjectNamesFromScript();
    UpdateObjectIndices();
    rng::fill(MultiScriptArray, 0u);
    NumberOfUsedObjects                        = 0;
    bAlreadyRunningAMissionScript              = 0;
    bUsingAMultiScriptFile                     = 1;
    MainScriptSize                             = 0;
    LargestMissionScriptSize                   = 0;
    NumberOfMissionScripts                     = 0;
    NumberOfExclusiveMissionScripts            = 0;
    LargestNumberOfMissionScriptLocalVariables = 0;

    ReadMultiScriptFileOffsetsFromScript();
    if (!CGame::bMissionPackGame) {
        StreamedScripts.ReadStreamedScriptData();
    }

    ForceRandomCarModel                    = -1;
    FailCurrentMission                     = 0;
    ScriptPickupCycleIndex                 = 0;
    bMiniGameInProgress                    = false;
    bDisplayNonMiniGameHelpMessages        = true;
    bPlayerHasMetDebbieHarry               = false;
    RiotIntensity                          = 0;
    bPlayerIsOffTheMap                     = false;
    RadarZoomValue                         = 0;
    RadarShowBlipOnAllLevels               = false;
    HideAllFrontEndMapBlips                = false;
    bDisplayHud                            = true;
    fCameraHeadingWhenPlayerIsAttached     = 0.0f;
    fCameraHeadingStepWhenPlayerIsAttached = 0.0f;
    bEnableCraneRaise                      = true;
    bEnableCraneLower                      = true;
    bEnableCraneRelease                    = true;
    bDrawCrossHair                         = eCrossHairType::NONE;
    gAllowScriptedFixedCameraCollision     = false;
    bAddNextMessageToPreviousBriefs        = true;
    bScriptHasFadedOut                     = false;
    bDrawOddJobTitleBeforeFade             = true;
    bDrawSubtitlesBeforeFade               = true;

    rng::fill(ScriptSphereArray, tScriptSphere{});
    rng::fill(IntroTextLines, tScriptText{});

    NumberOfIntroTextLinesThisFrame = 0;
    UseTextCommands                 = false;
    bUseMessageFormatting           = false;
    MessageCentre                   = 0;
    MessageWidth                    = 0;

    rng::fill(IntroRectangles, tScriptRectangle{});
    NumberOfIntroRectanglesThisFrame = 0;

    RemoveScriptTextureDictionary();

    rng::fill(BuildingSwapArray, tBuildingSwap{});
    rng::fill(InvisibilitySettingArray, nullptr);
    ClearAllSuppressedCarModels();
    ClearAllVehicleModelsBlockedByScript();
    InitialiseAllConnectLodObjects();
    InitialiseSpecialAnimGroupsAttachedToCharModels();
    rng::fill(ScriptEffectSystemArray, tScriptEffectSystem{});
    rng::fill(ScriptSearchLightArray, tScriptSearchlight{});
    NumberOfScriptSearchLights = 0;
    rng::fill(ScriptCheckpointArray, tScriptCheckpoint{});
    NumberOfScriptCheckpoints = 0;
    rng::fill(ScriptSequenceTaskArray, tScriptSequence{});

    CScripted2dEffects::Init();
    CTaskSequences::Init();
    CPedGroups::Init();
    CInformFriendsEventQueue::Init();
    CInformGroupEventQueue::Init();
    CDecisionMakerTypes::GetInstance();

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
    const auto scriptInfoOffset = notsa::ReadAs<uint32>(&ScriptSpace[3]);

    // TODO: Make a helper structure
    NumberOfUsedObjects = notsa::ReadAs<uint16>(&ScriptSpace[scriptInfoOffset + 8]);
    const auto* objNames = reinterpret_cast<char*>(&ScriptSpace[scriptInfoOffset + 12]);

    for (auto& obj : UsedObjectArray) {
        obj.nModelIndex = 0; // To be updated via UpdateObjectIndices.
        std::memcpy(obj.szModelName, objNames, sizeof(obj.szModelName));

        objNames += sizeof(obj.szModelName);
    }
}

// 0x486780
void CTheScripts::UpdateObjectIndices() {
    // NOTE: We drop the first because first entry has an empty name in vanilla,
    // so we ignore it?
    for (auto& obj : UsedObjectArray | std::views::drop(1)) {
        CModelInfo::GetModelInfo(obj.szModelName, &obj.nModelIndex);
    }
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
void CTheScripts::AddToVehicleModelsBlockedByScript(eModelID modelIndex) {
    if (notsa::contains(VehicleModelsBlockedByScript, modelIndex)) {
        return;
    }

    auto free = rng::find(VehicleModelsBlockedByScript, MODEL_INVALID);
    if (free == VehicleModelsBlockedByScript.end()) {
        // In vanilla, game chooses the last index to be filled, probably unwanted.
        NOTSA_UNREACHABLE();
    }

    *free = modelIndex;
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
    //plugin::Call<0x486670, CVehicle*>(vehicle);
    if (!vehicle || vehicle->m_nCreatedBy != eVehicleCreatedBy::MISSION_VEHICLE) {
        return;
    }

    vehicle->physicalFlags.bDontApplySpeed        = false;
    vehicle->physicalFlags.bDisableCollisionForce = false;
    vehicle->vehicleFlags.bIsLocked               = false;

    CCarCtrl::RemoveFromInterestingVehicleList(vehicle);
    CVehicleRecording::StopPlaybackRecordedCar(vehicle);
    vehicle->SetVehicleCreatedBy(eVehicleCreatedBy::RANDOM_VEHICLE);
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
// TODO: TEST REFACTOR!
int32 CTheScripts::GetNewUniqueScriptThingIndex(int32 index, eScriptThingType type) {
    //return plugin::CallAndReturn<uint32, 0x483720, int32, char>(index, type);
    const auto NewUniqueId = [index](auto& id) -> int32 {
        if (id == -1 || id == -2) {
            id = 1;
        } else {
            ++id;
        }

        return (uint32)id << 16 | index;
    };

    switch (type) {
    case eScriptThingType::SCRIPT_THING_SPHERE:
        return NewUniqueId(ScriptSphereArray[index].m_nUniqueId);
    case eScriptThingType::SCRIPT_THING_EFFECT_SYSTEM:
        return NewUniqueId(ScriptEffectSystemArray[index].m_nId);
    case eScriptThingType::SCRIPT_THING_SEARCH_LIGHT:
        return NewUniqueId(ScriptSearchLightArray[index].m_nId);
    case eScriptThingType::SCRIPT_THING_CHECKPOINT:
        return NewUniqueId(ScriptCheckpointArray[index].m_nId);
    case eScriptThingType::SCRIPT_THING_SEQUENCE_TASK:
        ScriptSequenceTaskArray[index].m_bUsed = true;
        return NewUniqueId(ScriptSequenceTaskArray[index].m_nId);
    case eScriptThingType::SCRIPT_THING_FIRE:
        return NewUniqueId(gFireManager.m_aFires[index].m_nScriptReferenceIndex);
    case eScriptThingType::SCRIPT_THING_2D_EFFECT:
        return NewUniqueId(CScripted2dEffects::ScriptReferenceIndex[index]);
    case eScriptThingType::SCRIPT_THING_DECISION_MAKER:
        CDecisionMakerTypes::GetInstance(); // ? TODO check if we really need this
        return NewUniqueId(CDecisionMakerTypes::ScriptReferenceIndex[index]);
    case eScriptThingType::SCRIPT_THING_PED_GROUP:
        return NewUniqueId(CPedGroups::ScriptReferenceIndex[index]);
    default:
        break;
    }

    return -1;
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
    for (auto& model : VehicleModelsBlockedByScript) {
        if (model == modelIndex) {
            model = MODEL_INVALID;
        }
    }
}

// 0x46ABC0
void CTheScripts::RemoveFromWaitingForScriptBrainArray(CEntity* entity, int16 modelIndex) {
    for (auto& bwe : EntitiesWaitingForScriptBrain) {
        if (bwe.m_pEntity != entity || bwe.m_nSpecialModelIndex != modelIndex) {
            continue;
        }

        CEntity::ClearReference(bwe.m_pEntity);
        bwe.m_nSpecialModelIndex = MODEL_INVALID;
    }
}

// 0x4936C0
void CTheScripts::RemoveScriptCheckpoint(int32 scriptIndex) {
    const auto i = GetActualScriptThingIndex(scriptIndex, eScriptThingType::SCRIPT_THING_CHECKPOINT);
    if (i == -1) {
        return;
    }

    auto& scp = ScriptCheckpointArray[i];
    if (const auto* cp = scp.m_Checkpoint) {
        CCheckpoints::DeleteCP(cp->m_nIdentifier, cp->m_nType);
    }
    scp.m_bUsed = false;
    scp.m_nId = 0;

    --NumberOfScriptCheckpoints;
}

// 0x492FD0
void CTheScripts::RemoveScriptEffectSystem(int32 scriptIndex) {
    const auto i = GetActualScriptThingIndex(scriptIndex, eScriptThingType::SCRIPT_THING_EFFECT_SYSTEM);
    if (i == -1) {
        return;
    }

    auto& sef = ScriptEffectSystemArray[i];
    sef.m_bUsed = false;
    sef.m_pFxSystem = nullptr;
}

// 0x493160
void CTheScripts::RemoveScriptSearchLight(int32 scriptIndex) {
    const auto i = GetActualScriptThingIndex(scriptIndex, eScriptThingType::SCRIPT_THING_SEARCH_LIGHT);
    if (i == -1) {
        return;
    }

    auto& ssl = ScriptSearchLightArray[i];
    CEntity::ClearReference(ssl.m_FollowingEntity);
    CEntity::ClearReference(ssl.m_AttachedEntity);
    CEntity::ClearReference(ssl.m_Tower);
    CEntity::ClearReference(ssl.m_Housing);
    CEntity::ClearReference(ssl.m_Bulb);
    ssl = tScriptSearchlight{};

    --NumberOfScriptSearchLights;
}

// 0x483BA0
void CTheScripts::RemoveScriptSphere(int32 scriptIndex) {
    const auto i = GetActualScriptThingIndex(scriptIndex, eScriptThingType::SCRIPT_THING_SPHERE);
    if (i == -1) {
        return;
    }

    auto& ss = ScriptSphereArray[i];
    ss.m_bUsed = false;
    ss.m_nId   = 0;
}

// 0x465A40
void CTheScripts::RemoveScriptTextureDictionary() {
    rng::for_each(ScriptSprites, &CSprite2d::Delete);
    if (const auto slot = CTxdStore::FindTxdSlot("script"); slot != -1) {
        if (const auto* txd = CTxdStore::ms_pTxdPool->GetAt(slot); txd) {
            CTxdStore::RemoveTxd(slot);
        }
    }
}

// 0x486240
void CTheScripts::RemoveThisPed(CPed* ped) {
    // plugin::Call<0x486240, CPed*>( ped);
    if (!ped) {
        return;
    }

    if (auto* veh = ped->GetVehicleIfInOne()) {
        if (veh->IsDriver(ped)) {
            veh->RemoveDriver(false);

            if (veh->m_nDoorLock == eCarLock::CARLOCK_COP_CAR) {
                veh->m_nDoorLock = eCarLock::CARLOCK_UNLOCKED;
            }

            if (ped->IsCop() && veh->IsLawEnforcementVehicle()) {
                veh->ChangeLawEnforcerState(false);
            }
        } else {
            veh->RemovePassenger(ped);
        }
    }

    const auto isMissionChar = ped->m_nCreatedBy == ePedCreatedBy::PED_MISSION;

    CWorld::RemoveReferencesToDeletedObject(ped);
    delete ped;

    if (isMissionChar) {
        --CPopulation::ms_nTotalMissionPeds;
    }
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
CRunningScript* CTheScripts::StartNewScript(uint8* startIP, uint16 index) {
    //return plugin::CallAndReturn<CRunningScript*, 0x464C90, uint8*, uint16>(startIP, index);
    if (!pIdleScripts) {
        return nullptr;
    }

    auto* script = pIdleScripts;
    while (script && script != &ScriptsArray[index]) {
        script = script->m_pNext;
    }

    if (!script) {
        return nullptr;
    }

    script->RemoveScriptFromList(&pIdleScripts);
    script->Init();
    script->SetCurrentIp(startIP);
    script->AddScriptToList(&pActiveScripts);
    script->SetActive(true);

    return script;
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
    return OnAMissionFlag && notsa::ReadAs<uint32_t>(&ScriptSpace[OnAMissionFlag]) == 1;
}

// 0x4861F0
bool CTheScripts::IsVehicleStopped(CVehicle* veh) {
    return std::max(CTimer::GetTimeStep(), CTimer::ms_fOldTimeStep) / 100.0f >= veh->m_fMovingSpeed;
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
    rng::fill(LocalVariablesForCurrentMission, tScriptParam{});
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

    StartNewScript(MainSCMBlock.data());
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
    DrawScriptSpheres();
    ProcessAllSearchLights();
    ProcessWaitingForScriptBrainArray();

    if (FailCurrentMission) {
        --FailCurrentMission;
    }

    if (UseTextCommands) {
        rng::fill(IntroTextLines, tScriptText{});
        NumberOfIntroTextLinesThisFrame = 0;

        rng::fill(IntroRectangles, tScriptRectangle{});
        NumberOfIntroRectanglesThisFrame = 0;

        UseTextCommands = false;
    }

    const auto timeStepMS = (int32)CTimer::GetTimeStepInMS();
    LocalVariablesForCurrentMission[SCRIPT_VAR_TIMERA].iParam += timeStepMS;
    LocalVariablesForCurrentMission[SCRIPT_VAR_TIMERB].iParam += timeStepMS;

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

    //return plugin::Call<0x4939F0>();
    for (auto& light : ScriptSearchLightArray) {
        if (!light.IsActive() || !(light.m_nFlags & 0b1000'0000)) {
            continue;
        }

        switch (light.m_nFlags & 0b111'1111) {
        case 1: {
            const auto d = light.m_PathCoord1 - light.m_Target;
            if (d.SquaredMagnitude() > sq(light.m_fPathSpeed)) {
                light.m_Target *= d.Normalized();
                break;
            }

            light.m_Target = light.m_PathCoord1;
            light.m_nFlags = 0b1000'0010;
            break;
        }
        case 2: {
            const auto d = light.m_PathCoord2 - light.m_Target;
            if (d.SquaredMagnitude() > sq(light.m_fPathSpeed)) {
                light.m_Target *= d.Normalized();
                break;
            }

            light.m_Target = light.m_PathCoord2;
            light.m_nFlags = 0b1000'0001;
            break;
        }
        case 3: {
            const auto d = light.m_FollowingEntity->GetPosition() - light.m_Target;
            if (d.SquaredMagnitude() > sq(light.m_fPathSpeed)) {
                light.m_Target *= d.Normalized();
                break;
            }

            light.m_Target = light.m_FollowingEntity->GetPosition();
            /* flag is not altered */
            break;
        }
        case 4: {
            auto d = light.m_PathCoord1 - light.m_FollowingEntity->GetPosition();
            if (d.SquaredMagnitude() > sq(light.m_fPathSpeed)) {
                light.m_Target *= d.Normalized();
                break;
            }

            light.m_Target     = light.m_PathCoord1;
            light.m_fPathSpeed = 0.0f;
            light.m_PathCoord1 = CVector{};
            light.m_nFlags     = 0b1000'0000;
            break;
        }
        default:
            break;
        }

        auto* bulb = light.m_Bulb;
        if (!bulb) {
            continue;
        }

        const auto prevPos    = bulb->GetPosition();
        const auto tgtBulbDir = (light.m_Target - bulb->GetPosition()).Normalized();

        const auto Transform = [&](CEntity* entity) {
            const auto rotX = std::atan2(tgtBulbDir.z, tgtBulbDir.Magnitude2D());
            const auto rotZ = tgtBulbDir.Heading();

            entity->m_matrix->RotateX(rotX);
            entity->m_matrix->RotateZ(rotZ);
            entity->GetPosition() += prevPos;
            entity->UpdateRW();
            entity->UpdateRwFrame();
        };

        Transform(bulb);
        Transform(light.m_Housing);
    }
}

void CTheScripts::ProcessWaitingForScriptBrainArray() {
    ZoneScoped;

    plugin::Call<0x46CF00>();
}

// 0x4812D0
void CTheScripts::UndoEntityInvisibilitySettings() {
    for (auto& is : InvisibilitySettingArray) {
        if (!is) {
            continue;
        }

        is->m_bIsVisible = true;
        is->m_bUsesCollision = true;

        is = nullptr; // Remove from the array.
    }
}

// 0x4646D0
void CTheScripts::PrintListSizes() {
    auto active{ 0u }, idle{ 0u };

    for (const auto* s = pActiveScripts; s; s = s->m_pNext) active++;
    for (const auto* s = pIdleScripts; s; s = s->m_pNext) idle++;

    NOTSA_LOG_DEBUG("Scripts Active: {}, Idle: {}", active, idle);
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

    for (auto& ss : ScriptSphereArray) {
        if (!ss.m_bUsed) {
            continue;
        }

        C3dMarkers::PlaceMarkerSet(
            ss.m_nId,
            e3dMarkerType::MARKER3D_CYLINDER,
            ss.m_vCoords,
            ss.m_fRadius,
            255,
            0,
            0,
            228,
            2048,
            0.1f,
            0
        );
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
