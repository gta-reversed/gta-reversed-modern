#pragma once

#include "Vector.h"
#include "PathFind.h"

class CVehicleStateEachFrame {
public:
    float   m_fTime;
    int16   m_sVelocityX;
    int16   m_sVelocityY;
    int16   m_sVelocityZ;
    uint8   m_bRightX;
    uint8   m_bRightY;
    uint8   m_bRightZ;
    uint8   m_bTopX;
    uint8   m_bTopY;
    uint8   m_bTopZ;
    uint8   m_bSteeringAngle;
    uint8   m_bGasPedalPower;
    uint8   m_bBreakPedalPower;
    uint8   m_bHandbrakeUsed;
    CVector m_vecPosn;
};

class CPath {
public:
    int32                   m_nNumber;
    CVehicleStateEachFrame* m_pData;
    int32                   m_nSize;
    int8                    m_nRefCount;
};

VALIDATE_SIZE(CVehicleStateEachFrame, 0x20);
VALIDATE_SIZE(CPath, 0x10);

struct RwStream;

constexpr auto TOTAL_VEHICLE_RECORDS = 16;

class CVehicleRecording {
public:
    static inline int32& NumPlayBackFiles = *(int32*)0x97F630;
    static inline std::array<CPath, TOTAL_RRR_MODEL_IDS>& StreamingArray = *(std::array<CPath, TOTAL_RRR_MODEL_IDS>*)0x97D880;
    static inline std::array<CVehicle*, TOTAL_VEHICLE_RECORDS> pVehicleForPlayback = *(std::array<CVehicle*, TOTAL_VEHICLE_RECORDS>*)0x97D840;
    static inline std::array<CVehicleStateEachFrame*, TOTAL_VEHICLE_RECORDS> pPlaybackBuffer = *(std::array<CVehicleStateEachFrame*, TOTAL_VEHICLE_RECORDS>*)0x97D800;
    static inline std::array<int32, TOTAL_VEHICLE_RECORDS> PlaybackIndex = *(std::array<int32, TOTAL_VEHICLE_RECORDS>*)0x97D7C0;
    static inline std::array<int32, TOTAL_VEHICLE_RECORDS> PlaybackBufferSize = *(std::array<int32, TOTAL_VEHICLE_RECORDS>*)0x97D780;
    static inline std::array<float, TOTAL_VEHICLE_RECORDS> PlaybackRunningTime = *(std::array<float, TOTAL_VEHICLE_RECORDS>*)0x97D740;
    static inline std::array<float, TOTAL_VEHICLE_RECORDS> PlaybackSpeed = *(std::array<float, TOTAL_VEHICLE_RECORDS>*)0x97D700;
    static inline std::array<bool, TOTAL_VEHICLE_RECORDS> bPlaybackGoingOn = *(std::array<bool, TOTAL_VEHICLE_RECORDS>*)0x97D6F0;
    static inline std::array<bool, TOTAL_VEHICLE_RECORDS> bPlaybackLooped = *(std::array<bool, TOTAL_VEHICLE_RECORDS>*)0x97D6E0;
    static inline std::array<bool, TOTAL_VEHICLE_RECORDS> bPlaybackPaused = *(std::array<bool, TOTAL_VEHICLE_RECORDS>*)0x97D6D0;
    static inline std::array<bool, TOTAL_VEHICLE_RECORDS> bUseCarAI = *(std::array<bool, TOTAL_VEHICLE_RECORDS>*)0x97D6C0;
    // static inline int32 PlayBackStreamingIndex = 0x97D670;
    // DisplayMode

public:
    static void InjectHooks();

    static void Init();
    static void InitAtStartOfGame();
    static void ShutDown();
    static void Render();

    /*
     * ChangeCarPlaybackToUseAI(CVehicle*)
     * FindIndexWithFileNameNumber(int32)
     * InterpolateInfoForCar(CVehicle*, CVehicleStateEachFrame*, float)
     */

    static bool HasRecordingFileBeenLoaded(int32 rrrNumber);
    static void Load(RwStream* stream, int32 resourceId, int32 totalSize);
    static void SmoothRecording(int32 resourceId);

    static int32 RegisterRecordingFile(const char* name);
    static void RemoveRecordingFile(int32);
    static void RequestRecordingFile(int32);

    static void SetPlaybackSpeed(CVehicle* vehicle, float speed);
    static void RenderLineSegment(int32& numVertices);

    /*
     * RemoveAllRecordingsThatArentUsed()
     * RestoreInfoForCar(CVehicle*, CVehicleStateEachFrame*, bool)
     * RestoreInfoForMatrix(CMatrix&, CVehicleStateEachFrame*)
     */
    static void SaveOrRetrieveDataForThisFrame();
    /*
     * SetRecordingToPointClosestToCoors(int32, CVector)
     * SkipForwardInRecording(CVehicle*, float)
     * SkipToEndAndStopPlaybackRecordedCar(CVehicle*)
     * StopPlaybackWithIndex(int32)
     */
    static void StartPlaybackRecordedCar(CVehicle* vehicle, int32 pathNumber, bool useCarAI, bool bLooped);
    static void StopPlaybackRecordedCar(CVehicle* vehicle);
    static void PausePlaybackRecordedCar(CVehicle* vehicle);
    static void UnpausePlaybackRecordedCar(CVehicle* vehicle);

    static bool IsPlaybackGoingOnForCar(CVehicle* vehicle);
    static bool IsPlaybackPausedForCar(CVehicle* vehicle);
};
