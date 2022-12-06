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

void CReplay::InjectHooks() {
    RH_ScopedClass(CReplay);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x45E220);
    RH_ScopedInstall(Update, 0x460500);
    RH_ScopedInstall(DisableReplays, 0x45B150);
    RH_ScopedInstall(EnableReplays, 0x45B160);
    RH_ScopedInstall(StorePedAnimation, 0x45B170);
    RH_ScopedInstall(StorePedUpdate, 0x45C940);
    RH_ScopedInstall(RetrievePedAnimation, 0x45B4D0);
    RH_ScopedInstall(ProcessReplayCamera, 0x45D060);
    RH_ScopedInstall(Display, 0x45C210);
    RH_ScopedInstall(MarkEverythingAsNew, 0x45D430);
    RH_ScopedInstall(EmptyReplayBuffer, 0x45EC90);
    RH_ScopedInstall(EmptyPedsAndVehiclePools_NoDestructors, 0x45D390);
    RH_ScopedInstall(GoToNextBlock, 0x45E2A0);
    RH_ScopedInstall(RecordVehicleDeleted, 0x45EBB0);
    RH_ScopedInstall(RecordPedDeleted, 0x45EC20);
    RH_ScopedInstall(SaveReplayToHD, 0x45C340);
    RH_ScopedInstall(PlayReplayFromHD, 0x460390);
    RH_ScopedInstall(ShouldStandardCameraBeProcessed, 0x45C440);
    RH_ScopedInstall(ProcessLookAroundCam, 0x45D760);
    RH_ScopedInstall(FindPoolIndexForPed, 0x45C450);
    RH_ScopedInstall(FindPoolIndexForVehicle, 0x45C460);
    RH_ScopedInstall(ProcessPedUpdate, 0x45CA70);
    RH_ScopedInstall(CanWeFindPoolIndexForPed, 0x45C470);
    RH_ScopedInstall(CanWeFindPoolIndexForVehicle, 0x45C490);
    RH_ScopedInstall(StorePlayerInfoVariables, 0x45F020);
    RH_ScopedInstall(RestorePlayerInfoVariables, 0x45E1F0);
    RH_ScopedInstall(StoreStuffInMem, 0x45F180);
    RH_ScopedInstall(RestoreStuffFromMem, 0x45ECD0);
    RH_ScopedInstall(FinishPlayback, 0x45F050);
    RH_ScopedInstall(RecordThisFrame, 0x45E300);
    RH_ScopedInstall(StoreClothesDesc, 0x45C750);
    RH_ScopedInstall(RestoreClothesDesc, 0x45C7D0);
    RH_ScopedInstall(DealWithNewPedPacket, 0x45CEA0);
    RH_ScopedInstall(PlayBackThisFrameInterpolation, 0x45F380, { .reversed = true });
    RH_ScopedInstall(FastForwardToTime, 0x460350);
    RH_ScopedInstall(PlayBackThisFrame, 0x4604A0);
    RH_ScopedInstall(FindSizeOfPacket, 0x45C850);
    RH_ScopedInstall(IsThisVehicleUsedInRecording, 0x45DE40);
    RH_ScopedInstall(IsThisPedUsedInRecording, 0x45DDE0);
    RH_ScopedInstall(InitialiseVehiclePoolConversionTable, 0x45EFA0);
    RH_ScopedInstall(InitialisePedPoolConversionTable, 0x45EF20);
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
        .poolRef                  = index,
        .heading                  = (int8)(ped->m_fCurrentRotation * HEADING_COMPRESS_VALUE),
        .vehicleIndex             = (uint8)vehicleIdx,
        .animState                = animState,
        .matrix                   = CCompressedMatrixNotAligned::Compress(ped->GetMatrix()),
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

    // NOTSA: FPS-independent 'REPLAY' text counter.
    static uint32 s_ReplayTextCounter = CTimer::GetTimeInMS();
    static bool s_ShowReplayText = true;
    if (CTimer::GetTimeInMS() - s_ReplayTextCounter >= 1000) {
        s_ReplayTextCounter = CTimer::GetTimeInMS();
        s_ShowReplayText = !s_ShowReplayText;
    }

    if (!s_ShowReplayText)
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

    Record.Write({.type = REPLAY_PACKET_DELETED_VEH, .deletedVehicle = {.poolRef = (int16)GetVehiclePool()->GetIndex(vehicle)}}, true);
    Record.Write({REPLAY_PACKET_END});
}

// 0x45EC20
void CReplay::RecordPedDeleted(CPed* ped) {
    if (Mode != MODE_RECORD)
        return;

    if (Record.m_nOffset + FindSizeOfPacket(REPLAY_PACKET_DELETED_PED) > 99'984) {
        GoToNextBlock();
    }

    Record.Write({.type = REPLAY_PACKET_DELETED_PED, .deletedPed = {.poolRef = (int16)GetPedPool()->GetIndex(ped)}}, true);
    Record.Write({REPLAY_PACKET_END});
}

