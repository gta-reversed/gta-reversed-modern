/*
    Plugin-SDK (Grand Theft Auto San Andreas) source file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#include "StdInc.h"
#include <initializer_list>
#include "IKChainManager_c.h"
#include "World.h"

int32 CWorld::TOTAL_PLAYERS = 2;
int32& CWorld::ms_iProcessLineNumCrossings = *(int32*)0xB7CD60;
float& CWorld::fWeaponSpreadRate = *(float*)0xB7CD64;
CEntity*& CWorld::pIgnoreEntity = *(CEntity**)0xB7CD68;
bool& CWorld::bSecondShift = *(bool*)0xB7CD6C;
bool& CWorld::bProcessCutsceneOnly = *(bool*)0xB7CD6D;
bool& CWorld::bForceProcessControl = *(bool*)0xB7CD6E;
bool& CWorld::bIncludeBikers = *(bool*)0xB7CD6F;
bool& CWorld::bIncludeCarTyres = *(bool*)0xB7CD70;
bool& CWorld::bIncludeDeadPeds = *(bool*)0xB7CD71;
bool& CWorld::bNoMoreCollisionTorque = *(bool*)0xB7CD72;
bool& CWorld::bDoingCarCollisions = *(bool*)0xB7CD73;
int8& CWorld::PlayerInFocus = *(int8*)0xB7CD74;
uint16& CWorld::ms_nCurrentScanCode = *(uint16*)0xB7CD78;
CPtrListSingleLink (&CWorld::ms_aLodPtrLists)[MAX_LOD_PTR_LISTS_Y][MAX_LOD_PTR_LISTS_X] = *(CPtrListSingleLink(*)[MAX_LOD_PTR_LISTS_Y][MAX_LOD_PTR_LISTS_X])0xB99EB8;
CPtrListDoubleLink& CWorld::ms_listMovingEntityPtrs = *(CPtrListDoubleLink*)0xB9ACC8;
CPtrListDoubleLink& CWorld::ms_listObjectsWithControlCode = *(CPtrListDoubleLink*)0xB9ACCC;
CColPoint* CWorld::m_aTempColPts = (CColPoint*)0xB9ACD0;
CVector& CWorld::SnookerTableMax = *(CVector*)0x8CDEF4;
CVector& CWorld::SnookerTableMin = *(CVector*)0x8CDF00;
uint32& FilledColPointIndex = *(uint32*)0xB7CD7C;
int16& TAG_SPRAYING_INCREMENT_VAL = *(int16*)0x8CDEF0;
int8& gCurCamColVars = *(int8*)0x8CCB80;

void CWorld::InjectHooks() {
    using namespace ReversibleHooks;
    // Install("CWorld", "hasCollisionBeenLoaded", 0x410CE0, &CWorld::hasCollisionBeenLoaded);
    Install("CWorld", "ProcessLineOfSightSectorList", 0x566EE0, &CWorld::ProcessLineOfSightSectorList);
    Install("CWorld", "FindUnsuspectingTargetPed", 0x566DA0, &CWorld::FindUnsuspectingTargetPed);
    Install("CWorld", "FindUnsuspectingTargetCar", 0x566C90, &CWorld::FindUnsuspectingTargetCar);
    Install("CWorld", "StopAllLawEnforcersInTheirTracks", 0x566C10, &CWorld::StopAllLawEnforcersInTheirTracks);
    Install("CWorld", "CallOffChaseForArea", 0x566A60, &CWorld::CallOffChaseForArea);
    Install("CWorld", "ExtinguishAllCarFiresInArea", 0x566950, &CWorld::ExtinguishAllCarFiresInArea);
    Install("CWorld", "SetAllCarsCanBeDamaged", 0x5668F0, &CWorld::SetAllCarsCanBeDamaged);
    Install("CWorld", "ProcessVerticalLine", 0x5674E0, &CWorld::ProcessVerticalLine);
    Install("CWorld", "ClearPedsFromArea", 0x5667F0, &CWorld::ClearPedsFromArea);
    Install("CWorld", "TestForUnusedModels", 0x566510, static_cast<void(*)()>(&CWorld::TestForUnusedModels));
    Install("CWorld", "TestForBuildingsOnTopOfEachOther_Void", 0x5664A0, static_cast<void(*)()>(&CWorld::TestForBuildingsOnTopOfEachOther));
    Install("CWorld", "PrintCarChanges", 0x566420, &CWorld::PrintCarChanges);
    Install("CWorld", "TestSphereAgainstSectorList", 0x566140, &CWorld::TestSphereAgainstSectorList);
    Install("CWorld", "UseDetonator", 0x5660B0, &CWorld::UseDetonator);
    Install("CWorld", "RemoveFallenCars", 0x565E80, &CWorld::RemoveFallenCars);
    Install("CWorld", "RemoveFallenPeds", 0x565CB0, &CWorld::RemoveFallenPeds);
    Install("CWorld", "ClearCarsFromArea", 0x566610, &CWorld::ClearCarsFromArea);
    Install("CWorld", "ProcessVerticalLine_FillGlobeColPoints", 0x567620, &CWorld::ProcessVerticalLine_FillGlobeColPoints);
    Install("CWorld", "TriggerExplosionSectorList", 0x567750, &CWorld::TriggerExplosionSectorList);
    //Install("CWorld", "Process", 0x5684A0, &CWorld::Process, true); // Unhooked by default, crashes in IkChain.Update
    Install("CWorld", "SetWorldOnFire", 0x56B910, &CWorld::SetWorldOnFire);
    Install("CWorld", "TriggerExplosion", 0x56B790, &CWorld::TriggerExplosion);
    Install("CWorld", "ProcessLineOfSightSector", 0x56B5E0, &CWorld::ProcessLineOfSightSector);
    Install("CWorld", "GetIsLineOfSightClear", 0x56A490, &CWorld::GetIsLineOfSightClear);
    Install("CWorld", "ClearExcitingStuffFromArea", 0x56A0D0, &CWorld::ClearExcitingStuffFromArea);
    Install("CWorld", "TestSphereAgainstWorld", 0x569E20, &CWorld::TestSphereAgainstWorld);
    Install("CWorld", "RepositionOneObject", 0x569850, &CWorld::RepositionOneObject);
    Install("CWorld", "FindLowestZForCoord", 0x5697F0, &CWorld::FindLowestZForCoord);
    Install("CWorld", "FindRoofZFor3DCoord", 0x569750, &CWorld::FindRoofZFor3DCoord);
    Install("CWorld", "FindGroundZFor3DCoord", 0x5696C0, &CWorld::FindGroundZFor3DCoord);// Install("CWorld", "FindGroundZForCoord", 0x569660, &CWorld::FindGroundZForCoord);
    Install("CWorld", "FindNearestObjectOfType", 0x5693F0, &CWorld::FindNearestObjectOfType);
    Install("CWorld", "FindMissionEntitiesIntersectingCube", 0x569240, &CWorld::FindMissionEntitiesIntersectingCube);
    Install("CWorld", "FindObjectsIntersectingAngledCollisionBox", 0x568FF0, &CWorld::FindObjectsIntersectingAngledCollisionBox);
    Install("CWorld", "FindObjectsIntersectingCube", 0x568DD0, &CWorld::FindObjectsIntersectingCube);
    Install("CWorld", "FindObjectsKindaColliding", 0x568B80, &CWorld::FindObjectsKindaColliding);
    Install("CWorld", "GetIsLineOfSightSectorClear", 0x568AD0, &CWorld::GetIsLineOfSightSectorClear);
    Install("CWorld", "SprayPaintWorld", 0x565B70, &CWorld::SprayPaintWorld);
    Install("CWorld", "SetCarsOnFire", 0x5659F0, &CWorld::SetCarsOnFire);
    Install("CWorld", "SetPedsChoking", 0x565800, &CWorld::SetPedsChoking);
    Install("CWorld", "SetPedsOnFire", 0x565610, &CWorld::SetPedsOnFire);
    Install("CWorld", "CallOffChaseForAreaSectorListVehicles", 0x563A80, &CWorld::CallOffChaseForAreaSectorListVehicles);
    Install("CWorld", "RemoveEntityInsteadOfProcessingIt", 0x563A10, &CWorld::RemoveEntityInsteadOfProcessingIt);
    Install("CWorld", "TestForUnusedModels_InputArray", 0x5639D0, static_cast<void(*)(CPtrList&, int32*)>(&CWorld::TestForUnusedModels));
    Install("CWorld", "TestForBuildingsOnTopOfEachOther", 0x563950, static_cast<void(*)(CPtrList&)>(&CWorld::TestForBuildingsOnTopOfEachOther));
    Install("CWorld", "RemoveStaticObjects", 0x563840, &CWorld::RemoveStaticObjects);
    Install("CWorld", "ProcessVerticalLineSectorList_FillGlobeColPoints", 0x5636A0, &CWorld::ProcessVerticalLineSectorList_FillGlobeColPoints);
    Install("CWorld", "FindObjectsOfTypeInRangeSectorList", 0x5635C0, &CWorld::FindObjectsOfTypeInRangeSectorList);
    Install("CWorld", "FindObjectsInRangeSectorList", 0x563500, &CWorld::FindObjectsInRangeSectorList);
    Install("CWorld", "ClearScanCodes", 0x563470, &CWorld::ClearScanCodes);
    Install("CWorld", "ProcessPedsAfterPreRender", 0x563430, &CWorld::ProcessPedsAfterPreRender);
    Install("CWorld", "ProcessForAnimViewer", 0x5633D0, &CWorld::ProcessForAnimViewer);
    Install("CWorld", "CastShadowSectorList", 0x563390, &CWorld::CastShadowSectorList);
    Install("CWorld", "ProcessVerticalLineSectorList", 0x5632B0, &CWorld::ProcessVerticalLineSectorList);
    Install("CWorld", "Remove", 0x563280, &CWorld::Remove);
    Install("CWorld", "Add", 0x563220, &CWorld::Add);
    Install("CWorld", "Initialise", 0x5631E0, &CWorld::Initialise);
    Install("CWorld", "ResetLineTestOptions", 0x5631C0, &CWorld::ResetLineTestOptions);
    Install("CWorld", "CallOffChaseForAreaSectorListPeds", 0x563D00, &CWorld::CallOffChaseForAreaSectorListPeds);
    Install("CWorld", "RepositionCertainDynamicObjects", 0x56B9C0, &CWorld::RepositionCertainDynamicObjects);
    Install("CWorld", "CameraToIgnoreThisObject", 0x563F40, &CWorld::CameraToIgnoreThisObject);
    Install("CWorld", "FindPlayerSlotWithVehiclePointer", 0x563FD0, &CWorld::FindPlayerSlotWithVehiclePointer);
    Install("CWorld", "RemoveReferencesToDeletedObject", 0x565510, &CWorld::RemoveReferencesToDeletedObject);
    Install("CWorld", "FindNearestObjectOfTypeSectorList", 0x565450, &CWorld::FindNearestObjectOfTypeSectorList);
    Install("CWorld", "FindMissionEntitiesIntersectingCubeSectorList", 0x565300, &CWorld::FindMissionEntitiesIntersectingCubeSectorList);
    Install("CWorld", "FindObjectsIntersectingAngledCollisionBoxSectorList", 0x565200, &CWorld::FindObjectsIntersectingAngledCollisionBoxSectorList);
    Install("CWorld", "FindObjectsIntersectingCubeSectorList", 0x5650E0, &CWorld::FindObjectsIntersectingCubeSectorList);
    Install("CWorld", "FindObjectsKindaCollidingSectorList", 0x565000, &CWorld::FindObjectsKindaCollidingSectorList);
    Install("CWorld", "FindLodOfTypeInRange", 0x564ED0, &CWorld::FindLodOfTypeInRange);
    Install("CWorld", "FindObjectsOfTypeInRange", 0x564C70, &CWorld::FindObjectsOfTypeInRange);
    Install("CWorld", "FindObjectsInRange", 0x564A20, &CWorld::FindObjectsInRange);
    Install("CWorld", "ProcessAttachedEntities", 0x5647F0, &CWorld::ProcessAttachedEntities);
    Install("CWorld", "GetIsLineOfSightSectorListClear", 0x564970, &CWorld::GetIsLineOfSightSectorListClear);
    Install("CWorld", "ProcessVerticalLineSector", 0x564500, &CWorld::ProcessVerticalLineSector);
    Install("CWorld", "ProcessVerticalLineSector_FillGlobeColPoints", 0x564420, &CWorld::ProcessVerticalLineSector_FillGlobeColPoints);
    Install("CWorld", "ClearForRestart", 0x564360, &CWorld::ClearForRestart);
    // Install("CWorld", "ShutDown", 0x564050, &CWorld::ShutDown);
    // Install("CWorld", "FindPlayerSlotWithVehiclePointer", 0x564000, &CWorld::FindPlayerSlotWithVehiclePointer);
    Install("CWorld", "FindPlayerSlotWithPedPointer", 0x563FA0, &CWorld::FindPlayerSlotWithPedPointer);
    // Install("CWorld", "ProcessLineOfSight", 0x56BA00, &CWorld::ProcessLineOfSight);
}

// 0x5631C0
void CWorld::ResetLineTestOptions() {
    bIncludeDeadPeds  = false;
    bIncludeCarTyres  = false;
    bIncludeBikers    = false;
    pIgnoreEntity     = nullptr;
    fWeaponSpreadRate = 0.0f;
}

// 0x5631E0
void CWorld::Initialise() {
    bDoingCarCollisions    = false;
    bNoMoreCollisionTorque = false;
    bIncludeDeadPeds       = false;
    bIncludeCarTyres       = false;
    bIncludeBikers         = false;
    bForceProcessControl   = false;
    bProcessCutsceneOnly   = false;
    bSecondShift           = false;
    pIgnoreEntity          = nullptr;
    fWeaponSpreadRate      = 0.0f;
    CIplStore::Initialise();
}

// 0x563220
void CWorld::Add(CEntity* entity) {
    entity->UpdateRW();
    entity->UpdateRwFrame();
    entity->Add();
    if (!entity->IsBuilding() && !entity->IsDummy()) {
        if (!entity->IsStatic() && !entity->m_bIsStaticWaitingForCollision) {
            entity->AsPhysical()->AddToMovingList();
        }
    }
}

// 0x563280
void CWorld::Remove(CEntity* entity) {
    entity->Remove();
    if (entity->IsPhysical())
        static_cast<CPhysical*>(entity)->RemoveFromMovingList();
}

// 0x5632B0
bool CWorld::ProcessVerticalLineSectorList(CPtrList& ptrList, const CColLine& colLine, CColPoint& colPoint, float& maxTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* collPoly) {
    auto maxTouchDistanceLocal{maxTouchDistance};

    for (CPtrNode* it = ptrList.m_node; it; it = it->m_next) {
        const auto entity = static_cast<CEntity*>(it->m_item);

        if (entity->m_nScanCode == ms_nCurrentScanCode || !entity->m_bUsesCollision || entity == pIgnoreEntity)
            continue;

        entity->m_nScanCode = ms_nCurrentScanCode;

        if (CCollision::ProcessVerticalLine(
            colLine,
            entity->GetMatrix(),
            *entity->GetColModel(),
            colPoint,
            maxTouchDistanceLocal,
            doSeeThroughCheck,
            false,
            collPoly
            )
        ) {
            outEntity = entity;
            ms_iProcessLineNumCrossings += CCollision::ms_iProcessLineNumCrossings;
        }
    }

    if (maxTouchDistanceLocal < maxTouchDistance) {
        maxTouchDistance = maxTouchDistanceLocal;
        return true;
    }

    return false;
}

// 0x563390
void CWorld::CastShadowSectorList(CPtrList& ptrList, float, float, float, float) {
    for (CPtrNode* it = ptrList.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode != ms_nCurrentScanCode && entity->m_bUsesCollision) {
            entity->m_nScanCode = ms_nCurrentScanCode;
        }
    }
}

// 0x5633D0
void CWorld::ProcessForAnimViewer() {
    for (CPtrNode* it = ms_listMovingEntityPtrs.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (!entity->m_bRemoveFromWorld) {
            entity->UpdateAnim();
            entity->UpdateRW();
        }
    }
}

// 0x563430
void CWorld::ProcessPedsAfterPreRender() {
    if (CTimer::bSkipProcessThisFrame)
        return; 

    for (CPtrNode* it = ms_listMovingEntityPtrs.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (!entity->m_bRemoveFromWorld) {
            if (entity->IsPed()) {
                static_cast<CPed*>(entity)->GetIntelligence()->ProcessAfterPreRender();
            }
        }
    }
}

// 0x563470
void CWorld::ClearScanCodes() {
    const auto ProcessList = [](const CPtrList& list) {
        for (CPtrNode* node = list.GetNode(); node; node = node->GetNext()) {
            static_cast<CEntity*>(node->m_item)->m_nScanCode = 0;
        }
    };

    for (auto y = 0; y < MAX_SECTORS_Y; y++) {
        for (auto x = 0; x < MAX_SECTORS_X; x++) {
            const auto& sector = *GetSector(x, y);
            ProcessList(sector.m_buildings);
            ProcessList(sector.m_dummies);
        }
    }

    for (auto y = 0; y < MAX_REPEAT_SECTORS_Y; y++) {
        for (auto x = 0; x < MAX_REPEAT_SECTORS_X; x++) {
            for (const auto& list : GetRepeatSector(x, y)->m_lists) {
                ProcessList(list);
            }
        }
    }
}

// 0x563500
void CWorld::FindObjectsInRangeSectorList(CPtrList& ptrList, const CVector& point, float radius, bool b2D, int16 & outCount, int16 maxCount, CEntity** outEntities) {
    const auto radiusSq = radius * radius;
    for (CPtrNode* it = ptrList.m_node, *next{}; it; it = next) {
        next = it->m_next;

        auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode)
            continue;
        entity->m_nScanCode = ms_nCurrentScanCode;

        if (b2D) {
            if (DistanceBetweenPointsSquared2D(CVector2D{ point }, entity->GetPosition()) > radiusSq)
                continue;
        } else {
            if (DistanceBetweenPointsSquared(point, entity->GetPosition()) > radiusSq)
                continue;
        }

        /* Don't stop if reached max count, because of entity scan code update */
        if (outCount < maxCount) {
            if (outEntities)
                outEntities[outCount] = entity;
            outCount++;
        }
    }
}

