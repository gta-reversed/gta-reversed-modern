#include "StdInc.h"

bool CWaterLevel::GetWaterLevel(float x, float y, float z, float * pOutWaterLevel, char bUnderWater, CVector* pVector)
{
    typedef bool(__cdecl*  hCWaterLevel_GetWaterLevel) ( float x, float y, float z, float * pOutWaterLevel, char bUnderWater, CVector* pVector );
    auto OLD_CWaterLevel_GetWaterLevel = (hCWaterLevel_GetWaterLevel)0x6EB690;
    return OLD_CWaterLevel_GetWaterLevel(x, y, z, pOutWaterLevel, bUnderWater, pVector);
}

bool CWaterLevel::GetWaterLevelNoWaves(float x, float y, float z, float* pOutWaterLevel, float* fUnkn1, float* fUnkn2) {
    return ((bool(__cdecl*)(float, float, float, float*, float*, float*))0x6E8580)(x, y, z, pOutWaterLevel, fUnkn1, fUnkn2);
}
