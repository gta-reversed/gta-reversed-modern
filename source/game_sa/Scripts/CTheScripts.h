/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CRunningScript.h"
#include "CPed.h"
#include "CVehicle.h"
#include "CObject.h"
#include "CMissionCleanup.h"
#include "CBuilding.h"
#include "CSprite2d.h"
#include "CStreamedScripts.h"
#include "CScriptResourceManager.h"
#include "CStuckCarCheck.h"
#include "CUpsideDownCarCheck.h"
#include "CScriptsForBrains.h"

struct tBuildingSwap
{
    CBuilding *m_pCBuilding;
    int m_nOldModelIndex;
    int m_nNewModelIndex;
};

struct tScriptSwitchCase
{
    int m_nSwitchValue;
    int m_nSwitchLabelAddress;
};

struct tScriptCheckpoint
{
    char bUsed;
    char field_1;
    short wUniqueID;
    void *field_4;
};
struct tScriptEffectSystem
{
    char bUsed;
    short wUniqueID;
    void *m_pFxSystem;
};

struct tScriptSequence
{
    char bUsed;
    short wUniqueID;
};

struct tScriptText
{
    float letterWidth;
    int letterHeight;
    RwRGBA color;
    char m_bJustify;
    char centered;
    char withBackground;
    char _pad;
    int lineHeight;
    int lineWidth;
    RwRGBA backgroundBoxColor;
    char proportional;
    RwRGBA backgroundColor;
    char shadowType;
    char outlineType;
    char m_bDrawBeforeFade;
    char m_bRightJustify;
    char _pad_25;
    char _pad_26;
    char _pad_27;
    int font;
    int xPosition;
    int yPosition;
    char gxtEntry[8];
    int param1;
    int param2;
};

struct tScriptRectangle
{
    int type;
    char m_bDrawBeforeFade;
    char field_5;
    short textureID;
    int cornerA_X;
    int cornerA_Y;
    int cornerB_X;
    int cornerB_Y;
    int angle;
    int transparentColor;
    char gxt[8];
    int field_28;
    int field_2C;
    int field_30;
    int field_34;
    char textboxStyle;
    char field_39[3];
};

struct tScriptAttachedAnimGroup
{
    int m_nModelID;
    char m_IfpName[16];
};

struct tScriptSearchlight
{
    char bUsed;
    char field_1;
    char bEnableShadow;
    char field_3;
    short wUniqueID;
    short field_6;
    RwV3d position;
    RwV3d target;
    float targetRadius;
    float baseRadius;
    RwV3d pathCoord1;
    RwV3d pathCoord2;
    float pathSpeed;
    int attachedEntity;
    int followingEntity;
    int tower;
    int housing;
    int bulb;
    RwV3d targetSpot;
    RwV3d field_64;
    RwV3d field_70;
};

struct tUsedObject
{
    char szModelName[24];
    int dwModelIndex;
};

struct tScriptSphere
{
    char bUsed;
    char field_1;
    short wUniqueID;
    int field_4;
    RwV3d vCoords;
    int fRadius;
};

