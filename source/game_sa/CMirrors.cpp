#include "StdInc.h"
#include "CMirrors.h"

int32_t& CMirrors::MirrorFlags = *(int32_t*)0xC7C618;
float& CMirrors::MirrorV = *(float*)0xC7C61C;
RwRaster*& CMirrors::pBuffer = *(RwRaster**)0xC7C71C;
RwRaster*& CMirrors::pZBuffer = *(RwRaster**)0xC7C720;
int32_t& CMirrors::TypeOfMirror = *(int32_t*)0xC7C724;
int8_t& CMirrors::bRenderingReflection = *(int8_t*)0xC7C728;
int8_t& CMirrors::d3dRestored = *(int8_t*)0xC7C729;
CVector& CMirrors::MirrorNormal = *(CVector*)0xC803D8;
bool& bFudgeNow = *(bool*)0xC7C72A;
CVector(&Screens8Track)[8] = *(CVector(*)[8])0x8D5DD8;

void CMirrors::InjectHooks() {
    ReversibleHooks::Install("CMirrors", "Init", 0x723000, &CMirrors::Init);
    ReversibleHooks::Install("CMirrors", "ShutDown", 0x723050, &CMirrors::ShutDown);
    ReversibleHooks::Install("CMirrors", "CreateBuffer", 0x7230A0, &CMirrors::CreateBuffer);
    ReversibleHooks::Install("CMirrors", "BuildCamMatrix", 0x723150, &CMirrors::BuildCamMatrix);
    ReversibleHooks::Install("CMirrors", "RenderMirrorBuffer", 0x726090, &CMirrors::RenderMirrorBuffer);
    ReversibleHooks::Install("CMirrors", "BuildCameraMatrixForScreens", 0x7266B0, &CMirrors::BuildCameraMatrixForScreens);
    // ReversibleHooks::Install("CMirrors", "BeforeConstructRenderList", 0x726DF0, &CMirrors::BeforeConstructRenderList);
    // ReversibleHooks::Install("CMirrors", "BeforeMainRender", 0x727140, &CMirrors::BeforeMainRender);
}

// 0x723000
void CMirrors::Init() {
    ShutDown();
}

// 0x723050
void CMirrors::ShutDown() {
    if (pBuffer)
        RwRasterDestroy(pBuffer);
    if (pZBuffer)
        RwRasterDestroy(pZBuffer);
    pBuffer = 0;
    pZBuffer = 0;
    TypeOfMirror = 0;
    MirrorFlags = 0;
}

// 0x7230A0
void CMirrors::CreateBuffer() {
    if (pBuffer)
        return;
    
    const auto depth = RwRasterGetDepth(RwCameraGetRaster(Scene.m_pRwCamera));
    if (g_fx.GetFxQuality() >= FxQuality_e::FXQUALITY_MEDIUM) {
        pBuffer = RwRasterCreate(1024, 512, depth, rwRASTERTYPECAMERATEXTURE);
        if (pBuffer) {
            pZBuffer = RwRasterCreate(1024, 512, depth, rwRASTERTYPEZBUFFER);
            if (pZBuffer)
                return;

            RwRasterDestroy(pBuffer);
            pBuffer = nullptr;
        }
    }

    // Low fx quality / fallback 
    pBuffer = RwRasterCreate(512, 256, depth, rwRASTERTYPECAMERATEXTURE);
    pZBuffer = RwRasterCreate(512, 256, depth, rwRASTERTYPEZBUFFER);
}

// 0x723150
void CMirrors::BuildCamMatrix(CMatrix& mat, CVector pointA, CVector pointB) {
    mat.SetTranslateOnly(pointA);
    mat.GetForward() = Normalized(pointB - pointA);
    mat.GetRight() = CrossProduct({ 0.0f, 0.0f, 1.0f }, mat.GetForward());
    mat.GetUp() = CrossProduct(mat.GetForward(), mat.GetRight());
}

