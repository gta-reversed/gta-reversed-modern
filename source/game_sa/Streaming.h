// Working?
/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Vector.h"
#include "StreamingInfo.h"
#include "RenderWare.h"
#include "Entity.h"
#include "PtrList.h"
#include "LinkList.h"
#include "LoadedCarGroup.h"
#include "Directory.h"
#include "constants.h"

enum class eChannelState
{
    IDLE = 0,
    READING = 1,
    STARTED = 2, // NOTE: This one seems to be related to big models in some way..
    ERR = 3, // Also called ERROR, but that's a `windgi.h` macro
};

enum eResourceFirstID {
    // First ID of the resource
    RESOURCE_ID_DFF = 0,                                            // default: 0
    RESOURCE_ID_TXD = RESOURCE_ID_DFF + TOTAL_DFF_MODEL_IDS,        // default: 20000
    RESOURCE_ID_COL = RESOURCE_ID_TXD + TOTAL_TXD_MODEL_IDS,        // default: 25000
    RESOURCE_ID_IPL = RESOURCE_ID_COL + TOTAL_COL_MODEL_IDS,        // default: 25255
    RESOURCE_ID_DAT = RESOURCE_ID_IPL + TOTAL_IPL_MODEL_IDS,        // default: 25511
    RESOURCE_ID_IFP = RESOURCE_ID_DAT + TOTAL_DAT_MODEL_IDS,        // default: 25575
    RESOURCE_ID_RRR = RESOURCE_ID_IFP + TOTAL_IFP_MODEL_IDS,        // default: 25755   (vehicle recordings)
    RESOURCE_ID_SCM = RESOURCE_ID_RRR + TOTAL_RRR_MODEL_IDS,        // default: 26230   (streamed scripts)
    RESOURCE_ID_INTERNAL_1 = RESOURCE_ID_SCM + TOTAL_SCM_MODEL_IDS, // default: 26312
    RESOURCE_ID_INTERNAL_2 = RESOURCE_ID_INTERNAL_1 + 1,            // default: 26313
    RESOURCE_ID_INTERNAL_3 = RESOURCE_ID_INTERNAL_2 + 1,            // default: 26314
    RESOURCE_ID_INTERNAL_4 = RESOURCE_ID_INTERNAL_3 + 1,            // default: 26315
    RESOURCE_ID_TOTAL                                               // default: 26316
};

enum class eModelType {
    DFF,
    TXD,
    COL,
    IPL,
    DAT,
    IFP,
    RRR,
    SCM,

    INTERNAL_1,
    INTERNAL_2,
    INTERNAL_3,
    INTERNAL_4
};

// Helper functions to deal with modelID's

eModelType GetModelType(uint32 model) {
    if (eResourceFirstID::RESOURCE_ID_DFF <= model && model < eResourceFirstID::RESOURCE_ID_TXD)
        return eModelType::DFF;

    if (eResourceFirstID::RESOURCE_ID_TXD <= model && model < eResourceFirstID::RESOURCE_ID_COL)
        return eModelType::TXD;

    if (eResourceFirstID::RESOURCE_ID_COL <= model && model < eResourceFirstID::RESOURCE_ID_IPL)
        return eModelType::COL;

    if (eResourceFirstID::RESOURCE_ID_IPL <= model && model < eResourceFirstID::RESOURCE_ID_DAT)
        return eModelType::IPL;

    if (eResourceFirstID::RESOURCE_ID_DAT <= model && model < eResourceFirstID::RESOURCE_ID_IFP)
        return eModelType::DAT;

    if (eResourceFirstID::RESOURCE_ID_IFP <= model && model < eResourceFirstID::RESOURCE_ID_RRR)
        return eModelType::IFP;

    if (eResourceFirstID::RESOURCE_ID_RRR <= model && model < eResourceFirstID::RESOURCE_ID_SCM)
        return eModelType::RRR;

    if (eResourceFirstID::RESOURCE_ID_SCM <= model && model < eResourceFirstID::RESOURCE_ID_INTERNAL_1)
        return eModelType::SCM;

    if (eResourceFirstID::RESOURCE_ID_INTERNAL_1 <= model && model < eResourceFirstID::RESOURCE_ID_INTERNAL_2)
        return eModelType::INTERNAL_1;

    if (eResourceFirstID::RESOURCE_ID_INTERNAL_2 <= model && model < eResourceFirstID::RESOURCE_ID_INTERNAL_3)
        return eModelType::INTERNAL_2;

    if (eResourceFirstID::RESOURCE_ID_INTERNAL_3 <= model && model < eResourceFirstID::RESOURCE_ID_INTERNAL_4)
        return eModelType::INTERNAL_3;

    if (eResourceFirstID::RESOURCE_ID_INTERNAL_4 <= model && model < eResourceFirstID::RESOURCE_ID_TOTAL)
        return eModelType::INTERNAL_4;
}

