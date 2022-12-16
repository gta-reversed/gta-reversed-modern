#include "StdInc.h"
#include <span>

#include "TimecycEditor.h"
#include "VehicleRecording.h"

#include "toolsmenu\DebugModules\CStreamingDebugModule.h"
#include "toolsmenu\DebugModules\CullZonesDebugModule.h"
#include "extensions\enumerate.hpp"

uint32 CPath::GetIndex() const {
    const auto index = this - CVehicleRecording::StreamingArray.data();
    assert(index >= 0 && index < TOTAL_VEHICLE_RECORDS);

    return index;
}

void CVehicleRecording::InjectHooks() {
    RH_ScopedClass(CVehicleRecording);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x459390);
    RH_ScopedInstall(InitAtStartOfGame, 0x45A1B0);
    RH_ScopedInstall(ShutDown, 0x459400);
    RH_ScopedInstall(Render, 0x459F70, {.locked = true});
    RH_ScopedInstall(ChangeCarPlaybackToUseAI, 0x45A360);
    RH_ScopedInstall(FindIndexWithFileNameNumber, 0x459FF0);
    RH_ScopedInstall(InterpolateInfoForCar, 0x459B30);
    RH_ScopedInstall(HasRecordingFileBeenLoaded, 0x45A060);
    RH_ScopedInstall(Load, 0x45A8F0);
    RH_ScopedInstall(SmoothRecording, 0x45A0F0, {.reversed = false});
    RH_ScopedInstall(RegisterRecordingFile, 0x459F80);
    RH_ScopedInstall(RemoveRecordingFile, 0x45A0A0);
    RH_ScopedInstall(RequestRecordingFile, 0x45A020);
    RH_ScopedInstall(StopPlaybackWithIndex, 0x459440);
    RH_ScopedInstall(StartPlaybackRecordedCar, 0x45A980, {.reversed = false});
    RH_ScopedInstall(StopPlaybackRecordedCar, 0x45A280);
    RH_ScopedInstall(PausePlaybackRecordedCar, 0x459740);
    RH_ScopedInstall(UnpausePlaybackRecordedCar, 0x459850);
    RH_ScopedInstall(SetPlaybackSpeed, 0x459660);
    RH_ScopedInstall(RenderLineSegment, 0x459F00);
    RH_ScopedInstall(RemoveAllRecordingsThatArentUsed, 0x45A160);
    RH_ScopedInstall(RestoreInfoForCar, 0x459A30);
    RH_ScopedInstall(RestoreInfoForMatrix, 0x459960);
    RH_ScopedInstall(SaveOrRetrieveDataForThisFrame, 0x45A610, {.reversed = false});
    RH_ScopedInstall(SetRecordingToPointClosestToCoors, 0x45A1E0);
    RH_ScopedInstall(IsPlaybackGoingOnForCar, 0x4594C0);
    RH_ScopedInstall(IsPlaybackPausedForCar, 0x4595A0);
}

// 0x459390
void CVehicleRecording::Init() {
    bPlaybackGoingOn.fill(false);
    bPlaybackPaused.fill(false);
    pPlaybackBuffer.fill(nullptr);
    pVehicleForPlayback.fill(nullptr);
    for (auto& recording : StreamingArray) {
        recording.m_pData = nullptr;
        recording.m_nRefCount = 0;
    }
}

// 0x45A1B0
void CVehicleRecording::InitAtStartOfGame() {
    for (auto& recording : StreamingArray) {
        recording.m_pData = nullptr;
    }
    Init();
}

// 0x459400
void CVehicleRecording::ShutDown() {
    for (auto&& [i, recording] : notsa::enumerate(StreamingArray)) {
        recording.Remove();
    }
}

