#include "StdInc.h"

#include "Mirrors.h"

#include "MovingThings.h"
#include "BreakManager_c.h"
#include "PlantMgr.h"
#include "Clouds.h"
#include "PostEffects.h"

RwRaster*& CMirrors::pBuffer = *(RwRaster**)0xC7C71C;
RwRaster*& CMirrors::pZBuffer = *(RwRaster**)0xC7C720;
bool& CMirrors::bRenderingReflection = *(bool*)0xC7C728;
bool& CMirrors::d3dRestored = *(bool*)0xC7C729;
int8& CMirrors::TypeOfMirror = *(int8*)0xC7C724;
int8& CMirrors::MirrorFlags = *(int8*)0xC7C618;
CVector& CMirrors::MirrorNormal = *(CVector*)0xC803D8;
float& CMirrors::MirrorV = *(float*)0xC7C61C;

bool& bFudgeNow = *(bool*)0xC7C72A;
CVector Screens8Track[2][4] = { // 0x8D5DD8
    {
        { -1333.453f, -221.89799f, 1079.141f },
        { -1333.453f, -189.89799f, 1079.141f },
        { -1333.453f, -189.89799f, 1067.141f },
        { -1333.453f, -221.89799f, 1067.141f },
    },
    {
        { -1477.845f, -189.96899f, 1079.141f },
        { -1477.845f, -221.96899f, 1079.141f },
        { -1477.845f, -221.96899f, 1067.141f },
        { -1477.845f, -189.96899f, 1067.141f },
    }
};

void CMirrors::InjectHooks() {
    RH_ScopedClass(CMirrors);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Init, 0x723000);
    RH_ScopedInstall(ShutDown, 0x723050);
    RH_ScopedInstall(CreateBuffer, 0x7230A0);
    RH_ScopedInstall(BuildCamMatrix, 0x723150);
    RH_ScopedInstall(RenderMirrorBuffer, 0x726090);
    RH_ScopedInstall(BuildCameraMatrixForScreens, 0x7266B0);
    RH_ScopedInstall(BeforeConstructRenderList, 0x726DF0);
    RH_ScopedInstall(BeforeMainRender, 0x727140);
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
    pBuffer = nullptr;
    pZBuffer = nullptr;
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
    if (TypeOfMirror == 0)
        return;

    RwRaster* raster = RwCameraGetRaster(Scene.m_pRwCamera);
    const CVector2D rastersz{ (float)RwRasterGetWidth(raster), (float)RwRasterGetHeight(raster) };

    DefinedState();

    RwRenderStateSet(rwRENDERSTATETEXTUREFILTER,     RWRSTATE(rwFILTERLINEAR));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(pBuffer));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDONE));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDZERO));

    RwImVertexIndex indices[] = { 0, 1, 2, 0, 2, 3 };

    if (MirrorFlags & CAM_STAIRS_FOR_PLAYER || bFudgeNow) {
        RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
        RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
        RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(TRUE));

        for (int x = 0; x < 2; x++) {
            constexpr CVector2D uvs[4]{
                {0.0f, 0.0f},
                {1.0f, 0.0f},
                {1.0f, 1.0f},
                {0.0f, 1.0f},
            };

            RxObjSpace3DVertex vertices[4];
            for (int i = 0; i < std::size(vertices); i++) {
                RwIm3DVertexSetRGBA(&vertices[i], 255, 255, 255, 255);
                RwV3dAssign(RwIm3DVertexGetPos(&vertices[i]), &Screens8Track[x][i]);
                RwIm3DVertexSetU(&vertices[i], uvs[i].x);
                RwIm3DVertexSetV(&vertices[i], uvs[i].y);
            }

            if (RwIm3DTransform(vertices, std::size(vertices), nullptr, rwIM3D_VERTEXUV)) {
                RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, indices, std::size(indices));
                RwIm3DEnd();
            }
        }
    } else {
        const CVector2D pos[] = {
           { 0.0f,       0.0f,      },
           { 0.0f,       rastersz.y },
           { rastersz.x, rastersz.y },
           { rastersz.x, 0.0f,      }
        };

        constexpr CVector2D uvs[] = {
            { 1.0f, 0.0f },
            { 1.0f, 1.0f },
            { 0.0f, 1.0f },
            { 0.0f, 0.0f }
        };

        RwIm2DVertex vertices[4];
        for (int i = 0; i < std::size(vertices); i++) {
            RwIm2DVertexSetRecipCameraZ(&vertices[i], 1.0f / RwCameraGetNearClipPlane(Scene.m_pRwCamera));
            RwIm2DVertexSetIntRGBA(&vertices[i], 255, 255, 255, 255);

            RwIm2DVertexSetScreenX(&vertices[i], pos[i].x);
            RwIm2DVertexSetScreenY(&vertices[i], pos[i].y);
            RwIm2DVertexSetScreenZ(&vertices[i], RwIm2DGetNearScreenZ());

            RwIm3DVertexSetU(&vertices[i], uvs[i].x);
            RwIm3DVertexSetV(&vertices[i], uvs[i].y);
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
        for (int i = 0; i < std::size(vertices); i++) {
            RwIm3DVertexSetRGBA(&vertices[i], 255, 255, 255, 255);
            RwV3dAssign(RwIm3DVertexGetPos(&vertices[i]), &pos[i]);
            RwIm3DVertexSetU(&vertices[i], uvs[i].x);
            RwIm3DVertexSetV(&vertices[i], uvs[i].y);
        }

        if (RwIm3DTransform(vertices, std::size(vertices), nullptr, rwIM3D_VERTEXUV)) {
            RwIm3DRenderIndexedPrimitive(rwPRIMTYPETRILIST, indices, std::size(indices));
            RwIm3DEnd();
        }
    }

    RwRenderStateSet(rwRENDERSTATEFOGENABLE,         RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,          RWRSTATE(rwBLENDSRCALPHA));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,         RWRSTATE(rwBLENDINVSRCALPHA));
}

