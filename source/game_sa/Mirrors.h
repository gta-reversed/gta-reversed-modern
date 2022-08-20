/*
    Plugin-SDK file
    Authors: GTA Community. See more here
    https://github.com/DK22Pac/plugin-sdk
    Do not delete this comment block. Respect others' work!
*/
#pragma once

#include "Matrix.h"
#include "Vector.h"

enum eMirrorType : uint8 {
    MIRROR_TYPE_NONE = 0,
    MIRROR_TYPE_WALL = 1,
    MIRROR_TYPE_FLOOR = 2,
    MIRROR_TYPE_SPHERE_MAP = 3
};

class CMirrors {
public:
    static RwRaster*& pBuffer;
    static RwRaster*& pZBuffer;
    static bool&      bRenderingReflection;
    static bool&      d3dRestored;
    static eMirrorType& TypeOfMirror;
    static uint8&     MirrorFlags;
    static float&     MirrorV;
    static CVector&   MirrorNormal;

public:
    static void InjectHooks();

    static void Init();
    static void ShutDown();

    static void BeforeConstructRenderList();
    static void BeforeMainRender();

    static void BuildCamMatrix(CMatrix& camMatrix, CVector source, CVector dest);
    static void BuildCameraMatrixForScreens(CMatrix& mat);

    static void CreateBuffer();

    static void RenderMirrorBuffer();
    static void RenderReflBuffer(bool);
    static void RenderReflections();

    static bool ShouldRenderPeds();
};
