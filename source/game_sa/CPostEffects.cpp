#include "StdInc.h"

float& CPostEffects::SCREEN_EXTRA_MULT_CHANGE_RATE = *(float*)0x8D5168; // 0.0005f;
float& CPostEffects::SCREEN_EXTRA_MULT_BASE_CAP = *(float*)0x8D516C;    // 0.35f;
float& CPostEffects::SCREEN_EXTRA_MULT_BASE_MULT = *(float*)0x8D5170;   // 1.0f;

bool& CPostEffects::m_bDisableAllPostEffect = *(bool*)0xC402CF;
bool& CPostEffects::m_bSavePhotoFromScript = *(bool*)0xC402D0;
bool& CPostEffects::m_bInCutscene = *(bool*)0xC402B7;

RwRaster*& pVisionFXRaster = *(RwRaster**)0xC40158;

RwD3D9Vertex (&vertexGroup)[4] = *(RwD3D9Vertex(*)[4])0xC401D8;

float& CPostEffects::m_xoffset = *(float*)0x8D5130; // 4.0f
float& CPostEffects::m_yoffset = *(float*)0x8D5134; // 24.0f

float& CPostEffects::m_colour1Multiplier = *(float*)0x8D5160;   // 1.0f;
float& CPostEffects::m_colour2Multiplier = *(float*)0x8D5164;   // 1.0f;
float& CPostEffects::m_colourLeftUOffset = *(float*)0x8D5150;   // 8
float& CPostEffects::m_colourRightUOffset = *(float*)0x8D5154;  // 8
float& CPostEffects::m_colourTopVOffset = *(float*)0x8D5158;    // 8
float& CPostEffects::m_colourBottomVOffset = *(float*)0x8D515C; // 8

bool& CPostEffects::m_bNightVision = *(bool*)0xC402B8;
float& CPostEffects::m_fNightVisionSwitchOnFXCount = *(float*)0xC40300; // = CPostEffects::m_fNightVisionSwitchOnFXTime
float& CPostEffects::m_fNightVisionSwitchOnFXTime = *(float*)0x8D50B0;  // 42480000h
int& CPostEffects::m_NightVisionGrainStrength = *(int*)0x8D50A8;        // 48
RwRGBA& CPostEffects::m_NightVisionMainCol = *(RwRGBA*)0x8D50AC;        // {0xFF, 0x0, 0x82, 0x0};

bool& CPostEffects::m_bDarknessFilter = *(bool*)0xC402C4;
int& CPostEffects::m_DarknessFilterAlpha = *(int*)0x8D5204;                   // 170
int& CPostEffects::m_DarknessFilterAlphaDefault = *(int*)0x8D50F4;            // 170
int& CPostEffects::m_DarknessFilterRadiosityIntensityLimit = *(int*)0x8D50F8; // 45

float& CPostEffects::m_fWaterFXStartUnderWaterness = *(float*)0x8D514C; // 0.535f;
float& CPostEffects::m_fWaterFullDarknessDepth = *(float*)0x8D5148;     // 90.0f
bool& CPostEffects::m_bWaterDepthDarkness = *(bool*)0x8D5144;           // true;

bool& CPostEffects::m_bHeatHazeFX = *(bool*)0xC402BA;
int& CPostEffects::m_HeatHazeFXSpeedMin = *(int*)0x8D50EC;  // 6
int& CPostEffects::m_HeatHazeFXSpeedMax = *(int*)0x8D50F0;  // 10
int& CPostEffects::m_HeatHazeFXIntensity = *(int*)0x8D50E8; // 150
int& CPostEffects::m_HeatHazeFXType = *(int*)0xC402BC;
int& CPostEffects::m_HeatHazeFXTypeLast = *(int*)0x8D50E4; // -1
int& CPostEffects::m_HeatHazeFXRandomShift = *(int*)0xC402C0;
float& CPostEffects::m_HeatHazeFXScanSizeX = *(float*)0xC40304;   // SCREEN_WIDTH * 0.0015625 * 24.0f;
float& CPostEffects::m_HeatHazeFXScanSizeY = *(float*)0xC40308;   // SCREEN_HEIGHT * 0.002232143 * 24.0f;
float& CPostEffects::m_HeatHazeFXRenderSizeX = *(float*)0xC4030C; // SCREEN_WIDTH * 0.0015625 * 24.0f;
float& CPostEffects::m_HeatHazeFXRenderSizeY = *(float*)0xC40310; // SCREEN_HEIGHT * 0.002232143 * 24.0f;

bool& CPostEffects::m_bFog = *(bool*)0xC402C6;

bool& CPostEffects::m_bSpeedFX = *(bool*)0x8D5100; // true;
bool& CPostEffects::m_bSpeedFXTestMode = *(bool*)0xC402C7;
bool& CPostEffects::m_bSpeedFXUserFlag = *(bool*)0x8D5108;             // always true;
bool& CPostEffects::m_bSpeedFXUserFlagCurrentFrame = *(bool*)0x8D5109; // 0
float& CPostEffects::m_fSpeedFXManualSpeedCurrentFrame = *(float*)0xC402C8;
int& CPostEffects::m_SpeedFXAlpha = *(int*)0x8D5104; // 36

