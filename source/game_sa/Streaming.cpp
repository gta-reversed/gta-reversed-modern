#include "StdInc.h"

#include "Radar.h"
#include <ranges>

uint32& CStreaming::ms_memoryAvailable = *reinterpret_cast<uint32*>(0x8A5A80);
int32& CStreaming::desiredNumVehiclesLoaded = *reinterpret_cast<int32*>(0x8A5A84);
bool& CStreaming::ms_bLoadVehiclesInLoadScene = *reinterpret_cast<bool*>(0x8A5A88);

// Default models for each level (see eLevelNames)
int32(&CStreaming::ms_aDefaultCopCarModel)[4] = *(int32(*)[4])0x8A5A8C;
int32(&CStreaming::ms_aDefaultCopModel)[4] = *(int32(*)[4])0x8A5AA0;
int32(&CStreaming::ms_aDefaultAmbulanceModel)[4] = *(int32(*)[4])0x8A5AB4;
int32(&CStreaming::ms_aDefaultMedicModel)[4] = *(int32(*)[4])0x8A5AC4;
int32(&CStreaming::ms_aDefaultFireEngineModel)[4] = *(int32(*)[4])0x8A5AD4;
int32(&CStreaming::ms_aDefaultFiremanModel)[4] = *(int32(*)[4])0x8A5AE4;

// Default models for current level
int32& CStreaming::ms_DefaultCopBikeModel = *reinterpret_cast<int32*>(0x8A5A9C);
int32& CStreaming::ms_DefaultCopBikerModel = *reinterpret_cast<int32*>(0x8A5AB0);

uint32& CStreaming::ms_nTimePassedSinceLastCopBikeStreamedIn = *reinterpret_cast<uint32*>(0x9654C0);
CDirectory*& CStreaming::ms_pExtraObjectsDir = *reinterpret_cast<CDirectory**>(0x8E48D0);
tStreamingFileDesc (&CStreaming::ms_files)[TOTAL_IMG_ARCHIVES] = *(tStreamingFileDesc(*)[TOTAL_IMG_ARCHIVES])0x8E48D8;
bool& CStreaming::ms_bLoadingBigModel = *reinterpret_cast<bool*>(0x8E4A58);
// There are only two channels within CStreaming::ms_channel
tStreamingChannel(&CStreaming::ms_channel)[2] = *(tStreamingChannel(*)[2])0x8E4A60;
signed int& CStreaming::ms_channelError = *reinterpret_cast<signed int*>(0x8E4B90);
bool& CStreaming::m_bHarvesterModelsRequested = *reinterpret_cast<bool*>(0x8E4B9C);
bool& CStreaming::m_bStreamHarvesterModelsThisFrame = *reinterpret_cast<bool*>(0x8E4B9D);
uint32& CStreaming::ms_numPriorityRequests = *reinterpret_cast<uint32*>(0x8E4BA0);
int32& CStreaming::ms_lastCullZone = *reinterpret_cast<int32*>(0x8E4BA4);
uint16& CStreaming::ms_loadedGangCars = *reinterpret_cast<uint16*>(0x8E4BA8);

// Bitfield of gangs loaded. Each gang is a bit. (0th bit being BALLAS, following the ordering in POPCYCLE_GROUP_BALLAS) 
uint16& CStreaming::ms_loadedGangs = *reinterpret_cast<uint16*>(0x8E4BAC);

int32& CStreaming::ms_numPedsLoaded = *reinterpret_cast<int32*>(0x8E4BB0);
int32(&CStreaming::ms_pedsLoaded)[8] = *(int32(*)[8])0x8E4C00;
int32* CStreaming::ms_NextPedToLoadFromGroup = reinterpret_cast<int32*>(0x8E4BB8);
int32& CStreaming::ms_currentZoneType = *reinterpret_cast<int32*>(0x8E4C20);
CLoadedCarGroup& CStreaming::ms_vehiclesLoaded = *reinterpret_cast<CLoadedCarGroup*>(0x8E4C24);
CStreamingInfo*& CStreaming::ms_pEndRequestedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C54);
CStreamingInfo*& CStreaming::ms_pStartRequestedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C58);
CStreamingInfo*& CStreaming::ms_pEndLoadedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C5C);
CStreamingInfo*& CStreaming::ms_startLoadedList = *reinterpret_cast<CStreamingInfo**>(0x8E4C60);
int32& CStreaming::ms_lastImageRead = *reinterpret_cast<int32*>(0x8E4C64);
int32(&CStreaming::ms_imageOffsets)[6] = *(int32(*)[6])0x8E4C8C;
bool& CStreaming::ms_bEnableRequestListPurge = *reinterpret_cast<bool*>(0x8E4CA4);
uint32& CStreaming::ms_streamingBufferSize = *reinterpret_cast<uint32*>(0x8E4CA8);
uint8** CStreaming::ms_pStreamingBuffer = reinterpret_cast<uint8**>(0x8E4CAC);
uint32& CStreaming::ms_memoryUsed = *reinterpret_cast<uint32*>(0x8E4CB4);
int32& CStreaming::ms_numModelsRequested = *reinterpret_cast<int32*>(0x8E4CB8);
CStreamingInfo(&CStreaming::ms_aInfoForModel)[26316] = *(CStreamingInfo(*)[26316])0x8E4CC0;
bool& CStreaming::ms_disableStreaming = *reinterpret_cast<bool*>(0x9654B0);
int32& CStreaming::ms_bIsInitialised = *reinterpret_cast<int32*>(0x9654B8);
bool& CStreaming::m_bBoatsNeeded = *reinterpret_cast<bool*>(0x9654BC);
bool& CStreaming::ms_bLoadingScene = *reinterpret_cast<bool*>(0x9654BD);
bool& CStreaming::m_bCopBikeLoaded = *reinterpret_cast<bool*>(0x9654BE);
bool& CStreaming::m_bDisableCopBikes = *reinterpret_cast<bool*>(0x9654BF);
CLinkList<CEntity*>& CStreaming::ms_rwObjectInstances = *reinterpret_cast<CLinkList<CEntity*>*>(0x9654F0);
CLink<CEntity*>*& CStreaming::ms_renderEntityLink = *reinterpret_cast<CLink<CEntity*>**>(0x8E48A0);
RwStream& gRwStream = *reinterpret_cast<RwStream*>(0x8E48AC);
bool& CStreaming::m_bLoadingAllRequestedModels = *reinterpret_cast<bool*>(0x965538);
bool& CStreaming::m_bModelStreamNotLoaded = *reinterpret_cast<bool*>(0x9654C4);
static int32& CurrentGangMemberToLoad = *(int32*)0x9654D4;

void CStreaming::InjectHooks()
{
    using namespace ReversibleHooks;
    Install("CStreaming", "AddEntity",0x409650, &CStreaming::AddEntity);
    Install("CStreaming", "AddImageToList",0x407610, &CStreaming::AddImageToList);
    Install("CStreaming", "AddLodsToRequestList",0x40C520, &CStreaming::AddLodsToRequestList);
    Install("CStreaming", "AddModelsToRequestList",0x40D3F0, &CStreaming::AddModelsToRequestList);
    Install("CStreaming", "AreAnimsUsedByRequestedModels",0x407AD0, &CStreaming::AreAnimsUsedByRequestedModels);
    Install("CStreaming", "AreTexturesUsedByRequestedModels",0x409A90, &CStreaming::AreTexturesUsedByRequestedModels);
    Install("CStreaming", "ClearFlagForAll",0x407A40, &CStreaming::ClearFlagForAll);
    Install("CStreaming", "ClearSlots",0x40BAA0, &CStreaming::ClearSlots);
    Install("CStreaming", "GetNextFileOnCd",0x408E20, &CStreaming::GetNextFileOnCd);
    Install("CStreaming", "HasSpecialCharLoaded",0x407F00, &CStreaming::HasSpecialCharLoaded);
    Install("CStreaming", "HasVehicleUpgradeLoaded",0x407820, &CStreaming::HasVehicleUpgradeLoaded);
    Install("CStreaming", "ConvertBufferToObject",0x40C6B0, &CStreaming::ConvertBufferToObject);
    Install("CStreaming", "DeleteAllRwObjects",0x4090A0, &CStreaming::DeleteAllRwObjects);
    Install("CStreaming", "DeleteLeastUsedEntityRwObject",0x409760, &CStreaming::DeleteLeastUsedEntityRwObject);
    Install("CStreaming", "DeleteRwObjectsAfterDeath",0x409210, &CStreaming::DeleteRwObjectsAfterDeath);
    Install("CStreaming", "DeleteRwObjectsBehindCamera",0x40D7C0, &CStreaming::DeleteRwObjectsBehindCamera);
    Install("CStreaming", "DeleteRwObjectsBehindCameraInSectorList",0x409940, &CStreaming::DeleteRwObjectsBehindCameraInSectorList);
    Install("CStreaming", "DeleteRwObjectsInSectorList",0x407A70, &CStreaming::DeleteRwObjectsInSectorList);
    Install("CStreaming", "DeleteRwObjectsNotInFrustumInSectorList",0x4099E0, &CStreaming::DeleteRwObjectsNotInFrustumInSectorList);
    Install("CStreaming", "RemoveReferencedTxds",0x40D2F0, &CStreaming::RemoveReferencedTxds);
    Install("CStreaming", "DisableCopBikes",0x407D10, &CStreaming::DisableCopBikes);
    Install("CStreaming", "IsVeryBusy",0x4076A0, &CStreaming::IsVeryBusy);
    Install("CStreaming", "Load",0x5D29E0, &CStreaming::Load);
    Install("CStreaming", "LoadAllRequestedModels",0x40EA10, &CStreaming::LoadAllRequestedModels);
    Install("CStreaming", "LoadCdDirectory_char", 0x5B6170, (void(*)(const char*, int32)) & CStreaming::LoadCdDirectory);
    Install("CStreaming", "LoadCdDirectory_void", 0x5B82C0, (void(*)()) & CStreaming::LoadCdDirectory);
    Install("CStreaming", "LoadInitialPeds",0x40D3D0, &CStreaming::LoadInitialPeds);
    Install("CStreaming", "LoadInitialWeapons",0x40A120, &CStreaming::LoadInitialWeapons);
    Install("CStreaming", "LoadScene",0x40EB70, &CStreaming::LoadScene);
    Install("CStreaming", "LoadSceneCollision",0x40ED80, &CStreaming::LoadSceneCollision);
    Install("CStreaming", "LoadZoneVehicle",0x40B4B0, &CStreaming::LoadZoneVehicle);
    Install("CStreaming", "PossiblyStreamCarOutAfterCreation",0x40BA70, &CStreaming::PossiblyStreamCarOutAfterCreation);
    Install("CStreaming", "RenderEntity",0x4096D0, &CStreaming::RenderEntity);
    Install("CStreaming", "RequestBigBuildings",0x409430, &CStreaming::RequestBigBuildings);
    Install("CStreaming", "RequestFile",0x40A080, &CStreaming::RequestFile);
    Install("CStreaming", "RequestFilesInChannel",0x409050, &CStreaming::RequestFilesInChannel);
    Install("CStreaming", "RequestModel",0x4087E0, &CStreaming::RequestModel);
    Install("CStreaming", "RequestTxdModel",0x407100, &CStreaming::RequestTxdModel);
    Install("CStreaming", "RequestVehicleUpgrade",0x408C70, &CStreaming::RequestVehicleUpgrade);
    Install("CStreaming", "FindMIPedSlotForInterior",0x407FB0, &CStreaming::FindMIPedSlotForInterior);
    Install("CStreaming", "FinishLoadingLargeFile",0x408CB0, &CStreaming::FinishLoadingLargeFile);
    Install("CStreaming", "FlushChannels",0x40E460, &CStreaming::FlushChannels);
    Install("CStreaming", "RequestModelStream",0x40CBA0, &CStreaming::RequestModelStream);
    Install("CStreaming", "RequestSpecialChar",0x40B450, &CStreaming::RequestSpecialChar);
    Install("CStreaming", "RequestSpecialModel",0x409D10, &CStreaming::RequestSpecialModel);
    Install("CStreaming", "ProcessLoadingChannel",0x40E170, &CStreaming::ProcessLoadingChannel);
    Install("CStreaming", "PurgeRequestList",0x40C1E0, &CStreaming::PurgeRequestList);
    Install("CStreaming", "ReInit",0x40E560, &CStreaming::ReInit);
    Install("CStreaming", "ReadIniFile",0x5BCCD0, &CStreaming::ReadIniFile);
    Install("CStreaming", "ReclassifyLoadedCars",0x40AFA0, &CStreaming::ReclassifyLoadedCars);
    Install("CStreaming", "RemoveAllUnusedModels",0x40CF80, &CStreaming::RemoveAllUnusedModels);
    Install("CStreaming", "RemoveBigBuildings",0x4093B0, &CStreaming::RemoveBigBuildings);
    Install("CStreaming", "RemoveBuildingsNotInArea",0x4094B0, &CStreaming::RemoveBuildingsNotInArea);
    Install("CStreaming", "RemoveCarModel",0x4080F0, &CStreaming::RemoveCarModel);
    Install("CStreaming", "RemoveCurrentZonesModels",0x40B080, &CStreaming::RemoveCurrentZonesModels);
    Install("CStreaming", "RemoveDodgyPedsFromRandomSlots",0x40BE60, &CStreaming::RemoveDodgyPedsFromRandomSlots);
    Install("CStreaming", "RemoveEntity",0x409710, &CStreaming::RemoveEntity);
    Install("CStreaming", "RemoveInappropriatePedModels",0x40B3A0, &CStreaming::RemoveInappropriatePedModels);
    Install("CStreaming", "RemoveLeastUsedModel",0x40CFD0, &CStreaming::RemoveLeastUsedModel);
    Install("CStreaming", "RemoveLoadedVehicle",0x40C020, &CStreaming::RemoveLoadedVehicle);
    Install("CStreaming", "RemoveLoadedZoneModel",0x40B340, &CStreaming::RemoveLoadedZoneModel);
    Install("CStreaming", "RemoveModel",0x4089A0, &CStreaming::RemoveModel);
    Install("CStreaming", "RemoveTxdModel",0x40C180, &CStreaming::RemoveTxdModel);
    Install("CStreaming", "MakeSpaceFor",0x40E120, &CStreaming::MakeSpaceFor);
    Install("CStreaming", "ProcessEntitiesInSectorList", 0x40C270, (void(*)(CPtrList&, float, float, float, float, float, float, float, int32)) & CStreaming::ProcessEntitiesInSectorList);
    Install("CStreaming", "RetryLoadFile",0x4076C0, &CStreaming::RetryLoadFile);
    Install("CStreaming", "LoadRequestedModels",0x40E3A0, &CStreaming::LoadRequestedModels);
    Install("CStreaming", "FlushRequestList",0x40E4E0, &CStreaming::FlushRequestList);
    Install("CStreaming", "AddToLoadedVehiclesList",0x408000, &CStreaming::AddToLoadedVehiclesList);
    Install("CStreaming", "GetDefaultCabDriverModel",0x407D50, &CStreaming::GetDefaultCabDriverModel);
    Install("CStreaming", "GetDefaultFiremanModel",0x407D40, &CStreaming::GetDefaultFiremanModel);
    Install("CStreaming", "GetDefaultMedicModel",0x407D20, &CStreaming::GetDefaultMedicModel);
    Install("CStreaming", "GetDefaultCopCarModel",0x407C50, &CStreaming::GetDefaultCopCarModel);
    Install("CStreaming", "GetDefaultCopModel",0x407C00, &CStreaming::GetDefaultCopModel);
    Install("CStreaming", "Init2",0x5B8AD0, &CStreaming::Init2);
    Install("CStreaming", "InitImageList",0x4083C0, &CStreaming::InitImageList);
    Install("CStreaming", "InstanceLoadedModels",0x4084F0, &CStreaming::InstanceLoadedModels);
    Install("CStreaming", "IsCarModelNeededInCurrentZone",0x407DD0, &CStreaming::IsCarModelNeededInCurrentZone);
    Install("CStreaming", "SetMissionDoesntRequireModel",0x409C90, &CStreaming::SetMissionDoesntRequireModel);
    Install("CStreaming", "SetModelIsDeletable",0x409C10, &CStreaming::SetModelIsDeletable);
    Install("CStreaming", "Shutdown",0x4084B0, &CStreaming::Shutdown);
    Install("CStreaming", "StreamAmbulanceAndMedic",0x40A2A0, &CStreaming::StreamAmbulanceAndMedic);
    Install("CStreaming", "StreamCopModels",0x40A150, &CStreaming::StreamCopModels);
    Install("CStreaming", "StreamFireEngineAndFireman",0x40A400, &CStreaming::StreamFireEngineAndFireman);
    Install("CStreaming", "StreamOneNewCar",0x40B4F0, &CStreaming::StreamOneNewCar);
    Install("CStreaming", "StreamPedsForInterior",0x40BBB0, &CStreaming::StreamPedsForInterior);
    Install("CStreaming", "StreamPedsIntoRandomSlots",0x40BDA0, &CStreaming::StreamPedsIntoRandomSlots);
    Install("CStreaming", "StreamVehiclesAndPeds",0x40B700, &CStreaming::StreamVehiclesAndPeds);
    Install("CStreaming", "StreamVehiclesAndPeds_Always",0x40B650, &CStreaming::StreamVehiclesAndPeds_Always);
    Install("CStreaming", "StreamZoneModels",0x40A560, &CStreaming::StreamZoneModels);
    Install("CStreaming", "StreamZoneModels_Gangs",0x40AA10, &CStreaming::StreamZoneModels_Gangs);
    Install("CStreaming", "Update",0x40E670, &CStreaming::Update);
    Install("CStreaming", "WeAreTryingToPhaseVehicleOut",0x407F80, &CStreaming::WeAreTryingToPhaseVehicleOut);
}

uint32 GetModelFromInfo(CStreamingInfo* info) {
    return info - CStreaming::ms_aInfoForModel;
}

CStreamingInfo& CStreaming::GetInfo(uint32 modelId) {
    return ms_aInfoForModel[modelId];
}

bool CStreaming::IsRequestListEmpty() {
    return ms_pEndRequestedList->GetPrev() == ms_pStartRequestedList;
}

// 0x409650
CLink<CEntity*>* CStreaming::AddEntity(CEntity* entity) {
    switch (entity->GetType()) {
    case eEntityType::ENTITY_TYPE_PED:
    case eEntityType::ENTITY_TYPE_VEHICLE:
        return nullptr;
    default:
        break;
    }
    
    CLink<CEntity*>* link = ms_rwObjectInstances.Insert(entity);
    if (!link) {
        CLink<CEntity*>* previousLink = ms_rwObjectInstances.usedListTail.prev;
        for (; previousLink != &ms_rwObjectInstances.usedListHead; previousLink = previousLink->prev) {
            CEntity* entity = previousLink->data;
            if (!entity->m_bImBeingRendered && !entity->m_bStreamingDontDelete)
                break;
        }
        if (previousLink == &ms_rwObjectInstances.usedListHead)
            return ms_rwObjectInstances.Insert(entity);
        previousLink->data->DeleteRwObject();
        link = ms_rwObjectInstances.Insert(entity);
    }
    return link;
}

// 0x407610
uint32 CStreaming::AddImageToList(char const* fileName, bool bNotPlayerImg) {
    const auto entry = std::ranges::find_if(ms_files,
        [](const auto& en) { return !en.IsInUse(); }
    );

    if (entry == std::end(ms_files))
        return 0; // No entry found

    *entry = { fileName, bNotPlayerImg }; // Set entry details

    return std::distance(ms_files, entry); // Return file index
}

// 0x40C520
void CStreaming::AddLodsToRequestList(CVector const& point, uint32 streamingFlags) {
    CWorld::IncrementCurrentScanCode();

    const float minX = point.x - CRenderer::ms_fFarClipPlane;
    const float maxX = point.x + CRenderer::ms_fFarClipPlane;
    const float minY = point.y - CRenderer::ms_fFarClipPlane;
    const float maxY = point.y + CRenderer::ms_fFarClipPlane;

    const int32 startSectorX = std::max(CWorld::GetLodSectorX(minX), 0);
    const int32 startSectorY = std::max(CWorld::GetLodSectorY(minY), 0);
    const int32 endSectorX = std::min(CWorld::GetLodSectorX(maxX), MAX_LOD_PTR_LISTS_X - 1);
    const int32 endSectorY = std::min(CWorld::GetLodSectorY(maxY), MAX_LOD_PTR_LISTS_Y - 1);

    for (int32 sy = startSectorY; sy <= endSectorY; ++sy) {
        for (int32 sx = startSectorX; sx <= endSectorX; ++sx) {
            ProcessEntitiesInSectorList(CWorld::GetLodPtrList(sx, sy), point.x, point.y, minX, minY, maxX, maxY, CRenderer::ms_fFarClipPlane, streamingFlags);
        }
    }
}

