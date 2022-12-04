#include "StdInc.h"

#include "Camera.h"
#include "ControllerConfigManager.h"
#include "EntryExitManager.h"
#include "FireManager.h"
#include "PedClothesDesc.h"
#include "PlaneBanners.h"
#include "RealTimeShadowManager.h"
#include "Replay.h"
#include "Skidmarks.h"
#include "extensions/enumerate.hpp"

constexpr float HEADING_COMPRESS_VALUE = 40.764328f;

void CReplay::InjectHooks() {
    RH_ScopedClass(CReplay);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x45E220);
    RH_ScopedInstall(Update, 0x460500);
    RH_ScopedInstall(DisableReplays, 0x45B150);
    RH_ScopedInstall(EnableReplays, 0x45B160);
    RH_ScopedInstall(StorePedAnimation, 0x45B170);
    RH_ScopedInstall(StorePedUpdate, 0x45C940, {.reversed = true});
    RH_ScopedInstall(RetrievePedAnimation, 0x45B4D0);
    RH_ScopedInstall(ProcessReplayCamera, 0x45D060);
    RH_ScopedInstall(Display, 0x45C210);
    RH_ScopedInstall(MarkEverythingAsNew, 0x45D430);
    RH_ScopedInstall(EmptyReplayBuffer, 0x45EC90);
    RH_ScopedInstall(EmptyPedsAndVehiclePools_NoDestructors, 0x45D390);
    RH_ScopedInstall(GoToNextBlock, 0x45E2A0);
    RH_ScopedInstall(RecordVehicleDeleted, 0x45EBB0);
    RH_ScopedInstall(RecordPedDeleted, 0x45EC20, { .reversed = false }); // <-- broken
    RH_ScopedInstall(SaveReplayToHD, 0x45C340);
    RH_ScopedInstall(PlayReplayFromHD, 0x460390);
    RH_ScopedInstall(ShouldStandardCameraBeProcessed, 0x45C440);
    RH_ScopedInstall(ProcessLookAroundCam, 0x45D760);
    RH_ScopedInstall(FindPoolIndexForPed, 0x45C450);
    RH_ScopedInstall(FindPoolIndexForVehicle, 0x45C460);
    RH_ScopedInstall(ProcessPedUpdate, 0x45CA70);
    // RH_ScopedInstall(CanWeFindPoolIndexForPed, 0x0, { .reversed = false });
    // RH_ScopedInstall(CanWeFindPoolIndexForVehicle, 0x0, { .reversed = false });
    RH_ScopedInstall(StorePlayerInfoVariables, 0x45F020);
    RH_ScopedInstall(RestorePlayerInfoVariables, 0x45E1F0);
    RH_ScopedInstall(StoreStuffInMem, 0x45F180);
    RH_ScopedInstall(RestoreStuffFromMem, 0x45ECD0);
    RH_ScopedInstall(FinishPlayback, 0x45F050);
    RH_ScopedInstall(RecordThisFrame, 0x45E300, { .reversed = false });
    RH_ScopedInstall(StoreClothesDesc, 0x45C750);
    RH_ScopedInstall(RestoreClothesDesc, 0x45C7D0);
    RH_ScopedInstall(DealWithNewPedPacket, 0x45CEA0);
    RH_ScopedInstall(PlayBackThisFrameInterpolation, 0x45F380, { .reversed = false });
    RH_ScopedInstall(FastForwardToTime, 0x460350);
    RH_ScopedInstall(PlayBackThisFrame, 0x4604A0);
    RH_ScopedInstall(FindSizeOfPacket, 0x45C850);
    RH_ScopedInstall(IsThisVehicleUsedInRecording, 0x45DE40);
    RH_ScopedInstall(IsThisPedUsedInRecording, 0x45DDE0);
    RH_ScopedInstall(InitialiseVehiclePoolConversionTable, 0x45EFA0, {.reversed = false}); // <-- broken for now
    RH_ScopedInstall(InitialisePedPoolConversionTable, 0x45EF20, {.reversed = false});     //
    RH_ScopedInstall(InitialisePoolConversionTables, 0x45F370);
    RH_ScopedInstall(FindFirstFocusCoordinate, 0x45D6C0);
    RH_ScopedInstall(NumberFramesAvailableToPlay, 0x45D670);
    RH_ScopedInstall(StreamAllNecessaryCarsAndPeds, 0x45D4B0);
    RH_ScopedInstall(CreatePlayerPed, 0x45D540, { .locked = true });
    RH_ScopedInstall(TriggerPlayback, 0x4600F0);
}

// 0x460625 thunk
// 0x45E220
void CReplay::Init() {
    Mode = MODE_RECORD;
    Playback = {.m_nOffset = 0, .m_pBase = nullptr, .m_bSlot = 0};
    EmptyReplayBuffer();
    pReferences = nullptr;
    pPickups = nullptr;
    pEmptyReferences = nullptr;
    pWorld1 = nullptr;
    pStoredCam = nullptr;
    pRadarBlips = nullptr;
    bPlayingBackFromFile = false;
    bDoLoadSceneWhenDone = false;
    FramesActiveLookAroundCam = 0;
    bReplayEnabled = true;
}

// 0x460500
void CReplay::Update() {
    if (CCutsceneMgr::IsCutsceneProcessing() || CPad::GetPad()->ArePlayerControlsDisabled()
        || FrontEndMenuManager.m_bMenuActive || CEntryExitManager::ms_exitEnterState) {
        Init();
        return;
    }

    if (CTimer::GetIsCodePaused() || CTimer::GetIsUserPaused())
        return;

    static uint32& s_FrameRecordCounter = *reinterpret_cast<uint32*>(0x97FB40);
    if (Mode == MODE_PLAYBACK) {
        PlayBackThisFrame();
    } else if (CTimer::GetTimeInMS() - s_FrameRecordCounter > 26) {
        s_FrameRecordCounter = CTimer::GetTimeInMS();
        RecordThisFrame();
    }

    if (CDraw::FadeValue == 0 && bReplayEnabled) {
        if (Mode == MODE_PLAYBACK) {
            if (ControlsManager.GetIsKeyboardKeyDown(rsF1) || ControlsManager.GetIsKeyboardKeyDown(rsF3)) {
                FinishPlayback();
            }
        } else {
            if (ControlsManager.GetIsKeyboardKeyDown(rsF1)) {
                // Play stored replay
                TriggerPlayback(REPLAY_CAM_MODE_AS_STORED, CVector{}, false);
            } else if (ControlsManager.GetIsKeyboardKeyDown(rsF2)) {
                // Save to hard disk
                SaveReplayToHD();
            } else if (ControlsManager.GetIsKeyboardKeyDown(rsF3)) {
                // Play from hard disk
                PlayReplayFromHD();
            }
        }
    }
}

// 0x45B150
void CReplay::DisableReplays() {
    bReplayEnabled = false;
}

// 0x45B160
void CReplay::EnableReplays() {
    bReplayEnabled = true;
}