RwRaster*& CPostEffects::pRasterFrontBuffer = *(RwRaster**)0xC402D8;

float& CPostEffects::ms_imf = *(float*)0xC40150;

bool& CPostEffects::m_bGrainEnable = *(bool*)0xC402B4;
RwRaster*& CPostEffects::m_pGrainRaster = *(RwRaster**)0xC402B0;
char (&CPostEffects::m_grainStrength)[2] = *(char (*)[2])0x8D5094;

bool& CPostEffects::m_bCCTV = *(bool*)0xC402C5;
CRGBA& CPostEffects::m_CCTVcol = *(CRGBA*)0x8D50FC; // r g b

bool& CPostEffects::m_bRainEnable = *(bool*)0xC402D1;
bool& CPostEffects::m_bColorEnable = *(bool*)0x8D518C; // true;

bool& CPostEffects::m_bRadiosity = *(bool*)0xC402CC;
// bool& CPostEffects::m_bRadiosityDebug = *(bool*)0x0;
// bool& CPostEffects::m_bRadiosityLinearFilter = *(bool*)0x0;
// bool& CPostEffects::m_bRadiosityStripCopyMode = *(bool*)0x0;
// static CPostEffects::m_RadiosityFilterUCorrection;
// static CPostEffects::m_RadiosityFilterVCorrection;
int& CPostEffects::m_RadiosityIntensity = *(int*)0x8D5118;      // 35
int& CPostEffects::m_RadiosityIntensityLimit = *(int*)0x8D5114; // 220
bool& CPostEffects::m_bRadiosityBypassTimeCycleIntensityLimit = *(bool*)0xC402CE;
float& CPostEffects::m_RadiosityPixelsX = *(float*)0xC40314;                    // SCREEN_WIDTH
float& CPostEffects::m_RadiosityPixelsY = *(float*)0xC40318;                    // SCREEN_HEIGHT
unsigned int& CPostEffects::m_RadiosityFilterPasses = *(unsigned int*)0x8D5110; // 1
unsigned int& CPostEffects::m_RadiosityRenderPasses = *(unsigned int*)0x8D510C; // 2

static RwBlendFunction& gStoredRenderStateSrcBlend = *(RwBlendFunction*)(0xC40280);
static RwBlendFunction& gStoredRenderStateDestBlend = *(RwBlendFunction*)(0xC40284);
static bool& gStoredRenderStateFogEnable = *(bool*)(0xC40288);
static RwCullMode& gStoredRenderStateCullMode = *(RwCullMode*)(0xC4028C);
static bool& gStoredRenderStateZTestEnable = *(bool*)(0xC40290);
static bool& gStoredRenderStateZWriteEnable = *(bool*)(0xC40294);
static RwShadeMode& gStoredRenderStateShadeMode = *(RwShadeMode*)(0xC40298);
static bool& gStoredRenderStateVertexAlphaEnable = *(bool*)(0xC4029C);
static RwTextureAddressMode& gStoredRenderStateTextureAddress = *(RwTextureAddressMode*)(0xC402A0);
static RwTextureFilterMode& gStoredRenderStateTextureFilter = *(RwTextureFilterMode*)(0xC402A4);

// see NightVision
static float& fRasterFrontBufferWidth = *(float*)0xC4015C;
static float& fRasterFrontBufferHeight = *(float*)0xC40160;

float& CPostEffects::m_VisionFXDayNightBalance = *(float*)0x8D50A4; // 1.0f

bool& CPostEffects::m_bInfraredVision = *(bool*)0xC402B9;
int& CPostEffects::m_InfraredVisionGrainStrength = *(int*)0x8D50B4;     // 64
float& CPostEffects::m_fInfraredVisionFilterRadius = *(float*)0x8D50B8; // 3B449BA6h
// float& CPostEffects::m_fInfraredVisionSwitchOnFXCount;
RwRGBA& CPostEffects::m_InfraredVisionCol = *(RwRGBA*)0x8D50CC;                    // FF 3C 28 6E
RwRGBA& CPostEffects::m_InfraredVisionMainCol = *(RwRGBA*)0x8D50D0;                // FF C8 00 64
RwRGBAReal& CPostEffects::m_fInfraredVisionHeatObjectCol = *(RwRGBAReal*)0x8D50BC; // {1.0f, 0.0f, 0.0f, 1.0f}

// see InfraredVision
RwTexCoords& UV_0 = *(RwTexCoords*)0xC40164;
RwTexCoords& UV_1 = *(RwTexCoords*)0xC4016C;

bool& CPostEffects::m_waterEnable = *(bool*)0xC402D3;
float& CPostEffects::m_waterStrength = *(float*)0x8D512C; // 64
float& CPostEffects::m_waterSpeed = *(float*)0x8D5138;    // dd 3AC49BA6h
float& CPostEffects::m_waterFreq = *(float*)0x8D513C;     // dd 3D23D70Ah
RwRGBA& CPostEffects::m_waterCol = *(RwRGBA*)0x8D5140;    // {64, 64, 64, 64}