// 0x40D3F0
void CStreaming::AddModelsToRequestList(CVector const& point, uint32 streamingFlags) {
    CWorld::IncrementCurrentScanCode();

    const float fRadius = CGame::CanSeeOutSideFromCurrArea() ? 80.0f : 40.0f;

    // Defines a rectangle outside of which models won't be loaded.
    const auto min = point - CVector2D{ fRadius, fRadius },
               max = point + CVector2D{ fRadius, fRadius };

    const auto noCheckRadius = static_cast<int32>(CWorld::GetHalfMapSectorX(fRadius));

    // Smaller radius, models in it are loaded regardless if they're in the rectangle
    // defined by `min` `max` or in `fRadius`.
    const int32 radiusInnerSq = (noCheckRadius - 1) * (noCheckRadius - 1);

    // Bigger radius, models in it are loaded only if in the above mentioned
    // rectangle and radius.
    const int32 radiusOuterSq = (noCheckRadius + 2) * (noCheckRadius + 2);

    const int32 pointSectorX = CWorld::GetSectorX(point.x);
    const int32 pointSectorY = CWorld::GetSectorY(point.y);

    const int32 startSectorX = std::max(CWorld::GetSectorX(min.x), 0);
    const int32 startSectorY = std::max(CWorld::GetSectorY(min.y), 0);
    const int32 endSectorX = std::min(CWorld::GetSectorX(max.x), MAX_SECTORS_X - 1);
    const int32 endSectorY = std::min(CWorld::GetSectorY(max.y), MAX_SECTORS_Y - 1);

    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
            CSector* pSector = GetSector(sectorX, sectorY);

            const int32 distanceY = sectorY - pointSectorY;
            const int32 distanceX = sectorX - pointSectorX;
            const int32 pointSectorDistSq = distanceX * distanceX + distanceY * distanceY;

            if (pointSectorDistSq <= radiusInnerSq) {
                ProcessEntitiesInSectorList(pSector->m_buildings, streamingFlags);
                ProcessEntitiesInSectorList(pRepeatSector->GetList(REPEATSECTOR_PEDS), streamingFlags);
                ProcessEntitiesInSectorList(pSector->m_dummies, streamingFlags);
            } else {
                if (pointSectorDistSq <= radiusOuterSq) {
                    ProcessEntitiesInSectorList(pSector->m_buildings, point.x, point.y, min.x, min.y, max.x, max.y, fRadius, streamingFlags);
                    ProcessEntitiesInSectorList(pRepeatSector->GetList(REPEATSECTOR_PEDS), point.x, point.y, min.x, min.y, max.x, max.y, fRadius, streamingFlags);
                    ProcessEntitiesInSectorList(pSector->m_dummies, point.x, point.y, min.x, min.y, max.x, max.y, fRadius, streamingFlags);
                }
            }
        }
    }
}

// 0x407AD0
bool CStreaming::AreAnimsUsedByRequestedModels(int32 animModelId) {
    for (auto info = ms_pStartRequestedList->GetNext(); info != ms_pEndRequestedList; info = info->GetNext()) {
        const auto modelId = GetModelFromInfo(info);
        if (IsModelDFF(modelId) && CModelInfo::ms_modelInfoPtrs[modelId]->GetAnimFileIndex() == animModelId)
            return true;
    }

    for (int32 channelId = 0; channelId < 2; channelId++) {
        tStreamingChannel& channel = ms_channel[channelId];
        for (int32 model : channel.modelIds) {
            if (model != -1 && IsModelDFF(model) &&
                CModelInfo::GetModelInfo(model)->GetAnimFileIndex() == animModelId)
            {
                return true;
            }
        }
    }

    return false;
}

// func not present in Android 1.0
// 0x409A90
bool CStreaming::AreTexturesUsedByRequestedModels(int32 txdModelId) {
    for (auto info = ms_pStartRequestedList->GetNext(); info != ms_pEndRequestedList; info = info->GetNext()) {
        switch (GetModelType(GetModelFromInfo(info))) {
        case eModelType::DFF: {
            if (CModelInfo::GetModelInfo(GetModelFromInfo(info))->m_nTxdIndex == txdModelId)
                return true;
            break;
        }
        case eModelType::TXD: {
            if (CTxdStore::GetParentTxdSlot(ModelIdToTXD(GetModelFromInfo(info))) == txdModelId)
                return true;
            break;
        }
        }
    }

    for (auto& ch : ms_channel) {
        for (const auto model : ch.modelIds) {
            if (model != -1) {
                switch (GetModelType(model)) {
                case eModelType::DFF: {
                    if (CModelInfo::GetModelInfo(model)->m_nTxdIndex == txdModelId)
                        return true;
                    break;
                }
                case eModelType::TXD: {
                    if (CTxdStore::GetParentTxdSlot(ModelIdToTXD(model)) == txdModelId)
                        return true;
                    break;
                }
                }
            }
        }
    }

    return false;
}

// 0x407A40
void CStreaming::ClearFlagForAll(uint32 streamingFlag) {
    for (int32 i = 0; i < RESOURCE_ID_TOTAL; i++) {
        GetInfo(i).ClearFlags(streamingFlag);
    }
}

// 0x40BAA0
void CStreaming::ClearSlots(int32 totalSlots) {
    for (auto i = 0; i < totalSlots; i++) {
        auto& modelId = ms_pedsLoaded[i];
        if (modelId >= 0) {
            SetModelAndItsTxdDeletable(modelId);
            modelId = -1;
            ms_numPedsLoaded--;
        }
    }
}

// 0x408E20
int32 CStreaming::GetNextFileOnCd(uint32 streamLastPosn, bool bNotPriority) {
    uint32 nextRequestModelPos    = UINT32_MAX;
    uint32 firstRequestModelCdPos = UINT32_MAX;
    int32  firstRequestModelId    = -1;
    int32  nextRequestModelId     = -1;
    for (auto info = ms_pStartRequestedList->GetNext(); info != ms_pEndRequestedList; info = info->GetNext()) {
        const auto modelId = GetModelFromInfo(info);
        if (bNotPriority && ms_numPriorityRequests != 0 && !info->IsPriorityRequest())
            continue;

        // Additional conditions for some model types (DFF, TXD, IFP)
        switch (GetModelType((modelId))) {
        case eModelType::DFF: {
            CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);

            // Make sure TXD will be loaded for this model
            const auto txdModel = TXDToModelId(modelInfo->m_nTxdIndex);
            if (!CStreaming::GetInfo(txdModel).IsLoadedOrBeingRead()) {
                RequestModel(txdModel, GetInfo(modelId).GetFlags()); // Request TXD for this DFF
                continue;
            }

            // Check if it has an anim (IFP), if so, make sure it gets loaded
            const int32 animFileIndex = modelInfo->GetAnimFileIndex();
            if (animFileIndex != -1) {
                const int32 animModelId = IFPToModelId(animFileIndex);
                if (!GetInfo(animModelId).IsLoadedOrBeingRead()) {
                    RequestModel(animModelId, STREAMING_KEEP_IN_MEMORY);
                    continue;
                }
            }
            break;
        }
        case eModelType::TXD: {
            // Make sure parent is/will be loaded
            TxdDef* texDictionary = CTxdStore::ms_pTxdPool->GetAt(ModelIdToTXD(modelId));
            const int16 parentIndex = texDictionary->m_wParentIndex;
            if (parentIndex != -1) {
                const int32 parentModelIdx = TXDToModelId(parentIndex);
                if (!GetInfo(parentModelIdx).IsLoadedOrBeingRead()) {
                    RequestModel(parentModelIdx, STREAMING_KEEP_IN_MEMORY);
                    continue;
                }
            }
            break;
        }
        case eModelType::IFP: {
            if (CCutsceneMgr::ms_cutsceneProcessing || !GetInfo(MODEL_MALE01).IsLoaded()) {
                // Skip in this case
                continue;
            }
            break;
        }
        }

        const uint32 modelCdPos = GetInfo(modelId).GetCdPosn();
        if (modelCdPos < firstRequestModelCdPos) {
            firstRequestModelCdPos = modelCdPos;
            firstRequestModelId = modelId;
        }

        if (modelCdPos < nextRequestModelPos && modelCdPos >= streamLastPosn) {
            nextRequestModelPos = modelCdPos;
            nextRequestModelId = modelId;
        }
    }

    const int32 nextModelId = nextRequestModelId == -1 ? firstRequestModelId : nextRequestModelId;
    if (nextModelId != -1 || ms_numPriorityRequests == 0)
        return nextModelId;

    ms_numPriorityRequests = 0;
    return -1;
}

// 0x407F00
bool CStreaming::HasSpecialCharLoaded(int32 slot) {
    return GetInfo(slot + SPECIAL_MODELS_RESOURCE_ID).IsLoaded();
}

// 0x407820
bool CStreaming::HasVehicleUpgradeLoaded(int32 modelId) {
    if (!GetInfo(modelId).IsLoaded())
        return false;

    const int16 otherUpgradeModelId = CVehicleModelInfo::ms_linkedUpgrades.FindOtherUpgrade(modelId);
    return otherUpgradeModelId == -1 || GetInfo(otherUpgradeModelId).IsLoaded();
}

// 0x40C6B0
bool CStreaming::ConvertBufferToObject(uint8* fileBuffer, int32 modelId)
{
    CStreamingInfo* pStartLoadedListStreamingInfo = ms_startLoadedList;
    CBaseModelInfo* baseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo& streamingInfo = GetInfo(modelId);

    const auto bufferSize = streamingInfo.GetCdSize() * STREAMING_SECTOR_SIZE;
    tRwStreamInitializeData rwStreamInitData = { fileBuffer, bufferSize };

    // Make RW stream from memory
    // TODO: The _ prefix seems to indicate its "private" (maybe), perhaps it was some kind of macro originally?
    RwStream* stream = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitData);

    switch (GetModelType(modelId)) {
    case eModelType::DFF: {

        // Check if TXD and IFP are loaded
        const int32 animFileIndex = baseModelInfo->GetAnimFileIndex();
        const int16 nTXDIdx = baseModelInfo->m_nTxdIndex;
        const TxdDef* txdDef = CTxdStore::ms_pTxdPool->GetAt(nTXDIdx);
        if ((txdDef && !txdDef->m_pRwDictionary) || /*check TXD (if any)*/
            animFileIndex != -1 && !CAnimManager::ms_aAnimBlocks[animFileIndex].bLoaded /*check anim (if any)*/
        ) {
            // TXD or IFP not loaded, re-request model. (I don't think this is supposed to happen at all)
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.GetFlags());
            RwStreamClose(stream, &rwStreamInitData);
            return false;
        }

        CTxdStore::AddRef(nTXDIdx);
        if (animFileIndex != -1)
            CAnimManager::AddAnimBlockRef(animFileIndex);
        CTxdStore::SetCurrentTxd(baseModelInfo->m_nTxdIndex);

        bool bFileLoaded = false;
        if (baseModelInfo->GetRwModelType() == rpATOMIC) {
            RwChunkHeaderInfo chunkHeaderInfo;
            RwStreamReadChunkHeaderInfo(stream, &chunkHeaderInfo);

            // Read UV Anim dict (if any)
            RtDict* pRtDictionary = nullptr;
            if (chunkHeaderInfo.type == rwID_UVANIMDICT) {
                pRtDictionary = RtDictSchemaStreamReadDict(&RpUVAnimDictSchema, stream);
                RtDictSchemaSetCurrentDict(&RpUVAnimDictSchema, pRtDictionary);
            }

            RwStreamClose(stream, &rwStreamInitData);

            // TODO: It seems like this stream is never closed...
            RwStream* stream2 = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitData);
            bFileLoaded = CFileLoader::LoadAtomicFile(stream2, modelId);
            if (pRtDictionary) {
                RtDictDestroy(pRtDictionary);
            }
        } else {
            bFileLoaded = CFileLoader::LoadClumpFile(stream, modelId);
        }

        if (!streamingInfo.IsLoadingFinishing())
        {
            CTxdStore::RemoveRefWithoutDelete(baseModelInfo->m_nTxdIndex);
            if (animFileIndex != -1)
                CAnimManager::RemoveAnimBlockRefWithoutDelete(animFileIndex);

            if (bFileLoaded && baseModelInfo->GetModelType() == MODEL_INFO_VEHICLE)
            {
                if (!AddToLoadedVehiclesList(modelId))
                {
                    RemoveModel(modelId);
                    RequestModel(modelId, streamingInfo.GetFlags());
                    RwStreamClose(stream, &rwStreamInitData);
                    return false;
                }
            }
        }

        if (!bFileLoaded)
        {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.GetFlags());
            RwStreamClose(stream, &rwStreamInitData);
            return false;
        }

        break;
    }
    case eModelType::TXD: {
        const int32 modelTxdIndex = ModelIdToTXD(modelId);
        const TxdDef* txdDef = CTxdStore::ms_pTxdPool->GetAt(modelTxdIndex);
        if (txdDef) {
            const int32 parentTXDIdx = txdDef->m_wParentIndex;
            if (parentTXDIdx != -1 && !CTxdStore::GetTxd(parentTXDIdx)) {
                // Parent not loaded, re-request..
                RemoveModel(modelId);
                RequestModel(modelId, streamingInfo.GetFlags());
                RwStreamClose(stream, &rwStreamInitData);
                return false;
            }
        }

        if (!streamingInfo.IsRequiredToBeKept() && !AreTexturesUsedByRequestedModels(modelTxdIndex))
        {
            // Model not needed anymore, unload
            RemoveModel(modelId);
            RwStreamClose(stream, &rwStreamInitData);
            return false;
        }

        bool bTxdLoaded = false;
        if (ms_bLoadingBigModel) {
            bTxdLoaded = CTxdStore::StartLoadTxd(modelTxdIndex, stream);
            if (bTxdLoaded)
                streamingInfo.m_nLoadState = LOADSTATE_FINISHING;
        } else {
            bTxdLoaded = CTxdStore::LoadTxd(modelTxdIndex, stream);
        }
        if (!bTxdLoaded) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.GetFlags());
            RwStreamClose(stream, &rwStreamInitData);
            return false;
        }
        
        break;
    }
    case eModelType::COL: {
        if (!CColStore::LoadCol(ModelIdToCOL(modelId), fileBuffer, bufferSize)) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.GetFlags());
            RwStreamClose(stream, &rwStreamInitData);
            return false;
        }
        break;
    }
    case eModelType::IPL: {
        if (!CIplStore::LoadIpl(ModelIdToIPL(modelId), fileBuffer, bufferSize)) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.GetFlags());
            RwStreamClose(stream, &rwStreamInitData);
            return false;
        }
        break;
    }
    case eModelType::DAT: {
        ThePaths.LoadPathFindData(stream, ModelIdToDAT(modelId));
        break;
    }
    case eModelType::IFP: {
        if (!streamingInfo.IsRequiredToBeKept()
            && !AreAnimsUsedByRequestedModels(ModelIdToIFP(modelId))
        ) {
            // Not required anymore, unload
            RemoveModel(modelId);
            RwStreamClose(stream, &rwStreamInitData);
            return false;
        }
        // Still required, load
        CAnimManager::LoadAnimFile(stream, true, nullptr);
        CAnimManager::CreateAnimAssocGroups();

        break;
    }
    case eModelType::RRR: {
        CVehicleRecording::Load(stream, ModelIdToRRR(modelId), bufferSize);
        break;
    }
    case eModelType::SCM: {
        CTheScripts::StreamedScripts.LoadStreamedScript(stream, ModelIdToSCM(modelId));
        break;
    }
    default: 
        assert(0); // NOTSA
        break;
    }

    RwStreamClose(stream, &rwStreamInitData);

    switch (GetModelType(modelId)) {
    case eModelType::SCM:
    case eModelType::IFP:
    case eModelType::TXD: {
        if (!streamingInfo.IsMissionOrGameRequired())
            streamingInfo.AddToList(pStartLoadedListStreamingInfo);
        break;
    }
    case eModelType::DFF: {
        // Model is a DFF
        switch (baseModelInfo->GetModelType()) {
        case eModelInfoType::MODEL_INFO_TYPE_VEHICLE:
        case eModelInfoType::MODEL_INFO_TYPE_PED:
            break;
        default: {
            if (CBaseModelInfo* atomicModelInfo = baseModelInfo->AsAtomicModelInfoPtr()) {
                // TODO: What the fuck...
                // From what I understand its either -1 or -0, which, when casted to uint8, becomes 128 or 129
                // Doesnt make a lot of sense to me
                atomicModelInfo->m_nAlpha = -((streamingInfo.GetFlags() & (STREAMING_LOADING_SCENE | STREAMING_MISSION_REQUIRED)) != 0);
            }

            if (!streamingInfo.IsMissionOrGameRequired())
                streamingInfo.AddToList(pStartLoadedListStreamingInfo);

            break;
        }
        }
        break;
    }
    }

    if (!streamingInfo.IsLoadingFinishing()) {
        streamingInfo.m_nLoadState = LOADSTATE_LOADED;
        ms_memoryUsed += bufferSize;
    }
    return true;
}

// 0x4090A0
void CStreaming::DeleteAllRwObjects() {
    for (int32 sx = 0; sx < MAX_SECTORS_X; ++sx) {
        for (int32 sy = 0; sy < MAX_SECTORS_Y; ++sy) {
            CRepeatSector* repeatSector = GetRepeatSector(sx, sy);
            CSector* sector = GetSector(sx, sy);
            DeleteRwObjectsInSectorList(sector->m_buildings);
            DeleteRwObjectsInSectorList(repeatSector->GetList(REPEATSECTOR_OBJECTS));
            DeleteRwObjectsInSectorList(sector->m_dummies);
        }
    }
}

