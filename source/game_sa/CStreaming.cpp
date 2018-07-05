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
tStreamingChannel *CStreaming::ms_channel = reinterpret_cast<tStreamingChannel *>(0x8E4A60);
signed int &CStreaming::ms_channelError = *reinterpret_cast<signed int *>(0x8E4B90);
bool &CStreaming::m_bHarvesterModelsRequested = *reinterpret_cast<bool *>(0x8E4B9C);
bool &CStreaming::m_bStreamHarvesterModelsThisFrame = *reinterpret_cast<bool *>(0x8E4B9D);
unsigned int &CStreaming::ms_numPriorityRequests = *reinterpret_cast<unsigned int *>(0x8E4BA0);
int &CStreaming::ms_lastCullZone = *reinterpret_cast<int *>(0x8E4BA4);
unsigned short &CStreaming::ms_loadedGangCars = *reinterpret_cast<unsigned short *>(0x8E4BA8);
unsigned short &CStreaming::ms_loadedGangs = *reinterpret_cast<unsigned short *>(0x8E4BAC);
unsigned int &CStreaming::ms_numPedsLoaded = *reinterpret_cast<unsigned int *>(0x8E4BB0);
unsigned int **CStreaming::ms_pedsLoaded = reinterpret_cast<unsigned int **>(0x8E4C00);
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
char *&CStreaming::ms_pStreamingBuffer = *reinterpret_cast<char **>(0x8E4CAC);
unsigned int &CStreaming::ms_memoryUsed = *reinterpret_cast<unsigned int *>(0x8E4CB4);
unsigned int &CStreaming::ms_numModelsRequested = *reinterpret_cast<unsigned int *>(0x8E4CB8);
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


bool CStreaming::IsVeryBusy() {
    std::printf("Streaming::IsVeryBusy called\n");
    return CRenderer::m_loadingPriority || CStreaming::ms_numModelsRequested > 5;
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
    if (!CStreaming::m_bLoadingAllRequestedModels)
    {
        CStreaming::m_bLoadingAllRequestedModels = true;
        CStreaming::FlushChannels();
        int numModelsToLoad = 10;
        if (2 * CStreaming::ms_numModelsRequested >= 10)
            numModelsToLoad = 2 * CStreaming::ms_numModelsRequested;

        int channelIndex = 0;
        while (1)
        {
            tStreamingChannel& firstStreamingChannel = CStreaming::ms_channel[0];
            tStreamingChannel& secondStreamingChannel = CStreaming::ms_channel[1];

            short endRequestPreviousIndex = CStreaming::ms_pEndRequestedList->m_nPrevIndex;
            CStreamingInfo * pStreamingInfo = endRequestPreviousIndex == -1 ? 0 : &CStreamingInfo::ms_pArrayBase[endRequestPreviousIndex];

            if (pStreamingInfo == CStreaming::ms_pStartRequestedList
                && !firstStreamingChannel.LoadStatus
                && !secondStreamingChannel.LoadStatus
                || numModelsToLoad <= 0)
            {
                break;
            }

            if (CStreaming::ms_bLoadingBigModel)
            {
                channelIndex = 0;
            }

            tStreamingChannel& streamingChannel = CStreaming::ms_channel[channelIndex];
            if (streamingChannel.LoadStatus)
            {
                CdStreamSync(channelIndex);
                streamingChannel.iLoadingLevel = 100;
            }

            if (streamingChannel.LoadStatus == LOADSTATE_LOADED)
            {
                CStreaming::ProcessLoadingChannel(channelIndex);
                if (streamingChannel.LoadStatus == LOADSTATE_Requested)
                {
                    CStreaming::ProcessLoadingChannel(channelIndex);
                }
            }

            if (bOnlyPriorityRequests && !CStreaming::ms_numPriorityRequests)
            {
                break;
            }

            if (!CStreaming::ms_bLoadingBigModel)
            {
                tStreamingChannel& otherStreamingChannel = CStreaming::ms_channel[1 - channelIndex];
                if (!otherStreamingChannel.LoadStatus)
                {
                    CStreaming::RequestModelStream(1 - channelIndex);
                }

                if (!streamingChannel.LoadStatus && !CStreaming::ms_bLoadingBigModel)
                {
                    CStreaming::RequestModelStream(channelIndex);
                }
            }
            if (!firstStreamingChannel.LoadStatus && !secondStreamingChannel.LoadStatus)
            {
                break;
            }

            channelIndex = 1 - channelIndex;
            --numModelsToLoad;
        }
        CStreaming::FlushChannels();
        CStreaming::m_bLoadingAllRequestedModels = false;
    }

}

