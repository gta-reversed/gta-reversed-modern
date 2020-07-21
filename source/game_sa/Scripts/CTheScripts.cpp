/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

bool &CTheScripts::DbgFlag = *reinterpret_cast<bool *>(0x859CF8);
tScriptParam *CTheScripts::ScriptParams = reinterpret_cast<tScriptParam *>(0xA43C78);
tScriptSwitchCase *CTheScripts::SwitchJumpTable = reinterpret_cast<tScriptSwitchCase *>(0xA43CF8);
unsigned short &CTheScripts::NumberOfEntriesInSwitchTable = *reinterpret_cast<unsigned short *>(0xA43F50);
void *&CTheScripts::SwitchDefaultAddress = *reinterpret_cast<void **>(0xA43F54);
bool &CTheScripts::SwitchDefaultExists = *reinterpret_cast<bool *>(0xA43F58);
int &CTheScripts::ValueToCheckInSwitchStatement = *reinterpret_cast<int *>(0xA43F5C);
unsigned short &CTheScripts::NumberOfEntriesStillToReadForSwitch = *reinterpret_cast<unsigned short *>(0xA43F60);
tScriptSequence *CTheScripts::ScriptSequenceTaskArray = reinterpret_cast<tScriptSequence *>(0xA43F68);
unsigned short &CTheScripts::NumberOfScriptCheckpoints = *reinterpret_cast<unsigned short *>(0xA44068);
tScriptCheckpoint *CTheScripts::ScriptCheckpointArray = reinterpret_cast<tScriptCheckpoint *>(0xA44070);
tScriptEffectSystem *CTheScripts::ScriptEffectSystemArray = reinterpret_cast<tScriptEffectSystem *>(0xA44110);
short &CTheScripts::CardStackPosition = *reinterpret_cast<short *>(0xA44210);
short *CTheScripts::CardStack = reinterpret_cast<short *>(0xA44218);
bool &CTheScripts::bDrawSubtitlesBeforeFade = *reinterpret_cast<bool *>(0xA44488);
bool &CTheScripts::bDrawOddJobTitleBeforeFade = *reinterpret_cast<bool *>(0xA44489);
bool &CTheScripts::bScriptHasFadedOut = *reinterpret_cast<bool *>(0xA4448A);
bool &CTheScripts::bAddNextMessageToPreviousBriefs = *reinterpret_cast<bool *>(0xA4448B);
int &CTheScripts::ForceRandomCarModel = *reinterpret_cast<int *>(0xA4448C);
bool &CTheScripts::bDrawCrossHair = *reinterpret_cast<bool *>(0xA44490);
bool &CTheScripts::bEnableCraneRelease = *reinterpret_cast<bool *>(0xA44494);
bool &CTheScripts::bEnableCraneLower = *reinterpret_cast<bool *>(0xA44495);
bool &CTheScripts::bEnableCraneRaise = *reinterpret_cast<bool *>(0xA44496);
float &CTheScripts::fCameraHeadingStepWhenPlayerIsAttached = *reinterpret_cast<float *>(0xA44498);
float &CTheScripts::fCameraHeadingWhenPlayerIsAttached = *reinterpret_cast<float *>(0xA4449C);
bool &CTheScripts::bDisplayHud = *reinterpret_cast<bool *>(0xA444A0);
bool &CTheScripts::HideAllFrontEndMapBlips = *reinterpret_cast<bool *>(0xA444A1);
bool &CTheScripts::RadarShowBlipOnAllLevels = *reinterpret_cast<bool *>(0xA444A2);
unsigned char &CTheScripts::RadarZoomValue = *reinterpret_cast<unsigned char *>(0xA444A3);
bool &CTheScripts::bPlayerIsOffTheMap = *reinterpret_cast<bool *>(0xA444A4);
char &CTheScripts::RiotIntensity = *reinterpret_cast<char *>(0xA444A5);
bool &CTheScripts::bPlayerHasMetDebbieHarry = *reinterpret_cast<bool *>(0xA444A6);
bool &CTheScripts::bDisplayNonMiniGameHelpMessages = *reinterpret_cast<bool *>(0xA444A7);
bool &CTheScripts::bMiniGameInProgress = *reinterpret_cast<bool *>(0xA444A8);
int &CTheScripts::ScriptPickupCycleIndex = *reinterpret_cast<int *>(0xA444AC);
char &CTheScripts::FailCurrentMission = *reinterpret_cast<char *>(0xA444B0);
bool &CTheScripts::bAlreadyRunningAMissionScript = *reinterpret_cast<bool *>(0xA444B1);
unsigned int& CTheScripts::LargestNumberOfMissionScriptLocalVariables = *reinterpret_cast<unsigned int*>(0xA444B4);
unsigned short& CTheScripts::NumberOfExclusiveMissionScripts = *reinterpret_cast<unsigned short*>(0xA444B8);
unsigned short& CTheScripts::NumberOfMissionScripts = *reinterpret_cast<unsigned short*>(0xA444BC);
unsigned int &CTheScripts::LargestMissionScriptSize = *reinterpret_cast<unsigned int *>(0xA444C0);
unsigned int &CTheScripts::MainScriptSize = *reinterpret_cast<unsigned int *>(0xA444C4);
int *CTheScripts::MultiScriptArray = reinterpret_cast<int*>(0xA444C8);
bool &CTheScripts::bUsingAMultiScriptFile = *reinterpret_cast<bool *>(0xA447E8);
int &CTheScripts::StoreVehicleIndex = *reinterpret_cast<int *>(0xA447EC);
bool &CTheScripts::StoreVehicleWasRandom = *reinterpret_cast<bool *>(0xA447F0);
unsigned short &CTheScripts::CommandsExecuted = *reinterpret_cast<unsigned short *>(0xA447F4);
unsigned short &CTheScripts::ScriptsUpdated = *reinterpret_cast<unsigned short *>(0xA447F8);
int *CTheScripts::ScriptConnectLodsObjects = reinterpret_cast<int *>(0xA44800);
tScriptAttachedAnimGroup *CTheScripts::ScriptAttachedAnimGroups = reinterpret_cast<tScriptAttachedAnimGroup *>(0xA44850);
int *CTheScripts::VehicleModelsBlockedByScript = reinterpret_cast<int *>(0xA448F0);
int *CTheScripts::SuppressedVehicleModels = reinterpret_cast<int *>(0xA44940);
CEntity **CTheScripts::InvisibilitySettingArray = reinterpret_cast<CEntity **>(0xA449E0);
tBuildingSwap *CTheScripts::BuildingSwapArray = reinterpret_cast<tBuildingSwap *>(0xA44A30);
unsigned short &CTheScripts::NumberOfIntroRectanglesThisFrame = *reinterpret_cast<unsigned short *>(0xA44B5C);
unsigned short &CTheScripts::MessageWidth = *reinterpret_cast<unsigned short *>(0xA44B60);
unsigned short &CTheScripts::MessageCentre = *reinterpret_cast<unsigned short *>(0xA44B64);
bool &CTheScripts::bUseMessageFormatting = *reinterpret_cast<bool *>(0xA44B66);
bool &CTheScripts::UseTextCommands = *reinterpret_cast<bool *>(0xA44B67);
unsigned short &CTheScripts::NumberOfIntroTextLinesThisFrame = *reinterpret_cast<unsigned short *>(0xA44B68);
unsigned short &CTheScripts::NumberOfUsedObjects = *reinterpret_cast<unsigned short *>(0xA44B6C);
tUsedObject *CTheScripts::UsedObjectArray = reinterpret_cast<tUsedObject *>(0xA44B70);
int &CTheScripts::LastRandomPedId = *reinterpret_cast<int *>(0xA476A4);
unsigned int &CTheScripts::LastMissionPassedTime = *reinterpret_cast<unsigned int *>(0xA476A8);
int &CTheScripts::OnAMissionFlag = *reinterpret_cast<int *>(0xA476AC);
CEntity *&CTheScripts::EntitiesWaitingForScriptBrain = *reinterpret_cast<CEntity **>(0xA476B0);
CStreamedScripts &CTheScripts::StreamedScripts = *reinterpret_cast<CStreamedScripts *>(0xA47B60);
CScriptResourceManager &CTheScripts::ScriptResourceManager = *reinterpret_cast<CScriptResourceManager *>(0xA485A8);
CUpsideDownCarCheck &CTheScripts::UpsideDownCars = *reinterpret_cast<CUpsideDownCarCheck *>(0xA4892C);
tScriptParam *CTheScripts::LocalVariablesForCurrentMission = reinterpret_cast<tScriptParam *>(0xA48960);
std::uint8_t* CTheScripts::ScriptSpace = reinterpret_cast<std::uint8_t*>(0xA49960);
char *CTheScripts::MissionBlock = reinterpret_cast<char *>(0xA7A6A0);
CRunningScript *&CTheScripts::pIdleScripts = *reinterpret_cast<CRunningScript **>(0xA8B428);
CRunningScript *&CTheScripts::pActiveScripts = *reinterpret_cast<CRunningScript **>(0xA8B42C);
CRunningScript *CTheScripts::ScriptsArray = reinterpret_cast<CRunningScript *>(0xA8B430);
unsigned short &CTheScripts::NumberOfScriptSearchLights = *reinterpret_cast<unsigned short *>(0xA90830);
CMissionCleanup &CTheScripts::MissionCleanUp = *reinterpret_cast<CMissionCleanup *>(0xA90850);
CStuckCarCheck &CTheScripts::StuckCars = *reinterpret_cast<CStuckCarCheck *>(0xA90AB0);
CScriptsForBrains &CTheScripts::ScriptsForBrains = *reinterpret_cast<CScriptsForBrains *>(0xA90CF0);
tScriptSphere *CTheScripts::ScriptSphereArray = reinterpret_cast<tScriptSphere *>(0xA91268);
tScriptText *CTheScripts::IntroTextLines = reinterpret_cast<tScriptText *>(0xA913E8);
tScriptRectangle *CTheScripts::IntroRectangles = reinterpret_cast<tScriptRectangle *>(0xA92D68);
CSprite2d *CTheScripts::ScriptSprites = reinterpret_cast<CSprite2d *>(0xA94B68);
tScriptSearchlight *CTheScripts::ScriptSearchLightArray = reinterpret_cast<tScriptSearchlight *>(0xA94D68);