// 0x409760
// Function name is a little misleading, as it deletes the first entity it can.
bool CStreaming::DeleteLeastUsedEntityRwObject(bool bNotOnScreen, uint32 streamingFlags) {
    const float fCameraFarPlane = RwCameraGetFarClipPlane(TheCamera.m_pRwCamera);
    CPlayerPed* player = FindPlayerPed(-1);

    for (auto prevLink = ms_rwObjectInstances.usedListTail.prev; prevLink != &ms_rwObjectInstances.usedListHead;) {
        CEntity* entity = prevLink->data;
        prevLink = prevLink->prev; // Has to be set here, because at the end of the loop it might be invalid.
        
        if (entity->m_bImBeingRendered || entity->m_bStreamingDontDelete)
            continue;

        const int32 modelId = entity->m_nModelIndex;
        const auto baseModelInfo = CModelInfo::GetModelInfo(modelId);
        float drawDistanceRadius = TheCamera.m_fLODDistMultiplier * baseModelInfo->m_fDrawDistance;
        if (entity->m_bIsBIGBuilding)
            drawDistanceRadius *= CRenderer::ms_lowLodDistScale;

        const CVector entityPos = entity->m_pLod ? entity->m_pLod->GetPosition() : entity->GetPosition();
        const float fEntityToCamDist = DistanceBetweenPoints(TheCamera.GetPosition(), entityPos);
        CEntity* const pEntityLastLod = entity->FindLastLOD();

        const float fModelRadius = baseModelInfo->GetColModel()->GetBoundRadius();
        if (ms_bLoadingScene
            || bNotOnScreen && !pEntityLastLod->GetIsOnScreen()
            || !entity->IsInCurrentAreaOrBarberShopInterior()
            || drawDistanceRadius + 50.0f < fEntityToCamDist
            || fModelRadius + fCameraFarPlane < fEntityToCamDist)
        {
            CStreamingInfo& streamingInfo = GetInfo(modelId);
            if (streamingInfo.InList() && !streamingInfo.AreAnyFlagsSetOutOf(streamingFlags)) {
                if (!player || player->bInVehicle || player->m_pContactEntity != entity) {
                    entity->DeleteRwObject();
                    if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount) {
                        RemoveModel(modelId);
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

// 0x409210
// Deletes all RW objects more than 3 sectors (on each axis) away from the given point's sector
void CStreaming::DeleteRwObjectsAfterDeath(CVector const& point) {
    const int32 pointSecX = CWorld::GetSectorX(point.x),
                pointSecY = CWorld::GetSectorY(point.y);
    for (int32 sx = 0; sx < MAX_SECTORS_X; ++sx) {
        if (abs(pointSecX - sx) > 3) {
            for (int32 sy = 0; sy < MAX_SECTORS_Y; ++sy) {
                if (abs(pointSecY - sy) > 3) {
                    CRepeatSector* repeatSector = GetRepeatSector(sx, sy);
                    CSector* sector = GetSector(sx, sy);
                    DeleteRwObjectsInSectorList(sector->m_buildings);
                    DeleteRwObjectsInSectorList(repeatSector->GetList(REPEATSECTOR_OBJECTS));
                    DeleteRwObjectsInSectorList(sector->m_dummies);
                }
            }
        }
    }
}

// 0x40D7C0
// TODO: Decode this, no clue whats going on here..
void CStreaming::DeleteRwObjectsBehindCamera(int32 memoryToCleanInBytes) {
    if (static_cast<int32>(CStreaming::ms_memoryUsed) < memoryToCleanInBytes)
        return;

    const CVector& cameraPos = TheCamera.GetPosition();
    const int32 pointSecX = CWorld::GetSectorX(cameraPos.x),
                pointSecY = CWorld::GetSectorY(cameraPos.y);
    const CVector2D& camFwd = TheCamera.GetForward();
    if (fabs(camFwd.y) < fabs(camFwd.x)) {
        int32 sectorStartY = std::max(pointSecY - 10, 0);
        int32 sectorEndY = std::min(pointSecY + 10, MAX_SECTORS_Y - 1);
        int32 sectorStartX = 0;
        int32 sectorEndX = 0;
        int32 factorX = 0;

        if (camFwd.x <= 0.0f) {
            sectorStartX = std::min(pointSecX + 10, MAX_SECTORS_X - 1);
            sectorEndX = std::min(pointSecX + 2, MAX_SECTORS_X - 1);
            factorX = -1;
        } else {
            sectorStartX = std::max(pointSecX - 10, 0);
            sectorEndX = std::max(pointSecX - 2, 0);
            factorX = 1;
        }

        CWorld::IncrementCurrentScanCode();
        for (int32 sectorX = sectorStartX; sectorX != sectorEndX; sectorX += factorX) {
            for (int32 sectorY = sectorStartY; sectorY <= sectorEndY; sectorY++) {
                CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* sector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(sector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(sector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(repeatSector->GetList(REPEATSECTOR_OBJECTS), memoryToCleanInBytes))
                {
                    return;
                }
            }
        }

        if (camFwd.x <= 0.0f) {
            sectorEndX = std::min(pointSecX + 2, MAX_SECTORS_X - 1);
            sectorStartX = std::max(pointSecX - 10, 0);
            factorX = -1;
        } else {
            sectorEndX = std::max(pointSecX - 2, 0);
            sectorStartX = std::min(pointSecX + 10, MAX_SECTORS_X - 1);
            factorX = 1;
        }

        CWorld::IncrementCurrentScanCode();
        for (int32 sectorX = sectorStartX; sectorX != sectorEndX; sectorX -= factorX) {
            for (int32 sectorY = sectorStartY; sectorY <= sectorEndY; sectorY++) {
                CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* sector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsNotInFrustumInSectorList(sector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(sector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(repeatSector->GetList(REPEATSECTOR_OBJECTS), memoryToCleanInBytes))
                {
                    return;
                }
            }
        }

        CWorld::IncrementCurrentScanCode();
        for (int32 sectorX = sectorStartX; sectorX != sectorEndX; sectorX -= factorX) {
            for (int32 sectorY = sectorStartY; sectorY <= sectorEndY; sectorY++) {
                CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* sector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(sector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(sector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(repeatSector->GetList(REPEATSECTOR_OBJECTS), memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
    }
    else {
        int32 sectorStartX = std::max(pointSecX - 10, 0);
        int32 sectorEndX = std::min(pointSecX + 10, MAX_SECTORS_X - 1);
        int32 sectorStartY = 0;
        int32 sectorEndY = 0;
        int32 factorY = 0;
        if (camFwd.y <= 0.0f) {
            sectorEndY = std::min(pointSecY + 2, MAX_SECTORS_Y - 1);
            sectorStartY = std::min(pointSecY + 10, MAX_SECTORS_Y - 1);
            factorY = -1;
        }
        else  {
            factorY = 1;
            sectorStartY = std::max(pointSecY - 10, 0);
            sectorEndY = std::max(pointSecY - 2, 0);
        }
        CWorld::IncrementCurrentScanCode();
        for (int32 sectorY = sectorStartY; sectorY != sectorEndY; sectorY += factorY) {
            for (int32 sectorX = sectorStartX; sectorX <= sectorEndX; sectorX++) {
                CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* sector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(sector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(sector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(repeatSector->GetList(REPEATSECTOR_OBJECTS), memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
        if (camFwd.y <= 0.0f) {
            sectorEndY = std::min(pointSecY + 2, MAX_SECTORS_Y - 1);
            sectorStartY = std::max(pointSecY - 10, 0);
            factorY = -1;
        }
        else {
            sectorEndY = std::max(pointSecY - 2, 0);
            sectorStartY = std::min(pointSecY + 10, MAX_SECTORS_Y - 1);
            factorY = 1;
        }
        CWorld::IncrementCurrentScanCode();
        for (int32 sectorY = sectorStartY; sectorY != sectorEndY; sectorY -= factorY) {
            for (int32 sectorX = sectorStartX; sectorX <= sectorEndX; sectorX++) {
                CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* sector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsNotInFrustumInSectorList(sector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(sector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsNotInFrustumInSectorList(repeatSector->GetList(REPEATSECTOR_OBJECTS), memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
        if (RemoveReferencedTxds(memoryToCleanInBytes))
            return;
        // BUG: possibly missing CWorld::IncrementCurrentScanCode() here?
        for (int32 sectorY = sectorStartY; sectorY != sectorEndY; sectorY -= factorY) {
            for (int32 sectorX = sectorStartX; sectorX <= sectorEndX; sectorX++) {
                CRepeatSector* repeatSector = GetRepeatSector(sectorX, sectorY);
                CSector* sector = GetSector(sectorX, sectorY);
                if (DeleteRwObjectsBehindCameraInSectorList(sector->m_buildings, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(sector->m_dummies, memoryToCleanInBytes) ||
                    DeleteRwObjectsBehindCameraInSectorList(repeatSector->m_lists[REPEATSECTOR_OBJECTS], memoryToCleanInBytes))
                {
                    return;
                }
            }
        }
    }

    while ((static_cast<int32>(ms_memoryUsed) >= memoryToCleanInBytes)) {
        if (!RemoveLeastUsedModel(0))
            break;
    }
}

// 0x409940
bool CStreaming::DeleteRwObjectsBehindCameraInSectorList(CPtrList& list, int32 memoryToCleanInBytes) {
    for (CPtrNode* node = list.GetNode(); node; node = node->m_next) {
        CEntity* entity = static_cast<CEntity*>(node->m_item);
        if (entity->m_nScanCode == GetCurrentScanCode())
            continue;

        entity->m_nScanCode = GetCurrentScanCode();

        const int32 modelId = entity->m_nModelIndex;
        if (!entity->m_bImBeingRendered && !entity->m_bStreamingDontDelete
            && entity->m_pRwObject
            && GetInfo(modelId).InList()
            && FindPlayerPed(-1)->m_pContactEntity != entity)
        {
            entity->DeleteRwObject();
            if (!CModelInfo::GetModelInfo(modelId)->m_nRefCount) {
                RemoveModel(modelId);
                if (static_cast<int32>(ms_memoryUsed) < memoryToCleanInBytes)
                    return true;
            }
        }
    }
    return false;
}

// 0x407A70
void CStreaming::DeleteRwObjectsInSectorList(CPtrList& list, int32 sectorX, int32 sectorY) {
    for (CPtrNode* node = list.GetNode(); node; node = node->m_next) {
        CEntity* entity = reinterpret_cast<CEntity*>(node->m_item);
        if (sectorX < 0 || entity->LivesInThisNonOverlapSector(sectorX, sectorY)) {
            if (!entity->m_bImBeingRendered && !entity->m_bStreamingDontDelete)
                entity->DeleteRwObject();
        }
    }
}

// 0x4099E0
bool CStreaming::DeleteRwObjectsNotInFrustumInSectorList(CPtrList& list, int32 memoryToCleanInBytes) {
    for (CPtrNode* node = list.GetNode(); node; node = node->m_next) {
        CEntity* entity = reinterpret_cast<CEntity*>(node->m_item);
        if (entity->m_nScanCode == GetCurrentScanCode())
            continue;

        entity->m_nScanCode = GetCurrentScanCode();

        const int32 modelId = entity->m_nModelIndex;
        if (!entity->m_bImBeingRendered && !entity->m_bStreamingDontDelete
            && entity->m_pRwObject
            && (!entity->IsVisible() || entity->m_bOffscreen)
            && GetInfo(modelId).InList())
        {
            entity->DeleteRwObject();
            if (!CModelInfo::GetModelInfo(modelId)->m_nRefCount) {
                RemoveModel(modelId);
                if (static_cast<int32>(ms_memoryUsed) < memoryToCleanInBytes)
                    return true;
            }
        }
    }
    return false;
}

// 0x40D2F0
// The naming seems to be incorrect.
// In fact it only removes TXDs with `STREAMING_LOADING_SCENE` not set and no references.
bool CStreaming::RemoveReferencedTxds(int32 memoryToCleanInBytes)
{
    for (auto info = ms_pEndLoadedList->GetPrev(); info != CStreaming::ms_startLoadedList; info = info->GetPrev()) {
        const auto modelId = GetModelFromInfo(info);
        if (IsModelTXD(modelId) && info->IsLoadingScene()) {
            if (!CTxdStore::GetNumRefs(ModelIdToTXD(modelId))) {
                CStreaming::RemoveModel(modelId);
                if (static_cast<int32>(CStreaming::ms_memoryUsed) < memoryToCleanInBytes)
                    return true;
            }
        }
    }
    return false;
}

// 0x407D10
void CStreaming::DisableCopBikes(bool bDisable) {
    m_bDisableCopBikes = bDisable;
}

// 0x4076A0
bool CStreaming::IsVeryBusy() {
    return CRenderer::m_loadingPriority || ms_numModelsRequested > 5;
}

// 0x5D29E0
void CStreaming::Load() {
    for (CStreamingInfo& info : ms_aInfoForModel) {
        uint8 flags;
        CGenericGameStorage::LoadDataFromWorkBuffer(&flags, sizeof(flags));
        if (info.IsLoaded() && flags != 0xFFu)
            info.SetFlags(flags);
    }
}

// There are only 2 streaming channels within CStreaming::ms_channel. In this function,
// if your current channelIndex is zero then "1 - channelIndex" will give you the other
// streaming channel within CStreaming::ms_channel which is 1 (second streaming channel).
// 0x40EA10
void CStreaming::LoadAllRequestedModels(bool bOnlyPriorityRequests)
{
    if (m_bLoadingAllRequestedModels)
        return;
    m_bLoadingAllRequestedModels = true;

    FlushChannels();

    auto numModelsToLoad = std::max(10, 2 * ms_numModelsRequested);
    int32 chIdx = 0;
    while (true)
    {
        const tStreamingChannel& ch1 = ms_channel[0];
        const tStreamingChannel& ch2 = ms_channel[1];

        if (IsRequestListEmpty() && ch1.LoadStatus == eChannelState::IDLE && ch2.LoadStatus == eChannelState::IDLE
            || numModelsToLoad <= 0)
        {
            break;
        }

        if (ms_bLoadingBigModel)
            chIdx = 0;

        auto& currCh = ms_channel[chIdx];

        if (currCh.LoadStatus != eChannelState::IDLE) {
            // Finish loading whatever it was loading
            CdStreamSync(chIdx);
            currCh.iLoadingLevel = 100;
        }
        
        if (currCh.IsReading()) {
            ProcessLoadingChannel(chIdx);
            if (currCh.IsStarted())
                ProcessLoadingChannel(chIdx); // Finish loading big model
        }

        if (bOnlyPriorityRequests && ms_numPriorityRequests == 0)
            break;

        if (!ms_bLoadingBigModel) {
            const auto other = 1 - chIdx;
            if (ms_channel[other].LoadStatus == eChannelState::IDLE)
                RequestModelStream(other);

            if (currCh.LoadStatus == eChannelState::IDLE && !ms_bLoadingBigModel)
                RequestModelStream(chIdx);
        }

        if (ch1.LoadStatus == eChannelState::IDLE && ch2.LoadStatus == eChannelState::IDLE)
            break;

        chIdx = 1 - chIdx; // Switch to other channel
        --numModelsToLoad;
    }
    FlushChannels();
    m_bLoadingAllRequestedModels = false;
}

// 0x5B6170
// Load a directory (aka img file)
// This will set the `CdSize, CdPosn, m_nImgId, m_nNextIndexOnCd` member variables of
// each model present in the file (according to file name)
void CStreaming::LoadCdDirectory(const char* filename, int32 archiveId)
{
    FILE* imgFile = CFileMgr::OpenFile(filename, "rb");
    if (!imgFile)
        return;

    // Read and check IMG file version
    {
        char version[4];
        CFileMgr::Read(imgFile, &version, 4u);    // �VER2� for SA
        assert(strncmp(version, "VER2", 4) == 0); // NOTSA
    }

    int32 previousModelId = -1;
    int32 entryCount;
    CFileMgr::Read(imgFile, &entryCount, 4u);
    for (int32 i = 0; i < entryCount; i++) {
        CDirectory::DirectoryInfo entry{};
        CFileMgr::Read(imgFile, &entry, sizeof(CDirectory::DirectoryInfo));

        // Maybe increase buffer size
        ms_streamingBufferSize = std::max(ms_streamingBufferSize, (uint32)entry.m_nStreamingSize);

        // Find extension from name
        constexpr auto nameSize = sizeof(CDirectory::DirectoryInfo::m_szName);
        entry.m_szName[nameSize - 1] = 0;
        char* extension = strchr(entry.m_szName, '.');
        if (!extension
            || (size_t)(extension - entry.m_szName) > nameSize - 4u // Check if extension string length is  < 4
        ) {
            entry.m_szName[nameSize - 1] = 0;
            previousModelId = -1;
            continue;
        }

        // Replace `.` with a null terminator
        // This way m_szName only contains the file name without the extension
        // Eg.: `car.dff` becomes `car`
        *extension = 0;

        // TODO: Maybe use `makeFourCC` here + switch case

        const auto ExtensionIs = [=](const char what[]) {
            return _memicmp(extension + 1, what, strlen(what)) == 0;
        };

        int32 modelId = -1;
        if (ExtensionIs("DFF")) {
            if (!CModelInfo::GetModelInfo(entry.m_szName, &modelId)) {
                entry.m_nOffset |= archiveId << 24;
                CStreaming::ms_pExtraObjectsDir->AddItem(entry);
                previousModelId = -1;
                continue;
            }

        } else if (ExtensionIs("TXD")) {
            int32 txdSlot = CTxdStore::FindTxdSlot(entry.m_szName);
            if (txdSlot == -1) {
                txdSlot = CTxdStore::AddTxdSlot(entry.m_szName);
                CVehicleModelInfo::AssignRemapTxd(entry.m_szName, txdSlot);
            }
            modelId = TXDToModelId(txdSlot);

        } else if (ExtensionIs("COL")) {
            int32 colSlot = CColStore::FindColSlot();
            if (colSlot == -1)
                colSlot = CColStore::AddColSlot(entry.m_szName);
            modelId = COLToModelId(colSlot);

        } else if (ExtensionIs("IPL")) {
            int32 iplSlot = CIplStore::FindIplSlot(entry.m_szName);
            if (iplSlot == -1)
                iplSlot = CIplStore::AddIplSlot(entry.m_szName);
            modelId = IPLToModelId(iplSlot);

        } else if (ExtensionIs("DAT")) {
            // Extract nodes file sector from name (Remember the format: `nodesXX.dat` where XX is the id)
            // TODO: Maybe one day add some error here if sscanf doesn't return 1 (that is, the number couldn't be read)
            (void)sscanf(&entry.m_szName[sizeof("nodes") - 1], "%d", &modelId); 
            modelId += RESOURCE_ID_DAT;

        } else if (ExtensionIs("IFP")) {
            modelId = IFPToModelId(CAnimManager::RegisterAnimBlock(entry.m_szName));

        } else if (ExtensionIs("RRR")) {
            modelId = RRRToModelId(CVehicleRecording::RegisterRecordingFile(entry.m_szName));

        } else if (ExtensionIs("SCM")) {
            modelId = SCMToModelId(CTheScripts::StreamedScripts.RegisterScript(entry.m_szName));
        } else {
            *extension = '.'; // Put `.` back as previously it was replace with a null terminator
            previousModelId = -1;
            continue;
        }

        CStreamingInfo& info = GetInfo(modelId);
        if (!info.HasCdPosnAndSize()) {
            info.m_nImgId = archiveId;

            if (entry.m_nSizeInArchive)
                entry.m_nStreamingSize = entry.m_nSizeInArchive;

            info.SetCdPosnAndSize(entry.m_nOffset, entry.m_nStreamingSize);
            info.ClearAllFlags();

            if (previousModelId != -1)
                GetInfo(previousModelId).m_nNextIndexOnCd = modelId;

            previousModelId = modelId;
        }
    }
    CFileMgr::CloseFile(imgFile);
}

// 0x5B82C0
void CStreaming::LoadCdDirectory()
{
    ///////////// unused //////////////
    ms_imageOffsets[0] = 0;
    ms_imageOffsets[1] = -1;
    ms_imageOffsets[2] = -1;
    ms_imageOffsets[3] = -1;
    ms_imageOffsets[4] = -1;
    ms_imageOffsets[5] = -1;
    // ms_imageSize = GetGTA3ImgSize(); 0x406360
    ///////////////////////////////////

    // This is used to load the archives
    auto archiveId{0};
    for (auto& file : ms_files) {
        if (file.IsInUse() && file.m_bNotPlayerImg) {
            LoadCdDirectory(file.m_szName, archiveId);
        }
        archiveId++;
    }

    ///////////// unused //////////////
    ms_lastImageRead = 0;
    // ms_imageSize = ms_imageSize >> 11;
}

// 0x40D3D0
void CStreaming::LoadInitialPeds() {
    RequestModel(MODEL_MALE01, STREAMING_GAME_REQUIRED); // Without this model the game basically crashes, it has to be loaded at all times.
    StreamCopModels(LEVEL_NAME_LOS_SANTOS);
}

// 0x407F20
void CStreaming::LoadInitialVehicles() {
    // NOP
}

// 0x40A120
void CStreaming::LoadInitialWeapons() {
    RequestModel(MODEL_COLT45, STREAMING_GAME_REQUIRED);
    RequestModel(MODEL_NITESTICK, STREAMING_GAME_REQUIRED);
    RequestModel(MODEL_MISSILE, STREAMING_GAME_REQUIRED);
}

// 0x40EB70
void CStreaming::LoadScene(CVector const& point) {
    ms_bLoadingScene = true;

    CVector playerPosition = FindPlayerCoors(0);

    // Can't use a simple `for` loop here, because model is unlinked (thus the iterator is invalidated) when removed.
    {
        CStreamingInfo* iter = ms_pEndRequestedList->GetPrev();
        while (iter != ms_pStartRequestedList) {
            const auto next = iter->GetPrev();
            if (!iter->DontRemoveInLoadScene())
                RemoveModel(GetModelFromInfo(iter));
            iter = next;
        }
    }

    CRenderer::SetLoadingPriority(0);
    DeleteAllRwObjects();
    RequestBigBuildings(point);
    CIplStore::LoadIpls(point, true);
    LoadAllRequestedModels(false);
    AddModelsToRequestList(point, STREAMING_LOADING_SCENE);
    CRadar::StreamRadarSections(point);
    ThePaths.LoadSceneForPathNodes(point);
    if (CGame::CanSeeOutSideFromCurrArea()) {
        if (ms_bLoadVehiclesInLoadScene) {
            if (CTheZones::GetZoneInfo(point, nullptr) != CTheZones::GetZoneInfo(playerPosition, nullptr)) {
                for (int32 i = 0; i < 5; i++) {
                    LoadZoneVehicle(point);
                }
            }
        }
        StreamCopModels(CTheZones::GetLevelFromPosition(point));
    }
    LoadAllRequestedModels(false);
    InstanceLoadedModels(point);
    ClearFlagForAll(STREAMING_LOADING_SCENE);
    ms_bLoadingScene = false;
    if (CWorld::Players[0].m_pPed)
        CPopulation::ManageAllPopulation();
}

// 0x40ED80
void CStreaming::LoadSceneCollision(CVector const& point) {
    CColStore::LoadCollision(point, true);
    CIplStore::LoadIpls(point, true);
    LoadAllRequestedModels(false);
}

// 0x40B4B0
void CStreaming::LoadZoneVehicle(const CVector& point) {
    if (CPopCycle::m_pCurrZoneInfo) {
        CTheZones::GetZoneInfo(point, nullptr); // called but return value is ignored
        const auto modelId = CCarCtrl::ChooseCarModelToLoad(CPopCycle::PickARandomGroupOfOtherPeds());
        if (modelId >= 0)
            RequestModel(modelId, STREAMING_KEEP_IN_MEMORY);
    }

}

// 0x40BA70
void CStreaming::PossiblyStreamCarOutAfterCreation(int32 modelId) {
    if (CModelInfo::GetModelInfo(modelId)->m_nFlags & STREAMING_UNKNOWN_1) {
        if (rand() % 2)
            SetModelIsDeletable(modelId);
    }
}

// 0x4096D0
void CStreaming::RenderEntity(CLink<CEntity*>* streamingLink) {
    if (streamingLink && streamingLink != ms_renderEntityLink) {
        streamingLink->Remove();
        ms_renderEntityLink->Insert(streamingLink);
        ms_renderEntityLink = streamingLink;
    }
}

// 0x409430
// Load big buildings around `point`
void CStreaming::RequestBigBuildings(CVector const& point) {
    for (int32 i = CPools::ms_pBuildingPool->GetSize() - 1; i >= 0; i--) {
        CBuilding* building = CPools::ms_pBuildingPool->GetAt(i);
        if (building && building->m_bIsBIGBuilding) {
            if (CRenderer::ShouldModelBeStreamed(building, point, TheCamera.m_pRwCamera->farPlane))
                RequestModel(building->m_nModelIndex, 0);
        }
    }
}

// 0x40A080
// Request model @ `posn` with size `size` in the img `imgId`.
void CStreaming::RequestFile(uint32 modelId, int32 posn, uint32 size, int32 imgId, uint32 streamingFlags) {
    auto& info = GetInfo(modelId);
    const uint32 blockOffset = (imgId << 24) | posn;
    if (info.GetCdSize() && info.GetCdPosn() == blockOffset && info.GetCdSize() == size) {
        RequestModel(modelId, streamingFlags);
    } else {
        RemoveModel(modelId);
        info.SetCdPosnAndSize(blockOffset & 0xFFFFFF, size);
        info.m_nImgId = imgId;
        RequestModel(modelId, streamingFlags);
    }
}

// 0x409050
// Goes thru given channel and removes then re-requests each model
void CStreaming::RequestFilesInChannel(int32 chIdx) {
    for (const auto modelId : ms_channel[chIdx].modelIds) {
        if (modelId != -1) {
            RemoveModel(modelId);
            RequestModel(modelId, GetInfo(modelId).GetFlags());
        }
    }
}

// 0x4087E0
// Request a given model to be loaded.
// Can be called on an already requested model to add `PRIORITY_REQUEST` flag
void CStreaming::RequestModel(int32 modelId, uint32 streamingFlags)
{
    CStreamingInfo& info = GetInfo(modelId);
    
    switch (info.m_nLoadState) {
    case eStreamingLoadState::LOADSTATE_NOT_LOADED:
        break;

    case eStreamingLoadState::LOADSTATE_REQUESTED: {
        // Model already requested, just set priority request flag if not set already
        if ((streamingFlags & STREAMING_PRIORITY_REQUEST) && !info.IsPriorityRequest())
        {
            ++ms_numPriorityRequests;
            info.SetFlags(STREAMING_PRIORITY_REQUEST);
        }
        break;
    }

    default: {
        streamingFlags &= ~STREAMING_PRIORITY_REQUEST; // Remove flag otherwise
        break;
    }
    }
    info.SetFlags(streamingFlags);

    // BUG: Possibly? If the model was requested once with `PRIORITY_REQUEST` set
    //      and later is requested without it `ms_numPriorityRequests` won't be decreased.

    switch (info.m_nLoadState) {
    case eStreamingLoadState::LOADSTATE_LOADED: {
        if (info.InList()) {
            info.RemoveFromList();
            if (IsModelDFF(modelId)) {
                switch (CModelInfo::GetModelInfo(modelId)->GetModelType()) {
                case eModelInfoType::MODEL_INFO_TYPE_PED:
                case eModelInfoType::MODEL_INFO_TYPE_VEHICLE: {
                    return;
                }
                }
            }

            if (!info.IsMissionOrGameRequired())
                info.AddToList(ms_startLoadedList);
        }
        break;
    }
    case eStreamingLoadState::LOADSTATE_READING:
    case eStreamingLoadState::LOADSTATE_REQUESTED:
    case eStreamingLoadState::LOADSTATE_FINISHING:
        break;

    case eStreamingLoadState::LOADSTATE_NOT_LOADED: {
        switch (GetModelType(modelId)) {
        case eModelType::TXD: { // Request parent (if any) TXD
            int32 txdEntryParentIndex = CTxdStore::GetParentTxdSlot(ModelIdToTXD(modelId));
            if (txdEntryParentIndex != -1)
                RequestTxdModel(txdEntryParentIndex, streamingFlags);
            break;
        }
        case eModelType::DFF: { // Request TXD and (if any) IFP
            CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
            RequestTxdModel(modelInfo->m_nTxdIndex, streamingFlags);

            const int32 animFileIndex = modelInfo->GetAnimFileIndex();
            if (animFileIndex != -1)
                RequestModel(IFPToModelId(animFileIndex), STREAMING_KEEP_IN_MEMORY);
            break;
        }
        }
        info.AddToList(ms_pStartRequestedList);

        ++ms_numModelsRequested;
        if (streamingFlags & STREAMING_PRIORITY_REQUEST)
            ++ms_numPriorityRequests;

        info.SetFlags(streamingFlags);
        info.m_nLoadState = LOADSTATE_REQUESTED;
        break;
    }
    }
}

// TODO: Make more of these functions, really makes the code cleaner.
// 0x407100
void CStreaming::RequestTxdModel(int32 slot, int32 streamingFlags) {
    RequestModel(TXDToModelId(slot), streamingFlags);
}

// 0x408C70
void CStreaming::RequestVehicleUpgrade(int32 modelId, uint32 streamingFlags)
{
    RequestModel(modelId, streamingFlags);
    if (const auto other = CVehicleModelInfo::ms_linkedUpgrades.FindOtherUpgrade(modelId); other != -1)
        RequestModel(other, streamingFlags);
}

// 0x407FB0
int32 CStreaming::FindMIPedSlotForInterior(int32 randFactor)
{
    for (auto i = 0; i < TOTAL_LOADED_PEDS; i++) {
        const auto modelId = ms_pedsLoaded[(i + randFactor) % TOTAL_LOADED_PEDS];
        if (modelId >= 0 && GetInfo(modelId).IsLoaded())
            return modelId;
    }
    return MODEL_MALE01;
}

// 0x408CB0
// Finishes loading a big model by loading the second half of the file
// residing at `pFileBuffer`.
void CStreaming::FinishLoadingLargeFile(uint8* pFileBuffer, int32 modelId)
{
    bool bFinishedLoadingLargeFile = false;
    CBaseModelInfo* baseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo& streamingInfo = GetInfo(modelId);
    if (streamingInfo.IsLoadingFinishing()/*first half loaded?*/) {
        const uint32 bufferSize = streamingInfo.GetCdSize() * STREAMING_SECTOR_SIZE;
        const tRwStreamInitializeData rwStreamInitializationData = { pFileBuffer, bufferSize };
        RwStream* pRwStream = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitializationData);

        bool bLoaded = false;
        switch (GetModelType(modelId)) {
        case eModelType::DFF: {
            CTxdStore::SetCurrentTxd(baseModelInfo->m_nTxdIndex);

            bLoaded = CFileLoader::FinishLoadClumpFile(pRwStream, modelId);
            if (bLoaded)
                bLoaded = AddToLoadedVehiclesList(modelId);
            baseModelInfo->RemoveRef();

            CTxdStore::RemoveRefWithoutDelete(baseModelInfo->m_nTxdIndex);

            const int32 animFileIndex = baseModelInfo->GetAnimFileIndex();
            if (animFileIndex != -1) {
                CAnimManager::RemoveAnimBlockRefWithoutDelete(animFileIndex);
            }
            break;
        }
        case eModelType::TXD: {
            CTxdStore::AddRef(ModelIdToTXD(modelId));
            bLoaded = CTxdStore::FinishLoadTxd(ModelIdToTXD(modelId), pRwStream);
            CTxdStore::RemoveRefWithoutDelete(ModelIdToTXD(modelId));
            break;
        }
        default: {
            assert(modelId < RESOURCE_ID_COL && "FinishLoadingLargeFile: model id is out of range");
            break;
        }
        }
        RwStreamClose(pRwStream, &pFileBuffer);

        streamingInfo.m_nLoadState = LOADSTATE_LOADED;
        ms_memoryUsed += bufferSize;
        if (!bLoaded) {
            RemoveModel(modelId);
            RequestModel(modelId, streamingInfo.GetFlags());
        }
    } else {
        if (IsModelDFF(modelId))
            baseModelInfo->RemoveRef();
    }
}

// 0x40E460
// Finishes loading all channels. (So both channels will be `IDLE` after it returns)
// Blocking. (Calls `CdStreamSync`)
void CStreaming::FlushChannels()
{
    // Big model. Finish loading it.
    if (ms_channel[1].IsStarted())
        ProcessLoadingChannel(1);

    // Force finish loading channel 0 by using `CdStreamSync`.
    if (ms_channel[0].IsReading())
    {
        CdStreamSync(0);
        ms_channel[0].iLoadingLevel = 100;
        ProcessLoadingChannel(0);
    }

    // Big model again. Finish loading it.
    if (ms_channel[0].IsStarted())
        ProcessLoadingChannel(0);

    // Force finish loading channel 1 by using `CdStreamSync`.
    if (ms_channel[1].IsReading())
    {
        CdStreamSync(1u);
        ms_channel[1].iLoadingLevel = 100;
        ProcessLoadingChannel(1);
    }

    // Big model again. Finish loading it.
    if (ms_channel[1].IsStarted())
        ProcessLoadingChannel(1);
}

// 0x40CBA0
// Starts reading at most 16 models at a time.
// Removes all unused (if not IsRequiredToBeKept()) IFP/TXDs models as well.
void CStreaming::RequestModelStream(int32 chIdx)
{
    int32 modelId = GetNextFileOnCd(CdStreamGetLastPosn(), true);
    if (modelId == -1)
        return;

    tStreamingChannel& ch = ms_channel[chIdx];
    uint32 posn = 0;
    uint32 nThisModelSizeInSectors = 0;
    CStreamingInfo* streamingInfo = &GetInfo(modelId);

    // Find first model that has to be loaded
    while (!streamingInfo->IsRequiredToBeKept()) {
        // In case of TXD/IFP's check if they're used at all, if not remove them.
        if (IsModelTXD(modelId)) {
            if (AreTexturesUsedByRequestedModels(ModelIdToTXD(modelId)))
                break;
        } else if (IsModelIFP(modelId)) {
            if (AreAnimsUsedByRequestedModels(ModelIdToIFP(modelId)))
                break;
        } else /*model is neither TXD or IFP*/ {
            break; // No checks needed
        }

        // TXD/IFP unused, so remove it, and go on to the next file

        RemoveModel(modelId);

        streamingInfo->GetCdPosnAndSize(posn, nThisModelSizeInSectors);         // Grab pos and size of this model
        modelId = GetNextFileOnCd(posn + nThisModelSizeInSectors, true);   // Find where the next file is after it
        if (modelId == -1)
            return; // No more models...
        streamingInfo = &GetInfo(modelId); // Grab next file's info
    }

    /* original duplicated and useless code
    if (modelId == -1)
        return;
    */

    // Grab cd pos and size for this model
    streamingInfo->GetCdPosnAndSize(posn, nThisModelSizeInSectors);

    // Check if its big
    if (nThisModelSizeInSectors > ms_streamingBufferSize) {
        // A model is considered "big" if it doesn't fit into a single channel's buffer
        // In which case it has to be loaded entirely by channel 0.
        if (chIdx == 1 || ms_channel[1].LoadStatus != eChannelState::IDLE)
            return;
        ms_bLoadingBigModel = true;
    }

    // Find all (but at most 16) consecutive models starting at `posn` and load them in one go
    uint32 nSectorsToRead = 0; // The # of sectors to be loaded beginning at `posn`

    bool isPreviousLargeishBigOrVeh = false;
    bool isPreviousModelPed = false;

    uint32 i = 0;
    for (; i < std::size(ch.modelIds); i++) {
        streamingInfo = &GetInfo(modelId);

        if (streamingInfo->m_nLoadState != LOADSTATE_REQUESTED)
            break; // Model not requested, so no need to load it. 

        if (streamingInfo->GetCdSize())
            nThisModelSizeInSectors = streamingInfo->GetCdSize();

        const bool isThisModelLargeish = nThisModelSizeInSectors > 200;

        if (ms_numPriorityRequests && !streamingInfo->IsPriorityRequest())
            break; // There are priority requests, but this isn't one of them

        if (IsModelDFF(modelId)) {
            CBaseModelInfo* pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];

            if (isPreviousModelPed && pBaseModelInfo->GetModelType() == MODEL_INFO_PED)
                break; // Don't load two peds after each other

            if (isPreviousLargeishBigOrVeh && pBaseModelInfo->GetModelType() == MODEL_INFO_VEHICLE)
                break; // Don't load two vehicles / big model + vehicle after each other

            // Check if TXD and/or IFP is loaded for this model.
            // If not we can't load the model yet.

            // Check TXD
            if (!GetInfo(TXDToModelId(pBaseModelInfo->m_nTxdIndex)).IsLoadedOrBeingRead())
                break;

            // Check IFP (if any)
            const int32 animFileIndex = pBaseModelInfo->GetAnimFileIndex();
            if (animFileIndex != -1)
            {
                if (!GetInfo(IFPToModelId(animFileIndex)).IsLoadedOrBeingRead())
                    break;
            }
        } else {
            if (IsModelIFP(modelId)) {
                if (CCutsceneMgr::ms_cutsceneProcessing || !GetInfo(MODEL_MALE01).IsLoaded())
                    break;
            } else {
                if (isPreviousLargeishBigOrVeh && isThisModelLargeish)
                    break; // Do not load a big model/car and a big model after each other 
            }
        }

        // At this point we've made sure the model can be loaded
        // so let's add it to the channel.

        // Set offset where the model's data begins at
        ch.modelStreamingBufferOffsets[i] = nSectorsToRead;

        // Set the corresponding modelid
        ch.modelIds[i] = modelId;

        // `i == 0` is a special case:
        // If the 0th model doesn't fit into the buffer it's a `big` one
        // so `ms_bLoadingBigModel` is set already (before the `for` loop).
        // But we still need to continue to set the appropriate states for the
        // model, thus we can't just `break` (which would also cause the loop below setting modelId slots `-1`'s to override the modelId)
        if (i > 0) {
            // Check if this model + all the previous fits into one channel's buffer
            if (nSectorsToRead + nThisModelSizeInSectors > ms_streamingBufferSize) {
                // No, so stop at the previous model, and ignore this one
                break;
            }
        }
        nSectorsToRead += nThisModelSizeInSectors;

        CBaseModelInfo* pBaseModelInfo = CModelInfo::GetModelInfo(modelId);
        if (IsModelDFF(modelId)) {
            switch (pBaseModelInfo->GetModelType()) {
            case ModelInfoType::MODEL_INFO_PED:
                isPreviousModelPed = true;
                break;
            case ModelInfoType::MODEL_INFO_VEHICLE:
                isPreviousLargeishBigOrVeh = true; // I guess all vehicles are considered big?
                break;
            }
        } else {
            if (isThisModelLargeish)
                isPreviousLargeishBigOrVeh = true;
        }

        // Modify the state of models
        {
            streamingInfo->m_nLoadState = LOADSTATE_READING; // Set as being read
            streamingInfo->RemoveFromList(); // Remove from it's current list (That is the requested list)
            ms_numModelsRequested--;
            if (streamingInfo->IsPriorityRequest()) {
                streamingInfo->ClearFlags(STREAMING_PRIORITY_REQUEST); // Remove priority request flag, as its not a request anymore.
                ms_numPriorityRequests--;
            }
        }

        modelId = streamingInfo->m_nNextIndexOnCd; // Continue onto the next one in the directory
    }

    // Set remaining modelId slots to `-1`
    for (uint32 x = i; x < std::size(ch.modelIds); x++) {
        ch.modelIds[x] = -1;
    }

    CdStreamRead(chIdx, ms_pStreamingBuffer[chIdx], posn, nSectorsToRead); // Request models to be read
    ch.LoadStatus = eChannelState::READING;
    ch.iLoadingLevel = 0;
    ch.sectorCount = nSectorsToRead; // Set how many sectors to read
    ch.offsetAndHandle = posn;       // And from where to read
    ch.totalTries = 0;
    if (m_bModelStreamNotLoaded)
        m_bModelStreamNotLoaded = false;
}

// 0x40B450
void CStreaming::RequestSpecialChar(int32 modelId, char const* name, int32 flags) {
    return RequestSpecialModel(modelId + SPECIAL_MODELS_RESOURCE_ID, name, flags);
}

// 0x409D10
// Load a special model as onto the given modelId.
// It's data should be available in the extra objects directory (ms_pExtraObjectsDir) with the given name.
// If there's already a model loaded onto `modelId` it will be unloaded along all the objects/peds using it.
// If streaming info for the given model can be found it will be requested to be loaded.
void CStreaming::RequestSpecialModel(int32 modelId, char const* name, int32 flags)
{
    CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
    CStreamingInfo& streamingInfo = CStreaming::GetInfo(modelId);
    
    if (CKeyGen::GetUppercaseKey(name) == modelInfo->m_nKey && streamingInfo.HasCdPosnAndSize()) {
        // Model present already present somewhere, so just load it
        RequestModel(modelId, flags);
        return;
    }

    // Make sure model isn't used anywhere by destroying all objects/peds using it.
    if (modelInfo->m_nRefCount > 0) {
        for (int32 i = CPools::ms_pPedPool->GetSize() - 1; i >= 0; i--) {
            if (modelInfo->m_nRefCount <= 0)
                break;

            CPed* ped = CPools::ms_pPedPool->GetAt(i);
            if (ped && ped->m_nModelIndex == modelId && !ped->IsPlayer() && ped->CanBeDeletedEvenInVehicle()) {
                CTheScripts::RemoveThisPed(ped);
            }
        }

        for (int32 i = CPools::ms_pObjectPool->GetSize() - 1; i >= 0; i--) {
            if (modelInfo->m_nRefCount <= 0)
                break;

            CObject* obj = CPools::ms_pObjectPool->GetAt(i);
            if (obj && obj->m_nModelIndex == modelId && obj->CanBeDeleted()) {
                CWorld::Remove(obj);
                CWorld::RemoveReferencesToDeletedObject(obj);
                delete obj;
            }
        }
    }

    const auto modelNameKey = modelInfo->GetModelName();
    modelInfo->SetModelName(name);

    // Find model info for model, and unload it
    {
        CBaseModelInfo* foundModelInfo = nullptr;
        for (int32 i = 0; i <= 1000; i++) {
            CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(i);
            if (modelInfo && modelNameKey == modelInfo->GetModelName()) {
                foundModelInfo = modelInfo;
            }
        }

        if (foundModelInfo
            && foundModelInfo->m_nTxdIndex != -1 && CTxdStore::ms_pTxdPool->GetAt(foundModelInfo->m_nTxdIndex) /*has valid TXD*/
            ) {
            CTxdStore::AddRef(foundModelInfo->m_nTxdIndex); // Makes sure TXD doesn't get unloaded
            RemoveModel(modelId);
            CTxdStore::RemoveRefWithoutDelete(foundModelInfo->m_nTxdIndex);
        }
        else {
            RemoveModel(modelId); // Just remove model
        }
    }

    // Find model in extra objects directory
    uint32 outOffset, outStreamingSize;
    CStreaming::ms_pExtraObjectsDir->FindItem(name, outOffset, outStreamingSize);
    modelInfo->ClearTexDictionary();
    modelInfo->SetTexDictionary(CTxdStore::FindTxdSlot(name) == -1 ? "generic" : name);

    // The first 3 bytes of outOffset is used for m_nCdPosn and
    // the remaining 1 byte is used for m_nImgId
    // outOffset & 0xFFFFF = returns the first 3 bytes and ignores the last one
    // outOffset >> 24 = Ignores the first 3 bytes and returns the last byte
    streamingInfo.SetCdPosnAndSize(outOffset & 0xFFFFFF, outStreamingSize);
    streamingInfo.m_nImgId = outOffset >> 24;
    streamingInfo.m_nNextIndexOnCd = -1;

    RequestModel(modelId, flags);
}

// 0x40E170
// If the channel is done reading (`CdStreamGetStatus(chIdx)` == READING_SUCCESS) then loads all the read models
// using either `ConvertBufferToObject` or `FinishLoadingLargeFile` (in case of big models)
bool CStreaming::ProcessLoadingChannel(int32 chIdx)
{
    tStreamingChannel& ch = ms_channel[chIdx];

    const eCdStreamStatus streamStatus = CdStreamGetStatus(chIdx);
    switch (streamStatus) {
    case eCdStreamStatus::READING_SUCCESS:
        break;

    case eCdStreamStatus::READING:
    case eCdStreamStatus::WAITING_TO_READ:
        return false; // Not ready yet.

    case eCdStreamStatus::READING_FAILURE: {
        // Retry

        ch.m_nCdStreamStatus = streamStatus;
        ch.LoadStatus = eChannelState::ERR;

        if (ms_channelError != -1)
            return false;

        ms_channelError = chIdx;
        RetryLoadFile(chIdx);

        return true;
    }
    }

    const bool isStarted = ch.IsStarted();
    ch.LoadStatus = eChannelState::IDLE;
    if (isStarted) {
        // It's a large model so finish loading it
        int32 bufferOffset = ch.modelStreamingBufferOffsets[0];
        uint8* pFileContents = reinterpret_cast<uint8*>(&ms_pStreamingBuffer[chIdx][STREAMING_SECTOR_SIZE * bufferOffset]);
        FinishLoadingLargeFile(pFileContents, ch.modelIds[0]);
        ch.modelIds[0] = -1;
    } else {
        // Load models individually
        for (uint32 i = 0; i < std::size(ch.modelIds); i++) {
            const int32 modelId = ch.modelIds[i];
            if (modelId == -1)
                continue;

            CBaseModelInfo* baseModelInfo = CModelInfo::GetModelInfo(modelId);
            CStreamingInfo& info = GetInfo(modelId);

            if (!IsModelDFF(modelId)
                || baseModelInfo->GetModelType() != MODEL_INFO_VEHICLE /* It's a DFF, check if its a vehicle */
                || ms_vehiclesLoaded.CountMembers() < desiredNumVehiclesLoaded /* It's a vehicle, so lets check if we can load more */
                || RemoveLoadedVehicle() /* no, so try to remove one, and load this in its place */
                || info.IsMissionOrGameRequired() /* failed, lets check if its absolutely mission critical */
            ) {
                if (!IsModelIPL(modelId))
                    MakeSpaceFor(info.GetCdSize() * STREAMING_SECTOR_SIZE); // IPL's dont require any memory themselves

                const int32 bufferOffsetInSectors = ch.modelStreamingBufferOffsets[i];
                uint8* fileBuffer = reinterpret_cast <uint8*> (&ms_pStreamingBuffer[chIdx][STREAMING_SECTOR_SIZE * bufferOffsetInSectors]);

                // Actually load the model into memory
                ConvertBufferToObject(fileBuffer, modelId);

                if (info.IsLoadingFinishing()) {
                    ch.LoadStatus = eChannelState::STARTED;
                    ch.modelStreamingBufferOffsets[i] = bufferOffsetInSectors;
                    ch.modelIds[i] = modelId;
                    if (i == 0)
                        continue;
                }
                ch.modelIds[i] = -1;
            } else {
                // I think at this point it's guaranteed to be a vehicle (thus its a DFF),
                // with `STREAMING_MISSION_REQUIRED` `STREAMING_GAME_REQUIRED` flags unset.

                const int32 modelTxdIdx = baseModelInfo->m_nTxdIndex;
                RemoveModel(modelId);

                if (info.IsMissionOrGameRequired()) {
                    // Re-request it.
                    // I think this code is unreachable, because
                    // if any of the 2 flags (above) is set this code is never reached.
                    RequestModel(modelId, info.GetFlags());
                } else if (!CTxdStore::GetNumRefs(modelTxdIdx))
                    RemoveTxdModel(modelTxdIdx); // Unload TXD, as it has no refs
            }
        }
    }

    if (ms_bLoadingBigModel) {
        if (ch.LoadStatus != eChannelState::STARTED) {
            ms_bLoadingBigModel = false;
            for (int32 i = 0; i < 16; i++) { // todo: magic number
                ms_channel[1].modelIds[i] = -1;
            }
        }
    }

    return true;
}

// 0x40C1E0
// Call `RemoveModel` on all models in the request list except
// those ones which have either `KEEP_IN_MEMORY` or `PRIORITY_REQUEST` flag(s) set.
void CStreaming::PurgeRequestList() {
    auto info = ms_pEndRequestedList->GetPrev();
    while (info != ms_pStartRequestedList) {
        auto prev = info->GetPrev();
        if (!info->DoKeepInMemory() && !info->IsPriorityRequest())
            RemoveModel(GetModelFromInfo(info));
        info = prev;
    }
}

// 0x40E560
// Reinits the streamer by:
// - Removing all models (except some)
// - Unloading all scripts
// - Deleting all RW objects
void CStreaming::ReInit() {
    CTheScripts::StreamedScripts.ReInitialise();
    FlushRequestList();
    DeleteAllRwObjects();
    RemoveAllUnusedModels();

    for (int32 modelId = 0; modelId < RESOURCE_ID_TOTAL; modelId++)
    {
        CStreamingInfo& streamingInfo = GetInfo(modelId);
        if (streamingInfo.IsMissionRequired())
            SetMissionDoesntRequireModel(modelId);
    }

    for (int32 scmId = 0; scmId < TOTAL_SCM_MODEL_IDS; scmId++) {
        RemoveModel(SCMToModelId(scmId));
    }

    ms_disableStreaming = false;
    ms_currentZoneType = -1;
    m_bBoatsNeeded = false;
    m_bCopBikeLoaded = false;
    m_bDisableCopBikes = false;
    ms_nTimePassedSinceLastCopBikeStreamedIn = 0;

    // Unload special objects
    const auto RemoveModelsInRange = [](auto base, auto count) {
        for (auto modelId = base; modelId < base + count; modelId++) {
            RemoveModel(modelId);
            CModelInfo::GetModelInfo(modelId)->SetModelName(gta_empty_string);
        }
    };
    RemoveModelsInRange(SPECIAL_MODELS_RESOURCE_ID, TOTAL_SPECIAL_MODELS);
    RemoveModelsInRange(CLOTHES_MODELS_RESOURCE_ID, TOTAL_CLOTHES_MODELS);
    RemoveModelsInRange(CUTSCENE_MODELS_RESOURCE_ID, TOTAL_CUTSCENE_MODELS);
}

// 0x5BCCD0
// Loads `stream.ini` settings file
void CStreaming::ReadIniFile() {
    bool bHasDevkitMemory = false;
    FILESTREAM file = CFileMgr::OpenFile("stream.ini", "r");
    for (char* line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file))
    {
        if (*line != '#' && *line)
        {
            char* attribute = strtok(line, " ,\t");
            char* value = strtok(nullptr, " ,\t");
            if (_stricmp(attribute, "memory") != 0 || bHasDevkitMemory)
            {
                if (!_stricmp(attribute, "devkit_memory"))
                {
                    CStreaming::ms_memoryAvailable = atoi(value) * 1024; // kB => bytes conversion
                    bHasDevkitMemory = true;
                }
                else if (!_stricmp(attribute, "vehicles"))
                {
                    CStreaming::desiredNumVehiclesLoaded = atoi(value);
                }
                else if (!_stricmp(attribute, "dontbuildpaths"))
                {
                    //bDontBuildPaths = 1; // unused
                }
                else if (!_stricmp(attribute, "pe_lightchangerate"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE = static_cast<float>(atof(value));
                }
                else if (!_stricmp(attribute, "pe_lightingbasecap"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP = static_cast<float>(atof(value));
                }
                else if (!_stricmp(attribute, "pe_lightingbasemult"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT = static_cast<float>(atof(value));
                }
                else if (!_stricmp(attribute, "pe_leftx"))
                {
                    CPostEffects::m_colourLeftUOffset = (float)atoi(value);
                }
                else if (!_stricmp(attribute, "pe_rightx"))
                {
                    CPostEffects::m_colourRightUOffset = (float)atoi(value);
                }
                else if (!_stricmp(attribute, "pe_topy"))
                {
                    CPostEffects::m_colourTopVOffset = (float)atoi(value);
                }
                else if (!_stricmp(attribute, "pe_bottomy"))
                {
                    CPostEffects::m_colourBottomVOffset = (float)atoi(value);
                }
                else if (!_stricmp(attribute, "pe_bRadiosity"))
                {
                    CPostEffects::m_bRadiosity = atoi(value) != 0;
                }
                else if (!_stricmp(attribute, "def_brightness_pal"))
                {
                    FrontEndMenuManager.m_nBrightness = atoi(value);
                }
            }
            else
            {
                CStreaming::ms_memoryAvailable = atoi(value) << 10;
            }
        }
    }
    CFileMgr::CloseFile(file);
}

// 0x40AFA0
void CStreaming::ReclassifyLoadedCars() {
    CLoadedCarGroup appropriateCarGroup = CPopulation::m_AppropriateLoadedCars;
    CLoadedCarGroup inAppropriateCarGroup = CPopulation::m_InAppropriateLoadedCars;

    CPopulation::m_AppropriateLoadedCars.Clear();
    CPopulation::m_InAppropriateLoadedCars.Clear();

    for (auto& group : { appropriateCarGroup, inAppropriateCarGroup }) {
        for (int32 i = 0; i < group.CountMembers(); i++) {
            int32 modelId = group.GetMember(i);
            if (IsCarModelNeededInCurrentZone(modelId))
                CPopulation::m_AppropriateLoadedCars.AddMember(modelId);
            else
                CPopulation::m_InAppropriateLoadedCars.AddMember(modelId);
        }
    }
}

// 0x40CF80
// Remove majority of loaded models
void CStreaming::RemoveAllUnusedModels() {
    // Remove all possibly removable vehicles
    for (int32 i = 0; i < 50; i++) { // TODO: Magic number
        RemoveLoadedVehicle();
    }

    // Remove majority of models with no refs
    for (int32 modelId = 1000; IsModelDFF(modelId); modelId++) {
        CStreamingInfo& streamingInfo = GetInfo(modelId);
        if (streamingInfo.IsLoaded() && !CModelInfo::GetModelInfo(modelId)->m_nRefCount) {
            RemoveModel(modelId);
            streamingInfo.ClearAllFlags();
        }
    }
}

// 0x4093B0
// Remove all BIG building's RW objects and models
void CStreaming::RemoveBigBuildings() {
    for (int32 i = CPools::ms_pBuildingPool->GetSize() - 1; i >= 0; i--) {
        CBuilding* building = CPools::ms_pBuildingPool->GetAt(i);
        if (building && building->m_bIsBIGBuilding && !building->m_bImBeingRendered) {
            building->DeleteRwObject();
            if (!CModelInfo::GetModelInfo(building->m_nModelIndex)->m_nRefCount)
                RemoveModel(building->m_nModelIndex);
        }
    }
}

// 0x4094B0
// Remove buildings, objects and dummies not in the current area (as in CWorld::currArea)
void CStreaming::RemoveBuildingsNotInArea(eAreaCodes areaCode) {
    for (int32 i = CPools::ms_pBuildingPool->GetSize() - 1; i >= 0; i--) {
        CBuilding* building = CPools::ms_pBuildingPool->GetAt(i);
        if (building && building->m_pRwObject) {
            if (!building->IsInCurrentAreaOrBarberShopInterior()) {
                if (!building->m_bImBeingRendered && !building->m_bIsBIGBuilding)
                    building->DeleteRwObject();
            }
        }
    }
    for (int32 i = CPools::ms_pObjectPool->GetSize() - 1; i >= 0; i--) {
        CObject* obj = CPools::ms_pObjectPool->GetAt(i);
        if (obj && obj->m_pRwObject) {
            if (obj->IsInCurrentAreaOrBarberShopInterior()) {
                if (!obj->m_bImBeingRendered && obj->m_nObjectType == eObjectType::OBJECT_GAME)
                    obj->DeleteRwObject();
            }
        }
    }
    for (int32 i = CPools::ms_pDummyPool->GetSize() - 1; i >= 0; i--) {
        CDummy* dummy = CPools::ms_pDummyPool->GetAt(i);
        if (dummy && dummy->m_pRwObject) {
            if (dummy->IsInCurrentAreaOrBarberShopInterior()) {
                if (!dummy->m_bImBeingRendered)
                    dummy->DeleteRwObject();
            }
        }
    }
}

// 0x4080F0
void CStreaming::RemoveCarModel(int32 modelId) {
    CPopulation::m_AppropriateLoadedCars.RemoveMember(modelId);
    CPopulation::m_InAppropriateLoadedCars.RemoveMember(modelId);
    CPopulation::m_LoadedBoats.RemoveMember(modelId);
    for (CLoadedCarGroup& group : CPopulation::m_LoadedGangCars) {
        group.RemoveMember(modelId);
    }
    ms_vehiclesLoaded.RemoveMember(modelId);
    CPopulation::RemoveSpecificDriverModelsForCar(modelId);
}

// 0x40B080
void CStreaming::RemoveCurrentZonesModels() {
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        if (modelId >= 0) {
            SetModelAndItsTxdDeletable(modelId);
            ms_pedsLoaded[i] = -1;
        }
    }
    ms_numPedsLoaded = 0;
    RequestModel(MODEL_MALE01, STREAMING_GAME_REQUIRED);
    for (int32 gangId = 0; gangId < TOTAL_GANGS; gangId++) {
        ePopcycleGroup popcycleGroup = static_cast<ePopcycleGroup>(gangId + POPCYCLE_GROUP_BALLAS);
        ePopcyclePedGroup pedGroupId = CPopulation::GetPedGroupId(popcycleGroup, 0);
        for (int32 i = 0; i < 5; i++) {
            int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, i);
            if (modelId != CPopulation::m_defaultCarGroupModelId) {
                SetModelAndItsTxdDeletable(modelId);
            }
        }
    }
    ms_currentZoneType = -1;
    ms_loadedGangs = 0;
    ms_loadedGangCars = 0;
}

// 0x40BE60
void CStreaming::RemoveDodgyPedsFromRandomSlots() {
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        switch (modelId)
        {
        case MODEL_VWFYST1:
        case MODEL_VBFYST2:
        case MODEL_VHFYST3:
        case MODEL_SBFYSTR:
        case MODEL_SWFYSTR:
            SetModelAndItsTxdDeletable(modelId);
            ms_pedsLoaded[i] = -1;
            ms_numPedsLoaded--;
            break;
        }
    }
}

// 0x409710
void CStreaming::RemoveEntity(CLink<CEntity*>* streamingLink)
{
    if (streamingLink) {
        if (streamingLink == ms_renderEntityLink)
            ms_renderEntityLink = ms_renderEntityLink->prev;
        ms_rwObjectInstances.Remove(streamingLink);
    }
}

// 0x40B3A0
void CStreaming::RemoveInappropriatePedModels() {
    if (CPopCycle::m_pCurrZoneInfo) {
        for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
            int32 modelId = ms_pedsLoaded[i];
            if (modelId >= 0 && !CPopCycle::IsPedAppropriateForCurrentZone(modelId)) {
                SetModelAndItsTxdDeletable(modelId);
                ms_pedsLoaded[i] = -1;
                ms_numPedsLoaded--;
            }
        }
    }
    else {
        for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
            int32 modelId = ms_pedsLoaded[i];
            if (modelId >= 0) {
                SetModelAndItsTxdDeletable(modelId);
                ms_pedsLoaded[i] = -1;
            }
        }
        ms_numPedsLoaded = 0;
    }
}

// 0x40CFD0
// The name is misleading: It just removes the first model with no references.
bool CStreaming::RemoveLeastUsedModel(uint32 streamingFlags) {
    auto streamingInfo = ms_pEndLoadedList->GetPrev();
    for (; streamingInfo != ms_startLoadedList; streamingInfo = streamingInfo->GetPrev()) {
        const auto modelId = GetModelFromInfo(streamingInfo);
        if (!streamingInfo->AreAnyFlagsSetOutOf(streamingFlags)) {
            switch (GetModelType(modelId)) {
            case eModelType::DFF: {
                if (!CModelInfo::ms_modelInfoPtrs[modelId]->m_nRefCount) {
                    RemoveModel(modelId);
                    return true;
                }
                break;
            }
            case eModelType::TXD: {
                const int32 txdId = ModelIdToTXD(modelId);
                if (!CTxdStore::GetNumRefs(txdId) && !AreTexturesUsedByRequestedModels(txdId)) {
                    RemoveModel(modelId);
                    return true;
                }
                break;
            }
            case eModelType::IFP: {
                const int32 animBlockId = ModelIdToIFP(modelId);
                if (!CAnimManager::GetNumRefsToAnimBlock(animBlockId) && !AreAnimsUsedByRequestedModels(animBlockId)) {
                    RemoveModel(modelId);
                    return true;
                }
                break;
            }
            case eModelType::SCM: {
                const int32 scmId = ModelIdToSCM(modelId);
                if (!CTheScripts::StreamedScripts.m_aScripts[scmId].m_nStatus) {
                    RemoveModel(modelId);
                    return true;
                }
                break;
            }
            }
        }
    }

    // todo: make more readable
    if (TheCamera.GetPosition().z - TheCamera.CalculateGroundHeight(eGroundHeightType::ENTITY_BOUNDINGBOX_BOTTOM) > 50.0f && (
                ms_numPedsLoaded > 4 && RemoveLoadedZoneModel() || ms_vehiclesLoaded.CountMembers() > 4 && RemoveLoadedVehicle()
            )
        || !ms_bLoadingScene && (
                DeleteLeastUsedEntityRwObject(false, streamingFlags)
                || ms_numPedsLoaded > 4 && RemoveLoadedZoneModel()
                || (ms_vehiclesLoaded.CountMembers() > 7 || !CGame::CanSeeOutSideFromCurrArea() && ms_vehiclesLoaded.CountMembers() > 4) && RemoveLoadedVehicle()
            )
        || DeleteLeastUsedEntityRwObject(true, streamingFlags)
        || (
                ms_vehiclesLoaded.CountMembers() > 7 || !CGame::CanSeeOutSideFromCurrArea() && ms_vehiclesLoaded.CountMembers() > 4
            ) && RemoveLoadedVehicle()
        || ms_numPedsLoaded > 4 && RemoveLoadedZoneModel())
    {
        return true;
    }
    return false;
}

bool CStreaming::CarIsCandidateForRemoval(int32 modelId) {
    CStreamingInfo& info = GetInfo(modelId);
    return CModelInfo::GetModelInfo(modelId)->m_nRefCount == 0 && !info.IsMissionOrGameRequired() && info.IsLoaded();
}

// 0x40C020
// Remove most of loaded vehicle models (the ones with neither `GAME/MISSION_REQUIRED` flags set and no references)
bool CStreaming::RemoveLoadedVehicle() {
    for (int32 i = 0; i < CPopulation::m_InAppropriateLoadedCars.CountMembers(); i++) {
        const auto modelId = CPopulation::m_InAppropriateLoadedCars.GetMember(i);
        if (CarIsCandidateForRemoval(modelId)) {
            RemoveModel(modelId);
            return true;
        }
    }

    {
        const auto numBoatsNeeded = CStreaming::m_bBoatsNeeded ? 2 : 0;
        if (numBoatsNeeded < CPopulation::m_LoadedBoats.CountMembers()) {
            for (int32 i = 0; i < CPopulation::m_LoadedBoats.CountMembers(); i++) {
                int32 modelId = CPopulation::m_LoadedBoats.GetMember(i);
                if (CarIsCandidateForRemoval(modelId)) {
                    RemoveModel(modelId);
                    return true;
                }
            }
        }
    }

    auto appropriateLoadedCars = CPopulation::m_AppropriateLoadedCars;
    appropriateLoadedCars.SortBasedOnUsage();
    for (int32 i = 0; i < appropriateLoadedCars.CountMembers(); i++) {
        int32 modelId = appropriateLoadedCars.GetMember(i);
        if (CarIsCandidateForRemoval(modelId)) {
            RemoveModel(modelId);
            return true;
        }
    }
    return false;
}

bool CStreaming::ZoneModelIsCandidateForRemoval(int32 modelId) {
    CStreamingInfo& info = GetInfo(modelId);
    return CModelInfo::GetModelInfo(modelId)->m_nRefCount == 0 && !info.IsMissionOrGameRequired() && info.IsLoaded();
}

// 0x40B340
bool CStreaming::RemoveLoadedZoneModel() {
    if (CStreaming::ms_currentZoneType == -1 || CCheat::IsZoneStreamingAllowed())
        return false;

    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        if (modelId >= 0 && ZoneModelIsCandidateForRemoval(modelId)) {
            RemoveModel(modelId);
            return true;
        }
    }
    return false;
}

// 0x4089A0
void CStreaming::RemoveModel(int32 modelId)
{
    CStreamingInfo& streamingInfo = GetInfo(modelId);;
    if (streamingInfo.m_nLoadState == LOADSTATE_NOT_LOADED)
        return;

    if (streamingInfo.IsLoaded()) {
        switch (GetModelType((modelId))) {
        case eModelType::DFF: {
            CBaseModelInfo* modelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
            modelInfo->DeleteRwObject();
            switch (modelInfo->GetModelType()) {
            case MODEL_INFO_PED: {
                for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
                    if (ms_pedsLoaded[i] == modelId) {
                        ms_pedsLoaded[i] = -1;
                        ms_numPedsLoaded--;
                    }
                }
                break;
            }
            case MODEL_INFO_VEHICLE: {
                RemoveCarModel(modelId);
                break;
            }
            }
            break;
        } 
        case eModelType::TXD: {
            CTxdStore::RemoveTxd(ModelIdToTXD(modelId));
            break;
        } 
        case eModelType::COL: {
            CColStore::RemoveCol(ModelIdToCOL(modelId));
            break;
        } 
        case eModelType::IPL: {
            CIplStore::RemoveIpl(ModelIdToIPL(modelId));
            break;
        } 
        case eModelType::DAT: {
            ThePaths.UnLoadPathFindData(ModelIdToDAT(modelId));
            break;
        } 
        case eModelType::IFP: {
            CAnimManager::RemoveAnimBlock(ModelIdToIFP(modelId));
            break;
        } 
        case eModelType::SCM: {
            CTheScripts::StreamedScripts.RemoveStreamedScriptFromMemory(ModelIdToSCM(modelId));
            break;
        }
        }
        ms_memoryUsed -= STREAMING_SECTOR_SIZE * streamingInfo.GetCdSize();
    }

    if (streamingInfo.m_nNextIndex == -1) {
        if (streamingInfo.IsBeingRead()) {
            for (int32 i = 0; i < 16; i++) {
                for (int32 channelId = 0; channelId < 2; channelId++) {
                    if (ms_channel[channelId].modelIds[i] == modelId)
                        ms_channel[channelId].modelIds[i] = -1;
                }
            }
        }
    } else {
        if (streamingInfo.IsRequested()) {
            ms_numModelsRequested--;
            if (streamingInfo.IsPriorityRequest()) {
                streamingInfo.ClearFlags(STREAMING_PRIORITY_REQUEST);
                ms_numPriorityRequests--;
            }
        }
        streamingInfo.RemoveFromList();
    }

    if (streamingInfo.IsLoadingFinishing()) {
        switch (GetModelType((modelId))) {
        case eModelType::DFF:
            RpClumpGtaCancelStream();
            break;
        case eModelType::TXD:
            CTxdStore::RemoveTxd(ModelIdToTXD(modelId));
            break;
        case eModelType::COL:
            CColStore::RemoveCol(ModelIdToCOL(modelId));
            break;
        case eModelType::IPL:
            CIplStore::RemoveIpl(ModelIdToIPL(modelId));
            break;
        case eModelType::IFP:
            CAnimManager::RemoveAnimBlock(ModelIdToIFP(modelId));
            break;
        case eModelType::SCM:
            CTheScripts::StreamedScripts.RemoveStreamedScriptFromMemory(ModelIdToSCM(modelId));
            break;
        }
    }

    streamingInfo.m_nLoadState = LOADSTATE_NOT_LOADED;
}

void CStreaming::RemoveUnusedModelsInLoadedList() {
    // empty function
}

// 0x40C180
void CStreaming::RemoveTxdModel(int32 modelId)
{
    RemoveModel(TXDToModelId(modelId));
}

// 0x40E120
void CStreaming::MakeSpaceFor(int32 memoryToCleanInBytes)
{
    while (ms_memoryUsed >= ms_memoryAvailable - memoryToCleanInBytes) {
        if (!RemoveLeastUsedModel(STREAMING_LOADING_SCENE)) {
            DeleteRwObjectsBehindCamera(ms_memoryAvailable - memoryToCleanInBytes);
            return;
        }
    }
}

// 0x40C270
// Similar to the other overload but also checks if model is:
// - In the rectangle defined by `minX, minY`, `maxX, maxY`
// - In the radius of min(radius, <model draw distance> * <cam lod dist multiplier>)
void CStreaming::ProcessEntitiesInSectorList(CPtrList& list, float posX, float posY, float minX, float minY, float maxX, float maxY, float radius, int32 streamingflags) {
    CVector2D position(posX, posY);
    for (CPtrNode* node = list.GetNode(); node; node = node->m_next) {
        CEntity* entity = reinterpret_cast<CEntity*>(node->m_item);

        if (entity->m_nScanCode == GetCurrentScanCode())
            continue;
        entity->m_nScanCode = GetCurrentScanCode();

        const uint16 modelId = entity->m_nModelIndex;
        if (CStreaming::GetInfo(modelId).IsLoaded())
            continue;
        if (entity->m_bStreamingDontDelete)
            continue;
        if (!entity->IsInCurrentAreaOrBarberShopInterior())
            continue;
        if (entity->m_bDontStream || !entity->m_bIsVisible)
            continue;

        // Check time for models visible only in specific time intervals
        CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
        CTimeInfo* timeInfo = modelInfo->GetTimeInfo();
        if (timeInfo && !timeInfo->IsVisibleNow())
            continue;

        const CVector& entityPos = entity->GetPosition();
        if (!IsPointInRect2D(entityPos, { minX, minY }, { maxX, maxY }))
            continue;

        const float drawDistanceRadius = TheCamera.m_fLODDistMultiplier * modelInfo->m_fDrawDistance;
        if (!IsPointInCircle2D(entityPos, position, std::min(drawDistanceRadius, radius)))
            continue;

        if (modelInfo->m_pRwObject && !entity->m_pRwObject)
            entity->CreateRwObject();

        RequestModel(entity->m_nModelIndex, streamingflags);    
    }
}

// 0x40C450
// Load all required models in the given sector list
// unlike the above function (other overload) this one doesn't do radius checks
// just requests all models necessary (if they meet the conditions).
void CStreaming::ProcessEntitiesInSectorList(CPtrList& list, int32 streamingFlags) {
    for (CPtrNode* node = list.GetNode(); node; node = node->m_next) {
        CEntity* entity = reinterpret_cast<CEntity*>(node->m_item);
        if (entity->m_nScanCode == GetCurrentScanCode())
            continue;
        entity->m_nScanCode = GetCurrentScanCode();

        const uint16 modelId = entity->m_nModelIndex;
        if (CStreaming::GetInfo(modelId).IsLoaded())
            continue;
        if (entity->m_bStreamingDontDelete)
            continue;
        if (!entity->IsInCurrentAreaOrBarberShopInterior())
            continue;
        if (entity->m_bDontStream || !entity->m_bIsVisible)
            continue;

        // Check time for models visible only in specific time intervals
        CBaseModelInfo* modelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
        CTimeInfo* timeInfo = modelInfo->GetTimeInfo();
        if (timeInfo && !CClock::GetIsTimeInRange(timeInfo->GetTimeOn(), timeInfo->GetTimeOff()))
            continue;

        if (modelInfo->m_pRwObject && !entity->m_pRwObject)
            entity->CreateRwObject();

        RequestModel(entity->m_nModelIndex, streamingFlags);
    }
}

// 0x4076C0
void CStreaming::RetryLoadFile(int32 chIdx) {
    printf("CStreaming::RetryLoadFile called!\n"); // NOTSA

    if (ms_channelError == -1)
        return CLoadingScreen::Continue();

    CLoadingScreen::Pause(); // empty function
    if (ms_channelError == -1)
        return;

    tStreamingChannel& ch = CStreaming::ms_channel[chIdx];
    while (true) {
        switch (ch.LoadStatus) {
        case eChannelState::READING: {
            if (ProcessLoadingChannel(chIdx)) {
                if (ch.IsStarted())
                    ProcessLoadingChannel(chIdx);

                ms_channelError = -1; // Clear error code
                return CLoadingScreen::Continue();
            }
            break;
        }
        case eChannelState::ERR: {
            ch.totalTries++;

            // Keep in mind that `CdStreamGetStatus` changes the stream status.
            const eCdStreamStatus status = CdStreamGetStatus(chIdx);
            if ((status == eCdStreamStatus::READING || status == eCdStreamStatus::WAITING_TO_READ) &&
                (status != eCdStreamStatus::READING || CdStreamGetStatus(chIdx) != eCdStreamStatus::READING)
            ) {
                break; // Otherwise fallthrough, and do stream read
            }

            [[fallthrough]];
        }
        case eChannelState::IDLE: {
            uint8* pBuffer = ms_pStreamingBuffer[chIdx];
            CdStreamRead(chIdx, pBuffer, ch.offsetAndHandle, ch.sectorCount);
            ch.LoadStatus = eChannelState::READING;
            ch.iLoadingLevel = -600;
            break;
        }
        }

        if (ms_channelError == -1)
            return CLoadingScreen::Continue();
    }
}

// 0x40E3A0
void CStreaming::LoadRequestedModels()
{
    static int32 currentChannel = 0;
    if (ms_bLoadingBigModel)
        currentChannel = 0;

    const tStreamingChannel& channel = ms_channel[currentChannel];
    if (channel.LoadStatus != eChannelState::IDLE)
        ProcessLoadingChannel(currentChannel);

    if (!ms_bLoadingBigModel) {
        const int32 otherChannelId = 1 - currentChannel;
        if (ms_channel[otherChannelId].LoadStatus == eChannelState::IDLE)
            RequestModelStream(otherChannelId);

        if (channel.LoadStatus == eChannelState::IDLE && !ms_bLoadingBigModel)
            RequestModelStream(currentChannel);
    }

    if (channel.LoadStatus != eChannelState::STARTED)
        currentChannel = 1 - currentChannel;
}

// 0x40E4E0
// Removes all models found in the `requested` list
void CStreaming::FlushRequestList()
{
    // Have to do it like this, because current iterator is invalidated when `RemoveModel` is called
    for (auto it = ms_pStartRequestedList->GetNext(); it != ms_pEndRequestedList;) {
        auto next = it->GetNext();
        RemoveModel(GetModelFromInfo(it));
        it = next;
    }
    FlushChannels();
}

// 0x408000
bool CStreaming::AddToLoadedVehiclesList(int32 modelId)
{
    auto vehicleModelInfo = static_cast<CVehicleModelInfo*>(CModelInfo::ms_modelInfoPtrs[modelId]);
    vehicleModelInfo->m_nTimesUsed = 0;

    // Add it to the appropriate car group
    {
        CLoadedCarGroup* loadedCarGroup = nullptr;
        for (int32 i = 0; i < CPopulation::m_nNumCarsInGroup[POPCYCLE_CARGROUP_BOATS]; i++) {
            if (CPopulation::m_CarGroups[POPCYCLE_CARGROUP_BOATS][i] == modelId) {
                loadedCarGroup = &CPopulation::m_LoadedBoats;
                break;
            }
        }
        if (!loadedCarGroup) {
            loadedCarGroup = &CPopulation::m_AppropriateLoadedCars;
            if (!IsCarModelNeededInCurrentZone(modelId))
                loadedCarGroup = &CPopulation::m_InAppropriateLoadedCars;
        }
        loadedCarGroup->AddMember(modelId);
    }

    // Add it to gang's loaded vehicles
    for (int32 gangId = 0; gangId < TOTAL_GANGS; gangId++) {
        const int32 groupId = gangId + POPCYCLE_CARGROUP_BALLAS;
        for (int32 i = 0; i < CPopulation::m_nNumCarsInGroup[groupId]; i++) {
            if (CPopulation::m_CarGroups[groupId][i] == modelId) {
                CPopulation::m_LoadedGangCars[gangId].AddMember(modelId);
                break;
            }
        }
    }

    ms_vehiclesLoaded.AddMember(modelId);

    return true;
}

// 0x407D50
int32 CStreaming::GetDefaultCabDriverModel()
{
    static int32 randomIndex = 0;
    const int32 defaultCabDriverModels[7] = {
        MODEL_BMOCD,
        MODEL_WMYCD1,
        MODEL_SBMOCD,
        MODEL_SWMOCD,
        MODEL_VBMOCD,
        MODEL_VWMYCD,
        -1
    };
    const int32 modelId = defaultCabDriverModels[randomIndex];
    if (CStreaming::GetInfo(modelId).m_nLoadState == eStreamingLoadState::LOADSTATE_NOT_LOADED) {
        if (CTheZones::m_CurrLevel != eLevelName::LEVEL_NAME_COUNTRY_SIDE)
            randomIndex = CGeneral::GetRandomNumberInRange(0, 2 * CTheZones::m_CurrLevel);
        return defaultCabDriverModels[randomIndex];
    }
    return modelId;
}

// 0x407C50
int32 CStreaming::GetDefaultCopCarModel(int32 ignoreLvpd1Model) {
    int32 carModelId = ms_DefaultCopBikeModel;
    if (!m_bCopBikeLoaded
        || ignoreLvpd1Model
        || !GetInfo(ms_DefaultCopBikerModel).IsLoaded()
        || !GetInfo(ms_DefaultCopBikeModel).IsLoaded())
    {
        carModelId = ms_aDefaultCopCarModel[CTheZones::m_CurrLevel];

        if (!GetInfo(ms_aDefaultCopModel[CTheZones::m_CurrLevel]).IsLoaded()
         || !GetInfo(carModelId).IsLoaded()
        ) {
            for (int32 i = 0; i < (ignoreLvpd1Model ? 3 : 4); i++) {
                if (GetInfo(ms_aDefaultCopModel[i]).IsLoaded()
                 && GetInfo(ms_aDefaultCopCarModel[i]).IsLoaded()
                ) {
                    return ms_aDefaultCopCarModel[i];
                }
            }
            return -1;
        }
    }
    return carModelId;
}

// 0x407C00
// Returns a loaded cop model.
int32 CStreaming::GetDefaultCopModel()
{
    // Try current level's model
    const int32 modelId = ms_aDefaultCopModel[CTheZones::m_CurrLevel];
    if (GetInfo(modelId).IsLoaded())
        return modelId;

    // Try all other level's model
    for (int32 i = 0; i < 4; i++) {
        if (GetInfo(ms_aDefaultCopModel[i]).IsLoaded())
            return ms_aDefaultCopModel[i];
    }

    // No cop model loaded
    return -1;
}

// 0x407D40
int32 CStreaming::GetDefaultFiremanModel() {
    return ms_aDefaultFiremanModel[CTheZones::m_CurrLevel];
}

// 0x407D20
int32 CStreaming::GetDefaultMedicModel() {
    return ms_aDefaultMedicModel[CTheZones::m_CurrLevel];
}

// 0x5B9020
void CStreaming::Init()
{
    Init2();
}

// 0x5B8AD0
void CStreaming::Init2()
{
    for (int32 modelId = 0; modelId < RESOURCE_ID_TOTAL; modelId++) {
        GetInfo(modelId).Init();
    }
    CStreamingInfo::ms_pArrayBase = &GetInfo(0);
    ms_startLoadedList = &GetInfo(RESOURCE_ID_INTERNAL_1);
    ms_pEndLoadedList = &GetInfo(RESOURCE_ID_INTERNAL_2);
    ms_pStartRequestedList = &GetInfo(RESOURCE_ID_INTERNAL_3);
    ms_pEndRequestedList = &GetInfo(RESOURCE_ID_INTERNAL_4);
    GetInfo(RESOURCE_ID_INTERNAL_1).m_nNextIndex = RESOURCE_ID_INTERNAL_2;
    GetInfo(RESOURCE_ID_INTERNAL_1).m_nPrevIndex = -1;
    GetInfo(RESOURCE_ID_INTERNAL_2).m_nNextIndex = -1;
    GetInfo(RESOURCE_ID_INTERNAL_2).m_nPrevIndex = RESOURCE_ID_INTERNAL_1;
    GetInfo(RESOURCE_ID_INTERNAL_3).m_nNextIndex = RESOURCE_ID_INTERNAL_4;
    GetInfo(RESOURCE_ID_INTERNAL_3).m_nPrevIndex = -1;
    GetInfo(RESOURCE_ID_INTERNAL_4).m_nNextIndex = -1;
    GetInfo(RESOURCE_ID_INTERNAL_4).m_nPrevIndex = RESOURCE_ID_INTERNAL_3;
    // ms_oldSectorX = 0; // Unused
    // ms_oldSectorY = 0; // Unused
    GetInfo(MODEL_TEMPCOL_DOOR1).m_nLoadState = LOADSTATE_LOADED;
    GetInfo(MODEL_TEMPCOL_BUMPER1).m_nLoadState = LOADSTATE_LOADED;
    GetInfo(MODEL_TEMPCOL_PANEL1).m_nLoadState = LOADSTATE_LOADED;
    GetInfo(MODEL_TEMPCOL_BONNET1).m_nLoadState = LOADSTATE_LOADED;
    GetInfo(MODEL_TEMPCOL_BOOT1).m_nLoadState = LOADSTATE_LOADED;
    GetInfo(MODEL_TEMPCOL_WHEEL1).m_nLoadState = LOADSTATE_LOADED;
    GetInfo(MODEL_TEMPCOL_BODYPART1).m_nLoadState = LOADSTATE_LOADED;
    GetInfo(MODEL_TEMPCOL_BODYPART2).m_nLoadState = LOADSTATE_LOADED;
    ms_streamingBufferSize = 0;
    ms_disableStreaming = false;
    ms_memoryUsed = 0;
    ms_channelError = -1;
    ms_bLoadingBigModel = false;
    ms_bEnableRequestListPurge = true;
    m_bStreamHarvesterModelsThisFrame = false;
    m_bHarvesterModelsRequested = false;
    for (int32 channelId = 0; channelId < 2; channelId++) {
        tStreamingChannel& streamingChannel = ms_channel[channelId];
        streamingChannel.LoadStatus = eChannelState::IDLE;
        for (int32 i = 0; i < 16; i++) {
            streamingChannel.modelIds[i] = -1;
        }
    }
    for (int32 i = 0; i < TOTAL_DFF_MODEL_IDS; i++) {
        const int32 modelId = DFFToModelId(i);
        auto baseModelnfo = CModelInfo::ms_modelInfoPtrs[modelId];
        CStreamingInfo& streamingInfo = GetInfo(modelId);
        if (baseModelnfo && baseModelnfo->m_pRwObject) {
            auto pAtomicModelInfo = baseModelnfo->AsAtomicModelInfoPtr();
            streamingInfo.ClearAllFlags();
            streamingInfo.SetFlags(STREAMING_GAME_REQUIRED);
            streamingInfo.m_nLoadState = LOADSTATE_LOADED;
            if (pAtomicModelInfo)
                pAtomicModelInfo->m_nAlpha = 255;
        }
    }
    for (int32 i = 0; i < TOTAL_TXD_MODEL_IDS; i++) {
        const int32 modelId = TXDToModelId(i);
        CStreamingInfo& streamingInfo = GetInfo(modelId);
        TxdDef* txd = CTxdStore::ms_pTxdPool->GetAt(i);
        if (txd && txd->m_pRwDictionary) {
            streamingInfo.m_nLoadState = LOADSTATE_LOADED;
        }
    }
    ms_vehiclesLoaded.Clear();
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        ms_pedsLoaded[i] = -1;
    }
    ms_numPedsLoaded = 0;
    for (int32 i = 0; i < 18; i++) {
        ms_NextPedToLoadFromGroup[i] = 0;
    }
    ms_pExtraObjectsDir = new CDirectory(550);
    ms_currentZoneType = -1;
    ms_loadedGangs = 0;
    ms_lastCullZone = -1;
    ms_numPriorityRequests = 0;
    CTheScripts::StreamedScripts.Initialise();
    // ms_streamingBufferSize is 0 at this point.
    // After calling LoadCdDirectory, ms_streamingBufferSize will contain the maximum number
    // of memory blocks/sectors used for a streaming model, like txd, dff, col, ipl, scm, etc.
    // The size of one streaming sector is STREAMING_BLOCK_SIZE by default.
    LoadCdDirectory();
    if (ms_streamingBufferSize & 1) // check if the value of ms_streamingBufferSize is odd
        ms_streamingBufferSize++; // make it even by adding 1

    // Since gta sa streamer runs on a secondary thread, if two models can fit
    // inside this one big buffer (one model goes in the 1st half of the buffer, the other
    // model goes in the second half), it will load the two models together.
    // Hence ms_pStreamingBuffer[0] is used by 1st channel and ms_pStreamingBuffer[1] is used by the 2nd channel.
    // If a model is big, and it cannot fit in half of the buffer, then the entire buffer is used,
    // and the model is loaded alone.

    // Here, ms_streamingBufferSize * STREAMING_BLOCK_SIZE = maximum size in bytes that a streaming model can possibly have.
    const uint32 maximumModelSizeInBytes = ms_streamingBufferSize * STREAMING_SECTOR_SIZE;
    ms_pStreamingBuffer[0] = CMemoryMgr::MallocAlign(maximumModelSizeInBytes, STREAMING_SECTOR_SIZE);
    ms_streamingBufferSize /= 2;
    ms_pStreamingBuffer[1] = &ms_pStreamingBuffer[0][STREAMING_SECTOR_SIZE * ms_streamingBufferSize];
    ms_memoryAvailable = 512 * 1024 * 1024;
    desiredNumVehiclesLoaded = 22;
    ms_rwObjectInstances.Init(12000);
    ms_bIsInitialised = true;
}

// 0x4083C0
void CStreaming::InitImageList() {
    for (auto& file : ms_files) {
        file = {};
    }
    AddImageToList("MODELS\\GTA3.IMG", true);
    AddImageToList("MODELS\\GTA_INT.IMG", true);
}

// 0x4084F0
void CStreaming::InstanceLoadedModels(CVector const& point) {
    float fRadius = 80.0f;
    if (!CGame::CanSeeOutSideFromCurrArea())
        fRadius = 40.0f;

    const float minX = point.x - fRadius;
    const float maxX = point.x + fRadius;
    const float minY = point.y - fRadius;
    const float maxY = point.y + fRadius;
    int32 startSectorX = std::max(CWorld::GetSectorX(minX), 0);
    int32 startSectorY = std::max(CWorld::GetSectorY(minY), 0);
    int32 endSectorX = std::min(CWorld::GetSectorX(maxX), MAX_SECTORS_X - 1);
    int32 endSectorY = std::min(CWorld::GetSectorY(maxY), MAX_SECTORS_Y - 1);
    for (int32 sectorY = startSectorY; sectorY <= endSectorY; ++sectorY) {
        for (int32 sectorX = startSectorX; sectorX <= endSectorX; ++sectorX) {
            CRepeatSector* pRepeatSector = GetRepeatSector(sectorX, sectorY);
            CSector* pSector = GetSector(sectorX, sectorY);
            InstanceLoadedModelsInSectorList(pSector->m_buildings);
            InstanceLoadedModelsInSectorList(pRepeatSector->m_lists[REPEATSECTOR_OBJECTS]);
            InstanceLoadedModelsInSectorList(pSector->m_dummies);
        }
    }
}

void CStreaming::InstanceLoadedModelsInSectorList(CPtrList& list)
{
    for (CPtrNode* node = list.GetNode(); node; node = node->m_next) {
        CEntity* entity = reinterpret_cast<CEntity*>(node->m_item);
        if (entity->IsInCurrentAreaOrBarberShopInterior() && !entity->m_pRwObject)
            entity->CreateRwObject();
    }
}

// 0x407DD0
bool CStreaming::IsCarModelNeededInCurrentZone(int32 modelId) {
    CZoneInfo* currentZoneInfo = CPopCycle::m_pCurrZoneInfo;
    if (!CPopCycle::m_pCurrZoneInfo)
        return false;

    // Check cheats
    if (CCheat::m_aCheatsActive[CHEAT_BEACH_PARTY])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_BEACHFOLK, modelId);

    if (CCheat::m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_FARMERS, modelId);

    if (CCheat::m_aCheatsActive[CHEAT_CHEAP_TRAFFIC])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT1, modelId);

    if (CCheat::m_aCheatsActive[CHEAT_FAST_TRAFFIC])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT2, modelId);

    if (CCheat::m_aCheatsActive[CHEAT_NINJA_THEME])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT3, modelId);

    if (CCheat::m_aCheatsActive[CHEAT_FUNHOUSE_THEME])
        return CPopulation::DoesCarGroupHaveModelId(POPCYCLE_CARGROUP_CHEAT4, modelId);

    // Check in current popcycle
    for (int32 groupId = 0; groupId < POPCYCLE_TOTAL_GROUP_PERCS; groupId++) {
        if (CPopCycle::GetCurrentPercTypeGroup(groupId, currentZoneInfo->zonePopulationType) &&
            CPopulation::DoesCarGroupHaveModelId(groupId, modelId)) {
            return true;
        }
    }

    // Check gangs
    for (int32 groupId = 0; groupId < TOTAL_GANGS; groupId++) {
        if (currentZoneInfo->GangDensity[groupId] != 0 && CPopulation::DoesCarGroupHaveModelId(groupId, modelId))
            return true;
    }

    return false;
}

// 0x407600
bool CStreaming::IsInitialised() {
    return ms_bIsInitialised;
}

// 0x407800
bool CStreaming::IsObjectInCdImage(int32 modelId) {
    return GetInfo(modelId).GetCdSize() != 0;
}

// 0x5D29A0
void CStreaming::Save() {
    plugin::Call<0x5D29A0>();
}

// 0x407A30
void CStreaming::SetLoadVehiclesInLoadScene(bool bEnable) {
    ms_bLoadVehiclesInLoadScene = bEnable;
}

// 0x48B570
void CStreaming::SetMissionDoesntRequireAnim(int32 slot) {
    SetMissionDoesntRequireModel(IFPToModelId(slot));
}

// 0x409C90
void CStreaming::SetMissionDoesntRequireModel(int32 nDFForTXDModel) {
    const auto ProcessOne = [](auto modelId) {
        CStreamingInfo& streamingInfo = CStreaming::GetInfo(modelId);
        streamingInfo.ClearFlags(STREAMING_MISSION_REQUIRED);
        if (!streamingInfo.IsGameRequired()) {
            if (streamingInfo.IsLoaded()) {
                if (!streamingInfo.InList())
                    streamingInfo.AddToList(ms_startLoadedList);
            } else if (!streamingInfo.DoKeepInMemory()) {
                RemoveModel(modelId);
            }
        }
    };

    ProcessOne(nDFForTXDModel);
    if (IsModelDFF(nDFForTXDModel)) 
        ProcessOne(TXDToModelId(CModelInfo::ms_modelInfoPtrs[nDFForTXDModel]->m_nTxdIndex)); // Process TXD of DFF

    /* Origianl code:
    for (int32 i = modelId; ; i = CModelInfo::ms_modelInfoPtrs[i]->TXDToModelId(m_nTxdIndex)) {
        CStreamingInfo& streamingInfo = CStreaming::GetInfo(i);
        streamingInfo.m_nFlags &= ~STREAMING_MISSION_REQUIRED;
        if (!streamingInfo.IsGameRequired()) {
            if (streamingInfo.IsLoaded()) {
                if (!streamingInfo.InList())
                    streamingInfo.AddToList(ms_startLoadedList);
            } else if (!streamingInfo.DoKeepInMemory()) {
                RemoveModel(i);
            }
        }
        if (i >= RESOURCE_ID_TXD)
            break;
    }
    */
}

// 0x40B490
void CStreaming::SetMissionDoesntRequireSpecialChar(int32 slot) {
    SetMissionDoesntRequireModel(slot + SPECIAL_MODELS_RESOURCE_ID);
}

// 0x409C10
void CStreaming::SetModelIsDeletable(int32 modelId) {
    CStreamingInfo& streamingInfo = GetInfo(modelId);
    streamingInfo.ClearFlags(STREAMING_GAME_REQUIRED);
    if (!streamingInfo.IsMissionRequired()) {
        if (streamingInfo.IsLoaded()) {
            if (!streamingInfo.InList())
                streamingInfo.AddToList(ms_startLoadedList);
        } else if (!streamingInfo.DoKeepInMemory()) {
            RemoveModel(modelId);
        }
    }
}

// 0x409C70
void CStreaming::SetModelTxdIsDeletable(int32 modelId) {
    SetModelIsDeletable(TXDToModelId(CModelInfo::ms_modelInfoPtrs[modelId]->m_nTxdIndex));
}

void CStreaming::SetModelAndItsTxdDeletable(int32 modelId) {
    SetModelIsDeletable(modelId);
    SetModelTxdIsDeletable(modelId);
}

// 0x40B470
void CStreaming::SetSpecialCharIsDeletable(int32 slot) {
    SetModelIsDeletable(slot + SPECIAL_MODELS_RESOURCE_ID);
}

// 0x4084B0
void CStreaming::Shutdown() {
    CMemoryMgr::FreeAlign(ms_pStreamingBuffer[0]);
    ms_pStreamingBuffer[0] = nullptr; // NOTSA
    ms_pStreamingBuffer[1] = nullptr; // NOTSA
    ms_streamingBufferSize = 0;
    delete ms_pExtraObjectsDir;
}

// 0x4096C0
void CStreaming::StartRenderEntities() {
    ms_renderEntityLink = &ms_rwObjectInstances.usedListHead;
}

// 0x40A2A0
bool CStreaming::StreamAmbulanceAndMedic(bool bStreamForAccident) {
    // Set models for each zone but LEVEL_NAME_COUNTRY_SIDE as deletable
    {
        // Medic model + txd
        for (int32 i = 1; i < 4; i++) {
            SetModelAndItsTxdDeletable(ms_aDefaultMedicModel[i]);
        }

        // Ambulance model + txd
        for (int32 i = 1; i < 4; i++) {
            SetModelAndItsTxdDeletable(ms_aDefaultAmbulanceModel[i]);
        }
    }

    if (CTheZones::m_CurrLevel == eLevelName::LEVEL_NAME_COUNTRY_SIDE || !bStreamForAccident)
        return false; // Models for `LEVEL_NAME_COUNTRY_SIDE` are always loaded (I guess so, since they arent set as deletable above)

    // Load medic and ambulance model for current level
    // TODO: Maybe this could be done with a loop? This doesn't look to readable...
    int32 medicModel = ms_aDefaultMedicModel[CTheZones::m_CurrLevel];
    int32 ambulanceModel = ms_aDefaultAmbulanceModel[CTheZones::m_CurrLevel];
    RequestModel(medicModel, STREAMING_KEEP_IN_MEMORY);
    RequestModel(ambulanceModel, STREAMING_KEEP_IN_MEMORY);
    const CStreamingInfo& medicInfo = GetInfo(medicModel);
    const CStreamingInfo& ambulanceInfo = GetInfo(ambulanceModel);
    if (!medicInfo.IsLoaded() || !ambulanceInfo.IsLoaded())
        return false;

    return true;
}

// 0x40A150
void CStreaming::StreamCopModels(eLevelName level) {
    if (!CGame::CanSeeOutSideFromCurrArea())
        return;

    // Maybe load a cop bike..
    if (FindPlayerWanted(-1) && FindPlayerWanted(-1)->m_nWantedLevel < 3
        && level != eLevelName::LEVEL_NAME_COUNTRY_SIDE
        && !m_bDisableCopBikes
    ) {
        const uint32 timeInMs = CTimer::GetTimeInMS();
        if (ms_nTimePassedSinceLastCopBikeStreamedIn < timeInMs) {
            m_bCopBikeLoaded = !m_bCopBikeLoaded;
            ms_nTimePassedSinceLastCopBikeStreamedIn = timeInMs + CGeneral::GetRandomNumberInRange(30000, 50000);
        }

        if (m_bCopBikeLoaded)
            level = (eLevelName)4; // Not sure, dont ask..
    } else {
        m_bCopBikeLoaded = false;
    }

    if (GetInfo(ms_aDefaultCopModel[level]).IsLoaded() && GetInfo(ms_aDefaultCopCarModel[level]).IsLoaded()) {
        for (int32 i = 0; i < 4; i++) {
            if (i != level) {
                if (level != 4) {
                    SetModelAndItsTxdDeletable(ms_aDefaultCopModel[i]);
                }
                SetModelAndItsTxdDeletable(ms_aDefaultCopCarModel[i]);
            }
        }
    }

    RequestModel(ms_aDefaultCopModel[level], STREAMING_GAME_REQUIRED);
    RequestModel(ms_aDefaultCopCarModel[level], STREAMING_GAME_REQUIRED);
}

// 0x40A400
// Same as `StreamAmbulanceAndMedic` but for firetruck and fireman
bool CStreaming::StreamFireEngineAndFireman(bool bStreamForFire) {
    // Set models for each zone but LEVEL_NAME_COUNTRY_SIDE as deletable
    {
        // Fireman model + txd
        for (int32 i = 1; i < 4; i++) {
            SetModelAndItsTxdDeletable(ms_aDefaultFiremanModel[i]);
        }

        // Fire truck model + txd
        for (int32 i = 1; i < 4; i++) {
            SetModelAndItsTxdDeletable(ms_aDefaultFireEngineModel[i]);
        }
    }

    if (CTheZones::m_CurrLevel == eLevelName::LEVEL_NAME_COUNTRY_SIDE || !bStreamForFire)
        return false; // Models for `LEVEL_NAME_COUNTRY_SIDE` are always loaded (I guess so, since they arent set as deletable above)

    // Load firemand and firetruck for current level
    // TODO: Maybe this could be done with a loop? This doesn't look to readable...
    int32 firemanModel = ms_aDefaultFiremanModel[CTheZones::m_CurrLevel];
    int32 fireTruckModel = ms_aDefaultFireEngineModel[CTheZones::m_CurrLevel];
    RequestModel(firemanModel, STREAMING_KEEP_IN_MEMORY);
    RequestModel(fireTruckModel, STREAMING_KEEP_IN_MEMORY);
    const CStreamingInfo& firemanInfo = GetInfo(firemanModel);
    const CStreamingInfo& fireTruckInfo = GetInfo(fireTruckModel);

    if (!firemanInfo.IsLoaded() || !fireTruckInfo.IsLoaded())
        return false;

    return true;
}

// 0x40B4F0
void CStreaming::StreamOneNewCar() {
    if (!CPopCycle::m_pCurrZoneInfo)
        return;

    bool bCheatActive = false;
    int32 carGroupId = 0;
    if (CCheat::m_aCheatsActive[CHEAT_BEACH_PARTY]) {
        carGroupId = POPCYCLE_CARGROUP_BEACHFOLK;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_COUNTRY_TRAFFIC]) {
        carGroupId = POPCYCLE_CARGROUP_FARMERS;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_CHEAP_TRAFFIC]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT1;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_FAST_TRAFFIC]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT2;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_NINJA_THEME]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT3;
        bCheatActive = true;
    }
    if (CCheat::m_aCheatsActive[CHEAT_FUNHOUSE_THEME]) {
        carGroupId = POPCYCLE_CARGROUP_CHEAT4;
        bCheatActive = true;
    }

    if (bCheatActive) {
        int32 carModelId = CCarCtrl::ChooseCarModelToLoad(carGroupId);
        if (carModelId < 0)
            return;
        RequestModel(carModelId, STREAMING_KEEP_IN_MEMORY);
        CPopulation::LoadSpecificDriverModelsForCar(carModelId);
        return;
    }

    // Load a boat if less than 2. If there's exactly 2 maybe load one.
    if (m_bBoatsNeeded && (
            CPopulation::m_LoadedBoats.CountMembers() < 2 ||                    // Load one
            CPopulation::m_LoadedBoats.CountMembers() <= 2 && (rand() % 8) == 3 // Maybe load one (1 in 8 chance)
        )
    ) {
        int32 boatModelId = CCarCtrl::ChooseCarModelToLoad(POPCYCLE_CARGROUP_BOATS);
        if (boatModelId >= 0) {
            RequestModel(boatModelId, STREAMING_KEEP_IN_MEMORY);
            CPopulation::LoadSpecificDriverModelsForCar(boatModelId);
            return;
        }
    }

    // Try loading either `MODEL_TAXI` or `MODEL_CABBIE`
    int32 carModelId = -1;
    if (!GetInfo(MODEL_TAXI).IsLoaded()
        && !GetInfo(MODEL_CABBIE).IsLoaded()
    ) {
        static int32 lastCarModelStreamedIn = MODEL_TAXI;
        if (lastCarModelStreamedIn == MODEL_TAXI) {
            if (!IsCarModelNeededInCurrentZone(MODEL_CABBIE) && IsCarModelNeededInCurrentZone(MODEL_TAXI)) {
                carModelId = MODEL_TAXI;
                lastCarModelStreamedIn = MODEL_TAXI;
            }
        } else {
            // Possibly dead code? Once `lastCarModelStreamedIn` is set as `MODEL_TAXI` it wont change.
            // Maybe default value for `lastCarModelStreamedIn` isn't `MODEL_TAXI`?
            if (IsCarModelNeededInCurrentZone(MODEL_TAXI)) {
                carModelId = MODEL_TAXI;
                lastCarModelStreamedIn = MODEL_TAXI;
            } else if (IsCarModelNeededInCurrentZone(MODEL_CABBIE)) {
                carModelId = MODEL_CABBIE;
                lastCarModelStreamedIn = MODEL_CABBIE;
            }
        }
    }

    if (carModelId < 0) {
        int32 carGroupId = CPopCycle::PickARandomGroupOfOtherPeds();
        carModelId = CCarCtrl::ChooseCarModelToLoad(carGroupId);
        if (carModelId < 0)
            return;
    }

    RequestModel(carModelId, STREAMING_KEEP_IN_MEMORY);
    CPopulation::LoadSpecificDriverModelsForCar(carModelId);
}

// 0x40BBB0
void CStreaming::StreamPedsForInterior(int32 interiorType) {
    switch (interiorType) {
    case 0: { // Household?
        const int32 rndHusband = rand() % CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_HUSBANDS, 0); // Choose a random husband

        const int32 numWives = CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_WIVES, 0);
        int32 randomWife = std::max(0, rndHusband - CGeneral::GetRandomNumberInRange(3, 9));
        if (numWives - 1 < randomWife)
            randomWife = numWives - 1;

        ClearSlots(2); // Clear 2 ped slots

        // Load husband
        ePopcyclePedGroup husbandGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_HUSBANDS, CPopulation::CurrentWorldZone);
        int32 husbandModelId = CPopulation::GetPedGroupModelId(husbandGroupId, rndHusband);
        RequestModel(husbandModelId, STREAMING_KEEP_IN_MEMORY);
        ms_pedsLoaded[0] = husbandModelId;
        ms_numPedsLoaded++;

        // Load wife
        ePopcyclePedGroup wifeGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_WIVES, CPopulation::CurrentWorldZone);
        int32 wifeModelId = CPopulation::GetPedGroupModelId(wifeGroupId, randomWife);
        RequestModel(wifeModelId, STREAMING_KEEP_IN_MEMORY);
        ms_pedsLoaded[1] = wifeModelId;
        ms_numPedsLoaded++;

        break;
    }
    case 1: { // Shop?
        ePopcyclePedGroup groupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_SHOPKEEPERS, CPopulation::CurrentWorldZone);
        int32 modelId = CPopulation::GetPedGroupModelId(groupId, rand() % CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_SHOPKEEPERS, 0));
        ClearSlots(1);
        RequestModel(modelId, STREAMING_KEEP_IN_MEMORY);
        ms_pedsLoaded[0] = modelId;
        ms_numPedsLoaded++;
        break;
    }
    case 2: { // Office?
        ClearSlots(TOTAL_LOADED_PEDS);

        int32 numPeds = CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_OFFICE_WORKERS, 0);
        int32 random = CGeneral::GetRandomNumberInRange(0, numPeds);
        ePopcyclePedGroup groupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_OFFICE_WORKERS, CPopulation::CurrentWorldZone);
        for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
            int32 modelId = CPopulation::GetPedGroupModelId(groupId, (i + random) % numPeds);
            RequestModel(modelId, STREAMING_KEEP_IN_MEMORY);
            ms_pedsLoaded[i] = modelId;
            ms_numPedsLoaded++;
        }
        break;
    }
    }
}

