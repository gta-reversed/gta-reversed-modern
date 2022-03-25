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

    tBuildingSwap() { // 0x469270
        Clear();
    }

    tBuildingSwap(CBuilding* building, int32 nNewModelIndex, int32 nOldModelIndex) {
        m_pCBuilding     = building;
        m_nNewModelIndex = nNewModelIndex;
        m_nOldModelIndex = nOldModelIndex;
    }

    void Clear() {
        m_pCBuilding     = nullptr;
        m_nNewModelIndex = -1;
        m_nOldModelIndex = -1;
    }
};

struct tScriptSwitchCase {
    int32 m_nSwitchValue;
    int32 m_nSwitchLabelAddress;
};
VALIDATE_SIZE(tScriptSwitchCase, 0x8);

struct tScriptCheckpoint {
    bool  m_bUsed;
    char  m_field_1;
    int16 m_nId;
    void* m_field_4;

    tScriptCheckpoint() { // 0x469334
        m_bUsed   = false;
        m_nId     = 1;
        m_field_4 = nullptr;
    }
};
VALIDATE_SIZE(tScriptCheckpoint, 0x8);

struct tScriptEffectSystem {
    char  bUsed;
    int16 nId;
    void* m_pFxSystem;
};
VALIDATE_SIZE(tScriptEffectSystem, 0x8);

struct tScriptSequence {
    bool  bUsed;
    int16 nId;
};
VALIDATE_SIZE(tScriptSequence, 0x4);

struct tScriptText {
    float     letterWidth;
    int32     letterHeight;
    RwRGBA    color;
    bool      m_bJustify;
    bool      m_bCentered;
    bool      m_bWithBackground;
    float     m_fLineHeight;
    float     m_fLineWidth;
    RwRGBA    backgroundBoxColor;
    bool      m_bProportional;
    RwRGBA    backgroundColor;
    int8      m_nShadowType;
    int8      m_nOutlineType;
    bool      m_bDrawBeforeFade;
    bool      m_bRightJustify;
    int32     font;
    CVector2D pos;
    char      gxtEntry[8];
    int32     param1;
    int32     param2;

    void Init(); // 0x4690A8
};
VALIDATE_SIZE(tScriptText, 0x44);

struct tScriptRectangle {
    int32     m_nType;
    bool      m_bDrawBeforeFade;
    char      field_5;
    int16     m_nTextureId;
    CVector2D cornerA;
    CVector2D cornerB;
    int32     m_nAngle;
    CRGBA     m_nTransparentColor;
    char      gxt[8];
    int32     field_28;
    int32     field_2C;
    int32     field_30;
    int32     field_34;
    uint32    m_nTextboxStyle;

    void Init() { // 0x4691C8
        m_nType             = 0;
        m_bDrawBeforeFade   = false;
        m_nTextureId        = -1;
        cornerA             = CVector2D();
        cornerB             = CVector2D();
        m_nAngle            = 0;
        m_nTransparentColor = CRGBA(255, 255, 255, 255);
        gxt[0]              = 0;
        m_nTextboxStyle     = 3;
    }
};
VALIDATE_SIZE(tScriptRectangle, 0x3C);

struct tScriptAttachedAnimGroup {
    int32 m_nModelID;
    char  m_IfpName[16];
};

struct tScriptSearchlight {
    bool     bUsed;
    char     field_1;
    bool     bEnableShadow;
    char     field_3;
    int16    nId;
    int16    field_6;
    CVector  position;
    CVector  target;
    float    fTargetRadius;
    float    fBaseRadius;
    CVector  vPathCoord1;
    CVector  vPathCoord2;
    float    fPathSpeed;
    CEntity* pAttachedEntity;
    CEntity* pFollowingEntity;
    CEntity* pTower;
    CEntity* pHousing;
    CEntity* pBulb;
    CVector  vTargetSpot;
    CVector  vf64;
    CVector  vf70;
};
VALIDATE_SIZE(tScriptSearchlight, 0x7C);

struct tUsedObject {
    char  szModelName[24];
    int32 nModelIndex;

