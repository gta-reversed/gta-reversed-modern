#include "StdInc.h"

unsigned int &CStreaming::ms_memoryAvailable = *reinterpret_cast<unsigned int *>(0x8A5A80);
unsigned int &CStreaming::desiredNumVehiclesLoaded = *reinterpret_cast<unsigned int *>(0x8A5A84);
bool &CStreaming::ms_bLoadVehiclesInLoadScene = *reinterpret_cast<bool *>(0x8A5A88);
int *CStreaming::ms_aDefaultCopCarModel = reinterpret_cast<int *>(0x8A5A8C);
int &CStreaming::ms_DefaultCopBikeModel = *reinterpret_cast<int *>(0x8A5A9C);
int *CStreaming::ms_aDefaultCopModel = reinterpret_cast<int *>(0x8A5AA0);
int &CStreaming::ms_DefaultCopBikerModel = *reinterpret_cast<int *>(0x8A5AB0);
signed int *CStreaming::ms_aDefaultAmbulanceModel = reinterpret_cast<signed int *>(0x8A5AB4);
signed int *CStreaming::ms_aDefaultMedicModel = reinterpret_cast<signed int *>(0x8A5AC4);
signed int *CStreaming::ms_aDefaultFireEngineModel = reinterpret_cast<signed int *>(0x8A5AD4);
signed int *CStreaming::ms_aDefaultFiremanModel = reinterpret_cast<signed int *>(0x8A5AE4);
signed int *CStreaming::ms_aDefaultCabDriverModel = reinterpret_cast<signed int *>(0x8A5AF4);
CDirectory *&CStreaming::ms_pExtraObjectsDir = *reinterpret_cast<CDirectory **>(0x8E48D0);
tStreamingFileDesc *CStreaming::ms_files = reinterpret_cast<tStreamingFileDesc *>(0x8E48D8);
bool &CStreaming::ms_bLoadingBigModel = *reinterpret_cast<bool *>(0x8E4A58);
// There are only two channels within CStreaming::ms_channel
tStreamingChannel *CStreaming::ms_channel = reinterpret_cast<tStreamingChannel *>(0x8E4A60);
signed int &CStreaming::ms_channelError = *reinterpret_cast<signed int *>(0x8E4B90);
bool &CStreaming::m_bHarvesterModelsRequested = *reinterpret_cast<bool *>(0x8E4B9C);
bool &CStreaming::m_bStreamHarvesterModelsThisFrame = *reinterpret_cast<bool *>(0x8E4B9D);
unsigned int &CStreaming::ms_numPriorityRequests = *reinterpret_cast<unsigned int *>(0x8E4BA0);
int &CStreaming::ms_lastCullZone = *reinterpret_cast<int *>(0x8E4BA4);
unsigned short &CStreaming::ms_loadedGangCars = *reinterpret_cast<unsigned short *>(0x8E4BA8);
unsigned short &CStreaming::ms_loadedGangs = *reinterpret_cast<unsigned short *>(0x8E4BAC);
int &CStreaming::ms_numPedsLoaded = *reinterpret_cast<int *>(0x8E4BB0);
int *CStreaming::ms_pedsLoaded = reinterpret_cast<int *>(0x8E4C00);
int &CStreaming::ms_currentZoneType = *reinterpret_cast<int *>(0x8E4C20);
CLoadedCarGroup &CStreaming::ms_vehiclesLoaded = *reinterpret_cast<CLoadedCarGroup *>(0x8E4C24);
CStreamingInfo *&CStreaming::ms_pEndRequestedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C54);
CStreamingInfo *&CStreaming::ms_pStartRequestedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C58);
CStreamingInfo *&CStreaming::ms_pEndLoadedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C5C);
CStreamingInfo *&CStreaming::ms_startLoadedList = *reinterpret_cast<CStreamingInfo **>(0x8E4C60);
int &CStreaming::ms_lastImageRead = *reinterpret_cast<int *>(0x8E4C64);
signed int *CStreaming::ms_imageOffsets = reinterpret_cast<signed int *>(0x8E4C8C);
bool &CStreaming::ms_bEnableRequestListPurge = *reinterpret_cast<bool *>(0x8E4CA4);
unsigned int &CStreaming::ms_streamingBufferSize = *reinterpret_cast<unsigned int *>(0x8E4CA8);
char **CStreaming::ms_pStreamingBuffer = reinterpret_cast<char **>(0x8E4CAC);
unsigned int &CStreaming::ms_memoryUsed = *reinterpret_cast<unsigned int *>(0x8E4CB4);
int &CStreaming::ms_numModelsRequested = *reinterpret_cast<int *>(0x8E4CB8);
CStreamingInfo *CStreaming::ms_aInfoForModel = reinterpret_cast<CStreamingInfo *>(0x8E4CC0);
bool &CStreaming::ms_disableStreaming = *reinterpret_cast<bool *>(0x9654B0);
int &CStreaming::ms_bIsInitialised = *reinterpret_cast<int *>(0x9654B8);
bool &CStreaming::m_bBoatsNeeded = *reinterpret_cast<bool *>(0x9654BC);
bool &CStreaming::m_bLoadingScene = *reinterpret_cast<bool *>(0x9654BD);
bool &CStreaming::m_bCopBikeLoaded = *reinterpret_cast<bool *>(0x9654BE);
bool &CStreaming::m_bDisableCopBikes = *reinterpret_cast<bool *>(0x9654BF);
CLinkList<CEntity*> &CStreaming::ms_rwObjectInstances = *reinterpret_cast<CLinkList<CEntity*> *>(0x9654F0);
RwStream &gRwStream = *reinterpret_cast<RwStream *>(0x8E48AC);
bool &CStreaming::m_bLoadingAllRequestedModels = *reinterpret_cast<bool *>(0x965538);
bool &CStreaming::m_bModelStreamNotLoaded = *reinterpret_cast<bool *>(0x9654C4);
unsigned int &CStreaming::ms_numberOfBytesRead = *reinterpret_cast<unsigned int *>(0x965534); 

void CStreaming::InjectHooks()
{
    //CStreamingInfo::InjectHooks(); 
    HookInstall(0x409650, &CStreaming::AddEntity, 7);
    HookInstall(0x4019B9, &CStreaming::AreAnimsUsedByRequestedModels, 7);
    HookInstall(0x15664B0, &CStreaming::AreTexturesUsedByRequestedModels, 7);
    HookInstall(0x408E20, &CStreaming::GetNextFileOnCd, 7);
    HookInstall(0x40C6B0, &CStreaming::ConvertBufferToObject, 7);
    HookInstall(0x40A45E, &CStreaming::LoadAllRequestedModels, 7);
    HookInstall(0x15663B0, &CStreaming::RequestFile, 7);
    HookInstall(0x409050, &CStreaming::RequestFilesInChannel, 7);
    HookInstall(0x4087E0, &CStreaming::RequestModel, 7);
    HookInstall(0x408CB0, &CStreaming::FinishLoadingLargeFile, 7);
    HookInstall(0x40E460, &CStreaming::FlushChannels, 7);
    HookInstall(0x40CBA0, &CStreaming::RequestModelStream, 7);
    HookInstall(0x40B450, &CStreaming::RequestSpecialChar, 7);
    HookInstall(0x409D10, &CStreaming::RequestSpecialModel, 7);
    HookInstall(0x40E170, &CStreaming::ProcessLoadingChannel, 7);
    HookInstall(0x5BCCD0, &CStreaming::ReadIniFile, 7);
    HookInstall(0x4089A0, &CStreaming::RemoveModel, 7);
    HookInstall(0x40E120, &CStreaming::MakeSpaceFor, 7);
    HookInstall(0x4076C0, &CStreaming::RetryLoadFile, 7);
    HookInstall(0x40E3A0, &CStreaming::LoadRequestedModels, 7);
    HookInstall(0x40E4E0, &CStreaming::FlushRequestList, 7); 
    HookInstall(0x156CD70, &CStreaming::GetDefaultFiremanModel, 7);
    HookInstall(0x1563A50, &CStreaming::GetDefaultMedicModel, 7);
}

