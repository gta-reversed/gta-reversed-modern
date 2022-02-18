/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "RunningScript.h"
#include "Ped.h"
#include "Vehicle.h"
#include "Object.h"
#include "MissionCleanup.h"
#include "Building.h"
#include "Sprite2d.h"
#include "StreamedScripts.h"
#include "ScriptResourceManager.h"
#include "StuckCarCheck.h"
#include "UpsideDownCarCheck.h"
#include "ScriptsForBrains.h"

struct tBuildingSwap {
    CBuilding* m_pCBuilding;
    int32      m_nNewModelIndex;
    int32      m_nOldModelIndex;
};

struct tScriptSwitchCase {
    int32 m_nSwitchValue;
    int32 m_nSwitchLabelAddress;
};

struct tScriptCheckpoint {
    char  bUsed;
    char  field_1;
    int16 wUniqueID;
    void* field_4;
};
struct tScriptEffectSystem {
    char  bUsed;
    int16 wUniqueID;
    void* m_pFxSystem;
};

struct tScriptSequence {
    char  bUsed;
    int16 wUniqueID;
};

struct tScriptText {
    float  letterWidth;
    int32  letterHeight;
    RwRGBA color;
    char   m_bJustify;
    char   centered;
    char   withBackground;
    char   _pad;
    int32  lineHeight;
    int32  lineWidth;
    RwRGBA backgroundBoxColor;
    char   proportional;
    RwRGBA backgroundColor;
    char   shadowType;
    char   outlineType;
    char   m_bDrawBeforeFade;
    char   m_bRightJustify;
    char   _pad_25;
    char   _pad_26;
    char   _pad_27;
    int32  font;
    int32  xPosition;
    int32  yPosition;
    char   gxtEntry[8];
    int32  param1;
    int32  param2;
};

struct tScriptRectangle {
    int32 type;
    char  m_bDrawBeforeFade;
    char  field_5;
    int16 textureID;
    int32 cornerA_X;
    int32 cornerA_Y;
    int32 cornerB_X;
    int32 cornerB_Y;
    int32 angle;
    int32 transparentColor;
    char  gxt[8];
    int32 field_28;
    int32 field_2C;
    int32 field_30;
    int32 field_34;
    char  textboxStyle;
    char  field_39[3];
};

struct tScriptAttachedAnimGroup {
    int32 m_nModelID;
    char  m_IfpName[16];
};

struct tScriptSearchlight {
    char  bUsed;
    char  field_1;
    char  bEnableShadow;
    char  field_3;
    int16 wUniqueID;
    int16 field_6;
    RwV3d position;
    RwV3d target;
    float targetRadius;
    float baseRadius;
    RwV3d pathCoord1;
    RwV3d pathCoord2;
    float pathSpeed;
    int32 attachedEntity;
    int32 followingEntity;
    int32 tower;
    int32 housing;
    int32 bulb;
    RwV3d targetSpot;
    RwV3d field_64;
    RwV3d field_70;
};

struct tUsedObject {
    char  szModelName[24];
    int32 dwModelIndex;
};

struct tScriptSphere {
    char  bUsed;
    char  field_1;
    int16 wUniqueID;
    int32 field_4;
    RwV3d vCoords;
    int32 fRadius;
};

enum eScriptThingType : int32 {
    SCRIPT_THING_SPHERE = 0,
    SCRIPT_THING_EFFECT_SYSTEM,
    SCRIPT_THING_SEARCH_LIGHT,
    SCRIPT_THING_CHECKPOINT,
    SCRIPT_THING_SEQUENCE_TASK,
    SCRIPT_THING_FIRE,
    SCRIPT_THING_2D_EFFECT,
    SCRIPT_THING_DECISION_MAKER,
    SCRIPT_THING_PED_GROUP
};

