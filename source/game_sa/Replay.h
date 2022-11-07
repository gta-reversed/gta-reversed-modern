#pragma once

#include "eReplay.h"
#include "Vector.h"
#include "PlayerInfo.h"

enum eReplayBufferStatus : uint8 {
    REPLAYBUFFER_STATUS_0 = 0,
    REPLAYBUFFER_STATUS_1 = 1, // full?
    REPLAYBUFFER_STATUS_2 = 2  // in use?
};

// NOTSA
// TODO: maybe spread all struct inside union and use std::variant?
#pragma pack(push, 1)
struct tReplayBlockData {
    eReplayPacket type;
#pragma pack(push, 1)
    union {
        // unk sizes are -1 because we don't include the `type` value in the beginning.
        struct ENDBlock { /* nil */ } end;
        struct VehicleBlock {
            uint8 unk[25];
            uint16 modelId;
            uint8 unk2[24];
        } vehicle;
        struct BikeBlock {
            uint8 unk[25];
            uint16 modelId;
            uint8 unk2[28];
        } bike;
        struct PlayerDataBlock {
            uint8 index; // handle?
            uint16 modelId;
            uint8 pedType;
            uint8 align[3];
        } playerData;
        struct PedBlock { uint8 unk[51]; } ped;
        struct CameraBlock {
            uint8 unk[75];
            CVector firstFocusPosn;
        } camera;
        struct DayTimeBlock {
            uint8 currentHour;
            uint8 currentMinute;
            uint8 align;
        } dayTime;
        struct WeatherBlock { uint8 unk[7]; } weather;
        struct EOFBlock { /* nil */ } eof; // end of frame
        struct TimerBlock {
            uint8 align[3];
            uint32 timer;
        } timer;
        struct BulletTraceBlock { uint8 unk[27]; } bulletTraces;
        struct ParticleBlock { uint8 unk[19]; } particle;
        struct MiscBlock { uint8 unk[15]; } misc;
        struct UnkBlock13 {
            uint8 unk;
            uint16 unk1;
        } deletedVehicle;
        struct UnkBlock14 {
            uint8 unk;
            uint16 unk1;
        } deletedPed;
        struct BmxBlock { uint8 unk[55]; } bmx;
        struct HeliBlock { uint8 unk[55]; } heli;
        struct PlaneBlock { uint8 unk[59]; } plane;
        struct TrainBlock { uint8 unk[75]; } train;
        struct ClothesBlock {
            std::array<uint32, 10> m_anModelKeys;
            std::array<uint32, 18> m_anTextureKeys;
            uint16 m_fFatStat;    // compressed float
            uint16 m_fMuscleStat; // compressed float
            uint8 align[3];
        } clothes;
    };
#pragma pack(pop)
};
#pragma pack(pop)