RwIm2DVertex(&cc_vertices) = *(RwIm2DVertex*)0xC400D8;                 // always nullptr
RwImVertexIndex (&cc_indices)[12] = *(RwImVertexIndex(*)[12])0x8D5174; // {0, 1, 2, 0, 2, 3, 0, 1, 2, 0, 2, 3};

int& dword_C400E8 = *(int*)0xC400E8;
int& dword_C40104 = *(int*)0xC40104;
int& dword_C40120 = *(int*)0xC40120;
int& dword_C4013C = *(int*)0xC4013C;

float (&dword_C3FE08_X)[180] = *(float (*)[180])0xC3FE08;
float (&dword_C3FB38_Y)[180] = *(float (*)[180])0xC3FE08;
float (&dword_C3F868_SPEED)[180] = *(float (*)[180])0xC3FE08;

void CPostEffects::InjectHooks() {
//    ReversibleHooks::Install("CPostEffects", "Initialise", 0x704630, &CPostEffects::Initialise);
    ReversibleHooks::Install("CPostEffects", "Close", 0x7010C0, &CPostEffects::Close);
//    ReversibleHooks::Install("CPostEffects", "DoScreenModeDependentInitializations", 0x7046D0, &CPostEffects::DoScreenModeDependentInitializations);
//    ReversibleHooks::Install("CPostEffects", "SetupBackBufferVertex", 0x7043D0, &CPostEffects::SetupBackBufferVertex);
    ReversibleHooks::Install("CPostEffects", "Update", 0x7046A0, &CPostEffects::Update);
    ReversibleHooks::Install("CPostEffects", "DrawQuad", 0x700EC0, &CPostEffects::DrawQuad);
//    ReversibleHooks::Install("CPostEffects", "DrawQuadSetDefaultUVs", 0x0, &CPostEffects::DrawQuadSetDefaultUVs);
//    ReversibleHooks::Install("CPostEffects", "DrawQuadSetUVs", 0x0, &CPostEffects::DrawQuadSetUVs);
//    ReversibleHooks::Install("CPostEffects", "FilterFX_StoreAndSetDayNightBalance", 0x7034B0, &CPostEffects::FilterFX_StoreAndSetDayNightBalance);
//    ReversibleHooks::Install("CPostEffects", "FilterFX_RestoreDayNightBalance", 0x7034D0, &CPostEffects::FilterFX_RestoreDayNightBalance);
//    ReversibleHooks::Install("CPostEffects", "ImmediateModeFilterStuffInitialize", 0x703CC0, &CPostEffects::ImmediateModeFilterStuffInitialize);
    ReversibleHooks::Install("CPostEffects", "ImmediateModeRenderStatesSet", 0x700D70, &CPostEffects::ImmediateModeRenderStatesSet);
    ReversibleHooks::Install("CPostEffects", "ImmediateModeRenderStatesStore", 0x700CC0, &CPostEffects::ImmediateModeRenderStatesStore);
    ReversibleHooks::Install("CPostEffects", "ImmediateModeRenderStatesReStore", 0x700E00, &CPostEffects::ImmediateModeRenderStatesReStore);
//    ReversibleHooks::Install("CPostEffects", "RasterCreatePostEffects", 0x0, &CPostEffects::RasterCreatePostEffects);
    ReversibleHooks::Install("CPostEffects", "ScriptCCTVSwitch", 0x7011B0, &CPostEffects::ScriptCCTVSwitch);
    ReversibleHooks::Install("CPostEffects", "ScriptDarknessFilterSwitch", 0x701170, &CPostEffects::ScriptDarknessFilterSwitch);
    ReversibleHooks::Install("CPostEffects", "ScriptHeatHazeFXSwitch", 0x701160, &CPostEffects::ScriptHeatHazeFXSwitch);
    ReversibleHooks::Install("CPostEffects", "ScriptInfraredVisionSwitch", 0x701140, &CPostEffects::ScriptInfraredVisionSwitch);
    ReversibleHooks::Install("CPostEffects", "ScriptNightVisionSwitch", 0x701120, &CPostEffects::ScriptNightVisionSwitch);
    ReversibleHooks::Install("CPostEffects", "ScriptResetForEffects", 0x7010F0, &CPostEffects::ScriptResetForEffects);
//    ReversibleHooks::Install("CPostEffects", "UnderWaterRipple", 0x7039C0, &CPostEffects::UnderWaterRipple);
//    ReversibleHooks::Install("CPostEffects", "UnderWaterRippleFadeToFX", 0x0, &CPostEffects::UnderWaterRippleFadeToFX);
//    ReversibleHooks::Install("CPostEffects", "HeatHazeFXInit", 0x701450, &CPostEffects::HeatHazeFXInit);
//    ReversibleHooks::Install("CPostEffects", "HeatHazeFX", 0x701780, &CPostEffects::HeatHazeFX);
    ReversibleHooks::Install("CPostEffects", "IsVisionFXActive", 0x7034F0, &CPostEffects::IsVisionFXActive);
//    ReversibleHooks::Install("CPostEffects", "NightVision", 0x7011C0, &CPostEffects::NightVision);
    ReversibleHooks::Install("CPostEffects", "NightVisionSetLights", 0x7012E0, &CPostEffects::NightVisionSetLights);
//    ReversibleHooks::Install("CPostEffects", "SetFilterMainColour", 0x703520, &CPostEffects::SetFilterMainColour);
    ReversibleHooks::Install("CPostEffects", "InfraredVision", 0x703F80, &CPostEffects::InfraredVision);
    ReversibleHooks::Install("CPostEffects", "InfraredVisionSetLightsForDefaultObjects", 0x701430, &CPostEffects::InfraredVisionSetLightsForDefaultObjects);
    ReversibleHooks::Install("CPostEffects", "InfraredVisionStoreAndSetLightsForHeatObjects", 0x701320, &CPostEffects::InfraredVisionStoreAndSetLightsForHeatObjects);
    ReversibleHooks::Install("CPostEffects", "InfraredVisionRestoreLightsForHeatObjects", 0x701410, &CPostEffects::InfraredVisionRestoreLightsForHeatObjects);
//    ReversibleHooks::Install("CPostEffects", "Fog", 0x704150, &CPostEffects::Fog);
//    ReversibleHooks::Install("CPostEffects", "CCTV", 0x702F40, &CPostEffects::CCTV);
//    ReversibleHooks::Install("CPostEffects", "Grain", 0x7037C0, &CPostEffects::Grain);
//    ReversibleHooks::Install("CPostEffects", "SpeedFX", 0x7030A0, &CPostEffects::SpeedFX);
//    ReversibleHooks::Install("CPostEffects", "DarknessFilter", 0x702F00, &CPostEffects::DarknessFilter);
//    ReversibleHooks::Install("CPostEffects", "ColourFilter", 0x703650, &CPostEffects::ColourFilter);
//    ReversibleHooks::Install("CPostEffects", "Radiosity", 0x702080, &CPostEffects::Radiosity);
//    ReversibleHooks::Install("CPostEffects", "Render", 0x7046E0, &CPostEffects::Render);
}