// 0x5635C0
void CWorld::FindObjectsOfTypeInRangeSectorList(uint32 modelId, CPtrList& ptrList, const CVector& point, float fRadiusSq, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities) {
    for (CPtrNode* it = ms_listMovingEntityPtrs.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode)
            continue;

        entity->m_nScanCode = ms_nCurrentScanCode;

        if (entity->m_nModelIndex != modelId)
            continue;

        if (b2D) {
            if (DistanceBetweenPointsSquared2D(CVector2D{ point }, entity->GetPosition()) > fRadiusSq)
                continue;
        }
        else {
            if (DistanceBetweenPoints(point, entity->GetPosition()) > fRadiusSq)
                continue;
        }

        /* Don't stop if reached max count, because of entity scan code update */
        if (*outCount < maxCount) {
            if (outEntities)
                outEntities[*outCount] = entity;
            outCount++;
        }
    }
}

// 0x5636A0
bool CWorld::ProcessVerticalLineSectorList_FillGlobeColPoints(CPtrList& ptrList, const CColLine& colLine, CEntity*& outEntity, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    const auto IsDirectionPointingUpwards = [](float startZ, float endZ) {
        return endZ >= startZ;
    };

    const auto  originalLineGoingUpwards = IsDirectionPointingUpwards(colLine.m_vecStart.z, colLine.m_vecEnd.z);

    auto localColLine = colLine;

    bool dontGoToNextNode{};
    for (CPtrNode* node = ptrList.GetNode(), *next{}; next || dontGoToNextNode;) {
        if (!dontGoToNextNode) {
            node = next;
            next = node->GetNext();
            localColLine = colLine;
        }

        dontGoToNextNode = false;

        const auto entity = static_cast<CEntity*>(node->m_item);

        if (entity->m_nScanCode == ms_nCurrentScanCode || !entity->m_bUsesCollision)
            continue;
        entity->m_nScanCode = ms_nCurrentScanCode;

        float touchDist{1.f};
        CColPoint cp{};
        if (!CCollision::ProcessVerticalLine(localColLine, entity->GetMatrix(), *entity->GetColModel(), cp, touchDist, doSeeThroughCheck, false, nullptr))
            continue;

        if (FilledColPointIndex < std::size(gaTempSphereColPoints)) { // TODO: Perhaps break if it's full?
            if (originalLineGoingUpwards == IsDirectionPointingUpwards(cp.m_vecPoint.z, localColLine.m_vecEnd.z) // Still pointing in the same direction
            ) { 
                entity->m_nScanCode = ms_nCurrentScanCode - 1;
                dontGoToNextNode = true;
                gaTempSphereColPoints[FilledColPointIndex++] = cp;
            }
            localColLine.m_vecEnd.z += originalLineGoingUpwards ? 0.1f : -0.1f;
        }
    }
}

// 0x563840
void CWorld::RemoveStaticObjects() {
    const auto ProcessList = [](const CPtrList& list) {
        for (CPtrNode* node = list.GetNode(), *next{}; node; node = next) {
            next = node->GetNext();

            const auto entity = static_cast<CEntity*>(node->m_item);
            Remove(entity);
            delete entity;
        }
    };

    for (auto y = 0; y < MAX_SECTORS_Y; y++) {
        for (auto x = 0; x < MAX_SECTORS_X; x++) {
            const auto& sector = *GetSector(x, y);
            ProcessList(sector.m_buildings);
            ProcessList(sector.m_dummies);
        }
    }

    for (auto y = 0; y < MAX_REPEAT_SECTORS_Y; y++) {
        for (auto x = 0; x < MAX_REPEAT_SECTORS_X; x++) {
            ProcessList(GetRepeatSector(x, y)->m_lists[REPEATSECTOR_OBJECTS]);
        }
    }
}

// 0x563950
void CWorld::TestForBuildingsOnTopOfEachOther(CPtrList& ptrList) {
    /* nothing meaningful */
}

// 0x5639D0
void CWorld::TestForUnusedModels(CPtrList& ptrList, int32* models) {
    for (CPtrNode* it = ms_listMovingEntityPtrs.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode)
            continue;
        entity->m_nScanCode = ms_nCurrentScanCode;
        models[entity->m_nModelIndex]++;
    }
}

// 0x563A10
void CWorld::RemoveEntityInsteadOfProcessingIt(CEntity* entity) {
    if (entity->IsPed()) {
        if (FindPlayerPed() == entity) {
            Remove(entity);
        } else {
            CPopulation::RemovePed(entity->AsPed());
        }
    } else {
        Remove(entity);
        delete entity;
    }
}

// 0x563A80
void CWorld::CallOffChaseForAreaSectorListVehicles(CPtrList& ptrList, float x1, float y1, float x2, float y2, float arg5, float arg6, float arg7, float arg8) {
    plugin::Call<0x563A80, CPtrList&, float, float, float, float, float, float, float, float>(ptrList, x1, y1, x2, y2, arg5, arg6, arg7, arg8);
}

// 0x563D00
void CWorld::CallOffChaseForAreaSectorListPeds(CPtrList& ptrList, float x1, float y1, float x2, float y2, float minX, float minY, float maxX, float maxY) {
    for (CPtrNode* node = ptrList.GetNode(), *next{}; node; node = next) {
        next = node->GetNext();

        const auto veh = static_cast<CVehicle*>(node->m_item);
        const auto pos = veh->GetPosition();
        const auto mat = (CMatrix)veh->GetMatrix();

        if (!IsPointWithinBounds2D({ minX, minY }, { maxX, maxY }, { pos }))
            continue;

        if (!veh->vehicleFlags.bIsLawEnforcer)
            continue;

        switch (veh->m_autoPilot.m_nCarMission) {
        case eCarMission::MISSION_RAMPLAYER_FARAWAY:
        case eCarMission::MISSION_RAMPLAYER_CLOSE:
        case eCarMission::MISSION_BLOCKPLAYER_FARAWAY:
        case eCarMission::MISSION_BLOCKPLAYER_CLOSE:
        case eCarMission::MISSION_3D:
        case eCarMission::MISSION_3C:
            break;
        default:
            continue;
        }

        veh->m_autoPilot.m_nTempAction = 1;
        veh->m_autoPilot.m_nTempActionTime = CTimer::GetTimeInMS() + 2000;

        if (const auto colData = veh->GetColModel()->m_pColData; colData->m_nNumSpheres) {
            for (auto i = 0; i < colData->m_nNumSpheres; i++) {
                const auto& sphere    = colData->m_pSpheres[i];
                const auto  radius    = sphere.m_fRadius;
                const auto  spherePos = MultiplyMatrixWithVector(mat, sphere.m_vecCenter);
                if (   (spherePos.x + radius > x1 && spherePos.x - radius < x2)
                    && (spherePos.y + radius > y1 && spherePos.y - radius < y2)
                ) {
                    // R* used a bool variable and then, after the loop they did this
                    // and didn't break after the sphere has been found.

                    auto& speed = veh->m_vecMoveSpeed;

                    if (pos.x <= (x1 + x2) / 2.f)
                        speed.x = std::min(speed.x, 0.0f);
                    else
                        speed.x = std::max(speed.x, 0.0f);

                    if (pos.y <= (y1 + y2) / 2.f)
                        speed.y = std::min(speed.y, 0.0f);
                    else
                        speed.y = std::max(speed.y, 0.0f);

                    break;
                }
            }
        }
    }
}

// 0x563F40
bool CWorld::CameraToIgnoreThisObject(CEntity* entity) {
    if (CGarages::IsModelIndexADoor(entity->m_nModelIndex))
        return false;

    switch (entity->AsObject()->m_pObjectInfo->m_nCameraAvoidObject) {
    case 1:
        return gCurCamColVars >= 10u;
    case 2:
        return false;
    case 3:
        return gCurCamColVars < 10u;
    default:
        return true;
    }
}

// 0x563FA0
int32 CWorld::FindPlayerSlotWithPedPointer(void* ped) {
    for (int32 i = 0; i < MAX_PLAYERS; i++) {
        if (Players[i].m_pPed == ped)
            return i;
    }
    return -1;
}

// 0x563FD0
int32 CWorld::FindPlayerSlotWithRemoteVehiclePointer(void* vehicle) {
    for (int32 i = 0; i < MAX_PLAYERS; i++) {
        if (Players[i].m_pRemoteVehicle == vehicle)
            return i;
    }
    return -1;
}

// 0x564000
int32 CWorld::FindPlayerSlotWithVehiclePointer(CEntity* vehiclePtr) {
    for (int32 i = 0; i < MAX_PLAYERS; i++) {
        if (FindPlayerVehicle(i) == vehiclePtr)
            return i;
    }
    return -1;
}

// 0x564050
void CWorld::ShutDown() {
    plugin::Call<0x564050>();
}

// 0x564360
void CWorld::ClearForRestart() {
    if (CCutsceneMgr::ms_cutsceneLoadStatus == 2)
        CCutsceneMgr::DeleteCutsceneData();

    CProjectileInfo::RemoveAllProjectiles();
    CObject::DeleteAllTempObjects();
    CObject::DeleteAllMissionObjects();
    for (auto& pSector : CWorld::ms_aRepeatSectors) {
        auto pedNode = pSector.m_lists[eRepeatSectorList::REPEATSECTOR_PEDS].GetNode();
        while (pedNode) {
            auto ped = reinterpret_cast<CPed*>(pedNode->m_item);
            pedNode = pedNode->m_next;

            ped->Remove();
            if (ped->IsPhysical())
                ped->RemoveFromMovingList();

            delete ped;
        }

        auto vehicleNode = pSector.m_lists[eRepeatSectorList::REPEATSECTOR_VEHICLES].GetNode();
        while (vehicleNode) {
            auto vehicle = reinterpret_cast<CVehicle*>(vehicleNode->m_item);
            vehicleNode = vehicleNode->m_next;

            vehicle->Remove();
            if (vehicle->IsPhysical())
                vehicle->RemoveFromMovingList();

            delete vehicle;
        }
    }

    CPickups::ReInit();
    CPools::CheckPoolsEmpty();
}

