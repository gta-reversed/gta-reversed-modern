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

const uint32 TOTAL_VEHICLE_RECORDS = 16;

class CVehicleRecording {
public:
    static int32& NumPlayBackFiles;
    static CPath (&StreamingArray)[TOTAL_RRR_MODEL_IDS];
    static bool (&bUseCarAI)[TOTAL_VEHICLE_RECORDS];
    /*
     * DisplayMode
     * PlayBackStreamingIndex
     * PlaybackBufferSize
     * PlaybackIndex
     * PlaybackRunningTime
     * PlaybackSpeed
     * StreamingArray
     * bPlaybackGoingOn
     * bPlaybackLooped
     * bPlaybackPaused
     * pPlaybackBuffer
     * pVehicleForPlayback*/

public:
    static void InjectHooks();

    static void Init();
    static void Render();
    /*
     * ChangeCarPlaybackToUseAI(CVehicle*)
     * FindIndexWithFileNameNumber(int32)
     * InitAtStartOfGame()
     * InterpolateInfoForCar(CVehicle*, CVehicleStateEachFrame*, float)
     * IsPlaybackGoingOnForCar(CVehicle*)
     * IsPlaybackPausedForCar(CVehicle*)
     */
    static bool  HasRecordingFileBeenLoaded(int32 rrrNumber);
    static void  Load(RwStream* stream, int32 resourceId, int32 totalSize);
    static int32 RegisterRecordingFile(char const* name);
    static void  SetPlaybackSpeed(CVehicle* vehicle, float speed);
    static void  RenderLineSegment(int32& numVertices);
    /*
     * PausePlaybackRecordedCar(CVehicle*)
     * RemoveAllRecordingsThatArentUsed()
     * RemoveRecordingFile(int32)
     * Render()
     * RequestRecordingFile(int32)
     * RestoreInfoForCar(CVehicle*, CVehicleStateEachFrame*, bool)
     * RestoreInfoForMatrix(CMatrix&, CVehicleStateEachFrame*)
     */
    static void SaveOrRetrieveDataForThisFrame();
    /*
     * SetRecordingToPointClosestToCoors(int32, CVector)
     * ShutDown()
     * SkipForwardInRecording(CVehicle*, float)
     * SkipToEndAndStopPlaybackRecordedCar(CVehicle*)
     * SmoothRecording(int32)
     * StopPlaybackWithIndex(int32)
     * UnpausePlaybackRecordedCar(CVehicle*)
     */
    static void StartPlaybackRecordedCar(CVehicle* vehicle, int32 pathNumber, bool bUseCarAI, bool bLooped);
    static void StopPlaybackRecordedCar(CVehicle* vehicle);
};
