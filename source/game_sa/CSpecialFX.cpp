#include "StdInc.h"

bool& CSpecialFX::bVideoCam = *(bool*)0xC7C70C;
bool& CSpecialFX::bLiftCam = *(bool*)0xC7C70D;
bool& CSpecialFX::bSnapShotActive = *(bool*)0xC7C714;
uint32& CSpecialFX::SnapShotFrames = *(uint32*)0xC7C710;

RwTexture*& gpFinishFlagTex = *reinterpret_cast<RwTexture**>(0xC7C718);

void CSpecialFX::InjectHooks() {
//    ReversibleHooks::Install("CSpecialFX", "Init", 0x7268F0, &CSpecialFX::Init);
//    ReversibleHooks::Install("CSpecialFX", "Update", 0x726AA0, &CSpecialFX::Update);
    ReversibleHooks::Install("CSpecialFX", "Shutdown", 0x723390, &CSpecialFX::Shutdown);
//    ReversibleHooks::Install("CSpecialFX", "AddWeaponStreak", 0x0, &CSpecialFX::AddWeaponStreak);
//    ReversibleHooks::Install("CSpecialFX", "Render", 0x726AD0, &CSpecialFX::Render);
//    ReversibleHooks::Install("CSpecialFX", "Render2DFXs", 0x721660, &CSpecialFX::Render2DFXs);
    ReversibleHooks::Install("CSpecialFX", "ReplayStarted", 0x721D30, &CSpecialFX::ReplayStarted);
}

// 0x7268F0
void CSpecialFX::Init() {
    plugin::Call<0x7268F0>();
}

// 0x726AA0
void CSpecialFX::Update() {
    plugin::Call<0x726AA0>();
}

// 0x723390
void CSpecialFX::Shutdown() {
    C3dMarkers::Shutdown();
    if (gpFinishFlagTex) {
        RwTextureDestroy(gpFinishFlagTex);
        gpFinishFlagTex = nullptr;
    }
    if (CMirrors::pBuffer) {
        RwRasterDestroy(CMirrors::pBuffer);
        CMirrors::pBuffer = nullptr;
    }
    if (CMirrors::pZBuffer) {
        RwRasterDestroy(CMirrors::pZBuffer);
        CMirrors::pZBuffer = nullptr;
    }
    CMirrors::TypeOfMirror = 0;
    CMirrors::MirrorFlags = 0;
}

// unused function
// 0x7233F0
void CSpecialFX::AddWeaponStreak(eWeaponType weaponType) {

}

// 0x726AD0
void CSpecialFX::Render() {
    plugin::Call<0x726AD0>();
//    CMotionBlurStreaks::Render();
//    CBulletTraces::Render();
//    CBrightLights::Render();
//    CShinyTexts::Render();
//    C3dMarkers::Render();
//    CCheckpoints::Render();
}

// 0x721660
void CSpecialFX::Render2DFXs() {
    plugin::Call<0x721660>();
}

// 0x721D30
void CSpecialFX::ReplayStarted() {
    if (CSpecialFX::bSnapShotActive) {
        CSpecialFX::bSnapShotActive = false;
        CTimer::ms_fTimeScale = 1.0f;
    }
}