// 0x704630
void CPostEffects::Initialise() {
    plugin::Call<0x704630>();
}

// 0x7010C0
void CPostEffects::Close() {
    RwRasterDestroy(m_pGrainRaster);
    if (pRasterFrontBuffer) {
        RwRasterDestroy(pRasterFrontBuffer);
        pRasterFrontBuffer = nullptr;
    }
}

// 0x7046D0
void CPostEffects::DoScreenModeDependentInitializations() {
    ImmediateModeFilterStuffInitialize();
    HeatHazeFXInit();
}

// 0x7043D0
void CPostEffects::SetupBackBufferVertex() {
    plugin::Call<0x7043D0>();
    return;

    // untested
    RwRaster* pRaster = RwCameraGetRaster(Scene.m_pRwCamera);
    // https://www.felixcloutier.com/x86/fyl2x
    // FYL2X — Compute y ∗ log2x
    // log(2.0) = 0.69314718055994528623

    // get maximum 2^N dimensions
    int width = (int)log2((float)RwRasterGetWidth(pRaster));
    width = (int)pow(2.0f, width);

    int height = (int)log2((float)RwRasterGetHeight(pRaster));
    height = (int)pow(2.0f, height);

    if (pRasterFrontBuffer) {
        if (width != RwRasterGetWidth(pRasterFrontBuffer) || height != RwRasterGetHeight(pRasterFrontBuffer)) {
            // cc_vertices = nullptr; // see LABEL_7

            RwRasterDestroy(pRasterFrontBuffer);
            pRasterFrontBuffer = nullptr;
        }
    }

    pRasterFrontBuffer = RwRasterCreate(width, height, RwRasterGetDepth(pRaster), rwRASTERTYPETEXTURE | rwRASTERTYPEZBUFFER);
    if (!pRasterFrontBuffer) {
        printf("Error subrastering");
        RwRasterDestroy(pRasterFrontBuffer);
        pRasterFrontBuffer = nullptr;
    }

    /* unused
    LABEL_7:
    dword_C400DC = 0;
    dword_C400E0 = RwIm2DGetNearScreenZ();

    v10 = 1.0 / RwCameraGetNearClipPlane(Scene.m_pRwCamera);

    dword_C400F4 = 0;
    flt_C400E4 = v10;
    flt_C400EC = 0.5 / width;
    flt_C400F0 = 0.5f / height;
    flt_C400F8 = height;
    dword_C400FC = RwIm2DGetNearScreenZ();

    flt_C40100 = 1.0 / Scene.m_pRwCamera->nearPlane;
    flt_C40108 = 0.5 / width;
    flt_C4010C = (height + 0.5) / height;
    flt_C40110 = width;
    flt_C40114 = height;
    dword_C40118 = RwIm2DGetNearScreenZ();

    dword_C40130 = 0;
    flt_C4011C = v10;
    flt_C40124 = (width + 0.5f) / width;
    flt_C40128 = (height + 0.5) / height;
    flt_C4012C = width;
    dword_C40134 = RwIm2DGetNearScreenZ();

    dword_C40140 = (width + 0.5f) / width;
    dword_C40144 = 0.5f / height;
    flt_C40138 = v10;
    */

    if (pRasterFrontBuffer) {
        DoScreenModeDependentInitializations();
    }
}