// 0x40BDA0
// Load peds into ped slots.
// Input array special values:
// * -1 - Don't change slot (If there's a ped in that slot it remains loaded)
// * -2 - Unload model from slot (If there's any)
// * Positive values - Load given model into slot
void CStreaming::StreamPedsIntoRandomSlots(int32 modelArray[TOTAL_LOADED_PEDS]) {
    for (int32 i = 0; i < TOTAL_LOADED_PEDS; i++) {
        int32 modelId = ms_pedsLoaded[i];
        int32 pedModelId = modelArray[i];
        if (pedModelId >= 0) {
            // Load model into slot
            if (modelId >= 0) {
                // Unload model from slot
                SetModelAndItsTxdDeletable(modelId);
                ms_pedsLoaded[i] = -1;
                ms_numPedsLoaded--;
            }
            // Load model into slot
            RequestModel(pedModelId, STREAMING_KEEP_IN_MEMORY);
            ms_pedsLoaded[i] = pedModelId;
            ms_numPedsLoaded++;
        } else if (pedModelId == -2) { // Unload model from slot
            if (modelId >= 0) {
                SetModelAndItsTxdDeletable(modelId);
                ms_pedsLoaded[i] = -1;
                ms_numPedsLoaded--;
            }
        }
    }
}

// 0x40B700
void CStreaming::StreamVehiclesAndPeds() {
    StreamCopModels(CTheZones::m_CurrLevel);

    // The stuff below (where `FindPlayerWanted` is repeatedly called) IMHO are inlined.
    CWanted* wanted = FindPlayerWanted(-1);
    if (wanted->AreSwatRequired()) {
        RequestModel(MODEL_ENFORCER, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_SWAT, STREAMING_GAME_REQUIRED);
    } else {
        SetModelIsDeletable(MODEL_ENFORCER);
        if (!GetInfo(MODEL_ENFORCER).IsLoaded())
            SetModelIsDeletable(MODEL_SWAT);
    }

    wanted = FindPlayerWanted(-1);
    if (wanted->AreFbiRequired()) {
        RequestModel(MODEL_FBIRANCH, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_FBI, STREAMING_GAME_REQUIRED);
    } else {
        SetModelIsDeletable(MODEL_FBIRANCH);
        if (!GetInfo(MODEL_FBIRANCH).IsLoaded())
            SetModelIsDeletable(MODEL_FBI);
    }

    wanted = FindPlayerWanted(-1);
    if (wanted->AreArmyRequired()) {
        RequestModel(MODEL_RHINO, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_BARRACKS, STREAMING_GAME_REQUIRED);
        RequestModel(MODEL_ARMY, STREAMING_GAME_REQUIRED);
    } else {
        SetModelIsDeletable(MODEL_BARRACKS);
        SetModelIsDeletable(MODEL_RHINO);
        if (!GetInfo(MODEL_BARRACKS).IsLoaded()
            && !GetInfo(MODEL_RHINO).IsLoaded())
        {
            SetModelIsDeletable(MODEL_ARMY);
        }
    }

    wanted = FindPlayerWanted(-1);
    if (wanted->NumOfHelisRequired() <= 0) {
        SetModelIsDeletable(MODEL_VCNMAV);
        SetModelIsDeletable(MODEL_POLMAV);
    } else {
        RequestModel(MODEL_POLMAV, STREAMING_GAME_REQUIRED);
        wanted = FindPlayerWanted(-1);
        if (wanted->NumOfHelisRequired() > 1 && CWanted::bUseNewsHeliInAdditionToPolice)
            RequestModel(MODEL_VCNMAV, STREAMING_GAME_REQUIRED);
        else
            SetModelIsDeletable(MODEL_VCNMAV);
    }

    int32 pedGroupId = -1;
    if (CPopCycle::m_NumDealers_Peds > 0.03f) {
        if (CWeather::WeatherRegion == WEATHER_REGION_SF) {
            pedGroupId = POPCYCLE_PEDGROUP_BUSINESS_LA;
        } else if (CPopCycle::m_pCurrZoneInfo) {
            uint8 currenZoneFlags = CPopCycle::m_pCurrZoneInfo->Flags2;
            if (currenZoneFlags & 1)
                pedGroupId = 0;
            else if (currenZoneFlags & 2)
                pedGroupId = 1;
            else
                pedGroupId = 2;
        }
    }

    ePopcyclePedGroup dealerGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_DEALERS, 0);
    for (int32 i = 0; i < CPopulation::GetNumPedsInGroup(POPCYCLE_GROUP_DEALERS, 0); i++) {
        if (i == pedGroupId) {
            RequestModel(CPopulation::GetPedGroupModelId(dealerGroupId, i), STREAMING_GAME_REQUIRED);
        } else {
            int32 modelId = CPopulation::GetPedGroupModelId(dealerGroupId, i);
            SetModelIsDeletable(modelId);
        }
        dealerGroupId = CPopulation::GetPedGroupId(POPCYCLE_GROUP_DEALERS, 0);
    }

    static int32 framesBeforeStreamingNextNewCar = 0;
    if (framesBeforeStreamingNextNewCar >= 0) {
        --framesBeforeStreamingNextNewCar;
    }
    else if (ms_vehiclesLoaded.CountMembers() <= desiredNumVehiclesLoaded && CPopCycle::m_pCurrZoneInfo) {
        StreamOneNewCar();
        framesBeforeStreamingNextNewCar = 350;
    }

    if (m_bStreamHarvesterModelsThisFrame) {
        RequestModel(ModelIndices::MI_HARVESTERBODYPART1, STREAMING_GAME_REQUIRED);
        RequestModel(ModelIndices::MI_HARVESTERBODYPART2, STREAMING_GAME_REQUIRED);
        RequestModel(ModelIndices::MI_HARVESTERBODYPART3, STREAMING_GAME_REQUIRED);
        RequestModel(ModelIndices::MI_HARVESTERBODYPART4, STREAMING_GAME_REQUIRED);
        m_bHarvesterModelsRequested = true;
        m_bStreamHarvesterModelsThisFrame = false;
    } else {
        if (m_bHarvesterModelsRequested) {
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART1);
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART2);
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART3);
            RemoveModel(ModelIndices::MI_HARVESTERBODYPART4);
            m_bHarvesterModelsRequested = false;
        }
        m_bStreamHarvesterModelsThisFrame = false;
    }
}