// 0x726090
void CMirrors::RenderMirrorBuffer() {
    if (!TypeOfMirror)
        return;

    RwRaster* raster = RwCameraGetRaster(Scene.m_pRwCamera);
    const CVector2D rastersz{ RwRasterGetWidth(raster), RwRasterGetHeight(raster) };

    DefinedState();

    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void*)rwFILTERLINEAR);
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,(void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,(void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,(void*)FALSE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)pBuffer);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,(void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDONE);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDZERO);

    RwImVertexIndex indices[] = { 0, 1, 2, 0, 2, 3 };

    if (MirrorFlags & 2 || bFudgeNow) {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)TRUE);
        RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)TRUE);

        for (int x = 0; x < 2; x++) {
            constexpr CVector2D uvs[4]{
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f},
            };

            RxObjSpace3DVertex vertices[4];
            for (int i = 0; i < 4; i++) {
                RwIm3DVertexSetRGBA(&vertices[i], 0xFF, 0xFF, 0xFF, 0xFF);
                RwV3dAssign(RwIm3DVertexGetPos(&vertices[i]), &Screens8Track[x * 4 + i]);
                RwIm3DVertexSetU(&vertices[i], uvs[i].x);
                RwIm3DVertexSetV(&vertices[i], uvs[i].y);
            }

            if (RwIm3DTransform(vertices, std::size(vertices), nullptr, rwIM3D_VERTEXUV)) {
                RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, indices, std::size(indices));
                RwIm3DEnd();
            }
        }
    } else {
        const float zBufferNear = RwEngineInstance->dOpenDevice.zBufferNear;
        const CVector pos[] = {
           { 0.0f,       0.0f,       zBufferNear },
           { 0.0f,       rastersz.y, zBufferNear },
           { rastersz.x, rastersz.y, zBufferNear },
           { rastersz.x, 0.0f,       zBufferNear }
        };

        constexpr CVector2D uvs[] = {
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f },
            { 0.0f, 0.0f }
        };

        RwIm2DVertex vertices[4];
        for (int i = 0; i < 4; i++) {
            RwIm2DVertexSetRecipCameraZ(&vertices[i], 1.0f / RwCameraGetNearClipPlane(Scene.m_pRwCamera));
            RwIm2DVertexSetIntRGBA(&vertices[i], 0xFF, 0xFF, 0xFF, 0xFF);

            RwIm2DVertexGetScreenX(&vertices[i], pos[i].x);
            RwIm2DVertexGetScreenY(&vertices[i], pos[i].y);
            RwIm2DVertexGetScreenZ(&vertices[i], pos[i].z);
        }

        RwIm2DRenderIndexedPrimitive(rwPRIMTYPETRILIST, vertices, std::size(vertices), indices, std::size(indices));
    }

    if (DistanceBetweenPoints(TheCamera.GetPosition(), { 1003.0f, -42.0f, 216.0f }) < 50.0f) {
        const CVector pos[]{
            { 216.0f, -45.0f, 1000.0f },
            { 216.0f, -45.0f, 1006.0f },
            { 216.0f, -39.0f, 1006.0f },
            { 216.0f, -39.0f, 1000.0f }
        };

        constexpr CVector2D uvs[]{
            { 0.0f, 0.0f },
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f },
        };

        // TODO: This is another very commonly used thing (constructing vertices from a set of pos, uvs)
        // Make a function out of it.

        RxObjSpace3DVertex vertices[4];
        for (int i = 0; i < 4; i++) {
            RwIm3DVertexSetRGBA(&vertices[i], 0xFF, 0xFF, 0xFF, 0xFF);
            RwV3dAssign(RwIm3DVertexGetPos(&vertices[i]), &pos[i]);
            RwIm3DVertexSetU(&vertices[i], uvs[i].x);
            RwIm3DVertexSetV(&vertices[i], uvs[i].y);
        }

        if (RwIm3DTransform(vertices, std::size(vertices), nullptr, rwIM3D_VERTEXUV)) {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, indices, std::size(indices));
            RwIm3DEnd();
        }
    }

    RwRenderStateSet(rwRENDERSTATEFOGENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, (void*)TRUE);
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER, (void*)nullptr);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, (void*)FALSE);
    RwRenderStateSet(rwRENDERSTATESRCBLEND, (void*)rwBLENDSRCALPHA);
    RwRenderStateSet(rwRENDERSTATEDESTBLEND, (void*)rwBLENDINVSRCALPHA);
}

// 0x7266B0
void CMirrors::BuildCameraMatrixForScreens(CMatrix & mat) {
    const uint32_t timeSeconds = (CTimer::m_snTimeInMilliseconds / 1000u) % 32; // Wrapped to (0, 32]
    const uint32_t timeMsLeftInSecond = CTimer::m_snTimeInMilliseconds % 1000u;
    switch (timeSeconds) {
    case 0u:
    case 1u:
    case 2u:
    case 3u: {
        BuildCamMatrix(
            mat,
            { ((float)timeMsLeftInSecond / 1000.0f + (float)timeSeconds) * 6.0f - 1249.3f, -224.5f, 1064.2f },
            { -1265.4f, -207.5f, 1053.2f }
        );
        break;
    }
    case 10u:
    case 11u:
    case 12u:
    case 13u: {
        BuildCamMatrix(mat,
            { -1406.4f, -135.3f, 1045.65f },
            { -1402.5f, -146.8f, 1043.10f }
        );
        break;
    }
    case 22u:
    case 23u:
    case 24u:
    case 25u: {
        BuildCamMatrix(mat,
            { -1479.0f, -290.5f, 1099.54f },
            { -1428.0f, -256.7f, ((float)timeMsLeftInSecond / 1000.0f + (float)(timeSeconds - 22)) * 3.0f + 1057.3f }
        );
        break;
    }
    default: {
        mat.SetRotateZOnly((CTimer::m_snTimeInMilliseconds % 16384) * 0.00038349521f);
        mat.SetTranslateOnly({ -1397.0, -219.0, 1054.0 });
        break;
    }
    }
}

// 0x726DF0
void CMirrors::BeforeConstructRenderList() {
    plugin::Call<0x726DF0>();
}

// 0x727140
void CMirrors::BeforeMainRender() {
    plugin::Call<0x727140>();
}