// 0x564420
bool CWorld::ProcessVerticalLineSector_FillGlobeColPoints(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    bool bSuccess{};

    bSuccess |= buildings && ProcessVerticalLineSectorList_FillGlobeColPoints(sector.m_buildings, colLine, outEntity, doSeeThroughCheck, outCollPoly);
    bSuccess |= vehicles && ProcessVerticalLineSectorList_FillGlobeColPoints(repeatSector.m_lists[0], colLine, outEntity, doSeeThroughCheck, outCollPoly);
    bSuccess |= peds && ProcessVerticalLineSectorList_FillGlobeColPoints(repeatSector.m_lists[1], colLine, outEntity, doSeeThroughCheck, outCollPoly);
    bSuccess |= objects && ProcessVerticalLineSectorList_FillGlobeColPoints(repeatSector.m_lists[2], colLine, outEntity, doSeeThroughCheck, outCollPoly);
    bSuccess |= dummies && ProcessVerticalLineSectorList_FillGlobeColPoints(sector.m_dummies, colLine, outEntity, doSeeThroughCheck, outCollPoly);

    return bSuccess;
}

// 0x564500
bool CWorld::ProcessVerticalLineSector(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    float max{1.f};

    const auto ProcessSector = [&](auto&& list) { // Wrapper to make code more readable
        ProcessVerticalLineSectorList(list, colLine, outColPoint, max, outEntity, doSeeThroughCheck, outCollPoly);
    };

    if (buildings)
        ProcessSector(sector.m_buildings);
    if (vehicles)
        ProcessSector(repeatSector.m_lists[REPEATSECTOR_VEHICLES]);
    if (peds)
        ProcessSector(repeatSector.m_lists[REPEATSECTOR_PEDS]);
    if (objects)
        ProcessSector(repeatSector.m_lists[REPEATSECTOR_OBJECTS]);
    if (dummies)
        ProcessSector(sector.m_dummies);

    return max < 1.f;
}

// 0x564600
void CWorld::CastShadow(float x1, float y1, float x2, float y2) {
    const size_t fromSecX = std::max(0, GetSectorX(x1)), fromSecY = std::max(0, GetSectorY(y1));
    const size_t toSexX = std::min(120, GetSectorX(x2)), toSecY = std::min(120, GetSectorY(y2));

    IncrementCurrentScanCode();

    for (size_t x = fromSecX; x <= toSexX; x++) {
        for (size_t y = fromSecY; y <= toSecY; y++) {
            CastShadowSectorList(GetSector(x, y)->m_buildings, 0.0f, 0.0f, 0.0f, 0.0f); // todo (Izzotop): Add a comment why these 4 floats are useless
        }
    }
}

// 0x5647F0
void CWorld::ProcessAttachedEntities() {
    for (int32 i = CPools::ms_pVehiclePool->GetSize(); i; i--) {
        if (CVehicle* veh = CPools::ms_pVehiclePool->GetAt(i - 1)) {
            if (const auto attachedTo = veh->m_pAttachedTo) {
                veh->m_pEntityIgnoredCollision = attachedTo;
                veh->PositionAttachedEntity();
                veh->UpdateRW();
                veh->UpdateRwFrame();
            }
        }
    }

    for (int32 i = CPools::ms_pObjectPool->GetSize(); i; i--) {
        if (CObject* obj = CPools::ms_pObjectPool->GetAt(i - 1)) {
            if (const auto attachedTo = obj->m_pAttachedTo) {
                Remove(obj);

                obj->PositionAttachedEntity();
                obj->UpdateRW();
                obj->UpdateRwFrame();
                obj->UpdateRW();
                obj->UpdateRwFrame();
                obj->Add();

                if (!obj->IsBuilding() && !obj->IsDummy()) { // TODO: I think this was meant to be IsPhysical? Maybe CObject had a non-virtual `IsPhysical` as well?
                    if (!obj->IsStatic()) {
                        obj->AddToMovingList();
                    }
                }
            }
        }
    }
}

// 0x564970
bool CWorld::GetIsLineOfSightSectorListClear(CPtrList& ptrList, const CColLine& colLine, bool doSeeThroughCheck, bool doCameraIgnoreCheck) {
    for (CPtrNode* it = ptrList.m_node; it;) {
        auto entity = static_cast<CEntity*>(it->m_item);
        it = it->m_next;

        if (entity->m_nScanCode == ms_nCurrentScanCode || !entity->m_bUsesCollision)
            continue;
        entity->m_nScanCode = ms_nCurrentScanCode;

        if (entity == pIgnoreEntity)
            continue;

        if (doCameraIgnoreCheck && CameraToIgnoreThisObject(entity))
            continue;

        if (CCollision::TestLineOfSight(colLine, entity->GetMatrix(), *entity->GetColModel(), doSeeThroughCheck, false))
            return false;
    }
    return true;
}

// 0x564A20
void CWorld::FindObjectsInRange(const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    const int32 startSectorX = GetSectorX(point.x - radius);
    const int32 startSectorY = GetSectorY(point.y - radius);
    const int32 endSectorX = GetSectorX(point.x + radius);
    const int32 endSectorY = GetSectorY(point.y + radius);

    IncrementCurrentScanCode();

    CEntity* hitEntity{};
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list) {
                FindObjectsInRangeSectorList(list, point, radius, b2D, *outCount, maxCount, outEntities);
            };

            auto sector = GetSector(sectorX, sectorY);
            auto repeatSector = GetRepeatSector(sectorX, sectorY);

            if (buildings)
                ProcessSector(sector->m_buildings);
            if (vehicles)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES]);
            if (peds)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS]);
            if (objects)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            if (dummies)
                ProcessSector(sector->m_dummies);
        }
    }
}

// 0x564C70
void CWorld::FindObjectsOfTypeInRange(uint32 modelId, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    const int32 startSectorX = GetSectorX(point.x - radius);
    const int32 startSectorY = GetSectorY(point.y - radius);
    const int32 endSectorX = GetSectorX(point.x + radius);
    const int32 endSectorY = GetSectorY(point.y + radius);

    IncrementCurrentScanCode();

    CEntity* hitEntity{};
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list) {
                FindObjectsOfTypeInRangeSectorList(modelId, list, point, radius, b2D, outCount, maxCount, outEntities);
            };

            auto sector = GetSector(sectorX, sectorY);
            auto repeatSector = GetRepeatSector(sectorX, sectorY);

            if (buildings)
                ProcessSector(sector->m_buildings);
            if (vehicles)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES]);
            if (peds)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS]);
            if (objects)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            if (dummies)
                ProcessSector(sector->m_dummies);
        }
    }
}

// 0x564ED0
void CWorld::FindLodOfTypeInRange(uint32 modelId, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities) {
    const int32 startSectorX = GetLodSectorX(point.x - radius);
    const int32 startSectorY = GetLodSectorY(point.y - radius);
    const int32 endSectorX = GetLodSectorX(point.x + radius);
    const int32 endSectorY = GetLodSectorY(point.y + radius);

    IncrementCurrentScanCode();

    *outCount = 0;
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            FindObjectsOfTypeInRangeSectorList(modelId, GetLodPtrList(sectorX, sectorY), point, radius, b2D, outCount, maxCount, outEntities);
        }
    }
}

// 0x565000
void CWorld::FindObjectsKindaCollidingSectorList(CPtrList& ptrList, const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities) {
    for (CPtrNode* it = ms_listMovingEntityPtrs.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode)
            continue;

        entity->m_nScanCode = ms_nCurrentScanCode;

        const float fRadiusToCheck = CModelInfo::GetModelInfo(entity->m_nModelIndex)->GetColModel()->GetBoundRadius() + radius;
        if (b2D) {
            if (DistanceBetweenPoints2D(CVector2D{ point }, entity->GetBoundCentre()) >= fRadiusToCheck)
                continue;
        } else {
            if (DistanceBetweenPoints(point, entity->GetBoundCentre()) >= fRadiusToCheck)
                continue;
        }

        if (*outCount < maxCount) {
            if (outEntities)
                outEntities[*outCount] = entity;
            outCount++;
        }
    }
}

// 0x5650E0
void CWorld::FindObjectsIntersectingCubeSectorList(CPtrList& ptrList, const CVector& min, const CVector& max, int16* outCount, int16 maxCount, CEntity** outEntities) {
    for (CPtrNode* it = ms_listMovingEntityPtrs.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode)
            continue;

        entity->m_nScanCode = ms_nCurrentScanCode;

        const float fBoundRadius = entity->GetColModel()->GetBoundRadius();
        const CVector pos = entity->GetPosition();

        // TODO:
        // The check below can be done using a bounding box.
        // const CVector vecOfRadius{fBoundRadius, fBoundRadius, fBoundRadius};
        // CBoundingBox bb{min - vecOfRadius, max + vecOfRadius};
        // bb.IsPointWithin(pos);

        if (pos.x + fBoundRadius >= min.x &&
            pos.x - fBoundRadius <= max.x && 
            pos.y + fBoundRadius >= min.y && 
            pos.y - fBoundRadius <= max.y && 
            pos.z + fBoundRadius >= min.z && 
            pos.z - fBoundRadius <= max.z 
        ) {
            if (*outCount < maxCount) {
                if (outEntities)
                    outEntities[*outCount] = entity;
                outCount++;
            }
        }
    }
}

// 0x565200
void CWorld::FindObjectsIntersectingAngledCollisionBoxSectorList(CPtrList& ptrList, CBox const& box, const CMatrix& transform, const CVector& point, int16* outCount, int16 maxCount, CEntity** outEntities) {
    for (CPtrNode* it = ms_listMovingEntityPtrs.m_node; it; it = it->m_next) {
        auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode)
            continue;
        entity->m_nScanCode = ms_nCurrentScanCode;

        CColSphere sphere{};
        sphere.Set(
            entity->GetColModel()->GetBoundRadius(),
            Multiply3x3(entity->GetPosition() - point, transform)
        );

        if (CCollision::TestSphereBox(sphere, box)) {
            if (*outCount < maxCount) {
                if (outEntities)
                    outEntities[*outCount] = entity;
                outCount++;
            }
        }
    }
}

// 0x565300
// Man, sometimes I wonder whoever wrote this code was just drunk
// Also, seems like namespaces weren't a thing in C++03.. Well, at least to R*.
void CWorld::FindMissionEntitiesIntersectingCubeSectorList(CPtrList& ptrList, const CVector& cornerA, const CVector& cornerB, int16* outCount, int16 maxCount, CEntity** outEntities, bool vehiclesList, bool pedsList, bool objectsList) {
    // NOTSA - Easier to do it this way..
    const CBoundingBox bb{ cornerA, cornerB };
    for (CPtrNode* node = ptrList.GetNode(), *next{}; node; node = next) {
        next = node->GetNext();

        const auto entity = static_cast<CEntity*>(node->m_item);
        if (entity->m_nScanCode == GetCurrentScanCode())
            continue;
        entity->m_nScanCode = ms_nCurrentScanCode;

        if (vehiclesList) {
            if (entity->AsVehicle()->GetCreatedBy() != eVehicleCreatedBy::MISSION_VEHICLE)
                continue;
        } else if (pedsList) {
            if (!entity->AsPed()->IsCreatedByMission())
                continue;
        } else { // They didn't even bother to use `else if (objectsList)` here xD
            switch (entity->AsObject()->m_nObjectType) {
            case eObjectType::OBJECT_MISSION:
            case eObjectType::OBJECT_MISSION2:
                break;
            default:
                continue;
            }
        }

        if (bb.IsPointWithin(entity->GetPosition())) {
            if (*outCount < maxCount) {
                outEntities[*outCount++] = entity;
            } else {
                break; // NOTSA - But makes sense lol
            }
        }
    }
}

// 0x565450
void CWorld::FindNearestObjectOfTypeSectorList(int32 modelId, CPtrList& ptrList, const CVector& point, float radius, bool b2D, CEntity *& outEntity, float& outDistance) {
    for (CPtrNode* node = ptrList.GetNode(), *next{}; node; node = next) {
        next = node->GetNext();

        const auto entity = static_cast<CEntity*>(node->m_item);
        if (entity->m_nScanCode == GetCurrentScanCode())
            continue;
        entity->m_nScanCode = ms_nCurrentScanCode;

        const auto GetDistance = [&] {
            if (b2D)
                return DistanceBetweenPoints2D({ point }, { entity->GetPosition() });
            return DistanceBetweenPoints(point, entity->GetPosition());
        };

        if (const float dist = GetDistance(); dist <= radius) {
            outDistance = dist;
            outEntity   = entity;
        }
    }
}

// 0x565510
void CWorld::RemoveReferencesToDeletedObject(CEntity* entity) {
    for (int32 i = CPools::ms_pPedPool->GetSize(); i; i--) {
        if (CPed* ped = CPools::ms_pPedPool->GetAt(i - 1)) {
            if (ped != entity) {
                ped->RemoveRefsToEntity(entity);
                if (ped->m_standingOnEntity == entity)
                    ped->m_standingOnEntity = nullptr;
            }
        }
    }

    for (int32 i = CPools::ms_pVehiclePool->GetSize(); i; i--) {
        if (CVehicle* veh = CPools::ms_pVehiclePool->GetAt(i - 1)) {
            if (veh != entity) {
                veh->RemoveRefsToEntity(entity);
                veh->RemoveRefsToVehicle(entity);
            }
        }
    }

    for (int32 i = CPools::ms_pObjectPool->GetSize(); i; i--) {
        if (CObject* obj = CPools::ms_pObjectPool->GetAt(i - 1)) {
            if (obj != entity) {
                obj->RemoveRefsToEntity(entity);
            }
        }
    }
}