    tUsedObject() = default; // 0x468F20
};
VALIDATE_SIZE(tUsedObject, 0x1C);

struct tScriptSphere {
    bool    m_bUsed;
    char    m_f1;
    int16   m_f2;
    int32   m_nId;
    CVector m_vCoords;
    float   m_fRadius;

    tScriptSphere() { // 0x469060
        m_vCoords = CVector();
        m_bUsed   = false;
        m_f2      = 1;
        m_nId     = 0;
        m_fRadius = 0.0f;
    }
};
VALIDATE_SIZE(tScriptSphere, 0x18);

struct tStoredLine {
    CVector vecInf;
    CVector vecSup;
    uint32  color1;
    uint32  color2;
};
VALIDATE_SIZE(tStoredLine, 0x20);

struct tScriptBrainWaitEntity {
    CEntity* m_pEntity;
    int16    m_nSpecialModelIndex;
    int16    field_6;

    tScriptBrainWaitEntity() { // 0x468E12
        m_pEntity = nullptr;
        m_nSpecialModelIndex = -1;
    }
};
VALIDATE_SIZE(tScriptBrainWaitEntity, 0x8);

enum {
    MAX_NUM_SCRIPTS               = 96,
    MAX_NUM_SCRIPT_SPRITES        = 128,
    MAX_NUM_SCRIPT_SPHERES        = 16,
    MAX_NUM_USED_OBJECTS          = 395,
    MAX_NUM_MISSION_SCRIPTS       = 200,
    MAX_NUM_BUILDING_SWAPS        = 25,
    MAX_NUM_INVISIBILITY_SETTINGS = 20,
    MAX_NUM_INTRO_TEXT_LINES      = 96,
    MAX_NUM_SCRIPT_RECTANGLES     = 128,
    MAX_NUM_SCRIPT_SEARCH_LIGHT   = 8,
    MAX_NUM_SCRIPT_SEQUENCE_TASKS = 64,
    MAX_NUM_SCRIPT_CHECKPOINTS    = 20,
    MAX_NUM_SCRIPT_EFFECT_SYSTEMS = 32,
    MAX_NUM_STORED_LINES          = 1024
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
    static inline std::array<tScriptSequence, MAX_NUM_SCRIPT_SEQUENCE_TASKS>& ScriptSequenceTaskArray = *(std::array<tScriptSequence, MAX_NUM_SCRIPT_SEQUENCE_TASKS>*)0xA43F68;
    static uint16& NumberOfScriptCheckpoints;
    static inline std::array<tScriptCheckpoint, MAX_NUM_SCRIPT_CHECKPOINTS>& ScriptCheckpointArray = *(std::array<tScriptCheckpoint, MAX_NUM_SCRIPT_CHECKPOINTS>*)0xA44070;
    static inline std::array<tScriptEffectSystem, MAX_NUM_SCRIPT_EFFECT_SYSTEMS>& ScriptEffectSystemArray = *(std::array<tScriptEffectSystem, MAX_NUM_SCRIPT_EFFECT_SYSTEMS>*)0xA44110;
    static int16& CardStackPosition;
    static inline std::array<int16, 312>& CardStack = *(std::array<int16, 312>*)0xA44218;
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
    static inline std::array<int32, MAX_NUM_MISSION_SCRIPTS>& MultiScriptArray = *(std::array<int32, MAX_NUM_MISSION_SCRIPTS>*)0xA444C8;
    static bool& bUsingAMultiScriptFile;
    static int32& StoreVehicleIndex;
    static bool& StoreVehicleWasRandom;
    static uint16& CommandsExecuted;
    static uint16& ScriptsUpdated;