inline bool IsModelDFF(uint32 model) { return GetModelType(model) == eModelType::DFF; }
inline bool IsModelTXD(uint32 model) { return GetModelType(model) == eModelType::TXD; }
inline bool IsModelCOL(uint32 model) { return GetModelType(model) == eModelType::COL; }
inline bool IsModelIPL(uint32 model) { return GetModelType(model) == eModelType::IPL; }
inline bool IsModelDAT(uint32 model) { return GetModelType(model) == eModelType::DAT; }
inline bool IsModelIFP(uint32 model) { return GetModelType(model) == eModelType::IFP; }
inline bool IsModelRRR(uint32 model) { return GetModelType(model) == eModelType::RRR; }
inline bool IsModelSCM(uint32 model) { return GetModelType(model) == eModelType::SCM; }
inline bool IsModelInternal1(uint32 model) { return GetModelType(model) == eModelType::INTERNAL_1; }
inline bool IsModelInternal2(uint32 model) { return GetModelType(model) == eModelType::INTERNAL_2; }
inline bool IsModelInternal3(uint32 model) { return GetModelType(model) == eModelType::INTERNAL_3; }
inline bool IsModelInternal4(uint32 model) { return GetModelType(model) == eModelType::INTERNAL_4; }

// Turn relative IDs into absolute ones.
inline uint32 ToDFFModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_DFF + relativeId; }
inline uint32 ToTXDModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_TXD + relativeId; }
inline uint32 ToCOLModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_COL + relativeId; }
inline uint32 ToIPLModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_IPL + relativeId; }
inline uint32 ToDATModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_DAT + relativeId; }
inline uint32 ToIFPModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_IFP + relativeId; }
inline uint32 ToRRRModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_RRR + relativeId; }
inline uint32 ToSCMModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_SCM + relativeId; }
inline uint32 ToInternal1ModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_INTERNAL_1 + relativeId; }
inline uint32 ToInternal2ModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_INTERNAL_2 + relativeId; }
inline uint32 ToInternal3ModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_INTERNAL_3 + relativeId; }
inline uint32 ToInternal4ModelId(uint32 relativeId) { return (uint32)eResourceFirstID::RESOURCE_ID_INTERNAL_4 + relativeId; }

struct tRwStreamInitializeData {
    uint8* m_pBuffer;
    uint32 m_uiBufferSize;
};

VALIDATE_SIZE(tRwStreamInitializeData, 0x8);

struct tStreamingFileDesc {
    tStreamingFileDesc() = default;

    tStreamingFileDesc(const char* name, bool bNotPlayerImg) :
        m_bNotPlayerImg(bNotPlayerImg),
        m_StreamHandle(CdStreamOpen(name))
    {
        strncpy_s(m_szName, name, std::size(m_szName));
    }

    bool IsInUse() const noexcept {
        return m_szName[0];
    }