enum eScriptThingType : std::int32_t
{
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

class CTheScripts
{
public:
     static bool &DbgFlag;
     static tScriptParam *ScriptParams; // static tScriptParam ScriptParams[10]
     static tScriptSwitchCase *SwitchJumpTable; // static tScriptSwitchCase SwitchJumpTable[75]
     static unsigned short &NumberOfEntriesInSwitchTable;
     static void *&SwitchDefaultAddress;
     static bool &SwitchDefaultExists;
     static int &ValueToCheckInSwitchStatement;
     static unsigned short &NumberOfEntriesStillToReadForSwitch;
     static tScriptSequence *ScriptSequenceTaskArray; // static tScriptSequence ScriptSequenceTaskArray[64]
     static unsigned short &NumberOfScriptCheckpoints;
     static tScriptCheckpoint *ScriptCheckpointArray; // static tScriptCheckpoint ScriptCheckpointArray[20]
     static tScriptEffectSystem *ScriptEffectSystemArray; // static tScriptEffectSystem ScriptEffectSystemArray[32]
     static short &CardStackPosition;
     static short *CardStack; // static short CardStack[312]
     static bool &bDrawSubtitlesBeforeFade;
     static bool &bDrawOddJobTitleBeforeFade;
     static bool &bScriptHasFadedOut;
     static bool &bAddNextMessageToPreviousBriefs;
     static int &ForceRandomCarModel;
     static bool &bDrawCrossHair;
     static bool &bEnableCraneRelease;
     static bool &bEnableCraneLower;
     static bool &bEnableCraneRaise;
     static float &fCameraHeadingStepWhenPlayerIsAttached;
     static float &fCameraHeadingWhenPlayerIsAttached;
     static bool &bDisplayHud;
     static bool &HideAllFrontEndMapBlips;
     static bool &RadarShowBlipOnAllLevels;
     static unsigned char &RadarZoomValue;
     static bool &bPlayerIsOffTheMap;
     static char &RiotIntensity;
     static bool &bPlayerHasMetDebbieHarry;
     static bool &bDisplayNonMiniGameHelpMessages;
     static bool &bMiniGameInProgress;
     static int &ScriptPickupCycleIndex;
     static char &FailCurrentMission;
     static bool &bAlreadyRunningAMissionScript;
     static unsigned int &LargestNumberOfMissionScriptLocalVariables;
     static unsigned short &NumberOfExclusiveMissionScripts;
     static unsigned short &NumberOfMissionScripts;
     static unsigned int &LargestMissionScriptSize;
     static unsigned int &MainScriptSize;
     static int *MultiScriptArray; // static char MultiScriptArray[800]
     static bool &bUsingAMultiScriptFile;
     static int &StoreVehicleIndex;
     static bool &StoreVehicleWasRandom;
     static unsigned short &CommandsExecuted;
     static unsigned short &ScriptsUpdated;
     static int *ScriptConnectLodsObjects; // static int ScriptConnectLodsObjects[20]
     static tScriptAttachedAnimGroup *ScriptAttachedAnimGroups; // static tScriptAttachedAnimGroup ScriptAttachedAnimGroups[8]
     static int *VehicleModelsBlockedByScript; // static int VehicleModelsBlockedByScript[20]
     static int *SuppressedVehicleModels; // static int SuppressedVehicleModels[40]
     static CEntity **InvisibilitySettingArray; // static CEntity *InvisibilitySettingArray[20]
     static tBuildingSwap *BuildingSwapArray; // static tBuildingSwap BuildingSwapArray[25]
     static unsigned short &NumberOfIntroRectanglesThisFrame;
     static unsigned short &MessageWidth;
     static unsigned short &MessageCentre;
     static bool &bUseMessageFormatting;
     static bool &UseTextCommands;
     static unsigned short &NumberOfIntroTextLinesThisFrame;
     static unsigned short &NumberOfUsedObjects;
     static tUsedObject *UsedObjectArray; // static tUsedObject UsedObjectArray[395]
     static int &LastRandomPedId;
     static unsigned int &LastMissionPassedTime;
     static int &OnAMissionFlag;
     static CEntity *&EntitiesWaitingForScriptBrain;
     static CStreamedScripts &StreamedScripts;
     static CScriptResourceManager &ScriptResourceManager;
     static CUpsideDownCarCheck &UpsideDownCars;
     static tScriptParam *LocalVariablesForCurrentMission; // static ScriptVar LocalVariablesForCurrentMission[1024]
    //! Script space, where main.scm MAIN section is loaded.
     static std::uint8_t* ScriptSpace; // static char ScriptSpace[200000]
     static char *MissionBlock; // static char MissionBlock[69000]
     static CRunningScript *&pIdleScripts;
     static CRunningScript *&pActiveScripts;
     static CRunningScript *ScriptsArray; // static CRunningScript ScriptsArray[96]
     static unsigned short &NumberOfScriptSearchLights;
     static CMissionCleanup &MissionCleanUp;
     static CStuckCarCheck &StuckCars;
     static CScriptsForBrains &ScriptsForBrains;
     static tScriptSphere *ScriptSphereArray; // static CScriptSphere ScriptSphereArray[16]
     static tScriptText *IntroTextLines; // static tScriptText IntroTextLines[96]
     static tScriptRectangle *IntroRectangles; // static tScriptRectangle IntroRectangles[128]
     static CSprite2d *ScriptSprites; // static CSprite2d ScriptSprites[128]
     static tScriptSearchlight *ScriptSearchLightArray; // static tScriptSearchlight ScriptSearchLightArray[8]