// 0x565610
// NOTE: Radius is treated as a cuboid with the height of 10, width and length of 2 * radius
//       Radius for `fireCreator` ped is halved
void CWorld::SetPedsOnFire(float x, float y, float z, float radius, CEntity* fireCreator) {
    for (int32 i = CPools::ms_pPedPool->GetSize(); i; i--) {
        if (CPed* ped = CPools::ms_pPedPool->GetAt(i - 1)) {
            float radiusForThisPed = ped == fireCreator ? radius / 2.f : radius;

            // NOTSA - Originally it was some abs() macro crap, we ain't gonna do it like that
            const CBoundingBox bb{
                {x - radiusForThisPed, y - radiusForThisPed, z - 5.f},
                {x + radiusForThisPed, y + radiusForThisPed, z + 5.f}
            };

            if (   ped->m_nPedState != PEDSTATE_DEAD
                && !ped->bInVehicle
                && !ped->physicalFlags.bFireProof
                && !ped->m_pFire
                && bb.IsPointWithin(ped->GetPosition())
            ) {
                if (   ped->physicalFlags.bInvulnerable
                    || !fireCreator
                    || fireCreator->IsPed() && fireCreator->AsPed()->IsPlayer()
                ) {
                    gFireManager.StartFire(ped, fireCreator, 0.8f, 1, 7000, 2);
                }
            }

        }
    }
}

// 0x565800
// NOTE: Radius is treated as a cuboid with the height of 10, width and length of 2 * radius
void CWorld::SetPedsChoking(float x, float y, float z, float radius, CEntity* gasCreator) {
    const CVector point{ x, y, z };

    // NOTSA - Originally it was some abs() macro crap, we ain't gonna do it like that
    const CBoundingBox bb{
        {x - radius, y - radius, z - 5.f},
        {x + radius, y + radius, z + 5.f}
    };

    for (int32 i = CPools::ms_pPedPool->GetSize(); i; i--) {
        if (CPed* ped = CPools::ms_pPedPool->GetAt(i - 1)) {
            if (    ped->m_nPedState != PEDSTATE_DEAD
                && !ped->bInVehicle
                && !ped->physicalFlags.bFireProof
                && !ped->m_pFire
                && !ped->IsCreatedByMission()
                &&  bb.IsPointWithin(ped->GetPosition())
            ) {
                CWeapon::GenerateDamageEvent(
                    ped,
                    gasCreator,
                    eWeaponType::WEAPON_TEARGAS,
                    1,
                    ePedPieceTypes::PED_PIECE_TORSO,
                    ped->GetLocalDirection(ped->GetPosition() - CVector{x, y, z})
                );   
            }
        }
    }
}

// 0x5659F0
// NOTE: Radius is treated as a cuboid with the height of 10, width and length of 2 * radius
void CWorld::SetCarsOnFire(float x, float y, float z, float radius, CEntity* fireCreator) {
    // NOTSA - Originally it was some abs() macro crap, we ain't gonna do it like that
    const CBoundingBox bb{
        {x - radius, y - radius, z - 5.f},
        {x + radius, y + radius, z + 5.f}
    };
    for (int32 i = CPools::ms_pVehiclePool->GetSize(); i; i--) {
        if (CVehicle* vehicle = CPools::ms_pVehiclePool->GetAt(i - 1)) {
            if (vehicle->m_nStatus == eEntityStatus::STATUS_WRECKED)
                continue;

            if (vehicle->m_pFire)
                continue; // Already on fire

            if (vehicle->physicalFlags.bFireProof)
                continue;

            if (bb.IsPointWithin(vehicle->GetPosition())) {
                gFireManager.StartFire(vehicle, fireCreator, 0.8f, 1, 7000, 100);
            }
        }
    }
}

// 0x565B70
bool CWorld::SprayPaintWorld(CVector& posn, CVector& outDir, float radius, bool processTagAlphaState) {
    CEntity* objects[15]{};
    int16 count{};
    FindObjectsInRange(posn, radius, false, &count, std::size(objects), objects, true, false, false, false, false);
    if (!count)
        return 0;

    bool hasChangedAlphaTo255{}, hasFoundTag{};
    for (auto i = 0; i < count; i++) {
        auto entity = objects[i];
        if (!CTagManager::IsTag(entity))
            continue;

        hasFoundTag = true;

        outDir = entity->GetForward();

        // Note: Original code has U.B. if `processTagAlphaState` is false, because `newAlpha` isn't assigned a meaningful value
        // But the only place this function is called has set `processTagAlphaState` to true, so..
        uint8 currAlpha = CTagManager::GetAlpha(entity), newAlpha{};
        if (processTagAlphaState) {
            newAlpha = std::min<uint8>(255u, currAlpha + (uint8)TAG_SPRAYING_INCREMENT_VAL);
        }

        if (currAlpha != 255 && newAlpha == 255)
            hasChangedAlphaTo255 = true;

        CTagManager::SetAlpha(entity, newAlpha);
    }

    return hasChangedAlphaTo255 ? 2 :
           hasFoundTag ? 1 : 0;
}

// 0x565CB0
void CWorld::RemoveFallenPeds() {
    for (int32 i = CPools::ms_pPedPool->GetSize(); i; i--) {
        CPed* ped = CPools::ms_pPedPool->GetAt(i - 1);
        if (!ped)
            continue;

        const CVector& vecPedPos = ped->GetPosition();
        if (vecPedPos.z > -100.0f)
            continue;
        if (!ped->IsCreatedBy(ePedCreatedBy::PED_GAME) || ped->IsPlayer()) {
            CNodeAddress pathNodeAddress;
            ThePaths.FindNodeClosestToCoors(&pathNodeAddress, vecPedPos.x, vecPedPos.y, vecPedPos.z, 1, 1000000.0f, 0, 0, 0, 0, 0);
            if (pathNodeAddress.m_wAreaId != -1) {
                CVector pathNodePos = ThePaths.GetPathNode(pathNodeAddress)->GetNodeCoors();
                pathNodePos.z += 2.0f;
                ped->Teleport(pathNodePos, false);
            } else
                ped->SetPosn(vecPedPos.x, vecPedPos.y, -95);
            ped->ResetMoveSpeed();
        } else
            CPopulation::RemovePed(ped);
    }
}

// 0x565E80
void CWorld::RemoveFallenCars() {
    for (int32 i = CPools::ms_pVehiclePool->GetSize(); i; i--) {
        CVehicle* vehicle = CPools::ms_pVehiclePool->GetAt(i - 1);
        if (!vehicle)
            continue;

        const CVector& vecPos = vehicle->GetPosition();
        if (vecPos.z > -100.0f)
            continue;

        const auto ShouldWeKeepIt = [vehicle]() {
            if (vehicle->IsCreatedBy(eVehicleCreatedBy::MISSION_VEHICLE) && !vehicle->physicalFlags.bDestroyed)
                return true;

            if (vehicle == FindPlayerVehicle(-1, false))
                return true;

            return vehicle->m_pDriver && vehicle->m_pDriver->IsPlayer();
        };

        if (ShouldWeKeepIt()) {
            CNodeAddress pathNodeAddress;
            ThePaths.FindNodeClosestToCoors(&pathNodeAddress, vecPos.x, vecPos.y, vecPos.z, 1, 1000000.0f, 0, 0, 0, 0, 0);
            if (pathNodeAddress.m_wAreaId != -1) {
                const auto pathNodePos = ThePaths.GetPathNode(pathNodeAddress)->GetNodeCoors();
                vehicle->Teleport(pathNodePos + CVector(0, 0, 3), true);
            } else
                vehicle->Teleport(CVector(vecPos.x, vecPos.y, 0), true);
            vehicle->ResetMoveSpeed();
        } else {
            if (!vehicle->IsCreatedBy(eVehicleCreatedBy::RANDOM_VEHICLE))
                if (!vehicle->IsCreatedBy(eVehicleCreatedBy::PARKED_VEHICLE))
                    continue;

            vehicle->Remove();
            if (vehicle->IsPhysical())
                vehicle->RemoveFromMovingList();

            delete vehicle;
        }
    }
}

// 0x5660B0
void CWorld::UseDetonator(CPed* creator) {
    const auto vehPool = CPools::ms_pVehiclePool;
    for (auto i = 0; i < vehPool->GetSize(); i++) {
        if (const auto veh = vehPool->GetAt(i)) {
            if (veh->m_nBombOnBoard != 3)
                continue;

            if (veh->m_pWhoInstalledBombOnMe != creator)
                continue;

            veh->m_nBombOnBoard = 0;
            veh->m_wBombTimer = 500;
            veh->m_pWhoDetonatedMe = creator;
            creator->RegisterReference(reinterpret_cast<CEntity**>(&veh->m_pWhoDetonatedMe));
        }
    }
    CProjectileInfo::RemoveDetonatorProjectiles();
}

// 0x566140
// Find first entity colliding with the sphere
CEntity* CWorld::TestSphereAgainstSectorList(CPtrList& ptrList, CVector sphereCenter, float sphereRadius, CEntity* ignoreEntity, bool doCameraIgnoreCheck) {
    if (!ptrList.m_node)
        return nullptr;

    CColModel      sphereColModel{};
    CCollisionData sphereColData{};

    sphereColModel.m_pColData = &sphereColData;
    sphereColModel.m_boundBox = { {-sphereRadius, -sphereRadius, -sphereRadius}, {sphereRadius, sphereRadius, sphereRadius} };
    sphereColModel.m_boundSphere = { {}, sphereRadius };

    CColSphere csphere{ {}, sphereRadius };
    sphereColData.m_nNumSpheres = 1;
    sphereColData.m_pSpheres = &csphere;

    CMatrix sphereMatrix{};
    sphereMatrix.SetTranslate(sphereCenter);

    for (CPtrNode *node = ptrList.GetNode(), *next{}; node; node = next) {
        next = node->GetNext();

        const auto entity = static_cast<CEntity*>(node->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode)
            continue;

        if (!entity->m_bUsesCollision || ignoreEntity == entity)
            continue;

        if (doCameraIgnoreCheck && CameraToIgnoreThisObject(entity))
            continue;

        entity->m_nScanCode = ms_nCurrentScanCode;

        CColModel& entityColModel = *entity->GetColModel();

        if ((entity->GetBoundCentre() - sphereCenter).Magnitude() >= sphereRadius + entityColModel.m_boundSphere.m_fRadius)
            continue; // Bound spheres not colliding

        if (CCollision::ProcessColModels(sphereMatrix, sphereColModel, entity->GetMatrix(), entityColModel, gaTempSphereColPoints, nullptr, nullptr, false)) {
            sphereColModel.m_pColData = nullptr; // Make sure CColModel destructor doesn't try our local variable
            return entity;
        }
    }

    sphereColModel.m_pColData = nullptr; // Make sure CColModel destructor doesn't try our local variable
    return nullptr;
}

// 0x566420
// Unused
void CWorld::PrintCarChanges() {
    plugin::Call<0x566420>();
}

// 0x5664A0
void CWorld::TestForBuildingsOnTopOfEachOther() {
    for (auto y = 0; y < MAX_SECTORS_Y; y++) {
        for (auto x = 0; x < MAX_SECTORS_X; x++) {
            const auto sector = GetSector(x, y);
            TestForBuildingsOnTopOfEachOther(sector->m_buildings);
            TestForBuildingsOnTopOfEachOther(sector->m_dummies);
        }
    }
}

// 0x566510
// Unused - Probably a debug function
void CWorld::TestForUnusedModels() {
    static uint32 usageCounts[TOTAL_DFF_MODEL_IDS]{}; // SA uses a stack-allocated variable, but 80 kB on the stack isn't nice, so we are going to do it this way
    std::ranges::fill(usageCounts, 0);

    IncrementCurrentScanCode();

    const auto ProcessSectorList = [&](const CPtrList& list) {
        for (auto node = list.GetNode(); node; node = node->m_next) {
            const auto object = static_cast<CEntity*>(node->m_item);
            if (object->m_nScanCode != ms_nCurrentScanCode) {
                usageCounts[object->m_nModelIndex]++;
            }
        }
    };

    for (auto y = 0; y < MAX_SECTORS_Y; y++) {
        for (auto x = 0; x < MAX_SECTORS_X; x++) {
            const auto sector = GetSector(x, y);
            ProcessSectorList(sector->m_buildings);
            ProcessSectorList(sector->m_dummies);
        }
    }
}

// 0x566610
void CWorld::ClearCarsFromArea(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    CBoundingBox box{ {minX, minY, minZ}, {maxX, maxY, maxZ} }; // NOTSA, but makes code cleaner
    for (int32 i = 0; i < CPools::ms_pVehiclePool->GetSize(); i++) {
        if (CVehicle* veh = CPools::ms_pVehiclePool->GetAt(i)) {
            if (veh == FindPlayerPed(-1)->m_pContactEntity && veh->IsBoat())
                continue;

            if (!box.IsPointWithin(veh->GetPosition()))
                continue;

            if (veh->vehicleFlags.bIsLocked || !veh->CanBeDeleted())
                continue;

            if (auto& driver = veh->m_pDriver) { // TODO: Is this some inlined stuff?
                CPopulation::RemovePed(driver);
                driver->CleanUpOldReference(reinterpret_cast<CEntity**>(&driver));
                driver = nullptr;
            }


            for (auto i = 0; i < veh->m_nMaxPassengers; i++) {
                if (auto psngr = veh->m_apPassengers[i]) {
                    veh->RemovePassenger(psngr);
                    CPopulation::RemovePed(psngr);
                }
            }

            if (CCarCtrl::IsThisVehicleInteresting(veh))
                CGarages::StoreCarInNearestImpoundingGarage(veh);

            CCarCtrl::RemoveFromInterestingVehicleList(veh);
            Remove(veh);
            delete veh;
        }
    }
}

