#include "StdInc.h"

#include "Replay.h"

eReplayMode &CReplay::Mode = *reinterpret_cast<eReplayMode*>(0xA43088);
bool& CReplay::bReplayEnabled = *reinterpret_cast<bool*>(0x8A6160);

void CReplay::InjectHooks() {
    RH_ScopedClass(CReplay);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(DisableReplays, 0x45B150);
    RH_ScopedInstall(EnableReplays, 0x45B160);
    // RH_ScopedInstall(StorePedAnimation, 0x0, { .reversed = false });
    // RH_ScopedInstall(StorePedUpdate, 0x0, { .reversed = false });
    RH_ScopedInstall(RetrievePedAnimation, 0x45B4D0, { .reversed = false });
    RH_ScopedInstall(ProcessReplayCamera, 0x45D060, { .reversed = false });
    RH_ScopedInstall(Display, 0x45C210, { .reversed = false });
    RH_ScopedInstall(MarkEverythingAsNew, 0x45D430, { .reversed = false });
    RH_ScopedInstall(EmptyReplayBuffer, 0x45EC90, { .reversed = false });
    // RH_ScopedInstall(GoToNextBlock, 0x0, { .reversed = false });
    RH_ScopedInstall(RecordVehicleDeleted, 0x45EBB0, { .reversed = false });
    // RH_ScopedInstall(RecordPedDeleted, 0x0, { .reversed = false });
    RH_ScopedInstall(Init, 0x45E220, { .reversed = false });
    RH_ScopedInstall(SaveReplayToHD, 0x45C340, { .reversed = false });
        RH_ScopedInstall(ShouldStandardCameraBeProcessed, 0x45C440);
    RH_ScopedInstall(ProcessLookAroundCam, 0x45D760, { .reversed = false });
    // RH_ScopedInstall(FindPoolIndexForPed, 0x0, { .reversed = false });
    // RH_ScopedInstall(FindPoolIndexForVehicle, 0x0, { .reversed = false });
    RH_ScopedInstall(ProcessPedUpdate, 0x45CA70, { .reversed = false });
    // RH_ScopedInstall(CanWeFindPoolIndexForPed, 0x0, { .reversed = false });
    // RH_ScopedInstall(CanWeFindPoolIndexForVehicle, 0x0, { .reversed = false });
    // RH_ScopedInstall(StorePlayerInfoVariables, 0x0, { .reversed = false });
    RH_ScopedInstall(StoreStuffInMem, 0x45F180, { .reversed = false });
    RH_ScopedInstall(RestorePlayerInfoVariables, 0x45E1F0, { .reversed = false });
    RH_ScopedInstall(RestoreStuffFromMem, 0x45ECD0, { .reversed = false });
    RH_ScopedInstall(FinishPlayback, 0x45F050, { .reversed = false });
    // RH_ScopedInstall(StoreClothesDesc, 0x0, { .reversed = false });
    RH_ScopedInstall(RecordThisFrame, 0x45E300, { .reversed = false });
    RH_ScopedInstall(RestoreClothesDesc, 0x45C7D0, { .reversed = false });
    RH_ScopedInstall(DealWithNewPedPacket, 0x45CEA0, { .reversed = false });
    RH_ScopedInstall(PlayBackThisFrameInterpolation, 0x45F380, { .reversed = false });
    RH_ScopedInstall(FastForwardToTime, 0x460350, { .reversed = false });
    RH_ScopedInstall(PlayBackThisFrame, 0x4604A0, { .reversed = false });
    RH_ScopedInstall(FindSizeOfPacket, 0x45C850, { .reversed = false });
    // RH_ScopedInstall(IsThisVehicleUsedInRecording, 0x0, { .reversed = false });
    // RH_ScopedInstall(IsThisPedUsedInRecording, 0x0, { .reversed = false });
    // RH_ScopedInstall(InitialiseVehiclePoolConversionTable, 0x0, { .reversed = false });
    // RH_ScopedInstall(InitialisePedPoolConversionTable, 0x0, { .reversed = false });
    // RH_ScopedInstall(InitialisePoolConversionTables, 0x0, { .reversed = false });
    RH_ScopedInstall(FindFirstFocusCoordinate, 0x45D6C0, { .reversed = false });
    // RH_ScopedInstall(NumberFramesAvailableToPlay, 0x0, { .reversed = false });
    RH_ScopedInstall(StreamAllNecessaryCarsAndPeds, 0x45D4B0, { .reversed = false });
    RH_ScopedInstall(CreatePlayerPed, 0x45D540, { .reversed = false });
    RH_ScopedInstall(TriggerPlayback, 0x4600F0, { .reversed = false });
    RH_ScopedInstall(Update, 0x460500, { .reversed = false });
}