    char  m_szName[40]{}; // If this string is empty (eg.: first elem in array is NULL) the entry isnt in use
    bool  m_bNotPlayerImg{};
    char  __pad[3]{};
    int32 m_StreamHandle{-1};
};

VALIDATE_SIZE(tStreamingFileDesc, 0x30);

struct tStreamingChannel {
    int32               modelIds[16];
    int32               modelStreamingBufferOffsets[16];
    eChannelState LoadStatus;
    int32               iLoadingLevel; // the value gets modified, but it's not used
    int32               offsetAndHandle;
    int32               sectorCount;
    int32               totalTries;
    eCdStreamStatus     m_nCdStreamStatus;
};

VALIDATE_SIZE(tStreamingChannel, 0x98);

class CStreaming {
public:
    static const int32 TOTAL_SPECIAL_MODELS = 10;
    static const int32 TOTAL_CLOTHES_MODELS = 10;
    static const int32 TOTAL_CUTSCENE_MODELS = 20;
    static const int32 SPECIAL_MODELS_RESOURCE_ID = 290;
    static const int32 CLOTHES_MODELS_RESOURCE_ID = 384;
    static const int32 CUTSCENE_MODELS_RESOURCE_ID = 300;
    static uint32& ms_memoryAvailable;
    static int32& desiredNumVehiclesLoaded;
    static bool& ms_bLoadVehiclesInLoadScene;
    static int32* ms_aDefaultCopCarModel; // static int32 ms_aDefaultCopCarModel[4]
    static int32& ms_DefaultCopBikeModel;
    static int32* ms_aDefaultCopModel; // static int32 ms_aDefaultCopModel[4]
    static int32& ms_DefaultCopBikerModel;
    static uint32& ms_nTimePassedSinceLastCopBikeStreamedIn;
    static signed int* ms_aDefaultAmbulanceModel;  // static signed int ms_aDefaultAmbulanceModel[4]
    static signed int* ms_aDefaultMedicModel;      // static signed int ms_aDefaultMedicModel[4]
    static signed int* ms_aDefaultFireEngineModel; // static signed int ms_aDefaultFireEngineModel[4]
    static signed int* ms_aDefaultFiremanModel;    // static signed int ms_aDefaultFiremanModel[4]
    static CDirectory*& ms_pExtraObjectsDir;
    static tStreamingFileDesc (&ms_files)[TOTAL_IMG_ARCHIVES];
    static bool& ms_bLoadingBigModel;
    // There are only two channels within CStreaming::ms_channel
    static tStreamingChannel* ms_channel; // static tStreamingChannel ms_channel[2]
    static signed int& ms_channelError;
    static bool& m_bHarvesterModelsRequested;
    static bool& m_bStreamHarvesterModelsThisFrame;
    static uint32& ms_numPriorityRequests;
    //! // initialized to -1 and never used
    static int32& ms_lastCullZone;
    static uint16& ms_loadedGangCars;
    static uint16& ms_loadedGangs;
    static int32& ms_numPedsLoaded;
    static int32(&ms_pedsLoaded)[8];
    static int32* ms_NextPedToLoadFromGroup;
    static int32& ms_currentZoneType;
    static CLoadedCarGroup& ms_vehiclesLoaded;
    static CStreamingInfo*& ms_pEndRequestedList;
    static CStreamingInfo*& ms_pStartRequestedList;
    static CStreamingInfo*& ms_pEndLoadedList;
    static CStreamingInfo*& ms_startLoadedList;
    //! initialized but not used?
    static int32& ms_lastImageRead;
    //! initialized but never used?
    static signed int* ms_imageOffsets; // static signed int ms_imageOffsets[6]
    static bool& ms_bEnableRequestListPurge;
    static uint32& ms_streamingBufferSize;
    static uint8** ms_pStreamingBuffer;
    static uint32& ms_memoryUsed;
    static int32& ms_numModelsRequested;
    static CStreamingInfo* ms_aInfoForModel; // static CStreamingInfo ms_aInfoForModel[26316]
    static bool& ms_disableStreaming;
    static int32& ms_bIsInitialised;
    static bool& m_bBoatsNeeded;
    static bool& ms_bLoadingScene;
    static bool& m_bCopBikeLoaded;
    static bool& m_bDisableCopBikes;
    static CLinkList<CEntity*>& ms_rwObjectInstances;
    static CLink<CEntity*>*& ms_renderEntityLink;
    static bool& m_bLoadingAllRequestedModels;
    static bool& m_bModelStreamNotLoaded;

public:
    static void InjectHooks();