// 0x45B170
void CReplay::StorePedAnimation(CPed* ped, CStoredAnimationState& state) {
    float blendValue{};
    CAnimBlendAssociation* secondAnim{};
    const auto assocMain = RpAnimBlendClumpGetMainAssociation(ped->m_pRwClump, &secondAnim, &blendValue);
    if (assocMain) {
        state.first = {
            .m_nAnimId   = assocMain->m_nAnimId,
            .m_nTime     = (uint8)(std::clamp(assocMain->m_fCurrentTime, 0.0f, 4.0f) * 63.75f),
            .m_nSpeed    = (uint8)(std::clamp(assocMain->m_fSpeed, 0.0f, 3.0f) * 85.0f),
            .m_nGroupId1 = (uint8)assocMain->m_nAnimGroup
        };
    } else {
        state.first = {
            .m_nAnimId   = ANIM_ID_IDLE,
            .m_nTime     = 0,
            .m_nSpeed    = 85,
            .m_nGroupId1 = 0
        };
    }

    if (secondAnim) {
        state.second = {
            .m_nAnimId   = secondAnim->m_nAnimId,
            .m_nTime     = (uint8)(std::clamp(secondAnim->m_fCurrentTime, 0.0f, 4.0f) * 63.75f),
            .m_nSpeed    = (uint8)(std::clamp(secondAnim->m_fSpeed, 0.0f, 3.0f) * 85.0f),
            .m_nGroupId1 = (uint8)(std::clamp(blendValue, 0.0f, 2.0f) * 127.5f),
            .m_nGroupId2 = (uint8)secondAnim->m_nAnimGroup
        };
    } else {
        state.second = {
            .m_nAnimId   = ANIM_ID_WALK,
            .m_nTime     = 0,
            .m_nSpeed    = 0,
            .m_nGroupId1 = 0,
            .m_nGroupId2 = 0
        };
    }

    const auto assocPartial = RpAnimBlendClumpGetMainPartialAssociation(ped->m_pRwClump);
    if (assocPartial && assocPartial->m_nAnimId >= ANIM_ID_WALK) {
        state.third = {
            .m_nAnimId   = assocPartial->m_nAnimId,
            .m_nTime     = (uint8)(std::clamp(assocPartial->m_fCurrentTime, 0.0f, 4.0f) * 63.75f),
            .m_nSpeed    = (uint8)(std::clamp(assocPartial->m_fSpeed, 0.0f, 3.0f) * 85.0f),
            .m_nGroupId1 = (uint8)(std::clamp(assocPartial->m_fBlendAmount, 0.0f, 2.0f) * 127.5f),
            .m_nGroupId2 = (uint8)assocPartial->m_nAnimGroup
        };
    } else {
        state.third = {
            .m_nAnimId   = ANIM_ID_WALK,
            .m_nTime     = 0,
            .m_nSpeed    = 0,
            .m_nGroupId1 = 0,
            .m_nGroupId2 = 0
        };
    }
}

// 0x45C940
void CReplay::StorePedUpdate(CPed* ped, uint8 index) {
    CCompressedMatrixNotAligned compMatrix{};
    compMatrix.CompressFromFullMatrix(ped->GetMatrix());

    // TODO: refactor
    uint8 flags = 0u;
    auto v3 = (flags ^ ((uint32)ped->m_nFlags >> 7)) & 1 ^ flags;
    auto v4 = v3 ^ (v3 ^ (uint8)(2 * ((uint32)ped->m_nFlags >> 30))) & 2;
    flags = v4 ^ (v4 ^ (4 * (ped->m_nFlags < 0))) & 4;

    if (ped == FindPlayerPed() && gbFirstPersonRunThisFrame) {
        flags &= ~1u;
    }

    auto vehicleIdx = [ped]() {
        if (ped->IsInVehicle()) {
            return GetVehiclePool()->GetIndex(ped->GetVehicleIfInOne()) + 1;
        } else {
            return 0;
        }
    }();

    CStoredAnimationState animState{};
    StorePedAnimation(ped, animState);

    Record.Write({.type = REPLAY_PACKET_PED_UPDATE, .ped = {
        .index                    = index,
        .heading                  = (int8)(ped->m_fCurrentRotation * HEADING_COMPRESS_VALUE),
        .vehicleIndex             = (uint8)vehicleIdx,
        .animState                = animState,
        .matrix                   = compMatrix,
        .weaponModel              = (int16)ped->m_nWeaponModelId,
        .animGroup                = (uint16)ped->m_nAnimGroup,
        .contactSurfaceBrightness = (uint8)(ped->m_fContactSurfaceBrightness * 100.0f),
        .flags                    = flags,
    }}, true);
}

// 0x45B4D0
void CReplay::RetrievePedAnimation(CPed* ped, const CStoredAnimationState& state) {
    // todo: refactor

    CAnimBlendAssociation* anim = nullptr;
    if (state.first.m_nAnimId > 3u) {
        auto animBlock = CAnimManager::ms_aAnimAssocGroups[state.first.m_nGroupId1].m_pAnimBlock;
        if (animBlock && animBlock->bLoaded) {
            anim = CAnimManager::BlendAnimation(ped->m_pRwClump, (AssocGroupId)state.first.m_nGroupId1, (AnimationId)state.first.m_nAnimId, 100.0f);
        } else {
            anim = CAnimManager::BlendAnimation(ped->m_pRwClump, ANIM_GROUP_DEFAULT, ANIM_ID_WALK, 100.0f);
        }
    } else {
        anim = CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, (AnimationId)state.first.m_nAnimId, 100.0f);
    }
    anim->SetCurrentTime(state.first.m_nTime * 0.015686275f);
    anim->SetSpeed(state.first.m_nSpeed * 0.011764706f);
    anim->SetBlend(1.0f, 1.0f);
    anim->m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;

    anim = nullptr;
    if (state.second.m_nGroupId1 && state.second.m_nAnimId && CAnimManager::ms_aAnimAssocGroups[state.second.m_nGroupId2].m_nNumAnimations > 0) {
        if (state.second.m_nAnimId > 3u) {
            anim = CAnimManager::BlendAnimation(ped->m_pRwClump, (AssocGroupId)state.second.m_nGroupId2, (AnimationId)state.second.m_nAnimId, 100.0f);
        } else {
            anim = CAnimManager::BlendAnimation(ped->m_pRwClump, ped->m_nAnimGroup, (AnimationId)state.second.m_nAnimId, 100.0f);
        }

        if (anim) {
            anim->SetCurrentTime(state.second.m_nTime * 0.015686275f);
            anim->SetSpeed(state.second.m_nSpeed * 0.011764706f);
            anim->SetBlend(state.second.m_nGroupId1 * 0.0078431377f, 1.0f); // wtf?
            anim->m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
        }
    }

    RpAnimBlendClumpRemoveAssociations(ped->m_pRwClump, 16u); // todo: flags
    if (state.third.m_nGroupId1 && state.third.m_nAnimId) {
        if (/*state.third.m_nGroupId1 >= 0 &&*/ state.third.m_nAnimId != 3u) {
            if (auto animBlock = CAnimManager::ms_aAnimAssocGroups[state.third.m_nGroupId2].m_pAnimBlock; animBlock && animBlock->bLoaded) {
                anim = CAnimManager::BlendAnimation(ped->m_pRwClump, (AssocGroupId)state.third.m_nGroupId2, (AnimationId)state.third.m_nAnimId, 1000.0f);

                anim->SetCurrentTime(state.third.m_nTime * 0.015686275f);
                anim->SetSpeed(state.third.m_nSpeed * 0.011764706f);
                anim->SetBlend(state.third.m_nGroupId1 * 0.0078431377f, 0.0f);
                anim->m_nCallbackType = ANIM_BLEND_CALLBACK_NONE;
            }
        }
    }

}