// 0x460625 thunk
// 0x45E220
void CReplay::Init() {
    plugin::Call<0x45E220>();
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
    static uint32& g_nReplayTimer = *(uint32*)0xA43240;

    assert(Mode == eReplayMode::MODE_RECORD || Mode == eReplayMode::MODE_PLAYBACK);

    if (ShouldStandardCameraBeProcessed()) // originally == MODE_RECORD
        return;

    g_nReplayTimer++;
    if ((g_nReplayTimer & 32) == 0)
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
    plugin::Call<0x45D430>();
}

// 0x45EC90
void CReplay::EmptyReplayBuffer() {
    plugin::Call<0x45EC90>();
}

// 0x
void CReplay::GoToNextBlock() {
    plugin::Call<0x0>();
}

// 0x45EBB0
void CReplay::RecordVehicleDeleted(CVehicle* vehicle) {
    plugin::Call<0x45EBB0, CVehicle*>(vehicle);
}

// 0x45EC20
void CReplay::RecordPedDeleted(CPed* ped) {
    plugin::Call<0x45EC20, CPed*>(ped);
}

// 0x45EFA0
void CReplay::InitialiseVehiclePoolConversionTable() {
    plugin::Call<0x45EFA0>();
}

// 0x45EF20
void CReplay::InitialisePedPoolConversionTable() {
    plugin::Call<0x45EF20>();
}

// 0x
void CReplay::InitialisePoolConversionTables() {
    plugin::Call<0x0>();
}

// 0x45C340
void CReplay::SaveReplayToHD() {
    plugin::Call<0x45C340>();
}

// 0x45C440
bool CReplay::ShouldStandardCameraBeProcessed() {
    return Mode != MODE_PLAYBACK;
}

// 0x
void CReplay::FindPoolIndexForPed(int32 a1) {
    plugin::Call<0x0, int32>(a1);
}

// 0x
void CReplay::FindPoolIndexForVehicle(int32 a1) {
    plugin::Call<0x0, int32>(a1);
}

// 0x45CA70
void CReplay::ProcessPedUpdate() {
    plugin::Call<0x45CA70>();
}

// 0x45D060
void CReplay::ProcessReplayCamera() {
    plugin::Call<0x45D060>();
}

// 0x45D760
void CReplay::ProcessLookAroundCam() {
    plugin::Call<0x45D760>();
}

// 0x
void CReplay::CanWeFindPoolIndexForPed(int32 a1) {
    plugin::Call<0x0, int32>(a1);
}

// 0x
void CReplay::CanWeFindPoolIndexForVehicle(int32 a1) {
    plugin::Call<0x0, int32>(a1);
}

// 0x0
void CReplay::StorePlayerInfoVariables() {
    plugin::Call<0x0>();
}

// 0x45F180
void CReplay::StoreStuffInMem() {
    plugin::Call<0x45F180>();
}

// 0x45E1F0
void CReplay::RestorePlayerInfoVariables() {
    plugin::Call<0x45E1F0>();
}

// 0x45ECD0
void CReplay::RestoreStuffFromMem() {
    plugin::Call<0x45ECD0>();
}

// 0x45F050
void CReplay::FinishPlayback() {
    plugin::Call<0x45F050>();
}

// 0x
void CReplay::StoreClothesDesc() {
    plugin::Call<0x0>();
}

// 0x45E300
void CReplay::RecordThisFrame() {
    plugin::Call<0x45E300>();
}

// 0x45C7D0
void CReplay::RestoreClothesDesc() {
    plugin::Call<0x45C7D0>();
}

// 0x45CEA0
void CReplay::DealWithNewPedPacket() {
    plugin::Call<0x45CEA0>();
}

// 0x45F380
void CReplay::PlayBackThisFrameInterpolation() {
    plugin::Call<0x45F380>();
}

// 0x460350
void CReplay::FastForwardToTime(uint32 a1) {
    plugin::Call<0x460350, uint32>(a1);
}

// 0x4604A0
void CReplay::PlayBackThisFrame() {
    plugin::Call<0x4604A0>();
}

// 0x45C850
void CReplay::FindSizeOfPacket(uint16 id) {
    plugin::Call<0x45C850, uint16>(id);
}

