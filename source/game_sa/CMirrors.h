/*
    Plugin-SDK (Grand Theft Auto San Andreas) header file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once
#include "PluginBase.h"
#include "CMatrix.h"

class  CMirrors {
public:
    static RwRaster *&pBuffer;
    static RwRaster *&pZBuffer;
    static unsigned int &TypeOfMirror;
    static bool &bRenderingReflection;
    static bool &d3dRestored;
    static unsigned int &MirrorFlags;
    static float &MirrorV;
    static CVector &MirrorNormal;

    static void BeforeConstructRenderList();
    static void BeforeMainRender();
    static void BuildCamMatrix(CMatrix* mat, CVector pointA, CVector pointB);
    static void BuildCameraMatrixForScreens(CMatrix* mat);
    static void CreateBuffer();
    static void Init();
    static void RenderMirrorBuffer();
    static void ShutDown();
};

extern bool &bFudgeNow;
extern float *Screens8Track; // float Screens8Track[24]