// 0x45C210
void CReplay::Display() {
    if (ShouldStandardCameraBeProcessed())
        return;

    static uint32& g_ReplayTextTimer = *(uint32*)0xA43240;
    if ((++g_ReplayTextTimer & 32) == 0)
        return;

    CFont::SetScale(SCREEN_SCALE_X(1.5f), SCREEN_SCALE_Y(1.5f));
    CFont::SetOrientation(eFontAlignment::ALIGN_LEFT);
    CFont::SetBackground(false, false);
    CFont::SetCentreSize(float(RsGlobal.maximumWidth - 20));
    CFont::SetProportional(true);
    CFont::SetColor({ 255u, 255u, 200u, 200u });
    CFont::SetFontStyle(eFontStyle::FONT_SUBTITLES);
    CFont::PrintString(float(RsGlobal.maximumWidth / 10), float(RsGlobal.maximumHeight / 15), TheText.Get("REPLAY"));
}

// 0x45D430
void CReplay::MarkEverythingAsNew() {
    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        if (auto ped = GetPedPool()->GetAt(i)) {
            ped->bHasAlreadyBeenRecorded = false;
        }
    }

    for (auto i = 0; i < GetVehiclePool()->GetSize(); i++) {
        if (auto vehicle = GetVehiclePool()->GetAt(i)) {
            vehicle->vehicleFlags.bHasAlreadyBeenRecorded = false;
        }
    }
}

// 0x45EC90
void CReplay::EmptyReplayBuffer() {
    if (Mode == MODE_PLAYBACK)
        return;

    rng::fill(BufferStatus, REPLAYBUFFER_NOT_AVAILABLE);
    BufferStatus[0] = REPLAYBUFFER_IN_USE;
    Buffers[0].Write(0, {REPLAY_PACKET_END});
    Record = {.m_nOffset = 0, .m_pBase = &Buffers[0], .m_bSlot = 0};
    MarkEverythingAsNew();
}

// 0x45D390
void CReplay::EmptyPedsAndVehiclePools_NoDestructors() {
    for (auto i = 0; i < GetVehiclePool()->GetSize(); i++) {
        if (auto vehicle = GetVehiclePool()->GetAt(i)) {
            CWorld::Remove(vehicle);
        }
    }

    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        if (auto ped = GetPedPool()->GetAt(i)) {
            CWorld::Remove(ped);

            if (auto shadow = ped->m_pShadowData) {
                g_realTimeShadowMan.ReturnRealTimeShadow(shadow);
            }
        }
    }
}

// 0x45E2A0
void CReplay::GoToNextBlock() {
    Record.Write({REPLAY_PACKET_END});
    BufferStatus[Record.m_bSlot] = REPLAYBUFFER_FULL;

    Record.Next();
    Record.Write({REPLAY_PACKET_END});
    BufferStatus[Record.m_bSlot] = REPLAYBUFFER_IN_USE;

    MarkEverythingAsNew();
}

// 0x45EBB0
void CReplay::RecordVehicleDeleted(CVehicle* vehicle) {
    if (Mode != MODE_RECORD)
        return;

    if (Record.m_nOffset + FindSizeOfPacket(REPLAY_PACKET_DELETED_VEH) > 99'984) {
        GoToNextBlock();
    }

    Record.Write({.type = REPLAY_PACKET_DELETED_VEH, .deletedVehicle = {.poolRef = (int16)(GetVehiclePool()->GetIndex(vehicle) / 2584)}}, true);
    Record.Write({REPLAY_PACKET_END});
}

// 0x45EC20; broken for some reason
void CReplay::RecordPedDeleted(CPed* ped) {
    if (Mode != MODE_RECORD)
        return;

    if (Record.m_nOffset + FindSizeOfPacket(REPLAY_PACKET_DELETED_PED) > 99'984) {
        GoToNextBlock();
    }

    Record.Write({.type = REPLAY_PACKET_DELETED_PED, .deletedPed = {.poolRef = (int16)(GetPedPool()->GetIndex(ped) / 1988)}}, true);
    Record.Write({REPLAY_PACKET_END});
}

// 0x45EFA0
void CReplay::InitialiseVehiclePoolConversionTable() {
    rng::fill(m_VehiclePoolConversion, -1);
    auto convIdx = 0u;
    for (auto poolIdx = 0; poolIdx < GetVehiclePool()->GetSize() && convIdx < std::size(m_VehiclePoolConversion); poolIdx++, convIdx++) {
        if (GetVehiclePool()->GetAt(poolIdx) && IsThisVehicleUsedInRecording(convIdx)) {
            m_VehiclePoolConversion[convIdx] = poolIdx;
        }
    }
}

// 0x45EF20
void CReplay::InitialisePedPoolConversionTable() {
    rng::fill(m_PedPoolConversion, -1);
    auto convIdx = 0u;
    for (auto poolIdx = 0; poolIdx < GetPedPool()->GetSize() && convIdx < std::size(m_PedPoolConversion); poolIdx++, convIdx++) {
        if (GetPedPool()->GetAt(poolIdx) && IsThisVehicleUsedInRecording(convIdx)) {
            m_PedPoolConversion[convIdx] = poolIdx;
        }
    }
}

// 0x45F370
void CReplay::InitialisePoolConversionTables() {
    InitialiseVehiclePoolConversionTable();
    InitialisePedPoolConversionTable();
}

// 0x45C340
void CReplay::SaveReplayToHD() {
    CFileMgr::SetDirMyDocuments();

    if (const auto file = CFileMgr::OpenFileForWriting("replay.rep")) {
        CFileMgr::Write(file, "GtaSA29", 8u);

        // TODO: refactor
        auto idx = 7u;
        for (auto&& [i, status] : notsa::enumerate(BufferStatus)) {
            if (status == 2) {
                idx = i;
                break;
            }
        }

        auto slot = (idx + 1) % 8;
        for (auto j = BufferStatus[slot]; j != REPLAYBUFFER_IN_USE && j != REPLAYBUFFER_FULL; j = BufferStatus[slot]) {
            slot = (slot + 1) % 8;
        }
        CFileMgr::Write(file, &Buffers.at(slot), sizeof(tReplayBuffer));

        for (slot = (slot + 1) % 8; BufferStatus[slot] != REPLAYBUFFER_IN_USE; slot = (slot + 1) % 8) {
            CFileMgr::Write(file, &Buffers[slot], sizeof(tReplayBuffer));
        }

        CFileMgr::CloseFile(file);
    }
    CFileMgr::SetDir("");
}