// 0x5667F0
void CWorld::ClearPedsFromArea(float minX, float minY, float minZ, float maxX, float maxY, float maxZ) {
    CBoundingBox box{ {minX, minY, minZ}, {maxX, maxY, maxZ} }; // NOTSA, but makes code cleaner
    for (int32 i = 0; i < CPools::ms_pPedPool->GetSize(); i++) {
        if (CPed* ped = CPools::ms_pPedPool->GetAt(i)) {
            if (!ped->IsPlayer() && ped->CanBeDeleted()) {
                if (box.IsPointWithin(ped->GetPosition())) {
                    CPopulation::RemovePed(ped);
                }
            }
        }
    }
}

// 0x5668F0
void CWorld::SetAllCarsCanBeDamaged(bool enable) {
    for (int32 i = 0; i < CPools::ms_pVehiclePool->GetSize(); i++) {
        if (CVehicle* veh = CPools::ms_pVehiclePool->GetAt(i)) {
            veh->vehicleFlags.bCanBeDamaged = enable;
        }
    }
}

// 0x566950
void CWorld::ExtinguishAllCarFiresInArea(CVector point, float radius) {
    for (int32 i = 0; i < CPools::ms_pVehiclePool->GetSize(); i++) {
        if (CVehicle* veh = CPools::ms_pVehiclePool->GetAt(i)) {
            if (DistanceBetweenPointsSquared(point, veh->GetPosition()) <= radius * radius) {
                veh->ExtinguishCarFire();
            }
        }
    }
}

// 0x566A60
void CWorld::CallOffChaseForArea(float x1, float y1, float x2, float y2) {
    const float minX = x1 - 10.f;
    const float maxX = x2 + 10.f;
    const float minY = y1 - 10.f;
    const float maxY = y2 + 10.f;
    const int32 startSectorX = GetSectorX(minX);
    const int32 startSectorY = GetSectorY(minY);
    const int32 endSectorX = GetSectorX(maxX);
    const int32 endSectorY = GetSectorY(maxY);

    IncrementCurrentScanCode();

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CRepeatSector* sector = GetRepeatSector(sectorX, sectorY);
            CallOffChaseForAreaSectorListVehicles(sector->m_lists[REPEATSECTOR_VEHICLES], x1, y1, x2, y2, minX, minY, maxX, maxY);
            CallOffChaseForAreaSectorListPeds(sector->m_lists[REPEATSECTOR_PEDS], x1, y1, x2, y2, minX, minY, maxX, maxY);
        }
    }
}

// 0x566C10
void CWorld::StopAllLawEnforcersInTheirTracks() {
    for (int32 i = 0; i < CPools::ms_pVehiclePool->GetSize(); i++) {
        if (CVehicle* veh = CPools::ms_pVehiclePool->GetAt(i)) {
            if (veh->vehicleFlags.bIsLawEnforcer) {
                veh->m_vecMoveSpeed = CVector{};
            }
        }
    }
}

// 0x566C90
CVehicle* CWorld::FindUnsuspectingTargetCar(CVector point, CVector playerPosn) {
    float nearestDist2D = std::numeric_limits<float>::max();
    CVehicle* nearestVeh{};
    for (int32 i = 0; i < CPools::ms_pVehiclePool->GetSize(); i++) {
        CVehicle* veh = CPools::ms_pVehiclePool->GetAt(i);
        if (!veh)
            continue;

        if (!veh->IsCreatedBy(eVehicleCreatedBy::RANDOM_VEHICLE) || !veh->IsSubclassAutomobile())
            continue;

        switch (veh->m_nStatus) {
        case eEntityStatus::STATUS_PHYSICS:
        case eEntityStatus::STATUS_SIMPLE:
            break;
        default:
            continue;
        }

        const float dist2D = DistanceBetweenPoints2D(point, veh->GetPosition());
        if (dist2D >= nearestDist2D)
            continue;

        if (DotProduct(playerPosn - veh->GetPosition(), veh->GetForward()) <= 0.0f)
            continue; // `point` is behind the ped

        nearestVeh = veh;
        nearestDist2D = dist2D;
    }
    return nearestVeh;
}

// 0x566DA0
CPed* CWorld::FindUnsuspectingTargetPed(CVector point, CVector playerPosn) {
    float nearestDist2D = std::numeric_limits<float>::max();
    CPed* nearestPed{};
    for (int32 i = 0; i < CPools::ms_pPedPool->GetSize(); i++) {
        CPed* ped = CPools::ms_pPedPool->GetAt(i);
        if (!ped)
            continue;

        if (!ped->IsCreatedBy(ePedCreatedBy::PED_GAME) || !ped->IsAlive())
            continue;

        if (ped->m_nPedType <= ePedType::PED_TYPE_GANG1 || ped->m_nPedType >= ePedType::PED_TYPE_GANG10)
            if (ped->m_nPedType != ePedType::PED_TYPE_CIVMALE)
                continue;

        if (CTask* pActive = ped->GetTaskManager().GetActiveTask())
            if (pActive->GetTaskType() != eTaskType::TASK_COMPLEX_WANDER)
                continue;

        const CVector pedPos = ped->GetPosition();
        const float dist2D = DistanceBetweenPoints2D(point, pedPos);
        if (dist2D >= nearestDist2D)
            continue;

        if (DotProduct(playerPosn - pedPos, ped->GetForward()) <= 0.0f)
            continue; // `point` is behind the ped

        nearestPed    = ped;
        nearestDist2D = dist2D;
    }
    return nearestPed;
}

// 0x566EE0
bool CWorld::ProcessLineOfSightSectorList(CPtrList& ptrList, const CColLine& colLine, CColPoint& outColPoint, float& minTouchDistance, CEntity*& outEntity, bool doSeeThroughCheck, bool doIgnoreCameraCheck, bool doShootThroughCheck) {
    if (!ptrList.m_node)
        return false;
     
    float localMinTouchDist = minTouchDistance;

    for (CPtrNode *it = ptrList.m_node; it; it = it->m_next) {
        //next = it->m_next;

        const auto entity = static_cast<CEntity*>(it->m_item);
        if (entity->m_nScanCode == ms_nCurrentScanCode || entity == pIgnoreEntity)
            continue;

        if (doIgnoreCameraCheck && CameraToIgnoreThisObject(entity))
            continue;

        if (!entity->m_bUsesCollision) {
            if (!entity->IsPed())
                continue;
            if (const auto ped = entity->AsPed(); !bIncludeBikers && !bIncludeDeadPeds)
                continue;
        }

        const auto ProcessColModel = [&](CColModel* colModel) {
            if (!colModel || !colModel->m_pColData)
                return;

            const auto colData = colModel->m_pColData;

            float makeBiggerBy{};

            if (fWeaponSpreadRate > 0.0f) {
                makeBiggerBy = (entity->GetPosition() - colLine.m_vecStart).Magnitude() * fWeaponSpreadRate;

                // Make bounding box bigger
                {
                    const CVector offsetVec{ makeBiggerBy , makeBiggerBy , makeBiggerBy };
                    colModel->m_boundBox.m_vecMin -= offsetVec;
                    colModel->m_boundBox.m_vecMax += offsetVec;
                }

                // Make spheres bigger
                colModel->m_boundSphere.m_fRadius += makeBiggerBy;

                if (colData->m_nNumSpheres) {
                    for (auto i = 0; i < colData->m_nNumSpheres; i++) {
                        colData->m_pSpheres[i].m_fRadius += makeBiggerBy;
                    }
                }

            }

            if (CCollision::ProcessLineOfSight(
                colLine,
                entity->GetMatrix(),
                *colModel,
                outColPoint,
                localMinTouchDist,
                doSeeThroughCheck,
                doShootThroughCheck)
            ) {
                outEntity = entity;
                ms_iProcessLineNumCrossings += CCollision::ms_iProcessLineNumCrossings;
            }

            if (makeBiggerBy > 0.0f) {
                // Undo changes made to the col. model previously

                // Bounding box
                {
                    const CVector offsetVec{ makeBiggerBy , makeBiggerBy , makeBiggerBy };
                    colModel->m_boundBox.m_vecMin += offsetVec;
                    colModel->m_boundBox.m_vecMax -= offsetVec;
                }

                // Spheres
                colModel->m_boundSphere.m_fRadius -= makeBiggerBy;

                if (colData->m_nNumSpheres) {
                    for (auto i = 0; i < colData->m_nNumSpheres; i++) {
                        colData->m_pSpheres[i].m_fRadius -= makeBiggerBy;
                    }
                }
            }
        };

        switch (entity->m_nType) {
        case eEntityType::ENTITY_TYPE_PED: {
            const auto ped = entity->AsPed();
            if (   ped->m_bUsesCollision
                || ped->m_pAttachedTo
                || (bIncludeDeadPeds && !ped->IsAlive())
                || (bIncludeBikers && ped->bTestForShotInVehicle)
            ) {
                ProcessColModel(CModelInfo::GetModelInfo(entity->m_nModelIndex)->AsPedModelInfoPtr()->AnimatePedColModelSkinned(entity->m_pRwClump));
            }
            break;
        }
        case eEntityType::ENTITY_TYPE_VEHICLE: {
            const auto veh = entity->AsVehicle();

            ProcessColModel(veh->GetColModel());

            if (bIncludeCarTyres)
                break;
            
            // Do car tyre test

            CColModel wheelCol{};
            CCollisionData colData{};
            CColSphere colSpheres[6];

            wheelCol.m_pColData = &colData;
            colData.m_nNumSpheres = std::size(colSpheres);
            colData.m_pSpheres = colSpheres;

            if (veh->SetUpWheelColModel(&wheelCol)) {
                CColPoint wheelCP{};
                float wheelTouchDist = localMinTouchDist;
                auto& mat = veh->GetMatrix();
                if (CCollision::ProcessLineOfSight(colLine, mat, wheelCol, wheelCP, wheelTouchDist, false, doShootThroughCheck)) {
                    ms_iProcessLineNumCrossings += CCollision::ms_iProcessLineNumCrossings;

                    if (wheelTouchDist < localMinTouchDist) {
                        localMinTouchDist = wheelTouchDist;
                        outColPoint = wheelCP;
                    } else {
                        // Since this col check consists only of checking the wheels
                        // if `colLine.start` is at the opposite side to the col point 
                        // will mean that the `line` went thru the vehicle body
                        // which means there must be a direct hit somewhere with the vehicle's body

                        const auto lineDir = colLine.m_vecEnd - colLine.m_vecStart;
                        const auto lineDirDot = DotProduct(lineDir, mat.GetRight());
                        const auto colPointToEntityDot = DotProduct(wheelCP.m_vecPoint - mat.GetPosition(), mat.GetRight());
                        if (lineDirDot < 0.f && colPointToEntityDot > 0.f  // Line begins at the left, col point is on the right
                            || lineDirDot > 0.f && colPointToEntityDot < 0.f) // Or the other way around
                        {
                            // And the absolute angle between the `line` and the `right` direction vector is less than 45 deg.
                            // Here they're betting on the fact that the wheel is not too far away from the body itself. (which is true in case of all vanilla models)
                            // If it is, and the vehicle is small in height this might be incorrect (because the line might go over the body itself, and just hit the wheel)
                            if (fabs(lineDirDot) / lineDir.Magnitude() > 0.5f) {
                                localMinTouchDist = wheelTouchDist;
                                outColPoint = wheelCP;
                                outEntity = entity;
                            }
                        }
                    }
                }
            }

            wheelCol.m_pColData = nullptr; // Otherwise destructor would try to free it

            break;
        }
        default: {
            ProcessColModel(entity->GetColModel());
            break;
        }
        }

        entity->m_nScanCode = ms_nCurrentScanCode; // Placed here, because the above switch has some type dependent conditions
    }

    if (localMinTouchDist < minTouchDistance) {
        //assert(outEntity != 0); // There must be one
        minTouchDistance = localMinTouchDist;
        return true;
    }
    return false;
}

// 0x5674E0
// ProcessVerticalLine => ProcessVerticalLineSector => ProcessVerticalLineSectorList => CCollision::ProcessVerticalLine
bool CWorld::ProcessVerticalLine(const CVector& origin, float distance, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    IncrementCurrentScanCode();
    ms_iProcessLineNumCrossings = 0;

    const int32 secX = GetSectorX(origin.x), secY = GetSectorY(origin.y);
    return ProcessVerticalLineSector(
        *GetSector(secX, secY),
        *GetRepeatSector(secX % MAX_REPEAT_SECTORS_X, secY % MAX_REPEAT_SECTORS_Y),
        CColLine{ origin, CVector{origin.x, origin.y, distance} },
        outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, outCollPoly
    );
}

// 0x567620
bool CWorld::ProcessVerticalLine_FillGlobeColPoints(const CVector& origin, float distance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, CStoredCollPoly* outCollPoly) {
    FilledColPointIndex = 0;

    const int32 secX = GetSectorX(origin.x), secY = GetSectorY(origin.y);
    CColLine colLine{ origin, CVector{origin.x, origin.y, distance} };
    return ProcessVerticalLineSector_FillGlobeColPoints(
        *GetSector(secX, secY),
        *GetRepeatSector(secX % MAX_REPEAT_SECTORS_X, secY % MAX_REPEAT_SECTORS_Y),
        colLine, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, outCollPoly
    );
}