void* CStreaming::AddEntity(CEntity* pEntity) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<void*, CEntity*>(0x409650, pEntity);
#else
    if (pEntity->m_nType == ENTITY_TYPE_PED || pEntity->m_nType == ENTITY_TYPE_VEHICLE)
        return nullptr;
    CLink<CEntity*>* link = ms_rwObjectInstances.Insert(pEntity);
    if (!link)
    {
        CLink<CEntity*>* previousLink = ms_rwObjectInstances.usedListTail.prev;
        for (; previousLink != &ms_rwObjectInstances.usedListHead; previousLink = previousLink->prev) {
            CEntity* entity = previousLink->data;
            if (!entity->m_bImBeingRendered && !entity->m_bStreamingDontDelete)
                break;
        }
        if (previousLink == &ms_rwObjectInstances.usedListHead)
            return ms_rwObjectInstances.Insert(pEntity);
        previousLink->data->DeleteRwObject();
        link = ms_rwObjectInstances.Insert(pEntity);
    }
    return link;
#endif
}

int CStreaming::AddImageToList(char const *lpFileName, bool bNotPlayerImg) {
    return plugin::CallAndReturnDynGlobal<int, char const *, bool>(0x407610, lpFileName, bNotPlayerImg);
}

void CStreaming::AddLodsToRequestList(CVector const *Posn, unsigned int Streamingflags) {
    plugin::CallDynGlobal<CVector const *, unsigned int>(0x40C520, Posn, Streamingflags);
}

void CStreaming::AddModelsToRequestList(CVector const *posn, unsigned int StreamingFlags) {
    plugin::CallDynGlobal<CVector const *, unsigned int>(0x40D3F0, posn, StreamingFlags);
}

bool CStreaming::AreAnimsUsedByRequestedModels(int animModelId) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<bool, int>(0x407AD0, animModelId);
#else
    auto pStreamingInfo = CStreaming::ms_pStartRequestedList->GetNext();
    for (; pStreamingInfo != CStreaming::ms_pEndRequestedList; pStreamingInfo = pStreamingInfo->GetNext()) {
        int modelId = pStreamingInfo - CStreaming::ms_aInfoForModel;
        if (modelId < RESOURCE_ID_TXD && CModelInfo::ms_modelInfoPtrs[modelId]->GetAnimFileIndex() == animModelId)
            return true;
    }
    if (pStreamingInfo == CStreaming::ms_pEndRequestedList) {
        for (int i = 0; i < 16; i++) {
            for (int channelId = 0; channelId < 2; channelId++) {
                int modelId = CStreaming::ms_channel[channelId].modelIds[i];
                if (modelId != -1 && modelId < RESOURCE_ID_TXD  && 
                    CModelInfo::ms_modelInfoPtrs[modelId]->GetAnimFileIndex() == animModelId)
                {
                    return true;
                }
            }
        }
    }
    return false;
#endif
}

bool CStreaming::AreTexturesUsedByRequestedModels(int txdModelId) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<bool, int>(0x409A90, txdModelId);
#else
    auto pStreamingInfo = ms_pStartRequestedList->GetNext();
    for (; pStreamingInfo != CStreaming::ms_pEndRequestedList; pStreamingInfo = pStreamingInfo->GetNext()) {
        int modelId = pStreamingInfo - CStreaming::ms_aInfoForModel;
        if (modelId < RESOURCE_ID_TXD) {
            if (CModelInfo::ms_modelInfoPtrs[modelId]->m_nTxdIndex == txdModelId)
                return true;
        }
        else if (modelId < RESOURCE_ID_COL) {
            if (CTxdStore::GetParentTxdSlot(modelId - RESOURCE_ID_TXD) == txdModelId)
                return true;
        }
    }
    if (pStreamingInfo == CStreaming::ms_pEndRequestedList) {
        for (int i = 0; i < 16; i++) {
            for (int channelId = 0; channelId < 2; channelId++) {
                int modelId = CStreaming::ms_channel[channelId].modelIds[i];
                if (modelId != -1) {
                    if (modelId < RESOURCE_ID_TXD) {
                        if (CModelInfo::ms_modelInfoPtrs[modelId]->m_nTxdIndex == txdModelId)
                            return true;
                    }
                    else if (modelId < RESOURCE_ID_COL) {
                        if (CTxdStore::GetParentTxdSlot(modelId - RESOURCE_ID_TXD) == txdModelId)
                            return true;
                    }
                }
            }
        }
    }
    return false;
#endif
}

int CStreaming::GetNextFileOnCd(unsigned int streamLastPosn, bool bNotPriority) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<int, int, bool>(0x408E20, streamLastPosn, bNotPriority);
#else
    unsigned int nextRequestModelPos = UINT_MAX;
    unsigned int firstRequestModelPos = UINT_MAX;
    int firstRequestModelId = -1;
    int nextRequestModelId = -1;
    auto pStreamingInfo = ms_pStartRequestedList->GetNext();
    for (; pStreamingInfo != ms_pEndRequestedList; pStreamingInfo = pStreamingInfo->GetNext())
    {
        int modelId = pStreamingInfo - ms_aInfoForModel;
        if (!bNotPriority || !ms_numPriorityRequests || pStreamingInfo->m_nFlags & PRIORITY_REQUEST) {
            if (modelId < RESOURCE_ID_TXD) {
                CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
                short txdIndex = pModelInfo->m_nTxdIndex;
                unsigned char txdLoadState = ms_aInfoForModel[txdIndex + RESOURCE_ID_TXD].m_nLoadState;
                if (txdLoadState != LOADSTATE_LOADED && txdLoadState != LOADSTATE_Channeled) {
                    RequestModel(txdIndex + RESOURCE_ID_TXD, ms_aInfoForModel[modelId].m_nFlags);
                    continue;
                }
                int animFileIndex = pModelInfo->GetAnimFileIndex();
                if (animFileIndex != -1) {
                    int animModelId = animFileIndex + RESOURCE_ID_IFP;
                    unsigned char animLoadState = ms_aInfoForModel[animModelId].m_nLoadState;
                    if (animLoadState != LOADSTATE_LOADED && animLoadState != LOADSTATE_Channeled) {
                        RequestModel(animModelId, KEEP_IN_MEMORY);
                        continue;
                    }
                }
            }
            else if (modelId < RESOURCE_ID_COL) {
                TxdDef* pTexDictionary = CTxdStore::ms_pTxdPool->GetAt(modelId - RESOURCE_ID_TXD);
                short parentIndex = pTexDictionary->m_wParentIndex;
                if (parentIndex != -1) {
                    int txdModelId = parentIndex + RESOURCE_ID_TXD;
                    unsigned char loadState = ms_aInfoForModel[txdModelId].m_nLoadState;
                    if (loadState != LOADSTATE_LOADED && loadState != LOADSTATE_Channeled) {
                        RequestModel(txdModelId, KEEP_IN_MEMORY);
                        continue;
                    }
                }
            }
            else if ((modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR)
                && (CCutsceneMgr::ms_cutsceneProcessing || ms_aInfoForModel[7].m_nLoadState != LOADSTATE_LOADED))
            {
                continue;
            }
            const unsigned int modelPos = ms_aInfoForModel[modelId].GetCdPosn();
            if (modelPos < firstRequestModelPos) {
                firstRequestModelPos = modelPos;
                firstRequestModelId = pStreamingInfo - ms_aInfoForModel;
            }
            if (modelPos < nextRequestModelPos && modelPos >= streamLastPosn) {
                nextRequestModelPos = modelPos;
                nextRequestModelId = pStreamingInfo - ms_aInfoForModel;
            }
        }
    }
    int nextModelId = nextRequestModelId;
    if (nextModelId == -1)
        nextModelId = firstRequestModelId;
    if (nextModelId != -1 || !ms_numPriorityRequests)
        return nextModelId;
    ms_numPriorityRequests = 0;
    return nextModelId;
#endif
}