// 0x
bool CReplay::IsThisVehicleUsedInRecording(int32 a1) {
    return plugin::CallAndReturn<bool, 0x0, int32>(a1);
}

// 0x
bool CReplay::IsThisPedUsedInRecording(int32 a1) {
    return plugin::CallAndReturn<bool, 0x0, int32>(a1);
}

// 0x45D6C0
void CReplay::FindFirstFocusCoordinate(CVector* a1) {
    plugin::Call<0x45D6C0, CVector*>(a1);
}

// 0x0
void CReplay::NumberFramesAvailableToPlay() {
    plugin::Call<0x0>();
}

// 0x45D4B0
void CReplay::StreamAllNecessaryCarsAndPeds() {
    plugin::Call<0x45D4B0>();
}

// 0x45D540
CPed* CReplay::CreatePlayerPed() {
    return plugin::CallAndReturn<CPed*, 0x45D4B0>();
}

// 0x4600F0
void CReplay::TriggerPlayback(bool a1, float a2, float a3, float a4, bool a5) {
    return plugin::Call<0x4600F0, bool, float, float, float, bool>(a1, a2, a3, a4, a5);

    if (!ShouldStandardCameraBeProcessed())
        return;

    CSpecialFX::ReplayStarted();
    CameraMode = cameraMomde;
    Mode = MODE_PLAYBACK;

    CameraFixedX = x;
    CameraFixedY = y;
    CameraFixedZ = z;

    bPlayingBackFromFile = 0;
    bAllowLookAroundCam = 1;
    FramesActiveLookAroundCam = 0;
    if (FindPlayerVehicle(-1, 0)) {
        OldRadioStation = CAERadioTrackManager::GetCurrentRadioStationID(&AERadioTrackManager);
        CAudioEngine::StopRadio(0, 0);
    } else {
        OldRadioStation = 0;
    }
    CurrArea = CGame::currArea;
    for (i = 0; i < 8; ++i) {
        if (BufferStatus[i] == 2)
            break;
    }
    v6 = (i + 1) % 8;
    for (j = BufferStatus[v6]; j != 2; j = BufferStatus[v6]) {
        if (j == 1)
            break;
        v6 = (v6 + 1) % 8;
    }
    Playback.m_bSlot = v6;
    memset(&point, 0, sizeof(point));
    Playback.m_pBase = (uint8*)Buffers[(unsigned __int8)v6];
    Playback.m_nOffset = 0;
    CObject::DeleteAllTempObjectsInArea(0.0, 0.0, 0.0, 999999.88);
    StoreStuffInMem();

    InitialisePedPoolConversionTable(); // InitialisePoolConversionTables
    InitialiseVehiclePoolConversionTable();

    EmptyPedsAndVehiclePools_NoDestructors();
    CSkidmarks::Clear();
    StreamAllNecessaryCarsAndPeds();
    CWorld::Players[0].m_pPed = CreatePlayerPed();
    if (bLoadScene) {
        bDoLoadSceneWhenDone = 0;
    } else {
        bDoLoadSceneWhenDone = 1;
        p_m_pos = &TheCamera.m_matrix->m_pos;
        if (!TheCamera.m_matrix)
            p_m_pos = &TheCamera.m_placement.m_vPosn;
        LoadSceneX = p_m_pos->x;
        p_m_vPosn = &TheCamera.m_matrix->m_pos;
        if (!TheCamera.m_matrix)
            p_m_vPosn = &TheCamera.m_placement.m_vPosn;
        LoadSceneY = p_m_vPosn->y;
        if (TheCamera.m_matrix)
            v10 = &TheCamera.m_matrix->m_pos;
        else
            v10 = &TheCamera.m_placement.m_vPosn;
        LoadSceneZ = v10->z;
        FindFirstFocusCoordinate(&point);
        CGame::currLevel = CTheZones::GetLevelFromPosition(&point);
        CCollision::SortOutCollisionAfterLoad();
        CStreaming::LoadScene(&point);
    }
    CWeaponEffects::ClearCrossHairs();
    CExplosion::ClearAllExplosions();
    CPlaneBanners::Init();
    gFireManager.DestroyAllFxSystems();
    TheCamera.Restore();
    CDraw::SetFOV(70.0);
    TheCamera.SetFadeColour(0, 0, 0);
    TheCamera.Fade(0.0f, eFadeFlag::FADE_IN);
    TheCamera.ProcessFade();
    TheCamera.Fade(1.5f, eFadeFlag::FADE_OUT);
}
