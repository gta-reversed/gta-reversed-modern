/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

#include "TheScripts.h"
#include "UpsideDownCarCheck.h"
#include "Lines.h"

bool& CTheScripts::DbgFlag = *reinterpret_cast<bool*>(0x859CF8);
tScriptParam* CTheScripts::ScriptParams = reinterpret_cast<tScriptParam*>(0xA43C78);
tScriptSwitchCase* CTheScripts::SwitchJumpTable = reinterpret_cast<tScriptSwitchCase*>(0xA43CF8);
uint16& CTheScripts::NumberOfEntriesInSwitchTable = *reinterpret_cast<uint16*>(0xA43F50);
void*& CTheScripts::SwitchDefaultAddress = *reinterpret_cast<void**>(0xA43F54);
bool& CTheScripts::SwitchDefaultExists = *reinterpret_cast<bool*>(0xA43F58);
int32& CTheScripts::ValueToCheckInSwitchStatement = *reinterpret_cast<int32*>(0xA43F5C);
uint16& CTheScripts::NumberOfEntriesStillToReadForSwitch = *reinterpret_cast<uint16*>(0xA43F60);
uint16& CTheScripts::NumberOfScriptCheckpoints = *reinterpret_cast<uint16*>(0xA44068);
int16& CTheScripts::CardStackPosition = *reinterpret_cast<int16*>(0xA44210);
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
bool& CTheScripts::bUsingAMultiScriptFile = *reinterpret_cast<bool*>(0xA447E8);
int32& CTheScripts::StoreVehicleIndex = *reinterpret_cast<int32*>(0xA447EC);
bool& CTheScripts::StoreVehicleWasRandom = *reinterpret_cast<bool*>(0xA447F0);
uint16& CTheScripts::CommandsExecuted = *reinterpret_cast<uint16*>(0xA447F4);
uint16& CTheScripts::ScriptsUpdated = *reinterpret_cast<uint16*>(0xA447F8);
uint16& CTheScripts::NumberOfIntroRectanglesThisFrame = *reinterpret_cast<uint16*>(0xA44B5C);
uint16& CTheScripts::MessageWidth = *reinterpret_cast<uint16*>(0xA44B60);
uint16& CTheScripts::MessageCentre = *reinterpret_cast<uint16*>(0xA44B64);
bool& CTheScripts::bUseMessageFormatting = *reinterpret_cast<bool*>(0xA44B66);
bool& CTheScripts::UseTextCommands = *reinterpret_cast<bool*>(0xA44B67);
uint16& CTheScripts::CurrentTextDrawer = *reinterpret_cast<uint16*>(0xA44B68);
uint16& CTheScripts::NumberOfIntroTextLinesThisFrame = *reinterpret_cast<uint16*>(0xA44B68);
uint16& CTheScripts::NumberOfUsedObjects = *reinterpret_cast<uint16*>(0xA44B6C);
int32& CTheScripts::LastRandomPedId = *reinterpret_cast<int32*>(0xA476A4);
uint32& CTheScripts::LastMissionPassedTime = *reinterpret_cast<uint32*>(0xA476A8);
int32& CTheScripts::OnAMissionFlag = *reinterpret_cast<int32*>(0xA476AC);
CStreamedScripts& CTheScripts::StreamedScripts = *reinterpret_cast<CStreamedScripts*>(0xA47B60);
CScriptResourceManager& CTheScripts::ScriptResourceManager = *reinterpret_cast<CScriptResourceManager*>(0xA485A8);
CUpsideDownCarCheck& CTheScripts::UpsideDownCars = *reinterpret_cast<CUpsideDownCarCheck*>(0xA4892C);
tScriptParam* CTheScripts::LocalVariablesForCurrentMission = reinterpret_cast<tScriptParam*>(0xA48960);
uint8* CTheScripts::ScriptSpace = reinterpret_cast<uint8*>(0xA49960);
char* CTheScripts::MissionBlock = reinterpret_cast<char*>(0xA7A6A0);
CRunningScript*& CTheScripts::pIdleScripts = *reinterpret_cast<CRunningScript**>(0xA8B428);
CRunningScript*& CTheScripts::pActiveScripts = *reinterpret_cast<CRunningScript**>(0xA8B42C);
uint16& CTheScripts::NumberOfScriptSearchLights = *reinterpret_cast<uint16*>(0xA90830);
CMissionCleanup& CTheScripts::MissionCleanUp = *reinterpret_cast<CMissionCleanup*>(0xA90850);
CStuckCarCheck& CTheScripts::StuckCars = *reinterpret_cast<CStuckCarCheck*>(0xA90AB0);
CScriptsForBrains& CTheScripts::ScriptsForBrains = *reinterpret_cast<CScriptsForBrains*>(0xA90CF0);