// 0x7046A0
void CPostEffects::Update() {
    m_bRainEnable = CWeather::Rain > 0.0f;
    if (!pRasterFrontBuffer) {
        SetupBackBufferVertex();
    }
}

// 0x700EC0
void CPostEffects::DrawQuad(float x1, float y1, float x2, float y2, char red, unsigned int green, unsigned int blue, char alpha, RwRaster* raster) {
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, raster);

    auto color = CRGBA(red, green, blue, alpha).ToIntARGB();

    vertexGroup[0].x = x1;
    vertexGroup[0].y = y1;
    vertexGroup[0].z = ms_imf;
    vertexGroup[0].emissiveColor = color;

    vertexGroup[1].x = x1 + x2;
    vertexGroup[1].y = y1;
    vertexGroup[1].z = ms_imf;
    vertexGroup[1].emissiveColor = color;

    vertexGroup[2].x = x1;
    vertexGroup[2].y = y1 + y2;
    vertexGroup[2].z = ms_imf;
    vertexGroup[2].emissiveColor = color;

    vertexGroup[3].x = x1 + x2;
    vertexGroup[3].y = y1 + y2;
    vertexGroup[3].z = ms_imf;
    vertexGroup[3].emissiveColor = color;

    RwIm2DRenderPrimitive(rwPRIMTYPETRISTRIP, vertexGroup, 4);
}

// 0x
void CPostEffects::DrawQuadSetDefaultUVs() {
    DrawQuadSetUVs(0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f);
}

// unused
// 0x700FE0
void CPostEffects::DrawQuadSetPixelUVs(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8) {
    float x = 1.0f / fRasterFrontBufferWidth;
    float y = 1.0f / fRasterFrontBufferHeight;

    vertexGroup[0].u = x * a1;
    vertexGroup[0].v = a2 * y;

    vertexGroup[1].u = x * a3;
    vertexGroup[1].v = a4 * y;

    vertexGroup[2].u = x * a7;
    vertexGroup[2].v = a8 * y;

    vertexGroup[3].u = x * a5;
    vertexGroup[3].v = y * a6;
}

// 0x
void CPostEffects::DrawQuadSetUVs(float a1, float a2, float a3, float a4, float a5, float a6, float a7, float a8) {}

// 0x7034B0
void CPostEffects::FilterFX_StoreAndSetDayNightBalance() {
    plugin::Call<0x7034B0>();
}

// 0x7034D0
void CPostEffects::FilterFX_RestoreDayNightBalance() {
    return plugin::Call<0x7034D0>();
}

// 0x703CC0
void CPostEffects::ImmediateModeFilterStuffInitialize() {
    plugin::Call<0x703CC0>();
}

// 0x700D70
void CPostEffects::ImmediateModeRenderStatesSet() {
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)rwCULLMODECULLNONE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)rwSHADEMODEGOURAUD);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)true);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)rwTEXTUREADDRESSCLAMP);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERNEAREST);
}

// 0x700CC0
void CPostEffects::ImmediateModeRenderStatesStore() {
    RwRenderStateGet(rwRENDERSTATESRCBLEND, &gStoredRenderStateSrcBlend);
    RwRenderStateGet(rwRENDERSTATEDESTBLEND, &gStoredRenderStateDestBlend);
    RwRenderStateGet(rwRENDERSTATEFOGENABLE, &gStoredRenderStateFogEnable);
    RwRenderStateGet(rwRENDERSTATECULLMODE, &gStoredRenderStateCullMode);
    RwRenderStateGet(rwRENDERSTATEZTESTENABLE, &gStoredRenderStateZTestEnable);
    RwRenderStateGet(rwRENDERSTATEZWRITEENABLE, &gStoredRenderStateZWriteEnable);
    RwRenderStateGet(rwRENDERSTATESHADEMODE, &gStoredRenderStateShadeMode);
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &gStoredRenderStateVertexAlphaEnable);
    RwRenderStateGet(rwRENDERSTATETEXTUREADDRESS, &gStoredRenderStateTextureAddress);
    RwRenderStateGet(rwRENDERSTATETEXTUREFILTER, &gStoredRenderStateTextureFilter);
}