// 0x460390
void CReplay::PlayReplayFromHD() {
    CFileMgr::SetDirMyDocuments();
    if (auto file = CFileMgr::OpenFile("replay.rep", "rb")) {
        CFileMgr::Read(file, gString, 8u);

        if (strncmp(gString, "GtaSA29", 8u) != 0) {
            DEV_LOG("Invalid replay file data, header unmatch (='{}')", std::string_view{gString, 8u});
        } else {
            auto bufferIdx = 0u;
            for (; bufferIdx < 8u && CFileMgr::Read(file, &Buffers[bufferIdx], sizeof(tReplayBuffer)); bufferIdx++) {
                BufferStatus[bufferIdx] = REPLAYBUFFER_FULL;
            }
            BufferStatus[bufferIdx - 1] = REPLAYBUFFER_IN_USE; // Mark last used buffer as in-use.

            for (auto i = bufferIdx; i < 8; i++) { // Mark unfilled buffer as n/a.
                BufferStatus[i] = REPLAYBUFFER_NOT_AVAILABLE;
            }

            CFileMgr::SetDir(""); // FileMgr dir should be resetted to root before the TriggerPlayback call.
            TriggerPlayback(REPLAY_CAM_MODE_AS_STORED, CVector{}, false);
            bPlayingBackFromFile = true;
            bAllowLookAroundCam = true;
            StreamAllNecessaryCarsAndPeds();
        }
        CFileMgr::CloseFile(file);
    }
    CFileMgr::SetDir("");
}

// 0x45C440
bool CReplay::ShouldStandardCameraBeProcessed() {
    return Mode != MODE_PLAYBACK;
}

// unused
// 0x45C450
int32 CReplay::FindPoolIndexForPed(int32 index) {
    return m_PedPoolConversion[index];
}

// unused
// 0x45C460
int32 CReplay::FindPoolIndexForVehicle(int32 index) {
    return m_VehiclePoolConversion[index];
}

// 0x45CA70
void CReplay::ProcessPedUpdate(CPed* ped, float interpValue, CAddressInReplayBuffer& address) {
    assert(address.Read<eReplayPacket>() == REPLAY_PACKET_PED_UPDATE);
    const auto packet = address.Read<tReplayBlockData>();

    address.m_nOffset += FindSizeOfPacket(REPLAY_PACKET_PED_UPDATE); // count packet read beforehand.
    if (!ped)
        return;

    ped->m_fCurrentRotation = (float)packet.ped.heading / HEADING_COMPRESS_VALUE;
    ped->m_fAimingRotation  = (float)packet.ped.heading / HEADING_COMPRESS_VALUE;

    CMatrix decompressed;
    packet.ped.matrix.DecompressIntoFullMatrix(decompressed);
    decompressed.ScaleAll(interpValue);
    ped->GetMatrix().ScaleAll(1.0f - interpValue);
    ped->GetMatrix() += decompressed;

    if (const auto vehIdx = packet.ped.vehicleIndex) {
        auto& vehicle = ped->m_pVehicle;
        if (vehicle)
            vehicle->CleanUpOldReference(ped->m_pVehicle);
        vehicle = nullptr;

        if (auto poolRef = m_VehiclePoolConversion[vehIdx - 1]; !GetVehiclePool()->IsFreeSlotAtIndex(poolRef)) {
            vehicle = GetVehiclePool()->GetAt(poolRef);
            vehicle->RegisterReference(vehicle);
            ped->bInVehicle = true;
        }
    } else {
        if (auto vehicle = ped->m_pVehicle)
            CEntity::CleanUpOldReference(vehicle);

        ped->m_pVehicle = nullptr;
        ped->bInVehicle = false;
    }
    if (const auto ag = packet.ped.animGroup; ag != ped->m_nAnimGroup) {
        ped->m_nAnimGroup = static_cast<AssocGroupId>(ag);
        if (ped == FindPlayerPed()) {
            ped->AsPlayer()->ReApplyMoveAnims();
        }
    }

    auto v10 = ((uint8)ped->m_nFlags ^ (uint8)(packet.ped.flags << 7)) & 0x80 ^ ped->m_nFlags;
    auto v11 = v10 ^ (v10 ^ ((uint8)packet.ped.flags << 29)) & 0x40000000;
    ped->m_nFlags = ((uint8)packet.ped.flags << 29) ^ (v11 ^ ((uint8)packet.ped.flags << 29)) & 0x7FFFFFFF;
    ped->m_fContactSurfaceBrightness = static_cast<float>(packet.ped.contactSurfaceBrightness) / 100.0f;
    RetrievePedAnimation(ped, packet.ped.animState);

    ped->RemoveWeaponModel();
    if (const auto wm = packet.ped.weaponModel; wm != -1) {
        if (CStreaming::ms_aInfoForModel[wm].IsLoaded()) {
            ped->AddWeaponModel(wm);
        } else {
            CStreaming::RequestModel(static_cast<eModelID>(wm), STREAMING_DEFAULT);
        }
    }

    ped->m_nAreaCode = static_cast<eAreaCodes>(CGame::currArea);
    CWorld::Remove(ped);
    CWorld::Add(ped);
}

// 0x45D060
void CReplay::ProcessReplayCamera() {
    assert(TheCamera.m_pRwCamera);

    auto modelling = TheCamera.GetRwMatrix();
    switch (CameraMode) {
    case REPLAY_CAM_MODE_TOPDOWN:
        TheCamera.GetRight()    = CVector{1.0f, 0.0f,  0.0f};
        TheCamera.GetUp()       = CVector{0.0f, 1.0f,  0.0f};
        TheCamera.GetForward()  = CVector{0.0f, 0.0f, -1.0f};
        TheCamera.GetPosition() = CVector{CameraFocus.x, CameraFocus.y, CameraFocus.z + 15.0f};

        modelling->pos   = CameraFocus;
        modelling->at    = TheCamera.GetForward();
        modelling->up    = TheCamera.GetUp();
        modelling->right = TheCamera.GetRight();
        break;
    case REPLAY_CAM_MODE_FIXED:
        const auto direction = (CameraFocus - CameraFixed).Normalized();
        const auto right = direction.Cross({0.0f, 0.0f, 1.0f}).Normalized();

        TheCamera.GetPosition() = CameraFixed;
        TheCamera.GetForward()  = direction;
        TheCamera.GetUp()       = direction.Cross(right);
        TheCamera.GetRight()    = right;

        modelling->pos   = CameraFocus;
        modelling->at    = TheCamera.GetForward();
        modelling->up    = TheCamera.GetUp();
        modelling->right = TheCamera.GetRight();
        break;
    default:
        break;
    }
    TheCamera.m_vecGameCamPos = TheCamera.GetPosition();
    TheCamera.CalculateDerivedValues(false, true);
    RwMatrixUpdate(modelling);
    RwFrameUpdateObjects(RwCameraGetFrame(TheCamera.m_pRwCamera));
    RwFrameOrthoNormalize(RwCameraGetFrame(TheCamera.m_pRwCamera));
}