// 0x459F70 hook not needed
void CVehicleRecording::Render() {
// NOTSA: Originally an empty function, called late in rendering pipeline, used for debug stuff
#ifdef EXTRA_DEBUG_FEATURES
    TimeCycleDebugModule::ProcessRender();
    COcclusionDebugModule::ProcessRender();
    CStreamingDebugModule::ProcessRender();
    CullZonesDebugModule::ProcessRender();
#endif
}

// 0x45A360
void CVehicleRecording::ChangeCarPlaybackToUseAI(CVehicle* vehicle) {
    FindVehicleRecordingIndex(vehicle).and_then([vehicle](uint32 index) -> std::optional<uint32> {
        bUseCarAI[index] = true;

        vehicle->m_autoPilot.m_nCarMission = MISSION_FOLLOW_PRE_RECORDED_PATH;
        SetRecordingToPointClosestToCoors(index, vehicle->GetPosition());
        vehicle->physicalFlags.bDisableCollisionForce = false;
        vehicle->ProcessControlCollisionCheck(false);
        vehicle->m_nStatus = STATUS_PHYSICS;

        return {};
    });
}

// inlined
// 0x459FF0
uint32 CVehicleRecording::FindIndexWithFileNameNumber(int32 number) {
    for (auto&& [i, recording] : notsa::enumerate(GetRecordings())) {
        if (recording.m_nNumber == number) {
            return i;
        }
    }
    return 0;
}

// 0x459B30
void CVehicleRecording::InterpolateInfoForCar(CVehicle* vehicle, CVehicleStateEachFrame* frame, float interpValue) {
    auto& vehicleMatrix = vehicle->GetMatrix();
    CMatrix transition;
    RestoreInfoForMatrix(transition, frame);
    // maybe make a lerp function for matrices
    transition.ScaleAll(interpValue);
    vehicleMatrix.ScaleAll(1.0f - interpValue);
    vehicleMatrix += transition;

    vehicle->GetMoveSpeed() = Lerp(vehicle->GetMoveSpeed(), frame->m_sVelocity, interpValue);
}

// 0x45A060
bool CVehicleRecording::HasRecordingFileBeenLoaded(int32 recordId) {
    const auto recording = FindRecording(recordId);
    return recording.has_value() && recording.value()->m_pData;
}

// 0x45A8F0
void CVehicleRecording::Load(RwStream* stream, int32 recordId, int32 totalSize) {
    auto allocated = CMemoryMgr::Malloc(totalSize);
    StreamingArray[recordId].m_pData = static_cast<CVehicleStateEachFrame*>(allocated);
    const auto size = RwStreamRead(stream, allocated, 9'999'999u);
    StreamingArray[recordId].m_nSize = size;
    RwStreamClose(stream, nullptr);

    for (auto&& [i, frame] : notsa::enumerate(std::span{ StreamingArray[recordId].m_pData, size })) {
        if (i != 0 && frame.m_nTime == 0) {
            // no valid frame that is not zeroth can have zero as a time.
            // so we count them as invalid and prune the following including itself.
            StreamingArray[recordId].m_nSize = i * sizeof(CVehicleStateEachFrame);
            break;
        }
    }
    SmoothRecording(recordId);
}

// 0x45A0F0
void CVehicleRecording::SmoothRecording(int32 recordId) {
    plugin::Call<0x45A0F0, int32>(recordId);
}

// 0x459F80
int32 CVehicleRecording::RegisterRecordingFile(const char* name) {
    auto recordId = 850;
    if (sscanf(name, "carrec%d", &recordId) == 0) {
        RET_IGNORED(sscanf(name, "CARREC%d", &recordId));
    }

    StreamingArray[NumPlayBackFiles].m_nNumber = recordId;
    StreamingArray[NumPlayBackFiles].m_pData = nullptr;
    return NumPlayBackFiles++;
}

// 0x45A0A0
void CVehicleRecording::RemoveRecordingFile(int32 recordId) {
    FindRecording(recordId).and_then([](CPath* recording) -> std::optional<uint32> {
        if (recording->m_pData && !recording->m_nRefCount) {
            recording->Remove();
        }
        return {};
    });
}

