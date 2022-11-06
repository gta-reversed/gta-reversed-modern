#pragma once

#include "eReplay.h"
#include "Vector.h"

class CAddressInReplayBuffer {
public:
    uint32 m_nOffset;
    uint8* m_pBase;
    uint8 m_bSlot;
};
VALIDATE_SIZE(CAddressInReplayBuffer, 0xC);

class CPacketPlayerClothes {
public:
    uint8 m_nType;
    std::array<uint32, 10> m_anModelKeys;
    std::array<uint32, 18> m_anTextureKeys;
    uint16 m_fFatStat;    // compressed float
    uint16 m_fMuscleStat; // compressed float
};

enum eReplayBufferStatus : uint8 {
    REPLAYBUFFER_STATUS_0 = 0
};

struct tReplayBlockData {
    eReplayPacket packetType;
    union {
        struct { /* nil */ } end;
        struct VehicleBlock { uint8 unk[51]; } vehicle;
        struct BikeBlock { uint8 unk[55]; } bike;
        struct PlayerDataBlock {
            uint8 index; // handle?
            uint16 modelId;
            uint8 pedType;
        } playerData;
        struct PedBlock { uint8 unk[51]; } ped;
        struct CameraBlock {
            uint8 unk[75];
            CVector firstFocusPosn;
        } camera;
        struct DayTimeBlock {
            uint8 currentHour;
            uint8 currentMinute;
        } dayTime;
        struct WeatherBlock { uint8 unk[7]; } weather;
        struct { /* nil */ } eof; // end of frame
        struct TimerBlock {
            uint8 align[2];
            uint32 timer;
        } timer;
        struct UnkBlock10 { uint8 unk[27]; } unkBlock10;
        struct UnkBlock11 { uint8 unk[19]; } unkBlock11;
        struct UnkBlock12 { uint8 unk[15]; } unkBlock12;
        struct UnkBlock13 { uint8 unk[3];  } unkBlock13;
        struct UnkBlock14 { uint8 unk[3];  } unkBlock14;
        struct BmxBlock { uint8 unk[55]; } bmx;
        struct HeliBlock { uint8 unk[55]; } heli;
        struct PlaneBlock { uint8 unk[59]; } plane;
        struct TrainBlock { uint8 unk[75]; } train;
        struct ClothesBlock {
            std::array<uint32, 10> m_anModelKeys;
            std::array<uint32, 18> m_anTextureKeys;
            uint16 m_fFatStat;    // compressed float
            uint16 m_fMuscleStat; // compressed float
        } clothes;

        // unk sizes are -1 because we don't include the `type` value in the beginning.
    };
};

class CReplay {
public:
    // @notsa
    struct CVector_Reversed {
        float z, y, x;

        CVector_Reversed(const CVector& vec) {
            z = vec.z;
            y = vec.y;
            x = vec.x;
        }

        operator CVector() {
            return {x, y, z};
        }
    };
    VALIDATE_SIZE(CVector_Reversed, sizeof(CVector));

    // @notsa
    class tReplayBuffer {
        std::array<uint8, 100'000> buffer;

    public:
        template <typename T>
        T Read(uint32 offset) const {
            return *(T*)(buffer.data() + offset);
        }

        uint8& at(size_t index)             { return buffer.at(index); }
        const uint8& at(size_t index) const { return buffer.at(index); }

        // Returns its index from CReplay::Buffers array.
        size_t GetIndex() const  { return (this - Buffers.data()) / sizeof(tReplayBuffer); }
        bool IsAvailable() const { return BufferStatus[GetIndex()] != REPLAYBUFFER_STATUS_0; }

        struct Iterator {
            const tReplayBuffer& m_buffer;
            uint32 m_offset{0};
            bool m_end{false};

            Iterator(const tReplayBuffer& buffer, bool end) : m_buffer(buffer), m_end(end) {}

            auto operator++() { // pre-increment
                const auto type = m_buffer.Read<eReplayPacket>(m_offset);
                m_end = type == REPLAY_PACKET_END;
                m_offset += CReplay::FindSizeOfPacket(type);
                return *this;
            }

            auto operator++(int) { // post-increment
                auto ret = *this;
                ++*this;
                return ret;
            }

            auto operator*() const {
                const auto type = m_buffer.Read<eReplayPacket>(m_offset);

                if (m_end || type == REPLAY_PACKET_END) {
                    NOTSA_UNREACHABLE("EOF packet can not be read!");
                }
                if (type >= NUM_REPLAY_PACKETS) {
                    NOTSA_UNREACHABLE("Invalid replay packet type! ID={}", (uint8)type);
                }

                // it won't be funny if user reads the union incorrectly but hey.
                return *(tReplayBlockData*)&m_buffer.at(m_offset);
            }

            bool operator==(const Iterator& rhs) {
                if (&m_buffer != &rhs.m_buffer)
                    return false;

                // we don't care about their offsets if they both ended anyways.
                if (m_end == rhs.m_end == true) {
                    return true;
                }

                return m_offset == rhs.m_offset;
            }

            bool operator!=(const Iterator& rhs) { return !(*this == rhs); }
        };

        auto begin() const { return Iterator{*this, false}; }
        auto end() const   { return Iterator{*this, true}; }
    };