    static inline std::array<int32*, 20>&                   ScriptConnectLodsObjects = *(std::array<int32*, 20>*)0xA44800;
    static inline std::array<tScriptAttachedAnimGroup*, 8>& ScriptAttachedAnimGroups = *(std::array<tScriptAttachedAnimGroup*, 8>*)0xA44850;
    static inline std::array<int32*, 20>&                   VehicleModelsBlockedByScript = *(std::array<int32*, 20>*)0xA448F0;
    static inline std::array<int32*, 40>&                   SuppressedVehicleModels = *(std::array<int32*, 40>*)0xA44940;
    static inline std::array<CEntity*, MAX_NUM_INVISIBILITY_SETTINGS>&   InvisibilitySettingArray = *(std::array<CEntity*, MAX_NUM_INVISIBILITY_SETTINGS>*)0xA449E0;
    static inline std::array<tBuildingSwap, MAX_NUM_BUILDING_SWAPS>&     BuildingSwapArray = *(std::array<tBuildingSwap, MAX_NUM_BUILDING_SWAPS>*)0xA44A30;

    static uint16& NumberOfIntroRectanglesThisFrame;
    static uint16& MessageWidth;
    static uint16& MessageCentre;
    static bool& bUseMessageFormatting;
    static uint16& CurrentTextDrawer;
    static bool& UseTextCommands;
    static uint16& NumberOfIntroTextLinesThisFrame;
    static uint16& NumberOfUsedObjects;
    static inline std::array<tUsedObject, MAX_NUM_USED_OBJECTS>& UsedObjectArray = *(std::array<tUsedObject, MAX_NUM_USED_OBJECTS>*)0xA44B70;
    static int32& LastRandomPedId;
    static uint32& LastMissionPassedTime;
    static int32& OnAMissionFlag;
    static inline std::array<tScriptBrainWaitEntity, 150>& EntitiesWaitingForScriptBrain = *(std::array<tScriptBrainWaitEntity, 150>*)0xA476B0;
    static CStreamedScripts& StreamedScripts;
    static CScriptResourceManager& ScriptResourceManager;
    static CUpsideDownCarCheck& UpsideDownCars;
    static tScriptParam* LocalVariablesForCurrentMission; // static ScriptVar LocalVariablesForCurrentMission[1024]
                                                          // Script space, where main.scm MAIN section is loaded.
    static uint8* ScriptSpace;                            // static char ScriptSpace[200000]
    static char* MissionBlock;                            // static char MissionBlock[69000]
    static CRunningScript*& pIdleScripts;
    static CRunningScript*& pActiveScripts;
    static inline std::array<CRunningScript, MAX_NUM_SCRIPTS>& ScriptsArray = *(std::array<CRunningScript, MAX_NUM_SCRIPTS>*)0xA8B430;
    static uint16& NumberOfScriptSearchLights;
    static CMissionCleanup& MissionCleanUp;
    static CStuckCarCheck& StuckCars;
    static CScriptsForBrains& ScriptsForBrains;

    static inline std::array<tScriptSphere, MAX_NUM_SCRIPT_SPHERES>&           ScriptSphereArray = *(std::array<tScriptSphere, MAX_NUM_SCRIPT_SPHERES>*)0xA91268;
    static inline std::array<tScriptText, MAX_NUM_INTRO_TEXT_LINES>&           IntroTextLines = *(std::array<tScriptText, MAX_NUM_INTRO_TEXT_LINES>*)0xA913E8;
    static inline std::array<tScriptRectangle, MAX_NUM_SCRIPT_RECTANGLES>&     IntroRectangles = *(std::array<tScriptRectangle, MAX_NUM_SCRIPT_RECTANGLES>*)0xA92D68;
    static inline std::array<CSprite2d, MAX_NUM_SCRIPT_SPRITES>&               ScriptSprites = *(std::array<CSprite2d, MAX_NUM_SCRIPT_SPRITES>*)0xA94B68;
    static inline std::array<tScriptSearchlight, MAX_NUM_SCRIPT_SEARCH_LIGHT>& ScriptSearchLightArray = *(std::array<tScriptSearchlight, MAX_NUM_SCRIPT_SEARCH_LIGHT>*)0xA94D68;

public:
    static void InjectHooks();

    static void Init();
    static void InitialiseAllConnectLodObjects();
    static void InitialiseConnectLodObjects(uint16 a1);
    static void InitialiseSpecialAnimGroup(uint16 a1);
    static void InitialiseSpecialAnimGroupsAttachedToCharModels();
    static void ReadObjectNamesFromScript();
    static void UpdateObjectIndices();
    static void ReadMultiScriptFileOffsetsFromScript();