// 0x45A020
void CVehicleRecording::RequestRecordingFile(int32 recordId) {
    auto index = 0;
    FindRecording(recordId).and_then([&index, recordId](CPath* recording) -> std::optional<uint32> {
        index = recording->GetIndex();
        recording->Remove();
        return {};
    });

    CStreaming::RequestModel(RRRToModelId(index), STREAMING_KEEP_IN_MEMORY | STREAMING_MISSION_REQUIRED);
}

// 0x459440
void CVehicleRecording::StopPlaybackWithIndex(int32 index) {
    if (auto vehicle = pVehicleForPlayback[index]) {
        vehicle->m_autoPilot.m_vehicleRecordingId = -1;
        pVehicleForPlayback[index]->physicalFlags.bDisableCollisionForce = false;
    }
    pVehicleForPlayback[index] = nullptr;
    pPlaybackBuffer[index] = nullptr;
    PlaybackBufferSize[index] = 0;
    bPlaybackGoingOn[index] = false;

    StreamingArray[PlayBackStreamingIndex[index]].RemoveRef();
}

// 0x45A980
void CVehicleRecording::StartPlaybackRecordedCar(CVehicle* vehicle, int32 pathNumber, bool useCarAI, bool bLooped) {
    const auto [freeIdx, streamId] = [pathNumber]() -> std::pair<uint32, uint32> {
        auto idx = 0;
        for (auto i : GetActivePlaybackIndices()) {
            if (!bPlaybackGoingOn[i]) {
                idx = i;
                break;
            }
        }

        return { idx, FindIndexWithFileNameNumber(pathNumber)};
    }();
    // ...
}

// 0x45A280
void CVehicleRecording::StopPlaybackRecordedCar(CVehicle* vehicle) {
    FindVehicleRecordingIndex(vehicle).and_then([](auto i) -> std::optional<uint32> { StopPlaybackWithIndex(i); return {}; });
}

// 0x459740
void CVehicleRecording::PausePlaybackRecordedCar(CVehicle* vehicle) {
    FindVehicleRecordingIndex(vehicle).and_then([](auto i) -> std::optional<uint32> { bPlaybackPaused[i] = true; return {}; });
}

// 0x459850
void CVehicleRecording::UnpausePlaybackRecordedCar(CVehicle* vehicle) {
    FindVehicleRecordingIndex(vehicle).and_then([](auto i) -> std::optional<uint32> { bPlaybackPaused[i] = false; return {}; });
}

