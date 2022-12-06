#pragma once

#include "Bmx.h"
#include "CompressedMatrixNotAligned.h"
#include "PlayerInfo.h"
#include "Vector.h"
#include "Vehicle.h"
#include "eReplay.h"
#include "ePedType.h"
#include "eWeatherType.h"
#include "extensions/enumerate.hpp"

class CCamera;

enum eReplayBufferStatus : uint8 {
    REPLAYBUFFER_NOT_AVAILABLE = 0,
    REPLAYBUFFER_FULL = 1,
    REPLAYBUFFER_IN_USE = 2
};

#pragma pack(push, 1)
struct AnimationState {
    int16 m_nAnimId;
    uint8 m_nTime;
    uint8 m_nSpeed;
    uint8 m_nGroupId1;
    uint8 m_nGroupId2;
};
#pragma pack(pop)
VALIDATE_SIZE(AnimationState, 6);

struct CStoredAnimationState {
    AnimationState first;
    AnimationState second;
    AnimationState third;
};
VALIDATE_SIZE(CStoredAnimationState, 18);

// Used for compressing angle values while recording replays.
constexpr float HEADING_COMPRESS_VALUE = 40.764328f;

// NOTSA
#pragma pack(push, 1)
struct tReplayBlockData {
    eReplayPacket type;
#pragma pack(push, 1)
    union {
        // unk sizes are -1 because we don't include the `type` value in the beginning.
        struct ENDBlock { /* nil */ } end;
        struct VehicleBlock {
            uint8 poolRef;
            uint8 health;
            uint8 gasPedal;
            CCompressedMatrixNotAligned matrix;
            uint8 angleDoorLF;
            uint8 angleDoorRF;
            uint16 modelId;
            uint32 panels;
            struct {
                int8 x, y, z;
            } vecMoveSpeed;
            uint8 steerAngle_or_doomVerticalRot; // m_fDoomVerticalRotation if modelId == RHINO, steerAngle if not.
            uint8 wheelsSuspensionCompression[4];
            uint8 wheelRotation[4];
            uint8 doorStatus;
            uint8 primaryColor;
            uint8 secondaryColor;
            uint8 physicalFlags;
            uint8 vehicleSubType;
            uint8 vehicleType;
            uint8 __pad[2];
        } vehicle;
        struct BikeBlock {
            VehicleBlock vehicle;
            uint8 animLean;
            uint8 steerAngle;
            uint8 __pad[2];
        } bike;
        struct PedHeaderBlock {
            uint8 poolRef;
            int16 modelId;
            uint8 pedType;
            uint8 __pad[3];
        } pedHeader;
        struct PedBlock {
            uint8 poolRef;
            int8 heading;
            uint8 vehicleIndex; // 0: not in a vehicle
            CStoredAnimationState animState;
            uint8 __pad1[2];
            CCompressedMatrixNotAligned matrix;
            int16 weaponModel;
            uint16 animGroup;
            uint8 contactSurfaceBrightness;
            uint8 flags;
            uint8 __pad2[2];
        } ped; // also called `ped update`
        struct CameraBlock {
            bool isUsingRemoteVehicle;
            uint8 __pad[2];
            uint8 matrix[sizeof(CMatrix)]; // cast to CMatrix until i found a solution to make it CMatrix cleanly.
            CVector firstFocusPosn;
        } camera;
        struct ClockBlock {
            uint8 currentHour;
            uint8 currentMinute;
            uint8 __pad;
        } clock;
        struct WeatherBlock {
            uint8 oldWeather;
            uint8 newWeather;
            uint8 __pad;
            float interpValue;
        } weather;
        struct EOFBlock { uint8 do_not_access[3]; } eof; // end of frame
        struct TimerBlock {
            uint8 __pad[3];
            uint32 timeInMS;
        } timer;
        struct BulletTraceBlock {
            uint8 __pad[2];
            uint8 index;
            CVector start;
            CVector end;
        } bulletTrace;
        struct ParticleBlock { uint8 unk[19]; } particle; // Unused
        struct MiscBlock {
            uint8 __pad1[3];
            uint32 camShakeStart;
            float camShakeForce;
            uint8 currArea;
            struct {
                bool videoCam : 1;
                bool liftCam : 1;
            } camConfig;
            uint8 __pad2[2];
        } misc;
        struct DeletedVehicle {
            uint8 __pad;
            int16 poolRef;
        } deletedVehicle;
        struct DeletedPed {
            uint8 __pad;
            int16 poolRef;
        } deletedPed;
        struct BmxBlock {
            VehicleBlock vehicle;
            uint8 animLean;
            uint8 steerAngle;
            uint8 __pad[2];
        } bmx; // same as BikeBlock
        struct HeliBlock {
            VehicleBlock vehicle;
            float rotorSpeed;
        } heli;
        struct PlaneBlock {
            VehicleBlock vehicle;
            float propSpeed;
            float field_9C8;
        } plane;
        struct TrainBlock {
            VehicleBlock vehicle;
            float trainSpeed;
            float currentRailDistance;
            float length;
            uint32 prevCarriageRef;
            uint32 nextCarriageRef;
            uint8 trackId;
            uint8 __pad[3];
        } train;
        struct ClothesBlock {
            uint8 __pad[3];
            std::array<uint32, 10> m_anModelKeys;
            std::array<uint32, 18> m_anTextureKeys;
            uint16 m_fFatStat;    // compressed float
            uint16 m_fMuscleStat; // compressed float
        } clothes;
    };
#pragma pack(pop)

