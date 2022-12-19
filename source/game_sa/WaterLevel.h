#pragma once

#include "Base.h"
#include "Vector.h"
#include "RGBA.h"
#include "Vector.h"
#include "Vector2D.h"

#include <extensions/utility.hpp>

struct CRenPar {
    float z;                        // Z pos of this thing. x, y can be found in the containing vertex, see `CWaterVertex`.
    float bigWaves, smallWaves;     // Height of waves
    int8  flowX, flowY;             // Fixed-point float. Divide by 64
};

// 0x6E5280
static CRenPar lerp(CRenPar rp1, CRenPar rp2, float t) {
    return {
        lerp(rp1.z, rp2.z, t),
        lerp(rp1.bigWaves, rp2.bigWaves, t),
        lerp(rp1.smallWaves, rp2.smallWaves, t),
        0, 0
    };
}

struct CWaterVertex {
    int16  x;
    int16  y;
    CRenPar renPar;
};

class CWaterLevel {
 public:
    /* Missing (in no particular order):
    m_BlocksToBeRenderedOutsideWorldX
    m_BlocksToBeRenderedOutsideWorldY
    m_CurrentDesiredFlowX
    m_CurrentDesiredFlowY
    m_CurrentFlowX
    m_CurrentFlowY
    m_ElementsOnQuadsAndTrianglesList
    m_NumBlocksOutsideWorldToBeRendered
    m_QuadsAndTrianglesInEachBlock
    m_QuadsAndTrianglesList
    m_WaterFogCol
    m_WaterFogDensity
    m_WaterFogHourOfDayEnd
    m_WaterFogHourOfDayStart
    m_WaterFogInsideCol
    m_aQuads
    m_aTriangles
    m_fWaterFogHeight
    m_fWaterFogInsideFadeSpeed
    m_nNumOfWaterQuads
    m_nNumOfWaterTriangles
    m_aVertices
    */
    static inline uint32& m_nWaterConfiguration = *(uint32*)0xC228A0;
    static inline uint32& m_nWaterTimeOffset = *(uint32*)0xC228A4;
    static inline bool& m_bWaterFog = *(bool*)0x8D37D4;
    static inline bool& m_bWaterFogScript = *(bool*)0x8D37D5;
    static inline int32& m_WaterFogDensity = *(int32*)0x8D37E0;

    static inline float (&faWaveMultipliersX)[8] = *(float(*)[8])0x8D38C8;
    static inline float (&faWaveMultipliersY)[8] = *(float(*)[8])0x8D38E8;
    static inline float (&ms_WakePointAlphaMults)[4] = *(float(*)[4])0x8D390C;

    static inline RwRaster*&   waterclear256Raster = *(RwRaster**)0xC228A8;
    static inline RwTexture*&  texWaterclear256 = *(RwTexture**)0xC228AC;

    static inline RwRaster*&   seabd32Raster = *(RwRaster**)0xC228B0;
    static inline RwTexture*&  texSeabd32 = *(RwTexture**)0xC228B4;

    static inline RwRaster*&   waterwakeRaster = *(RwRaster**)0xC228B8;
    static inline RwTexture*&  texWaterwake = *(RwTexture**)0xC228BC;

    static inline int32& NumWaterTriangles = *(int32*)0xC22884;
    static inline int32& NumWaterQuads = *(int32*)0xC22888;
    static inline int32& NumWaterVertices = *(int32*)0xC2288C;
    static inline int32& NumWaterZonePolys = *(int32*)0xC215F0;

    static inline int32& CameraRangeMaxY = *(int32*)0xC1F950;
    static inline int32& CameraRangeMinY = *(int32*)0xC1F954;

    static inline int32& CameraRangeMaxX = *(int32*)0xC1F958;
    static inline int32& CameraRangeMinX = *(int32*)0xC1F95C;

    static inline auto& WaterZones = *(notsa::mdarray<int32, 12, 12>*)0xC21B70;

    static inline auto& DETAILEDWATERDIST = *(int32*)0x8D37D0; // Default: 48
    static inline auto& bSplitBigPolys = *(bool*)0x8D37F4;     // Default: true
    static inline auto  BigPolySize = 168; // NOTSA variable, but value is OG.

    static inline auto& TextureShiftFirstV = *(float*)0xC21178;
    static inline auto& TextureShiftFirstU = *(float*)0xC2117C;

    static inline auto& TextureShiftSecondV = *(float*)0xC21180;
    static inline auto& TextureShiftSecondU = *(float*)0xC21184;