class CTheScripts {
public:
    static bool& DbgFlag;
    static tScriptParam* ScriptParams;         // static tScriptParam ScriptParams[10]
    static tScriptSwitchCase* SwitchJumpTable; // static tScriptSwitchCase SwitchJumpTable[75]
    static uint16& NumberOfEntriesInSwitchTable;
    static void*& SwitchDefaultAddress;
    static bool& SwitchDefaultExists;
    static int32& ValueToCheckInSwitchStatement;
    static uint16& NumberOfEntriesStillToReadForSwitch;
    static tScriptSequence* ScriptSequenceTaskArray; // static tScriptSequence ScriptSequenceTaskArray[64]
    static uint16& NumberOfScriptCheckpoints;
    static tScriptCheckpoint* ScriptCheckpointArray;     // static tScriptCheckpoint ScriptCheckpointArray[20]
    static tScriptEffectSystem* ScriptEffectSystemArray; // static tScriptEffectSystem ScriptEffectSystemArray[32]
    static int16& CardStackPosition;
    static int16* CardStack; // static int16 CardStack[312]
    static bool& bDrawSubtitlesBeforeFade;
    static bool& bDrawOddJobTitleBeforeFade;
    static bool& bScriptHasFadedOut;
    static bool& bAddNextMessageToPreviousBriefs;
    static int32& ForceRandomCarModel;
    static bool& bDrawCrossHair;
    static bool& bEnableCraneRelease;
    static bool& bEnableCraneLower;
    static bool& bEnableCraneRaise;
    static float& fCameraHeadingStepWhenPlayerIsAttached;
    static float& fCameraHeadingWhenPlayerIsAttached;
    static bool& bDisplayHud;
    static bool& HideAllFrontEndMapBlips;
    static bool& RadarShowBlipOnAllLevels;
    static uint8& RadarZoomValue;
    static bool& bPlayerIsOffTheMap;
    static char& RiotIntensity;
    static bool& bPlayerHasMetDebbieHarry;
    static bool& bDisplayNonMiniGameHelpMessages;
    static bool& bMiniGameInProgress;
    static int32& ScriptPickupCycleIndex;
    static char& FailCurrentMission;
    static bool& bAlreadyRunningAMissionScript;
    static uint32& LargestNumberOfMissionScriptLocalVariables;
    static uint16& NumberOfExclusiveMissionScripts;
    static uint16& NumberOfMissionScripts;
    static uint32& LargestMissionScriptSize;
    static uint32& MainScriptSize;
    static int32* MultiScriptArray; // static char MultiScriptArray[800]
    static bool& bUsingAMultiScriptFile;
    static int32& StoreVehicleIndex;
    static bool& StoreVehicleWasRandom;
    static uint16& CommandsExecuted;
    static uint16& ScriptsUpdated;
    static int32* ScriptConnectLodsObjects;                      // static int32 ScriptConnectLodsObjects[20]
    static tScriptAttachedAnimGroup* ScriptAttachedAnimGroups; // static tScriptAttachedAnimGroup ScriptAttachedAnimGroups[8]
    static int32* VehicleModelsBlockedByScript;                  // static int32 VehicleModelsBlockedByScript[20]
    static int32* SuppressedVehicleModels;                       // static int32 SuppressedVehicleModels[40]
    static CEntity** InvisibilitySettingArray;                 // static CEntity *InvisibilitySettingArray[20]

    static constexpr int32 NUM_BUILDING_SWAPS = 25;
    static tBuildingSwap (&BuildingSwapArray)[NUM_BUILDING_SWAPS]; // static tBuildingSwap BuildingSwapArray[25]