#define SPHERE_MARKER_R 252
#define SPHERE_MARKER_G 138
#define SPHERE_MARKER_B 242
#define SPHERE_MARKER_A 228
#define SPHERE_MARKER_PULSE_PERIOD 2048
#define SPHERE_MARKER_PULSE_FRACTION 0.1f

void CTheScripts::InjectHooks() {
    RH_ScopedClass(CTheScripts);
    RH_ScopedCategory("Scripts");

    // RH_ScopedInstall(AddScriptCheckpoint, 0x0);
    // RH_ScopedInstall(AddScriptEffectSystem, 0x0);
    // RH_ScopedInstall(AddScriptSearchLight, 0x0);
    // RH_ScopedInstall(AddScriptSphere, 0x0);
    RH_ScopedInstall(AddToBuildingSwapArray, 0x481140);
    // RH_ScopedInstall(AddToInvisibilitySwapArray, 0x0);
    // RH_ScopedInstall(AddToListOfConnectedLodObjects, 0x0);
    // RH_ScopedInstall(AddToListOfSpecialAnimGroupsAttachedToCharModels, 0x0);
    // RH_ScopedInstall(AddToSuppressedCarModelArray, 0x0);
    // RH_ScopedInstall(AddToSwitchJumpTable, 0x0);
    // RH_ScopedInstall(AddToVehicleModelsBlockedByScript, 0x0);
    // RH_ScopedInstall(AddToWaitingForScriptBrainArray, 0x0);
    // RH_ScopedInstall(AttachSearchlightToSearchlightObject, 0x0);
    // RH_ScopedInstall(CheckScriptVersion, 0x0);
    // RH_ScopedInstall(CheckStreamedScriptVersion, 0x0);
    RH_ScopedInstall(CleanUpThisObject, 0x4866C0);
    // RH_ScopedInstall(CleanUpThisPed, 0x486300);
    // RH_ScopedInstall(CleanUpThisVehicle, 0x486670);
    // RH_ScopedInstall(ClearAllSuppressedCarModels, 0x0);
    // RH_ScopedInstall(ClearAllVehicleModelsBlockedByScript, 0x0);
    // RH_ScopedInstall(ClearSpaceForMissionEntity, 0x486B00);
    // RH_ScopedInstall(DoScriptSetupAfterPoolsHaveLoaded, 0x5D3390);
    // RH_ScopedInstall(DrawDebugAngledCube, 0x0);
    // RH_ScopedInstall(DrawDebugAngledSquare, 0x0);
    // RH_ScopedInstall(DrawDebugCube, 0x0);
    // RH_ScopedInstall(DrawDebugSquare, 0x486840);
    // RH_ScopedInstall(DrawScriptSpheres, 0x4810E0);
    // RH_ScopedInstall(DrawScriptSpritesAndRectangles, 0x0);
    // RH_ScopedInstall(GetActualScriptThingIndex, 0x0);
    // RH_ScopedInstall(GetNewUniqueScriptThingIndex, 0x0);
    // RH_ScopedInstall(GetScriptIndexFromPointer, 0x0);
    // RH_ScopedInstall(GetUniqueScriptThingIndex, 0x0);
    // RH_ScopedInstall(HasCarModelBeenSuppressed, 0x0);
    // RH_ScopedInstall(HasVehicleModelBeenBlockedByScript, 0x0);
    // RH_ScopedInstall(HighlightImportantAngledArea, 0x0);
    // RH_ScopedInstall(HighlightImportantArea, 0x0);
    // RH_ScopedInstall(Init, 0x0);
    // RH_ScopedInstall(InitialiseAllConnectLodObjects, 0x0);
    // RH_ScopedInstall(InitialiseConnectLodObjects, 0x0); // unused
    // RH_ScopedInstall(InitialiseSpecialAnimGroup, 0x0);
    // RH_ScopedInstall(InitialiseSpecialAnimGroupsAttachedToCharModels, 0x0);
    // RH_ScopedInstall(IsEntityWithinAnySearchLight, 0x0);
    // RH_ScopedInstall(IsEntityWithinSearchLight, 0x0);
    // RH_ScopedInstall(IsPedStopped, 0x0);
    // RH_ScopedInstall(IsPlayerOnAMission, 0x0);
    // RH_ScopedInstall(IsPointWithinSearchLight, 0x0);
    // RH_ScopedInstall(IsVehicleStopped, 0x0);
    // RH_ScopedInstall(Load, 0x0);
    // RH_ScopedInstall(LoadAfter, 0x0);
    // RH_ScopedInstall(MoveSearchLightBetweenTwoPoints, 0x0);
    // RH_ScopedInstall(MoveSearchLightToEntity, 0x0);
    // RH_ScopedInstall(MoveSearchLightToPointAndStop, 0x0);
    RH_ScopedInstall(PrintListSizes, 0x4646D0); // unused
    // RH_ScopedInstall(Process, 0x0);
    // RH_ScopedInstall(ProcessAllSearchLights, 0x0);
    // RH_ScopedInstall(ProcessWaitingForScriptBrainArray, 0x0);
    // RH_ScopedInstall(ReadMultiScriptFileOffsetsFromScript, 0x0);
    // RH_ScopedInstall(ReadObjectNamesFromScript, 0x0);
    // RH_ScopedInstall(ReinitialiseSwitchStatementData, 0x0);
    // RH_ScopedInstall(RemoveFromSuppressedCarModelArray, 0x0);
    // RH_ScopedInstall(RemoveFromVehicleModelsBlockedByScript, 0x0);
    // RH_ScopedInstall(RemoveFromWaitingForScriptBrainArray, 0x0);
    // RH_ScopedInstall(RemoveScriptCheckpoint, 0x0);
    // RH_ScopedInstall(RemoveScriptEffectSystem, 0x0);
    // RH_ScopedInstall(RemoveScriptSearchLight, 0x0);
    // RH_ScopedInstall(RemoveScriptSphere, 0x0);
    // RH_ScopedInstall(RemoveScriptTextureDictionary, 0x0);
    // RH_ScopedInstall(RemoveThisPed, 0x0);
    // RH_ScopedInstall(RenderAllSearchLights, 0x0);
    // RH_ScopedInstall(RenderTheScriptDebugLines, 0x0);
    // RH_ScopedInstall(Save, 0x0);
    // RH_ScopedInstall(SaveAfter, 0x0);
    // RH_ScopedInstall(ScriptAttachAnimGroupToCharModel, 0x0);
    // RH_ScopedInstall(ScriptConnectLodsFunction, 0x0);
    // RH_ScopedInstall(ScriptDebugCircle2D, 0x485C20); // unused
    // RH_ScopedInstall(ScriptDebugLine3D, 0x485DE0);
    // RH_ScopedOverloadedInstall(StartNewScript, 0x0);
    // RH_ScopedOverloadedInstall(StartNewScript, 0x0);
    RH_ScopedInstall(StartTestScript, 0x464D40);
    // RH_ScopedInstall(UndoBuildingSwaps, 0x481290);
    // RH_ScopedInstall(UndoEntityInvisibilitySettings, 0x0);
    // RH_ScopedInstall(UpdateObjectIndices, 0x0);
    // RH_ScopedInstall(UseSwitchJumpTable, 0x0);
    // RH_ScopedInstall(WipeLocalVariableMemoryForMissionScript, 0x0);
}

