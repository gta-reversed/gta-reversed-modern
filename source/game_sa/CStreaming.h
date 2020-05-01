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

enum eResourceMaxIDs
{
                             // Model ID Range
    RESOURCE_MAX_ID_DFF = 19999, // 0-19999
    RESOURCE_MAX_ID_TXD = 24999, // 20000-24999
    RESOURCE_MAX_ID_COL = 25255, // 25000-25254
    RESOURCE_MAX_ID_IPL = 25510, // 25255-25510
    RESOURCE_MAX_ID_DAT = 25574, // 25511-25574 
    RESOURCE_MAX_ID_IFP = 25754, // 25575-25754
    RESOURCE_MAX_ID_RRR = 26229, // 25755-26229 (vechicle recordings)
    RESOURCE_MAX_ID_SCM = 26311, // 26230-26311 (streamed scripts)
};

enum eResourceFirstID
{
    // First ID of the resource
    RESOURCE_ID_DFF = 0,
    RESOURCE_ID_TXD = 20000,
    RESOURCE_ID_COL = 25000,
    RESOURCE_ID_IPL = 25255,
    RESOURCE_ID_DAT = 25511,
    RESOURCE_ID_IFP = 25575,
    RESOURCE_ID_RRR = 25755, // (vechicle recordings)
    RESOURCE_ID_SCM = 26230, // (streamed scripts)
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
     static unsigned int &desiredNumVehiclesLoaded;
     static bool &ms_bLoadVehiclesInLoadScene;
     static int *ms_aDefaultCopCarModel; // static int ms_aDefaultCopCarModel[4]
     static int &ms_DefaultCopBikeModel;
     static int *ms_aDefaultCopModel; // static int ms_aDefaultCopModel[4]
     static int &ms_DefaultCopBikerModel;
     static signed int *ms_aDefaultAmbulanceModel; // static signed int ms_aDefaultAmbulanceModel[4]
     static signed int *ms_aDefaultMedicModel; // static signed int ms_aDefaultMedicModel[4]
     static signed int *ms_aDefaultFireEngineModel; // static signed int ms_aDefaultFireEngineModel[4]
     static signed int *ms_aDefaultFiremanModel; // static signed int ms_aDefaultFiremanModel[4]
     static signed int *ms_aDefaultCabDriverModel; // static signed int ms_aDefaultCabDriverModel[7]
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
     static char **ms_pStreamingBuffer;
     static unsigned int &ms_memoryUsed;
     static int &ms_numModelsRequested;
     static CStreamingInfo *ms_aInfoForModel; // static CStreamingInfo ms_aInfoForModel[26316]
     static bool &ms_disableStreaming;
     static int &ms_bIsInitialised;
     static bool &m_bBoatsNeeded;
     static bool &m_bLoadingScene;
     static bool &m_bCopBikeLoaded;
     static bool &m_bDisableCopBikes;
     static CLinkList<CEntity*> &ms_rwObjectInstances;
     static bool &m_bLoadingAllRequestedModels;
     static bool &m_bModelStreamNotLoaded;
     static unsigned int &ms_numberOfBytesRead; 
     
     static void InjectHooks();


