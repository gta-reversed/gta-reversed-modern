/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "TheScripts.h"

bool& CTheScripts::DbgFlag = *reinterpret_cast<bool*>(0x859CF8);
tScriptParam* CTheScripts::ScriptParams = reinterpret_cast<tScriptParam*>(0xA43C78);
tScriptSwitchCase* CTheScripts::SwitchJumpTable = reinterpret_cast<tScriptSwitchCase*>(0xA43CF8);
uint16& CTheScripts::NumberOfEntriesInSwitchTable = *reinterpret_cast<uint16*>(0xA43F50);
void*& CTheScripts::SwitchDefaultAddress = *reinterpret_cast<void**>(0xA43F54);
bool& CTheScripts::SwitchDefaultExists = *reinterpret_cast<bool*>(0xA43F58);
int32& CTheScripts::ValueToCheckInSwitchStatement = *reinterpret_cast<int32*>(0xA43F5C);
uint16& CTheScripts::NumberOfEntriesStillToReadForSwitch = *reinterpret_cast<uint16*>(0xA43F60);
tScriptSequence* CTheScripts::ScriptSequenceTaskArray = reinterpret_cast<tScriptSequence*>(0xA43F68);
uint16& CTheScripts::NumberOfScriptCheckpoints = *reinterpret_cast<uint16*>(0xA44068);
tScriptCheckpoint* CTheScripts::ScriptCheckpointArray = reinterpret_cast<tScriptCheckpoint*>(0xA44070);
tScriptEffectSystem* CTheScripts::ScriptEffectSystemArray = reinterpret_cast<tScriptEffectSystem*>(0xA44110);
int16& CTheScripts::CardStackPosition = *reinterpret_cast<int16*>(0xA44210);
int16* CTheScripts::CardStack = reinterpret_cast<int16*>(0xA44218);
bool& CTheScripts::bDrawSubtitlesBeforeFade = *reinterpret_cast<bool*>(0xA44488);
bool& CTheScripts::bDrawOddJobTitleBeforeFade = *reinterpret_cast<bool*>(0xA44489);
bool& CTheScripts::bScriptHasFadedOut = *reinterpret_cast<bool*>(0xA4448A);
bool& CTheScripts::bAddNextMessageToPreviousBriefs = *reinterpret_cast<bool*>(0xA4448B);
int32& CTheScripts::ForceRandomCarModel = *reinterpret_cast<int32*>(0xA4448C);
bool& CTheScripts::bDrawCrossHair = *reinterpret_cast<bool*>(0xA44490);
bool& CTheScripts::bEnableCraneRelease = *reinterpret_cast<bool*>(0xA44494);
bool& CTheScripts::bEnableCraneLower = *reinterpret_cast<bool*>(0xA44495);
bool& CTheScripts::bEnableCraneRaise = *reinterpret_cast<bool*>(0xA44496);
float& CTheScripts::fCameraHeadingStepWhenPlayerIsAttached = *reinterpret_cast<float*>(0xA44498);
float& CTheScripts::fCameraHeadingWhenPlayerIsAttached = *reinterpret_cast<float*>(0xA4449C);
bool& CTheScripts::bDisplayHud = *reinterpret_cast<bool*>(0xA444A0);
bool& CTheScripts::HideAllFrontEndMapBlips = *reinterpret_cast<bool*>(0xA444A1);
bool& CTheScripts::RadarShowBlipOnAllLevels = *reinterpret_cast<bool*>(0xA444A2);
uint8& CTheScripts::RadarZoomValue = *reinterpret_cast<uint8*>(0xA444A3);
bool& CTheScripts::bPlayerIsOffTheMap = *reinterpret_cast<bool*>(0xA444A4);
char& CTheScripts::RiotIntensity = *reinterpret_cast<char*>(0xA444A5);
bool& CTheScripts::bPlayerHasMetDebbieHarry = *reinterpret_cast<bool*>(0xA444A6);
bool& CTheScripts::bDisplayNonMiniGameHelpMessages = *reinterpret_cast<bool*>(0xA444A7);
bool& CTheScripts::bMiniGameInProgress = *reinterpret_cast<bool*>(0xA444A8);
int32& CTheScripts::ScriptPickupCycleIndex = *reinterpret_cast<int32*>(0xA444AC);
char& CTheScripts::FailCurrentMission = *reinterpret_cast<char*>(0xA444B0);
bool& CTheScripts::bAlreadyRunningAMissionScript = *reinterpret_cast<bool*>(0xA444B1);
uint32& CTheScripts::LargestNumberOfMissionScriptLocalVariables = *reinterpret_cast<uint32*>(0xA444B4);
uint16& CTheScripts::NumberOfExclusiveMissionScripts = *reinterpret_cast<uint16*>(0xA444B8);
uint16& CTheScripts::NumberOfMissionScripts = *reinterpret_cast<uint16*>(0xA444BC);
uint32& CTheScripts::LargestMissionScriptSize = *reinterpret_cast<uint32*>(0xA444C0);
uint32& CTheScripts::MainScriptSize = *reinterpret_cast<uint32*>(0xA444C4);
int32* CTheScripts::MultiScriptArray = reinterpret_cast<int32*>(0xA444C8);
bool& CTheScripts::bUsingAMultiScriptFile = *reinterpret_cast<bool*>(0xA447E8);
int32& CTheScripts::StoreVehicleIndex = *reinterpret_cast<int32*>(0xA447EC);
bool& CTheScripts::StoreVehicleWasRandom = *reinterpret_cast<bool*>(0xA447F0);
uint16& CTheScripts::CommandsExecuted = *reinterpret_cast<uint16*>(0xA447F4);
uint16& CTheScripts::ScriptsUpdated = *reinterpret_cast<uint16*>(0xA447F8);
int32* CTheScripts::ScriptConnectLodsObjects = reinterpret_cast<int32*>(0xA44800);
tScriptAttachedAnimGroup* CTheScripts::ScriptAttachedAnimGroups = reinterpret_cast<tScriptAttachedAnimGroup*>(0xA44850);
int32* CTheScripts::VehicleModelsBlockedByScript = reinterpret_cast<int32*>(0xA448F0);
int32* CTheScripts::SuppressedVehicleModels = reinterpret_cast<int32*>(0xA44940);
CEntity** CTheScripts::InvisibilitySettingArray = reinterpret_cast<CEntity**>(0xA449E0);
tBuildingSwap (&CTheScripts::BuildingSwapArray)[NUM_BUILDING_SWAPS] = *reinterpret_cast<tBuildingSwap (*)[NUM_BUILDING_SWAPS]>(0xA44A30);
uint16& CTheScripts::NumberOfIntroRectanglesThisFrame = *reinterpret_cast<uint16*>(0xA44B5C);
uint16& CTheScripts::MessageWidth = *reinterpret_cast<uint16*>(0xA44B60);
uint16& CTheScripts::MessageCentre = *reinterpret_cast<uint16*>(0xA44B64);
bool& CTheScripts::bUseMessageFormatting = *reinterpret_cast<bool*>(0xA44B66);
bool& CTheScripts::UseTextCommands = *reinterpret_cast<bool*>(0xA44B67);
uint16& CTheScripts::CurrentTextDrawer = *reinterpret_cast<uint16*>(0xA44B68);
uint16& CTheScripts::NumberOfIntroTextLinesThisFrame = *reinterpret_cast<uint16*>(0xA44B68);
uint16& CTheScripts::NumberOfUsedObjects = *reinterpret_cast<uint16*>(0xA44B6C);
tUsedObject* CTheScripts::UsedObjectArray = reinterpret_cast<tUsedObject*>(0xA44B70);
int32& CTheScripts::LastRandomPedId = *reinterpret_cast<int32*>(0xA476A4);
uint32& CTheScripts::LastMissionPassedTime = *reinterpret_cast<uint32*>(0xA476A8);
int32& CTheScripts::OnAMissionFlag = *reinterpret_cast<int32*>(0xA476AC);
CEntity*& CTheScripts::EntitiesWaitingForScriptBrain = *reinterpret_cast<CEntity**>(0xA476B0);
CStreamedScripts& CTheScripts::StreamedScripts = *reinterpret_cast<CStreamedScripts*>(0xA47B60);
CScriptResourceManager& CTheScripts::ScriptResourceManager = *reinterpret_cast<CScriptResourceManager*>(0xA485A8);
CUpsideDownCarCheck& CTheScripts::UpsideDownCars = *reinterpret_cast<CUpsideDownCarCheck*>(0xA4892C);
tScriptParam* CTheScripts::LocalVariablesForCurrentMission = reinterpret_cast<tScriptParam*>(0xA48960);
uint8* CTheScripts::ScriptSpace = reinterpret_cast<uint8*>(0xA49960);
char* CTheScripts::MissionBlock = reinterpret_cast<char*>(0xA7A6A0);
CRunningScript*& CTheScripts::pIdleScripts = *reinterpret_cast<CRunningScript**>(0xA8B428);
CRunningScript*& CTheScripts::pActiveScripts = *reinterpret_cast<CRunningScript**>(0xA8B42C);
CRunningScript* CTheScripts::ScriptsArray = reinterpret_cast<CRunningScript*>(0xA8B430);
uint16& CTheScripts::NumberOfScriptSearchLights = *reinterpret_cast<uint16*>(0xA90830);
CMissionCleanup& CTheScripts::MissionCleanUp = *reinterpret_cast<CMissionCleanup*>(0xA90850);
CStuckCarCheck& CTheScripts::StuckCars = *reinterpret_cast<CStuckCarCheck*>(0xA90AB0);
CScriptsForBrains& CTheScripts::ScriptsForBrains = *reinterpret_cast<CScriptsForBrains*>(0xA90CF0);
tScriptSphere* CTheScripts::ScriptSphereArray = reinterpret_cast<tScriptSphere*>(0xA91268);
tScriptText* CTheScripts::IntroTextLines = reinterpret_cast<tScriptText*>(0xA913E8);
tScriptRectangle* CTheScripts::IntroRectangles = reinterpret_cast<tScriptRectangle*>(0xA92D68);
CSprite2d* CTheScripts::ScriptSprites = reinterpret_cast<CSprite2d*>(0xA94B68);
tScriptSearchlight* CTheScripts::ScriptSearchLightArray = reinterpret_cast<tScriptSearchlight*>(0xA94D68);

