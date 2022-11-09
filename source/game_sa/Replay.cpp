#include "StdInc.h"

#include "Replay.h"
#include "Skidmarks.h"
#include "PlaneBanners.h"
#include "FireManager.h"
#include "PedClothesDesc.h"
#include "Camera.h"
#include "extensions/enumerate.hpp"

// player desc: PED_HEADER -> CLOTHES -> PED_UPDATE

void CReplay::InjectHooks() {
    RH_ScopedClass(CReplay);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x45E220);
    RH_ScopedInstall(DisableReplays, 0x45B150);
    RH_ScopedInstall(EnableReplays, 0x45B160);
    // RH_ScopedInstall(StorePedAnimation, 0x0, { .reversed = false });
    // RH_ScopedInstall(StorePedUpdate, 0x0, { .reversed = false });
    RH_ScopedInstall(RetrievePedAnimation, 0x45B4D0, { .reversed = false });
    RH_ScopedInstall(ProcessReplayCamera, 0x45D060);
    RH_ScopedInstall(Display, 0x45C210);
    RH_ScopedInstall(MarkEverythingAsNew, 0x45D430);
    RH_ScopedInstall(EmptyReplayBuffer, 0x45EC90);
    RH_ScopedInstall(GoToNextBlock, 0x45E2A0);
    RH_ScopedInstall(RecordVehicleDeleted, 0x45EBB0);
    RH_ScopedInstall(RecordPedDeleted, 0x45EC20);
    RH_ScopedInstall(SaveReplayToHD, 0x45C340);
    RH_ScopedInstall(ShouldStandardCameraBeProcessed, 0x45C440);
    RH_ScopedInstall(ProcessLookAroundCam, 0x45D760, { .reversed = false });
    RH_ScopedInstall(FindPoolIndexForPed, 0x45C450);
    RH_ScopedInstall(FindPoolIndexForVehicle, 0x45C460);
    RH_ScopedInstall(ProcessPedUpdate, 0x45CA70, { .reversed = false });
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
    // RH_ScopedInstall(NumberFramesAvailableToPlay, 0x0, { .reversed = false });
    RH_ScopedInstall(StreamAllNecessaryCarsAndPeds, 0x45D4B0);
    RH_ScopedInstall(CreatePlayerPed, 0x45D540);
    RH_ScopedInstall(TriggerPlayback, 0x4600F0);
    RH_ScopedInstall(Update, 0x460500, { .reversed = false });
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
    plugin::Call<0x460500>();
}

// 0x45B150
void CReplay::DisableReplays() {
    bReplayEnabled = false;
}

// 0x45B160
void CReplay::EnableReplays() {
    bReplayEnabled = true;
}

// 0x
void CReplay::StorePedAnimation() {
    plugin::Call<0x0>();
}

// 0x
void CReplay::StorePedUpdate(CPed* ped, int32 a2) {
    plugin::Call<0x0, CPed*, int32>(ped, a2);
}

// 0x45B4D0
void CReplay::RetrievePedAnimation() {
    plugin::Call<0x45B4D0>();
}

// 0x45C210
void CReplay::Display() {
    static uint32& g_ReplayTextTimer = *(uint32*)0xA43240;

    assert(Mode == eReplayMode::MODE_RECORD || Mode == eReplayMode::MODE_PLAYBACK);

    if (ShouldStandardCameraBeProcessed()) // originally == MODE_RECORD
        return;

    g_ReplayTextTimer++;
    if ((g_ReplayTextTimer & 32) == 0)
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
    Buffers.at(0).Write(0, {REPLAY_PACKET_END});
    Record = {.m_nOffset = 0, .m_pBase = &Buffers.at(0), .m_bSlot = 0};
    MarkEverythingAsNew();
}

// 0x45D390
void CReplay::EmptyPedsAndVehiclePools_NoDestructors() {
    plugin::Call<0x45D390>();
}

// 0x45E2A0
void CReplay::GoToNextBlock() {
    Record.Write({REPLAY_PACKET_END});
    BufferStatus[Record.m_bSlot] = REPLAYBUFFER_FULL;

    Record.m_bSlot = (Record.m_bSlot + 1) % 8;
    Record.m_pBase = &Buffers.at(Record.m_bSlot);
    Record.m_nOffset = 0;

    Record.Write({REPLAY_PACKET_END});
    BufferStatus[Record.m_bSlot] = REPLAYBUFFER_IN_USE;
    MarkEverythingAsNew();
}

// 0x45EBB0
void CReplay::RecordVehicleDeleted(CVehicle* vehicle) {
    if (Mode != MODE_RECORD)
        return;

    if (Record.m_nOffset + FindSizeOfPacket(REPLAY_PACKET_DELETED_VEH) > 99984) {
        GoToNextBlock();
    }

    Record.Write({.type = REPLAY_PACKET_DELETED_VEH, .deletedVehicle = {.unk1 = (uint16)(GetVehiclePool()->GetIndex(vehicle) / 2584)}}, true);
    Record.Write({REPLAY_PACKET_END});
}

