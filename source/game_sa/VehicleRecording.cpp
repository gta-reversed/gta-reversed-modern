#include "StdInc.h"

#include "VehicleRecording.h"

#include "toolsmenu\DebugModules\CStreamingDebugModule.h"
#include "TimecycEditor.h"
#include "toolsmenu\DebugModules\CullZonesDebugModule.h"


void CVehicleRecording::InjectHooks() {
    RH_ScopedClass(CVehicleRecording);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x459390);
    RH_ScopedInstall(InitAtStartOfGame, 0x45A1B0);
    RH_ScopedInstall(ShutDown, 0x459400);
}

// 0x459390
void CVehicleRecording::Init() {
    bPlaybackGoingOn.fill(false);
    bPlaybackPaused.fill(false);
    pPlaybackBuffer.fill(nullptr);
    pVehicleForPlayback.fill(nullptr);
    for (auto& path : StreamingArray) {
        path.m_pData = nullptr;
        path.m_nRefCount = 0;
    }
}

// 0x45A1B0
void CVehicleRecording::InitAtStartOfGame() {
    for (auto& array : StreamingArray) {
        array.m_pData = nullptr;
    }
    Init();
}

// 0x459400
void CVehicleRecording::ShutDown() {
    for (auto id = 0; auto& array : StreamingArray) {
        if (array.m_pData) {
            CMemoryMgr::Free(array.m_pData);
            array.m_pData = nullptr;
            CStreaming::RemoveModel(RRRToModelId(id));
        }
        id++;
    }
}

// 0x459F70 hook not needed
void CVehicleRecording::Render() {
// NOTSA: Originally an empty function, called late in rendering pipeline, used for debug stuff
#ifdef EXTRA_DEBUG_FEATURES
    COcclusionDebugModule::ProcessRender();
    CullZonesDebugModule::ProcessRender();
#endif
}

// 0x45A060
bool CVehicleRecording::HasRecordingFileBeenLoaded(int32 rrrNumber) {
    return plugin::CallAndReturn<bool, 0x45A060, int32>(rrrNumber);
}

// 0x45A8F0
void CVehicleRecording::Load(RwStream* stream, int32 resourceId, int32 totalSize) {
    return plugin::Call<0x45A8F0, RwStream*, int32, int32>(stream, resourceId, totalSize);
}

// 0x45A0F0
void CVehicleRecording::SmoothRecording(int32 resourceId) {
    assert(0);
}

// 0x459F80
int32 CVehicleRecording::RegisterRecordingFile(const char* name) {
    return plugin::CallAndReturn<int32, 0x459F80, const char*>(name);

    auto recordId = 850;
    if (sscanf(name, "carrec%d", &recordId) == 0) {
        sscanf(name, "CARREC%d", &recordId);
    }

    StreamingArray[NumPlayBackFiles].m_nNumber = recordId;
    StreamingArray[NumPlayBackFiles].m_pData = nullptr;
    return NumPlayBackFiles++;
}

void CVehicleRecording::RemoveRecordingFile(int32) {
    assert(0);
}


void CVehicleRecording::RequestRecordingFile(int32) {
    assert(0);
}

// 0x45A980
void CVehicleRecording::StartPlaybackRecordedCar(CVehicle* vehicle, int32 pathNumber, bool useCarAI, bool bLooped) {
    plugin::Call<0x45A980, CVehicle*, int32, bool, bool>(vehicle, pathNumber, useCarAI, bLooped);
}

// 0x45A280
void CVehicleRecording::StopPlaybackRecordedCar(CVehicle* vehicle) {
    plugin::Call<0x45A280, CVehicle*>(vehicle);
}

// 0x459740
void CVehicleRecording::PausePlaybackRecordedCar(CVehicle* vehicle) {
    assert(0);
}

// 0x459850
void CVehicleRecording::UnpausePlaybackRecordedCar(CVehicle* vehicle) {
    assert(0);
}

// 0x459660
void CVehicleRecording::SetPlaybackSpeed(CVehicle* vehicle, float speed) {
    plugin::Call<0x459660, CVehicle*, float>(vehicle, speed);
}

// [debug]
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

// 0x45A610
void CVehicleRecording::SaveOrRetrieveDataForThisFrame() {
    plugin::Call<0x45A610>();
}

// 0x4594C0
bool CVehicleRecording::IsPlaybackGoingOnForCar(CVehicle* vehicle) {
    return plugin::CallAndReturn<bool, 0x4594C0, CVehicle*>(vehicle);
}

// 0x4595A0
bool CVehicleRecording::IsPlaybackPausedForCar(CVehicle* vehicle) {
    return plugin::CallAndReturn<bool, 0x4595A0, CVehicle*>(vehicle);
}
