#include "StdInc.h"

eReplayMode &CReplay::Mode = *reinterpret_cast<eReplayMode*>(0xA43088);
bool& CReplay::bReplayEnabled = *reinterpret_cast<bool*>(0x8A6160);

void CReplay::InjectHooks() {
    ReversibleHooks::Install("CReplay", "DisableReplays", 0x45B150, &CReplay::DisableReplays);
    ReversibleHooks::Install("CReplay", "EnableReplays", 0x45B160, &CReplay::EnableReplays);
//    ReversibleHooks::Install("CReplay", "StorePedAnimation", 0x0, &CReplay::StorePedAnimation);
//    ReversibleHooks::Install("CReplay", "StorePedUpdate", 0x0, &CReplay::StorePedUpdate);
//    ReversibleHooks::Install("CReplay", "RetrievePedAnimation", 0x45B4D0, &CReplay::RetrievePedAnimation);
//    ReversibleHooks::Install("CReplay", "ProcessReplayCamera", 0x45D060, &CReplay::ProcessReplayCamera);
//    ReversibleHooks::Install("CReplay", "Display", 0x45C210, &CReplay::Display);
//    ReversibleHooks::Install("CReplay", "MarkEverythingAsNew", 0x45D430, &CReplay::MarkEverythingAsNew);
//    ReversibleHooks::Install("CReplay", "EmptyReplayBuffer", 0x45EC90, &CReplay::EmptyReplayBuffer);
//    ReversibleHooks::Install("CReplay", "GoToNextBlock", 0x0, &CReplay::GoToNextBlock);
//    ReversibleHooks::Install("CReplay", "RecordVehicleDeleted", 0x45EBB0, &CReplay::RecordVehicleDeleted);
//    ReversibleHooks::Install("CReplay", "RecordPedDeleted", 0x0, &CReplay::RecordPedDeleted);
//    ReversibleHooks::Install("CReplay", "Init", 0x45E220, &CReplay::Init);
//    ReversibleHooks::Install("CReplay", "Init_thunk", 0x460625, &CReplay::Init);
//    ReversibleHooks::Install("CReplay", "SaveReplayToHD", 0x45C340, &CReplay::SaveReplayToHD);
    ReversibleHooks::Install("CReplay", "ShouldStandardCameraBeProcessed", 0x45C440, &CReplay::ShouldStandardCameraBeProcessed);
//    ReversibleHooks::Install("CReplay", "ProcessLookAroundCam", 0x45D760, &CReplay::ProcessLookAroundCam);
//    ReversibleHooks::Install("CReplay", "FindPoolIndexForPed", 0x0, &CReplay::FindPoolIndexForPed);
//    ReversibleHooks::Install("CReplay", "FindPoolIndexForVehicle", 0x0, &CReplay::FindPoolIndexForVehicle);
//    ReversibleHooks::Install("CReplay", "ProcessPedUpdate", 0x45CA70, &CReplay::ProcessPedUpdate);
//    ReversibleHooks::Install("CReplay", "CanWeFindPoolIndexForPed", 0x0, &CReplay::CanWeFindPoolIndexForPed);
//    ReversibleHooks::Install("CReplay", "CanWeFindPoolIndexForVehicle", 0x0, &CReplay::CanWeFindPoolIndexForVehicle);
//    ReversibleHooks::Install("CReplay", "StorePlayerInfoVariables", 0x0, &CReplay::StorePlayerInfoVariables);
//    ReversibleHooks::Install("CReplay", "StoreStuffInMem", 0x45F180, &CReplay::StoreStuffInMem);
//    ReversibleHooks::Install("CReplay", "RestorePlayerInfoVariables", 0x45E1F0, &CReplay::RestorePlayerInfoVariables);
//    ReversibleHooks::Install("CReplay", "RestoreStuffFromMem", 0x45ECD0, &CReplay::RestoreStuffFromMem);
//    ReversibleHooks::Install("CReplay", "FinishPlayback", 0x45F050, &CReplay::FinishPlayback);
//    ReversibleHooks::Install("CReplay", "StoreClothesDesc", 0x0, &CReplay::StoreClothesDesc);
//    ReversibleHooks::Install("CReplay", "RecordThisFrame", 0x45E300, &CReplay::RecordThisFrame);
//    ReversibleHooks::Install("CReplay", "RestoreClothesDesc", 0x45C7D0, &CReplay::RestoreClothesDesc);
//    ReversibleHooks::Install("CReplay", "DealWithNewPedPacket", 0x45CEA0, &CReplay::DealWithNewPedPacket);
//    ReversibleHooks::Install("CReplay", "PlayBackThisFrameInterpolation", 0x45F380, &CReplay::PlayBackThisFrameInterpolation);
//    ReversibleHooks::Install("CReplay", "FastForwardToTime", 0x460350, &CReplay::FastForwardToTime);
//    ReversibleHooks::Install("CReplay", "PlayBackThisFrame", 0x4604A0, &CReplay::PlayBackThisFrame);
//    ReversibleHooks::Install("CReplay", "FindSizeOfPacket", 0x45C8, &CReplay::FindSizeOfPacket);
//    ReversibleHooks::Install("CReplay", "IsThisVehicleUsedInRecording", 0x0, &CReplay::IsThisVehicleUsedInRecording);
//    ReversibleHooks::Install("CReplay", "IsThisPedUsedInRecording", 0x0, &CReplay::IsThisPedUsedInRecording);
//    ReversibleHooks::Install("CReplay", "InitialiseVehiclePoolConversionTable", 0x0, &CReplay::InitialiseVehiclePoolConversionTable);
//    ReversibleHooks::Install("CReplay", "InitialisePedPoolConversionTable", 0x0, &CReplay::InitialisePedPoolConversionTable);
//    ReversibleHooks::Install("CReplay", "InitialisePoolConversionTables", 0x0, &CReplay::InitialisePoolConversionTables);
//    ReversibleHooks::Install("CReplay", "FindFirstFocusCoordinate", 0x45D6C0, &CReplay::FindFirstFocusCoordinate);
//    ReversibleHooks::Install("CReplay", "NumberFramesAvailableToPlay", 0x0, &CReplay::NumberFramesAvailableToPlay);
//    ReversibleHooks::Install("CReplay", "StreamAllNecessaryCarsAndPeds", 0x45D4B0, &CReplay::StreamAllNecessaryCarsAndPeds);
//    ReversibleHooks::Install("CReplay", "CreatePlayerPed", 0x45D540, &CReplay::CreatePlayerPed);
//    ReversibleHooks::Install("CReplay", "TriggerPlayback", 0x4600F0, &CReplay::TriggerPlayback);
//    ReversibleHooks::Install("CReplay", "Update", 0x460500, &CReplay::Update);
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
    CReplay::bReplayEnabled = false;
}

// 0x45B160
void CReplay::EnableReplays() {
    CReplay::bReplayEnabled = true;
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
    plugin::Call<0x45C210>();
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

// 0x
void CReplay::RecordPedDeleted(CPed* ped) {
    plugin::Call<0x0, CPed*>(ped);
}

// 0x
void CReplay::InitialiseVehiclePoolConversionTable() {
    plugin::Call<0x0>();
}

// 0x
void CReplay::InitialisePedPoolConversionTable() {
    plugin::Call<0x0>();
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
    return CReplay::Mode != REPLAY_MODE_1;
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
    plugin::Call<0x4600F0, bool, float, float, float, bool>(a1, a2, a3, a4, a5);
}