    static uint16& NumberOfIntroRectanglesThisFrame;
    static uint16& MessageWidth;
    static uint16& MessageCentre;
    static bool& bUseMessageFormatting;
    static uint16& CurrentTextDrawer;
    static bool& UseTextCommands;
    static uint16& NumberOfIntroTextLinesThisFrame;
    static uint16& NumberOfUsedObjects;
    static tUsedObject* UsedObjectArray; // static tUsedObject UsedObjectArray[395]
    static int32& LastRandomPedId;
    static uint32& LastMissionPassedTime;
    static int32& OnAMissionFlag;
    static CEntity*& EntitiesWaitingForScriptBrain;
    static CStreamedScripts& StreamedScripts;
    static CScriptResourceManager& ScriptResourceManager;
    static CUpsideDownCarCheck& UpsideDownCars;
    static tScriptParam* LocalVariablesForCurrentMission; // static ScriptVar LocalVariablesForCurrentMission[1024]
                                                          //! Script space, where main.scm MAIN section is loaded.
    static uint8* ScriptSpace;                     // static char ScriptSpace[200000]
    static char* MissionBlock;                            // static char MissionBlock[69000]
    static CRunningScript*& pIdleScripts;
    static CRunningScript*& pActiveScripts;
    static CRunningScript* ScriptsArray; // static CRunningScript ScriptsArray[96]
    static uint16& NumberOfScriptSearchLights;
    static CMissionCleanup& MissionCleanUp;
    static CStuckCarCheck& StuckCars;
    static CScriptsForBrains& ScriptsForBrains;
    static tScriptSphere* ScriptSphereArray;           // static CScriptSphere ScriptSphereArray[16]
    static tScriptText* IntroTextLines;                // static tScriptText IntroTextLines[96]
    static tScriptRectangle* IntroRectangles;          // static tScriptRectangle IntroRectangles[128]
    static CSprite2d* ScriptSprites;                   // static CSprite2d ScriptSprites[128]
    static tScriptSearchlight* ScriptSearchLightArray; // static tScriptSearchlight ScriptSearchLightArray[8]

public:
    static void InjectHooks();

    static void Init();
    static void InitialiseAllConnectLodObjects();
    static void InitialiseConnectLodObjects(uint16 a1);
    static void InitialiseSpecialAnimGroup(uint16 a1);
    static void InitialiseSpecialAnimGroupsAttachedToCharModels();

    static int32 AddScriptCheckpoint(float atX, float atY, float atZ, float PointToX, float PointToY, float PointToZ, float radius, int32 type);
    static int32 AddScriptEffectSystem(FxSystem_c* a1);
    static int32 AddScriptSearchLight(float startX, float startY, float startZ, CEntity* entity, float targetX, float targetY, float targetZ, float targetRadius, float baseRadius);
    static uint32 AddScriptSphere(uint32 id, CVector posn, float radius);