// 0x468D50
void CTheScripts::Init() {
    plugin::Call<0x468D50>();
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

    for (auto& swap : CTheScripts::BuildingSwapArray) {
        if (!swap.m_pCBuilding) {
            swap = tBuildingSwap(building, newModelId, oldModelId);
            return;
        }
    }
}

// 0x4866C0
void CTheScripts::CleanUpThisObject(CObject* obj) {
    if (!obj)
        return;

    if (obj->IsMissionObject()) {
        obj->m_nObjectType = OBJECT_TEMPORARY;
        obj->m_nRemovalTime = CTimer::GetTimeInMS() + 200'00'000;
        obj->m_nRefModelIndex = -1;
        obj->m_nObjectFlags = obj->m_nObjectFlags & 0xFFFFFF7F; // todo: flags
        ++CObject::nNoTempObjects;
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

// 0x486B00
void CTheScripts::ClearSpaceForMissionEntity(const CVector& pos, CEntity* entity) {
    plugin::Call<0x486B00, const CVector&, CEntity*>(pos, entity);
}

// 0x5D3390
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
    for (auto& swap : BuildingSwapArray) {
        if (swap.m_pCBuilding) {
            swap.m_pCBuilding->ReplaceWithNewModel(swap.m_nOldModelIndex);
            swap.Clear();
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

// 0x4646D0
void CTheScripts::PrintListSizes()
{
    int active = 0;
    int idle = 0;

    for (CRunningScript* script = pActiveScripts; script; script = script->m_pNext) active++;
    for (CRunningScript* script = pIdleScripts; script; script = script->m_pNext) idle++;

    printf("active: %d, idle: %d\n", active, idle);
}

uint32 DbgLineColour = 0x0000FFFF; // r = 0, g = 0, b = 255, a = 255

// Usage:
//  const auto pos = FindPlayerPed()->GetPosition() + CVector{ 0.0f, 0.f, 1.0f };
//  CTheScripts::DrawDebugSquare(pos.x + 5.f, pos.y, pos.x, pos.y + 5.f);
// 0x486840
void CTheScripts::DrawDebugSquare(float x1, float y1, float x2, float y2)
{
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
void CTheScripts::DrawDebugAngledSquare(const CVector2D& inf, const CVector2D& sup, const CVector2D& rotSup, const CVector2D& rotInf)
{
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
void CTheScripts::DrawDebugCube(const CVector& inf, const CVector& sup)
{
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
void CTheScripts::DrawDebugAngledCube(const CVector& inf, const CVector& sup, const CVector2D& rotSup, const CVector2D& rotInf)
{
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

// Usage:
//   const auto pos = FindPlayerPed()->GetPosition() + CVector{ 0.0f, 0.f, 1.0f };
//   CTheScripts::ScriptDebugCircle2D(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 100, 50.f, 50.f, HudColour.GetRGB(HUD_COLOUR_RED).ToInt());
// 0x485C20
void CTheScripts::ScriptDebugCircle2D(float x, float y, float width, float height, CRGBA color)
{
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
        RwIm2DRenderLine(vertices, std::size(vertices), 0, 1); // todo: _BUGFIX
    }

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
}

// 0x4810E0
void CTheScripts::DrawScriptSpheres()
{
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
void CTheScripts::HighlightImportantArea(uint32 id, float x1, float y1, float x2, float y2, float z)
{
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
    }
    else {
        inf.y = y2;
        sup.y = y1;
    }
    CVector center;
    center.x = (inf.x + sup.x) / 2;
    center.y = (inf.y + sup.y) / 2;
    center.z = (z <= MAP_Z_LOW_LIMIT) ? CWorld::FindGroundZForCoord(center.x, center.y) : z;
    CShadows::RenderIndicatorShadow(id, 2, nullptr, &center, sup.x - center.x, 0.0f, 0.0f, center.y - sup.y, 0);
}

// 0x485EF0
void CTheScripts::HighlightImportantAngledArea(uint32 id, float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float z)
{
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
    CShadows::RenderIndicatorShadow(id, 2, nullptr, &center, sup.x - center.x, 0.0f, 0.0f, center.y - sup.y, 0);
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
