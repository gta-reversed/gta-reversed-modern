#include "StdInc.h"

// float& CClouds::m_fVolumetricCloudDensity; // unused
// bool& CClouds::m_bVolumetricCloudHeightSwitch; // unused
// float& CClouds::m_fVolumetricCloudWindMoveFactor; // unused
float& CClouds::m_fVolumetricCloudMaxDistance = *reinterpret_cast<float*>(0xC6AA58);
unsigned int& CClouds::m_VolumetricCloudsUsedNum = *reinterpret_cast<unsigned int*>(0xC6AA5C);

float& CClouds::ms_cameraRoll = *reinterpret_cast<float*>(0xC6AA64);

int& CClouds::IndividualRotation = *reinterpret_cast<int*>(0xC6AA6C);
float& CClouds::CloudRotation = *reinterpret_cast<float*>(0xC6AA70);

tVolumetricClouds& CClouds::ms_vc = *reinterpret_cast<tVolumetricClouds*>(0xC6AAB0);
tMovingFog& CClouds::ms_mf = *reinterpret_cast<tMovingFog*>(0xC6C158);

CVector& CClouds::PlayerCoords = *reinterpret_cast<CVector*>(0xC6E958); // gVecPlayerCoors
CVector& CClouds::CameraCoors = *reinterpret_cast<CVector*>(0xC6E964);  // gVecCameraCoors

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
    ReversibleHooks::Install("CClouds", "SetUpOneSkyPoly", 0x713060, &CClouds::SetUpOneSkyPoly);
    ReversibleHooks::Install("CClouds", "MovingFogInit", 0x713660, &CClouds::MovingFogInit);
    ReversibleHooks::Install("CClouds", "MovingFog_Create", 0x713760, &CClouds::MovingFog_Create);
    ReversibleHooks::Install("CClouds", "MovingFog_Delete", 0x713730, &CClouds::MovingFog_Delete);
    ReversibleHooks::Install("CClouds", "MovingFog_Update", 0x716B10, &CClouds::MovingFog_Update);
    ReversibleHooks::Install("CClouds", "MovingFog_GetFXIntensity", 0x7136D0, &CClouds::MovingFog_GetFXIntensity);
    ReversibleHooks::Install("CClouds", "MovingFog_GetWind", 0x7136E0, &CClouds::MovingFog_GetWind);
    ReversibleHooks::Install("CClouds", "MovingFog_GetFirstFreeSlot", 0x713710, &CClouds::MovingFog_GetFirstFreeSlot);
    ReversibleHooks::Install("CClouds", "MovingFogRender", 0x716C90, &CClouds::MovingFogRender);
    //    ReversibleHooks::Install("CClouds", "Render", 0x713950, &CClouds::Render);
    ReversibleHooks::Install("CClouds", "RenderSkyPolys", 0x714650, &CClouds::RenderSkyPolys);
    //    ReversibleHooks::Install("CClouds", "RenderBottomFromHeight", 0x7154B0, &CClouds::RenderBottomFromHeight);
    ReversibleHooks::Install("CClouds", "VolumetricCloudsInit", 0x7131C0, &CClouds::VolumetricCloudsInit);
    //    ReversibleHooks::Install("CClouds", "VolumetricClouds_Create", 0x715F40, &CClouds::VolumetricClouds_Create);
    ReversibleHooks::Install("CClouds", "VolumetricClouds_Delete", 0x7135F0, &CClouds::VolumetricClouds_Delete);
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
    IndividualRotation += (int)((CTimer::ms_fTimeStep * CWeather::Wind * 0.5f + 0.3f) * 60.0f);
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
void CClouds::SetUpOneSkyPoly(CVector vert1pos, CVector vert2pos, CVector vert3pos, CVector vert4pos, unsigned char topRed, unsigned char topGreen, unsigned char topBlue,
                              unsigned char bottomRed, unsigned char bottomGreen, unsigned char bottomBlue) {
    unsigned short uiStartVertex = uiTempBufferVerticesStored;
    unsigned short iStartIndex = uiTempBufferIndicesStored;

    RwIm3DVertexSetRGBA(&aTempBufferVertices[uiStartVertex + 0], topRed, topGreen, topBlue, 0xFF);
    RwIm3DVertexSetPos(&aTempBufferVertices[uiStartVertex + 0], vert1pos.x, vert1pos.y, vert1pos.z);
    RwIm3DVertexSetU(&aTempBufferVertices[uiStartVertex + 0], 0.f);
    RwIm3DVertexSetV(&aTempBufferVertices[uiStartVertex + 0], 0.f);

    RwIm3DVertexSetRGBA(&aTempBufferVertices[uiStartVertex + 1], topRed, topGreen, topBlue, 0xFF);
    RwIm3DVertexSetPos(&aTempBufferVertices[uiStartVertex + 1], vert2pos.x, vert2pos.y, vert2pos.z);
    RwIm3DVertexSetU(&aTempBufferVertices[uiStartVertex + 1], 0.f);
    RwIm3DVertexSetV(&aTempBufferVertices[uiStartVertex + 1], 0.f);

    RwIm3DVertexSetRGBA(&aTempBufferVertices[uiStartVertex + 2], bottomRed, bottomGreen, bottomBlue, 0xFF);
    RwIm3DVertexSetPos(&aTempBufferVertices[uiStartVertex + 2], vert3pos.x, vert3pos.y, vert3pos.z);
    RwIm3DVertexSetU(&aTempBufferVertices[uiStartVertex + 2], 0.f);
    RwIm3DVertexSetV(&aTempBufferVertices[uiStartVertex + 2], 0.f);

    RwIm3DVertexSetRGBA(&aTempBufferVertices[uiStartVertex + 3], bottomRed, bottomGreen, bottomBlue, 0xFF);
    RwIm3DVertexSetPos(&aTempBufferVertices[uiStartVertex + 3], vert4pos.x, vert4pos.y, vert4pos.z);
    RwIm3DVertexSetU(&aTempBufferVertices[uiStartVertex + 3], 0.f);
    RwIm3DVertexSetV(&aTempBufferVertices[uiStartVertex + 3], 0.f);

    aTempBufferIndices[iStartIndex + 0] = uiStartVertex;
    aTempBufferIndices[iStartIndex + 1] = uiStartVertex + 2;
    aTempBufferIndices[iStartIndex + 2] = uiStartVertex + 1;
    aTempBufferIndices[iStartIndex + 3] = uiStartVertex + 1;
    aTempBufferIndices[iStartIndex + 4] = uiStartVertex + 2;
    aTempBufferIndices[iStartIndex + 5] = uiStartVertex + 3;

    uiTempBufferIndicesStored += 6;
    uiTempBufferVerticesStored += 4;
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

    ms_mf.m_vecPosn[slotId].x = rand() * RAND_MAX_FLOAT_RECIPROCAL * 116.0f - 58.0f + posn->x;
    ms_mf.m_vecPosn[slotId].y = rand() * RAND_MAX_FLOAT_RECIPROCAL * 116.0f - 58.0f + posn->y;
    ms_mf.m_vecPosn[slotId].z = rand() * RAND_MAX_FLOAT_RECIPROCAL * 10.0f - 5.0f + posn->z;

    ms_mf.m_fSize[slotId] = rand() * RAND_MAX_FLOAT_RECIPROCAL * 6.0f + 4.0f;
    ms_mf.m_fIntensity[slotId] = 1.0f;
    ms_mf.m_fMaxIntensity[slotId] = rand() * RAND_MAX_FLOAT_RECIPROCAL * 12.0f + 8.0f;
    ms_mf.m_fSpeed[slotId] = rand() * RAND_MAX_FLOAT_RECIPROCAL * 0.7f + 0.5f;
    ms_mf.m_bFogSlots[slotId] = true;
}

