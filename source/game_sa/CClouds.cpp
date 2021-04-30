#include "StdInc.h"

//float& CClouds::m_fVolumetricCloudDensity; // unused
//bool& CClouds::m_bVolumetricCloudHeightSwitch; // unused
//float& CClouds::m_fVolumetricCloudWindMoveFactor; // unused
float& CClouds::m_fVolumetricCloudMaxDistance = *reinterpret_cast<float*>(0xC6AA58);
unsigned int& CClouds::m_VolumetricCloudsUsedNum = *reinterpret_cast<unsigned int*>(0xC6AA5C);

float& CClouds::ms_cameraRoll = *reinterpret_cast<float*>(0xC6AA64);

int& CClouds::IndividualRotation = *reinterpret_cast<int*>(0xC6AA6C);
float& CClouds::CloudRotation = *reinterpret_cast<float*>(0xC6AA70);

tVolumetricClouds& CClouds::ms_vc = *reinterpret_cast<tVolumetricClouds*>(0xC6AAB0);
tMovingFog& CClouds::ms_mf = *reinterpret_cast<tMovingFog*>(0xC6C158);

CVector& CClouds::PlayerCoords = *reinterpret_cast<CVector*>(0xC6E958); // gVecPlayerCoors
CVector& CClouds::CameraCoors = *reinterpret_cast<CVector*>(0xC6E964); // gVecCameraCoors

float& CurrentFogIntensity = *reinterpret_cast<float*>(0x8D5798);

RwTexture*& gpMoonMask = *reinterpret_cast<RwTexture**>(0xC6AA74);
RwTexture* (&gpCloudTex)[2] = *reinterpret_cast<RwTexture* (*)[2]>(0xC6AA78);

float& flt_C6E954 = *reinterpret_cast<float*>(0xC6E954); // see CClouds::RenderBottomFromHeight, CClouds::MovingFogRender
float& flt_C6E970 = *reinterpret_cast<float*>(0xC6E970); // see CClouds::VolumetricCloudsRender

int& dword_C6E974 = *reinterpret_cast<int*>(0xC6E974); // see CClouds::VolumetricCloudsRender

void CClouds::InjectHooks() {
    ReversibleHooks::Install("CClouds", "Init", 0x7138D0, &CClouds::Init);
    ReversibleHooks::Install("CClouds", "Update", 0x712FF0, &CClouds::Update);
    ReversibleHooks::Install("CClouds", "Shutdown", 0x712FA0, &CClouds::Shutdown);
//    ReversibleHooks::Install("CClouds", "SetUpOneSkyPoly", 0x713060, &CClouds::SetUpOneSkyPoly);
    ReversibleHooks::Install("CClouds", "MovingFogInit", 0x713660, &CClouds::MovingFogInit);
    ReversibleHooks::Install("CClouds", "MovingFog_Create", 0x713760, &CClouds::MovingFog_Create);
//    ReversibleHooks::Install("CClouds", "MovingFog_Delete", 0x713730, &CClouds::MovingFog_Delete);
//    ReversibleHooks::Install("CClouds", "MovingFog_Update", 0x716B10, &CClouds::MovingFog_Update);
    ReversibleHooks::Install("CClouds", "MovingFog_GetFXIntensity", 0x7136D0, &CClouds::MovingFog_GetFXIntensity);
    ReversibleHooks::Install("CClouds", "MovingFog_GetWind", 0x7136E0, &CClouds::MovingFog_GetWind);
    ReversibleHooks::Install("CClouds", "MovingFog_GetFirstFreeSlot", 0x713710, &CClouds::MovingFog_GetFirstFreeSlot);
//    ReversibleHooks::Install("CClouds", "MovingFogRender", 0x716C90, &CClouds::MovingFogRender);
//    ReversibleHooks::Install("CClouds", "Render", 0x713950, &CClouds::Render);
//    ReversibleHooks::Install("CClouds", "RenderSkyPolys", 0x714650, &CClouds::RenderSkyPolys);
//    ReversibleHooks::Install("CClouds", "RenderBottomFromHeight", 0x7154B0, &CClouds::RenderBottomFromHeight);
    ReversibleHooks::Install("CClouds", "VolumetricCloudsInit", 0x7131C0, &CClouds::VolumetricCloudsInit);
//    ReversibleHooks::Install("CClouds", "VolumetricClouds_Create", 0x715F40, &CClouds::VolumetricClouds_Create);
//    ReversibleHooks::Install("CClouds", "VolumetricClouds_Delete", 0x7135F0, &CClouds::VolumetricClouds_Delete);
    ReversibleHooks::Install("CClouds", "VolumetricClouds_GetFirstFreeSlot", 0x7135C0, &CClouds::VolumetricClouds_GetFirstFreeSlot);
    ReversibleHooks::Install("CClouds", "VolumetricCloudsGetMaxDistance", 0x713630, &CClouds::VolumetricCloudsGetMaxDistance);
//    ReversibleHooks::Install("CClouds", "VolumetricCloudsRender", 0x716380, &CClouds::VolumetricCloudsRender);
}