    inline static eReplayMode& Mode = *reinterpret_cast<eReplayMode*>(0xA43088);
    inline static bool& bReplayEnabled = *reinterpret_cast<bool*>(0x8A6160);
    inline static bool& bPlayingBackFromFile = *reinterpret_cast<bool*>(0x97FAE1);
    inline static bool& bAllowLookAroundCam = *reinterpret_cast<bool*>(0x97FAE0);
    inline static bool& bDoLoadSceneWhenDone = *reinterpret_cast<bool*>(0x97FACC);

    inline static CVector_Reversed& CameraFixed = *reinterpret_cast<CVector_Reversed*>(0x97FB24);
    inline static CVector_Reversed& LoadScene = *reinterpret_cast<CVector_Reversed*>(0x97FAC0);
    inline static eReplayCamMode& CameraMode = *reinterpret_cast<eReplayCamMode*>(0x97FB30);
    inline static int32& FramesActiveLookAroundCam = *reinterpret_cast<int32*>(0x97FAD0);
    inline static int8& OldRadioStation = *reinterpret_cast<int8*>(0x97FABC);
    inline static int8& CurrArea = *reinterpret_cast<int8*>(0x97FAB8);
    inline static std::array<eReplayBufferStatus, 8u>& BufferStatus = *reinterpret_cast<std::array<eReplayBufferStatus, 8u>*>(0x97FB7C);

    inline static std::array<tReplayBuffer, 8>& Buffers = *reinterpret_cast<std::array<tReplayBuffer, 8>*>(0x97FB88);

    inline static CAddressInReplayBuffer& Playback = *reinterpret_cast<CAddressInReplayBuffer*>(0x97FB64);
    inline static CAddressInReplayBuffer& Record = *reinterpret_cast<CAddressInReplayBuffer*>(0x97FB70);

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void DisableReplays();
    static void EnableReplays();
    static void StorePedAnimation();
    static void StorePedUpdate(CPed* ped, int32 a2);
    static void RetrievePedAnimation();
    static void Display();
    static void MarkEverythingAsNew();
    static void EmptyReplayBuffer();
    static void EmptyPedsAndVehiclePools_NoDestructors();
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
    static void FindPoolIndexForPed(int32 a1);
    static void FindPoolIndexForVehicle(int32 a1);
    static void CanWeFindPoolIndexForPed(int32 a1);
    static void CanWeFindPoolIndexForVehicle(int32 a1);
    static void StorePlayerInfoVariables();
    static void StoreStuffInMem();
    static void RestorePlayerInfoVariables();
    static void RestoreStuffFromMem();
    static void FinishPlayback();
    static void StoreClothesDesc();
    static void RecordThisFrame();
    static void RestoreClothesDesc(CPedClothesDesc& desc, CPacketPlayerClothes& packet);
    static void DealWithNewPedPacket();
    static bool PlayBackThisFrameInterpolation(CAddressInReplayBuffer& buffer, float interpolation, uint32& outTimer);
    static bool FastForwardToTime(uint32 start);
    static void PlayBackThisFrame();

    // Returns size of the specified packed id
    static uint32 FindSizeOfPacket(uint16 id);
    static bool IsThisVehicleUsedInRecording(int32 a1);
    static bool IsThisPedUsedInRecording(int32 a1);
    static void FindFirstFocusCoordinate(CVector& outPos);
    static void NumberFramesAvailableToPlay();
    static void StreamAllNecessaryCarsAndPeds();
    static CPlayerPed* CreatePlayerPed();
    static void TriggerPlayback(eReplayCamMode mode, CVector fixedCamPos, bool loadScene);

    // @notsa
    // @brief Returns all non-empty and non-EOF buffers
    static auto GetAllActiveBuffers() { return Buffers | std::views::filter([](auto&& buffer) { return !buffer.IsAvailable(); }); }
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
*CanWeFindPoolIndexForPed(int32)
* CanWeFindPoolIndexForVehicle(int32)
* CreatePlayerPed()
* DealWithNewPedPacket(CPacketNewPed*, bool, CPacketPlayerClothes*)
* DisableReplays()
* EmptyPedsAndVehiclePools_NoDestructors()
* EmptyReplayBuffer()
* EnableReplays()
* FastForwardToTime(uint32)
* FindFirstFocusCoordinate(CVector*)
* FindPoolIndexForPed(int32)
* FindPoolIndexForVehicle(int32)
* FindSizeOfPacket(uint8)
* FinishPlayback()
* GoToNextBlock()
* Init()
* InitialisePedPoolConversionTable()
* InitialisePoolConversionTables()
* InitialiseVehiclePoolConversionTable()
* IsThisPedUsedInRecording(int32)
* IsThisVehicleUsedInRecording(int32)
* MarkEverythingAsNew()
* NumberFramesAvailableToPlay()
* PlayBackThisFrame()
* PlayBackThisFrameInterpolation(CAddressInReplayBuffer*, float, uint32*)
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
* StorePedUpdate(CPed*, int32)
* StorePlayerInfoVariables()
* StoreStuffInMem()
* StreamAllNecessaryCarsAndPeds()
* TriggerPlayback(uint8, float, float, float, bool)
* Update()*/