    static void AddToBuildingSwapArray(CBuilding* building, int32 oldModelId, int32 newModelId);
    static void AddToInvisibilitySwapArray(CEntity* a2, bool bVisible);
    static void AddToListOfConnectedLodObjects(CObject* pObject1, CObject* pObject2);
    static void AddToListOfSpecialAnimGroupsAttachedToCharModels(int32 modelId, char* ifpName);
    static double AddToSwitchJumpTable(int32 switchValue, int32 switchLabelLocalAddress);
    static void AddToVehicleModelsBlockedByScript(int32 modelIndex);
    static void AddToWaitingForScriptBrainArray(CEntity* entity, int16 arg2);
    static void AttachSearchlightToSearchlightObject(int32 searchLightId, CObject* tower, CObject* housing, CObject* bulb, float offsetX, float offsetY, float offsetZ);
    static char CheckStreamedScriptVersion(RwStream* arg1, char* arg2);
    static void CleanUpThisObject(CObject* obj);
    static void CleanUpThisPed(CPed* ped);
    static void CleanUpThisVehicle(CVehicle* vehicle);
    static void ClearAllSuppressedCarModels();
    static void ClearAllVehicleModelsBlockedByScript();
    static void ClearSpaceForMissionEntity(const CVector& pos, CEntity* entity);
    static void DoScriptSetupAfterPoolsHaveLoaded();
    static void DrawDebugAngledSquare(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
    static void DrawDebugCube(float x1, float y1, float x2, float y2);
    static void DrawScriptSpheres();
    static void DrawScriptSpritesAndRectangles(char bDrawBeforeFade);
    static int32 GetActualScriptThingIndex(int32 index, uint8 type);
    static uint32 GetNewUniqueScriptThingIndex(uint32 index, char type);
    static int32 GetScriptIndexFromPointer(CRunningScript* thread);
    //! type is always 8 , which refers to PedGroups
    static uint32 GetUniqueScriptThingIndex(int32 playerGroup, uint8 type);
    static bool HasVehicleModelBeenBlockedByScript(int32 modelIndex);
    static void HighlightImportantAngledArea(uint32 markerId, float fromX, float fromY, float toX, float toY, float angledToX, float angledToY, float angledFromX, float angledFromY, float height);
    static void HighlightImportantArea(int32 markerId, float fromX, float fromY, float toX, float toY, float height);

    static bool IsEntityWithinAnySearchLight(CEntity* entity, int32* pIndex);
    static bool IsEntityWithinSearchLight(uint32 index, CEntity* entity);
    static bool IsPedStopped(CPed* ped);
    static bool IsPlayerOnAMission();
    static bool IsPointWithinSearchLight(CVector* pointPosn, int32 index);
    static bool IsVehicleStopped(CVehicle* vehicle);

    static bool Load();
    static bool Save();

    static void MoveSearchLightBetweenTwoPoints(int32 index, float x1, float y1, float z1, float x2, float y2, float z2, float pathSpeed);
    static void MoveSearchLightToEntity(int32 index, CEntity* entity, float pathSpeed);
    static void MoveSearchLightToPointAndStop(int32 index, float x, float y, float z, float pathSpeed);
    static void PrintListSizes();

    static void Process();
    static void ProcessAllSearchLights();
    static void ProcessWaitingForScriptBrainArray();

    static void ReadMultiScriptFileOffsetsFromScript();
    static void ReadObjectNamesFromScript();
    static void ReinitialiseSwitchStatementData();

    static void RemoveFromVehicleModelsBlockedByScript(int32 modelIndex);
    static int32 RemoveFromWaitingForScriptBrainArray(CEntity* a1, int16 modelIndex);
    static void RemoveScriptCheckpoint(int32 arg1);
    static void RemoveScriptEffectSystem(int32 arg1);
    static void RemoveScriptSearchLight(uint32 index);
    static void RemoveScriptSphere(int32 index);
    static void RemoveScriptTextureDictionary();
    static void RemoveThisPed(CPed* ped);

    static void RenderAllSearchLights();
    static bool ScriptAttachAnimGroupToCharModel(int32 modelId, char* ifpName);
    static void ScriptConnectLodsFunction(int32 objectHandle1, int32 objectHandle2);
    static void ScriptDebugCircle2D(float x, float y, float width, float height, CRGBA color);
    static CRunningScript* StartNewScript(uint8* startIP);
    // static int32 StartNewScript(uint8* startIP, uint16 index); // seems unused
    static void StartTestScript();
    static void UndoBuildingSwaps();
    static void UndoEntityInvisibilitySettings();
    static void UpdateObjectIndices();
    static void UseSwitchJumpTable(int32* pSwitchLabelAddress);
    static void WipeLocalVariableMemoryForMissionScript();

    static int32* GetPointerToScriptVariable(uint32 offset) {
        // TODO: find out how this method changed between re3 and GTA:SA
        assert(offset >= 8 && offset < CTheScripts::GetSizeOfVariableSpace());
        return (int32*)&ScriptSpace[offset];
    }

    static int32 Read4BytesFromScript(uint8*& ip) {
        int32 retval = *reinterpret_cast<int32*>(ip); // big-endian unfriendly/unaligned mem access
        ip += 4;
        return retval;
    }
    static int16 Read2BytesFromScript(uint8*& ip) {
        int16 retval = *reinterpret_cast<int16*>(ip);
        ip += 2;
        return retval;
    }
    static int8 Read1ByteFromScript(uint8*& ip) {
        int8 retval = *reinterpret_cast<int8*>(ip);
        ip += 1;
        return retval;
    }
    static float ReadFloatFromScript(uint8*& ip) {
        int32 retval = Read4BytesFromScript(ip);
        return *reinterpret_cast<float*>(&retval);
    }

    static int32 GetSizeOfVariableSpace() {
        uint8* tmp = &ScriptSpace[3];
        return Read4BytesFromScript(tmp);
    }
};