bool CStreaming::ConvertBufferToObject(unsigned char* pFileBuffer, int modelId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<bool, unsigned char*, int >(0x40C6B0, pFileBuffer, modelId);
#else
    CStreamingInfo *pStartLoadedListStreamingInfo = ms_startLoadedList;;
    CBaseModelInfo *pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo *pModelStreamingInfo = &ms_aInfoForModel[modelId];

    unsigned int bufferSize = pModelStreamingInfo->m_nCdSize * 2048;
    tRwStreamInitializeData rwStreamInitializationData = { pFileBuffer, bufferSize };

    RwStream* pRwStream = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitializationData);
    if (modelId >= RESOURCE_ID_TXD)
    {
        if (modelId >= RESOURCE_ID_COL)
        {
            if (modelId >= RESOURCE_ID_IPL)
            {
                if (modelId >= RESOURCE_ID_DAT)
                {
                    if (modelId >= RESOURCE_ID_IFP)
                    {
                        if (modelId >= RESOURCE_ID_RRR)
                        {
                            if (modelId >= RESOURCE_ID_SCM) {
                                CStreamedScripts & pStreamedScripts = CTheScripts::StreamedScripts;
                                pStreamedScripts.LoadStreamedScript(pRwStream, modelId - RESOURCE_ID_SCM);
                            }
                            else {
                                CVehicleRecording::Load(pRwStream, modelId - RESOURCE_ID_RRR, bufferSize);
                            }
                        }
                        else {
                            if (!(pModelStreamingInfo->m_nFlags & (KEEP_IN_MEMORY | MISSION_REQUIRED | GAME_REQUIRED))
                                && !AreAnimsUsedByRequestedModels(modelId - RESOURCE_ID_IFP))  {
                                RemoveModel(modelId);
                                RwStreamClose(pRwStream, &rwStreamInitializationData);
                                return false;
                            }
                            CAnimManager::LoadAnimFile(pRwStream, true, 0);
                            CAnimManager::CreateAnimAssocGroups();
                        }
                    }
                    else
                    {
                        ThePaths.LoadPathFindData(pRwStream, modelId - RESOURCE_ID_DAT);
                    }
                }
                else if (!CIplStore::LoadIpl(modelId - RESOURCE_ID_IPL, pFileBuffer, bufferSize))
                {
                    RemoveModel(modelId);
                    RequestModel(modelId, pModelStreamingInfo->m_nFlags);
                    RwStreamClose(pRwStream, &rwStreamInitializationData);
                    return false;
                }
            }
            else if (!CColStore::LoadCol(modelId - RESOURCE_ID_COL, pFileBuffer, bufferSize))
            {
                RemoveModel(modelId);
                RequestModel(modelId, pModelStreamingInfo->m_nFlags);
                RwStreamClose(pRwStream, &rwStreamInitializationData);
                return false;
            }
        }
        else {
            int modelTxdIndex = modelId - RESOURCE_ID_TXD;
            TxdDef *pTxdDef = CTxdStore::ms_pTxdPool->GetAt(modelTxdIndex);
            if (pTxdDef) {
                int txdIndex = pTxdDef->m_wParentIndex;
                if (txdIndex != -1 && !CTxdStore::GetTxd(txdIndex)) {
                    RemoveModel(modelId);
                    RequestModel(modelId, pModelStreamingInfo->m_nFlags);
                    RwStreamClose(pRwStream, &rwStreamInitializationData);
                    return false;
                }
            }

            if (!(pModelStreamingInfo->m_nFlags & (KEEP_IN_MEMORY | MISSION_REQUIRED | GAME_REQUIRED))
                && !AreTexturesUsedByRequestedModels(modelTxdIndex))
            {
                RemoveModel(modelId);
                RwStreamClose(pRwStream, &rwStreamInitializationData);
                return false;
            }

            bool bTxdLoaded = false;
            if (ms_bLoadingBigModel) {
                bTxdLoaded = CTxdStore::StartLoadTxd(modelTxdIndex, pRwStream);
                if (bTxdLoaded)
                    pModelStreamingInfo->m_nLoadState = LOADSTATE_Finishing;
            }
            else {
                bTxdLoaded = CTxdStore::LoadTxd(modelTxdIndex, pRwStream);
            }
            if (!bTxdLoaded) {
                RemoveModel(modelId);
                RequestModel(modelId, pModelStreamingInfo->m_nFlags);
                RwStreamClose(pRwStream, &rwStreamInitializationData);
                return false;
            }
        }
    }
    else {
        int animFileIndex = pBaseModelInfo->GetAnimFileIndex();
        short wTxdIndex = pBaseModelInfo->m_nTxdIndex;
        TxdDef* pTxdDef = CTxdStore::ms_pTxdPool->GetAt(wTxdIndex);
        if ((pTxdDef && !pTxdDef->m_pRwDictionary) || animFileIndex != -1 && !CAnimManager::ms_aAnimBlocks[animFileIndex].bLoaded)
        {
            RemoveModel(modelId);
            RequestModel(modelId, pModelStreamingInfo->m_nFlags);
            RwStreamClose(pRwStream, &rwStreamInitializationData);
            return false;
        }

        CTxdStore::AddRef(wTxdIndex);
        if (animFileIndex != -1)
            CAnimManager::AddAnimBlockRef(animFileIndex);
        CTxdStore::SetCurrentTxd(pBaseModelInfo->m_nTxdIndex);

        bool bFileLoaded = false;
        if (pBaseModelInfo->GetRwModelType() == RWMODEL_INFO_ATOMIC) {
            RtDict* pRtDictionary = nullptr;
            RwChunkHeaderInfo chunkHeaderInfo;
            RwStreamReadChunkHeaderInfo(pRwStream, &chunkHeaderInfo);
            if (chunkHeaderInfo.type == rwID_UVANIMDICT) {
                pRtDictionary = RtDictSchemaStreamReadDict(&RpUVAnimDictSchema, pRwStream);
                RtDictSchemaSetCurrentDict(&RpUVAnimDictSchema, pRtDictionary);
            }
            RwStreamClose(pRwStream, &rwStreamInitializationData);
            RwStream* pRwStream2 = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitializationData);
            bFileLoaded = CFileLoader::LoadAtomicFile(pRwStream2, modelId);
            if (pRtDictionary)
            {
                RtDictDestroy(pRtDictionary);
            }
        }
        else
        {
            bFileLoaded = CFileLoader::LoadClumpFile(pRwStream, modelId);
        }
        if (pModelStreamingInfo->m_nLoadState != LOADSTATE_Finishing)
        {
            CTxdStore::RemoveRefWithoutDelete(pBaseModelInfo->m_nTxdIndex);
            if (animFileIndex != -1)
            {
                CAnimManager::RemoveAnimBlockRefWithoutDelete(animFileIndex);
            }

            if (bFileLoaded && pBaseModelInfo->GetModelType() == MODEL_INFO_VEHICLE)
            {
                if (!AddToLoadedVehiclesList(modelId))
                {
                    RemoveModel(modelId);
                    RequestModel(modelId, pModelStreamingInfo->m_nFlags);
                    RwStreamClose(pRwStream, &rwStreamInitializationData);
                    return false;
                }
            }
        }
        if (!bFileLoaded)
        {
            RemoveModel(modelId);
            RequestModel(modelId, pModelStreamingInfo->m_nFlags);
            RwStreamClose(pRwStream, &rwStreamInitializationData);
            return false;
        }
    }

    RwStreamClose(pRwStream, &rwStreamInitializationData);
    if (modelId >= RESOURCE_ID_TXD) {
        if (!(modelId >= RESOURCE_ID_COL && (modelId < RESOURCE_ID_IFP || modelId >= RESOURCE_ID_RRR) 
            && modelId < RESOURCE_ID_SCM || pModelStreamingInfo->m_nFlags & (MISSION_REQUIRED | GAME_REQUIRED))) {
            pModelStreamingInfo->AddToList(pStartLoadedListStreamingInfo);
        }
    }
    else {
        if (pBaseModelInfo->GetModelType() != MODEL_INFO_VEHICLE && pBaseModelInfo->GetModelType() != MODEL_INFO_PED) {
            CBaseModelInfo * pAsAtomicModelInfo = pBaseModelInfo->AsAtomicModelInfoPtr();
            if (pAsAtomicModelInfo)
                pAsAtomicModelInfo->m_nAlpha = -((pModelStreamingInfo->m_nFlags & 0x24) != 0);
            if (!(pModelStreamingInfo->m_nFlags & (MISSION_REQUIRED | GAME_REQUIRED)))
                pModelStreamingInfo->AddToList(pStartLoadedListStreamingInfo);
        }
    }

    if (pModelStreamingInfo->m_nLoadState != LOADSTATE_Finishing) {
        pModelStreamingInfo->m_nLoadState = LOADSTATE_LOADED;
        ms_memoryUsed += bufferSize;
    }
    return true;