// 0x40B650
void CStreaming::StreamVehiclesAndPeds_Always(CVector const& unused) {
    if (CVehicle* vehicle = FindPlayerVehicle(-1, false)) {
        switch (vehicle->m_vehicleSubType) {
        case VEHICLE_PLANE:
            return;

        case VEHICLE_HELI: {
            if (vehicle->m_vecMoveSpeed.Magnitude2D() > 0.1f)
                return;
        }
        }
    }

    if (CTimer::GetFrameCounter() % 64 == 0 && CPopulation::m_AppropriateLoadedCars.CountMembers() < 3)
        StreamOneNewCar();

    StreamZoneModels_Gangs({});

    if (CPopCycle::m_pCurrZoneInfo) {
        static int32 lastZonePopulationType = 0;
        if (CPopCycle::m_pCurrZoneInfo->zonePopulationType != lastZonePopulationType) {
            ReclassifyLoadedCars();
            lastZonePopulationType = CPopCycle::m_pCurrZoneInfo->zonePopulationType;
        }
    }
}

// 0x40A560
void CStreaming::StreamZoneModels(CVector const& unused) {
    if (!CPopCycle::m_pCurrZoneInfo || CCheat::IsZoneStreamingAllowed())
        return;

    static int32 timeBeforeNextLoad = 0;
    if (CPopCycle::m_pCurrZoneInfo->zonePopulationType == ms_currentZoneType) {
        if (timeBeforeNextLoad >= 0) {
            timeBeforeNextLoad--;
        } else {
           const auto slot = std::ranges::find_if(ms_pedsLoaded,
                [](auto model) { return model == -1 || CModelInfo::GetModelInfo(model)->m_nRefCount == 0; }
            );
            if (slot != std::end(ms_pedsLoaded)) {
                int32 pedModelId = CPopCycle::PickPedMIToStreamInForCurrentZone();
                if (pedModelId != *slot && pedModelId >= 0) {
                    RequestModel(pedModelId, STREAMING_KEEP_IN_MEMORY | STREAMING_GAME_REQUIRED);
                    GetInfo(pedModelId).ClearFlags(STREAMING_GAME_REQUIRED); // Ok???? Y?

                    if (ms_numPedsLoaded == TOTAL_LOADED_PEDS) {
                        SetModelAndItsTxdDeletable(*slot);
                       *slot = -1;
                    } else {
                        ++ms_numPedsLoaded;
                    }

                    int32 freeSlot = 0;
                    for (; ms_pedsLoaded[freeSlot] >= 0; freeSlot++); // Find free slot
                    ms_pedsLoaded[freeSlot] = pedModelId;

                    timeBeforeNextLoad = 300;
                }
            }
        }
    } else {
        int32 numPedsToLoad = ms_numPedsLoaded;

        // Unload all models from slots
        for (auto& model : ms_pedsLoaded) {
            if (model >= 0) {
                SetModelAndItsTxdDeletable(model);
                model = -1;
            }
        }
        ms_numPedsLoaded = 0;

        ms_currentZoneType = CPopCycle::m_pCurrZoneInfo->zonePopulationType;

        numPedsToLoad = std::max(numPedsToLoad, 4); // Loads back the same count of models as before unloading them, but at least 4.
        for (int32 i = 0; i < numPedsToLoad; i++) {
            int32 pedModelId = CPopCycle::PickPedMIToStreamInForCurrentZone();
            if (pedModelId < 0) {
                ms_pedsLoaded[i] = -1;
            } else {
                RequestModel(pedModelId, STREAMING_KEEP_IN_MEMORY | STREAMING_GAME_REQUIRED);
                GetInfo(pedModelId).ClearFlags(STREAMING_GAME_REQUIRED);
                ms_pedsLoaded[i] = pedModelId;
                ms_numPedsLoaded++;
            }
        }

        timeBeforeNextLoad = 300;
    }

    static int32 timeBeforeNextGangLoad = 0;
    if (timeBeforeNextGangLoad >= 0) {
        timeBeforeNextGangLoad--;
    } else /*if (timeBeforeNextGangLoad < 0) - unnecessary*/ {
        timeBeforeNextGangLoad = 550;

        const int32 currentGangMemberToLoadSlot = CurrentGangMemberToLoad;
        const int32 nextGangMemberToLoadSlot = CurrentGangMemberToLoad + 1;
        const int32 nextGangMemberToLoadAnySlot = (CurrentGangMemberToLoad + 1) % 21; // TODO: Magic number
        CurrentGangMemberToLoad = nextGangMemberToLoadAnySlot;
        for (int32 gangId = 0; gangId < TOTAL_GANGS; gangId++) {
            const auto popcycleGroup = static_cast<ePopcycleGroup>(gangId + POPCYCLE_GROUP_BALLAS);
            const ePopcyclePedGroup pedGroupId = CPopulation::GetPedGroupId(popcycleGroup, 0);
            if (ms_loadedGangs & (1 << gangId)) {
                const int32 nPedsInGang = CPopulation::GetNumPedsInGroup(pedGroupId);
                const int32 currGangMemberSlot = currentGangMemberToLoadSlot % nPedsInGang;
                const int32 nextGangMemberSlot = nextGangMemberToLoadSlot % nPedsInGang;
                const int32 nextGangMemberSlot1 = nextGangMemberToLoadAnySlot % nPedsInGang;
                const int32 nextGangMemberSlot2 = (nextGangMemberToLoadAnySlot + 1) % nPedsInGang;
                for (int32 slot = 0; slot < nPedsInGang; slot++) {
                    if (slot == currGangMemberSlot || slot == nextGangMemberSlot) {
                        if (slot == nextGangMemberSlot1) {
                            if (slot != currGangMemberSlot && slot != nextGangMemberSlot) {
                                const int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, slot);
                                RequestModel(modelId, STREAMING_GAME_REQUIRED);
                                continue;
                            }
                        } else if (slot != nextGangMemberSlot2) {
                            const int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, slot);
                            SetModelAndItsTxdDeletable(modelId);
                            continue;
                        }
                    } else {
                        if (slot == nextGangMemberSlot1 || slot == nextGangMemberSlot2) {
                            const int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, slot);
                            RequestModel(modelId, STREAMING_GAME_REQUIRED);
                        }
                    }
                }
            }
        }
    }
}

