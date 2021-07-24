#include "StdInc.h"

uint32_t& CWaterLevel::m_nWaterConfiguration = *(uint32_t*)0xC228A0;
uint32_t& CWaterLevel::m_nWaterTimeOffset = *(uint32_t*)0xC228A4;
float* CWaterLevel::faWaveMultipliersX = (float*)0x8D38C8;
float* CWaterLevel::faWaveMultipliersY = (float*)0x8D38E8;

RwRaster* CWaterLevel::waterclear256Raster = (RwRaster*)0xC228A8;
RwTexture* CWaterLevel::texWaterclear256 = (RwTexture*)0xC228AC;
RwRaster* CWaterLevel::seabd32Raster = (RwRaster*)0xC228B0;
RwTexture* CWaterLevel::texSeabd32 = (RwTexture*)0xC228B4;
RwRaster* CWaterLevel::waterwakeRaster = (RwRaster*)0xC228B8;
RwTexture* CWaterLevel::texWaterwake = (RwTexture*)0xC228BC;

bool& CWaterLevel::m_bWaterFog = *(bool*)0x8D37D4;
bool& CWaterLevel::m_bWaterFogScript = *(bool*)0x8D37D5;

void CWaterLevel::InjectHooks()
{
    ReversibleHooks::Install("CWaterLevel", "GetWaterLevel", 0x6EB690, &CWaterLevel::GetWaterLevel);
    ReversibleHooks::Install("CWaterLevel", "SyncWater", 0x6E76E0, &CWaterLevel::SyncWater);
    ReversibleHooks::Install("CWaterLevel", "CalculateWavesOnlyForCoordinate", 0x6E7210, &CWaterLevel::CalculateWavesOnlyForCoordinate);
    //ReversibleHooks::Install("CWaterLevel", "AddWaveToResult", 0x6E81E0, &CWaterLevel::AddWaveToResult);
    //ReversibleHooks::Install("CWaterLevel", "GetWaterLevelNoWaves", 0x6E8580, &CWaterLevel::GetWaterLevelNoWaves);
}

void CWaterLevel::AddWaveToResult(float x, float y, float* pfWaterLevel, float fUnkn1, float fUnkn2, CVector* pVecNormal)
{
    plugin::Call<0x6E81E0, float, float, float*, float, float, CVector*>(x, y, pfWaterLevel, fUnkn1, fUnkn2, pVecNormal);
    return;

    /*if (!ReversibleHooks::Hooked("CWaterLevel", "ProcessBuoyancy")) {
        plugin::Call<0x6E81E0, float, float, float*, float, float, CVector*>(x, y, pfWaterLevel, fUnkn1, fUnkn2, pVecNormal);
        return;
    }*/
}

void CWaterLevel::CalculateWavesOnlyForCoordinate(int x, int y, float fUnkn1, float fUnkn2, float* fOutWave)
{
    if (x < 0)
        x = -x;

    if (y < 0)
        y = -y;

    auto xInd = (x / 2) & 0x7;
    auto yInd = (y / 2) & 0x7;

    auto fWaveMultiplier = CWeather::Wavyness * CWaterLevel::faWaveMultipliersX[xInd] * CWaterLevel::faWaveMultipliersY[yInd];
    auto fX = static_cast<float>(x);
    auto fY = static_cast<float>(y);

    auto iTimeOffset = CTimer::m_snTimeInMilliseconds - CWaterLevel::m_nWaterTimeOffset;
    const auto fTwoPiToChar = 256.0F / TWO_PI;

    const auto fLowFreqOffsetMult = TWO_PI / 5000.0F;
    const auto fLowFreqMult = TWO_PI / 64.0F;
    auto fIndex = (static_cast<float>(iTimeOffset % 5000U) * fLowFreqOffsetMult + (fX + fY) * fLowFreqMult) * fTwoPiToChar;
    unsigned char uiIndex = static_cast<unsigned char>(fIndex) + 1;
    float fLowFreqWaves = CMaths::ms_SinTable[uiIndex] * 2.0F * fWaveMultiplier * fUnkn1;
    *fOutWave += fLowFreqWaves;

    const auto fMidFreqOffsetMult = TWO_PI / 3500.0F;
    const auto fMidFreqXMult = TWO_PI / 26.0F;
    const auto fMidFreqYMult = TWO_PI / 52.0F;
    fIndex = (static_cast<float>(iTimeOffset % 3500U) * fMidFreqOffsetMult + (fX * fMidFreqXMult) + (fY * fMidFreqYMult)) * fTwoPiToChar;
    uiIndex = static_cast<unsigned char>(fIndex) + 1;
    float fMidFreqWaves = CMaths::ms_SinTable[uiIndex] * 1.0F * fWaveMultiplier * fUnkn2;
    *fOutWave += fMidFreqWaves;

    const auto fHighFreqOffsetMult = TWO_PI / 3000.0F;
    const auto fHighFreqYMult = TWO_PI / 20.0F;
    fIndex = (static_cast<float>(iTimeOffset % 3000U) * fHighFreqOffsetMult + (fY * fHighFreqYMult)) * fTwoPiToChar;
    uiIndex = static_cast<unsigned char>(fIndex) + 1;
    float fHighFreqWaves = CMaths::ms_SinTable[uiIndex] * 0.5F * fWaveMultiplier * fUnkn2;
    *fOutWave += fHighFreqWaves;
}

bool CWaterLevel::GetWaterDepth(CVector const& vecPos, float* pOutWaterDepth, float* pOutWaterLevel, float* pOutGroundLevel)
{
    return plugin::CallAndReturn<bool, 0x6EA960, CVector const&, float*, float*, float*>
        (vecPos, pOutWaterDepth, pOutWaterLevel, pOutGroundLevel);
}

bool CWaterLevel::GetWaterLevel(float x, float y, float z, float* pOutWaterLevel, unsigned char bTouchingWater, CVector* pVecNormals)
{
    float fUnkn1, fUnkn2;
    if (!CWaterLevel::GetWaterLevelNoWaves(x, y, z, pOutWaterLevel, &fUnkn1, &fUnkn2))
        return false;

    if ((*pOutWaterLevel - z > 3.0F) && !bTouchingWater) {
        *pOutWaterLevel = 0.0F;
        return false;
    }

    CWaterLevel::AddWaveToResult(x, y, pOutWaterLevel, fUnkn1, fUnkn2, pVecNormals);
    return true;
}

bool CWaterLevel::GetWaterLevelNoWaves(float x, float y, float z, float* pOutWaterLevel, float* fUnkn1, float* fUnkn2) {
    return plugin::CallAndReturn<bool, 0x6E8580, float, float, float, float*, float*, float*>(x, y, z, pOutWaterLevel, fUnkn1, fUnkn2);
}

void CWaterLevel::SyncWater()
{
    CWaterLevel::m_nWaterTimeOffset = CTimer::m_snTimeInMilliseconds;
}

// 0x6EAE80
void CWaterLevel::WaterLevelInitialise() {
    plugin::Call<0x6EAE80>();
}

// 0x6EB710
void CWaterLevel::PreRenderWater() {
    plugin::Call<0x6EB710>();
}

// 0x6EF650
void CWaterLevel::RenderWater() {
    plugin::Call<0x6EF650>();
}
