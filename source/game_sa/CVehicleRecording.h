#include "CVector.h"

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

VALIDATE_SIZE(CVehicleStateEachFrame, 0x20);

struct RwStream;

class CVehicleRecording
{
public:
    // seems like majority of them are static, like functions
    /*
    * DisplayMode
    * NumPlayBackFiles
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
    * HasRecordingFileBeenLoaded(int)
    * Init()
    * InitAtStartOfGame()
    * InterpolateInfoForCar(CVehicle*, CVehicleStateEachFrame*, float)
    * IsPlaybackGoingOnForCar(CVehicle*)
    * IsPlaybackPausedForCar(CVehicle*)
    */
    static CVehicleStateEachFrame* Load(RwStream *stream, int resourceId, int totalSize);
    static std::int32_t RegisterRecordingFile(char const* name);
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
    * SetPlaybackSpeed(CVehicle*, float)
    * SetRecordingToPointClosestToCoors(int, CVector)
    * ShutDown()
    * SkipForwardInRecording(CVehicle*, float)
    * SkipToEndAndStopPlaybackRecordedCar(CVehicle*)
    * SmoothRecording(int)
    * StartPlaybackRecordedCar(CVehicle*, unsigned int, bool, bool)
    * StopPlaybackRecordedCar(CVehicle*)
    * StopPlaybackWithIndex(int)
    * UnpausePlaybackRecordedCar(CVehicle*)
    */
};
