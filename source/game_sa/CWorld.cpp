/*
Plugin-SDK (Grand Theft Auto San Andreas) source file
Authors: GTA Community. See more here
https://github.com/DK22Pac/plugin-sdk
Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"

std::int32_t CWorld::TOTAL_PLAYERS = 2;
int &CWorld::ms_iProcessLineNumCrossings = *(int *)0xB7CD60;
float &CWorld::fWeaponSpreadRate = *(float *)0xB7CD64;
CEntity *&CWorld::pIgnoreEntity = *(CEntity **)0xB7CD68;
bool &CWorld::bSecondShift = *(bool *)0xB7CD6C;
bool &CWorld::bProcessCutsceneOnly = *(bool *)0xB7CD6D;
bool &CWorld::bForceProcessControl = *(bool *)0xB7CD6E;
bool &CWorld::bIncludeBikers = *(bool *)0xB7CD6F;
bool &CWorld::bIncludeCarTyres = *(bool *)0xB7CD70;
bool &CWorld::bIncludeDeadPeds = *(bool *)0xB7CD71;
bool &CWorld::bNoMoreCollisionTorque = *(bool *)0xB7CD72;
bool &CWorld::bDoingCarCollisions = *(bool *)0xB7CD73;
char &CWorld::PlayerInFocus = *(char *)0xB7CD74;
unsigned short&CWorld::ms_nCurrentScanCode = *(unsigned short*)0xB7CD78;
CPlayerInfo *CWorld::Players = (CPlayerInfo *)0xB7CD98;
CSector *CWorld::ms_aSectors = (CSector *)0xB7D0B8;
CRepeatSector *CWorld::ms_aRepeatSectors = (CRepeatSector *)0xB992B8;
CPtrListSingleLink(&CWorld::ms_aLodPtrLists)[MAX_LOD_PTR_LISTS_Y][MAX_LOD_PTR_LISTS_X] = *(CPtrListSingleLink(*)[MAX_LOD_PTR_LISTS_Y][MAX_LOD_PTR_LISTS_X])0xB99EB8;
CPtrListDoubleLink &CWorld::ms_listMovingEntityPtrs = *(CPtrListDoubleLink *)0xB9ACC8;
CPtrListDoubleLink &CWorld::ms_listObjectsWithControlCode = *(CPtrListDoubleLink *)0xB9ACCC;
CColPoint *CWorld::m_aTempColPts = (CColPoint *)0xB9ACD0;
CVector &CWorld::SnookerTableMax = *(CVector *)0x8CDEF4;
CVector &CWorld::SnookerTableMin = *(CVector *)0x8CDF00;
unsigned int &FilledColPointIndex = *(unsigned int*)0xB7CD7C;
CColPoint *gaTempSphereColPoints = (CColPoint *)0xB9B250;
short &TAG_SPRAYING_INCREMENT_VAL = *(short *)0x8CDEF0;

void CWorld::InjectHooks() {
    HookInstall(0x565CB0, RemoveFallenPeds);
    HookInstall(0x565E80, RemoveFallenCars);
}

// Converted from cdecl void CWorld::ResetLineTestOptions(void) 0x5631C0
void CWorld::ResetLineTestOptions() {
    plugin::Call<0x5631C0>();
}

// Converted from cdecl void CWorld::Initialise(void) 0x5631E0
void CWorld::Initialise() {
    plugin::Call<0x5631E0>();
}

// Converted from cdecl void CWorld::Add(CEntity *entity) 0x563220
void CWorld::Add(CEntity* entity) {
    plugin::Call<0x563220, CEntity*>(entity);
}

// Converted from cdecl void CWorld::Remove(CEntity *entity) 0x563280
void CWorld::Remove(CEntity* entity) 
{
    plugin::Call<0x563280, CEntity*>(entity);
}

// Converted from cdecl bool CWorld::ProcessVerticalLineSectorList(CPtrList &ptrList,CColLine const&colLine,CColPoint &colPoint,float &maxTouchDistance,CEntity *&outEntity,bool doSeeThroughCheck,CStoredCollPoly *collPoly) 0x5632B0
bool CWorld::ProcessVerticalLineSectorList(CPtrList& ptrList, CColLine const& colLine, CColPoint& colPoint, float& maxTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* collPoly) {
    return plugin::CallAndReturn<bool, 0x5632B0, CPtrList&, CColLine const&, CColPoint&, float&, CEntity*&, bool, CStoredCollPoly*>(ptrList, colLine, colPoint, maxTouchDistance, outEntity, doSeeThroughCheck, collPoly);
}

// Converted from cdecl void CWorld::CastShadowSectorList(CPtrList &ptrList,float,float,float,float) 0x563390
void CWorld::CastShadowSectorList(CPtrList& ptrList, float arg1, float arg2, float arg3, float arg4) {
    plugin::Call<0x563390, CPtrList&, float, float, float, float>(ptrList, arg1, arg2, arg3, arg4);
}

// Converted from cdecl void CWorld::ProcessForAnimViewer(void) 0x5633D0
void CWorld::ProcessForAnimViewer() {
    plugin::Call<0x5633D0>();
}

// Converted from cdecl void CWorld::ProcessPedsAfterPreRender(void) 0x563430
void CWorld::ProcessPedsAfterPreRender() {
    plugin::Call<0x563430>();
}

// Converted from cdecl void CWorld::ClearScanCodes(void) 0x563470
void CWorld::ClearScanCodes() {
    plugin::Call<0x563470>();
}

// Converted from cdecl void CWorld::FindObjectsInRangeSectorList(CPtrList &,CVector const&point,float radius,bool b2D,short *outCount,short maxCount,CEntity **outEntities) 0x563500
void CWorld::FindObjectsInRangeSectorList(CPtrList& arg0, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities) {
    plugin::Call<0x563500, CPtrList&, CVector const&, float, bool, short*, short, CEntity**>(arg0, point, radius, b2D, outCount, maxCount, outEntities);
}

// Converted from cdecl void CWorld::FindObjectsOfTypeInRangeSectorList(uint modelId,CPtrList &ptrList,CVector const&point,float radius,bool b2D,short *outCount,short maxCount,CEntity **outEntities) 0x5635C0
void CWorld::FindObjectsOfTypeInRangeSectorList(unsigned int modelId, CPtrList& ptrList, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities) {
    plugin::Call<0x5635C0, unsigned int, CPtrList&, CVector const&, float, bool, short*, short, CEntity**>(modelId, ptrList, point, radius, b2D, outCount, maxCount, outEntities);
}

// Converted from cdecl bool CWorld::ProcessVerticalLineSectorList_FillGlobeColPoints(CPtrList &ptrList,CColLine const&colLine,CEntity *&outEntity,bool doSeeThroughCheck,CStoredCollPoly *outCollPoly) 0x5636A0
bool CWorld::ProcessVerticalLineSectorList_FillGlobeColPoints(CPtrList& ptrList, CColLine const& colLine, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    return plugin::CallAndReturn<bool, 0x5636A0, CPtrList&, CColLine const&, CEntity*&, bool, CStoredCollPoly*>(ptrList, colLine, outEntity, doSeeThroughCheck, outCollPoly);
}

// Converted from cdecl void CWorld::RemoveStaticObjects(void) 0x563840
void CWorld::RemoveStaticObjects() {
    plugin::Call<0x563840>();
}

// Converted from cdecl void CWorld::TestForBuildingsOnTopOfEachOther(CPtrList &ptrList) 0x563950
void CWorld::TestForBuildingsOnTopOfEachOther(CPtrList& ptrList) {
    plugin::Call<0x563950, CPtrList&>(ptrList);
}

// Converted from cdecl void CWorld::TestForUnusedModels(CPtrList &ptrList,int *models) 0x5639D0
void CWorld::TestForUnusedModels(CPtrList& ptrList, int* models) {
    plugin::Call<0x5639D0, CPtrList&, int*>(ptrList, models);
}

// Converted from cdecl void CWorld::RemoveEntityInsteadOfProcessingIt(CEntity *entity) 0x563A10
void CWorld::RemoveEntityInsteadOfProcessingIt(CEntity* entity) {
    plugin::Call<0x563A10, CEntity*>(entity);
}

// Converted from cdecl void CWorld::CallOffChaseForAreaSectorListVehicles(CPtrList &ptrList,float x1,float y1,float x2,float y2,float,float,float,float) 0x563A80
void CWorld::CallOffChaseForAreaSectorListVehicles(CPtrList& ptrList, float x1, float y1, float x2, float y2, float arg5, float arg6, float arg7, float arg8) {
    plugin::Call<0x563A80, CPtrList&, float, float, float, float, float, float, float, float>(ptrList, x1, y1, x2, y2, arg5, arg6, arg7, arg8);
}

// Converted from cdecl void CWorld::CallOffChaseForAreaSectorListPeds(CPtrList &ptrList,float x1,float y1,float x2,float y2,float,float,float,float) 0x563D00
void CWorld::CallOffChaseForAreaSectorListPeds(CPtrList& ptrList, float x1, float y1, float x2, float y2, float arg5, float arg6, float arg7, float arg8) {
    plugin::Call<0x563D00, CPtrList&, float, float, float, float, float, float, float, float>(ptrList, x1, y1, x2, y2, arg5, arg6, arg7, arg8);
}

// Converted from cdecl bool CWorld::CameraToIgnoreThisObject(CEntity *entity) 0x563F40
bool CWorld::CameraToIgnoreThisObject(CEntity* entity) {
    return plugin::CallAndReturn<bool, 0x563F40, CEntity*>(entity);
}

// Converted from cdecl int CWorld::FindPlayerSlotWithPedPointer(void *ptr) 0x563FA0
int CWorld::FindPlayerSlotWithPedPointer(void* ptr) {
    return plugin::CallAndReturn<int, 0x563FA0, void*>(ptr);
}

// Converted from cdecl int CWorld::FindPlayerSlotWithRemoteVehiclePointer(void *ptr) 0x563FD0
int CWorld::FindPlayerSlotWithRemoteVehiclePointer(void* ptr) {
    return plugin::CallAndReturn<int, 0x563FD0, void*>(ptr);
}

// Converted from cdecl void CWorld::FindPlayerSlotWithVehiclePointer(CEntity *vehiclePtr) 0x564000
void CWorld::FindPlayerSlotWithVehiclePointer(CEntity* vehiclePtr) {
    plugin::Call<0x564000, CEntity*>(vehiclePtr);
}

// Converted from cdecl void CWorld::ShutDown(void) 0x564050
void CWorld::ShutDown() {
    plugin::Call<0x564050>();
}

// Converted from cdecl void CWorld::ClearForRestart(void) 0x564360
void CWorld::ClearForRestart() {
    plugin::Call<0x564360>();
}

// Converted from cdecl bool CWorld::ProcessVerticalLineSector_FillGlobeColPoints(CSector &sector,CRepeatSector &repeatSector,CColLine const&colLine,CEntity *&outEntity,bool buildings,bool vehicles,bool peds,bool objects,bool dummies,bool doSeeThroughCheck,CStoredCollPoly *outCollPoly) 0x564420
bool CWorld::ProcessVerticalLineSector_FillGlobeColPoints(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    return plugin::CallAndReturn<bool, 0x564420, CSector&, CRepeatSector&, CColLine const&, CEntity*&, bool, bool, bool, bool, bool, bool, CStoredCollPoly*>(sector, repeatSector, colLine, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, outCollPoly);
}

// Converted from cdecl bool CWorld::ProcessVerticalLineSector(CSector &sector,CRepeatSector &repeatSector,CColLine const&colLine,CColPoint &outColPoint,CEntity *&outEntity,bool buildings,bool vehicles,bool peds,bool objects,bool dummies,bool doSeeThroughCheck,CStoredCollPoly *outCollPoly) 0x564500
bool CWorld::ProcessVerticalLineSector(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    return plugin::CallAndReturn<bool, 0x564500, CSector&, CRepeatSector&, CColLine const&, CColPoint&, CEntity*&, bool, bool, bool, bool, bool, bool, CStoredCollPoly*>(sector, repeatSector, colLine, outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, outCollPoly);
}

// Converted from cdecl void CWorld::CastShadow(float x1,float y1,float x2,float y2) 0x564600
void CWorld::CastShadow(float x1, float y1, float x2, float y2) {
    plugin::Call<0x564600, float, float, float, float>(x1, y1, x2, y2);
}

// Converted from cdecl void CWorld::ProcessAttachedEntities(void) 0x5647F0
void CWorld::ProcessAttachedEntities() {
    plugin::Call<0x5647F0>();
}

// Converted from cdecl bool CWorld::GetIsLineOfSightSectorListClear(CPtrList &ptrList,CColLine const&colLine,bool doSeeThroughCheck,bool doCameraIgnoreCheck) 0x564970
bool CWorld::GetIsLineOfSightSectorListClear(CPtrList& ptrList, CColLine const& colLine, bool doSeeThroughCheck, bool doCameraIgnoreCheck) {
    return plugin::CallAndReturn<bool, 0x564970, CPtrList&, CColLine const&, bool, bool>(ptrList, colLine, doSeeThroughCheck, doCameraIgnoreCheck);
}

// Converted from cdecl void CWorld::FindObjectsInRange(CVector const&point,float radius,bool b2D,short *outCount,short maxCount,CEntity **outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) 0x564A20
void CWorld::FindObjectsInRange(CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    plugin::Call<0x564A20, CVector const&, float, bool, short*, short, CEntity**, bool, bool, bool, bool, bool>(point, radius, b2D, outCount, maxCount, outEntities, buildings, vehicles, peds, objects, dummies);
}

// Converted from cdecl void CWorld::FindObjectsOfTypeInRange(uint modelId,CVector const&point,float radius,bool b2D,short *outCount,short maxCount,CEntity **outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) 0x564C70
void CWorld::FindObjectsOfTypeInRange(unsigned int modelId, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    plugin::Call<0x564C70, unsigned int, CVector const&, float, bool, short*, short, CEntity**, bool, bool, bool, bool, bool>(modelId, point, radius, b2D, outCount, maxCount, outEntities, buildings, vehicles, peds, objects, dummies);
}

// Converted from cdecl void CWorld::FindLodOfTypeInRange(uint modelId,CVector const&point,float radius,bool b2D,short *outCount,short maxCount,CEntity **outEntities) 0x564ED0
void CWorld::FindLodOfTypeInRange(unsigned int modelId, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities) {
    plugin::Call<0x564ED0, unsigned int, CVector const&, float, bool, short*, short, CEntity**>(modelId, point, radius, b2D, outCount, maxCount, outEntities);
}

// Converted from cdecl void CWorld::FindObjectsKindaCollidingSectorList(CPtrList &ptrList,CVector const&point,float radius,bool b2D,short *outCount,short maxCount,CEntity **outEntities) 0x565000
void CWorld::FindObjectsKindaCollidingSectorList(CPtrList& ptrList, CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities) {
    plugin::Call<0x565000, CPtrList&, CVector const&, float, bool, short*, short, CEntity**>(ptrList, point, radius, b2D, outCount, maxCount, outEntities);
}

// Converted from cdecl void CWorld::FindObjectsIntersectingCubeSectorList(CPtrList &ptrList,CVector const&cornerA,CVector const&cornerB,short *outCount,short maxCount,CEntity **outEntities) 0x5650E0
void CWorld::FindObjectsIntersectingCubeSectorList(CPtrList& ptrList, CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities) {
    plugin::Call<0x5650E0, CPtrList&, CVector const&, CVector const&, short*, short, CEntity**>(ptrList, cornerA, cornerB, outCount, maxCount, outEntities);
}

// Converted from cdecl void CWorld::FindObjectsIntersectingAngledCollisionBoxSectorList(CPtrList &ptrList,CBox const&box,CMatrix const&transform,CVector const&point,short *outCount,short maxCount,CEntity **outEntities) 0x565200
void CWorld::FindObjectsIntersectingAngledCollisionBoxSectorList(CPtrList& ptrList, CBox const& box, CMatrix const& transform, CVector const& point, short* outCount, short maxCount, CEntity** outEntities) {
    plugin::Call<0x565200, CPtrList&, CBox const&, CMatrix const&, CVector const&, short*, short, CEntity**>(ptrList, box, transform, point, outCount, maxCount, outEntities);
}

// Converted from cdecl void CWorld::FindMissionEntitiesIntersectingCubeSectorList(CPtrList &ptrList,CVector const&cornerA,CVector const&cornerB,short *outCount,short maxCount,CEntity **outEntities,bool vehiclesList,bool pedsList,bool objectsList) 0x565300
void CWorld::FindMissionEntitiesIntersectingCubeSectorList(CPtrList& ptrList, CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities, bool vehiclesList, bool pedsList, bool objectsList) {
    plugin::Call<0x565300, CPtrList&, CVector const&, CVector const&, short*, short, CEntity**, bool, bool, bool>(ptrList, cornerA, cornerB, outCount, maxCount, outEntities, vehiclesList, pedsList, objectsList);
}

// Converted from cdecl void CWorld::FindNearestObjectOfTypeSectorList(int modelId,CPtrList &ptrList,CVector const&point,float radius,bool b2D,CEntity **outEntities,float *outDistance) 0x565450
void CWorld::FindNearestObjectOfTypeSectorList(int modelId, CPtrList& ptrList, CVector const& point, float radius, bool b2D, CEntity** outEntities, float* outDistance) {
    plugin::Call<0x565450, int, CPtrList&, CVector const&, float, bool, CEntity**, float*>(modelId, ptrList, point, radius, b2D, outEntities, outDistance);
}

// Converted from cdecl void CWorld::RemoveReferencesToDeletedObject(CEntity *entity) 0x565510
void CWorld::RemoveReferencesToDeletedObject(CEntity* entity) {
    plugin::Call<0x565510, CEntity*>(entity);
}

// Converted from cdecl void CWorld::SetPedsOnFire(float x1,float y1,float x2,float y2,CEntity *fireCreator) 0x565610
void CWorld::SetPedsOnFire(float x1, float y1, float x2, float y2, CEntity* fireCreator) {
    plugin::Call<0x565610, float, float, float, float, CEntity*>(x1, y1, x2, y2, fireCreator);
}

// Converted from cdecl void CWorld::SetPedsChoking(float x1,float y1,float x2,float y2,CEntity *gasCreator) 0x565800
void CWorld::SetPedsChoking(float x1, float y1, float x2, float y2, CEntity* gasCreator) {
    plugin::Call<0x565800, float, float, float, float, CEntity*>(x1, y1, x2, y2, gasCreator);
}

// Converted from cdecl void CWorld::SetCarsOnFire(float x1,float y1,float x2,float y2,CEntity *fireCreator) 0x5659F0
void CWorld::SetCarsOnFire(float x1, float y1, float x2, float y2, CEntity* fireCreator) {
    plugin::Call<0x5659F0, float, float, float, float, CEntity*>(x1, y1, x2, y2, fireCreator);
}

// Converted from cdecl bool CWorld::SprayPaintWorld(CVector &posn,CVector &outDir,float radius,bool processTagAlphaState) 0x565B70
bool CWorld::SprayPaintWorld(CVector& posn, CVector& outDir, float radius, bool processTagAlphaState) {
    return plugin::CallAndReturn<bool, 0x565B70, CVector&, CVector&, float, bool>(posn, outDir, radius, processTagAlphaState);
}

// Converted from cdecl void CWorld::RemoveFallenPeds(void) 0x565CB0
void CWorld::RemoveFallenPeds() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x565CB0>();
#else
    for (int i = CPools::ms_pPedPool->GetSize(); i; i--)
    {
        CPed* pPed = CPools::ms_pPedPool->GetAt(i - 1);
        if (!pPed)
            continue;
        const CVector& vecPedPos = pPed->GetPosition();
        if (vecPedPos.z > -100.0f)
            continue;
        if (!pPed->IsCreatedBy(ePedCreatedBy::PED_GAME) || pPed->IsPlayer())
        {
            CNodeAddress pathNodeAddress;
            ThePaths.FindNodeClosestToCoors(&pathNodeAddress, vecPedPos.x, vecPedPos.y, vecPedPos.z, 1, 1000000.0f, 0, 0, 0, 0, 0);
            if (pathNodeAddress.m_wAreaId != -1)
            {
                CVector pathNodePos = ThePaths.GetPathNode(pathNodeAddress)->GetNodeCoors();
                pathNodePos.z += 2.0f;
                pPed->Teleport(pathNodePos, false); 
            }
            else
                pPed->SetPosn(vecPedPos.x, vecPedPos.y, -95);
            pPed->ResetMoveSpeed();
        }
        else
            CPopulation::RemovePed(pPed);
    }
#endif
}

// Converted from cdecl void CWorld::RemoveFallenCars(void) 0x565E80
void CWorld::RemoveFallenCars() {

#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x565E80>();
#else
    for (int i = CPools::ms_pVehiclePool->GetSize(); i; i--)
    {
        CVehicle* pVeh = CPools::ms_pVehiclePool->GetAt(i - 1);
        if (!pVeh)
            continue;

        const CVector& vecPos = pVeh->GetPosition();
        if (vecPos.z > -100.0f)
            continue;

        const auto ShouldWeKeepIt = [pVeh]() {
            if (pVeh->IsCreatedBy(eVehicleCreatedBy::MISSION_VEHICLE) && !pVeh->physicalFlags.bDestroyed)
                return true;

            if (pVeh == FindPlayerVehicle(-1, false))
                return true;

            return pVeh->m_pDriver && pVeh->m_pDriver->IsPlayer();
        };

        if (ShouldWeKeepIt())
        {
            CNodeAddress pathNodeAddress;
            ThePaths.FindNodeClosestToCoors(&pathNodeAddress, vecPos.x, vecPos.y, vecPos.z, 1, 1000000.0f, 0, 0, 0, 0, 0);
            if (pathNodeAddress.m_wAreaId != -1)
            {
                const auto pathNodePos = ThePaths.GetPathNode(pathNodeAddress)->GetNodeCoors();
                pVeh->Teleport(pathNodePos + CVector(0, 0, 3), false);
            }
            else
                pVeh->Teleport(CVector(vecPos.x, vecPos.y, 0), false);
            pVeh->ResetMoveSpeed();
        }
        else
        {
            if (!pVeh->IsCreatedBy(eVehicleCreatedBy::RANDOM_VEHICLE))
                if (!pVeh->IsCreatedBy(eVehicleCreatedBy::PARKED_VEHICLE))
                    continue;

            if (pVeh->IsPhysical())
                pVeh->RemoveFromMovingList();

            delete pVeh;
        }
    }
#endif
}

// Converted from cdecl void CWorld::UseDetonator(CEntity *creator) 0x5660B0
void CWorld::UseDetonator(CEntity* creator) {
    plugin::Call<0x5660B0, CEntity*>(creator);
}

// Converted from cdecl CEntity* CWorld::TestSphereAgainstSectorList(CPtrList &ptrList,CVector sphereCenter,float sphereRadius,CEntity *ignoreEntity,bool doCameraIgnoreCheck) 0x566140
CEntity* CWorld::TestSphereAgainstSectorList(CPtrList& ptrList, CVector sphereCenter, float sphereRadius, CEntity* ignoreEntity, bool doCameraIgnoreCheck) {
    return plugin::CallAndReturn<CEntity*, 0x566140, CPtrList&, CVector, float, CEntity*, bool>(ptrList, sphereCenter, sphereRadius, ignoreEntity, doCameraIgnoreCheck);
}

// Converted from cdecl void CWorld::PrintCarChanges(void) 0x566420
void CWorld::PrintCarChanges() {
    plugin::Call<0x566420>();
}

// Converted from cdecl void CWorld::TestForBuildingsOnTopOfEachOther(void) 0x5664A0
void CWorld::TestForBuildingsOnTopOfEachOther() {
    plugin::Call<0x5664A0>();
}

// Converted from cdecl void CWorld::TestForUnusedModels(void) 0x566510
void CWorld::TestForUnusedModels() {
    plugin::Call<0x566510>();
}

// Converted from cdecl void CWorld::ClearCarsFromArea(float x1,float y1,float z1,float x2,float y2,float z2) 0x566610
void CWorld::ClearCarsFromArea(float x1, float y1, float z1, float x2, float y2, float z2) {
    plugin::Call<0x566610, float, float, float, float, float, float>(x1, y1, z1, x2, y2, z2);
}

// Converted from cdecl void CWorld::ClearPedsFromArea(float x1,float y1,float z1,float x2,float y2,float z2) 0x5667F0
void CWorld::ClearPedsFromArea(float x1, float y1, float z1, float x2, float y2, float z2) {
    plugin::Call<0x5667F0, float, float, float, float, float, float>(x1, y1, z1, x2, y2, z2);
}

// Converted from cdecl void CWorld::SetAllCarsCanBeDamaged(bool enable) 0x5668F0
void CWorld::SetAllCarsCanBeDamaged(bool enable) {
    plugin::Call<0x5668F0, bool>(enable);
}

// Converted from cdecl void CWorld::ExtinguishAllCarFiresInArea(CVector point,float radius) 0x566950
void CWorld::ExtinguishAllCarFiresInArea(CVector point, float radius) {
    plugin::Call<0x566950, CVector, float>(point, radius);
}

// Converted from cdecl void CWorld::CallOffChaseForArea(float x1,float y1,float x2,float y2) 0x566A60
void CWorld::CallOffChaseForArea(float x1, float y1, float x2, float y2) {
    plugin::Call<0x566A60, float, float, float, float>(x1, y1, x2, y2);
}

// Converted from cdecl void CWorld::StopAllLawEnforcersInTheirTracks(void) 0x566C10
void CWorld::StopAllLawEnforcersInTheirTracks() {
    plugin::Call<0x566C10>();
}

// Converted from cdecl CVehicle* CWorld::FindUnsuspectingTargetCar(CVector point,CVector playerPosn) 0x566C90
CVehicle* CWorld::FindUnsuspectingTargetCar(CVector point, CVector playerPosn) {
    return plugin::CallAndReturn<CVehicle*, 0x566C90, CVector, CVector>(point, playerPosn);
}

// Converted from cdecl CPed* CWorld::FindUnsuspectingTargetPed(CVector point,CVector playerPosn) 0x566DA0
CPed* CWorld::FindUnsuspectingTargetPed(CVector point, CVector playerPosn) {
    return plugin::CallAndReturn<CPed*, 0x566DA0, CVector, CVector>(point, playerPosn);
}

// Converted from cdecl bool CWorld::ProcessLineOfSightSectorList(CPtrList &ptrList,CColLine const&colLine,CColPoint &outColPoint,float &maxTouchDistance,CEntity *&outEntity,bool doSeeThroughCheck,bool doIgnoreCameraCheck,bool doShootThroughCheck) 0x566EE0
bool CWorld::ProcessLineOfSightSectorList(CPtrList& ptrList, CColLine const& colLine, CColPoint& outColPoint, float& maxTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, bool doIgnoreCameraCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x566EE0, CPtrList&, CColLine const&, CColPoint&, float&, CEntity*&, bool, bool, bool>(ptrList, colLine, outColPoint, maxTouchDistance, outEntity, doSeeThroughCheck, doIgnoreCameraCheck, doShootThroughCheck);
}

// Converted from cdecl bool CWorld::ProcessVerticalLine(CVector const&origin,float distance,CColPoint &outColPoint,CEntity *&outEntity,bool buildings, bool vehicles, bool peds, bool objects, bool dummies,bool doSeeThroughCheck,CStoredCollPoly *outCollPoly) 0x5674E0
bool CWorld::ProcessVerticalLine(CVector const& origin, float distance, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    return plugin::CallAndReturn<bool, 0x5674E0, CVector const&, float, CColPoint&, CEntity*&, bool, bool, bool, bool, bool, bool, CStoredCollPoly*>(origin, distance, outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, outCollPoly);
}

// Converted from cdecl bool CWorld::ProcessVerticalLine_FillGlobeColPoints(CVector const&origin,float distance,CEntity *&outEntity,bool buildings, bool vehicles, bool peds, bool objects, bool dummies,bool doSeeThroughCheck,CStoredCollPoly *outCollPoly) 0x567620
bool CWorld::ProcessVerticalLine_FillGlobeColPoints(CVector const& origin, float distance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    return plugin::CallAndReturn<bool, 0x567620, CVector const&, float, CEntity*&, bool, bool, bool, bool, bool, bool, CStoredCollPoly*>(origin, distance, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, outCollPoly);
}

// Converted from cdecl void CWorld::TriggerExplosionSectorList(CPtrList &ptrList,CVector const&point,float radius,float visibleDistance,CEntity *victim,CEntity *creator,bool processVehicleBombTimer,float damage) 0x567750
void CWorld::TriggerExplosionSectorList(CPtrList& ptrList, CVector const& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage) {
    plugin::Call<0x567750, CPtrList&, CVector const&, float, float, CEntity*, CEntity*, bool, float>(ptrList, point, radius, visibleDistance, victim, creator, processVehicleBombTimer, damage);
}

// Converted from cdecl void CWorld::Process(void) 0x5684A0
void CWorld::Process() {
    plugin::Call<0x5684A0>();
}

// Converted from cdecl bool CWorld::GetIsLineOfSightSectorClear(CSector &sector,CRepeatSector &repeatSector,CColLine const&colLine,bool buildings, bool vehicles, bool peds, bool objects, bool dummies,bool doSeeThroughCheck,bool doIgnoreCameraCheck) 0x568AD0
bool CWorld::GetIsLineOfSightSectorClear(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doIgnoreCameraCheck) {
    return plugin::CallAndReturn<bool, 0x568AD0, CSector&, CRepeatSector&, CColLine const&, bool, bool, bool, bool, bool, bool, bool>(sector, repeatSector, colLine, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doIgnoreCameraCheck);
}

// Converted from cdecl void CWorld::FindObjectsKindaColliding(CVector const&point,float radius,bool b2D,short *outCount,short maxCount,CEntity **outEntities,bool buildings, bool vehicles, bool peds, bool objects, bool dummies) 0x568B80
void CWorld::FindObjectsKindaColliding(CVector const& point, float radius, bool b2D, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    plugin::Call<0x568B80, CVector const&, float, bool, short*, short, CEntity**, bool, bool, bool, bool, bool>(point, radius, b2D, outCount, maxCount, outEntities, buildings, vehicles, peds, objects, dummies);
}

// Converted from cdecl void CWorld::FindObjectsIntersectingCube(CVector const&cornerA,CVector const&cornerB,short *outCount,short maxCount,CEntity **outEntities,bool buildings, bool vehicles, bool peds, bool objects, bool dummies) 0x568DD0
void CWorld::FindObjectsIntersectingCube(CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    plugin::Call<0x568DD0, CVector const&, CVector const&, short*, short, CEntity**, bool, bool, bool, bool, bool>(cornerA, cornerB, outCount, maxCount, outEntities, buildings, vehicles, peds, objects, dummies);
}

// Converted from cdecl void CWorld::FindObjectsIntersectingAngledCollisionBox(CBox const&box,CMatrix const&transform,CVector const&point,float x1,float y1,float x2,float y2,short *outCount,short maxCount,CEntity **outEntities,bool buildings, bool vehicles, bool peds, bool objects, bool dummies) 0x568FF0
void CWorld::FindObjectsIntersectingAngledCollisionBox(CBox const& box, CMatrix const& transform, CVector const& point, float x1, float y1, float x2, float y2, short* outCount, short maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    plugin::Call<0x568FF0, CBox const&, CMatrix const&, CVector const&, float, float, float, float, short*, short, CEntity**, bool, bool, bool, bool, bool>(box, transform, point, x1, y1, x2, y2, outCount, maxCount, outEntities, buildings, vehicles, peds, objects, dummies);
}

// Converted from cdecl void CWorld::FindMissionEntitiesIntersectingCube(CVector const&cornerA,CVector const&cornerB,short *outCount,short maxCount,CEntity **outEntities,bool vehicles,bool peds,bool objects) 0x569240
void CWorld::FindMissionEntitiesIntersectingCube(CVector const& cornerA, CVector const& cornerB, short* outCount, short maxCount, CEntity** outEntities, bool vehicles, bool peds, bool objects) {
    plugin::Call<0x569240, CVector const&, CVector const&, short*, short, CEntity**, bool, bool, bool>(cornerA, cornerB, outCount, maxCount, outEntities, vehicles, peds, objects);
}

// Converted from cdecl void CWorld::FindNearestObjectOfType(int modelId,CVector const&point,float radius,bool b2D,bool buildings, bool vehicles, bool peds, bool objects, bool dummies) 0x5693F0
void CWorld::FindNearestObjectOfType(int modelId, CVector const& point, float radius, bool b2D, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    plugin::Call<0x5693F0, int, CVector const&, float, bool, bool, bool, bool, bool, bool>(modelId, point, radius, b2D, buildings, vehicles, peds, objects, dummies);
}

// Converted from cdecl float CWorld::FindGroundZForCoord(float x,float y) 0x569660
float CWorld::FindGroundZForCoord(float x, float y) {
    return plugin::CallAndReturn<float, 0x569660, float, float>(x, y);
}

// Converted from cdecl float CWorld::FindGroundZFor3DCoord(float x,float y,float z,bool *outResult,CEntity **outEntity) 0x5696C0
float CWorld::FindGroundZFor3DCoord(float x, float y, float z, bool* outResult, CEntity** outEntity) {
    return plugin::CallAndReturn<float, 0x5696C0, float, float, float, bool*, CEntity**>(x, y, z, outResult, outEntity);
}

// Converted from cdecl float CWorld::FindRoofZFor3DCoord(float x,float y,float z,bool *outResult) 0x569750
float CWorld::FindRoofZFor3DCoord(float x, float y, float z, bool* outResult) {
    return plugin::CallAndReturn<float, 0x569750, float, float, float, bool*>(x, y, z, outResult);
}

// Converted from cdecl float CWorld::FindLowestZForCoord(float x,float y) 0x5697F0
float CWorld::FindLowestZForCoord(float x, float y) {
    return plugin::CallAndReturn<float, 0x5697F0, float, float>(x, y);
}

// Converted from cdecl void CWorld::RepositionOneObject(CEntity *object) 0x569850
void CWorld::RepositionOneObject(CEntity* object) {
    plugin::Call<0x569850, CEntity*>(object);
}

// Converted from cdecl CEntity* CWorld::TestSphereAgainstWorld(CVector sphereCenter,float sphereRadius,CEntity *,bool buildings, bool vehicles, bool peds, bool objects, bool dummies,bool doCameraIgnoreCheck) 0x569E20
CEntity* CWorld::TestSphereAgainstWorld(CVector sphereCenter, float sphereRadius, CEntity* arg2, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doCameraIgnoreCheck) {
    return plugin::CallAndReturn<CEntity*, 0x569E20, CVector, float, CEntity*, bool, bool, bool, bool, bool, bool>(sphereCenter, sphereRadius, arg2, buildings, vehicles, peds, objects, dummies, doCameraIgnoreCheck);
}

// Converted from cdecl void CWorld::ClearExcitingStuffFromArea(CVector const&point,float radius,uchar bRemoveProjectilesAndShadows) 0x56A0D0
void CWorld::ClearExcitingStuffFromArea(CVector const& point, float radius, unsigned char bRemoveProjectilesAndShadows) {
    plugin::Call<0x56A0D0, CVector const&, float, unsigned char>(point, radius, bRemoveProjectilesAndShadows);
}

// Converted from cdecl bool CWorld::GetIsLineOfSightClear(CVector const&origin,CVector const&target,bool buildings, bool vehicles, bool peds, bool objects, bool dummies,bool doSeeThroughCheck,bool doCameraIgnoreCheck) 0x56A490
bool CWorld::GetIsLineOfSightClear(CVector const& origin, CVector const& target, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck) {
    return plugin::CallAndReturn<bool, 0x56A490, CVector const&, CVector const&, bool, bool, bool, bool, bool, bool, bool>(origin, target, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doCameraIgnoreCheck);
}

// Converted from cdecl bool CWorld::ProcessLineOfSightSector(CSector &sector,CRepeatSector &repeatSector,CColLine const&colLine,CColPoint &outColPoint,float &maxTouchDistance,CEntity *&outEntity,bool buildings, bool vehicles, bool peds, bool objects, bool dummies,bool doSeeThroughCheck,bool doCameraIgnoreCheck,bool doShootThroughCheck) 0x56B5E0
bool CWorld::ProcessLineOfSightSector(CSector& sector, CRepeatSector& repeatSector, CColLine const& colLine, CColPoint& outColPoint, float& maxTouchDistance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x56B5E0, CSector&, CRepeatSector&, CColLine const&, CColPoint&, float&, CEntity*&, bool, bool, bool, bool, bool, bool, bool, bool>(sector, repeatSector, colLine, outColPoint, maxTouchDistance, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doCameraIgnoreCheck, doShootThroughCheck);
}

// Converted from cdecl void CWorld::TriggerExplosion(CVector const&point,float radius,float visibleDistance,CEntity *victim,CEntity *creator,bool processVehicleBombTimer,float damage) 0x56B790
void CWorld::TriggerExplosion(CVector const& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage) {
    plugin::Call<0x56B790, CVector const&, float, float, CEntity*, CEntity*, bool, float>(point, radius, visibleDistance, victim, creator, processVehicleBombTimer, damage);
}

// Converted from cdecl void CWorld::SetWorldOnFire(float x,float y,float z,float radius,CEntity *fireCreator) 0x56B910
void CWorld::SetWorldOnFire(float x, float y, float z, float radius, CEntity* fireCreator) {
    plugin::Call<0x56B910, float, float, float, float, CEntity*>(x, y, z, radius, fireCreator);
}

// Converted from cdecl void CWorld::RepositionCertainDynamicObjects(void) 0x56B9C0
void CWorld::RepositionCertainDynamicObjects() {
    plugin::Call<0x56B9C0>();
}

// Converted from cdecl bool CWorld::ProcessLineOfSight(CVector const&origin,CVector const&target,CColPoint &outColPoint,CEntity *&outEntity,bool buildings, bool vehicles, bool peds, bool objects, bool dummies,bool doSeeThroughCheck,bool doCameraIgnoreCheck,bool doShootThroughCheck) 0x56BA00
bool CWorld::ProcessLineOfSight(CVector const& origin, CVector const& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x56BA00, CVector const&, CVector const&, CColPoint&, CEntity*&, bool, bool, bool, bool, bool, bool, bool, bool>(origin, target, outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doCameraIgnoreCheck, doShootThroughCheck);
}

void CWorld::IncrementCurrentScanCode()
{
    if (CWorld::ms_nCurrentScanCode >= 65535u)
    {
        CWorld::ClearScanCodes();
        CWorld::ms_nCurrentScanCode = 1;
    }
    else
    {
        ++CWorld::ms_nCurrentScanCode;
    }
}

// Converted from cdecl short GetCurrentScanCode() 0x407250
short GetCurrentScanCode() {
    return plugin::CallAndReturn<short, 0x407250>();
}

// Converted from cdecl CSector* GetSector(int x, int y) 0x407260
CSector* GetSector(int x, int y) {
    return plugin::CallAndReturn<CSector*, 0x407260, int, int>(x, y);
}

// Converted from cdecl CRepeatSector* GetRepeatSector(int x, int y) 0x4072A0
CRepeatSector* GetRepeatSector(int x, int y) {
    return plugin::CallAndReturn<CRepeatSector*, 0x4072A0, int, int>(x, y);
}

// Converted from cdecl CPtrListSingleLink* GetLodPtrList(int x, int y) 0x4072C0
CPtrListSingleLink& CWorld::GetLodPtrList(std::int32_t x, std::int32_t y) {
    x = clamp<std::int32_t>(x, 0, MAX_LOD_PTR_LISTS_X - 1);
    y = clamp<std::int32_t>(y, 0, MAX_LOD_PTR_LISTS_Y - 1);
    return ms_aLodPtrLists[y][x];
    //return plugin::CallAndReturn<CPtrListSingleLink*, 0x4072C0, std::int32_t, std::int32_t>(x, y);
}

// Converted from cdecl void SetNextScanCode() 0x4072E0
void SetNextScanCode() {
    plugin::Call<0x4072E0>();
}

double ScaleLighting(unsigned char lighting, float fScale)
{
    return plugin::CallAndReturn<double, 0x59F0C0, unsigned char, float> (lighting, fScale);
}