// 0x459660
void CVehicleRecording::SetPlaybackSpeed(CVehicle* vehicle, float speed) {
    FindVehicleRecordingIndex(vehicle).and_then([speed](auto i) -> std::optional<uint32> { PlaybackSpeed[i] = speed; return {}; });
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

// 0x45A160
void CVehicleRecording::RemoveAllRecordingsThatArentUsed() {
    for (auto&& [i, recording] : notsa::enumerate(GetRecordings())) {
        if (recording.m_nNumber == i && recording.m_pData && !recording.m_nRefCount) {
            recording.Remove();
        }
    }
}

// 0x459A30
void CVehicleRecording::RestoreInfoForCar(CVehicle* vehicle, CVehicleStateEachFrame* frame, bool pause) {
    RestoreInfoForMatrix(vehicle->GetMatrix(), frame);
    vehicle->ResetTurnSpeed();
    vehicle->m_fSteerAngle = frame->m_bSteeringAngle;
    vehicle->m_fGasPedal   = frame->m_bGasPedalPower;
    vehicle->m_fBreakPedal = frame->m_bBreakPedalPower;
    vehicle->vehicleFlags.bIsHandbrakeOn = !pause && frame->m_bHandbrakeUsed;

    if (pause) {
        vehicle->m_fSteerAngle = vehicle->m_fGasPedal = vehicle->m_fBreakPedal = 0.0f;
        vehicle->ResetMoveSpeed();
    }
}

// 0x459960
void CVehicleRecording::RestoreInfoForMatrix(CMatrix& matrix, CVehicleStateEachFrame* frame) {
    matrix.GetRight()    = frame->m_bRight;
    matrix.GetForward()  = frame->m_bTop;
    matrix.GetUp()       = matrix.GetRight().Cross(matrix.GetForward());
    matrix.GetPosition() = frame->m_vecPosn;
}

// 0x45A610
void CVehicleRecording::SaveOrRetrieveDataForThisFrame() {
    if (CReplay::Mode == MODE_PLAYBACK)
        return;

    for (auto i : GetActivePlaybackIndices()) {
        auto vehicle = pVehicleForPlayback[i];
        if (!vehicle || vehicle->physicalFlags.bDestroyed) {
            StopPlaybackWithIndex(i);
            continue;
        }
        if (bUseCarAI[i])
            continue;

        const auto delta = static_cast<float>(CTimer::GetTimeInMS() - CTimer::m_snPPPPreviousTimeInMilliseconds);
        if (delta * PlaybackSpeed[i] / 4.0f > 500.0f) {
            printf("That's a really big step\n");
        }
        PlaybackRunningTime[i] += delta * PlaybackSpeed[i] / 4.0f;

        auto current = GetCurrentFrameForBuffer(i);
        auto next = current + 1;
        if (next->m_nTime < PlaybackRunningTime[i]) {
            for (; next < current + PlaybackBufferSize[i] && next->m_nTime < PlaybackRunningTime[i]; ++next) {
                ++current;
                PlaybackIndex[i] += sizeof(CVehicleStateEachFrame);
            }
        }
        for (; current > pPlaybackBuffer[i] && current->m_nTime > PlaybackRunningTime[i]; --next) {
            --current;
            PlaybackIndex[i] -= sizeof(CVehicleStateEachFrame);
        }

        if (next < GetCurrentFrameForBuffer(i)) {
            RestoreInfoForCar(vehicle, current, 0);
            const auto interp = PlaybackRunningTime[i] - (float)current->m_nTime / (float)(next->m_nTime - current->m_nTime);
            InterpolateInfoForCar(vehicle, next, interp);

            if (vehicle->IsSubTrain()) {
                vehicle->AsTrain()->FindPositionOnTrackFromCoors();
            }
            vehicle->ProcessControlCollisionCheck(false);
            vehicle->RemoveAndAdd();
            vehicle->UpdateRW();
            vehicle->UpdateRwFrame();
            MarkSurroundingEntitiesForCollisionWithTrain(vehicle->GetPosition(), 5.0f, vehicle, true);
        } else if (bPlaybackLooped[i]) {
            PlaybackRunningTime[i] = 0.0f;
            PlaybackIndex[i] = 0;
        } else {
            StopPlaybackRecordedCar(vehicle);
        }
    }
}

// 0x45A1E0
void CVehicleRecording::SetRecordingToPointClosestToCoors(int32 playbackId, CVector posn) {
    assert(0);
    auto minDist = 1'000'000.0f; // FLT_MAX
    for (auto&& [i, frame] : notsa::enumerate(GetFramesFromPlaybackBuffer(playbackId))) {
        if (const auto d = DistanceBetweenPoints(frame.m_vecPosn, posn); d < minDist) {
            SetFrameIndexForPlaybackBuffer(playbackId, i);
            minDist = d;
        }
    }
}

// 0x4594C0
bool CVehicleRecording::IsPlaybackGoingOnForCar(CVehicle* vehicle) {
    return FindVehicleRecordingIndex(vehicle).has_value();
}

// 0x4595A0
bool CVehicleRecording::IsPlaybackPausedForCar(CVehicle* vehicle) {
    // SA code loops through all playbacks but always returns false.
    return false;
}
