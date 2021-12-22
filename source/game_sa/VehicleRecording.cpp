#include "StdInc.h"

#include "CStreamingDebugModule.h"

int32& CVehicleRecording::NumPlayBackFiles = *(int32*)0x97F630;
CPath(&CVehicleRecording::StreamingArray)[TOTAL_RRR_MODEL_IDS] = *(CPath(*)[TOTAL_RRR_MODEL_IDS])0x97D880;
bool(&CVehicleRecording::bUseCarAI)[TOTAL_VEHICLE_RECORDS] = *(bool(*)[TOTAL_VEHICLE_RECORDS])0x97D6C0;

void CVehicleRecording::InjectHooks() {
    ReversibleHooks::Install("CVehicleRecording", "Render", 0x459F70, &CVehicleRecording::Render);
}

void CVehicleRecording::Init()
{
    plugin::Call<0x459390>();
}

void CVehicleRecording::Render()
{
//NOTSA: Originally an empty function, called late in rendering pipeline, used for debug stuff
#ifdef EXTRA_DEBUG_FEATURES
    COcclusionDebugModule::ProcessRender();
    CStreamingDebugModule::ProcessRender();
#endif
}

bool CVehicleRecording::HasRecordingFileBeenLoaded(int32 rrrNumber)
{
    return plugin::CallAndReturn<bool, 0x45A060, int32>(rrrNumber);
}

void CVehicleRecording::Load(RwStream *stream, int32 resourceId, int32 totalSize)
{
    return plugin::Call<0x45A8F0, RwStream*, int32, int32>(stream, resourceId, totalSize);
}

int32 CVehicleRecording::RegisterRecordingFile(char const* name)
{
    return plugin::CallAndReturn<int32, 0x459F80, char const*>(name);
}

void CVehicleRecording::StartPlaybackRecordedCar(CVehicle* vehicle, int32 pathNumber, bool bUseCarAI, bool bLooped)
{
    plugin::Call<0x45A980, CVehicle*, int32, bool, bool>(vehicle, pathNumber, bUseCarAI, bLooped);
}

void CVehicleRecording::StopPlaybackRecordedCar(CVehicle* vehicle)
{
    plugin::Call<0x45A280, CVehicle*>(vehicle);
}

void CVehicleRecording::SetPlaybackSpeed(CVehicle* vehicle, float speed)
{
    plugin::Call<0x459660, CVehicle*, float>(vehicle, speed);
}

// unused, inlined?
// 0x459F00
void CVehicleRecording::RenderLineSegment(int32& numVertices) {
    if (numVertices > 1) {
        for (int32 i = 0; i < numVertices - 1; i++) {
            aTempBufferIndices[2 * i] = i;
            aTempBufferIndices[2 * i + 1] = i + 1;
        }
        if (RwIm3DTransform(aTempBufferVertices, numVertices, nullptr, 0)) {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPELINELIST, aTempBufferIndices, (numVertices - 1) * 2);
            RwIm3DEnd();
        }
    }
    numVertices = 0;
}
