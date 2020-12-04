#pragma once
class CVector;
struct CRenPar
{
    float z;
    float u;
    float waveHeight;
    float velocity;
};

struct CWaterVertex
{
    uint16_t x;
    uint16_t y;
    CRenPar renPar;
};

class CWaterLevel
{
public:
    /*
    * AddToQuadsAndTrianglesList(int, int, int, unsigned int)
    * AddWaterLevelQuad(int, int, CRenPar, int, int, CRenPar, int, int, CRenPar, int, int, CRenPar, unsigned int)
    * AddWaterLevelTriangle(int, int, CRenPar, int, int, CRenPar, int, int, CRenPar, unsigned int)
    */
    static int AddWaterLevelVertex(int x, int y, CRenPar renPar);
    /* AddWaveToResult(float, float, float*, float, float, CVector*)
    * AddWaveToResult(int, int, float*, float, float)
    * BlockHit(int, int)
    * CalculateWavesForCoordinate(int, int, float, float, float*, float*, float*, CVector*)
    * CalculateWavesOnlyForCoordinate(int, int, float, float, float*)
    * ChangeWaterConfiguration(int)
    * CreateBeachToy(CVector const&, eBeachToy)
    * FillQuadsAndTrianglesList()
    * FindNearestWaterAndItsFlow()
    * FixVertexOnToLine(CWaterVertex*, CWaterVertex*, CWaterVertex*, float*)
    * GetGroundLevel(CVector const&, float*, ColData*, float)
    * GetGroundLevel_WS(CVector const&, float*, ColData*, float)
    * GetWaterDepth(CVector const&, float*, float*, float*)
    */
    static bool GetWaterLevel(float x, float y, float z, float * pOutWaterLevel, char bUnderWater, CVector* pVector);
    static bool GetWaterLevelNoWaves(float x, float y, float z, float* pOutWaterLevel, float* fUnkn1, float* fUnkn2);
    /*
    * HandleBeachToysStuff()
    * IsLocationOutOfWorldBounds_WS(CVector const&, int)
    * MarkQuadsAndPolysToBeRendered(int, int, bool)
    * PreRenderWater()
    * RenderAndEmptyRenderBuffer()
    * RenderBoatWakes()
    * RenderDetailedSeaBedSegment(int, int, float, float, float, float)
    * RenderFlatWaterRectangle(int, int, int, int, CRenPar, CRenPar, CRenPar, CRenPar)
    * RenderFlatWaterRectangle_OneLayer(int, int, int, int, CRenPar, CRenPar, CRenPar, CRenPar, int)
    * RenderFlatWaterTriangle(int, int, CRenPar, int, int, CRenPar, int, int, CRenPar)
    * RenderFlatWaterTriangle_OneLayer(int, int, CRenPar, int, int, CRenPar, int, int, CRenPar, int)
    * RenderHighDetailWaterRectangle(int, int, int, int, CRenPar, CRenPar, CRenPar, CRenPar)
    * RenderHighDetailWaterRectangle_OneLayer(int, int, int, int, CRenPar, CRenPar, CRenPar, CRenPar, int, int, int, int, int)
    * RenderHighDetailWaterTriangle(int, int, CRenPar, int, int, CRenPar, int, int, CRenPar)
    * RenderHighDetailWaterTriangle_OneLayer(int, int, CRenPar, int, int, CRenPar, int, int, CRenPar, int, int, int, int)
    * RenderSeaBedSegment(int, int, float, float, float, float)
    * RenderShipsOnHorizon()
    * RenderTransparentWater()
    * RenderWakeSegment(CVector2D&, CVector2D&, CVector2D&, CVector2D&, float&, float&, float&, float&, float&)
    * RenderWater()
    * RenderWaterFog()
    * RenderWaterRectangle(int, int, int, int, CRenPar, CRenPar, CRenPar, CRenPar)
    * RenderWaterTriangle(int, int, CRenPar, int, int, CRenPar, int, int, CRenPar)
    * ScanThroughBlocks()
    * SetCameraRange()
    * SetUpWaterFog(int, int, int, int)
    * Shutdown()
    * SplitWaterRectangleAlongXLine(int, int, int, int, int, CRenPar, CRenPar, CRenPar, CRenPar)
    * SplitWaterRectangleAlongYLine(int, int, int, int, int, CRenPar, CRenPar, CRenPar, CRenPar)
    * SplitWaterTriangleAlongXLine(int, int, int, CRenPar, int, int, CRenPar, int, int, CRenPar)
    * SplitWaterTriangleAlongYLine(int, int, int, CRenPar, int, int, CRenPar, int, int, CRenPar)
    * SyncWater()
    * TestLineAgainstWater(CVector, CVector, CVector*)
    * TestQuadToGetWaterLevel(CWaterQuad*, float, float, float, float*, float*, float*)
    * TestTriangleToGetWaterLevel(CWaterTriangle*, float, float, float, float*, float*, float*)
    * WaterLevelInitialise()
    */
private:
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
    /* m_bWaterFog
    * m_bWaterFogScript
    * m_fWaterFogHeight
    * m_fWaterFogInsideFadeSpeed
    * m_nNumOfWaterQuads
    * m_nNumOfWaterTriangles
    */
    static uint32_t m_nNumOfWaterVertices;
    /* m_nWaterConfiguration
    * m_nWaterTimeOffset
    * ms_WaterFog
    */
};