// 0x700E00
void CPostEffects::ImmediateModeRenderStatesReStore() {
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)gStoredRenderStateSrcBlend);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)gStoredRenderStateDestBlend);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)gStoredRenderStateFogEnable);
    RwRenderStateSet(rwRENDERSTATECULLMODE, (void*)gStoredRenderStateCullMode);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)gStoredRenderStateZTestEnable);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)gStoredRenderStateZWriteEnable);
    RwRenderStateSet(rwRENDERSTATESHADEMODE, (void*)gStoredRenderStateShadeMode);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)gStoredRenderStateVertexAlphaEnable);
    RwRenderStateSet(rwRENDERSTATETEXTUREADDRESS, (void*)gStoredRenderStateTextureAddress);
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)gStoredRenderStateTextureFilter);
}

// 0x
void CPostEffects::RasterCreatePostEffects(RwRect rect) {}

// 0x7011B0
void CPostEffects::ScriptCCTVSwitch(bool enable) {
    m_bCCTV = enable;
}

// 0x701170
void CPostEffects::ScriptDarknessFilterSwitch(bool enable, int alpha) {
    m_bDarknessFilter = enable;
    if (alpha == 255) {
        m_DarknessFilterAlpha = m_DarknessFilterAlphaDefault;
    } else {
        m_DarknessFilterAlpha = clamp(0, alpha, 255);
    }
}

// 0x701160
void CPostEffects::ScriptHeatHazeFXSwitch(bool enable) {
    m_bHeatHazeFX = enable;
}

// 0x701140
void CPostEffects::ScriptInfraredVisionSwitch(bool enable) {
    if (enable) {
        m_bInfraredVision = true;
        m_bNightVision = false;
    } else {
        m_bInfraredVision = false;
    }
}

// 0x701120
void CPostEffects::ScriptNightVisionSwitch(bool enable) {
    if (enable) {
        m_bNightVision = true;
        m_bInfraredVision = false;
    } else {
        m_bNightVision = false;
    }
}

// 0x7010F0
void CPostEffects::ScriptResetForEffects() {
    m_bNightVision = false;
    m_bInfraredVision = false;
    m_bHeatHazeFX = false;
    m_bDarknessFilter = false;
    m_bCCTV = false;
    CWaterLevel::m_bWaterFogScript = true;
}

// 0x7039C0
void CPostEffects::UnderWaterRipple(RwRGBA a1, float a2, float a3, int a4, float a5, float a6) {
    plugin::Call<0x7039C0, RwRGBA, float, float, int, float, float>(a1, a2, a3, a4, a5, a6);
}

// unused
// 0x0
void CPostEffects::UnderWaterRippleFadeToFX() {}

// 0x701450
void CPostEffects::HeatHazeFXInit() {
    plugin::Call<0x701450>();

    /*
    if (m_HeatHazeFXType == m_HeatHazeFXTypeLast) {
        return;
    }

    switch (m_HeatHazeFXType) {
    case HEAT_HAZE_0:
        m_HeatHazeFXIntensity = 80;
        m_HeatHazeFXRandomShift = 0;
        m_HeatHazeFXSpeedMin = 12;
        m_HeatHazeFXSpeedMax = 18;
        m_HeatHazeFXScanSizeX = flt_859520 * 47.0f;
        m_HeatHazeFXScanSizeY = flt_859524 * 47.0f;
        m_HeatHazeFXRenderSizeX = flt_859520 * 50.0f;
        m_HeatHazeFXRenderSizeY = flt_859524 * 50.0f;
        break;
    case HEAT_HAZE_1:
        m_HeatHazeFXIntensity = 32;
        m_HeatHazeFXRandomShift = 0;
        m_HeatHazeFXSpeedMin = 6;
        m_HeatHazeFXSpeedMax = 10;
        m_HeatHazeFXScanSizeX = flt_859520 * 100.0f;
        m_HeatHazeFXScanSizeY = flt_859524 * 52.0f;
        m_HeatHazeFXRenderSizeX = flt_859520 * 100.0f;
        m_HeatHazeFXRenderSizeY = flt_859524 * 60.0f;
        break;
    case HEAT_HAZE_2:
        m_HeatHazeFXIntensity = 32;
        m_HeatHazeFXRandomShift = 0;
        m_HeatHazeFXSpeedMin = 4;
        m_HeatHazeFXSpeedMax = 8;
        m_HeatHazeFXScanSizeX = flt_859520 * 70.0f;
        m_HeatHazeFXScanSizeY = flt_859524 * 70.0f;
        m_HeatHazeFXRenderSizeX = flt_859520 * 80.0f;
        m_HeatHazeFXRenderSizeY = flt_859524 * 80.0f;
        break;
    case HEAT_HAZE_3:
        m_HeatHazeFXRandomShift = 1;
        m_HeatHazeFXIntensity = 150;
        m_HeatHazeFXSpeedMin = 5;
        m_HeatHazeFXSpeedMax = 8;
        m_HeatHazeFXScanSizeX = flt_859520 * 60.0f;
        m_HeatHazeFXScanSizeY = flt_859524 * 24.0f;
        m_HeatHazeFXRenderSizeX = flt_859520 * 62.0f;
        m_HeatHazeFXRenderSizeY = flt_859524 * 24.0f;
        break;
    case HEAT_HAZE_4:
        m_HeatHazeFXRandomShift = 1;
        m_HeatHazeFXIntensity = 150;
        m_HeatHazeFXSpeedMin = 5;
        m_HeatHazeFXSpeedMax = 8;
        m_HeatHazeFXScanSizeX = flt_859520 * 60.0f;
        m_HeatHazeFXScanSizeY = flt_859524 * 24.0f;
        m_HeatHazeFXRenderSizeX = flt_859520 * 62.0f;
        m_HeatHazeFXRenderSizeY = flt_859524 * 24.0f;
        break;
    default:
        break;
    }
    m_HeatHazeFXTypeLast = m_HeatHazeFXType;

    double x = flt_858B14 * pRasterFrontBuffer->width - m_HeatHazeFXScanSizeX;
    double y = flt_858B14 * pRasterFrontBuffer->height - m_HeatHazeFXScanSizeY;
    double speed = flt_858B14 * (m_HeatHazeFXSpeedMax - m_HeatHazeFXSpeedMin) + m_HeatHazeFXSpeedMin;
    for (int i = 0; i < 180; i++) {
      dword_C3FE08_X[i] = rand() * x;
      dword_C3FB38_Y[i] = rand() * y;
      dword_C3F868_SPEED[i] = rand() * speed;
    }
    */
}

