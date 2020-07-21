#include "CVector.h"
#include "CPathFind.h"

class CVehicleStateEachFrame
{
public:
    float m_fTime;
    short m_sVelocityX;
    short m_sVelocityY;
    short m_sVelocityZ;
    BYTE m_bRightX;
    BYTE m_bRightY;
    BYTE m_bRightZ;
    BYTE m_bTopX;
    BYTE m_bTopY;
    BYTE m_bTopZ;
    BYTE m_bSteeringAngle;
    BYTE m_bGasPedalPower;
    BYTE m_bBreakPedalPower;
    BYTE m_bHandbrakeUsed;
    CVector m_vecPosn;
};

class CPath
{
public:
    std::int32_t m_nNumber;
    CVehicleStateEachFrame* m_pData;
    std::int32_t m_nSize;
    std::int8_t m_nRefCount;
};

VALIDATE_SIZE(CVehicleStateEachFrame, 0x20);
VALIDATE_SIZE(CPath, 0x10);

struct RwStream;

class CVehicleRecording
{
public:
    static std::int32_t& NumPlayBackFiles;
    static CPath(&StreamingArray)[TOTAL_RRR_MODEL_IDS];
    // seems like majority of them are static, like functions
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
    * bUseCarAI
    * pPlaybackBuffer
    * pVehicleForPlayback*/

    /*
    * ChangeCarPlaybackToUseAI(CVehicle*)
    * FindIndexWithFileNameNumber(int)
    * Init()
    * InitAtStartOfGame()
    * InterpolateInfoForCar(CVehicle*, CVehicleStateEachFrame*, float)
    * IsPlaybackGoingOnForCar(CVehicle*)
    * IsPlaybackPausedForCar(CVehicle*)
    */
    static bool HasRecordingFileBeenLoaded(std::int32_t rrrNumber);
    static void Load(RwStream *stream, std::int32_t resourceId, std::int32_t totalSize);
    static std::int32_t RegisterRecordingFile(char const* name);
    static void SetPlaybackSpeed(CVehicle* vehicle, float speed);
    /*
    * PausePlaybackRecordedCar(CVehicle*)
    * RemoveAllRecordingsThatArentUsed()
    * RemoveRecordingFile(int)
    * Render()
    * RenderLineSegment(int&)
    * RequestRecordingFile(int)
    * RestoreInfoForCar(CVehicle*, CVehicleStateEachFrame*, bool)
    * RestoreInfoForMatrix(CMatrix&, CVehicleStateEachFrame*)
    * SaveOrRetrieveDataForThisFrame()
    * SetRecordingToPointClosestToCoors(int, CVector)
    * ShutDown()
    * SkipForwardInRecording(CVehicle*, float)
    * SkipToEndAndStopPlaybackRecordedCar(CVehicle*)
    * SmoothRecording(int)
    * StopPlaybackWithIndex(int)
    * UnpausePlaybackRecordedCar(CVehicle*)
    */
    static void StartPlaybackRecordedCar(CVehicle* vehicle, std::int32_t pathNumber, bool bUseCarAI, bool bLooped);
    static void StopPlaybackRecordedCar(CVehicle* vehicle);
};