// ANDROID 1.0 0x5078B8
void CMirrors::RenderReflBuffer(bool) {

}

// ANDROID 1.0 0x507B2C
void CMirrors::RenderReflections() {

}

// 0x7266B0
void CMirrors::BuildCameraMatrixForScreens(CMatrix & mat) {
    const uint32 timeSeconds = (CTimer::GetTimeInMS() / 1000) % 32; // Wrapped to (0, 32]
    const uint32 timeMsLeftInSecond = CTimer::GetTimeInMS() % 1000;

    switch (timeSeconds) {
    case 0:
    case 1:
    case 2:
    case 3: {
        BuildCamMatrix(
            mat,
            { ((float)timeMsLeftInSecond / 1000.0f + (float)timeSeconds) * 6.0f - 1249.3f, -224.5f, 1064.2f },
            { -1265.4f, -207.5f, 1053.2f }
        );
        break;
    }
    case 10:
    case 11:
    case 12:
    case 13: {
        BuildCamMatrix(mat,
            { -1406.4f, -135.3f, 1045.65f },
            { -1402.5f, -146.8f, 1043.10f }
        );
        break;
    }
    case 22:
    case 23:
    case 24:
    case 25: {
        BuildCamMatrix(mat,
            { -1479.0f, -290.5f, 1099.54f },
            { -1428.0f, -256.7f, ((float)timeMsLeftInSecond / 1000.0f + (float)(timeSeconds - 22)) * 3.0f + 1057.3f }
        );
        break;
    }
    default: {
        mat.SetRotateZOnly((CTimer::GetTimeInMS() % 16384) * 0.00038349521f);
        mat.SetTranslateOnly({ -1397.0f, -219.0f, 1054.0f });
        break;
    }
    }
}

// NOTSA, inlined, line 67
bool CMirrors::IsEitherScreenVisibleToCam() {
    for (int i = 0; i < 2; i++) {
        TheCamera.m_bMirrorActive = false;
        auto origin = CVector::AverageN(std::begin(Screens8Track[i]), 4);
        if (TheCamera.IsSphereVisible(origin, 8.0f)) {
            return false;
        }
    }
    return false;
}

// 0x726DF0
void CMirrors::BeforeConstructRenderList() {
    if (d3dRestored) {
        d3dRestored = false;
        Init();
    }

    const auto TryUpdate = [] {
        // Check player is in heli/plane
        if (CVehicle* veh = FindPlayerVehicle()) {
            if (veh->IsSubHeli() || veh->IsSubPlane())
                return false;
        }

        CCullZoneReflection* mirrorAttrs = CCullZones::FindMirrorAttributesForCoors_(TheCamera.GetPosition());
        if (!mirrorAttrs)
            return false;

        if (mirrorAttrs->flags & CAM_STAIRS_FOR_PLAYER) {
            if (!IsEitherScreenVisibleToCam())
                return false;
        }

        // Actually update cam

        MirrorV = mirrorAttrs->cm;
        MirrorNormal = CVector{
            (float)mirrorAttrs->vx,
            (float)mirrorAttrs->vy,
            (float)mirrorAttrs->vz,
        } / 100.0f;
        MirrorFlags = mirrorAttrs->flags;

        TypeOfMirror = (fabs(MirrorNormal.z) <= 0.7f) ? 1 : 2;
        CreateBuffer();

        return true;
    };

    if (!TryUpdate()) {
        ShutDown();
    }

    if (MirrorFlags & CAM_STAIRS_FOR_PLAYER || bFudgeNow) {
        CMatrix mat{};
        BuildCameraMatrixForScreens(mat);
        TheCamera.DealWithMirrorBeforeConstructRenderList(true, MirrorNormal, MirrorV, &mat);
    } else {
        TheCamera.DealWithMirrorBeforeConstructRenderList(true, MirrorNormal, MirrorV, nullptr);
    }
}