    static int32 AddScriptCheckpoint(float atX, float atY, float atZ, float pointToX, float pointToY, float pointToZ, float radius, int32 type);
    static int32 AddScriptEffectSystem(FxSystem_c* system);
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
    static char CheckStreamedScriptVersion(RwStream* stream, char* arg2);
    static void CleanUpThisObject(CObject* obj);
    static void CleanUpThisPed(CPed* ped);
    static void CleanUpThisVehicle(CVehicle* vehicle);
    static void ClearAllSuppressedCarModels();
    static void ClearAllVehicleModelsBlockedByScript();
    static void ClearSpaceForMissionEntity(const CVector& pos, CEntity* entity);
    static void DoScriptSetupAfterPoolsHaveLoaded();

    static int32 GetActualScriptThingIndex(int32 index, uint8 type);
    static uint32 GetNewUniqueScriptThingIndex(uint32 index, char type);
    static int32 GetScriptIndexFromPointer(CRunningScript* thread);
    //! type is always 8 , which refers to PedGroups
    static uint32 GetUniqueScriptThingIndex(int32 playerGroup, uint8 type);
    static bool HasVehicleModelBeenBlockedByScript(int32 modelIndex);

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

    static void Process();
    static void ProcessAllSearchLights();
    static void ProcessWaitingForScriptBrainArray();

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
    static int32 StartNewScript(uint8* startIP, uint16 index);
    static void StartTestScript();
    static void UndoBuildingSwaps();
    static void UndoEntityInvisibilitySettings();
    static void UseSwitchJumpTable(int32* pSwitchLabelAddress);
    static void WipeLocalVariableMemoryForMissionScript();

    // DEBUG
    static void ScriptDebugLine3D(const CVector& start, const CVector& end, uint32 color1, uint32 color2);
    static void RenderTheScriptDebugLines();

    static void PrintListSizes();

    static void DrawScriptSpheres();
    static void HighlightImportantArea(uint32 markerId, float fromX, float fromY, float toX, float toY, float height);
    static void HighlightImportantAngledArea(uint32 markerId, float fromX, float fromY, float toX, float toY, float angledToX, float angledToY, float angledFromX, float angledFromY, float height);
    static void DrawDebugSquare(float, float, float, float);
    static void DrawDebugAngledSquare(const CVector2D& inf, const CVector2D& sup, const CVector2D& rotSup, const CVector2D& rotInf);
    static void DrawDebugCube(const CVector& inf, const CVector& sup);
    static void DrawDebugAngledCube(const CVector& inf, const CVector& sup, const CVector2D& rotSup, const CVector2D& rotInf);
    static void DrawScriptSpritesAndRectangles(bool bDrawBeforeFade);

    static int32* GetPointerToScriptVariable(uint32 offset) {
        assert(offset >= 8 && offset < CTheScripts::GetSizeOfVariableSpace());
        return (int32*)&ScriptSpace[offset];
    }

    static int32 Read4BytesFromScript(uint32* ip) {
        int32 retval = ScriptSpace[*ip + 3] << 24 | ScriptSpace[*ip + 2] << 16 | ScriptSpace[*ip + 1] << 8 | ScriptSpace[*ip];
        *ip += 4;
        return retval;
    }
    static int16 Read2BytesFromScript(uint32* ip) {
        int16 retval = ScriptSpace[*ip + 1] << 8 | ScriptSpace[*ip];
        *ip += 2;
        return retval;
    }
    static int8 Read1ByteFromScript(uint32* ip) {
        int8 retval = ScriptSpace[*ip];
        *ip += 1;
        return retval;
    }
    static float ReadFloatFromScript(uint32* ip) {
        return Read2BytesFromScript(ip) / 16.0f;
    }

    static int32 GetSizeOfVariableSpace() {
        uint32 tmp = 3;
        return Read4BytesFromScript(&tmp);
    }
};