// 0x701780
void CPostEffects::HeatHazeFX(float a1, bool a2) {
    plugin::Call<0x701780, float, bool>(a1, a2);
}

// 0x7034F0
bool CPostEffects::IsVisionFXActive() {
    return !m_bInCutscene && (m_bNightVision || m_bInfraredVision);
}

// 0x7011C0
void CPostEffects::NightVision() {
    plugin::Call<0x7011C0>();
    return;

    // fix fade-in
    if (m_fNightVisionSwitchOnFXCount > 0.0f) {
        m_fNightVisionSwitchOnFXCount -= CTimer::ms_fTimeStep;
        if (m_fNightVisionSwitchOnFXCount <= 0.0f) {
            m_fNightVisionSwitchOnFXCount = 0.0f;
        }

        ImmediateModeRenderStatesStore();
        ImmediateModeRenderStatesSet();
        RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
        RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);

        for (int i = 0, end = m_fNightVisionSwitchOnFXCount; i < end; i++) {
            DrawQuad(0.0f, 0.0f, fRasterFrontBufferWidth, fRasterFrontBufferHeight, 8, 8, 8, 255, pVisionFXRaster);
        }

        ImmediateModeRenderStatesReStore();
    }

    ImmediateModeRenderStatesStore();
    ImmediateModeRenderStatesSet();
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDZERO);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDSRCCOLOR);
    DrawQuad(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 32, 255, 32, 255, nullptr);
    ImmediateModeRenderStatesReStore();
}

// 0x7012E0
void CPostEffects::NightVisionSetLights() {
    if (m_bNightVision && !m_bInCutscene) {
        SetLightsForNightVision();
    }
}

// 0x703520
void CPostEffects::SetFilterMainColour(RwRGBA a1, RwRGBA a2) {
    plugin::Call<0x703520, RwRGBA, RwRGBA>(a1, a2);
    return;

    // result not equal to original function (very close, but different)
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERNEAREST);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, pRasterFrontBuffer);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);

    /*
    dword_C400E8 = BYTE2(a2) | ((BYTE1(a2) | (((unsigned __int8)a2 | (HIBYTE(a2) << 8)) << 8)) << 8);
    dword_C40104 = dword_C400E8;
    dword_C40120 = dword_C400E8;
    dword_C4013C = dword_C400E8;
    */

    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDDESTALPHA);
    RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, &cc_vertices, 4, cc_indices, 6);

    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)nullptr);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

// 0x703F80
void CPostEffects::InfraredVision(RwRGBA color, RwRGBA colorMain) {
    //    plugin::Call<0x703F80, RwRGBA, RwRGBA>(a1, a2);

    ImmediateModeRenderStatesStore();
    ImmediateModeRenderStatesSet();

    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);

    float radius = m_fInfraredVisionFilterRadius * 100.0f;
    int i = 0, j;
    float xy;
    do {
        j = i + 1;

        vertexGroup[0].u = UV_0.u;
        vertexGroup[0].v = UV_0.v;

        vertexGroup[1].u = UV_1.u;
        vertexGroup[1].v = UV_0.v;

        vertexGroup[2].u = UV_0.u;
        vertexGroup[2].v = UV_1.v;

        vertexGroup[3].u = UV_1.u;
        vertexGroup[3].v = UV_1.v;

        xy = (float)(j) * radius;
        DrawQuad(
            -xy,
            -xy,
            SCREEN_WIDTH + xy + xy,
            SCREEN_HEIGHT + xy + xy,
            color.red,
            color.green,
            color.blue,
            255,
            pVisionFXRaster
        );
        i = j;
    } while (j < 4);

    vertexGroup[0].u = 0.0f;
    vertexGroup[0].v = 0.0f;

    vertexGroup[1].u = 1.0f;
    vertexGroup[1].v = 0.0f;

    vertexGroup[2].u = 0.0f;
    vertexGroup[2].v = 1.0f;

    vertexGroup[3].u = 1.0f;
    vertexGroup[3].v = 1.0f;

    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDZERO);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDSRCCOLOR);

    DrawQuad(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT, 255, 64, 255, 255, nullptr);
    ImmediateModeRenderStatesReStore();
    SetFilterMainColour(color, colorMain);
}