#endif
}

bool CStreaming::IsVeryBusy() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<bool>(0x4076A0);
#else
    return CRenderer::m_loadingPriority || ms_numModelsRequested > 5;
#endif
}

//////////////////////////////////////////////////////////////////////////////////////////
// CStreaming::LoadAllRequestedModels
//
// There are only 2 streaming channels within CStreaming::ms_channel. In this function, 
// if your current channelIndex is zero then "1 - channelIndex" will give you the other 
// streaming channel within CStreaming::ms_channel which is 1 (second streaming channel). 
//////////////////////////////////////////////////////////////////////////////////////////
void CStreaming::LoadAllRequestedModels(bool bOnlyPriorityRequests)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<bool>(0x40EA10, bOnlyPriorityRequests);
#else
    if (!m_bLoadingAllRequestedModels)
    {
        m_bLoadingAllRequestedModels = true;
        FlushChannels();
        int numModelsToLoad = 10;
        if (2 * ms_numModelsRequested >= 10)
            numModelsToLoad = 2 * ms_numModelsRequested;

        int channelIndex = 0;
        while (1)
        {
            tStreamingChannel& firstStreamingChannel = ms_channel[0];
            tStreamingChannel& secondStreamingChannel = ms_channel[1];

            short endRequestPreviousIndex = ms_pEndRequestedList->m_nPrevIndex;
            CStreamingInfo * pStreamingInfo = endRequestPreviousIndex == -1 ? 0 : &CStreamingInfo::ms_pArrayBase[endRequestPreviousIndex];

            if (pStreamingInfo == ms_pStartRequestedList
                && !firstStreamingChannel.LoadStatus
                && !secondStreamingChannel.LoadStatus
                || numModelsToLoad <= 0)
            {
                break;
            }

            if (ms_bLoadingBigModel)
            {
                channelIndex = 0;
            }

            tStreamingChannel& streamingChannel = ms_channel[channelIndex];
            if (streamingChannel.LoadStatus)
            {
                CdStreamSync(channelIndex);
                streamingChannel.iLoadingLevel = 100;
            }

            if (streamingChannel.LoadStatus == LOADSTATE_LOADED)
            {
                ProcessLoadingChannel(channelIndex);
                if (streamingChannel.LoadStatus == LOADSTATE_Requested)
                {
                    ProcessLoadingChannel(channelIndex);
                }
            }

            if (bOnlyPriorityRequests && !ms_numPriorityRequests)
            {
                break;
            }

            if (!ms_bLoadingBigModel)
            {
                tStreamingChannel& otherStreamingChannel = ms_channel[1 - channelIndex];
                if (!otherStreamingChannel.LoadStatus)
                {
                    RequestModelStream(1 - channelIndex);
                }

                if (!streamingChannel.LoadStatus && !ms_bLoadingBigModel)
                {
                    RequestModelStream(channelIndex);
                }
            }
            if (!firstStreamingChannel.LoadStatus && !secondStreamingChannel.LoadStatus)
            {
                break;
            }

            channelIndex = 1 - channelIndex;
            --numModelsToLoad;
        }
        FlushChannels();
        m_bLoadingAllRequestedModels = false;
    }
#endif
}

void CStreaming::RequestFile(int modelId, int posn, int size, int imgId, int streamingFlags)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x40A080, int, int, int, int, int>(modelId, posn, size, imgId, streamingFlags);
#else
    auto& streamingInfo = ms_aInfoForModel[modelId];
    const unsigned int blockOffset = (imgId << 24) | posn;
    if (streamingInfo.m_nCdSize && streamingInfo.GetCdPosn() == blockOffset && streamingInfo.m_nCdSize == size) {
        RequestModel(modelId, streamingFlags);
    }
    else {
        RemoveModel(modelId);
        streamingInfo.m_nCdPosn = blockOffset & 0xFFFFFF;
        streamingInfo.m_nCdSize = size;
        streamingInfo.m_nImgId = imgId;
        RequestModel(modelId, streamingFlags);
    }
#endif
}

void CStreaming::RequestFilesInChannel(int channelId) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int>(0x409050, channelId);
#else
    const tStreamingChannel& channel = CStreaming::ms_channel[channelId];
    for (int i = 0; i < 16; i++) {
        const int modelId = channel.modelIds[i];
        if (modelId != -1) {
            int flags = CStreaming::ms_aInfoForModel[modelId].m_nFlags;
            RemoveModel(modelId);
            RequestModel(modelId, flags);
        }
    }
#endif
}

void CStreaming::RequestModel(int modelId, unsigned int streamingFlags)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int, unsigned int>(0x4087E0, modelId, streamingFlags);
#else
    CStreamingInfo & modelStreamingInfo = ms_aInfoForModel[modelId];
    char loadState = modelStreamingInfo.m_nLoadState;
    if (loadState == LOADSTATE_Requested)
    {
        if ((streamingFlags & PRIORITY_REQUEST) && !(modelStreamingInfo.m_nFlags & PRIORITY_REQUEST))
        {
            ++ms_numPriorityRequests;
            modelStreamingInfo.m_nFlags |= PRIORITY_REQUEST;
        }
    }
    else if (loadState)
    {
        streamingFlags &= ~PRIORITY_REQUEST;
    }

    modelStreamingInfo.m_nFlags |= streamingFlags;
    if (loadState == LOADSTATE_LOADED) {
        if (modelStreamingInfo.InList()) {
            modelStreamingInfo.RemoveFromList();
            if (modelId < RESOURCE_ID_TXD) {
                CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
                size_t modelType = modelInfo->GetModelType();
                if (modelType == MODEL_INFO_TYPE_PED || modelType == MODEL_INFO_TYPE_VEHICLE)
                {
                    return;
                }
            }

            if (!(modelStreamingInfo.m_nFlags & (GAME_REQUIRED | MISSION_REQUIRED)))
                modelStreamingInfo.AddToList(ms_startLoadedList);
        }
    }
    else if (loadState != LOADSTATE_Channeled && loadState != LOADSTATE_Requested && loadState != LOADSTATE_Finishing) {
        if (loadState == LOADSTATE_NOT_LOADED) {
            if (modelId >= RESOURCE_ID_TXD) {
                if (modelId < RESOURCE_ID_COL) {
                    int txdEntryParentIndex = CTxdStore::GetParentTxdSlot(modelId - RESOURCE_ID_TXD);
                    if (txdEntryParentIndex != -1)
                        RequestTxdModel(txdEntryParentIndex, streamingFlags);
                }
            }
            else
            {
                CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
                RequestTxdModel(modelInfo->m_nTxdIndex, streamingFlags);
                int animFileIndex = modelInfo->GetAnimFileIndex();
                if (animFileIndex != -1)
                    RequestModel(animFileIndex + RESOURCE_ID_IFP, KEEP_IN_MEMORY);
            }
            modelStreamingInfo.AddToList(ms_pStartRequestedList);
            ++ms_numModelsRequested;
            if (streamingFlags & PRIORITY_REQUEST)
                ++ms_numPriorityRequests;
        }
        modelStreamingInfo.m_nFlags = streamingFlags;
        modelStreamingInfo.m_nLoadState = LOADSTATE_Requested;// requested, loading
    }
#endif
}

void CStreaming::RequestTxdModel(int txdModelID, int streamingFlags) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int, int>(0x407100, txdModelID, streamingFlags);
#else
    RequestModel(txdModelID + RESOURCE_ID_TXD, streamingFlags);
#endif
}

