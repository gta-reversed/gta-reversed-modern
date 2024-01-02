#include "StdInc.h"

#include "StencilShadowObject.h"

void CStencilShadowObject::InjectHooks() {
    RH_ScopedClass(CStencilShadowObject);
    RH_ScopedCategoryGlobal();

    RH_ScopedInstall(Shutdown, 0x711390, { .reversed = false });
    RH_ScopedInstall(Render, 0x710D50, { .reversed = false });
    RH_ScopedInstall(RenderForVehicle, 0x70FAE0, { .reversed = false });
    RH_ScopedInstall(RenderForObject, 0x710310, { .reversed = false });
}

// 0x711280
CStencilShadowObject::CStencilShadowObject() {
    plugin::CallMethod<0x711280, CStencilShadowObject*>(this);
}

// 0x711310
CStencilShadowObject::~CStencilShadowObject() {
    plugin::CallMethod<0x711310, CStencilShadowObject*>(this);
}

// 0x711390
void CStencilShadowObject::Shutdown() {
    plugin::Call<0x711390>();
}

// 0x710D50
void CStencilShadowObject::Render(CRGBA* color) {
    plugin::Call<0x710D50, CRGBA*>(color);
}

// 0x70FAE0
void CStencilShadowObject::RenderForVehicle(CDummy* dummy) {
    plugin::Call<0x70FAE0, CDummy*>(dummy);
}

// 0x710310
void CStencilShadowObject::RenderForObject(CStencilShadowObject* object) {
    plugin::Call<0x710310, CStencilShadowObject*>(object);
}

// 0x7113B0
bool gRenderStencil() {
    return plugin::CallAndReturn<bool, 0x7113B0>();

    // todo:
    const auto depth = RwRasterGetDepth(RwCameraGetRaster(Scene.m_pRwCamera));
    if ( g_fx.GetFxQuality() < FX_QUALITY_MEDIUM || depth < 32 )
        return false;

    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,                RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,            RWRSTATE(0));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESRCBLEND,                 RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,                RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONMASK,      RWRSTATE(uint32(-1)));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONWRITEMASK, RWRSTATE(uint32(-1)));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTION,          RWRSTATE(8u));
    RwRenderStateSet(rwRENDERSTATESTENCILFAIL,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILPASS,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONREF,       RWRSTATE(0));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(7u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(3u));

    const auto black = CRGBA(0, 0, 0, 255);
    // RenderStencil(black); // 0x710D50

    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(8u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(2u));

    // RenderStencil(black);

    // WTF is up with these states?
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(FALSE)); // same state
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEFOGENABLE,                RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(TRUE)); // same state
    RwRenderStateSet(rwRENDERSTATESRCBLEND,                 RWRSTATE(5u));
    RwRenderStateSet(rwRENDERSTATEDESTBLEND,                RWRSTATE(6u));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATETEXTURERASTER,            RWRSTATE(NULL));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTIONREF,       RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILFUNCTION,          RWRSTATE(4u));
    RwRenderStateSet(rwRENDERSTATESTENCILFAIL,              RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILZFAIL,             RWRSTATE(1u));
    RwRenderStateSet(rwRENDERSTATESTENCILPASS,              RWRSTATE(1u));

    CSprite2d::InitPerFrame();

    auto color = CRGBA(0, 0, 0, 50u);
    color.a = (color.a * CTimeCycle::m_CurrentColours.m_nShadowStrength) >> 8;
    CRect rect(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT);
    CSprite2d::DrawRect(rect, color);

    RwRenderStateSet(rwRENDERSTATESTENCILENABLE,            RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATEZWRITEENABLE,             RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEZTESTENABLE,              RWRSTATE(TRUE));
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE,        RWRSTATE(FALSE));
    RwRenderStateSet(rwRENDERSTATESHADEMODE,                RWRSTATE(2u));
    RwRenderStateSet(rwRENDERSTATECULLMODE,                 RWRSTATE(2u));

    return true;
}
