#pragma once

enum eReplayMode : std::int32_t {
    REPLAY_MODE_0,
    REPLAY_MODE_1
};

class CReplay {
public:
    static eReplayMode& Mode;
    static bool& bReplayEnabled;

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void DisableReplays();
    static void EnableReplays();
    static void StorePedAnimation();
    static void StorePedUpdate(CPed* ped, int a2);
    static void RetrievePedAnimation();
    static void Display();
    static void MarkEverythingAsNew();
    static void EmptyReplayBuffer();
    static void GoToNextBlock();
    static void RecordVehicleDeleted(CVehicle* vehicle);
    static void RecordPedDeleted(CPed* ped);
    static void InitialiseVehiclePoolConversionTable();
    static void InitialisePedPoolConversionTable();
    static void InitialisePoolConversionTables();
    static void SaveReplayToHD();
    static bool ShouldStandardCameraBeProcessed();
    static void ProcessPedUpdate();
    static void ProcessReplayCamera();
    static void ProcessLookAroundCam();
    static void FindPoolIndexForPed(int a1);
    static void FindPoolIndexForVehicle(int a1);
    static void CanWeFindPoolIndexForPed(int a1);
    static void CanWeFindPoolIndexForVehicle(int a1);
    static void StorePlayerInfoVariables();
    static void StoreStuffInMem();
    static void RestorePlayerInfoVariables();
    static void RestoreStuffFromMem();
    static void FinishPlayback();
    static void StoreClothesDesc();
    static void RecordThisFrame();
    static void RestoreClothesDesc();
    static void DealWithNewPedPacket();
    static void PlayBackThisFrameInterpolation();
    static void FastForwardToTime(unsigned int a1);
    static void PlayBackThisFrame();
    static void FindSizeOfPacket(unsigned short id);
    static bool IsThisVehicleUsedInRecording(int a1);
    static bool IsThisPedUsedInRecording(int a1);
    static void FindFirstFocusCoordinate(CVector* a1);
    static void NumberFramesAvailableToPlay();
    static void StreamAllNecessaryCarsAndPeds();
    static CPed* CreatePlayerPed();
    static void TriggerPlayback(bool a1, float a2, float a3, float a4, bool a5);
};

/*
CReplay(69 variables, 46 functions)
Variables list :
*ActiveSequences
* BufferStatus
* Buffers
* CameraFixedX
* CameraFixedY
* CameraFixedZ
* CameraMode
* ClockHours
* ClockMinutes
* CurrArea
* FireArray
* Frame
* FramesActiveLookAroundCam
* LastRecordedFrameTime
* LoadSceneX
* LoadSceneY
* LoadSceneZ
* Mode
* NewWeatherType
* OldRadioStation
* OldWeatherType
* PedGroup_NumKills
* PedGroup_OnMission
* Playback
* PlayerInfo
* Record
* Time1
* Time2
* Time3
* Time4
* Time5
* Time6
* Time7
* TimeScale
* TimeStep
* TimeStepNonClipped
* WeatherInterpolationValue
* WorldPtrList
* bAllowLookAroundCam
* bDoLoadSceneWhenDone
* bPlayingBackFromFile
* bReplayEnabled
* fAlphaAngleLookAroundCam
* fBetaAngleLookAroundCam
* fDistanceLookAroundCam
* m_PedPoolConversion
* m_VehiclePoolConversion
* ms_nNumCivFemale_Stored
* ms_nNumCivMale_Stored
* ms_nNumCop_Stored
* ms_nNumDealers_Stored
* ms_nNumEmergency_Stored
* ms_nNumGang_Stored
* ms_nTotalCarPassengerPeds_Stored
* ms_nTotalCivPeds_Stored
* ms_nTotalGangPeds_Stored
* ms_nTotalMissionPeds_Stored
* ms_nTotalPeds_Stored
* pBufSeq0
* pBufSeq1
* pEmptyReferences
* pGarages
* pPickups
* pRadarBlips
* pReferences
* pStoredCam
* pWorld1
* paProjectileInfo
* paProjectiles

Functions list :
*CanWeFindPoolIndexForPed(int)
* CanWeFindPoolIndexForVehicle(int)
* CreatePlayerPed()
* DealWithNewPedPacket(CPacketNewPed*, bool, CPacketPlayerClothes*)
* DisableReplays()
* EmptyPedsAndVehiclePools_NoDestructors()
* EmptyReplayBuffer()
* EnableReplays()
* FastForwardToTime(unsigned int)
* FindFirstFocusCoordinate(CVector*)
* FindPoolIndexForPed(int)
* FindPoolIndexForVehicle(int)
* FindSizeOfPacket(unsigned char)
* FinishPlayback()
* GoToNextBlock()
* Init()
* InitialisePedPoolConversionTable()
* InitialisePoolConversionTables()
* InitialiseVehiclePoolConversionTable()
* IsThisPedUsedInRecording(int)
* IsThisVehicleUsedInRecording(int)
* MarkEverythingAsNew()
* NumberFramesAvailableToPlay()
* PlayBackThisFrame()
* PlayBackThisFrameInterpolation(CAddressInReplayBuffer*, float, unsigned int*)
* ProcessLookAroundCam()
* ProcessPedUpdate(CPed*, float, CAddressInReplayBuffer*)
* ProcessReplayCamera()
* RecordPedDeleted(CPed*)
* RecordThisFrame()
* RecordVehicleDeleted(CVehicle*)
* RestoreClothesDesc(CPedClothesDesc*, CPacketPlayerClothes*)
* RestorePlayerInfoVariables()
* RestoreStuffFromMem()
* RetrievePedAnimation(CPed*, CStoredAnimationState*)
* SaveReplayToHD()
* ShouldStandardCameraBeProcessed()
* StoreClothesDesc(CPedClothesDesc*, CPacketPlayerClothes*)
* StorePedAnimation(CPed*, CStoredAnimationState*)
* StorePedUpdate(CPed*, int)
* StorePlayerInfoVariables()
* StoreStuffInMem()
* StreamAllNecessaryCarsAndPeds()
* TriggerPlayback(unsigned char, float, float, float, bool)
* Update()*/