// 0x7138D0
void CClouds::Init() {
    CTxdStore::PushCurrentTxd();
    auto txd = CTxdStore::FindTxdSlot("particle");
    CTxdStore::SetCurrentTxd(txd);
    gpCloudTex[0] = RwTextureRead("cloud1", nullptr);
    gpCloudTex[1] = RwTextureRead("cloudmasked", nullptr);
    gpMoonMask = RwTextureRead("lunar", "lunarm");
    ms_vc.m_pTex = RwTextureRead("cloudhigh", "cloudhighm");
    CTxdStore::PopCurrentTxd();
    CloudRotation = 0.0f;
    VolumetricCloudsInit();
    MovingFogInit();
}

// 0x712FF0
void CClouds::Update() {
    CloudRotation = std::sin(TheCamera.m_fOrientation - 0.85f) * CWeather::Wind * 0.001f + CClouds::CloudRotation;
    IndividualRotation += (CTimer::ms_fTimeStep * CWeather::Wind * 0.5f + 0.3f) * 60.0f;
}

// 0x712FA0
void CClouds::Shutdown() {
    RwTextureDestroy(gpCloudTex[0]);
    gpCloudTex[0] = nullptr;

    RwTextureDestroy(gpCloudTex[1]);
    gpCloudTex[1] = nullptr;

    RwTextureDestroy(CClouds::ms_vc.m_pTex);
    CClouds::ms_vc.m_pTex = nullptr;
}

// 0x713060
void CClouds::SetUpOneSkyPoly(CVector vert1pos, CVector vert2pos, CVector vert3pos, CVector vert4pos,
                              unsigned char topRed, unsigned char topGreen, unsigned char topBlue,
                              unsigned char bottomRed, unsigned char bottomGreen, unsigned char bottomBlue) {
    plugin::Call<0x713060,
                 CVector, CVector, CVector, CVector,
                 unsigned char, unsigned char, unsigned char,
                 unsigned char, unsigned char, unsigned char>(
                 vert1pos, vert2pos, vert3pos, vert4pos,
                 topRed, topGreen, topBlue,
                 bottomRed, bottomGreen, bottomBlue);
}

// 0x713660
void CClouds::MovingFogInit() {
    ms_mf = {};
    ms_mf.m_nPrimIndices[0] = 0;
    ms_mf.m_nPrimIndices[1] = 1;
    ms_mf.m_nPrimIndices[2] = 2;
    ms_mf.m_nPrimIndices[3] = 0;
    ms_mf.m_nPrimIndices[4] = 2;
    ms_mf.m_nPrimIndices[5] = 3;
    ms_mf.m_vecWind = CVector(0.06f, 0.06f, 0.0f);
}

// 0x713760
void CClouds::MovingFog_Create(CVector* posn) {
    int slotId = MovingFog_GetFirstFreeSlot();

    if (slotId == -1) {
        return;
    }

    ms_mf.m_vecPosn[slotId].x = rand() * RAND_MAX_RECIPROCAL * 116.0f - 58.0f + posn->x;
    ms_mf.m_vecPosn[slotId].y = rand() * RAND_MAX_RECIPROCAL * 116.0f - 58.0f + posn->y;
    ms_mf.m_vecPosn[slotId].z = rand() * RAND_MAX_RECIPROCAL * 10.0f - 5.0f + posn->z;

    ms_mf.m_fSize[slotId] = rand() * RAND_MAX_RECIPROCAL * 6.0f + 4.0f;
    ms_mf.m_fIntensity[slotId] = 1.0f;
    ms_mf.m_fMaxIntensity[slotId] = rand() * RAND_MAX_RECIPROCAL * 12.0f + 8.0f;
    ms_mf.m_fSpeed[slotId] = rand() * RAND_MAX_RECIPROCAL * 0.7f + 0.5f;
    ms_mf.m_bFogSlots[slotId] = true;
}

// unused
// 0x713730
void CClouds::MovingFog_Delete(int fogSlotIndex) {
    plugin::Call<0x713730, int>(fogSlotIndex);
}