// 0x701430
void CPostEffects::InfraredVisionSetLightsForDefaultObjects() {
    if (m_bInfraredVision && !m_bInCutscene) {
        SetLightsForInfraredVisionDefaultObjects();
    }
}

// unused
// 0x701300
void CPostEffects::InfraredVisionSetLightsForHeatObjects() {
    if (m_bInfraredVision && !m_bInCutscene) {
        SetLightsForInfraredVisionHeatObjects();
    }
}

// 0x701320
void CPostEffects::InfraredVisionStoreAndSetLightsForHeatObjects(CPed* ped) {
    if (!m_bInfraredVision || m_bInCutscene) {
        return;
    }

    // store color
    RwUInt8 red = m_fInfraredVisionHeatObjectCol.red;
    RwUInt8 green = m_fInfraredVisionHeatObjectCol.green;
    RwUInt8 blue = m_fInfraredVisionHeatObjectCol.blue;
    RwUInt8 alpha = m_fInfraredVisionHeatObjectCol.alpha;

    if (ped->m_nPedState == PEDSTATE_DEAD) {
        int v8 = CTimer::m_snTimeInMilliseconds - ped->m_nDeathTime;
        if (v8 < 0)
            v8 = ped->m_nDeathTime - CTimer::m_snTimeInMilliseconds;

        float v6 = (float)v8 * 0.0001f;
        m_fInfraredVisionHeatObjectCol.red = m_fInfraredVisionHeatObjectCol.red - v6;
        if (m_fInfraredVisionHeatObjectCol.red < 0.0f) {
            m_fInfraredVisionHeatObjectCol.red = 0.0f;
        }
        m_fInfraredVisionHeatObjectCol.green = 0.0f;
        m_fInfraredVisionHeatObjectCol.blue = m_fInfraredVisionHeatObjectCol.blue + v6;
        if (m_fInfraredVisionHeatObjectCol.blue > 1.0f)
            m_fInfraredVisionHeatObjectCol.blue = 1.0f;
    }
    StoreAndSetLightsForInfraredVisionHeatObjects();

    // restore color
    m_fInfraredVisionHeatObjectCol.red = red;
    m_fInfraredVisionHeatObjectCol.green = green;
    m_fInfraredVisionHeatObjectCol.blue = blue;
    m_fInfraredVisionHeatObjectCol.alpha = alpha;
}

// 0x701410
void CPostEffects::InfraredVisionRestoreLightsForHeatObjects() {
    if (m_bInfraredVision && !m_bInCutscene) {
        RestoreLightsForInfraredVisionHeatObjects();
    }
}

// 0x704150
void CPostEffects::Fog() {
    plugin::Call<0x704150>();
}

// 0x702F40
void CPostEffects::CCTV() {
    plugin::Call<0x702F40>();
}

// 0x7037C0
void CPostEffects::Grain(int strength, bool a2) {
    plugin::Call<0x7037C0, int, bool>(strength, a2);
}

// 0x7030A0
void CPostEffects::SpeedFX(float speed) {
    plugin::Call<0x7030A0, float>(speed);
}

// 0x702F00
void CPostEffects::DarknessFilter(int a1) {
    plugin::Call<0x702F00, int>(a1);
}

// 0x703650
void CPostEffects::ColourFilter(int pass1, int pass2) {
    plugin::Call<0x703650>();
    return;

    // result not equal to original function
    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERNEAREST);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)pRasterFrontBuffer);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDONE);

    dword_C400E8 = pass1 | ((pass1 | ((pass1 | (pass1 << 8)) << 8)) << 8);
    dword_C40104 = dword_C400E8;
    dword_C40120 = dword_C400E8;
    dword_C4013C = dword_C400E8;
    RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, &cc_vertices, 4, cc_indices, 6);

    dword_C400E8 = pass2 | ((pass2 | ((pass2 | (pass2 << 8)) << 8)) << 8);
    dword_C40104 = dword_C400E8;
    dword_C40120 = dword_C400E8;
    dword_C4013C = dword_C400E8;
    RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, &cc_vertices, 4, cc_indices, 6);

    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)nullptr);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

// 0x702080
void CPostEffects::Radiosity(int a1, int a2, int a3, int a4) {
    plugin::Call<0x702080>();
}

//0x619450
void RsCameraBeginUpdate(RwCamera* camera) {
    plugin::Call<0x619450, RwCamera*>(camera);
}

// 0x7046E0
void CPostEffects::Render() {
    plugin::Call<0x7046E0>();
}