    static tReplayBlockData MakeVehicleUpdateData(CVehicle* vehicle, int32 poolIdx);
    static tReplayBlockData MakeTrainUpdateData(CTrain* train, int32 poolIdx);
    static tReplayBlockData MakeBikeUpdateData(CBike* bike, int32 poolIdx);
    static tReplayBlockData MakeBmxUpdateData(CBmx* bmx, int32 poolIdx);

    static void ExtractVehicleUpdateData(tReplayBlockData& packet, CVehicle* vehicle, float interpolation);
    static void ExtractBikeUpdateData(tReplayBlockData& packet, CBike* bike, float interpolation);
    static void ExtractTrainUpdateData(tReplayBlockData& packet, CTrain* train, float interpolation);
};
#pragma pack(pop)

constexpr auto NUM_REPLAY_BUFFERS = 8u;
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
            if (data.type == REPLAY_PACKET_END) {
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
        bool IsAvailable() const { return BufferStatus[GetIndex()] != REPLAYBUFFER_NOT_AVAILABLE; }

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
        uint8 m_bSlot; // first slot to contain data

        // Read helper
        template <typename T>
        T Read() const {
            return m_pBase->Read<T>(m_nOffset);
        }

        // Write helper
        void Write(const tReplayBlockData& data, bool seek = false) {
            const auto written = m_pBase->Write(m_nOffset, data);
            if (seek) {
                m_nOffset += written;
            }
        }

        void Next() {
            m_bSlot = GetNextSlot();
            m_pBase = &Buffers[m_bSlot];
            m_nOffset = 0u;
        }

        eReplayBufferStatus GetStatus() {
            return BufferStatus[m_bSlot];
        }

        uint8 GetNextSlot(uint8 stride = 1u) {
            return (stride + m_bSlot) % NUM_REPLAY_BUFFERS;
        }
    };
    VALIDATE_SIZE(CAddressInReplayBuffer, 0xC);

    inline static eReplayMode& Mode = *reinterpret_cast<eReplayMode*>(0xA43088);
    inline static bool& bReplayEnabled = *reinterpret_cast<bool*>(0x8A6160);
    inline static bool& bPlayingBackFromFile = *reinterpret_cast<bool*>(0x97FAE1);
    inline static bool& bAllowLookAroundCam = *reinterpret_cast<bool*>(0x97FAE0);
    inline static bool& bDoLoadSceneWhenDone = *reinterpret_cast<bool*>(0x97FACC);
    inline static bool& bIsUsingRemoteCar = *reinterpret_cast<bool*>(0x97F66D);

    inline static void*& pReferences = *reinterpret_cast<void**>(0x97FB0C);
    inline static void*& pPickups = *reinterpret_cast<void**>(0x97FB08);
    inline static void*& pEmptyReferences = *reinterpret_cast<void**>(0x97FB04);
    inline static void*& pWorld1 = *reinterpret_cast<void**>(0x97FB00);
    inline static CCamera*& pStoredCam = *reinterpret_cast<CCamera**>(0x97FAF8);
    inline static void*& pRadarBlips = *reinterpret_cast<void**>(0x97FAF4);

    inline static uint32& Time1 = *reinterpret_cast<uint32*>(0x97FB60);
    inline static uint32& Time2 = *reinterpret_cast<uint32*>(0x97FB5C);
    inline static uint32& Time3 = *reinterpret_cast<uint32*>(0x97FB58);
    inline static uint32& Time4 = *reinterpret_cast<uint32*>(0x97FB54);
    inline static uint32& Time5 = *reinterpret_cast<uint32*>(0x97FB50);
    inline static uint32& Time6 = *reinterpret_cast<uint32*>(0x97FB4C);
    inline static uint32& Time7 = *reinterpret_cast<uint32*>(0x97FB48);
    inline static uint32& Frame = *reinterpret_cast<uint32*>(0x97FB44);
    inline static float& TimeStepNonClipped = *reinterpret_cast<float*>(0x97FB34);
    inline static float& TimeStep = *reinterpret_cast<float*>(0x97FB38);
    inline static float& TimeScale = *reinterpret_cast<float*>(0x97FB3C);

    // these are overwritten when OldWeatherType changes for some reason
    // they have no unreversed xref anyways so it's fine.
    // inline static uint8& ClockHours = *reinterpret_cast<uint8*>(0x97FAEF);
    // inline static uint8& ClockMinutes = *reinterpret_cast<uint8*>(0x97FAEE);
    inline static uint8 ClockHours{};
    inline static uint8 ClockMinutes{};

    inline static eWeatherType& OldWeatherType = *reinterpret_cast<eWeatherType*>(0x97FAEC);
    inline static eWeatherType& NewWeatherType = *reinterpret_cast<eWeatherType*>(0x97FAE8);
    inline static float& WeatherInterpolationValue = *reinterpret_cast<float*>(0x97FAE4);

    inline static uint32& ms_nNumCivMale_Stored = *reinterpret_cast<uint32*>(0x97FAB4);
    inline static uint32& ms_nNumCivFemale_Stored = *reinterpret_cast<uint32*>(0x97FAB0);
    inline static uint32& ms_nNumCop_Stored = *reinterpret_cast<uint32*>(0x97FAAC);
    inline static uint32& ms_nNumEmergency_Stored = *reinterpret_cast<uint32*>(0x97FAA8);
    inline static uint32& ms_nNumDealers_Stored = *reinterpret_cast<uint32*>(0x97FA7C);
    inline static uint32& ms_nTotalCarPassengerPeds_Stored = *reinterpret_cast<uint32*>(0x97FA78);
    inline static uint32& ms_nTotalCivPeds_Stored = *reinterpret_cast<uint32*>(0x97FA74);
    inline static uint32& ms_nTotalGangPeds_Stored = *reinterpret_cast<uint32*>(0x97FA70);
    inline static uint32& ms_nTotalPeds_Stored = *reinterpret_cast<uint32*>(0x97FA6C);
    inline static uint32& ms_nTotalMissionPeds_Stored = *reinterpret_cast<uint32*>(0x97FA68);
    inline static std::array<uint32, TOTAL_GANGS>& ms_nNumGang_Stored = *reinterpret_cast<std::array<uint32, TOTAL_GANGS>*>(0x97FA80);

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
    inline static std::array<eReplayBufferStatus, NUM_REPLAY_BUFFERS>& BufferStatus = *reinterpret_cast<std::array<eReplayBufferStatus, NUM_REPLAY_BUFFERS>*>(0x97FB7C);

    inline static std::array<tReplayBuffer, NUM_REPLAY_BUFFERS>& Buffers = *reinterpret_cast<std::array<tReplayBuffer, NUM_REPLAY_BUFFERS>*>(0x97FB88);

    inline static CAddressInReplayBuffer& Playback = *reinterpret_cast<CAddressInReplayBuffer*>(0x97FB64);
    inline static CAddressInReplayBuffer& Record = *reinterpret_cast<CAddressInReplayBuffer*>(0x97FB70);