     static int AddScriptCheckpoint(float at_X, float at_Y, float at_Z, float PointTo_X, float PointTo_Y, float PointTo_Z, float radius, int type);
     static int AddScriptEffectSystem(FxSystem_c *a1);
     static int AddScriptSearchLight(float startX, float startY, float startZ, CEntity *entity, float targetX, float targetY, float targetZ, float targetRadius, float baseRadius);
     static unsigned int AddScriptSphere(unsigned int id, CVector posn, float radius);
     static void AddToBuildingSwapArray(CBuilding *a1, int newModelId, int oldModelId);
     static void AddToInvisibilitySwapArray(CEntity *a2, bool bVisible);
     static void AddToListOfConnectedLodObjects(CObject *pObject1, CObject *pObject2);
     static void AddToListOfSpecialAnimGroupsAttachedToCharModels(int modelid, char *ifpName);
     static double AddToSwitchJumpTable(int switchValue, int switchLabelLocalAddress);
     static void AddToVehicleModelsBlockedByScript(int modelindex);
     static void AddToWaitingForScriptBrainArray(CEntity *pEntity, short arg2);
     static void AttachSearchlightToSearchlightObject(int searchlightid, CObject *tower, CObject *housing, CObject *bulb, float offsetX, float offsetY, float offsetZ);
     static char CheckStreamedScriptVersion(RwStream *arg1, char *arg2);
     static void CleanUpThisObject(CObject *pObject);
     static void CleanUpThisPed(CPed *ped);
     static void CleanUpThisVehicle(CVehicle *pVehicle);
     static void ClearAllSuppressedCarModels();
     static void ClearAllVehicleModelsBlockedByScript();
     static void ClearSpaceForMissionEntity(CVector const &pos, CEntity *pEntity);
     static void DoScriptSetupAfterPoolsHaveLoaded();
     static void DrawDebugAngledSquare(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4);
     static void DrawDebugCube(float x1, float y1, float x2, float y2);
     static void DrawScriptSpheres();
     static void DrawScriptSpritesAndRectangles(char bDrawBeforeFade);
     static signed int GetActualScriptThingIndex(int index, unsigned char type);
     static unsigned int GetNewUniqueScriptThingIndex(unsigned int index, char type);
     static int GetScriptIndexFromPointer(CRunningScript *thread);
    //! type is always 8 , which refers to PedGroups
     static unsigned int GetUniqueScriptThingIndex(int playergroup, unsigned char type);
     static bool HasVehicleModelBeenBlockedByScript(int modelindex);
     static void HighlightImportantAngledArea(unsigned int markerid, float from_X, float from_Y, float to_X, float to_Y, float angledTo_X, float angledTo_Y, float angledFrom_X, float angledFrom_Y, float height);
     static void HighlightImportantArea(int markerid, float from_X, float from_Y, float to_X, float to_Y, float height);
     static void Init();
     static void InitialiseAllConnectLodObjects();
     static void InitialiseConnectLodObjects(unsigned short a1);
     static void InitialiseSpecialAnimGroup(unsigned short a1);
     static void InitialiseSpecialAnimGroupsAttachedToCharModels();
     static bool IsEntityWithinAnySearchLight(CEntity *pEntity, int *pIndex);
     static bool IsEntityWithinSearchLight(unsigned int index, CEntity *pEntity);
     static bool IsPedStopped(CPed *ped);
     static bool IsPlayerOnAMission();
     static bool IsPointWithinSearchLight(CVector *pointPosn, int index);
     static bool IsVehicleStopped(CVehicle *pVehicle);
     static void Load();
     static void MoveSearchLightBetweenTwoPoints(int index, float x1, float y1, float z1, float x2, float y2, float z2, float pathSpeed);
     static void MoveSearchLightToEntity(int index, CEntity *pEntity, float pathSpeed);
     static void MoveSearchLightToPointAndStop(int index, float x, float y, float z, float pathSpeed);
     static void PrintListSizes();
     static void Process();
     static void ProcessAllSearchLights();
     static void ProcessWaitingForScriptBrainArray();
     static void ReadMultiScriptFileOffsetsFromScript();
     static void ReadObjectNamesFromScript();
     static void ReinitialiseSwitchStatementData();
     static void RemoveFromVehicleModelsBlockedByScript(int modelindex);
     static int RemoveFromWaitingForScriptBrainArray(CEntity *a1, short modelIndex);
     static void RemoveScriptCheckpoint(int arg1);
     static void RemoveScriptEffectSystem(int arg1);
     static void RemoveScriptSearchLight(unsigned int index);
     static void RemoveScriptSphere(int index);
     static void RemoveScriptTextureDictionary();
     static void RemoveThisPed(CPed *ped);
     static void RenderAllSearchLights();
     static void Save();
     static bool ScriptAttachAnimGroupToCharModel(int modelId, char *ifpName);
     static void ScriptConnectLodsFunction(int objecthandle1, int objecthandle2);
     static void ScriptDebugCircle2D(float x, float y, float width, float height, CRGBA color);
     static CRunningScript* StartNewScript(std::uint8_t* startIP);
     static int StartNewScript(unsigned char *startIP, unsigned short index);
     static void StartTestScript();
     static void UndoBuildingSwaps();
     static void UndoEntityInvisibilitySettings();
     static void UpdateObjectIndices();
     static void UseSwitchJumpTable(int *pSwitchLabelAddress);
     static void WipeLocalVariableMemoryForMissionScript();
};

//#include "meta/meta.CTheScripts.h"
