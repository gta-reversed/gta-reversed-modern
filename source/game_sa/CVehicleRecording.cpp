#include "StdInc.h"

CVehicleStateEachFrame* CVehicleRecording::Load(RwStream *stream, int resourceId, int totalSize)
{
    return plugin::CallAndReturn<CVehicleStateEachFrame*, 0x45A8F0, RwStream*, int, int>(stream, resourceId, totalSize);
}

std::int32_t CVehicleRecording::RegisterRecordingFile(char const* name)
{
    return plugin::CallAndReturn<std::int32_t, 0x459F80, char const*>(name);
}