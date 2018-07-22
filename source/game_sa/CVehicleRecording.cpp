#include "StdInc.h"

CVehicleStateEachFrame* CVehicleRecording::Load(RwStream *stream, int resourceId, int totalSize)
{
    return plugin::CallAndReturn<CVehicleStateEachFrame*, 0x45A8F0, RwStream*, int, int>(stream, resourceId, totalSize);
}