// 0x716B10
void CClouds::MovingFog_Update() {
    plugin::Call<0x716B10>();
}

// 0x7136D0
float CClouds::MovingFog_GetFXIntensity() {
    return CWeather::Foggyness_SF;
}

// 0x7136E0
CVector CClouds::MovingFog_GetWind() {
    return ms_mf.m_vecWind;
}

// unused
// 0x713710
int CClouds::MovingFog_GetFirstFreeSlot() {
    int result = 0;
    while (CClouds::ms_mf.m_bFogSlots[result]) {
        if (++result >= MAX_MOVING_FOG)
            return -1;
    }
    return result;
}

// 0x716C90
void CClouds::MovingFogRender() {
    plugin::Call<0x716C90>();
}

// 0x713950
void CClouds::Render() {
    plugin::Call<0x713950>();
}

// 0x714650
void CClouds::RenderSkyPolys() {
    plugin::Call<0x714650>();
}

// 0x7154B0
void CClouds::RenderBottomFromHeight() {
    plugin::Call<0x7154B0>();
}

// 0x7131C0
void CClouds::VolumetricCloudsInit() {
    ms_vc.m_vecCloudsSpace[0] = CVector(0.0f, 1.0f, 0.0f);
    ms_vc.m_vecCloudsSpace[1] = CVector(0.0f, 0.0f, 1.0f);
    ms_vc.m_vecCloudsSpace[2] = CVector(1.0f, 0.0f, 0.0f);

    ms_vc.m_fCloudXCoords[0] = -0.5f;
    ms_vc.m_fCloudYCoords[0] = 0.0f;
    ms_vc.m_fCloudZCoords[0] = 0.5f;
    ms_vc.m_fCloudUCoords[0] = 0.0f;
    ms_vc.m_fCloudVCoords[0] = 0.0f;

    ms_vc.m_fCloudXCoords[1] = 0.5f;
    ms_vc.m_fCloudYCoords[1] = 0.0f;
    ms_vc.m_fCloudZCoords[1] = 0.5f;
    ms_vc.m_fCloudUCoords[1] = 1.0f;
    ms_vc.m_fCloudVCoords[1] = 0.0f;

    ms_vc.m_fCloudXCoords[2] = -0.5f;
    ms_vc.m_fCloudYCoords[2] = 0.0f;
    ms_vc.m_fCloudZCoords[2] = -0.5f;
    ms_vc.m_fCloudUCoords[2] = 0.0f;
    ms_vc.m_fCloudVCoords[2] = 1.0f;

    ms_vc.m_fCloudXCoords[3] = 0.5f;
    ms_vc.m_fCloudYCoords[3] = 0.0f;
    ms_vc.m_fCloudZCoords[3] = 0.5f;
    ms_vc.m_fCloudUCoords[3] = 1.0f;
    ms_vc.m_fCloudVCoords[3] = 0.0f;

    ms_vc.m_fCloudXCoords[4] = 0.5f;
    ms_vc.m_fCloudYCoords[4] = 0.0f;
    ms_vc.m_fCloudZCoords[4] = -0.5f;
    ms_vc.m_fCloudUCoords[4] = 1.0f;
    ms_vc.m_fCloudVCoords[4] = 1.0f;

    ms_vc.m_fCloudXCoords[5] = -0.5f;
    ms_vc.m_fCloudYCoords[5] = 0.0f;
    ms_vc.m_fCloudZCoords[5] = -0.5f;
    ms_vc.m_fCloudUCoords[5] = 0.0f;
    ms_vc.m_fCloudVCoords[5] = 1.0f;

    ms_vc.m_fCloudXCoords[6] = -0.5f;
    ms_vc.m_fCloudYCoords[6] = 0.5f;
    ms_vc.m_fCloudZCoords[6] = 0.0f;
    ms_vc.m_fCloudUCoords[6] = 0.0f;
    ms_vc.m_fCloudVCoords[6] = 0.0f;

    ms_vc.m_fCloudXCoords[7] = 0.5f;
    ms_vc.m_fCloudYCoords[7] = 0.5f;
    ms_vc.m_fCloudZCoords[7] = 0.0f;
    ms_vc.m_fCloudUCoords[7] = 1.0f;
    ms_vc.m_fCloudVCoords[7] = 0.0f;

    ms_vc.m_fCloudXCoords[8] = -0.5f;
    ms_vc.m_fCloudYCoords[8] = -0.5f;
    ms_vc.m_fCloudZCoords[8] = 0.0f;
    ms_vc.m_fCloudUCoords[8] = 0.0f;
    ms_vc.m_fCloudVCoords[8] = 1.0f;

    ms_vc.m_fCloudXCoords[9] = 0.5f;
    ms_vc.m_fCloudYCoords[9] = 0.5f;
    ms_vc.m_fCloudZCoords[9] = 0.0f;
    ms_vc.m_fCloudUCoords[9] = 1.0f;
    ms_vc.m_fCloudVCoords[9] = 0.0f;

    ms_vc.m_fCloudXCoords[10] = 0.5f;
    ms_vc.m_fCloudYCoords[10] = -0.5f;
    ms_vc.m_fCloudZCoords[10] = 0.0f;
    ms_vc.m_fCloudUCoords[10] = 1.0f;
    ms_vc.m_fCloudVCoords[10] = 1.0f;

    ms_vc.m_fCloudXCoords[11] = -0.5f;
    ms_vc.m_fCloudYCoords[11] = -0.5f;
    ms_vc.m_fCloudZCoords[11] = 0.0f;
    ms_vc.m_fCloudUCoords[11] = 0.0f;
    ms_vc.m_fCloudVCoords[11] = 1.0f;

    ms_vc.m_fCloudXCoords[12] = 0.0f;
    ms_vc.m_fCloudYCoords[12] = -0.5f;
    ms_vc.m_fCloudZCoords[12] = 0.5f;
    ms_vc.m_fCloudUCoords[12] = 0.0f;
    ms_vc.m_fCloudVCoords[12] = 0.0f;

    ms_vc.m_fCloudXCoords[13] = 0.0f;
    ms_vc.m_fCloudYCoords[13] = 0.5f;
    ms_vc.m_fCloudZCoords[13] = 0.5f;
    ms_vc.m_fCloudUCoords[13] = 1.0f;
    ms_vc.m_fCloudVCoords[13] = 0.0f;

    ms_vc.m_fCloudXCoords[14] = 0.0f;
    ms_vc.m_fCloudYCoords[14] = -0.5f;
    ms_vc.m_fCloudZCoords[14] = -0.5f;
    ms_vc.m_fCloudUCoords[14] = 0.0f;
    ms_vc.m_fCloudVCoords[14] = 1.0f;

    ms_vc.m_fCloudXCoords[15] = 0.0f;
    ms_vc.m_fCloudYCoords[15] = 0.5f;
    ms_vc.m_fCloudZCoords[15] = 0.5f;
    ms_vc.m_fCloudUCoords[15] = 1.0f;
    ms_vc.m_fCloudVCoords[15] = 0.0f;

    ms_vc.m_fCloudXCoords[16] = 0.0f;
    ms_vc.m_fCloudYCoords[16] = 0.5f;
    ms_vc.m_fCloudZCoords[16] = -0.5f;
    ms_vc.m_fCloudUCoords[16] = 1.0f;
    ms_vc.m_fCloudVCoords[16] = 1.0f;

    ms_vc.m_fCloudXCoords[17] = 0.0f;
    ms_vc.m_fCloudYCoords[17] = -0.5f;
    ms_vc.m_fCloudZCoords[17] = -0.5f;
    ms_vc.m_fCloudUCoords[17] = 0.0f;
    ms_vc.m_fCloudVCoords[17] = 1.0f;

    for (int i = 0; i < MAX_VOLUMETRIC_CLOUDS; ++i) {
        ms_vc.m_bSlots[i] = 0;
        ms_vc.m_bInsideVisibilityRange[i] = 0;
    }
}

// see VolumetricClouds_GetFirstFreeSlot
// 0x715F40
void CClouds::VolumetricClouds_Create(CVector* posn) {
    plugin::Call<0x715F40, CVector*>(posn);
}

// 0x7135F0
void CClouds::VolumetricClouds_Delete(int vcSlotIndex) {
    plugin::Call<0x7135F0, int>(vcSlotIndex);
}

// unused
// inlined into VolumetricClouds_Create
// 0x7135C0
int CClouds::VolumetricClouds_GetFirstFreeSlot() {
    return plugin::CallAndReturn<int, 0x7135C0>();
}

// 0x713630
float CClouds::VolumetricCloudsGetMaxDistance() {
    if (Scene.m_pRwCamera->farPlane < 600.0f) {
        return Scene.m_pRwCamera->farPlane;
    }
    return 600.0f;
}

// 0x716380
void CClouds::VolumetricCloudsRender() {
   plugin::Call<0x716380>();
}