// unused
// 0x713730
void CClouds::MovingFog_Delete(int fogSlotIndex) {
    fogSlotIndex = clamp(fogSlotIndex, 0, MAX_MOVING_FOG - 1);
    ms_mf.m_bFogSlots[fogSlotIndex] = false;
}

// 0x716B10
void CClouds::MovingFog_Update() {
    if (CWeather::Foggyness_SF == 0.f)
        return;

    CVector camPos = TheCamera.GetPosition();
    for (int i = 0; i < MAX_MOVING_FOG; i++) {
        CVector& fogPosn = ms_mf.m_vecPosn[i];
        CVector offset = fogPosn - camPos;
        if (!ms_mf.m_bFogSlots[i]) {
            MovingFog_Create(&camPos);
            continue;
        }

        fogPosn.x += CClouds::ms_mf.m_vecWind.x + ms_mf.m_fSpeed[i];
        fogPosn.y += CClouds::ms_mf.m_vecWind.y + ms_mf.m_fSpeed[i];

        if (offset.Magnitude() <= 60.f) {
            ms_mf.m_fIntensity[i] = std::min(ms_mf.m_fIntensity[i] + CTimer::ms_fTimeStep, ms_mf.m_fMaxIntensity[i]);
        } else {
            ms_mf.m_fIntensity[i] -= CTimer::ms_fTimeStep;
            if (ms_mf.m_fIntensity[i] <= 0.f)
                MovingFog_Delete(i);
        }
    }
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
    if (CWeather::Foggyness_SF == 0.f || CGame::currArea == AREA_CODE_NORMAL_WORLD || FindPlayerPed(-1)->m_nAreaCode == AREA_CODE_NORMAL_WORLD)
        return;

    float step = CTimer::ms_fTimeStep * (1.f / 300.f);
    if (CCullZones::CamNoRain() && CCullZones::PlayerNoRain())
        CurrentFogIntensity = std::max(CurrentFogIntensity - step, 0.f);
    else
        CurrentFogIntensity = std::min(CurrentFogIntensity + step, 0.f);

    if (CWeather::UnderWaterness >= CPostEffects::m_fWaterFXStartUnderWaterness)
        CurrentFogIntensity = 0.f;

    if (CurrentFogIntensity == 0.f)
        return;
    CVector up = TheCamera.GetUpVector(), right = TheCamera.GetRightVector();
    CPostEffects::ImmediateModeRenderStatesStore();
    CPostEffects::ImmediateModeRenderStatesSet();

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, gpCloudTex[1]->raster);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);

    int red = std::min(CTimeCycle::m_CurrentColours.m_nSkyBottomRed + 132, 255), green = std::min(CTimeCycle::m_CurrentColours.m_nSkyBottomGreen + 132, 255),
        blue = std::min(CTimeCycle::m_CurrentColours.m_nSkyBottomBlue + 132, 255);

    int numVerts = 0;
    for (int i = 0; i < MAX_MOVING_FOG; i++) {
        if (!ms_mf.m_bFogSlots[i])
            continue;
        float halfSize = ms_mf.m_fSize[i] * 0.5f;
        CVector up1 = up * halfSize, right1 = right * halfSize;

        int alpha = static_cast<int>(CWeather::Foggyness_SF * ms_mf.m_fIntensity[i] * CurrentFogIntensity);
        for (int l = 0; l < 6; l++) {
            float u = 0.f, v = 0.f;
            CVector pos = ms_mf.m_vecPosn[i];

            switch (ms_mf.m_nPrimIndices[l]) {
            case 0:
                u = 0.f;
                v = 0.f;
                pos += right1 + up1;
                break;

            case 1:
                u = 1.f;
                v = 0.f;
                pos += right1 - up1;
                break;

            case 2:
                u = 1.f;
                v = 1.f;
                pos -= right1 + up1;
                break;

            case 3:
                u = 0.f;
                v = 1.f;
                pos -= right1 - up1;
                break;
            }

            RwIm3DVertexSetRGBA(&aTempBufferVertices[numVerts], red, green, blue, alpha);
            RwIm3DVertexSetPos(&aTempBufferVertices[numVerts], pos.x, pos.y, pos.z);
            RwIm3DVertexSetU(&aTempBufferVertices[numVerts], u);
            RwIm3DVertexSetV(&aTempBufferVertices[numVerts], v);
            numVerts++;

            if (numVerts == TOTAL_TEMP_BUFFER_VERTICES - 2) {
                if (RwIm3DTransform(aTempBufferVertices, numVerts, 0, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXUV)) {
                    RwIm3DRenderPrimitive(rwPRIMTYPETRILIST);
                    RwIm3DEnd();
                }
                numVerts = 0;
            }
        }
    }

    if (numVerts > 0 && RwIm3DTransform(aTempBufferVertices, numVerts, 0, rwIM3D_VERTEXXYZ | rwIM3D_VERTEXUV)) {
        RwIm3DRenderPrimitive(rwPRIMTYPETRILIST);
        RwIm3DEnd();
    }
    CPostEffects::ImmediateModeRenderStatesReStore();
    CClouds::MovingFog_Update();
}