void CStreaming::RequestModel(int modelId, char streamingFlags)
{
    int flags = streamingFlags;
    CStreamingInfo & modelStreamingInfo = CStreaming::ms_aInfoForModel[modelId];
    char loadState = modelStreamingInfo.m_nLoadState;
    if (loadState == LOADSTATE_Requested)
    {
        if ((streamingFlags & PRIORITY_REQUEST) && !(modelStreamingInfo.m_nFlags & PRIORITY_REQUEST))
        {
            ++CStreaming::ms_numPriorityRequests;
            modelStreamingInfo.m_nFlags |= PRIORITY_REQUEST;
        }
    }
    else if (loadState)
    {
        flags = streamingFlags & 0xEF;
    }

    modelStreamingInfo.m_nFlags |= flags;
    if (loadState == LOADSTATE_LOADED)
    {
        if (modelStreamingInfo.InList())
        {
            modelStreamingInfo.RemoveFromList();
            if ((modelId < 20000))
            {
                CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
                size_t modelType = modelInfo->GetModelType();
                if (modelType == MODEL_INFO_TYPE_PED && modelType == MODEL_INFO_TYPE_VEHICLE)
                {
                    return;
                }
            }

            if (!(modelStreamingInfo.m_nFlags & (GAME_REQUIRED || MISSION_REQUIRED)))
            {
                modelStreamingInfo.AddToList(CStreaming::ms_startLoadedList);
            }
        }
    }
    else if (loadState != LOADSTATE_Channeled && loadState != LOADSTATE_Requested && loadState != LOADSTATE_Finishing)
    {
        if (loadState == LOADSTATE_NOT_LOADED)
        {
            if (modelId >= 20000)
            {
                if (modelId < 25000)                // txd
                {
                    int txdEntryParentIndex = CTxdStore::GetParentTxdSlot(modelId - 20000);
                    if (txdEntryParentIndex != -1)
                        RequestTxdModel(txdEntryParentIndex, flags);
                }
            }
            else
            {
                CBaseModelInfo* modelInfo = CModelInfo::GetModelInfo(modelId);
                RequestTxdModel(modelInfo->m_nTxdIndex, flags);
                int animFileIndex = modelInfo->GetAnimFileIndex();
                if (animFileIndex != -1)
                    RequestModel(animFileIndex + 25575, KEEP_IN_MEMORY);
            }
            modelStreamingInfo.AddToList(CStreaming::ms_pStartRequestedList);
            ++CStreaming::ms_numModelsRequested;
            if (flags & PRIORITY_REQUEST)
                ++CStreaming::ms_numPriorityRequests;
        }
        modelStreamingInfo.m_nFlags = flags;
        modelStreamingInfo.m_nLoadState = LOADSTATE_Requested;// requested, loading
    }
}

void CStreaming::RequestTxdModel(int txdModelID, int streamingFlags) {
    RequestModel(txdModelID + 20000, streamingFlags);
}

bool CStreaming::FlushChannels()
{
    return plugin::CallAndReturnDynGlobal<bool>(0x40E460);
}

void CStreaming::RequestModelStream(int streamNum)
{
    plugin::CallDynGlobal<int>(0x40CBA0, streamNum);
}

bool CStreaming::ProcessLoadingChannel(int channelIndex)
{
    return plugin::CallAndReturnDynGlobal<bool, int>(0x40E170, channelIndex);
}