// 0x567750
void CWorld::TriggerExplosionSectorList(CPtrList& ptrList, const CVector& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage) {
    for (CPtrNode* node = ptrList.GetNode(), *next{}; node; node = next) {
        next = node->GetNext();

        const auto entity = static_cast<CPhysical*>(node->m_item);
        const auto entityToPointDir = (entity->GetPosition () - point);
        const auto entityToPointDist = entityToPointDir.Magnitude();

        if (entityToPointDist >= radius)
            continue;

        if (entity->IsObject())
            entity->AsObject()->TryToExplode();

        if (entity->physicalFlags.bExplosionProof)
            continue;

        if (entity->IsPed() && entity->AsPed()->bInVehicle)
            continue;

        if (entity->IsStatic()) {
            if (!entity->IsObject()) {
                if (entity->m_bUsesCollision) {
                    entity->SetIsStatic(false);
                    entity->AddToMovingList();
                }
            } else if (!entity->physicalFlags.bDisableTurnForce) {
                const auto object = entity->AsObject();

                if (visibleDistance > object->m_pObjectInfo->m_fUprootLimit || ModelIndices::IsFence1Or2(object->m_nModelIndex)) {
                    if (IsGlassModel(object)) {
                        CGlass::WindowRespondsToExplosion(object, point);
                    } else {
                        object->SetIsStatic(false);
                        object->AddToMovingList();

                        if (   object->m_nModelIndex != ModelIndices::MI_FIRE_HYDRANT
                            || object->objectFlags.bIsExploded
                        ) {
                            if (object->IsObject() && !object->m_pObjectInfo->m_bCausesExplosion) {
                                object->objectFlags.bIsExploded = true;
                            }
                        } else {
                            g_fx.TriggerWaterHydrant(object->GetPosition());
                            object->objectFlags.bIsExploded = true;
                        }
                    }
                }        
            }

            if (entity->m_nModelIndex == ModelIndices::MI_ATM && creator == FindPlayerPed()) {
                assert(0); // NOTSA
                // Makes no sense whatsoever, especially because `radiusProgress2x` is only set after later
                // entity->AsObject()->m_fHealth -= 2 * radiusProgress2x;
            }

            if (entity->IsStatic()) { // Redudant check
                entity->AsObject()->ObjectDamage(std::min(1.0f, 2.f * (radius - entityToPointDist) / radius), nullptr, nullptr, creator, WEAPON_EXPLOSION);
            }
        }

        if (entity->IsStatic() || !entity->m_bUsesCollision)
            continue;

        const auto entityRelDistToRadiusEnd_Doubled = std::min(1.f, 2.f * (radius - entityToPointDist) / radius);


        auto impactVelocity = entityToPointDir / std::max(0.01f, entityToPointDist);
        impactVelocity.z = std::max(impactVelocity.z, 0.f);

        float impactVelocityFactor = entity->m_fMass / 1400.f * entityRelDistToRadiusEnd_Doubled * visibleDistance;

        switch (entity->m_nType) {
        case eEntityType::ENTITY_TYPE_VEHICLE: {
            const auto veh = entity->AsVehicle();

            if (auto driver = veh->m_pDriver;  veh->m_vehicleSubType == eVehicleType::VEHICLE_BMX && driver) {
                CEventKnockOffBike event{ veh, &veh->m_vecMoveSpeed, &impactVelocity, 0.f, 0.f, KNOCK_OFF_TYPE_EXPLOSION, 0, 0, nullptr, true, false };
                driver->GetIntelligence()->m_eventGroup.Add(&event, false);

                CWeapon::GenerateDamageEvent(
                    driver,
                    veh,
                    WEAPON_EXPLOSION,
                    (uint32)(damage * entityRelDistToRadiusEnd_Doubled * 1100.f),
                    PED_PIECE_TORSO,
                    driver->GetLocalDirection(impactVelocity)
                );
            }

            if (entity->m_nStatus == eEntityStatus::STATUS_SIMPLE)
                CCarCtrl::SwitchVehicleToRealPhysics(veh);

            veh->InflictDamage(creator, WEAPON_EXPLOSION, entityRelDistToRadiusEnd_Doubled * damage * 1100.f, {});

            if (processVehicleBombTimer) {
                if (veh->m_wBombTimer) {
                    veh->m_wBombTimer = veh->m_wBombTimer / 10 + 1;
                }
            }

            CVector colPointPos{};
            CColPoint cp{};
            float maxTouchDist{ 100'000.f };
            if (CCollision::ProcessSphereBox(
                CColSphere{ Multiply3x3(veh->GetMatrix(), -entityToPointDir), entityToPointDist },
                veh->GetColModel()->m_boundBox,
                cp,
                maxTouchDist)
            ) {
                auto colNormal = Multiply3x3(veh->GetMatrix(), -cp.m_vecNormal);
                if (auto& z = colNormal.z; z >= -0.f) { // TODO: Wat is dis?
                    if (z < 0.2f && z > 0.f)
                        z += 0.2f;
                } else {
                    z = -0.2f;
                }

                           colPointPos  = Multiply3x3(veh->GetMatrix(), cp.m_vecPoint);
                const auto colPointToExploPointDist = ((colPointPos + veh->GetPosition()) - point).Magnitude();

                // TODO: Document this a little better pls

                auto forceFactor = std::min(1.f, (radius - colPointToExploPointDist) / radius * 2.f);
                if (entity == victim)
                    forceFactor *= 0.2f;

                forceFactor *= std::min(1.f, veh->m_fMass / 3000.f);
                forceFactor *= visibleDistance;
                if (float dot = DotProduct(veh->GetSpeed(colPointPos), colNormal); dot > forceFactor * 3.f) {
                    forceFactor = std::max(0.f, forceFactor - dot);
                }

                if (!veh->physicalFlags.bDisableTurnForce)
                    veh->ApplyTurnForce(colNormal * forceFactor, colPointPos);
            }

            if (veh->IsPlane()) {
                auto normalBackwards = cp.m_vecNormal;
                auto colPos = colPointPos + veh->GetPosition();
                veh->VehicleDamage(1000.f, 0, creator, &colPos, &normalBackwards, WEAPON_EXPLOSION);
            }

            break;
        }
        case eEntityType::ENTITY_TYPE_PED: {
            const auto ped = entity->AsPed();

            const auto pedLocalDir = ped->GetLocalDirection(impactVelocity);
            if (const auto attachedTo = ped->m_pAttachedTo; attachedTo && attachedTo->IsVehicle() && attachedTo->m_nStatus == STATUS_WRECKED) {
                CPedDamageResponseCalculator pedDamageResponseCalculator{ creator, 1000.f, WEAPON_EXPLOSION, ePedPieceTypes::PED_PIECE_TORSO, false};
                
                CEventDamage eventDamage{ creator, CTimer::GetTimeInMS(), WEAPON_EXPLOSION, ePedPieceTypes::PED_PIECE_TORSO, (uint8)pedLocalDir, false, !!ped->bIsTalking };
                if (eventDamage.AffectsPed(ped)) {
                    pedDamageResponseCalculator.ComputeDamageResponse(ped, &eventDamage.m_damageResponse, true);
                } else {
                    eventDamage.m_damageResponse.m_bDamageCalculated = true;
                }

                ped->GetIntelligence()->m_eventGroup.Add(&eventDamage, false);
            } else {
                if (!attachedTo) {
                    impactVelocityFactor = std::min(impactVelocityFactor, ped->m_fMass / 4.f);
                    if (const float dot = DotProduct(ped->m_vecMoveSpeed, impactVelocity) * ped->m_fMass; dot > 2.f * impactVelocityFactor) {
                        impactVelocityFactor = std::max(0.f, impactVelocityFactor - dot);
                    }

                    impactVelocity *= impactVelocityFactor;

                    if (ped->bIsStanding && ped->m_bUsesCollision) {
                        ped->bIsStanding = false;
                        impactVelocity.z += 4.f;
                    } else {
                        impactVelocity.z += CTimer::GetTimeStepInMS() * ped->m_fMass / 125.f;
                    }

                    ped->ApplyMoveForce(impactVelocity);
                }

                CPedDamageResponseCalculator pedDamageResponseCalculator{ creator, entityRelDistToRadiusEnd_Doubled * 250.f, WEAPON_EXPLOSION, ePedPieceTypes::PED_PIECE_TORSO, false };
                
                CEventDamage eventDamage{ creator, CTimer::GetTimeInMS(), WEAPON_EXPLOSION, ePedPieceTypes::PED_PIECE_TORSO, (uint8)pedLocalDir, false, !!ped->bIsTalking };
                if (eventDamage.AffectsPed(ped)) {
                    pedDamageResponseCalculator.ComputeDamageResponse(ped, &eventDamage.m_damageResponse, true);
                }
                else {
                    eventDamage.m_damageResponse.m_bDamageCalculated = true;
                }

                ped->GetIntelligence()->m_eventGroup.Add(&eventDamage, false);

                if (creator && creator->IsPed()) {
                    CCrime::ReportCrime(creator->AsPed()->m_nPedType == PED_TYPE_COP ? CRIME_DAMAGE_COP_CAR : CRIME_DAMAGE_CAR, ped, creator->AsPed());
                }
            }
            break;
        }
        case eEntityType::ENTITY_TYPE_OBJECT: {
            if (!entity->physicalFlags.bDisableZ && !entity->physicalFlags.bDisableCollisionForce) {
                if (impactVelocity.z < 0.1f)
                    impactVelocity.z = 0.2f;

                if (const auto dot = DotProduct(entity->m_vecMoveSpeed, impactVelocity) * entity->m_fMass; dot > 4.f * impactVelocityFactor) {
                    impactVelocityFactor = std::max(0.f, impactVelocityFactor - dot);
                }
                impactVelocity *= impactVelocityFactor;
                entity->ApplyMoveForce(impactVelocity);

                impactVelocity *= std::min(1.f, entity->m_fTurnMass / entity->m_fMass);
                entity->ApplyTurnForce(impactVelocity, {0.f, 0.f, entity->GetColModel()->m_boundSphere.m_fRadius / 2.f});
            }
                
            entity->AsObject()->ObjectDamage(entityRelDistToRadiusEnd_Doubled * 300.f, nullptr, nullptr, creator, WEAPON_EXPLOSION);
            break;
        }
        }
    }
}

// 0x5684A0
// TODO: Fix crash caused by `g_ikChainMan.Update`
void CWorld::Process() {
    return plugin::Call<0x5684A0>();

    const auto IterateMovingList = [&](auto&& fn) {
        for (CPtrNodeDoubleLink* node = ms_listMovingEntityPtrs.GetNode(), *next{}; node; node = next) {
            next = node->m_next;
            fn(static_cast<CEntity*>(node->m_item));
        }
    };

    IterateMovingList([&](CEntity* entity) {
        if (entity->IsPed()) {
            GetEventGlobalGroup()->AddEventsToPed(entity->AsPed());
        }
    });

    for (auto& group : CPedGroups::ms_groups) {
        GetEventGlobalGroup()->AddEventsToGroup(&group);
    }

    CInformFriendsEventQueue::Process();
    CInformGroupEventQueue::Process();

    GetEventGlobalGroup()->Flush(false);

    if ((CTimer::m_FrameCounter % 64) == 0)
        CReferences::PruneAllReferencesInWorld();

    if (bProcessCutsceneOnly && CCutsceneMgr::ms_running) {
        for (auto* obj : CCutsceneMgr::ms_pCutsceneObjects) {
            if (obj && !obj->m_pCollisionList.IsEmpty()) {
                obj->UpdateAnim();
                obj->ProcessControl();
                obj->ProcessCollision();
                obj->UpdateRW();
                obj->UpdateRwFrame();
            }
        }
        return;
    }

    IterateMovingList([&](CEntity* entity) {
        if (!entity->m_bRemoveFromWorld) {
            entity->UpdateAnim();
        }
    });
    
    {
        const auto ProcessMovingEntity = [](CEntity* entity) {
            if (entity->m_bRemoveFromWorld) {
                if (entity->IsPed()) { // Inverted loop compared to original
                    if (FindPlayerPed() == entity) {
                        entity->Remove();
                        if (entity->IsPhysical())
                            entity->AsPhysical()->RemoveFromMovingList();
                    } else {
                        CPopulation::RemovePed(entity->AsPed());
                    }
                } else {
                    entity->Remove();
                    if (entity->IsPhysical())
                        entity->AsPhysical()->RemoveFromMovingList();
                    delete entity;
                }
            } else {
                entity->ProcessControl();
                if (entity->IsStatic())
                    entity->AsPhysical()->RemoveFromMovingList();
            }
        };

        IterateMovingList(ProcessMovingEntity);

        bForceProcessControl = true;
        IterateMovingList([&](CEntity* entity) {
            if (!entity->m_bWasPostponed)
                ProcessMovingEntity(entity);
        });
        bForceProcessControl = false;
    }

    for (CPtrNodeDoubleLink* node = ms_listObjectsWithControlCode.GetNode(), *next{}; node; node = next) {
        next = node->m_next;
        static_cast<CObject*>(node->m_item)->ProcessControlLogic();
    }

    if (CReplay::Mode == 1) {
        IterateMovingList([&](CEntity* entity) {
            entity->m_bIsInSafePosition = true;
            entity->UpdateRW();
            entity->UpdateRwFrame();
        });
    } else {
        // Process collision
        {
            const auto ProcessMovingEntityCollision = [](CEntity* entity) {
                if (!entity->m_bIsInSafePosition) {
                    entity->ProcessCollision();
                    entity->UpdateRW();
                    entity->UpdateRwFrame();
                }
            };

            const auto ProcessMovingEntityCollisions = [&] {
                IterateMovingList(ProcessMovingEntityCollision);
            };

            bNoMoreCollisionTorque = false;
            ProcessMovingEntityCollisions();
            bNoMoreCollisionTorque = true;

            // Process entities a few more times..
            for (auto i = 0; i < 4; i++) {
                ProcessMovingEntityCollisions();
            }

            // Mark entities as `stuck` if they're still in unsafe positions
            IterateMovingList([&](CEntity* entity) {
                if (!entity->m_bIsInSafePosition) {
                    entity->m_bIsStuck = true;

                    entity->ProcessCollision();
                    entity->UpdateRW();
                    entity->UpdateRwFrame();

                    if (!entity->m_bIsInSafePosition)
                        entity->m_bIsStuck = true;
                }
            });
        }

        // Process "Shift" (Not sure what that is)
        {
            bSecondShift = false;

            IterateMovingList([&](CEntity* entity) {
                if (!entity->m_bIsInSafePosition) {
                    entity->ProcessShift();
                    entity->UpdateRW();
                    entity->UpdateRwFrame();

                    if (!entity->m_bIsInSafePosition)
                        entity->m_bIsStuck = true;
                }
            });

            bSecondShift = true;

            IterateMovingList([&](CEntity* entity) {
                if (!entity->m_bIsInSafePosition) {
                    entity->ProcessShift();
                    entity->UpdateRW();
                    entity->UpdateRwFrame();

                    if (!entity->m_bIsInSafePosition) {
                        entity->m_bIsStuck = true;

                        if (entity->m_nStatus == STATUS_PLAYER) { // Try to unstuck player
                            const auto physical = entity->AsPhysical();
                            physical->m_vecMoveSpeed *= (float)std::pow(SQRT_2 / 2.f, CTimer::GetTimeStepInMS());
                            physical->ApplyMoveSpeed();
                            physical->ApplyTurnSpeed();
                        }
                    }
                }
            });
        }
    }

    g_LoadMonitor.EndTimer(true);
    CVehicleRecording::SaveOrRetrieveDataForThisFrame();
    g_ikChainMan.Update(CTimer::GetTimeStepInSeconds());
    ProcessAttachedEntities();

    IterateMovingList([&](CEntity* entity) {
        if (entity->IsPed()) {
            const auto ped = entity->AsPed();
            ped->GetIntelligence()->ProcessAfterProcCol();
            if (const auto attachedTo = ped->m_pAttachedTo) {
                ped->m_pEntityIgnoredCollision = attachedTo;
                ped->PositionAttachedPed();
                ped->UpdateRW();
                ped->UpdateRwFrame();
            }
        }
    });

    CMessages::Process();

    for (auto i = 0; i < std::size(Players); i++) {
        if (Players[i].m_pPed)
            Players[i].Process(i);
    }

    CPedScriptedTaskRecord::Process();

    CPedGroups::Process();

    switch (CTimer::GetFrameCounter() % 8) {
    case 1:
        RemoveFallenPeds();
        break;
    case 5:
        RemoveFallenCars();
        break;
    }
}

// 0x568AD0
bool CWorld::GetIsLineOfSightSectorClear(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doIgnoreCameraCheck){
    const auto ProcessSectorList = [&](CPtrList& list, bool doIgnoreCamCheckForThisSector = false) {
        return GetIsLineOfSightSectorListClear(list, colLine, doSeeThroughCheck, doIgnoreCamCheckForThisSector);
    };
    return   (!buildings || ProcessSectorList(sector.m_buildings))
          && (!vehicles  || ProcessSectorList(repeatSector.m_lists[REPEATSECTOR_VEHICLES]))
          && (!peds      || ProcessSectorList(repeatSector.m_lists[REPEATSECTOR_PEDS]))
          && (!objects   || ProcessSectorList(repeatSector.m_lists[REPEATSECTOR_OBJECTS], doIgnoreCameraCheck))
          && (!dummies   || ProcessSectorList(sector.m_dummies));
}

// 0x568B80
void CWorld::FindObjectsKindaColliding(const CVector& point, float radius, bool b2D, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    const int32 startSectorX = GetSectorX(point.x - radius);
    const int32 startSectorY = GetSectorY(point.y - radius);
    const int32 endSectorX = GetSectorX(point.x + radius);
    const int32 endSectorY = GetSectorY(point.y + radius);

    IncrementCurrentScanCode();

    CEntity* hitEntity{};
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list) {
                FindObjectsKindaCollidingSectorList(list, point, radius, b2D, outCount, maxCount, outEntities);
            };

            auto sector = GetSector(sectorX, sectorY);
            auto repeatSector = GetRepeatSector(sectorX, sectorY);

            if (buildings)
                ProcessSector(sector->m_buildings);
            if (vehicles)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES]);
            if (peds)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS]);
            if (objects)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            if (dummies)
                ProcessSector(sector->m_dummies);
        }
    }
}