// 0x40AA10
void CStreaming::StreamZoneModels_Gangs(CVector const& unused) {
    if (!CPopCycle::m_pCurrZoneInfo)
        return;

    uint32 gangsNeeded = 0; // Bitfield of gangs to be loaded
    for (int32 i = 0; i < TOTAL_GANGS; i++) {
        if (CPopCycle::m_pCurrZoneInfo->GangDensity[i] != 0)
            gangsNeeded |= (1 << i);
    }
    if (CCheat::m_aCheatsActive[CHEAT_GANGS_CONTROLS_THE_STREETS])
        gangsNeeded |= 0xFF; // All gangs basically

    CGangWars::TellStreamingWhichGangsAreNeeded(&gangsNeeded);
    if (gangsNeeded == ms_loadedGangs && gangsNeeded == ms_loadedGangCars)
        return; // Everything loaded already

    for (int32 gangId = 0; gangId < TOTAL_GANGS; gangId++) {
        // Unload all / load some (1 vehicle, 2 ped) models of gangs based on whenever they're in `gangsNeeded`.

        const ePopcycleGroup popcycleGroup = static_cast<ePopcycleGroup>(gangId + POPCYCLE_GROUP_BALLAS);
        const ePopcyclePedGroup pedGroupId = CPopulation::GetPedGroupId(popcycleGroup, 0);
        const uint16 gangBit = 1 << gangId;

        // Handle ped models
        if (!(gangsNeeded & gangBit) /*gang not needed*/ || ms_loadedGangs & gangBit /*gang is loaded*/) {
            if (!(gangsNeeded & gangBit) /*gang not needed*/ && ms_loadedGangs & gangBit /*gang is loaded*/) {
                // Unload all models of this gang
                for (int32 i = 0; i < CPopulation::GetNumPedsInGroup(pedGroupId); ++i) {
                    int32 modelId = CPopulation::GetPedGroupModelId(pedGroupId, i);
                    SetModelAndItsTxdDeletable(modelId);
                }
                ms_loadedGangs &= ~gangBit;
            }
        } else /*gang needed and is not loaded - load 2 models*/ {
            const auto GetModel = [nPeds = CPopulation::GetNumPedsInGroup(pedGroupId), pedGroupId](auto off) {
                return CPopulation::GetPedGroupModelId(pedGroupId, off % nPeds);
            };

            RequestModel(GetModel(CurrentGangMemberToLoad), STREAMING_KEEP_IN_MEMORY);
            RequestModel(GetModel(CurrentGangMemberToLoad + 1), STREAMING_KEEP_IN_MEMORY);

            ms_loadedGangs |= gangBit; // Mark gang as loaded
        }

        // Handle vehicle models
        CLoadedCarGroup& loadedGangCarGroup = CPopulation::m_LoadedGangCars[gangId];
        if (loadedGangCarGroup.CountMembers() < 1) {
            if (!(gangsNeeded & gangBit) || ms_loadedGangCars & gangBit) /*gang not needed or is loaded*/ {
                if (!(gangsNeeded & gangBit) && (ms_loadedGangCars & gangBit)) /*gang not needed but is loaded*/ {

                    // Unload all car models related to this gang which are not needed,
                    // that is, the model isn't in `m_AppropriateLoadedCars` nor any other gang needs it.
                    CLoadedCarGroup loadedCarGroup = loadedGangCarGroup;
                    for (int32 i = 0; i < loadedCarGroup.CountMembers(); i++) {
                        int32 gangCarModelId = loadedCarGroup.GetMember(i);

                        bool bKeepCarModel = false;

                        for (int32 x = 0; x < CPopulation::m_AppropriateLoadedCars.CountMembers(); ++x) {
                            if (gangCarModelId == CPopulation::m_AppropriateLoadedCars.GetMember(x)) {
                                bKeepCarModel = true;
                                break; // R* forgot this originally
                            }
                        }

                        // Check if any other gang used this car model.
                        //
                        // NOTE:
                        // I think there should be a `if (!bKeepCarModel)` check
                        // since the above loop might already have set `bKeepCarModel` to `true`.
                        // Also if `modelId != CPopulation::m_defaultCarGroupModelId` is `false`
                        // this loop will never set `bKeepCarModel` to `true`.
                        for (int32 otherGangId = 0; otherGangId < TOTAL_GANGS; otherGangId++) {
                            if (otherGangId != gangId && (ms_loadedGangs & (1 << otherGangId))/*other gang is loaded*/) {
                                const int32 carGroupId = otherGangId + POPCYCLE_CARGROUP_BALLAS;
                                for (int32 i = 0; i < 23; i++) { // TODO: Magic number
                                    int32 modelId = CPopulation::m_CarGroups[carGroupId][i];
                                    if (modelId != CPopulation::m_defaultCarGroupModelId && modelId == gangCarModelId)
                                        bKeepCarModel = true;
                                }
                            }
                        }

                        if (!bKeepCarModel) {
                            SetModelAndItsTxdDeletable(gangCarModelId);
                        }
                    }
                }
            } else /*gang is needed but not loaded*/ {
                const int32 carGroupId = gangId + POPCYCLE_CARGROUP_BALLAS;
                const uint16 numCars = CPopulation::m_nNumCarsInGroup[carGroupId];
                const int32 modelId = CPopulation::m_CarGroups[carGroupId][rand() % numCars];
                if (!GetInfo(modelId).IsLoaded())
                    RequestModel(modelId, STREAMING_KEEP_IN_MEMORY); // Load 1 random car model
            }
        }
    }
    ms_loadedGangCars = gangsNeeded;
}

