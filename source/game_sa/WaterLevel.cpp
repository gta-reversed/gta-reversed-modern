#include "StdInc.h"
#include "WaterLevel.h"
#include <sstream>

#define TRIANGLE_ARGS_OUT X1, Y1, P1, X2, Y2, P2, X3, Y3, P3

void CWaterLevel::InjectHooks() {
    RH_ScopedClass(CWaterLevel);
    RH_ScopedCategoryGlobal();

    RH_ScopedGlobalInstall(WaterLevelInitialise, 0x6EAE80);
    RH_ScopedGlobalInstall(Shutdown, 0x6E59E0);
    RH_ScopedGlobalInstall(RenderWaterTriangle, 0x6EE240);
    RH_ScopedGlobalInstall(RenderFlatWaterTriangle, 0x6EE080, { .reversed = false });
    RH_ScopedGlobalInstall(RenderBoatWakes, 0x6ED9A0, { .reversed = false });
    RH_ScopedGlobalInstall(SplitWaterTriangleAlongXLine, 0x6ECF00, { .reversed = false });
    RH_ScopedGlobalInstall(RenderWaterRectangle, 0x6EC5D0, { .reversed = false });
    RH_ScopedGlobalInstall(RenderFlatWaterRectangle, 0x6EBEC0, { .reversed = false });
    RH_ScopedGlobalInstall(SplitWaterRectangleAlongXLine, 0x6EB810, { .reversed = false });
    RH_ScopedGlobalInstall(PreRenderWater, 0x6EB710, { .reversed = false });
    RH_ScopedOverloadedInstall(GetWaterLevel, "", 0x6EB690, bool(*)(float, float, float, float*, uint8, CVector*));
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
    RH_ScopedGlobalInstall(SetCameraRange, 0x6E9C80);
}

// NOTSA
bool CWaterLevel::LoadDataFile() {
    const auto file = CFileMgr::OpenFile(m_nWaterConfiguration == 1 ? "DATA//water1.dat" : "DATA//water.dat", "r");

    const notsa::AutoCallOnDestruct autoCloser{ [&] { CFileMgr::CloseFile(file); } };

    uint32 nline{}, ntri{}, nquad{};
    for (;; nline++) {
        const auto line = CFileLoader::LoadLine(file);
        if (!line) {
            break;
        }
        std::stringstream liness{ line };

        auto nvertices{0u};

        struct {
            CVector   pos{};
            CVector2D flow{};
            float     bigWaves{}, smallWaves{};
        } vertices[4]{};

        // Helper function to read a vertex from the stream
        const auto ReadNextVertex = [&]() {
            const auto orgpos = liness.tellg();

            auto& vtx = vertices[nvertices];
            liness
                >> vtx.pos.x
                >> vtx.pos.y
                >> vtx.pos.z
                >> vtx.flow.x
                >> vtx.flow.y
                >> vtx.bigWaves
                >> vtx.smallWaves;

            if (liness.good()) {
                nvertices++;
                return true;
            } else {
                liness.clear(); // reset error flags
                liness.seekg(orgpos); // go back to before
                return false;
            }

        };

        // If can't read first vertex just ignore line
        if (!ReadNextVertex()) {
            continue;
        }

        // Read 2/3 more vertices
        while (ReadNextVertex() && nvertices < 4);

        // Check if we have enough vertices
        if (nvertices < 3) {
            DEV_LOG("[Warning]: Not enough vertices, got {}, expected 3 or 4. [Line: {}]", nvertices, nline);
            continue;
            //return false; // Just stop here, this parser is way too primitive to be able to recover from errors
        }

        // Optional flag after vertices
        uint32 flags{};
        liness >> flags;

        // I'm sorry, but don't blame me I HAD NO OTHER CHOICE!
        #define VertexUnpack(n) \
            (int32)vertices[n].pos.x, (int32)vertices[n].pos.y, \
            CRenPar{vertices[n].pos.z, vertices[n].bigWaves, vertices[n].smallWaves, (int8)(vertices[n].flow.x * 64.f), (int8)(vertices[n].flow.y * 64.f)}

        // Add quad/triangle
        if (nvertices == 4) {
            CWaterLevel::AddWaterLevelQuad(
                VertexUnpack(0),
                VertexUnpack(1),
                VertexUnpack(2),
                VertexUnpack(3),
                flags
            );
            nquad++;
        } else {
            CWaterLevel::AddWaterLevelTriangle(
                VertexUnpack(0),
                VertexUnpack(1),
                VertexUnpack(2),
                flags
            );
            ntri++;
        }
        #undef ArgUnpack
    }
    DEV_LOG("Successfully loaded! [Quads: {}; Tris: {}]", nquad, ntri);
    return true;
}

// NOTSA: Code @ 0x6EB5F4
void CWaterLevel::LoadTextures() {
    CTxdStore::PushCurrentTxd();    
    CTxdStore::SetCurrentTxd(CTxdStore::FindTxdSlot("particle"));

    const auto DoTex = [](auto& inOutTex, auto& outRaster, const char* name) {
        if (!inOutTex) {
            inOutTex = RwTextureRead(name, nullptr);
        }
        outRaster = RwTextureGetRaster(inOutTex);
    };
    DoTex(texWaterclear256, waterclear256Raster, "waterclear256");
    DoTex(texSeabd32,       seabd32Raster,       "seabd32"      );
    DoTex(texWaterwake,     waterwakeRaster,     "waterwake"    );

    CTxdStore::PopCurrentTxd();
}

// 0x6EAE80
void CWaterLevel::WaterLevelInitialise() {
    NumWaterTriangles = 0;
    NumWaterQuads = 0;
    NumWaterVertices = 0;
    NumWaterZonePolys = 0;
    
    (void)LoadDataFile();
    FillQuadsAndTrianglesList();

    LoadTextures();
}