void RenderScene();

// 0x727140
void CMirrors::BeforeMainRender() {
    if (TypeOfMirror == 0)
        return;

    RwRaster* prevCamRaster  = RwCameraGetRaster(Scene.m_pRwCamera);
    RwRaster* prevCamZRaster = RwCameraGetZRaster(Scene.m_pRwCamera);

    RwCameraSetRaster(Scene.m_pRwCamera, pBuffer);
    RwCameraSetZRaster(Scene.m_pRwCamera, pZBuffer);

    TheCamera.SetCameraUpForMirror();

    RwRGBA color{ 0, 0, 0, 0xFF };
    RwCameraClear(Scene.m_pRwCamera, &color, rwCAMERACLEARZ | rwCAMERACLEARIMAGE | (GraphicsLowQuality() ? rwCAMERACLEARSTENCIL : 0));
    if (RsCameraBeginUpdate(Scene.m_pRwCamera)) {
        bRenderingReflection = true;
        DefinedState();
        RenderScene();
        CVisibilityPlugins::RenderWeaponPedsForPC();
        CVisibilityPlugins::ms_weaponPedsForPC.Clear();
        bRenderingReflection = false;

        RwCameraEndUpdate(Scene.m_pRwCamera);

        RwCameraSetRaster(Scene.m_pRwCamera, prevCamRaster);
        RwCameraSetZRaster(Scene.m_pRwCamera, prevCamZRaster);

        TheCamera.RestoreCameraAfterMirror();
    }
}

// 0x53DF40
void RenderScene() {
    bool underWater = CWeather::UnderWaterness <= 0.0f;

    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,     RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,       RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,      RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, RWRSTATE(FALSE));

    if (CMirrors::TypeOfMirror == 0) {
        CMovingThings::Render_BeforeClouds();
        CClouds::Render();
    }

    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,  RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE, RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,    RWRSTATE(rwSHADEMODEGOURAUD));

    CCarFXRenderer::PreRenderUpdate();
    CRenderer::RenderRoads();
    CCoronas::RenderReflections();
    CRenderer::RenderEverythingBarRoads();
    g_breakMan.Render(false);

    CRenderer::RenderFadingInUnderwaterEntities();
    if (underWater) {
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
        CWaterLevel::RenderWater();
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
    }

    CRenderer::RenderFadingInEntities();
    if (!CMirrors::bRenderingReflection) {
        float nearClipPlaneOld = RwCameraGetNearClipPlane(Scene.m_pRwCamera);
        float farPlane  = RwCameraGetFarClipPlane(Scene.m_pRwCamera);

        float v3;
        float z = TheCamera.GetActiveCamera().m_vecFront.z;
        if (z <= 0.0f)
            v3 = -z;
        else
            v3 = 0.0f;

        constexpr float flt_8CD4F0 = 2.0f;
        constexpr float flt_8CD4EC = 5.9604645e-8f;

        float unknown = ((flt_8CD4F0 * flt_8CD4EC * 0.25f - flt_8CD4F0 * flt_8CD4EC) * v3 + flt_8CD4F0 * flt_8CD4EC) * (farPlane - nearClipPlaneOld);

        RwCameraEndUpdate(Scene.m_pRwCamera);
        RwCameraSetNearClipPlane(Scene.m_pRwCamera, unknown + nearClipPlaneOld);
        RwCameraBeginUpdate(Scene.m_pRwCamera);
        CShadows::UpdateStaticShadows();
        CShadows::RenderStaticShadows();
        CShadows::RenderStoredShadows();
        RwCameraEndUpdate(Scene.m_pRwCamera);
        RwCameraSetNearClipPlane(Scene.m_pRwCamera, nearClipPlaneOld);
        RwCameraBeginUpdate(Scene.m_pRwCamera);
    }

    g_breakMan.Render(true);
    CPlantMgr::Render();

    RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));

    if (CMirrors::TypeOfMirror == 0) {
        CClouds::RenderBottomFromHeight();
        CWeather::RenderRainStreaks();
        CCoronas::RenderSunReflection();
    }

    if (underWater) {
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLNONE));
        CWaterLevel::RenderWater();
        RwRenderStateSet(rwRENDERSTATECULLMODE, RWRSTATE(rwCULLMODECULLBACK));
    }

    gRenderStencil();
}
