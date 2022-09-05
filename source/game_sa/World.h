/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

class CPlayerInfo;
class CColPoint;
class CStoredCollPoly;
class CSector;
class CRepeatSector;
class CPtrListSingleLink;
class CPed;
class CVehicle;

constexpr int32 MAX_PLAYERS = 2;
constexpr int32 MAX_WORLD_UNITS = 6000;

constexpr int32 MAX_SECTORS_X = 120;
constexpr int32 MAX_SECTORS_Y = 120;
constexpr int32 MAX_SECTORS = MAX_SECTORS_X * MAX_SECTORS_Y;

constexpr int32 MAX_REPEAT_SECTORS_X = 16;
constexpr int32 MAX_REPEAT_SECTORS_Y = 16;
constexpr int32 MAX_REPEAT_SECTORS = MAX_REPEAT_SECTORS_X * MAX_REPEAT_SECTORS_Y;

constexpr int32 MAX_LOD_PTR_LISTS_X = 30;
constexpr int32 MAX_LOD_PTR_LISTS_Y = 30;
constexpr int32 MAX_LOD_PTR_LISTS = MAX_LOD_PTR_LISTS_X * MAX_LOD_PTR_LISTS_Y;

constexpr inline CRect WORLD_BOUNDS{-3000.0F, -3000.0F, 3000.0F, 3000.0F};
constexpr float MAP_Z_LOW_LIMIT = -100.0f;

class CWorld {
public:
    static int32& ms_iProcessLineNumCrossings;
    static float& fWeaponSpreadRate;
    // entity to ignore
    static CEntity*& pIgnoreEntity;
    static bool& bSecondShift;
    static bool& bProcessCutsceneOnly;
    static bool& bForceProcessControl;
    static bool& bIncludeBikers;
    static bool& bIncludeCarTyres;
    static bool& bIncludeDeadPeds;
    static bool& bNoMoreCollisionTorque;
    static bool& bDoingCarCollisions;
    // Current player
    static int8& PlayerInFocus;
    static uint16& ms_nCurrentScanCode;
    static inline CPlayerInfo(&Players)[MAX_PLAYERS] = *(CPlayerInfo(*)[MAX_PLAYERS])0xB7CD98;
    // Use GetSector() to access this array
    static inline CSector(&ms_aSectors)[MAX_SECTORS_Y][MAX_SECTORS_X] = *(CSector(*)[MAX_SECTORS_Y][MAX_SECTORS_X])0xB7D0B8;
    // Use GetRepeatSector() to access this array
    static inline CRepeatSector(&ms_aRepeatSectors)[MAX_REPEAT_SECTORS_Y][MAX_REPEAT_SECTORS_X] = *(CRepeatSector(*)[MAX_REPEAT_SECTORS_Y][MAX_REPEAT_SECTORS_X])0xB992B8;
    // Use GetLodPtrList() to access this array
    static CPtrListSingleLink(&ms_aLodPtrLists)[MAX_LOD_PTR_LISTS_Y][MAX_LOD_PTR_LISTS_X];
    static CPtrListDoubleLink &ms_listMovingEntityPtrs;
    static CPtrListDoubleLink &ms_listObjectsWithControlCode;
    static inline CColPoint(&m_aTempColPts)[32] = *(CColPoint(*)[32])0xB9ACD0;
    static CVector &SnookerTableMax; // default { 497.7925, -1670.3999, 13.19 }
    static CVector &SnookerTableMin; // default { 2495.8525, -1671.4099, 12.9 }

    static void InjectHooks();