    static CLink<CEntity*>* AddEntity(CEntity* pEntity);
    //! return StreamingFile Index in CStreaming::ms_files
    static uint32 AddImageToList(char const* pFileName, bool bNotPlayerImg);
    static void AddLodsToRequestList(CVector const& point, uint32 streamingFlags);
    static void AddModelsToRequestList(CVector const& point, uint32 streamingFlags);
    static bool AddToLoadedVehiclesList(int32 modelId);
    static bool AreAnimsUsedByRequestedModels(int32 animModelId);
    static bool AreTexturesUsedByRequestedModels(int32 txdModelId);
    static void ClearFlagForAll(uint32 streamingFlag);
    static void ClearSlots(int32 totalSlots);
    static bool ConvertBufferToObject(uint8* pFileBuffer, int32 modelId);
    static void DeleteAllRwObjects();
    static bool DeleteLeastUsedEntityRwObject(bool bNotOnScreen, uint32 streamingFlags);
    static void DeleteRwObjectsAfterDeath(CVector const& point);
    static void DeleteRwObjectsBehindCamera(int32 memoryToCleanInBytes);
    static bool DeleteRwObjectsBehindCameraInSectorList(CPtrList& list, int32 memoryToCleanInBytes);
    static void DeleteRwObjectsInSectorList(CPtrList& list, int32 sectorX = -1, int32 sectorY = -1);
    static bool DeleteRwObjectsNotInFrustumInSectorList(CPtrList& list, int32 memoryToCleanInBytes);
    static bool RemoveReferencedTxds(int32 memoryToCleanInBytes);
    static void DisableCopBikes(bool bDisable);
    //! RandFactor : random number between 1-7
    static int32 FindMIPedSlotForInterior(int32 randFactor);
    static void FinishLoadingLargeFile(uint8* pFileBuffer, int32 modelId);
    static void FlushChannels();
    static void FlushRequestList();
    // Sets value of two global vars, the value is then set to false in CStreaming::RequestModelStream
    // It has no affect on the game, so let's leave it
    static void ForceLayerToRead(int32 arg1);
    static int32 GetDefaultCabDriverModel();
    static int32 GetDefaultCopCarModel(int32 ignoreLvpd1Model);
    static int32 GetDefaultCopModel();
    static int32 GetDefaultFiremanModel();
    static int32 GetDefaultMedicModel();
    //! unused
    static signed int GetDiscInDrive();
    static int32 GetNextFileOnCd(uint32 streamLastPosn, bool bNotPriority);
    static bool HasSpecialCharLoaded(int32 slot);
    static bool HasVehicleUpgradeLoaded(int32 modelId);
    //! does nothing (NOP)
    static void IHaveUsedStreamingMemory();
    //! does nothing (NOP)
    static void ImGonnaUseStreamingMemory();
    static void Init();
    static void Init2();
    static void InitImageList();
    static void InstanceLoadedModels(CVector const& point);
    static void InstanceLoadedModelsInSectorList(CPtrList& list);
    static bool IsCarModelNeededInCurrentZone(int32 modelId);
    //! unused
    static bool IsInitialised();
    static bool IsObjectInCdImage(int32 modelId);
    static bool IsVeryBusy();
    static void Load();
    static void LoadAllRequestedModels(bool bOnlyPriorityRequests);
    static void LoadCdDirectory(const char* filename, int32 archiveId);
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
    static void MakeSpaceFor(int32 memoryToCleanInBytes);
    static void PossiblyStreamCarOutAfterCreation(int32 modelId);
    static void ProcessEntitiesInSectorList(CPtrList& list, float posX, float posY, float minX, float minY, float maxX, float maxY, float radius, int32 streamingflags);
    static void ProcessEntitiesInSectorList(CPtrList& list, int32 streamingFlags);
    static bool ProcessLoadingChannel(int32 channelIndex);
    static void PurgeRequestList();
    static void ReInit();
    static void ReadIniFile();
    static void ReclassifyLoadedCars();
    static void RemoveAllUnusedModels();
    static void RemoveBigBuildings();
    static void RemoveBuildingsNotInArea(eAreaCodes areaCode);
    static void RemoveCarModel(int32 modelId);
    static void RemoveCurrentZonesModels();
    static void RemoveDodgyPedsFromRandomSlots();
    static void RemoveEntity(CLink<CEntity*>* streamingLink);
    static void RemoveInappropriatePedModels();
    static bool RemoveLeastUsedModel(uint32 streamingFlags);
    static bool CarIsCandidateForRemoval(int32 modelId);
    static bool RemoveLoadedVehicle();
    static bool ZoneModelIsCandidateForRemoval(int32 modelId);
    static bool RemoveLoadedZoneModel();
    static void RemoveModel(int32 modelId);
    static void RemoveTxdModel(int32 modelId);
    //! does nothing (NOP)
    static void RemoveUnusedModelsInLoadedList();
    static void RenderEntity(CLink<CEntity*>* streamingLink);
    static void RequestBigBuildings(CVector const& point);
    static void RequestFile(int32 modelId, int32 posn, int32 size, int32 imgId, int32 streamingFlags);
    //! unused
    static void RequestFilesInChannel(int32 channelId);
    static void RequestModel(int32 dwModelId, uint32 streamingFlags); // see eStreamingFlags
    static void RequestModelStream(int32 channelId);
    //! unused
    static void RequestPlayerSection(int32 modelId, char const* string, int32 streamingFlags);
    static void RequestSpecialChar(int32 modelId, char const* name, int32 flags);
    static void RequestSpecialModel(int32 modelId, char const* name, int32 flags);
    static void RequestTxdModel(int32 slot, int32 streamingFlags);
    static void RequestVehicleUpgrade(int32 modelId, uint32 streamingFlags);
    static void RetryLoadFile(int32 channelId);
    static void Save();
    static void SetLoadVehiclesInLoadScene(bool bEnable);
    static void SetMissionDoesntRequireAnim(int32 slot);
    static void SetMissionDoesntRequireModel(int32 modelId);
    static void SetMissionDoesntRequireSpecialChar(int32 slot);
    static void SetModelIsDeletable(int32 modelId);
    static void SetModelTxdIsDeletable(int32 modelId);
    static void SetModelAndItsTxdDeletable(int32 modelId);
    //! unused
    static void SetSpecialCharIsDeletable(int32 slot);
    static void Shutdown();
    static void StartRenderEntities();
    static bool StreamAmbulanceAndMedic(bool bStreamForAccident);
    static void StreamCopModels(eLevelName level);
    static bool StreamFireEngineAndFireman(bool bStreamForFire);
    static void StreamOneNewCar();
    //! interiorType : 0 - house , 1 - shop , 2 - office
    static void StreamPedsForInterior(int32 interiorType);
    static void StreamPedsIntoRandomSlots(int32 modelArray[TOTAL_LOADED_PEDS]);
    static void StreamVehiclesAndPeds();
    static void StreamVehiclesAndPeds_Always(CVector const& unused);
    static void StreamZoneModels(CVector const& unused);
    static void StreamZoneModels_Gangs(CVector const& unused);
    static void Update();
    //! unused
    static void UpdateForAnimViewer();
    static bool WeAreTryingToPhaseVehicleOut(int32 modelId);
};

extern RwStream& gRwStream;