// 0x568DD0
void CWorld::FindObjectsIntersectingCube(const CVector& cornerA, const CVector& cornerB, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    const int32 startSectorX = GetSectorX(cornerA.x);
    const int32 startSectorY = GetSectorY(cornerA.y);
    const int32 endSectorX = GetSectorX(cornerB.x);
    const int32 endSectorY = GetSectorY(cornerB.y);

    IncrementCurrentScanCode();

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list) {
                FindObjectsIntersectingCubeSectorList(list, cornerA, cornerB, outCount, maxCount, outEntities);
            };

            auto sector = GetSector(sectorX, sectorY);
            auto repeatSector = GetRepeatSector(sectorX, sectorY);

            if (buildings)
                ProcessSector(sector->m_buildings);
            if (vehicles)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES]);
            if (peds)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS]);
            if (objects)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            if (dummies)
                ProcessSector(sector->m_dummies);
        }
    }
}

// 0x568FF0
void CWorld::FindObjectsIntersectingAngledCollisionBox(CBox const& box, const CMatrix& transform, const CVector& point, float x1, float y1, float x2, float y2, int16* outCount, int16 maxCount, CEntity** outEntities, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    const int32 startSectorX = GetSectorX(x1);
    const int32 startSectorY = GetSectorY(y1);
    const int32 endSectorX = GetSectorX(x2);
    const int32 endSectorY = GetSectorY(y2);

    IncrementCurrentScanCode();

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list) {
                FindObjectsIntersectingAngledCollisionBoxSectorList(list, box, transform, point, outCount, maxCount, outEntities);
            };

            auto sector = GetSector(sectorX, sectorY);
            auto repeatSector = GetRepeatSector(sectorX, sectorY);

            if (buildings)
                ProcessSector(sector->m_buildings);
            if (vehicles)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES]);
            if (peds)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS]);
            if (objects)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            if (dummies)
                ProcessSector(sector->m_dummies);
        }
    }
}

// 0x569240
void CWorld::FindMissionEntitiesIntersectingCube(const CVector& cornerA, const CVector& cornerB, int16* outCount, int16 maxCount, CEntity** outEntities, bool vehicles, bool peds, bool objects) {
    const int32 startSectorX = GetSectorX(cornerA.x);
    const int32 startSectorY = GetSectorY(cornerA.y);
    const int32 endSectorX = GetSectorX(cornerB.x);
    const int32 endSectorY = GetSectorY(cornerB.y);

    IncrementCurrentScanCode();

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list, bool isVehicleList, bool isPedList, bool isObjList) {
                FindMissionEntitiesIntersectingCubeSectorList(list, cornerA, cornerB, outCount, maxCount, outEntities, isVehicleList, isPedList, isObjList);
            };

            auto repeatSector = GetRepeatSector(sectorX, sectorY);
            if (vehicles)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES], true, false, false);
            if (peds)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS], false, true, false);
            if (objects)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS], false, false, true);
        }
    }
}

// 0x5693F0
CEntity* CWorld::FindNearestObjectOfType(int32 modelId, const CVector& point, float radius, bool b2D, bool buildings, bool vehicles, bool peds, bool objects, bool dummies) {
    const int32 startSectorX = GetSectorX(point.x - radius);
    const int32 startSectorY = GetSectorY(point.y - radius);
    const int32 endSectorX = GetSectorX(point.x + radius);
    const int32 endSectorY = GetSectorY(point.y + radius);

    IncrementCurrentScanCode();

    CEntity* hitEntity{};
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list) {
                // Clever trick: re-use `radius` as `outDistance`, so if an entity is hit `radius` is automatically decreased
                FindNearestObjectOfTypeSectorList(modelId, list, point, radius, b2D, &hitEntity, &radius);
            };

            auto sector = GetSector(sectorX, sectorY);
            auto repeatSector = GetRepeatSector(sectorX, sectorY);

            if (buildings)
                ProcessSector(sector->m_buildings);
            if (vehicles)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES]);
            if (peds)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS]);
            if (objects)
                ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            if (dummies)
                ProcessSector(sector->m_dummies);
        }
    }
    return hitEntity;
}

// 0x569660
float CWorld::FindGroundZForCoord(float x, float y) {
    return plugin::CallAndReturn<float, 0x569660, float, float>(x, y);
}

// 0x5696C0
float CWorld::FindGroundZFor3DCoord(float x, float y, float z, bool* outResult, CEntity** outEntity) {
    CEntity* localOutEntity{};
    CColPoint colPoint;
    if (ProcessVerticalLine({ x, y, z }, -1000.0f, colPoint, localOutEntity, true, false, false, false, true, false, nullptr)) {
        if (outResult)
            *outResult = true;
        if (outEntity)
            *outEntity = localOutEntity;
        return colPoint.m_vecPoint.z;
    }
    else {
        if (outResult)
            *outResult = false;
        if (outEntity)
            *outEntity = nullptr;
        return 0.0f;
    }
}

// 0x569750
float CWorld::FindRoofZFor3DCoord(float x, float y, float z, bool* outResult) {
    CEntity* outEntity{};
    CColPoint colPoint;
    if (ProcessVerticalLine({ x, y, z }, 1000.0f, colPoint, outEntity, true, false, false, false, true, false, nullptr)) {
        if (outResult)
            *outResult = true;
        return colPoint.m_vecPoint.z;
    } else {
        if (outResult)
            *outResult = false;
        else
            printf("THERE IS NO MAP BELOW THE FOLLOWING COORS:%f %f %f. (FindGroundZFor3DCoord)\n", x, y, z); // R* triggered
        return 20.0f;
    }
}

// 0x5697F0
float CWorld::FindLowestZForCoord(float x, float y) {
    CEntity* outEntity{};
    CColPoint colPoint;
    if (ProcessVerticalLine({ x, y, -1000.0f }, 1000.0f, colPoint, outEntity, true, false, false, false, true, false, nullptr))
        return colPoint.m_vecPoint.z;

    return 20.0f;
}

// 0x569850
void CWorld::RepositionOneObject(CEntity* object) {
    using namespace ModelIndices;

    // I mean, you can imagine this isn't original code, but we want to make it look readable :)
    // I mean, they probably used a macro or something... so, who knows :D
    // Maybe.. maybe they were time travellers and used c++20 ranges, and had a good compiler to mask it away
    // you never know..

    const auto IsObjectModelAnyOf = [object](std::initializer_list<ModelIndex> models) {
        return std::ranges::find(models, (ModelIndex)object->m_nModelIndex) != models.end();
    };

    const auto MI = CModelInfo::GetModelInfo(object->m_nModelIndex);
    const auto CM = MI->GetColModel();

    // Recalculate position to be on ground level where is `point`
    const auto RecalcZPosAtPoint = [&](CVector2D point) {
        auto& pos = object->GetMatrix().GetPosition();
        pos.z = FindGroundZFor3DCoord(point.x, point.y, pos.z + std::max(2.f, CM->m_boundBox.GetHeight()), nullptr, nullptr) - CM->m_boundBox.m_vecMin.z;
        object->UpdateRW();
        object->UpdateRwFrame();
    };

    if (MI->SwaysInWind() || IsObjectModelAnyOf({
        MI_PARKINGMETER,
        MI_PHONEBOOTH1,
        MI_WASTEBIN,
        MI_BIN,
        MI_POSTBOX1,
        MI_NEWSSTAND,
        MI_TRAFFICCONE,
        MI_DUMP1,
        MI_ROADWORKBARRIER1,
        MI_ROADBLOCKFUCKEDCAR1,
        MI_ROADBLOCKFUCKEDCAR2,
        MI_BUSSIGN1,
        MI_NOPARKINGSIGN1,
        MI_PHONESIGN,
        MI_FIRE_HYDRANT,
        MI_BOLLARDLIGHT,
        MI_PARKTABLE,
        MI_PARKINGMETER2,
        MI_TELPOLE02,
        MI_PARKBENCH,
        MI_BARRIER1
    })) { 
        RecalcZPosAtPoint(object->GetPosition());
    } else if (IsObjectModelAnyOf({
        MI_SINGLESTREETLIGHTS1,
        MI_SINGLESTREETLIGHTS2,
        MI_SINGLESTREETLIGHTS3,
        MI_TRAFFICLIGHTS_MIAMI,
        MI_TRAFFICLIGHTS_VEGAS,
        MI_TRAFFICLIGHTS_TWOVERTICAL,
        MI_TRAFFICLIGHTS_3,
        MI_TRAFFICLIGHTS_4,
        MI_TRAFFICLIGHTS_5,
        MI_MLAMPPOST,
        MI_STREETLAMP1,
        MI_STREETLAMP2
    })) {
        if (const auto CD = CM->m_pColData) {
            if (CD->m_nNumBoxes == 1) {
                RecalcZPosAtPoint(Multiply3x3(object->GetMatrix(), CD->m_pBoxes[0].GetCenter()));
            } else if (CD->m_nNumSpheres) {
                auto point{ object->GetPosition() };
                point.z = 1000.f;

                for (auto i = 0; i < CD->m_nNumSpheres; i++) {
                    const auto& sphere = CD->m_pSpheres[i];
                    if (sphere.m_vecCenter.z < point.z)
                        point = sphere.m_vecCenter;
                }

                if (point.z >= 1000.f)
                    RecalcZPosAtPoint(object->GetPosition());
                else
                    RecalcZPosAtPoint(Multiply3x3(object->GetMatrix(), point));
            }
        } else {
            RecalcZPosAtPoint(object->GetPosition());
        }
    }

    // This code piece seems quite incomplete, they might've just left it in accidentally?
    if (object->m_nModelIndex == MI_BUOY) {
        // Orginally `ProcessVerticalLine` is called, but the result is unused.

        auto& pos = object->GetPosition();
        auto height = CM->GetBoundingBox().GetHeight();
        pos.z = 6.f - height / 2.f + height / 5.f;
    }
}

