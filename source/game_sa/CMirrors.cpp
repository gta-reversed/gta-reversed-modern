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
float* Screens8Track = (float*)0x8D5DD8;

void CMirrors::InjectHooks() {
    ReversibleHooks::Install("CMirrors", "Init", 0x723000, &CMirrors::Init);
    ReversibleHooks::Install("CMirrors", "ShutDown", 0x723050, &CMirrors::ShutDown);
    // ReversibleHooks::Install("CMirrors", "CreateBuffer", 0x7230A0, &CMirrors::CreateBuffer);
    // ReversibleHooks::Install("CMirrors", "BuildCamMatrix", 0x723150, &CMirrors::BuildCamMatrix);
    // ReversibleHooks::Install("CMirrors", "RenderMirrorBuffer", 0x726090, &CMirrors::RenderMirrorBuffer);
    // ReversibleHooks::Install("CMirrors", "BuildCameraMatrixForScreens", 0x7266B0, &CMirrors::BuildCameraMatrixForScreens);
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
    plugin::Call<0x7230A0>();
}

// 0x723150
void CMirrors::BuildCamMatrix(const CMatrix& mat, CVector pointA, CVector pointB) {
    plugin::Call<0x723150, const CMatrix&, CVector, CVector>(mat, pointA, pointB);
}

// 0x726090
void CMirrors::RenderMirrorBuffer() {
    plugin::Call<0x726090>();
}

// 0x7266B0
void CMirrors::BuildCameraMatrixForScreens(const CMatrix& mat) {
    plugin::Call<0x7266B0, const CMatrix&>(mat);
}

// 0x726DF0
void CMirrors::BeforeConstructRenderList() {
    plugin::Call<0x726DF0>();
}

// 0x727140
void CMirrors::BeforeMainRender() {
    plugin::Call<0x727140>();
}