// 0x45EC20
void CReplay::RecordPedDeleted(CPed* ped) {
    if (Mode != MODE_RECORD)
        return;

    if (Record.m_nOffset + FindSizeOfPacket(REPLAY_PACKET_DELETED_PED) > 99984) {
        GoToNextBlock();
    }

    Record.Write({.type = REPLAY_PACKET_DELETED_PED, .deletedPed = {.unk1 = (uint16)(GetPedPool()->GetIndex(ped) / 1988)}}, true);
    Record.Write({REPLAY_PACKET_END});
}

// 0x45EFA0
void CReplay::InitialiseVehiclePoolConversionTable() {
    rng::fill(m_VehiclePoolConversion, -1);
    auto convIdx = 0u;
    for (auto poolIdx = 0; poolIdx < GetVehiclePool()->GetSize() && convIdx < std::size(m_VehiclePoolConversion); poolIdx++, convIdx++) {
        if (GetVehiclePool()->GetAt(poolIdx) && IsThisVehicleUsedInRecording(convIdx)) {
            m_VehiclePoolConversion.at(convIdx) = poolIdx;
        }
    }
}

// 0x45EF20
void CReplay::InitialisePedPoolConversionTable() {
    rng::fill(m_PedPoolConversion, -1);
    auto convIdx = 0u;
    for (auto poolIdx = 0; poolIdx < GetPedPool()->GetSize() && convIdx < std::size(m_PedPoolConversion); poolIdx++, convIdx++) {
        if (GetPedPool()->GetAt(poolIdx) && IsThisVehicleUsedInRecording(convIdx)) {
            m_PedPoolConversion.at(convIdx) = poolIdx;
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
        auto idx = 7;
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
            CFileMgr::Write(file, &Buffers.at(slot), sizeof(tReplayBuffer));
        }

        CFileMgr::CloseFile(file);
    }
}

// 0x45C440
bool CReplay::ShouldStandardCameraBeProcessed() {
    return Mode != MODE_PLAYBACK;
}

// unused
// 0x45C450
int32 CReplay::FindPoolIndexForPed(int32 index) {
    return m_PedPoolConversion.at(index);
}

// unused
// 0x45C460
int32 CReplay::FindPoolIndexForVehicle(int32 index) {
    return m_VehiclePoolConversion.at(index);
}

// 0x45CA70
void CReplay::ProcessPedUpdate(CPed* ped, float a2, const CAddressInReplayBuffer& buffer) {
    plugin::Call<0x45CA70, CPed*, float, const CAddressInReplayBuffer&>(ped, a2, buffer);
}

// 0x45D060
void CReplay::ProcessReplayCamera() {
    assert(TheCamera.m_pRwCamera);

    auto modelling = TheCamera.GetRwMatrix();
    switch (CameraMode) {
    case REPLAY_CAM_MODE_TOPDOWN:
        TheCamera.GetPosition() = CVector{CameraFocus.x, CameraFocus.y, CameraFocus.z + 15.0f};
        TheCamera.GetRight()    = CVector{1.0f, 0.0f,  0.0f};
        TheCamera.GetUp()       = CVector{0.0f, 1.0f,  0.0f};
        TheCamera.GetForward()  = CVector{0.0f, 0.0f, -1.0f};

        modelling->pos = CameraFocus;
        modelling->at = TheCamera.GetForward();
        modelling->up = TheCamera.GetUp();
        modelling->right = TheCamera.GetRight();
        break;
    case REPLAY_CAM_MODE_FIXED:
        const auto direction = (CameraFocus - CameraFixed).Normalized();
        const auto right = direction.Cross({0.0f, 0.0f, 1.0f}).Normalized();

        TheCamera.GetPosition() = CameraFixed;
        TheCamera.GetForward() = direction;
        TheCamera.GetUp() = direction.Cross(right);
        TheCamera.GetRight() = right;

        modelling->pos = CameraFocus;
        modelling->at = TheCamera.GetForward();
        modelling->up = TheCamera.GetUp();
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
    plugin::Call<0x45D760>();
}

// 0x
bool CReplay::CanWeFindPoolIndexForPed(int32 index) {
    return plugin::CallAndReturn<bool, 0x0, int32>(index);
}

// 0x
bool CReplay::CanWeFindPoolIndexForVehicle(int32 index) {
    return plugin::CallAndReturn<bool, 0x0, int32>(index);
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
        for (auto& packet : buffer) {
            if (packet.type == REPLAY_PACKET_PED_HEADER && packet.playerData.index == index) {
                return true;
            }
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

// 0x0
void CReplay::NumberFramesAvailableToPlay() {
    plugin::Call<0x0>();
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
        auto& buffer = Buffers.at(slot);
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
                if (player && player == GetPedPool()->GetAt(m_PedPoolConversion[packet.ped.pedIndexInPool])) {
                    ProcessPedUpdate(player, 1.0f, {.m_nOffset = offset, .m_pBase = &buffer, .m_bSlot = (uint8)i}); // m_bSlot def is NOTSA
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

    auto slot = (idx + 1) % 8;
    for (auto j = BufferStatus[slot]; j != 2 && j != 1; j = BufferStatus[slot]) {
        slot = (slot + 1) % 8;
    }

    Playback.m_bSlot = slot;
    Playback.m_pBase = &Buffers.at(slot);
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