// 0x45D760
void CReplay::ProcessLookAroundCam() {
    //return plugin::Call<0x45D760>();
    if (bAllowLookAroundCam) {
        static float& playerCameraDistance = *(float*)0x97FAD4;
        static float& playerCameraDirAngle = *(float*)0x97FADC;
        static float& viewAngle = *(float*)0x97FAD8;

        const auto& pad = CPad::GetPad();
        const auto steer = CVector2D{pad->NewMouseControllerState.X / 200.0f, pad->NewMouseControllerState.Y / 200.0f};
        // steerX2 = steer.x;
        // steerY2 = steer.y;
        // if (v2 | v2)             <-- replays does not care about inverted-y, maybe is it
        // if (steerX2 > 0.01f)         because of these are undefined?
        //     goto LABEL_8
        // if (v6 | v7)
        //     steerY2 = -steerY2;
        // if (steerY2 > 0.01f)
        //     goto LABEL_8
        //
        if (steer.y > 0.01f) {
            // label_8:
            if (!FramesActiveLookAroundCam) {
                const auto& camPos    = TheCamera.GetPosition();
                const auto& playerPos = FindPlayerCoors();
                playerCameraDistance = std::clamp(DistanceBetweenPoints(playerPos, camPos), 3.0f, 15.0f);
                playerCameraDirAngle = std::atan2(camPos.x - playerPos.x, camPos.y - playerPos.y);
            }
            FramesActiveLookAroundCam = 60;
        }

        static bool& byte_97f66d = *(bool*)0x97f66d;
        if (byte_97f66d) {
            FramesActiveLookAroundCam = 0;
        } else if (FramesActiveLookAroundCam) {
            playerCameraDirAngle += steer.x;
            FramesActiveLookAroundCam--;

            if (pad->NewMouseControllerState.lmb && pad->NewMouseControllerState.rmb) {
                playerCameraDistance = std::clamp(playerCameraDistance + 2.0f * steer.y, 3.0f, 15.0f);
            } else {
                viewAngle = std::clamp(viewAngle + steer.y, 0.1f, 1.5f); // probably some kind of cheap clamping between [0, pi/2].
            }

            auto target = CVector{
                    std::sinf(playerCameraDirAngle) * std::cosf(viewAngle) * playerCameraDistance,
                    std::cosf(playerCameraDirAngle) * std::cosf(viewAngle) * playerCameraDistance,
                    std::sinf(viewAngle) * playerCameraDistance
            } + CameraFocus;

            CColPoint colPoint;
            CEntity* outEntity{};
            if (CWorld::ProcessLineOfSight(CameraFocus, target, colPoint, outEntity, true, false, false, false, false, true, true, false)) {
                target = colPoint.m_vecPoint;
                const auto focusCollisionDir = (CameraFocus - colPoint.m_vecPoint).Normalized();
                target.x += focusCollisionDir.x / 4.0f;
                target.y += focusCollisionDir.y / 4.0f;
                target.z += focusCollisionDir.z;
            }

            const auto forward = (CameraFocus - target).Normalized();
            const auto right   = CVector{0.0f, 0.0f, 1.0f}.Cross(forward);
            const auto up      = forward.Cross(right);

            TheCamera.GetForward()  = forward;
            TheCamera.GetUp()       = up;
            TheCamera.GetRight()    = right;
            TheCamera.GetPosition() = target;

            auto modelling = TheCamera.GetRwMatrix();
            modelling->pos   = target;
            modelling->at    = forward;
            modelling->up    = up;
            modelling->right = right;
            TheCamera.CalculateDerivedValues(false, true);
            RwMatrixUpdate(modelling);
            RwFrameUpdateObjects(RwCameraGetFrame(TheCamera.m_pRwCamera));
            RwFrameOrthoNormalize(RwCameraGetFrame(TheCamera.m_pRwCamera));
        }
    }

    RwCameraSetNearClipPlane(Scene.m_pRwCamera, 0.5f);
    if (FramesActiveLookAroundCam) {
        const auto MakeVisible = [](auto* entity) {
            if (entity) {
                entity->m_bIsVisible = true;
            }
        };

        MakeVisible(FindPlayerPed());
        MakeVisible(FindPlayerVehicle());
    }
}

// 0x45C470
bool CReplay::CanWeFindPoolIndexForPed(int32 index) {
    return m_PedPoolConversion[index] >= 0;
}

// 0x45C490
bool CReplay::CanWeFindPoolIndexForVehicle(int32 index) {
    return m_VehiclePoolConversion[index] >= 0;
}

// 0x45F020
void CReplay::StorePlayerInfoVariables() {
    auto& playerInfo = FindPlayerInfo(PED_TYPE_PLAYER1);

    PlayerInfo = playerInfo;
    playerInfo.m_PlayerData.m_pWanted = nullptr;
    playerInfo.m_PlayerData.m_pPedClothesDesc = nullptr;
    playerInfo.m_PlayerData.m_pArrestingCop = nullptr;
    playerInfo.m_PlayerData.m_nMeleeWeaponAnimReferenced = 0;
    playerInfo.m_PlayerData.m_nMeleeWeaponAnimReferencedExtra = 0;
    playerInfo.m_pSkinTexture = nullptr;
}

// 0x45E1F0
void CReplay::RestorePlayerInfoVariables() {
    FindPlayerInfo(PED_TYPE_PLAYER1) = PlayerInfo;
    PlayerInfo.m_PlayerData.m_pWanted = nullptr;
    PlayerInfo.m_PlayerData.m_pPedClothesDesc = nullptr;
    PlayerInfo.m_PlayerData.m_pArrestingCop = nullptr;
    PlayerInfo.m_pSkinTexture = nullptr;
}

// 0x45F180
void CReplay::StoreStuffInMem() {
    pStoredCam = new CCamera;
    memcpy(pStoredCam, &TheCamera, sizeof(CCamera));

    StorePlayerInfoVariables();
    Time1 = CTimer::GetTimeInMS();
    Time2 = CTimer::GetTimeInMSNonClipped();
    Time3 = CTimer::GetPreviousTimeInMS();
    Time4 = CTimer::m_snPPreviousTimeInMilliseconds;
    Time5 = CTimer::m_snPPPreviousTimeInMilliseconds;
    Time6 = CTimer::m_snPPPPreviousTimeInMilliseconds;
    Time7 = CTimer::GetTimeInMSPauseMode();
    Frame = CTimer::GetFrameCounter();
    TimeScale = CTimer::GetTimeScale();
    TimeStep = CTimer::GetTimeStep();
    TimeStepNonClipped = CTimer::GetTimeStepNonClipped();

    ClockHours = CClock::GetGameClockHours();
    ClockMinutes = CClock::GetGameClockMinutes();

    OldWeatherType = CWeather::OldWeatherType;
    NewWeatherType = CWeather::NewWeatherType;
    WeatherInterpolationValue = CWeather::InterpolationValue;

    ms_nNumCivMale_Stored = CPopulation::ms_nNumCivMale;
    ms_nNumCivFemale_Stored = CPopulation::ms_nNumCivFemale;
    ms_nNumCop_Stored = CPopulation::ms_nNumCop;
    ms_nNumEmergency_Stored = CPopulation::ms_nNumEmergency;
    ms_nNumDealers_Stored = CPopulation::ms_nNumDealers;
    ms_nTotalCarPassengerPeds_Stored = CPopulation::ms_nTotalCarPassengerPeds;
    ms_nTotalCivPeds_Stored = CPopulation::ms_nTotalCivPeds;
    ms_nTotalGangPeds_Stored = CPopulation::ms_nTotalGangPeds;
    ms_nTotalPeds_Stored = CPopulation::ms_nTotalPeds;
    ms_nTotalMissionPeds_Stored = CPopulation::ms_nTotalMissionPeds;
    rng::copy(CPopulation::ms_nNumGang, ms_nNumGang_Stored.begin());
}

