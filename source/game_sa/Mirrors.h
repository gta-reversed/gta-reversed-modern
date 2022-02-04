/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Matrix.h"
#include "Vector.h"

class CMirrors {
public:
    static RwRaster*& pBuffer;
    static RwRaster*& pZBuffer;
    static bool&      bRenderingReflection;
    static bool&      d3dRestored;
    static int8&      TypeOfMirror;
    static int8&      MirrorFlags;
    static float&     MirrorV;
    static CVector&   MirrorNormal;

public:
    static void InjectHooks();

    static void Init();
    static void ShutDown();

    static void BeforeConstructRenderList();
    static void BeforeMainRender();

    static void BuildCamMatrix(CMatrix& mat, CVector pointA, CVector pointB);
    static void BuildCameraMatrixForScreens(CMatrix& mat);

    static void CreateBuffer();

    static void RenderMirrorBuffer();
    static void RenderReflBuffer(bool);
    static void RenderReflections();

    // NOTSA
    static bool IsEitherScreenVisibleToCam();
};