void CStreaming::FinishLoadingLargeFile(unsigned char * pFileBuffer, int modelId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x408CB0, unsigned char *, int>(pFileBuffer, modelId);
#else
    bool bFinishedLoadingLargeFile = 0;
    CBaseModelInfo *pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo& streamingInfo = CStreaming::ms_aInfoForModel[modelId];
    if (streamingInfo.m_nLoadState == LOADSTATE_Finishing)
    {

        unsigned int bufferSize = streamingInfo.m_nCdSize << 11;
        tRwStreamInitializeData rwStreamInitializationData = { pFileBuffer, bufferSize };
        RwStream * pRwStream = _rwStreamInitialize(&gRwStream, 0, rwSTREAMMEMORY, rwSTREAMREAD, &rwStreamInitializationData);
        bool bLoaded = false;
        if (modelId >= RESOURCE_ID_TXD) {
            if (modelId >= RESOURCE_ID_COL) {
                bLoaded = modelId;
            }
            else
            {
                CTxdStore::AddRef(modelId - RESOURCE_ID_TXD);
                bLoaded = CTxdStore::FinishLoadTxd(modelId - RESOURCE_ID_TXD, pRwStream);
                CTxdStore::RemoveRefWithoutDelete(modelId - RESOURCE_ID_TXD);
            }
        }
        else {
            CTxdStore::SetCurrentTxd(pBaseModelInfo->m_nTxdIndex);
            bLoaded = CFileLoader::FinishLoadClumpFile(pRwStream, modelId);
            if (bLoaded)
                bLoaded = CStreaming::AddToLoadedVehiclesList(modelId);
            pBaseModelInfo->RemoveRef();
            CTxdStore::RemoveRefWithoutDelete(pBaseModelInfo->m_nTxdIndex);
            int animFileIndex = pBaseModelInfo->GetAnimFileIndex();
            if (animFileIndex != -1) {
                CAnimManager::RemoveAnimBlockRefWithoutDelete(animFileIndex);
            }
        }
        RwStreamClose(pRwStream, &pFileBuffer);
        streamingInfo.m_nLoadState = LOADSTATE_LOADED;
        CStreaming::ms_memoryUsed += bufferSize;
        if (!bLoaded) {
            CStreaming::RemoveModel(modelId);
            CStreaming::RequestModel(modelId, streamingInfo.m_nFlags);
        }
    }
    else {
        if (modelId < RESOURCE_ID_TXD)
            pBaseModelInfo->RemoveRef();
    }
#endif
}

void CStreaming::FlushChannels()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x40E460>();
#else
    if (ms_channel[1].LoadStatus == LOADSTATE_Requested)
        ProcessLoadingChannel(1);
    if (ms_channel[0].LoadStatus == LOADSTATE_LOADED)
    {
        CdStreamSync(0);
        ms_channel[0].iLoadingLevel = 100;
        ProcessLoadingChannel(0);
    }
    if (ms_channel[0].LoadStatus == LOADSTATE_Requested)
        ProcessLoadingChannel(0);
    if (ms_channel[1].LoadStatus == LOADSTATE_LOADED)
    {
        CdStreamSync(1u);
        ms_channel[1].iLoadingLevel = 100;
        ProcessLoadingChannel(1);
    }
    if (ms_channel[1].LoadStatus == LOADSTATE_Requested)
        ProcessLoadingChannel(1);;
#endif
}

void CStreaming::RequestModelStream(int channelIndex)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int>(0x40CBA0, channelIndex);
#else
    int CdStreamLastPosn = CdStreamGetLastPosn();
    int modelId = GetNextFileOnCd(CdStreamLastPosn, 1);
    if (modelId == -1)
    {
        return;
    }

    int32_t blockOffsetMimg = 0;
    unsigned int blockCount = 0;

    CStreamingInfo * streamingInfo = &ms_aInfoForModel[modelId];
    while (!(streamingInfo->m_nFlags & (KEEP_IN_MEMORY | MISSION_REQUIRED | GAME_REQUIRED)))
    {
        if (modelId < RESOURCE_ID_TXD || modelId >= RESOURCE_ID_COL || AreTexturesUsedByRequestedModels(modelId - RESOURCE_ID_TXD))
        {
            if (modelId < RESOURCE_ID_IFP || modelId >= RESOURCE_ID_RRR || AreAnimsUsedByRequestedModels(modelId - RESOURCE_ID_IFP))
                break;
        }
        RemoveModel(modelId);
        if (streamingInfo->m_nCdSize)
        {
            blockOffsetMimg = streamingInfo->m_nCdPosn + ms_files[streamingInfo->m_nImgId].m_StreamHandle;
            blockCount = streamingInfo->m_nCdSize;
        }

        modelId = GetNextFileOnCd(blockCount + blockOffsetMimg, 1);
        if (modelId == -1)
        {
            return;
        }
        streamingInfo = &ms_aInfoForModel[modelId];
    }
    if (modelId == -1)
    {
        return;
    }
    if (streamingInfo->m_nCdSize)
    {
        blockOffsetMimg = streamingInfo->m_nCdPosn + ms_files[streamingInfo->m_nImgId].m_StreamHandle;
        blockCount = streamingInfo->m_nCdSize;
    }
    if (blockCount > ms_streamingBufferSize)
    {
        if (channelIndex == 1 || ms_channel[1].LoadStatus)
        {
            return;
        }
        ms_bLoadingBigModel = 1;
    }

    unsigned int sectorCount = 0;
    bool isVehcileModelORBlockCountGreaterThan200 = false;
    bool isModelTypePed = false;

    int modelIndex = 0;
    const int numberOfModelIds = sizeof(tStreamingChannel::modelIds) / sizeof(tStreamingChannel::modelIds[0]);
    while (modelIndex < numberOfModelIds)
    {
        streamingInfo = &ms_aInfoForModel[modelId];
        if (streamingInfo->m_nLoadState != LOADSTATE_Requested)
        {
            break;
        }
        if (streamingInfo->m_nCdSize)
        {
            blockCount = streamingInfo->m_nCdSize;
        }
        if (ms_numPriorityRequests && !(streamingInfo->m_nFlags & PRIORITY_REQUEST))
        {
            break;
        }
        if (modelId >= RESOURCE_ID_TXD)
        {
            if (modelId < RESOURCE_ID_IFP || modelId >= RESOURCE_ID_RRR)
            {
                if (isVehcileModelORBlockCountGreaterThan200 && blockCount > 200)
                {
                    break;
                }
            }
            else if (CCutsceneMgr::ms_cutsceneProcessing || ms_aInfoForModel[7].m_nLoadState != LOADSTATE_LOADED)
            {
                break;
            }
        }
        else
        {
            CBaseModelInfo * pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
            ModelInfoType modelType = pBaseModelInfo->GetModelType();
            if (isModelTypePed && modelType == MODEL_INFO_PED)
            {
                break;
            }
            if (isVehcileModelORBlockCountGreaterThan200 && modelType == MODEL_INFO_VEHICLE)
            {
                break;
            }
            unsigned char loadState = ms_aInfoForModel[pBaseModelInfo->m_nTxdIndex + RESOURCE_ID_TXD].m_nLoadState;
            if (loadState != LOADSTATE_LOADED && loadState != LOADSTATE_Channeled)
            {
                break;
            }
            int animFileIndex = pBaseModelInfo->GetAnimFileIndex();
            if (animFileIndex != -1)
            {
                unsigned char loadState = ms_aInfoForModel[animFileIndex + RESOURCE_ID_IFP].m_nLoadState;
                if (loadState != LOADSTATE_LOADED && loadState != LOADSTATE_Channeled)
                    break;
            }
        }

        tStreamingChannel & streamingChannel = ms_channel[channelIndex];
        streamingChannel.modelStreamingBufferOffsets[modelIndex] = sectorCount;
        streamingChannel.modelIds[modelIndex] = modelId;

        sectorCount += blockCount;
        if (sectorCount > ms_streamingBufferSize && modelIndex > 0)
        {
            sectorCount = sectorCount - blockCount;
            break;
        }


        CBaseModelInfo *  pBaseModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
        if (modelId >= RESOURCE_ID_TXD)
        {
            if (blockCount > 200)
            {
                isVehcileModelORBlockCountGreaterThan200 = true;
            }
        }
        else
        {
            if (pBaseModelInfo->GetModelType() == MODEL_INFO_PED)
            {
                isModelTypePed = true;
            }
            if (pBaseModelInfo->GetModelType() == MODEL_INFO_VEHICLE)
            {
                isVehcileModelORBlockCountGreaterThan200 = true;
            }
        }

        streamingInfo->m_nLoadState = LOADSTATE_Channeled;
        streamingInfo->RemoveFromList();
        --ms_numModelsRequested;

        if (streamingInfo->m_nFlags & PRIORITY_REQUEST)
        {
            int numPriorityRequests = ms_numPriorityRequests - 1;
            streamingInfo->m_nFlags &= ~PRIORITY_REQUEST;
            ms_numPriorityRequests = numPriorityRequests;
        }

        modelId = streamingInfo->m_nNextIndexOnCd;
        modelIndex++;
    }

    if (modelIndex < numberOfModelIds)
    {
        tStreamingChannel & streamingChannel = ms_channel[channelIndex];
        memset(&streamingChannel.modelIds[modelIndex], 0xFFu, 4 * (numberOfModelIds - modelIndex)); // 0xFFu = -1
    }

    CdStreamRead(channelIndex, ms_pStreamingBuffer[channelIndex], blockOffsetMimg, sectorCount);

    tStreamingChannel & streamingChannel = ms_channel[channelIndex];
    streamingChannel.LoadStatus = LOADSTATE_LOADED;
    streamingChannel.iLoadingLevel = 0;
    streamingChannel.iBlockCount = sectorCount;
    streamingChannel.iBlockOffset = blockOffsetMimg;
    streamingChannel.totalTries = 0;

    if (m_bModelStreamNotLoaded)
        m_bModelStreamNotLoaded = false;