// 0x6E59E0
void CWaterLevel::Shutdown() {
    // Unload Textures
    for (auto tex : { &texWaterclear256, &texSeabd32, &texWaterwake }) {
        if (*tex) {
            RwTextureDestroy(*tex);
            *tex = nullptr;
        }
    }
}

// 0x6E81E0
void CWaterLevel::AddWaveToResult(float x, float y, float* pfWaterLevel, float fUnkn1, float fUnkn2, CVector* pVecNormal)
{
    plugin::Call<0x6E81E0, float, float, float*, float, float, CVector*>(x, y, pfWaterLevel, fUnkn1, fUnkn2, pVecNormal);
}

// 0x6EE240
void CWaterLevel::RenderWaterTriangle(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3) {
    const auto [minX, maxX] = std::make_pair(X1, X2); // Assumes: Starting in top left vertex with clockwise order
    const auto [minY, maxY] = std::minmax(Y1, Y3);
    if (minX >= CameraRangeMaxX || maxX <= CameraRangeMinX || minY >= CameraRangeMaxY || maxY <= CameraRangeMinY) { // Lies outside (of camera) fully
        RenderFlatWaterTriangle(TRIANGLE_ARGS_OUT);
    } else if (minX < CameraRangeMinX || maxX > CameraRangeMaxX) { // Lies outside on X (But inside on Y)
        SplitWaterTriangleAlongXLine(minX < CameraRangeMinX ? CameraRangeMinX : CameraRangeMaxX, TRIANGLE_ARGS_OUT);
    } else if (minY < CameraRangeMinY || maxY > CameraRangeMaxY) { // Lies outside on Y (But inside on X)
        SplitWaterTriangleAlongYLine(minY < CameraRangeMinY ? CameraRangeMinY : CameraRangeMaxY, TRIANGLE_ARGS_OUT);
    } else { // Lies inside of camera fully
        RenderHighDetailWaterTriangle(TRIANGLE_ARGS_OUT);
    }
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
    if (!GetWaterLevelNoWaves(x, y, z, pOutWaterLevel, &fUnkn1, &fUnkn2))
        return false;
     
    if ((*pOutWaterLevel - z > 3.0F) && !bTouchingWater) {
        *pOutWaterLevel = 0.0F;
        return false;
    }

    AddWaveToResult(x, y, pOutWaterLevel, fUnkn1, fUnkn2, pVecNormals);
    return true;
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
bool CWaterLevel::GetWaterLevelNoWaves(float x, float y, float z, float * pOutWaterLevel, float * fUnkn1, float * fUnkn2) {
    return plugin::CallAndReturn<bool, 0x6E8580, float, float, float, float *, float *, float *>(x, y, z, pOutWaterLevel, fUnkn1, fUnkn2);
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
void CWaterLevel::CalculateWavesOnlyForCoordinate(int32 x, int32 y, float lowFreqMult, float midHighFreqMult, float& outWave,
    float& colorMult, float& glare, CVector& vecNormal)
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

// 0x6E6D10
void CWaterLevel::ScanThroughBlocks() {
    plugin::Call<0x6E6D10>();
}

// 0x6EE5A0
void CWaterLevel::SplitWaterTriangleAlongYLine(int32 a0, int32 a1, int32 a2, CRenPar a3, int32 a4, int32 a5, CRenPar a6, int32 a7, int32 a8, CRenPar a9) {
    plugin::Call<0x6EE5A0, int32, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar>(a0, a1, a2, a3, a4, a5, a6, a7, a8, a9);
}

void CWaterLevel::RenderHighDetailWaterTriangle(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3) {
    plugin::CallAndReturn<void, 0x6EDDC0, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar>(X1, Y1, P1, X2, Y2, P2, X3, Y3, P3);
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
    if (GetWaterLevelNoWaves(point.x, point.y, point.z, &level, nullptr, nullptr))
        return level > point.z;
    return false;
}

bool CWaterLevel::GetWaterLevel(const CVector& pos, float& outWaterLevel, bool touchingWater, CVector* normals) {
    return GetWaterLevel(pos.x, pos.y, pos.z, &outWaterLevel, touchingWater, normals);
}

// 0x6E7EF0
void CWaterLevel::AddWaterLevelQuad(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3, int32 X4, int32 Y4, CRenPar P4, uint32 Flags) {
    return plugin::CallAndReturn<void, 0x6E7EF0, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, uint32>(X1, Y1, P1, X2, Y2, P2, X3, Y3, P3, X4, Y4, P4, Flags);
}

// 0x6E7D40
void CWaterLevel::AddWaterLevelTriangle(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3, uint32 Flags) {
    return plugin::CallAndReturn<void, 0x6E7D40, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, uint32>(X1, Y1, P1, X2, Y2, P2, X3, Y3, P3, Flags);
}

void CWaterLevel::FillQuadsAndTrianglesList() {
    plugin::Call<0x6E7B30>();
}

// 0x6E9C80
void CWaterLevel::SetCameraRange() {
    const auto& cmpos = TheCamera.GetPosition();

    const auto CalcMin = [](float p) { return 2 * (int32)std::floor((p - (float)DETAILEDWATERDIST) / 2.f); };
    const auto CalcMax = [](float p) { return 2 * (int32)std::ceil((p + (float)DETAILEDWATERDIST) / 2.f); };

    CameraRangeMinX = CalcMin(cmpos.x);
    CameraRangeMaxX = CalcMax(cmpos.x);

    CameraRangeMinY = CalcMin(cmpos.y);
    CameraRangeMaxY = CalcMax(cmpos.y);
}
