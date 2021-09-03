#pragma once

class CVector;

struct CRenPar {
    float z;
    float u;
    float waveHeight;
    float velocity;
};

struct CWaterVertex {
    uint16  x;
    uint16  y;
    CRenPar renPar;
};

class CWaterLevel {
public:
   /*
   * m_BlocksToBeRenderedOutsideWorldX
   * m_BlocksToBeRenderedOutsideWorldY
   * m_CurrentDesiredFlowX
   * m_CurrentDesiredFlowY
   * m_CurrentFlowX
   * m_CurrentFlowY
   * m_ElementsOnQuadsAndTrianglesList
   * m_NumBlocksOutsideWorldToBeRendered
   * m_QuadsAndTrianglesInEachBlock
   * m_QuadsAndTrianglesList
   * m_WaterFogCol
   * m_WaterFogDensity
   * m_WaterFogHourOfDayEnd
   * m_WaterFogHourOfDayStart
   * m_WaterFogInsideCol
   * m_aQuads
   * m_aTriangles
   */
    static CWaterVertex m_aVertices[1021];
    static bool& m_bWaterFog;
    static bool& m_bWaterFogScript;
    /*
    * m_fWaterFogHeight
    * m_fWaterFogInsideFadeSpeed
    * m_nNumOfWaterQuads
    * m_nNumOfWaterTriangles
    */
    static uint32 m_nNumOfWaterVertices;
    static uint32& m_nWaterConfiguration;
    static uint32& m_nWaterTimeOffset;
    static float* faWaveMultipliersX;
    static float* faWaveMultipliersY;

  public:
    static RwRaster* waterclear256Raster;
    static RwTexture* texWaterclear256;
    static RwRaster* seabd32Raster;
    static RwTexture* texSeabd32;
    static RwRaster* waterwakeRaster;
    static RwTexture* texWaterwake;

    /* m_nWaterConfiguration
    * ms_WaterFog
    */

public:
    static void InjectHooks();

    /*
    * AddToQuadsAndTrianglesList(int32, int32, int32, uint32)
    * AddWaterLevelQuad(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, uint32)
    * AddWaterLevelTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, uint32)
    */
    static int32 AddWaterLevelVertex(int32 x, int32 y, CRenPar renPar);
    static void AddWaveToResult(float x, float y, float* pfWaterLevel, float fUnkn1, float fUnkn2, CVector* pVecNormal);
    static void CalculateWavesOnlyForCoordinate(int32 x, int32 y, float fUnkn1, float fUnkn2, float* fOutWave);
    /*
    * static void AddWaveToResult(float x, float y, float z, float* pLevel, uint8 bTouchingWater, CVector* normalVec);
    * AddWaveToResult(int32, int32, float*, float, float)
    * BlockHit(int32, int32)
    * CalculateWavesForCoordinate(int32, int32, float, float, float*, float*, float*, CVector*)
    * ChangeWaterConfiguration(int32)
    * CreateBeachToy(CVector const&, eBeachToy)
    * FillQuadsAndTrianglesList()
    * FindNearestWaterAndItsFlow()
    * FixVertexOnToLine(CWaterVertex*, CWaterVertex*, CWaterVertex*, float*)
    * GetGroundLevel(CVector const&, float*, ColData*, float)
    * GetGroundLevel_WS(CVector const&, float*, ColData*, float)
    *
    */
    static bool GetWaterDepth(CVector const& vecPos, float* pOutWaterDepth, float* pOutWaterLevel, float* pOutGroundLevel);
    static bool GetWaterLevel(float x, float y, float z, float * pOutWaterLevel, uint8 bTouchingWater, CVector* pVecNormals);
    static bool GetWaterLevelNoWaves(float x, float y, float z, float* pOutWaterLevel, float* fUnkn1, float* fUnkn2);
    /*
    * HandleBeachToysStuff()
    * IsLocationOutOfWorldBounds_WS(CVector const&, int32)
    * MarkQuadsAndPolysToBeRendered(int32, int32, bool)
    */
    static void PreRenderWater();
    /* RenderAndEmptyRenderBuffer()
    * RenderBoatWakes()
    * RenderDetailedSeaBedSegment(int32, int32, float, float, float, float)
    * RenderFlatWaterRectangle(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    * RenderFlatWaterRectangle_OneLayer(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar, int32)
    * RenderFlatWaterTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)
    * RenderFlatWaterTriangle_OneLayer(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, int32)
    * RenderHighDetailWaterRectangle(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    * RenderHighDetailWaterRectangle_OneLayer(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar, int32, int32, int32, int32, int32)
    * RenderHighDetailWaterTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)
    * RenderHighDetailWaterTriangle_OneLayer(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, int32, int32)
    * RenderSeaBedSegment(int32, int32, float, float, float, float)
    * RenderShipsOnHorizon()
    * RenderTransparentWater()
    * RenderWakeSegment(CVector2D&, CVector2D&, CVector2D&, CVector2D&, float&, float&, float&, float&, float&)
    */
    static void RenderWater();
    /* RenderWaterFog()
    * RenderWaterRectangle(int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    * RenderWaterTriangle(int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)
    * ScanThroughBlocks()
    * SetCameraRange()
    * SetUpWaterFog(int32, int32, int32, int32)
    * Shutdown()
    * SplitWaterRectangleAlongXLine(int32, int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    * SplitWaterRectangleAlongYLine(int32, int32, int32, int32, int32, CRenPar, CRenPar, CRenPar, CRenPar)
    * SplitWaterTriangleAlongXLine(int32, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)
    * SplitWaterTriangleAlongYLine(int32, int32, int32, CRenPar, int32, int32, CRenPar, int32, int32, CRenPar)
    * TestLineAgainstWater(CVector, CVector, CVector*)
    * TestQuadToGetWaterLevel(CWaterQuad*, float, float, float, float*, float*, float*)
    * TestTriangleToGetWaterLevel(CWaterTriangle*, float, float, float, float*, float*, float*)
    * WaterLevelInitialise()
    */
    static void SyncWater();
    static void WaterLevelInitialise();
};