#endif
}

void CStreaming::RequestSpecialChar(int modelId, char const* name, int flags)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int, char const*, int>(0x40B450, modelId, name, flags);
#else
    return CStreaming::RequestSpecialModel(modelId + 290, name, flags);
#endif
}

void CStreaming::RequestSpecialModel(int modelId, char const* name, int flags)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int, char const*, int>(0x409D10, modelId, name, flags);
#else
    CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
    CStreamingInfo& streamingInfo = CStreaming::ms_aInfoForModel[modelId];
    unsigned int CdPosn, CdSize;
    if (CKeyGen::GetUppercaseKey(name) == pModelInfo->m_nKey && streamingInfo.GetCdPosnAndSize(&CdPosn, &CdSize)) {
        RequestModel(modelId, flags);
        return;
    }
    if (pModelInfo->m_nRefCount > 0) {
        for (int i = CPools::ms_pPedPool->GetSize() - 1; i >= 0; i--) {
            if (pModelInfo->m_nRefCount <= 0)
                break;
            CPed* pPed = CPools::ms_pPedPool->GetAt(i);
            if (pPed && pPed->m_nModelIndex == modelId && !pPed->IsPlayer() && pPed->CanBeDeletedEvenInVehicle()) {
                CTheScripts::RemoveThisPed(pPed);
            }
        }
        for (int i = CPools::ms_pObjectPool->GetSize() - 1; i >= 0; i--) {
            if (pModelInfo->m_nRefCount <= 0)
                break;
            CObject* pObject = CPools::ms_pObjectPool->GetAt(i);
            if (pObject && pObject->m_nModelIndex == modelId &&  pObject->CanBeDeleted()) {
                CWorld::Remove(pObject);
                CWorld::RemoveReferencesToDeletedObject(pObject);
                pObject->DeletingDestructor(1); // TODO: Use delete
            }
        }
    }
    const unsigned int modelNameKey = pModelInfo->m_nKey;
    pModelInfo->m_nKey = CKeyGen::GetUppercaseKey(name);
    CBaseModelInfo* pFoundModelInfo = nullptr;
    for (int i = 0; i < 1001; i++) {
        CBaseModelInfo* pTheModelInfo = CModelInfo::ms_modelInfoPtrs[i];
        if (pTheModelInfo && modelNameKey == pTheModelInfo->m_nKey) {
            pFoundModelInfo = pTheModelInfo;
        }
    }
    if (pFoundModelInfo && pFoundModelInfo->m_nTxdIndex != -1 && CTxdStore::ms_pTxdPool->GetAt(pFoundModelInfo->m_nTxdIndex)) {
        CTxdStore::AddRef(pFoundModelInfo->m_nTxdIndex);
        RemoveModel(modelId);
        CTxdStore::RemoveRefWithoutDelete(pFoundModelInfo->m_nTxdIndex);
    }
    else {
        RemoveModel(modelId);
    }
    unsigned int outOffset, outStreamingSize;
    CStreaming::ms_pExtraObjectsDir->FindItem(name, outOffset, outStreamingSize);
    pModelInfo->ClearTexDictionary();
    if (CTxdStore::FindTxdSlot(name) == -1)
        pModelInfo->SetTexDictionary("generic");
    else
        pModelInfo->SetTexDictionary(name);
    // The first 3 bytes of outOffset is used for m_nCdPosn and 
    // the remaining 1 byte is used for m_nImgId
    // outOffset & 0xFFFFF = returns the first 3 bytes and ignores the last one
    // outOffset >> 24 = Ignores the first 3 bytes and returns the last byte
    streamingInfo.m_nCdPosn = outOffset & 0xFFFFFF;
    streamingInfo.m_nCdSize = outStreamingSize;
    streamingInfo.m_nImgId = outOffset >> 24;
    streamingInfo.m_nNextIndexOnCd = -1;
    RequestModel(modelId, flags);
#endif
}

bool CStreaming::ProcessLoadingChannel(int channelIndex)
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<bool, int>(0x40E170, channelIndex);
#else
    tStreamingChannel& streamingChannel = ms_channel[channelIndex];
    int streamStatus = CdStreamGetStatus(channelIndex);
    if (streamStatus) {
        if (streamStatus == 255)
            return false;
        if (streamStatus == 250)
            return false;
        streamingChannel.m_nCdStreamStatus = streamStatus;
        streamingChannel.LoadStatus = LOADSTATE_Channeled;

        bool isChannelErrorFree = ms_channelError == -1;
        if (!isChannelErrorFree)
            return false;
        ms_channelError = channelIndex;
        RetryLoadFile(channelIndex);
        return true;
    }

    bool isRequested = streamingChannel.LoadStatus == LOADSTATE_Requested;
    streamingChannel.LoadStatus = LOADSTATE_NOT_LOADED; // 0;
    if (!isRequested) {
        int numberOfModelIds = sizeof(tStreamingChannel::modelIds) / sizeof(tStreamingChannel::modelIds[0]);
        for (int modelIndex = 0; modelIndex < numberOfModelIds; modelIndex++) {
            int modelId = streamingChannel.modelIds[modelIndex];
            if (modelId != -1) {
                CBaseModelInfo* baseModelInfo = CModelInfo::GetModelInfo(modelId);
                CStreamingInfo& streamingInfo = ms_aInfoForModel[modelId];
                int nCdSize = streamingInfo.m_nCdSize;

                if (modelId >= RESOURCE_ID_TXD
                    || baseModelInfo->GetModelType() != MODEL_INFO_VEHICLE
                    || ms_vehiclesLoaded.CountMembers() < desiredNumVehiclesLoaded
                    || RemoveLoadedVehicle()
                    || streamingInfo.m_nFlags & (MISSION_REQUIRED | GAME_REQUIRED))
                {
                    if (modelId < RESOURCE_ID_IPL || modelId >= RESOURCE_ID_DAT)
                        MakeSpaceFor(nCdSize << 11); // MakeSpaceFor(nCdSize * (2^11))

                    int bufferOffset = streamingChannel.modelStreamingBufferOffsets[modelIndex];
                    unsigned char * pFileBuffer = reinterpret_cast <unsigned char*> (&ms_pStreamingBuffer[channelIndex][2048 * bufferOffset]);

                    ConvertBufferToObject(pFileBuffer, modelId);

                    if (streamingInfo.m_nLoadState != LOADSTATE_Finishing
                        || (streamingChannel.LoadStatus = LOADSTATE_Requested,
                            streamingChannel.modelStreamingBufferOffsets[modelIndex] = bufferOffset,
                            streamingChannel.modelIds[modelIndex] = modelId,
                            modelIndex))
                    {
                        streamingChannel.modelIds[modelIndex] = -1;
                    }
                }
                else {
                    int modelTxdIndex = baseModelInfo->m_nTxdIndex;
                    RemoveModel(modelId);
                    if (streamingInfo.m_nFlags & (MISSION_REQUIRED | GAME_REQUIRED))
                        RequestModel(modelId, streamingInfo.m_nFlags);
                    else if (!CTxdStore::GetNumRefs(modelTxdIndex))
                        RemoveTxdModel(modelTxdIndex);
                }
            }
        }
    }
    else
    {
        int bufferOffset = streamingChannel.modelStreamingBufferOffsets[0];
        unsigned char * pFileContents = reinterpret_cast<unsigned char*>(&ms_pStreamingBuffer[channelIndex][2048 * bufferOffset]);
        FinishLoadingLargeFile(pFileContents, streamingChannel.modelIds[0]);
        streamingChannel.modelIds[0] = -1;
    }

    if (ms_bLoadingBigModel)
    {
        if (streamingChannel.LoadStatus != LOADSTATE_Requested)
        {
            ms_bLoadingBigModel = false;
            memset(&ms_channel[1], 0xFFu, 64u);
        }
    }
    return true;