// 0x45ECD0
void CReplay::RestoreStuffFromMem() {
    for (auto poolIdx = 0; poolIdx < GetPedPool()->GetSize(); poolIdx++) {
        if (auto ped = GetPedPool()->GetAt(poolIdx)) {
            if (ped->bUsedForReplay) {
                if (auto playerData = ped->m_pPlayerData) {
                    playerData->DeAllocateData();
                }
                CWorld::Remove(ped);
                delete ped;
            } else { // if not, restore it
                CWorld::Add(ped);
            }
        }
    }

    for (auto poolIdx = 0; poolIdx < GetVehiclePool()->GetSize(); poolIdx++) {
        if (auto veh = GetVehiclePool()->GetAt(poolIdx)) {
            if (veh->vehicleFlags.bUsedForReplay) {
                CWorld::Remove(veh);
                delete veh;
            } else { // if not, restore it
                CWorld::Add(veh);
            }
        }
    }

    memcpy(&TheCamera, pStoredCam, sizeof(TheCamera));
    delete pStoredCam;
    pStoredCam = nullptr;

    CTimer::SetTimeInMS(Time1);
    CTimer::SetTimeInMSNonClipped(Time2);
    CTimer::SetPreviousTimeInMS(Time3);
    CTimer::m_snPreviousTimeInMilliseconds = Time3;
    CTimer::m_snPPreviousTimeInMilliseconds = Time4;
    CTimer::m_snPPPreviousTimeInMilliseconds = Time5;
    CTimer::m_snPPPPreviousTimeInMilliseconds = Time6;
    CTimer::SetTimeInMSPauseMode(Time7);
    CTimer::SetTimeStep(TimeStep);
    CTimer::SetTimeStepNonClipped(TimeStepNonClipped);
    CTimer::SetTimeScale(TimeScale);
    CTimer::SetFrameCounter(Frame);
    CClock::SetGameClock(ClockHours, ++ClockMinutes, 0);

    RestorePlayerInfoVariables();
    CWeather::OldWeatherType = OldWeatherType;
    CWeather::NewWeatherType = NewWeatherType;
    CWeather::InterpolationValue = WeatherInterpolationValue;

    CGame::currArea = static_cast<int8>(CurrArea);
    CPopulation::ms_nNumCivMale = ms_nNumCivMale_Stored;
    CPopulation::ms_nNumCivFemale = ms_nNumCivFemale_Stored;
    CPopulation::ms_nNumCop = ms_nNumCop_Stored;
    CPopulation::ms_nNumEmergency = ms_nNumEmergency_Stored;
    CPopulation::ms_nTotalCarPassengerPeds = ms_nTotalCarPassengerPeds_Stored;
    CPopulation::ms_nTotalCivPeds = ms_nTotalCivPeds_Stored;
    CPopulation::ms_nTotalGangPeds = ms_nTotalGangPeds_Stored;
    CPopulation::ms_nTotalPeds = ms_nTotalPeds_Stored;
    CPopulation::ms_nTotalMissionPeds = ms_nTotalMissionPeds_Stored;

    // FIX_BUGS? ms_nNumGang not restored
    // rng::copy(ms_nNumGang_Stored, CPopulation::ms_nNumGang.begin());
}

// 0x45F050
void CReplay::FinishPlayback() {
    if (ShouldStandardCameraBeProcessed())
        return;

    RestoreStuffFromMem();
    Mode = MODE_RECORD;

    if (bDoLoadSceneWhenDone) {
        CGame::currLevel = CTheZones::GetLevelFromPosition(LoadScene);
        CCollision::SortOutCollisionAfterLoad();
        CStreaming::LoadScene(LoadScene);
    }
    bDoLoadSceneWhenDone = false;

    if (bPlayingBackFromFile) {
        Init();
        MarkEverythingAsNew();
    }

    TheCamera.SetFadeColour(0, 0, 0);
    TheCamera.Fade(0.0f, eFadeFlag::FADE_IN);
    TheCamera.ProcessFade();
    TheCamera.Fade(1.0f, eFadeFlag::FADE_OUT);

    gFireManager.CreateAllFxSystems();
    AudioEngine.SetEffectsMasterVolume(FrontEndMenuManager.m_nSfxVolume);
    AudioEngine.SetMusicMasterVolume(FrontEndMenuManager.m_nRadioVolume);

    if (auto vehicle = FindPlayerVehicle()) {
        vehicle->m_vehicleAudio.TurnOnRadioForVehicle();
        AudioEngine.RetuneRadio(OldRadioStation);
    }
}

// 0x45E300
void CReplay::RecordThisFrame() {
    plugin::Call<0x45E300>();
}

// 0x45C750
void CReplay::StoreClothesDesc(CPedClothesDesc& desc, tReplayBlockData& packet) {
    packet.type = REPLAY_PACKET_CLOTHES;
    rng::copy(desc.m_anModelKeys, packet.clothes.m_anModelKeys.begin());
    rng::copy(desc.m_anTextureKeys, packet.clothes.m_anTextureKeys.begin());
    packet.clothes.m_fFatStat = (int16)desc.m_fFatStat;
    packet.clothes.m_fMuscleStat = (int16)desc.m_fMuscleStat;
}

// 0x45C7D0, broken
void CReplay::RestoreClothesDesc(CPedClothesDesc& desc, tReplayBlockData& packet) {
    assert(packet.type == REPLAY_PACKET_CLOTHES);
    rng::copy(packet.clothes.m_anModelKeys, desc.m_anModelKeys.begin());
    rng::copy(packet.clothes.m_anTextureKeys, desc.m_anTextureKeys.begin());
    desc.m_fFatStat = (float)packet.clothes.m_fFatStat;
    desc.m_fMuscleStat = (float)packet.clothes.m_fMuscleStat;
}

// 0x45CEA0
CPed* CReplay::DealWithNewPedPacket(tReplayBlockData& pedPacket, bool loadModel, tReplayBlockData& clothesPacket) {
    assert(pedPacket.type == REPLAY_PACKET_PED_HEADER);

    if (GetPedPool()->GetAt(m_PedPoolConversion[pedPacket.playerData.index]))
        return nullptr;

    if (pedPacket.playerData.pedType == PED_TYPE_PLAYER1 && loadModel) {
        CStreaming::RequestModel(pedPacket.playerData.modelId, STREAMING_DEFAULT);
        CStreaming::LoadAllRequestedModels(false);
    }

    if (CStreaming::GetInfo(pedPacket.playerData.modelId).IsLoaded()) {
        CPed* ped = nullptr;
        if (pedPacket.playerData.pedType == PED_TYPE_PLAYER1) {
            assert(clothesPacket.type == REPLAY_PACKET_CLOTHES);

            ped = new (m_PedPoolConversion[pedPacket.playerData.index] << 8) CPlayerPed(PED_TYPE_PLAYER1, true);
            RestoreClothesDesc(*ped->GetClothesDesc(), clothesPacket);
            CClothes::RebuildPlayer(static_cast<CPlayerPed*>(ped), true);
        } else if (!loadModel) {
            ped = new (m_PedPoolConversion[pedPacket.playerData.index] << 8) CCivilianPed((ePedType)pedPacket.playerData.pedType, pedPacket.playerData.modelId);
        } else {
            return nullptr;
        }

        ped->m_nStatus = STATUS_PLAYER_PLAYBACK_FROM_BUFFER;
        ped->bUsedForReplay = true;
        ped->GetMatrix().SetUnity();
        ped->SetCharCreatedBy(PED_GAME_MISSION);
        CWorld::Remove(ped);
        CWorld::Add(ped);
        return ped;
    } else {
        CStreaming::RequestModel(pedPacket.playerData.modelId, STREAMING_DEFAULT);
    }
    return nullptr;
}