    static void Initialise();
    static void ShutDown();
    static void ClearForRestart();
    static void Add(CEntity* entity);
    static void Remove(CEntity* entity);
    static void ResetLineTestOptions();
    static bool ProcessVerticalLineSectorList(CPtrList& ptrList, const CColLine& colLine, CColPoint& colPoint, float& maxTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* collPoly);
    static void CastShadowSectorList(CPtrList& ptrList, float arg1, float arg2, float arg3, float arg4);
    static void ProcessForAnimViewer();
    static void ProcessPedsAfterPreRender();
    static void ClearScanCodes();
    static void FindObjectsInRangeSectorList(CPtrList& arg0, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities);
    static void FindObjectsOfTypeInRangeSectorList(uint32 modelId, CPtrList& ptrList, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities);
    static bool ProcessVerticalLineSectorList_FillGlobeColPoints(CPtrList& ptrList, const CColLine& colLine, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static void RemoveStaticObjects();
    static void TestForBuildingsOnTopOfEachOther(CPtrList& ptrList);
    static void TestForUnusedModels(CPtrList& ptrList, int32* models);
    static void RemoveEntityInsteadOfProcessingIt(CEntity* entity);
    static void CallOffChaseForAreaSectorListVehicles(CPtrList& ptrList, float x1, float y1, float x2, float y2, float minX, float minY, float maxX, float maxY);
    static void CallOffChaseForAreaSectorListPeds(CPtrList& ptrList, float x1, float y1, float x2, float y2, float minX, float minY, float maxX, float maxY);
    static bool CameraToIgnoreThisObject(CEntity* entity);
    static int32 FindPlayerSlotWithPedPointer(void* ptr);
    static int32 FindPlayerSlotWithRemoteVehiclePointer(void* ptr);
    static int32 FindPlayerSlotWithVehiclePointer(CEntity* vehiclePtr);
    static bool ProcessVerticalLineSector_FillGlobeColPoints(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static bool ProcessVerticalLineSector(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static void CastShadow(float x1, float y1, float x2, float y2);
    static void ProcessAttachedEntities();
    static bool GetIsLineOfSightSectorListClear(CPtrList& ptrList, const CColLine& colLine, bool doSeeThroughCheck, bool doCameraIgnoreCheck);
    static void FindObjectsInRange(const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindObjectsOfTypeInRange(uint32 modelId, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindLodOfTypeInRange(uint32 modelId, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities);
    static void FindObjectsKindaCollidingSectorList(CPtrList& ptrList, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities);
    static void FindObjectsIntersectingCubeSectorList(CPtrList& ptrList, const CVector& cornerA, const CVector& cornerB, int16* outCount, int16 maxCount, CEntity** outEntities);
    static void FindObjectsIntersectingAngledCollisionBoxSectorList(CPtrList& ptrList, const CBox& box, const CMatrix& transform, const CVector& point, int16* outCount, int16 maxCount, CEntity** outEntities);
    static void FindMissionEntitiesIntersectingCubeSectorList(CPtrList& ptrList, const CVector& cornerA, const CVector& cornerB, int16* outCount, int16 maxCount, CEntity** outEntities, bool vehiclesList, bool pedsList, bool objectsList);
    static void FindNearestObjectOfTypeSectorList(int32 modelId, CPtrList& ptrList, const CVector& point, float radius, bool b2D, CEntity *& outEntity, float& outDistance);
    static void RemoveReferencesToDeletedObject(CEntity* entity);
    static void SetPedsOnFire(float x, float y, float z, float radius, CEntity* fireCreator);
    static void SetPedsChoking(float x, float y, float z, float radius, CEntity* gasCreator);
    static void SetCarsOnFire(float x, float y, float z, float radius, CEntity* fireCreator);
    static int32 SprayPaintWorld(CVector& posn, CVector& outDir, float radius, bool processTagAlphaState);
    static void RemoveFallenPeds();
    static void RemoveFallenCars();
    static void UseDetonator(CPed* creator);
    static CEntity* TestSphereAgainstWorld(CVector sphereCenter, float sphereRadius, CEntity* ignoreEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doCameraIgnoreCheck);
    static CEntity* TestSphereAgainstSectorList(CPtrList& ptrList, CVector sphereCenter, float sphereRadius, CEntity* ignoreEntity, bool doCameraIgnoreCheck);
    static void PrintCarChanges();
    static void TestForBuildingsOnTopOfEachOther();
    static void TestForUnusedModels();
    static void ClearCarsFromArea(float x1, float y1, float z1, float x2, float y2, float z2);
    static void ClearPedsFromArea(float x1, float y1, float z1, float x2, float y2, float z2);
    static void SetAllCarsCanBeDamaged(bool enable);
    static void ExtinguishAllCarFiresInArea(CVector point, float radius);
    static void CallOffChaseForArea(float x1, float y1, float x2, float y2);
    static void StopAllLawEnforcersInTheirTracks();
    static CVehicle* FindUnsuspectingTargetCar(CVector point, CVector playerPosn);
    static CPed* FindUnsuspectingTargetPed(CVector point, CVector playerPosn);
    static bool ProcessLineOfSightSectorList(CPtrList& ptrList, const CColLine& colLine, CColPoint& outColPoint, float& minTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, bool doIgnoreCameraCheck, bool doShootThroughCheck);
    static bool ProcessVerticalLine(const CVector& origin, float distance, CColPoint& outColPoint, CEntity*& outEntity, bool buildings = false, bool vehicles = false, bool peds = false, bool objects = false, bool dummies = false, bool doSeeThroughCheck = false, CStoredCollPoly* outCollPoly = nullptr);
    static bool ProcessVerticalLine_FillGlobeColPoints(const CVector& origin, float distance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static void TriggerExplosionSectorList(CPtrList& ptrList, const CVector& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage);
    static void Process();
    static bool GetIsLineOfSightSectorClear(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doIgnoreCameraCheck);
    static void FindObjectsKindaColliding(const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindObjectsIntersectingCube(const CVector& cornerA, const CVector& cornerB, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindObjectsIntersectingAngledCollisionBox(const CBox& box, const CMatrix& transform, const CVector& point, float x1, float y1, float x2, float y2, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindMissionEntitiesIntersectingCube(const CVector& cornerA, const CVector& cornerB, int16* outCount, int16 maxCount, CEntity** outEntities, bool vehicles, bool peds, bool objects);
    static CEntity* FindNearestObjectOfType(int32 modelId, const CVector& point, float radius, bool b2D, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static float FindGroundZForCoord(float x, float y);
    static float FindGroundZFor3DCoord(CVector coord, bool* outResult, CEntity** outEntity);
    static float FindRoofZFor3DCoord(float x, float y, float z, bool* outResult);
    static float FindLowestZForCoord(float x, float y);
    static void RepositionOneObject(CEntity* object);
    static void ClearExcitingStuffFromArea(const CVector& point, float radius, uint8 bRemoveProjectilesAndShadows);
    static bool GetIsLineOfSightClear(const CVector& origin, const CVector& target, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck);
    static bool ProcessLineOfSightSector(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, CColPoint& outColPoint, float& maxTouchDistance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck);
    static void TriggerExplosion(const CVector& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage);
    static void SetWorldOnFire(float x, float y, float z, float radius, CEntity* fireCreator);
    static void RepositionCertainDynamicObjects();
    static bool ProcessLineOfSight(const CVector& origin, const CVector& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck);
    static void IncrementCurrentScanCode();
    static CPtrListSingleLink& GetLodPtrList(int32 x, int32 y);

    // Returns sector index in range -60 to 60 (Example: -3000 => -60, 3000 => 60)
    static float GetHalfMapSectorX(float x) { return x / static_cast<float>(MAX_WORLD_UNITS / MAX_SECTORS_X); }
    static float GetHalfMapSectorY(float y) { return y / static_cast<float>(MAX_WORLD_UNITS / MAX_SECTORS_Y); }

    // Returns sector index in range 0 to 120 (Example: -3000 => 0, 3000 => 120)
    static float GetSectorfX(float x) { return GetHalfMapSectorX(x) + static_cast<float>(MAX_SECTORS_X / 2); }
    static float GetSectorfY(float y) { return GetHalfMapSectorY(y) + static_cast<float>(MAX_SECTORS_Y / 2); }

    // returns sector index in range 0 to 120 (covers full map)
    static int32 GetSectorX(float x) { return static_cast<int32>(std::floor(GetSectorfX(x))); }
    static int32 GetSectorY(float y) { return static_cast<int32>(std::floor(GetSectorfY(y))); }

    static float GetSectorPosX(int32 sector)
    {
        constexpr auto HalfOfTotalSectorsX = MAX_SECTORS_X / 2;
        constexpr auto fTotalMapUnitsX = MAX_WORLD_UNITS / MAX_SECTORS_X;
        return (sector - HalfOfTotalSectorsX) * fTotalMapUnitsX + (fTotalMapUnitsX / 2);
    }

    static float GetSectorPosY(int32 sector)
    {
        constexpr auto HalfOfTotalSectorsY = MAX_SECTORS_Y / 2;
        constexpr auto fTotalMapUnitsY = MAX_WORLD_UNITS / MAX_SECTORS_Y;
        return (sector - HalfOfTotalSectorsY) * fTotalMapUnitsY + (fTotalMapUnitsY / 2);
    }

    static CVector2D GetSectorPos(int32 sector) { return { GetSectorPosX(sector), GetSectorPosY(sector) }; }

    // returns sector index in range 0 to 15 (covers half of the map)
    static float GetHalfMapLodSectorX(float sector) { return sector / static_cast<float>(MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_X); }
    static float GetHalfMapLodSectorY(float sector) { return sector / static_cast<float>(MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_Y); }
    static float GetLodSectorfX(float sector) { return GetHalfMapLodSectorX(sector) + static_cast<float>(MAX_LOD_PTR_LISTS_X / 2); }
    static float GetLodSectorfY(float sector) { return GetHalfMapLodSectorY(sector) + static_cast<float>(MAX_LOD_PTR_LISTS_Y / 2); }
    // returns sector index in range 0 to 30 (covers full map)
    static int32 GetLodSectorX(float fSector) { return static_cast<int32>(std::floor(GetLodSectorfX(fSector))); }
    static int32 GetLodSectorY(float fSector) { return static_cast<int32>(std::floor(GetLodSectorfY(fSector))); }
    static float GetLodSectorPosX(int32 sector)
    {
        const int32 HalfOfTotalSectorsX = MAX_LOD_PTR_LISTS_X / 2;
        const float fTotalMapUnitsX = static_cast<float>(MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_X);
        return (sector - HalfOfTotalSectorsX) * fTotalMapUnitsX + (fTotalMapUnitsX / 2);
    }
    static float GetLodSectorPosY(int32 sector)
    {
        const int32 HalfOfTotalSectorsY = MAX_LOD_PTR_LISTS_Y / 2;
        const float fTotalMapUnitsY = static_cast<float>(MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_Y);
        return (sector - HalfOfTotalSectorsY) * fTotalMapUnitsY + (fTotalMapUnitsY / 2);
    }
    static bool IsInWorldBounds(CVector2D pos) { // NOTSA
        return pos.x > -3000.0f && pos.x < 3000.0f
            && pos.y > -3000.0f && pos.y < 3000.0f;
    }

    static void RemoveVehicleAndItsOccupants(CVehicle* veh);
};

extern uint32 &FilledColPointIndex;
static inline CColPoint (&gaTempSphereColPoints)[32] = *(CColPoint(*)[32])0xB9B250;
extern int16 &TAG_SPRAYING_INCREMENT_VAL; // default 8

uint16 GetCurrentScanCode();
CSector* GetSector(int32 x, int32 y);
CRepeatSector* GetRepeatSector(int32 x, int32 y);

CPlayerInfo&   FindPlayerInfo(int32 playerId = -1);
CPlayerPed*    FindPlayerPed(int32 playerId = -1);
CVehicle*      FindPlayerVehicle(int32 playerId = -1, bool bIncludeRemote = false);
CVector        FindPlayerCoors(int32 playerId = -1);
CVector&       FindPlayerSpeed(int32 playerId = -1);
CEntity*       FindPlayerEntity(int32 playerId = -1);
CTrain*        FindPlayerTrain(int32 playerId = -1);
const CVector& FindPlayerCentreOfWorld(int32 playerId = -1);
const CVector& FindPlayerCentreOfWorld_NoSniperShift(int32 playerId = -1);
CVector        FindPlayerCentreOfWorld_NoInteriorShift(int32 playerId = -1);
float          FindPlayerHeading(int32 playerId = -1);
float          FindPlayerHeight(int32 playerId = -1);
CWanted*       FindPlayerWanted(int32 playerId = -1);
CPedGroup&     FindPlayerGroup(int32 playerId = -1);