void CTheScripts::CleanUpThisVehicle(CVehicle* pVehicle) {
    plugin::CallDynGlobal<CVehicle*>(0x486670, pVehicle);
}

signed int CTheScripts::GetActualScriptThingIndex(int index, unsigned char type) {
    return plugin::CallAndReturnDynGlobal<signed int, int, unsigned char>(0x4839A0, index, type);
}

unsigned int CTheScripts::GetNewUniqueScriptThingIndex(unsigned int index, char type) {
    return plugin::CallAndReturnDynGlobal<unsigned int, unsigned int, char>(0x483720, index, type);
}

int CTheScripts::GetScriptIndexFromPointer(CRunningScript* thread) {
    return plugin::CallAndReturnDynGlobal<int, CRunningScript*>(0x464D20, thread);
}

void CTheScripts::RemoveThisPed(CPed* ped) {
    plugin::CallDynGlobal<CPed*>(0x486240, ped);
}

CRunningScript* CTheScripts::StartNewScript(std::uint8_t* startIP)
{
    return plugin::CallAndReturn<CRunningScript*, 0x464C20, std::uint8_t*>(startIP);
}

bool CTheScripts::IsPlayerOnAMission() {
    return plugin::CallAndReturnDynGlobal<bool>(0x464D50);
}

bool CTheScripts::IsVehicleStopped(CVehicle* pVehicle) {
    return plugin::CallAndReturnDynGlobal<bool, CVehicle*>(0x4861F0, pVehicle);
}

void CTheScripts::WipeLocalVariableMemoryForMissionScript() {
    plugin::CallDynGlobal(0x464BB0);
}