    // In reality the alpha component isn't used and instead `WaterLayerAlpha` is used
    static inline auto& WaterColorTriangle = *(CRGBA*)0xC21168;
    static inline auto& WaterColor         = *(CRGBA*)0xC2116C;

    static inline auto& WaterLayerAlpha = *(std::array<uint32, 2>*)0x8D3808;

    //! NOTSA: Stop `SetCameraRange()` from running
    static inline bool DontUpdateCameraRange = false;

    //static inline std::array<std::array<

    // NOTSA Section - Used for debugging //
    static inline struct DebugWaterColor {
        enum {
            TRI,
            RECT
        };

        bool  active{};
        CRGBA color{};
    } DebugWaterColors[2];

    static inline bool DontRenderYSplitTri = false;

public:
    static void InjectHooks();

    static void Shutdown();
    static void AddWaveToResult(float x, float y, float* pfWaterLevel, float fUnkn1, float fUnkn2, CVector* pVecNormal);
    static void RenderWaterTriangle(int32 a1, int32 a2, CRenPar a3, int32 a4, int32 a5, CRenPar a6, int32 a7, int32 a8, CRenPar a9);

    // NOTSA
    struct WaterLayerTexInfo {
        CVector2D shift;
        float     size;
    };
    /*!
    * @addr notsa
    * @brief Get texture info for a given layer
    */
    static auto GetWaterLayerTexInfo(int32 WaterLayer) -> WaterLayerTexInfo;

    // NOTSA
    struct TexUV {
        float     size;      // Texture size
        CVector2D pos;       // Pos of the 0th vertex (top left) on the texture 
        CVector2D baseShift; // Shift from the 0th vertex
    };
    /*!
    * @addr notsa
    * @brief Calculate texture UV mapping coords at a given position for a given layer
    */
    static auto GetTextureUV(int32 X1, int32 Y1, int32 Y3, int32 WaterLayer) -> TexUV;

    /*!
    * @addr notsa
    * @brief Choose color to use for rendering
    *
    * @param real       The real color (As it should be originally)
    * @param debug      Debug color
    * @param WaterLayer The water layer for which this color is. If the choosen color is the `real` the associated alpha will be applied.
    *
    * @return The color that should be used for rendering
    */
    static CRGBA GetWaterColorForRendering(CRGBA real, DebugWaterColor debug, int32 WaterLayer);

    static void RenderFlatWaterTriangle_OneLayer(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3, int32 WaterLayer);
    static void RenderFlatWaterTriangle(int32 a1, int32 a2, CRenPar a3, int32 a4, int32 a5, CRenPar a6, int32 a7, int32 a8, CRenPar a9);
    static void RenderBoatWakes();
    static void SplitWaterTriangleAlongXLine(int32 a7, int32 a1, int32 a2, CRenPar a4, int32 a5, int32 a6, CRenPar arg18, int32 a8, int32 a9, CRenPar a10);

    static void RenderWaterRectangle(int32 minX, int32 maxX, int32 Y1, int32 Y2, CRenPar P1, CRenPar P2, CRenPar P3, CRenPar P4);
    static void RenderFlatWaterRectangle(int32 minX, int32 maxX, int32 Y1, int32 Y2, CRenPar P1, CRenPar P2, CRenPar P3, CRenPar P4);
    static void RenderFlatWaterRectangle_OneLayer(int32 minX, int32 maxX, int32 Y1, int32 Y2, CRenPar P1, CRenPar P2, CRenPar P3, CRenPar P4, int32 WaterLayer);
    static void RenderHighDetailWaterRectangle(int32 minX, int32 maxX, int32 Y1, int32 Y2, CRenPar P1, CRenPar P2, CRenPar P3, CRenPar P4);
    static void SplitWaterRectangleAlongXLine(int32 a1, int32 a2, int32 a3, int32 a4, int32 a5, CRenPar a6, CRenPar a7, CRenPar a8, CRenPar a9);
    static void SplitWaterRectangleAlongYLine(int32 splitAtY, int32 minX, int32 maxX, int32 Y1, int32 Y2, CRenPar P1, CRenPar P2, CRenPar P3, CRenPar P4);