// 0x569E20
CEntity* CWorld::TestSphereAgainstWorld(CVector sphereCenter, float sphereRadius, CEntity* ignoreEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doCameraIgnoreCheck) {
    const int32 startSectorX = GetSectorX(sphereCenter.x - sphereRadius);
    const int32 startSectorY = GetSectorY(sphereCenter.y - sphereRadius);
    const int32 endSectorX = GetSectorX(sphereCenter.x + sphereRadius);
    const int32 endSectorY = GetSectorY(sphereCenter.y + sphereRadius);

    IncrementCurrentScanCode();

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](CPtrList& list, bool doIgnoreCameraCheckForThisSector) {
                return TestSphereAgainstSectorList(list, sphereCenter, sphereRadius, ignoreEntity, doIgnoreCameraCheckForThisSector);
            };

            auto sector = GetSector(sectorX, sectorY);
            auto repeatSector = GetRepeatSector(sectorX, sectorY);

            CEntity* hitEntity{};

            if (buildings && (hitEntity = ProcessSector(sector->m_buildings, false)))
                return hitEntity;

            if (vehicles && (hitEntity = ProcessSector(repeatSector->m_lists[REPEATSECTOR_VEHICLES], false)))
                return hitEntity;

            if (peds && (hitEntity = ProcessSector(repeatSector->m_lists[REPEATSECTOR_PEDS], false)))
                return hitEntity;

            if (objects && (hitEntity = ProcessSector(repeatSector->m_lists[REPEATSECTOR_OBJECTS], doCameraIgnoreCheck)))
                return hitEntity;

            if (dummies && (hitEntity = ProcessSector(sector->m_dummies, false)))
                return hitEntity;
        }
    }
    return nullptr;
}

// 0x56A0D0
void CWorld::ClearExcitingStuffFromArea(const CVector& point, float radius, uint8 bRemoveProjectilesAndShadows) {
    const auto vehPool = CPools::ms_pVehiclePool;
    const auto playerPed = FindPlayerPed();
    const auto playerGroup = CPedGroups::GetPedsGroup(playerPed);
    for (auto i = 0; i < vehPool->GetSize(); i++) {
        if (const auto veh = vehPool->GetAt(i)) {
            if (playerGroup && veh->IsAnyOfPassengersFollowerOfGroup(*playerGroup))
                continue;

            if (playerPed->m_pContactEntity == veh && !veh->IsBoat())
                continue;

            if (radius * radius <= DistanceBetweenPointsSquared2D(point, veh->GetPosition()))
                continue;

            if (veh->vehicleFlags.bIsLocked || !veh->CanBeDeleted())
                continue;

            if (CGarages::IsPointWithinHideOutGarage(veh->GetPosition()))
                continue;

            // TODO: Below code is inlined. Same code can be found in `ClearCarsFromArea`

            if (auto& driver = veh->m_pDriver) { 
                CPopulation::RemovePed(driver);
                driver->CleanUpOldReference(reinterpret_cast<CEntity**>(&driver));
                driver = nullptr;
            }

            for (auto i = 0; i < veh->m_nMaxPassengers; i++) {
                if (auto psngr = veh->m_apPassengers[i]) {
                    veh->RemovePassenger(psngr);
                    CPopulation::RemovePed(psngr);
                }
            }

            if (CCarCtrl::IsThisVehicleInteresting(veh))
                CGarages::StoreCarInNearestImpoundingGarage(veh);
            
            CCarCtrl::RemoveFromInterestingVehicleList(veh);

            Remove(veh);
            delete veh;
        }
    }
}

// 0x56A490
bool CWorld::GetIsLineOfSightClear(const CVector& origin, const CVector& target, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck) {

    const int32 originSectorX = GetSectorX(origin.x);
    const int32 originSectorY = GetSectorY(origin.y);
    const int32 targetSectorX = GetSectorX(target.x);
    const int32 targetSectorY = GetSectorY(target.y);

    IncrementCurrentScanCode();

    const auto ProcessSector = [&](int32 x, int32 y) {
        return GetIsLineOfSightSectorClear(
            *GetSector(x, y),
            *GetRepeatSector(x, y),
            { origin, target },
            buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doCameraIgnoreCheck
        );
    };

    if (originSectorX == targetSectorX && originSectorY == targetSectorY) { // Both in the same sector
        return ProcessSector(originSectorX, originSectorY); 
    }
    else if (originSectorX == targetSectorX) { // Same X for both, iterate on Y
        if (originSectorY >= targetSectorY) { // origin => target on Y axis
            for (auto y = originSectorY; y >= targetSectorY; y--) {
                if (!ProcessSector(originSectorX, y))
                    return false;
            }
        } else { // target => origin on Y axis
            for (auto y = targetSectorY; y >= originSectorY; y--) {
                if (!ProcessSector(originSectorX, y))
                    return false;
            }
        }
    }
    else if (originSectorY == targetSectorY) { // Same Y for both, iterate on X
        if (originSectorX >= targetSectorX) { // origin => target on X axis
            for (auto x = originSectorX; x >= targetSectorX; x--) {
                if (!ProcessSector(x, originSectorY))
                    return false;
            }
        }
        else { // target => origin on X axis
            for (auto x = targetSectorX; x >= originSectorX; x--) {
                if (!ProcessSector(x, originSectorY))
                    return false;
            }
        }
    }
    else {  // Different x and y sectors
        float displacement = (target.y - origin.y) / (target.x - origin.x);

        // TODO: Make this more readable

        int32 startY, endY, x, y;
        if (origin.x < target.x) { // Step from left to right
            startY = originSectorY;
            endY = GetSectorY((GetSectorPosX(originSectorX + 1) - origin.x) * displacement + origin.y);

            if (originSectorY < endY) {
                for (y = originSectorY; y <= endY; y++) {
                    if (!ProcessSector(originSectorX, y))
                        return false;
                }
            }
            else {
                for (y = originSectorY; y >= endY; y--) {
                    if (!ProcessSector(originSectorX, y))
                        return false;
                }
            }

            for (x = originSectorX + 1; x < targetSectorX; x++) {
                startY = endY;
                endY = GetSectorY((GetSectorPosX(x + 1) - origin.x) * displacement + origin.y);
                if (startY < endY) {
                    for (y = startY; y <= endY; y++) {
                        if (!ProcessSector(x, y))
                            return false;
                    }
                }
                else {
                    for (y = startY; y >= endY; y--) {
                        if (!ProcessSector(x, y))
                            return false;
                    }
                }
            }

            startY = endY;
            endY = targetSectorY;

            if (startY < endY) {
                for (y = startY; y <= endY; y++) {
                    if (!ProcessSector(targetSectorX, y))
                        return false;
                }
            }
            else {
                for (y = startY; y >= endY; y--) {
                    if (!ProcessSector(targetSectorX, y))
                        return false;
                }
            }
        } else { // Step from right to left
            startY = originSectorY;
            endY = GetSectorY((GetSectorPosX(originSectorX) - origin.x) * displacement + origin.y);
            if (startY < endY) {
                for (y = startY; y <= endY; y++) {
                    if (!ProcessSector(originSectorX, y))
                        return false;
                }
            }
            else {
                for (y = startY; y >= endY; y--) {
                    if (!ProcessSector(originSectorX, y))
                        return false;
                }
            }

            for (x = originSectorX - 1; x > targetSectorX; x--) {
                startY = endY;
                endY = GetSectorY((GetSectorPosX(x) - origin.x) * displacement + origin.y);
                if (startY < endY) {
                    for (y = startY; y <= endY; y++) {
                        if (!ProcessSector(x, y))
                            return false;
                    }
                }
                else {
                    for (y = startY; y >= endY; y--) {
                        if (!ProcessSector(x, y))
                            return false;
                    }
                }
            }

            startY = endY;
            endY = targetSectorY;
            if (startY < endY) {
                for (y = startY; y <= endY; y++) {
                    if (!ProcessSector(targetSectorX, y))
                        return false;
                }
            }
            else {
                for (y = startY; y >= endY; y--) {
                    if (!ProcessSector(targetSectorX, y))
                        return false;
                }
            }
        }
    }
    return true;
}

// 0x56B5E0
bool CWorld::ProcessLineOfSightSector(CSector& sector, CRepeatSector& repeatSector, const CColLine& colLine, CColPoint& outColPoint, float& maxTouchDistance, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck) {
    float localMaxTouchDist = maxTouchDistance;

    const auto bIncludeDeadPeds_Original = bIncludeDeadPeds;
    const auto bIncludeBikers_Original = bIncludeBikers;
    const auto fWeaponSpreadRate_Original = fWeaponSpreadRate;

    bIncludeDeadPeds = false;
    bIncludeBikers = false;
    fWeaponSpreadRate = 0.f;

    const auto ProcessSector = [&](CPtrList& list, bool doIgnoreCameraCheckForThisSector = false) {
        CWorld::ProcessLineOfSightSectorList(list, colLine, outColPoint, localMaxTouchDist, outEntity, doSeeThroughCheck, doIgnoreCameraCheckForThisSector, doShootThroughCheck);
    };

    if (buildings)
        ProcessSector(sector.m_buildings);

    if (fWeaponSpreadRate_Original > 0.f)
        fWeaponSpreadRate = fWeaponSpreadRate_Original;

    if (vehicles)
        ProcessSector(repeatSector.m_lists[REPEATSECTOR_VEHICLES]);

    if (peds) {
        if (bIncludeDeadPeds_Original)
            bIncludeDeadPeds = bIncludeDeadPeds_Original;

        if (bIncludeBikers_Original)
            bIncludeBikers = bIncludeBikers_Original;

        ProcessSector(repeatSector.m_lists[REPEATSECTOR_PEDS]);

        bIncludeDeadPeds = false;
        bIncludeBikers = false;

    }

    if (objects)
        ProcessSector(repeatSector.m_lists[REPEATSECTOR_OBJECTS]);

    if (dummies)
        ProcessSector(sector.m_dummies);

    bIncludeDeadPeds = bIncludeDeadPeds_Original;
    bIncludeBikers = bIncludeBikers_Original;

    if (localMaxTouchDist < maxTouchDistance) {
        maxTouchDistance = localMaxTouchDist;
        return true;
    }
    return false;
}

// 0x56B790
void CWorld::TriggerExplosion(const CVector& point, float radius, float visibleDistance, CEntity* victim, CEntity* creator, bool processVehicleBombTimer, float damage) {
    const int32 startSectorX = GetSectorX(point.x - radius);
    const int32 startSectorY = GetSectorY(point.y - radius);
    const int32 endSectorX = GetSectorX(point.x + radius);
    const int32 endSectorY = GetSectorY(point.y + radius);

    IncrementCurrentScanCode();

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            const auto ProcessSector = [&](auto& sector) {
                TriggerExplosionSectorList(sector, point, radius, visibleDistance, victim, creator, processVehicleBombTimer, damage);
            };

            auto sector = GetRepeatSector(sectorX, sectorY);
            ProcessSector(sector->m_lists[REPEATSECTOR_VEHICLES]);
            ProcessSector(sector->m_lists[REPEATSECTOR_PEDS]);
            ProcessSector(sector->m_lists[REPEATSECTOR_OBJECTS]);
        }
    }
}

// 0x56B910
void CWorld::SetWorldOnFire(float x, float y, float z, float radius, CEntity* fireCreator) {
    if (TestSphereAgainstWorld({ x, y, z }, radius, nullptr, true, false, false, true, false, false)) {
        if (!gFireManager.GetNumFiresInRange({ x, y, z }, 2.f)) {
            gFireManager.StartFire({ x, y, z }, 0.8f, true, nullptr, 0, 7000, true);
        }
    }
}

// 0x56B9C0
void CWorld::RepositionCertainDynamicObjects() {
    for (int32 i = CPools::ms_pDummyPool->GetSize(); i; i--) {
        if (CDummy* dummy = CPools::ms_pDummyPool->GetAt(i - 1)) {
            RepositionOneObject(dummy);
        }
    }
}

// 0x56BA00
bool CWorld::ProcessLineOfSight(const CVector& origin, const CVector& target, CColPoint& outColPoint, CEntity*& outEntity, bool buildings, bool vehicles, bool peds, bool objects, bool dummies, bool doSeeThroughCheck, bool doCameraIgnoreCheck, bool doShootThroughCheck) {
    return plugin::CallAndReturn<bool, 0x56BA00, const CVector&, const CVector&, CColPoint&, CEntity*&, bool, bool, bool, bool, bool, bool, bool, bool>(origin, target, outColPoint, outEntity, buildings, vehicles, peds, objects, dummies, doSeeThroughCheck, doCameraIgnoreCheck, doShootThroughCheck);
}

void CWorld::IncrementCurrentScanCode() {
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

// 0x407250
int16 GetCurrentScanCode() {
    return plugin::CallAndReturn<int16, 0x407250>();
}

// 0x407260
CSector* GetSector(int32 x, int32 y) {
    return plugin::CallAndReturn<CSector*, 0x407260, int32, int32>(x, y);
}

// 0x4072A0
CRepeatSector* GetRepeatSector(int32 x, int32 y) {
    return plugin::CallAndReturn<CRepeatSector*, 0x4072A0, int32, int32>(x, y);
}

// 0x4072C0
CPtrListSingleLink& CWorld::GetLodPtrList(int32 x, int32 y) {
    x = clamp<int32>(x, 0, MAX_LOD_PTR_LISTS_X - 1);
    y = clamp<int32>(y, 0, MAX_LOD_PTR_LISTS_Y - 1);
    return ms_aLodPtrLists[y][x];
    // return plugin::CallAndReturn<CPtrListSingleLink*, 0x4072C0, int32, int32>(x, y);
}

// 0x4072E0
void SetNextScanCode() {
    plugin::Call<0x4072E0>();
}

float ScaleLighting(uint8 lighting, float fScale)
{
    return plugin::CallAndReturn<float, 0x59F0C0, uint8, float> (lighting, fScale);
}
