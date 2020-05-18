// Working?
/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "PluginBase.h"
#include "CVector.h"
#include "CStreamingInfo.h"
#include "RenderWare.h"
#include "CEntity.h"
#include "CPtrList.h"
#include "CLinkList.h"
#include "CLoadedCarGroup.h"
#include "CDirectory.h"
#include "constants.h"

enum eResourceFirstID
{
    // First ID of the resource
    RESOURCE_ID_DFF = 0, // default: 0
    RESOURCE_ID_TXD = RESOURCE_ID_DFF + TOTAL_DFF_MODEL_IDS, // default: 20000
    RESOURCE_ID_COL = RESOURCE_ID_TXD + TOTAL_TXD_MODEL_IDS, // default: 25000
    RESOURCE_ID_IPL = RESOURCE_ID_COL + TOTAL_COL_MODEL_IDS, // default: 25255
    RESOURCE_ID_DAT = RESOURCE_ID_IPL + TOTAL_IPL_MODEL_IDS, // default: 25511
    RESOURCE_ID_IFP = RESOURCE_ID_DAT + TOTAL_DAT_MODEL_IDS, // default: 25575
    RESOURCE_ID_RRR = RESOURCE_ID_IFP + TOTAL_IFP_MODEL_IDS, // default: 25755   (vechicle recordings)
    RESOURCE_ID_SCM = RESOURCE_ID_RRR + TOTAL_RRR_MODEL_IDS, // default: 26230   (streamed scripts)
    RESOURCE_ID_INTERNAL_1 = RESOURCE_ID_SCM + TOTAL_SCM_MODEL_IDS, // default: 26312
    RESOURCE_ID_INTERNAL_2 = RESOURCE_ID_INTERNAL_1 + 1, // default: 26313
    RESOURCE_ID_INTERNAL_3 = RESOURCE_ID_INTERNAL_2 + 1, // default: 26314
    RESOURCE_ID_INTERNAL_4 = RESOURCE_ID_INTERNAL_3 + 1, // default: 26315
    RESOURCE_ID_TOTAL  // default: 26316
};


struct tRwStreamInitializeData
{
    unsigned char * m_pBuffer;
    unsigned int m_uiBufferSize;
};

VALIDATE_SIZE(tRwStreamInitializeData, 0x8);

struct tStreamingFileDesc
{
  char m_szName[40];
  bool m_bNotPlayerImg;
  char __pad[3];
  int m_StreamHandle;
};

VALIDATE_SIZE(tStreamingFileDesc, 0x30);

struct tStreamingChannel
{
    int modelIds[16];
    int modelStreamingBufferOffsets[16];
    eStreamingLoadState LoadStatus;
    int iLoadingLevel;
    int iBlockOffset;
    int iBlockCount;
    int totalTries;
    int m_nCdStreamStatus;
};

VALIDATE_SIZE(tStreamingChannel, 0x98);

class  CStreaming {
public:
     static unsigned int &ms_memoryAvailable;
     static int &desiredNumVehiclesLoaded;
     static bool &ms_bLoadVehiclesInLoadScene;
     static int *ms_aDefaultCopCarModel; // static int ms_aDefaultCopCarModel[4]
     static int &ms_DefaultCopBikeModel;
     static int *ms_aDefaultCopModel; // static int ms_aDefaultCopModel[4]
     static int &ms_DefaultCopBikerModel;
     static std::uint32_t& ms_nTimePassedSinceLastCopBikeStreamedIn;
     static signed int *ms_aDefaultAmbulanceModel; // static signed int ms_aDefaultAmbulanceModel[4]
     static signed int *ms_aDefaultMedicModel; // static signed int ms_aDefaultMedicModel[4]
     static signed int *ms_aDefaultFireEngineModel; // static signed int ms_aDefaultFireEngineModel[4]
     static signed int *ms_aDefaultFiremanModel; // static signed int ms_aDefaultFiremanModel[4]
     static CDirectory *&ms_pExtraObjectsDir;
     static tStreamingFileDesc *ms_files; // static tStreamingFileDesc ms_files[8]
     static bool &ms_bLoadingBigModel;
     // There are only two channels within CStreaming::ms_channel
     static tStreamingChannel *ms_channel; // static tStreamingChannel ms_channel[2]
     static signed int &ms_channelError;
     static bool &m_bHarvesterModelsRequested;
     static bool &m_bStreamHarvesterModelsThisFrame;
     static unsigned int &ms_numPriorityRequests;
    //! // initialized to -1 and never used
     static int &ms_lastCullZone;
     static unsigned short &ms_loadedGangCars;
     static unsigned short &ms_loadedGangs;
     static int &ms_numPedsLoaded;
     static int *ms_pedsLoaded; // static unsigned int* ms_pedsLoaded[8]
     static std::int32_t* ms_NextPedToLoadFromGroup;
     static int &ms_currentZoneType;
     static CLoadedCarGroup &ms_vehiclesLoaded;
     static CStreamingInfo *&ms_pEndRequestedList;
     static CStreamingInfo *&ms_pStartRequestedList;
     static CStreamingInfo *&ms_pEndLoadedList;
     static CStreamingInfo *&ms_startLoadedList;
    //! initialized but not used?
     static int &ms_lastImageRead;
    //! initialized but never used?
     static signed int *ms_imageOffsets; // static signed int ms_imageOffsets[6]
     static bool &ms_bEnableRequestListPurge;
     static unsigned int &ms_streamingBufferSize;
     static std::uint8_t** ms_pStreamingBuffer;
     static unsigned int &ms_memoryUsed;
     static int &ms_numModelsRequested;
     static CStreamingInfo *ms_aInfoForModel; // static CStreamingInfo ms_aInfoForModel[26316]
     static bool &ms_disableStreaming;
     static int &ms_bIsInitialised;
     static bool &m_bBoatsNeeded;
     static bool &ms_bLoadingScene;
     static bool &m_bCopBikeLoaded;
     static bool &m_bDisableCopBikes;
     static CLinkList<CEntity*> &ms_rwObjectInstances;
     static CLink<CEntity*>*& ms_renderEntityLink;
     static bool &m_bLoadingAllRequestedModels;
     static bool &m_bModelStreamNotLoaded; 
     