#endif
}

void CStreaming::ReadIniFile() {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<>(0x5BCCD0);
#else
    bool bHasDevkitMemory = false;
    FILE* file = CFileMgr::OpenFile("stream.ini", "r");
    for (char* line = CFileLoader::LoadLine(file); line; line = CFileLoader::LoadLine(file))
    {
        if (*line != '#' && *line)
        {
            char* attribute = strtok(line, " ,\t");
            char* value = strtok(0, " ,\t");
            if (stricmp(attribute, "memory") || bHasDevkitMemory)
            {
                if (!stricmp(attribute, "devkit_memory"))
                {
                    CStreaming::ms_memoryAvailable = atoi(value) << 10;
                    bHasDevkitMemory = true;
                }
                else if (!stricmp(attribute, "vehicles"))
                {
                    CStreaming::desiredNumVehiclesLoaded = atoi(value);
                }
                else if (!stricmp(attribute, "dontbuildpaths"))
                {
                    //bDontBuildPaths = 1; // unused
                }
                else if (!stricmp(attribute, "pe_lightchangerate"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE = static_cast<float>(atof(value));
                }
                else if (!stricmp(attribute, "pe_lightingbasecap"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP = static_cast<float>(atof(value));
                }
                else if (!stricmp(attribute, "pe_lightingbasemult"))
                {
                    CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT = static_cast<float>(atof(value));
                }
                else if (!stricmp(attribute, "pe_leftx"))
                {
                    CPostEffects::m_colourLeftUOffset = atoi(value);
                }
                else if (!stricmp(attribute, "pe_rightx"))
                {
                    CPostEffects::m_colourRightUOffset = atoi(value);
                }
                else if (!stricmp(attribute, "pe_topy"))
                {
                    CPostEffects::m_colourTopVOffset = atoi(value);
                }
                else if (!stricmp(attribute, "pe_bottomy"))
                {
                    CPostEffects::m_colourBottomVOffset = atoi(value);
                }
                else if (!stricmp(attribute, "pe_bRadiosity"))
                {
                    CPostEffects::m_bRadiosity = atoi(value) != 0;
                }
                else if (!stricmp(attribute, "def_brightness_pal"))
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
#endif
}

void CStreaming::RemoveCarModel(int modelIndex) {
    plugin::CallDynGlobal<int>(0x4080F0, modelIndex);
}

void CStreaming::RemoveModel(int modelId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int>(0x4089A0, modelId);
#else
    CStreamingInfo& streamingInfo = CStreaming::ms_aInfoForModel[modelId];;
    if (streamingInfo.m_nLoadState == LOADSTATE_NOT_LOADED)
        return;
    if (streamingInfo.m_nLoadState == LOADSTATE_LOADED) {
        if (modelId >= RESOURCE_ID_DFF && modelId < RESOURCE_ID_TXD) {
            CBaseModelInfo* pModelInfo = CModelInfo::ms_modelInfoPtrs[modelId];
            pModelInfo->DeleteRwObject();
            if (pModelInfo->GetModelType() == MODEL_INFO_PED) {
                int numPedsLoaded = CStreaming::ms_numPedsLoaded;
                for (int i = 0; i < 8; i++) {
                    if (CStreaming::ms_pedsLoaded[i] == modelId) {
                        CStreaming::ms_pedsLoaded[i] = -1;
                        numPedsLoaded--;
                    }
                }
                CStreaming::ms_numPedsLoaded = numPedsLoaded;
            }
            else if (pModelInfo->GetModelType() == MODEL_INFO_VEHICLE) {
                RemoveCarModel(modelId);
            }
        }
        else if (modelId >= RESOURCE_ID_TXD && modelId < RESOURCE_ID_COL) {
            CTxdStore::RemoveTxd(modelId - RESOURCE_ID_TXD);
        }
        else if (modelId >= RESOURCE_ID_COL && modelId < RESOURCE_ID_IPL) {
            CColStore::RemoveCol(modelId - RESOURCE_ID_COL);
        }
        else if (modelId >= RESOURCE_ID_IPL && modelId < RESOURCE_ID_DAT) {
            CIplStore::RemoveIpl(modelId - RESOURCE_ID_IPL);
        }
        else if (modelId >= RESOURCE_ID_DAT && modelId < RESOURCE_ID_IFP) {
            ThePaths.UnLoadPathFindData(modelId - RESOURCE_ID_DAT);
        }
        else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR) {
            CAnimManager::RemoveAnimBlock(modelId - RESOURCE_ID_IFP);
        }
        else if (modelId >= RESOURCE_ID_SCM) {
            CTheScripts::StreamedScripts.RemoveStreamedScriptFromMemory(modelId - RESOURCE_ID_SCM);
        }
        CStreaming::ms_memoryUsed -= 2048 * streamingInfo.m_nCdSize;
    }
    if (streamingInfo.m_nNextIndex == -1) {
        if (streamingInfo.m_nLoadState == LOADSTATE_Channeled) {
            for (int i = 0; i < 16; i++) {
                for (int channelId = 0; channelId < 2; channelId++) {
                    if (ms_channel[channelId].modelIds[i] == modelId)
                        ms_channel[channelId].modelIds[i] = -1;
                }
            }
        }
    }
    else {
        if (streamingInfo.m_nLoadState == LOADSTATE_Requested) {
            CStreaming::ms_numModelsRequested--;
            if (streamingInfo.m_nFlags & PRIORITY_REQUEST) {
                streamingInfo.m_nFlags &= ~PRIORITY_REQUEST;
                CStreaming::ms_numPriorityRequests--;
            }
        }
        streamingInfo.RemoveFromList();
    }
    if (streamingInfo.m_nLoadState == LOADSTATE_Finishing) {
        if (modelId < RESOURCE_ID_TXD)
            RpClumpGtaCancelStream();
        else if (modelId < RESOURCE_ID_COL)
            CTxdStore::RemoveTxd(modelId - RESOURCE_ID_TXD);
        else if (modelId < RESOURCE_ID_IPL)
            CColStore::RemoveCol(modelId - RESOURCE_ID_COL);
        else if (modelId < RESOURCE_ID_DAT)
            CIplStore::RemoveIpl(modelId - RESOURCE_ID_IPL);
        else if (modelId >= RESOURCE_ID_IFP && modelId < RESOURCE_ID_RRR)
            CAnimManager::RemoveAnimBlock(modelId - RESOURCE_ID_IFP);
        else if (modelId >= RESOURCE_ID_SCM)
            CTheScripts::StreamedScripts.RemoveStreamedScriptFromMemory(modelId - RESOURCE_ID_SCM);
    }
    streamingInfo.m_nLoadState = LOADSTATE_NOT_LOADED;
#endif
}

void CStreaming::RemoveTxdModel(int modelId)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int>(0x40C180, modelId);
#else
    RemoveModel(modelId + RESOURCE_ID_TXD);
#endif
}

void CStreaming::MakeSpaceFor(int memoryToCleanInBytes)
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int>(0x40E120, memoryToCleanInBytes);
#else
    if (ms_memoryUsed >= (ms_memoryAvailable - memoryToCleanInBytes))
    {
        while (RemoveLeastUsedModel(0x20u))
        {
            if (ms_memoryUsed < (ms_memoryAvailable - memoryToCleanInBytes))
                return;
        }
        DeleteRwObjectsBehindCamera(ms_memoryAvailable - memoryToCleanInBytes);
    }
#endif
}

bool CStreaming::RemoveLoadedVehicle() {
    return plugin::CallAndReturnDynGlobal<bool>(0x40C020);
}

void CStreaming::RetryLoadFile(int channelId) {
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::CallDynGlobal<int>(0x4076C0, channelId);
#else
    if (CStreaming::ms_channelError == -1) 
        return CLoadingScreen::Continue();
    // CLoadingScreen::Pause(); // empty function
    if (CStreaming::ms_channelError == -1)
        return;
    tStreamingChannel& streamingChannel = CStreaming::ms_channel[channelId];
    while (true) {
        bool bStreamRead = false;
        eStreamingLoadState loadState = streamingChannel.LoadStatus;
        if (loadState == LOADSTATE_NOT_LOADED) {
            bStreamRead = true;
        }
        else if (loadState == LOADSTATE_LOADED) {
            if (CStreaming::ProcessLoadingChannel(channelId)) {
                if (streamingChannel.LoadStatus == LOADSTATE_Requested)
                    CStreaming::ProcessLoadingChannel(channelId);
                CStreaming::ms_channelError = -1;
                return CLoadingScreen::Continue();
            }
        }
        else if (loadState == LOADSTATE_Channeled) {
            streamingChannel.totalTries++;
            int streamStatus = CdStreamGetStatus(channelId);
            if (streamStatus != 255 && streamStatus != 250)
                bStreamRead = true;
            else if (streamStatus == 255 && CdStreamGetStatus(channelId) != 255)
                bStreamRead = true;
        }
        if (bStreamRead) {
            char* pBuffer = CStreaming::ms_pStreamingBuffer[channelId];
            CdStreamRead(channelId, pBuffer, streamingChannel.iBlockOffset, streamingChannel.iBlockCount);
            streamingChannel.LoadStatus = LOADSTATE_LOADED;
            streamingChannel.iLoadingLevel = -600;
        }
        if (CStreaming::ms_channelError == -1)
            return CLoadingScreen::Continue();
    }
#endif
}


void CStreaming::LoadRequestedModels()
{
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::Call<0x40E3A0>();
#else
    unsigned channelIndex = 0;

    if (ms_bLoadingBigModel)
    {
        channelIndex = 0;
        ms_numberOfBytesRead = 0;
    }
    else
    {
        channelIndex = ms_numberOfBytesRead;
    }
    if (ms_channel[channelIndex].LoadStatus)
    {
        ProcessLoadingChannel(channelIndex);
        channelIndex = ms_numberOfBytesRead;
    }
    if (!ms_bLoadingBigModel)
    {
        int otherChannelIndex = 1 - channelIndex;
        if (!ms_channel[otherChannelIndex].LoadStatus)
        {
            RequestModelStream(1 - channelIndex);
            channelIndex = ms_numberOfBytesRead;
        }
        if (!ms_channel[channelIndex].LoadStatus && !ms_bLoadingBigModel)
        {
            RequestModelStream(channelIndex);
            channelIndex = ms_numberOfBytesRead;
        }
    }
    if (ms_channel[channelIndex].LoadStatus != LOADSTATE_Requested)
    {
        ms_numberOfBytesRead = 1 - channelIndex;
    }
#endif
}

void CStreaming::FlushRequestList()
{
#ifdef USE_DEFAULT_FUNCTIONS
    plugin::Call<0x40E4E0>();
#else
    CStreamingInfo *streamingInfo = nullptr;
    CStreamingInfo *nextStreamingInfo = nullptr;

    if (ms_pStartRequestedList->m_nNextIndex == -1)
    {
        streamingInfo = nullptr;
    }
    else
    {
        streamingInfo = &CStreamingInfo::ms_pArrayBase[ms_pStartRequestedList->m_nNextIndex];
    }
    if (streamingInfo != ms_pEndRequestedList)
    {
        do
        {
            if (streamingInfo->m_nNextIndex == -1)
            {
                nextStreamingInfo = nullptr;
            }
            else
            {
                nextStreamingInfo = &CStreamingInfo::ms_pArrayBase[streamingInfo->m_nNextIndex];
            }
            RemoveModel(streamingInfo - ms_aInfoForModel);
            streamingInfo = nextStreamingInfo;
        } while (nextStreamingInfo != ms_pEndRequestedList);
    }
    FlushChannels();
#endif
}

bool CStreaming::AddToLoadedVehiclesList(int modelIndex) {
    return plugin::CallAndReturnDynGlobal<bool, int>(0x408000, modelIndex);
}

void CStreaming::DeleteRwObjectsBehindCamera(int memoryToCleanInBytes) {
    plugin::CallDynGlobal<int>(0x40D7C0, memoryToCleanInBytes);
}

bool CStreaming::RemoveLeastUsedModel(unsigned int StreamingFlags) {
    return plugin::CallAndReturnDynGlobal<bool, unsigned int>(0x40CFD0, StreamingFlags);
}


void CStreaming::SetModelIsDeletable(int modelIndex) {
    plugin::CallDynGlobal<int>(0x409C10, modelIndex);
}

void CStreaming::SetModelTxdIsDeletable(int modelIndex) {
    plugin::CallDynGlobal<int>(0x409C70, modelIndex);
}

int CStreaming::GetDefaultCopCarModel(int ignoreLvpd1Model) {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<int, unsigned int>(0x407C50, ignoreLvpd1Model);
#else
    int carModelId = ms_DefaultCopBikeModel;
    if (!m_bCopBikeLoaded || ignoreLvpd1Model ||
        ms_aInfoForModel[ms_DefaultCopBikerModel].m_nLoadState != LOADSTATE_LOADED ||
        ms_aInfoForModel[ms_DefaultCopBikeModel].m_nLoadState != LOADSTATE_LOADED)
    {
        carModelId = ms_aDefaultCopCarModel[CTheZones::m_CurrLevel];
        if (ms_aInfoForModel[ms_aDefaultCopModel[CTheZones::m_CurrLevel]].m_nLoadState != LOADSTATE_LOADED
            || ms_aInfoForModel[carModelId].m_nLoadState != LOADSTATE_LOADED)
        {
            int elementCount = 4;
            if (ignoreLvpd1Model)
                elementCount = 3;
            for (int i = 0; i < elementCount; i++) {
                unsigned char copModelLoadState = ms_aInfoForModel[ms_aDefaultCopModel[i]].m_nLoadState;
                unsigned char copCarModelLoadState = ms_aInfoForModel[ms_aDefaultCopCarModel[i]].m_nLoadState;
                if (copModelLoadState == LOADSTATE_LOADED && copCarModelLoadState == LOADSTATE_LOADED) {
                    return ms_aDefaultCopCarModel[i];
                }
            }
            return -1;
        }
    }
    return carModelId;
#endif
}


int CStreaming::GetDefaultFiremanModel() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<int>(0x407D40);
#else
    return ms_aDefaultFiremanModel[CTheZones::m_CurrLevel];
#endif
}

int CStreaming::GetDefaultMedicModel() {
#ifdef USE_DEFAULT_FUNCTIONS
    return plugin::CallAndReturnDynGlobal<int>(0x407D20);
#else
    return ms_aDefaultMedicModel[CTheZones::m_CurrLevel];
#endif
}