#include "StdInc.h"
#include "WaterLevel.h"

void CWaterLevel::InjectHooks() {
    RH_ScopedClass(CWaterLevel);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(Shutdown, 0x6E59E0, { .reversed = false });
    RH_ScopedGlobalInstall(RenderWaterTriangle, 0x6EE240, { .reversed = false });
    RH_ScopedGlobalInstall(RenderFlatWaterTriangle, 0x6EE080, { .reversed = false });
    RH_ScopedGlobalInstall(RenderBoatWakes, 0x6ED9A0, { .reversed = false });
    RH_ScopedGlobalInstall(SplitWaterTriangleAlongXLine, 0x6ECF00, { .reversed = false });
    RH_ScopedGlobalInstall(RenderWaterRectangle, 0x6EC5D0, { .reversed = false });
    RH_ScopedGlobalInstall(RenderFlatWaterRectangle, 0x6EBEC0, { .reversed = false });
    RH_ScopedGlobalInstall(SplitWaterRectangleAlongXLine, 0x6EB810, { .reversed = false });
    RH_ScopedGlobalInstall(PreRenderWater, 0x6EB710, { .reversed = false });
    RH_ScopedOverloadedInstall(GetWaterLevel, "", 0x6EB690, bool(*)(float, float, float, float*, uint8, CVector*));
    RH_ScopedGlobalInstall(WaterLevelInitialise, 0x6EAE80, { .reversed = false });
    RH_ScopedGlobalInstall(SetUpWaterFog, 0x6EA9F0, { .reversed = false });
    RH_ScopedGlobalInstall(RenderWakeSegment, 0x6EA260, { .reversed = false });
    RH_ScopedGlobalInstall(FindNearestWaterAndItsFlow, 0x6E9D70, { .reversed = false });
    RH_ScopedGlobalInstall(GetWaterLevelNoWaves, 0x6E8580, { .reversed = false });
    RH_ScopedGlobalInstall(RenderWaterFog, 0x6E7760, { .reversed = false });
    RH_ScopedGlobalInstall(CalculateWavesOnlyForCoordinate, 0x6E6EF0);
    RH_ScopedGlobalInstall(ScanThroughBlocks, 0x6E6D10, { .reversed = false });
    RH_ScopedGlobalInstall(SplitWaterTriangleAlongYLine, 0x6EE5A0, { .reversed = false });
    RH_ScopedGlobalInstall(RenderWater, 0x6EF650, { .reversed = false });
    RH_ScopedGlobalInstall(AddWaveToResult, 0x6E81E0, { .reversed = false });
}

// 0x6E59E0
void CWaterLevel::Shutdown() {
    plugin::Call<0x6E59E0>();
}

// 0x6E81E0
void CWaterLevel::AddWaveToResult(float x, float y, float* pfWaterLevel, float fUnkn1, float fUnkn2, CVector* pVecNormal)
{
    plugin::Call<0x6E81E0, float, float, float*, float, float, CVector*>(x, y, pfWaterLevel, fUnkn1, fUnkn2, pVecNormal);
}

