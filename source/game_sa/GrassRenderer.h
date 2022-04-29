#pragma once

#include "PPTriPlantBuffer.h"

class CVector;

class CGrassRenderer {
public:
    static float& m_windBending;
    static float& m_closeDist;
    static CVector& m_vecCameraPos;
    static float& m_farDist;

public:
    static void InjectHooks();

    CGrassRenderer() = default;
    ~CGrassRenderer() = default;

    static bool Initialise();
    static void Shutdown();

    static void AddTriPlant(PPTriPlant* plant, uint32 type);
    static void DrawTriPlants(PPTriPlant* plant, int32 count, RpAtomic** atomics);
    static void FlushTriPlantBuffer();

    static void* GetPlantModelsTab(uint32 type);
    static void SetPlantModelsTab(uint32 type, RpAtomic** atomics);

    static void SetCloseFarAlphaDist(float fCloseDist, float fFarDist);
    static void SetCurrentScanCode(uint16 scanCode);
    static void SetGlobalCameraPos(const CVector& cameraPosn);
    static void SetGlobalWindBending(float bending);

    static void sub_5DAB00(CVector& outPosn, const CVector& startMin, const CVector& startMax, const CVector& endMin, float randA, float randB);
};
