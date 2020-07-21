#include "StdInc.h"

std::int32_t& CVehicleRecording::NumPlayBackFiles = *(std::int32_t*)0x97F630;
CPath(&CVehicleRecording::StreamingArray)[TOTAL_RRR_MODEL_IDS] = *(CPath(*)[TOTAL_RRR_MODEL_IDS])0x97D880;

bool CVehicleRecording::HasRecordingFileBeenLoaded(std::int32_t rrrNumber)
{
    return plugin::CallAndReturn<bool, 0x45A060, std::int32_t>(rrrNumber);
}

void CVehicleRecording::Load(RwStream *stream, std::int32_t resourceId, std::int32_t totalSize)
{
    return plugin::Call<0x45A8F0, RwStream*, std::int32_t, std::int32_t>(stream, resourceId, totalSize);
}

std::int32_t CVehicleRecording::RegisterRecordingFile(char const* name)
{
    return plugin::CallAndReturn<std::int32_t, 0x459F80, char const*>(name);
}

void CVehicleRecording::StartPlaybackRecordedCar(CVehicle* vehicle, std::int32_t pathNumber, bool bUseCarAI, bool bLooped)
{
    plugin::Call<0x45A980, CVehicle*, std::int32_t, bool, bool>(vehicle, pathNumber, bUseCarAI, bLooped);
}

void CVehicleRecording::StopPlaybackRecordedCar(CVehicle* vehicle)
{
    plugin::Call<0x45A280, CVehicle*>(vehicle);
}

void CVehicleRecording::SetPlaybackSpeed(CVehicle* vehicle, float speed)
{
    plugin::Call<0x459660, CVehicle*, float>(vehicle, speed);
}