void CTheScripts::InjectHooks() {
    RH_ScopedClass(CTheScripts);
    RH_ScopedCategory("Scripts");

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

    for (auto& swap : CTheScripts::BuildingSwapArray) {
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

    for (auto& swap : CTheScripts::BuildingSwapArray) {
        if (!swap.m_pCBuilding) {
            swap.m_pCBuilding = building;
            swap.m_nOldModelIndex = oldModelId;
            swap.m_nNewModelIndex = newModelId;
            return;
        }
    }
}

// 0x486670
void CTheScripts::CleanUpThisVehicle(CVehicle* pVehicle) {
    plugin::Call<0x486670, CVehicle*>(pVehicle);
}

// 0x486B00
void CTheScripts::ClearSpaceForMissionEntity(CVector const& pos, CEntity* pEntity) {
    plugin::Call<0x486B00, CVector const&, CEntity*>(pos, pEntity);
}

void CTheScripts::DoScriptSetupAfterPoolsHaveLoaded() {
    plugin::Call<0x5D3390>();
}

// 0x4839A0
signed int CTheScripts::GetActualScriptThingIndex(int32 index, uint8 type) {
    return plugin::CallAndReturn<signed int, 0x4839A0, int32, uint8>(index, type);
}

// 0x483720
uint32 CTheScripts::GetNewUniqueScriptThingIndex(uint32 index, char type) {
    return plugin::CallAndReturn<uint32, 0x483720, uint32, char>(index, type);
}

// 0x464D20
int32 CTheScripts::GetScriptIndexFromPointer(CRunningScript* thread) {
    return plugin::CallAndReturn<int32, 0x464D20, CRunningScript*>(thread);
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
    return plugin::CallAndReturn<CRunningScript*, 0x464C20, uint8*>(startIP);
}

void CTheScripts::UndoBuildingSwaps() {
    for (auto& swap : CTheScripts::BuildingSwapArray) {
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
bool CTheScripts::IsVehicleStopped(CVehicle* pVehicle) {
    return plugin::CallAndReturn<bool, 0x4861F0, CVehicle*>(pVehicle);
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
    StartNewScript(CTheScripts::ScriptSpace);
}

// 0x46A000
void CTheScripts::Process() {
    plugin::Call<0x46A000>();
}

// 0x4812D0
void CTheScripts::UndoEntityInvisibilitySettings() {
    plugin::Call<0x4812D0>();
}