// 0x45F380
bool CReplay::PlayBackThisFrameInterpolation(CAddressInReplayBuffer& buffer, float interpolation, uint32* outTimer) {
    return plugin::CallAndReturn<bool, 0x45F380, CAddressInReplayBuffer, float, uint32*>(buffer, interpolation, outTimer);

    CBulletTraces::Init();
    for (auto it = &buffer.m_pBase[buffer.m_nOffset]; it->Read<eReplayPacket>(buffer.m_nOffset) != REPLAY_PACKET_END_OF_FRAME;) {
        auto packet = it->Read<tReplayBlockData>(buffer.m_nOffset);

        switch (packet.type) {
        case REPLAY_PACKET_END:
            if (buffer.GetStatus() == REPLAYBUFFER_IN_USE) {
                FinishPlayback();
                return true;
            }
            buffer.Next();
            break;
        case REPLAY_PACKET_VEHICLE: {
            const auto mi = packet.vehicle.modelId;
            const auto poolIdx = m_VehiclePoolConversion[packet.vehicle.index];

            if (CStreaming::IsModelLoaded(mi)) {
                auto created = [&]() -> CVehicle* {
                    switch (packet.vehicle.vehicleSubType) {
                    case VEHICLE_TYPE_AUTOMOBILE:
                        return new (poolIdx << 8) CAutomobile(mi, MISSION_VEHICLE, true);
                    case VEHICLE_TYPE_MTRUCK:
                        return new (poolIdx << 8) CMonsterTruck(mi, MISSION_VEHICLE);
                    case VEHICLE_TYPE_QUAD:
                        return new (poolIdx << 8) CQuadBike(mi, MISSION_VEHICLE);
                    case VEHICLE_TYPE_BOAT:
                        return new (poolIdx << 8) CBoat(mi, MISSION_VEHICLE);
                    case VEHICLE_TYPE_TRAIN:
                        return new (poolIdx << 8) CTrain(mi, MISSION_VEHICLE);
                    case VEHICLE_TYPE_TRAILER:
                        return new (poolIdx << 8) CTrailer(mi, MISSION_VEHICLE);
                    default:
                        NOTSA_UNREACHABLE("Unknown vehicle subtype ={}", (int)packet.vehicle.vehicleSubType);
                    }
                }();
                created->m_nStatus = STATUS_PLAYER_PLAYBACK_FROM_BUFFER;
                created->vehicleFlags.bUsedForReplay = true;
                packet.vehicle.matrix.DecompressIntoFullMatrix(*created->m_matrix);
                created->m_nPrimaryColor = packet.vehicle.primaryColor;
                created->m_nSecondaryColor = packet.vehicle.secondaryColor;
                if (created->IsSubBoat()) {
                    created->AsBoat()->m_nBoatFlags.bAnchored = false;
                }

                CWorld::Add(created);
            } else {
                CStreaming::RequestModel(mi, STREAMING_DEFAULT);
            }
        }
        }

        if (packet.type != REPLAY_PACKET_END) {
            buffer.m_nOffset += FindSizeOfPacket(packet.type);
        }
    }
}

// 0x460350
bool CReplay::FastForwardToTime(uint32 start) {
    if (!start)
        return true;

    uint32 timer = 0;
    while (!PlayBackThisFrameInterpolation(Playback, 1.0f, &timer)) {
        if (timer >= start) {
            return true;
        }
    }

    return false;
}

// 0x4604A0
void CReplay::PlayBackThisFrame() {
    if (PlayBackThisFrameInterpolation(Playback, 1.0f, nullptr)) {
        AudioEngine.SetEffectsMasterVolume(FrontEndMenuManager.m_nSfxVolume);
        AudioEngine.SetMusicMasterVolume(FrontEndMenuManager.m_nRadioVolume);
    } else {
        ProcessLookAroundCam();
        AudioEngine.SetEffectsMasterVolume(0);
        AudioEngine.SetMusicMasterVolume(0);
    }
}

// 0x45C850
constexpr uint32 CReplay::FindSizeOfPacket(eReplayPacket type) {
    switch (type) {
    case REPLAY_PACKET_END:          // <- actually 1 but we shouldn't call this func with this anyways so it's no problem.
    case REPLAY_PACKET_END_OF_FRAME:
    case REPLAY_PACKET_CLOCK:
    case REPLAY_PACKET_DELETED_VEH:
    case REPLAY_PACKET_DELETED_PED:
        return 4;
    case REPLAY_PACKET_VEHICLE:
    case REPLAY_PACKET_PED_UPDATE:
        return 52;
    case REPLAY_PACKET_BIKE:
    case REPLAY_PACKET_BMX:
    case REPLAY_PACKET_HELI:
        return 56;
    case REPLAY_PACKET_PED_HEADER:
    case REPLAY_PACKET_WEATHER:
    case REPLAY_PACKET_TIMER:
        return 8;
    case REPLAY_PACKET_GENERAL:
        return 88;
    case REPLAY_PACKET_BULLET_TRACES:
        return 28;
    case REPLAY_PACKET_PARTICLE:
        return 20;
    case REPLAY_PACKET_MISC:
        return 16;
    case REPLAY_PACKET_PLANE:
        return 60;
    case REPLAY_PACKET_TRAIN:
        return 76;
    case REPLAY_PACKET_CLOTHES:
        return 120;
    default:
        return 0;
    }
}

// 0x45DE40
bool CReplay::IsThisVehicleUsedInRecording(int32 index) {
    for (auto& buffer : Buffers) {
        for (auto& packet : buffer) {
            switch (packet.type) {
            case REPLAY_PACKET_VEHICLE:
            case REPLAY_PACKET_BIKE:
            case REPLAY_PACKET_BMX:
            case REPLAY_PACKET_HELI:
            case REPLAY_PACKET_PLANE:
            case REPLAY_PACKET_TRAIN:
                if (packet.vehicle.index == index) {
                    return true;
                }
                break;
            case REPLAY_PACKET_PED_UPDATE:
                if (auto pedIdx = packet.ped.vehicleIndex; pedIdx && pedIdx - 1 == index) {
                    return true;
                }
                break;
            default:
                break;
            }
        }
    }
    return false;
}

// 0x45DDE0
bool CReplay::IsThisPedUsedInRecording(int32 index) {
    for (auto& buffer : Buffers) {
        const auto packet = rng::find_if(buffer, [index](auto&& p) {
            return p.type == REPLAY_PACKET_PED_HEADER && p.playerData.index == index;
        });

        if (packet != buffer.end()) {
            return true;
        }
    }
    return false;
}