public:
    static void InjectHooks();

    static void Init();
    static void Update();
    static void DisableReplays();
    static void EnableReplays();
    static void StorePedAnimation(CPed* ped, CStoredAnimationState& state);
    static void StorePedUpdate(CPed* ped, uint8 index);
    static void RetrievePedAnimation(CPed* ped, const CStoredAnimationState& state);
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
    static void PlayReplayFromHD();
    static bool ShouldStandardCameraBeProcessed();
    static void ProcessPedUpdate(CPed* ped, float a2, CAddressInReplayBuffer& address);
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
    static void StoreClothesDesc(const CPedClothesDesc& desc, tReplayBlockData& packet);
    static void RecordThisFrame();
    static void RestoreClothesDesc(CPedClothesDesc& desc, tReplayBlockData& packet);
    static CPed* DealWithNewPedPacket(tReplayBlockData& pedPacket, bool loadModel, tReplayBlockData* clothesPacket);
    static bool PlayBackThisFrameInterpolation(CAddressInReplayBuffer& buffer, float interpolation, uint32* outTimer);
    static bool FastForwardToTime(uint32 start);
    static void PlayBackThisFrame();

    // Returns size of the specified packed id
    // NOTSA: Marked as constexpr because we're using this to validate tReplayBlockData block sizes.
    static constexpr uint32 FindSizeOfPacket(eReplayPacket type);
    static bool IsThisVehicleUsedInRecording(int32 a1);
    static bool IsThisPedUsedInRecording(int32 a1);
    static void FindFirstFocusCoordinate(CVector& outPos);
    static uint32 NumberFramesAvailableToPlay();
    static void StreamAllNecessaryCarsAndPeds();
    static CPlayerPed* CreatePlayerPed();
    static void TriggerPlayback(eReplayCamMode mode, CVector fixedCamPos, bool loadScene);

    // @notsa
    // @brief Returns all available buffers
    static auto GetAllActiveBuffers() { return Buffers | std::views::filter([](auto&& buffer) { return buffer.IsAvailable(); }); }
};
