/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CPlayerInfo.h"
#include "CColPoint.h"
#include "CStoredCollPoly.h"
#include "CSector.h"
#include "CRepeatSector.h"
#include "CPtrListSingleLink.h"
#include "CPed.h"
#include "CVehicle.h"

extern const std::int32_t MAX_PLAYERS = 2;
extern const std::int32_t MAX_WORLD_UNITS = 6000;
extern const std::int32_t MAX_SECTORS_X = 120;
extern const std::int32_t MAX_SECTORS_Y = 120;
extern const std::int32_t MAX_SECTORS = MAX_SECTORS_X * MAX_SECTORS_Y;
extern const std::int32_t MAX_REPEAT_SECTORS_X = 16;
extern const std::int32_t MAX_REPEAT_SECTORS_Y = 16;
extern const std::int32_t MAX_REPEAT_SECTORS = MAX_REPEAT_SECTORS_X * MAX_REPEAT_SECTORS_Y;
extern const std::int32_t MAX_LOD_PTR_LISTS_X = 30; 
extern const std::int32_t MAX_LOD_PTR_LISTS_Y = 30;
extern const std::int32_t MAX_LOD_PTR_LISTS = MAX_LOD_PTR_LISTS_X * MAX_LOD_PTR_LISTS_Y;

class  CWorld {
public:
    static int &ms_iProcessLineNumCrossings;
    static float &fWeaponSpreadRate;
    // entity to ignore
    static CEntity *&pIgnoreEntity;
    static bool &bSecondShift;
    static bool &bProcessCutsceneOnly;
    static bool &bForceProcessControl;
    static bool &bIncludeBikers;
    static bool &bIncludeCarTyres;
    static bool &bIncludeDeadPeds;
    static bool &bNoMoreCollisionTorque;
    static bool &bDoingCarCollisions;
    // Current player
    static char &PlayerInFocus;
    static unsigned short &ms_nCurrentScanCode;
    // Player data array for 2 players
    static CPlayerInfo *Players; // static CPlayerInfo Players[MAX_PLAYERS]
    // Use GetSector() to access this array
    static CSector *ms_aSectors; // static CSector ms_aSectors[MAX_SECTORS] default 120x120
    // Use GetRepeatSector() to access this array
    static CRepeatSector *ms_aRepeatSectors; // static CRepeatSector ms_aRepeatSectors[MAX_REPEAT_SECTORS] default 16x16
    // Use GetLodPtrList() to access this array
    
    static CPtrListSingleLink(&ms_aLodPtrLists)[MAX_LOD_PTR_LISTS_Y][MAX_LOD_PTR_LISTS_X];
    static CPtrListDoubleLink &ms_listMovingEntityPtrs;
    static CPtrListDoubleLink &ms_listObjectsWithControlCode;
    static CColPoint *m_aTempColPts; // static CColPoint m_aTempColPts[32]
    static CVector &SnookerTableMax; // default { 497.7925, -1670.3999, 13.19 }
    static CVector &SnookerTableMin; // default { 2495.8525, -1671.4099, 12.9 }