    static void PreRenderWater();
    static bool GetWaterDepth(const CVector& vecPos, float* pOutWaterDepth, float* pOutWaterLevel, float* pOutGroundLevel);
    static bool GetWaterLevel(float x, float y, float z, float* pOutWaterLevel, uint8 bTouchingWater, CVector* pVecNormals);
    static bool LoadDataFile();
    static void LoadTextures();
    static void WaterLevelInitialise();
    static void SetUpWaterFog(int32 a1, int32 a2, int32 a3, int32 a4);
    static int32 RenderWakeSegment(CVector2D & a1, CVector2D & a2, CVector2D & a3, CVector2D & a4, float & a5, float & a6, float & alphaMult1, float & alphaMult2, float & a9);
    static void FindNearestWaterAndItsFlow();
    static bool GetWaterLevelNoWaves(float x, float y, float z, float * pOutWaterLevel, float * fUnkn1, float * fUnkn2);
    static void RenderWaterFog();
    static void CalculateWavesOnlyForCoordinate(int32 x, int32 y, float lowFreqMult, float midHighFreqMult, float& outWave, float& colorMult, float& glare, CVector& vecNormal);
    static void ScanThroughBlocks();
    static void SplitWaterTriangleAlongYLine(int32 a0, int32 a1, int32 a2, CRenPar a3, int32 a4, int32 a5, CRenPar a6, int32 a7, int32 a8, CRenPar a9);
    static void RenderHighDetailWaterTriangle(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3);
    static void RenderWater();
    static void SyncWater();

    static bool IsPointUnderwaterNoWaves(const CVector& point);
    static bool GetWaterLevel(const CVector& pos, float& outWaterLevel, bool touchingWater, CVector* normals = nullptr);

    static void AddWaterLevelQuad(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3, int32 X4, int32 Y4, CRenPar P4, uint32 Flags);
    static void AddWaterLevelTriangle(int32 X1, int32 Y1, CRenPar P1, int32 X2, int32 Y2, CRenPar P2, int32 X3, int32 Y3, CRenPar P3, uint32 Flags);

    static void FillQuadsAndTrianglesList();

    static void SetCameraRange();

    /* Missing (In no particular order):
    static void AddWaveToResult(float x, float y, float z, float* pLevel, uint8 bTouchingWater, CVector* normalVec);
    AddWaveToResult(int32, int32, float*, float, float)
    BlockHit(int32, int32)
    CalculateWavesForCoordinate(int32, int32, float, float, float*, float*, float*, CVector*)
    ChangeWaterConfiguration(int32)
    CreateBeachToy(const CVector&, eBeachToy)
    FindNearestWaterAndItsFlow()
    FixVertexOnToLine(CWaterVertex*, CWaterVertex*, CWaterVertex*, float*)
    GetGroundLevel(const CVector&, float*, ColData*, float)
    GetGroundLevel_WS(const CVector&, float*, ColData*, float)
    RenderAndEmptyRenderBuffer()
    AddToQuadsAndTrianglesList(int32, int32, int32, uint32)
    AddWaterLevelQuad(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, uint32)
    AddWaterLevelTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, uint32)
    HandleBeachToysStuff()
    IsLocationOutOfWorldBounds_WS(const CVector&, int32)
    MarkQuadsAndPolysToBeRendered(int32, int32, bool)
    RenderBoatWakes()
    RenderDetailedSeaBedSegment(int32, int32, float, float, float, float)

    RenderFlatWaterTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)

    RenderFlatWaterRectangle(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    RenderFlatWaterRectangle_OneLayer(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar, int32)

    RenderHighDetailWaterRectangle_OneLayer(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar, int32, int32, int32, int32, int32)

    RenderHighDetailWaterTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)
    RenderHighDetailWaterTriangle_OneLayer(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, int32, int32)

    RenderSeaBedSegment(int32, int32, float, float, float, float)
    RenderShipsOnHorizon()
    RenderTransparentWater()
    RenderWakeSegment(CVector2D&, CVector2D&, CVector2D&, CVector2D&, float&, float&, float&, float&, float&)
    HandleBeachToysStuff()
    IsLocationOutOfWorldBounds_WS(const CVector&, int32) // WS = World Space
    MarkQuadsAndPolysToBeRendered(int32, int32, bool)
    RenderWaterFog()
    RenderWaterRectangle(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    RenderWaterTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)
    ScanThroughBlocks()
    SetUpWaterFog(int32, int32, int32, int32)
    SplitWaterRectangleAlongXLine(int32, int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    SplitWaterRectangleAlongYLine(int32, int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    TestLineAgainstWater(CVector, CVector, CVector*)
    TestQuadToGetWaterLevel(CWaterQuad*, float, float, float, float*, float*, float*)
    TestTriangleToGetWaterLevel(CWaterTriangle*, float, float, float, float*, float*, float*)
    */
};