     static void *AddEntity(CEntity * pEntity);
    //! return StreamingFile Index in CStreaming::ms_files
     static int AddImageToList(char const * pFileName, bool bNotPlayerImg);
     static void AddLodsToRequestList(CVector const *Posn, unsigned int Streamingflags);
     static void AddModelsToRequestList(CVector const *posn, unsigned int StreamingFlags);
     static bool AddToLoadedVehiclesList(int modelIndex);
     static bool AreAnimsUsedByRequestedModels(int animModelId);
     static bool AreTexturesUsedByRequestedModels(int txdModelId);
     static void ClearFlagForAll(unsigned int eStreamingFlag);
     static void ClearSlots(int NumOfSlots);
    //! ChanndelIndex is unused
     static bool ConvertBufferToObject(unsigned char* pFileBuffer, int ChannelIndex);
     static void DeleteAllRwObjects();
     static bool DeleteLeastUsedEntityRwObject(bool bNotOnScreen, unsigned int StreamingFlags);
     static void DeleteRwObjectsAfterDeath(CVector const *PlayerPosn);
     static void DeleteRwObjectsBehindCamera(int memoryToCleanInBytes);
     static bool DeleteRwObjectsBehindCameraInSectorList(CPtrList *List, int memoryToCleanInBytes);
    //! unused
     static void DeleteRwObjectsInSectorList(CPtrList *PtrList, int arg2, int arg3);
     static char DeleteRwObjectsNotInFrustumInSectorList(CPtrList *List, int memoryToCleanInBytes);
     static void DisableCopBikes(bool bDisable);
    //! RandFactor : random number between 1-7
     static int FindMIPedSlotForInterior(int RandFactor);
     static void FinishLoadingLargeFile(unsigned char * pFileBuffer, int modelIndex);
     static void FlushChannels();
     static void FlushRequestList();
     static void ForceLayerToRead(int arg1);
     static int GetDefaultCabDriverModel();
     static int GetDefaultCopCarModel(int ignoreLvpd1Model);
     static int GetDefaultCopModel();
     static int GetDefaultFiremanModel();
     static int GetDefaultMedicModel();
    //! unused
     static signed int GetDiscInDrive();
    //! return modelIndex
     static int GetNextFileOnCd(unsigned int streamLastPosn, bool bNotPriority);
     static bool HasSpecialCharLoaded(int slot);
     static bool HasVehicleUpgradeLoaded(int ModelIndex);
    //! does nothing (NOP)
     static void IHaveUsedStreamingMemory();
    //! does nothing (NOP)
     static void ImGonnaUseStreamingMemory();
     static void Init();
     static void Init2();
     static void InitImageList();
     static void InstanceLoadedModels(CVector const *posn);
     static bool IsCarModelNeededInCurrentZone(int VehicleModelIndex);
    //! unused
     static bool IsInitialised();
     static bool IsObjectInCdImage(int ModelInex);
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
     static void LoadScene(CVector const *Posn);
     static void LoadSceneCollision(CVector const *Posn);
    //! unused
     static void LoadZoneVehicle(CVector const *posn);
     static void MakeSpaceFor(int memoryToCleanInBytes);
     static void PossiblyStreamCarOutAfterCreation(int modelId);
     static void ProcessEntitiesInSectorList(CPtrList *list, float posn_x, float posn_y, float min_posn_x, float min_posn_y, float max_posn_x, float max_posn_y, float distance, unsigned int Streamingflags);
     static void ProcessEntitiesInSectorList(CPtrList *list, unsigned int streamingFlags);
     static bool ProcessLoadingChannel(int channelIndex);
     static void PurgeRequestList();
     static unsigned int ReInit();
     static void ReadIniFile();
     static void ReclassifyLoadedCars();
     static void RemoveAllUnusedModels();
     static void RemoveBigBuildings();
     static void RemoveBuildingsNotInArea(int AreaCode);
     static void RemoveCarModel(int modelIndex);
     static void RemoveCurrentZonesModels();
     static void RemoveDodgyPedsFromRandomSlots();
     static void RemoveEntity(CLink<CEntity*> *streamingLink);
     static void RemoveInappropriatePedModels();
     static bool RemoveLeastUsedModel(unsigned int StreamingFlags);
     static bool RemoveLoadedVehicle();
     static bool RemoveLoadedZoneModel();
     static void RemoveModel(int modelId);
     static void RemoveTxdModel(int modelId);
    //! does nothing (NOP)
     static unsigned int RemoveUnusedModelsInLoadedList();
     static void RenderEntity(CLink<CEntity*> *streamingLink);
     static void RequestBigBuildings(CVector const *posn);
     static void RequestFile(int modelId, int posn, int size, int imgId, int streamingFlags);
    //! unused
     static void RequestFilesInChannel(int channelId);
     static void RequestModel(int dwModelId, unsigned int Streamingflags);
     static void RequestModelStream(int streamNum);
    //! unused
     static void RequestPlayerSection(int modelIndex, char const *string, int streamingFlags);
     static void RequestSpecialChar(int modelId, char const *name, int flags);
     static void RequestSpecialModel(int modelId, char const* name, int flags);
     static void RequestTxdModel(int TxdModelID, int flags);
     static void RequestVehicleUpgrade(int modelIndex, int flags);
     static void RetryLoadFile(int channelId);
     static void Save();
     static void SetLoadVehiclesInLoadScene(bool bEnable);
     static void SetMissionDoesntRequireAnim(int slot);
     static void SetMissionDoesntRequireModel(int modelIndex);
     static void SetMissionDoesntRequireSpecialChar(int slot);
     static void SetModelIsDeletable(int modelIndex);
     static void SetModelTxdIsDeletable(int modelIndex);
    //! unused
     static void SetSpecialCharIsDeletable(int slot);
     static void Shutdown();
     static void StartRenderEntities();
     static bool StreamAmbulanceAndMedic(bool bStreamForAccident);
     static void StreamCopModels(int townID);
     static bool StreamFireEngineAndFireman(bool bStreamForFire);
     static void StreamOneNewCar();
    //! interiorType : 0 - house , 1 - shop , 2 - office
     static void StreamPedsForInterior(int interiorType);
     static void StreamPedsIntoRandomSlots(int *pModelID);
     static void StreamVehiclesAndPeds();
     static void StreamVehiclesAndPeds_Always(CVector const *posn);
     static void StreamZoneModels(CVector const *posn);
     static void StreamZoneModels_Gangs(CVector const *unused);
     static void Update();
    //! unused
     static void UpdateForAnimViewer();
     static bool WeAreTryingToPhaseVehicleOut(int modelIndex);
};

 extern RwStream &gRwStream;


//#include "meta/meta.CStreaming.h"