// 0x713950
void CClouds::Render() {
    plugin::Call<0x713950>();
}

// 0x714650
void CClouds::RenderSkyPolys() {
    CVector norm, pos;

    if (TheCamera.m_matrix) {
        pos = TheCamera.m_matrix->GetPosition();
        norm = TheCamera.m_matrix->GetForward();
    } else {
        pos = TheCamera.m_placement.m_vPosn;
        float fHeading = TheCamera.m_placement.m_fHeading;
        norm.x = -sin(fHeading);
        norm.y = cos(fHeading);
    }
    norm.z = 0.f;
    norm.Normalise();

    CVector invNorm = -norm;
    float fBlendFactor = (pos.z - 25.0f) * (1.0f / 80.0f);
    fBlendFactor = clamp(fBlendFactor, 0.f, 1.f);
    fBlendFactor = std::max(fBlendFactor, CWeather::Foggyness);

    RwRGBA belowHorizonGrey = CTimeCycle::m_BelowHorizonGrey;
    belowHorizonGrey.red += static_cast<RwUInt8>(fBlendFactor * static_cast<float>(CTimeCycle::m_CurrentColours.m_nSkyBottomRed - belowHorizonGrey.red));
    belowHorizonGrey.green += static_cast<RwUInt8>(fBlendFactor * static_cast<float>(CTimeCycle::m_CurrentColours.m_nSkyBottomGreen - belowHorizonGrey.green));
    belowHorizonGrey.blue += static_cast<RwUInt8>(fBlendFactor * static_cast<float>(CTimeCycle::m_CurrentColours.m_nSkyBottomBlue - belowHorizonGrey.blue));

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, nullptr);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, nullptr);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, nullptr);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, nullptr);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, RWRSTATE(rwBLENDINVSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, nullptr);
    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));

    uiTempBufferIndicesStored = 0;
    uiTempBufferVerticesStored = 0;

    CVector2D scale{norm.y * SKYP_WIDTH_MULT, invNorm.x * SKYP_WIDTH_MULT}, aPos2D[4] = {};
    CVector aVertices[4] = {};
    float aPosZ[6] = {};

    aPos2D[0].x = pos.x + (invNorm.x - scale.x) * SKYP_CAM_DIST;
    aPos2D[0].y = pos.y + (invNorm.y - scale.y) * SKYP_CAM_DIST;
    aPos2D[1].x = pos.x + (invNorm.x + scale.x) * SKYP_CAM_DIST;
    aPos2D[1].y = pos.y + (invNorm.y + scale.y) * SKYP_CAM_DIST;
    aPos2D[2].x = pos.x + (norm.x - scale.x) * SKYP_CAM_DIST;
    aPos2D[2].y = pos.y + (norm.y - scale.y) * SKYP_CAM_DIST;
    aPos2D[3].x = pos.x + (norm.x + scale.x) * SKYP_CAM_DIST;
    aPos2D[3].y = pos.y + (norm.y + scale.y) * SKYP_CAM_DIST;

    aPosZ[0] = pos.z + (invNorm.z + SKYP_ABOVE_HORIZON_Z) * SKYP_CAM_DIST;
    aPosZ[1] = pos.z + (norm.z + SKYP_ABOVE_HORIZON_Z) * SKYP_CAM_DIST;
    aPosZ[2] = pos.z + (norm.z + SKYP_HORIZON_Z) * SKYP_CAM_DIST;
    aPosZ[3] = pos.z + (norm.z + SKYP_SEA_HORIZON_Z) * SKYP_CAM_DIST;
    aPosZ[4] = pos.z + (norm.z + SKYP_BELOW_HORIZON_Z) * SKYP_CAM_DIST;
    aPosZ[5] = pos.z + (invNorm.z + SKYP_BELOW_HORIZON_Z) * SKYP_CAM_DIST;

    aVertices[0].x = aPos2D[2].x;
    aVertices[0].y = aPos2D[2].y;
    aVertices[0].z = aPosZ[1];
    aVertices[1].x = aPos2D[3].x;
    aVertices[1].y = aPos2D[3].y;
    aVertices[1].z = aPosZ[1];
    aVertices[2].x = aPos2D[2].x;
    aVertices[2].y = aPos2D[2].y;
    aVertices[2].z = aPosZ[2];
    aVertices[3].x = aPos2D[3].x;
    aVertices[3].y = aPos2D[3].y;
    aVertices[3].z = aPosZ[2];

    CClouds::SetUpOneSkyPoly(aVertices[0], aVertices[1], aVertices[2], aVertices[3], CTimeCycle::m_CurrentColours.m_nSkyTopRed, CTimeCycle::m_CurrentColours.m_nSkyTopGreen,
                             CTimeCycle::m_CurrentColours.m_nSkyTopBlue, CTimeCycle::m_CurrentColours.m_nSkyBottomRed, CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
                             CTimeCycle::m_CurrentColours.m_nSkyBottomBlue);

    aVertices[0].z = aPosZ[2];
    aVertices[1].z = aPosZ[2];
    aVertices[2].z = aPosZ[3];
    aVertices[3].z = aPosZ[3];

    CClouds::SetUpOneSkyPoly(aVertices[0], aVertices[1], aVertices[2], aVertices[3], CTimeCycle::m_CurrentColours.m_nSkyBottomRed, CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
                             CTimeCycle::m_CurrentColours.m_nSkyBottomBlue, CTimeCycle::m_CurrentColours.m_nSkyBottomRed, CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
                             CTimeCycle::m_CurrentColours.m_nSkyBottomBlue);

    aVertices[0].z = aPosZ[3];
    aVertices[1].z = aPosZ[3];
    aVertices[2].z = aPosZ[4];
    aVertices[3].z = aPosZ[4];

    CClouds::SetUpOneSkyPoly(aVertices[0], aVertices[1], aVertices[2], aVertices[3], CTimeCycle::m_CurrentColours.m_nSkyBottomRed, CTimeCycle::m_CurrentColours.m_nSkyBottomGreen,
                             CTimeCycle::m_CurrentColours.m_nSkyBottomBlue, belowHorizonGrey.red, belowHorizonGrey.green, belowHorizonGrey.blue);

    aVertices[0].z = aPosZ[1];
    aVertices[1].z = aPosZ[1];
    aVertices[2].x = aPos2D[0].x;
    aVertices[2].y = aPos2D[0].y;
    aVertices[2].z = aPosZ[0];
    aVertices[3].x = aPos2D[1].x;
    aVertices[3].y = aPos2D[1].y;
    aVertices[3].z = aPosZ[0];

    CClouds::SetUpOneSkyPoly(aVertices[0], aVertices[1], aVertices[2], aVertices[3], CTimeCycle::m_CurrentColours.m_nSkyTopRed, CTimeCycle::m_CurrentColours.m_nSkyTopGreen,
                             CTimeCycle::m_CurrentColours.m_nSkyTopBlue, CTimeCycle::m_CurrentColours.m_nSkyTopRed, CTimeCycle::m_CurrentColours.m_nSkyTopGreen,
                             CTimeCycle::m_CurrentColours.m_nSkyTopBlue);

    aVertices[0].z = aPosZ[4];
    aVertices[1].x = aPos2D[3].x;
    aVertices[1].y = aPos2D[3].y;
    aVertices[1].z = aPosZ[4];
    aVertices[2].z = aPosZ[5];
    aVertices[3].z = aPosZ[5];

    CClouds::SetUpOneSkyPoly(aVertices[0], aVertices[1], aVertices[2], aVertices[3], belowHorizonGrey.red, belowHorizonGrey.green, belowHorizonGrey.blue, belowHorizonGrey.red,
                             belowHorizonGrey.green, belowHorizonGrey.blue);

    CBrightLights::RenderOutGeometryBuffer();
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
        ms_vc.m_bSlots[i] = false;
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
    vcSlotIndex = clamp(vcSlotIndex, 0, MAX_VOLUMETRIC_CLOUDS - 1);
    ms_vc.m_bSlots[vcSlotIndex] = false;
    ms_vc.m_bInsideVisibilityRange[vcSlotIndex] = false;
}

// unused
// inlined into VolumetricClouds_Create
// 0x7135C0
int CClouds::VolumetricClouds_GetFirstFreeSlot() {
    for (int i = 0; i < CClouds::m_VolumetricCloudsUsedNum; i++) {
        if (!ms_vc.m_bSlots[i])
            return i;
    }

    return -1;
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