     static void InjectHooks();


     static void *AddEntity(CEntity * pEntity);
    //! return StreamingFile Index in CStreaming::ms_files
     static int AddImageToList(char const * pFileName, bool bNotPlayerImg);
     static void AddLodsToRequestList(CVector const& point, unsigned int streamingFlags);
     static void AddModelsToRequestList(CVector const& point, unsigned int streamingFlags);
     static bool AddToLoadedVehiclesList(std::int32_t modelId);
     static bool AreAnimsUsedByRequestedModels(int animModelId);
     static bool AreTexturesUsedByRequestedModels(int txdModelId);
     static void ClearFlagForAll(unsigned int streamingFlag);
     static void ClearSlots(int totalSlots);
     static bool ConvertBufferToObject(unsigned char* pFileBuffer, int modelId);
     static void DeleteAllRwObjects();
     static bool DeleteLeastUsedEntityRwObject(bool bNotOnScreen, unsigned int streamingFlags);
     static void DeleteRwObjectsAfterDeath(CVector const &point);
     static void DeleteRwObjectsBehindCamera(std::int32_t memoryToCleanInBytes);
     static bool DeleteRwObjectsBehindCameraInSectorList(CPtrList& list, std::int32_t memoryToCleanInBytes);
     static void DeleteRwObjectsInSectorList(CPtrList& list, std::int32_t sectorX, std::int32_t sectorY);
     static bool DeleteRwObjectsNotInFrustumInSectorList(CPtrList& list, std::int32_t memoryToCleanInBytes);
     static bool RemoveReferencedTxds(std::int32_t memoryToCleanInBytes);
     static void DisableCopBikes(bool bDisable);
    //! RandFactor : random number between 1-7
     static std::int32_t FindMIPedSlotForInterior(std::int32_t randFactor);
     static void FinishLoadingLargeFile(unsigned char * pFileBuffer, int modelId);
     static void FlushChannels();
     static void FlushRequestList();
     // Sets value of two global vars, the value is then set to false in CStreaming::RequestModelStream
     // It has no affect on the game, so let's leave it
     static void ForceLayerToRead(int arg1);
     static std::int32_t GetDefaultCabDriverModel();
     static int GetDefaultCopCarModel(int ignoreLvpd1Model);
     static std::int32_t GetDefaultCopModel();
     static int GetDefaultFiremanModel();
     static int GetDefaultMedicModel();
    //! unused
     static signed int GetDiscInDrive();
     static int GetNextFileOnCd(unsigned int streamLastPosn, bool bNotPriority);
     static bool HasSpecialCharLoaded(std::int32_t slot);
     static bool HasVehicleUpgradeLoaded(std::int32_t modelId);
    //! does nothing (NOP)
     static void IHaveUsedStreamingMemory();
    //! does nothing (NOP)
     static void ImGonnaUseStreamingMemory();
     static void Init();
     static void Init2();
     static void InitImageList();
     static void InstanceLoadedModels(CVector const& point);
     static void InstanceLoadedModelsInSectorList(CPtrList& list);
     static bool IsCarModelNeededInCurrentZone(int modelId);
    //! unused
     static bool IsInitialised();
     static bool IsObjectInCdImage(int modelId);
     static bool IsVeryBusy();
     static void Load();
     static void LoadAllRequestedModels(bool bOnlyPriorityRequests);
     static void LoadCdDirectory(const char* filename, std::int32_t archiveId);
     static void LoadCdDirectory();
     static void LoadInitialPeds();
    //! does nothing (NOP)
     static void LoadInitialVehicles();
     static void LoadInitialWeapons();
     static void LoadRequestedModels();
     static void LoadScene(CVector const& point);
     static void LoadSceneCollision(CVector const& point);
    //! unused
     static void LoadZoneVehicle(const CVector& point);
     static void MakeSpaceFor(int memoryToCleanInBytes);
     static void PossiblyStreamCarOutAfterCreation(int modelId);
     static void ProcessEntitiesInSectorList(CPtrList& list, float posX, float posY, float minX, float minY, float maxX, float maxY, float radius, std::int32_t streamingflags);
     static void ProcessEntitiesInSectorList(CPtrList& list, std::int32_t streamingFlags);
     static bool ProcessLoadingChannel(int channelIndex);
     static void PurgeRequestList();
     static void ReInit();
     static void ReadIniFile();
     static void ReclassifyLoadedCars();
     static void RemoveAllUnusedModels();
     static void RemoveBigBuildings();
     static void RemoveBuildingsNotInArea(int areaCode);
     static void RemoveCarModel(int modelId);
     static void RemoveCurrentZonesModels();
     static void RemoveDodgyPedsFromRandomSlots();
     static void RemoveEntity(CLink<CEntity*> *streamingLink);
     static void RemoveInappropriatePedModels();
     static bool RemoveLeastUsedModel(unsigned int streamingFlags);
     static bool CarIsCandateForRemoval(std::int32_t modelId);
     static bool RemoveLoadedVehicle();
     static bool ZoneModelIsCandateForRemoval(std::int32_t modelId);
     static bool RemoveLoadedZoneModel();
     static void RemoveModel(int modelId);
     static void RemoveTxdModel(int modelId);
    //! does nothing (NOP)
     static void RemoveUnusedModelsInLoadedList();
     static void RenderEntity(CLink<CEntity*> *streamingLink);
     static void RequestBigBuildings(CVector const& point);
     static void RequestFile(int modelId, int posn, int size, int imgId, int streamingFlags);
    //! unused
     static void RequestFilesInChannel(int channelId);
     static void RequestModel(int dwModelId, unsigned int Streamingflags);
     static void RequestModelStream(int streamNum);
    //! unused
     static void RequestPlayerSection(int modelId, char const *string, int streamingFlags);
     static void RequestSpecialChar(int modelId, char const *name, int flags);
     static void RequestSpecialModel(int modelId, char const* name, int flags);
     static void RequestTxdModel(int slot, int streamingFlags);
     static void RequestVehicleUpgrade(std::int32_t modelId, std::uint32_t streamingFlags);
     static void RetryLoadFile(int channelId);
     static void Save();
     static void SetLoadVehiclesInLoadScene(bool bEnable);
     static void SetMissionDoesntRequireAnim(int slot);
     static void SetMissionDoesntRequireModel(int modelId);
     static void SetMissionDoesntRequireSpecialChar(int slot);
     static void SetModelIsDeletable(int modelId);
     static void SetModelTxdIsDeletable(int modelId);
    //! unused
     static void SetSpecialCharIsDeletable(int slot);
     static void Shutdown();
     static void StartRenderEntities();
     static bool StreamAmbulanceAndMedic(bool bStreamForAccident);
     static void StreamCopModels(int level);
     static bool StreamFireEngineAndFireman(bool bStreamForFire);
     static void StreamOneNewCar();
    //! interiorType : 0 - house , 1 - shop , 2 - office
     static void StreamPedsForInterior(int interiorType);
     static void StreamPedsIntoRandomSlots(int * modelArray);
     static void StreamVehiclesAndPeds();
     static void StreamVehiclesAndPeds_Always(CVector const& unused);
     static void StreamZoneModels(CVector const& unused);
     static void StreamZoneModels_Gangs(CVector const& unused);
     static void Update();
    //! unused
     static void UpdateForAnimViewer();
     static bool WeAreTryingToPhaseVehicleOut(int modelId);
};

 extern RwStream &gRwStream;


//#include "meta/meta.CStreaming.h"