constexpr auto REPLAY_BUFFER_SIZE = 100'000u;

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
    struct tReplayBuffer {
        std::array<uint8, REPLAY_BUFFER_SIZE> buffer;

        template <typename T>
        T Read(uint32 offset) const {
            return *(T*)(buffer.data() + offset);
        }

        // Returns total bytes written
        uint32 Write(uint32 offset, const tReplayBlockData& data) {
            if (data.type == REPLAY_PACKET_END || data.type == REPLAY_PACKET_END_OF_FRAME) {
                *(eReplayPacket*)(buffer.data() + offset) = data.type;
                return 1;
            }
            std::memcpy(buffer.data() + offset, &data, FindSizeOfPacket(data.type));

            return FindSizeOfPacket(data.type);
        }

        uint8& at(size_t index)             { return buffer.at(index); }
        const uint8& at(size_t index) const { return buffer.at(index); }

        // Returns its index from CReplay::Buffers array.
        size_t GetIndex() const  { return (this - Buffers.data()) / sizeof(tReplayBuffer); }
        bool IsAvailable() const { return BufferStatus[GetIndex()] != REPLAYBUFFER_STATUS_0; }

        struct Iterator {
            using value_type = tReplayBlockData;
            using reference = value_type&;
            using pointer = value_type*;
            using iter_difference = ptrdiff_t;
            using iterator_category = std::forward_iterator_tag;

            const tReplayBuffer* m_buffer{nullptr};
            uint32 m_offset{REPLAY_BUFFER_SIZE};

            Iterator() = default;
            Iterator(const tReplayBuffer* buffer, uint32 offset) : m_buffer(buffer), m_offset(offset) {}

            Iterator& operator++() {
                if (m_offset >= REPLAY_BUFFER_SIZE || !m_buffer) {
                    NOTSA_UNREACHABLE("Increment after end()!");
                }

                const auto type = m_buffer->Read<eReplayPacket>(m_offset);
                m_offset = (type != REPLAY_PACKET_END) ? m_offset + CReplay::FindSizeOfPacket(type) : REPLAY_BUFFER_SIZE;
                return *this;
            }

            Iterator operator++(int) {
                auto a = *this;
                ++*this;
                return a;
            }

            tReplayBlockData& operator*() const {
                if (m_offset >= REPLAY_BUFFER_SIZE || !m_buffer) {
                    NOTSA_UNREACHABLE("Dereferencing of end()!");
                }

                return *(tReplayBlockData*)&m_buffer->at(m_offset);
            }

            tReplayBlockData* operator->() const {
                if (m_offset >= REPLAY_BUFFER_SIZE || !m_buffer) {
                    NOTSA_UNREACHABLE("Dereferencing of end()!");
                }

                return (tReplayBlockData*)&m_buffer->at(m_offset);
            }

            bool operator==(const Iterator& rhs) const = default;
            bool operator!=(const Iterator& rhs) const = default;

            ptrdiff_t operator-(const Iterator& rhs) const {
                assert(m_buffer == rhs.m_buffer);
                return m_offset - rhs.m_offset;
            }
        };

        auto begin() const { return Iterator{this, 0}; }
        auto end() const   { return Iterator{this, REPLAY_BUFFER_SIZE}; }

    };

    class CAddressInReplayBuffer {
    public:
        uint32 m_nOffset;
        tReplayBuffer* m_pBase;
        uint8 m_bSlot;

        // Read helper
        template <typename T>
        T Read() const {
            return m_pBase->Read<T>(m_nOffset);
        }

        // Write helper
        void Write(const tReplayBlockData& data) {
            m_nOffset += m_pBase->Write(m_nOffset, data);
        }
    };
    VALIDATE_SIZE(CAddressInReplayBuffer, 0xC);

    inline static eReplayMode& Mode = *reinterpret_cast<eReplayMode*>(0xA43088);
    inline static bool& bReplayEnabled = *reinterpret_cast<bool*>(0x8A6160);
    inline static bool& bPlayingBackFromFile = *reinterpret_cast<bool*>(0x97FAE1);
    inline static bool& bAllowLookAroundCam = *reinterpret_cast<bool*>(0x97FAE0);
    inline static bool& bDoLoadSceneWhenDone = *reinterpret_cast<bool*>(0x97FACC);

    inline static void*& pReferences = *reinterpret_cast<void**>(0x97FB0C);
    inline static void*& pPickups = *reinterpret_cast<void**>(0x97FB08);
    inline static void*& pEmptyReferences = *reinterpret_cast<void**>(0x97FB04);
    inline static void*& pWorld1 = *reinterpret_cast<void**>(0x97FB00);
    inline static void*& pStoredCam = *reinterpret_cast<void**>(0x97FAF8);
    inline static void*& pRadarBlips = *reinterpret_cast<void**>(0x97FAF4);

    inline static CPlayerInfo& PlayerInfo = *reinterpret_cast<CPlayerInfo*>(0xA430B0);

    inline static std::array<int32, 140>& m_PedPoolConversion = *reinterpret_cast<std::array<int32, 140>*>(0x97F838);
    inline static std::array<int32, 110>& m_VehiclePoolConversion = *reinterpret_cast<std::array<int32, 110>*>(0x97F680);

    inline static CVector_Reversed& CameraFocus = *reinterpret_cast<CVector_Reversed*>(0x97F670);
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
    static int32 FindPoolIndexForPed(int32 index);
    static int32 FindPoolIndexForVehicle(int32 index);
    static bool CanWeFindPoolIndexForPed(int32 index);
    static bool CanWeFindPoolIndexForVehicle(int32 index);
    static void StorePlayerInfoVariables();
    static void StoreStuffInMem();
    static void RestorePlayerInfoVariables();
    static void RestoreStuffFromMem();
    static void FinishPlayback();
    static void StoreClothesDesc(CPedClothesDesc& desc, tReplayBlockData& packet);
    static void RecordThisFrame();
    static void RestoreClothesDesc(CPedClothesDesc& desc, tReplayBlockData& packet);
    static void DealWithNewPedPacket();
    static bool PlayBackThisFrameInterpolation(CAddressInReplayBuffer& buffer, float interpolation, uint32& outTimer);
    static bool FastForwardToTime(uint32 start);
    static void PlayBackThisFrame();

    // Returns size of the specified packed id
    static constexpr uint32 FindSizeOfPacket(eReplayPacket type); // constexpr cuz look tReplayBlockData
    static bool IsThisVehicleUsedInRecording(int32 a1);
    static bool IsThisPedUsedInRecording(int32 a1);
    static void FindFirstFocusCoordinate(CVector& outPos);
    static void NumberFramesAvailableToPlay();
    static void StreamAllNecessaryCarsAndPeds();
    static CPlayerPed* CreatePlayerPed();
    static void TriggerPlayback(eReplayCamMode mode, CVector fixedCamPos, bool loadScene);

    // @notsa
    // @brief Returns all non-empty and non-EOF buffers
    static auto GetAllActiveBuffers() { return Buffers | std::views::filter([](auto&& buffer) { return buffer.IsAvailable(); }); }
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
