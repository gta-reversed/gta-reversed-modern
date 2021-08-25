/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CMatrix.h"
#include "CVector.h"

class CMirrors {
public:
    static int32_t& MirrorFlags;
    static float& MirrorV;
    static RwRaster*& pBuffer;
    static RwRaster*& pZBuffer;
    static int32_t& TypeOfMirror;
    static int8_t& bRenderingReflection;
    static int8_t& d3dRestored;
    static CVector& MirrorNormal;

public:
    static void InjectHooks();

    static void Init();
    static void ShutDown();
    static void CreateBuffer();
    static void BuildCamMatrix(CMatrix& mat, CVector pointA, CVector pointB);
    static void RenderMirrorBuffer();
    static void BuildCameraMatrixForScreens(CMatrix & mat);
    static void BeforeConstructRenderList();
    static void BeforeMainRender();
    static bool AreEitherScreensVisibleToCam();
};

extern bool& bFudgeNow;
extern CVector(&Screens8Track)[8];