// 0x45EFA0
void CReplay::InitialiseVehiclePoolConversionTable() {
    rng::fill(m_VehiclePoolConversion, -1);
    auto convIdx = 0u;
    for (auto poolIdx = 0; poolIdx < GetVehiclePool()->GetSize(); poolIdx++) {
        if (GetVehiclePool()->GetAt(poolIdx))
            continue;

        if (!IsThisVehicleUsedInRecording(convIdx)) {
            while (++convIdx != std::size(m_VehiclePoolConversion) && !IsThisVehicleUsedInRecording(convIdx))
                ;

            if (convIdx >= std::size(m_VehiclePoolConversion))
                break;
        }

        m_VehiclePoolConversion[convIdx++] = poolIdx;
    }
}

// 0x45EF20
void CReplay::InitialisePedPoolConversionTable() {
    rng::fill(m_PedPoolConversion, -1);
    auto convIdx = 0u;
    for (auto poolIdx = 0; poolIdx < GetPedPool()->GetSize(); poolIdx++) {
        if (GetPedPool()->GetAt(poolIdx))
            continue;

        if (!IsThisPedUsedInRecording(convIdx)) {
            while (++convIdx != std::size(m_PedPoolConversion) && !IsThisPedUsedInRecording(convIdx))
                ;

            if (convIdx >= std::size(m_PedPoolConversion))
                break;
        }

        m_PedPoolConversion[convIdx++] = poolIdx;
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
            if (status == REPLAYBUFFER_IN_USE) {
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

// inlined
// 0x45C450
int32 CReplay::FindPoolIndexForPed(int32 index) {
    return m_PedPoolConversion[index];
}

// inlined
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

    auto decompressed = CCompressedMatrixNotAligned::Decompress(packet.ped.matrix);
    decompressed.ScaleAll(interpValue);
    ped->GetMatrix().ScaleAll(1.0f - interpValue);
    ped->GetMatrix() += decompressed;

    if (const auto vehIdx = packet.ped.vehicleIndex) {
        auto& vehicle = ped->m_pVehicle;
        if (vehicle)
            vehicle->CleanUpOldReference(ped->m_pVehicle);
        vehicle = nullptr;

        if (auto poolRef = FindPoolIndexForVehicle(vehIdx - 1); !GetVehiclePool()->IsFreeSlotAtIndex(poolRef)) {
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
    return FindPoolIndexForPed(index) >= 0;
}

// 0x45C490
bool CReplay::CanWeFindPoolIndexForVehicle(int32 index) {
    return FindPoolIndexForVehicle(index) >= 0;
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
    // Calculate the frame size beforehand.
    auto framePacketSize = 116u;
    for (auto i = 0; i < GetVehiclePool()->GetSize(); i++) {
        if (auto vehicle = GetVehiclePool()->GetAt(i); vehicle && vehicle->m_pRwObject) {
            switch (vehicle->m_nVehicleSubType) {
            case VEHICLE_TYPE_AUTOMOBILE:
            case VEHICLE_TYPE_MTRUCK:
            case VEHICLE_TYPE_QUAD:
            case VEHICLE_TYPE_BOAT:
            case VEHICLE_TYPE_TRAILER:
                framePacketSize += FindSizeOfPacket(REPLAY_PACKET_VEHICLE);
                break;
            case VEHICLE_TYPE_HELI:
            case VEHICLE_TYPE_BIKE:
            case VEHICLE_TYPE_BMX:
                framePacketSize += 56; // REPLAY_PACKET_BIKE/BMX/HELI
                break;
            case VEHICLE_TYPE_PLANE:
                framePacketSize += FindSizeOfPacket(REPLAY_PACKET_PLANE);
                break;
            case VEHICLE_TYPE_TRAIN:
                framePacketSize += FindSizeOfPacket(REPLAY_PACKET_TRAIN);
                break;
            default:
                break;
            }
        }
    }

    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        if (auto ped = GetPedPool()->GetAt(i); ped && ped->m_pRwObject) {
            if (!ped->bHasAlreadyBeenRecorded) {
                // New ped!
                framePacketSize += FindSizeOfPacket(REPLAY_PACKET_PED_HEADER);
                if (ped->IsPlayer()) {
                    framePacketSize += FindSizeOfPacket(REPLAY_PACKET_CLOTHES);
                }
            }
            framePacketSize += FindSizeOfPacket(REPLAY_PACKET_PED_UPDATE);
        }
    }

    for (auto& trace : CBulletTraces::aTraces) {
        if (trace.m_bExists) {
            framePacketSize += FindSizeOfPacket(REPLAY_PACKET_BULLET_TRACES);
        }
    }

    if (Record.m_nOffset + framePacketSize + 20 > 99'984) {
        // writing the frame will overflow the current buffer, switch to next.
        GoToNextBlock();
    }

    CMatrix cameraMatrix = TheCamera.GetMatrix();
    auto cameraPacket = tReplayBlockData{.type = REPLAY_PACKET_GENERAL, .camera = {
        .isUsingRemoteVehicle = FindPlayerInfo().m_pRemoteVehicle != nullptr,
        .matrix               = 0 /* to be filled */,
        .firstFocusPosn       = FindPlayerCoors()
    }};
    memcpy(cameraPacket.camera.matrix, &cameraMatrix, sizeof(CMatrix));
    Record.Write(cameraPacket, true);

    Record.Write({.type = REPLAY_PACKET_CLOCK, .clock = {
        .currentHour = CClock::GetGameClockHours(), .currentMinute = CClock::GetGameClockMinutes()
    }}, true);

    Record.Write({.type = REPLAY_PACKET_WEATHER, .weather = {
        .oldWeather  = (uint8)CWeather::OldWeatherType,
        .newWeather  = (uint8)CWeather::NewWeatherType,
        .interpValue = CWeather::InterpolationValue
    }}, true);

    Record.Write({.type = REPLAY_PACKET_TIMER, .timer = {.timeInMS = CTimer::GetTimeInMS()}}, true);

    for (auto i = 0; i < GetVehiclePool()->GetSize(); i++) {
        if (auto vehicle = GetVehiclePool()->GetAt(i); vehicle && vehicle->m_pRwObject) {
            switch (vehicle->m_nVehicleSubType) {
            case VEHICLE_TYPE_AUTOMOBILE:
            case VEHICLE_TYPE_MTRUCK:
            case VEHICLE_TYPE_QUAD:
            case VEHICLE_TYPE_BOAT:
            case VEHICLE_TYPE_TRAILER:
                Record.Write(tReplayBlockData::MakeVehicleUpdateData(vehicle, i), true);
                break;
            case VEHICLE_TYPE_HELI: {
                auto packet = tReplayBlockData::MakeVehicleUpdateData(vehicle, i);
                packet.type = REPLAY_PACKET_HELI;
                packet.heli.rotorSpeed = vehicle->AsHeli()->m_fHeliRotorSpeed;
                Record.Write(packet, true);
                break;
            }
            case VEHICLE_TYPE_PLANE: {
                auto packet = tReplayBlockData::MakeVehicleUpdateData(vehicle, i);
                packet.type = REPLAY_PACKET_PLANE;
                packet.plane.field_9C8 = vehicle->AsPlane()->field_9C8;
                packet.plane.propSpeed = vehicle->AsPlane()->m_fPropSpeed;
                Record.Write(packet, true);
                break;
            }
            case VEHICLE_TYPE_TRAIN:
                Record.Write(tReplayBlockData::MakeTrainUpdateData(vehicle->AsTrain(), i), true);
                break;

            case VEHICLE_TYPE_BIKE:
                Record.Write(tReplayBlockData::MakeBikeUpdateData(vehicle->AsBike(), i), true);
                break;

            case VEHICLE_TYPE_BMX:
                Record.Write(tReplayBlockData::MakeBmxUpdateData(vehicle->AsBmx(), i), true);
                break;
            default:
                break;
            }
        }
    }

    for (auto i = 0; i < GetPedPool()->GetSize(); i++) {
        if (auto ped = GetPedPool()->GetAt(i); ped && ped->m_pRwObject) {
            if (!ped->bHasAlreadyBeenRecorded) {
                // New ped!
                const auto mi = ped->m_nModelIndex;

                Record.Write({.type = REPLAY_PACKET_PED_HEADER, .pedHeader = {
                    .poolRef = (uint8)i,
                    .modelId = (int16)((mi >= 290 && mi <= 300) ? 7 : mi),
                    .pedType = (uint8)ped->m_nPedType
                }}, true);

                if (ped->IsPlayer()) {
                    tReplayBlockData clothesData{};
                    StoreClothesDesc(*ped->AsPlayer()->GetClothesDesc(), clothesData);
                    Record.Write(clothesData, true);
                }

                ped->bHasAlreadyBeenRecorded = true;
            }
            StorePedUpdate(ped, i);
        }
    }

    for (auto&& [i, trace] : notsa::enumerate(CBulletTraces::aTraces)) {
        if (!trace.m_bExists)
            continue;

        tReplayBlockData packet{};
        packet.type = REPLAY_PACKET_BULLET_TRACES;
        packet.bulletTrace.index = i;
        packet.bulletTrace.start = trace.m_vecStart;
        packet.bulletTrace.end = trace.m_vecEnd;
    }

    Record.Write({.type = REPLAY_PACKET_MISC, .misc = {
        .camShakeStart = TheCamera.m_nCamShakeStart,
        .camShakeForce = TheCamera.m_fCamShakeForce,
        .currArea      = (uint8)CGame::currArea,
        .camConfig     = {
            .bVideoCam = CSpecialFX::bVideoCam,
            .bLiftCam = CSpecialFX::bLiftCam
        }
    }}, true);

    Record.Write({.type = REPLAY_PACKET_END_OF_FRAME}, true);
    Record.Write({.type = REPLAY_PACKET_END});
}

// 0x45C750
void CReplay::StoreClothesDesc(const CPedClothesDesc& desc, tReplayBlockData& packet) {
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
CPed* CReplay::DealWithNewPedPacket(tReplayBlockData& pedPacket, bool loadModel, tReplayBlockData* clothesPacket) {
    assert(pedPacket.type == REPLAY_PACKET_PED_HEADER);

    if (GetPedPool()->GetAt(FindPoolIndexForPed(pedPacket.pedHeader.poolRef)))
        return nullptr;

    if (pedPacket.pedHeader.pedType == PED_TYPE_PLAYER1 && loadModel) {
        CStreaming::RequestModel(pedPacket.pedHeader.modelId, STREAMING_DEFAULT);
        CStreaming::LoadAllRequestedModels(false);
    }

    if (CStreaming::GetInfo(pedPacket.pedHeader.modelId).IsLoaded()) {
        CPed* ped = nullptr;
        if (pedPacket.pedHeader.pedType == PED_TYPE_PLAYER1) {
            assert(clothesPacket->type == REPLAY_PACKET_CLOTHES);

            ped = new (FindPoolIndexForPed(pedPacket.pedHeader.poolRef) << 8) CPlayerPed(PED_TYPE_PLAYER1, true);
            RestoreClothesDesc(*ped->GetClothesDesc(), *clothesPacket);
            CClothes::RebuildPlayer(static_cast<CPlayerPed*>(ped), true);
        } else if (!loadModel) {
            ped = new (FindPoolIndexForPed(pedPacket.pedHeader.poolRef) << 8) CCivilianPed((ePedType)pedPacket.pedHeader.pedType, pedPacket.pedHeader.modelId);
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
        CStreaming::RequestModel(pedPacket.pedHeader.modelId, STREAMING_DEFAULT);
    }
    return nullptr;
}

// Returns true if the playback has ended.
// 0x45F380
bool CReplay::PlayBackThisFrameInterpolation(CAddressInReplayBuffer& buffer, float interpolation, uint32* outTimer) {
    const auto SetupVehicle = [](tReplayBlockData& packet, CVehicle* vehicle) {
        vehicle->m_nStatus = STATUS_PLAYER_PLAYBACK_FROM_BUFFER;
        vehicle->vehicleFlags.bUsedForReplay = true;
        vehicle->m_bUsesCollision = false;
        packet.vehicle.matrix.DecompressIntoFullMatrix(vehicle->GetMatrix());
        vehicle->m_nPrimaryColor = packet.vehicle.primaryColor;
        vehicle->m_nSecondaryColor = packet.vehicle.secondaryColor;
        if (vehicle->IsSubBoat()) {
            vehicle->AsBoat()->m_nBoatFlags.bAnchored = false;
        }

        CWorld::Add(vehicle);
    };

    CBulletTraces::Init();

    while (buffer.Read<eReplayPacket>() != REPLAY_PACKET_END_OF_FRAME) {
        auto packet = buffer.Read<tReplayBlockData>();

        switch (packet.type) {
        case REPLAY_PACKET_END:
            if (buffer.GetStatus() == REPLAYBUFFER_IN_USE) {
                FinishPlayback();
                return true;
            }
            buffer.Next();
            continue; // We do not increment when we read end packet.
        case REPLAY_PACKET_VEHICLE: {
            const auto mi = packet.vehicle.modelId;
            const auto poolIdx = FindPoolIndexForVehicle(packet.vehicle.poolRef);

            if (!GetVehiclePool()->GetAt(poolIdx)) {
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

                    SetupVehicle(packet, created);
                } else {
                    CStreaming::RequestModel(mi, STREAMING_DEFAULT);
                }
            } else {
                tReplayBlockData::ExtractVehicleUpdateData(packet, GetVehiclePool()->GetAt(poolIdx), interpolation);
            }
            break;
        }
        case REPLAY_PACKET_BIKE: {
            const auto mi = packet.vehicle.modelId;
            const auto poolIdx = FindPoolIndexForVehicle(packet.vehicle.poolRef);

            if (!GetVehiclePool()->GetAt(poolIdx)) {
                if (CStreaming::IsModelLoaded(mi)) {
                    SetupVehicle(packet, new (poolIdx << 8) CBike(mi, MISSION_VEHICLE));
                } else {
                    CStreaming::RequestModel(mi, STREAMING_DEFAULT);
                }
            } else {
                tReplayBlockData::ExtractBikeUpdateData(packet, GetVehiclePool()->GetAt(poolIdx)->AsBike(), interpolation);
            }
            break;
        }
        case REPLAY_PACKET_PED_HEADER:
            DealWithNewPedPacket(packet, false, nullptr);
            break;
        case REPLAY_PACKET_PED_UPDATE: {
            const auto poolIdx = FindPoolIndexForPed(packet.ped.poolRef);
            ProcessPedUpdate(GetPedPool()->GetAt(poolIdx), interpolation, buffer);
            continue; // ProcessPedUpdate increments the offset by itself already.
        }
        case REPLAY_PACKET_GENERAL: {
            TheCamera.GetMatrix().ScaleAll(1.0f - interpolation);
            CMatrix packetMatrix(*(const CMatrix*)&packet.camera.matrix);
            packetMatrix.ScaleAll(interpolation);
            TheCamera.GetMatrix() += packetMatrix;
            auto modelling = TheCamera.GetRwMatrix();
            modelling->pos = TheCamera.GetMatrix().GetPosition();
            modelling->at = TheCamera.GetMatrix().GetForward();
            modelling->up = TheCamera.GetMatrix().GetUp();
            modelling->right = TheCamera.GetMatrix().GetRight();

            CameraFocus = packet.camera.firstFocusPosn * interpolation + CameraFocus * (1.0f - interpolation);
            bIsUsingRemoteCar = packet.camera.isUsingRemoteVehicle;
            break;
        }
        case REPLAY_PACKET_CLOCK:
            CClock::SetGameClock(packet.clock.currentHour, packet.clock.currentMinute, 0);
            break;
        case REPLAY_PACKET_WEATHER:
            CWeather::OldWeatherType = (eWeatherType)packet.weather.oldWeather;
            CWeather::NewWeatherType = (eWeatherType)packet.weather.newWeather;
            CWeather::InterpolationValue = packet.weather.interpValue;
            break;
        case REPLAY_PACKET_END_OF_FRAME:
            break;
        case REPLAY_PACKET_TIMER:
            if (outTimer) {
                *outTimer = packet.timer.timeInMS;
            }

            CTimer::SetTimeInMS(packet.timer.timeInMS);
            break;
        case REPLAY_PACKET_BULLET_TRACES: {
            auto& trace = CBulletTraces::aTraces[packet.bulletTrace.index];
            trace.m_bExists = true;
            trace.m_vecStart = packet.bulletTrace.start;
            trace.m_vecEnd = packet.bulletTrace.end;
            break;
        }
        case REPLAY_PACKET_MISC:
            TheCamera.m_nCamShakeStart = packet.misc.camShakeStart;
            TheCamera.m_fCamShakeForce = packet.misc.camShakeForce;
            CSpecialFX::bVideoCam = packet.misc.camConfig.bVideoCam;
            CSpecialFX::bLiftCam = packet.misc.camConfig.bLiftCam;
            CGame::currArea = packet.misc.currArea;
            break;
        case REPLAY_PACKET_DELETED_VEH: {
            const auto idx = FindPoolIndexForVehicle(packet.deletedVehicle.poolRef);
            if (idx >= 0 && !GetVehiclePool()->IsFreeSlotAtIndex(idx)) {
                if (auto vehicle = GetVehiclePool()->GetAt(idx)) {
                    CWorld::Remove(vehicle);
                    delete vehicle;
                }
            }
            break;
        }
        case REPLAY_PACKET_DELETED_PED: {
            const auto idx = FindPoolIndexForPed(packet.deletedPed.poolRef);
            if (idx >= 0 && !GetPedPool()->IsFreeSlotAtIndex(idx)) {
                if (auto ped = GetPedPool()->GetAt(idx)) {
                    CWorld::Remove(ped);
                    delete ped;
                }
            }
            break;
        }
        case REPLAY_PACKET_BMX: {
            const auto mi = packet.vehicle.modelId;
            const auto poolIdx = FindPoolIndexForVehicle(packet.vehicle.poolRef);

            if (!GetVehiclePool()->GetAt(poolIdx)) {
                if (CStreaming::IsModelLoaded(mi)) {
                    SetupVehicle(packet, new (poolIdx << 8) CBmx(mi, MISSION_VEHICLE));
                } else {
                    CStreaming::RequestModel(mi, STREAMING_DEFAULT);
                }
            } else {
                // Originally BMX has an exclusive extractor for itself but it's exactly the
                // same with bike extractor, so it's fine to use bike one here.
                tReplayBlockData::ExtractBikeUpdateData(packet, GetVehiclePool()->GetAt(poolIdx)->AsBike(), interpolation);
            }
            break;
        }
        case REPLAY_PACKET_HELI: {
            const auto mi = packet.vehicle.modelId;
            const auto poolIdx = FindPoolIndexForVehicle(packet.vehicle.poolRef);

            if (!GetVehiclePool()->GetAt(poolIdx)) {
                if (CStreaming::IsModelLoaded(mi)) {
                    SetupVehicle(packet, new (poolIdx << 8) CHeli(mi, MISSION_VEHICLE));
                } else {
                    CStreaming::RequestModel(mi, STREAMING_DEFAULT);
                }
            } else {
                auto vehicle = GetVehiclePool()->GetAt(poolIdx);
                tReplayBlockData::ExtractVehicleUpdateData(packet, vehicle, interpolation);
                vehicle->AsHeli()->m_fHeliRotorSpeed = packet.heli.rotorSpeed;
            }
            break;
        }
        case REPLAY_PACKET_PLANE: {
            const auto mi = packet.vehicle.modelId;
            const auto poolIdx = FindPoolIndexForVehicle(packet.vehicle.poolRef);

            if (!GetVehiclePool()->GetAt(poolIdx)) {
                if (CStreaming::IsModelLoaded(mi)) {
                    SetupVehicle(packet, new (poolIdx << 8) CPlane(mi, MISSION_VEHICLE));
                } else {
                    CStreaming::RequestModel(mi, STREAMING_DEFAULT);
                }
            } else {
                auto vehicle = GetVehiclePool()->GetAt(poolIdx);
                tReplayBlockData::ExtractVehicleUpdateData(packet, vehicle, interpolation);
                vehicle->AsPlane()->field_9C8 = packet.plane.field_9C8;
                vehicle->AsPlane()->m_fPropSpeed = packet.plane.propSpeed;
            }
            break;
        }
        case REPLAY_PACKET_TRAIN: {
            const auto mi = packet.vehicle.modelId;
            const auto poolIdx = FindPoolIndexForVehicle(packet.vehicle.poolRef);

            if (!GetVehiclePool()->GetAt(poolIdx)) {
                if (CStreaming::IsModelLoaded(mi)) {
                    SetupVehicle(packet, new (poolIdx << 8) CTrain(mi, MISSION_VEHICLE));
                } else {
                    CStreaming::RequestModel(mi, STREAMING_DEFAULT);
                }
            } else {
                tReplayBlockData::ExtractTrainUpdateData(packet, GetVehiclePool()->GetAt(poolIdx)->AsTrain(), interpolation);
            }
            break;
        }
        case REPLAY_PACKET_CLOTHES:
            break;
        default:
            NOTSA_UNREACHABLE("Invalid packet read (type ID={})", (int32)packet.type);
        }

        buffer.m_nOffset += FindSizeOfPacket(packet.type);
    }
    buffer.m_nOffset += 4;
    ProcessReplayCamera();

    return false;
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
                if (packet.vehicle.poolRef == index) {
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
            return p.type == REPLAY_PACKET_PED_HEADER && p.pedHeader.poolRef == index;
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
                CStreaming::RequestModel(packet.pedHeader.modelId, STREAMING_DEFAULT);
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

                    player = static_cast<CPlayerPed*>(DealWithNewPedPacket(packet, true, &next));
                }
                break;
            case REPLAY_PACKET_PED_UPDATE:
                if (player && player == GetPedPool()->GetAt(FindPoolIndexForPed(packet.ped.poolRef))) {
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

    constexpr auto s = sizeof(tReplayBlockData::misc);
}

tReplayBlockData tReplayBlockData::MakeVehicleUpdateData(CVehicle* vehicle, int32 poolIdx) {
    tReplayBlockData ret{};
    ret.type = REPLAY_PACKET_VEHICLE;
    ret.vehicle.poolRef  = (uint8)poolIdx;
    ret.vehicle.health   = (uint8)(std::min(vehicle->m_fHealth, 1000.0f) / 4.0f);
    ret.vehicle.gasPedal = (uint8)(vehicle->m_fGasPedal * 100.0f);
    ret.vehicle.matrix   = CCompressedMatrixNotAligned::Compress(vehicle->GetMatrix());
    ret.vehicle.modelId  = vehicle->m_nModelIndex;
    ret.vehicle.panels   = (vehicle->IsAutomobile()) ? vehicle->AsAutomobile()->m_damageManager.m_nPanelsStatus : 0;
    ret.vehicle.vecMoveSpeed = {
        (int8)(std::clamp(vehicle->GetMoveSpeed().x, -4.0f, 4.0f) * 8000.0f),
        (int8)(std::clamp(vehicle->GetMoveSpeed().y, -4.0f, 4.0f) * 8000.0f),
        (int8)(std::clamp(vehicle->GetMoveSpeed().z, -4.0f, 4.0f) * 8000.0f)
    };
    ret.vehicle.primaryColor   = vehicle->m_nPrimaryColor;
    ret.vehicle.secondaryColor = vehicle->m_nSecondaryColor;
    ret.vehicle.physicalFlags  = (uint8)vehicle->m_nPhysicalFlags;

    // todo refactor
    auto v9 = (ret.vehicle.physicalFlags ^ (2 * ((uint32)vehicle->m_nFlags >> 7))) & 2 ^ ret.vehicle.physicalFlags;
    auto v10 = v9 ^ (v9 ^ (uint8)(4 * ((uint32)vehicle->m_nFlags >> 30))) & 4;
    ret.vehicle.physicalFlags = v10 ^ (v10 ^ (8 * (vehicle->m_nFlags < 0))) & 8;

    if (vehicle == FindPlayerVehicle() && gbFirstPersonRunThisFrame) {
        ret.vehicle.physicalFlags &= ~2u;
    }

    ret.vehicle.steerAngle_or_doomVerticalRot = (uint8)[&] {
        if (vehicle->m_nModelIndex == MODEL_RHINO) {
            return vehicle->AsAutomobile()->m_fDoomVerticalRotation * HEADING_COMPRESS_VALUE;
        } else {
            return vehicle->m_fSteerAngle * 50.0f;
        }
    }();

    if (vehicle->IsAutomobile()) {
        auto automobile = vehicle->AsAutomobile();

        for (auto i = 0; i < 4; i++) { // for each wheel
            ret.vehicle.wheelsSuspensionCompression[i] = (uint8)(automobile->m_fWheelsSuspensionCompression[i] * 50.0f);
            ret.vehicle.wheelRotation[i] = (uint8)(automobile->m_wheelRotation[i] * HEADING_COMPRESS_VALUE);
        }
        ret.vehicle.angleDoorLF = (uint8)(automobile->m_doors[DOOR_LEFT_FRONT].m_fAngle * 20.222929f);
        ret.vehicle.angleDoorRF = (uint8)(automobile->m_doors[DOOR_RIGHT_FRONT].m_fAngle * 20.222929f);

        ret.vehicle.doorStatus = 0u;
        for (auto&& [i, status] : notsa::enumerate(automobile->m_damageManager.GetAllDoorsStatus())) {
            if (status == eDoorState::DOOR_SLAM_SHUT) {
                ret.vehicle.doorStatus |= (uint8)std::pow(2, i);
            }
        }
    }
    ret.vehicle.physicalFlags ^= (ret.vehicle.physicalFlags ^ (vehicle->m_nPhysicalFlags >> 29)) & 1;
    ret.vehicle.vehicleSubType = vehicle->m_nVehicleSubType;
    return ret;
}

tReplayBlockData tReplayBlockData::MakeTrainUpdateData(CTrain* train, int32 poolIdx) {
    tReplayBlockData ret = MakeVehicleUpdateData(train->AsVehicle(), poolIdx);
    ret.type = REPLAY_PACKET_TRAIN;
    ret.train.trainSpeed = train->m_fTrainSpeed;
    ret.train.currentRailDistance = train->m_fCurrentRailDistance;
    ret.train.length = train->m_fLength;
    ret.train.trackId = train->m_nTrackId;
    ret.train.prevCarriageRef = ret.train.nextCarriageRef = 0;

    if (auto carriage = train->m_pPrevCarriage) {
        ret.train.prevCarriageRef = GetVehiclePool()->GetIndex(carriage->AsVehicle()) + 1;
    }

    if (auto carriage = train->m_pNextCarriage) {
        ret.train.nextCarriageRef = GetVehiclePool()->GetIndex(carriage->AsVehicle()) + 1;
    }
    return ret;
}

tReplayBlockData tReplayBlockData::MakeBikeUpdateData(CBike* bike, int32 poolIdx) {
    tReplayBlockData ret = MakeVehicleUpdateData(bike->AsVehicle(), poolIdx);
    ret.type = REPLAY_PACKET_BIKE;
    ret.bike.animLean = (uint8)(bike->GetRideAnimData()->m_fAnimLean * 50.0f);
    ret.bike.steerAngle = (uint8)(bike->GetRideAnimData()->m_fSteerAngle * 50.0f);
    return ret;
}

tReplayBlockData tReplayBlockData::MakeBmxUpdateData(CBmx* bmx, int32 poolIdx) {
    // Same as Bike, but the type is different.
    tReplayBlockData ret = MakeBikeUpdateData(bmx->AsBike(), poolIdx);
    ret.type = REPLAY_PACKET_BMX;
    return ret;
}

void tReplayBlockData::ExtractVehicleUpdateData(tReplayBlockData& packet, CVehicle* vehicle, float interpolation) {
    if (!vehicle)
        return;

    auto packetMatrix = CCompressedMatrixNotAligned::Decompress(packet.vehicle.matrix);
    packetMatrix.ScaleAll(interpolation);
    vehicle->GetMatrix().ScaleAll(1.0f - interpolation);
    vehicle->GetMatrix() += packetMatrix;
    vehicle->GetTurnSpeed() = CVector{0.0f};
    vehicle->m_fHealth = (float)(packet.vehicle.health * 4);
    vehicle->m_fGasPedal = (float)packet.vehicle.gasPedal / 100.0f;
    if (vehicle->IsAutomobile()) {
        // inlined ApplyPanelDamageToCar() @ 0x59CA10
        auto automobile = vehicle->AsAutomobile();
        const auto& damageManager = automobile->m_damageManager;

        for (auto i = 0; i < MAX_PANELS; i++) {
            const auto bitIdx = 0xF << (0x4 * i);
            const auto panel = (ePanels)i;
            const auto provided = (ePanelDamageState)(packet.vehicle.panels & bitIdx);
            const auto current = (ePanelDamageState)(damageManager.m_nPanelsStatus & bitIdx);

            if (provided != current) {
                automobile->m_damageManager.SetPanelStatus(panel, provided);
                automobile->SetPanelDamage(panel, true);
            }
        }
    }

    vehicle->GetMoveSpeed().x = (float)packet.vehicle.vecMoveSpeed.x / 8000.0f;
    vehicle->GetMoveSpeed().y = (float)packet.vehicle.vecMoveSpeed.y / 8000.0f;
    vehicle->GetMoveSpeed().z = (float)packet.vehicle.vecMoveSpeed.z / 8000.0f;

    auto v5 = ((uint8)vehicle->m_nFlags ^ (uint8)(packet.vehicle.physicalFlags << 6)) & 0x80 ^ vehicle->m_nFlags;
    auto v6 = v5 ^ (v5 ^ (packet.vehicle.physicalFlags << 28)) & 0x40000000;
    vehicle->m_nFlags = (packet.vehicle.physicalFlags << 28) ^ (v6 ^ (packet.vehicle.physicalFlags << 28)) & 0x7FFFFFFF;

    if (vehicle->m_nModelIndex == MODEL_RHINO) {
        vehicle->m_fSteerAngle = 0.0f;
        vehicle->AsAutomobile()->m_fDoomVerticalRotation = (float)packet.vehicle.steerAngle_or_doomVerticalRot / HEADING_COMPRESS_VALUE;
    } else {
        vehicle->m_fSteerAngle = (float)packet.vehicle.steerAngle_or_doomVerticalRot / 50.0f;
    }

    if (vehicle->IsAutomobile()) {
        auto automobile = vehicle->AsAutomobile();

        for (auto i = 0; i < 4; i++) { // for each wheel
            automobile->m_fWheelsSuspensionCompression[i] = (float)packet.vehicle.wheelsSuspensionCompression[i] / 50.0f;
            automobile->m_wheelRotation[i] = (float)packet.vehicle.wheelRotation[i] / HEADING_COMPRESS_VALUE;

        }
        automobile->m_doors[DOOR_LEFT_FRONT].m_fAngle = (float)packet.vehicle.angleDoorLF / 20.222929f;
        automobile->m_doors[DOOR_LEFT_FRONT].m_fPrevAngle = automobile->m_doors[DOOR_LEFT_FRONT].m_fAngle;

        automobile->m_doors[DOOR_RIGHT_FRONT].m_fAngle = (float)packet.vehicle.angleDoorRF / 20.222929f;
        automobile->m_doors[DOOR_RIGHT_FRONT].m_fPrevAngle = automobile->m_doors[DOOR_RIGHT_FRONT].m_fAngle;

        auto& damageManager = automobile->m_damageManager;
        if (packet.vehicle.angleDoorLF != 0) {
            damageManager.SetDoorOpen(DOOR_LEFT_FRONT);
        }

        if (packet.vehicle.angleDoorRF != 0) {
            damageManager.SetDoorOpen(DOOR_RIGHT_FRONT);
        }

        for (auto i = 0; i < MAX_DOORS; i++) {
            const auto bitIdx = (uint32)std::pow(2, i);
            const auto door = (eDoors)i;
            if (packet.vehicle.doorStatus & bitIdx && damageManager.IsDoorPresent(door)) {
                damageManager.SetDoorStatus(door, DAMSTATE_NOTPRESENT);
                automobile->SetDoorDamage(door, true);
            }
        }

        automobile->m_nWheelsOnGround = 4;
    }

    vehicle->vehicleFlags.bEngineOn = vehicle->vehicleFlags.bEngineBroken != true;
    vehicle->m_nAreaCode = static_cast<eAreaCodes>(CGame::currArea); // FIXME

    CWorld::Remove(vehicle);
    CWorld::Add(vehicle);
    vehicle->m_nPhysicalFlags ^= (vehicle->m_nPhysicalFlags ^ (packet.vehicle.physicalFlags << 29)) & 0x20000000;
}

void tReplayBlockData::ExtractBikeUpdateData(tReplayBlockData& packet, CBike* bike, float interpolation) {
    ExtractVehicleUpdateData(packet, bike->AsVehicle(), interpolation);

    bike->GetRideAnimData()->m_fSteerAngle = (float)packet.bike.steerAngle / 50.0f;
    bike->GetRideAnimData()->m_fAnimLean   = (float)packet.bike.animLean / 50.0f;
    bike->CalculateLeanMatrix();
}

void tReplayBlockData::ExtractTrainUpdateData(tReplayBlockData& packet, CTrain* train, float interpolation) {
    ExtractVehicleUpdateData(packet, train->AsVehicle(), interpolation);

    train->m_fTrainSpeed = packet.train.trainSpeed;
    train->m_fCurrentRailDistance = packet.train.currentRailDistance;
    train->m_fLength = packet.train.length;
    train->m_nTrackId = packet.train.trackId;

    if (auto prevCarriage = packet.train.prevCarriageRef) {
        CEntity::SafeCleanUpRef(train->m_pPrevCarriage);

        train->m_pPrevCarriage = GetVehiclePool()->GetAt(CReplay::FindPoolIndexForVehicle(prevCarriage - 1))->AsTrain();
        CEntity::SafeRegisterRef(train->m_pPrevCarriage);
    }

    if (auto nextCarriage = packet.train.nextCarriageRef) {
        CEntity::SafeCleanUpRef(train->m_pNextCarriage);

        train->m_pNextCarriage = GetVehiclePool()->GetAt(CReplay::FindPoolIndexForVehicle(nextCarriage - 1))->AsTrain();
        CEntity::SafeRegisterRef(train->m_pNextCarriage);
    }
}

// tReplayBlockData checks
#define CHECK_SIZE(_struct, _enum) static_assert(sizeof(tReplayBlockData::_struct) + sizeof(eReplayPacket) == CReplay::FindSizeOfPacket(REPLAY_PACKET_##_enum))
CHECK_SIZE(vehicle,        VEHICLE);
CHECK_SIZE(bike,           BIKE);
CHECK_SIZE(pedHeader,      PED_HEADER);
CHECK_SIZE(ped,            PED_UPDATE);
CHECK_SIZE(camera,         GENERAL);
CHECK_SIZE(clock,          CLOCK);
CHECK_SIZE(weather,        WEATHER);
CHECK_SIZE(timer,          TIMER);
CHECK_SIZE(bulletTrace ,   BULLET_TRACES);
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
