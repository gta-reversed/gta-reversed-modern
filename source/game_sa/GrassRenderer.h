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

    static void AddTriPlant(PPTriPlant* srcPlant, uint32 plantModelSet);
    static void DrawTriPlants(PPTriPlant* triPlants, int32 numTriPlants, RpAtomic** plantModelsTab, RwMatrix* ltm = nullptr);
    static void FlushTriPlantBuffer();

    static void* GetPlantModelsTab(uint32 type);
    static void SetPlantModelsTab(uint32 type, RpAtomic** atomics);

    static void SetCloseFarAlphaDist(float fCloseDist, float fFarDist);
    static void SetCurrentScanCode(uint16 scanCode);
    static void SetGlobalCameraPos(const CVector& cameraPosn);
    static void SetGlobalWindBending(float bending);

    static CVector& InterpolateTriangle(CVector& outPosn, const CVector& v1, const CVector& v2, const CVector& v3, float randA, float randB);
};