// 0x6EE240
void CWaterLevel::RenderWaterTriangle(int32 a1, int32 a2, CRenPar a3, int32 a4, int32 a5, CRenPar a6, int32 a7, int32 a8, CRenPar a9) {
    plugin::Call<0x6EE240, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar>(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

// 0x6EE080
void CWaterLevel::RenderFlatWaterTriangle(int32 a1, int32 a2, CRenPar a3, int32 a4, int32 a5, CRenPar a6, int32 a7, int32 a8, CRenPar a9) {
    plugin::Call<0x6EE080, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar>(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

// 0x6ED9A0
void CWaterLevel::RenderBoatWakes() {
    plugin::Call<0x6ED9A0>();
}

// 0x6ECF00
void CWaterLevel::SplitWaterTriangleAlongXLine(int32 a7, int32 a1, int32 a2, CRenPar a4, int32 a5, int32 a6, CRenPar arg18, int32 a8, int32 a9, CRenPar a10) {
    plugin::Call<0x6ECF00, int32, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar>(a7, a1, a2, a4, a5, a6, arg18, a8, a9, a10);
}

// 0x6EC5D0
void CWaterLevel::RenderWaterRectangle(int32 a1, int32 a2, int32 a3, int32 a4, CRenPar a5, CRenPar a6, CRenPar a7, CRenPar a8) {
    plugin::Call<0x6EC5D0, int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar>(a1, a2, a3, a4, a5, a6, a7, a8);
}

// 0x6EBEC0
int32 CWaterLevel::RenderFlatWaterRectangle(int32 a1, int32 a2, int32 a3, int32 a4, CRenPar a5, CRenPar a6, CRenPar a7, CRenPar a8) {
    return plugin::CallAndReturn<int32, 0x6EBEC0, int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar>(a1, a2, a3, a4, a5, a6, a7, a8);
}

// 0x6EB810
void CWaterLevel::SplitWaterRectangleAlongXLine(int32 a1, int32 a2, int32 a3, int32 a4, int32 a5, CRenPar a6, CRenPar a7, CRenPar a8, CRenPar a9) {
    plugin::Call<0x6EB810, int32, int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar>(a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

// 0x6EB710
void CWaterLevel::PreRenderWater() {
    plugin::Call<0x6EB710>();
}

// 0x6EB690
bool CWaterLevel::GetWaterLevel(float x, float y, float z, float* pOutWaterLevel, uint8 bTouchingWater, CVector* pVecNormals) {
    float fUnkn1, fUnkn2;
    if (!GetWaterLevelNoWaves({x, y, z}, pOutWaterLevel, &fUnkn1, &fUnkn2))
        return false;

    if ((*pOutWaterLevel - z > 3.0F) && !bTouchingWater) {
        *pOutWaterLevel = 0.0F;
        return false;
    }

    AddWaveToResult(x, y, pOutWaterLevel, fUnkn1, fUnkn2, pVecNormals);
    return true;
}

// 0x6EAE80
void CWaterLevel::WaterLevelInitialise() {
    plugin::Call<0x6EAE80>();
}

// 0x6EA9F0
void CWaterLevel::SetUpWaterFog(int32 a1, int32 a2, int32 a3, int32 a4) {
    plugin::Call<0x6EA9F0, int32, int32, int32, int32>(a1, a2, a3, a4);
}

// 0x6EA260
int32 CWaterLevel::RenderWakeSegment(CVector2D & a1, CVector2D & a2, CVector2D & a3, CVector2D & a4, float & a5, float & a6, float & alphaMult1, float & alphaMult2, float & a9) {
    return plugin::CallAndReturn<int32, 0x6EA260, CVector2D &, CVector2D &, CVector2D &, CVector2D &, float &, float &, float &, float &, float &>(a1, a2, a3, a4, a5, a6, alphaMult1, alphaMult2, a9);
}

// 0x6E9D70
void CWaterLevel::FindNearestWaterAndItsFlow() {
    plugin::Call<0x6E9D70>();
}

// 0x6E8580
bool CWaterLevel::GetWaterLevelNoWaves(CVector pos, float * pOutWaterLevel, float * pOutBigWaves, float * pOutSmallWaves) {
    return plugin::CallAndReturn<bool, 0x6E8580, CVector, float *, float *, float *>(pos, pOutWaterLevel, pOutBigWaves, pOutSmallWaves);
}

bool CWaterLevel::GetWaterDepth(const CVector& vecPos, float* pOutWaterDepth, float* pOutWaterLevel, float* pOutGroundLevel)
{
    return plugin::CallAndReturn<bool, 0x6EA960, const CVector&, float*, float*, float*>
        (vecPos, pOutWaterDepth, pOutWaterLevel, pOutGroundLevel);
}

// 0x6E7760
void CWaterLevel::RenderWaterFog() {
    plugin::Call<0x6E7760>();
}

// 0x6E6EF0
void CWaterLevel::CalculateWavesOnlyForCoordinate(
    int32 x, int32 y,
    float lowFreqMult,
    float midHighFreqMult,
    float& outWave,
    float& colorMult,
    float& glare,
    CVector& vecNormal
)
{
    x = std::abs(x);
    y = std::abs(y);
    vecNormal = CVector{};

    constexpr auto tauToChar = 256.0f / TWO_PI;
    float waveMult = faWaveMultipliersX[(x / 2) % 8] * faWaveMultipliersX[(y / 2) % 8] * CWeather::Wavyness;
    float fX = (float)x, fY = (float)y;

    // literal AIDS code
    const auto CalculateWave = [&](int32 offset, float angularPeriodX, float angularPeriodY) {
        const float freqOffsetMult = TWO_PI / static_cast<float>(offset);
        const CVector2D w{ TWO_PI / angularPeriodX, TWO_PI / angularPeriodY };

        switch (offset) {
        case 5000: {
            auto step = (CTimer::GetTimeInMS() - m_nWaterTimeOffset) % offset;
            auto index = (step * freqOffsetMult + fX * w.x + fY * w.y) * tauToChar;

            outWave += CMaths::ms_SinTable[static_cast<uint8>(index) + 1] * 2.0f * waveMult * lowFreqMult;
            auto outNext = -(CMaths::ms_SinTable[static_cast<uint8>(index + 64.0f) + 1] * 2.0f * waveMult * lowFreqMult * w.x);
            vecNormal += { outNext, outNext, 1.0f };
            break;
        }
        case 3500: {
            auto step = (CTimer::GetTimeInMS() - m_nWaterTimeOffset) % offset;
            auto index = (step * freqOffsetMult + fX * w.x + fY * w.y) * tauToChar;

            outWave += CMaths::ms_SinTable[static_cast<uint8>(index) + 1] * 1.0f * waveMult * midHighFreqMult;
            auto outNext = CMaths::ms_SinTable[static_cast<uint8>(index + 64.0f) + 1];
            auto vAdd = outNext * waveMult * w.x * w.x;
            vecNormal += { vAdd, vAdd, 0.0f };
            break;
        }
        case 3000: {
            auto step = (CTimer::GetTimeInMS() - m_nWaterTimeOffset) % offset;
            auto index = (step * freqOffsetMult + fX * w.x + fY * w.y) * tauToChar;

            outWave += CMaths::ms_SinTable[static_cast<uint8>(index) + 1] * 0.5f * waveMult * midHighFreqMult;
            auto outNext = CMaths::ms_SinTable[static_cast<uint8>(index + 64.0f) + 1];
            vecNormal.x += waveMult * (outNext / 2.0f) * midHighFreqMult * (PI / 10.0f);
            break;
        }
        }
    };

    CalculateWave(5000, 64.0f, 64.0f);
    CalculateWave(3500, 26.0f, 52.0f);
    CalculateWave(3000,  0.0f, 20.0f);

    vecNormal.Normalise();
    auto v17 = (vecNormal.x + vecNormal.y + vecNormal.z) * 0.57700002f;

    colorMult = std::max(v17, 0.0f) * 0.65f + 0.27f;
    glare = std::clamp(8.0f * v17 - 5.0f, 0.0f, 0.99f) * CWeather::SunGlare;
}

// 0x6E7210
void CWaterLevel::CalculateWavesOnlyForCoordinate2( // TODO: Original name didn't have a 2 in it... I'm just lazy!
    int32 x, int32 y,
    float* pResultHeight,
    float bigWavesAmpl,
    float smallWavesAmpl
) {
    plugin::Call<0x6E7210>(x, y, bigWavesAmpl, smallWavesAmpl, pResultHeight);
}

// 0x6E6D10
void CWaterLevel::ScanThroughBlocks() {
    plugin::Call<0x6E6D10>();
}

// 0x6EE5A0
void CWaterLevel::SplitWaterTriangleAlongYLine(int32 a0, int32 a1, int32 a2, CRenPar a3, int32 a4, int32 a5, CRenPar a6, int32 a7, int32 a8, CRenPar a9) {
    plugin::Call<0x6EE5A0, int32, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar>(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

// 0x6EF650
void CWaterLevel::RenderWater() {
    plugin::Call<0x6EF650>();
}

void CWaterLevel::SyncWater() {
    m_nWaterTimeOffset = CTimer::GetTimeInMS();
}

// NOTSA
bool CWaterLevel::IsPointUnderwaterNoWaves(const CVector& point) {
    float level{};
    if (GetWaterLevelNoWaves(point, &level, nullptr, nullptr))
        return level > point.z;
    return false;
}

bool CWaterLevel::GetWaterLevel(const CVector& pos, float& outWaterLevel, bool touchingWater, CVector* normals) {
    return GetWaterLevel(pos.x, pos.y, pos.z, &outWaterLevel, touchingWater, normals);
}