// 0x40E670
void CStreaming::Update() {
    g_LoadMonitor.m_numModelsRequest = ms_numModelsRequested;
    if (CTimer::GetIsPaused())
        return;

    const float fCamDistanceToGroundZ = TheCamera.GetPosition().z - TheCamera.CalculateGroundHeight(eGroundHeightType::ENTITY_BOUNDINGBOX_BOTTOM);
    if (!ms_disableStreaming && !CRenderer::m_loadingPriority) {
        if (fCamDistanceToGroundZ >= 50.0) {
            if (CGame::CanSeeOutSideFromCurrArea()) {
                AddLodsToRequestList(TheCamera.GetPosition(), 0);
            }
        }
        else if (CRenderer::ms_bRenderOutsideTunnels) {
            AddModelsToRequestList(TheCamera.GetPosition(), 0);
        }
    }

    if (CTimer::GetFrameCounter() % 128 == 106) {
        m_bBoatsNeeded = false;
        if (TheCamera.GetPosition().z < 500.0f)
            m_bBoatsNeeded = ThePaths.IsWaterNodeNearby(TheCamera.GetPosition(), 80.0f);
    }

    if (!ms_disableStreaming
        && !CCutsceneMgr::ms_cutsceneProcessing
        && CGame::CanSeeOutSideFromCurrArea()
        && CReplay::Mode != REPLAY_MODE_1
        && fCamDistanceToGroundZ < 50.0f
    ) {
        StreamVehiclesAndPeds_Always(FindPlayerCoors(-1));
        if (!IsVeryBusy()) {
            StreamVehiclesAndPeds();
            StreamZoneModels(FindPlayerCoors(-1));
        }
    }
    LoadRequestedModels();

    CVector playerPos = FindPlayerCoors(-1);
    if (CVehicle* pRemoteVehicle = CWorld::Players[0].m_pRemoteVehicle) {
        CColStore::AddCollisionNeededAtPosn(playerPos);
        CIplStore::AddIplsNeededAtPosn(playerPos);

        CColStore::LoadCollision(pRemoteVehicle->GetPosition(), false);
        CColStore::EnsureCollisionIsInMemory(pRemoteVehicle->GetPosition());
        CIplStore::LoadIpls(pRemoteVehicle->GetPosition(), false);
        CIplStore::EnsureIplsAreInMemory(pRemoteVehicle->GetPosition());
    }
    else {
        CColStore::LoadCollision(playerPos, false);
        CColStore::EnsureCollisionIsInMemory(playerPos);
        CIplStore::LoadIpls(playerPos, false);
        CIplStore::EnsureIplsAreInMemory(playerPos);
    }

    if (ms_bEnableRequestListPurge)
        PurgeRequestList();
}

// unused
// 0x40E960
void CStreaming::UpdateForAnimViewer() {
    CVector position;
    AddModelsToRequestList(position, 0);
    LoadRequestedModels();
    sprintf(gString, "Requested %d, memory size %dK\n", ms_numModelsRequested, 2 * ms_memoryUsed);
}

// 0x407F80
bool CStreaming::WeAreTryingToPhaseVehicleOut(int32 modelId) {
    CStreamingInfo& streamingInfo = CStreaming::GetInfo(modelId);
    if (streamingInfo.IsLoaded())
        return streamingInfo.m_nNextIndex >= 0 || streamingInfo.m_nPrevIndex >= 0;
    return false;
}