    static void ResetLineTestOptions();
    static void Initialise();
    static void Add(CEntity* entity);
    static void Remove(CEntity* entity);
    static bool ProcessVerticalLineSectorList(CPtrList& ptrList, CColLine const& colLine, CColPoint& colPoint, float& maxTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* collPoly);
    static void CastShadowSectorList(CPtrList& ptrList, float arg1, float arg2, float arg3, float arg4);
    static void ProcessForAnimViewer();
    static void ProcessPedsAfterPreRender();
    static void ClearScanCodes();
    static void FindObjectsInRangeSectorList(CPtrList& arg0, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities);
    static void FindObjectsOfTypeInRangeSectorList(unsigned int modelId, CPtrList& ptrList, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities);
    static bool ProcessVerticalLineSectorList_FillGlobeColPoints(CPtrList& ptrList, CColLine const& colLine, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static void RemoveStaticObjects();
    static void TestForBuildingsOnTopOfEachOther(CPtrList& ptrList);
    static void TestForUnusedModels(CPtrList& ptrList, int* models);
    static void RemoveEntityInsteadOfProcessingIt(CEntity* entity);
    static void CallOffChaseForAreaSectorListVehicles(CPtrList& ptrList, float x1, float y1, float x2, float y2, float arg5, float arg6, float arg7, float arg8);
    static void CallOffChaseForAreaSectorListPeds(CPtrList& ptrList, float x1, float y1, float x2, float y2, float arg5, float arg6, float arg7, float arg8);
    static bool CameraToIgnoreThisObject(CEntity* entity);
    // returns player ID (0 or 1), -1 - not found
    static int FindPlayerSlotWithPedPointer(void* ptr);
    // returns player ID (0 or 1), -1 - not found
    static int FindPlayerSlotWithRemoteVehiclePointer(void* ptr);
    // returns player ID (0 or 1)
    static void FindPlayerSlotWithVehiclePointer(CEntity* vehiclePtr);
    static void ShutDown();
    static void ClearForRestart();
    static bool ProcessVerticalLineSector_FillGlobeColPoints(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static bool ProcessVerticalLineSector(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static void CastShadow(float x1, float y1, float x2, float y2);
    static void ProcessAttachedEntities();
    static bool GetIsLineOfSightSectorListClear(CPtrList& ptrList, CColLine const& colLine, bool doSeeThroughCheck, bool doCameraIgnoreCheck);
    static void FindObjectsInRange(CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindObjectsOfTypeInRange(unsigned int modelId, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindLodOfTypeInRange(unsigned int modelId, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities);
    static void FindObjectsKindaCollidingSectorList(CPtrList& ptrList, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities);
    static void FindObjectsIntersectingCubeSectorList(CPtrList& ptrList, CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities);
    static void FindObjectsIntersectingAngledCollisionBoxSectorList(CPtrList& ptrList, CBox const& box, CMatrix const& transform, CVector const& point, short* outCount, short maxCount, CEntity** outEntities);
    static void FindMissionEntitiesIntersectingCubeSectorList(CPtrList& ptrList, CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities, bool vehiclesList, bool pedsList, bool objectsList);
    static void FindNearestObjectOfTypeSectorList(int modelId, CPtrList& ptrList, CVector const& point, float radius, bool b2D, CEntity** outEntities, float* outDistance);
    static void RemoveReferencesToDeletedObject(CEntity* entity);
    static void SetPedsOnFire(float x1, float y1, float x2, float y2, CEntity* fireCreator);
    static void SetPedsChoking(float x1, float y1, float x2, float y2, CEntity* gasCreator);
    static void SetCarsOnFire(float x1, float y1, float x2, float y2, CEntity* fireCreator);
    static bool SprayPaintWorld(CVector& posn, CVector& outDir, float radius, bool processTagAlphaState);
    static void RemoveFallenPeds();
    static void RemoveFallenCars();
    static void UseDetonator(CEntity* creator);
    // returns entity
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
    static bool ProcessLineOfSightSectorList(CPtrList& ptrList, CColLine const& colLine, CColPoint& outColPoint, float& maxTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, bool doIgnoreCameraCheck, bool doShootThroughCheck);
    static bool ProcessVerticalLine(CVector const& origin, float distance, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static bool ProcessVerticalLine_FillGlobeColPoints(CVector const& origin, float distance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly);
    static void TriggerExplosionSectorList(CPtrList& ptrList, CVector const& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage);
    static void Process();
    static bool GetIsLineOfSightSectorClear(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doIgnoreCameraCheck);
    static void FindObjectsKindaColliding(CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindObjectsIntersectingCube(CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindObjectsIntersectingAngledCollisionBox(CBox const& box, CMatrix const& transform, CVector const& point, float x1, float y1, float x2, float y2, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static void FindMissionEntitiesIntersectingCube(CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities, bool vehicles, bool peds, bool objects);
    static void FindNearestObjectOfType(int modelId, CVector const& point, float radius, bool b2D, bool buildings, bool vehicles, bool peds, bool objects, bool dummies);
    static float FindGroundZForCoord(float x, float y);
    static float FindGroundZFor3DCoord(float x, float y, float z, bool* outResult, CEntity** outEntity);
    static float FindRoofZFor3DCoord(float x, float y, float z, bool* outResult);
    static float FindLowestZForCoord(float x, float y);
    static void RepositionOneObject(CEntity* object);
    // returns entity
    static CEntity* TestSphereAgainstWorld(CVector sphereCenter, float sphereRadius, CEntity* arg2, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doCameraIgnoreCheck);
    static void ClearExcitingStuffFromArea(CVector const& point, float radius, unsigned char bRemoveProjectilesAndShadows);
    static bool GetIsLineOfSightClear(CVector const& origin, CVector const& target, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck);
    static bool ProcessLineOfSightSector(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, CColPoint& outColPoint, float& maxTouchDistance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck);
    static void TriggerExplosion(CVector const& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage);
    static void SetWorldOnFire(float x, float y, float z, float radius, CEntity* fireCreator);
    static void RepositionCertainDynamicObjects();
    static bool ProcessLineOfSight(CVector const& origin, CVector const& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck);
    static void IncrementCurrentScanCode();
    static CPtrListSingleLink& GetLodPtrList(std::int32_t x, std::int32_t y);

    // returns sector index in range 0 to 60 (covers half of the map) 
    static float GetHalfMapSectorX(float fSector) { return fSector / (MAX_WORLD_UNITS / MAX_SECTORS_X); }
    static float GetHalfMapSectorY(float fSector) { return fSector / (MAX_WORLD_UNITS / MAX_SECTORS_Y); }
    static float GetSectorfX(float fSector) { return GetHalfMapSectorX(fSector) + (MAX_SECTORS_X / 2); }
    static float GetSectorfY(float fSector) { return GetHalfMapSectorY(fSector) + (MAX_SECTORS_Y / 2); }
    // returns sector index in range 0 to 120 (covers full map) 
    static std::int32_t GetSectorX(float fSector) { return static_cast<std::int32_t>(std::floor(GetSectorfX(fSector))); }
    static std::int32_t GetSectorY(float fSector) { return static_cast<std::int32_t>(std::floor(GetSectorfY(fSector))); }
    static float GetSectorPosX(std::int32_t sector)
    {
        const std::int32_t HalfOfTotalSectorsX = MAX_SECTORS_Y / 2;
        const float fTotalMapUnitsX = MAX_WORLD_UNITS / MAX_SECTORS_Y;
        return (sector - HalfOfTotalSectorsX) * fTotalMapUnitsX + (fTotalMapUnitsX / 2);
    }
    static float GetSectorPosY(std::int32_t sector)
    {
        const std::int32_t HalfOfTotalSectorsY = MAX_SECTORS_Y / 2;
        const float fTotalMapUnitsY = MAX_WORLD_UNITS / MAX_SECTORS_Y;
        return (sector - HalfOfTotalSectorsY) * fTotalMapUnitsY + (fTotalMapUnitsY / 2);
    }

    // returns sector index in range 0 to 15 (covers half of the map) 
    static float GetHalfMapLodSectorX(float fSector) { return fSector / (MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_X); }
    static float GetHalfMapLodSectorY(float fSector) { return fSector / (MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_Y); }
    static float GetLodSectorfX(float fSector) { return GetHalfMapLodSectorX(fSector) + (MAX_LOD_PTR_LISTS_X / 2); }
    static float GetLodSectorfY(float fSector) { return GetHalfMapLodSectorY(fSector) + (MAX_LOD_PTR_LISTS_Y / 2); }
    // returns sector index in range 0 to 30 (covers full map) 
    static std::int32_t GetLodSectorX(float fSector) { return static_cast<std::int32_t>(std::floor(GetLodSectorfX(fSector))); }
    static std::int32_t GetLodSectorY(float fSector) { return static_cast<std::int32_t>(std::floor(GetLodSectorfY(fSector)));  }
    static float GetLodSectorPosX(std::int32_t sector)
    {
        const std::int32_t HalfOfTotalSectorsX = MAX_LOD_PTR_LISTS_X / 2;
        const float fTotalMapUnitsX = MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_X;
        return (sector - HalfOfTotalSectorsX) * fTotalMapUnitsX + (fTotalMapUnitsX / 2);
    }
    static float GetLodSectorPosY(std::int32_t sector)
    {
        const std::int32_t HalfOfTotalSectorsY = MAX_LOD_PTR_LISTS_Y / 2;
        const float fTotalMapUnitsY = MAX_WORLD_UNITS / MAX_LOD_PTR_LISTS_Y;
        return (sector - HalfOfTotalSectorsY) * fTotalMapUnitsY + (fTotalMapUnitsY / 2);
    }
};

extern unsigned int &FilledColPointIndex;
extern CColPoint *gaTempSphereColPoints; // CColPoint gaTempSphereColPoints[32]
extern short &TAG_SPRAYING_INCREMENT_VAL; // default 8

short GetCurrentScanCode();
CSector* GetSector(int x, int y);
CRepeatSector* GetRepeatSector(int x, int y);
void SetNextScanCode();

double ScaleLighting(unsigned char lighting, float fScale);