// 0x45D6C0
void CReplay::FindFirstFocusCoordinate(CVector& outPos) {
    for (auto& buffer : GetAllActiveBuffers()) {
        const auto packet = rng::find_if(buffer, [](auto&& p) { return p.type == REPLAY_PACKET_GENERAL; });
        if (packet != buffer.end()) {
            outPos = packet->camera.firstFocusPosn;
            break;
        }
    }
}

// 0x45D670
uint32 CReplay::NumberFramesAvailableToPlay() {
    auto frames = 0u;
    for (auto& buffer : GetAllActiveBuffers()) {
        for (auto it = buffer.begin(); it != buffer.end();) {
            it = std::find_if(it, buffer.end(), [](auto&& p) { return p.type == REPLAY_PACKET_END_OF_FRAME; });
            if (it != buffer.end())
                frames++;
        }
    }
    return frames;
}

// 0x45D4B0
void CReplay::StreamAllNecessaryCarsAndPeds() {
    for (auto& buffer : GetAllActiveBuffers()) {
        for (auto& packet : buffer) {
            switch (packet.type) {
            case REPLAY_PACKET_VEHICLE:
            case REPLAY_PACKET_BIKE:
                CStreaming::RequestModel(packet.vehicle.modelId, STREAMING_DEFAULT);
                break;
            case REPLAY_PACKET_PED_HEADER:
                CStreaming::RequestModel(packet.playerData.modelId, STREAMING_DEFAULT);
                break;
            default:
                break;
            }
        }
    }
    CStreaming::LoadAllRequestedModels(false);
}

// 0x45D540
CPlayerPed* CReplay::CreatePlayerPed() {
    CPlayerPed* player = nullptr;

    auto i = 0;
    for (auto slot = Playback.GetNextSlot(i); i < NUM_REPLAY_BUFFERS && BufferStatus[slot]; slot = Playback.GetNextSlot(++i)) {
        auto& buffer = Buffers[slot];
        if (buffer.Read<eReplayPacket>(0) == REPLAY_PACKET_END)
            break;

        for (auto& packet : buffer) {
            const auto offset = (size_t)((uint8*)&packet - (uint8*)&buffer);

            switch (packet.type) {
            case REPLAY_PACKET_PED_HEADER:
                if (!player) {
                    // get the next packet
                    auto next = buffer.Read<tReplayBlockData>(offset + FindSizeOfPacket(REPLAY_PACKET_PED_HEADER));
                    assert(next.type == REPLAY_PACKET_CLOTHES);

                    player = static_cast<CPlayerPed*>(DealWithNewPedPacket(packet, true, next));
                }
                break;
            case REPLAY_PACKET_PED_UPDATE:
                if (player && player == GetPedPool()->GetAt(m_PedPoolConversion[packet.ped.index])) {
                    CAddressInReplayBuffer address = {.m_nOffset = offset, .m_pBase = &buffer, .m_bSlot = (uint8)i}; // m_bSlot definition is NOTSA
                    ProcessPedUpdate(player, 1.0f, address);
                    return player;
                }
            }
        }
    }
    return nullptr;
}

// 0x4600F0
void CReplay::TriggerPlayback(eReplayCamMode mode, CVector fixedCamPos, bool loadScene) {
    if (!ShouldStandardCameraBeProcessed())
        return;

    CSpecialFX::ReplayStarted();
    CameraMode = mode;
    Mode = MODE_PLAYBACK;
    CameraFixed = fixedCamPos;

    bPlayingBackFromFile = false;
    bAllowLookAroundCam = true;
    FramesActiveLookAroundCam = 0;

    OldRadioStation = [&]() -> int8 {
        if (FindPlayerVehicle()) {
            AudioEngine.StopRadio(nullptr, false);
            return AERadioTrackManager.GetCurrentRadioStationID();
        }

        return 0;
    }();

    CurrArea = CGame::currArea;

    // TODO: refactor
    auto idx = 7;
    for (auto&& [i, status] : notsa::enumerate(BufferStatus)) {
        if (status == 2) {
            idx = i;
            break;
        }
    }

    // TODO: refactor
    auto slot = (idx + 1) % 8;
    for (auto j = BufferStatus[slot]; j != 2 && j != 1; j = BufferStatus[slot]) {
        slot = (slot + 1) % 8;
    }
    slot %= 8;

    Playback.m_bSlot = slot;
    Playback.m_pBase = &Buffers[slot];
    Playback.m_nOffset = 0u;

    CObject::DeleteAllTempObjectsInArea(CVector{0.0f}, 1'000'000.0f);
    StoreStuffInMem();
    InitialisePoolConversionTables();
    EmptyPedsAndVehiclePools_NoDestructors();
    CSkidmarks::Clear();
    StreamAllNecessaryCarsAndPeds();

    CWorld::Players[0].m_pPed = CreatePlayerPed();

    bDoLoadSceneWhenDone = [&] {
        if (!loadScene) {
            LoadScene = TheCamera.GetPosition();
            CVector point{};
            FindFirstFocusCoordinate(point);
            CGame::currLevel = CTheZones::GetLevelFromPosition(&point);
            CCollision::SortOutCollisionAfterLoad();
            CStreaming::LoadScene(&point);

            return true;
        }
        return false;
    }();

    CWeaponEffects::ClearCrossHairs();
    CExplosion::ClearAllExplosions();
    CPlaneBanners::Init();
    gFireManager.DestroyAllFxSystems();
    TheCamera.Restore();
    CDraw::SetFOV(70.0f);
    TheCamera.SetFadeColour(0, 0, 0);
    TheCamera.Fade(0.0f, eFadeFlag::FADE_IN);
    TheCamera.ProcessFade();
    TheCamera.Fade(1.5f, eFadeFlag::FADE_OUT);
}

// tReplayBlockData checks
#define CHECK_SIZE(_struct, _enum) static_assert(sizeof(tReplayBlockData::_struct) + sizeof(eReplayPacket) == CReplay::FindSizeOfPacket(REPLAY_PACKET_##_enum))
CHECK_SIZE(vehicle,        VEHICLE);
CHECK_SIZE(bike,           BIKE);
CHECK_SIZE(playerData,     PED_HEADER);
CHECK_SIZE(ped,            PED_UPDATE);
CHECK_SIZE(camera,         GENERAL);
CHECK_SIZE(dayTime,        CLOCK);
CHECK_SIZE(weather,        WEATHER);
CHECK_SIZE(timer,          TIMER);
CHECK_SIZE(bulletTraces,   BULLET_TRACES);
CHECK_SIZE(particle,       PARTICLE);
CHECK_SIZE(misc,           MISC);
CHECK_SIZE(deletedVehicle, DELETED_VEH);
CHECK_SIZE(deletedPed,     DELETED_PED);
CHECK_SIZE(bmx,            BMX);
CHECK_SIZE(heli,           HELI);
CHECK_SIZE(plane,          PLANE);
CHECK_SIZE(train,          TRAIN);
CHECK_SIZE(clothes,        CLOTHES);
#undef CHECK_SIZE
